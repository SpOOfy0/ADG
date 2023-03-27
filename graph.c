#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <assert.h>
#include "graph.h"


Graph *graphAlloc(int numVertex)
{
    // Allouer de la mémoire pour le graphe et initialiser tous les pointeurs à NULL
    Graph* graph = (Graph*) malloc(sizeof(Graph));
    graph->numVertex = numVertex;
    graph->visited = (int*) malloc(numVertex * sizeof(int));
    graph->adjLists = (node**) malloc(numVertex * sizeof(node*));

    // Initialiser le tableau des listes d'adjacence à NULL pour chaque sommet
    for (int i = 0; i < numVertex; i++) {
        graph->visited[i] = 0;
        graph->adjLists[i] = NULL;
    }
    return graph;
}

node *nodeAlloc()
{
  node *node;

  node = malloc( sizeof(node) );
  assert(node);

  node->vertex = 0;
  node->next = NULL;

  return node;
}

/*Graph *graphCreat(int **Matrix, int Size)
{
    Graph* graph = graphAlloc(Size);
    graph->numVertex = Size;
    node *node = nodeAlloc();
    node *tmp = nodeAlloc();
    
    for(int i=0; i<Size; i++)
    {
        for(int j=0; j<Size; j++)
        {
            if (Matrix[i][j]==1)
            {
                node->vertex=j;
                node->next=NULL;
                if (graph->adjLists[i]==NULL)
                {
                graph->adjLists[i]=node;
                }
                else
                {
                    tmp=graph->adjLists[i];
                    while(tmp->next!=NULL)
                        tmp->next=tmp->next->next;
                    tmp->next=node;
                    
                }
            }
        }
    }
    return graph;
}*/

Graph *graphCreat(int **Matrix, int Size)
{
    Graph* graph = graphAlloc(Size);
    graph->numVertex = Size;
    
    for(int i = 0; i < Size; i++)
    {
        node *head = NULL; // liste d'adjacence vide pour ce sommet
        node **tail = &head; // pointeur vers la dernière cellule de la liste
        
        for(int j = 0; j < Size; j++)
        {
            if (Matrix[i][j] == 1)
            {
                node *new_node = nodeAlloc();
                new_node->vertex = j;
                new_node->next = NULL;
                
                *tail = new_node;
                tail = &new_node->next;
            }
        }
        
        graph->adjLists[i] = head;
    }
    
    return graph;
}
