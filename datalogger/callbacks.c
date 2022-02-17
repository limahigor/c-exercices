#include "callbacks.h"

gboolean on_start_stop_clicked(GtkWidget *button, gpointer user_data){
	gint validator;

	GObject *b = g_object_new(G_TYPE_OBJECT, NULL);
	GObject *obj = g_object_new(G_TYPE_OBJECT, NULL);

	obj = G_OBJECT(user_data);

	b = G_OBJECT(g_object_get_data(G_OBJECT(obj),"b_start"));
	GtkWidget *b_start = (GtkWidget *) b;

	b = G_OBJECT(g_object_get_data(G_OBJECT(obj),"b_stop"));
	GtkWidget *b_stop = (GtkWidget *) b;

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
	g_object_set_data(obj, "validator", p);
	
	g_timeout_add_seconds(1, G_SOURCE_FUNC(set), obj);
	return TRUE;
}	

gboolean set(gpointer user_data){
	volatile static int num = 0;
	GObject *aux = g_object_new(G_TYPE_OBJECT, NULL);
	gint n;

	n = GPOINTER_TO_INT(g_object_get_data(user_data,"validator"));

	GtkLabel *tmp_val = GTK_LABEL(g_object_get_data(G_OBJECT(user_data),"tmp"));

	char *text = g_strdup_printf("%i", num);

	if(!n){
		gtk_label_set_label(GTK_LABEL(tmp_val), "--");
		g_object_unref(aux);
		g_free(text);
		return FALSE;
	}

	printf("%i\n", num);
	gtk_label_set_label(GTK_LABEL(tmp_val), text);

	num++;
	return TRUE;
}