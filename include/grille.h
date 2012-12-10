#ifndef GRILLE_H
#define GRILLE_H

#include "cellule.h"

typedef struct StrGrille
{
	Cellule ** plateau;
	int i_debut;
	int j_debut;
	int i_fin;
	int j_fin;
} Grille;

Grille * init(int, int);
void afficherGrille(Grille *);
Grille * decoupe(Grille *, int, int);
void free_grille(Grille *);

#endif
