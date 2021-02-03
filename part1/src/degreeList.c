#include "../inc/degreeList.h"

degreeList dg_create(int _n, int _m)
{
  degreeList dl;
  dl.n = _n;
  dl.m = _m;
  dl.start = 0;
  dl.pointers = (dlEntry**) malloc(_n*sizeof(dlEntry*));
  dl.list = (dlEntry**) malloc(_n*sizeof(dlEntry*));

  int i;
  for (i = 0; i < _n; i++)
  {
    dl.pointers[i] = 0;
    dl.list[i] = 0;
  }
  return dl;
}

void dg_addNode(int _node, int _degree, degreeList* dl)
{
  dlEntry* newEntry = (dlEntry*) malloc(sizeof(dlEntry));
  newEntry->node = _node;
  newEntry->degree = _degree;
  newEntry->left = 0;
  newEntry->right = dl->list[_degree];
  (dl->pointers)[_node] = newEntry;

  dlEntry* temp = dl->list[_degree];
  dl->list[_degree] = newEntry;
  if(temp != 0)
  {
    temp->left = newEntry;
  }
}

void dg_removeNode(int _node, degreeList* dl)
{
  dlEntry* ep = (dl->pointers)[_node];
  dlEntry* _left = ep->left;
  dlEntry* _right = ep->right;

  if (_left == 0)
  {
    (dl->list)[ep->degree] = _right;
  }
  else
  {
    _left->right = _right;
  }

  if (_right != 0)
  {
    _right->left = _left;
  }
  (dl->pointers)[_node] = 0;
  free(ep);
}

void dg_degreeDecrease(int _node, degreeList* dl)
{
  if((dl->pointers)[_node] == 0)
  {
    return;
  }
  int deg = ((dl->pointers)[_node])->degree;
  dg_removeNode(_node, dl);
  dg_addNode(_node, deg - 1, dl);

  if ( (deg - 1) < dl->start)
  {
    (dl->start)--;
  }
  (dl->m)--;
}

double dg_getDensity(degreeList* dl)
{
  if(dl-> n == 0)
  {
    return 0.0;
  }
  return ((double) dl->m) / ((double) dl->n);
}

void dg_moveStart(degreeList* dl)
{
  while ((dl->list)[dl->start] == 0 && dl->start < dl->n)
  {
    (dl->start)++;
  }
}

int dg_removeNodeLowestDegree(degreeList* dl)
{
  dg_moveStart(dl);

  if (dl->n == 0)
  {
    return -1;
  }

  dlEntry *ep = (dl->list)[dl->start];
  int _node = ep->node;
  ep = 0;
  dg_removeNode(_node, dl);

  (dl->n)--;

  return _node;
}

void dg_printList(degreeList* dl)
{
  int i;
  printf("degreeList\n");
  printf("n : %d\n", dl->n);
  printf("dl->start: %d\n", dl->start);
  for (i = 0; i < dl->n; i++)
  {
    if ((dl->list)[i]) printf("\ndegree %d: ", i);
    dlEntry *ep = (dl->list)[i];
    while(ep)
    {
      printf ("%d ", ep->node + 1);
      ep = ep->right;
    }

  }  printf("\n");
}

void dg_delete(degreeList* dl)
{
  free(dl->pointers);
  free(dl->list);
}
