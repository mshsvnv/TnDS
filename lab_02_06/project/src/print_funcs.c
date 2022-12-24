#include "../inc/defs.h"

void print_hat(void)
{
    printf("\n//-------/--------------------------------------/-----------/-------/-----------/-----------/------/------/--------/---------/------//");
    printf("\n// Index /                Adress                /   Square  / Rooms /  $ sq. m  /  Housing  / Trim / Year / Owners / Roomers / Pets //");
    printf("\n//-------/    Street     / House / Floor / Flat /-----------/-------/-----------/-----------/------/------/--------/---------/------//");
}

void print_menu(void)
{
    printf("\n\n//----------------------------------MENU-------------------------------------//");
    printf("\n// 1.  Read input file                                                       //");
    printf("\n// 2.  Output data_table                                                     //");
    printf("\n// 3.  Output keys_table                                                     //");
    printf("\n// 4.  Add new record                                                        //");
    printf("\n// 5.  Delete record by field \"street name\"                                  //");
    printf("\n// 6.  Find record by \"precence of trim\"                                     //");
    printf("\n// 7.  Sort data_table(quick sort)                                           //");
    printf("\n// 8.  Sort keys_table(quick sort)                                           //");
    printf("\n// 9.  Sort data_table(slow sort)                                            //");
    printf("\n// 10. Sort keys_table(slow sort)                                            //");
    printf("\n// 11. Output whole data by keys_table                                       //");
    printf("\n// 12. Output efficiency_table                                               //");
    printf("\n// 13. Output list of secondary 2 rooms flats without pets in the cost range //");
    printf("\n// 14. Write in new file                                                     //");
    printf("\n// 15. Exit                                                                  //");
    printf("\n//---------------------------------------------------------------------------//\n");

    printf("\nInput option: ");
}

void print_struct(int *num, flat_t *tmp)
{
    printf("\n// %3d   ", *num);   
    printf("/ %12s  /  %3d  / %3d  /  %3d  /", tmp->adress.street, tmp->adress.house, tmp->adress.floor, tmp->adress.flat); 
    printf(" %8.1lf  /", tmp->whole_squares);
    printf(" %3d   /", tmp->count_rooms);
    printf(" %8.1lf  /", tmp->cost_square_m);

    if (tmp->kind == 1)
    {
        printf(" %5s   /", "primary");
        printf("  %c   /", tmp->housing.primary.trim);
        printf("  -   /");
        printf("   -    /");
        printf("   -    /");
        printf("   -   //");
    }
    else
    {
        printf(" %5s /", "secondary");
        printf("  -   /");
        printf(" %3d /", tmp->housing.secondary.year_constr);
        printf("  %3d   /", tmp->housing.secondary.count_former_owners);
        printf("   %3d  /", tmp->housing.secondary.count_last_roomers);
        printf("   %c   //", tmp->housing.secondary.pets);
    }
    printf("\n//-------/---------------/-------/------/-------/-----------/-------/-----------/-----------/------/------/--------/--------/-------//");
}

int print_table(flat_t *flats, int *count)
{
    int i = 0;
    if (*count == 0)
    {
        printf("Not avaliable data!\n");
        return EMPTY_TABLE_ERR;
    }
    else
    {
        print_hat();
        for (; i < *count; i++)
            print_struct(&i, &flats[i]);
    }

    return SUCCESS;
}

int print_keys(keys_t *keys, int *count)
{
    int i = 0;

    if (*count == 0)
    {
        printf("Not avaliable data!\n");
        return EMPTY_TABLE_ERR;
    }
    else
    {
        printf("//------/-------/-------//\n");
        printf("//   №  / Index / Rooms //\n");
        for (; i < *count; i++)
        {
            printf("// %3d  / %3d   / %3d   //\n", i + 1, keys[i].index, keys[i].count_rooms);
            printf("//------/-------/-------//\n");
        }
        
    }
    return SUCCESS;
}

int print_table_by_keys(flat_t *flats, keys_t *keys, int *count)
{
    int i = 0, k = 1, ind;
    if (*count == 0)
    {
        printf("Not avaliable data!\n");
        return EMPTY_TABLE_ERR;
    }
    else
    {
        print_hat();
        for (; i < *count; i++)
        {
            ind = keys[i].index;
            print_struct(&k, &flats[ind]);
            k++;
        }
    }

    return SUCCESS;
}