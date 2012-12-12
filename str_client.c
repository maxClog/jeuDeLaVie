#include "str_client.h" 

str_client * strc_new(char * host)
{
	str_client * s; 
	s = malloc( sizeof(str_client) ); 
	s->t = malloc( sizeof(pthread_t) ); ; 
	s->mutex =malloc(sizeof(pthread_mutex_t) );
	s->cond=malloc(sizeof(pthread_cond_t) ); 
	s->etat=CLIENT_ATTENTE; 
	s->g = NULL; 
	int err;

	strcpy(s->host, host); 

	if( (err = pthread_create( s->t, NULL, client_routing, s) ) )
	{
		fprintf(stderr, "%s", strerror(err) ); 
	}

	pthread_mutex_init(s->mutex, NULL); 
	pthread_cond_init(s->cond, NULL);
	return s; 
}

void strc_free(str_client * s )
{
	free(s->cond);
	free(s->mutex);
	free(s->t); 
	free(s); 
}

void cb_strc_free( void * s )
{
	strc_free(s); 
}

void * client_routing(void * arg )
{
	str_client * s = arg; 
	int cont=1; 
	Grille * pres; 
	enum clnt_stat stat; 

	while( cont )
	{
		s->etat = CLIENT_ATTENTE; 
		pthread_cond_wait(s->cond, s->mutex); 
		s->etat = CLIENT_TRAITEMENT; 

		stat = callrpc( s->host, PROGNUM, VERSNUM, 1, 
			(xdrproc_t)xdr_grille, (char*)&(s->g), 
			(xdrproc_t)xdr_grille, (char *)&pres);

		if (stat != RPC_SUCCESS)
		{
			fprintf(stderr,"client, erreur dans callrpc : ") ;
			clnt_perrno(stat) ;
			fprintf(stderr,"\n") ;
			cont=0; 
			free_grille(s->g);
			s->etat = CLIENT_DECONNECTE; 
		}
		else
		{
			free_grille(s->g);
			s->g = pres; 
		}
	}

	return NULL; 	
}
