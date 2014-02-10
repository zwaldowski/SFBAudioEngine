/*
 *  Copyright (C) 2010, 2011, 2012, 2013 Stephen F. Booth <me@sbooth.org>
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

#include "Semaphore.h"

#include "CFWrapper.h"
#include "DispatchWrapper.h"
#include "Logger.h"

#include <dispatch/dispatch.h>

using namespace SFB::Dispatch;

namespace {
	static dispatch_time_t TimeFromNow(CFTimeInterval duration) {
		return dispatch_time(DISPATCH_TIME_NOW, (int64_t)(duration * NSEC_PER_SEC));
	}
}

namespace SFB {
	namespace Dispatch {
		struct SemaphoreImpl
		{
			SemaphoreImpl(dispatch_semaphore_t iSema) : semaphore(iSema) {
				if (!semaphore) {
					LOGGER_CRIT("org.sbooth.AudioEngine.Dispatch.Semaphore", "dispatch_semaphore_create failed.");
					throw std::runtime_error("Unable to create the semaphore");
				}
			}
			
			bool Signal()
			{
				return (dispatch_semaphore_signal(semaphore) != 0);
			}
			
			bool Wait()
			{
				return Wait(DISPATCH_TIME_FOREVER);
			}
			
			bool Wait(CFTimeInterval duration)
			{
				return Wait(TimeFromNow(duration));
			}
			
		private:
			
			bool Wait(dispatch_time_t time)
			{
				return (dispatch_semaphore_wait(semaphore, time) == 0);
			}
			
			dispatch_semaphore semaphore;
		};
	}
}

Semaphore::Semaphore(long count) : mPrivate(nullptr)
{
	mPrivate.reset(new SemaphoreImpl(dispatch_semaphore_create(count)));
}

Semaphore::~Semaphore() { }

bool Semaphore::Signal()
{
	return mPrivate->Signal();
}

bool Semaphore::Wait()
{
	return mPrivate->Wait();
}

bool Semaphore::Wait(CFTimeInterval duration)
{
	return mPrivate->Wait(duration);
}
