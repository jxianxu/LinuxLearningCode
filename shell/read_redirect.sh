#!/bin/sh
# redirection file input
exec 0<testfile.txt
count=1
while read line
do
	echo "Line $count: $line"
	count=$[ $count+1  ]
done
