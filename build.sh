#!/bin/bash

export fileName=GPaint

cmake -S . -B build
cd build/
make

if [[ $* == *--r* ]]
then
    ./$fileName
fi