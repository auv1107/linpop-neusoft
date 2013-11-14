#include "writelog.h"

int log_fd;
BOOL Opened;
char Default_log_path[128] = "log/running.log";

BOOL log_init() {
	Opened = FALSE;

	/* 从配置文件获取log存储路径 */
	char str_logpath[128];
	GetProfileString("cls.conf", "base_setting", "logpath", str_logpath);
	if(str_logpath == NULL || 
			strlen(str_logpath) == 0) {
	}
	else {
		strncpy(Default_log_path, str_logpath, 128);
	}

	/* 打开指定的log文件 */
	log_fd = open(Default_log_path, O_WRONLY|O_CREAT|O_APPEND, 
										S_IRUSR|S_IWUSR|S_IROTH|S_IRGRP);
	if(log_fd == -1) {
		write(2, "Open log file error\n", 21);
	}
	else {
		Opened = TRUE;
	}
	
	return Opened;
}
void write_log(char* function_name, char* detail, char* other) {
	if(Opened == FALSE) {
		if(log_init() == FALSE) {
			return;
		}
	}
	
	time_t t = time(0);
	char time[128];
	memset(time,'\0', 128);
	strncpy(time, ctime(&t), 24);

	char buf[256];
	if(other == NULL || strlen(other) == 0) {
		sprintf(buf, "%s\t%s\t%s\n", time, function_name, detail);
	}
	else {
		sprintf(buf, "%s\t%s\t%s\t错误号: %s\n", time, function_name, detail, other);
	}
	write(log_fd, buf, strlen(buf));
}

void log_close() {
	if(Opened) {
		close(log_fd);
	}
}
