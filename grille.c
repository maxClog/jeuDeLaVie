#include "include/grille.h"
#include "include/file.h"

#include <math.h>
#include <stdio.h>

Grille * init(int h, int l)
{
	int i,j;
	Grille * g = (Grille*)malloc(sizeof(Grille));
	
	g->i_fin = h - 1;
	g->j_fin = l - 1;
	
	g->i_debut = 0;
	g->j_debut = 0;
	
	// Allocation du plateau
	g->plateau = (Cellule**)malloc(h * sizeof(Cellule*));
	for(i = 0 ; i < h ; i++)
	{
		g->plateau[i] = (Cellule*)malloc(l * sizeof(Cellule));
		for(j = 0 ; j < l ; j++)
		{
			Cellule c;
			c.etat = 0;
			c.petat = 0;
			c.marquer = 0;
			g->plateau[i][j] = c;
		}
	}
	return g;
}

Grille * grille_cpy( Grille * g )
{
	int i, j; 
	Grille * r = init(g->i_fin - g->i_debut +1, g->j_fin - g->j_debut +1);

	for( i=0; i<=(g->i_fin - g->i_debut); i++ )
	{
		for( j=0; j<=(g->j_fin - g->j_debut); j++ )
		{
			r->plateau[i][j] = g->plateau[i][j]; 
		}
	}

	return r; 
}

Grille * resetMarquage(Grille * g)
{
	int i,j;
	for(i=0;i<=(g->i_fin-g->i_debut);i++)
	{
		for(j=0;j<=(g->j_fin-g->j_debut);j++)
		{
			g->plateau[i][j].marquer = 0;
		}
	}
	return g;
}

Grille * resetGrille(Grille * g)
{
	int i,j;
	for(i=0;i<=(g->i_fin-g->i_debut);i++)
	{
		for(j=0;j<=(g->j_fin-g->j_debut);j++)
		{
			g->plateau[i][j].etat = 0;
		}
	}
	return g;
}

Grille * lectureFichier(char * nom_fichier)
{
	Grille * g;
	int l, h, i=0, j=0; 
	char ligne[1024]; 
	FILE * fichier = NULL; 
	struct winsize size;
	
	if( (fichier = fopen( nom_fichier, "r" ) ) == NULL )
	{
		printf("Erreur d'ouverture du fichier\n");
		exit(EXIT_FAILURE); 
	}

	if( fgets(ligne, 1024, fichier) == NULL )
	{
		return NULL; 
	}

	sscanf(ligne, "%d %d ", &l, &h ); 
	g = init(h, l); 

	if (ioctl(STDIN_FILENO,TIOCGWINSZ, (char*) &size)<0)
	{
		printf ("Erreur TIOCGEWINSZ\n");
	}
	else if( size.ws_row < h || size.ws_col < l )
	{
		printf ("votre terminal comporte %d lignes et %d colones\n\r", 
			size.ws_row,size.ws_col);
		printf ("La grille comporte %d lignes et %d colones\n\r", h, l ); 
		printf ("Risque d'affichage inattendu\n"); 
		exit(EXIT_SUCCESS); 
	}

	for(i=0; fgets(ligne, 1024, fichier) != NULL; i++ )
	{
		for(j=0; ligne[j] != '\0'; j++ )
		{
			if( ligne[j] == 'V' )
			{
				g->plateau[i][j].etat = 1;
			}
		}
	}

	fclose(fichier); 
	return g; 
}

Grille * evolution(Grille * g)
{
	int i, j, k, fk, l, fl, nbc; 
	int hauteur = g->i_fin - g->i_debut + 1;
	int largeur = g->j_fin - g->j_debut + 1;
	
	for( i=1; i<hauteur-1; i++ )
	{
		for( j=1; j<largeur-1; j++ )
		{
			// Check de la case actuelle 
			nbc = 0; 
			g->plateau[i][j].petat = g->plateau[i][j].etat; 

			for( k=i-1; k<=i+1; k++ )
			{
				for( l=j-1; l<=j+1; l++)
				{
					if( !( i==k && j==l ) )
					{
						if( g->plateau[k][l].etat == 1)
						{
							nbc++; 
						}
					}
				}
			}

			if( g->plateau[i][j].etat == 1)
			{
				if( (nbc > 3) || (nbc < 2) )
				{
					g->plateau[i][j].petat = 0; 
				}
			}
			else if( g->plateau[i][j].etat == 0)
			{
				if( nbc == 3 )
				{
					g->plateau[i][j].petat = 1; 
				}
			}
		}
	}

	for( i=1; i<hauteur-1; i++ )
	{
		for( j=1; j<largeur-1; j++ )
		{
			g->plateau[i][j].etat = g->plateau[i][j].petat; 
		}
	}

	return g;
}

void afficherGrille(Grille * g)
{
	int i, j;
	for(i = 0 ; i <= (g->i_fin - g->i_debut) ; i++)
	{
		for(j = 0 ; j <= (g->j_fin - g->j_debut) ; j++)
		{
			if(g->plateau[i][j].etat == 1)
				printf("X");
			else
				printf("_");
		}
		printf("\n\r");
	}
	printf("\n\r");
}

Grille * decoupe(Grille * g, int x, int y)
{
	int i = 0, j = 0;
	int k,l;
	int i_actuel, j_actuel;
	int i_debut, j_debut;
	int i_fin = 0, j_fin = 0;
	
	File * f = nouvelleFile();
	
	Grille * nouvelleGrille = (Grille*)malloc(sizeof(Grille));
	
	// On a une cellule vivante à la position x,y
	i_debut = x;
	j_debut = y;
	
	f = enfiler(i_debut, j_debut, f);			// On enfile sa position dans la grille
	g->plateau[i_debut][j_debut].marquer = 1;	// On marque la cellule
	while(!fileEstVide(f))
	{
		i_actuel = f->i;
		j_actuel = f->j;
		
		f = defiler(f);
		
		// On parcours les cases alentours
		for(k = i_actuel-2;k<=i_actuel+2;k++)
		{
			for(l = j_actuel-2 ; l<=j_actuel+2;l++)
			{
				if((k != i_actuel || l != j_actuel) && (k >= g->i_debut && k <= g->i_fin && l >= g->j_debut && l <= g->j_fin))
				{
					// Obtenir les extremités du tableau
					if(k < i_debut)
						i_debut = k;
					if(k > i_fin)
						i_fin = k;
					if(l < j_debut)
						j_debut = l;
					if(l > j_fin)
						j_fin = l;
					
					// Si une case autour est un voisin, on l'enfile pour la parcourir
					if(g->plateau[k][l].etat == 1 && g->plateau[k][l].marquer == 0)
					{
						f = enfiler(k, l, f);
						// Une fois qu'elle est enfiler on peut la marquer pour qu'elle ne soit pas comptabiliser plusieurs fois
						g->plateau[k][l].marquer = 1;
					}
					else
					{
						// On marque les cases alentours
						g->plateau[k][l].marquer = 1;
					}
				}
			}
		}
	}
		
	// La grille peut être formée
	nouvelleGrille->i_debut = i_debut;
	nouvelleGrille->j_debut = j_debut;
	nouvelleGrille->i_fin = i_fin;
	nouvelleGrille->j_fin = j_fin;
	
	// Allocation du plateau
	nouvelleGrille->plateau = (Cellule**)malloc((i_fin - i_debut + 1) * sizeof(Cellule*));
	for(i=0;i<=(i_fin-i_debut);i++)
		nouvelleGrille->plateau[i] = (Cellule*)malloc((j_fin-j_debut+1) * sizeof(Cellule));
	
	for(k=0, i=i_debut;i<=i_fin;i++, k++)
	{
		for(l=0, j=j_debut;j<=j_fin;j++, l++)
		{
			nouvelleGrille->plateau[k][l] = g->plateau[i][j];
		}
	}
	return nouvelleGrille;
}

void free_grille(Grille * g)
{
	int i; 
	for(i=0; i<=g->i_fin-g->i_debut; i++)
	{
		free(g->plateau[i]); 
	}

	free(g->plateau);
	free(g);
}

void cb_free_grille( void * p )
{
	free_grille(p);
}

bool_t xdr_cellule(XDR *xdrs, Cellule * c)
{
	return xdr_int(xdrs, &(c->etat) ) 
		&& xdr_int(xdrs, &(c->petat) )
		&& xdr_int(xdrs, &(c->marquer) );
}

bool_t xdr_grille(XDR *xdrs, Grille **g)
{
	unsigned int i, j, c;
	int i_d,j_d,i_f,j_f;
	Grille * tmpg;
	char * tab; 
	int taille_tampon; 

	switch (xdrs->x_op) 
	{
		case XDR_ENCODE : 
			//fprintf(stderr,"xdr_grille : ENCODE(%d)\n", xdrs->x_op) ;   
		break ; 
		case XDR_DECODE : 
			//fprintf(stderr,"xdr_grille : DECODE(%d)\n", xdrs->x_op) ;   
		break ; 
		case XDR_FREE :   
			//fprintf(stderr,"xdr_grille : FREE(%d)\n", xdrs->x_op) ;     
			free_grille(*g); 
			return TRUE; 
		break ; 
		default :         
			//fprintf(stderr,"xdr_grille : default(%d)\n", xdrs->x_op) ;  
		break ; 
	}

	if (xdrs->x_op == XDR_ENCODE)
	{
		tmpg = *g;
		i_d = tmpg->i_debut; 
		i_f = tmpg->i_fin;
		j_d = tmpg->j_debut;
		j_f = tmpg->j_fin; 

		if( !( xdr_int(xdrs, &i_d ) 
			&& xdr_int(xdrs, &j_d )
			&& xdr_int(xdrs, &i_f )
			&& xdr_int(xdrs, &j_f ) 
		) )
			return FALSE;

		taille_tampon = sizeof(char)*(i_f-i_d+1)*(j_f-j_d+1);
		tab = malloc(taille_tampon ); 
		for(c=0, i=0; i<=(i_f-i_d); i++)
		{
			for(j=0; j<=(j_f-j_d); j++)
			{
				tab[c] = tmpg->plateau[i][j].etat; 
				c++; 
			}
		}

		if(!xdr_bytes(xdrs, &tab, &taille_tampon, taille_tampon) )
		{
			free(tab) ;
			return FALSE ;
		}
		else
		{
			free(tab) ;
		}
	}
	else if(xdrs->x_op == XDR_DECODE)
	{
		if( !(xdr_int(xdrs, &i_d ) 
			&& xdr_int(xdrs, &j_d )
			&& xdr_int(xdrs, &i_f )
			&& xdr_int(xdrs, &j_f )
		) )
			return FALSE ;

		tmpg = init( i_f-i_d+1, j_f-j_d+1);
		*g = tmpg;

		tmpg->i_debut = i_d;
		tmpg->i_fin = i_f;
		tmpg->j_debut = j_d; 
		tmpg->j_fin = j_f; 
		taille_tampon = sizeof(char)*(i_f-i_d+1)*(j_f-j_d+1);
		tab = malloc(taille_tampon ); 

		if(!xdr_bytes(xdrs, &tab, &taille_tampon, taille_tampon) )
		{
			free(tab) ;
			return FALSE ;
		}

		for(i=0, c=0; i<=(i_f-i_d); i++)
		{
			for(j=0; j<=(j_f-j_d); j++)
			{
				tmpg->plateau[i][j].etat=tab[c]; 
				c++; 
			}
		}

		free(tab) ;
	}

	return TRUE ;
}


Grille * couper(Grille *g, int i_deb, int i_fin, int j_deb, int j_fin )
{
	Grille * res = init(i_fin-i_deb+2, j_fin-j_deb+2 ); 
	int i, j, ig, jg, etat; 
	i_deb--;
	i_fin++;
	j_deb--;
	j_fin++; 

	for( i=0, ig=i_deb; i<res->i_fin-res->i_debut+1; i++, ig++ )
	{
		for(j=0, jg=j_deb; j<res->j_fin-res->j_debut+1; j++, jg++)
		{
			if( jg < 0 || jg >= (g->j_fin - g->j_debut +1) || 
				ig < 0 || ig >= (g->i_fin - g->i_debut +1 ) )
				etat = 0; 
			else 
				etat = g->plateau[ig][jg].etat; 

			res->plateau[i][j].etat = etat; 
		}
	}

	return res; 
}

void coller( Grille * or, Grille * g, int x, int y )
{
	int i,j; 	
	int ig, jg; 

	for( i=x, ig=1; i< (x + g->i_fin - g->i_debut -1); i++, ig++ )
	{
		for( j=y, jg=1; j< (y + g->j_fin - g->j_debut -1); j++, jg++ )
		{
			if( !(j < 0 || j >= (or->j_fin - or->j_debut +1) || 
				i < 0 || i >= (or->i_fin - or->i_debut +1 ) ) )
				or->plateau[i][j].etat = g->plateau[ig][jg].etat; 

		}
	}
}

liste explode_grille( Grille * g, int nb )
{
	int largeur = g->i_fin - g->i_debut +1; 
	int t = ceil(largeur / (float)nb); 
	int i; 
	int d=0, f=t; 
	Grille * gtmp; 
	coupe_capsule * tmp; 
	liste l = liste_init(); 

	for( i=0; i<nb; i++ )
	{
		gtmp = couper(g, 0, g->i_fin-g->i_debut+1, d, f); 
		tmp = cc_nouveau(gtmp, 0, d);
		d+=t;
		f+=t; 
		liste_ajt(l, tmp); 
	}
	
	return l; 
}

Grille * implode_grille(Grille *g, liste l )
{
	coupe_capsule * tmp; 
	
	while( (tmp=liste_suiv(l) )!=NULL )
	{
		coller(	g, tmp->g, tmp->x, tmp->y);
	}

	return g; 
}

coupe_capsule * cc_nouveau(Grille * g, int x, int y )
{
	coupe_capsule * c = malloc( sizeof(coupe_capsule) ); 
	c->g = g; 
	c->x = x; 
	c->y = y; 
	c->etat = NON_TRAITER;
	return c; 
}

void cc_free(coupe_capsule * c )
{
	if( c->g != NULL )
		free_grille(c->g); 

	free(c); 	
}

void cb_cc_free( void * c )
{
	cc_free(c); 
}
