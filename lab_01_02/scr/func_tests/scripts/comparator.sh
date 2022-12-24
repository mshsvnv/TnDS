#!/bin/bash

if [[ -f "$1" && -f "$2" ]]; then

	seq_1=$(cat "$1")
	seq_2=$(cat "$2")

	if [[ "$seq_1" == "$seq_2" ]]; then
		exit 0
	else
		exit 1
	fi
else
	exit 1
fi
