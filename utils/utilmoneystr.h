// Copyright (c) 2009-2010 Satoshi Nakamoto
// Copyright (c) 2009-2014 The _ebzz_ebzz developers
// Original code was distributed under the MIT software license.
// Copyright (c) 2014-2019 Coin Sciences Ltd
// bzz code distributed under the GPLv3 license, see COPYING file.

/**
 * Money parsing/formatting utilities.
 */
#ifndef _ebzz_ebzz_UTILMONEYSTR_H
#define _ebzz_ebzz_UTILMONEYSTR_H

#include <stdint.h>
#include <string>

#include "structs/amount.h"

std::string FormatMoney(const CAmount& n, bool fPlus=false);
bool ParseMoney(const std::string& str, CAmount& nRet);
bool ParseMoney(const char* pszIn, CAmount& nRet);

#endif // _ebzz_ebzz_UTILMONEYSTR_H
