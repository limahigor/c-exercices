#include "store.h"

void *libstore_create(TREE *p){
	p->root = (PRODUCT *)malloc(sizeof(PRODUCT)); //p->root = NULL;
	p->head = (PRODUCT *)malloc(sizeof(PRODUCT)); //p->left = NULL;
}

void libstore_destroy(PRODUCT *p){
	if(p)
		free(p);
}

void libstore_setid(PRODUCT *p){
	p->id = 15;
}

PRODUCT *libstore_insert(TREE *n, PRODUCT *p, int id, int qnt, char *name){
	PRODUCT *new_node;

	new_node = (PRODUCT *)malloc(sizeof(PRODUCT));
	if(p == NULL){
		new_node->left = NULL;
		new_node->right = NULL;
		n->head = new_node;
		n->root = new_node;
	}

	if(p != NULL){
		p->next = new_node;
		n->root = n->root->left;
	}

	new_node->next = NULL;


	//Inserindo informacoes
	new_node->id = id;
	new_node->qnt = qnt;

	new_node->name = (char*)malloc(sizeof(strlen(name)-1));
	strcpy(new_node->name, name);

	return new_node;
}