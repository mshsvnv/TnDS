#include "../inc/stack.h"
#include "../inc/funcs.h"
#include "../inc/tree.h"
#include "../inc/hash.h"
#include "../inc/dot.h"
#include "../inc/test.h"

int main()
{
    int choice = SUCCESS + 1, rc = SUCCESS;
    int val, amount = 0, compares;

    int *bs_numbers = NULL;         // значения, полученные в результате вычислений в дереве выражений
    int *expr_numbers = NULL;       // к-ты выражения

    node_tree_t *bs_tree = NULL;    // ДДП
    node_tree_t *avl_tree = NULL;   // АВЛ-дерево
    node_tree_t *expr_tree = NULL;  // Дерево выражения
    node_tree_t *tmp_node = NULL;   

    hash_table_t *open_adr_table = NULL;          // открытая адресация
    hash_table_t *chained_table = NULL;          // метод цепочек
    ptr_hash_func_t func = hash_func_mul;

    char infix[MAX_LEN] = "a + ( b * ( c + ( d * ( e + f ) - ( g - h ) ) + i ) )\0";
    char postfix[MAX_LEN] = { '\0' };
    char res[MAX_LEN] = { '\0' };
    char buf[MAX_LEN] = { '\0' };

    conv_postfix(infix, postfix);

    while (choice != -1)
    {
        print_actions();

        if (fscanf(stdin, "%d", &choice) != 1 || choice < 0 || choice > 7)
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
                        printf("\nПолученная постфиксная запись: %s\n", res);

                        post_order(expr_tree, node_free, NULL, NULL);
                        post_order(bs_tree, node_free, NULL, NULL);
                        post_order(avl_tree, node_free, NULL, NULL);

                        open_adr_table_free(open_adr_table);
                        chained_table_free(chained_table);                                          

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

                        expr_tree = expr_tree_constructor(res);

                        printf("\nВыражение записано в дерево!\n");

                        val = tree_calc(expr_tree);

                        printf("\nЗначение, вычисленное с помощью дерева: %d\n", val);

                        amount = make_bs_numbers_array(expr_tree, &bs_numbers);
                        
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

                        bs_tree = bs_tree_constructor(bs_numbers, amount, NULL);

                        printf("\nДДП создано!\n");

                        avl_tree = bs_tree_constructor(bs_numbers, amount, node_balance);

                        printf("\nАВЛ-дерево создано!\n");

                        open_adr_table = open_adr_table_construct(bs_numbers, amount, func);

                        printf("\nХеш-таблица с открытой адресацией создана!\n");
                        
                        chained_table = chained_table_construct(bs_numbers, amount, func);

                        printf("\nХеш-таблица методом цепочек создана!\n");

                        rc = SUCCESS;
                        break;
                    }
                case 4:
                    {
                        if (!bs_tree)
                        {
                            rc = ERR_TREE_EMPTY;
                            printf("\nПустое дерево!\n");
                            break;   
                        }
                        
                        printf("\nВведите значение для поиска: ");
                        
                        if (fscanf(stdin, "%d", &val) != 1)
                        {
                            printf("\nНеверное значение!\n");
                            rc = ERR_NUMBERS;
                            break;
                        }
                        
                        compares = 0;
                        tmp_node = node_tree_find(bs_tree, val, &compares);

                        if (compares != -1)
                            printf("\nЗначение, найденное в ДДП: %d!\n", tmp_node->value);
                        else
                            printf("\nВведенное значение в ДДП не найдено!\n");

                        compares = 0;
                        tmp_node = node_tree_find(avl_tree, val, &compares);

                        if (compares != -1)
                            printf("\nЗначение, найденное в АВЛ-дереве: %d!\n", tmp_node->value);
                        else
                            printf("\nВведенное значение в АВЛ-дереве не найдено!\n");

                        int res = open_adr_table_find(open_adr_table, val, func, &compares);
                        
                        if (compares != -1)
                            printf("\nЗначение, найденное в хеш-таблице: %d!\n", res);
                        else
                            printf("\nВведенное значение в хеш-таблице не найдено!\n");

                        res = chained_table_find(chained_table, val, func, &compares);
                        
                        if (compares != -1)
                            printf("\nЗначение, найденное в хеш-таблице: %d!\n", res);
                        else
                            printf("\nВведенное значение в хеш-таблице не найдено!\n");

                        rc = SUCCESS;
                        break;
                    }
                case 5:
                    {
                        if (!expr_tree)
                        {
                            rc = ERR_TREE_EMPTY;
                            printf("\nПустое дерево!\n"); 
                        }
                        else
                        {
                            FILE *expr_tree_file = fopen("out/expr_tree.gv", "w");

                            tree_export_to_dot(expr_tree, expr_tree_file, "expression tree");
                            printf("\nДерево выражений записано в файл!\n");

                            fclose(expr_tree_file);

                            rc = SUCCESS;
                        }

                        if (!bs_tree)
                        {
                            rc = ERR_TREE_EMPTY;
                            printf("\nПустое дерево!\n");
                        }
                        else
                        {
                            FILE *bs_tree_file = fopen("out/bs_tree.gv", "w");

                            tree_export_to_dot(bs_tree, bs_tree_file, "binary search tree");
                            printf("\nДДП записано в файл!\n");

                            fclose(bs_tree_file);

                            rc = SUCCESS;
                        }

                        if (!avl_tree)
                        {
                            rc = ERR_TREE_EMPTY;
                            printf("\nПустое дерево!\n");
                        }
                        else
                        {

                            FILE *avl_tree_file = fopen("out/avl_tree.gv", "w");

                            tree_export_to_dot(avl_tree, avl_tree_file, "avl tree");
                            printf("\nАВЛ-дерево записано в файл!\n");

                            fclose(avl_tree_file);

                            rc = SUCCESS;
                        }
                        break;

                    }
                case 6:
                    {
                        if (!open_adr_table)
                        {
                            rc = ERR_TREE_TABLE;
                            printf("\nПустая таблица!\n");
                        }
                        else
                        {

                            FILE *open_adr_table_file = fopen("out/open_adr_table.gv", "w");

                            open_adr_table_export_to_dot(open_adr_table, open_adr_table_file, "open adressing table");
                            printf("\nХеш-таблица с внутренним хешрованием записано в файл!\n");

                            fclose(open_adr_table_file);

                            rc = SUCCESS;
                        }

                        if (!chained_table)
                        {
                            rc = ERR_TREE_TABLE;
                            printf("\nПустая таблица!\n");
                        }
                        else
                        {

                            FILE *chained_table_file = fopen("out/chained_table.gv", "w");

                            chained_table_export_to_dot(chained_table, chained_table_file, "chained table");
                            printf("\nХеш-таблица с внешним хешрованием записано в файл!\n");

                            fclose(chained_table_file);

                            rc = SUCCESS;
                        }
                        break;
                    }
                case 7:
                    {
                        if (!chained_table)
                        {
                            rc = ERR_TREE_TABLE;
                            printf("\nПустая таблица!\n");
                        }
                        else
                        {
                            test(amount, bs_numbers, bs_tree, avl_tree, &open_adr_table, &chained_table, func);
                            rc = SUCCESS;
                        }
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

    post_order(expr_tree, node_free, NULL, NULL);
    post_order(bs_tree, node_free, NULL, NULL);
    post_order(avl_tree, node_free, NULL, NULL);

    open_adr_table_free(open_adr_table);
    chained_table_free(chained_table);

    free(bs_numbers);
    free(expr_numbers);

    return rc;
}

