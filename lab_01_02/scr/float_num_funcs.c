#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>

#include "defs.h"
#include "typedefs.h"
#include "essential_funcs.h"
#include "optional_funcs.h"

int valid_input_float(char *buffer, int *count_signs, int *count_e, int *count_point) 
{                                                              // функция для проверки валидности 
    int i, let = 0;                                            // вещественного числа

    for (i = 0; buffer[i] != '\0'; i++)
    {
        if (buffer[i] == PLUS || buffer[i] == MINUS)
            (*count_signs)++;

        else if (buffer[i] == e || buffer[i] == E)
            (*count_e)++;

        else if (buffer[i] == POINT || buffer[i] == COMMA)
            (*count_point)++;

        else if (isdigit(buffer[i]) == 0)
        {
            let++;
            break;
        }
    }

    if (*count_signs > 2 || *count_e > 1 || let != 0 || *count_point > 1)  // если входные данные некорректны,
    {                                                                      // то выводим соответствующее сообщение
        printf("\nInvalid input for float!\n\n");
        return FL_VALUE_ERR;
    }
    
    if (buffer[0] != MINUS && buffer[0] != PLUS && isdigit(buffer[0]) == 0)
    {
        printf("\nInvalid input for float!\n\n");
        return FL_VALUE_ERR;
    }

    return SUCCESS;
}

int make_float(char *buffer, float_num *p_second, int *current_len, int *current_pow, int *index_sign, int *index_point, int *index_e, int *count_point, int *count_zero, int *shift)
{
    int i;
    
    if (isdigit(buffer[0]) != 0 || buffer[0] == PLUS)
        p_second->sign = 1;
    else if (buffer[0] == MINUS)
        p_second->sign = -1;

    *index_sign = (buffer[0] == PLUS || buffer[0] == MINUS) ? 1 : 0;
    i = 0;
    *index_point = 0;
    *count_point = 0;

    while (buffer[i] != '\0')
    {
        if (isdigit(buffer[i]) != 0)
            p_second->numbers[i - *index_sign - *count_point] = buffer[i] - '0';
        else
        {
            if (buffer[i] == E || buffer[i] == e)
                break; 
            
            else if (buffer[i] == POINT || buffer[i] == COMMA)
            {
                (*count_point)++;
                *index_point = i;
            }
            else if (i != 0)
            { 
                printf("\nInvalid input for float!\n\n");
                return FL_VALUE_ERR;
            }
        }
        i++;
    }

    *current_len = i - *index_sign - *count_point;   // длина мантиссы

    if (buffer[i - 1] - '0' == 0 && i - *index_point > 2 && *index_point != 0)
    { 
        printf("\nInvalid input for float!\n\n");
        return FL_VALUE_ERR;
    }
    else if (buffer[i - 1] - '0' == 0 && i - *index_point == 2 && *index_point != 0)
        (*current_len)--;
    else if (*index_point != 0)
        *shift = -(i - *index_point - 1);

    if (*current_len == 0 || *current_len > MAX_MANTISSA)
    {
        printf("\nInvalid length for float!\n\n");
        return FL_LEN_ERR;
    }
    else if (((*index_e - *index_point) == 1 && *index_point != 0) || (*index_point == i - 1 && *index_point != 0))
    {
        { 
            printf("\nInvalid input for float!\n\n");
            return FL_VALUE_ERR;
        }
    }

    if (buffer[i] == E || buffer[i] == e)
    {
        i++;

        if (isdigit(buffer[i]) != 0 || buffer[i] == PLUS)
            p_second->power = 1;
        else if (buffer[i] == MINUS)
            p_second->power = -1;
        else
        {
            printf("\nInvalid input for float!\n\n");
            return FL_VALUE_ERR;
        }

        i += (isdigit(buffer[i]) != 0) ? 0 : 1;
        *count_zero = 0;
        *index_e = i;

        while (buffer[i] != '\0')
        {
            if (isdigit(buffer[i]) == 0)
            {
                printf("\nInvalid input for float!\n\n");
                return FL_VALUE_ERR;
            }
            
            if (buffer[i] - '0' == 0)
            {
                if (isdigit(buffer[i + 1]) != 0)
                {
                    *count_zero = 1;
                    break;
                }
            }
            
            *current_pow = (*current_pow)*BASE + (buffer[i] - '0');
            i++;
        }

        *current_pow *= p_second->power;

        if (*current_pow > MAX_POWER || *current_pow < MIN_POWER || *count_zero == 1)
        {
            printf("\nInvalid power for float!\n\n");
            return FL_POW_ERR;
        }
    }
    else if (buffer[i] != '\0')
    {
        printf("\nInvalid input for float!\n\n");
        return FL_VALUE_ERR;
    }

    *current_pow += *shift;

    return SUCCESS;
}

int write_float(float_num *p_second, int *current_len, int *current_pow, int *index_sign, int *index_point)
{                                                             // функция для записи вещественного числа
    int i = 0, j; 
                                                              // если в начале мантиссы идут нули, чтобы вычленить целую часть числа
    while (p_second->numbers[i] == 0 && i < *current_len)     // считаем кол-во нулей
        i++;

    if (i == *current_len)
    {
        if (i == 1 || (i == 2 && *index_point == 1 + *index_sign))
        {
            p_second->len = 1;
            p_second->power = 0;
            p_second->sign = 1;
            return SUCCESS;
        }
        else
        {
            printf("\nInvalid input for float!\n\n");
            return FL_VALUE_ERR;
        }
    }
    else if (i != 0)                                                  // если такие "0" есть, то
    {
        if (*index_point == *index_sign + 1 ) 
        {                                                             // смещаем числа влево на их кол-во и  
            for (j = i; j < *current_len; j++)                        // уменьшаем степень
                p_second->numbers[j - i] = p_second->numbers[j];
                                                                      // обновляем степень
            *current_len -= i;                                        // обновляем длину мантиссы
        }
        else
        {
            printf("\nInvalid input for float!\n\n");
            return FL_VALUE_ERR;
        }
    }

    i = *current_len - 1;                                             // если в конце мантиссы находятся нули, то
    while (p_second->numbers[i] == 0 && i != 0)                       // уменьшаем длину мантиссы и увеличиваем стпенеь
    {
        (*current_pow)++;                     
        (*current_len)--;
        i--;
    }

    p_second->len = *current_len;
    p_second->power = *current_pow;

    return SUCCESS;
}

int check_num_float(float_num *p_second)
{
    char buffer[BUF_LEN];
    
    int rc, shift = 0; 

    int count_signs = 0, count_e = 0, count_point = 0, count_zero = 0;
    int index_e = 0, index_point = 0, index_sign = 0;
    int current_pow = 0, current_len = 0;

    printf("                    5    10   15   20   25   30\n");
    printf("               |    |    |    |    |    |    |\n");
    printf("Input a float : ");
    fill_buffer(buffer);

    rc = valid_input_float(buffer, &count_signs, &count_e, &count_point);

    if (rc != SUCCESS)
        return rc;

    rc = make_float(buffer, p_second, &current_len, &current_pow, &index_sign, &index_point, &index_e, &count_point, &count_zero, &shift);

    if (rc != SUCCESS)
        return rc;

    rc = write_float(p_second, &current_len, &current_pow, &index_sign, &index_point);

    if (rc != SUCCESS)
        return rc;

    return SUCCESS;
}