#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#define TAM 15

struct st{
	unsigned char id;
	unsigned int num;
};

int main(int arc, char *argv[]){
	struct st s;

	s.id = 3;
	s.num = 10;

	printf("%zu\n", sizeof(struct st));
	
	return 0;
}