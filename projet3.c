#include <stdio.h>
#include <stdlib.h>
#include <assert.h>
#include <string.h>
#include <stdarg.h>
#include <unistd.h>
typedef struct
{
	int val;
	int initial;
}cellule;


typedef struct
{
	cellule *tab;
	int n;
}grille;

grille * creer_grille(int n)
{
	assert(n==4 ||n==6 || n==8);
	grille * a = malloc(sizeof(grille));
	if (a == NULL)
	{
		printf("Mémoire insuffisante.");
		exit(1);
	}
	(*a).n=n;
	(*a).tab=malloc(n*n*sizeof(cellule));
	int i;

	for (i = 0; i < n * n; i++)
	{
		a->tab[i].val = -1;
		a->tab[i].initial = 0;
	}

	return a;
}

void detruire_grille(grille * g)
{

	free((*g).tab);
	free(g);

}

int est_indice_valide(grille * g, int indice)
{
	int r;
	if(indice>=0 && indice < ((*g).n))
	{
		r = 1;
	}
	else
	{
		r = 0;
	}
	return r;
}

int est_cellule(grille * g, int i, int j)
{

	if  ((est_indice_valide(g,i)) && (est_indice_valide(g,j)))
        return 1;
	return 0;
}


int get_val_cellule(grille * g, int i, int j)
{
	int a;
	assert(est_cellule(g,i,j));
	a = (*g).tab[((*g).n)*i + j].val;
	return a;
}

void set_val_cellule(grille * g, int i, int j, int vale)
{
	assert(est_cellule(g, i, j));
	assert(vale <= 1 && vale >= -1);
	(*g).tab[(((*g).n)*i) + j].val = vale;
}

int est_cellule_initiale(grille * g, int i, int j)
{
	assert(est_cellule(g, i, j));
	if ((*g).tab[(((*g).n)*i) + j].initial == 1)
        return 1;

    return 0;
}


int est_cellule_vide(grille * g, int i, int j)
{
	assert(est_cellule(g, i, j));
	int r = get_val_cellule(g, i, j);
	int b;
	if (r == -1)
	{
		b = 1;
	}
	else
	{
		b = 0;
	}
	return b;
}

void afficher_grille(grille * g) {

	int i =0;
	int k, m, j;


	for (j = 0; j < 4 * (g->n) + 1; j++)
	{
		printf("* ");
	}
	printf("\n");

	while (i < g->n)
	{
		for (j = 0; j < g->n; j++)
		{
			printf("*       ");
		}
		printf("*\n");

		for (k = 0; k < g->n; k++)
		{
			m = get_val_cellule(g, i, k);
			if (est_cellule_initiale(g, i, k))
			{
				printf("*   %d%d  ", m, m);
			}

			else
			{

					if (est_cellule_vide(g, i, k))
					{
						printf("*       ");
					}

					else
					{
						printf("*   %d   ", m);
					}

			}
		}
		printf("*\n");

		for (j = 0; j < g->n; j++)
		{
			printf("*       ");
		}
		printf("*\n");

		for (j = 0; j < 4 * (g->n) + 1; j++)
		{
			printf("* ");
		}
		printf("\n");

    i++;
	}

}







void rendre_cellule_initiale(grille * g, int i, int j)
{
    assert(est_cellule(g,i,j));
    assert(est_cellule_initiale(g,i,j)==0);
    (*g).tab[(((*g).n)*i) + j].initial=1;
}


grille * initialiser_grille(char nom_fichier[])
{
    FILE *f=fopen(nom_fichier,"rt");
    int a,b,c,d,e;
    int i=0;
    fscanf(f, "%d %d",&a,&b);
    grille * g = creer_grille(a);
    while(i<b)
    {
        fscanf(f,"%d %d %d",&c,&d,&e);
        rendre_cellule_initiale(g,c,d);
        set_val_cellule(g,c,d,e);
        i++;
    }


    return g;
}


int est_grille_pleine(grille * g)
{
    int i;
    int j;
    int cpt = 0;
    int r=0;
    for(i=0;i<(*g).n;i++)
    {
        for(j=0;j<(*g).n;j++)
        {
            if(get_val_cellule(g,i,j)==1 || get_val_cellule(g,i,j)==0)
            {
                cpt++;
            }
        }
    }

    if(cpt==(((*g).n)*((*g).n)))
    {
        r=1;
    }
    return r;
}


int pas_zero_un_consecutifs(grille * g)
{
   int i;
   int j;

   for (i=0;i<((*g).n-2);i++)
   {
       for (j=0;j<((*g).n -2);j++)
       {
           if(get_val_cellule(g,i,j)==get_val_cellule(g,(i+1),j) && get_val_cellule(g,i,j)==get_val_cellule(g,(i+2),j))
            {
                return 0;
            }
            if(get_val_cellule(g,i,j)==get_val_cellule(g,i,j+1) && get_val_cellule(g,i,j)==get_val_cellule(g,i,j+2))
            {
                return 0;
            }
       }
   }
    return 1;
}





int meme_nombre_zero_un(grille * g)
{
    int i;
    int j;

    for(i=0;i<(*g).n;i++)
    {
        int a=0;
        for(j=0;j<(*g).n;j++)
        {
            a=a+(get_val_cellule(g,i,j));

        }
        if (a!=(((*g).n)/2))
            {
                return 0;
            }
    }


    for(j=0;j<(*g).n;j++)
    {
        int b=0;
        for(i=0;i<(*g).n;i++)
        {
            b=b+(get_val_cellule(g,i,j));
        }
        if(b!=(((*g).n)/2))
        {
            return 0;
        }
    }


    return 1;
}

int lignes_colonnes_distinctes(grille * g)
{
    int a=0;
    int nb=0;
    int nb2=0;
    int i=0;
    int j=0;
    for(a=0;a<(*g).n;a++)
    {
        for (i=0;i<(*g).n;i++)
        {
            for(j=0;j<(*g).n;j++)
            {
                if(a!=i && get_val_cellule(g,a,j)==get_val_cellule(g,i,j))
                    nb++;
            }
            if(nb==(*g).n)
                return 0;
            nb=0;
        }
    }

    for(a=0;a<(*g).n;a++)
    {
        for (j=0;j<(*g).n;j++)
        {
            for(i=0;i<(*g).n;i++)
            {
                if(a!=i && get_val_cellule(g,a,i)==get_val_cellule(g,j,i))
                    nb2++;
            }
            if(nb2==(*g).n)
                return 0;
            nb2=0;
        }
    }
    return 1;
}


int est_partie_gagnee(grille * g)
{
    if(est_grille_pleine(g)==1 && pas_zero_un_consecutifs(g)==1 && meme_nombre_zero_un(g)==1 && lignes_colonnes_distinctes(g)==1)
        return 1;

    return 0;
}

int est_mouvement_valide(grille * g, char mouv[], int * ligne, int * colonne, int * val)
{
    * ligne = mouv[0]-'A';
	* colonne = mouv[1]-'A';
	if(mouv[2] != '\0')
		* val = mouv[2]-'0';
	else
		* val = -1;

	if(est_cellule(g, *ligne, *colonne) == 1 && est_cellule_initiale(g, *ligne, *colonne) == 0)
	{
		return 1;
	}

    return 0;
}

void tour_de_jeu(grille * g)
{

    char mouv[3];
    int ligne;
    int colonne;
    int val;
    do{
        afficher_grille(g);
        printf("Saisir le mouvement : ");
        scanf("%s",mouv);
    } while(est_mouvement_valide(g,mouv,&ligne,&colonne,&val)==0);
    set_val_cellule(g,ligne,colonne,val);
}

void jouer(char ch[])
{
   grille *g=initialiser_grille(ch);
    while(est_partie_gagnee(g)==0)
    {
        tour_de_jeu(g);
    }
    printf("VICTOIRE !!");
}

void choisir_grille(char s[])
{
    int taille;
    do{
        printf("\n Choississez une taille de grille(4,6,8)");
        scanf("%d",&taille);
    }while(taille!=4 && taille!=6 && taille!=8);
    s[9]=taille + '0';
    s[17]=((rand()%5)+1) + '0';
    printf("%s\n",s);
}

/////////////////////////////////////////////////////////
//                                                     //
//             Fonction test partie 3!                 //
//                                                     //
/////////////////////////////////////////////////////////
void test_afficher_grille() {
	grille * g = creer_grille(4);
	int val_cellule[16] = {  0,1,1,0,1,0,0,1,0,0,1,1,1,1,0,0 };
	int initial_cellule[16] = { 0,1,0,1,0,0,1,0,0,1,0,0,1,1,0,1 };
	int i;
	for (i = 0; i < 16; i++) {
		g->tab[i].val = val_cellule[i];
		g->tab[i].initial = initial_cellule[i];
	}
	afficher_grille(g);
	printf("L'affichage doit Ãªtre celui de la grille solution dans le pdf\n");
    if(est_partie_gagnee(g))
        printf("gg");
}

void test()
{

	char titre[]="code.txt";
    grille * g=initialiser_grille(titre);
    afficher_grille(g);
    if(est_partie_gagnee(g))
        printf("gagné\n");
    else
        printf("perdue\n");
    printf("meme nombre zero un : %d\n",meme_nombre_zero_un(g));
    printf("Lignes colonnes distinctes : %d\n",lignes_colonnes_distinctes(g));
    printf("pas trois meme nombres consecutifs : %d\n",pas_zero_un_consecutifs(g));
    printf("grille pleine : %d\n",est_grille_pleine(g));

}
void test_est_mouv_valide()
{

	char titre[]="grille1.txt";
    grille * g=initialiser_grille(titre);
    afficher_grille(g);
    int val=0;
    int ligne=0;
    int colonne=0;
    char mouv1="AA1";
    char mouv2="XX0";
    printf("mouv valide : %d\n",est_mouvement_valide(g,mouv1,&ligne,&colonne,&val));

}
void test_tour_de_jeu()
{

    grille * g=initialiser_grille("test2.txt");
    tour_de_jeu(g);

}
void test_jouer()
{
    char test[]="test7.txt";
    jouer(test);
}


int main() {


	srand(time(NULL));
    char nom[50]="Grilles/G0/grille0.txt";
    choisir_grille(nom);
    jouer(nom);

    /*test_choisir_grille();
    test_est_mouv_valide();
    test_jouer();
    test_tour_de_jeu();*/
    return 0;
}
