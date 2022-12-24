#include "../inc/test.h"

unsigned long long microseconds_now(void)
{
    struct timeval val;

    if (gettimeofday(&val, NULL))
        return (unsigned long long) - 1;

    return val.tv_sec * 1000000ULL + val.tv_usec;
}

void test(int amount, int *numbers, node_tree_t *bs_tree, node_tree_t *avl_tree, hash_table_t **open_adr_table, hash_table_t **chained_table, ptr_hash_func_t func)
{
    srand(time(NULL));

    int ideal_comp, total_comp, cur_comp, aver_comp, rc = 0, i, index, iters = 10000;

    unsigned long long beg_time = 0, end_time = 0, total_time;
    size_t size;

    while (rc != 1)
    {
        printf("\nВведите среднее кол-во сравнений для поиска в таблице: ");

        if (fscanf(stdin, "%d", &ideal_comp) && ideal_comp > 0)
            rc = 1;
    }

    index = rand() % amount;

    printf("* Кол-во итераций: %d\n", iters);
    printf("\n+-------------------------+-----------------------------+----------------+--------------------------+\n");
    printf("|                         | Время поиска %d эл-ов(мкс.) | Объем (байтов) | Среднее кол-во сравнений |\n", amount);
    printf("+-------------------------+-----------------------------+----------------+--------------------------+\n");
    
    total_time = 0;
    total_comp = 0;

    beg_time = microseconds_now();
    for (i = 0; i < iters; i++)
    {
        cur_comp = 0;
        node_tree_find(bs_tree, numbers[index], &cur_comp);

        total_comp += cur_comp;
    }
    end_time = microseconds_now();

    aver_comp = total_comp / iters;
    total_time  = end_time - beg_time;
    size = (sizeof(node_tree_t) - sizeof(int)) * amount;

    printf("| Двоичное дерево поиска  |%29.1llu|%16ld|%26d|\n", total_time, size, aver_comp);
    printf("+-------------------------+-----------------------------+----------------+--------------------------+\n");

    total_time = 0;
    total_comp = 0;

    beg_time = microseconds_now();
    for (i = 0; i < iters; i++)
    {
        cur_comp = 0;
        node_tree_find(avl_tree, numbers[index], &cur_comp);

        total_comp += cur_comp;
    }
    end_time = microseconds_now();

    aver_comp = total_comp / iters;
    total_time  = end_time - beg_time;
    size = (sizeof(node_tree_t)) * amount;

    printf("| Сбалансированное ДДП    |%29.1llu|%16ld|%26d|\n", total_time, size, aver_comp);
    printf("+-------------------------+-----------------------------+----------------+--------------------------+\n");
 
    total_time = 0;
    total_comp = 0;

    beg_time = microseconds_now();
    for (i = 0; i < iters; i++)
    {
        cur_comp = 0;
        open_adr_table_find(*open_adr_table, numbers[index], func, &cur_comp);
        total_comp += cur_comp;
    }
    end_time = microseconds_now();

    aver_comp = total_comp / iters;
    total_time  = end_time - beg_time;
    size = sizeof(cell_t) * (*open_adr_table)->max_size;

    printf("| Внутреннее хеширование  |%29.1llu|%16ld|%26d|\n", total_time, size, aver_comp);
    printf("+-------------------------+-----------------------------+----------------+--------------------------+\n");
    
    if (ideal_comp < aver_comp)
    {
        *open_adr_table = open_adr_table_restruct(*open_adr_table, func);

        printf("\n* После реструктуризации внутреннего хеширования:\n");

        total_time = 0;
        total_comp = 0;

        beg_time = microseconds_now();
        for (i = 0; i < iters; i++)
        {
            cur_comp = 0;
            open_adr_table_find(*open_adr_table, numbers[index], func, &cur_comp);

            total_comp += cur_comp;
        }
        end_time = microseconds_now();

        aver_comp = total_comp / iters;
        total_time  = end_time - beg_time;
        size = sizeof(cell_t) * (*open_adr_table)->max_size;

        printf("+-------------------------+-----------------------------+----------------+--------------------------+\n");
        printf("| Внутреннее хеширование  |%29.1llu|%16ld|%26d|\n", total_time, size, aver_comp);
        printf("+-------------------------+-----------------------------+----------------+--------------------------+\n\n");
    }

    total_time = 0;
    total_comp = 0;

    beg_time = microseconds_now();
    for (i = 0; i < iters; i++)
    {
        cur_comp = 0;
        chained_table_find(*chained_table, numbers[index], func, &cur_comp);
        
        total_comp += cur_comp;
    }
    end_time = microseconds_now();

    if (ideal_comp <= aver_comp)
        printf("+-------------------------+-----------------------------+----------------+--------------------------+\n");
    
    aver_comp = total_comp / iters;
    total_time  = end_time - beg_time;
    size = sizeof(list_cell_t) * (*chained_table)->max_size;

    printf("| Внешнее хеширование     |%29.1llu|%16ld|%26d|\n", total_time, size, aver_comp);
    printf("+-------------------------+-----------------------------+----------------+--------------------------+\n");

    if (ideal_comp < aver_comp)
    {
        *chained_table = chained_table_restruct(*chained_table, func);

        printf("\n* После реструктуризации внешнего хеширования:\n");

        total_time = 0;
        total_comp = 0;

        beg_time = microseconds_now();
        for (i = 0; i < iters; i++)
        {
            cur_comp = 0;
            chained_table_find(*chained_table, numbers[index], func, &cur_comp);

            total_comp += cur_comp;
        }
        end_time = microseconds_now();

        aver_comp = total_comp / iters;
        total_time  = end_time - beg_time;
        size = sizeof(list_cell_t) * (*chained_table)->max_size;
        
        printf("+-------------------------+-----------------------------+----------------+--------------------------+\n");
        printf("| Внешнее хеширование     |%29.1llu|%16ld|%26d|\n", total_time, size, aver_comp);
        printf("+-------------------------+-----------------------------+----------------+--------------------------+\n");
    }
}

