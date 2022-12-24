
#include "../inc/defs.h"
#include "../inc/specific_funcs.h"

long file_size(FILE *f)
{
    fseek(f, 0, SEEK_END);
    long size = ftell(f);
    fseek(f, 0, SEEK_SET);

    return size;
}

int write_file(flat_t *flats, int *count, FILE *f)
{
    int i = 0;

    if (*count == 0)
    {
        printf("Not avaliable data!\n");
        return EMPTY_TABLE_ERR;
    }
    else
    {
        for (; i < *count; i++)
        {
            fprintf(f, "%s\n%d\n%d\n%d\n", flats[i].adress.street, flats[i].adress.house, flats[i].adress.floor, flats[i].adress.flat);
            fprintf(f, "%.1lf\n", flats[i].whole_squares);
            fprintf(f, "%d\n", flats[i].count_rooms);
            fprintf(f, "%.1lf\n", flats[i].cost_square_m);

            if (flats[i].kind == 1)
                fprintf(f, "%s\n%c\n", "primary", flats[i].housing.primary.trim);
            else
            {
                fprintf(f, "%s\n%d\n%d\n", "secondary", flats[i].housing.secondary.year_constr, flats[i].housing.secondary.count_former_owners);
                fprintf(f, "%d\n%c\n",flats[i].housing.secondary.count_last_roomers, flats[i].housing.secondary.pets);
            }
        }
    }

    return SUCCESS;
}

int read_struct(flat_t *tmp, FILE *f, int type)
{
    char buffer[MAX_STREET + 2], ch, ch_tr;
    double buffer_double;
    int buffer_int;

    if (type == 1)
    {
        f = stdin;
        printf("\n*Maximim length: 20\n");
        printf("Input street name: ");
    }
    if (fgets(buffer, MAX_STREET + 2, f) && strlen(buffer) - 1 < MAX_STREET && (strlen(buffer) - 1) > 0)
    {
        buffer[strlen(buffer) - 1] = '\0';
        
        if (check_street(buffer) != SUCCESS)
        {
            printf("Wrong street name!\n");
            return INPUT_ERR;
        }

        strcpy(tmp->adress.street, buffer);
    }
    else
    {
        printf("Wrong street name!\n");
        return INPUT_ERR;
    }

    if (type == 1)
    {
        printf("\n*Integer positive value(1, 99999)\n");
        printf("Input number of house: ");
    }
    if (fgets(buffer, MAX_STREET + 2, f) && strlen(buffer) - 1 < MAX_INT && (strlen(buffer) - 1) > 0)
    {
        buffer[strlen(buffer) - 1] = '\0';
        
        if (check_integer(buffer, &buffer_int) != SUCCESS)
        {
            printf("Wrong house number!\n");
            return INPUT_ERR;
        }
        
        tmp->adress.house = buffer_int;
    }
    else
    {
        printf("Wrong house number!\n");
        return INPUT_ERR;
    }

    if (type == 1)
    {
        printf("\n*Integer positive value(1, 99999)\n");
        printf("Input number of floor: ");
    }
    if (fgets(buffer, MAX_STREET + 2, f) && strlen(buffer) - 1 < MAX_INT && (strlen(buffer) - 1) > 0)
    {
        buffer[strlen(buffer) - 1] = '\0';
        
        if (check_integer(buffer, &buffer_int) != SUCCESS)
        {
            printf("Wrong floor number!\n");
            return INPUT_ERR;
        }
        
        tmp->adress.floor = buffer_int;
    }
    else
    {
        printf("Wrong floor number!\n");
        return INPUT_ERR;
    }

    if (type == 1)
    {
        printf("\n*Integer positive value(1, 99999)\n");
        printf("Input number of flat: ");
    }
    if (fgets(buffer, MAX_STREET + 2, f) && strlen(buffer) - 1 < MAX_INT && (strlen(buffer) - 1) > 0)
    {
        buffer[strlen(buffer) - 1] = '\0';
        
        if (check_integer(buffer, &buffer_int) != SUCCESS)
        {
            printf("Wrong flat number!\n");
            return INPUT_ERR;
        }
        
        tmp->adress.flat = buffer_int;
    }
    else
    {
        printf("Wrong flat number!\n");
        return INPUT_ERR;
    }

    if (type == 1)
    {
        printf("\n*Double positive value(1.0, 99999.9)\n");
        printf("Input square meters: ");
    }
    if (fgets(buffer, MAX_STREET + 2, f) && strlen(buffer) - 1 < MAX_DOUBLE && (strlen(buffer) - 1) > 0)
    {
        buffer[strlen(buffer) - 1] = '\0';
        int rc = check_double(buffer, &buffer_double);
        
        if (rc != SUCCESS)
        {
            printf("Wrong square meters!\n");
            return INPUT_ERR;
        }
        
        tmp->whole_squares = buffer_double;
    }
    else
    {
        printf("Wrong square meters!\n");
        return INPUT_ERR;
    }
    
    if (type == 1)
    {
        printf("\n*Integer positive value(1, 99999)\n");
        printf("Input number of rooms: ");
    }
    if (fgets(buffer, MAX_STREET + 2, f) && strlen(buffer) - 1 < MAX_INT && (strlen(buffer) - 1) > 0)
    {
        buffer[strlen(buffer) - 1] = '\0';
        
        if (check_integer(buffer, &buffer_int) != SUCCESS)
        {
            printf("Wrong rooms number!\n");
            return INPUT_ERR;
        }

        tmp->count_rooms = buffer_int;
    }
    else
    {
        printf("Wrong rooms number!\n");
        return INPUT_ERR;
    }

    if (type == 1)
    {
        printf("\n*Double positive value(1.0, 99999.9)\n");
        printf("Input cost of square meter: ");
    }
    if (fgets(buffer, MAX_STREET + 2, f) && strlen(buffer) - 1 < MAX_DOUBLE && (strlen(buffer) - 1) > 0)
    {
        buffer[strlen(buffer) - 1] = '\0';
        
        if (check_double(buffer, &buffer_double) != SUCCESS)
        {
            printf("Wrong cost of square meters!\n");
            return INPUT_ERR;
        }
        
        tmp->cost_square_m = buffer_double;
    }
    else
    {
        printf("Wrong cost of square meters!\n");
        return INPUT_ERR;
    }
    
    if (type == 1)
    {
        printf("Housing:\n - primary\n - secondary\n");
        printf("Input kind of housing: ");
    }
    if (fgets(buffer, MAX_STREET + 2, f) && strlen(buffer) - 1 < MAX_STREET && (strlen(buffer) - 1) > 0)
    {
        buffer[strlen(buffer) - 1] = '\0';

        if (strcmp(buffer, "primary") == 0)
            tmp->kind = 1;
        else if (strcmp(buffer, "secondary") == 0)
            tmp->kind = 2;
        else
        {
            printf("Wrong kind!\n");
            return INPUT_ERR;
        }
    }
    else
    {
        printf("Wrong kind!\n");
        return INPUT_ERR;
    }

    if (tmp->kind == 1)
    {
        if (type == 1)
            printf("Input precence of trim(y/n): ");
        if (fscanf(f, "%c%c", &ch_tr, &ch) && ch_tr == 'y' && ch == '\n')
            tmp->housing.primary.trim = 'y';
        else if (ch_tr == 'n' && ch == '\n')
            tmp->housing.primary.trim = 'n';
        else
        {
            printf("Wrong value for trim!\n");
            return INPUT_ERR;
        }
    }
    else
    {
        if (type == 1)
        {
            printf("\n*Integer positive value(1, 99999)\n");
            printf("Input year of construction: ");
        }
        if (fgets(buffer, MAX_STREET + 2, f) && strlen(buffer) - 1 < MAX_INT && (strlen(buffer) - 1) > 0)
        {
            buffer[strlen(buffer) - 1] = '\0';
            
            if (check_integer(buffer, &buffer_int) != SUCCESS)
            {
                printf("Wrong value for year!\n");
                return INPUT_ERR;
            }
            
            tmp->housing.secondary.year_constr = buffer_int;
        }
        else
        {
            printf("Wrong value for year!\n");
            return INPUT_ERR;
        }

        if (type == 1)
        {
            printf("\n*Integer positive value(1, 99999)\n");
            printf("Input number of former owners: ");
        }
        if (fgets(buffer, MAX_STREET + 2, f) && strlen(buffer) - 1 < MAX_INT && (strlen(buffer) - 1) > 0)
        {
            buffer[strlen(buffer) - 1] = '\0';
            
            if (check_integer(buffer, &buffer_int) != SUCCESS)
            {
                printf("Wrong number of former owners!\n");
                return INPUT_ERR;
            }
            
            tmp->housing.secondary.count_former_owners = buffer_int;
        }
        else
        {
            printf("Wrong number of former owners!\n");
            return INPUT_ERR;
        }

        if (type == 1)
        {
            printf("\n*Input positive value\n");
            printf("Input number of last roomers: ");
        }
        if (fgets(buffer, MAX_STREET + 2, f) && strlen(buffer) - 1 < MAX_INT && (strlen(buffer) - 1) > 0)
        {
            buffer[strlen(buffer) - 1] = '\0';
            
            if (check_integer(buffer, &buffer_int) != SUCCESS)
            {
                printf("Wrong number of last roomers!\n");
                return INPUT_ERR;
            }
            
            tmp->housing.secondary.count_last_roomers = buffer_int;
        }
        else
        {
            printf("Wrong number of last roomers!\n");
            return INPUT_ERR;
        }

        if (type == 1)
                printf("Input precence of pets(y/n): ");
        if (fscanf(f, "%c%c", &ch_tr, &ch))
        {
            if (ch_tr == 'y' && ch == '\n')
                tmp->housing.secondary.pets = 'y';
            else if (ch_tr == 'n' && ch == '\n')
                tmp->housing.secondary.pets = 'n';
            else
            {
                printf("Wrong value for presence of pets!\n");
                return INPUT_ERR;
            }
        }
        else
        {
            printf("Wrong value for presence of pets!\n");
            return INPUT_ERR;
        }

    }
    return SUCCESS;
}

int read_file(flat_t *flats, int *count, FILE *f)
{
    int rc = 0;
    char ch;
    flat_t tmp;

    *count = 0;

    while (!feof(f) && (ch = fgetc(f)) != EOF)
    {
        fseek(f, -1, SEEK_CUR);
        if (*count > MAX_STRUCTS)
            return STRUCTS_AMOUNT_ERR;
        rc = read_struct(&tmp, f, 0);

        if (rc)
            return rc;

        flats[*count] = tmp;
        (*count)++;
    }

    return SUCCESS;
}