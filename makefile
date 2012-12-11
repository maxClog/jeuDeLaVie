Objets=file.o liste.o grille.o console.o 

All : main serveur client 

main : main.c ${Objets}
	gcc -o $@ main.c ${Objets}

serveur : serveur.o ${Objets}
	gcc -g -Wall -Iinclude -o serveur serveur.o grille.o file.o liste.o

client : ${Objets} client.o 
	gcc -g -Wall -Iinclude -o client client.o grille.o file.o liste.o

%.o: %.c 
	gcc -Wall -Iinclude -g -c $<

clean:
	rm *.o *~ include/*~ main
