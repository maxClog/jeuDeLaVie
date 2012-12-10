#include <time.h>

#include "include/file.h"
#include "include/liste.h"
#include "include/console.h"

#define H_PLATEAU 10
#define L_PLATEAU 10

int main(int argc, char ** argv)
{
	srand( time(NULL) ); 
	int c=1, t; 
	float vit=1; 
	struct timeval tv = { 0, 0 };
	fd_set readfds, readfds_cp;
	Grille * g = NULL;

	if(argc == 2)
	{
		printf("Initialisation du jeu depuis %s.\n\r", argv[1]); 
		g = lectureFichier(argv[1]); 
	}
	else
	{
		g = init(H_PLATEAU, L_PLATEAU); 
		
		Cellule c;
		c.etat = 1;
		c.marquer = 0;
		c.petat = 1;
		
		// départ 
		g->plateau[4][4] = c; 
		g->plateau[5][5] = c; 
		g->plateau[5][6] = c; 
		g->plateau[5][7] = c; 
		g->plateau[5][8] = c; 
		
		g->plateau[4][8] = c; 
		g->plateau[3][8] = c; 
		g->plateau[2][7] = c; 
	}

	// fin départ 
	
	mode_raw(1); 

	FD_ZERO(&readfds);
	FD_SET(STDIN_FILENO, &readfds);

	while(c)
	{
		readfds_cp = readfds; 
		if( select(STDIN_FILENO + 1, &readfds_cp, NULL, NULL, &tv) != -1 )
		{
			if( FD_ISSET(STDIN_FILENO, &readfds_cp ) )
			{
				switch( t = getchar() )
				{
					case 'q' : 
						c=0; 
					break; 
					case 'p' : 
						vit/=2;
					break; 
					case 'm' : 
						if( vit < 6 )
							vit*=2; 
					break; 
					case 'r' : 
						free_grille(g); 
						g = lectureFichier(argv[1]);
						vit=1; 
					break; 
					default : 
						printf("Touche %c préssé\n\r", t); 
				}
			}

			if( tv.tv_sec == 0 && tv.tv_usec == 0 )
			{
				g = evolution(g);
				afficherGrille(g);
			}

			tv.tv_usec = 500000*vit;
		}

	}

	mode_raw(0); 
	free_grille(g);
	return EXIT_SUCCESS; 
}
