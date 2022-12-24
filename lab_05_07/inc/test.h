#ifndef __TEST_H__ 
#define __TEST_H__ 

#include "constants.h"
#include "structures.h"
#include "array.h"
#include "list.h"
#include "others.h"

// функция для отсчета времени
unsigned long long milliseconds_now(void);

// функция для получения рандомного числа
double rand_time(times_t *t);

// функция для анализа эффективности
void test_time_memory(void);

// функция для изменеия времени
int change_time(times_t *t_1, times_t *t_2);

// функция для моделирования для очереди-список
void list_modeling(times_t *t_1, times_t *t_2);

// функция для моделирования для очереди-массив
void arr_modeling(times_t *t_1, times_t *t_2);

#endif // __TEST_H__ 