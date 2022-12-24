
#include "../inc/defs.h"
#include "../inc/file_funcs.h"
#include "../inc/specific_funcs.h"
#include "../inc/print_funcs.h"

int del_struct(flat_t *flats, int *count)
{
    char buffer[MAX_STREET + 2];
    int i = 0, j = 0, k = 0, count_old = *count;

    if (*count == 0)
    {
        printf("Not avaliable data!\n");
        return EMPTY_TABLE_ERR;
    }

    fgets(buffer, 3, stdin);
    printf("\nInput street name to delete: ");

    if (fgets(buffer, MAX_STREET + 2, stdin) && strlen(buffer) - 1 < MAX_STREET && (strlen(buffer) - 1) > 0)
    {
        buffer[strlen(buffer) - 1] = '\0';
        while (k < *count)
        {
            if (strcmp(buffer, flats[i].adress.street) == 0)
            {
                for (j = i; j < count_old - 1; j++)
                    flats[j] = flats[j + 1];

                count_old--;
            }
            else
                i++;
            
            k++;
        }
    }
    else
        return INPUT_ERR;

    if (count_old == *count)
    {
        printf("Nothing to find :(\n");
        return NO_DEL_ERR;
    }
    else
    {
        *count = count_old;
        return SUCCESS;
    }
}

int find_struct_by_variable_field(flat_t *flats, int *count)
{
    int i = 0, k = 0;
    char buffer[MAX_STREET];

    if (*count == 0)
    {
        printf("Not avaliable data!\n");
        return EMPTY_TABLE_ERR;
    }

    printf("Input precence of trim(y/n): ");
    fgets(buffer, 3, stdin);
    fgets(buffer, MAX_STREET, stdin);

    if (strcmp(buffer, "y\n") != 0 && strcmp(buffer, "n\n") != 0)
    {
        printf("Wrong value for presence of trim!\n");
        return INPUT_ERR;
    }

    for (; i < *count; i++)
    {
        if (flats[i].kind == 1)
        {
            if (flats[i].housing.primary.trim == buffer[0])
            {
                k++;
                if (k == 1)
                    print_hat();
                print_struct(&k, &flats[i]);
            }
        }
    }
    
    if (k == 0)
    {
        printf("No avaliable fields :(\n");
        return EMPTY_LIST_ERR;
    }
    else
        return SUCCESS;
}

int find_flats(flat_t *flats, int *count)
{
    double from, to, cost;
    int i = 0, k = 0;
    char buffer[MAX_STREET + 2];

    if (*count == 0)
    {
        printf("Not avaliable data!\n");
        return EMPTY_TABLE_ERR;
    }

    fgets(buffer, 3, stdin);
    printf("*Min value:  1\n");
    printf("*Max value:  9 999 999 999 999 999 999\n");
    printf("Costs from: ");
    if (fgets(buffer, MAX_STREET + 2, stdin) && strlen(buffer) - 1 < MAX_STREET && (strlen(buffer) - 1) > 0)
    {
        buffer[strlen(buffer) - 1] = '\0';
        
        if (check_double(buffer, &from) != SUCCESS)
        {
            printf("Incorrect input!\n");
            return INPUT_ERR;
        }
    }
    else
    {
        printf("Incorrect input!\n");
        return INPUT_ERR;
    }

    printf("To: ");
    if (fgets(buffer, MAX_STREET + 2, stdin) && strlen(buffer) - 1 < MAX_STREET && (strlen(buffer) - 1) > 0)
    {
        buffer[strlen(buffer) - 1] = '\0';
        
        if (check_double(buffer, &to) != SUCCESS)
        {
            printf("Incorrect input!\n");
            return INPUT_ERR;
        }
    }
    else
    {
        printf("Incorrect input!\n");
        return INPUT_ERR;
    }

    if (from > to)
    {
        cost = from;
        from = to;
        to = cost;
    }

    for (; i < *count; i++)
    {
        if (flats[i].kind == 2 && flats[i].count_rooms == 2 && flats[i].housing.secondary.pets == 'n')
        {
            cost = flats[i].cost_square_m * flats[i].whole_squares;

            if (cost < to && cost > from)
            {
                if (k == 0)
                    print_hat();
                print_struct(&k, &flats[i]);
                k++;
            }
        }
    }

    if (k == 0)
    {
        printf("Empty list :(\n");
        return EMPTY_LIST_ERR;
    }

    return SUCCESS;
}

int add_struct(flat_t *flats, int *count)
{
    flat_t tmp;
    int rc;

    char buf[3];
    fgets(buf, 3, stdin);

    if (*count == MAX_STRUCTS)
    {
        printf("No avaliable space for new structure :(\n");
        return COUNT_STRUCT_ERR;
    }

    rc = read_struct(&tmp, stdin, 1);

    if (rc)
        return rc;

    flats[*count] = tmp;
    (*count)++;

    return SUCCESS;
}
