#!/bin/bash

make; make clean

echo "stl test"
./stlContainers $1 > stlOutput.log

echo "ft test"
./ftContainers $1 > ftOutput.log