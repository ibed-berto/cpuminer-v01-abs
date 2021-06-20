if WANT_JANSSON
JANSSON_INCLUDES= -I$(top_srcdir)/data/json
else
JANSSON_INCLUDES=
endif

EXTRA_DIST	= example-cfg.json nomacro.pl

SUBDIRS		= data

ALL_INCLUDES	= @PTHREAD_FLAGS@ -fno-strict-aliasing $(JANSSON_INCLUDES) -I.

bin_PROGRAMS	= minerd

dist_man_MANS	= minerd.1

minerd_SOURCES	= \
          cpu-miner.c util.c \
          yescrypt/yescrypt-common.c yescrypt/yescrypt-best.c \
          yescrypt/sha256_Y.c

disable_flags =

if USE_ASM

if ARCH_x86
minerd_SOURCES += cpu/sha2-x86.S cpu/scrypt-x86.S
endif

if ARCH_x86_64
minerd_SOURCES += cpu/sha2-x64.S cpu/scrypt-x64.S
endif

if ARCH_ARM
minerd_SOURCES += cpu/sha2-arm.S cpu/scrypt-arm.S
endif

if ARCH_PPC
minerd_SOURCES += cpu/sha2-ppc.S cpu/scrypt-ppc.S
endif

else

   disable_flags += -DNOASM

endif

minerd_LDFLAGS	= $(PTHREAD_FLAGS)
minerd_LDADD	= @LIBCURL@ @JANSSON_LIBS@ @PTHREAD_LIBS@ @WS2_LIBS@
minerd_CFLAGS	= -Wno-pointer-sign -Wno-pointer-to-int-cast $(disable_flags)
minerd_CPPFLAGS	= @LIBCURL_CPPFLAGS@ $(ALL_INCLUDES)
