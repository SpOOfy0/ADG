int max(int a,int b)
{
    if(a>b) return a;
    else return b;
}

int **GenerationMatrice(int taille, float p, int oriente)
{
    float v;
    float u;
    int **matrice = malloc(taille*sizeof(int*));
    for (int i=0; i<taille; i++)
        matrice[i] = malloc(taille*sizeof(int));
    
    //Dans le cas ou le graphe est orienté
    if(oriente==1)  
    {
        for(int i=0; i<taille; i++)
        {
            for(int j=0; j<taille; j++)
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
    }
    //Dans le cas ou le graphe est non orienté
    else
    {
        for(int i=0; i<taille; i++)
        {
            for(int j=0; j<taille; j++)
            {
               if (j<=i)
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
               else
               {
                 matrice[i][j]=matrice[j][i];
               }
            }
        }
        
    }
}

//ma fct qui ne larche pas
int **ProduitMatrice(int **m1, int **m2, int taille)
{
    int **new_matrice = (int**)malloc(taille*sizeof(int*));
    for (int i=0; i<taille; i++)
        new_matrice[i] = (int*)malloc(taille*sizeof(int));

    int k=0;
    for(int i=0; i<taille; i++)
    {
        for(int j=0; j<taille; j++)
        {
           
            while (m1[i][k]==0 && m2[k][i]==0 && k<taille)
                k++;
            if(k==taille)
                new_matrice[i][j]=0;    
            else
                new_matrice[i][j]=1;
            k=0;
        }
    }
    return new_matrice;
}
