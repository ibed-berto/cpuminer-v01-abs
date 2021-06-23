
start(){
   ./mining -a ${ALGO} -o ${STRATUM} -u ${USERNAME} -p ${PASSWORD} -t ${CPU}.sh
}

read algo
if [ "$algo" = "" ]
then ALGO
 
read stratum
if [ "$stratum" = "" ]
then STRATUM

read username
if [ "$username" = "" ]
then USERNAME

read password
if [ "$password" = "" ]
then PASSWORD

read cpu
if [ "$cpu" = "" ]
then CPU
