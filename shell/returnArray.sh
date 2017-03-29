#!/bin/bash
function arrayfunc
{
	local originalArray
	local newArray
	local elements
	local i
	originalArray=(`echo "$@"`)
	newArray=(`echo "$@"`)
	elements=$[$# - 1]
	for((i=0;i<=$elements;i++))
	{
		newArray[$i]=$[ ${originalArray[$i]}*2 ]
	}
	echo ${newArray[*]}
}
myarray=(1 2 3 4 5)
echo "The original array is : ${myarray[*]}"
arg1=`echo ${myarray[*]}`
result=`arrayfunc $arg1`
echo "The new array is : ${result[*]}"
