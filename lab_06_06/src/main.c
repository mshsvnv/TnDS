#include "../inc/stack.h"
#include "../inc/funcs.h"
#include "../inc/tree.h"
#include "../inc/test.h"

int main()
{
    int choice = SUCCESS + 1, rc = SUCCESS;
    int val, amount;

    int *bs_numbers = NULL;
    int *expr_numbers = NULL;

    node_tree_t *bs_tree = NULL;
    node_tree_t *expr_tree = NULL;
    node_tree_t *tmp = NULL;

    char infix[MAX_LEN] = "a + ( b * ( c + ( d * ( e + f ) - ( g - h ) ) + i ) )\0";
    char postfix[MAX_LEN] = { '\0' };
    char res[MAX_LEN] = { '\0' };
    char buf[MAX_LEN] = { '\0' };
    char copy[MAX_LEN] = { '\0' };

    char *format = "%s ";
    
    conv_postfix(infix, postfix);

    while (choice != -1)
    {
        print_actions();

        if (fscanf(stdin, "%d", &choice) != 1 || choice < 0 || choice > 17)
        {
            fgets(buf, MAX_LEN, stdin);
            printf("\nНеверный пункт меню!\n");
            rc = ERR_WRONG_CHOICE;
        }
        else
        {
            switch(choice)
            {
                case 1:
                    {
                        clean_str(res);

                        expr_numbers = input_numbers(expr_numbers, AMOUNT);

                        if (!expr_numbers)
                        {
                            fgets(buf, MAX_LEN, stdin);
                            rc = ERR_NUMBERS;
                            printf("\nНеверное значение!\n");
                            break;
                        }

                        insert_numbers(postfix, expr_numbers, res);
                        printf("\n%s\n", res);

                        rc = SUCCESS;
                        break;
                    }
                case 2:
                    {
                        if (!expr_numbers)
                        {
                            rc = ERR_NUMBERS;
                            printf("\nНеверное значение!\n");
                            break;
                        }
                        else
                            post_order(expr_tree, node_free, NULL);

                        expr_tree = expr_tree_constructor(res);

                        if (!expr_tree)
                        {
                            rc = ERR_TREE_EMPTY;
                            printf("\nПустое дерево!\n");
                            break;   
                        }

                        printf("\nВыражение записано в дерево!\n");

                        rc = SUCCESS;
                        break;
                    }
                case 3:
                    {
                        if (!expr_tree)
                        {
                            rc = ERR_TREE_EMPTY;
                            printf("\nПустое дерево!\n");
                            break;   
                        }

                        val = tree_calc(expr_tree);

                        printf("\nВычисленное значение с помощью дерева: %d\n", val);

                        rc = SUCCESS;
                        break;
                    }
                case 4:
                    {
                        clean_str(copy);
                        strcpy(copy, res);

                        if (!expr_numbers)
                        {
                            rc = ERR_NUMBERS;
                            printf("\nНет доступных значений!\n");
                            break;   
                        }

                        val = stack_calc(copy);

                        printf("\nВычисленное значение с помощью стека: %d\n", val);
                        
                        rc = SUCCESS;
                        break;
                    }
                case 5:
                    {
                        test();
                        
                        rc = SUCCESS;
                        break;
                    }
                case 6:
                    {
                        if (!expr_tree)
                        {
                            rc = ERR_TREE_EMPTY;
                            printf("\nПустое дерево!\n");
                            break;   
                        }

                        printf("\nПрефиксный обход: ");
                        pre_order(expr_tree, node_print, format);
                        printf("\n");

                        rc = SUCCESS;
                        break;
                    }
                case 7:
                    {
                        if (!expr_tree)
                        {
                            rc = ERR_TREE_EMPTY;
                            printf("\nПустое дерево!\n");
                            break;   
                        }

                        printf("\nИнфиксный обход: ");
                        in_order(expr_tree, node_print, format);
                        printf("\n");

                        rc = SUCCESS;
                        break;
                    }
                case 8:
                    {
                        if (!expr_tree)
                        {
                            rc = ERR_TREE_EMPTY;
                            printf("\nПустое дерево!\n");
                            break;   
                        }

                        printf("\nПостфиксный обход: ");
                        post_order(expr_tree, node_print, format);
                        printf("\n");

                        rc = SUCCESS;
                        break;
                    }
                case 9:
                    {
                        if (!expr_tree)
                        {
                            rc = ERR_TREE_EMPTY;
                            printf("\nПустое дерево!\n");
                            break;   
                        }

                        FILE *expr_tree_file = fopen("out/expr_tree.gv", "w");

                        tree_export_to_dot(expr_tree, expr_tree_file, "expression tree");
                        printf("\nДерево выражений записано в файл!\n");

                        fclose(expr_tree_file);

                        rc = SUCCESS;
                        break;
                    }
                case 10:
                    {
                        rc = input_amount(&amount);

                        if (rc)
                        {
                            fgets(buf, MAX_LEN, stdin);
                            printf("\nНеверное значение!\n");
                            rc = ERR_NUMBERS;
                            break;
                        }

                        if (bs_numbers)
                        {
                            free(bs_numbers);
                            bs_numbers = NULL;

                            post_order(bs_tree, node_free, NULL);
                        }

                        bs_numbers = input_numbers(bs_numbers, amount);

                        if (!bs_numbers)
                        {
                            fgets(buf, MAX_LEN, stdin);
                            printf("\nНеверное значение!\n");
                            rc = ERR_NUMBERS;
                            break;
                        }

                        bs_tree = bs_tree_constructor(bs_numbers, amount);

                        if (!bs_tree)
                        {
                            rc = ERR_TREE_EMPTY;
                            printf("\nПустое дерево!\n");
                            break;   
                        }

                        printf("\nДДС создано!\n");

                        rc = SUCCESS;
                        break;
                    }
                case 11:
                    {
                        if (!bs_tree)
                        {
                            rc = ERR_TREE_EMPTY;
                            printf("\nПустое дерево!\n");
                            break;   
                        }
                        
                        fgets(buf, strlen(buf), stdin);
                        printf("\nВведите значение для поиска: ");
                        
                        if (fscanf(stdin, "%d", &val) != 1)
                        {
                            fgets(buf, MAX_LEN, stdin);
                            printf("\nНеверное значение!\n");
                            rc = ERR_NUMBERS;
                            break;
                        }

                        sprintf(buf, "%d", val);

                        tmp = node_tree_find(bs_tree, buf);

                        if (tmp)
                            printf("\nВведенное значение найдено: %s!\n", tmp->data);
                        else
                            printf("\nВведенное значение не найдено!\n");

                        rc = SUCCESS;
                        break;
                    }
                case 12:
                    {
                        fgets(buf, strlen(buf), stdin);
                        printf("\nВведите значение для добавления: ");
                        
                        if (fscanf(stdin, "%d", &val) != 1)
                        {
                            fgets(buf, MAX_LEN, stdin);
                            printf("\nНеверное значение!\n");
                            rc = ERR_NUMBERS;
                            break;
                        }

                        sprintf(buf, "%d", val);

                        tmp = node_tree_find(bs_tree, buf);

                        if (tmp)
                        {
                            printf("\nНеверное значение!\n");
                            rc = ERR_NUMBERS;
                            break;
                        }

                        tmp = node_tree_create(buf, NULL, NULL, amount++);
                        bs_tree = node_tree_insert(bs_tree, tmp);

                        printf("\nВведенное значение добавлено в дерево!\n");

                        rc = SUCCESS;
                        break;
                    }
                case 13:
                    {
                        if (!bs_tree)
                        {
                            rc = ERR_TREE_EMPTY;
                            printf("\nПустое дерево!\n");
                            break;   
                        }
                        
                        fgets(buf, strlen(buf), stdin);
                        printf("\nВведите значение для удаления: ");
                        
                        if (fscanf(stdin, "%d", &val) != 1)
                        {
                            fgets(buf, MAX_LEN, stdin);
                            printf("\nНеверное значение!\n");
                            rc = ERR_NUMBERS;
                            break;
                        }

                        sprintf(buf, "%d", val);

                        tmp = node_tree_find(bs_tree, buf);

                        if (tmp)
                        {
                            node_tree_delete(&bs_tree, tmp->data);
                            printf("\nВведенное значение удалено!\n");
                        }
                        else
                            printf("\nВведенного значения нет в дереве!\n");

                        rc = SUCCESS;
                        break;
                    }
                case 14:
                    {
                        if (!bs_tree)
                        {
                            rc = ERR_TREE_EMPTY;
                            printf("\nПустое дерево!\n");
                            break;   
                        }

                        printf("\nПрефиксный обход: ");
                        pre_order(bs_tree, node_print, format);
                        printf("\n");

                        rc = SUCCESS;
                        break;
                    }
                case 15:
                    {
                        if (!bs_tree)
                        {
                            rc = ERR_TREE_EMPTY;
                            printf("Пустое дерево!\n");
                            break;   
                        }

                        printf("\nИнфиксный обход: ");
                        in_order(bs_tree, node_print, format);
                        printf("\n");

                        rc = SUCCESS;
                        break;
                    }
                case 16:
                    {
                        if (!bs_tree)
                        {
                            rc = ERR_TREE_EMPTY;
                            printf("\nПустое дерево!\n");
                            break;   
                        }

                        printf("\nПостфиксный обход: ");
                        post_order(bs_tree, node_print, format);
                        printf("\n");

                        rc = SUCCESS;
                        break;
                    }
                case 17:
                    {
                        if (!bs_tree)
                        {
                            rc = ERR_TREE_EMPTY;
                            printf("\nПустое дерево!\n");
                            break;   
                        }

                        FILE *bs_tree_file = fopen("out/bs_tree.gv", "w");

                        tree_export_to_dot(bs_tree, bs_tree_file, "binary search tree");
                        printf("\nДвоичное дерево поиска записано в файл!\n");

                        fclose(bs_tree_file);

                        rc = SUCCESS;
                        break;
                    }
                case 0:
                    {
                        choice = -1;
                        break;
                    }
            }
        }
    }

    post_order(expr_tree, node_free, NULL);
    post_order(bs_tree, node_free, NULL);

    free(bs_numbers);
    free(expr_numbers);

    return rc;
}

