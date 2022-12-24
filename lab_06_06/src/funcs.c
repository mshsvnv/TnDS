#include "../inc/funcs.h"

void print_actions(void)
{
    printf("\nДействия :\n");
    printf("\nС деревом выражения :\n");
    printf("          1. Ввод коэффициентов\n");
    printf("          2. Запись выражения в дерево\n");
    printf("          3. Вычисление выражения с помощью дерева\n");
    printf("          4. Вычисление выражения с помощью стека\n");
    printf("          5. Сравнение вычисления выражения\n");
    printf("          6-8. Префиксный/инфиксный/постфиксный обход дерева\n");
    printf("          9. Вывод дерева в файл\n");
    printf("\nС ДДП :\n");
    printf("          10. Создание дерева\n");
    printf("          11. Поиск значения\n");
    printf("          12. Добавление узла\n");
    printf("          13. Удаление узла\n");
    printf("          14-16. Префиксный/инфиксный/постфиксный обход дерева\n");
    printf("          17. Вывод дерева в файл\n");
    printf("          0. Выход\n\n");

    printf("Введите выбранный пункт: ");
}


int input_amount(int *amount)
{
    printf("*Диапазон значений: [1; %d]\n", MAX_LEN);
    printf("Введите кол-во элементов в дереве: ");

    if (fscanf(stdin, "%d", amount) != 1 || *amount <= 0 || *amount > MAX_LEN)
    {
        printf("Неверное значение!\n");
        return ERR_NUMBERS;
    }

    return SUCCESS;
}

int *input_numbers(int *arr, int amount)
{
    int i, num;

    if (!arr)
        arr = malloc(sizeof(int) * amount);

    if (arr)
    {
        printf("*Диапазон значений: [%d; %d]\n", -1 - MAX_ELEM, MAX_ELEM);
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

int process(char *op, int left, int right)
{
    if (!strcmp(op, ADD))
        return left + right;
    if (!strcmp(op, DIF))
        return left - right;
    if (!strcmp(op, MUL))
        return left * right;
    if (!strcmp(op, DIV))
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