#include "str_client.h" 

str_client * strc_new(char * host)
{
	str_client * s; 
	s = malloc( sizeof(str_client) ); 
	s->t = malloc( sizeof(pthread_t) ); ; 
	s->mutex =malloc(sizeof(pthread_mutex_t) );
	s->cond=malloc(sizeof(pthread_cond_t) ); 
	s->etat=CLIENT_ATTENTE; 
	s->sorti = NULL; 
	s->entre = NULL; 
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
	if( s->t != NULL )
	{
		printf("Cancel\n"); 
		if( pthread_cancel(*(s->t)) != 0 )
		{
			printf("Raté\n"); 
		}
		if( pthread_join( *(s->t), NULL) != 0 )
		{
			printf("doublement raté\n"); 
		}
	}

	if( s->entre != NULL )
	{
		printf("free entre\n"); 
		free_grille(s->entre); 
	}

	if( s->sorti != NULL )
	{
		printf("free sorti\n"); 
		free_grille(s->sorti);
	}

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
	enum clnt_stat stat; 

	while( cont )
	{
		pthread_cond_wait(s->cond, s->mutex); 

		s->sorti = NULL; 
		s->etat = CLIENT_TRAITEMENT; 

		stat = callrpc( s->host, PROGNUM, VERSNUM, 1, 
			(xdrproc_t)xdr_grille, (char*)&(s->entre), 
			(xdrproc_t)xdr_grille, (char *)&(s->sorti) );

		if (stat != RPC_SUCCESS)
		{
			fprintf(stderr,"client, erreur dans callrpc : ") ;
			clnt_perrno(stat) ;
			fprintf(stderr,"\n") ;
			cont=0; 
			s->etat = CLIENT_DECONNECTE; 
			pthread_exit(NULL); 
		}

		s->etat = CLIENT_ATTENTE; 
	}

	pthread_exit(NULL); 
}
