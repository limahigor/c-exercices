#include <stdio.h>
#include <stdlib.h>
#include "lib/store.h"

int fatal(char *msg){
	printf("Error: %s\n", msg);
	exit(EXIT_FAILURE);
}

int main(){
	struct tree *lista;
	PRODUCT *produto = NULL;
	
	libstore_create(lista);

	produto = libstore_insert(lista, produto, 1, 15, "Arroz");
	PRODUCT *produto2 = produto;
	produto2 = libstore_insert(lista, produto2, 2, 15, "Feijao");


	printf("Nome: %s\nID: %i\nQNT: %i\n\n", produto->name, produto->id, produto->qnt);
	printf("Nome: %s\nID: %i\nQNT: %i\n\n", produto2->name, produto2->id, produto2->qnt);

	printf("Nome: %s\nID: %i\nQNT: %i\n\n", lista->head->name, lista->head->id, lista->head->qnt);
	if(lista->root == NULL)
		printf("eh nulo\n");


	return 0;
}