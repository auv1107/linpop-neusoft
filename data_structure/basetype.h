#ifndef BASETYPE
#define BASETYPE
#include <gtk/gtk.h>
#include <string.h>
struct Member {
           char name[32];
           char ip[16];
           int msg_recv_port;
           int file_send_port;
	   int t;
  } ;
  GArray* userlist;

typedef struct {
	//GtkTextBuffer* save_buff_output;
	//GtkTextIter save_end_out;
	GtkTextView* view;
	char name[32];
	char ip[16];
}Savechat;
GArray* chatlist;	



#endif
