#include <stdio.h>

int comp=0;
int ech=0;

void affiche_tab(int tab[], int deb, int fin) //affiche le tableau jusqu'à l'élément n
{
	for (int i = deb; i < fin; ++i) //parcours du tableau jusqu'à n
	{
		printf("%d ", tab[i]);
	}
}

void echanger(int *T, int deb, int fin)
{
    int tmp = T[deb];
    T[deb] = T[fin];
    T[fin] = tmp;
    ech+=1;
}

int partition(int *T, int deb, int fin)
{
    int pivot = T[deb];
    int lambda = deb + 1;
    int rho = fin;
    int comparer = 1;

    while (comparer > 0)
    {
        
        while (T[lambda] < pivot)
        {
            lambda += 1;
            comp+=1;
            if (lambda > fin)
                return -1;
        }
        while (T[rho] > pivot)
        {
            rho -= 1;
            comp+=1;
            if (rho < deb)
                return -1;
        }
        if (lambda < rho)
            echanger(T, lambda, rho);
        else
            comparer = 0;
         comp+=1;
    }

    if (deb < rho)
        echanger(T, deb, rho);

    return rho;
}

int partitionBis(int *T, int deb, int fin){

    int indpiv = deb; //position actuel du pivot
    int pospiv = deb; //position finale du pivot dans la section T[deb,fin]
    int x = T[deb]; //le pivot
    // printf("\n");
    // printf("\nLe pivot: %d", x);
    printf("\n");
    affiche_tab(T,deb, fin);

    for (int j = deb + 1;  j < fin; j++)
    {
        // printf("\nLa comparaison: %d", T[j]);
        comp +=1;
        if (T[j] <= x)
        {
            pospiv = pospiv +1;
            // printf("\npospiv: %d", pospiv);
            if (j > pospiv) 
            {
                echanger(T,pospiv,j);
                // printf("\nechange pospiv et j: ");
                // affiche_tab(T,deb, fin);
            }
        }
    }
    if (indpiv < pospiv) 
    {
        echanger(T,indpiv,pospiv);
        // printf("\nechange indpiv et pospiv: ");
        // affiche_tab(T,deb, fin);
    }
    // printf("\npospiv: %d", pospiv);
    return pospiv;
}

int trirapide(int *T, int deb, int fin)
{
    if (deb >= fin)
        return -1;
    if (fin == (deb + 1))
    {
        int x = T[deb];
        if (x > T[fin])
        {
            T[deb] = T[fin];
            T[fin] = x;
        }
    }
    else
    {
        int pi = partitionBis(T, deb, fin);

        trirapide(T, deb, pi);
        trirapide(T, pi + 1, fin);
    }
    return 0;
}

int main()
{
    int tab[7] = {2,6,0,4,3,1,5};
    printf("\n");
    affiche_tab(tab,0,7); //tableau avant tri
    trirapide(tab, 0, 7);
    printf("\n");
    affiche_tab(tab,0,7); //trableau après tri
    printf("\nle nombre de comparaison est %d\n",comp);
    printf("le nombre d'echange est %d\n",ech);
    printf("la somme est %d\n",comp+ech);

    int tab2[7] = {7,6,5,4,3,2,1};
    comp=0, ech=0;
    printf("\n");
    affiche_tab(tab2,0,7); //tableau avant tri
    trirapide(tab2, 0, 7);
    printf("\n");
    affiche_tab(tab2,0,7);
    printf("\nle nombre de comparaison est %d\n",comp);
    printf("le nombre d'echange est %d\n",ech);
    printf("la somme est %d\n",comp+ech);


    int tab3[7] = {1,2,3,4,5,6,7};
    comp=0, ech=0;
    printf("\n");
    affiche_tab(tab3,0,7); //tableau avant tri
    trirapide(tab3, 0, 7);
    printf("\n");
    affiche_tab(tab3,0,7);
    printf("\nle nombre de comparaison est %d\n",comp);
    printf("le nombre d'echange est %d\n",ech);
    printf("la somme est %d\n",comp+ech);


    return 0;
}