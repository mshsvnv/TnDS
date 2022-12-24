#!/bin/bash

# $1: файл с входными данными

neg_in="$1"

./app.exe < "$neg_in" > neg_res.txt

exit_code="$?"

if [[ "$exit_code" -ne 0 ]]; then
	exit_code=0
else
	exit_code=1
fi

exit "$exit_code"