#ifndef PACKET
#define PACKET _


#include "basetype.h"
#include "networkapi.h"
#include "myio.h"
#include "gtkapi.h"

#include <stdlib.h>
#include <string.h>
#include <stdio.h>



/*
  获取状态封包
  @condition:  0  在线状态
  			   1  离线状态
  @返回值:   整合了状态信息，个人信息的封包
  			 格式为：0,         0/1,			name,ip,msg_recv_port,file_send_port
			 	     封包类型  在线/离线状态	其它相关信息
  */

char* get_condition_packet(int condition, struct Member self);

/*
  获取发送消息的封包
  @msg:  需要发送的内容
  @self:  使用用户
  @返回值:  整合消息内容的封包
  			格式:  1,		name,ip,	msg
				   封包类型 相关信息	消息正文
  */
char* get_msg_sending_packet(char* msg, struct Member self);

/*
  获取发送文件的封包
  @filename:  目标文件名
  @self:  使用用户
  @返回值:  整合文件信息的封包
  			格式:  2,		name,ip,file_send_port, filename
				   封包类型 相关信息				文件名
  */
char* get_file_sending_packet(char* filename, struct Member self);

/*
  对接收到的封包进行处理
  @packet:  接收到的封包
  @返回值:  处理结果  
  				0  正确处理
  				-1  不识别/错误封包格式
  */
int packet_handling(char* packet);
	
void handle_login_condition_packet(
		int condition, char* name, char* ip, int msg_recv_port, int file_send_port);

void handle_msg_sending_packet(
		char* name, char* ip, char* msg);

void handle_file_sending_packet(
		char* name, char* ip, int port, char* filename);

#endif
