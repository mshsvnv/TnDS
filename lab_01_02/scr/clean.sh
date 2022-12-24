#!/bin/bash

# переменные для цветного вывода в консоль
end="\033[0m"
red="\033[1;31m"
bold_white="\033[1m"

# f - флаг для учета удаляемых файлов 
f=0
seq=$(ls)
for file in $seq; do
	if [ -f "$file" ]; then
		# удаляем файлы с недопустиыми расширениями
		if [[ $file != *.sh && $file != *.c && $file != *.h ]]; then
			rm "$file"
			f=$((f+1))
		fi
	fi
done

# если не нашлись файлы для удаления, выводим соответсвующее сообщение
if [ "$f" != 0 ]; then
	echo -e "$bold_white""DELETED $f FILES""$end"
	exit 0
else
	echo -e "$red""NO FILES TO BE DELETED""$end"
	exit 1
fi