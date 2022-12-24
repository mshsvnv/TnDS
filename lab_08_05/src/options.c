#include "../inc/options.h"

void print_menu(void)
{
    printf("\n             :: Меню ::\n\n");
    printf("1 - Прочитать граф из файла;\n");
    printf("2 - Проверка графа на дерево;\n");
    printf("3 - Запись графа в файл;\n");
    printf("0 - Выход из программы;\n\n");
    printf("Введите выбранный пункт: ");
}

int read_verteces(int *verteces, FILE *f_in)
{
    if (fscanf(f_in, "%d", verteces) != 1 || *verteces <= 0)
    {
        printf("\nНеверное кол-во вершин графа!\n");
        return ERR_WRONG_AMOUNT;
    }

    return SUCCESS;
}

graph_t *graph_fill(graph_t *cur_graph, FILE *f_in, int *rc)
{
    int verteces, src, dst;

    *rc = read_verteces(&verteces, f_in);

    if (*rc)
        return NULL;

    cur_graph = graph_create(cur_graph, verteces);

    while (! feof(f_in))
    {
        if (fscanf(f_in, "%d %d", &src, &dst) != 2 || src < 0 || dst < 0 || src == dst \
        || src >= cur_graph->num_vertex || dst >= cur_graph->num_vertex)
        {
            printf("\nНет доступной вершины графа!\n");
            *rc = ERR_WRONG_VERTEX;
            break;
        }

        node_add(cur_graph, src, dst);
    }

    if (*rc)
    {
        graph_free(cur_graph);
        cur_graph = NULL;
    }

    return cur_graph;
}

void export_to_dot(graph_t *cur_graph, FILE *f_out, char *name, int vertex)
{
    int i;
    node_t *tmp = NULL;

    fprintf(f_out, "graph %s {\ngraph [ordering=\"out\"];\n", name);

    for (i = 0 ; i < cur_graph->num_vertex; i++)
    {
        if (cur_graph->head[i])
        {
            tmp = cur_graph->head[i];

            while (tmp)
            {
                if (i < tmp->vertex)
                    fprintf(f_out, "%d -- %d;\n", i, tmp->vertex);
                tmp = tmp->next;
            }
        }
        else if (i != vertex)
            fprintf(f_out, "%d;\n", i);
    }

    fprintf(f_out, "}\n");
}

long file_size(FILE *f_in)
{
    long size;

    fseek(f_in, 0, SEEK_END);
    size = ftell(f_in);
    fseek(f_in, 0, SEEK_SET);

    return size;
}