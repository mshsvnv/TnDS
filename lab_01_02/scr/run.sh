#!/bin/bash

seq=$(ls)
for file in $seq; do
	if [[ "$file" == *.c ]]; then
		# компиляция программы
		gcc -std=c99 -Wall -Werror -Wpedantic -Wvla -Wextra -Wfloat-equal -Wfloat-conversion -c ./*.c 
		# компановка программы
		gcc -o app.exe ./*.o -lm
		break
	fi
done

./app.exe