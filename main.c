#include <time.h>

#include "file.h"
#include "liste-gen.h"
#include "console.h"
#include "grille.h" 

#define H_PLATEAU 10
#define L_PLATEAU 10

int main(int argc, char ** argv)
{
	Grille * g = lectureFichier("models/canon-glisseur.txt"); 
	afficherGrille(g); 
	Grille * tmp; 
	/*
	Grille * c1 = couper(g, 0, 10, 0, 5); 
	afficherGrille(c1); 

	Grille * c2 = couper(g, 0, 10, 5, 10); 
	afficherGrille(c2); 

	Grille * h = init(10,10); 
	coller(h, c1, 0, 0);
	coller(h, c2, 0, 5); 
	afficherGrille(h); 
	*/

	while( 1)
	{

		liste l = explode_grille(g, 5); 

		while( (tmp = liste_suiv(l) ) != NULL )
		{
			printf("===========\n"); 
			afficherGrille(tmp); 
			tmp = evolution(tmp); 
			afficherGrille(tmp); 
			printf("===========\n"); 
		}

		tmp = implode_grille(g, l); 
		afficherGrille(g); 
		usleep(100000); 
	}
		
	return EXIT_SUCCESS;
}
