#ifndef GRAPH_HEADER
#define GRAPH_HEADER

#include <stdio.h>
#include <stdlib.h>
#include "degreeList.h"

typedef struct edge
{
    int vertex;
    struct edge* next;
} edge;

typedef struct graph
{
    int num_v;
    edge** adj_list;
} graph;

graph graph_create(int _num_v);

void graph_addEdge(graph *gp, int v, int u);

void graph_addSingleEdge(graph *gp, int v, int u);

void graph_print(graph *gp);

void graph_deleteGraph(graph* gp);

int graph_calculateDegree(graph* gp, int node);

int graph_removeNodeLowestDegree(graph *gp, degreeList* dl);

void graph_finalPrint(graph *gp, int* nodeIsPrinted, FILE* fp);

int graph_getFinalNumEdges(graph *gp, int* nodeIsPrinted);

#endif
