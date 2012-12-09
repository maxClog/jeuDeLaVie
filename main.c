#include "include/file.h"
#include "include/liste.h"

#include <stdio.h>

#define H_PLATEAU 10
#define L_PLATEAU 10

int main()
{
	int i, j;
	// Structure contenant le plateau du jeux
	Grille * g = (Grille*)malloc(sizeof(Grille));
	
	g->i_fin = H_PLATEAU - 1;
	g->j_fin = L_PLATEAU - 1;
	
	g->i_debut = 0;
	g->j_debut = 0;
	
	// Allocation du plateau
	g->plateau = (Cellule**)malloc(H_PLATEAU * sizeof(Cellule*));
	for(i = 0 ; i < H_PLATEAU ; i++)
	{
		g->plateau[i] = (Cellule*)malloc(L_PLATEAU * sizeof(Cellule));
		for(j = 0 ; j < L_PLATEAU ; j++)
		{
			Cellule c;
			c.etat = 0;
			c.marquer = 0;
			g->plateau[i][j] = c;
		}
	}
	
	// On defini quelques cellules
	
	Cellule c;
	c.etat = 1;
	c.marquer = 0;
	
	g->plateau[1][2] = c;
	g->plateau[2][3] = c;
	g->plateau[3][2] = c;
	g->plateau[3][3] = c;
	
	g->plateau[5][6] = c;
	g->plateau[5][7] = c;
	g->plateau[6][6] = c;
	g->plateau[6][7] = c;
	
	g->plateau[6][2] = c;
	g->plateau[7][3] = c;
	g->plateau[8][4] = c;
		
	// Grille créé
	
	Liste * l;
	l = parcoursGrille(g);
	
	afficherListe(l);
	
	return 0;
}
