#ifndef _DOT_H_ 
#define _DOT_H_

#include "structures.h"
#include "constants.h"
#include "tree.h"

void tree_export_to_dot(node_tree_t *tree, FILE *f, char *name);

void node_to_dot(node_tree_t *tree, void *arg_1, void *arg_2);

void open_adr_table_export_to_dot(hash_table_t *table, FILE *f, char *name);

void chained_table_export_to_dot(hash_table_t *table, FILE *f, char *name);


#endif // _DOT_H_