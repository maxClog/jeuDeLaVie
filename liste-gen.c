#include "liste-gen.h"

void liste_ajt( liste lsb,  void * ele )
{
	liste_element e = malloc( sizeof(struct str_ele) ); 
	e->suiv = NULL; 
	e->ele = ele; 

	if( lsb->prem!=NULL )
	{
		e->suiv = lsb->prem; 
	}

	lsb->prem = e; 
	lsb->nb_ele++; 
	liste_debut(lsb); 
}

void * liste_suiv(liste lsb )
{
	void * tmp; 
	if( lsb->act == NULL )
	{
		liste_debut(lsb); 
		return NULL; 
	}
	else
	{
		tmp = lsb->act->ele; 
		lsb->act = lsb->act->suiv; 
		return tmp; 
	}
}

void liste_debut(liste lsb )
{
	lsb->act = lsb->prem; 
	return;
}

liste liste_init(void)
{
	liste lsb=malloc(sizeof( struct str_liste) ); ; 
	lsb->prem = NULL;
	lsb->act = NULL; 
	lsb->nb_ele=0; 
	return lsb; 
}

void liste_sup(liste lsb, void * sup, void (free_ele( void * ) ) )
{
	if ( lsb->prem == NULL )
	{
		return; 
	}

	liste_element tmp = lsb->prem; 
	liste_element tmp_avant = NULL; 

	if( tmp->ele == sup )
	{
		lsb->prem = tmp->suiv; 
		if( sup != NULL )
		{
			free_ele(sup); 
		}
		free(tmp); 
	}
	else
	{
		do 
		{
			tmp_avant = tmp; 
			tmp=tmp->suiv; 
		}
		while( tmp->ele!=sup ); 

		tmp_avant->suiv = tmp->suiv; 
		if( sup != NULL )
		{
			free(sup); 
		}
		free(tmp); 
	}
	
	lsb->nb_ele--; 
	return;
}

void liste_sup_nf(liste lsb, void * sup )
{
	liste_element tmp = lsb->prem; 
	liste_element tmp_avant = NULL; 

	if( tmp->ele == sup )
	{
		lsb->prem = tmp->suiv; 
		free(tmp); 
	}
	else
	{
		do 
		{
			tmp_avant = tmp; 
			tmp=tmp->suiv; 
		}
		while( tmp->ele!=sup ); 

		tmp_avant->suiv = tmp->suiv; 
		free(tmp); 
	}
	
	lsb->nb_ele--; 
	return;
}

void liste_free(liste lsb,  void ( free_ele( void * ) )  )
{
	liste_element tmp_avant=lsb->prem;
	liste_element tmp; 

	if( tmp_avant != NULL )
	{
		tmp = lsb->prem->suiv; 

		while( tmp != NULL ) 
		{
			if( tmp_avant->ele != NULL )
			{
				free_ele(tmp_avant->ele); 
			}
			free(tmp_avant); 
			tmp_avant = tmp; 
			tmp = tmp->suiv; 
		}

		if( tmp_avant->ele != NULL )
		{
			free_ele(tmp_avant->ele); 
		}
		free(tmp_avant); 
	}

	free(lsb); 
}

int liste_taille(liste l)
{
	return l->nb_ele; 
}
