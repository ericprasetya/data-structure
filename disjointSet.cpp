#include <stdio.h>
#include <stdlib.h>

struct Edge{
  int src, dst;
};

struct Graph{
  int eCount, vCount;
  struct Edge *edge;
};

struct Graph *makeGraph(int vCount, int eCount){
  //alokasi meorinya
  struct Graph *curr = (Graph*) malloc(sizeof(Graph));
  curr->eCount = eCount;
  curr->vCount = vCount;
  curr->edge = (Edge*) malloc(sizeof(Edge) * eCount);
  return curr;
}

int findParent(int parent[], int i){
  if(parent[i] == i){
    return i;
  }else{
    //path compression
    parent[i] = findParent(parent, parent[i]);
    return parent[i];
  }
}

bool isCyclic(Graph *graph){
  //make set
  int parent[graph->vCount];
  for(int i = 0; i< graph->vCount ; i++){
    parent[i]= i;
  }
  for (int i = 0; i < count; i++)
  {
    int src = graph->edge[i].src;
    int dst = graph->edge[i].dst;

    int srcParent = findParent(parent, src);
    int dstParent = findParent(parent, dst);

    if(srcParent == dstParent){
      return true;
    }

    srcParent = dstParent;
  }
  return false;
  

}

int main(){
  const int eCount = 3;
  const int vCount = 4;
  struct Graph *graph = makeGraph(vCount, eCount);
  graph->edge[0].src = 0;
  graph->edge[0].dst = 1;

  graph->edge[1].src = 1;
  graph->edge[1].dst = 2;

  graph->edge[2].src = 2;
  graph->edge[2].dst = 3;

  printf("is graph cyclic? %s", isCyclic(graph)? "Yes" : "No" );
  return 0;
}