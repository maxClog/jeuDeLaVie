Objets=file.o liste.o grille.o console.o 

All : main

main : main.c ${Objets}
	gcc -Iinclude -o $@ main.c ${Objets}

serveur : serveur.o ${Objets} str_client.o liste-gen.o 
	gcc -g -Wall -Iinclude -o serveur ${Objets} serveur.o str_client.o liste-gen.o -lpthread -D_REENTRANT -DLinux 

client : ${Objets} client.o 
	gcc -g -Wall -Iinclude -o client ${Objets} client.o -lpthread -D_REENTRANT -DLinux 

%.o: %.c 
	gcc -Wall -Iinclude -g -c $< -lpthread -D_REENTRANT -DLinux 

clean:
	rm *.o *~ include/*~ main client serveur
