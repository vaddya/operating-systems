#!/bin/bash
mkdir fold
SIZE=0
for I in $(seq 0 $1)
do
	echo $I > ./fold/$I
	S=$(ls -l | grep "fold" | cut -f5 -d" ")
	if [ $SIZE -ne $S ]; then
		echo "$I: Folder size: $S"
	fi
	SIZE=$S
done
rm -r fold
