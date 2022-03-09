#ifndef PROCESSOR_H
#define PROCESSOR_H

typedef struct registro_s *registro_h;
typedef struct list_s *list_h;
typedef struct resume_s resume_h;

int processor_interrupt(int var);

void processor_file_min(list_h list);
void processor_file_resume(list_h list);

void processor_register(registro_h *registro, int adc, int id, list_h list);

void list_create(list_h *list);

guint get_count_file_min(list_h list);

void reset_count_file_min(list_h list);

void set_count_file_resume(list_h list, gint count_resume);

//Test functions
void print_id(registro_h registro);

#endif