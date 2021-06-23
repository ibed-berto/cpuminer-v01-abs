#!/bin/sh


read -p 1;
 if [ $1 = "m7mhash" ] 
 then ALGO

read -p "Url server stratum: " STRATUM

read -p "Username or Wallet: " USERNAME

read -p "password:" PASSWORD

read -p "Jumlah cpu yang ingin anda gunakan: Default 0-8"  CPU

./mining -a $ALGO -o $STRATUM -u $USERNAME -p $PAS
SWORD -t $CPU
