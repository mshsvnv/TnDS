#include "../inc/hash.h"

int hash_func_div(int key, int table_size)
{
    key = key > 0 ? key : key * (-1);
    return key % table_size;
}

int hash_func_mul(int key, int table_size)
{
    key = key > 0 ? key : key * (-1);
    return (int)(table_size * key * RATIO) % table_size;
}

hash_table_t *open_adr_table_create(hash_table_t *table, int size)
{
    table = malloc(sizeof(hash_table_t *));
    cell_t *cur = NULL;
    int i;

    if (table)
    {
        table->max_size = size;
        cur = malloc(sizeof(cell_t) * size);

        for (i = 0; i < size; i++)
            cur[i].empty = 0;

        table->cells = cur;
    }

    return table;
}

hash_table_t *chained_table_create(hash_table_t *table, int size)
{
    table = malloc(sizeof(hash_table_t *));
    list_cell_t **cur = NULL;
    int i;

    if (table)
    {
        table->max_size = size;
        cur = malloc(sizeof(list_cell_t *) * size);

        for (i = 0; i < size; i++)
            cur[i] = NULL;

        table->cells = cur;
    }

    return table;
}

void open_adr_table_free(hash_table_t *table)
{
    if (table)
    {
        cell_t *cur  = table->cells;

        free(cur);
        free(table);
    }
}

void list_free(list_cell_t *head)
{
    list_cell_t *cur = NULL;

    while (head)
    {
        cur = head;
        head = head->next;

        free(cur);
    }
}

void chained_table_free(hash_table_t *table)
{
    int i;

    if (table)
    {
        list_cell_t **cur = table->cells;

        for (i = 0; i < table->max_size; i++)
        {
            if (cur[i] != NULL)
                list_free(cur[i]);
        }

        free(cur);
        free(table);
    }
}

list_cell_t *list_cell_create(int key)
{
    list_cell_t *cell = malloc(sizeof(list_cell_t));

    if (cell)
    {
        cell->key = key;

        cell->next = NULL;
    }

    return cell;
}

hash_table_t *open_adr_table_insert(hash_table_t *table, int key, ptr_hash_func_t func)
{
    cell_t *cells = table->cells;

    int hash = func(key, table->max_size);

    if (!cells[hash].empty)
    {
        cells[hash].key = key;
        cells[hash].empty = 1;
    }
    else
    {
        if (cells[hash].key != key)
        {
            while (cells[hash % table->max_size].empty)
            {
                if (cells[hash % table->max_size].key == key)
                    return table;
                hash++;
            }

            hash = hash % table->max_size;
            cells[hash].key = key;
            cells[hash].empty = 1;
        }
    }

    // printf("%d\n", cells[hash].key);

    return table;
}

list_cell_t *list_cells_insert(list_cell_t *head, list_cell_t *cell)
{
    list_cell_t *cur = head;

    while (cur->next)
    {
        if (cur->key == cell->key)
            return head;
        cur = cur->next;
    }
    
    cur->next = cell;

    return head;
}

hash_table_t *chained_table_insert(hash_table_t *table, int key, ptr_hash_func_t func)
{
    list_cell_t *cell = NULL;
    list_cell_t **list_cells = table->cells;

    int hash = func(key, table->max_size);

    if (list_cells[hash] == NULL)
    {
        cell = list_cell_create(key);

        if (cell)
            list_cells[hash] = cell;
        else
            return NULL;
    }
    else 
    {
        cell = list_cell_create(key);

        if (cell)
            list_cells[hash] = list_cells_insert(list_cells[hash], cell);
        else
            return NULL;                                
    }

    return table;
}

hash_table_t *open_adr_table_restruct(hash_table_t *old, ptr_hash_func_t func)
{
    int new_size = get_next_prime(old->max_size), i;

    hash_table_t *new = NULL;
    cell_t *cells = old->cells;

    new = open_adr_table_create(new, new_size);

    if (new)
    {
        for (i = 0; i < old->max_size; i++)
        {
            if (cells[i].empty)
            {
                //printf("restr %d\n", cells[i].key);
                new = open_adr_table_insert(new, cells[i].key, func);
            }
        }
    }

    open_adr_table_free(old);

    return new;
}

hash_table_t *chained_table_restruct(hash_table_t *old, ptr_hash_func_t func)
{
    int new_size = get_next_prime(old->max_size), i;
    hash_table_t *new = NULL;

    list_cell_t **list_cells = old->cells, *cur = NULL;

    new = chained_table_create(new, new_size);

    if (new)
    {
        for (i = 0; i < old->max_size; i++)
        {
            cur = list_cells[i];

            while (cur)
            {
                new = chained_table_insert(new, cur->key, func);
                cur = cur->next;
            }
        }
    }

    chained_table_free(old);

    return new;
}

int open_adr_table_find(hash_table_t *table, int key, ptr_hash_func_t func, int *compares)
{
    int hash = func(key, table->max_size);
    cell_t *cells = table->cells;
    
    *compares = 1;

    if (cells[hash].empty)
    {
        if (cells[hash].key != key)
        {
            while (cells[hash++ % table->max_size].key != key)
            {
                (*compares)++;

                if (*compares > table->max_size)
                {
                    *compares = -1;
                    break;
                }
            }

            return cells[--hash % table->max_size].key;
        }

        return cells[hash].key;
    }
    else
        *compares = -1;

    return SUCCESS;
}

int chained_table_find(hash_table_t *table, int key, ptr_hash_func_t func, int *compares)
{
    int hash = func(key, table->max_size);
    list_cell_t **list_cells = table->cells, *cur = NULL;
    
    *compares = 1;

    if (list_cells[hash])
    {
        if (list_cells[hash]->key != key)
        {
            cur = list_cells[hash];

            while (cur)
            {
                if (cur->key == key)
                    return key;

                (*compares)++;
                cur = cur->next;

                if (!cur)
                {
                    *compares = -1;
                    return SUCCESS;
                }
            }
        }

        return list_cells[hash]->key;
    }
    else
        *compares = -1;

    return SUCCESS;
}

hash_table_t *open_adr_table_construct(int *values, int amount, ptr_hash_func_t func)
{
    int i;
    int new_amount = get_next_prime(amount);

    hash_table_t *open_adr_table = NULL;
    open_adr_table = open_adr_table_create(open_adr_table, new_amount);

    if (open_adr_table)
    {
        for (i = 0; i < amount; i++)
            open_adr_table = open_adr_table_insert(open_adr_table, values[i], func);
    }

    return open_adr_table;
}

hash_table_t *chained_table_construct(int *values, int amount, ptr_hash_func_t func)
{
    int i;
    int new_amount = get_next_prime(amount);

    hash_table_t *chained_table = NULL;
    chained_table = chained_table_create(chained_table, new_amount);

    if (chained_table)
    {
        for (i = 0; i < amount; i++)
            chained_table = chained_table_insert(chained_table, values[i], func);
    }

    return chained_table;
}