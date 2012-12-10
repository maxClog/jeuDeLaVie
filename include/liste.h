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

// Genere une nouvelle liste
Liste * nouvelleListe();

// Ajoute une grille en tete de liste
Liste * ajoutTete(Grille *, Liste *);

// Ajoute une grille en queue de liste
Liste * ajoutQueue(Grille *, Liste *);

// Supprime une grille en tete de liste
Liste * supprTete(Liste *);

// Supprime une grille en queue de liste
Liste * supprQueue(Liste *);

// Indique si la liste est vide ou pas
int listeEstVide(Liste *);

// Retourne la taille de la liste
int tailleListe(Liste *);

// Affiche les grilles de la liste
void afficherListe(Liste *);

// Decoupe toute la grille en plusieurs et les places dans une liste
Liste * parcoursGrille(Grille *);

// Integre une grille dans l'autre aux bonnes coordonnées
Grille * assembler(Grille *, Grille *);

// Recolle toutes les grilles de la liste dans la grille principale
Grille * recollageGrille(Grille *, Liste *);

#endif
