#include "../inc/defs.h"

int multiplication_matrix(ordinary_mtr_t *matrix_p_1, ordinary_mtr_t *matrix_p_2,  ordinary_mtr_t *res_p)
{
    size_t i, j, k;
    int sum;

    for (i = 0; i < matrix_p_1->rows; i++)
    {
        for (j = 0; j < matrix_p_2->rows; j++)
        {
            sum = 0;

            for (k = 0; k < matrix_p_1->columns; k++)
                sum += matrix_p_1->pointer[i * matrix_p_1->columns + k] * matrix_p_2->pointer[j * matrix_p_2->columns + k];

            res_p->pointer[i * res_p->columns + j] = sum;
        }
    }

    return SUCCESS;
}

int multiplication_sparse_matrix(sparse_mtr_t *matrix_p_1, sparse_mtr_t *matrix_p_2,  sparse_mtr_t *res_p)
{
    size_t i, j, k, r, t, k_i, k_j, cnt_i, cnt_j;
    int sum;
    char first_non_zero;

    t = 0;

    for (i = 1; i < matrix_p_1->rows; i++)
    {
        first_non_zero = 0;

        if (matrix_p_1->IA[i] - matrix_p_1->IA[i - 1] != 0)
        {
            k_i = matrix_p_1->IA[i - 1];

            for (j = 1; j < matrix_p_2->rows; j++)
            {
                k_j = matrix_p_2->IA[j - 1];

                if (matrix_p_2->IA[j] - matrix_p_2->IA[j - 1] != 0)
                {
                    cnt_i = matrix_p_1->IA[i] - matrix_p_1->IA[i - 1];
                    cnt_j = matrix_p_2->IA[j] - matrix_p_2->IA[j - 1];

                    sum = 0;

                    for (k = 0; k < cnt_j; k++)
                    {
                        for (r = 0; r < cnt_i; r++)
                        {
                            if (matrix_p_1->JA[k_i + r] == matrix_p_2->JA[k_j + k])
                                sum += matrix_p_1->A[k_i + r] * matrix_p_2->A[k_j + k];
                        }
                    }

                    if (sum != 0)
                    {
                        res_p->A[t] = sum;
                        res_p->JA[t] = j - 1; 

                        if (first_non_zero == 0)
                            res_p->IA[i - 1] = t, first_non_zero++;

                        t++;
                    }
                }
            }
            if (first_non_zero == 0)
                res_p->IA[i - 1] = t;
        }
        else
            res_p->IA[i - 1] = t;
    }

    res_p->IA[res_p->rows - 1] = t;
    res_p->elems = t;

    return SUCCESS;
}