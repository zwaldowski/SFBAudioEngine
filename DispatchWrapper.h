/*
 *  Copyright (C) 2012-2014 Stephen F. Booth <me@sbooth.org>
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

#ifdef __OBJC__
#error Wrapped Grand Central Dispatch objects cannot be compiled in Objective-C mode.
#endif

#include <iostream>
#include <dispatch/dispatch.h>

/*! @file DispatchWrapper.h @brief A wrapper around a Grand Central Dispatch object */

/*! @brief \c SFBAudioEngine's encompassing namespace */
namespace SFB {
	namespace Dispatch {
	
		/*!
		 * @brief A wrapper around a Grand Central Dispatch object
		 *
		 * \c Wrapper simplifies the use of CFTypes in C++ by wrapping a CF object, ensuring
		 * \c dispatch_release will be called when the \c Wrapper goes out of scope.
		 * @tparam T A \c CFType
		 */
		template <typename T>
		class Wrapper
		{
		public:
			
			// ========================================
			/*! @name Creation and Destruction */
			//@{
			
			/*! @brief Create a new \c Wrapper */
			inline Wrapper()						: Wrapper(nullptr)					{}
			
			/*!
			 * @brief Create a new \c Wrapper
			 * @note The \c Wrapper takes ownership of \c object
			 * @param object The object to wrap
			 */
			inline Wrapper(T object)				: Wrapper(object, true)				{}
			
			/*!
			 * @brief Create a new \c Wrapper
			 * @param object The object to wrap
			 * @param release Whether this \c Wrapper should take ownership of \c object
			 */
			Wrapper(T object, bool release)
			: mObject(object) , mRelease(release)
			{
			}
			
			
			/*! @brief Create a new \c Wrapper */
			Wrapper(Wrapper&& rhs)
			: mObject(rhs.mObject) , mRelease(rhs.mRelease)
			{
				rhs.mObject = nullptr;
			}
			
			/*! @brief Create a new \c Wrapper */
			Wrapper(const Wrapper& rhs)
			: mObject(rhs.mObject), mRelease(rhs.mRelease)
			{
				if(mObject && mRelease)
					dispatch_retain(mObject);
			}
			
			/*! @brief Destroy this \c Wrapper and ensure \c dispatch_release() is called if necessary */
			~Wrapper()
			{
				if(mObject && mRelease)
					dispatch_release(mObject);

				mObject = nullptr;
			}
			
			//@}
			
			
			/*! @name Assignment */
			//@{
			
			/*!
			 * @brief Replace the wrapped object
			 * @note The \c Wrapper takes ownership of \c rhs
			 * @param rhs The object to wrap
			 */
			Wrapper& operator=(const T& rhs)
			{
				if(mObject != rhs) {
					dispatch_object_t oldToRelease = nullptr;
					if(mObject && mRelease) {
						oldToRelease = mObject;
					}

					mObject = rhs;
					mRelease = true;
					
					if (oldToRelease != nullptr) {
						dispatch_release(oldToRelease);
					}
				}
				
				return *this;
			}
			
			/*! @brief Replace the wrapped object */
			Wrapper& operator=(const Wrapper& rhs)
			{
				if(mObject != rhs.mObject) {
					dispatch_object_t oldToRelease = nullptr;
					if (mObject && mRelease) {
						oldToRelease = mObject;
					}
					
					if (rhs.mObject && rhs.mRelease) {
						dispatch_retain(rhs.mObject);
					}
					
					mObject = rhs.mObject;
					mRelease = rhs.mRelease;
					
					if (oldToRelease != nullptr) {
						dispatch_release(oldToRelease);
					}
				}
				
				return *this;
			}
			
			/*! @brief Replace the wrapped object */
			Wrapper& operator=(Wrapper&& rhs)
			{
				if(mObject != rhs.mObject) {
					dispatch_object_t oldToRelease = nullptr;
					if(mObject && mRelease) {
						oldToRelease = mObject;
					}
					
					mObject = rhs.mObject;
					mRelease = rhs.mRelease;
					
					rhs.mObject = nullptr;
					
					if (oldToRelease != nullptr) {
						dispatch_release(oldToRelease);
					}
				}
				
				return *this;
			}
			
			//@}
			
			
			// ========================================
			/*! @name Pointer management */
			//@{
			
			/*! @brief Relinquish ownership of the wrapped object and return it */
			inline T Relinquish()
			{
				T object = mObject;
				mObject = nullptr;
				
				return object;
			}
			
			//@}
			
			
			// ========================================
			/*! @name Equality testing */
			//@{
			
			/*! @brief Test two \c Wrapper objects for equality using \c CFEqual() */
			inline bool operator==(const Wrapper& rhs) const
			{
				return (mObject == rhs.mObject);
			}
			
			/*! @brief Test two \c Wrapper objects for inequality */
			inline bool operator!=(const Wrapper& rhs) const		{ return !operator==(rhs); }
			
			//@}
			
			
			// ========================================
			/*! @name Grand Central Dispatch object access */
			//@{
			
			/*! @brief Check whether the wrapped object is not \c nullptr */
			inline explicit operator bool() const					{ return nullptr != mObject; }
			
			/*! @brief Check whether the wrapped object is \c nullptr */
			inline bool operator!() const							{ return nullptr == mObject; }
			
			/*! @brief Get the wrapped object */
			inline operator T() const								{ return mObject; }
			
			/*! @brief Get the wrapped object */
			inline T Object() const									{ return mObject; }
			
			//@}
			
		private:
			T mObject;				/*!< The Grand Central Dispatch object */
			bool mRelease;			/*!< Whether \c dispatch_release should be called on destruction or reassignment */
		};
		
		// ========================================
		// Typedefs for common Grand Central Dispatch types
		
		typedef Wrapper<dispatch_object_t> dispatch_object;					/*!< @brief A wrapped \c dispatch_object_t */
		typedef Wrapper<dispatch_queue_t> dispatch_queue;					/*!< @brief A wrapped \c dispatch_queue_t */
		typedef Wrapper<dispatch_group_t> dispatch_group;					/*!< @brief A wrapped \c dispatch_group_t */
		typedef Wrapper<dispatch_source_t> dispatch_source;					/*!< @brief A wrapped \c dispatch_source_t */
		typedef Wrapper<dispatch_semaphore_t> dispatch_semaphore;			/*!< @brief A wrapped \c dispatch_semaphore_t */
		typedef Wrapper<dispatch_data_t> dispatch_data;						/*!< @brief A wrapped \c dispatch_data_t */
		typedef Wrapper<dispatch_io_t> dispatch_io;							/*!< @brief A wrapped \c dispatch_io_t */
	}
}

/*! @cond */

template <typename T>
std::ostream& operator<<(std::ostream& out, SFB::Dispatch::Wrapper<T> obj)
{
	out << (T)obj;
	return out;
}

/*! @endcond */
