#ifndef __STRUCTURES_H__
#define __STRUCTURES_H__

// Структура для прдедставления очереди в виде массива
typedef struct
{
    int *arr;       // указатель на массив

    int last;      // индекс последнего добавленного элнмента
    int total_size;// размер массива
} arr_queue_t;

// стркутура для одного элемента списка
typedef struct node_s node_t;
// стркутура для одного элемента списка
struct node_s
{
    int inf;        // значение
    node_t *next;   // указатель на следующий элемент
};

// струтура для очереди-список
typedef struct
{
    node_t *first;   // указатель на голову
    node_t *last;    // указатель на хвост

    int cur_size;    // текущий размер
    int total_size;  // полный размер
} list_queue_t;

// структура для массива свободных адресов
typedef struct
{
    int total_size;  // полный размер
    int cur_size;    // текущий размер
    node_t **adresses;  // указатель на массив
} list_adresses_t;

// структура для времени обработки/прихода
typedef struct
{
    double min; // максимальное значение
    double max; // минимальное значение
} times_t;

#endif // __STRUCTURES_H__