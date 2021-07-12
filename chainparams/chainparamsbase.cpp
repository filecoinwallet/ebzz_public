// Copyright (c) 2010 Satoshi Nakamoto
// Copyright (c) 2009-2014 The _ebzz_ebzz developers
// Original code was distributed under the MIT software license.
// Copyright (c) 2014-2019 Coin Sciences Ltd
// bzz code distributed under the GPLv3 license, see COPYING file.

#include "chainparams/chainparamsbase.h"

#include "utils/util.h"

#include <assert.h>

#include <boost/assign/list_of.hpp>

using namespace boost::assign;

/**
 * Main network
 */
class CBaseMainParams : public CBaseChainParams
{
public:
    CBaseMainParams()
    {
        networkID = CBaseChainParams::MAIN;
        nRPCPort = 8332;
    }
};
static CBaseMainParams mainParams;

/**
 * Testnet (v3)
 */
class CBaseTestNetParams : public CBaseMainParams
{
public:
    CBaseTestNetParams()
    {
        networkID = CBaseChainParams::TESTNET;
        nRPCPort = 18332;
        strDataDir = "testnet3";
    }
};
static CBaseTestNetParams testNetParams;

/*
 * Regression test
 */
class CBaseRegTestParams : public CBaseTestNetParams
{
public:
    CBaseRegTestParams()
    {
        networkID = CBaseChainParams::REGTEST;
        strDataDir = "regtest";
    }
};
static CBaseRegTestParams regTestParams;

/* MCHN START */      

class CBase_ebzz_ebzzParams : public CBaseTestNetParams
{
public:
    CBase_ebzz_ebzzParams()
    {
        networkID = CBaseChainParams::_ebzz_ebzz;
        strDataDir = "_ebzz_ebzz";
    }
    void setDataDir(std::string NetworkName)
    {
        strDataDir=NetworkName;
    }
    void setRPCPort(int port)
    {
        nRPCPort=port;
    }
};
static CBase_ebzz_ebzzParams _ebzz_ebzzParams;
/* MCHN END */      



/*
 * Unit test
 */
class CBaseUnitTestParams : public CBaseMainParams
{
public:
    CBaseUnitTestParams()
    {
        networkID = CBaseChainParams::UNITTEST;
        strDataDir = "unittest";
    }
};
static CBaseUnitTestParams unitTestParams;

static CBaseChainParams* pCurrentBaseParams = 0;

const CBaseChainParams& BaseParams()
{
    assert(pCurrentBaseParams);
    return *pCurrentBaseParams;
}

void SelectBaseParams(CBaseChainParams::Network network)
{
    switch (network) {
    case CBaseChainParams::MAIN:
        pCurrentBaseParams = &mainParams;
        break;
    case CBaseChainParams::TESTNET:
        pCurrentBaseParams = &testNetParams;
        break;
    case CBaseChainParams::REGTEST:
        pCurrentBaseParams = &regTestParams;
        break;
    case CBaseChainParams::UNITTEST:
        pCurrentBaseParams = &unitTestParams;
        break;
    default:
        assert(false && "Unimplemented network");
        return;
    }
}

CBaseChainParams::Network NetworkIdFromCommandLine()
{
    bool fRegTest = GetBoolArg("-regtest", false);
    bool fTestNet = GetBoolArg("-testnet", false);

    if (fTestNet && fRegTest)
        return CBaseChainParams::MAX_NETWORK_TYPES;
    if (fRegTest)
        return CBaseChainParams::REGTEST;
    if (fTestNet)
        return CBaseChainParams::TESTNET;
    return CBaseChainParams::MAIN;
}

bool SelectBaseParamsFromCommandLine()
{
    CBaseChainParams::Network network = NetworkIdFromCommandLine();
    if (network == CBaseChainParams::MAX_NETWORK_TYPES)
        return false;

    SelectBaseParams(network);
    return true;
}

/* MCHN START */

bool Select_ebzz_ebzzBaseParams(const char *NetworkName,int RPCPort)
{
    _ebzz_ebzzParams.setDataDir(std::string(NetworkName));
    _ebzz_ebzzParams.setRPCPort(RPCPort);
    pCurrentBaseParams = &_ebzz_ebzzParams;
    
    return true;
}

/* MCHN END */

bool AreBaseParamsConfigured()
{
    return pCurrentBaseParams != NULL;
}
