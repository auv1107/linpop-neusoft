#include <gtk/gtk.h>
int record(int argc, char *argv[]) 
{
   GtkWidget *record_window;
   GtkWidget *record_fixed;
   GtkWidget *record_view;
   GtkWidget *record_vbox;
   GtkWidget *record_button;
   
   gtk_init(&argc,&argv); 
   record_window = gtk_window_new(GTK_WINDOW_TOPLEVEL);
   gtk_window_set_title(GTK_WINDOW(record_window),"聊天记录");
   gtk_window_set_position(GTK_WINDOW(record_window),GTK_WIN_POS_CENTER);
   gtk_widget_set_size_request(record_window,400,300);
   record_fixed = gtk_fixed_new();
   gtk_widget_set_size_request(record_fixed,400,300);
   gtk_container_add(GTK_CONTAINER(record_window),record_fixed); 

   gtk_container_set_border_width(GTK_CONTAINER(record_window), 5);
   GTK_WINDOW(record_window)->allow_shrink = TRUE;
   record_vbox = gtk_vbox_new(FALSE, 0);
   gtk_widget_set_size_request(record_vbox, 380, 250);
   record_view = gtk_text_view_new();
   gtk_widget_set_visible(record_view,TRUE);
   gtk_widget_set_can_focus(record_view,FALSE);
   gtk_box_pack_start(GTK_BOX(record_vbox), record_view, TRUE, TRUE, 0);
   record_button = gtk_button_new_with_label("关闭");
   gtk_fixed_put(GTK_FIXED(record_fixed), record_button, 280, 260);
   gtk_widget_set_size_request(record_button, 90, 30);
   gtk_fixed_put(GTK_FIXED(record_fixed), record_vbox,5,5);
   gtk_widget_show_all(record_window); 
   g_signal_connect(record_window, "destroy",G_CALLBACK(gtk_main_quit), NULL);
   gtk_main();
   return 0;   
}
