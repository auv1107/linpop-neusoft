#ifndef NETWORKAPI 
#define NETWORKAPI _

#include "basetype.h"
#include "packet.h"
#include "myio.h"

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include <arpa/inet.h>
#include <netinet/in.h>
#include <sys/socket.h>
#include <sys/types.h>
#include <unistd.h>

#include <sys/stat.h>
#include <fcntl.h>

#include <pthread.h>

/*
	测试用的宏
	*/
#define BACKLOG 0
#define BROADCAST_PORT 1



struct sockaddr_in Broadcast_addr;
int Broadcast_fd;
int Udp_send_msg_fd;
int Udp_recv_msg_fd;
struct Member Self;
int *Msg_update_condition;
struct Member* Member_head;
int Backlog;

/*
  获取当前在线用户链表头
  */

struct Member* get_online_member_head();

/*
  向目标发送消息
  @msg:  要发送的消息
  @dest:  目标用户(或用户链表头)
  @返回值:  -1  出错
  			0	发送失败
			1	发送成功
  */
int send_msg(char* msg, struct Member dest, struct Member self);

/*
  获取最近items条消息记录
  @dest: 目标用户
  @items:  获取的条数
  @返回值: 与dest用户的最近items条记录信息
  */
char* get_msg(struct Member dest, int items);

/*
  发送文件
  @path: 文件路径
  @dest: 目标用户
  @返回值: 用来唯一标识此动作的句柄
  */
int send_file(char* path, struct Member dest, struct Member self);

/*
  接收文件
  @path: 文件保存路径
  @返回值: 用来唯一标识此动作的句柄
  */
int recv_file(char* path, char* dest_ip, int dest_port);

/*
  广播在线状态
  @self:  本机用户信息
  @返回值:    0   成功
  			  1   失败
  */

int online(struct Member self);

/*
  广播离线状态
  @self:  本机用户信息
  @返回值:    0   成功
  			  1   失败
  */
int offline(struct Member self);


/*
  监听msg接收端口
  */
void *listen_msg_recv_port();

#endif
