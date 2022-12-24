#ifndef __GRAPH_H__
#define __GRAPH_H__

#include "constants.h"
#include "structures.h"
#include "options.h"

graph_t *graph_create(graph_t *cur_graph, int vertices);

graph_t *graph_copy(graph_t *cur_graph, graph_t *new_graph, int vertex);

node_t *node_create(int vertex);

void node_add(graph_t *cur_graph, int src, int dst);

void dfs(graph_t *cur_graph, int vertex, int *visited);

void graph_free(graph_t *cur_graph);

void list_free(node_t *head);

int count_edges(graph_t *cur_graph);

int graph_check_tree(graph_t *cur_graph);

#endif //__GRAPH_H__