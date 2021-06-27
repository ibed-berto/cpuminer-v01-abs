if WANT_JANSSON
JANSSON_INCLUDES= -I$(top_srcdir)/data/json
else
JANSSON_INCLUDES=
endif

EXTRA_DIST	= example-cfg.json nomacro.pl

SUBDIRS		= data abs

INCLUDES	= $(PTHREAD_FLAGS) -fno-strict-aliasing $(JANSSON_INCLUDES)
INCLUDES       += -I$(top_srcdir)/abs
bin_PROGRAMS	= cpuminer

dist_man_MANS	= cpuminer.1

mining_SOURCES	= 
          elist.h miner.h file.h \
          cpu-miner.c util.c \
          cpu/sha2.c \
          cpu/scrypt.c \
          m7mhash.c \
          
         
          
          
          


if USE_ASM
if ARCH_x86
cpuminer_SOURCES += sha2-x86.S scrypt-x86.S
endif
if ARCH_x86_64
cpuminer_SOURCES += sha2-x64.S scrypt-x64.S
endif
if ARCH_ARM
cpuminer_SOURCES += sha2-arm.S scrypt-arm.S
endif
endif

cpuminer_LDFLAGS	= $(PTHREAD_FLAGS) -flto -fuse-linker-plugin -Ofast
cpuminer_LDADD	= @LIBCURL@ @JANSSON_LIBS@ @PTHREAD_LIBS@ @WS2_LIBS@ @M7M_LIBS@ -lgmp -lcurl -lm
cpuminer_CPPFLAGS = -Iabs -Ofast -march=native -flto -fuse-linker-plugin
cpuminer_CFLAGS   = -Wno-pointer-sign -Wno-pointer-to-int-cast $(disable_flags)
