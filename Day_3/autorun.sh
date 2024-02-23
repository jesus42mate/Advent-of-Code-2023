#!/bin/bash

clang -o YEAH.out "./src/gear_ratios_alternative.c"

if [ $? -eq -1 ]; then
	echo "Failed to compile the program"
fi

if [ $? -eq 0 ]; then
	./YEAH.out
else
	echo "Failed to run the program."
fi




