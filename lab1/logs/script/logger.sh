#!/bin/bash
touch log
now=`date`
echo -e "\n$now\n" | tee -a log
who=`whoami`
host=`hostname`
while true
do
	dir=`pwd`
	echo -n "$who@$host:$dir$ " | tee -a log
	read command
	result=`$command`
	echo "$command" >> log
	echo "$result" | tee -a log
done
