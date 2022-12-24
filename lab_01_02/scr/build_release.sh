#!/bin/bash

# переменные для цветного вывода в консоль
end="\033[0m"
red="\033[1;31m"
green="\033[1;32m"

# f - флаг для подсчета исходных файлов
f=0
seq=$(ls)
for file in $seq; do
	if [[ "$file" == *.c ]]; then
		# компиляция программы
		gcc -std=c99 -Wall -Werror -Wpedantic -Wvla -Wextra -Wfloat-equal -Wfloat-conversion -c ./*.c 
		# компановка программы
		gcc -o app.exe ./*.o -lm
		f=$((f+1)) 
		break
	fi
done

# если программа успешно скомпелировалась, то выводим соответствующее сообщение 
if [[ "$f" -ne 0 ]]; then
	echo -e "$green""SUCCESSFULLY COMPILED""$end"
else
	echo -e "$red""NO OBJECT FILE TO BE COMPILED""$end"
fi