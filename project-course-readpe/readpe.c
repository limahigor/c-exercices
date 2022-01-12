#include <stdio.h>
#include <stdlib.h>
#include "lib/petest.h"

void fatal(char *msg){
	fprintf(stderr, "Erro: %s\n", msg);
	exit(1);
}

void usage(){
	printf("Uso: readpe [arquivo.exe]\nreadpe --help para mais informacoes\n");
	exit(1);
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
	fclose(fh);
	// printf("%d\n", ispe(buffer));
	if(petest_ispe(buffer))
		fatal("o arquivo nao parece ser um executavel");

	return 0;
}