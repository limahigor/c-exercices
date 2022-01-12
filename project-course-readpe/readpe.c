#include <stdio.h>
#include <stdlib.h>

void fatal(char *msg){
	fprintf(stderr, "Erro: %s\n", msg);
	exit(1);
}

void usage(){
	printf("Uso: readpe [arquivo]\nreadpe --help para mais informacoes\n");
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

	if(buffer[0] != 'M' || buffer[1] != 'Z' || buffer[2] != 'P'){
		fatal("o arquivo nao parece ser um executavel");
	}

	return 0;
}