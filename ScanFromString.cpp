//
//  ScanFromString.cpp
//  SFBAudioEngine
//
//  Created by Zach Waldowski on 2/16/14.
//  Copyright (c) 2014 sbooth.org. All rights reserved.
//

#include "ScanFromString.h"

namespace {
	// http://www.opensource.apple.com/source/CF/CF-855.11/CFStringScanner.c
	
	static inline Boolean IsWhitespace(UniChar theChar) {
		return ((theChar < 0x21) || (theChar > 0x7E && theChar < 0xA1) || (theChar >= 0x2000 && theChar <= 0x200B) || (theChar == 0x3000)) ? true : false;
	}
	
	static inline UniChar GetFirstNonSpaceCharacterFromInlineBuffer(CFStringInlineBuffer *buf, SInt32 *indexPtr) {
		UniChar ch;
		
		while (IsWhitespace(ch = CFStringGetCharacterFromInlineBuffer(buf, *indexPtr))) (*indexPtr)++;
		return ch;
	}
	
	static inline bool CharacterIsADigit(UniChar ch) {
		return (ch >= '0' && ch <= '9') ? true : false;
	}
	
	static inline SInt32 CharacterNumericValue(UniChar ch) {
		return (ch >= '0' && ch <= '9') ? (ch - '0') : -1;
	}
}

SInt64 SFB::CFStringGetLongValue(CFStringRef str)
{
	CFStringInlineBuffer buf;
    CFStringInitInlineBuffer(str, &buf, CFRangeMake(0, CFStringGetLength(str)));
	
	Boolean neg = false;
	int64_t longlongResult = 0;
	UniChar ch;
    SInt32 idx = 0;
	
	ch = GetFirstNonSpaceCharacterFromInlineBuffer(&buf, &idx);
	
	if (ch == '-' || ch == '+') {
		neg = (ch == '-');
		idx++;
		ch = GetFirstNonSpaceCharacterFromInlineBuffer(&buf, &idx);
	}
	
	if (!CharacterIsADigit(ch)) return 0;	/* No digits, bail out... */
	do {
		if ((longlongResult >= LLONG_MAX / 10) && ((longlongResult > LLONG_MAX / 10) || (CharacterNumericValue(ch) - (neg ? 1 : 0) >= LLONG_MAX - longlongResult * 10))) {
			longlongResult = neg ? LLONG_MIN : LLONG_MAX;
			neg = false;
			while (CharacterIsADigit(ch = CFStringGetCharacterFromInlineBuffer(&buf, ++idx)));	/* Skip remaining digits */
		} else {
			longlongResult = longlongResult * 10 + CharacterNumericValue(ch);
			ch = CFStringGetCharacterFromInlineBuffer(&buf, ++idx);
		}
	} while (CharacterIsADigit(ch));
	
	return neg ? -longlongResult : longlongResult;
}
