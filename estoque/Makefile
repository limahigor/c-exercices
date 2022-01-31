all:
	gcc -o estoque.o estoque.c -c
	gcc -o estoque estoque.o lib/libstore.a
	rm -f estoque.o
clean:
	rm -f estoque