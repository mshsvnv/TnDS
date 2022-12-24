#include "../inc/defs.h"

int check_street(char *street)
{
    int i = 0;
    while (street[i] != '\0')
    {
        if (isalpha(street[i]) == 0)
            return INPUT_ERR;
        i++;
    }

    return SUCCESS;
}

int check_integer(char *integer, int *integer_conv)
{
    int i = 0;
    while (integer[i] != '\0')
    {
        if (isdigit(integer[i]) == 0)
            return INPUT_ERR;
        i++;
    }

    *integer_conv = atoi(integer);

    if (*integer_conv == 0)
        return INPUT_ERR;

    return SUCCESS;
}

int check_double(char *double_b, double *double_conv)
{
    int i = 0, k = 0;
    while (double_b[i] != '\0')
    {
        if (isdigit(double_b[i]) == 0)
        {
            if (double_b[i] != '.' || k != 0 || i == 0) 
                return INPUT_ERR;
            else if (double_b[i] == '.' && k == 0 && i != 0)
                k++;
        }
    
        i++;
    }

    *double_conv = atof(double_b);

    if (*double_conv < 1)
        return INPUT_ERR;

    return SUCCESS;
}