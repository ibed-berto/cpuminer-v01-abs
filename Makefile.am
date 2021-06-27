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
          elist.h miner.h file.h \
          cpu-miner.c util.c \
          cpu/sha2.c \
          cpu/scrypt.c \
          m7mhash.c \
          yescrypt/yescrypt.c \
          yescrypt/yescrypt-best.c 

disable_flags =

if USE_ASM
   mining_SOURCES += 
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
