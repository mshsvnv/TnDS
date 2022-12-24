#include "../inc/tree.h"

stack_tree_t *stack_tree_create(node_tree_t *data)
{
    stack_tree_t *tmp = malloc(sizeof(stack_tree_t));

    if (tmp)
    {
        tmp->data = data;
        tmp->next = NULL;
    }

    return tmp;
}

stack_tree_t *stack_tree_push(stack_tree_t *head, stack_tree_t *tmp)
{
    stack_tree_t *cur = head;

    if (head)
    {
        for (; cur->next; cur = cur->next);

        cur->next = tmp;

        return head;
    }
    else
        return tmp;
}

node_tree_t *stack_tree_pop(stack_tree_t **head)
{
    stack_tree_t *cur = *head, *prev  = NULL;
    node_tree_t *data;

    while (cur->next)
    {
        prev = cur;
        cur = cur->next;
    }
    
    data = cur->data;

    if (prev)
        prev->next = NULL;

    if ((void *)*head == (void *)cur)
    {
        free(*head);
        *head = NULL;
    }
    else
    {
        free(cur);
        cur = NULL;
    }

    return data;
}

node_tree_t *node_tree_create(int value, char operand, node_tree_t *left, node_tree_t *right)
{
    node_tree_t *tmp = malloc(sizeof(node_tree_t));

    if (tmp)
    {
        tmp->value = value;
        tmp->operand = operand;

        tmp->left = left;
        tmp->right = right;

        tmp->height = 1;
    }

    return tmp;
}

node_tree_t *node_tree_insert(node_tree_t *tree, node_tree_t *tmp, ptr_balance_t func)
{
    int cmp;

    if (!tree)
        return tmp;
    
    cmp = tree->value - tmp->value;

    if (cmp > 0)
        tree->left = node_tree_insert(tree->left, tmp, func);
    else
        tree->right = node_tree_insert(tree->right, tmp, func);

    return func ? func(tree) : tree;
}

node_tree_t *expr_tree_constructor(char *postfix)
{
    char copy_postfix[MAX_LEN];
    
    size_t i = 0;

    while (i < strlen(postfix))
    {
        copy_postfix[i] = postfix[i];
        i++;
    }

    copy_postfix[i] = '\0';

    char *delim = " ";
    char *postfix_cur = strtok(copy_postfix, delim);

    node_tree_t *tmp_l = NULL, *tmp_r = NULL, *tmp;
    stack_tree_t *head_stack = NULL, *tmp_stack = NULL;

    while (postfix_cur != NULL)
    {
        if (is_operand(postfix_cur))
        {
            tmp_l = stack_tree_pop(&head_stack);
            tmp_r = stack_tree_pop(&head_stack);

            tmp = node_tree_create(0, postfix_cur[0], tmp_r, tmp_l);
        }
        else
            tmp = node_tree_create(atoi(postfix_cur), -1, NULL, NULL);

        tmp_stack = stack_tree_create(tmp);
        head_stack = stack_tree_push(head_stack, tmp_stack);
        
        postfix_cur = strtok(NULL, delim);
    }

    return stack_tree_pop(&head_stack);
}

node_tree_t *bs_tree_constructor(int *bs_numbers, int amount, ptr_balance_t func)
{
    int i;

    node_tree_t *tree = NULL, *tmp = NULL;

    for (i = 0; i < amount; i++)
    {
        tmp = node_tree_create(bs_numbers[i], -1, NULL, NULL);

        tree = node_tree_insert(tree, tmp, func);
    }

    return tree;
}

node_tree_t *node_tree_find(node_tree_t *tree, int value, int *compares)
{
    int cmp;

    if (!tree)
    {
        (*compares) = -1;
        return NULL;
    }

    (*compares)++;

    cmp = tree->value - value;

    if (!cmp)
        return tree;
    else if (cmp > 0)
        tree = node_tree_find(tree->left, value, compares);
    else
        tree = node_tree_find(tree->right, value, compares);

    return tree;
}

// void node_print(node_tree_t *tree, void *arg_1, void *arg_2)
// {
//     char *format;

//     if (tree->operand == -1)
//     {
//         format = arg_1;
//         printf(format, tree->value);
//     }
//     else
//     {
//         format = arg_2;
//         printf(format, tree->operand);
//     }
// }

void node_free(node_tree_t *tree, void *arg_1, void *arg_2)
{
    if (!arg_1 && !arg_2)
        free(tree);
}

void in_order(node_tree_t *tree, ptr_action_t func, void *arg_1, void *arg_2)
{
    if (!tree)
        return;

    in_order(tree->left, func, arg_1, arg_2);
    func(tree, arg_1, arg_2);
    in_order(tree->right, func, arg_1, arg_2);
}

void post_order(node_tree_t *tree, ptr_action_t func, void *arg_1, void *arg_2)
{
    if (!tree)
        return;
    
    post_order(tree->left, func, arg_1, arg_2);
    post_order(tree->right, func, arg_1, arg_2);
    func(tree, arg_1, arg_2);
}

void pre_order(node_tree_t *tree, ptr_action_t func, void *arg_1, void *arg_2)
{
    if (!tree)
        return;
    
    func(tree, arg_1, arg_2);
    pre_order(tree->left, func, arg_1, arg_2);
    pre_order(tree->right, func, arg_1, arg_2);
}

int is_leaf(node_tree_t *head)
{
    return (head->left == NULL) && (head->right == NULL);
}

int tree_calc(node_tree_t *tree)
{
    if (!tree)
        return 0;

    if (is_leaf(tree))
        return tree->value;

    int left = tree_calc(tree->left);
    int right = tree_calc(tree->right);

    tree->value = process(tree->operand, left, right);

    return tree->value;
}

void node_count(node_tree_t *tree, void *arg_1, void *arg_2)
{
    int *cur_count = arg_1;

    if (!arg_2 && tree)
        (*cur_count)++;
}

void node_value(node_tree_t *tree, void *arg_1, void *arg_2)
{
    int *arr = arg_1;
    int *cur_index = arg_2;

    arr[*cur_index] = tree->value;

    (*cur_index)++;
}

int make_bs_numbers_array(node_tree_t *tree, int **bs_numbers)
{
    int total_amount = 0;
    void *ptr_total_amount = &total_amount;

    in_order(tree, node_count, ptr_total_amount, NULL);

    *bs_numbers = malloc(sizeof(int) * total_amount);

    int i = 0, j, k, tmp, cur_amount = total_amount;
    void *ptr_i = &i;

    in_order(tree, node_value, (void *)(*bs_numbers), ptr_i);

    printf("Массив, полученный инфиксным обходом до удаления повторов: ");
    for (i = 0; i < total_amount; i++)
        printf("%d ", (*bs_numbers)[i]);
    printf("\n\n");

    i = 0;
    while (i != total_amount)
    {
        j = i + 1;
        while (j < cur_amount)
        {
            if ((*bs_numbers)[i] == (*bs_numbers)[j])
            {
                for (k = j; k < total_amount - 1; k++)
                {
                    tmp = (*bs_numbers)[k];
                    (*bs_numbers)[k] = (*bs_numbers)[k + 1];
                    (*bs_numbers)[k + 1] = tmp;
                }

                cur_amount--;
            }
            j++;
        }
        i++;
    }

    total_amount = cur_amount;

    printf("Массив, полученный инфиксным обходом после удаления повторов: ");
    for (i = 0; i < total_amount; i++)
        printf("%d ", (*bs_numbers)[i]);
    printf("\n");

    return total_amount;
}

int tree_height(node_tree_t *tree)
{
    return tree ? tree->height : 0;
}

int balance_factor(node_tree_t *tree)
{
    return tree_height(tree->right) - tree_height(tree->left);
}

void fix_height(node_tree_t *tree)
{
    int h_l = tree_height(tree->left);
    int h_r = tree_height(tree->right);

    tree->height = (h_l > h_r ? h_l : h_r) + 1;
}

node_tree_t *rotate_right(node_tree_t *node_p)
{
    node_tree_t *node_q = node_p->left;
    node_p->left = node_q->right;
    node_q->right = node_p;

    fix_height(node_p);
    fix_height(node_q);

    return node_q;
}

node_tree_t *rotate_left(node_tree_t *node_q)
{
    node_tree_t *node_p = node_q->right;
    node_q->right = node_p->left;
    node_p->left = node_q;

    fix_height(node_q);
    fix_height(node_p);

    return node_p;
}

node_tree_t *node_balance(node_tree_t *node_p)
{
    fix_height(node_p);

    if (balance_factor(node_p) == 2)
    {
        if (balance_factor(node_p->right) < 0)
            node_p->right = rotate_right(node_p->right);

        return rotate_left(node_p);
    }

    if (balance_factor(node_p) == -2)
    {
        if (balance_factor(node_p->left) > 0)
            node_p->left = rotate_left(node_p->left);

        return rotate_right(node_p);
    }

    return node_p;
}
