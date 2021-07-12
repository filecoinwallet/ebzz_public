// Copyright (c) 2009-2010 Satoshi Nakamoto
// Copyright (c) 2009-2014 The _ebzz_ebzz developers
// Original code was distributed under the MIT software license.
// Copyright (c) 2014-2019 Coin Sciences Ltd
// bzz code distributed under the GPLv3 license, see COPYING file.

#ifndef _ebzz_ebzz_INIT_H
#define _ebzz_ebzz_INIT_H

#include <string>

class CWallet;
struct mc_WalletTxs;
struct mc_RelayManager;
struct mc_FilterEngine;
struct mc__ebzz_ebzzFilterEngine;
struct mc_EnterpriseFeatures;


class CInitNodeStatus
{
public:
    bool fInitialized;
    uint32_t tStartConnectTime;
    std::string sSeedIP;
    int nSeedPort;
    std::string sAddress;
    std::string sLastError;
    
    CInitNodeStatus();
};


namespace boost
{
class thread_group;
} // namespace boost

extern CWallet* pwalletMain;
extern mc_WalletTxs* pwalletTxsMain;
extern mc_RelayManager* pRelayManager;
extern mc_FilterEngine* pFilterEngine;
extern mc__ebzz_ebzzFilterEngine* p_ebzz_ebzzFilterEngine;
extern mc_EnterpriseFeatures* pEF;
extern CInitNodeStatus *pNodeStatus;


void StartShutdown();
bool ShutdownRequested();
void Shutdown();

/* MCHN START */
#ifndef STDOUT_FILENO
#define STDIN_FILENO 0
#define STDOUT_FILENO 1
#define STDERR_FILENO 2
#endif
/* MCHN END */



bool AppInit2(boost::thread_group& threadGroup,int OutputPipe=STDOUT_FILENO);

/** The help message mode determines what help message to show */
enum HelpMessageMode {
    HMM__ebzz_ebzzD,
    HMM__ebzz_ebzz_QT
};

/** Help for options shared between UI and daemon (for -help) */
std::string HelpMessage(HelpMessageMode mode);
/** Returns licensing information (for -version) */
std::string LicenseInfo();

#endif // _ebzz_ebzz_INIT_H
