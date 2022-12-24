#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>
#include <string.h>

#include "defs.h"
#include "typedefs.h"
#include "essential_funcs.h"
#include "optional_funcs.h"

int valid_input_int(char *buffer, int *current_len, int *index_sign)  // функция для проверки валидности
{                                                                     // целого числа
    int i, count_zero = 0;

    for (i = 0; buffer[i] != '\0'; i++)
    {
        if (isdigit(buffer[i]) == 0)
        {  
            if ((i == 0 && buffer[0] != MINUS && buffer[0] != PLUS) || i != 0)
            {
                printf("\nInvalid input for integer!\n\n");
                return INT_VALUE_ERR;
            }
        }
    }

    *index_sign = (buffer[0] == PLUS || buffer[0] == MINUS) ? 1 : 0;
    *current_len = strlen(buffer) - *index_sign;
    i = *index_sign;

    while(buffer[i] - '0' == 0 && i < *current_len)
    {
        count_zero++;
        i++;
    }

    if (*current_len > MAX_INTEGER || *current_len == 0)
    {
        printf("\nInvalid length for integer!\n\n");
        return INT_LEN_ERR;
    }
    else if(count_zero > 0 && *current_len > 1)
    {
        printf("\nInvalid input for integer!\n\n");
        return INT_VALUE_ERR;
    }

    return SUCCESS;
}

void write_int(char *buffer, int_num *p_first, int *current_len)  // функция для записи целого числа
{
    int i;

    for (i = 0; buffer[i] != '\0'; i++)
    {
        if (isdigit(buffer[0]) != 0)
        {
            if (i == 0)
                p_first->sign = 1;
            p_first->numbers[i] = buffer[i] - '0';
        }
        else
        {
            if (i == 0)
                p_first->sign = (buffer[0] == MINUS) ? -1 : 1;

            else
                p_first->numbers[i - 1] = buffer[i] - '0';
        }
    }
    
    i = *current_len - 1;
    p_first->power = 0;

    while (p_first->numbers[i] == 0)
    {
        p_first->power++;
        (*current_len)--;
        i--;
    }

    p_first->len = *current_len;
}

int check_num_int(int_num *p_first)
{
    char buffer[BUF_LEN];
    int rc, current_len = 0, index_sign;
    
    printf("                       5    10   15   20   25   30\n");
    printf("                  |    |    |    |    |    |    |\n");
    printf("Input an integer : ");
    fill_buffer(buffer);

    rc = valid_input_int(buffer, &current_len, &index_sign);

    if (rc != SUCCESS)
        return rc;

    write_int(buffer, p_first, &current_len);
    printf("\n");

    return SUCCESS;
}
