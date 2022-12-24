#include "../inc/defs.h"
#include "../inc/file_funcs.h"
#include "../inc/memory_funcs.h"
#include "../inc/multiplication_funcs.h"
#include "../inc/other_funcs.h"
#include "../inc/testing_funcs.h"

int main(int argc, char **argv)
{
    int choice, rc;
    FILE *f;
    long size;

    ordinary_mtr_t matrix, vector, vector_res;
    sparse_mtr_t spr_matrix, spr_vector, spr_vector_res;

    matrix.pointer = NULL, vector.pointer = NULL, vector_res.pointer = NULL;
    spr_matrix.A = NULL, spr_matrix.IA = NULL, spr_matrix.JA = NULL;
    spr_vector.A = NULL, spr_vector.IA = NULL, spr_vector.JA = NULL;
    spr_vector_res.A = NULL, spr_vector_res.IA = NULL, spr_vector_res.JA = NULL;

    printf("\nThis programm provides STORAGE, MULTIPLICATION of matrix in ordinary and sparse form");
    printf("\nAlso you have the opportunity to compare efficiency of the different storage forms, size, %%fill\n");

    printf("\n1. Manual input\n2. File input\n3. Random input\n4. Check efficiency\n\nOption: ");

    if (scanf("%d", &choice) != 1)
    {
        printf("Wrong choice :(\n");
        return WRONG_CHOICE_ERR;
    }

    if (choice == 4)
    {
        testing();
        return SUCCESS;
    }

    printf("\n");

    if (choice != 2)
        f = stdin;
    else if (choice == 2)
    {       
        f = fopen(argv[1], "r");

        if (!f || argc != 2)
        {
            printf("No input file :(\n");
            return WRONG_FILE_ERR;
        }

        size = check_file_size(f);

        if (size == 0)
        {
            printf("Empty input file :(\n");
            return EMPTY_FILE_ERR;
        }
    }

    printf("\n::::First matrix::::\n");
    if (choice == 3)
    {
        srand(time(NULL));
        rc = fill_matrix(f, &matrix, 0, read_matrix_random);
    }
    else if (choice == 2)
        rc = fill_matrix(f, &matrix, 0, read_matrix_file);
    else
        rc = fill_matrix(f, &matrix, 0, read_matrix_manual);

    if (rc)
        return rc;

    rc = fill_sparse_matrix(&matrix, &spr_matrix);

    if (rc)
    {
        free_matrix(&matrix);
        return rc;
    }

    printf("\n::::Second matrix::::\n");
    if (choice == 3)
        rc = fill_matrix(f, &vector, matrix.rows, read_matrix_random);
    else if (choice == 2)
        rc = fill_matrix(f, &vector, matrix.rows, read_matrix_file);
    else
        rc = fill_matrix(f, &vector, matrix.rows, read_matrix_manual);

    if (rc)
    {
        free_matrix(&matrix), free_sparse_matrix(&spr_matrix);
        return rc;
    }

    if (vector.columns != 1)
    {
        printf("Incorrect dimensions :(\n");
        free_matrix(&vector), free_matrix(&matrix), free_sparse_matrix(&spr_matrix);
        return rc;
    }

    rc = fill_sparse_matrix(&vector, &spr_vector);

    if (rc)
    {
        free_matrix(&vector), free_matrix(&matrix), free_sparse_matrix(&spr_matrix);
        return rc;
    }

    rc = transpose(&vector);

    if (rc)
    {
        free_matrix(&matrix), free_matrix(&vector);
        free_sparse_matrix(&spr_matrix), free_sparse_matrix(&spr_vector);
        return rc;
    }

    rc = fill_sparse_matrix(&vector, &spr_vector);

    if (rc)
    {
        free_matrix(&matrix), free_matrix(&vector);
        free_sparse_matrix(&spr_matrix), free_sparse_matrix(&spr_vector);
        return rc;
    }

    rc = init_res_matrix(&matrix, &vector, &vector_res);

    if (rc)
    {
        free_matrix(&matrix), free_matrix(&vector);
        free_sparse_matrix(&spr_matrix), free_sparse_matrix(&spr_vector);
        return rc;
    }

    rc = multiplication_matrix(&matrix, &vector, &vector_res);

    if (rc)
    {
        free_matrix(&matrix), free_matrix(&vector);
        free_sparse_matrix(&spr_matrix), free_sparse_matrix(&spr_vector);
        return rc;
    }

    rc = init_res_sparse_matrix(&spr_matrix, &spr_vector, &spr_vector_res);

    if (rc)
    {
        free_matrix(&matrix), free_matrix(&vector), free_matrix(&vector_res);
        free_sparse_matrix(&spr_matrix), free_sparse_matrix(&spr_vector);
        return rc;
    }

    rc = multiplication_sparse_matrix(&spr_matrix, &spr_vector, &spr_vector_res);

    if (rc)
    {
        free_matrix(&matrix), free_matrix(&vector), free_matrix(&vector_res);
        free_sparse_matrix(&spr_matrix), free_sparse_matrix(&spr_vector);
        return rc;
    }

    printf("\n-------------------------------First Matrix-------------------------------\n");
    print(&matrix, &spr_matrix);

    printf("\n-------------------------------Second Matrix-------------------------------\n");
    print(&vector, &spr_vector);

    printf("\n-------------------------------Result-------------------------------\n");
    print(&vector_res, &spr_vector_res);

    free_matrix(&matrix), free_matrix(&vector), free_matrix(&vector_res);
    free_sparse_matrix(&spr_matrix), free_sparse_matrix(&spr_vector), free_sparse_matrix(&spr_vector_res);

    if (f != stdin)
        fclose(f);

    return SUCCESS;
}
