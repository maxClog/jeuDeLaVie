#ifndef __LISTE_H
#define __LISTE_H 

#include <stdlib.h>
#include <stdio.h>

typedef struct str_ele {
	void * ele; 
	struct str_ele * suiv; 
} *liste_element; 

typedef struct str_liste {
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

#endif 
