/*
 *  Copyright (C) 2014 Zach Waldowski <zach@waldowski.me>
 *  Copyright (C) 2010-2013 Stephen F. Booth <me@sbooth.org>
 *  All Rights Reserved.
 *
 *  Redistribution and use in source and binary forms, with or without
 *  modification, are permitted provided that the following conditions are
 *  met:
 *
 *    - Redistributions of source code must retain the above copyright
 *      notice, this list of conditions and the following disclaimer.
 *    - Redistributions in binary form must reproduce the above copyright
 *      notice, this list of conditions and the following disclaimer in the
 *      documentation and/or other materials provided with the distribution.
 *    - Neither the name of Stephen F. Booth nor the names of its
 *      contributors may be used to endorse or promote products derived
 *      from this software without specific prior written permission.
 *
 *  THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS
 *  "AS IS" AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT
 *  LIMITED TO, THE IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR
 *  A PARTICULAR PURPOSE ARE DISCLAIMED. IN NO EVENT SHALL THE COPYRIGHT
 *  HOLDER OR CONTRIBUTORS BE LIABLE FOR ANY DIRECT, INDIRECT, INCIDENTAL,
 *  SPECIAL, EXEMPLARY, OR CONSEQUENTIAL DAMAGES (INCLUDING, BUT NOT
 *  LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES; LOSS OF USE,
 *  DATA, OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER CAUSED AND ON ANY
 *  THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT
 *  (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE
 *  OF THIS SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.
 */

#include "Queue.h"

#include "CFWrapper.h"
#include "DispatchWrapper.h"
#include "Logger.h"

#include <mach/mach_time.h>
#include <dispatch/dispatch.h>
#include <pthread.h>
#include <set>
#include <map>

using namespace SFB::Dispatch;

namespace {
	static const void *IsCurrentKey = &IsCurrentKey;
	static int IsCurrentValue = 1;
	static const void *QueueStackKey = &QueueStackKey;
	
	typedef std::set<QueueImpl *> QueueStack;
	
	static QueueStack *GetQueueStack(dispatch_queue_t q)
	{
		void *context = dispatch_queue_get_specific(q, QueueStackKey);
		auto setPtr = static_cast<QueueStack *>(context);
		return setPtr;
	}
	
	static void DestroyQueueStack(void *context)
	{
		auto setPtr = static_cast<QueueStack *>(context);
		delete setPtr;
	}
	
	static CFTimeInterval Now()
	{
		static mach_timebase_info_data_t info;
		static dispatch_once_t pred;
		dispatch_once(&pred, ^{ mach_timebase_info(&info); });
		
		uint64_t t = mach_absolute_time();
		t *= info.numer;
		t /= info.denom;
		return t / NSEC_PER_SEC;
	}
	
	static CFStringRef GetDispatchQueueLabel(dispatch_queue_t q)
	{
		const char *labelStr = dispatch_queue_get_label(q);
		CFStringRef label = labelStr ? CFStringCreateWithCString(NULL, labelStr, kCFStringEncodingUTF8) : CFSTR("unlabeled");
		return label;
	}
}

namespace SFB {
	namespace Dispatch {
		struct Timer
		{
		public:
			Timer()
			: mBlock(nullptr), source(nullptr), nextScheduled(0), interval(0), tolerance(0) { }
			
			Timer(dispatch_block_t iBlock, dispatch_source_t iSource, CFTimeInterval iInterval, CFTimeInterval iTolerance)
			: source(iSource), interval(iInterval), tolerance(iTolerance), nextScheduled(DBL_MAX) {
				block(iBlock);
			}
			
			~Timer() {
				block(nullptr);
			}
			
			dispatch_block_t const block() { return mBlock; }
			void const block(dispatch_block_t block) {
				dispatch_block_t old = mBlock;
				if (block) {
					mBlock = Block_copy(block);
				} else {
					mBlock = nullptr;
				}
				if (old != nullptr) {
					Block_release(block);
				}
			}
			
			dispatch_source source;
			CFTimeInterval nextScheduled;
			CFTimeInterval interval;
			CFTimeInterval tolerance;
		private:
			dispatch_block_t mBlock;
		};
		
		struct QueueImpl
		{
			QueueImpl(dispatch_queue_t iQueue, bool iConcurrent = false) : queue(iQueue), concurrent(iConcurrent) {
				if (!queue) {
					LOGGER_CRIT("org.sbooth.AudioEngine.Dispatch_Queue", "dispatch_queue creation failed.");
					throw std::runtime_error("Unable to create the queue");
				}
				dispatch_queue_set_specific(queue, IsCurrentKey, &IsCurrentValue, NULL);
			}
			
			bool IsCurrentQueue() {
				return (dispatch_get_specific(IsCurrentKey) == &IsCurrentValue);
			}
			
			bool IsMainQueue() {
				return (pthread_main_np() != 0);
			}
			
			CFStringRef GetLabel()
			{
				return GetDispatchQueueLabel(queue);
			}
			
			QueueStack *GetQueueStack()
			{
				return ::GetQueueStack(queue);
			}
			
			bool IsInQueueStack()
			{
				QueueStack *stack = ::GetQueueStack(queue);
				if (stack == nullptr) {
					return false;
				}
				return stack->find(this) != stack->end();
			}
			
			bool IsConcurrent()
			{
				return concurrent;
			}
			
			void DispatchSync(::Block block)
			{
				auto stack = GetQueueStack();
				bool newStack = false;
				if (stack == nullptr) {
					stack = new QueueStack();
					newStack = true;
				}
				
				// dispatch_queue_set_specific should be serialized within the queue, so it's consistent from one block execution to the next
				dispatch_sync(queue, ^{
					DispatchSerialGuard(block, concurrent, stack, newStack);
				});
			}
			
			void DispatchAsync(::Block block)
			{
				if (concurrent) {
					dispatch_async(queue, block);
				} else {
					dispatch_async(queue, ^{
						DispatchAsyncSerial(block);
					});
				}
			}
			
			void DispatchAsyncBlockingCaller(void(^task)(dispatch_block_t enter, dispatch_block_t exit)){
				dispatch_group group = dispatch_group_create();
				
				dispatch_block_t block = ^{
					task(^{
						dispatch_group_enter(group);
					}, ^{
						dispatch_group_leave(group);
					});
				};
				
				if (concurrent) {
					dispatch_group_async(group, queue, block);
				} else {
					dispatch_group_async(group, queue, ^{
						DispatchAsyncSerial(block);
					});
				}
				
				dispatch_group_wait(group, DISPATCH_TIME_FOREVER);
			}
			
			void ScheduleTask(CFStringRef name, CFTimeInterval interval, ::Block block, Queue::TimerBehavior timerBehavior, CFTimeInterval tolerance)
			{
				CFTimeInterval dispatchedTime = Now();
				DispatchAsync(^{
					Timer timer;
					bool needsHandler = false;
					if (timers.find(name) != timers.end()) {
						timer = timers[name];
						needsHandler = (timer.block() != block);
					} else {
						timer = Timer(block, nullptr, interval, tolerance);
						needsHandler = true;
					}
					ScheduleTaskInner(name, timer, false, needsHandler, timerBehavior, dispatchedTime);
				});
			}
			
			void SignalTask(CFStringRef name, bool cancel, dispatch_block_t enter = nullptr, dispatch_block_t exit = nullptr)
			{
				Timer time = timers[name];
				dispatch_block_t block = Block_copy(time.block());
				if (!block) return;
				
				if (enter) enter();
				block();
				Block_release(block);
				if (cancel) {
					CancelTask(name);
				} else {
					RescheduleTask(name, time);
				}
				if (exit) exit();
			}
			
			void SignalAllTasks(bool cancel, dispatch_block_t enter = nullptr, dispatch_block_t exit = nullptr)
			{
				for (auto it : timers) {
					CFStringRef name = it.first;
					Timer timer = it.second;
					dispatch_block_t block = Block_copy(timer.block());
					
					if (!block) continue;
					if (enter) enter();
					block();
					Block_release(block);
					if (cancel) {
						CancelTask(name);
					} else {
						RescheduleTask(name, timer);
					}
					if (exit) exit();
				}
				timers.clear();
			}
			
			void CancelTask(CFStringRef name)
			{
				CancelTimerNamed(name, NULL);
			}
			
			void CancelAllTasks()
			{
				for (auto it : timers) {
					CancelTimer(it.second, NULL);
				}
				timers.clear();
			}
			
		private:
			
			void DispatchAsyncSerial(::Block block)
			{
				if (GetQueueStack() != nullptr) {
					throw std::runtime_error("There should be no queue stack set before execution of a block dispatched asynchronously.");
				}
				DispatchSerialGuard(block, false, new QueueStack(), true);
			}
			
			void DispatchSerialGuard(::Block block, bool actConcurrent, QueueStack *stack, bool isNewStack)
			{
				if (!actConcurrent) {
					stack->insert(this);
				}
				dispatch_queue_set_specific(queue, QueueStackKey, stack, DestroyQueueStack);
				
				block();
				
				QueueStack::reverse_iterator last = stack->rbegin();
				if (*last != this) {
					throw std::runtime_error("The queue stack set after execution of a block should have the parent queue as the last object.");
				}
				
				if (!actConcurrent) {
					stack->erase(*last);
				}
				
				if (isNewStack && !stack->empty()) {
					throw std::runtime_error("The queue stack should be empty after execution of a block dispatched asynchronously.");
				}
				
				dispatch_queue_set_specific(queue, QueueStackKey, NULL, NULL);
			}
			
			void RescheduleTask(CFStringRef name, Timer timer)
			{
				if (timers.find(name) == timers.end()) {
					return;
				}
				ScheduleTaskInner(name, timer, true, false);
			}
			
			void ScheduleTaskInner(CFStringRef name, Timer timer, bool forceReset, bool rescheduleHandler, Queue::TimerBehavior timerBehavior = Queue::TimerBehavior::RepeatingCoalesce, CFTimeInterval dispatchedTime = Now())
			{
				bool newTimer = false;
				dispatch_source source = timer.source;
				if (!source) {
					newTimer = true;
					source = dispatch_source_create(DISPATCH_SOURCE_TYPE_TIMER, 0, 0, queue);
					timer.source = source;
					rescheduleHandler = true;
				}
				
				bool delayBehavior = (timerBehavior == Queue::TimerBehavior::OnceReset || timerBehavior == Queue::TimerBehavior::RepeatingReset);
				bool cancelAfterFirstRun = (timerBehavior == Queue::TimerBehavior::OnceCoalesce || timerBehavior == Queue::TimerBehavior::OnceReset);
				
				CFTimeInterval nextFire = timer.nextScheduled;
				CFTimeInterval now = Now();
				CFTimeInterval adjustedDelay = MAX(0, timer.interval - (now - dispatchedTime));
				CFTimeInterval newFireTime = now + adjustedDelay;
				if (forceReset || nextFire == DBL_MAX || delayBehavior || newFireTime < nextFire)
				{
					dispatch_time_t start = dispatch_time(DISPATCH_TIME_NOW, (int64_t)(adjustedDelay * NSEC_PER_SEC));
					uint64_t interval = (uint64_t)(timer.interval * NSEC_PER_SEC);
					uint64_t leeway = (uint64_t)(timer.tolerance * NSEC_PER_SEC);
					dispatch_source_set_timer(source, start, interval, leeway);
				}
				timer.nextScheduled = newFireTime;
				
				if (rescheduleHandler) {
					::Block block = timer.block();
					if (concurrent) {
						dispatch_source_set_event_handler(source, ^{
							block();
							if (cancelAfterFirstRun) {
								CancelTimerNamed(name, NULL);
							}
						});
					} else {
						dispatch_source_set_event_handler(source, ^{
							DispatchAsyncSerial(block);
							if (cancelAfterFirstRun) {
								CancelTimerNamed(name, NULL);
							}
						});
					}
				}
				
				if (newTimer) {
					dispatch_resume(source);
				}
				
				timers[name] = timer;
			}
			
			bool CancelTimerNamed(CFStringRef timerName, void(^onCancel)(Timer))
			{
				Timer timer = timers[timerName];
				if (CancelTimer(timer, onCancel)) {
					timers.erase(timerName);
					return true;
				}
				return false;
			}
			
			bool CancelTimer(Timer timer, void(^onCancel)(Timer))
			{
				dispatch_source_t source = timer.source;
				if (!source) {
					return false;
				}
				if (onCancel) {
					dispatch_source_set_cancel_handler(source, ^{
						onCancel(timer);
					});
				}
				dispatch_source_cancel(source);
				return true;
			}
			
			dispatch_queue queue;
			bool concurrent;
			std::map<CFString, Timer> timers;
		};
	}
}

Queue *Queue::Global()
{
	static Queue::unique_ptr mGlobalQueue;
	static std::once_flag mGlobalQueueInit;
	std::call_once(mGlobalQueueInit, ^{
		dispatch_queue_t globalQ = dispatch_get_global_queue(DISPATCH_QUEUE_PRIORITY_DEFAULT, 0);
		mGlobalQueue.reset(new Queue(new QueueImpl(dispatch_queue(globalQ, false), true), DeadlockBehavior::Block));
	});
    return mGlobalQueue.get();
}

Queue *Queue::Main()
{
	static Queue::unique_ptr mMainQueue;
	static std::once_flag mMainQueueInit;
	std::call_once(mMainQueueInit, ^{
		dispatch_queue_t mainQ = dispatch_get_main_queue();
		mMainQueue.reset(new Queue(new QueueImpl(dispatch_queue(mainQ, false), false), DeadlockBehavior::Block));
	});
    return mMainQueue.get();
}

Queue::unique_ptr Queue::Create(const char *label, DeadlockBehavior behavior, bool concurrent)
{
	dispatch_queue_t q = dispatch_queue_create(label, concurrent ? DISPATCH_QUEUE_CONCURRENT : DISPATCH_QUEUE_SERIAL);
	
	return unique_ptr(new Queue(new QueueImpl(q, concurrent), behavior));
}

Queue::Queue() : mPrivate(nullptr) { }

Queue::Queue(QueueImpl *impl, DeadlockBehavior behavior) : mPrivate(nullptr), mDeadlockBehavior(behavior) {
	mPrivate.reset(impl);
}

Queue::~Queue() { }

CFStringRef Queue::GetDescription()
{
	return CFStringCreateWithFormat(nullptr, nullptr, CFSTR("<DispatchQueue: %p>[%@]"), this, mPrivate->GetLabel());
}

CFStringRef Queue::GetLabel()
{
	return mPrivate->GetLabel();
}

bool Queue::IsConcurrent()
{
	return mPrivate->IsConcurrent();
}

bool Queue::IsCurrentQueue()
{
	return mPrivate->IsCurrentQueue();
}

bool Queue::IsMainQueue()
{
	return this == Queue::Main();
}

bool Queue::IsInCurrentQueueStack()
{
	// main queue is easier and safer to assert
	if (IsMainQueue()) {
		return mPrivate->IsMainQueue();
	}
	return mPrivate->IsInQueueStack();
}

void Queue::DispatchSync(::Block block)
{
	DeadlockBehavior behavior = mDeadlockBehavior;
	
	if (behavior == DeadlockBehavior::Block || !IsInCurrentQueueStack()) {
		mPrivate->DispatchSync(block);
	} else {
		if (behavior == DeadlockBehavior::Execute) {
			block();
		} else if (behavior == DeadlockBehavior::Log) {
			LOGGER_WARNING("org.sbooth.AudioEngine.DispatchQueue", "Synchronous dispatch can not be executed on the queue with label '" << GetLabel() << "' because it is already part of the current dispatch queue hierarchy.");
		} else if (behavior == DeadlockBehavior::Assert) {
			std::stringstream ss;
			ss << "Synchronous dispatch can not be executed on the queue with label '" << GetLabel() << "' because it is already part of the current dispatch queue hierarchy.";
			throw std::runtime_error(ss.str());
		}
	}
}

void Queue::DispatchAsync(::Block block)
{
	mPrivate->DispatchAsync(block);
}

void Queue::ScheduleTask(CFStringRef name, CFTimeInterval delay, ::Block block, TimerBehavior behavior, CFTimeInterval tolerance)
{
	mPrivate->ScheduleTask(name, delay, block, behavior, tolerance);
}

void Queue::SignalTask(CFStringRef name, bool waitForCompletion, bool cancel)
{
	if (waitForCompletion) {
		mPrivate->DispatchAsyncBlockingCaller(^(dispatch_block_t enter, dispatch_block_t exit){
			mPrivate->SignalTask(name, cancel, enter, exit);
		});
	} else {
		DispatchAsync(^{
			mPrivate->SignalTask(name, cancel);
		});
	}
}

void Queue::SignalAllTasks(bool waitForCompletion, bool cancel)
{
	if (waitForCompletion) {
		mPrivate->DispatchAsyncBlockingCaller(^(dispatch_block_t enter, dispatch_block_t exit){
			mPrivate->SignalAllTasks(cancel, enter, exit);
		});
	} else {
		DispatchAsync(^{
			mPrivate->SignalAllTasks(cancel);
		});
	}
}

void Queue::CancelTask(CFStringRef name)
{
	DispatchAsync(^{
		mPrivate->CancelTask(name);
	});
}

void Queue::CancelAllTasks()
{
	DispatchAsync(^{
		mPrivate->CancelAllTasks();
    });
}
