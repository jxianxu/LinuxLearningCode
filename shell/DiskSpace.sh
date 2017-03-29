#/bin/bash
#
# Big_Users - find big disk users in various directories
# Parameters for Script
#
CHECK_DIRECTORIES="/var/log /home"
#
######################Main Script########################
#
DATE=$(date '+%m%d%y')    #Date for report file
#
exec > disk_space_$DATE.rpt  #Make report file Std Output
echo "Top Ten Disk Space Usage"
echo "for $CHECK_DIRECTORIES Directories"
#
for DIR_CHECK in $CHECK_DIRECTORIES   #loop to du directories
do
	echo ""
	echo "The $DIR_CHECK Directory:"
#
# Create a listing of top ten disk space users
	du -S $DIR_CHECK 2>/dev/null |
	sort -rn |
	sed '{11,$D;=}' |
	sed 'N; s/\n/ /' |
	gawk '{printf $1 ":" "\t" $2 "\t" $3 "\n"}'
#
done
