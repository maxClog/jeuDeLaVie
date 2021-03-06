#ifndef __LISTE_GEN_H
#define __LISTE_GEN_H 

#include <stdlib.h>
#include <stdio.h>

typedef struct str_ele {
	void * ele; 
	struct str_ele * suiv; 
} *liste_element; 

typedef struct str_liste {
	int nb_ele; 
	liste_element prem; 
	liste_element act; 
	liste_element prec; 
} *liste; 

liste liste_init(void);
void liste_debut(liste lsb ); 
void liste_ajt( liste lsb,  void * b ); 
void * liste_suiv(liste lsb); 
void liste_sup(liste lsb, void * sup, void ( free_ele( void * ) ) ); 
void liste_free(liste lsb,  void ( free_ele( void * ) )  ); 
int liste_taille(liste l); 
void liste_sup_nf(liste lsb, void * sup ); 
int liste_dedans( liste l, void * p ); 

#endif 
