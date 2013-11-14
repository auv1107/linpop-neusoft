#ifndef GTKAPI
#define GTKAPI _

#include "basetype.h"
#include "networkapi.h"
#include "chat.h"

#include <gtk/gtk.h>
#include"hisinfo.h"
enum{ COLUMN = 0, NUM_COLS} ;
GtkWidget* view;
void gtk_del_member(struct Member user);
void gtk_add_new_member(struct Member new_user);
void gtk_add_new_message(char* username,char* ip, char* message);
void gtk_recv_file(char* name, char* ip, int port, char* filename);
GtkTreeStore *treestore;
GtkTreeIter toplevel, child;

#endif
