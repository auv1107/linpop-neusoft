#include "basetype.h"


void member_init(struct Member *m, 
			char* name, char* ip, int msg_recv_port, int file_send_port) {
	strncpy(m->name, name, 32);
	strncpy(m->ip, ip, 16);
	m->msg_recv_port = msg_recv_port;
	m->file_send_port = file_send_port;
	m->t = 5;
}
