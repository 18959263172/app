#!/bin/sh
find ../../www -name "*.*" > websfile
./webcomp ../../www ./websfile > webrom.c
