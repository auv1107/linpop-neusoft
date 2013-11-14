#include "gtkapi.h"


void gtk_del_member(struct Member user) {
    int i;
    for (i = 0; i < userlist->len; i++) 
    {
	if (strcmp(g_array_index(userlist,struct Member,i).name, user.name) == 0 && strcmp(g_array_index(userlist,struct Member,i).ip,user.ip)==0)
        {
			g_array_remove_index(userlist, i);
			break;
		}
    }

	gtk_tree_store_clear(treestore);
	gtk_tree_store_append(treestore, &toplevel, NULL);
	gtk_tree_store_set(treestore, &toplevel,COLUMN, "在线好友", -1);


	for(i=0;i<userlist->len;i++){
		char buf[1024];
		sprintf(buf,"%s,%s",g_array_index(userlist,struct Member,i).name,g_array_index(userlist,struct Member,i).ip);
		gtk_tree_store_append(treestore, &child, &toplevel);
		gtk_tree_store_set(treestore, &child, COLUMN, buf,-1);
	}

	
}

void gtk_add_new_member(struct Member new_user)
{  
	if (strcmp(Self.name, new_user.name) == 0 && strcmp(Self.ip,new_user.ip)==0){ 
		return;
	}
   // ini();
    int i;
    for (i = 0; i < userlist->len; i++) 
    {
	if (strcmp(g_array_index(userlist,struct Member,i).name, new_user.name) == 0 && strcmp(g_array_index(userlist,struct Member,i).ip,new_user.ip)==0)
        {
           g_array_index(userlist,struct Member,i).t=5;
		   break;
	}
    }

    if(i==userlist->len)
    {
        g_array_append_val(userlist,new_user);

		  char buf[1024];
		  sprintf(buf,"%s,%s",g_array_index(userlist,struct Member,i).name,g_array_index(userlist,struct Member,i).ip);
		  gtk_tree_store_append(treestore, &child, &toplevel);
		  gtk_tree_store_set(treestore, &child, COLUMN, buf,-1);
	}
}



void gtk_add_new_message(char* username,char* ip, char* message)
{
	write_log("gtk_add_new_message()", "", "");
	int i;
	for(i=0;i<chatlist->len;i++)
	{
		if(strcmp(g_array_index(chatlist,Savechat,i).name,username)==0&&strcmp(g_array_index(chatlist,Savechat,i).ip,ip)==0)
		{
		write_log("gtk_add_new_message()", "add new words", "");
		//gtk_text_buffer_inser_(GTK_TEXT_BUFFER(g_array_index(chatlist,Savechat,i).save_buff_output), &g_array_index(chatlist,Savechat,i).save_end_out,message,strlen(message));
		GtkTextBuffer* buff_output;
		GtkTextIter start_out,end_out;

		buff_output = gtk_text_view_get_buffer(GTK_TEXT_VIEW(g_array_index(chatlist,Savechat,i).view));
		gtk_text_buffer_get_bounds(GTK_TEXT_BUFFER(buff_output), &start_out,&end_out);

		char *time=getCurrentTime();
		char buf[128];
		sprintf(buf, "%s  %s", username, time);
		gtk_text_buffer_insert(GTK_TEXT_BUFFER(buff_output), &end_out,buf, strlen(buf));
		gtk_text_buffer_insert(GTK_TEXT_BUFFER(buff_output), &end_out,message, strlen(message));
		gtk_text_buffer_insert(GTK_TEXT_BUFFER(buff_output), &end_out,"\n\n", 2);
		return;
		}
	}

	/* new window */
	strcpy(his_username,username);
	strcpy(his_ip,ip);
	strcpy(current_username,username);
	strcpy(current_ip,ip);
	chatwin(0,NULL);
	gtk_add_new_message(username, ip, message);
}

void gtk_recv_file(char* name, char* ip, int port, char* filename) {
}
