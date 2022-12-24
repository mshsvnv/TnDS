#ifndef __STRUCTURES_H__
#define __STRUCTURES_H__

typedef struct node node_t;

struct node
{
    int vertex;
    node_t *next;
};

typedef struct
{
    int num_vertex;
    node_t **head;
} graph_t;

#endif // __STRUCTURES_H__