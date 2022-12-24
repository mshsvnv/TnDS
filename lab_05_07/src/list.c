#include "../inc/list.h"

int list_queue_create(list_queue_t **list_queue, FILE *f_in, int test_size)
{
    int size;

    (*list_queue) = malloc(sizeof(list_queue_t));

    if (! *list_queue)
        return ERR_MEMORY;

    (*list_queue)->first = NULL;
    (*list_queue)->last = NULL;
    (*list_queue)->cur_size = 0;
    (*list_queue)->total_size = 0;

    if (test_size == -1)
    {
        if (f_in == stdin)
            printf("\n*Допустимый значения: [1, %d]\nВведите размер очереди: ", MAX_ELEMS);

        if (fscanf(f_in, "%d", &size) != 1 || size < 1 || size > MAX_ELEMS)
            return ERR_WRONG_SIZE;
    }
    else    
        size = test_size;

    (*list_queue)->total_size = size;

    return SUCCESS;
}

int list_queue_fill(list_queue_t **list_queue, FILE *f_in)
{
    int i, elem;
    node_t *tmp;

    if (f_in == stdin)
        printf("\n*Допустимый значения: [-%d, %d]\n", MAX_ELEM, MAX_ELEM - 1);

    for (i = 0; i < (*list_queue)->total_size; i++)
    {
        if (f_in == stdin)
            printf("Введите значение элемента: ");

        if (fscanf(f_in, "%d", &elem) != 1 || elem < -MAX_ELEM || elem > MAX_ELEM - 1)
            return ERR_WRONG_ELEM;

        tmp = node_create(&elem);
        list_push(list_queue, tmp);
    }

    return SUCCESS;
}

int list_is_full(list_queue_t *list_queue)
{
    return (list_queue->cur_size == list_queue->total_size) ? ERR_OVER : SUCCESS;
}

int list_is_empty(list_queue_t *list_queue)
{
    return (list_queue->cur_size == 0) ? ERR_EMPTY : SUCCESS;
}

void list_push(list_queue_t **list_queue, node_t *new_node)
{
   // node_t *tmp = (*list_queue)->first;

    if (!(*list_queue)->first)
    {
        (*list_queue)->first = new_node;
        (*list_queue)->last = (*list_queue)->first;
        (*list_queue)->cur_size++;
    }
    else
    {
        // while (tmp->next)
        //     tmp = tmp->next;

        // tmp->next = new_node;
        (*list_queue)->last->next = new_node;
        (*list_queue)->last = (*list_queue)->last->next;
        (*list_queue)->cur_size++;
    }
}

node_t *list_pop(list_queue_t *list_queue)
{
    node_t *first = list_queue->first;
    list_queue->first = list_queue->first->next;

    list_queue->cur_size--;

    return first;
}

void list_clear(list_queue_t *list_queue)
{
    node_t *tmp = NULL, *cur = NULL;

    if (list_queue)
    {
        cur = list_queue->first;
        
        while (cur)
        {
            tmp = cur;
            cur = cur->next;
            free(tmp);
        }

        list_queue->first = NULL;
        list_queue->last = NULL;

        free(list_queue);

        list_queue = NULL;
    }
}

node_t *node_create(int *elem)
{
    node_t *new = malloc(sizeof(node_t));

    if (!new)
        return NULL;

    new->inf = *elem;
    new->next = NULL;

    return new;
}

void list_print(list_queue_t *list_queue)
{
    node_t *tmp = list_queue->first;

    for (; tmp; tmp = tmp->next)
    {
        printf("\n+--------+----------------+---------------+\n");
        if (tmp == list_queue->first)
            printf("%s| Верх:  ", MAGENTA);
        else if (tmp == list_queue->last)
            printf("%s| Хвост: ", MAGENTA);
        else
            printf("%s|        ", MAGENTA);

        printf("| Значение:      |%15d|%s\n", tmp->inf, RESET);
        printf("|        +----------------+---------------+\n");
        printf("|        | Текущий адрес: |%15p|\n", (void *)tmp);
        printf("+--------+----------------+---------------+\n");
    }
}

void list_adresses_clear(list_adresses_t *list_adresses)
{
    if (list_adresses)
    {
        free(list_adresses->adresses);

        list_adresses->adresses = NULL;

        free(list_adresses);

        list_adresses = NULL;
    }
}

int list_adresses_init(list_adresses_t **list_adresses)
{
    *list_adresses = malloc(sizeof(list_adresses_t));

    if (!(*list_adresses))
        return ERR_MEMORY;

    (*list_adresses)->cur_size = 0;
    (*list_adresses)->total_size = 10;

    (*list_adresses)->adresses = malloc(sizeof(node_t *) * (*list_adresses)->total_size);
    
    if (!(*list_adresses)->adresses)
        return ERR_MEMORY;

    return SUCCESS;
}

void list_adresses_expand(list_adresses_t *list_adresses)
{
    list_adresses->total_size += 10;
    
    void *p = realloc(list_adresses->adresses, sizeof(node_t *) * list_adresses->total_size);

    if (p)
        list_adresses->adresses = p;
}

void list_adresses_add(list_adresses_t *list_adresses, node_t *tmp)
{
    list_adresses->adresses[list_adresses->cur_size++] = tmp;

    printf("\n+----------------+---------------+\n");
    printf("%s| Значение       |%15d|%s\n", MAGENTA, tmp->inf, RESET);
    printf("+----------------+---------------+\n");
    printf("| Текущий адрес: |%15p|\n", (void *)tmp);
    printf("+----------------+---------------+\n");
}

void list_adresses_del(list_adresses_t *list_adresses, node_t *tmp)
{
    int i, k;

    for (i = 0; i < list_adresses->cur_size; i++)
    {
        if (list_adresses->adresses[i] == tmp)
        {
            for (k = i ; k < list_adresses->cur_size - 1; i++)
                list_adresses->adresses[i] = list_adresses->adresses[i + 1];

            list_adresses->cur_size--;
            break;
        }
    }
}

void list_adresses_print(list_adresses_t *list_adresses)
{
    printf("\n+------------------+\n");
    printf("| Свободные адреса |\n");
    printf("+------------------+\n");

    int i;

    for (i = 0; i < list_adresses->cur_size; i++)
    {
        printf("|%18p|\n", (void *)list_adresses->adresses[i]);
        printf("+------------------+\n");
    }
}