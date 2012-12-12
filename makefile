Objets=file.o liste.o grille.o console.o 

All : main serveur client 

main : main.c ${Objets}
	gcc -Iinclude -o $@ main.c ${Objets}

serveur : serveur.o ${Objets} str_client.o liste-gen.o 
	gcc -g -Wall -Iinclude -o serveur ${Objets} serveur.o str_client.o liste-gen.o 

client : ${Objets} client.o 
	gcc -g -Wall -Iinclude -o client ${Objets} client.o

%.o: %.c 
	gcc -Wall -Iinclude -g -c $<

clean:
	rm *.o *~ include/*~ main
