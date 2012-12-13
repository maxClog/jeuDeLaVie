#include <time.h>

#include "file.h"
#include "liste-gen.h"
#include "console.h"
#include "grille.h" 

#define H_PLATEAU 10
#define L_PLATEAU 10

int main(int argc, char ** argv)
{
	Grille * g = lectureFichier("models/canon-planeur.txt"); 
	Grille * tmp; 
	int cycle=0; 

	while( cycle < 100)
	{

		liste l = explode_grille(g, 8); 

		while( (tmp = liste_suiv(l) ) != NULL )
		{
			tmp = evolution(tmp); 
		}

		tmp = implode_grille(g, l); 
		afficherGrille(g); 
		usleep(50000); 
		liste_free(l, cb_free_grille); 
		cycle++; 
	}

	free_grille(g); 
	return EXIT_SUCCESS;
}
