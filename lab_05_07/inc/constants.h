#ifndef __CONSTANTS_H__
#define __CONSTANTS_H__

#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <sys/time.h>
#include <time.h>

// цветной вывод
#define RESET      "\033[0m"
// цветной вывод
#define MAGENTA "\033[0;35m"

// удачное завершение
#define SUCCESS           0

// неверный размер
#define ERR_WRONG_SIZE    1

// ошибки по памяти
#define ERR_MEMORY        2

// неверный элемент
#define ERR_WRONG_ELEM    3

// пустая очередь
#define ERR_EMPTY         4

// заполненная очередь
#define ERR_OVER          5

// неверно выбранный пункт меню
#define ERR_WRONG_CHOICE  6

// нет входного файла
#define ERR_IO            7

// неинициализированная очередь
#define ERR_NO_INIT       8

// кол-во заявок
#define QUEUE          1000

// максимальное кол-во элементов очереди
#define MAX_ELEMS     10000

// максимальное знеачение очереди
#define MAX_ELEM      65536

// разность для вещественных элементов
#define EPS         0.00001

#endif // __CONSTANTS_H__