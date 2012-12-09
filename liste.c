#include "include/liste.h"

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

void afficherListe(Liste * l)
{
	Liste * q = l;
	do
	{
		afficherGrille(q->g);
		printf("\n-------------------------------\n");
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
	
	for(i=0;i<(g->i_fin-g->i_debut);i++)
	{
		for(j=0;j<(g->j_fin - g->j_debut);j++)
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
