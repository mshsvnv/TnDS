#ifndef __HASH_H__
#define __HASH_H__

#include "structures.h"
#include "constants.h"
#include "funcs.h"

int hash_func_div(int key, int table_size);

int hash_func_mul(int key, int table_size);

hash_table_t *open_adr_table_create(hash_table_t *table, int size);

hash_table_t *chained_table_create(hash_table_t *table, int size);

void open_adr_table_free(hash_table_t *table);

void list_free(list_cell_t *head);

void chained_table_free(hash_table_t *table);

list_cell_t *list_cell_create(int key);

hash_table_t *open_adr_table_insert(hash_table_t *table, int key, ptr_hash_func_t func);

list_cell_t *list_cells_insert(list_cell_t *head, list_cell_t *cell);

hash_table_t *chained_table_insert(hash_table_t *table, int key, ptr_hash_func_t func);

hash_table_t *open_adr_table_restruct(hash_table_t *old, ptr_hash_func_t func);

hash_table_t *chained_table_restruct(hash_table_t *old, ptr_hash_func_t func);

int open_adr_table_find(hash_table_t *table, int key, ptr_hash_func_t func, int *compares);

int chained_table_find(hash_table_t *table, int key, ptr_hash_func_t func, int *compares);

hash_table_t *open_adr_table_construct(int *values, int amount, ptr_hash_func_t func);

hash_table_t *chained_table_construct(int *values, int amount, ptr_hash_func_t func);

#endif // __HASH_H__