#ifndef __DEFS_H__
#define __DEFS_H__

// константы
#define MAX_MANTISSA   30    // максимальная длина мантиссы
#define MAX_POWER   99999    // максимальная степень порядка
#define MIN_POWER  -99999    // минимальная степень порядка

#define MAX_INTEGER    30    // максимальная длина целого числа

#define BUF_LEN       1000    // длина буфера для считывания
#define PLUS           43    // ASCII код "+"
#define MINUS          45    // ASCII код "-"
#define POINT          44    // ASCII код "."
#define COMMA          46    // ASCII код ","
#define E              69    // ASCII код "E"
#define e             101    // ASCII код "e"
#define BASE           10    // основание СИ

// коды возврата
#define SUCCESS         0    // успешно
#define INT_VALUE_ERR   1    // некорректные данные целого числа
#define INT_LEN_ERR     2    // некорректная длина целого числа(0 или > MAX_NUMBER)
#define FL_VALUE_ERR    3    // некорректные данные действительного числа
#define FL_LEN_ERR      4    // некорректная длина мантиссы числа(0 или > MAX_NUMBER)
#define FL_POW_ERR      5    // некорректное значение порядка
#define RES_POW_ERROR   6    // переполнение порядка в итоговом числе

#endif // __DEFS_H__