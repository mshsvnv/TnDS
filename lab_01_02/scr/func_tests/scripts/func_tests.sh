#!/bin/bash

# переменные для цветного вывода в консоль
end="\033[0m"
red="\033[1;31m"
green="\033[1;32m"
yel="\033[1;33m"
bold_white="\033[1m"
abstr="\033[1;3;4;37;45m"
abstr_t="\033[1;3;34m"

# если нет исполняемого файла, выводим соответствующее сообщение
if [[ ! ( -e ./app.exe ) ]]; then
	echo -e "$red""CAN NOT RUN FUNC_TEST.SH""$end"
	exit 1
fi

# функция, обрабатывающая позитивные тесты
pos_tests() {

	pos_in=$(ls ./func_tests/data/pos_in_"$i".txt)
	pos_out=$(ls ./func_tests/data/pos_out_"$i".txt)

	./func_tests/scripts/pos_case.sh "$pos_in" "$pos_out" 
	
	exit_code="$?"
	if [[ "$exit_code" -eq 0 ]]; then 
		echo -e "POS TEST pos_${i}_in.txt:$green PASSED""$end"
		pos_pass=$((pos_pass+1))
	else
		echo -e "POS TEST pos_${i}_in.txt:$red FAILED""$end"
	fi
}

# функция, обрабатывающая негативные тесты
neg_tests() {

	neg_in=$(ls ./func_tests/data/neg_in_"$i".txt)
	./func_tests/scripts/neg_case.sh "$neg_in" 
        
    exit_code="$?"
	if [[ "$exit_code" -eq 0 ]]; then 
		echo -e "NEG TEST neg_${i}_in.txt:$green PASSED""$end"
		neg_pass=$((neg_pass+1))
	else
		echo -e "NEG TEST neg_${i}_in.txt:$red FAILED$end"	
	fi
}

echo -e "${abstr}Functional testing${end}\n"

echo -e "${abstr_t}Positive tests${end}\n"

# no_files - код возврата в случае отсутствия тестовых данных
no_files=0
# total - кол-во непройденных тестов
total=0

i="01"
j=1
# pos_pass - кол-во пройденных позитивных тестов
pos_pass=0

while [[ -f ./func_tests/data/pos_in_"$i".txt ]]; do

	pos_tests "$i"

	j=$((j+1))
	if [[ $j -gt 9 ]]; then
		i="$j"
	else
		i="0$j"
	fi

done

if [[ "$j" -eq 1 ]]; then 
	echo -e "${bold_white}No positive tests${end}\n"
	no_files=$((no_files+1))
else
	echo -e "\n${bold_white}Positive tests:$end correct $pos_pass of $((j-1))\n"
fi
	
total=$((j-1-pos_pass))

echo -e "${abstr_t}Negative tests${end}\n"

i="01"
j=1
# neg_pass - кол-во пройденных негативных тестов
neg_pass=0

while [[ -f ./func_tests/data/neg_in_"$i".txt ]]; do

	neg_tests "$i"

	j=$((j+1))
	if [[ $j -gt 9 ]]; then
		i="$j"
	else
		i="0$j"
	fi

done

if [[ $j -eq 1 ]]; then 
	echo -e "${bold_white}No negative tests$end\n"
	no_files=$((no_files+1))
else
	echo -e "\n${bold_white}Negative tests:$end correct $neg_pass of $((j-1))\n"
fi

total=$((total+j-1-neg_pass))
if [[ $no_files -eq 2 ]]; then 
	exit "$no_files"
else
	exit "$total"
fi