Sources=$(shell ls *.c)
Objets=$(patsubst %.c, %.o, ${Sources})

main : ${Objets} makefile
	gcc -g -o $@ ${Objets}

%.o: %.c 
	gcc -Wall -g -c $<
clean:
	rm *.o *~ include/*~ main
