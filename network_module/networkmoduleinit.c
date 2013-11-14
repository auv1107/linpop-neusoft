#include "networkmoduleinit.h"

/*
  网络模块初始化
  */
int network_module_init() {
	write_log("network_module_init()","", "");

	/* 广播地址、socket初始化 */
	Broadcast_fd = socket(AF_INET, SOCK_DGRAM, 0);
	if(Broadcast_fd == -1) {
		write_log("network_module_init()","Broadcast_fd 初始化出错", "-1");
		return -1;
	}

	int broadcast_port;
	char str_bdct_port[32];
	GetProfileString("cls.conf", "base_setting", "broadcast_port", str_bdct_port);
	sscanf(str_bdct_port, "%d", &broadcast_port);

	bzero(&Broadcast_addr, sizeof(Broadcast_addr));
	Broadcast_addr.sin_family = AF_INET;
	Broadcast_addr.sin_addr.s_addr = htonl(INADDR_BROADCAST);
	Broadcast_addr.sin_port = htons(broadcast_port);
	setsockopt(Broadcast_fd, SOL_SOCKET, SO_BROADCAST, (struct sockaddr*)&Broadcast_addr, sizeof(Broadcast_addr));

	/* 发送、接收消息socket初始化 */
	Udp_send_msg_fd = socket(AF_INET, SOCK_DGRAM, 0);
	if(Udp_send_msg_fd == -1) {
		write_log("network_module_init()","Udp_send_msg_fd 初始化出错", "-1");
		return -1;
	}

	Udp_recv_msg_fd = socket(AF_INET, SOCK_DGRAM, 0);
	if(Udp_recv_msg_fd == -1) {
		write_log("network_module_init()","Udp_recv_msg_fd 初始化出错", "-1");
		return -1;
	}

	/* 接收消息端口绑定 */
	struct sockaddr_in localaddr;
	bzero(&localaddr, sizeof(localaddr));
	localaddr.sin_family = AF_INET;
	localaddr.sin_addr.s_addr = htonl(INADDR_ANY);
	localaddr.sin_port = htons(Self.msg_recv_port);

	int res = bind(Udp_recv_msg_fd, (struct sockaddr*)&localaddr, sizeof(localaddr));
	if(res == -1) {
		write_log("network_module_init()","Udp_recv_msg_fd 绑定错误", "-1");
		return -1;
	}
	
	/* 初始化TCP服务器最大允许的连接数 */
	char str_backlog[32];
	GetProfileString("cls.conf", "tcp_server", "backlog", str_backlog);
	sscanf(str_backlog, "%d", &Backlog);
	/*  */
	pthread_attr_t attr;
	pthread_attr_init(&attr);
	pthread_attr_setdetachstate(&attr, PTHREAD_CREATE_DETACHED);
	pthread_t pid;
	pthread_create(&pid, &attr, listen_msg_recv_port, NULL);

	/* 成员链表头初始化 */
	Member_head = (struct Member*) malloc (sizeof(struct Member));

	return 0;
}
