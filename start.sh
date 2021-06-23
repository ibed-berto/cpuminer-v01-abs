#!/bin/sh

abs=Algo:
read -p "Algo: "  ALGO
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

fi
