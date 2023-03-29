#ifndef OUTILS_H
#define OUTILS_H

#define dimension 5

struct zdata
{
    int mouille;
    int etape;
    int* sommets;
};
typedef struct zdata *Data;

int max(int a,int b);
int min(int a, int b);
void printMatrice(int **Matrice, int taille);
int **CreationMatrice(int taille);
int ** CopieMatrice(int **matrice, int taille);
void DiagonalMatriceZero(int **matrice,int taille);
void DiagonalMatriceUn(int **matrice,int taille);
Data *ConversionTableau(int **matrice, int taille);

#endif