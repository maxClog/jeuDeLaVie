#include "grille.h"

#define TAILLE 16 * 1024 

int main (int argc, char *argv[])
{
	Grille *pg = init(93,93);
	Grille *pres ; // pointeur sur la grille résultat 
	enum clnt_stat stat ;

	if (argc != 3)
	{
		fprintf(stderr, "Usage : %s <machine_serveur> <no procedure>\n", argv[0]) ;
		exit(1) ;
	}

	// call rpc procedure
	stat = callrpc(argv[1], PROGNUM, VERSNUM, atoi(argv[2]), (xdrproc_t)xdr_grille, (char*)&pg, (xdrproc_t)xdr_grille, (char *)&pres) ;

	if (stat != RPC_SUCCESS)
	{
		fprintf(stderr,"client, erreur dans callrpc : ") ;
		clnt_perrno(stat) ;
		fprintf(stderr,"\n") ;
		return 1 ;
	}

	afficherGrille(pg); 
	afficherGrille(pres); 

	printf("Poulette\n"); 
	free_grille(pres);
	printf("Poulette 2\n"); 
	free_grille(pg); 
	return 0 ;  
}
