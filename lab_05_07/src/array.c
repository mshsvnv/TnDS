#include "../inc/array.h"

int arr_queue_create(arr_queue_t **arr_queue, FILE *f_in, int test_size)
{
    int size;

    *arr_queue = malloc(sizeof(arr_queue_t));

    if (! *arr_queue)
        return ERR_MEMORY;

    (*arr_queue)->last = 0;
    (*arr_queue)->total_size = 0;
    (*arr_queue)->arr = NULL;

    if (test_size == -1)
    {
        if (f_in == stdin)
            printf("\n*Допустимый значения: [1, %d]\nВведите размер очереди: ", MAX_ELEMS);

        if (fscanf(f_in, "%d", &size) != 1 || size < 1 || size > MAX_ELEMS)
            return ERR_WRONG_SIZE;
    }
    else 
        size = test_size;

    (*arr_queue)->total_size = size;

    (*arr_queue)->arr = malloc(sizeof(int) * size);

    if (!(*arr_queue)->arr)
        return ERR_MEMORY;

    return SUCCESS;
}

int arr_queue_fill(arr_queue_t *arr_queue, FILE *f_in)
{
    int rc, i, elem;

    if (f_in == stdin)
        printf("\n*Допустимый значения: [-%d, %d]\n", MAX_ELEM, MAX_ELEM - 1);
    
    for (i = 0; i < arr_queue->total_size; i++)
    {
        if (f_in == stdin)
            printf("Введите значение элемента: ");

        if ((rc = fscanf(f_in, "%d", &elem) != 1) || elem < -MAX_ELEM || elem > MAX_ELEM - 1)
            return ERR_WRONG_ELEM;

        arr_push(arr_queue, &elem);
    }

    return SUCCESS;
}

int arr_is_full(arr_queue_t *arr_queue)
{
    return (arr_queue->last == arr_queue->total_size) ? ERR_OVER : SUCCESS;
}

int arr_is_empty(arr_queue_t *arr_queue)
{
    return (arr_queue->last == 0) ? ERR_EMPTY : SUCCESS;
}

void arr_push(arr_queue_t *arr_queue, int *value)
{
    arr_queue->arr[arr_queue->last++] = *value;
}

int arr_pop(arr_queue_t *arr_queue)
{
    int i, first;

    first = arr_queue->arr[0];

    for (i = 0; i < arr_queue->last - 1; i++)
        arr_queue->arr[i] = arr_queue->arr[i + 1];

    arr_queue->last--;

    return first;
}

void arr_clear(arr_queue_t *arr_queue)
{
    if (arr_queue)
    {
        free(arr_queue->arr);

        arr_queue->arr = NULL;

        free(arr_queue);

        arr_queue = NULL;
    }
}

void arr_print(arr_queue_t *arr_queue)
{
    int i;

    printf("%s", MAGENTA);
    printf("\n+--------+----------+\n");
    printf("|        | Значение |\n");
    printf("+--------+----------+\n");

    for (i = 0; i < arr_queue->last; i++)
    {
        if (!i)
            printf("| Верх:  ");
        else if (i == arr_queue->last - 1)
            printf("| Хвост: ");
        else
            printf("|        ");

        printf("|%10d|\n", arr_queue->arr[i]);
        printf("+--------+----------+\n");
    }
    printf("%s\n", RESET);
}
