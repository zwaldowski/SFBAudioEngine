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

#pragma once

#include <iostream>
#include <CoreFoundation/CoreFoundation.h>

/*! @file Queue.h @brief A class for simplified queueing and timers. */

/*! @brief \c SFBAudioEngine's encompassing namespace */
namespace SFB {
	
	/*! @brief %Threading functionality */
	namespace Dispatch {
		// For possible conversion to lambdas
		typedef const dispatch_block_t Block;
		
		/*! @brief Internal implementation, wraps dispatch_queue_t. */
		struct QueueImpl;
		
		/*! @brief A wrapper around a native queue. */
		class Queue
		{
		public:
			// ========================================
			/*! @brief The response the queue will take to methods that
			 *  would cause it to deadlock. */
			enum DeadlockBehavior {
				Execute,		/*!< Execute synchronously on the calling thread. */
				Skip,		/*!< Ignore dispatches that would deadlock. */
				Log,			/*!< Log dispatches that would deadlock. */
				Assert,		/*!< Raise an exception instead of deadlocking. */
				Block		/*!< Carry through with deadlocking the recieving queue. */
			};
			
			/*! @brief Scheduling and re-scheduling behaviors for a timer. */
			enum TimerBehavior {
				OnceCoalesce,		/*!< Reschedulings will only run out the clock on the scheduling */
				OnceReset,			/*!< Reschedulings will reset (extend) the timer */
				RepeatingCoalesce,	/*!< Reschedulings will run out the clock on the next recurrance */
				RepeatingReset		/*!< Reschedulings will reset the recurring timer */
			};
			
			/*! @brief A \c std::shared_ptr for \c Queue objects */
			typedef std::unique_ptr<Queue> unique_ptr;
			
			// ========================================
			/*! @name Global queues */
			//@{

			static Queue *Global();
			static Queue *Main();

			//@}
			
			// ========================================
			/*! @name Creation and Destruction */
			//@{

			/*!
			 * @brief Create a new \c Queue
			 * @param label An optional character array label to attach to the queue.
			 * @param behavior An optional action the queue will take if it is instructed to perform a dispatch that results in a deadlock.
			 * @param concurrent Whether the queue should optionally parallelize dispatches.
			 */
			static unique_ptr Create(const char *label = nullptr, DeadlockBehavior behavior = DeadlockBehavior::Execute, bool concurrent = false);
			
			/*!
			 * @brief Create a new \c Queue
			 * @param label An optional string label to attach to the queue.
			 * @param behavior An optional action the queue will take if it is instructed to perform a dispatch that results in a deadlock.
			 * @param concurrent Whether the queue should optionally parallelize dispatches.
			 */
			static inline unique_ptr Create(CFStringRef label, DeadlockBehavior behavior = DeadlockBehavior::Execute, bool concurrent = false)
			{
				return Create(CFStringGetCStringPtr(label, kCFStringEncodingUTF8), behavior, concurrent);
			}
			
			/*! @brief Destroy this \c Queue */
			virtual ~Queue();
			
			/*! @cond */
			
			/*! @internal This class is non-copyable */
			Queue(const Queue& rhs) = delete;
			
			/*! @internal This class is non-assignable */
			Queue& operator=(const Queue& rhs) = delete;
			
			/*! @endcond */
			//@}
			
			/*! @brief Returns a textual description for debugging. */
			CFStringRef GetDescription();
			
			/*! @brief Returns the optional label given during initialization. */
			CFStringRef GetLabel();
			
			/*! @brief Returns the deadlocking behavior for this queue */
			inline DeadlockBehavior GetDeadlockBehavior() const { return mDeadlockBehavior; }
			
			/*! @brief Returns whether the queue executes dispatches in parallel */
			bool IsConcurrent();
			
			/*! @brief Returns whether the backing queue of this queue is the same as the calling queue. */
			bool IsCurrentQueue(void);
			
			/*!
			 * @brief Dispatches a block synchronously on the recieving queue.
			 * @remarks If this is called from the same \c Queue, behavior is defined by the \c DeadlockBehavior of the queue.
			 * @param block A no-return, no-parameter unit of work.
			 * @throws std::runtime_exception
			 */
			void DispatchSync(SFB::Dispatch::Block block);
			
			/*!
			 * @brief Dispatches a block asynchronously on the recieving queue.
			 * @remarks An asynchronous dispatch cannot be done from synchronous queue stacks generated by a parent of the recieving queue, and will raise an exception if encountered.
			 * @param block A no-return, no-parameter unit of work.
			 * @throws std::runtime_exception
			 */
			void DispatchAsync(SFB::Dispatch::Block block);
			
			/*!
			 * @brief Schedule or reschedule a recurring task on a queue.
			 * @param name A required unique name string key.
			 * @param interval A number of seconds after which the given block will be dispatches.
			 * @param block A no-return, no-parameter unit of work.
			 * @param behavior Whether the task will recur, and the action subsequent calls to this method with the same key. See \c TimerBehavior.
			 * @param tolerance An amount of variance in the timer, which can be used by the system to improve power consumption and performance.
			 */
			void ScheduleTask(CFStringRef name, CFTimeInterval interval, SFB::Dispatch::Block block, TimerBehavior behavior = OnceCoalesce, CFTimeInterval tolerance = 0);
			
			/*!
			 * @brief After scheduling a task, invoke it immediately.
			 * @remarks If no such timer is scheduled, nothing happens.
			 * @remarks If waitForCompletion is true and the calling queue is the target queue, behavior is defined by the \c DeadlockBehavior of the queue.
			 * @remarks If the timer in question is repeatable, it will be rescheduled as though it naturally reached a firing by the system.
			 * @remarks If the timer in question is not repeatable, it will be cancelled by this method.
			 * @param name The unique name string key of the scheduled task.
			 * @param waitForCompletion If true, the calling queue will be blocked until the timer firing is reached.
             * @param cancel If true, a recurring timer will not be rescheduled.
			 */
			void SignalTask(CFStringRef name, bool waitForCompletion = false, bool cancel = false);

			/*!
			 * @brief Invoke all scheduled tasks immediately.
			 * @warning It would not be wise to call this method on a global \c Queue.
			 * @remarks If waitForCompletion is true and the calling queue is the target queue, behavior is defined by the \c DeadlockBehavior of the queue.
			 * @remarks If any of the timers in question are repeatable, they will be rescheduled as though they were fired by the system.
			 * @remarks If any of the timer sin question are not repeatable, they will be cancelled by this method.
			 * @param waitForCompletion If true, the calling queue will be blocked until all timers have fired.
             * @param cancel If true, no recurring timers will be rescheduled.
			 */
			void SignalAllTasks(bool waitForCompletion = false, bool cancel = false);
			
			/*!
			 * @brief Cancel a task, allowing it no further dispatches.
			 * @remarks If no such timer is scheduled, nothing happens.
			 * @remarks This method will not cancelany in-progress executions of the task.
			 * @param name The unique name string key of the scheduled task.
			 */
			void CancelTask(CFStringRef name);
			
			/*!
			 * @brief Cancel all tasks, allowing no further dispatches.
			 * @warning It would not be wise to call this method on a global \c Queue.
			 * @remarks This method will not cancel any in-progress executions of any tasks.
			 */
			void CancelAllTasks();
		protected:
			/*! @brief Create a new \c Queue and initialize \c Queue::mPrivate to \c nullptr. */
			Queue();
		private:
			/*! @brief Create a new \c Decoder and initialize \c Queue::mPrivate to \c impl. */
			Queue(QueueImpl *impl, DeadlockBehavior behavior);
			
			// Data members
			std::unique_ptr<QueueImpl> mPrivate;
			DeadlockBehavior mDeadlockBehavior;
			
			// Internal methods
			bool IsMainQueue();
			bool IsInCurrentQueueStack();
		};
	}
}
