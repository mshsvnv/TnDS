#ifndef __ARRAY_FUNCS_H__
#define __ARRAY_FUNCS_H__

#include "defs.h"
#include "opt_funcs.h"
#include "list_funcs.h"

// создание стека
int array_init(array_t **array_stack, int *max_capacity);

// освобождение стека
void array_free(array_t *array_stack);

// проверка на полноту
int array_is_full(array_t *array_stack);

// проверка на пустоту
int array_is_empty(array_t *array_stack, int *type);

// добавление элемента
int array_push(array_t *array_stack, data *num, int *type);

// удаление элемента
data array_pop(array_t *array_stack, int *type);

// ввод элемента в стек
int array_stack_fill(array_t *array_stack, int *capacity, int *type);

// вывод стека
int array_stack_print(array_t *array_stack, int *type);

// создание массива пустых адресов
int array_adress_init(array_adress_t **array_address, int *max_capacity);

// вывода массива пустых адресов
int array_adress_print(array_adress_t *array_adress);

// освобожденеи массива пустых адресов
void array_adress_free(array_adress_t *array_adress);

#endif // __ARRAY_FUNCS_H__