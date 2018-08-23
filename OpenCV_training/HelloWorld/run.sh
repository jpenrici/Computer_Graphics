#!/bin/bash

ask () {
echo ""
read -p "Continue (y/n)?" R
if [ "$R" = "" ];then
    $R="Y"
else
    if [ `echo "$R" | tr '[:lower:]' '[:upper:]'` != "Y" ];then
	echo "Stop. Fineshed !!"
	exit 0
fi fi
echo "" 
}

cmake CMakeLists.txt
ask

make
ask

echo "./helloWorld"
./helloWorld