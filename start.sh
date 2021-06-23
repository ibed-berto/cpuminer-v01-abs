#!/bin/sh


clear

echo "Support algoritma: \n                                     1. m7mhash \n
2. sha256d \n
3. script \n"

abs="Masukkan algoritma yang ingin anda gunakan: "

read -p "$abs "  ALGO
if [ "$ALGO" = "m7mhash" ] || [ "$ALGO" = "sha256d" ];
then

read -p "Stratum: " STRATUM
read -p "User/Wallet: " USER
read -p "Password: " PW
read -p "Jumlah cpu yang ingin anda gunakan: " CPU

  ./mining -a $ALGO -o $STRATUM -u  $USER -p $PW -t $CPU

elif [ "$ALGO" != "m7mhash" ] || [ "$ALGO" != "sha256d" ];
then
echo go back
exit
