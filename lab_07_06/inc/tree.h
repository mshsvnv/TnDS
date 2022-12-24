#ifndef __TREE_H__ 
#define __TREE_H__

#include "constants.h"
#include "structures.h"
#include "funcs.h"

void node_print(node_tree_t *tree, void *arg_1, void *arg_2);

// освобождение паямти
void node_free(node_tree_t *tree, void *arg_1, void *arg_2);

// создание элемента дерева
node_tree_t *node_tree_create(int value, char operand, node_tree_t *left, node_tree_t *right);

node_tree_t *node_tree_insert(node_tree_t *tree, node_tree_t *tmp, ptr_balance_t func);

node_tree_t *node_tree_find(node_tree_t *tree, int value, int *compares);

// void node_tree_delete(node_tree_t **tree, char *data);

// работа с элементами стека для хранения адресов узлов
stack_tree_t *stack_tree_create(node_tree_t *data);

stack_tree_t *stack_tree_push(stack_tree_t *head, stack_tree_t *tmp);

node_tree_t *stack_tree_pop(stack_tree_t **head);

// создание дерева выражений
node_tree_t *expr_tree_constructor(char *postfix);

// создание ДДП
node_tree_t *bs_tree_constructor(int *numbers, int amount, ptr_balance_t func);

// функции обхода
void in_order(node_tree_t *tree, ptr_action_t func, void *arg_1, void *arg_2);

void post_order(node_tree_t *tree, ptr_action_t func, void *arg_1, void *arg_2);

void pre_order(node_tree_t *tree, ptr_action_t func, void *arg_1, void *arg_2);

// функция подсчета значения выражения
int tree_calc(node_tree_t *head);

int is_leaf(node_tree_t *head);

void node_count(node_tree_t *tree, void *arg_1, void *arg_2);

void node_value(node_tree_t *tree, void *arg_1, void *arg_2);

int make_bs_numbers_array(node_tree_t *tree, int **bs_numbers);

// определить длину в узле
int tree_height(node_tree_t *tree);

// разница между длинами в ветвях
int balance_factor(node_tree_t *tree);

// записать длину в узел
void fix_height(node_tree_t *tree);

// повернуть направо
node_tree_t *rotate_right(node_tree_t *node_p);

// повернуть налево
node_tree_t *rotate_left(node_tree_t *node_q);

// балансировка
node_tree_t *node_balance(node_tree_t *node_p);

// вставка в балансированное дерево

#endif // __TREE_H__