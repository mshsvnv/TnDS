#ifndef __INT_NUM_FUNCS_C__
#define __INT_NUM_FUNCS_C__

int check_num_int(int_num *p_first);                                       // функция для проверки валидности действительного числа
int valid_input_int(char *buffer, int *current_len, int *index_sign);        // функция для проверки валидных символов целого числа
void write_int(char *buffer, int_num *p_first, int *current_len);             // функция для записи целого числа

#endif // __INT_NUM_FUNCS_C__