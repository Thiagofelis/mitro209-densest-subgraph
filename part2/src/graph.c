#include "../inc/graph.h"

graph graph_create(int _max_n, int n, int* _nodeInGraph)
{
  graph newGraph;
  newGraph.degree = (int*) malloc(_max_n * sizeof(int));
  newGraph.nodeInGraph = _nodeInGraph;

  int i;
  for (i = 0; i < _max_n; i++)
  {
    newGraph.degree[i] = 0;
  }
  newGraph.n = n;
  newGraph.max_n = _max_n;
  newGraph.m = 0;
  return newGraph;
}

int graph_nodeIsInGraph (int a1, graph* gp)
{
  if (gp->nodeInGraph[a1])
  {
    return 1;
  }
  return 0;
}

void graph_deleteGraph(graph* gp)
{
  free(gp->nodeInGraph);
  free(gp->degree);
}

void graph_addEdge(int a1, int a2, graph* gp)
{
  if (gp->nodeInGraph[a1] && gp->nodeInGraph[a2])
  {
    (gp->degree[a1])++;
    (gp->degree[a2])++;
    (gp->m)++;
  }
}

int* graph_getNodesHighDensity(double bound, int *new_n, graph* gp)
{
  int i;
  int *nodeInNewGraph = (int*) malloc(gp->max_n * sizeof(int));
  *new_n = 0;
  for (i = 0; i < gp->max_n; i++)
  {
    if (gp->nodeInGraph[i] && (double) gp->degree[i] > bound)
    {
      nodeInNewGraph[i] = 1;
      (*new_n)++;
    }
    else
    {
      nodeInNewGraph[i] = 0;
    }
  }
  return nodeInNewGraph;
}

double graph_getDensity(graph* gp)
{
  return (double) gp->m / (double) gp-> n;
}
