#include "../inc/defs.h"
#include "../inc/efficiency_funcs.h"
#include "../inc/file_funcs.h"
#include "../inc/flats_funcs.h"
#include "../inc/keys_funcs.h"
#include "../inc/print_funcs.h"
#include "../inc/sort_funcs.h"
#include "../inc/specific_funcs.h"

int main(int argc, char **argv)
{
    keys_t keys[MAX_STRUCTS];
    flat_t flats[MAX_STRUCTS];
    int rc = 0, count = 0, choice = 0;
    char buffer[MAX_STREET];

    if (argc != 3)
    {
        printf("Wrong number of arguments!\n");
        return ARGUMENTS_ERR;
    }

    FILE  *f_in = fopen(argv[1], "r");
    if (!f_in)
    {
        printf("No avaliable input file!\n");
        return WRONG_FILE_ERR;
    }
    
    long size = file_size(f_in);
    if (size == 0)
    {
        printf("Empty input file!\n");
        return EMPTY_FILE_ERR;
    }

    while (1)
    {
        print_menu();
        rc = scanf("%d", &choice);
        
        if (rc != 1 || choice > 15 || choice < 1)
        {
            printf("Wrong choice!\n");
            return CHOICE_ERR;
        }
    
        switch (choice)
        {
        case 1:
        {
            if (count != 0)
            {
                printf("Data has already been read!\n");
                break;
            }

            rc = read_file(flats, &count, f_in);
            fclose(f_in);

            if (rc != 0)
                return rc;
            make_keys(keys, flats, &count);

            printf("\nDone!\n");
            break;
        }
        case 2:
        {
            rc = print_table(flats, &count);

            if (rc != 0)
                return rc;

            printf("\nDone!\n");
            break;
        }
        case 3:
        {
            rc = print_keys(keys, &count);

            if (rc != 0)
                return rc;

            printf("\nDone!\n");
            break;
        }
        case 4:
        {
            rc = add_struct(flats, &count);

            if (rc != 0)
                return rc;

            add_keys(keys, &flats[count - 1].count_rooms, &count);

            printf("\nDone!\n");
            break;
        }
        case 5:
        {
            rc = del_struct(flats, &count);

            if (rc != 0)
                return rc;

            make_keys(keys, flats, &count);

            printf("\nDone!\n");
            break;
        }
        case 6:
        {
            rc = find_struct_by_variable_field(flats, &count);

            if (rc != 0)
                return rc;

            printf("\nDone!\n");
            break;
        }
        case 7:
        {
            rc = sort_table_quicksort(flats, &count);

            if (rc != 0)
                return rc;

            printf("\nDone!\n");
            break;
        }
        case 8:
        {
            rc = sort_keys_quicksort(keys, &count);

            if (rc != 0)
                return rc;

            printf("\nDone!\n");
            break;
        }
        case 9:
        {
            rc = sort_table_slowsort(flats, &count);

            if (rc != 0)
                return rc;

            printf("\nDone!\n");
            break;
        }
        case 10:
        {
            rc = sort_keys_slowsort(keys, &count);

            if (rc != 0)
                return rc;

            printf("\nDone!\n");
            break;
        }
        case 11:
        {
            rc = print_table_by_keys(flats, keys, &count);

            if (rc != 0)
                return rc;

            printf("\nDone!\n");
            break;
        }
        case 12:
        {
            efficiency_table();
            printf("\nDone!\n");
            break;
        }
        case 13:
        {
            rc = find_flats(flats, &count);

            if (rc != 0)
                return rc;

            printf("\nDone!\n");
            break;
        }
        case 14:
        {
            FILE  *f_out = fopen(argv[2], "a");

            long size = file_size(f_out);
            if (size != 0)
            {
                fgets(buffer, 3, stdin);
                printf("Output file is not empty. Do you want to rewrite it?(y/n): ");
                fgets(buffer, MAX_STREET, stdin);
                if (strcmp(buffer, "n\n") == 0)
                    break;
                else if (strcmp(buffer, "y\n") == 0)
                {
                    fclose(f_out);
                    f_out = fopen(argv[2], "w");
                }
                else
                {
                    printf("Wrong input!\n");
                    return INPUT_ERR;
                }
            }

            rc = write_file(flats, &count, f_out);
            fclose(f_out);

            if (rc != 0)
                return rc;

            printf("\nDone!\n");
            break;
        }
        case 15:
        {
            printf("See you next time;)\n");
            exit(0);
        }
        default:
            break;
        } 

    }

    return SUCCESS;
    
}