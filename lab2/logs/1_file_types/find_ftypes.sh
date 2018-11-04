#!/bin/bash
FTYPES=('-' 'd' 'l' 'c' 'b' 'p' 's')
for FTYPE in ${FTYPES[@]}
do
	ls -lR / | grep -P "^${FTYPE}" | head -1 >> $1
done
