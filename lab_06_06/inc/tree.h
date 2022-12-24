#ifndef __TREE_H__ 
#define __TREE_H__

#include "constants.h"
#include "structures.h"
#include "funcs.h"

// вывод в файл
void tree_export_to_dot(node_tree_t *tree, FILE *f, char *name);

void node_to_dot(node_tree_t *tree, void *arg);

void node_print(node_tree_t *tree, void *arg);

// освобождение паямти
void node_free(node_tree_t *tree, void *arg);

// создание элемента дерева
node_tree_t *node_tree_create(char *data, node_tree_t *left, node_tree_t *right, int index);

node_tree_t *node_tree_insert(node_tree_t *tree, node_tree_t *tmp);

node_tree_t *node_tree_find(node_tree_t *tree, char *data);

void node_tree_delete(node_tree_t **tree, char *data);

// работа с элементами стека для хранения адресов узлов
stack_tree_t *stack_tree_create(node_tree_t *data);

stack_tree_t *stack_tree_push(stack_tree_t *head, stack_tree_t *tmp);

node_tree_t *stack_tree_pop(stack_tree_t **head);

// создание дерева выражений
node_tree_t *expr_tree_constructor(char *postfix);

node_tree_t *bs_tree_constructor(int *numbers, int amount);

// функции обхода
void in_order(node_tree_t *tree, ptr_action_t func, void *arg);

void post_order(node_tree_t *tree, ptr_action_t func, void *arg);

void pre_order(node_tree_t *tree, ptr_action_t func, void *arg);

// функция подсчета значения выражения
int tree_calc(node_tree_t *head);

int is_leaf(node_tree_t *head);

#endif // __TREE_H__