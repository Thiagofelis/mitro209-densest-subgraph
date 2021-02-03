#include <stdio.h>
#include <stdlib.h>

typedef struct _graph {
  int *nodeInGraph;
  int* degree;
  int n;
  int max_n;
  int m;
} graph;

typedef struct gl {
  struct gl* next;
  graph g;
  double density;
}graphList;

int graph_nodeIsInGraph (int a1, graph* gp);

graph graph_create(int _max_n, int n, int* _nodeInGraph);

void graph_addEdge(int a1, int a2, graph* gp);

int* graph_getNodesHighDensity(double bound, int *new_n, graph* gp);

double graph_getDensity(graph* gp);

void graph_deleteGraph(graph* gp);
