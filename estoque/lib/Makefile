all:
	gcc -o libstore.o store.c -c
	ar -r libstore.a libstore.o
	rm -f libstore.o
clean:
	rm -f libstore.a