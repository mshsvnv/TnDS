#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>
#include "defs.h"
#include "typedefs.h"

void info(void)
{
    printf("________________________________INFO___________________________________\n");
    printf("|                                                                     |\n");
    printf("| 1. знак числа может быть как указан, так и нет                      |\n");
    printf("| 2. вещественное число можно вводить как с точкой, так и без         |\n");
    printf("| 3. вещественное число можно вводить как с порядком, так и без       |\n");
    printf("| 4. в вещественном числе после точки может идти только 1 \"0\"         |\n");
    printf("| 5. в вещественном числе до точки может идти только 1 \"0\"            |\n");
    printf("| 6. в целом числе может идти только 1 \"0\"                            |\n");
    printf("| 7. в порядке вещественного числа может быть только 1 значащий \"0\"   |\n");
    printf("|                                                                     |\n");
    printf("| Примеры корректного ввода:                                          |\n");
    printf("| -целое число: 1; +1; -1; 100; 0                                     |\n");
    printf("| -вещественное число: 1; +1; -1; 1.0; 1e0; 1e+0 0e0                  |\n");
    printf("|                                                                     |\n");
    printf("| Примеры некорректного ввода:                                        |\n");
    printf("| -целое число: ; ++1; aaa; 10.0;                                     |\n");
    printf("| -вещественное число: 0.00; 1.00; 1e08                               |\n");
    printf("|_____________________________________________________________________|\n\n");

}

void fill_buffer(char *buffer)   // функция для ввода чисел
{
    char tmp = fgetc(stdin);
    size_t i =  0;

    while (tmp != '\n')          // ввод чисел оканчивается символом 
    {                            // перехода на новую строку
        buffer[i] = tmp;
        i++;
        tmp = fgetc(stdin);
    }

    buffer[i] = '\0';
}

void shift(int *buffer, int *current_len)  // функция сдвига массива вправо при условии,
{                                           // что первый элемент больше 10
    int i, tmp;

    while (buffer[0] > 9)                   // пока первый элемент массива больше 9,
    {                                       // то сдвигаем оставшийся массив вправо
        for (i = *current_len; i > 1; i--)
        {
            tmp = buffer[i];
            buffer[i] = buffer[i - 1];
            buffer[i - 1] = tmp;
        }

        (*current_len)++;

        buffer[1] = buffer[0] % BASE;
        buffer[0] = buffer[0] / BASE;
    }
}

void output_res(float_num *res)    // функция для вывода итогового числа
{
    int i;
    char s = (res->sign == 1) ? PLUS : MINUS;
    
    if (res->len == 0)
        printf("\nTotal result : 0.0E0\n");
    else
    {
        printf("\nTotal result : %c0.", s);

        for (i = 0; i < res->len; i++)
            printf("%d", res->numbers[i]); 
        
        printf("E%d\n", res->power);
    }
}