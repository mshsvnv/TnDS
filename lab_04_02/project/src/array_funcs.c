#include "../inc/array_funcs.h"

int array_init(array_t **array_stack, int *max_capacity)
{
    void *p = malloc(sizeof(array_t));

    if (!p)
    {
        printf("\nMemmory error :(\n");
        return ERR_MEMMORY;
    }

    *array_stack = p;

    p = malloc(sizeof(data) * (*max_capacity));

    if (!p)
    {
        printf("\nMemmory error :(\n");
        return ERR_MEMMORY;
    }

    (*array_stack)->pointer = p;
    (*array_stack)->capacity = *max_capacity;

    (*array_stack)->top_1 = -1;
    (*array_stack)->top_2 = *max_capacity;

    return SUCCESS;
}

void array_free(array_t *array_stack)
{
    free(array_stack->pointer);
    free(array_stack);
}

int array_is_full(array_t *array_stack)
{
    return (array_stack->top_1 + 1 == array_stack->top_2) ? ERR_OVERFLOW : SUCCESS; 
}

int array_is_empty(array_t *array_stack, int *type)
{
    if (*type == 1)
        return (array_stack->top_1 < 0) ? ERR_UNDERFLOW : SUCCESS; 
    else
        return (array_stack->top_2 >= (int)(array_stack->capacity)) ? ERR_UNDERFLOW : SUCCESS; 
}

int array_push(array_t *array_stack, data *num, int *type)
{
    if (array_is_full(array_stack))
    {
        printf("\nStack is overflowed :(\n");
        return ERR_OVERFLOW;
    }

    if (*type == 1)
    {
        array_stack->top_1++;
        array_stack->pointer[array_stack->top_1] = *num;
    }
    else
    {
        array_stack->top_2--;
        array_stack->pointer[array_stack->top_2] = *num;
    }

    return SUCCESS;
}

data array_pop(array_t *array_stack, int *type)
{
    if (*type == 1)
        return array_stack->pointer[array_stack->top_1--];
    else
        return array_stack->pointer[array_stack->top_2++];
}

int array_stack_print(array_t *array_stack, int *type)
{
    int i;

    if (array_is_empty(array_stack, type))
    {
        printf("\nStack is empty :(\n");
        return ERR_UNDERFLOW;
    }
    else if (*type == 3)
    {
        int t = 1;
        int n = 2;
        if (array_is_empty(array_stack, &t) || array_is_empty(array_stack, &n))
        {
            printf("\nStack is empty :(\n");
            return ERR_UNDERFLOW;
        } 
    }

    if (*type == 1)
    {
        printf("\n|     FIRST STACK     |\n");
        for (i = array_stack->top_1; i >= 0; i--)
            printf("|%21.6lf|\n", array_stack->pointer[i]);
    }
    else if (*type == 2)
    {
        printf("\n|     SECOND STACK     |\n");
        for (i = array_stack->top_2; i < (int)(array_stack->capacity); i++)
            printf("|%22.6lf|\n", array_stack->pointer[i]);
    }
    else 
    {
        printf("\n|      WHOLE STACK     |\n");
        for (i = 0; i < (int)(array_stack->capacity); i++)
        {
            if (i <= array_stack->top_1 || i >= array_stack->top_2)
                printf("|%22.6lf|\n", array_stack->pointer[i]);
            else 
                printf("|%22s|\n", "-");
        }
    }
    printf("\n");

    return SUCCESS;
}

int array_adress_init(array_adress_t **array_adress, int *max_capacity)
{
    void *p = malloc(sizeof(array_adress));

    if (!p)
    {
        printf("\nMemmory error :(\n");
        return ERR_MEMMORY;
    }

    *array_adress = p;
    
    p = malloc(sizeof(node) * (*max_capacity));

    if (!p)
        return ERR_MEMMORY;

    (*array_adress)->pointer = p;
    (*array_adress)->capacity = (*max_capacity) * (*max_capacity);
    (*array_adress)->len = -1;

    return SUCCESS;
}

int array_adress_print(array_adress_t *array_adress)
{
    int i;
    void *p;

    if (array_adress->len == -1)
    {
        printf("\nNo avaliable adress :(\n");
        return ERR_NO_ADRESS;   
    }

    printf("\nAvaliable adresses:\n");

    for (i = 0; i < array_adress->len + 1; i++)
    {
        p = array_adress->pointer[i];
        printf("|%20p|\n",p);
    }
    
    return SUCCESS;
}

void array_adress_free(array_adress_t *array_adress)
{    
    free(array_adress->pointer);
    free(array_adress);

    array_adress = NULL;
}

int array_stack_fill(array_t *array_stack, int *capacity, int *type)
{
    int i;
    double temp;
    int rc;

    for (i = 0; i < *capacity; i++)
    {
        if ((rc = input_num(&temp)))
            return rc;

        if ((rc = array_push(array_stack, &temp, type)))
            return rc;
    }

    return SUCCESS;
}
