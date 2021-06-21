if WANT_JANSSON
JANSSON_INCLUDES= -I$(top_srcdir)/data/json
else
JANSSON_INCLUDES=
endif

EXTRA_DIST	= example-cfg.json nomacro.pl

SUBDIRS		= data

INCLUDES	= $(PTHREAD_FLAGS) -fno-strict-aliasing $(JANSSON_INCLUDES)
INCLUDES       += -I$(top_srcdir)/abs
bin_PROGRAMS	= minerd

dist_man_MANS	= minerd.1

minerd_SOURCES	= \
          cpu-miner.c util.c \
          yescrypy/yescrypt-common.c yescrypy/yescrypt-best.c \
          yescrypy/sha256_Y.c\
          m7mhash.c


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

minerd_LDFLAGS	= $(PTHREAD_FLAGS) -flto -fuse-linker-plugin -Ofast
minerd_LDADD	= @LIBCURL@ @JANSSON_LIBS@ @PTHREAD_LIBS@ @WS2_LIBS@ @M7M_LIBS@ -lgmp -lcurl -lm
minerd_CPPFLAGS = -Iabs -Ofast -march=native -flto -fuse-linker-plugin
