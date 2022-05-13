#!/bin/bash

make; make clean

COLOR_REST="$(tput sgr0)"
COLOR_GREEN="$(tput setaf 82)"
COLOR_RED="$(tput setaf 9)"

for i in $(seq 1 $1);
	do
		./vector > output.log
		if [ $? -eq 0 ]; then
			grep false output.log | grep -v capacity > logs/output$i.log
			if [ -s logs/output$i.log ]; then
			# The file is not-empty.
				printf '%s%-30s%s%s\n' $COLOR_RED "test $i" "failure" $COLOR_REST
			else
				# The file is empty.
				printf '%s%-30s%s%s\n' $COLOR_GREEN "test $i" "success" $COLOR_REST
				rm logs/output$i.log
			fi
		else #fail
			cp output.log logs/output$i.log
			printf '%s%-30s%s%s\n' $COLOR_RED "test $i" "failure" $COLOR_REST
		fi
	done
