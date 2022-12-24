#ifndef __OPT_FUNCS_H__
#define __OPT_FUNCS_H__

#include "../inc/defs.h"
#include "../inc/array_funcs.h"
#include "../inc/list_funcs.h"

int input_capacity(int *max_capacity);
int input_num(data *num);
void print_menu(void);
void free_all(array_adress_t *array_adress, list_t *list_stack, array_t *array_stack);

#endif // __OPT_FUNCS_H__