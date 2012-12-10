#include "include/file.h"
#include "include/liste.h"

#include <stdio.h>

#define H_PLATEAU 10
#define L_PLATEAU 10

int main()
{
	// Structure contenant le plateau du jeux
	Grille * g = init(H_PLATEAU, L_PLATEAU);
	
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
	// Découpage de la grille en tas de cellule qu'on mets dans une liste
	l = parcoursGrille(g);
	
	afficherGrille(g);
	
	// Evolution de chaques grilles dans la liste
	Liste * q = l;
	do
	{
		q->g = evolution(q->g);
		q = q->suiv;
	}while(q != NULL);
	
	printf("\n--EVOLUTION--\n");
	// On réassemble la liste de grille dans la grille de départ
	g = recollageGrille(g, l);
	
	afficherGrille(g);
	
	return 0;
}
