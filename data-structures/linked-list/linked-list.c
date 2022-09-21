#include <stdio.h>
#include <stdlib.h>

struct node_s{
	int item;
	struct node_s *next;
};

struct lists_s{
	struct node_s *head, *tail;
};

void list_clear(struct lists_s *list){
	struct node_s *aux, *parent;

	parent = list->head;
	aux = parent->next;
	while(aux != aux->next){
		parent->next = aux->next;
		free(aux);
		aux = parent->next;
	}
}

void list_delete(struct lists_s *list){
	list_clear(list);

	free(list->head);
	list->head = NULL;
	
	free(list->tail);
	list->tail = NULL;
}

void list_print(struct lists_s *list){
	struct node_s *aux;

	aux = list->head->next;
	while(aux != aux->next){
		printf("V: %i\n", aux->item);
		aux = aux->next;
	}
}

void list_insert(struct lists_s *list, int item){
	struct node_s *new_node;
	new_node = (struct node_s *)malloc(sizeof(struct node_s));
	new_node->item = item;
	new_node->next = list->head->next;
	list->head->next = new_node;
}

void list_create(struct lists_s **list){
	struct lists_s *aux;

	aux = (struct lists_s *)malloc(sizeof(struct lists_s));

	aux->head = (struct node_s *)malloc(sizeof(struct node_s));
	aux->tail = (struct node_s *)malloc(sizeof(struct node_s));
	aux->head->next = aux->tail;
    	aux->tail->next = aux->tail;

    *list = aux;
}

int main(){
	struct lists_s *list = NULL;

	list_create(&list);
	list_insert(list, 9);
	list_insert(list, 13);
	list_insert(list, 12);
	list_insert(list, 12);
	list_insert(list, 12);
	list_insert(list, 12);

	list_print(list);
	list_clear(list);
	printf("TESTE\n");
	list_print(list);

	return 0;
}
