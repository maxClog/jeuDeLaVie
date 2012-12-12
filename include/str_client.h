#ifndef STR_CLIENT_H
#define STR_CLIENT_H

#include <stdlib.h>

typedef struct {
	char host[20]; 
} str_client; 

str_client * strc_new();
void strc_free(str_client * s );
void cb_strc_free( void * s ); 

#endif 
