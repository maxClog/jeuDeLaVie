#include "include/grille.h"
#include "include/file.h"

#include <stdio.h>

void afficherGrille(Grille * g)
{
	int i, j;
	for(i = 0 ; i <= (g->i_fin - g->i_debut) ; i++)
	{
		for(j = 0 ; j <= (g->j_fin - g->j_debut) ; j++)
		{
			if(g->plateau[i][j].etat == 1)
				printf("X");
			else
				printf("-");
		}
		printf("\n");
	}
}

Grille * decoupe(Grille * g, int x, int y)
{
	int i = 0, j = 0;
	int k,l;
	int i_actuel, j_actuel;
	int i_debut, j_debut;
	int i_fin = 0, j_fin = 0;
	
	File * f = nouvelleFile();
	
	Grille * nouvelleGrille = (Grille*)malloc(sizeof(Grille));
	
	// On a une cellule vivante à la position i,j
	i_debut = x;
	j_debut = y;
	
	f = enfiler(i_debut, j_debut, f);			// On enfile sa position dans la grille
	g->plateau[i_debut][j_debut].marquer = 1;	// On marque la cellule
	while(!fileEstVide(f))
	{
		i_actuel = f->i;
		j_actuel = f->j;
		
		f = defiler(f);
		
		// On parcours les cases alentours
		for(k = i_actuel-1;k<=i_actuel+1;k++)
		{
			for(l = j_actuel-1 ; l<=j_actuel+1;l++)
			{
				if(k != i_actuel || l != j_actuel)
				{
					// Obtenir les extremités du tableau
					if(k < i_debut)
						i_debut = k;
					if(k > i_fin)
						i_fin = k;
					if(l < j_debut)
						j_debut = l;
					if(l > j_fin)
						j_fin = l;
					
					// Si une case autour est un voisin, on l'enfile pour la parcourir
					if(g->plateau[k][l].etat == 1 && g->plateau[k][l].marquer == 0)
					{
						f = enfiler(k, l, f);
						// Une fois qu'elle est enfiler on peut la marquer pour qu'elle ne soit pas comptabiliser plusieurs fois
						g->plateau[k][l].marquer = 1;
					}
					else
					{
						// On marque les cases alentours
						g->plateau[k][l].marquer = 1;
					}
				}
			}
		}
	}
		
	// La grille peut être formée
	nouvelleGrille->i_debut = i_debut;
	nouvelleGrille->j_debut = j_debut;
	nouvelleGrille->i_fin = i_fin;
	nouvelleGrille->j_fin = j_fin;
	
	// Allocation du plateau
	nouvelleGrille->plateau = (Cellule**)malloc((i_fin - i_debut + 1) * sizeof(Cellule*));
	for(i=0;i<=(i_fin-i_debut);i++)
		nouvelleGrille->plateau[i] = (Cellule*)malloc((j_fin-j_debut+1) * sizeof(Cellule));
	
	for(k=0, i=i_debut;i<=i_fin;i++, k++)
	{
		for(l=0, j=j_debut;j<=j_fin;j++, l++)
		{
			nouvelleGrille->plateau[k][l] = g->plateau[i][j];
		}
	}
	
	return nouvelleGrille;
}
