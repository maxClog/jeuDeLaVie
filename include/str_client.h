#ifndef STR_CLIENT_H
#define STR_CLIENT_H

#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <pthread.h>
#include "grille.h" 

#define CLIENT_ATTENTE 1
#define CLIENT_DECONNECTE 2
#define CLIENT_TRAITEMENT 3

typedef struct {
	char host[20]; 
	pthread_t * t; 
	pthread_mutex_t * mutex; 
	pthread_cond_t * cond; 
	int etat; 
	Grille * g; 
} str_client; 

str_client * strc_new();
void strc_free(str_client * s );
void cb_strc_free( void * s ); 
void * client_routing(void * arg ); 

#endif 
