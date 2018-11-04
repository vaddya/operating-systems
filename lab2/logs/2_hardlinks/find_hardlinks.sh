#!/bin/bash
INODE=$(ls -li $1 | cut -c1-8)
ls -liR $2 | grep "$INODE"
