#!/bin/bash

seq 10000000 | sed "s/.*/abcdef&/g"   > 10mil.txt
seq 40000000 | sed "s/.*/abcdefgh&/g" > 40mil.txt
