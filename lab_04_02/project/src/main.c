#include "../inc/defs.h"
#include "../inc/array_funcs.h"
#include "../inc/opt_funcs.h"
#include "../inc/list_funcs.h"
#include "../inc/test_funcs.h"

int main(void)
{
    int choice = 1, rc = SUCCESS, type;

    int max_capacity;
    array_t *array_stack = NULL;
    list_t *list_stack = NULL;
    array_adress_t *array_adress = NULL;
    data num;

    do
    {
        print_menu();

        if (fscanf(stdin, "%d", &choice) != 1 || choice > 10 || choice < 0)
        {
            printf("\nWrong choice :(\n");
            rc = ERR_CHOICE;
            break;
        }

        switch (choice)
        {
            case 0:
            {
                printf("\nSee you next time >^.^<\n");

                // free_all(array_adress, list_stack, array_stack);

                break;
            }

            case 1:
            {
                if (!array_stack)
                {
                    rc = input_capacity(&max_capacity);

                    if (rc)
                    {
                        // free_all(array_adress, list_stack, array_stack);
                        break;
                    }

                    rc = array_init(&array_stack, &max_capacity);

                    if (rc)
                    {
                        // free_all(array_adress, list_stack, array_stack);
                        break;
                    }

                    printf("\nWell done :)\n");

                }
                else
                    printf("\nStack has been already initialized!!\n");

                break;
            };

            case 2:
            {
                if (!array_stack)
                {
                    printf("No avaliable stack :(\n");
                    // free_all(array_adress, list_stack, array_stack);
                    rc = ERR_NO_STACK;

                    break;
                }

                printf("\nIn which stack do you want to add 1/2?: ");

    
                if (fscanf(stdin, "%d", &type) != 1 || (type != 1 && type != 2))
                {
                    printf("Wrong choice :(\n");
                    // free_all(array_adress, list_stack, array_stack);
                    rc =  ERR_CHOICE;

                    break;
                }

                if (array_is_full(array_stack))
                {
                    printf("Stack is overflowed :(\n");
                    // free_all(array_adress, list_stack, array_stack);
                    rc =  ERR_OVERFLOW;

                    break;
                }

                rc = input_num(&num);
                if (rc)
                {
                    // free_all(array_adress, list_stack, array_stack);
                    break;
                }

                rc = array_push(array_stack, &num, &type);

                if (rc)
                {
                    // free_all(array_adress, list_stack, array_stack);
                    break;
                }

                printf("\nWell done :)\n");

                break;
            }

            case 3:
            {
                if (!array_stack)
                {
                    printf("No avaliable stack :(\n");
                    // free_all(array_adress, list_stack, array_stack);
                    rc = ERR_NO_STACK;

                    break;
                }

                printf("\nFrom which stack do you want to remove 1/2?: ");

                if (fscanf(stdin, "%d", &type) != 1 || (type != 1 && type != 2))
                {
                    printf("Wrong choice :(\n");
                    // free_all(array_adress, list_stack, array_stack);
                    rc = ERR_CHOICE;

                    break;
                }

                if (array_is_empty(array_stack, &type))
                {
                    printf("Stack is empty :(\n");
                    // free_all(array_adress, list_stack, array_stack);
                    rc = ERR_UNDERFLOW;

                    break;
                }

                num = array_pop(array_stack, &type);

                printf("\nThis elem %.6lf was removed from %d stack\n", num, type);

                printf("\nWell done :)\n");

                break;
            }

            case 4:
            {
                if (!array_stack)
                {
                    printf("No avaliable stack :(\n");
                    // free_all(array_adress, list_stack, array_stack);
                    rc = ERR_NO_STACK;

                    break;
                }

                printf("\nWhich stack do you want to print 1/2/3(both)?: ");

                if (fscanf(stdin, "%d", &type) != 1 && type != 1 && type != 2 && type != 3)
                {
                    printf("Wrong choice :(\n");
                    // free_all(array_adress, list_stack, array_stack);
                    rc = ERR_CHOICE;

                    break;
                }

                rc = array_stack_print(array_stack, &type);

                if (rc)
                {
                    // free_all(array_adress, list_stack, array_stack);
                    break;
                }

                printf("\nWell done :)\n");
                
                break;
            }

            case 5:
            {
                if (!list_stack)
                {
                    rc = input_capacity(&max_capacity);

                    if (rc)
                    {
                        // free_all(array_adress, list_stack, array_stack);
                        break;
                    }

                    rc = list_init(&list_stack, &max_capacity);

                    if (rc)
                    {
                        // free_all(array_adress, list_stack, array_stack);
                        break;
                    }

                    rc = array_adress_init(&array_adress, &max_capacity);

                    if (rc)
                    {
                        // free_all(array_adress, list_stack, array_stack);
                        break;
                    }

                    list_stack->capacity = max_capacity;

                    printf("\nWell done :)\n");
                }
                else
                    printf("\nStack has been already initialized!!\n");

                break;
            }

            case 6:
            {
                if (!list_stack)
                {
                    printf("No avaliable stack :(\n");
                    // free_all(array_adress, list_stack, array_stack);
                    rc = ERR_NO_STACK;

                    break;
                }

                if (list_is_full(list_stack))
                {
                    printf("Stack is overflowed :(\n");
                    // free_all(array_adress, list_stack, array_stack);
                    rc = ERR_OVERFLOW;

                    break;
                }

                rc = input_num(&num);
                
                if (rc)
                {
                    // free_all(array_adress, list_stack, array_stack);
                    break;
                }

                rc = list_push(list_stack, &num, array_adress);

                if (rc)
                {
                    // free_all(array_adress, list_stack, array_stack);
                    break;
                }

                printf("\nWell done :)\n");

                break;
            }

            case 7:
            {
                if (!list_stack)
                {
                    // free_all(array_adress, list_stack, array_stack);
                    printf("No avaliable stack :(\n");
                    rc = ERR_NO_STACK;

                    break;
                }


                if (list_is_empty(list_stack))
                {
                    printf("Stack is empty :(\n");
                    // free_all(array_adress, list_stack, array_stack);
                    rc = ERR_UNDERFLOW;

                    break;
                }

                num = list_pop(list_stack, array_adress);

                printf("\nThis elem %.6lf was removed from stack\n", num);
                printf("\nWell done :)\n");
                break;
            }

            case 8:
            {
                if (!list_stack)
                {
                    // free_all(array_adress, list_stack, array_stack);
                    printf("No avaliable stack :(\n");
                    rc = ERR_NO_STACK;
                }

                rc = list_stack_print(list_stack, array_adress);

                if (rc)
                {
                    // free_all(array_adress, list_stack, array_stack);
                    break;
                }

                printf("\nWell done :)\n");

                break;
            }

            case 9:
            {
                if (!array_adress)
                {
                    // free_all(array_adress, list_stack, array_stack);
                    printf("No avaliable stack :(\n");
                    rc = ERR_NO_STACK;
                }

                rc = array_adress_print(array_adress);

                if (rc)
                {
                    // free_all(array_adress, list_stack, array_stack);
                    break;
                }

                printf("\nWell done :)\n");
                break;
            }

            case 10:
            {
                test();

                printf("\nWell done :)\n");

                rc = SUCCESS;

                break;
            }
        }

    } while (choice != 0);

    free_all(array_adress, list_stack, array_stack);

    return rc;
}
