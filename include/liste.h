#ifndef LISTE_H
#define LISTE_H

#include <stdlib.h>
#include <stdio.h>

#include "grille.h"

typedef struct StrListe
{
	Grille * g;
	struct StrListe * suiv;
} StrListe;

typedef StrListe Liste;

Liste * nouvelleListe();
Liste * ajoutTete(Grille *, Liste *);
Liste * ajoutQueue(Grille *, Liste *);
Liste * supprTete(Liste *);
Liste * supprQueue(Liste *);
int listeEstVide(Liste *);
void afficherListe(Liste *);
Liste * parcoursGrille(Grille *);

#endif
