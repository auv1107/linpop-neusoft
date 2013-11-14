#include "packet.h"


/*
  获取状态封包
  @condition:  0  在线状态
  			   1  离线状态
  @返回值:   整合了状态信息，个人信息的封包
  			 格式为：0,         0/1,			name,ip,msg_recv_port,file_send_port
			 	     封包类型  在线/离线状态	其它相关信息
  */

char* get_condition_packet(int condition, struct Member self) {
	char* buf;
	buf = (char*) malloc (256);
	memset(buf, '\0', 256);
	sprintf(buf, "0,%d,%s,%s,%d,%d", condition, self.name, self.ip, self.msg_recv_port, self.file_send_port);
	write_log("get_condition_packet()", buf, "");
	return buf;
}

/*
  获取发送消息的封包
  @msg:  需要发送的内容
  @self:  使用用户
  @返回值:  整合消息内容的封包
  			格式:  1,		name,ip,	msg
				   封包类型 相关信息	消息正文
  */
char* get_msg_sending_packet(char* msg, struct Member self) {
	char* buf;
	buf = (char*) malloc (256);
	memset(buf, 0, 256);
	sprintf(buf, "1,%s,%s,%s", self.name, self.ip, msg);
	write_log("get_msg_sending_packet()", buf, "");
	return buf;
}


/*
  获取发送文件的封包
  @filename:  目标文件名
  @self:  使用用户
  @返回值:  整合文件信息的封包
  			格式:  2,		name,ip,	filename
				   封包类型 相关信息	文件名
  */
char* get_file_sending_packet(char* filename, struct Member self) {
	char* buf;
	buf = (char*) malloc (256);
	memset(buf, 0, 256);
	sprintf(buf, "2,%s,%s,%d,%s", self.name, self.ip, self.file_send_port, filename);
	return buf;
}

/*
  对接收到的封包进行处理
  @packet:  接收到的封包
  @返回值:  处理结果  
  				0  正确处理
  				-1  不识别/错误封包格式
  */
int packet_handling(char* packet) {
	switch(packet[0]) {
		case '0':
		{
			int condition;
			char name[32];
			char ip[16];
			int msg_recv_port;
			int file_send_port;
			sscanf(packet, "0,%d,%[^,],%[^,],%d,%d", &condition, name, ip, &msg_recv_port, &file_send_port);
			handle_login_condition_packet(
					condition, name, ip, msg_recv_port, file_send_port);
		}
			break;
		case '1':
		{
			char name[32];
			char ip[16];
			char msg[207];
			sscanf(packet, "1,%[^,],%[^,],%[^,]", name, ip, msg);
			handle_msg_sending_packet(name, ip, msg);
		}
			break;
		case '2':
		{
			char name[32];
			char ip[16];
			int port;
			char filename[32];
			sscanf(packet, "2,%[^,],%[^,],%d,%[^,]", name, ip, &port, filename);
			handle_file_sending_packet(name, ip, port, filename);
		}
			break;
		default:
			return -1;
	}
	return 0;
}
	
	
void handle_login_condition_packet(
		int condition, char* name, char* ip, int msg_recv_port, int file_send_port) {
	char buf[1024];
	write_log("handle_login_condition_packet()", "", "");
	sprintf(buf, "condition: %d\nname: %s\nip: %s\nport1: %d\nport2: %d\n", condition, name, ip, msg_recv_port, file_send_port);
	write_log("handle_login_condition_packet()", buf, "");
	struct Member new_member;
	member_init(&new_member, name, ip, msg_recv_port, file_send_port);
	if(condition == 0) {
		gtk_add_new_member(new_member);
	} else {
		gtk_del_member(new_member);
	}
		}

void handle_msg_sending_packet(
		char* name, char* ip, char* msg){
	write_log("handle_msg_sending_packet()", "", "");
	char buf[1024];
	sprintf(buf, "name: %s\nip: %s\nmsg: %s\n", name, ip, msg);	
	write_log("handle_msg_sending_packet()", buf, "");
	gtk_add_new_message(name, ip, msg);
	write_into_record_file(name, ip, msg);
		}

void handle_file_sending_packet(
		char* name, char* ip, int port, char* filename){
	write_log("handle_file_sending_packet()", "", "");
	char buf[1024];
	sprintf(buf, "name: %s\nip: %s\nport: %d\nfilename: %s\n", name, ip, port, filename);	
	write_log("handle_file_sending_packet()", buf, "");

//	gtk_recv_file(name, ip, port, filename);
	recv_file(filename, ip, port);	
		}
