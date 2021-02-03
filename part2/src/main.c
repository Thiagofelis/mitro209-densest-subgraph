#include <stdlib.h>
#include <stdio.h>
#include "../inc/graph.h"
#include "../inc/auxfunc.h"

int main(int argc, char** argv)
{
  // checks if the correct number of arguments was given
  if (argc != 4)
  {
    printf("Should Be Like ./tp epsilon inputFileName.txt outputFileName.txt\n");
    return 1;
  }

  FILE* fp = fopen(argv[2], "r");
  if(fp == 0)
  {
      printf("file doesnt exist");
      return 0;
  }
  int i, node_a, node_b;

  double epsilon = atof(argv[1]);

  char buffer[20];
  read(fp, buffer);
  int num_nodes = atoi(buffer);

  read(fp, buffer);
  int num_edges = atoi(buffer);

  int* nodesInGraph = (int*) malloc(sizeof(int) * num_nodes);
  for (i = 0; i < num_nodes; i++)
  {
    nodesInGraph[i] = 1;
  }

  graphList* gl = 0;

  fclose(fp);

  int new_n = num_nodes;
/* ---------START--------- */
  do{
    // open input file
    fp = fopen(argv[2], "r");
    // jumps first line
    read(fp, buffer);
    read(fp, buffer);

    graph g = graph_create(num_nodes, new_n, nodesInGraph);
    for (i = 0; i < num_edges; i++)
    {
        read(fp, buffer);
        node_a = atoi(buffer);
        read(fp, buffer);
        node_b = atoi(buffer);
        graph_addEdge(node_a - 1, node_b - 1, &g);
      // ^ on the file, nodes go from 1 to n
    }
    double density = graph_getDensity(&g);

    graphList *cell = (graphList*) malloc(sizeof(graphList));
    cell->next = gl;
    cell->g = g;
    cell->density = density;
    gl = cell;
    
    nodesInGraph = graph_getNodesHighDensity(2.0 * (1.0 + epsilon) * density, &new_n, &g);
    fclose(fp);
  } while(new_n);

  free(nodesInGraph);

  graph finalGraph = gl->g;
  int maxDensity = gl->density;
  graphList* cell = gl;
  gl = gl->next;
  free(cell);

  while(gl)
  {
    if(gl->density > maxDensity)
    {
      graph_deleteGraph(&finalGraph);
      finalGraph = gl->g;
      maxDensity = gl->density;
      cell = gl;
      gl = gl->next;
      free(cell);
    }
    else
    {
      graph_deleteGraph(&(gl->g));
      cell = gl;
      gl = gl->next;
      free(cell);
    }
  }

  fp = fopen(argv[2], "r");
  FILE* out = fopen(argv[3], "w");
  // jumps first line
  read(fp, buffer);
  read(fp, buffer);

  fprintf(out, "%d %d\n", finalGraph.n, finalGraph.m);

  for (i = 0; i < num_edges; i++)
  {
      read(fp, buffer);
      node_a = atoi(buffer);
      read(fp, buffer);
      node_b = atoi(buffer);

      if (graph_nodeIsInGraph(node_a - 1, &finalGraph) && graph_nodeIsInGraph(node_b - 1, &finalGraph))
      {
        fprintf(out, "%d %d\n", node_a, node_b);
      }
    // ^ on the file, nodes go from 1 to n
  }
  fclose(fp);
  fclose(out);
  graph_deleteGraph(&finalGraph);

  return 0;
}
