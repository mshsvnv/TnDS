
#include "../inc/defs.h"
#include "../inc/memory_funcs.h"

int init_res_matrix(ordinary_mtr_t *matrix_p_1, ordinary_mtr_t *matrix_p_2,  ordinary_mtr_t *res_p)
{
    int rc;

    if (matrix_p_1->columns != matrix_p_2->columns)
    {
        printf("Wrong dimensions :(\n");
        return WRONG_SIZE_ERR;
    }

    res_p->rows = matrix_p_1->rows, res_p->columns = matrix_p_2->rows,
    rc = allocation_matrix(res_p);

    if (rc)
    {
        printf("Memory error :(\n");
        return MEMORY_ERR;
    }

    return SUCCESS;
}

int init_res_sparse_matrix(sparse_mtr_t *matrix_p_1, sparse_mtr_t *matrix_p_2,  sparse_mtr_t *res_p)
{
    size_t max;
    int rc;

    max = matrix_p_1->elems * matrix_p_2->elems;

    rc = allocation_sparse_matrix(res_p, &max, matrix_p_1->rows);

    if (rc)
    {
        printf("Memory error :(\n");
        return MEMORY_ERR;
    }

    return SUCCESS;
}

int transpose(ordinary_mtr_t *matrix)
{
    size_t i, j, buf;

    int *tmp = malloc(sizeof(int) * matrix->columns * matrix->rows);

    if (!tmp)
        return MEMORY_ERR;

    for (i = 0; i < matrix->rows; i++)
    {
        for (j = 0; j < matrix->columns; j++)
            tmp[j * matrix->rows + i] = matrix->pointer[i * matrix->columns + j];
    }

    buf = matrix->columns;
    matrix->columns = matrix->rows;
    matrix->rows = buf;

    for (i = 0; i < matrix->rows; i++)
    {
        for (j = 0; j < matrix->columns; j++)
            matrix->pointer[i * matrix->columns + j] = tmp[i * matrix->columns + j];
    }

    free(tmp);

    return SUCCESS;
}

void generate_matrix(ordinary_mtr_t *matrix_p, size_t fill)
{
    size_t i, j, choice;

    for (i = 0; i < matrix_p->rows; i++)
    {
        for (j = 0; j < matrix_p->columns; j++)
        {
            choice = (size_t)(rand() % 100);

            if (choice > fill)
                matrix_p->pointer[i * matrix_p->columns + j] = 0;
            else
                matrix_p->pointer[i * matrix_p->columns + j] = rand() % 100 - 50;
        }
    }
}

void print(ordinary_mtr_t *matrix_p, sparse_mtr_t *sparse_matrix)
{
    size_t i, j;

    if (matrix_p->rows <= 20 && matrix_p->columns <= 20)
    {
        printf("\nRows:    %ld", matrix_p->rows);
        printf("\nColumns: %ld\n\n", matrix_p->columns);

        for (i = 0; i < matrix_p->rows; i++)
        {
            for (j = 0; j < matrix_p->columns; j++)
            {
                if (j == matrix_p->columns - 1)
                    printf("%7d|\n",matrix_p->pointer[i * matrix_p->columns + j]);
                
                else
                    printf("%7d| ",matrix_p->pointer[i * matrix_p->columns + j]);
            }
        }
        printf("\n\n");
    }

    printf("A : ");
    for (i = 0; i < sparse_matrix->elems; i++)
        printf("%7d| ", sparse_matrix->A[i]);

    printf("\nJA: ");
    for (i = 0; i < sparse_matrix->elems; i++)
        printf("%7d| ", sparse_matrix->JA[i]);

    printf("\nIA: ");
    for (i = 0; i < sparse_matrix->rows; i++)
        printf("%7d| ", sparse_matrix->IA[i]);

    printf("\n\n");
}