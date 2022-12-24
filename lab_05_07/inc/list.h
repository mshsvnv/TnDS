#ifndef __LIST_H__
#define __LIST_H__

#include <stdio.h>
#include "constants.h"
#include "structures.h"

// функция инициализации очереди-список
int list_queue_create(list_queue_t **list_queue, FILE *f_in, int test_size);

// функция запонения очереди-список
int list_queue_fill(list_queue_t **list_queue, FILE *f_in);

// функция для создания элемента список
node_t *node_create(int *elem);

// функция на проверку переполнения очереди-список
int list_is_full(list_queue_t *list_queue);

// функция на проверку пустоты очереди-список
int list_is_empty(list_queue_t *list_queue);

// функция для добавления элемента в очередь-список
void list_push(list_queue_t **list_queue, node_t *new_node);

// функция для удаления элемента из очереди-список
node_t *list_pop(list_queue_t *list_queue);

// функция для освобождения очереди-список
void list_clear(list_queue_t *list_queue);

// функция для вывода очереди-список
void list_print(list_queue_t *list_queue);

// функция для освобождения массива адресов
void list_adresses_clear(list_adresses_t *list_adresses);

// функция для инициализации массива адресов
int list_adresses_init(list_adresses_t **list_adresses);

// функция для увеличения размера массива адресов
void list_adresses_expand(list_adresses_t *list_adresses);

// функция для добавления адреса в массив адресов
void list_adresses_add(list_adresses_t *list_adresses, node_t *tmp);

// функция для удаления адреса из массива адресов
void list_adresses_del(list_adresses_t *list_adresses, node_t *tmp);

// функция для вывода массива адресов
void list_adresses_print(list_adresses_t *list_adresses);

#endif // __LIST_H__