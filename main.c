#include "include/file.h"
#include "include/liste.h"

#define H_PLATEAU 10
#define L_PLATEAU 10

int main()
{
	Grille * g = lectureFichier("models/canon-glisseur.txt");
	afficherGrille(g);
	return 0;
}
