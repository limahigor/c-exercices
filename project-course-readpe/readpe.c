#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

void fatal(char *msg){
	fprintf(stderr, "Erro: %s\n", msg);
	exit(1);
}

void usage(){
	printf("Uso: readpe [arquivo]\nreadpe --help para mais informacoes\n");
	exit(1);
}

bool ispe(const unsigned char *b){
	return(b[0] != 'M' || b[1] != 'Z' || b[2] != 'P');
}

int main(int argc, char *argv[]){
	FILE *fh;
	unsigned char buffer[32];

	if(argc != 2){
		usage();
	}

	fh = fopen(argv[1], "rb");

	if (fh == NULL)
		fatal("Arquivo nao encontrado ou sem permissao de leitura");

	if(fread(buffer, 32, 1, fh) != 1)
		fatal("nao consegui ler os 32 bytes arquivo");

	return 0;
}