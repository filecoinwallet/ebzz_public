// Copyright (c) 2010 Satoshi Nakamoto
// Copyright (c) 2014-2016 The _ebzz_ebzz Core developers
// Original code was distributed under the MIT software license.
// Copyright (c) 2014-2019 Coin Sciences Ltd
// bzz code distributed under the GPLv3 license, see COPYING file.

#if defined(HAVE_CONFIG_H)
#include "config/_ebzz_ebzz-config.h"
#endif


#include "rpc/rpcserver.h"


/* MCHN START */
static const CRPCCommand vRPCWalletReadCommands[] =
{ //  category              name                      actor (function)         okSafeMode threadSafe reqWallet
  //  --------------------- ------------------------  -----------------------  ---------- ---------- ---------
    { "wallet",            "bzz_getbalance",             &getbalance,             false,     false,      true },
    { "wallet",            "bzz_getreceivedbyaccount",   &getreceivedbyaccount,   false,     false,      true },
    { "wallet",            "bzz_getreceivedbyaddress",   &getreceivedbyaddress,   false,     false,      true },
    { "wallet",            "bzz_gettransaction",         &gettransaction,         false,     false,      true },
    { "wallet",            "bzz_getunconfirmedbalance",  &getunconfirmedbalance,  false,     false,      true },
    { "wallet",            "bzz_getwalletinfo",          &getwalletinfo,          false,     false,      true },
    { "wallet",            "bzz_listlockunspent",        &listlockunspent,        false,     false,      true },
    { "wallet",            "bzz_listreceivedbyaccount",  &listreceivedbyaccount,  false,     false,      true },
    { "wallet",            "bzz_listreceivedbyaddress",  &listreceivedbyaddress,  false,     false,      true },
    { "wallet",            "bzz_listsinceblock",         &listsinceblock,         false,     false,      true },
    { "wallet",            "bzz_listtransactions",       &listtransactions,       false,     false,      true },
    { "wallet",            "bzz_listunspent",            &listunspent,            false,     false,      true },
    { "wallet",            "bzz_getassetbalances",       &getassetbalances,       false,     false,      true },
    { "wallet",            "bzz_gettotalbalances",       &gettotalbalances,       false,     false,      true },
    
    { "wallet",            "bzz_getmultibalances",       &getmultibalances,       false,     false,      true },
    { "wallet",            "bzz_getaddressbalances",     &getaddressbalances,     false,     false,      true },
    
    { "wallet",            "bzz_listwallettransactions", &listwallettransactions, false,     false,      true },
    { "wallet",            "bzz_listaddresstransactions",&listaddresstransactions,false,     false,      true },
    { "wallet",            "bzz_getwallettransaction",   &getwallettransaction,   false,     false,      true },
    { "wallet",            "bzz_getaddresstransaction",  &getaddresstransaction,  false,     false,      true },
};

/* MCHN END */

/**
 * Call Table
 */
static const CRPCCommand vRPCCommands[] =
{ //  category              name                      actor (function)         okSafeMode threadSafe reqWallet
  //  --------------------- ------------------------  -----------------------  ---------- ---------- ---------
    /* Overall control/query calls */
    { "control",            "bzz_getinfo",                &getinfo,                true,      false,      false }, /* uses wallet if enabled */
    { "control",            "bzz_getchaintotals",         &getchaintotals,        true,      true,       false },
    { "control",            "bzz_getinitstatus",          &getinitstatus,          true,      true,       false },
    { "control",            "bzz_gethealthcheck",         &gethealthcheck,         true,      true,       false },
    { "control",            "bzz_help",                   &help,                   true,      true,       false },
    { "control",            "bzz_stop",                   &stop,                   true,      true,       false },
/* MCHN START */    
    { "control",            "bzz_pause",                  &pausecmd,               true,      false,      false },
    { "control",            "bzz_resume",                 &resumecmd,              true,      false,      false },
    { "control",            "bzz_clearmempool",           &clearmempool,           true,      false,      false },
    { "control",            "bzz_setlastblock",           &setlastblock,           true,      false,      false },
    { "control",            "bzz_getblockchainparams",    &getblockchainparams,    true,      false,      false }, 
    { "control",            "bzz_getruntimeparams",       &getruntimeparams,       true,      false,      false }, 
    { "control",            "bzz_setruntimeparam",        &setruntimeparam,        true,      false,      false }, 
/* MCHN END */    

    /* P2P networking */
    { "network",            "bzz_getnetworkinfo",         &getnetworkinfo,         true,      false,      false },
    { "network",            "bzz_addnode",                &addnode,                true,      true,       false },
    { "network",            "bzz_getaddednodeinfo",       &getaddednodeinfo,       true,      true,       false },
    { "network",            "bzz_getconnectioncount",     &getconnectioncount,     true,      false,      false },
    { "network",            "bzz_getnettotals",           &getnettotals,           true,      true,       false },
    { "network",            "bzz_getpeerinfo",            &getpeerinfo,            true,      false,      false },
    { "network",            "bzz_ping",                   &ping,                   true,      false,      false },
    { "network",            "bzz_getchunkqueueinfo",      &getchunkqueueinfo,      true,      true,       false },
    { "network",            "bzz_getchunkqueuetotals",    &getchunkqueuetotals,    true,      true,       false },

    /* Block chain and UTXO */
    { "blockchain",            "bzz_getblockchaininfo",      &getblockchaininfo,      true,      false,      false },
    { "blockchain",            "bzz_getbestblockhash",       &getbestblockhash,       true,      false,      false },
    { "blockchain",            "bzz_getblockcount",          &getblockcount,          true,       true,      false },
    { "blockchain",            "bzz_getlastblockinfo",       &getlastblockinfo,       true,      false,      false },
    { "blockchain",            "bzz_getblock",               &getblock,               true,      false,      false },
    { "blockchain",            "bzz_getblockhash",           &getblockhash,           true,      false,      false },
    { "blockchain",            "bzz_getchaintips",           &getchaintips,           true,      false,      false },
    { "blockchain",            "bzz_getdifficulty",          &getdifficulty,          true,      false,      false },
    { "blockchain",            "bzz_getmempoolinfo",         &getmempoolinfo,         true,      true,       false },
    { "blockchain",            "bzz_getrawmempool",          &getrawmempool,          true,      false,      false },
    { "blockchain",            "bzz_gettxout",               &gettxout,               true,      false,      false },
    { "blockchain",            "bzz_gettxoutsetinfo",        &gettxoutsetinfo,        true,      false,      false },
    { "blockchain",            "bzz_verifychain",            &verifychain,            true,      false,      false },
    { "blockchain",            "bzz_invalidateblock",        &invalidateblock,        true,      true,       false },
    { "blockchain",            "bzz_reconsiderblock",        &reconsiderblock,        true,      true,       false },

/* MCHN START */    
    { "blockchain",            "bzz_listassets",             &listassets,             true,      false,      false },
    { "blockchain",            "bzz_listpermissions",        &listpermissions,        true,      false,      false },
    { "blockchain",            "bzz_listminers",             &listminers,             true,      false,      false },
    { "blockchain",            "bzz_liststreams",            &liststreams,            true,      false,      false },
    { "blockchain",            "bzz_listupgrades",           &listupgrades,           true,      false,      false },
    { "blockchain",            "bzz_listtxfilters",          &listtxfilters,          true,      false,      false },
    { "blockchain",            "bzz_liststreamfilters",      &liststreamfilters,      true,      false,      false },
    { "blockchain",            "bzz_getfiltercode",          &getfiltercode,          true,      false,      false },
    { "blockchain",            "bzz_testtxfilter",           &testtxfilter,           true,      false,      false },
    { "blockchain",            "bzz_runtxfilter",            &runtxfilter,            true,      false,      false },
    { "blockchain",            "bzz_teststreamfilter",       &teststreamfilter,       true,      false,      false },
    { "blockchain",            "bzz_runstreamfilter",        &runstreamfilter,        true,      false,      false },
    { "blockchain",            "bzz_listblocks",             &listblocks,             true,      false,      false },
    { "blockchain",            "bzz_getassetinfo",           &getassetinfo,           true,      false,      false },
    { "blockchain",            "bzz_getstreaminfo",          &getstreaminfo,          true,      false,      false },
    { "blockchain",            "bzz_verifypermission",       &verifypermission,       true,      false,      false },

    { "blockchain",            "bzz_listvariables",          &listvariables,          true,      false,      false },
    { "blockchain",            "bzz_getvariableinfo",        &getvariableinfo,        true,      false,      false },
    { "blockchain",            "bzz_setvariablevalue",       &setvariablevalue,       true,      false,      false },
    { "blockchain",            "bzz_setvariablevaluefrom",   &setvariablevaluefrom,   true,      false,      false },
    { "blockchain",            "bzz_getvariablevalue",       &getvariablevalue,       true,      false,      false },
    { "blockchain",            "bzz_getvariablehistory",     &getvariablehistory,     true,      false,      false },
    { "blockchain",            "bzz_listassetissues",        &listassetissues,     true,      false,      false },

    { "blockchain",            "bzz_listlibraries",          &listlibraries,          true,      false,      false },
    { "blockchain",            "bzz_addlibraryupdate",       &addlibraryupdate,       true,      false,      false },
    { "blockchain",            "bzz_addlibraryupdatefrom",   &addlibraryupdatefrom,   true,      false,      false },
    { "blockchain",            "bzz_getlibrarycode",         &getlibrarycode,         true,      false,      false },
    { "blockchain",            "bzz_testlibrary",            &testlibrary,            true,      false,      false },
    
/* MCHN END */    
    
    /* Mining */
    { "mining",            "bzz_getblocktemplate",       &getblocktemplate,       true,      false,      false },
    { "mining",            "bzz_getmininginfo",          &getmininginfo,          true,      false,      false },
    { "mining",            "bzz_getnetworkhashps",       &getnetworkhashps,       true,      false,      false },
    { "mining",            "bzz_prioritisetransaction",  &prioritisetransaction,  true,      false,      false },
    { "mining",            "bzz_submitblock",            &submitblock,            true,      true,       false },

#ifdef ENABLE_WALLET
    /* Coin generation */
    { "generating",            "bzz_getgenerate",            &getgenerate,            true,      false,      false },
    { "generating",            "bzz_gethashespersec",        &gethashespersec,        true,      false,      false },
    { "generating",            "bzz_setgenerate",            &setgenerate,            true,      true,       false },
#endif

    /* Raw transactions */
    { "rawtransactions",            "bzz_appendrawtransaction",   &appendrawtransaction,   true,      false,      false },
    { "rawtransactions",            "bzz_createrawtransaction",   &createrawtransaction,   true,      false,      false },
    { "rawtransactions",            "bzz_decoderawtransaction",   &decoderawtransaction,   true,      false,      false },
    { "rawtransactions",            "bzz_decodescript",           &decodescript,           true,      false,      false },
    { "rawtransactions",            "bzz_getrawtransaction",      &getrawtransaction,      true,      false,      false },
    { "rawtransactions",            "bzz_sendrawtransaction",     &sendrawtransaction,     false,     false,      false },
    { "rawtransactions",            "bzz_signrawtransaction",     &signrawtransaction,     false,     false,      false }, /* uses wallet if enabled */
/* MCHN START */    
    { "rawtransactions",            "bzz_appendrawchange",        &appendrawchange,        false,     false,      false },
    { "hidden",            "bzz_appendrawmetadata",      &appendrawmetadata,      false,     false,      false },
    { "rawtransactions",            "bzz_appendrawdata",          &appendrawmetadata,      false,     false,      false },
    { "hidden",            "bzz_debug",                  &debug,                  false,     true,       false },
/* MCHN END */    

    /* Utility functions */
    { "util",            "bzz_createkeypairs",         &createkeypairs,         true,      true ,      false },
    { "util",            "bzz_createmultisig",         &createmultisig,         true,      true ,      false },
    { "util",            "bzz_validateaddress",        &validateaddress,        true,      false,      false }, /* uses wallet if enabled */
    { "util",            "bzz_verifymessage",          &verifymessage,          true,      false,      false },
    { "util",            "bzz_estimatefee",            &estimatefee,            true,      true,       false },
    { "util",            "bzz_estimatepriority",       &estimatepriority,       true,      true,       false },
    
    { "util",            "bzz_createbinarycache",      &createbinarycache,      true,      true,      false },
    { "util",            "bzz_appendbinarycache",      &appendbinarycache,      true,      true,      false },
    { "util",            "bzz_deletebinarycache",      &deletebinarycache,      true,      true,      false },

    /* Not shown in help */
    { "hidden",            "bzz_invalidateblock",        &invalidateblock,        true,      true,       false },
    { "hidden",            "bzz_reconsiderblock",        &reconsiderblock,        true,      true,       false },
    { "hidden",            "bzz_setmocktime",            &setmocktime,            true,      false,      false },
    { "hidden",            "bzz_data-all",               &purehelpitem_nomethod,  true,      true,       false },
    { "hidden",            "bzz_data-with",              &purehelpitem_nomethod,  true,      true,       false },
    { "hidden",            "bzz_addresses-all",          &purehelpitem_nomethod,  true,      true,       false },
    { "hidden",            "bzz_feed-options",           &purehelpitem_nomethod,  true,      true,       false },
    
    { "hidden",            "bzz_getfilterstreamitem",    &purehelpitem_onlyfilter,true,      false,      false },
    { "hidden",            "bzz_getfilterstream",        &purehelpitem_onlyfilter,true,      false,      false },
    { "hidden",            "bzz_getfiltertransaction",   &purehelpitem_onlyfilter,true,      false,      false },
    { "hidden",            "bzz_getfilterassetbalances", &purehelpitem_onlyfilter,true,      false,      false },
    { "hidden",            "bzz_getfiltertxid",          &purehelpitem_onlyfilter,true,      true,       false },
    { "hidden",            "bzz_getfiltertxinput",       &purehelpitem_onlyfilter,true,      true,       false },
    { "hidden",            "bzz_setfilterparam",         &purehelpitem_onlyfilter,true,      true,       false },
    { "hidden",            "bzz_filters",                &purehelpitem_nomethod,  true,      true,       false },

#ifdef ENABLE_WALLET
    /* Licensing */
    { "hidden",            "bzz_getlicenserequest",      &getlicenserequest,       true,      false,      true },
    { "hidden",            "bzz_decodelicenserequest",   &decodelicenserequest,    true,      false,      true },
    { "hidden",            "bzz_decodelicenseconfirmation",   &decodelicenseconfirmation,    true,      false,      true },
    { "hidden",            "bzz_activatelicense",        &activatelicense,         true,      false,      true },
    { "hidden",            "bzz_activatelicensefrom",    &activatelicensefrom,     true,      false,      true },
    { "hidden",            "bzz_transferlicense",        &transferlicense,         true,      false,      true },
    { "hidden",            "bzz_takelicense",            &takelicense,             true,      false,      true },
    { "hidden",            "bzz_listlicenses",           &listlicenses,            true,      false,      true },
    { "hidden",            "bzz_getlicenseconfirmation", &getlicenseconfirmation,  true,      false,      true },
    { "hidden",            "bzz_importlicenserequest",   &importlicenserequest,       true,      false,      true },
    
    { "feeds",            "bzz_createfeed",             &createfeed,              true,      false,      false },
    { "feeds",            "bzz_deletefeed",             &deletefeed,              true,      true,       false },
    { "feeds",            "bzz_pausefeed",              &pausefeed,               true,      false,      false },
    { "feeds",            "bzz_resumefeed",             &resumefeed,              true,      false,      false },
    { "feeds",            "bzz_addtofeed",              &addtofeed,               true,      false,      false },
    { "feeds",            "bzz_updatefeed",             &updatefeed,              true,      false,      false },
    { "feeds",            "bzz_purgefeed",              &purgefeed,               true,      true,       false },
    { "feeds",            "bzz_listfeeds",              &listfeeds,               true,      false,      false },
    { "feeds",            "bzz_getdatarefdata",         &getdatarefdata,          true,      true,      false },
    { "feeds",            "bzz_datareftobinarycache",   &datareftobinarycache,    true,      true,      false },

    /* Wallet */
    { "wallet",            "bzz_addmultisigaddress",     &addmultisigaddress,     true,      false,      true },
    { "wallet",            "bzz_backupwallet",           &backupwallet,           true,      false,      true },
    { "wallet",            "bzz_dumpprivkey",            &dumpprivkey,            true,      false,      true },
    { "wallet",            "bzz_dumpwallet",             &dumpwallet,             true,      false,      true },
    { "wallet",            "bzz_encryptwallet",          &encryptwallet,          true,      false,      true },
    { "wallet",            "bzz_getaccountaddress",      &getaccountaddress,      true,      false,      true },
    { "wallet",            "bzz_getaccount",             &getaccount,             true,      false,      true },
    { "wallet",            "bzz_getaddressesbyaccount",  &getaddressesbyaccount,  true,      false,      true },
    { "wallet",            "bzz_getbalance",             &getbalance,             false,     false,      true },
    { "wallet",            "bzz_getnewaddress",          &getnewaddress,          true,      false,      true },
    { "wallet",            "bzz_getrawchangeaddress",    &getrawchangeaddress,    true,      false,      true },
    { "wallet",            "bzz_getreceivedbyaccount",   &getreceivedbyaccount,   false,     false,      true },
    { "wallet",            "bzz_getreceivedbyaddress",   &getreceivedbyaddress,   false,     false,      true },
    { "wallet",            "bzz_gettransaction",         &gettransaction,         false,     false,      true },
    { "wallet",            "bzz_getunconfirmedbalance",  &getunconfirmedbalance,  false,     false,      true },
    { "wallet",            "bzz_getwalletinfo",          &getwalletinfo,          false,     false,      true },
    { "wallet",            "bzz_importprivkey",          &importprivkey,          true,      false,      true },
    { "wallet",            "bzz_importwallet",           &importwallet,           true,      false,      true },
    { "wallet",            "bzz_importaddress",          &importaddress,          true,      false,      true },
    { "wallet",            "bzz_keypoolrefill",          &keypoolrefill,          true,      false,      true },
    { "wallet",            "bzz_listaccounts",           &listaccounts,           false,     false,      true },
    { "wallet",            "bzz_listaddressgroupings",   &listaddressgroupings,   false,     false,      true },
    { "wallet",            "bzz_listlockunspent",        &listlockunspent,        false,     false,      true },
    { "wallet",            "bzz_listreceivedbyaccount",  &listreceivedbyaccount,  false,     false,      true },
    { "wallet",            "bzz_listreceivedbyaddress",  &listreceivedbyaddress,  false,     false,      true },
    { "wallet",            "bzz_listsinceblock",         &listsinceblock,         false,     false,      true },
    { "wallet",            "bzz_listtransactions",       &listtransactions,       false,     false,      true },
    { "wallet",            "bzz_listunspent",            &listunspent,            false,     false,      true },
    { "wallet",            "bzz_lockunspent",            &lockunspent,            true,      false,      true },
    { "wallet",            "bzz_move",                   &movecmd,                false,     false,      true },
//    { "wallet",            "bzz_sendfrom",               &sendfrom,               false,     false,      true },
    { "wallet",            "bzz_sendfromaccount",        &sendfrom,               false,     false,      true },
    { "wallet",            "bzz_sendmany",               &sendmany,               false,     false,      true },
    { "hidden",            "bzz_sendtoaddress",          &sendtoaddress,          false,     false,      true },
    { "wallet",            "bzz_send",                   &sendtoaddress,          false,     false,      true },
/* MCHN START */    
    { "wallet",            "bzz_getaddresses",           &getaddresses,           true,      false,      true },
    { "wallet",            "bzz_combineunspent",         &combineunspent,         false,     false,      true }, 
    { "wallet",            "bzz_grant",                  &grantcmd,               false,     false,      true }, 
    { "wallet",            "bzz_revoke",                 &revokecmd,              false,     false,      true },
    { "wallet",            "bzz_issue",                  &issuecmd,               false,     false,      true },
    { "wallet",            "bzz_issuemore",              &issuemorecmd,           false,     false,      true },
    { "wallet",            "bzz_getassetbalances",       &getassetbalances,       false,     false,      true },
    { "wallet",            "bzz_gettotalbalances",       &gettotalbalances,       false,     false,      true },
    { "hidden",            "bzz_sendassettoaddress",     &sendassettoaddress,     false,     false,      true },
    { "wallet",            "bzz_sendasset",              &sendassettoaddress,     false,     false,      true },
    { "wallet",            "bzz_preparelockunspent",     &preparelockunspent,     false,     false,      true },
    { "wallet",            "bzz_createrawexchange",      &createrawexchange,      false,     false,      true },
    { "wallet",            "bzz_appendrawexchange",      &appendrawexchange,      false,     false,      true },
    { "wallet",            "bzz_completerawexchange",    &completerawexchange,    false,     false,      true },
    { "wallet",            "bzz_decoderawexchange",      &decoderawexchange,      false,     false,      true },
    
    { "wallet",            "bzz_grantfrom",              &grantfromcmd,           false,     false,      true }, 
    { "wallet",            "bzz_approvefrom",            &approvefrom,            false,     false,      true }, 
    { "wallet",            "bzz_revokefrom",             &revokefromcmd,          false,     false,      true },
    { "wallet",            "bzz_issuefrom",              &issuefromcmd,           false,     false,      true },
    { "wallet",            "bzz_issuemorefrom",          &issuemorefromcmd,       false,     false,      true },
    { "wallet",            "bzz_preparelockunspentfrom", &preparelockunspentfrom, false,     false,      true },
    { "wallet",            "bzz_sendassetfrom",          &sendassetfrom,          false,     false,      true },
    { "hidden",            "bzz_sendfromaddress",        &sendfromaddress,        false,     false,      true },
    { "wallet",            "bzz_sendfrom",               &sendfromaddress,        false,     false,      true },
    { "wallet",            "bzz_getmultibalances",       &getmultibalances,       false,     false,      true },
    { "wallet",            "bzz_getaddressbalances",     &getaddressbalances,     false,     false,      true },
    { "wallet",            "bzz_disablerawtransaction",  &disablerawtransaction,  false,     false,      true },
    { "hidden",            "bzz_sendwithmetadata",       &sendwithmetadata,       false,     false,      true },
    { "wallet",            "bzz_sendwithdata",           &sendwithmetadata,       false,     false,      true },
    { "hidden",            "bzz_sendwithmetadatafrom",   &sendwithmetadatafrom,   false,     false,      true },
    { "wallet",            "bzz_sendwithdatafrom",       &sendwithmetadatafrom,   false,     false,      true },
    { "hidden",            "bzz_grantwithmetadata",      &grantwithmetadata,      false,     false,      true },
    { "wallet",            "bzz_grantwithdata",          &grantwithmetadata,      false,     false,      true },
    { "hidden",            "bzz_grantwithmetadatafrom",  &grantwithmetadatafrom,  false,     false,      true },
    { "wallet",            "bzz_grantwithdatafrom",      &grantwithmetadatafrom,  false,     false,      true },
    { "wallet",            "bzz_createrawsendfrom",      &createrawsendfrom,      false,     false,      true },
    
    { "wallet",            "bzz_listaddresses",          &listaddresses,          false,     false,      true },
    { "wallet",            "bzz_listwallettransactions", &listwallettransactions, false,     false,      true },
    { "wallet",            "bzz_listaddresstransactions",&listaddresstransactions,false,     false,      true },
    { "wallet",            "bzz_getwallettransaction",   &getwallettransaction,   false,     false,      true },
    { "wallet",            "bzz_getaddresstransaction",  &getaddresstransaction,  false,     false,      true },
    { "wallet",            "bzz_resendwallettransactions",&resendwallettransactions,  false,     false,      true },
    
    { "wallet",            "bzz_create",                 &createcmd,               false,     false,      true },
    { "wallet",            "bzz_createfrom",             &createfromcmd,           false,     false,      true },
    { "wallet",            "bzz_publish",                &publish,                 false,     false,      true },
    { "wallet",            "bzz_publishfrom",            &publishfrom,             false,     false,      true },
    { "wallet",            "bzz_publishmulti",           &publishmulti,            false,     false,      true },
    { "wallet",            "bzz_publishmultifrom",       &publishmultifrom,        false,     false,      true },
    { "wallet",            "bzz_subscribe",              &subscribe,               false,     false,      true },
    { "wallet",            "bzz_unsubscribe",            &unsubscribe,             false,     false,      true },
    { "wallet",            "bzz_trimsubscribe",          &trimsubscribe,           false,     false,      true },
    { "wallet",            "bzz_retrievestreamitems",    &retrievestreamitems,     false,     false,      true },
    { "wallet",            "bzz_purgestreamitems",       &purgestreamitems,        false,     false,      true },
    { "wallet",            "bzz_purgepublisheditems",    &purgepublisheditems,     false,     false,      true },
    { "wallet",            "bzz_listassettransactions",  &listassettransactions,   false,     false,      true },
    { "wallet",            "bzz_getassettransaction",    &getassettransaction,     false,     false,      true },
    { "wallet",            "bzz_getstreamitem",          &getstreamitem,           false,      true,      true },
    { "wallet",            "bzz_liststreamtxitems",      &liststreamtxitems,       false,      true,      true },
    { "wallet",            "bzz_liststreamitems",        &liststreamitems,         false,      true,      false },
    { "wallet",            "bzz_liststreamqueryitems",   &liststreamqueryitems,    false,     true,      true },
    { "wallet",            "bzz_liststreamkeyitems",     &liststreamkeyitems,      false,      true,      true },
    { "wallet",            "bzz_liststreampublisheritems",&liststreampublisheritems,false,     true,      true },
    { "wallet",            "bzz_liststreamkeys",         &liststreamkeys,          false,      true,      true },
    { "wallet",            "bzz_liststreampublishers",   &liststreampublishers,    false,      true,      true },
    { "wallet",            "bzz_gettxoutdata",           &gettxoutdata,            false,     true,      true },
    { "wallet",            "bzz_txouttobinarycache",     &txouttobinarycache,      false,     true,      true },
    { "wallet",            "bzz_liststreamblockitems",   &liststreamblockitems,    false,     true,      false },
    { "wallet",            "bzz_getstreamkeysummary",    &getstreamkeysummary,     false,     true,      true },
    { "wallet",            "bzz_getstreampublishersummary",&getstreampublishersummary,false,  true,      true },
    { "hidden",            "bzz_storechunk",             &storechunk,              false,     false,      true },
    
    { "wallet",            "bzz_explorerlisttransactions",             &explorerlisttransactions,              false,      true,      false },
    { "wallet",            "bzz_explorerlistaddresses",       &explorerlistaddresses,        false,      true,      false },
    { "wallet",            "bzz_explorerlistaddresstransactions",      &explorerlistaddresstransactions,       false,      true,      false },
    { "wallet",            "bzz_explorerlistblocktransactions",        &explorerlistblocktransactions,         false,      true,      false },
    { "wallet",            "bzz_explorerlistredeemtransactions",       &explorerlistredeemtransactions,        false,      true,      false },
    { "wallet",            "bzz_explorerlistaddressassets",   &explorerlistaddressassets,    false,      true,      false },
    { "wallet",            "bzz_explorerlistaddressstreams",  &explorerlistaddressstreams,   false,      true,      false },
    { "wallet",            "bzz_explorerlistassetaddresses",  &explorerlistassetaddresses,   false,      true,      false },
    { "wallet",            "bzz_explorerlistaddressassettransactions", &explorerlistaddressassettransactions,  false,      true,      false },
    { "wallet",            "bzz_explorergetrawtransaction", &explorergetrawtransaction,                false,      false,     false },
    
/* MCHN END */    
    { "wallet",            "bzz_setaccount",             &setaccount,             true,      false,      true },
    { "wallet",            "bzz_settxfee",               &settxfee,               true,      false,      true },
    { "wallet",            "bzz_signmessage",            &signmessage,            true,      false,      true },
    { "wallet",            "bzz_walletlock",             &walletlock,             true,      false,      true },
    { "wallet",            "bzz_walletpassphrasechange", &walletpassphrasechange, true,      false,      true },
    { "wallet",            "bzz_walletpassphrase",       &walletpassphrase,       true,      false,      true },
#endif // ENABLE_WALLET
};

void mc_InitRPCList(std::vector<CRPCCommand>& vStaticRPCCommands,std::vector<CRPCCommand>& vStaticRPCWalletReadCommands)
{
    unsigned int vcidx;
    vStaticRPCCommands.clear();
    vStaticRPCWalletReadCommands.clear();
    for (vcidx = 0; vcidx < (sizeof(vRPCCommands) / sizeof(vRPCCommands[0])); vcidx++)
    {
        vStaticRPCCommands.push_back(vRPCCommands[vcidx]);
    }    
    for (vcidx = 0; vcidx < (sizeof(vRPCWalletReadCommands) / sizeof(vRPCWalletReadCommands[0])); vcidx++)
    {
        vStaticRPCWalletReadCommands.push_back(vRPCCommands[vcidx]);
    }    
}
