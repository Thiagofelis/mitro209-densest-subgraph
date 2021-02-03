
#include "../inc/graph.h"

graph graph_create(int _num_v)
{
	// on the chosen implementation, we allocate an array of edge*.
	// at position i, we put the head of the list of edges incident to node i

    graph new_graph;
    new_graph.num_v = _num_v;
    new_graph.adj_list = (edge**) malloc(_num_v * sizeof(edge*));

    edge* head;
    int i;
    for (i = 0; i < _num_v; i++)
    {
        head = (edge*) malloc(sizeof(edge));
        new_graph.adj_list[i] = head;
        head->vertex = -1;
        head->next = 0;
    }
    return new_graph;
}

void graph_addEdge(graph *gp, int v, int u)
{
    graph_addSingleEdge(gp, v, u);
    graph_addSingleEdge(gp, u, v);
}

void graph_addSingleEdge(graph *gp, int v, int u)
{
    edge* head = (gp->adj_list)[v];
    edge* ep = (edge*) malloc(sizeof(edge));
    ep->vertex = u;
    ep->next = head->next;
    head->next = ep;

}

int graph_calculateDegree(graph* gp, int node)
{
  int d = 0;
  edge* temp = ((gp->adj_list)[node])->next;
  while (temp != 0)
  {
    d++;
    temp = temp->next;
  }
  return d;
}

void graph_print(graph *gp)
{
    int i;
    for (i = 0; i < gp->num_v; i++)
    {
        edge* temp = ((gp->adj_list)[i])->next;
        printf("edges incident to node %d: ", i);
        while (temp != 0)
        {
            printf("(%d to %d), ", i, temp->vertex);
            temp = temp->next;
        }
        printf("\n");
    }
}

void graph_finalPrint(graph *gp, int* nodeIsPrinted, FILE* fp)
{
  int i;
  for (i = 0; i < gp->num_v; i++)
  {
    if (nodeIsPrinted[i])
    {
      edge* temp = ((gp->adj_list)[i])->next;
      while (temp != 0)
      {
        if (i < temp->vertex && nodeIsPrinted[temp->vertex])
        {
          fprintf(fp, "%d %d\n", i+1, temp->vertex+1);
        }
        temp = temp->next;
      }
    }
  }
}

int graph_getFinalNumEdges(graph *gp, int* nodeIsPrinted)
{
  int i;
  int num_edges = 0;
  for (i = 0; i < gp->num_v; i++)
  {
    if (nodeIsPrinted[i])
    {
      edge* temp = ((gp->adj_list)[i])->next;
      while (temp != 0)
      {
        if (i < temp->vertex && nodeIsPrinted[temp->vertex])
        {
          num_edges++;
        }
        temp = temp->next;
      }
    }
  }
  return num_edges;
}

int graph_removeNodeLowestDegree(graph *gp, degreeList* dl)
{

  int v = dg_removeNodeLowestDegree(dl);

  edge* temp = ((gp->adj_list)[v])->next;
  while (temp != 0)
  {
      dg_degreeDecrease(temp->vertex, dl);
      temp = temp->next;
  }
  return v;
}

void graph_deleteGraph(graph* gp)
{
    edge *temp, *temp2;
    int i;
    for (i = 0; i < gp->num_v; i++)
    {
        temp = (gp->adj_list)[i];
        while (temp != 0)
        {
            temp2 = temp;
            temp = temp->next;
            free(temp2);
        }
    }
    free(gp->adj_list);
}
