#ifndef DEGREELIST_HEADER
#define DEGREELIST_HEADER

#include <stdio.h>
#include <stdlib.h>

typedef struct dlEntry
{
  struct dlEntry* left;
  struct dlEntry* right;
  int node;
  int degree;
} dlEntry;

typedef struct degreeList
{
  dlEntry **list;
  dlEntry **pointers;
  int start;
  int n;
  int m;
} degreeList;

degreeList dg_create(int _n, int _m);

void dg_addNode(int _node, int _degree, degreeList* dl);

void dg_removeNode(int _node, degreeList* dl);

void dg_degreeDecrease(int _node, degreeList* dl);

double dg_getDensity(degreeList* dl);

int dg_removeNodeLowestDegree(degreeList* dl);

void dg_moveStart(degreeList* dl);

void dg_printList(degreeList* dl);

void dg_delete(degreeList* dl);

#endif
