#!/bin/sh

cek="mining"

if [ -f "$cek" ];
then
echo "\n$(tput setaf 6)Support algoritma: \n
$(tput setaf 5)1. m7mhash \n
2. sha256d \n
3. scrypt \n$(tput setaf 6) \n\n
$(tput setaf 6)Tekan CTRL+c+ENTER untuk exit\n"

fi

if [ ! -f "$cek" ]
then
echo "\n WARNING !!!\n
Cpu Miner belum terinstall atau lakukan instalasi ulang.$(tput sgr 0)"
exit
fi
echo "$(tput setaf 2)\nCATATAN:MASUKAN SEMUA INPUT DI BAWAH INI TANPA TANOA SPASI\n$(tput setaf 6)"

abs="Masukkan algoritma yang ingin anda gunakan: "

read -p "$abs "  ALGO
if [ "$ALGO" = "m7mhash" ] || [ "$ALGO" = "sha256d" ] || [ "$ALGO" = "scrypt" ];
then

read -p "Stratum: " STRATUM
read -p "User/Wallet: " USER
read -p "Password: " PW
read -p "Jumlah cpu yang ingin anda gunakan: " CPU
clear
echo "\n$(tput setaf 3)\n"

  ./mining -a $ALGO -o $STRATUM -u  $USER -p $PW -t $CPU

elif [ "$ALGO" != "m7mhash" ] || [ "$ALGO" != "sha256d" ] || [ "$ALGO" != "scrypt" ];
then

clear
echo "\nFormat salah.\n
Masukan format nama yang benar.\n Ex $(tput setaf 5)m7mhash\n\n$(tput sgr 0)"

exit

fi

read inp

if [ "$inp" = "^C" ];

then echo "$(tput sgr o) exit  "

fi

 if [ "cur" ]; then echo "$(tput sgr 0) "

fi

echo "$(tput sgr 0) "
