#ifndef __STRUCTURES_H__ 
#define __STRUCTURES_H__

// структура для описания узла дерева
typedef struct node_tree node_tree_t;
struct node_tree
{
    int value;
    char operand;

    int height;
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
typedef void(*ptr_action_t)(node_tree_t *, void *, void *);

typedef node_tree_t *(*ptr_balance_t)(node_tree_t *);

// ячейка таблицы
typedef struct
{
    int key;                        // ключ
    unsigned short int empty;       // значение
} cell_t;

typedef struct list_cell list_cell_t;
struct list_cell
{
    int key;            // указатель на значение

    list_cell_t *next;  // указатель на следующий элемент
};

typedef struct 
{
    int max_size;        // максимальный размер таблицы 

    void *cells;         // указатель на таблицу
} hash_table_t;

typedef int (*ptr_hash_func_t)(int, int);

#endif // __STRUCTURES_H__