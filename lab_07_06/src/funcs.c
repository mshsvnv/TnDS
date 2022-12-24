#include "../inc/funcs.h"

void print_actions(void)
{
    printf("\nДействия:\n");
    printf("          1 - Ввод коэффициентов\n");
    printf("          2 - Запись выражения в дерево выражений\n");
    printf("          3 - Создание ДДП/АВЛ-дерева/Хеш-таблицы\n");
    printf("          4 - Поиск значения в ДДП/АВЛ-дереве/Хеш-таблице\n");
    printf("          5 - Вывод ДДП/АВЛ-дерева в файлы\n");
    printf("          6 - Вывод Хеш-таблиц в файл\n");
    printf("          7 - Сравнение эффективностей СД\n");
    printf("          0 - Выход\n\n");

    printf("Введите выбранный пункт: ");
}

int *input_numbers(int *arr, int amount)
{
    int i, num;

    if (!arr)
        arr = malloc(sizeof(int) * amount);

    if (arr)
    {
        printf("\n* Все значения различны!");
        printf("\n* Диапазон значений: [%d; %d]\n\n", -1 - MAX_ELEM, MAX_ELEM);
        for (i = 0; i < amount; i++)
        {
            printf("Введите %d элемент: ", i + 1);

            if (!fscanf(stdin, "%d", &num) || num > MAX_ELEM || num < -MAX_ELEM - 1)
            {
                free(arr);
                arr = NULL;
                
                return NULL;
            }

            arr[i] = num;
        }
    }

    if (arr != NULL && unique_items(arr, amount))
    {
        free(arr);
        arr = NULL;
    }

    return arr;
}

void make_string(char *dst, char *src)
{
    char *p = dst + strlen(dst);

    while (*src)
        *(p++) = *(src++);
    
    *p = ' ';
}

void insert_numbers(char *postfix, int *numbers, char *res)
{
    int i = 0;

    char *postfix_cur = postfix;
    char buf[20];

    while (*postfix_cur != '\0')
    {
        if (*postfix_cur >= 'a' && *postfix_cur <= 'z')
        {
            sprintf(buf, "%d", numbers[i++]);
            make_string(res, buf);
        }
        else if (*postfix_cur != ' ')
        {
            snprintf(buf, 2, "%c", *postfix_cur);
            make_string(res, buf);
        }
        postfix_cur++;
    }
}

void clean_str(char *str)
{
    size_t i = 0;

    while (i < MAX_LEN)
        str[i++] = '\0';
}

int priority(char *c)
{
    if (!strcmp(c, MUL) || !strcmp(c, DIV))
        return 1;
    if (!strcmp(c, ADD) || !strcmp(c, DIF))
        return 2;
    if (!strcmp(c, BRACE_OP))
        return 3;
    return SUCCESS;
}

int is_operand(char *c)
{
    return priority(c);
}

int process(char op, int left, int right)
{
    char buf[10] = { '\0' };

    buf[0] = op;

    if (!strcmp(buf, ADD))
        return left + right;
    if (!strcmp(buf, DIF))
        return left - right;
    if (!strcmp(buf, MUL))
        return left * right;
    if (!strcmp(buf, DIV))
        return left / right;

    return SUCCESS;
}

int unique_items(int *arr, int amount)
{
    int i, j;

    for (i = 0; i < amount - 1; i++)
    {
        for (j = i + 1; j < amount; j++)
        {
            if (arr[i] == arr[j])
                return ERR_UNIQUE;
        }
    }

    return SUCCESS;
}

int check_prime(int value)
{
    int i;

    for (i = 2; i < value; i++)
    {
        if (value % i == 0)
            return SUCCESS;
    }

    return SUCCESS + 1;
}

int get_next_prime(int value)
{
    int flag = value;

    while (1)
    {
        if (check_prime(value) && value > flag)
            break;
        value++;
    }

    return value;
}

int *random_numbers(int *numbers, int size)
{
    int i;

    numbers = malloc(sizeof(int) * size);

    for (i = 0; i < size; i++)
        numbers[i] = rand() % 100 - 50;

    return numbers;
}
