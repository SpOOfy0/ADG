#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include "outils.h"

int max(int a,int b)
{
    if(a>b) return a;
    else return b;
}

int min(int a, int b)
{
    if(a<b) return a;
    else return b;
}

int **CreationMatrice(int taille)
{
    int **matrice = (int**)malloc(taille*sizeof(int*));
    for (int i=0; i<taille; i++)
        matrice[i] = (int*)malloc(taille*sizeof(int));

    return matrice;
}


int ** CopieMatrice(int **matrice, int taille)
{
    int **newMatrice=CreationMatrice(taille);
    for(int i=0; i<taille;i=i+1)
    {
        for(int j=0;j<taille;j=j+1)
        {
            newMatrice[i][j]=matrice[i][j];
        }
    }
    return newMatrice;
}

void DiagonalMatriceUn(int **matrice,int taille)
{
    for(int i=0;i<taille;i=i+1)
    {
        matrice[i][i]=1;
    }
}

void DiagonalMatriceZero(int **matrice,int taille)
{
    for(int i=0;i<taille;i=i+1)
    {

        matrice[i][i]=0;
    }
}

Data *ConversionTableau(int **matrice, int taille)
{
    Data* graphe = (Data*) malloc(taille * sizeof(Data));
    int k;
    
    
    for (int i = 0; i < taille; i=i+1) 
    {
        int nb_sommets = 0;
        for (int j = 0; j < taille; j=j+1) 
        {
            if (matrice[i][j] == 1) // Si les sommets i et j sont liés
            { 
                nb_sommets=nb_sommets+1; // Incrémenter le nombre de sommets liés directement à i
            }
        }
        printf("sommet ");
        printf("%d",i);
        printf("\n");
        graphe[i] = (Data) malloc(sizeof(struct zdata)); // Allouer de la mémoire pour la structure zdata
        graphe[i]->sommets = (int*) malloc(nb_sommets * sizeof(int)); // Allouer de la mémoire pour le tableau de sommets liés
        graphe[i]->mouille = 0; // Initialiser "mouillé" à 0
        graphe[i]->etape = 0; // Initialiser "etape" à 0

        k = 0; // Remettre k à zéro pour chaque sommet traité
        
        for (int j = 0; j < taille; j=j+1) 
        {
            if (matrice[i][j] == 1) // Si les sommets i et j sont liés
            { 
                graphe[i]->sommets[k] = j; // Ajouter j au tableau de sommets liés de i
                k=k+1;
                printf("%d ",j);
            }
        }
        printf("\n");
    }
    return graphe;
}



void printTableau(int **tableau, int taille) 
{
  for (int i = 0; i < taille; i++) {
    for (int j = 0; j < taille; j++) {
      printf("%d ", tableau[i][j]);
    }
    printf("\n");
  }
}