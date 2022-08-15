#!/bin/bash

# set file name's environment variable name
export fileName=OPaint

cmake -S . -B build
cd build/
make

if [[ $* == *--r* ]]
then
    ./$fileName
fi