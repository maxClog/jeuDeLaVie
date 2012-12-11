#include "grille.h" 

Grille ** modifier(Grille ** g)
{
	unsigned int i, j ;
	static Grille * res = NULL;
	Grille * tmp = *g; 

	if ( res != NULL)
	{
		free_grille(res);
	}

	res = init(tmp->i_fin-tmp->i_debut+1, tmp->j_fin-tmp->j_debut+1);

	fprintf(stdout,"Modification\n");

	for (i=0; i<=(tmp->i_fin-tmp->i_debut); ++i)
	{
		for (j=0; j<=(tmp->j_fin-tmp->j_debut); ++j)
		{
			res->plateau[i][j].etat=1;
		}
	}

	return &res;
}

int main (void)
{
	registerrpc(PROGNUM, VERSNUM,1 ,modifier, xdr_grille, xdr_grille);
	svc_run();
	return 0;
}

