#include "networkapi.h"












/*
  获取当前在线用户链表头
  */

struct Member* get_online_member_head() {
	write_log("get_online_member_head()", "", "");
	return Member_head;
}

/*
  向目标发送消息
  @msg:  要发送的消息
  @dest:  目标用户(或用户链表头)
  @返回值:  -1  出错
  			0	发送失败
			1	发送成功
  */
int send_msg(char* msg, struct Member dest, struct Member self) {
	write_log("send_msg()","","");

	if(msg == NULL || strlen(msg) == 0) {		// msg == ""  需要注意
		write_log("send_msg()", "msg is NULL or \"\"", NULL);
		return -1;
	}

	struct sockaddr_in addr;
	bzero(&addr, sizeof(addr));
	addr.sin_family = AF_INET;
	addr.sin_addr.s_addr = inet_addr(dest.ip);
	addr.sin_port = htons(dest.msg_recv_port);
		
	char buf[1024];
	strncpy(buf, get_msg_sending_packet(msg, self), sizeof(buf)) ;
	return sendto(Udp_send_msg_fd, buf, strlen(buf), 0, (struct sockaddr*)&addr, sizeof(addr));
}

/*
  获取最近lines行消息记录
  @dest: 目标用户
  @lines:  获取的行数
  @返回值: 与dest用户的最近lines条记录信息
  */
char* get_msg(struct Member dest, int lines) {
	write_log("get_msg()","","");

	char path[128];
	strncpy(path, get_dest_record_path(dest.ip, dest.name), 128);

	return read_n_lines_from_tail(path, lines);		// io模块提供的函数
}

/*
  发送文件
  @path: 文件路径
  @self: 本机用户
  @dest: 目标用户
  @返回值: -1  出错
  		   >=0  用来唯一标识此动作的句柄
  */
int send_file(char* path, struct Member dest, struct Member self) {
	write_log("send_file()","",path);

	struct sockaddr_in addr;
	bzero(&addr, sizeof(addr));

	addr.sin_family = AF_INET;
	addr.sin_addr.s_addr = htonl(INADDR_ANY);
	addr.sin_port = htons(self.file_send_port);

	int send_fd = socket(AF_INET, SOCK_STREAM, 0);
	if(send_fd == -1) {
		write_log("send_file()","socket 建立失败","");
		return -1;
	}
	write_log("send_file()","socket 建立成功","");


	int res = bind(send_fd, (struct sockaddr*)&addr, sizeof(addr));
	if(res == -1) {
		write_log("send_file()","绑定失败","");
		return -1;
	}
	write_log("send_file()","绑定成功","");

	res = listen(send_fd, Backlog);
	if(res == -1) {
		write_log("send_file()","监听失败","");
		return -1;
	}
	write_log("send_file()","监听...","");

	struct sockaddr_in dest_addr;
	bzero(&dest_addr, sizeof(dest_addr));

	dest_addr.sin_family = AF_INET;
	dest_addr.sin_addr.s_addr = inet_addr(dest.ip);
	dest_addr.sin_port = htons(dest.msg_recv_port);

	char packet[1024];

	strncpy(packet, get_file_sending_packet(get_file_name(path), self), 1024) ;
	sendto(Udp_send_msg_fd, packet, strlen(packet), 0, (struct sockaddr*)&dest_addr, sizeof(dest_addr));
	/* test */
	/*	
		char buf1[256];
		sprintf(buf1, "%s:%d:%d:%s:%d", packet, backlog, strlen(packet), self.ip, self.file_send_port);
	*/
	/* end test */
	write_log("send_file()","发送传送文件请求,等待连接","");

	int client_fd = accept(send_fd, NULL, NULL);
	if(client_fd == -1) {
		write_log("send_file()","接收连接失败","");
		return -1;
	}
	write_log("send_file()","接受连接请求","");


	int read_fd = open(path,O_RDONLY);
	if(read_fd == -1) {
		write_log("send_file()", "目标文件打开失败", "");
		return -1;
	}
	write_log("send_file()","目标文件打开成功,开始传输文件","");

	int len;
	char buf[32];
	while((len = read(read_fd, buf, 32)) > 0) {
		write(client_fd, buf, len);
	}
	
	write_log("send_file()","文件传输完毕","");

	close(send_fd);
	close(read_fd);

	return 0;
}

/*
  接收文件
  @path: 文件保存路径
  @返回值: -1  出错
  		   >=0  用来唯一标识此动作的句柄
  */
int recv_file(char* path, char* dest_ip, int dest_port) {
	write_log("recv_file()","","");

	struct sockaddr_in addr;
	bzero(&addr, sizeof(addr));

	addr.sin_family = AF_INET;
	addr.sin_addr.s_addr = inet_addr(dest_ip);
	addr.sin_port = htons(dest_port);
	
	int recv_fd = socket(AF_INET, SOCK_STREAM, 0);
	if(recv_fd == -1) {
		return -1;
	}
	write_log("recv_file()","建立socket成功,请求服务器连接","");

	//sleep(10);
	int res = connect(recv_fd, (struct sockaddr*)&addr, sizeof(addr));
	if(res == -1) {
		return -1;
	}
	write_log("recv_file()","连接服务器成功,接收文件","");

	char new_path[128];
	sprintf(new_path, "recvfile/%s", path);
	int save_fd = open(new_path, O_CREAT|O_WRONLY, S_IRUSR|S_IWUSR|S_IRGRP|S_IROTH);
	if(save_fd == -1) {
		write_log("recv_file()","创建文件失败","");
		return -1;
	}

	char buf[32];
	int len;
	while((len=recv(recv_fd, buf, 32, 0)) > 0) {
		write(save_fd, buf, len);
	}
	write_log("recv_file()","接收文件完成","");

	close(save_fd);
	close(recv_fd);
	return 0;
}

/*
  广播在线状态
  @返回值:    0   成功
  			  1   失败
  */

int online(struct Member self) {
	write_log("online()","","");
	
	char packet[128];
	/* for test */
	char buf[128];
	sprintf(buf, "port: %d\n", ntohs(Broadcast_addr.sin_port));
	write_log("online()", buf, "");
	strncpy(packet, get_condition_packet(0, self), 128);
	setsockopt(Broadcast_fd, SOL_SOCKET, SO_BROADCAST, (struct sockaddr*)&Broadcast_addr, sizeof(Broadcast_addr));
	return sendto(Broadcast_fd, packet, strlen(packet), 0, (struct sockaddr*)&Broadcast_addr, sizeof(Broadcast_addr));
}
/*
  广播离线状态
  @返回值:    0   成功
  			  1   失败
  */
int offline(struct Member self) {
	write_log("offline()","","");
	
	char packet[128];
	strncpy(packet, get_condition_packet(1, self), 128);
	setsockopt(Broadcast_fd, SOL_SOCKET, SO_BROADCAST, (struct sockaddr*)&Broadcast_addr, sizeof(Broadcast_addr));
	return sendto(Broadcast_fd, packet, strlen(packet), 0, (struct sockaddr*)&Broadcast_addr, sizeof(Broadcast_addr));
}



/*
  监听msg接收端口
  */
void* listen_msg_recv_port() {
	write_log("listen_msg_recv_port()", "","");

	char packet[1024];
	memset(packet, 0, 1024);
	while(1) {
		recvfrom(Udp_recv_msg_fd, packet, 1024, 0, NULL, NULL);
		write_log("listen_msg_recv_port()", "recieved packet: ", packet);
		
		packet_handling(packet);
		memset(packet, 0, 1024);
	}
}
