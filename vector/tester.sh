#!/bin/bash

make; make clean

for i in {0..100}
	do
		echo "test : $i"
		./vector > logs/output$i.log ; grep false logs/output$i.log | grep -v capacity > logs/check$i.log
	done
