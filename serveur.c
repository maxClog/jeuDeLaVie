#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <unistd.h>
#include <sys/time.h>
#include "grille.h"
#include "str_client.h" 
#include "console.h" 
#include "liste-gen.h" 

#define TBUFF 256

int main (int argc, char *argv[])
{
	Grille *pg = lectureFichier("models/canon-glisseur.txt");
	Grille *pres ; // pointeur sur la grille résultat 
	int c=1, t, nfds; 
	float vit=1; 
	enum clnt_stat stat ;
	struct timeval tv = { 0, 0 };
	struct sockaddr_in client_addr; 
	fd_set readfds, readfds_cp;
	char buf[TBUFF]; 
	int tmes;
	struct sockaddr_in my_addr; 
	int sock_client; 
	socklen_t addrlen; 
	liste lsc=liste_init(); 
	int port=strtol(argv[1], NULL, 10); 
	str_client * strc; 

	if (argc != 2)
	{
		fprintf(stderr, "Usage : %s <no_port>\n", argv[0]) ;
		exit(1) ;
	}

	/*
		Création de la socket pour les vendeurs 
	*/


	if( (sock_client = socket(AF_INET, SOCK_DGRAM, IPPROTO_UDP) ) == -1 )
	{
		perror(NULL); 
		exit(EXIT_FAILURE); 
	}

	my_addr.sin_family = AF_INET; 
	my_addr.sin_port = htons(port); 
	my_addr.sin_addr.s_addr = htonl(INADDR_ANY);
	addrlen = sizeof(struct sockaddr_in); 

	if( bind(sock_client, (struct sockaddr * )&my_addr, addrlen) == -1 )
	{
		perror(NULL); 
		close(sock_client); 
		exit(EXIT_FAILURE); 
	}
	
	// Fin init écoute client 

	mode_raw(1); 

	FD_ZERO(&readfds);
	FD_SET(STDIN_FILENO, &readfds);
	FD_SET(sock_client, &readfds);
	nfds = sock_client+1; 

	while(c)
	{

		while( strc = liste_suiv(lsc) )
		{
			stat = callrpc( strc->host, PROGNUM, VERSNUM, 1, 
				(xdrproc_t)xdr_grille, (char*)&pg, 
				(xdrproc_t)xdr_grille, (char *)&pres);

			if (stat != RPC_SUCCESS)
			{
				fprintf(stderr,"client, erreur dans callrpc : ") ;
				clnt_perrno(stat) ;
				fprintf(stderr,"\n") ;
				liste_sup(lsc, strc, cb_strc_free ); 
			}
			else
			{
				free(pg);
				pg = pres; 
			}
		}

		readfds_cp = readfds; 

		if( select(nfds, &readfds_cp, NULL, NULL, &tv) != -1 )
		{
			if( FD_ISSET(STDIN_FILENO, &readfds_cp ) )
			{
				switch( t = getchar() )
				{
					case 'q' : 
						c=0; 
					break; 
					case 'p' : 
						vit/=2;
					break; 
					case 'm' : 
						if( vit < 6 )
							vit*=2; 
					break; 
					case 'r' : 
						free_grille(pg); 
						pg = lectureFichier(argv[1]);
						vit=1; 
					break; 
					default : 
						printf("Touche %c préssé\n\r", t); 
				}
			}

			if( FD_ISSET(sock_client, &readfds_cp ) )
			{
				memset(buf, '\0', TBUFF);

				if( ( tmes=recvfrom( sock_client, buf, TBUFF, 0, (struct sockaddr *)&client_addr, &addrlen) ) == -1 )
				{
					perror(NULL);
				}
				else
				{
					// Ajout du client à la liste. 
					strc = strc_new(); 
					strcpy(strc->host, inet_ntoa(client_addr.sin_addr) ); 
					liste_ajt(lsc, strc); 


				}

			}

			if( c && tv.tv_sec == 0 && tv.tv_usec == 0 )
			{
				afficherGrille(pg);
			}

			tv.tv_usec = 500000*vit;
		}
	}

	mode_raw(0); 
	free_grille(pg); 
	return 0 ;  
}
