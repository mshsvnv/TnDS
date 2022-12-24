#ifndef __PRINT_FUNCS_H__
#define __PRINT_FUNCS_H__

void print_menu(void);
int print_table(flat_t *flats, int *count);
int print_keys(keys_t *keys, int *count);
void print_struct(int *num, flat_t *tmp);
void print_hat(void);
int print_table_by_keys(flat_t *flats, keys_t *keys, int *count);

#endif //__PRINT_FUNCS_H__