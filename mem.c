#include <stdio.h>
#include <stdlib.h>
#define TAM 15

#define MALLOC(ptr, size){\
	ptr = malloc(size);\
	if(ptr == NULL){\
		fprintf(stderr, "memoria insuficiente!");\
		exit(1);\
	}\
}

void *malloc_s(size_t size){
	void *ptr;

	ptr = malloc(size);
	if(ptr == NULL){
		fprintf(stderr, "memoria insuficiente!");
		exit(1);
	}

	return ptr;
}

int main(int arc, char *argv[]){
	int *p = NULL;

	p = malloc_s(TAM*sizeof(int));

	for(int c = 0; c < TAM; c++){
		p[c] = TAM + c%8 + TAM%3 + c%3;
	}

	for(int c = 0; c < TAM; c++){
		printf("%d:[%d]\n", c+1, c[p]);
	}

	putchar('\n');

	return 0;
}