#include "../inc/others.h"

void print_menu(void)
{
    printf("\n+-----------------------------------------------+");
    printf("\n|                  Меню                         |");
    printf("\n+----------+------------------------------------+");
    printf("\n|          | *0. Выход из программы             |");
    printf("\n+----------+------------------------------------+");
    printf("\n|  Массив  | 1. Создание очереди вручную        |");
    printf("\n|          |------------------------------------+");
    printf("\n|          | 2. Создание из файла               |");
    printf("\n|          |------------------------------------+");
    printf("\n|          | 3. Добавить элемент                |");
    printf("\n|          |------------------------------------+");
    printf("\n|          | 4. Удалить элемент                 |");
    printf("\n|          |------------------------------------+");
    printf("\n|          | 5. Распечатать очередь             |");
    printf("\n+----------+------------------------------------+");
    printf("\n|  Список  | 6. Создание очереди вручную        |");
    printf("\n|          |------------------------------------+");
    printf("\n|          | 7. Создание из файла               |");
    printf("\n|          |------------------------------------+");
    printf("\n|          | 8. Добавить элемент                |");
    printf("\n|          |------------------------------------+");
    printf("\n|          | 9. Удалить элемент                 |");
    printf("\n|          |------------------------------------+");
    printf("\n|          | 10. Распечатать очередь            |");
    printf("\n|          |------------------------------------+");
    printf("\n|          | 11. Распечатать свободные адреса   |");
    printf("\n+----------+------------------------------------+");
    printf("\n|  Задание | 12. Изменить время обработки заявки|");
    printf("\n|          |------------------------------------+");
    printf("\n|          | 13. Для массива                    |");
    printf("\n|          |------------------------------------+");
    printf("\n|          | 14. Для списка                     |");
    printf("\n|          |------------------------------------+");
    printf("\n|          | 15. Замеры времени и памяти        |");
    printf("\n+----------+------------------------------------+");
    
    printf("\n\nВведите пункт меню: ");
}

void free_all(arr_queue_t *arr_queue, list_queue_t *list_queue, list_adresses_t *list_adresses)
{
    arr_clear(arr_queue);
    list_clear(list_queue);
    list_adresses_clear(list_adresses);
}

long check_file_size(FILE *f)
{
    fseek(f, 0, SEEK_END);
    long size = ftell(f);
    fseek(f, 0, SEEK_SET);

    return size;
}

int input_elem(int *num)
{
    printf("\n*Допустимый значения: [-%d, %d]\n", MAX_ELEM, MAX_ELEM);
   
    printf("\nВведите значение элемента: ");

    if (fscanf(stdin, "%d", num) != 1 || *num < -MAX_ELEM || *num > MAX_ELEM - 1)
        return ERR_WRONG_ELEM;

    return SUCCESS;
}

int cmp_double(double a, double b)
{
    if (fabs(a - b) <= EPS)
        return 0;
    else if (a < (b - EPS))
        return -1;
    else
        return 1;
}
