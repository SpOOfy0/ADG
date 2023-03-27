#include <stdio.h>
#include <stdlib.h>
#include <time.h>

#define dimention 5


int max(int a,int b)
{
    if(a>b) return a;
    else return b;
}

int **CreationMatrice(int taille)
{
    int **matrice = (int**)malloc(taille*sizeof(int*));
    for (int i=0; i<taille; i++)
        matrice[i] = (int*)malloc(taille*sizeof(int));

    return matrice;
}


int **GenerationMatrice(int taille, float p, int oriente)
{
    float v;
    float u;
    int **matrice = (int**)malloc(taille*sizeof(int*));
    for (int i=0; i<taille; i++)
        matrice[i] = (int*)malloc(taille*sizeof(int));
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


void AfficherMatrice(int **M, int taille)
{
	int i,j;
    
    for (i=0; i<taille; i++){
        for (j=0; j<taille; j++)
            printf("%d ", M[i][j]);
        printf("\n");
    }
    printf("\n");
}


int DegreMatrice(int **M, int taille)
{
     int degres = 0;
    int nb = 0;
    for(int i=0; i<taille; i++)
    {
        for(int j=0; j<taille; j++)
        {
            if(M[i][j]==1)
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

int **ProduitMatrice(int **matrice1, int **matrice2, int taille)
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

int **PuissanceMatrice(int **M, int taille, int puissance)
{
    int **new_matrice = M;
    for(int i=0; i<puissance; i++)
    {
        new_matrice=ProduitMatrice(new_matrice,M,taille);
    }
    return new_matrice;
}

//Cette fonction sert à Mouillé le sommet
int *Mouille(int *Tableau, int sommet, int *accu)
{
    Tableau[sommet]=1; // 1 signifie que le soomet est mouillé , 0 s'il est non mouillé
    (*accu)++;            //necessaire pour la condition d'arrêt dans la fonction EsrConnexe()
    return Tableau;
}

void MouilleRecurcive(int **M, int *Tableau, int Taille, int *accu, int sommet)
{
    if (*accu==100)
       return ;
    else
    {
        Tableau[sommet]=1;  
        (*accu)++;
        for (int i=0; i<Taille; i++)
        {
            if (M[sommet][i]==1)
            {
                Tableau[i]=1; 
                (*accu)++;
            }
        }
        for (int j=0; j<Taille; j++)
        {
            if (Tableau[j]==1)
               MouilleRecurcive(M,Tableau,Taille,accu,j);
        }
    }
}

int EstConnexe(int *T ,int Taille)
{
    for (int i=0; i<Taille; i++)
    {
        printf("%d\n",T[i]);
        if (T[i]==0)
        return 0;
    }
    return 1;
}
int main()
{
    int **M=GenerationMatrice(4,0.7,1);
    AfficherMatrice(M,4);
    
    int *T=calloc(100,sizeof(int));
    
    int a=0;
    
    MouilleRecurcive(M,T,4,&a,0);
    a=EstConnexe(T,4);
    //T=Mouille(T,3,&a);
    printf("It's for a  %d\n",a);
    

    return 0;
}



