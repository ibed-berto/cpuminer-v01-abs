#!/bin/bash

clear
printf "\x1b[38;5;87m \nSedang mengekstrak file.\n\n"

rm -f config.status
./mining.sh 
printf "\x1b[38;5;87m \nSedang menginstall.\n\n"

if [[ "$OSTYPE" == "darwin"* ]]; then
    ./nomacro.pl
    ./configure \
        CFLAGS="-march=native -O2 -Ofast -flto -DUSE_ASM -pg" \
        --with-crypto=/usr/local/opt/openssl \
        --with-curl=/usr/local/opt/curl
    make -j4
    strip mining
    exit 0
fi

# Linux build

# Ubuntu 10.04 (gcc 4.4)
# extracflags="-O3 -march=native -Wall -D_REENTRANT -funroll-loops -fvariable-expansion-in-unroller -fmerge-all-constants -fbranch-target-load-optimize2 -fsched2-use-superblocks -falign-loops=16 -falign-functions=16 -falign-jumps=16 -falign-labels=16"

# Debian 7.7 / Ubuntu 14.04 (gcc 4.7+)
extracflags="$extracflags -Ofast -flto -fuse-linker-plugin -ftree-loop-if-convert-stores"

if [ ! "0" = `cat /proc/cpuinfo | grep -c avx` ]; then
    # march native doesn't always works, ex. some Pentium Gxxx (no avx)
    extracflags="$extracflags -march=native"
fi

./configure --with-crypto --with-curl CFLAGS="-O2 $extracflags -DUSE_ASM -pg"

make -j 4

strip -s mining

clear
printf "\x1b[38;5;87m \nPenginstallan selesai.\n\n
Untuk memulai masukan script sperti di bawah ini:\n \x1b[38;5;214m\n./mining -a m7mhash -o <url stratum pool> -u <user/wallet anda> -p <password anda> -t <jumlah cpu yang ingin anda gunakan (default 1-8)\n\nENTER\n\n\x1b[38;5;87mTekan CTRL+c+ENTER untuk mengakhiri.\n"
printf "\e[0m"
