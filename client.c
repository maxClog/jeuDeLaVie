#include <unistd.h>
#include <stdlib.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <stdio.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <string.h>
#include "grille.h" 

#define TBUFF 256 

Grille ** modifier(Grille ** g)
{
	static Grille * res = NULL;

	if ( res != NULL)
	{
		free_grille(res);
	}

	fprintf(stdout,"Modification\n");
	res = evolution( grille_cpy(*g) ); 

	return &res;
}

int main (int argc, char ** argv )
{
	char buf[TBUFF]; 
	int sockfd; 
	struct sockaddr_in dest; 
	socklen_t addrlen; 
	registerrpc(PROGNUM, VERSNUM,1 ,modifier, xdr_grille, xdr_grille);

	if( argc != 3 )
	{
		printf("Usage %s <serv_addr> <port_number>\n", argv[0]); 
		exit(EXIT_FAILURE); 
	}

	if( (sockfd=socket(AF_INET, SOCK_DGRAM, IPPROTO_UDP) ) == -1 )
	{
		perror("Echèc à la création de la socket."); 
		exit(EXIT_FAILURE); 
	}

	dest.sin_family = AF_INET; 
	dest.sin_port = htons(strtol(argv[2], NULL, 10) ); 
	addrlen = sizeof(struct sockaddr_in); 

	if( inet_pton( AF_INET, argv[1], &dest.sin_addr) != 1 )
	{
		printf("inet_pton echoue\n"); 
		close(sockfd); 
		exit(EXIT_FAILURE); 
	}

	memset(buf, '\0', sizeof(char)*TBUFF); 
	strcpy(buf, "Je suis là"); 

	if( sendto( sockfd, buf, strlen(buf), 0, (struct sockaddr*)&dest, addrlen) == -1 )
	{
		close(sockfd); 
		exit(EXIT_FAILURE); 
	}

	close(sockfd); 

	printf("En attente de demande de traitement\n"); 
	svc_run();
	return 0;
}

