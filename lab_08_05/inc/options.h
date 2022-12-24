#ifndef __OPTOINS_H__
#define __OPTOINS_H__

#include "constants.h"
#include "structures.h"
#include "graph.h"

int read_verteces(int *verteces, FILE *f_in);

graph_t *graph_fill(graph_t *graph, FILE *f_in, int *rc);

void export_to_dot(graph_t *graph, FILE *f_out, char *name, int vertex);

void print_menu(void);

long file_size(FILE *f_in);

#endif // __OPTOINS_H__
