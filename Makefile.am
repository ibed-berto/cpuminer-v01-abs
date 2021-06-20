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
          yescrypy/yescrypt-common.c yescrypy/yescrypt-best.c \
          yescrypy/sha256_Y.c



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

endif

minerd_LDFLAGS	= $(PTHREAD_FLAGS)
minerd_LDADD	= @LIBCURL@ @JANSSON_LIBS@ @PTHREAD_LIBS@ @WS2_LIBS@ @ABS_LIBS@
minerd_CFLAGS	= -fno-strict-aliasing
minerd_CPPFLAGS	= @LIBCURL_CPPFLAGS@ $(JANSSON_INCLUDES) $(PTHREAD_FLAGS)
