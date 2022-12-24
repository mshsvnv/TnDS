#include "../inc/opt_funcs.h"

int input_capacity(int *max_capacity)
{
    int temp;

    printf("\nINFO:");
    printf("\n     A number from 1 to %u\n", MAX_AMOUNT);
    printf("\nInput max capacity of the stack: ");


    if (fscanf(stdin, "%d", &temp) != 1 || temp <= 0 || temp > MAX_AMOUNT)
    {
        printf("\nWrong capacity :(\n");
        return ERR_WRONG_CAPACITY;
    }
    
    *max_capacity = temp;

    return SUCCESS;
}

int input_num(data *num)
{
    data temp;

    printf("\nINFO:");
    printf("\n     A number from -%u to %u\n", MAX_ELEM, MAX_ELEM);

    printf("\nInput a number to write: ");

    if (fscanf(stdin, "%lf", &temp) != 1 || temp < MAX_ELEM * (-1) || temp > MAX_ELEM)
    {
        printf("\nWrong number :(\n");
        return ERR_WRONG_NUM;
    }
    
    *num = temp;

    return SUCCESS;
}

void free_all(array_adress_t *array_adress, list_t *list_stack, array_t *array_stack)
{
    if (array_stack)
        array_free(array_stack);

    if (list_stack)
        list_free(list_stack);

    if (array_adress)
        array_adress_free(array_adress);
}

void print_menu(void)
{
    printf("\n-------------------------MENU------------------------\n");
    printf("\nARRAY\n");
    printf("    1  - Init stack\n");
    printf("    2  - Add element to stack\n");
    printf("    3  - Remove element from stack\n");
    printf("    4  - Output current stack\n");
    printf("\nLIST\n");
    printf("    5  - Init stack\n");
    printf("    6  - Add element to stack\n");
    printf("    7  - Remove element from stack\n");
    printf("    8  - Output current stack\n");
    printf("    9  - Output current array of freed adresses\n\n");
    printf("    10 - Check up time\n\n");
    printf("0  - EXIT\n\n");
    printf("Input an option (e.g. 1): ");
}