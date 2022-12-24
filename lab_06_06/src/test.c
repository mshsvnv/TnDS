#include "../inc/test.h"

unsigned long long milliseconds_now(void)
{
    struct timeval val;

    if (gettimeofday(&val, NULL))
        return (unsigned long long) - 1;

    return val.tv_sec * 1000000ULL + val.tv_usec;
}

void test(void)
{
    srand(time(NULL));

    unsigned long long beg_tree, end_tree, total_tree, beg_stack, end_stack, total_stack;

    char infix_1[MAX_LEN] = "15 + ( 2 * ( 3 + ( 4 * ( 5 + 6 ) - ( 7 - 8 ) ) + 9 ) )\0";
    char infix_2[MAX_LEN] = "16 * ( 2 - 3 * 4 - ( 5 * 6 * 7 + 8 * 9 ) - ( 10 + 11 - ( 12 + 13 ) ) )\0";
    char infix_3[MAX_LEN] = "17 * ( 2 * ( 3 * ( 4 - 5 ) - 6 ) - 7 ) + 8 * 9 - 10 - 11 + 12\0";

    char postfix[MAX_LEN] = { '\0' };

    int val_stack, val_tree, i;

    node_tree_t *tree = NULL;

    
    printf("\n+-----------------------------------------+----------------------+----------------------+\n");
    printf("|                                         |         Стек         |        Дерево        |\n");
    printf("+                                         +-----------+----------+-----------+----------+\n");
    printf("|                                         |Время(мкс.)| Значение |Время(мкс.)| Значение |\n");
    printf("+-----------------------------------------+-----------+----------+-----------+----------+\n");
    
    // first expression

    conv_postfix(infix_1, postfix);

    total_stack = 0, total_tree = 0;

    for (i = 0; i < MAX_LEN; i++)
    {    
        beg_stack = milliseconds_now();
        val_stack = stack_calc(postfix);
        end_stack = milliseconds_now();

        total_stack += end_stack - beg_stack;
    }

    for (i = 0; i < MAX_LEN; i++)
    {
        beg_tree = milliseconds_now();
        tree = expr_tree_constructor(postfix);
        val_tree = tree_calc(tree);
        post_order(tree, node_free, NULL);
        end_tree = milliseconds_now();

        total_tree += end_tree - beg_tree;
    }

    printf("|1. 15+(2*(3+(4*(5+6)-(7-8))+9))          |%11llu|%10d|%11llu|%10d|\n", total_stack, val_stack, total_tree, val_tree);
    printf("+-----------------------------------------+-----------+----------+-----------+----------+\n");
        
    clean_str(postfix);

    // second expression

    conv_postfix(infix_2, postfix);

    total_stack = 0, total_tree = 0;

    for (i = 0; i < MAX_LEN; i++)
    {    
        beg_stack = milliseconds_now();
        val_stack = stack_calc(postfix);
        end_stack = milliseconds_now();

        total_stack += end_stack - beg_stack;
    }

    for (i = 0; i < MAX_LEN; i++)
    {
        beg_tree = milliseconds_now();
        tree = expr_tree_constructor(postfix);
        val_tree = tree_calc(tree);
        post_order(tree, node_free, NULL);
        end_tree = milliseconds_now();

        total_tree += end_tree - beg_tree;
    }

    printf("|2. 16*(2-3*4-(5*6*7+8*9)-(10+11-(12+13)))|%11llu|%10d|%11llu|%10d|\n", total_stack, val_stack, total_tree, val_tree);
    printf("+-----------------------------------------+-----------+----------+-----------+----------+\n");
        
    clean_str(postfix);

    // // third expression

    conv_postfix(infix_3, postfix);

    total_stack = 0, total_tree = 0;

    for (i = 0; i < MAX_LEN; i++)
    {    
        beg_stack = milliseconds_now();
        val_stack = stack_calc(postfix);
        end_stack = milliseconds_now();

        total_stack += end_stack - beg_stack;
    }

    for (i = 0; i < MAX_LEN; i++)
    {
        beg_tree = milliseconds_now();
        tree = expr_tree_constructor(postfix);
        val_tree = tree_calc(tree);
        post_order(tree, node_free, NULL);
        end_tree = milliseconds_now();

        total_tree += end_tree - beg_tree;
    }  

    printf("|3. 17*(2*(3*(4-5)-6)-7)+8*9-10-11+12     |%11llu|%10d|%11llu|%10d|\n", total_stack, val_stack, total_tree, val_tree);
    printf("+-----------------------------------------+-----------+----------+-----------+----------+\n");
        
    clean_str(postfix);
}