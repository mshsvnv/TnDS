#include "../inc/defs.h"
#include "../inc/memory_funcs.h"
#include "../inc/file_funcs.h"
#include "../inc/other_funcs.h"

int fill_sparse_matrix(ordinary_mtr_t *matrix_p, sparse_mtr_t *sparse_p)
{
    int rc;
    size_t i, j, k, non_zero = 0;
    char first_non_zero;

    for (i = 0; i < matrix_p->rows; i++)
    {
        for (j = 0; j < matrix_p->columns; j++) 
        {
            if (matrix_p->pointer[i * matrix_p->columns + j] != 0)
                non_zero++;
        }
    }

    rc = allocation_sparse_matrix(sparse_p, &non_zero, matrix_p->rows + 1);

    if (rc)
    {
        printf("Memory error :(\n");
        return rc;
    }

    k = 0;
    for (i = 0; i < matrix_p->rows; i++)
    {
        first_non_zero = 0;
        for (j = 0; j < matrix_p->columns; j++) 
        {
            if (matrix_p->pointer[i * matrix_p->columns + j] != 0)
            {
                sparse_p->A[k] = matrix_p->pointer[i * matrix_p->columns + j];
                sparse_p->JA[k] = j;

                if (first_non_zero == 0)
                    sparse_p->IA[i] = k, first_non_zero++;
                
                k++;
            }
        }

        if (first_non_zero == 0)
            sparse_p->IA[i] = k;

    }

    sparse_p->IA[matrix_p->rows] = k;

    return SUCCESS;
}

long check_file_size(FILE *f)
{
    fseek(f, 0, SEEK_END);
    long size = ftell(f);
    fseek(f, 0, SEEK_SET);

    return size;
}

int read_rows_columns(FILE *f, ordinary_mtr_t *matrix_p, size_t row)
{
    size_t tmp[2];
    int rc;

    if (f == stdin)
    {
        printf("\nMIN value: 0, MAX value: %d\n", MAX_MTR_SIZE);
        printf("Input rows and columns: ");
    }

    rc = fscanf(f, "%lu%lu", &tmp[0], &tmp[1]);

    if (row != 0 && row != 1)
        return WRONG_SIZE_ERR;

    if (rc != 2)
        return WRONG_SIZE_ERR;

    if (tmp[0] >  MAX_VALUE || tmp[1] > MAX_VALUE) 
        return WRONG_SIZE_ERR;
    else
        matrix_p->rows = tmp[0], matrix_p->columns = tmp[1];

    return SUCCESS;
}

int read_matrix_manual(FILE *f, ordinary_mtr_t *matrix_p)
{
    int dig, rc = 3;
    size_t row, column;
    char buf[2];

    fgets(buf, 2, stdin);

    printf("\n*ATTENTION: any wrong symbol means the ending of the input!\n\n");

    while (rc == 3)
    {
        printf("Input row / column / value: ");
    
        rc = fscanf(f, "%lu%lu%d", &row, &column, &dig);

        if (rc != 3)
        {
            fgets(buf, 2, stdin);
            return SUCCESS;
        }

        if (row >= matrix_p->rows || column >= matrix_p->columns)
            break;
        else
            matrix_p->pointer[row * matrix_p->columns + column] = dig;                
    }

    fgets(buf, 2, stdin);

    return SUCCESS;
}

int read_matrix_file(FILE *f, ordinary_mtr_t *matrix_p)
{
    int dig;
    size_t i, j;
    char ch;
    int rc;

    while (!feof(f) && (ch = fgetc(f)) != EOF)
    {
        fseek(f, -1, SEEK_CUR);

        for (i = 0; i < matrix_p->rows; i++)
        {
            for (j = 0; j < matrix_p->columns; j++)
            {
                if (fscanf(f, "%d", &dig) == 1)
                {
                    matrix_p->pointer[i * matrix_p->columns + j] = dig;
                }
                else
                    return INCORR_DATA_ERR;
            }
        }
        rc = fscanf(f, "%c", &ch);

        if ((rc == 1 && ch == '\n') || rc == -1)
            return SUCCESS;
        else if (rc == 1 && ch != '\n')
            return INCORR_DATA_ERR;                     
    }

    return SUCCESS;
}

int read_matrix_random(FILE *f, ordinary_mtr_t *matrix_p)
{
    size_t fill;

    printf("\nInput %%fill: ");
    if (fscanf(f, "%lu", &fill) != 1 || fill > 100)
        return MEMORY_ERR;

    if (f)
        generate_matrix(matrix_p, fill);
    else
        return MEMORY_ERR;

    return SUCCESS;
}


int fill_matrix(FILE *f, ordinary_mtr_t *matrix_p, size_t row, int (*func_ptr)(FILE *, ordinary_mtr_t *))
{
    int rc = 0;

    rc = read_rows_columns(f, matrix_p, row);

    if (rc)
    {
        printf("Incorrect dimensions :(\n");
        return rc;
    }

    rc = allocation_matrix(matrix_p);

    if (rc)
    {
        printf("Memory error :(\n");
        return rc;
    }
    
    if (func_ptr == read_matrix_file)
        rc = read_matrix_file(f, matrix_p);
    else if (func_ptr == read_matrix_manual)
        rc = read_matrix_manual(f, matrix_p);
    else
        rc = read_matrix_random(f, matrix_p);

    if (rc)
    {
        printf("Incorrect data :(\n");
        free(matrix_p->pointer);
        return rc;
    }

    return SUCCESS;
}


