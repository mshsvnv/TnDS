#ifndef __DEFS_H__
#define __DEFS_H__

#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <sys/time.h>

typedef double data; // тип данных

typedef struct node
{
    data value;
    struct node *next;
} node;

typedef struct
{
    node *begin;
    int size;
    int capacity;
} list_t;

typedef struct
{
    int top_1;         // номер головы первого стека
    int top_2;         // номер головы второго стека
    int capacity;      // размер стека
    data *pointer;        // указатель на массив 
} array_t;

typedef struct
{
    int len;
    int capacity;             // размер стека
    node **pointer;            // указатель на массив 
} array_adress_t;

#define ITER_1000          1000
#define ITER_10000         10000
#define MAX_AMOUNT         100000
#define MAX_ELEM           1000000

#define SUCCESS 0

#define ERR_WRONG_CAPACITY 1
#define ERR_MEMMORY        2
#define ERR_OVERFLOW       3
#define ERR_UNDERFLOW      4
#define ERR_NO_STACK       5
#define ERR_NO_ADRESS      6
#define ERR_CHOICE         7
#define ERR_WRONG_NUM      8

#endif // __DEFS_H__s