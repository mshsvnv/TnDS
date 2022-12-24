#ifndef __STACK_H__ 
#define __STACK_H__

#include "constants.h"
#include "structures.h"
#include "funcs.h"

node_stack_t *node_stack_create(char *data);

node_stack_t *stack_push(node_stack_t *head, node_stack_t *tmp);

int stack_is_empty(node_stack_t *head);

char *stack_pop(node_stack_t **head);

void stack_free(node_stack_t *head);

//void stack_print(node_stack_t *head);

char *stack_top(node_stack_t *head);

int len(node_stack_t *head);

void conv_postfix(char *infix, char *postfix);

//int stack_calc(char *copy_postfix);

#endif // __STACK_H__