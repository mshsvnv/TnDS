#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>
#include "defs.h"
#include "typedefs.h"
#include "optional_funcs.h"

int normalization(float_num *res, int *buffer)        // функция нормализации числа
{
    int i;
    int current_len = res->len, current_pow = res->power + res->len;

    i = MAX_MANTISSA;
    if (buffer[i] > 5 && current_len == MAX_MANTISSA + 1) // если 31 знак мантиссы больше 5,
    {                                                 // то производим циклическое округление
        while (buffer[i] > 5)
        {
            buffer[i] = 0;
            i--;
            buffer[i] += 1;

            current_len--;
        }
    }
    else if (buffer[i] <= 5 && current_len == MAX_MANTISSA + 1) // если 31 цифра меньше 5, то
    {                                                       // отбрасывем её
        current_len--;
        current_pow++;
    }
    else if (current_len > MAX_MANTISSA + 1)
        current_len = MAX_MANTISSA;

    shift(buffer, &current_len);

    i = current_len - 1;
    while (buffer[i] == 0)      
    {;
        current_len--;
        i--;
    }

    if (current_pow > MAX_POWER || current_pow < MIN_POWER)   // если итоговый порядок вне допустимого 
    {                                                         // диапазона, то выводим соответствующее сообщение
        printf("\nStack overflow!\n");
        return RES_POW_ERROR;
    }

    for (i = 0; i < current_len; i++)  // итоговую мантиссу записываем в наш тип данных
        res->numbers[i] = buffer[i];

    res->power = current_pow;          // обновляем длину мантиссы и порядок
    res->len = current_len;

    return SUCCESS;
}

int multiplication(int_num *p_first, float_num *p_second, float_num *res)   // функция перемножения
{
    int buffer[BUF_LEN] = {0};

    int current_len = p_first->len + p_second->len;
    int current_pow = p_second->power+p_first->power;
    int i, j;

    for (i = 0; i < p_first->len; i++)    // алгоритм реализуется аналогично умножению "в столбик"
    {
        for (j = 0; j < p_second->len; j++)
            buffer[i + j] += p_second->numbers[j]*p_first->numbers[i];
    }

    for (i = current_len - 1; i > 0; i--)   // каждый элемент массива - число меньше 9,
    {                                       // поэтому начиная с последнего элемента 
        buffer[i - 1] += buffer[i] / BASE;  // в текущем элементе оставляем остаток от деления на 10,
        buffer[i] = buffer[i] % BASE;       // а в следующий элемент добавляем целую часть от деления
    }

    shift(buffer, &current_len);

    res->sign = p_first->sign*p_second->sign;   // обновляем знак итогового числа
    res->len = current_len - 1;                 // обновляем длину мантиссы итогового числа
    res->power = current_pow;                   // обновляем порядок итогового числа

    return normalization(res, buffer);
    //return SUCCESS;
}
