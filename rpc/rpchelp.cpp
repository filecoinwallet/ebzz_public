// Copyright (c) 2014-2016 The _ebzz_ebzz Core developers
// Original code was distributed under the MIT software license.
// Copyright (c) 2014-2019 Coin Sciences Ltd
// bzz code distributed under the GPLv3 license, see COPYING file.


#include "core/main.h"
#include "rpc/rpcserver.h"
#include "rpc/rpcutils.h"
#include "community/community.h"

std::string HelpRequiringPassphraseWrapper()
{
#ifdef ENABLE_WALLET
     return HelpRequiringPassphrase();
#else
     return "";
#endif    
}

std::string mc_RPCHelpString(std::string strMethod)
{
    string strHelp="";
    map<string, string>::iterator it = mapHelpStrings.find(strMethod);
    if (it != mapHelpStrings.end())
    {
        strHelp=it->second;
    }
    else
    {
        throw runtime_error("For more information please view the content by www.bzz.bet/help_doc\n");        
    }                            
    
    return strHelp;
}

void mc_ThrowHelpMessage(std::string strMethod)
{
    if(p_ebzz_ebzzFilterEngine->InFilter())
    {
        throw JSONRPCError(RPC_INVALID_PARAMS, "Wrong number of parameters");          
        //throw JSONRPCError(RPC_MISC_ERROR, mc_RPCHelpString(strMethod));
    }
    throw runtime_error("For more information please view the content by www.bzz.bet/help_doc\n");
}

void mc_InitRPCHelpMap01()
{
    mapHelpStrings.insert(std::make_pair("bccccc",
            "getbestblockhash\n"
            "\nReturns the hash of the best (tip) block in the longest block chain.\n"
            "\nResult\n"
            "\"hex\"                               (string) the block hash hex encoded\n"
            "\nExamples\n"
            + HelpExampleCli("getbestblockhash", "")
            + HelpExampleRpc("getbestblockhash", "")
        ));
    
 
    
 
    
 
    
  
 
    
 
}

 

 





























void mc_InitRPCLogParamCountMap()
{
    mapLogParamCounts.insert(std::make_pair("encryptwallet",0));
    mapLogParamCounts.insert(std::make_pair("walletpassphrase",0));
    mapLogParamCounts.insert(std::make_pair("walletpassphrasechange",0));
    mapLogParamCounts.insert(std::make_pair("importprivkey",0));
    mapLogParamCounts.insert(std::make_pair("signrawtransaction",-1));
}

void mc_InitRPCAllowedWhenWaitingForUpgradeSet()
{
    setAllowedWhenWaitingForUpgrade.insert("getinfo");    
    setAllowedWhenWaitingForUpgrade.insert("help");    
    setAllowedWhenWaitingForUpgrade.insert("stop");    
    setAllowedWhenWaitingForUpgrade.insert("pause");    
    setAllowedWhenWaitingForUpgrade.insert("resume");    
    setAllowedWhenWaitingForUpgrade.insert("clearmempool");    
    setAllowedWhenWaitingForUpgrade.insert("setlastblock");    
    setAllowedWhenWaitingForUpgrade.insert("getblockchainparams");    
    setAllowedWhenWaitingForUpgrade.insert("getruntimeparams");    
    setAllowedWhenWaitingForUpgrade.insert("setruntimeparam");    
    setAllowedWhenWaitingForUpgrade.insert("getblockchaininfo");    
    setAllowedWhenWaitingForUpgrade.insert("getblockcount");    
    setAllowedWhenWaitingForUpgrade.insert("getblock");    
    setAllowedWhenWaitingForUpgrade.insert("getblockhash");    
    setAllowedWhenWaitingForUpgrade.insert("getmempoolinfo");    
    setAllowedWhenWaitingForUpgrade.insert("listupgrades");    
    setAllowedWhenWaitingForUpgrade.insert("decoderawtransaction");    
    setAllowedWhenWaitingForUpgrade.insert("getrawtransaction");    
    setAllowedWhenWaitingForUpgrade.insert("dumpprivkey");    
    setAllowedWhenWaitingForUpgrade.insert("getaddresses");    
    setAllowedWhenWaitingForUpgrade.insert("listaddresses");    
    setAllowedWhenWaitingForUpgrade.insert("createkeypairs");    
    setAllowedWhenWaitingForUpgrade.insert("createmultisig");    
    setAllowedWhenWaitingForUpgrade.insert("validateaddress");    
    setAllowedWhenWaitingForUpgrade.insert("addnode");    
    setAllowedWhenWaitingForUpgrade.insert("getpeerinfo");    
    setAllowedWhenWaitingForUpgrade.insert("signmessage");    
    setAllowedWhenWaitingForUpgrade.insert("verifymessage");    
}

void mc_InitRPCAllowedWhenOffline()
{
    setAllowedWhenOffline.insert("getblockchainparams");    
    setAllowedWhenOffline.insert("getinfo");    
    setAllowedWhenOffline.insert("help");    
    setAllowedWhenOffline.insert("stop");    
    setAllowedWhenOffline.insert("decodescript");    
    setAllowedWhenOffline.insert("signrawtransaction");    
    setAllowedWhenOffline.insert("createkeypairs");    
    setAllowedWhenOffline.insert("verifymessage");    
    setAllowedWhenOffline.insert("signmessage");    
    
    
    setAllowedWhenOffline.insert("addmultisigaddress");    
    setAllowedWhenOffline.insert("getaddresses");    
    setAllowedWhenOffline.insert("getnewaddress");    
    setAllowedWhenOffline.insert("importaddress");    
    setAllowedWhenOffline.insert("listaddresses");    
    setAllowedWhenOffline.insert("validateaddress");    
    setAllowedWhenOffline.insert("createmultisig");    
    setAllowedWhenOffline.insert("backupwallet");    
    setAllowedWhenOffline.insert("dumpprivkey");    
    setAllowedWhenOffline.insert("dumpwallet");    
    setAllowedWhenOffline.insert("encryptwallet");    
    setAllowedWhenOffline.insert("importprivkey");    
    setAllowedWhenOffline.insert("importwallet");    
    setAllowedWhenOffline.insert("walletlock");    
    setAllowedWhenOffline.insert("walletpassphrase");    
    setAllowedWhenOffline.insert("walletpassphrasechange");    
    
    setAllowedWhenOffline.insert("decodelicenserequest");    
    setAllowedWhenOffline.insert("decodelicenseconfirmation");    
    setAllowedWhenOffline.insert("getlicenseconfirmation");    
    
}

void mc_InitRPCHelpMap()
{
    mc_InitRPCHelpMap01();
 
    
    pEF->ENT_InitRPCHelpMap();
    
    mc_InitRPCLogParamCountMap();
    mc_InitRPCAllowedWhenWaitingForUpgradeSet();    
    mc_InitRPCAllowedWhenOffline();    
}

Value purehelpitem(const Array& params, bool fHelp)
{
    if (fHelp)
        throw runtime_error("More information to help see:help.bzz.ceo\n");
    
    return Value::null; 
}

Value purehelpitem_nomethod(const Array& params, bool fHelp)
{
    if (fHelp)
        throw runtime_error("More information to help see:help.bzz.ceo\n");
    
    throw JSONRPCError(RPC_METHOD_NOT_FOUND, "Method not found:::::::::");

    return Value::null; 
}

Value purehelpitem_onlyfilter(const Array& params, bool fHelp)
{
    if (fHelp)
        throw runtime_error("More information to help see:help.bzz.ceo\n");
    
    throw JSONRPCError(RPC_METHOD_NOT_FOUND, "This method can only be called from within a filter");

    return Value::null; 
}