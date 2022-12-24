#include "../inc/defs.h"
#include "../inc/memory_funcs.h"
#include "../inc/multiplication_funcs.h"
#include "../inc/other_funcs.h"
#include "../inc/file_funcs.h"

unsigned long long milliseconds_now(void)
{
    struct timeval val;

    if (gettimeofday(&val, NULL))
        return (unsigned long long) - 1;

    return val.tv_sec * 1000000ULL + val.tv_usec;
}

void testing(void)
{
    size_t fill[] = {5, 10, 15, 25, 30, 35, 45, 50, 55};
    size_t size[] = {10, 50, 100, 500};
    size_t i, j, k;

    int rc, volume, volume_spr;

    ordinary_mtr_t matrix, vector, vector_res;
    sparse_mtr_t spr_matrix, spr_vector, spr_vector_res;

    long long unsigned beg, end, total, total_spr;

    srand(time(NULL));

    printf("\n*Measurements of time in microseconds\nMeasurements of memory in bytes\n\n");
    printf("\n---------------------------------------------------------------------------------------------------\n");
    printf("|     FILL%%      |     SIZE     |        ORDINARY MATRIX        |           SPARES MATRIX         |\n");
    printf("|                |              |     TIME    |      MEMORY     |      TIME     |     MEMORY      |\n");
    for (j = 0; j < 9; j++)
    {
        printf("---------------------------------------------------------------------------------------------------\n");
        for (i = 0; i < 4; i++)
        {
            total = 0, total_spr = 0;
        
            for (k = 0; k < ITERS; k++)
            {
                matrix.rows = size[i], matrix.columns = size[i];
                rc = allocation_matrix(&matrix);

                if (rc)
                    break;

                generate_matrix(&matrix, fill[j]);

                rc = fill_sparse_matrix(&matrix, &spr_matrix);
                if (rc)
                    break;

                vector.rows = size[i], vector.columns = 1;
                rc = allocation_matrix(&vector);

                if (rc)
                {
                    free_matrix(&matrix);
                    break;
                }

                generate_matrix(&vector, fill[j]);

                rc = transpose(&vector);
                if (rc)
                {
                    free_matrix(&matrix), free_matrix(&vector);
                    free_sparse_matrix(&spr_matrix);
                    break;
                }

                rc = fill_sparse_matrix(&vector, &spr_vector);

                if (rc)
                {
                    free_matrix(&matrix), free_matrix(&vector);
                    free_sparse_matrix(&spr_matrix);
                    break;
                }

                rc = init_res_matrix(&matrix, &vector, &vector_res);

                if (rc)
                {
                    free_matrix(&matrix), free_matrix(&vector);
                    free_sparse_matrix(&spr_matrix), free_sparse_matrix(&spr_vector);
                break;
                }

                beg = milliseconds_now();
                rc = multiplication_matrix(&matrix, &vector, &vector_res);
                end = milliseconds_now();

                total += end - beg;

                if (rc)
                {
                    free_matrix(&matrix), free_matrix(&vector);
                    free_sparse_matrix(&spr_matrix), free_sparse_matrix(&spr_vector);
                break;
                }

                rc = init_res_sparse_matrix(&spr_matrix, &spr_vector, &spr_vector_res);

                if (rc)
                {
                    free_matrix(&matrix), free_matrix(&vector), free_matrix(&vector_res);
                    free_sparse_matrix(&spr_matrix), free_sparse_matrix(&spr_vector);
                break;
                }

                beg = milliseconds_now();
                rc = multiplication_sparse_matrix(&spr_matrix, &spr_vector, &spr_vector_res);
                end = milliseconds_now();

                total_spr += end - beg;

                if (rc)
                {
                    free_matrix(&matrix), free_matrix(&vector), free_matrix(&vector_res);
                    free_sparse_matrix(&spr_matrix), free_sparse_matrix(&spr_vector);
                break;
                }

                free_matrix(&matrix), free_matrix(&vector), free_matrix(&vector_res);
                free_sparse_matrix(&spr_matrix), free_sparse_matrix(&spr_vector), free_sparse_matrix(&spr_vector_res);
            }

            volume = sizeof(int) * (size[i] * size[i] + 2 * size[i]);
            volume_spr = sizeof(int) * (2 * spr_matrix.elems + spr_matrix.rows + 2 * spr_vector.elems + spr_vector.rows + 2 * spr_vector_res.elems + spr_vector_res.rows);
            
            total /= ITERS;
            total_spr /= ITERS;

            if (i == 2)
                printf("|    %5ld       |    %5ld     |    %5llu    |     %7d     |     %6llu    |     %7d     |\n", fill[j], size[i], total, volume, total_spr, volume_spr);
            else
                printf("|                |    %5ld     |    %5llu    |     %7d     |     %6llu    |     %7d     |\n", size[i], total, volume, total_spr, volume_spr);
            

        }
    }
    printf("---------------------------------------------------------------------------------------------------\n");
    printf("\n");
}