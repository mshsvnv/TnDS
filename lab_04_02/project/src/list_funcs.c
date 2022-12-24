#include "../inc/list_funcs.h"

int list_init(list_t **list_stack, int *max_capacity)
{
    void *p = malloc(sizeof(list_t));

    if (!p)
    {
        printf("\nMemmory error :(\n");
        return ERR_MEMMORY;
    }

    *list_stack = p;

    (*list_stack)->begin = NULL;
    (*list_stack)->size = 0;
    (*list_stack)->capacity = *max_capacity;

    return SUCCESS;
}

void list_free(list_t *list_stack)
{
    node_free(list_stack->begin);
    free(list_stack);

    list_stack = NULL;
}

void node_free(node *begin)
{
    node *p = begin;

    while (p) 
    {
        node *tmp = p;
        p = p->next;
        free(tmp);
    }
}

int list_is_full(list_t *list_stack)
{
    return (list_stack->size == list_stack->capacity) ? ERR_OVERFLOW : SUCCESS;
}

int list_is_empty(list_t *list_stack)
{
    return (list_stack->size == 0) ? ERR_UNDERFLOW : SUCCESS;
}

int list_push(list_t *list_stack, data *num, array_adress_t *array_adress)
{
    int i, j = -1;

    if (list_is_full(list_stack))
    {
        printf("\nStack is overflowed :(\n");
        return ERR_OVERFLOW;
    }

    node *temp = malloc(sizeof(node));

    if (!temp)
    {
        printf("\nMemmory error :(\n");
        return ERR_MEMMORY;
    }

    temp->value = *num;
    temp->next = list_stack->begin;
    list_stack->begin = temp;
    list_stack->size++;

    if (array_adress)
    {
        for (i = 0; i < array_adress->len + 1; i++)
        {
            if (array_adress->pointer[i] == temp)
            {
                printf("%d\n", array_adress->len);
                for (j = i; j < array_adress->len; j++)
                    array_adress->pointer[j + 1] = array_adress->pointer[j];

                array_adress->len--;
            }

            if (j != -1)
                break;
        }
    }

    return SUCCESS;
}

data list_pop(list_t *list_stack, array_adress_t *array_adress)
{

    if (list_is_empty(list_stack))
    {
        printf("\nStack is empty :(\n");
        return ERR_UNDERFLOW;
    }
    
    node *temp_n = list_stack->begin;
    data temp = temp_n->value;
    list_stack->begin = list_stack->begin->next;
    list_stack->size--;

    if (array_adress != NULL)
        array_adress->pointer[++array_adress->len] = temp_n;

    free(temp_n);

    return temp;
}

int list_stack_print(list_t *list_stack, array_adress_t *array_adress)
{
    void *p_1;

    if (list_is_empty(list_stack))
    {
        printf("\nStack is empty :(\n");
        return ERR_UNDERFLOW;
    }

    printf("%d\n", array_adress->len);

    printf("\n|       STACK        |       ADRESS       |\n");
    printf("|--------------------|--------------------|\n");
    for (node *p = list_stack->begin; p; p = p->next)
    {   
        p_1 = p;

        printf("|%20.6lf|%20p|\n", p->value, p_1);
    }

    return SUCCESS;
}
