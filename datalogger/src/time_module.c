#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <gtk/gtk.h>
#include "../include/time_module.h"

struct count_s{
	unsigned int seconds, minutes, hours, total_seconds;
};

int get_count_second(count_h count){
	return count->seconds;
}

int get_count_minute(count_h count){
	return count->minutes;
}

int get_total_seconds(count_h count){
	return count->total_seconds;
}

char *get_count_string(count_h count){
	char *time_string = calloc(100, sizeof(char));

	count->seconds++;
	count->total_seconds++;

	if(count->seconds > 59){
		count->seconds = 0;
		count->minutes +=1;
	}

	if(count->minutes > 59){
		count->minutes = 0;
		count->hours += 1;
	}

	sprintf(time_string, "%.2i:%.2i:%.2i", count->hours, count->minutes, count->seconds);

	return time_string;
}

gboolean count_init(count_h *contador){
	count_h aux;

	if(!contador)
		return FALSE;

	aux = malloc(sizeof(*aux)); 

	if(!aux)
		return FALSE;

	memset(aux, 0, sizeof(*aux));

	aux->total_seconds = 0;
	aux->seconds = 0;
	aux->minutes = 0;
	aux->hours = 0;

	*contador = aux;

	return TRUE;
}

void get_time(struct tm **atual){
	struct tm *aux;
	time_t segundos;

	time(&segundos);

	aux = localtime(&segundos);

	*atual = aux;
}

char *get_date_string(){
	struct tm *atual;
	time_t segundos;
	char *time_string = calloc(100, sizeof(char));

	time(&segundos);

	atual = localtime(&segundos);

	sprintf(time_string, "%.2i/%.2i/%.2i", atual->tm_mday, atual->tm_mon+1, atual->tm_year+1900);

	return time_string;
}

char *get_time_string(){
	struct tm *atual;
	time_t segundos;
	char *time_string = calloc(100, sizeof(char));

	time(&segundos);

	atual = localtime(&segundos);

	sprintf(time_string, "%.2i:%.2i:%.2i", atual->tm_hour, atual->tm_min, atual->tm_sec);

	return time_string;
}

gboolean count_free(count_h count){
	if(!count){
		printf("Invalido!");
		return FALSE;
	}

	g_free(count);
	return TRUE;
}