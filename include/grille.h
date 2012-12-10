#ifndef GRILLE_H
#define GRILLE_H

#include <unistd.h>
#include <sys/ioctl.h>

#include "cellule.h"

typedef struct StrGrille
{
	Cellule ** plateau;
	int i_debut;
	int j_debut;
	int i_fin;
	int j_fin;
} Grille;

// Initialise la grille
Grille * init(int, int);

// Remet tous les marquages à 0
Grille * resetMarquage(Grille *);

// Tue toutes les cellules de la grille
Grille * resetGrille(Grille *);

// Genere une grille depuis un fichier
Grille * lectureFichier(char *);

// Fait evoluer une grille
Grille * evolution(Grille *);

// Affiche une grille
void afficherGrille(Grille *);

// Découpe un morceau de la grille contenant un tas de cellules vivantes
Grille * decoupe(Grille *, int, int);

// Désalloue la grille
void free_grille(Grille *);

#endif
