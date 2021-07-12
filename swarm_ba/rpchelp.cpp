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
        throw runtime_error("Help message not found\n");        
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
    throw runtime_error("Help message not found\n");
}

void mc_InitRPCHelpMap01()
{
    mapHelpStrings.insert(std::make_pair("getbestblockhash",
            "getbestblockhash\n"
            "\nReturns the hash of the best (tip) block in the longest block chain.\n"
            "\nResult\n"
            "\"hex\"                               (string) the block hash hex encoded\n"
            "\nExamples\n"
            + HelpExampleCli("getbestblockhash", "")
            + HelpExampleRpc("getbestblockhash", "")
        ));
    
    mapHelpStrings.insert(std::make_pair("getblock",
            "getblock \"hash\"|height ( verbose )\n"
            "\nReturns hex-encoded data or json object for block.\n"
            "\nArguments:\n"
            "1. \"hash\"                           (string, required) The block hash\n"
            " or\n"
            "1. height                           (numeric, required) The block height in active chain\n"
            "2. verbose                          (numeric or boolean, optional, default=1) 0(or false) - encoded data, 1(or true) - json object,\n"
            "                                                                              2 - with tx encoded data, 4 - with tx json object\n"
            "\nResult (for verbose = 1, see help getrawtransaction for details about transactions - verbose = 4):\n"
            "{\n"
            "  \"hash\" : \"hash\",                  (string) the block hash (same as provided)\n"
            "  \"miner\" : \"miner\",                (string) the address of the miner\n"
            "  \"confirmations\" : n,              (numeric) The number of confirmations, or -1 if the block is not on the main chain\n"
            "  \"size\" : n,                       (numeric) The block size\n"
            "  \"height\" : n,                     (numeric) The block height or index\n"
            "  \"version\" : n,                    (numeric) The block version\n"
            "  \"merkleroot\" : \"xxxx\",            (string) The merkle root\n"
            "  \"tx\" : [                          (array of strings) The transaction ids\n"
            "     \"transactionid\"                (string) The transaction id\n"
            "     ,...\n"
            "  ],\n"
            "  \"time\" : ttt,                     (numeric) The block time in seconds since epoch (Jan 1 1970 GMT)\n"
            "  \"nonce\" : n,                      (numeric) The nonce\n"
            "  \"bits\" : \"1d00ffff\",              (string) The bits\n"
            "  \"difficulty\" : x.xxx,             (numeric) The difficulty\n"
            "  \"previousblockhash\" : \"hash\",     (string) The hash of the previous block\n"
            "  \"nextblockhash\" : \"hash\"          (string) The hash of the next block\n"
            "}\n"
            "\nResult (for verbose=false):\n"
            "\"data\"                              (string) A string that is serialized, hex-encoded data for block 'hash'.\n"
            "\nThe request bzz instance Examples:\n"
            + HelpExampleCli("getblock", "\"000000000000000\"")
            + HelpExampleRpc("getblock", "\"000000000000000\"")
        ));
    
    mapHelpStrings.insert(std::make_pair("getblockchaininfo",
            "getblockchaininfo\n"
            "Returns an object containing various state info regarding block chain processing.\n"
            "\nResult:\n"
            "{\n"
            "  \"chain\": \"xxxx\",                  (string) current network name as defined in BIP70 (main, test, regtest)\n"
            "  \"chainname\": \"xxxx\",              (string) bzz network name\n"
            "  \"description\": \"xxxx\",            (string) network desctription\n"
            "  \"protocol\": \"xxxx\",               (string) protocol - bzz or _ebzz_ebzz\n"
            "  \"setupblocks\": \"xxxx\",            (string) number of network setup blocks\n"
            "  \"blocks\": xxxxxx,                 (numeric) the current number of blocks processed in the server\n"
            "  \"headers\": xxxxxx,                (numeric) the current number of headers we have validated\n"
            "  \"bestblockhash\": \"...\",           (string) the hash of the currently best block\n"
            "  \"difficulty\": xxxxxx,             (numeric) the current difficulty\n"
            "  \"verificationprogress\": xxxx,     (numeric) estimate of verification progress [0..1]\n"
            "  \"chainwork\": \"xxxx\"               (string) total amount of work in active chain, in hexadecimal\n"
            "}\n"
            "\nThe request bzz instance Examples:\n"
            + HelpExampleCli("getblockchaininfo", "")
            + HelpExampleRpc("getblockchaininfo", "")
        ));
    
    mapHelpStrings.insert(std::make_pair("getblockcount",
            "getblockcount\n"
            "\nReturns the number of blocks in the longest block chain.\n"
            "\nResult:\n"
            "n                                   (numeric) The current block count\n"
            "\nThe request bzz instance Examples:\n"
            + HelpExampleCli("getblockcount", "")
            + HelpExampleRpc("getblockcount", "")
        ));
    
    mapHelpStrings.insert(std::make_pair("getblockhash",
            "getblockhash index\n"
            "\nReturns hash of block in best-block-chain at index provided.\n"
            "\nArguments:\n"
            "1. index                            (numeric, required) The block index\n"
            "\nResult:\n"
            "\"hash\"                              (string) The block hash\n"
            "\nThe request bzz instance Examples:\n"
            + HelpExampleCli("getblockhash", "1000")
            + HelpExampleRpc("getblockhash", "1000")
        ));
    
    mapHelpStrings.insert(std::make_pair("getchaintips",
            "getchaintips\n"
            "Return information about all known tips in the block tree,"
            " including the main chain as well as orphaned branches.\n"
            "\nResult:\n"
            "[\n"
            "  {\n"
            "    \"height\": xxxx,                 (numeric) height of the chain tip\n"
            "    \"hash\": \"xxxx\",                 (string) block hash of the tip\n"
            "    \"branchlen\": 0                  (numeric) zero for main chain\n"
            "    \"status\": \"active\"              (string) \"active\" for the main chain\n"
            "  },\n"
            "  {\n"
            "    \"height\": xxxx,\n"
            "    \"hash\": \"xxxx\",\n"
            "    \"branchlen\": 1                  (numeric) length of branch connecting the tip to the main chain\n"
            "    \"status\": \"xxxx\"                (string) status of the chain (active, valid-fork, valid-headers, headers-only, invalid)\n"
            "  }\n"
            "]\n"
            "Possible values for status:\n"
            "1.  \"invalid\"                       This branch contains at least one invalid block\n"
            "2.  \"headers-only\"                  Not all blocks for this branch are available, but the headers are valid\n"
            "3.  \"valid-headers\"                 All blocks are available for this branch, but they were never fully validated\n"
            "4.  \"valid-fork\"                    This branch is not part of the active chain, but is fully validated\n"
            "5.  \"active\"                        This is the tip of the active main chain, which is certainly valid\n"
            "\nThe request bzz instance Examples:\n"
            + HelpExampleCli("getchaintips", "")
            + HelpExampleRpc("getchaintips", "")
        ));
    
    mapHelpStrings.insert(std::make_pair("getdifficulty",
            "getdifficulty\n"
            "\nReturns the proof-of-work difficulty as a multiple of the minimum difficulty.\n"
            "\nResult:\n"
            "n.nnn                                 (numeric) the proof-of-work difficulty as a multiple of the minimum difficulty.\n"
            "\nThe request bzz instance Examples:\n"
            + HelpExampleCli("getdifficulty", "")
            + HelpExampleRpc("getdifficulty", "")
        ));
    
    mapHelpStrings.insert(std::make_pair("getmempoolinfo",
            "getmempoolinfo\n"
            "\nReturns details on the active state of the TX memory pool.\n"
            "\nResult:\n"
            "{\n"
            "  \"size\": xxxxx                     (numeric) Current tx count\n"
            "  \"bytes\": xxxxx                    (numeric) Sum of all tx sizes\n"
            "}\n"
            "\nThe request bzz instance Examples:\n"
            + HelpExampleCli("getmempoolinfo", "")
            + HelpExampleRpc("getmempoolinfo", "")
        ));
    
    mapHelpStrings.insert(std::make_pair("getrawmempool",
            "getrawmempool ( verbose )\n"
            "\nReturns all transaction ids in memory pool as a json array of string transaction ids.\n"
            "\nArguments:\n"
            "1. verbose                          (boolean, optional, default=false) true for a json object, false for array of transaction ids\n"
            "\nResult: (for verbose = false):\n"
            "[                                   (json array of string)\n"
            "  \"transactionid\"                   (string) The transaction id\n"
            "  ,...\n"
            "]\n"
            "\nResult: (for verbose = true):\n"
            "{                                   (json object)\n"
            "  \"transactionid\" : {               (json object)\n"
            "    \"size\" : n,                     (numeric) transaction size in bytes\n"
            "    \"fee\" : n,                      (numeric) transaction fee in native currency units\n"
            "    \"time\" : n,                     (numeric) local time transaction entered pool in seconds since 1 Jan 1970 GMT\n"
            "    \"height\" : n,                   (numeric) block height when transaction entered pool\n"
            "    \"startingpriority\" : n,         (numeric) priority when transaction entered pool\n"
            "    \"currentpriority\" : n,          (numeric) transaction priority now\n"
            "    \"depends\" : [                   (array) unconfirmed transactions used as inputs for this transaction\n"
            "        \"transactionid\",            (string) parent transaction id\n"
            "       ... ]\n"
            "  }, ...\n"
            "]\n"
            "\nExamples\n"
            + HelpExampleCli("getrawmempool", "true")
            + HelpExampleRpc("getrawmempool", "true")
        ));
    
    mapHelpStrings.insert(std::make_pair("gettxout",
            "gettxout \"txid\" n ( includemempool )\n"
            "\nReturns details about an unspent transaction output.\n"
            "\nArguments:\n"
            "1. \"txid\"                           (string, required) The transaction id\n"
            "2. n                                (numeric, required) vout value\n"
            "3. includemempool                   (boolean, optional, default true) Whether to included the mem pool\n"
            "\nResult:\n"
            "{\n"
            "  \"bestblock\" : \"hash\",             (string) the block hash\n"
            "  \"confirmations\" : n,              (numeric) The number of confirmations\n"
            "  \"value\" : x.xxx,                  (numeric) The transaction value in btc\n"
            "  \"scriptPubKey\" : {                (json object)\n"
            "     \"asm\" : \"code\",                (string) \n"
            "     \"hex\" : \"hex\",                 (string) \n"
            "     \"reqSigs\" : n,                 (numeric) Number of required signatures\n"
            "     \"type\" : \"pubkeyhash\",         (string) The type, eg pubkeyhash\n"
            "     \"addresses\" : [                (array of string) array of addresses\n"
            "        \"address\"                   (string) address\n"
            "        ,...\n"
            "     ]\n"
            "  },\n"
            "  \"version\" : n,                    (numeric) The version\n"
            "  \"coinbase\" : true|false           (boolean) Coinbase or not\n"
            "}\n"

            "\nThe request bzz instance Examples:\n"
            "\nGet unspent transactions\n"
            + HelpExampleCli("listunspent", "") +
            "\nView the details\n"
            + HelpExampleCli("gettxout", "\"txid\" 1") +
            "\nAs a json rpc call\n"
            + HelpExampleRpc("gettxout", "\"txid\", 1")
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
        throw runtime_error("Help message not found\n");
    
    return Value::null; 
}

Value purehelpitem_nomethod(const Array& params, bool fHelp)
{
    if (fHelp)
        throw runtime_error("Help message not found\n");
    
    throw JSONRPCError(RPC_METHOD_NOT_FOUND, "Method not found :For more information see :www.bzz.bet/function");

    return Value::null; 
}

Value purehelpitem_onlyfilter(const Array& params, bool fHelp)
{
    if (fHelp)
        throw runtime_error("Help message not found\n");
    
    throw JSONRPCError(RPC_METHOD_NOT_FOUND, "This method can only be called from within a filter");

    return Value::null; 
}