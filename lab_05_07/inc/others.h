#ifndef __OTHERS_H__
#define __OTHERS_H__

#include "constants.h"
#include "structures.h"
#include "array.h"
#include "list.h"

// функция для вывода меню
void print_menu(void);

// функция для удаления всех очередей
void free_all(arr_queue_t *arr_queue, list_queue_t *list_queue, list_adresses_t *list_adresses);

// функция для определения размера входного файла
long check_file_size(FILE *f);

// функция для ввода числа
int input_elem(int *num);

// функция для сравнения вещественных чисел
int cmp_double(double a, double b);

#endif // __OTHERS_H__