#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <sys/param.h>
#include <assert.h>
#include "graph.h"
#include "outils.h"

// Partie 1 :

int **GenerationMatrice(int taille, float p, int oriente)
{
    float v;
    float u;
    int **matrice = CreationMatrice(taille);
    for(int i=0;i<taille;i=i+1)
    {
        for(int j=0;j<taille;j=j+1)
        {
            
            v=rand()%RAND_MAX;
            u=v/RAND_MAX;
            if(u<p)
            {
                matrice[i][j]=1;
            }
            else
            {
                matrice[i][j]=0;
            }
        }
    }
    if(oriente==1)
    {
        for(int i=0;i<taille;i=i+1)
        {
             for(int j=0;j<taille;j=j+1)
             {
                matrice[i][j]=matrice[j][i];
             }
        }
    }
    return matrice;
}


int DegresGraphes(int **matrice,int taille)
{
    int degres = 0;
    int nb = 0;
    for(int i=0;i<taille;i=i+1)
    {
        for(int j=0;j<taille;j=j+1)
        {
            if(matrice[i][j]==1)
            {
                nb=nb+1;
            }
        }
        
        if(degres<nb)
        {
            degres=nb;
        }
        nb = 0;
    }
    return degres;
}


int **ProduitMatriceConnexite(int **matrice1, int **matrice2, int taille)
{
    int **newMatrice =CreationMatrice(taille);

    for(int i=0;i<taille;i=i+1)
    {
        for(int j=0;j<taille;j=j+1)
        {
            newMatrice[i][j]=0;
            for(int n=0;n<taille;n=n+1)
            {
                newMatrice[i][j]=max(newMatrice[i][j],matrice1[i][n]*matrice2[n][j]);
            }
        }
    }
    return newMatrice;
}


int** Connexite(int **matrice, int taille)
{
    int **newMatrice=CopieMatrice(matrice,taille);
    int **newMatrice2;

    DiagonalMatriceUn(newMatrice,taille);
    newMatrice2=CopieMatrice(newMatrice,taille);  
    newMatrice=ProduitMatriceConnexite(newMatrice,newMatrice,taille);

    for(int i=2;i<taille;i=i+1)
    {
        newMatrice=ProduitMatriceConnexite(newMatrice2,newMatrice,taille);
    }
    return newMatrice;
}


void EstConnexe(int **matrice, int taille)
{
    int **M=Connexite(matrice,taille);
    int connexe = 1;
    for(int i=0; i<taille;i=i+1)
    {
        for(int j=0;j<taille;j=j+1)
        {
            if(M[i][j]!=1) connexe=0;
        }
    }
    if(connexe==1) printf("Ce graphe est connexe");
    else printf("Ce graphe n'est pas connexe");
}


int **ProduitMatriceFloyd(int **matrice1, int **matrice2, int taille)
{
    int **newMatrice = CreationMatrice(taille);

    for(int i=0;i<taille;i=i+1)
    {
        for(int j=0;j<taille;j=j+1)
        {
            newMatrice[i][j]=matrice1[i][j];
            for(int n=0;n<taille;n=n+1)
            {
                newMatrice[i][j]=min(newMatrice[i][j],matrice1[i][n]+matrice2[n][j]);
            }
        }
    }
    return newMatrice;
}


int** PlusCourtChemin(int **matrice, int taille)
{
    int **newMatrice = CreationMatrice(taille);
    int **newMatrice2;

    for(int i=0;i<taille;i=i+1)
    {
        for(int j=0;j<taille;j=j+1)
        {

            if(matrice[i][j]==0)
            {
                newMatrice[i][j]=50000;
            }
            else
            {
                newMatrice[i][j]=matrice[i][j];
            }
        }
    }
    DiagonalMatriceZero(newMatrice,taille);
    newMatrice2=CopieMatrice(newMatrice,taille);
    newMatrice=ProduitMatriceFloyd(newMatrice,newMatrice,taille);

    for(int i=2;i<taille;i=i+1)
    {
        newMatrice=ProduitMatriceFloyd(newMatrice2,newMatrice,taille);
    }

    return newMatrice;
}

//Partie 2 :

queue *createQueue() {
    queue *q = malloc(sizeof(queue));
    q->front = -1;
    q->rear = -1;
    return q;
}

// Checks for empty queue
int isEmpty(queue *q) {
    if (q->rear == -1)
        return 1;
    else
        return 0;
}
// Inserts item at start of queue
void enqueue(queue *q, int value) {
    if (q->rear == SIZE - 1)
        printf("\nQueue is Full!!");
    else {
        if (q->front == -1)
            q->front = 0;
        q->rear++;
        q->items[q->rear] = value;
    }
}

// Returns item at front of queue and removes it from queue
int dequeue(queue *q) {
    int item;
    if (isEmpty(q)) {
        printf("Queue is empty");
        item = -1;
    }
    else {
        item = q->items[q->front];
        q->front++;
        if (q->front > q->rear) {
            q->front = q->rear = -1;
        }
    }
    return item;
}

// Returns element at front of queue
int pollQueue(queue *q) { return q->items[q->front]; }

//Parcours le graphe en utilisant la procédure de la vague
void bfs(Graph *graph, int startVertex) {
    queue *q = createQueue();

    // Add to visited list and put in queue
    graph->visited[startVertex] = 1;
    enqueue(q, startVertex);
    printf("Breadth first traversal from vertex %d is:\n", startVertex);

    // Iterate while queue not empty
    while (!isEmpty(q)) {
        printf("%d ", pollQueue(q));
        int currentVertex = dequeue(q);
        

        node *temp = graph->adjLists[currentVertex];
        // Add all unvisited neighbours of current vertex to queue to be printed
        // next
        while (temp) {
            int adjVertex = temp->vertex;
            // Only add if neighbour is unvisited
            if (graph->visited[adjVertex] == 0) {
                graph->visited[adjVertex] = 1;
                enqueue(q, adjVertex);
            }
            temp = temp->next;
        }
    }
}

//Parcours le graphe tout en renvoyant le plus court chemin
void shortestPath(Graph *graph, int startVertex) {
    
    queue *q = createQueue();

    // Initialiser les tableaux de distance et de parent
    int distance[graph->numVertex];
    int parent[graph->numVertex];
    int i;
    for (i = 0; i < graph->numVertex; i++) {
        distance[i] = -1;
        parent[i] = -1;
    }

    // Ajouter le sommet de départ à la file et initialiser sa distance et son parent
    enqueue(q, startVertex);
    distance[startVertex] = 0;
    parent[startVertex] = -1;

    // Parcourir le graphe en largeur jusqu'à ce que la file soit vide
    while (!isEmpty(q)) {
        int currentVertex = dequeue(q);

        node *temp = graph->adjLists[currentVertex];
        while (temp) {
            int adjVertex = temp->vertex;
            if (distance[adjVertex] == -1) { // Le sommet n'a pas encore été visité
                distance[adjVertex] = distance[currentVertex] + 1;
                parent[adjVertex] = currentVertex;
                enqueue(q, adjVertex);
            }
            temp = temp->next;
        }
    }

    // Afficher les distances et les chemins les plus courts
    printf("Shortest paths from vertex %d:\n", startVertex);
    for (i = 0; i < graph->numVertex; i++) {
        printf("Vertex %d, Distance %d, Path: ", i, distance[i]);
        int j = i;
        while (j != -1) {
            printf("%d ", j);
            j = parent[j];
        }
        printf("\n");
    }
}




//comment
int main(){
    int **M = GenerationMatrice(8,0.7,1);
    for(int i = 0; i<8; i++){
        for(int j = 0; j<8; j++){
            printf("%d\t", M[i][j]);
        }
        printf("\n");
    }
    
    printf("\n");
    printf("\n");
    printf("\n");
    printf("\n");
    
    int numVertex=4,h=1;
    Graph *graph;
    graph=graphAlloc(numVertex);
    graph=graphCreat(M,numVertex);
    
    bfs(graph,h);

    printf("\n");
    printf("\n");
    printf("\n");
    printf("\n");

    shortestPath(graph,h);
    
    return 0;
    
}
