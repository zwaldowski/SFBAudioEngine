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

#pragma once

#include <iostream>
#include <CoreFoundation/CoreFoundation.h>

/*! @file Semaphore.h @brief A class for multi-threaded data flow and access control. */

/*! @brief \c SFBAudioEngine's encompassing namespace */
namespace SFB {

	/*! @brief %Threading functionality */
	namespace Dispatch {
		/*! @brief Internal implementation, wraps dispatch_semaphore_t. */
		struct SemaphoreImpl;

		/*! @brief A wrapper around a native semaphore. */
		class Semaphore
		{
		public:
			
			// ========================================
			/*! @name Factory Methods */
			//@{
			
			/*! @brief A \c std::unique_ptr for \c Semaphore objects */
			typedef std::unique_ptr<Semaphore> unique_ptr;
			
			//@}
			
			// ========================================
			/*! @name Creation and Destruction */
			// @{
			
			/*!
			 * @brief Create a new \c Semaphore
			 * @throws std::runtime_exception
			 */
			inline Semaphore() : Semaphore(0) { };
			
			/*!
			 * @brief Create a new \c Semaphore
			 * @param count The starting value for the semaphore. Waiting and
			 * signalling the semaphore will decrement and increment this count,
			 * respectively.
			 * @throws std::runtime_exception
			 */
			Semaphore(long count);
			
			/*! @brief Destroy this \c Semaphore */
			~Semaphore();
			
			/*! @cond */
			
			/*! @internal This class is non-copyable */
			Semaphore(const Semaphore& rhs) = delete;
			
			/*! @internal This class is non-assignable */
			Semaphore& operator=(const Semaphore& rhs) = delete;
			
			/*! @endcond */
			
			//@}
						
			/*!
			 * @brief Signal the \c Semaphore to wake a blocked thread
			 * @return \c true if successful, \c false otherwise
			 */
			bool Signal();
			
			/*!
			 * @brief Block the calling thread until the \c Semaphore is signaled
			 * @return \c true if successful, \c false otherwise
			 */
			bool Wait();
			
			/*!
			 * @brief Block the calling thread until the \c Semaphore is signaled
			 * @param duration The maximum duration to block
			 * @return \c true if successful, \c false otherwise
			 */
			bool Wait(CFTimeInterval duration);
		private:
			std::unique_ptr<SemaphoreImpl> mPrivate;
		};
	}
}
