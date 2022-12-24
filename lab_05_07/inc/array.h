#ifndef __ARRAY_H__
#define __ARRAY_H__

#include <stdio.h>
#include "structures.h"
#include "constants.h"

// функция инициализации очереди-массив
int arr_queue_create(arr_queue_t **arr_queue, FILE *f_in, int test_size);

// функция запонения очереди-массив
int arr_queue_fill(arr_queue_t *arr_queue, FILE *f_in);

// функция на проверку переполнения очереди-массив
int arr_is_full(arr_queue_t *arr_queue);

// функция на проверку пустоты очереди-массив
int arr_is_empty(arr_queue_t *arr_queue);

// функция для добавления элемента в очередь-массив
void arr_push(arr_queue_t *arr_queue, int *value);

// функция для удаления элемента из очереди-массив
int arr_pop(arr_queue_t *arr_queue);

// функция для освобождения очереди-массив
void arr_clear(arr_queue_t *arr_queue);

// функция для вывода очереди-массив
void arr_print(arr_queue_t *arr_queue);

#endif // __ARRAY_H__