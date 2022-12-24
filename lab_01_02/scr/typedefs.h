#ifndef __TYPEDEFS_H__
#define __TYPEDEFS_H__

typedef struct
{
    short int sign;                // знак целого числа
    int len;                       // длина целого числа
    int power;                     // значение порядка целого числа
    int numbers[MAX_INTEGER];      // массив, для хранения целого числа
} int_num; 

typedef struct
{
    short int sign;                 // знак действительного числа
    int len;                        // длина мантиссы
    int power;                      // значение порядка вещественного числа
    int numbers[MAX_MANTISSA];      // массив, для хранения мантиссы
} float_num;

#endif // __TYPEDEFS_H__