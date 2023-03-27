#ifndef GRAPH_H
#define GRAPH_H
#define SIZE 40
#define m 999999999

// Structure d'une file d'attente pour stocker les sommets visités
typedef struct queuez {
    int items[SIZE];
    int front;
    int rear;
}queue;

// Structure d'un noeud dans la liste d'adjacence
typedef struct nodez{
    int vertex;           // Le numéro du sommet adjacent
    struct nodez *next;    // Pointeur vers le prochain noeud de la liste
}node;

// Structure d'un graphe représenté par une liste d'adjacence
typedef struct Graphz {
    int numVertex;      // Nombre de sommets dans le graphe
    int *visited;         // Tableau des marques visitées
    node **adjLists; // Tableau des listes d'adjacence
} Graph;


Graph *graphAlloc(int numVertex);//Alloue de l'espace memoire au graph
Graph *graphCreat(int **Matrix, int Size);//Crée un graph à partir de sa matrice d'adjacence

#endif




