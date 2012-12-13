#ifndef GRILLE_H
#define GRILLE_H

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/ioctl.h>

#include <rpc/types.h>
#include <rpc/xdr.h>
#include <rpc/rpc.h>

#define PROGNUM 0x20000135
#define VERSNUM 1
#define PROCNUM 1

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

// Initialise et copy une grille 
Grille * grille_cpy( Grille * g );

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

// Xdr de la grille 
bool_t xdr_grille(XDR *xdrs, Grille **grille);
bool_t xdr_cellule(XDR *xdrs, Cellule * c); 

#endif
