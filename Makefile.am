FwalDIST_SUBDIRS = secp256k1
AM_LDFLAGS = $(PTHREAD_CFLAGS) $(LIBTOOL_LDFLAGS)
CXXFLAGS += -std=c++0x

CPPFLAGS += -Wno-deprecated-declarations -Wno-unused-local-typedefs -Wno-unused-result -DBOOST_SYSTEM_NO_DEPRECATED=1 

if EMBEDDED_LEVELDB
LEVELDB_CPPFLAGS += -I$(srcdir)/leveldb/include
LEVELDB_CPPFLAGS += -I$(srcdir)/leveldb/helpers/memenv
LEVELDB_CPPFLAGS += -Wno-deprecated
LIBLEVELDB += $(builddir)/leveldb/libleveldb.a
LIBMEMENV  += $(builddir)/leveldb/libmemenv.a

# NOTE: This dependency is not strictly necessary, but without it make may try to build both in parallel, which breaks the LevelDB build system in a race
$(LIBLEVELDB): $(LIBMEMENV)

$(LIBLEVELDB) $(LIBMEMENV):
	@echo "Building LevelDB ..." && $(MAKE) -C $(@D) $(@F) CXX="$(CXX)" \
	  CC="$(CC)" PLATFORM=$(TARGET_OS) AR="$(AR)" $(LEVELDB_TARGET_FLAGS) \
          OPT="$(CXXFLAGS) $(CPPFLAGS)"
endif

_ebzz_ebzz_CONFIG_INCLUDES=-I$(builddir)/config
_ebzz_ebzz_INCLUDES=-I$(builddir) -I$(builddir)/obj $(BOOST_CPPFLAGS) $(LEVELDB_CPPFLAGS) $(CRYPTO_CFLAGS) $(SSL_CFLAGS)

_ebzz_ebzz_INCLUDES += -I$(srcdir)/secp256k1/include

LIB_ebzz_ebzz_ENTERPRISE=lib_ebzz_ebzz_enterprise.a
LIB_ebzz_ebzz_COMMUNITY=lib_ebzz_ebzz_community.a
LIB_ebzz_ebzz_SERVER=lib_ebzz_ebzz_server.a
LIB_ebzz_ebzz_WALLET=lib_ebzz_ebzz_wallet.a
LIB_ebzz_ebzz_COMMON=lib_ebzz_ebzz_common.a
LIB_ebzz_ebzz_CLI=lib_ebzz_ebzz_cli.a
LIB_ebzz_ebzz_UTIL=lib_ebzz_ebzz_util.a
LIB_ebzz_ebzz_CRYPTO=crypto/lib_ebzz_ebzz_crypto.a
LIB_ebzz_ebzz__ebzz_ebzz=_ebzz_ebzz/lib_ebzz_ebzz__ebzz_ebzz.a
LIB_ebzz_ebzz_UNIVALUE=univalue/lib_ebzz_ebzz_univalue.a
LIB_ebzz_ebzzQT=qt/lib_ebzz_ebzzqt.a
LIBSECP256K1=secp256k1/libsecp256k1.la
if !TARGET_WINDOWS
LIB_ebzz_ebzz_V8=lib_ebzz_ebzz_v8.a
endif

$(LIBSECP256K1): $(wildcard secp256k1/src/*) $(wildcard secp256k1/include/*)
	$(AM_V_at)$(MAKE) $(AM_MAKEFLAGS) -C $(@D) $(@F)

# Make is not made aware of per-object dependencies to avoid limiting building parallelization
# But to build the less dependent modules first, we manually select their order here:
EXTRA_LIBRARIES = \
  crypto/lib_ebzz_ebzz_crypto.a \
  _ebzz_ebzz/lib_ebzz_ebzz__ebzz_ebzz.a \
  lib_ebzz_ebzz_util.a \
  lib_ebzz_ebzz_common.a \
  univalue/lib_ebzz_ebzz_univalue.a \
  lib_ebzz_ebzz_enterprise.a \
  lib_ebzz_ebzz_community.a \
  lib_ebzz_ebzz_server.a \
  lib_ebzz_ebzz_cli.a
if ENABLE_WALLET
_ebzz_ebzz_INCLUDES += $(BDB_CPPFLAGS)
EXTRA_LIBRARIES += lib_ebzz_ebzz_wallet.a
endif
if !TARGET_WINDOWS
EXTRA_LIBRARIES += $(LIB_ebzz_ebzz_V8)
endif
if BUILD__ebzz_ebzz_LIBS
lib_LTLIBRARIES = lib_ebzz_ebzzconsensus.la
LIB_ebzz_ebzz_CONSENSUS=lib_ebzz_ebzzconsensus.la
else
LIB_ebzz_ebzz_CONSENSUS=
endif

bin_PROGRAMS =
TESTS =

if BUILD__ebzz_ebzzD
#  bin_PROGRAMS += _ebzz_ebzzd _ebzz_ebzzd						# MCHN
  bin_PROGRAMS += _ebzz_ebzzd _ebzz_ebzzd-cold					# MCHN
endif

if BUILD__ebzz_ebzz_UTILS
#  bin_PROGRAMS += _ebzz_ebzz-util _ebzz_ebzz-cli _ebzz_ebzz-cli _ebzz_ebzz-tx		# MCHN
  bin_PROGRAMS += _ebzz_ebzz-util _ebzz_ebzz-cli 		# MCHN
endif

.PHONY: FORCE
# _ebzz_ebzz core #
_ebzz_ebzz_CORE_H = \
  storage/addrman.h \
  structs/alert.h \
  utils/allocators.h \
  structs/amount.h \
  structs/base58.h \
  structs/bloom.h \
  chain/chain.h \
  chainparams/chainparams.h \
  chainparams/chainparamsbase.h \
  chainparams/chainparamsseeds.h \
  chain/checkpoints.h \
  checkqueue.h \
  version/clientversion.h \
  coincontrol.h \
  storage/coins.h \
  utils/compat.h \
  utils/compressor.h \
  primitives/block.h \
  primitives/transaction.h \
  utils/core_io.h \
  wallet/crypter.h \
  wallet/dbflat.h \
  wallet/db.h \
  wallet/dbwrap.h \
  structs/hash.h \
  core/init.h \
  keys/key.h \
  wallet/keystore.h \
  storage/leveldbwrapper.h \
  structs/limitedmap.h \
  core/main.h \
  chain/merkleblock.h \
  miner/miner.h \
  utils/mruset.h \
  net/netbase.h \
  net/net.h \
  ui/noui.h \
  chain/pow.h \
  protocol/netprotocol.h \
  keys/pubkey.h \
  utils/random.h \
  utils/utilparse.h \
  rpc/rpcclient.h \
  rpc/rpcprotocol.h \
  rpc/rpcasio.h \
  rpc/rpcutils.h \
  rpc/rpcwallet.h \
  rpc/rpcserver.h \
  script/interpreter.h \
  script/interpreter.h \
  script/script.h \
  script/sigcache.h \
  script/sign.h \
  script/standard.h \
  script/script_error.h \
  utils/serialize.h \
  utils/streams.h \
  utils/sync.h \
  utils/threadsafety.h \
  utils/timedata.h \
  utils/tinyformat.h \
  storage/txdb.h \
  chain/txmempool.h \
  ui/ui_interface.h \
  structs/uint256.h \
  chain/undo.h \
  utils/util.h \
  utils/utilstrencodings.h \
  utils/utilmoneystr.h \
  utils/utiltime.h \
  version/bcversion.h \
  wallet/wallet.h \
  wallet/wallettxs.h \
  wallet/wallet_ismine.h \
  wallet/walletdb.h \
  compat/sanity.h

JSON_H = \
  json/json_spirit.h \
  json/json_spirit_error_position.h \
  json/json_spirit_reader.h \
  json/json_spirit_reader_template.h \
  json/json_spirit_stream_reader.h \
  json/json_spirit_utils.h \
  json/json_spirit_value.h \
  json/json_spirit_writer.h \
  json/json_spirit_writer_template.h \
  json_spirit_ubjson.h

obj/build.h: FORCE
	@$(MKDIR_P) $(builddir)/obj
	@$(top_srcdir)/share/genbuild.sh $(abs_top_builddir)/src/obj/build.h \
	  $(abs_top_srcdir)
lib_ebzz_ebzz_util_a-clientversion.$(OBJEXT): obj/build.h

lib_ebzz_ebzz_community_a_CPPFLAGS = $(_ebzz_ebzz_INCLUDES)
lib_ebzz_ebzz_community_a_SOURCES = \
  community/community.cpp \
  wallet/db.cpp \
  wallet/dbwrap_com.cpp

if ENABLE_ENTERPRISE
include entMakefile.am
else
lib_ebzz_ebzz_enterprise_a_CPPFLAGS = $(_ebzz_ebzz_INCLUDES)
lib_ebzz_ebzz_enterprise_a_SOURCES = \
  community/community.cpp \
  wallet/db.cpp \
  wallet/dbwrap_com.cpp
endif

# server: shared between _ebzz_ebzzd and _ebzz_ebzz-qt
lib_ebzz_ebzz_server_a_CPPFLAGS = $(_ebzz_ebzz_INCLUDES) $(MINIUPNPC_CPPFLAGS)
lib_ebzz_ebzz_server_a_SOURCES = \
  storage/addrman.cpp \
  structs/alert.cpp \
  structs/bloom.cpp \
  chain/chain.cpp \
  chain/checkpoints.cpp \
  core/init.cpp \
  storage/leveldbwrapper.cpp \
  core/main.cpp \
  protocol/_ebzz_ebzztx.cpp \
  protocol/_ebzz_ebzzblock.cpp \
  custom/custom_server.cpp \
  filters/_ebzz_ebzzfilter.cpp \
  protocol/relay.cpp \
  protocol/handshake.cpp \
  chain/merkleblock.cpp \
  miner/miner.cpp \
  net/net.cpp \
  ui/noui.cpp \
  chain/pow.cpp \
  net/rest.cpp \
  utils/utilparse.cpp \
  json/json_spirit_ubjson.cpp \
  rpc/rpcrawdata.cpp \
  rpc/rpcutils.cpp \
  rpc/rpccache.cpp \
  rpc/rpcchunks.cpp \
  rpc/rpcdebug.cpp \
  rpc/rpchelp.cpp \
  rpc/rpcblockchain.cpp \
  rpc/rpcmining.cpp \
  rpc/rpcmisc.cpp \
  rpc/rpcnet.cpp \
  rpc/rpcrawtransaction.cpp \
  rpc/rpcfeeds.cpp \
  rpc/rpcserver.cpp \
  script/sigcache.cpp \
  utils/timedata.cpp \
  storage/txdb.cpp \
  chain/txmempool.cpp \
  $(JSON_H) \
  $(_ebzz_ebzz_CORE_H)

# wallet: shared between _ebzz_ebzzd and _ebzz_ebzz-qt, but only linked
# when wallet enabled
lib_ebzz_ebzz_wallet_a_CPPFLAGS = $(_ebzz_ebzz_INCLUDES)
lib_ebzz_ebzz_wallet_a_SOURCES = \
  wallet/dbflat.cpp \
  wallet/crypter.cpp \
  community/license.cpp \
  rpc/rpcdump.cpp \
  rpc/rpcwallet.cpp \
  rpc/rpcwalletutils.cpp \
  rpc/rpcwallettxs.cpp \
  rpc/rpcexchange.cpp \
  rpc/rpcwalletsend.cpp \
  rpc/rpcpermissions.cpp \
  rpc/rpcassets.cpp \
  rpc/rpcstreams.cpp \
  rpc/rpcupgrades.cpp \
  rpc/rpcfilters.cpp \
  rpc/rpcvariables.cpp \
  rpc/rpclibraries.cpp \
  rpc/rpclicense.cpp \
  rpc/rpcexplorer.cpp \
  wallet/wallet.cpp \
  wallet/walletcoins.cpp \
  wallet/wallettxs.cpp \
  wallet/wallet_ismine.cpp \
  wallet/walletdb.cpp \
  $(_ebzz_ebzz_CORE_H)

# crypto primitives library
crypto_lib_ebzz_ebzz_crypto_a_CPPFLAGS = $(_ebzz_ebzz_CONFIG_INCLUDES)
crypto_lib_ebzz_ebzz_crypto_a_SOURCES = \
  crypto/sha1.cpp \
  crypto/sha256.cpp \
  crypto/sha512.cpp \
  crypto/hmac_sha256.cpp \
  crypto/hmac_sha512.cpp \
  crypto/ripemd160.cpp \
  crypto/common.h \
  crypto/sha256.h \
  crypto/sha512.h \
  crypto/hmac_sha256.h \
  crypto/hmac_sha512.h \
  crypto/sha1.h \
  crypto/ripemd160.h




# _ebzz_ebzz library
_ebzz_ebzz_lib_ebzz_ebzz__ebzz_ebzz_a_CPPFLAGS = $(_ebzz_ebzz_CONFIG_INCLUDES)
_ebzz_ebzz_lib_ebzz_ebzz__ebzz_ebzz_a_SOURCES = \
  utils/utility.cpp \
  utils/systemdependent.cpp \
  utils/tools.cpp \
  utils/utilwrapper.cpp \
  version/version.cpp \
  custom/custom.cpp \
  custom/custom__ebzz_ebzz.cpp \
  chainparams/params.cpp \
  protocol/_ebzz_ebzzscript.cpp \
  utils/dbwrapper.cpp \
  wallet/wallettxdb.cpp \
  wallet/chunkdb.cpp \
  wallet/chunkcollector.cpp \
  permissions/permission.cpp \
  entities/asset.cpp

# univalue JSON library
univalue_lib_ebzz_ebzz_univalue_a_SOURCES = \
  univalue/univalue.cpp \
  univalue/univalue_read.cpp \
  univalue/univalue_write.cpp \
  univalue/univalue_escapes.h \
  univalue/univalue.h

# common: shared between _ebzz_ebzzd, and _ebzz_ebzz-qt and non-server tools
lib_ebzz_ebzz_common_a_CPPFLAGS = $(_ebzz_ebzz_INCLUDES)
lib_ebzz_ebzz_common_a_SOURCES = \
  utils/allocators.cpp \
  structs/amount.cpp \
  structs/base58.cpp \
  chainparams/chainparams.cpp \
  storage/coins.cpp \
  utils/compressor.cpp \
  primitives/block.cpp \
  primitives/transaction.cpp \
  utils/core_read.cpp \
  utils/core_write.cpp \
  structs/hash.cpp \
  keys/key.cpp \
  wallet/keystore.cpp \
  net/netbase.cpp \
  protocol/netprotocol.cpp \
  keys/pubkey.cpp \
  script/interpreter.cpp \
  script/script.cpp \
  script/sign.cpp \
  script/standard.cpp \
  script/script_error.cpp \
  $(_ebzz_ebzz_CORE_H)

# util: shared between all executables.
# This library *must* be included to make sure that the glibc
# backward-compatibility objects and their sanity checks are linked.
lib_ebzz_ebzz_util_a_CPPFLAGS = $(_ebzz_ebzz_INCLUDES)
lib_ebzz_ebzz_util_a_SOURCES = \
  compat/strnlen.cpp \
  compat/glibc_sanity.cpp \
  compat/glibcxx_sanity.cpp \
  chainparams/chainparamsbase.cpp \
  version/clientversion.cpp \
  utils/random.cpp \
  rpc/rpcprotocol.cpp \
  utils/sync.cpp \
  structs/uint256.cpp \
  utils/util.cpp \
  utils/utilstrencodings.cpp \
  utils/utilmoneystr.cpp \
  utils/utiltime.cpp \
  $(_ebzz_ebzz_CORE_H)

if GLIBC_BACK_COMPAT
lib_ebzz_ebzz_util_a_SOURCES += compat/glibc_compat.cpp
lib_ebzz_ebzz_util_a_SOURCES += compat/glibcxx_compat.cpp
endif

# cli: shared between _ebzz_ebzz-cli and _ebzz_ebzz-qt
lib_ebzz_ebzz_cli_a_CPPFLAGS = $(_ebzz_ebzz_INCLUDES)
lib_ebzz_ebzz_cli_a_SOURCES = \
  rpc/rpcclient.cpp \
  $(_ebzz_ebzz_CORE_H)

nodist_lib_ebzz_ebzz_util_a_SOURCES = $(srcdir)/obj/build.h
#

# _ebzz_ebzzd binary #
#_ebzz_ebzzd_LDADD = \
  $(LIB_ebzz_ebzz_SERVER) \
  $(LIB_ebzz_ebzz_COMMON) \
  $(LIB_ebzz_ebzz_UNIVALUE) \
  $(LIB_ebzz_ebzz_WALLET) \
  $(LIB_ebzz_ebzz__ebzz_ebzz) \
  $(LIB_ebzz_ebzz_UTIL) \
  $(LIB_ebzz_ebzz_CRYPTO) \
  $(LIBLEVELDB) \
  $(LIBMEMENV) \
  $(LIBSECP256K1)

#if ENABLE_WALLET
#_ebzz_ebzzd_LDADD += lib_ebzz_ebzz_wallet.a
#endif
#_ebzz_ebzzd_LDADD += _ebzz_ebzz/lib_ebzz_ebzz__ebzz_ebzz.a
#_ebzz_ebzzd_SOURCES = _ebzz_ebzzd.cpp chainparams/buildgenesis.cpp
#

if TARGET_WINDOWS
#_ebzz_ebzzd_SOURCES += _ebzz_ebzzd-res.rc
endif

#_ebzz_ebzzd_LDADD += $(BOOST_LIBS) $(BDB_LIBS) $(SSL_LIBS) $(CRYPTO_LIBS) $(MINIUPNPC_LIBS)
#_ebzz_ebzzd_CPPFLAGS = $(_ebzz_ebzz_INCLUDES)
#_ebzz_ebzzd_LDFLAGS = $(RELDFLAGS) $(AM_LDFLAGS) $(LIBTOOL_APP_LDFLAGS)

# _ebzz_ebzz-cli binary #
#_ebzz_ebzz_cli_LDADD = \
  $(LIB_ebzz_ebzz_CLI) \
  $(LIB_ebzz_ebzz_UTIL) \
  $(LIB_ebzz_ebzz__ebzz_ebzz) \
  $(LIB_ebzz_ebzz_CRYPTO) \
  $(LIBLEVELDB) \
  $(BOOST_LIBS) \
  $(SSL_LIBS) \
  $(CRYPTO_LIBS)

#_ebzz_ebzz_cli_SOURCES = \
  _ebzz_ebzz-cli.cpp

#_ebzz_ebzz_cli_CPPFLAGS = $(_ebzz_ebzz_INCLUDES)
#

# _ebzz_ebzz-tx binary #
#_ebzz_ebzz_tx_LDADD = \
  $(LIB_ebzz_ebzz_COMMON) \
  $(LIB_ebzz_ebzz_UNIVALUE) \
  $(LIB_ebzz_ebzz__ebzz_ebzz) \
  $(LIB_ebzz_ebzz_UTIL) \
  $(LIB_ebzz_ebzz_CRYPTO) \
  $(LIBLEVELDB) \
  $(LIBSECP256K1) \
  $(BOOST_LIBS) \
  $(CRYPTO_LIBS)

#_ebzz_ebzz_tx_SOURCES = _ebzz_ebzz-tx.cpp
#_ebzz_ebzz_tx_CPPFLAGS = $(_ebzz_ebzz_INCLUDES)
#
#_ebzz_ebzz_tx_LDFLAGS = $(RELDFLAGS) $(AM_LDFLAGS) $(LIBTOOL_APP_LDFLAGS)

if TARGET_WINDOWS
#_ebzz_ebzz_cli_SOURCES += _ebzz_ebzz-cli-res.rc
endif
#_ebzz_ebzz_cli_LDFLAGS = $(RELDFLAGS) $(AM_LDFLAGS) $(LIBTOOL_APP_LDFLAGS)

# MCHN START

V8_ROOT = $(top_builddir)/v8build/v8
V8_INCLUDE = -I$(V8_ROOT)/include
V8_LIB_DIR = $(V8_ROOT)/out.gn/x64.release/obj
V8_LIBS = \
    -L$(V8_LIB_DIR) -L$(V8_LIB_DIR)/third_party/icu
if !TARGET_DARWIN
V8_LIBS += \
    -Wl,--start-group
endif
V8_LIBS += \
        -lv8_libbase \
        -lv8_libplatform \
        -lv8_base \
        -lv8_external_snapshot \
        -lv8_libsampler \
        -licuuc \
        -licui18n \
        -lv8_data \
    -ldl
if !TARGET_DARWIN
V8_LIBS += \
    -lrt
endif

lib_ebzz_ebzz_v8_a_SOURCES = \
  v8/v8engine.cpp \
  v8/v8filter.cpp \
  v8/callbacks.cpp \
  v8/v8json_spirit.cpp

#if TARGET_WINDOWS
#lib_ebzz_ebzz_v8_a_SOURCES += v8/callbacks_win.cpp v8/v8blob.dpp
#endif

lib_ebzz_ebzz_v8_a_CPPFLAGS = $(_ebzz_ebzz_INCLUDES) $(V8_INCLUDE)

# _ebzz_ebzzd binary #
_ebzz_ebzzd_LDADD = \
  $(LIB_ebzz_ebzz_SERVER) \
  $(LIB_ebzz_ebzz_COMMON) \
  $(LIB_ebzz_ebzz_UNIVALUE) \
  $(LIB_ebzz_ebzz_WALLET) \
  $(LIB_ebzz_ebzz_ENTERPRISE) \
  $(LIB_ebzz_ebzz__ebzz_ebzz) \
  $(LIB_ebzz_ebzz_UTIL) \
  $(LIB_ebzz_ebzz_CRYPTO) \
  $(LIBLEVELDB) \
  $(LIBMEMENV) \
  $(LIBSECP256K1)

if TARGET_WINDOWS
  _ebzz_ebzzd_LDADD += $(top_builddir)/src/v8_win/build/Release/_ebzz_ebzz-v8.lib
else
  _ebzz_ebzzd_LDADD += $(LIB_ebzz_ebzz_V8)
endif

#if ENABLE_WALLET
#_ebzz_ebzzd_LDADD += lib_ebzz_ebzz_wallet.a
#endif
_ebzz_ebzzd_SOURCES = \
    _ebzz_ebzz/_ebzz_ebzzd.cpp \
    rpc/rpclist.cpp \
    chainparams/buildgenesis.cpp \
    filters/filtercallback.cpp \
    filters/watchdog.cpp \
    json/json_spirit_writer.cpp

if TARGET_WINDOWS
_ebzz_ebzzd_SOURCES += filters/filter_win.cpp _ebzz_ebzzd-res.rc
else
_ebzz_ebzzd_SOURCES += filters/filter.cpp
endif

_ebzz_ebzzd_LDADD += $(BOOST_LIBS) $(BDB_LIBS) $(SSL_LIBS) $(CRYPTO_LIBS) $(MINIUPNPC_LIBS)
_ebzz_ebzzd_CPPFLAGS = $(_ebzz_ebzz_INCLUDES) $(V8_INCLUDE)
_ebzz_ebzzd_LDFLAGS = $(RELDFLAGS) $(AM_LDFLAGS) $(LIBTOOL_APP_LDFLAGS) -pthread
if !TARGET_WINDOWS
_ebzz_ebzzd_LDFLAGS += $(V8_LIBS)
endif

# _ebzz_ebzzd-cold binary #
_ebzz_ebzzd_cold_LDADD = \
  $(LIB_ebzz_ebzz_SERVER) \
  $(LIB_ebzz_ebzz_COMMON) \
  $(LIB_ebzz_ebzz_UNIVALUE) \
  $(LIB_ebzz_ebzz_WALLET) \
  $(LIB_ebzz_ebzz_COMMUNITY) \
  $(LIB_ebzz_ebzz__ebzz_ebzz) \
  $(LIB_ebzz_ebzz_UTIL) \
  $(LIB_ebzz_ebzz_CRYPTO) \
  $(LIBLEVELDB) \
  $(LIBMEMENV) \
  $(LIBSECP256K1)

#if ENABLE_WALLET
#_ebzz_ebzzd_cold_LDADD += lib_ebzz_ebzz_wallet.a
#endif
_ebzz_ebzzd_cold_SOURCES = \
    _ebzz_ebzz/_ebzz_ebzzd-cold.cpp \
    core/init-cold.cpp \
    rpc/rpclist-cold.cpp \
    chainparams/buildgenesis.cpp \
    filters/filter_cold.cpp \
    filters/filtercallback_cold.cpp \
    filters/watchdog.cpp \
    json/json_spirit_writer.cpp
#

if TARGET_WINDOWS
_ebzz_ebzzd_cold_SOURCES += _ebzz_ebzzd-cold-res.rc
endif

_ebzz_ebzzd_cold_LDADD += $(BOOST_LIBS) $(BDB_LIBS) $(SSL_LIBS) $(CRYPTO_LIBS) $(MINIUPNPC_LIBS)
_ebzz_ebzzd_cold_CPPFLAGS = $(_ebzz_ebzz_INCLUDES)
_ebzz_ebzzd_cold_LDFLAGS = $(RELDFLAGS) $(AM_LDFLAGS) $(LIBTOOL_APP_LDFLAGS) -pthread

# _ebzz_ebzz-cli binary #
_ebzz_ebzz_cli_LDADD = \
  $(LIB_ebzz_ebzz_CLI) \
  $(LIB_ebzz_ebzz_UTIL) \
  $(LIB_ebzz_ebzz__ebzz_ebzz) \
  $(LIB_ebzz_ebzz_CRYPTO) \
  $(LIBLEVELDB) \
  $(BOOST_LIBS) \
  $(SSL_LIBS) \
  $(CRYPTO_LIBS)

_ebzz_ebzz_cli_SOURCES =  _ebzz_ebzz/_ebzz_ebzz-cli.cpp

_ebzz_ebzz_cli_CPPFLAGS = $(_ebzz_ebzz_INCLUDES)
#

if TARGET_WINDOWS
_ebzz_ebzz_cli_SOURCES += _ebzz_ebzz-cli-res.rc
endif
_ebzz_ebzz_cli_LDFLAGS = $(RELDFLAGS) $(AM_LDFLAGS) $(LIBTOOL_APP_LDFLAGS)

# _ebzz_ebzz-util binary #
_ebzz_ebzz_util_LDADD = \
  $(LIB_ebzz_ebzz_UNIVALUE) \
  $(LIB_ebzz_ebzz__ebzz_ebzz) \
  $(LIB_ebzz_ebzz_COMMON) \
  $(LIB_ebzz_ebzz_UTIL) \
  $(LIB_ebzz_ebzz_CRYPTO) \
  $(LIBLEVELDB) \
  $(LIBSECP256K1) \
  $(BOOST_LIBS) \
  $(CRYPTO_LIBS)

_ebzz_ebzz_util_SOURCES = _ebzz_ebzz/_ebzz_ebzz-util.cpp chainparams/buildgenesis.cpp

_ebzz_ebzz_util_CPPFLAGS = $(_ebzz_ebzz_INCLUDES)
#
if TARGET_WINDOWS
_ebzz_ebzz_util_SOURCES += _ebzz_ebzz-util-res.rc
endif
_ebzz_ebzz_util_LDFLAGS = $(RELDFLAGS) $(AM_LDFLAGS) $(LIBTOOL_APP_LDFLAGS)


# MCHN END




if BUILD__ebzz_ebzz_LIBS
include_HEADERS = script/_ebzz_ebzzconsensus.h
lib_ebzz_ebzzconsensus_la_SOURCES = \
  primitives/transaction.cpp \
  crypto/hmac_sha512.cpp \
  crypto/sha1.cpp \
  crypto/sha256.cpp \
  crypto/sha512.cpp \
  crypto/ripemd160.cpp \
  utils/utility.cpp \
  utils/systemdependent.cpp \
  utils/tools.cpp \
  utils/utilwrapper.cpp \
  chainparams/buildgenesis.cpp \
  version/version.cpp \
  custom/custom.cpp \
  custom/custom__ebzz_ebzz.cpp \
  chainparams/chainparams.cpp \
  protocol/_ebzz_ebzzscript.cpp \
  utils/dbwrapper.cpp \
  wallet/wallettxdb.cpp \
  wallet/chunkdb.cpp \
  wallet/chunkcollector.cpp \
  permissions/permission.cpp \
  entities/asset.cpp \
  structs/hash.cpp \
  keys/pubkey.cpp \
  script/script.cpp \
  script/interpreter.cpp \
  script/_ebzz_ebzzconsensus.cpp \
  structs/uint256.cpp \
  utils/utilstrencodings.cpp

if GLIBC_BACK_COMPAT
  lib_ebzz_ebzzconsensus_la_SOURCES += compat/glibc_compat.cpp
  lib_ebzz_ebzzconsensus_la_SOURCES += compat/glibcxx_compat.cpp
endif

lib_ebzz_ebzzconsensus_la_LDFLAGS = -no-undefined $(RELDFLAGS)
lib_ebzz_ebzzconsensus_la_LIBADD = $(LIBSECP256K1)
lib_ebzz_ebzzconsensus_la_CPPFLAGS = -I$(builddir)/obj -I$(srcdir)/secp256k1/include -DBUILD__ebzz_ebzz_INTERNAL
endif

CLEANFILES = leveldb/libleveldb.a leveldb/libmemenv.a *.gcda *.gcno

DISTCLEANFILES = obj/build.h

EXTRA_DIST = leveldb

clean-local:
	-$(MAKE) -C leveldb clean
	-$(MAKE) -C secp256k1 clean
	rm -f leveldb/*/*.gcno leveldb/helpers/memenv/*.gcno
	-rm -f config.h

.rc.o:
	@test -f $(WINDRES)
	$(AM_V_GEN) $(WINDRES) -DWINDRES_PREPROC -i $< -o $@

.mm.o:
	$(AM_V_CXX) $(OBJCXX) $(DEFS) $(DEFAULT_INCLUDES) $(INCLUDES) $(AM_CPPFLAGS) \
	  $(CPPFLAGS) $(AM_CXXFLAGS) $(QT_INCLUDES) $(CXXFLAGS)  -c -o $@ $<

%.pb.cc %.pb.h: %.proto
	@test -f $(PROTOC)
	$(AM_V_GEN) $(PROTOC) --cpp_out=$(@D) --proto_path=$(abspath $(<D) $<)

#if ENABLE_TESTS
#include Makefile.test.include
#endif

#if ENABLE_QT
#include Makefile.qt.include
#endif

#if ENABLE_QT_TESTS
#include Makefile.qttest.include
#endif
