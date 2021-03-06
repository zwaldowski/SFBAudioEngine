/*
 *  Copyright (C) 2013 Stephen F. Booth <me@sbooth.org>
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

#include "RingBuffer.h"

#include <stdlib.h>
#include <algorithm>

namespace {

	/*!
	 * Copy non-interleaved audio from \c bufferList to \c buffers
	 * @param buffers The destination buffers
	 * @param destOffset The byte offset in \c buffers to begin writing
	 * @param bufferList The source buffers
	 * @param srcOffset The byte offset in \c bufferList to begin reading
	 * @param byteCount The number of bytes per non-interleaved buffer to read and write
	 */
	inline void StoreABL(unsigned char **buffers, size_t destOffset, const AudioBufferList *bufferList, size_t srcOffset, size_t byteCount)
	{
		for(UInt32 bufferIndex = 0; bufferIndex < bufferList->mNumberBuffers; ++bufferIndex)
			memcpy(buffers[bufferIndex] + destOffset, (unsigned char *)bufferList->mBuffers[bufferIndex].mData + srcOffset, byteCount);
	}

	/*!
	 * Copy non-interleaved audio from \c buffers to \c bufferList
	 * @param bufferList The destination buffers
	 * @param destOffset The byte offset in \c bufferList to begin writing
	 * @param buffers The source buffers
	 * @param srcOffset The byte offset in \c bufferList to begin reading
	 * @param byteCount The number of bytes per non-interleaved buffer to read and write
	 */
	inline void FetchABL(AudioBufferList *bufferList, size_t destOffset, const unsigned char **buffers, size_t srcOffset, size_t byteCount)
	{
		for(UInt32 bufferIndex = 0; bufferIndex < bufferList->mNumberBuffers; ++bufferIndex)
			memcpy((unsigned char *)bufferList->mBuffers[bufferIndex].mData + destOffset, buffers[bufferIndex] + srcOffset, byteCount);
	}

	/*!
	 * Return the smallest power of two value greater than \c x
	 * @param x A value in the range [2..2147483648]
	 * @return The smallest power of two greater than \c x
	 *
	 */
	__attribute__ ((const)) inline uint32_t NextPowerOfTwo(uint32_t x)
	{
#if 0
		assert(x > 1);
		assert(x <= ((UINT32_MAX / 2) + 1));
#endif

		return 1 << (32 - __builtin_clz(x - 1));
	}

}

#pragma mark Creation and Destruction

SFB::Audio::RingBuffer::RingBuffer()
	: mBuffers(nullptr), mNumberChannels(0), mCapacityFrames(0), mCapacityBytes(0), mReadPointer(0), mWritePointer(0)
{}

SFB::Audio::RingBuffer::~RingBuffer()
{
	Deallocate();
}

#pragma mark Buffer Management

bool SFB::Audio::RingBuffer::Allocate(const AudioStreamBasicDescription& format, size_t capacityFrames)
{
	if(!(kAudioFormatFlagIsNonInterleaved & format.mFormatFlags))
		return false;
	return Allocate(format.mChannelsPerFrame, format.mBytesPerFrame, capacityFrames);
}

bool SFB::Audio::RingBuffer::Allocate(UInt32 channelCount, UInt32 bytesPerFrame, size_t capacityFrames)
{
	Deallocate();

	// Round up to the next power of two
	capacityFrames = NextPowerOfTwo((uint32_t)capacityFrames);

	mNumberChannels = channelCount;
	mBytesPerFrame = bytesPerFrame;

	mCapacityFrames = capacityFrames;
	mCapacityFramesMask = capacityFrames - 1;

	mCapacityBytes = bytesPerFrame * capacityFrames;

	// One memory allocation holds everything- first the pointers followed by the deinterleaved channels
	size_t allocationSize = (mCapacityBytes + sizeof(unsigned char *)) * channelCount;
	unsigned char *memoryChunk = (unsigned char *)malloc(allocationSize);
	if(nullptr == memoryChunk)
		return false;

	// Zero the entire allocation
	memset(memoryChunk, 0, allocationSize);

	// Assign the pointers and channel buffers
	mBuffers = (unsigned char **)memoryChunk;
	memoryChunk += channelCount * sizeof(unsigned char *);
	for(UInt32 i = 0; i < channelCount; ++i) {
		mBuffers[i] = memoryChunk;
		memoryChunk += mCapacityBytes;
	}

	mReadPointer = 0;
	mWritePointer = 0;

	return true;
}

void SFB::Audio::RingBuffer::Deallocate()
{
	if(mBuffers)
		free(mBuffers), mBuffers = nullptr;
}


void SFB::Audio::RingBuffer::Reset()
{
	mReadPointer = 0;
	mWritePointer = 0;

	for(UInt32 i = 0; i < mNumberChannels; ++i)
		memset(mBuffers[i], 0, mCapacityBytes);
}

size_t SFB::Audio::RingBuffer::GetFramesAvailableToRead() const
{
	size_t w = mWritePointer;
	size_t r = mReadPointer;

	if(w > r)
		return w - r;
	else
		return (w - r + mCapacityFrames) & mCapacityFramesMask;
}

size_t SFB::Audio::RingBuffer::GetFramesAvailableToWrite() const
{
	size_t w = mWritePointer;
	size_t r = mReadPointer;

	if(w > r)
		return ((r - w + mCapacityFrames) & mCapacityFramesMask) - 1;
	else if(w < r)
		return (r - w) - 1;
	else
		return mCapacityFrames - 1;
}

size_t SFB::Audio::RingBuffer::ReadAudio(AudioBufferList *bufferList, size_t frameCount)
{
	if(0 == frameCount)
		return 0;

	size_t framesAvailable = GetFramesAvailableToRead();
	if(0 == framesAvailable)
		return 0;

	size_t framesToRead = std::min(framesAvailable, frameCount);
	size_t cnt2 = mReadPointer + framesToRead;

	size_t n1, n2;
	if(cnt2 > mCapacityFrames) {
		n1 = mCapacityFrames - mReadPointer;
		n2 = cnt2 & mCapacityFramesMask;
	}
	else {
		n1 = framesToRead;
		n2 = 0;
	}

	FetchABL(bufferList, 0, (const unsigned char **)mBuffers, mReadPointer * mBytesPerFrame, n1 * mBytesPerFrame);
	mReadPointer = (mReadPointer + n1) & mCapacityFramesMask;

	if(n2) {
		FetchABL(bufferList, n1 * mBytesPerFrame, (const unsigned char **)mBuffers, mReadPointer * mBytesPerFrame, n2 * mBytesPerFrame);
		mReadPointer = (mReadPointer + n2) & mCapacityFramesMask;
	}

	// Set the buffer sizes
	for(UInt32 bufferIndex = 0; bufferIndex < bufferList->mNumberBuffers; ++bufferIndex)
		bufferList->mBuffers[bufferIndex].mDataByteSize = (UInt32)(framesToRead * mBytesPerFrame);

	return framesToRead;
}

size_t SFB::Audio::RingBuffer::WriteAudio(const AudioBufferList *bufferList, size_t frameCount)
{
	if(0 == frameCount)
		return 0;

	size_t framesAvailable = GetFramesAvailableToWrite();
	if(0 == framesAvailable)
		return 0;

	size_t framesToWrite = std::min(framesAvailable, frameCount);
	size_t cnt2 = mWritePointer + framesToWrite;

	size_t n1, n2;
	if(cnt2 > mCapacityFrames) {
		n1 = mCapacityFrames - mWritePointer;
		n2 = cnt2 & mCapacityFramesMask;
	}
	else {
		n1 = framesToWrite;
		n2 = 0;
	}

	StoreABL(mBuffers, mWritePointer * mBytesPerFrame, bufferList, 0, n1 * mBytesPerFrame);
	mWritePointer = (mWritePointer + n1) & mCapacityFramesMask;

	if(n2) {
		StoreABL(mBuffers, mWritePointer * mBytesPerFrame, bufferList, n1 * mBytesPerFrame, n2 * mBytesPerFrame);
		mWritePointer = (mWritePointer + n2) & mCapacityFramesMask;
	}

	return framesToWrite;
}
