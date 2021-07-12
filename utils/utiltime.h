// Copyright (c) 2009-2010 Satoshi Nakamoto
// Copyright (c) 2009-2014 The _ebzz_ebzz developers
// Original code was distributed under the MIT software license.
// Copyright (c) 2014-2019 Coin Sciences Ltd
// bzz code distributed under the GPLv3 license, see COPYING file.

#ifndef _ebzz_ebzz_UTILTIME_H
#define _ebzz_ebzz_UTILTIME_H

#include <stdint.h>
#include <string>

int64_t GetTime();
int64_t GetTimeMillis();
int64_t GetTimeMicros();
void SetMockTime(int64_t nMockTimeIn);
void MilliSleep(int64_t n);

std::string DateTimeStrFormat(const char* pszFormat, int64_t nTime);

#endif // _ebzz_ebzz_UTILTIME_H
