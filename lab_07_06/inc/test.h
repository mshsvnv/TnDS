#ifndef _TEST_H_ 
#define _TEST_H_

#include <sys/time.h>
#include <time.h>

#include "tree.h"
#include "stack.h"
#include "hash.h"

unsigned long long microseconds_now(void);

void test(int amount, int *numbers, node_tree_t *bs_tree, node_tree_t *avl_tree, hash_table_t **open_adr_table, hash_table_t **chained_table, ptr_hash_func_t func);

void test_restruct(ptr_hash_func_t func);

#endif // _TEST_H_