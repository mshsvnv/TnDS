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

node_tree_t *node_tree_create(char *data, node_tree_t *left, node_tree_t *right, int index)
{
    node_tree_t *tmp = malloc(sizeof(node_tree_t));

    char *str = malloc(sizeof(data));
    strcpy(str, data);

    if (tmp)
    {
        tmp->data = str;
        tmp->right = right;
        tmp->left = left;
        tmp->index = index;
    }

    return tmp;
}

void node_tree_delete(node_tree_t **tree, char *data)
{
    int cmp = atoi((*tree)->data) - atoi(data);

    node_tree_t *pointer = *tree, *parent = NULL, *removed = NULL, *child = NULL;
    node_tree_t *min_left = NULL, *min_left_parent;

    while (cmp && pointer)
    {
        parent = pointer;

        if (cmp > 0)
            pointer = parent->left;
        else
            pointer = parent->right;

        cmp = atoi(pointer->data) - atoi(data);
        
    }

    if (!pointer->left || !pointer->right)
    {
        removed = pointer;

        if (pointer->left)
            child = pointer->left;
        else if (pointer->right)
            child = pointer->right;

        if (!parent)
            *tree = child;
        else
        {
            if (parent->left == pointer)
                parent->left = child;
            else
                parent->right = child;
        }
    }
    else
    {
        min_left = pointer->right;
        min_left_parent = pointer;

        while (min_left->left)
        {
            min_left_parent = min_left;
            min_left = min_left->left;
        }

        memmove(pointer->data, min_left->data, strlen(min_left->data));
        removed = min_left;

        if (min_left_parent->left == min_left)
            min_left_parent->left = NULL;
        else
            min_left_parent->right = min_left->right;
    }

    node_free(removed, NULL);
}

node_tree_t *node_tree_insert(node_tree_t *tree, node_tree_t *tmp)
{
    int cmp;

    if (!tree)
        return tmp;
    
    cmp = atoi(tree->data) - atoi(tmp->data);

    if (cmp > 0)
        tree->left = node_tree_insert(tree->left, tmp);
    else
        tree->right = node_tree_insert(tree->right, tmp);

    return tree;
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

    int index = 0;

    while (postfix_cur != NULL)
    {
        if (is_operand(postfix_cur))
        {
            tmp_l = stack_tree_pop(&head_stack);
            tmp_r = stack_tree_pop(&head_stack);

            tmp = node_tree_create(postfix_cur, tmp_r, tmp_l, index++);
        }
        else
            tmp = node_tree_create(postfix_cur, NULL, NULL, -1);

        tmp_stack = stack_tree_create(tmp);
        head_stack = stack_tree_push(head_stack, tmp_stack);
        
        postfix_cur = strtok(NULL, delim);
    }

    return stack_tree_pop(&head_stack);
}

node_tree_t *bs_tree_constructor(int *numbers, int amount)
{
    int i;

    node_tree_t *tree = NULL, *tmp = NULL;
    char buf[MAX_LEN];

    for (i = 0; i < amount; i++)
    {
        sprintf(buf, "%d", numbers[i]);

        tmp = node_tree_create(buf, NULL, NULL, -1);

        tree = node_tree_insert(tree, tmp);
    }

    return tree;
}

node_tree_t *node_tree_find(node_tree_t *tree, char *data)
{
    int cmp;

    if (!tree)
        return NULL;

    cmp = atoi(tree->data) - atoi(data);

    if (!cmp)
        return tree;
    else if (cmp > 0)
        return node_tree_find(tree->left, data);
    else
        return node_tree_find(tree->right, data);
}

void node_print(node_tree_t *tree, void *arg)
{
    char *format = arg;

    printf(format, tree->data);
}

void node_free(node_tree_t *tree, void *arg)
{
    if (!arg)
    {
        free(tree->data);
        free(tree);
    }
}

void in_order(node_tree_t *tree, ptr_action_t func, void *arg)
{
    if (!tree)
        return;
    
    if (is_operand(tree->data))
        printf("(");

    in_order(tree->left, func, arg);
    func(tree, arg);
    in_order(tree->right, func, arg);

    if (is_operand(tree->data))
        printf(")");
}

void post_order(node_tree_t *tree, ptr_action_t func, void *arg)
{
    if (!tree)
        return;
    
    post_order(tree->left, func, arg);
    post_order(tree->right, func, arg);
    func(tree, arg);
}

void pre_order(node_tree_t *tree, ptr_action_t func, void *arg)
{
    if (!tree)
        return;
    
    func(tree, arg);
    pre_order(tree->left, func, arg);
    pre_order(tree->right, func, arg);
}

int is_leaf(node_tree_t *head)
{
    return (head->left == NULL) && (head->right == NULL);
}

int tree_calc(node_tree_t *head)
{
    if (!head)
        return 0;

    if (is_leaf(head))
        return atoi(head->data);

    int left = tree_calc(head->left);
    int right = tree_calc(head->right);

    return process(head->data, left, right);
}

void tree_export_to_dot(node_tree_t *tree, FILE *f, char *name)
{
    fprintf(f, "digraph \"%s\" {\n", name);

    post_order(tree, node_to_dot, f);

    fprintf(f, "}\n");
}

void node_to_dot(node_tree_t *tree, void *arg)
{
    FILE *f = arg;


    if (tree->left)
    {
        if (tree->index == -1)
        {
            if (tree->left->index == -1)
                fprintf(f, "\"%s\" -> \"%s\";\n", tree->data, tree->left->data);
            else  
                fprintf(f, "\"%s\" -> \"%s | %d\";\n", tree->data, tree->left->data, tree->left->index); 
        }
        else
        {
            if (tree->left->index == -1)
                fprintf(f, "\"%s | %d\"-> \"%s\";\n", tree->data, tree->index, tree->left->data);
            else  
                fprintf(f, "\"%s | %d\" -> \"%s | %d\";\n", tree->data, tree->index, tree->left->data, tree->left->index); 
        }    
    }
    else
        fprintf(f, "\"%s\";\n", tree->data);  

    if (tree->right)
    {
        if (tree->index == -1)
        {
            if (tree->right->index == -1)
                fprintf(f, "\"%s\" -> \"%s\";\n", tree->data, tree->right->data);
            else  
                fprintf(f, "\"%s\" -> \"%s | %d\";\n", tree->data, tree->right->data, tree->right->index); 
        }
        else
        {
            if (tree->right->index == -1)
                fprintf(f, "\"%s | %d\"-> \"%s\";\n", tree->data, tree->index, tree->right->data);
            else  
                fprintf(f, "\"%s | %d\" -> \"%s | %d\";\n", tree->data, tree->index, tree->right->data, tree->right->index); 
        }    
    }
}
