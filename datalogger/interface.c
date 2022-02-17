#include "interface.h"

static void activate(GtkApplication *app, gpointer user_data){   
  GtkWidget *window;
  GtkWidget *container, *button_box, *label_f_box, *label_v_box, *label_pack, *timer_pack; //Containers
  GtkWidget *tmp_label, *bin_label, *timer_label; //Labels fixas
  GtkWidget *relogio, *tmp_val, *bin_val; //Labels variaveis
  GtkWidget *b_start, *b_stop; //Buttons

  window = gtk_application_window_new(app);
  gtk_window_set_title(GTK_WINDOW (window), "Temperature Logger");
  gtk_window_set_default_size(GTK_WINDOW (window), 300, 350);
  gtk_window_set_resizable(GTK_WINDOW(window), 0);

  if(gtk_window_get_deletable(GTK_WINDOW(window)));
    g_print("TESTE\n");

  //--------------------- EMPACOTAMENTO ------------------------//

  container = gtk_fixed_new(); //CRIA UM CONTAINER ONDE VAI FICAR OS OUTROS WIDGETS
  gtk_container_add(GTK_CONTAINER(window), container); //ADICIONA NA JANELA PRINCIPAL

  label_pack = gtk_box_new(GTK_ORIENTATION_HORIZONTAL, 80); //EMPACOTANDO LABELS FIXAS E VARIAVEIS
  gtk_fixed_put(GTK_FIXED(container), label_pack, 85, 120); //ADICIONANDO AO CONTAINER

  timer_pack = gtk_box_new(GTK_ORIENTATION_VERTICAL, 5); //EMPACOTANDO LABELS FIXAS E VARIAVEIS
  gtk_fixed_put(GTK_FIXED(container), timer_pack, 210, 10); //ADICIONANDO AO CONTAINER

  label_v_box = gtk_box_new(GTK_ORIENTATION_VERTICAL, 20); //CRIA O BOX ONDE FICA AS LABELS VARIAVEIS
  gtk_box_pack_end(GTK_BOX(label_pack), label_v_box, FALSE, FALSE, 0); //SETA A POSIÇÃO NA TELA

  label_f_box = gtk_box_new(GTK_ORIENTATION_VERTICAL, 20); //CRIA O BOX ONDE FICA AS LABELS FIXAS
  gtk_box_pack_end(GTK_BOX(label_pack), label_f_box, FALSE, FALSE, 0); //SETA A POSIÇÃO NA TELA

  button_box = gtk_box_new(GTK_ORIENTATION_HORIZONTAL, 20); //CRIA O button_box ONDE FICA CONTIDO OS BOTÕES
  gtk_fixed_put(GTK_FIXED(container), button_box, 60, 280); //SETA A POSIÇÃO NA TELA

  //----------------------- TIMER LABELS ----------------------//

  timer_label = gtk_label_new("00:00:00"); //CRIA A LABEL TIMER
  gtk_box_pack_end(GTK_BOX(timer_pack), timer_label, FALSE, FALSE, 0);

  relogio = gtk_label_new("HH:HH:HH"); //CRIA A LABEL RELOGIO
  gtk_box_pack_start(GTK_BOX(timer_pack), relogio, FALSE, FALSE, 0); //ADICIONANDO AO CONTAINER


  //----------------------- LABELS VARIAVEIS ----------------------//

  tmp_val = gtk_label_new("--");
  gtk_box_pack_start(GTK_BOX(label_v_box), tmp_val, FALSE, FALSE, 0);

  bin_val = gtk_label_new("00");
  gtk_box_pack_start(GTK_BOX(label_v_box), bin_val, FALSE, FALSE, 0);

  //----------------------- LABELS FIXAS ----------------------//

  bin_label = gtk_label_new("BIN:"); //CRIA A LABEL RELOGIO
  gtk_box_pack_end(GTK_BOX(label_f_box), bin_label, FALSE, FALSE, 0); //SETA A POSIÇÃO DELA NA TELA

  tmp_label = gtk_label_new("TMP:"); //CRIA A LABEL QUE MOSTRA O VALOR tmp
  gtk_box_pack_end(GTK_BOX(label_f_box), tmp_label, FALSE, FALSE, 0); //SETA A POSIÇÃO DELA NA TELA


  //---------------------- BOTÕES ---------------------//
  b_start = gtk_button_new_with_label("Start"); //CRIA O BOTÃO INICIAR
  gtk_widget_set_size_request(b_start, 80, 25); //SETA O TAMANHO DELE
  gtk_box_pack_start(GTK_BOX(button_box), b_start, FALSE, FALSE, 0); //ADICIONA O BOTÃO NO button_box

  b_stop = gtk_button_new_with_label("Stop");  //CRIA O BOTÃO STOP
  gtk_widget_set_size_request(b_stop, 80, 25); //SETA O TAMANHO DELE
  gtk_box_pack_start(GTK_BOX(button_box), b_stop, FALSE, FALSE, 0); //ADICIONA O BOTÃO NO button_box

  //Objects to pass as argument callbacks
  GObject *LabelsContent = g_object_new(G_TYPE_OBJECT, NULL);

  g_object_set_data(LabelsContent,"bin", bin_val);
  g_object_set_data(LabelsContent,"tmp", tmp_val);
  g_object_set_data(LabelsContent,"timer", timer_label);
  g_object_set_data(LabelsContent,"clock", relogio);
  g_object_set_data(LabelsContent,"b_start", b_start);
  g_object_set_data(LabelsContent,"b_stop", b_stop);
  g_object_set_data(LabelsContent,"window", window);

  //Signals and Events
  g_signal_connect(b_start, "clicked", G_CALLBACK(on_start_stop_clicked), LabelsContent); //ACIONA EVENTO SE FOR CLICADO
  g_signal_connect(b_stop, "clicked", G_CALLBACK(on_start_stop_clicked), LabelsContent); //ACIONA EVENTO SE FOR CLICADO

  gtk_widget_show_all(window);
}

int main(int argc, char **argv){
  if(argc > 2){
    printf("Muitos argumentos!\ndatalogger -ng para iniciar sem GUI!\n");
    return 0;
  }

  if(argc == 1){
    GtkApplication *app;
    int status;

    app = gtk_application_new("lim.datalogger", G_APPLICATION_FLAGS_NONE);
    g_signal_connect(app, "activate", G_CALLBACK (activate), NULL);
    status = g_application_run(G_APPLICATION(app), argc, argv);
    g_object_unref(app);
  }else if(!strcmp(argv[1], "-ng"))
    printf("Em construcao....\n");
  else
    printf("Argumento invalido!\ndatalogger -ng para iniciar sem GUI!\n");
  

  return 0;
}