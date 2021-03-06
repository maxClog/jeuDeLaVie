#include "include/liste.h"

#include <math.h>

Liste * nouvelleListe()
{
	return NULL;
}

Liste * ajoutTete(Grille * g, Liste * l)
{
	if(listeEstVide(l))
	{
		l = ajoutQueue(g, l);
	}
	else
	{
		StrListe * s = (StrListe*)malloc(sizeof(Liste));
		s->g = g;
		s->suiv = l;
		l = s;
	}
	return l;
}

Liste * ajoutQueue(Grille * g, Liste * l)
{
	StrListe * s = (StrListe*)malloc(sizeof(StrListe));
	s->g = g;
	s->suiv = NULL;
	
	if(listeEstVide(l))
	{
		l = s;
	}
	else
	{
		Liste * q = l;
		while(q->suiv != NULL)
			q = q->suiv;
		q->suiv = s;
	}
	return l;
}

Liste * supprTete(Liste * l)
{
	if(listeEstVide(l) || l->suiv == NULL)
	{
		return NULL;
	}
	else
	{
		StrListe * save = l;
		l = l->suiv;
		free(save);
	}
	return l;
}

Liste * supprQueue(Liste * l)
{
	if(listeEstVide(l) || l->suiv == NULL)
		return NULL;
	else
	{
		Liste * q = l;
		while(q->suiv->suiv != NULL)
			q = q->suiv;
		free(q->suiv);
		q->suiv = NULL;
	}
	return l;
}

int listeEstVide(Liste * l)
{
	if(l == NULL)
		return 1;
	else
		return 0;
}

int tailleListe(Liste * l)
{
	int compteur = 0;
	if(listeEstVide(l))
		return 0;
	else
	{
		Liste * q = l;
		while(q != NULL)
		{
			compteur++;
			q = q->suiv;
		}
		return compteur;
	}
}

void afficherListe(Liste * l)
{
	Liste * q = l;
	do
	{
		afficherGrille(q->g);
		printf("\n\r");
		printf("(%d,%d) : (%d,%d)\n\r", q->g->i_debut, q->g->i_fin, q->g->j_debut, q->g->j_fin);
		q = q->suiv;
	}while(q != NULL);
}

/**
 * Parcours l'ensemble du plateau
 * Quand on arrive sur une cellule vivante et non marqué, on lance l'algorithme de découpage
 * Il retournera une grille qu'on ajoutera dans la liste
 * On retourne cette liste qui devra être envoyé aux différents clients
 */
Liste * parcoursGrille(Grille * g)
{
	int i,j;
	
	// Initialisation de la liste
	Liste * l = nouvelleListe();
	Grille * h = NULL;
	
	for(i=0;i<=(g->i_fin-g->i_debut);i++)
	{
		for(j=0;j<=(g->j_fin - g->j_debut);j++)
		{
			if(g->plateau[i][j].etat == 1 && g->plateau[i][j].marquer == 0)
			{
				h = decoupe(g, i, j);
				l = ajoutQueue(h, l);
			}
		}
	}
	return l;
}

Liste * decoupeServeur(int nbClients, Grille * g_princ)
{
	Liste * l = nouvelleListe();
	int hauteur = g_princ->i_fin - g_princ->i_debut + 1;
	int largeur = g_princ->j_fin - g_princ->j_debut + 1;
	int nbCellules = hauteur * largeur;
	int nbCellulesMax = 90*90;
	int nbDeTrames;
	int debut, fin;
	int i,j,k,m;
	
	if(nbClients == 0)
		return NULL;
	else if(nbClients == 1)
	{
		if(nbCellules <= nbCellulesMax)
		{
			l = ajoutQueue(g_princ, l);
			return l;
		}
	}
	else if(nbClients > largeur)
		nbClients = largeur;
	
	nbDeTrames = largeur / nbClients;
	debut = 0;
	fin = debut + nbDeTrames;
	
	// Decoupe de la grille en nbDeTrames parties
	for(k=0;k<nbClients;k++)
	{
		// Initialise la grille à la bonne taille
		Grille * g = init(hauteur, fin-debut+1);
		g->j_debut = debut;
		g->j_fin = fin;
		g->i_debut = 0;
		g->i_fin = hauteur-1;
		
		// On decoupe une trame
		for(j=debut, m=0;j<=fin;j++, m++) // Parcours de la largeur
		{
			for(i=0;i<hauteur;i++) // Parcours de la hauteur
			{
				g->plateau[i][m] = g_princ->plateau[i][j];
			}
		}
		
		// On enregistre la grille
		l = ajoutQueue(g, l);
		
		// On rééquilibre les variables
		debut = fin-1;
		fin = (k == nbClients - 2 ? largeur - 1 : debut + nbDeTrames);
	}
	return l;
}

Liste * decoupeClient(int nbCores, Grille * g_princ)
{
	Liste * l = nouvelleListe();
	int hauteur = g_princ->i_fin - g_princ->i_debut + 1;
	int largeur = g_princ->j_fin - g_princ->j_debut + 1;
	int nbDeTrames;
	int debut, fin;
	int i,j,k,m;
	
	if(nbCores == 0)
		return NULL;
	else if(nbCores == 1)
	{
		l = ajoutQueue(g_princ, l);
		return l;
	}
	else if(nbCores > hauteur)
		nbCores = hauteur;
	
	nbDeTrames = hauteur / nbCores;
	debut = 0;
	fin = debut + nbDeTrames;
	
	// Decoupe de la grille en nbDeTrames parties
	for(k=0;k<nbCores;k++)
	{
		// Initialise la grille à la bonne taille
		Grille * g = init(fin-debut+1, largeur);
		g->j_debut = 0;
		g->j_fin = largeur-1;
		g->i_debut = debut;
		g->i_fin = fin;
		
		// On decoupe une trame
		for(j=0;j<largeur;j++) // Parcours de la largeur
		{
			for(i=debut, m=0;i<=fin;i++, m++) // Parcours de la hauteur
			{
				g->plateau[m][j] = g_princ->plateau[i][j];
			}
		}
		
		// On enregistre la grille
		l = ajoutQueue(g, l);
		
		// On rééquilibre les variables
		debut = fin;
		fin = (k == nbCores - 2 ? hauteur - 1 : debut + nbDeTrames);
	}
	return l;
}

/**
 * Réassemble la grille avec les nouveau paramètres
 * @params : La grille principale contenant toutes les cellules
 * @params : La liste de grille retournées par les clients
 * @return : La grille complete que l'on va affiché
 */
Grille * recollageGrille(Grille * g, Liste * l)
{
	if(listeEstVide(l))
	{
		return g;
	}
	else
	{
		Liste * q = l;
		do
		{
			g = assembler(q->g, g);
			q = q->suiv;
		}while(q != NULL);
	}
	return g;
}

/**
 * Integre la premiere grille passé en parametre, dans la deuxieme
 * @param : La grille retournée par un des clients
 * @param : La grille principale contenant toutes les cellules
 * @return : La grille principale avec la nouvelle grille insérer
 */
Grille * assembler(Grille * g, Grille * main)
{	
	int i,j;
	int k,l;
	for(i=g->i_debut, k=0;i<=g->i_fin;i++, k++)
	{
		for(j=g->j_debut, l=0;j<=g->j_fin;j++, l++)
		{
			// On change la cellule s'il y a un changement d'etat de morte à vivante
			if(main->plateau[i][j].etat == 0 && g->plateau[k][l].etat == 1)
				main->plateau[i][j] = g->plateau[k][l];
		}
	}
	return main;
}
