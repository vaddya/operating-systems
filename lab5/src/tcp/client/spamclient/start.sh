#!/bin/bash

gcc -o spamclient spamclient.c > /dev/null &> /dev/null
for I in $(seq 0 $1)
do
	exec `./spamclient "127.0.0.1" 8888 "message from client $I"` &
done
