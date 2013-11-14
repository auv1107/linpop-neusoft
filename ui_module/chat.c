#include <gtk/gtk.h>
#include <pango/pango.h>
#include <time.h>
#include <stdlib.h>
#include"record.c"
#include"myinfo.h"
#include"hisinfo.h"
#include"basetype.h"
#include "networkapi.h"
#include "chat.h"
#define MAX_BUF 2048
//char current_username[32];
//char current_ip[16];
char* getCurrentTime() {
	time_t t = time(0);
	return ctime(&t);
}
gint quit_event(GtkWidget *widget,gpointer data)
{
	gtk_main_quit();
}
void close_event(GtkWidget *widget, GtkWidget *window) {
	gtk_widget_destroy(window);
}

void chat_send_handle(GtkWidget *widget,gpointer* data)
{
	GtkTextIter start_in, end_in, start_out, end_out;
	gchar *text_msg = malloc(MAX_BUF);

	GtkTextBuffer *buff_input, *buff_output;
	buff_input = gtk_text_view_get_buffer(
	GTK_TEXT_VIEW(data[0]));
	buff_output = gtk_text_view_get_buffer(
	GTK_TEXT_VIEW(data[1]));

	gtk_text_buffer_get_bounds(GTK_TEXT_BUFFER(buff_input), &start_in, &end_in);
	gtk_text_buffer_get_bounds(GTK_TEXT_BUFFER(buff_output), &start_out,
			&end_out);

	text_msg = gtk_text_buffer_get_text(GTK_TEXT_BUFFER(buff_input), &start_in,
			&end_in, FALSE);

	char *msg_title;
	if (text_msg == NULL || strlen(text_msg) == 0) {
		printf("没有消息\n");
		return;
	} else {
		int i;	
		for(i=0;i<userlist->len;i++)
		{
			if(strcmp(g_array_index(userlist, struct Member, i).name, current_username) == 0&& 
					strcmp(g_array_index(userlist, struct Member, i).ip, current_ip) == 0) {
					break;
					}
		}

		if(i >= userlist->len) {
			return;
		}

		send_msg(text_msg, g_array_index(userlist, struct Member, i), Self);
		write_into_record_file(Self.name, Self.ip, text_msg);


		// 清除输入 text view 数据
		gtk_text_buffer_delete(GTK_TEXT_BUFFER(buff_input), &start_in, &end_in);

		char *time_str = getCurrentTime();
		msg_title = g_strdup_printf("%s  %s", Self.name, time_str);

		// 插入文本到消息接收 text view
		gtk_text_buffer_insert(GTK_TEXT_BUFFER(buff_output), &end_out,msg_title, strlen(msg_title));
		gtk_text_buffer_insert(GTK_TEXT_BUFFER(buff_output), &end_out, text_msg,strlen(text_msg));
		gtk_text_buffer_insert(GTK_TEXT_BUFFER(buff_output), &end_out, "\n\n",strlen("\n\n"));

		write_into_record_file(Self.name, Self.ip, text_msg);
		//scrollTextview((char *) id);
	Savechat s;
	for(i=0;i<chatlist->len;i++)
	{
		if(strcmp(g_array_index(chatlist,Savechat,i).name,current_username)==0&&strcmp(g_array_index(chatlist,Savechat,i).ip,current_ip)==0)
		{
			g_array_index(chatlist,Savechat,i).view=GTK_TEXT_VIEW(data[1]);
			break;
		}
		if(i>=chatlist->len) {
			strcpy(s.name,current_username);
			strcpy(s.ip,current_ip);
			s.view=GTK_TEXT_VIEW(data[1]);
			g_array_append_val(chatlist,s);
		}
		

	}
	}
}
int chatwin(int argc, char *argv[]) 
{
        GtkWidget *chat_window;    
	GtkWidget *chat_fixed;   
	GtkWidget *chat_box;
	//GtkWidget *chat_show_text;
        GtkWidget *chat_send;//,*chat_close;
	GtkWidget *chat_sfile_button, *chat_record_button,*chat_rfile_button;
        GtkWidget *chat_frame,*chat_fileframe,*valign,*chat_vbox,*va,*vb;
	//GtkWidget *chat_input_text;
	GtkWidget *chat_text[2];
        GtkWidget *chat_filename;
        GtkWidget *chat_label;
        GtkWidget *chat_label1,*chat_label2,*chat_label3,*chat_label4;
        GtkWidget *sendprocess;
        GtkTextBuffer *chat_show_buffer;
        GtkTextBuffer *chat_input_buffer;
	 
	gtk_init(&argc,&argv);   
	    
	/*创建一个窗口*/
	chat_window = gtk_window_new(GTK_WINDOW_TOPLEVEL);
	gtk_window_set_title(GTK_WINDOW(chat_window),"Linpop");
	gtk_window_set_position(GTK_WINDOW(chat_window),GTK_WIN_POS_CENTER);
	gtk_widget_set_size_request(chat_window,550,400);
		    
	    
	    
	/*创建一个固定容器*/
  	chat_fixed = gtk_fixed_new();
	gtk_widget_set_size_request(chat_fixed,550,400);
	gtk_container_add(GTK_CONTAINER(chat_window),chat_fixed);   
	    
	    
	/*创建盒*/
	chat_box = gtk_hbox_new(FALSE,0);
	gtk_widget_set_size_request(chat_box,350,30);
	gtk_fixed_put(GTK_FIXED(chat_fixed),chat_box,0,210);    
	
	/*创建一个文本输入框*/
	chat_text[0]  = gtk_text_view_new();
	chat_input_buffer = gtk_text_view_get_buffer(GTK_TEXT_VIEW(chat_text[0]));
	gtk_widget_set_size_request(chat_text[0],350,100);
	gtk_fixed_put(GTK_FIXED(chat_fixed),chat_text[0],2,240);
	gtk_widget_show(chat_text[0]);
	
	/*创建一个显示文本框*/
	chat_text[1] = gtk_text_view_new();
	chat_show_buffer = gtk_text_view_get_buffer(GTK_TEXT_VIEW(chat_text[1]));
	gtk_text_view_set_editable(GTK_TEXT_VIEW(chat_text[1]),FALSE);
	gtk_widget_set_size_request(chat_text[1],350,200);
	gtk_fixed_put(GTK_FIXED(chat_fixed),chat_text[1],2,10);
	gtk_widget_show(chat_text[1]);
	    
	//send file
        chat_sfile_button = gtk_button_new_with_label("发送文件");
	gtk_box_pack_start(GTK_BOX(chat_box),chat_sfile_button,FALSE,FALSE,5);
	gtk_widget_show(chat_sfile_button);	
	//recv file
        chat_rfile_button = gtk_button_new_with_label("接收文件");
	gtk_box_pack_start(GTK_BOX(chat_box),chat_rfile_button,FALSE,FALSE,5);
	gtk_widget_show(chat_rfile_button);
	/*创建聊天记录按钮*/
	chat_record_button = gtk_button_new_with_label("聊天记录");
	gtk_box_pack_start(GTK_BOX(chat_box),chat_record_button,FALSE,FALSE,5);
	
	gtk_widget_show(chat_record_button);

        chat_send = gtk_button_new_with_label("发送");
        gtk_fixed_put(GTK_FIXED(chat_fixed), chat_send, 20, 350);
        gtk_widget_set_size_request(chat_send, 60, 30);


	g_signal_connect(chat_send,"clicked",G_CALLBACK(chat_send_handle),chat_text);

       /* chat_close = gtk_button_new_with_label("关闭");
        gtk_fixed_put(GTK_FIXED(chat_fixed), chat_close, 170, 350);
        gtk_widget_set_size_request(chat_close, 60, 30);*/
        
        chat_frame = gtk_frame_new("对方信息");
        gtk_frame_set_shadow_type(GTK_FRAME(chat_frame), GTK_SHADOW_IN);
        gtk_fixed_put(GTK_FIXED(chat_fixed), chat_frame, 370, 15);
        gtk_widget_set_size_request(chat_frame, 150, 150);
        va = gtk_alignment_new(0.3,1,0,0);
        gtk_container_add(GTK_CONTAINER(chat_frame), va);
	vb = gtk_vbox_new(TRUE, 2);
        gtk_container_add(GTK_CONTAINER(va), vb);
	his_username=(gchar*)calloc(4,256);
	his_ip=(gchar*)calloc(4,256);
	sscanf(his_buf,"%[^,],%s",his_username,his_ip);
        chat_label1=gtk_label_new("昵称:");
        chat_label2=gtk_label_new(his_username);
	strcpy(current_username,his_username);
        chat_label3=gtk_label_new("IP:");
        chat_label4=gtk_label_new(his_ip);
	strcpy(current_ip,his_ip);
        gtk_box_pack_start(GTK_BOX(vb),chat_label1,FALSE,FALSE,5);
        gtk_box_pack_start(GTK_BOX(vb),chat_label2,FALSE,FALSE,5);
        gtk_box_pack_start(GTK_BOX(vb),chat_label3,FALSE,FALSE,5);
        gtk_box_pack_start(GTK_BOX(vb),chat_label4,FALSE,FALSE,5);


	Savechat s;

			strcpy(s.name,current_username);
			strcpy(s.ip,current_ip);
			s.view=GTK_TEXT_VIEW(chat_text[1]);
			g_array_append_val(chatlist,s);


        chat_fileframe = gtk_frame_new("文件传输");
        gtk_frame_set_shadow_type(GTK_FRAME(chat_fileframe), GTK_SHADOW_IN);
        gtk_fixed_put(GTK_FIXED(chat_fixed), chat_fileframe, 370, 180);
        gtk_widget_set_size_request(chat_fileframe, 150, 150);
        //gtk_widget_set_no_show_all(fileframe,TRUE);
         
        valign = gtk_alignment_new(0.5,1,0,0);
        gtk_container_add(GTK_CONTAINER(chat_fileframe), valign);
	chat_vbox = gtk_vbox_new(TRUE, 2);
        gtk_container_add(GTK_CONTAINER(valign), chat_vbox);
        chat_filename =gtk_label_new("文件名");
        gtk_widget_set_size_request(chat_filename, 100, 30);        
        chat_label=gtk_label_new("文件传输进度");
        gtk_widget_set_size_request(chat_label, 60, 30);
        sendprocess =gtk_progress_bar_new();
        gtk_widget_set_size_request(sendprocess, 100, 20);

        gtk_box_pack_start(GTK_BOX(chat_vbox),chat_filename,FALSE,FALSE,5);
        gtk_box_pack_start(GTK_BOX(chat_vbox),chat_label,FALSE,FALSE,5);
        gtk_box_pack_start(GTK_BOX(chat_vbox),sendprocess,FALSE,FALSE,5);
        
       

        gtk_label_set_justify(GTK_LABEL (chat_filename), GTK_JUSTIFY_FILL);
	//gtk_label_set_line_wrap(GTK_LABEL (filename), TRUE);
	//gtk_label_set_line_wrap_mode(GTK_LABEL (filename), PANGO_WRAP_CHAR);
        
        void sendFile(GtkButton *button, gpointer data) {
	 
	GtkWidget *dialog;
	GSList *filenames;
	gchar *str_file;

	dialog = gtk_file_chooser_dialog_new("打开文件 ...", NULL,
			GTK_FILE_CHOOSER_ACTION_OPEN, GTK_STOCK_CANCEL, GTK_RESPONSE_CANCEL,
			GTK_STOCK_OPEN, GTK_RESPONSE_ACCEPT, NULL);

	gtk_file_chooser_set_current_folder(GTK_FILE_CHOOSER (dialog),
			g_get_home_dir());

	gint result = gtk_dialog_run(GTK_DIALOG(dialog));
        if (result == GTK_RESPONSE_ACCEPT) {
		filenames = gtk_file_chooser_get_filenames(GTK_FILE_CHOOSER(dialog));
		gchar *file = (gchar*) filenames->data;;
		printf("filename :%s\n",file);
		str_file = g_strdup(file);

		int i;
		for(i=0;i<userlist->len;i++)
		{
			if(strcmp(g_array_index(userlist, struct Member, i).name, current_username) == 0&& 
					strcmp(g_array_index(userlist, struct Member, i).ip, current_ip) == 0) {
				send_file(file, g_array_index(userlist, struct Member, i), Self);
				break;		
					}
		}

		gtk_label_set_text(GTK_LABEL(chat_filename), str_file);
		gtk_widget_show(GTK_WIDGET(sendprocess));
		gtk_widget_show(chat_filename);

		 
	}
        
	gtk_widget_destroy(dialog);
    }
     g_signal_connect(chat_sfile_button,"clicked", G_CALLBACK(sendFile),NULL);
     gtk_widget_set_visible(chat_sfile_button, TRUE);   

     g_signal_connect(chat_record_button, "clicked", G_CALLBACK(record),NULL);

     gtk_widget_show_all(chat_window); 
    // g_signal_connect(chat_close, "clicked",G_CALLBACK(gtk_main_quit), NULL);
     g_signal_connect(chat_window, "destroy",G_CALLBACK(gtk_main_quit), NULL);
     gtk_main();
     return 0;
}
