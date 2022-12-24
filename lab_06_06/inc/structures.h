#ifndef __STRUCTURES_H__ 
#define __STRUCTURES_H__

// структура для описания узла дерева
typedef struct node_tree node_tree_t;
struct node_tree
{
    char *data;
    int index;
    node_tree_t *left;
    node_tree_t *right;
};

// структура для описания стека, хранящего адреса узлов дерева
typedef struct stack_tree stack_tree_t;
struct stack_tree
{
    node_tree_t *data;
    stack_tree_t *next;
};

// структрура для описания элемента стека
typedef struct node_stack node_stack_t;
struct node_stack
{
    char *data;
    node_stack_t *next;
};

// указатель функции
typedef void (*ptr_action_t)(node_tree_t *, void *);

#endif // __STRUCTURES_H__