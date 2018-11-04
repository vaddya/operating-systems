#!/bin/bash
mkdir fold
for I in $(seq 0 $1)
do
	echo $I > ./fold/$I
	S=$(du -h ./fold/ | cut -f 1)
	echo "$I: Folder size: $S"
done
rm -rf fold
