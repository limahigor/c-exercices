#include <stdio.h>
#include <gtk/gtk.h>
#include "../include/callbacks.h"
#include "../include/time_module.h"
#include "../include/processor.h"

gboolean update_label_time(gpointer user_data){
	GtkLabel *time_label = GTK_LABEL(g_object_get_data(G_OBJECT(user_data),"time_label"));
	GtkLabel *date_label = GTK_LABEL(g_object_get_data(G_OBJECT(user_data),"date_label"));

	gchar *t = get_time_string();
	gtk_label_set_text(time_label, t);

	t = get_date_string();
	gtk_label_set_text(date_label, t);

	free(t);
	return G_SOURCE_CONTINUE;
}

void startThread(GtkWidget *button, gpointer user_data){
	GThread   *myThread; 
	myThread = g_thread_new(NULL,(GThreadFunc) init, user_data);
}

gboolean on_start_stop_clicked(GtkWidget *button, gpointer user_data){
	gint validator;

	GObject *aux = g_object_new(G_TYPE_OBJECT, NULL);

	aux = G_OBJECT(g_object_get_data(G_OBJECT(user_data),"b_start"));
	GtkWidget *b_start = (GtkWidget *) aux;

	aux = G_OBJECT(g_object_get_data(G_OBJECT(user_data),"b_stop"));
	GtkWidget *b_stop = (GtkWidget *) aux;

	if(button == b_start){
		if(gtk_widget_get_sensitive(b_start) == TRUE){
			gtk_widget_set_sensitive(b_start, FALSE);
			gtk_widget_set_sensitive(b_stop, TRUE);
			validator = 1;
		}
	}else{
		if(gtk_widget_get_sensitive(b_start) != TRUE){
			gtk_widget_set_sensitive(b_start, TRUE);
			gtk_widget_set_sensitive(b_stop, FALSE);
			validator = 0;
		}
	}

	gpointer p = GINT_TO_POINTER(validator);
	g_object_set_data(user_data, "validator", p);

	startThread(button, user_data);
	return TRUE;
}	

void init(gpointer user_data){
	volatile static int adc_reg = 0;
	static count_h count = NULL;
	static gint validator, resume_valor;
	list_h list = NULL;
	list_create(&list);

	validator = GPOINTER_TO_INT(g_object_get_data(user_data,"validator"));

	GtkLabel *count_label = GTK_LABEL(g_object_get_data(G_OBJECT(user_data),"timer"));
	GtkLabel *adc_val = GTK_LABEL(g_object_get_data(G_OBJECT(user_data),"adc"));

	if(validator == 0){
		gtk_label_set_label(GTK_LABEL(adc_val), "--");
		gtk_label_set_label(GTK_LABEL(count_label), "00:00:00");
		adc_reg = 0;

		count_free(count);
	}

	if(!count_init(&count))
		g_print("Falha ao iniciar o timer\n");

	while(validator){
		resume_valor = GPOINTER_TO_INT(g_object_get_data(user_data,"resume_valor"));
		set_count_file_resume(list, resume_valor);
		registro_h registro = NULL;

		adc_reg = processor_interrupt(get_total_seconds(count)+1); //gera um sinal analógico hipotético

		processor_register(&registro, adc_reg, get_total_seconds(count), list);

		if(get_count_second(count) == 59){
			GThread   *fileminThread; 
			fileminThread = g_thread_new(NULL,(GThreadFunc) processor_file_min, list);
		}

		if(get_count_file_min(list) == resume_valor){
			GThread   *fileminThread; 
			fileminThread = g_thread_new(NULL,(GThreadFunc) processor_file_resume, list);
		}

		gchar *string = get_count_string(count); //atualiza o timer e pega a string
		gchar *text = g_strdup_printf("%i", adc_reg); //transforma o valor ADC em string

		gtk_label_set_label(GTK_LABEL(count_label), string);
		gtk_label_set_label(GTK_LABEL(adc_val), text);

		g_free(text);
		g_free(string);
		sleep(1);
	}
}