#ifndef CALLBACKS_H
#define CALLBACKS_H

gboolean on_start_stop_clicked(GtkWidget *button, gpointer user_data);
void init(gpointer user_data);
void startThread(GtkWidget *button, gpointer user_data);
void controlThread(gpointer user_data);

gboolean update_label_time(gpointer user_data);

#endif