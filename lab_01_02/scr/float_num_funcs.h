#ifndef __FLOAT_NUM_FUNCS_C__
#define __FLOAT_NUM_FUNCS_C__

int check_num_float(float_num *p_second);                                  // функция для проверки валидности целого числа
int valid_input_float(char *buffer, int *count_signs, int *count_e, int *count_point);        // функция для проверки валидных символов целого числа
int make_float(char *buffer, float_num *p_second, int *current_len, int *current_pow, int *index_sign, int *index_point, int *index_e, int *count_point, int *count_zero, int *shift);           // функция для записи целого числа
int write_float(float_num *p_second, int *current_len, int *current_pow, int *index_sign, int *index_point);

#endif // __FLOAT_NUM_FUNCS_C__