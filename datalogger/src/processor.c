#include <math.h>
#include <stdio.h>
#include <gtk/gtk.h>
#include <time.h>
#include <stdlib.h>
#include <fcntl.h>
#include <errno.h>
#include <sys/types.h>
#include <sys/stat.h>
#include "../include/processor.h"
#include "../include/time_module.h"

#pragma pack(push, 1)
struct registro_s{
	int id;
	int val;
	int min, sec, hour;
	int day, month, year;
};
#pragma pop

#pragma pack(push, 1)
struct resume_s{
	int max_val;
	int min_val;
	double med_val;
	double rms_val;
};
#pragma pop

struct list_s{
	GList *list_reg;
	GList *list_resume;
	guint count_file_min;
	guint count_file_resume;
};

void list_create(list_h *list){
	list_h aux;
	if(!list)
		printf("Erro\n");

	aux = malloc(sizeof(*aux));

	if(!aux)
		printf("Erro");

	memset(aux, 0, sizeof(*aux));

	aux->list_reg = NULL;
	aux->list_resume = NULL;
	aux->count_file_min = 0;
	aux->count_file_resume = 0;

	*list = aux;
}

guint get_count_file_min(list_h list){
	return list->count_file_min;
}

void reset_count_file_min(list_h list){
	list->count_file_min = 0;
}

int processor_interrupt(int var){
	return (int)1800.0*sin(    2.0*3.1415*60.0*var/2000.0)+
           (int)1100.0*sin(5.0*2.0*3.1415*60.0*var/2000.0)+
           (int) 950.0*sin(9.0*2.0*3.1415*60.0*var/2000.0);
}

void processor_register(registro_h *registro, int adc, int id, list_h list){
	struct tm *time;
	registro_h aux;

	get_time(&time);

	if(!registro)
		printf("Erro\n");

	aux = malloc(sizeof(*aux));

	if(!aux)
		printf("Erro\n");

	memset(aux, 0, sizeof(*aux));

	aux->id = id;
	aux->val = adc;
	aux->sec = time->tm_sec;
	aux->min = time->tm_min;
	aux->hour = time->tm_hour;
	aux->day = time->tm_mday;
	aux->month = time->tm_mon+1;
	aux->year = time->tm_year+1900;

	*registro = aux;

	list->list_reg = g_list_append(list->list_reg, *registro);
}

void print_id(registro_h registro){
	printf("%i\n", registro->id);
}

void processor_file_min(list_h list){
	char *nome_arq = (char*)malloc(sizeof(char)*30);
	register int i;

	struct tm *time;
	get_time(&time);

	sprintf(nome_arq, "../bin/%.2d-%.2d-%.4d_%.2d-%.2d-%.2d.bin", time->tm_mday,
													  			  time->tm_mon+1,
													  			  time->tm_year+1900,
													  			  time->tm_hour,
																  time->tm_min,
																  time->tm_sec);

	int fd = open(nome_arq, O_WRONLY | O_CREAT, 0764);

	if(fd == -1)
		printf("Erro ao abrir arquivo!\n");

	register guint pos = (g_list_length(list->list_reg) - 60);

	for(i = 0; i < 60; i++){
		registro_h aux = (registro_h)g_list_nth_data(list->list_reg, pos+i);
		write(fd, aux, sizeof(aux));
	}

	close(fd);

	list->count_file_min += 1;

	list->list_resume = g_list_append(list->list_resume, nome_arq);
}

void processor_file_resume(list_h list){
	//inicializa a estrutura que vai conter os valores de resumo dos minutos pré estabelecidos
	resume_h resume;
	resume.med_val = 0;
	resume.rms_val = 0;
	int soma_med = 0, soma_rms = 0;

	char *arq_resume = (char*)malloc(sizeof(char)*37);

	struct tm *time;
	get_time(&time);

	mkdir("../bin", S_IRWXU | S_IRWXG | S_IRWXO);
	sprintf(arq_resume, "../bin/resume/%.2d-%.2d-%.4d_%.2d-%.2d-%.2d.bin", time->tm_mday,
													  			  time->tm_mon+1,
													  			  time->tm_year+1900,
													  			  time->tm_hour,
																  time->tm_min,
																  time->tm_sec);

	GList *listrunner = g_list_first(list->list_resume);

	while(listrunner){
		//abre o arquivo contendo os registros dos minutos
		int fd_min = open(listrunner->data, O_RDONLY);

		if(fd_min == -1)
			printf("Erro ao abrir arquivo!\n");

		//Criando e alocando memoria pra estrutura temporaria pra ler os registros
		registro_h temp = malloc(sizeof(*temp));

		if(!temp)
			printf("Erro alocar memoria");
		memset(temp, 0, sizeof(*temp));

		read(fd_min, temp, sizeof(temp));

		//inicializando valores maximos e minimos
		if(listrunner == g_list_first(list->list_resume))
			resume.max_val = resume.min_val = temp->val;

		for(int i = 0; i < 60; i++){
			read(fd_min, temp, sizeof(temp));
		
			//verificando valor maximo
			if(temp->val > resume.max_val)
				resume.max_val = temp->val;

			//verificando valor minimo
			if(temp->val < resume.min_val)
				resume.min_val = temp->val;

			//soma o valor pra calcular a media
			soma_med += temp->val;

			//soma os quadrados pra calcular o rms
			soma_rms += temp->val*temp->val;

		}

		free(temp);
		listrunner = g_list_next(listrunner);
		close(fd_min);
	}

	//calcula o valor medio
	resume.med_val = soma_med/(list->count_file_resume*60.0);

	//calcula o valor rms
	resume.rms_val = sqrt(soma_rms/(list->count_file_resume*60.0));

	//tenta criar o diretorio para o arquivo de resumo, caso não exista
	mkdir("../bin/resume", S_IRWXU | S_IRWXG | S_IRWXO);

	//cria e abre o arquivo
	int fd_resume = open(arq_resume, O_WRONLY | O_CREAT, 0764);
	if(fd_resume == -1)
		printf("Erro ao abrir o arquvi resumo!\n");

	//escreve os dados
	write(fd_resume, &resume, sizeof(resume));

	reset_count_file_min(list);
	close(fd_resume);
	free(arq_resume);
}

void set_count_file_resume(list_h list, gint count_resume){
	list->count_file_resume = count_resume;
}