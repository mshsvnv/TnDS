#ifndef __FUNCS_H__ 
#define __FUNCS_H__

#include "constants.h"
#include "structures.h"

void print_actions(void);

void print_value(int value, char *arg);

int input_amount(int *amount);

int *input_numbers(int *arr, int amount);

void make_string(char *dst, char *src);

void insert_numbers(char *postfix, int *numbers, char *res);

void clean_str(char *str);

int is_operand(char *c);

int priority(char *c);

int process(char *op, int left, int right);

int unique_items(int *arr, int amount);

#endif // __FUNCS_H__