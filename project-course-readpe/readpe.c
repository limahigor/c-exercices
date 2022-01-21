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

void print_cabecalho(){
	
}

int main(int argc, char *argv[]){
	FILE *fh;
	unsigned char buffer[32];

	if(argc != 2){
		usage();
	}

	PEFILE pe;

	pe.filepath = argv[1];

	petest_init(&pe);

	if(petest_ispe(&pe))
		printf("O arquivo eh um PE, continuando...\n\n");
	else
		fatal("O arquivo nao eh um PE");

	printf("File: %s\n", pe.filepath);
	printf("MZ Header: %x\n", pe.hdr_dos->e_magic);
	printf("COFF Header offset: %x\n", pe.hdr_dos->e_lfanew);

	return 0;
}