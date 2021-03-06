#include <gtk/gtk.h>
#include"mainwin.c"
#include"myinfo.h"
#include"string.h"
#include"basetype.h"
#include"getip.h"
#include "networkapi.h"
//GArray* userlist;



void ini()
{
	userlist=g_array_new(FALSE,FALSE,sizeof(struct Member));
	chatlist=g_array_new(FALSE,FALSE,sizeof(Savechat));
	struct Member m1;
	strcpy(m1.name,"John");
	strcpy(m1.ip,"192.168.0.1");
	m1.msg_recv_port=3000;
	m1.file_send_port=3001;
	m1.t=5;
	g_array_append_val(userlist,m1);
	struct Member m2;
	strcpy(m2.name,"Scott");
	strcpy(m2.ip,"192.168.0.2");
	m2.msg_recv_port=4000;
	m2.file_send_port=4001;
	m2.t=5;
	g_array_append_val(userlist,m2);
}


void show_mainwin(GtkWidget* widget,gpointer* window)
{
  // gtk_label_set_text(label1,gtk_entry_get_text((GtkEntry*)window[1]);
   my_username=gtk_entry_get_text((GtkEntry*)window[1]);
   my_ip = getip();
   char str_port[16];
   GetProfileString("cls.conf", "base_setting", "msg_recv_port", str_port);
   sscanf(str_port, "%d", &my_msg_recv_port);
   GetProfileString("cls.conf", "base_setting", "file_send_port", str_port);
   sscanf(str_port, "%d", &my_file_send_port);
   
   member_init(&Self, my_username, my_ip, my_msg_recv_port, my_file_send_port);
   network_module_init();
   online(Self);

	

   mainwin(0,NULL);
   gtk_widget_destroy(window[0]);
   // gtk_entry_set_text((GtkEntry*)window[1],my_username);
}
int main(int argc, char *argv[]) 
{
   ini();
  // printf("%s",g_array_index(userlist,struct Member,1).name);
   //GtkWidget *log_window;
   GtkWidget *log_label;
   //GtkWidget *log_entry;
   GtkWidget *log_button;
   GtkWidget *log_fixed;
   GtkWidget *parameter[2];
   gtk_init(&argc, &argv);
   parameter[0] = gtk_window_new(GTK_WINDOW_TOPLEVEL);
   gtk_window_set_position(GTK_WINDOW(parameter[0]), GTK_WIN_POS_CENTER);
   gtk_window_set_default_size(GTK_WINDOW(parameter[0]), 250, 150);
   gtk_window_set_title(GTK_WINDOW(parameter[0]), "登陆窗口");
   log_fixed = gtk_fixed_new();
   gtk_container_add(GTK_CONTAINER(parameter[0]), log_fixed);
   log_button = gtk_button_new_with_label("登录");
   gtk_fixed_put(GTK_FIXED(log_fixed), log_button, 90, 100);
   gtk_widget_set_size_request(log_button, 60, 30);
  // g_signal_connect(log_button,"clicked",G_CALLBACK(show_mainwin),parameter);
   log_label = gtk_label_new("昵称");
   gtk_widget_set_size_request(log_label, 60, 30);
   gtk_fixed_put(GTK_FIXED(log_fixed), log_label, 40, 40);
   
   parameter[1] = gtk_entry_new();
   gtk_fixed_put(GTK_FIXED(log_fixed), parameter[1], 100, 40);
   gtk_widget_set_size_request(parameter[1], 100, 30);
  // my_username=gtk_entry_get_text((GtkEntry*)log_entry);
   g_signal_connect(log_button,"clicked",G_CALLBACK(show_mainwin),parameter);
   gtk_widget_show_all(parameter[0]);
   g_signal_connect(parameter[0], "destroy",G_CALLBACK(gtk_main_quit), NULL);
   gtk_main();
   return 0;
}
