#ifndef __LIST_FUNCS_H__
#define __LIST_FUNCS_H__

#include "defs.h"
#include "opt_funcs.h"
#include "array_funcs.h"

// создание стека
int list_init(list_t **list_stack, int *max_capacity);

// проверка на полноту
int list_is_full(list_t *list_stack);

// проверка на пустоту
int list_is_empty(list_t *list_stack);

// добавление элемента
int list_push(list_t *list_stack, data *num, array_adress_t *array_adress);

// удаление элемента
data list_pop(list_t *list_stack, array_adress_t *array_adress);

// вывод стека
int list_stack_print(list_t *list_stack, array_adress_t *array_adress);

// освобождение стека
void list_free(list_t *list_stack);
void node_free(node *begin);


#endif // __LIST_FUNCS_H__