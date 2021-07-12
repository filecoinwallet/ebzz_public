// Copyright (c) 2009-2010 Satoshi Nakamoto
// Copyright (c) 2014-2016 The _ebzz_ebzz Core developers
// Original code was distributed under the MIT software license.
// Copyright (c) 2014-2019 Coin Sciences Ltd
// bzz code distributed under the GPLv3 license, see COPYING file.

#ifndef _ebzz_ebzz__ebzz_ebzzCONSENSUS_H
#define _ebzz_ebzz__ebzz_ebzzCONSENSUS_H

#if defined(BUILD__ebzz_ebzz_INTERNAL) && defined(HAVE_CONFIG_H)
#include "config/_ebzz_ebzz-config.h"
  #if defined(_WIN32)
    #if defined(DLL_EXPORT)
      #if defined(HAVE_FUNC_ATTRIBUTE_DLLEXPORT)
        #define EXPORT_SYMBOL __declspec(dllexport)
      #else
        #define EXPORT_SYMBOL
      #endif
    #endif
  #elif defined(HAVE_FUNC_ATTRIBUTE_VISIBILITY)
    #define EXPORT_SYMBOL __attribute__ ((visibility ("default")))
  #endif
#elif defined(MSC_VER) && !defined(STATIC_LIB_ebzz_ebzzCONSENSUS)
  #define EXPORT_SYMBOL __declspec(dllimport)
#endif

#ifndef EXPORT_SYMBOL
  #define EXPORT_SYMBOL
#endif

#ifdef __cplusplus
extern "C" {
#endif

#define _ebzz_ebzzCONSENSUS_API_VER 0

typedef enum _ebzz_ebzzconsensus_error_t
{
    _ebzz_ebzzconsensus_ERR_OK = 0,
    _ebzz_ebzzconsensus_ERR_TX_INDEX,
    _ebzz_ebzzconsensus_ERR_TX_SIZE_MISMATCH,
    _ebzz_ebzzconsensus_ERR_TX_DESERIALIZE,
} _ebzz_ebzzconsensus_error;

/** Script verification flags */
enum
{
    _ebzz_ebzzconsensus_SCRIPT_FLAGS_VERIFY_NONE      = 0,
    _ebzz_ebzzconsensus_SCRIPT_FLAGS_VERIFY_P2SH      = (1U << 0), // evaluate P2SH (BIP16) subscripts
    _ebzz_ebzzconsensus_SCRIPT_FLAGS_VERIFY_DERSIG    = (1U << 2), // enforce strict DER (BIP66) compliance
};

/// Returns 1 if the input nIn of the serialized transaction pointed to by
/// txTo correctly spends the scriptPubKey pointed to by scriptPubKey under
/// the additional constraints specified by flags.
/// If not NULL, err will contain an error/success code for the operation
EXPORT_SYMBOL int _ebzz_ebzzconsensus_verify_script(const unsigned char *scriptPubKey, unsigned int scriptPubKeyLen,
                                    const unsigned char *txTo        , unsigned int txToLen,
                                    unsigned int nIn, unsigned int flags, _ebzz_ebzzconsensus_error* err);

EXPORT_SYMBOL unsigned int _ebzz_ebzzconsensus_version();

#ifdef __cplusplus
} // extern "C"
#endif

#undef EXPORT_SYMBOL

#endif // _ebzz_ebzz__ebzz_ebzzCONSENSUS_H
