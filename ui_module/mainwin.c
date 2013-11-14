#include <gtk/gtk.h>
#include"chat.c"
#include"myinfo.h"
#include"hisinfo.h"
#include"basetype.h"
#include<stdlib.h>
#include "gtkapi.h"
//gchar* his_username="123";gchar* his_ip="456"; 
//enum{ COLUMN = 0, NUM_COLS} ;
void *broadcast_online() {
	while(1) {
	sleep(1);
	online(Self);
	}
}

void* check_offline() {
	while(1) {
	sleep(1);
	int i;
	for(i=0; i<userlist->len; i++) {
		g_array_index(userlist,struct Member, i).t--;
		if(g_array_index(userlist, struct Member, i).t <= 0) {
			g_array_remove_index(userlist, i);
		}
	}
	}
}

void user_offline(GtkWidget *widget, gpointer data) {
	offline(Self);
	gtk_main_quit();
}
void on_changed(GtkWidget *widget, gpointer statusbar)
 {
   GtkTreeIter iter;
   GtkTreeModel *model;
   char *value;
   if (gtk_tree_selection_get_selected(
   GTK_TREE_SELECTION(widget), &model, &iter)) {
   gtk_tree_model_get(model, &iter, COLUMN, &value, -1);
   gtk_statusbar_push(GTK_STATUSBAR(statusbar),
   gtk_statusbar_get_context_id(GTK_STATUSBAR(statusbar),
   value), value);
   g_free(value);
   }
 }
void row_activated(GtkTreeView* treeview,GtkTreePath*path,GtkTreeViewColumn*col,gpointer userdata)
{
   GtkTreeModel* model;
   GtkTreeIter iter;
   //char buf[1024];
   model = gtk_tree_view_get_model(treeview);
   if (gtk_tree_model_get_iter(model, &iter, path))
   {
      gtk_tree_model_get(model, &iter, COLUMN, &his_buf, -1);
     // his_username=(gchar*)calloc(4,1024);his_ip=(gchar*)calloc(4,1024);
     // sscanf(buf,"%s,%s",his_username,his_ip);
      //g_free(name);
   }
   chatwin(0,NULL);
}
static GtkTreeModel *
create_and_fill_model (void)
{
//  GtkTreeStore *treestore;
 // GtkTreeIter toplevel, child;
  int i;
  treestore = gtk_tree_store_new(NUM_COLS, G_TYPE_STRING);
  gtk_tree_store_append(treestore, &toplevel, NULL);
  gtk_tree_store_set(treestore, &toplevel,COLUMN, "在线好友", -1);
  //if(userlist->len!=0){
 // gtk_tree_store_set(treestore,&child,COLUMN,g_array_index(userlist,struct Member,1).name,-1);
  //gtk_tree_store_append(treestore,&child,&toplevel);
  /*for(i=0;i<userlist->len;i++)
  {
	char* buf;
	sprintf(buf,"%s%s",g_array_index(userlist,struct Member,i).name,g_array_index(userlist,struct Member,i).ip);	
	gtk_tree_store_set(treestore, &child, COLUMN, buf, -1);
        gtk_tree_store_append(treestore, &child, &toplevel);
  }*/
 //gtk_tree_store_set(treestore, &child, COLUMN, "Karl", -1);
  //gtk_tree_store_append(treestore, &child, &toplevel);
  //gtk_tree_store_set(treestore, &child, COLUMN, "Sccot",-1);
  for(i=0;i<userlist->len;i++){
  char buf[1024];
  sprintf(buf,"%s,%s",g_array_index(userlist,struct Member,i).name,g_array_index(userlist,struct Member,i).ip);
  gtk_tree_store_append(treestore, &child, &toplevel);
 gtk_tree_store_set(treestore, &child, COLUMN, buf,-1);}
  //gtk_tree_store_append(treestore, &toplevel, NULL);
 /* gtk_tree_store_set(treestore, &toplevel, COLUMN, "离线好友",-1);
  gtk_tree_store_append(treestore, &child, &toplevel);
  gtk_tree_store_set(treestore, &child, COLUMN, "Luoli",-1);
  gtk_tree_store_append(treestore, &child, &toplevel);
  gtk_tree_store_set(treestore, &child, COLUMN, "Yujie",-1);
  gtk_tree_store_append(treestore, &child, &toplevel);
  gtk_tree_store_set(treestore, &child, COLUMN, "Nvw",-1);*/
  return GTK_TREE_MODEL(treestore);
}
static GtkWidget *
create_view_and_model (void){
  GtkTreeViewColumn *col;
  GtkCellRenderer *renderer;
  GtkWidget *view;
  GtkTreeModel *model;
  view = gtk_tree_view_new();
  col = gtk_tree_view_column_new();
  gtk_tree_view_column_set_title(col, "");
  gtk_tree_view_append_column(GTK_TREE_VIEW(view), col);
  renderer = gtk_cell_renderer_text_new();
  gtk_tree_view_column_pack_start(col, renderer, TRUE);
  gtk_tree_view_column_add_attribute(col, renderer, "text", COLUMN);
  model = create_and_fill_model();
  gtk_tree_view_set_model(GTK_TREE_VIEW(view), model);
  g_object_unref(model);
  return view;
}
int mainwin(int argc, char *argv[]) 
{


     GtkWidget *statusbar;
     GtkWidget *view;
     GtkTreeSelection *selection;
     GtkWidget *vbox;
     GtkWidget *window;    
     GtkWidget *fixed;
     GtkWidget *label,*box1,*box2,*label1,*list,*ip;
     gtk_init(&argc,&argv);   
     window = gtk_window_new(GTK_WINDOW_TOPLEVEL);
     gtk_window_set_title(GTK_WINDOW(window),"LinPop");
     gtk_window_set_position(GTK_WINDOW(window),GTK_WIN_POS_CENTER);
     gtk_widget_set_size_request(window,250,500);
     fixed = gtk_fixed_new();
     gtk_widget_set_size_request(fixed,250,500);
     gtk_container_add(GTK_CONTAINER(window),fixed);   
   
     box1 = gtk_hbox_new(FALSE,0);
     gtk_widget_set_size_request(box1,230,25);
     gtk_fixed_put(GTK_FIXED(fixed),box1,0,0); 
     box2 = gtk_hbox_new(FALSE,0);
     gtk_widget_set_size_request(box2,230,25);
     gtk_fixed_put(GTK_FIXED(fixed),box2,0,25); 
     label = gtk_label_new("昵称");
     gtk_box_pack_start(GTK_BOX(box1),label,FALSE,FALSE,5);

     label1 = gtk_label_new(my_username);
    // gtk_label_set_text(label1,my_username);

     gtk_box_pack_start(GTK_BOX(box1),label1,FALSE,FALSE,5);
     list = gtk_label_new("好友列表");
     gtk_widget_set_size_request(list, 80, 25);
     gtk_box_pack_start(GTK_BOX(box2),list,FALSE,FALSE,5);
     ip = gtk_label_new("IP");
     gtk_widget_set_size_request(ip, 150, 25);
     gtk_box_pack_start(GTK_BOX(box2),ip,FALSE,FALSE,5);
     
     vbox = gtk_vbox_new(FALSE,2);
     gtk_widget_set_size_request(vbox, 230, 450);
     gtk_fixed_put(GTK_FIXED(fixed), vbox,0,50);
     view = create_view_and_model();
     selection = gtk_tree_view_get_selection(GTK_TREE_VIEW(view));
     gtk_box_pack_start(GTK_BOX(vbox), view, TRUE, TRUE, 1);
     statusbar = gtk_statusbar_new();
     gtk_box_pack_start(GTK_BOX(vbox), statusbar, FALSE, TRUE, 1);
     g_signal_connect(selection, "changed", G_CALLBACK(on_changed),
     statusbar);
    
     g_signal_connect(view,"row-activated",G_CALLBACK(row_activated),NULL);

     gtk_widget_show_all(window); 
     g_signal_connect(window, "destroy",G_CALLBACK(user_offline), NULL);

	pthread_attr_t attr;
	pthread_attr_init(&attr);
	pthread_attr_setdetachstate(&attr, PTHREAD_CREATE_DETACHED);
	pthread_t pid;
	pthread_create(&pid, &attr, broadcast_online, NULL);

	pthread_attr_t attr1;
	pthread_attr_init(&attr1);
	pthread_attr_setdetachstate(&attr1, PTHREAD_CREATE_DETACHED);
	pthread_t pid1;
	pthread_create(&pid1, &attr1, check_offline, NULL);

     gtk_main();
     return 0;    
}


