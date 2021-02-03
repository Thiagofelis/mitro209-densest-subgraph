#include <stdio.h>
#include <stdlib.h>

#include "../inc/graph.h"
#include "../inc/degreeList.h"
#include "../inc/auxfunc.h"

int main(int argc, char* argv[])
{
  // checks if the correct number of arguments was given
  if (argc != 3)
  {
    printf("Should Be Like ./tp inputFileName.txt outputFileName.txt\n");
    return 1;
  }

  FILE* fp = fopen(argv[1], "r");
  FILE* out = fopen(argv[2], "w");
  if(fp == 0 || out == 0)
  {
      printf("file doesnt exist");
      return 0;
  }

// reads the graph
  char buffer[20];
  read(fp, buffer);
  int num_nodes = atoi(buffer);

  read(fp, buffer);
  int num_edges = atoi(buffer);

  graph *gp = (graph*) malloc(sizeof(graph));
  *gp = graph_create(num_nodes);
  int i, node_a, node_b;
  for (i = 0; i < num_edges; i++)
  {
      read(fp, buffer);
      node_a = atoi(buffer);
      read(fp, buffer);
      node_b = atoi(buffer);
      graph_addEdge(gp, node_a - 1, node_b - 1);
    // ^ on the file, nodes go from 1 to n
  }

  //removalList: on position i, the node that was removed in step i
  int* removalList = (int*) malloc(num_nodes*sizeof(int));
  //densitiesList: on position i, the graph density AFTER step i
  double* densitiesList = (double*) malloc(num_nodes*sizeof(double));

  // creates the degreeList
  degreeList dList = dg_create(num_nodes, num_edges);
  for (i = 0; i < num_nodes; i++)
  {
    dg_addNode(i, graph_calculateDegree(gp, i), &dList);
  }

  // at each step, we remove the node with lowest degree
  for(i = 0; i < num_nodes; i++)
  {
    removalList[i] = graph_removeNodeLowestDegree(gp, &dList);
    densitiesList[i] = dg_getDensity(&dList);
  }

  // greatestDensity = -1 represents the density BEFORE step 0
  // (in other words, of the original graph)
  int greatestDensity = -1;
  double greatestDensityValue = (double) num_edges / (double) num_nodes;

  // calculates the step in which the density was the greatest
  for (i = 0; i < num_nodes; i++)
  {
    if (densitiesList[i] > greatestDensityValue)
    {
      greatestDensity = i;
      greatestDensityValue = densitiesList[i];
    }
  }

  // calculates the nodes in the solution
  int* nodeIsInSolution = (int*) malloc(num_nodes*sizeof(int));
  for (i = 0; i < num_nodes; i++)
  {
    nodeIsInSolution[i] = 1;
  }
  int newNumNodes = num_nodes;
  for (i = 0; i < num_nodes; i++)
  { // if node was removed from the graph before the step in which the density
    // was the greatest, then its not on the solution
    if(i <= greatestDensity)
    {
      nodeIsInSolution[removalList[i]] = 0;
      newNumNodes--;
    }
  }
  int newNumEdges = graph_getFinalNumEdges(gp, nodeIsInSolution);

  // prints the graph
  fprintf(out, "%d %d\n", newNumNodes, newNumEdges);
  graph_finalPrint(gp, nodeIsInSolution, out);


  // uncomment to see removalList and densitiesList
/*printf("removal list and densities:\n");
  for(i = 0; i < num_nodes; i++)
  {
    printf("%d %f\n", removalList[i]+1, densitiesList[i]);
  }*/

  graph_deleteGraph(gp);
  free(gp);
  dg_delete(&dList);
  free(removalList);
  free(densitiesList);
  free(nodeIsInSolution);

  fclose(fp);
  fclose(out);
  return 0;
}
