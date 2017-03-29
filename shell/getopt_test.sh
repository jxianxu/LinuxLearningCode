#!/bin/sh
count=1
#getopt -o list the short options supported by command
#getopt -l list the long options supported by command
#: indicates that this option has parameter
#:: indicates that this option can take paramter and also can take no paramt#er
#getopt -n if getopt occuts an error, sipcify the error handle file
args=`getopt -o  abc:d -l along,clong:"$@" -n test.sh`
while [ -n "$1" ]
do
 case $1 in
 a|along)
	echo "parameter a!";;
 b)
	echo "parameter b!";;
 c|--clong|-clong)
	echo "parameter c! $1" ;;
 d)
	echo "paramter d!";;
 \?)
	echo "error parameter!" ;;
 esac
 shift
done
