#include "../inc/test_funcs.h"

unsigned long long milliseconds_now(void)
{
    struct timeval val;

    if (gettimeofday(&val, NULL))
        return (unsigned long long) - 1;

    return val.tv_sec * 1000000ULL + val.tv_usec;
}

void make_array(data **array, int *size)
{
    int i;

    *array = malloc(sizeof(data) * (*size));

    for (i = 0; i < *size; i++)
        (*array)[i] = (data)((rand() % 100 - 50) % 3);
}

void test(void)
{
    array_t *array_stack_1 = NULL, *array_stack_2 = NULL;
    list_t *list_stack = NULL;
    data *array, value;

    int rc, i, j, size, type = 1;
    size_t size_array_1, size_array_2, size_list;

    long long unsigned beg_a_1, end_a_1, beg_a_2, end_a_2, beg_l, end_l;

    int size_arr[] = {100, 1000, 5000, 8000, 10000};

    printf("\n");
    for (j = 0; j < 5; j++)
    {
        size = size_arr[j];

        make_array(&array, &size);

        rc = array_init(&array_stack_1, &size);
        size_array_1 = sizeof(array_stack_1) + sizeof(data) * array_stack_1->capacity;

        rc = array_init(&array_stack_2, &size);
        size_array_2 = sizeof(array_stack_2) + sizeof(data) * array_stack_2->capacity;
        
        rc = list_init(&list_stack, &size);
        size_list = sizeof(list_stack) + sizeof(node) * list_stack->capacity;

        printf("-------------------TEST %d SIZE-------------------\n", size);

        printf("|             |   ARRAY_1  |  ARRAY_2  |   LIST    |\n");
        printf("|SIZE(bytes)  | %11lu|%11lu|%11lu|\n", size_array_1, size_array_2, size_list);
        
        // PUSH
        beg_a_1 = milliseconds_now();
        for (i = 0; i < size; i++)
            rc = array_push(array_stack_1, &(array[i]), &type);
        end_a_1 = milliseconds_now();

        type = 2;

        beg_a_2 = milliseconds_now();
        for (i = 0; i < size; i++)
            rc = array_push(array_stack_2, &(array[i]), &type);
        end_a_2 = milliseconds_now();

        beg_l = milliseconds_now();
        for (i = 0; i < size; i++)
            rc = list_push(list_stack, &(array[i]), NULL);
        end_l = milliseconds_now();

        printf("|PUSH(mcs)    | %11llu|%11llu|%11llu|\n", end_a_1 - beg_a_1, end_a_2 - beg_a_2, end_l - beg_l);

        // POP
        beg_a_1 = milliseconds_now();
        for (i = 0; i < size; i++)
            value = array_pop(array_stack_1, &type);
        end_a_1 = milliseconds_now();

        beg_a_2 = milliseconds_now();
        for (i = 0; i < size; i++)
            value = array_pop(array_stack_2, &type);
        end_a_2 = milliseconds_now();

        beg_l = milliseconds_now();
        for (i = 0; i < size; i++)
            value = list_pop(list_stack, NULL);
        end_l = milliseconds_now();

        if (rc != SUCCESS)
            printf("%lf\n", value);

        printf("|POP(mcs)     | %11llu|%11llu|%11llu|\n", end_a_1 - beg_a_1, end_a_2 - beg_a_2, end_l - beg_l);

        free(array);
        array = NULL;   
    }
    printf("----------------------------------------------------\n");
}