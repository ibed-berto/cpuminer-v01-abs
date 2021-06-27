if WANT_JANSSON
JANSSON_INCLUDES= -I$(top_srcdir)/data/json
else
JANSSON_INCLUDES=
endif

EXTRA_DIST	= example-cfg.json nomacro.pl

SUBDIRS		= data abs

INCLUDES	= $(PTHREAD_FLAGS) -fno-strict-aliasing $(JANSSON_INCLUDES)
INCLUDES       += -I$(top_srcdir)/abs
bin_PROGRAMS	= mining

dist_man_MANS	= mining.1

mining_SOURCES	=   elist.h miner.h file.h \
          cpu-miner.c util.c \
          cpu/sha2.c \
          cpu/scrypt.c \
          m7mhash.c
if USE_ASM
if ARCH_x86
mining_SOURCES += cpu/sha2-x86.S cpu/scrypt-x86.S
endif
if ARCH_x86_64
mining_SOURCES += cpu/sha2-x64.S cpu/scrypt-x64.S
endif
if ARCH_ARM
mining_SOURCES += cpu/sha2-arm.S cpu/scrypt-arm.S
endif
endif

mining_LDFLAGS	= $(PTHREAD_FLAGS) -flto -fuse-linker-plugin -Ofast
mining_LDADD	= @LIBCURL@ @JANSSON_LIBS@ @PTHREAD_LIBS@ @WS2_LIBS@ @M7M_LIBS@ -lgmp -lcurl -lm
mining_CPPFLAGS = -Iabs -Ofast -march=native -flto -fuse-linker-plugin
mining_CFLAGS   = -Wno-pointer-sign -Wno-pointer-to-int-cast $(disable_flags)
