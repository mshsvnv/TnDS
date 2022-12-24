#include "../inc/constants.h"
#include "../inc/structures.h"
#include "../inc/array.h"
#include "../inc/list.h"
#include "../inc/others.h"
#include "../inc/test.h"

int main(int argc, char **argv)
{
    int choice = 1, rc = SUCCESS, num, flag = 0;
    long size;
    char buf[5];

    FILE *f_in;

    node_t *tmp;
    list_adresses_t *list_adresses = NULL;
    arr_queue_t *arr_queue = NULL;
    list_queue_t *list_queue = NULL;

    times_t t_1 = { 0, 6 }, t_2 = { 0, 1 };

    while (choice != 0)
    {
        print_menu();

        if (fscanf(stdin, "%d", &choice) != 1 || choice < 0 || choice > 15 || argc > 2)
        {
            printf("Неверный пункт меню!\n");
            rc = ERR_WRONG_CHOICE;
            break;
        }

        switch (choice)
        {
            case 1:
                {
                    if (!arr_queue || arr_queue->total_size == 0)
                    {
                        f_in = stdin;

                        rc = arr_queue_create(&arr_queue, f_in, -1);

                        if (rc == ERR_WRONG_SIZE)
                        {
                            printf("Неверный размер!\n");
                            break;
                        }
                        else if (rc == ERR_MEMORY)
                            break;

                        rc = arr_queue_fill(arr_queue, f_in);

                        if (rc)
                        {
                            printf("Неверное значение!\n");
                            break;
                        }
                        break;
                    }

                    printf("Очередь уже создана!\n");
                    break;
                }
            case 2:
                {
                    if (!arr_queue || arr_queue->total_size == 0)
                    {
                        if (!flag)
                        {
                            f_in = fopen(argv[1], "r");
                            flag = 1;
                        }
                        else
                            fseek(f_in, 0, SEEK_SET);


                        if (!f_in)
                        {
                            rc = ERR_IO;
                            flag = 0;
                            printf("Входного файла нет!\n");
                            break;
                        }

                        size = check_file_size(f_in);

                        if (size == 0)
                        {
                            rc = ERR_EMPTY;
                            printf("Пустой входной файл!\n");
                            break;
                        }  

                        rc = arr_queue_create(&arr_queue, f_in, -1);

                        if (rc == ERR_WRONG_SIZE)
                        {
                            printf("Неверный размер!\n");
                            break;
                        }
                        else if (rc == ERR_MEMORY)
                            break;

                        rc = arr_queue_fill(arr_queue, f_in);

                        if (rc)
                        {
                            printf("Неверное значение!\n");
                            fgets(buf, 5, stdin);
                            break;
                        }
                        break;
                    }

                    printf("Очередь уже создана!\n");
                    break;
                }
            case 3:
                {
                    if (!arr_queue)
                    {
                        rc = ERR_NO_INIT;
                        printf("Нет доступной очереди!\n");
                        break;
                    }

                    rc = arr_is_full(arr_queue);

                    if (rc)
                    {
                        printf("Очередь переполнена!\n");
                        break;
                    }

                    rc = input_elem(&num);

                    if (rc)
                    {
                        printf("Неверное значение!\n");
                        fgets(buf, 5, stdin);
                        break;
                    }

                    arr_push(arr_queue, &num);
                    break;
                }
            case 4:
                {
                    if (!arr_queue)
                    {
                        rc = ERR_NO_INIT;
                        printf("Нет доступной очереди!\n");
                        break;
                    }

                    rc = arr_is_empty(arr_queue);

                    if (rc)
                    {
                        printf("Очередь пуста!\n");
                        break;
                    }

                    num = arr_pop(arr_queue);

                    printf("\nУдаленное значение: %s%d %s\n", MAGENTA, num, RESET);
                    break;                                                                                  
                }
            case 5:
                {
                    if (!arr_queue)
                    {
                        rc = ERR_NO_INIT;
                        printf("Нет доступной очереди!\n");
                        break;
                    }

                    rc = arr_is_empty(arr_queue);

                    if (rc)
                    {
                        printf("Очередь пуста!\n");
                        break;
                    }

                    arr_print(arr_queue);

                    rc = SUCCESS;
                    break;
                }
            case 6:
                {
                    if (!list_queue || list_queue->total_size == 0)
                    {
                        f_in = stdin;

                        rc = list_queue_create(&list_queue, f_in, -1);

                        if (rc == ERR_WRONG_SIZE)
                        {
                            printf("Неверный размер!\n");
                            break;
                        }
                        else if (rc == ERR_MEMORY)
                            break;

                        rc = list_queue_fill(&list_queue, f_in);

                        if (rc)
                        {
                            printf("Неверное значение!\n");
                            fgets(buf, 5, stdin);
                            break;
                        }

                        rc = list_adresses_init(&list_adresses);
                        break;
                    }

                    printf("Очередь уже создана!\n");
                    break;
                }
            case 7:
                {
                    if (!list_queue || list_queue->total_size == 0)
                    {
                        if (!flag)
                        {
                            f_in = fopen(argv[1], "r");
                            flag = 1;
                        }
                        else
                            fseek(f_in, 0, SEEK_SET);

                        if (!f_in)
                        {
                            rc = ERR_IO;
                            flag = 0;
                            printf("Входного файла нет!\n");
                            break;
                        }

                        size = check_file_size(f_in);

                        if (size == 0)
                        {
                            rc = ERR_EMPTY;
                            printf("Пустой входной файл!\n");
                            break;
                        }  

                        rc = list_queue_create(&list_queue, f_in, -1);

                        if (rc)
                        {
                            printf("Неверный размер!\n");
                            break;
                        }

                        rc = list_queue_fill(&list_queue, f_in);

                        if (rc)
                        {
                            printf("Неверное значение!\n");
                            break;
                        }
                        
                        rc = list_adresses_init(&list_adresses);
                        break;
                    }

                    printf("Очередь уже создана!\n");
                    break;
                }
            case 8:
                {
                    if (!list_queue)
                    {
                        rc = ERR_NO_INIT;
                        printf("Нет доступной очереди!\n");
                        break;
                    }

                    rc = list_is_full(list_queue);

                    if (rc)
                    {
                        printf("Очередь переполнена!\n");
                        break;
                    }

                    rc = input_elem(&num);

                    if (rc)
                    {
                        printf("Неверное значение!\n");
                        fgets(buf, 5, stdin);
                        break;
                    }

                    tmp = node_create(&num);

                    if (!tmp)
                        break;

                    list_push(&list_queue, tmp);

                    if (list_adresses)
                        list_adresses_del(list_adresses, tmp);
                    break;
                }
            case 9:
                {
                    if (!list_queue)
                    {
                        rc = ERR_NO_INIT;
                        printf("Нет доступной очереди!\n");
                        break;
                    }

                    rc = list_is_empty(list_queue);

                    if (rc)
                    {
                        printf("Очередь пуста!\n");
                        break;
                    }

                    if (list_adresses->cur_size == list_adresses->total_size)
                        list_adresses_expand(list_adresses);

                    list_adresses_add(list_adresses, list_queue->first);

                    tmp = list_pop(list_queue);

                    free(tmp);
                    break;
                }
            case 10:
                {
                    if (!list_queue)
                    {
                        rc = ERR_NO_INIT;
                        printf("Нет доступной очереди!\n");
                        break;
                    }

                    rc = list_is_empty(list_queue);

                    if (rc)
                    {
                        printf("Очередь пуста!\n");
                        break;
                    }

                    list_print(list_queue);

                    rc = SUCCESS;
                    break;
                }
            case 11:
                {
                    if (!list_adresses)
                    {
                        rc = ERR_NO_INIT;
                        printf("Нет доступныйх адресов!\n");
                        break;
                    }

                    if (list_adresses->cur_size == 0)
                    {
                        rc = ERR_NO_INIT;
                        printf("Список адресов пуст!\n");
                        break;
                    }

                    list_adresses_print(list_adresses);

                    rc = SUCCESS;
                    break;
                }
            case 12:
                {
                    rc = change_time(&t_1, &t_2);
                    break;
                }
            case 13:
                {
                    arr_modeling(&t_1, &t_2);
                    break;
                }
            case 14:
                {
                    list_modeling(&t_1, &t_2);
                    break;
                }
            case 15:
                {
                    test_time_memory();
                    break;
                }
            case 0:
                {
                    choice = 0;
                    break;
                }
        }
    }

    free_all(arr_queue, list_queue, list_adresses);
    
    if (flag)
        fclose(f_in);

    return rc;
}