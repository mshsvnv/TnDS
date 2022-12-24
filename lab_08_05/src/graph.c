#include "../inc/graph.h"

graph_t *graph_create(graph_t *cur_graph, int vertices)
{
    int i;

    cur_graph = malloc(sizeof(graph_t) * vertices);

    if (cur_graph)
    {
        cur_graph->num_vertex = vertices;

        cur_graph->head = malloc(sizeof(node_t *) * vertices);

        for (i = 0; i < vertices; i++)
            cur_graph->head[i] = NULL;
    }

    return cur_graph;
}

graph_t *graph_copy(graph_t *cur_graph, graph_t *new_graph, int vertex_to_del)
{
    int i;
    node_t *tmp = NULL;

    for (i = 0; i < cur_graph->num_vertex; i++)
    {
        if (cur_graph->head[i] && i != vertex_to_del)
        {
            tmp = cur_graph->head[i];

            while (tmp)
            {
                if (tmp->vertex != vertex_to_del && i < tmp->vertex)
                    node_add(new_graph, i, tmp->vertex);
                
                tmp = tmp->next;
            }
        }
    }

    return new_graph;
}

node_t *node_create(int vertex)
{
    node_t *tmp = malloc(sizeof(node_t));

    if (tmp)
    {
        tmp->vertex = vertex;
        tmp->next = NULL;
    }

    return tmp;
}

void node_add(graph_t *cur_graph, int src, int dst)
{
    node_t *tmp = node_create(dst);
    tmp->next = cur_graph->head[src];
    cur_graph->head[src] = tmp;

    tmp = node_create(src);
    tmp->next = cur_graph->head[dst];
    cur_graph->head[dst] = tmp;   
}

void dfs(graph_t *cur_graph, int vertex, int *visited)
{
    node_t *tmp = cur_graph->head[vertex];
    visited[vertex] = 1;

    while (tmp)
    {
        if (visited[tmp->vertex] == 0)
            dfs(cur_graph, tmp->vertex, visited);
        tmp = tmp->next;
    }
}

void list_free(node_t *head)
{
    node_t *tmp = NULL;

    while(head)
    {
        tmp = head;
        head = head->next;

        free(tmp);
    }
}

void graph_free(graph_t *cur_graph)
{
    int i;

    if (cur_graph)
    {
        for (i = 0; i < cur_graph->num_vertex; i++)
            list_free(cur_graph->head[i]);

        free(cur_graph->head);
        free(cur_graph);
    }
}

int graph_check_tree(graph_t *cur_graph)
{
    int vertex_to_del, i, rc;
    int *visited = NULL;
    char file_name[30];

    graph_t *new_graph = NULL;
    
    FILE *f_out;

    char *name = "result_graph";

    for (vertex_to_del = 0; vertex_to_del < cur_graph->num_vertex; vertex_to_del++)
    {
        rc = SUCCESS;

        new_graph = graph_create(new_graph, cur_graph->num_vertex);

        if (!new_graph)
            return ERR_MEMORY;

        new_graph = graph_copy(cur_graph, new_graph, vertex_to_del);

        visited = calloc(new_graph->num_vertex, sizeof(int));

        dfs(new_graph, (vertex_to_del + 1) % cur_graph->num_vertex, visited);

        for (i = 0; i < new_graph->num_vertex; i++)
        {
            if (visited[i] == 0 && i != vertex_to_del)
            {
                printf("\nГраф, с убранной %d вершиной, не связный!\n", vertex_to_del);
                rc = ERR_NO_CONNECT;
                break;
            }
        }

        if (count_edges(new_graph) + 1 != new_graph->num_vertex - 1 && !rc)
        { 
            printf("\nГраф, с убранной %d вершиной, имеет циклы!\n", vertex_to_del);
            rc = ERR_NO_TREE;
        }
        else if (!rc)
            printf("\nГраф, с убранной %d вершиной, является деревом!\n", vertex_to_del);

        sprintf(file_name, "result_graph_%d.gv", vertex_to_del);

        f_out = fopen(file_name, "wb");

        export_to_dot(new_graph, f_out, name, vertex_to_del);

        fclose(f_out);
        
        free(visited);
        graph_free(new_graph);
    }

    return SUCCESS;
}

int count_edges(graph_t *cur_graph)
{
    int i, count_edges;
    node_t *tmp = NULL;

    count_edges = 0;

    for (i = 0; i < cur_graph->num_vertex; i++)
    {
        tmp = cur_graph->head[i];

        while (tmp)
        {
            count_edges += (tmp->vertex > i) ? 1 : 0;
            tmp = tmp->next;
        }
    }

    return count_edges;
}