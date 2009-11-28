/*
 *  Copyright (C) 2009 Stephen F. Booth <me@sbooth.org>
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

#include "DecoderStateData.h"
#include "AudioDecoder.h"
#include "AudioEngineDefines.h"

#include <pthread.h>

DecoderStateData::DecoderStateData()
	: mDecoder(NULL), mTimeStamp(0), mTotalFrames(0), mFramesRendered(0), mFrameToSeek(-1), mDecodingThread(static_cast<pthread_t>(0)), mKeepDecoding(true), mReadyForCollection(false)
{}

DecoderStateData::DecoderStateData(AudioDecoder *decoder)
	: mDecoder(decoder), mTimeStamp(0), mFramesRendered(0), mFrameToSeek(-1), mDecodingThread(static_cast<pthread_t>(0)), mKeepDecoding(true), mReadyForCollection(false)
{
	assert(NULL != decoder);
	
	// NB: The decoder may return an estimate of the total frames
	mTotalFrames = mDecoder->GetTotalFrames();
}
	
DecoderStateData::~DecoderStateData()
{
	// Wait for the decoding thread to end, if it hasn't already
	if(static_cast<pthread_t>(0) != mDecodingThread) {
		mKeepDecoding = false;
		
		int result = pthread_join(mDecodingThread, NULL);
		if(0 != result)
			ERR("pthread_join failed: %i", result);
		
		mDecodingThread = static_cast<pthread_t>(0);
	}

	// Delete the decoder
	if(NULL != mDecoder)
		delete mDecoder, mDecoder = NULL;
}
