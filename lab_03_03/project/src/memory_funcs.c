
#include "../inc/defs.h"

int allocation_matrix(ordinary_mtr_t *matrix_p)
{
    int *ptr;

    ptr = calloc(matrix_p->columns * matrix_p->rows, sizeof(int));

    if (!ptr)
        return MEMORY_ERR;
    
    matrix_p->pointer = ptr;
    
    return SUCCESS;
}

int allocation_sparse_matrix(sparse_mtr_t *sparse_p, size_t *non_zero, size_t rows)
{
    void *p;

    p = malloc(sizeof(int) * (*non_zero));

    if (!p)
    {
        printf("Memory error :(\n");
        return MEMORY_ERR;
    }

    sparse_p->A = p;

    p = malloc(sizeof(int) * (*non_zero));

    if (!p)
    {
        printf("Memory error :(\n");
        free(sparse_p->A);
        return MEMORY_ERR;
    }

    sparse_p->JA = p;

    p = malloc(sizeof(int) * (rows));

    if (!p)
    {
        printf("Memory error :(\n");
        free(sparse_p->A), free(sparse_p->JA);
        return MEMORY_ERR;
    }

    sparse_p->IA = p;

    sparse_p->elems = *non_zero;
    sparse_p->rows = rows;

    return SUCCESS;
}

void free_matrix(ordinary_mtr_t *matrix_p)
{
    free(matrix_p->pointer);
}

void free_sparse_matrix(sparse_mtr_t *sparse_p)
{
    free(sparse_p->A);
    free(sparse_p->IA);
    free(sparse_p->JA);
}