#!/bin/sh
while getopts "abc:d" opt
do
	case $opt in
		a)
			echo "parameter a!";;
		b)
			echo "parameter b!";;
		c)
			echo "parameter c: $OPTARG";;
		d)
			echo "parameter d!";;
		*)
			echo "error parameter!"
	esac
done
