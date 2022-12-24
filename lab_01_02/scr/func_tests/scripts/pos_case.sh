#!/bin/bash

pos_in="$1"
pos_out="$2"

./app.exe < "$pos_in" > pos_res.txt

./func_tests/scripts/comparator.sh pos_res.txt "$pos_out"
exit_code="$?"

exit "$exit_code"