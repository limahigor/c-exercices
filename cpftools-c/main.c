#include <stdio.h>
#include <string.h>
#include "cpftools.h"

int main(int argc, char *argv[]){

	if(argc > 1){
		printf("%i %i", strlen(argv[1]), strlen("gen"));

		if(argv[1] == "check"){
			if(argv[2] == NULL){
				printf("Teste check sem --input\n");
			}else if(argv[2] == "-i" || argv[2] == "--input"){
				printf("Teste check com --input\n");
			}else{
				printf("Error argv3\n");
			}
		}else if(argv[1] == "gen"){
			printf("Teste Gen");
		}else if(argv[1] == "--help" || argv[1] == "-h"){
			printf("teste help\n");
		}else{
			printf("Error argv\n");
		}
	}else{
		printf("Error argc\n");
	}

	return 0;
}