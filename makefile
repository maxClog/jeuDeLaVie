Objets= file.o liste.o grille.o console.o 

%.o: %.c 
	gcc -Wall -Iinclude -g -c $<

main : main.c 
	gcc -o $@ main.c ${Objets}

serveur : serveur.o grille.o file.o liste.o
	gcc -g -Wall -Iinclude -o serveur serveur.o grille.o file.o liste.o

client : client.o grille.o file.o liste.o
	gcc -g -Wall -Iinclude -o client client.o grille.o file.o liste.o


clean:
	rm *.o *~ include/*~ main
