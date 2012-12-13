Objets=file.o liste.o grille.o console.o 

All : main

main : main.c ${Objets}
	gcc -o $@ main.c ${Objets}

%.o: %.c 
	gcc -Wall -Iinclude -g -c $<

clean:
	rm *.o *~ include/*~ main client serveur
