#!/bin/bash
i="01"
j=1

while [[ "$j" -lt 14 ]]; do

    cat > pos_in_"$i".txt
    touch pos_out_"$i".txt
    touch neg_in_"$i".txt
    touch neg_out_"$i".txt

	j=$((j+1))
	if [[ $j -gt 9 ]]; then
		i="$j"
	else
		i="0$j"
	fi

done
