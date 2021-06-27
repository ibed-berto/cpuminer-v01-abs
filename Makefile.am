if WANT_JANSSON
JANSSON_INCLUDES= -I$(top_srcdir)/data/json
else
JANSSON_INCLUDES=
endif

EXTRA_DIST	= example-cfg.json nomacro.pl

SUBDIRS		= data abs

ALL_INCLUDES	= @PTHREAD_FLAGS@ -fno-strict-aliasing $(JANSSON_INCLUDES) -I.

bin_PROGRAMS	= mining

dist_man_MANS	= mining.1

cpuminer_SOURCES = \
  cpu-miner.c util.c \
  api.c sysinfos.c \
  uint256.cpp \
  
  yescrypt/yescrypt-common.c yescrypt/yescrypt-best.c \
  yescrypt/sha256_Y.c \
  algo/allium.c \
  algo/axiom.c \
  algo/bastion.c \
  algo/blake.c \
  algo/blakecoin.c \
  algo/blake2.c \
  algo/bmw256.c \
  algo/c11.c \
  algo/cryptonight.c \
  algo/cryptolight.c \
  algo/decred.c \
  algo/drop.c \
  algo/fresh.c \
  algo/geek.c \
  algo/groestl.c \
  algo/heavy.c \
  algo/ink.c \
  algo/jha.c \
  algo/lbry.c \
  algo/luffa.c \
  algo/lyra2re.c \
  algo/lyra2rev2.c \
  algo/lyra2v3.c \
  algo/myr-groestl.c \
  algo/keccak.c \
  algo/pentablake.c \
  algo/phi1612.c \
  algo/phi2.c \
  algo/quark.c \
  algo/neoscrypt.c \
  algo/nist5.c \
  algo/pluck.c \
  algo/qubit.c \
  algo/rainforest.c \
  algo/scrypt.c \
  algo/scrypt-jane.c \
  algo/sha2.c \
  algo/sia.c \
  algo/sibcoin.c \
  algo/skein.c \
  algo/skein2.c \
  algo/sonoa.c \
  algo/s3.c \
  algo/bitcore.c \
  algo/timetravel.c \
  algo/tribus.c \
  algo/veltor.c \
  algo/x11evo.c \
  algo/x11.c \
  algo/x12.c \
  algo/x13.c \
  algo/x14.c \
  algo/x15.c \
  algo/x16r.c \
  algo/x16rv2.c \
  algo/x16s.c \
  algo/x20r.c \
  algo/x17.c \
  algo/xevan.c \
  algo/yescrypt.c \
  algo/zr5.c

disable_flags =

if USE_ASM
   mining_SOURCES += asm/neoscrypt_asm.S
if ARCH_x86
   mining_SOURCES += cpu/sha2-x86.S cpu/scrypt-x86.S cpu/aesb-x86.S
endif
if ARCH_x86_64
   mining_SOURCES += cpu/sha2-x64.S cpu/scrypt-x64.S cpu/aesb-x64.S
endif
if ARCH_ARM
   mining_SOURCES += cpu/sha2-arm.S cpu/scrypt-arm.S
endif
else
   disable_flags += -DNOASM
endif

if HAVE_WINDOWS
   mining_SOURCES += data/winansi.c
endif

mining_LDFLAGS	= @LDFLAGS@
mining_LDADD	= @LIBCURL@ @JANSSON_LIBS@ @PTHREAD_LIBS@ @WS2_LIBS@ @M7M_LIBS@
mining_CPPFLAGS = @LIBCURL_CPPFLAGS@ $(ALL_INCLUDES)
mining_CFLAGS   = -Wno-pointer-sign -Wno-pointer-to-int-cast $(disable_flags)

if HAVE_WINDOWS
mining_CFLAGS += -Wl,--stack,10485760
mining_LDADD += -lcrypt32 -lgdi32 -lgcc -lgcc_eh
endif

if ARCH_ARM
mining_CFLAGS += -D__arm__
endif

if HAVE_WINDOWS
# use to profile an object
# gprof_cflags = -pg -g3
# mining_LDFLAGS += -pg
# mining_CFLAGS += -fno-inline-functions -static

# copy/paste from generated Makefile
common_ccflags = $(DEFS) $(ALL_INCLUDES) $(mining_CPPFLAGS) $(CPPFLAGS) $(mining_CFLAGS) $(CFLAGS)


endif
