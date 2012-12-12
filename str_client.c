#include "str_client.h" 

str_client * strc_new()
{
	str_client * s; 
	s = malloc( sizeof(str_client) ); 
	return s; 
}

void strc_free(str_client * s )
{
	free(s); 
}

void cb_strc_free( void * s )
{
	strc_free(s); 
}
