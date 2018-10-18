#!/bin/bash
touch log
now=`eval date`
echo -e "\n$now\n" | tee -a log
who=`eval whoami`
host=`eval hostname`
while true
do
	dir=`eval pwd`
	echo -n "$who@$host:$dir$ " | tee -a log
	read command
	result=`eval $command`
	echo "$command" >> log
	echo "$result" | tee -a log
done
