#ifndef __DEFS_H__
#define __DEFS_H__

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/time.h>
#include <time.h>

// return codes
#define SUCCESS          0
#define WRONG_CHOICE_ERR 1
#define WRONG_FILE_ERR   2
#define EMPTY_FILE_ERR   3
#define WRONG_SIZE_ERR   4
#define MEMORY_ERR       5
#define INCORR_DATA_ERR  6


// some important constatnts
#define MAX_MTR_SIZE 2000
#define FILL_20 20
#define ITERS 10
#define MAX_VALUE 65535
#define MIN_VALUE -65536

// structure that contains a normal matrix
typedef struct 
{
    size_t rows;    // amount of rows 
    size_t columns; // amount of columns
    int *pointer;   // a ponter to the array of the matrix's elements
} ordinary_mtr_t;

// structure that contains a sparse maytix
typedef struct 
{
    int *A;     // array of non-zero elements
    int *JA;    // array with columns of non-zero elements 
    int *IA;    // array of the amount of the non-zero

    size_t elems;
    size_t rows;
} sparse_mtr_t;

typedef int (*func_ptr)(FILE *, ordinary_mtr_t *);

#endif // __DEFS_H__

