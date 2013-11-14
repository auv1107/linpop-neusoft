#include "myio.h"

void write_into_record_file(char* name, char* ip, char* msg) {
	write_log("write_into_record_file()", "", "");
	char path[128];
	strncpy(path, get_dest_record_path(name, ip), 128);
	
	int fd = open(path, O_APPEND|O_WRONLY|O_CREAT, S_IRUSR|S_IWUSR|S_IRGRP|S_IROTH);
	if(fd == -1) {
		write_log("write_into_record_file()", "open record error", "-1");
		return;
	}

	char buf[1024];
	sprintf(buf, "%s  %s%s\n\n", name, get_current_time(), msg);
	write(fd, buf, strlen(buf));
	close(fd);
}

char* read_n_lines_from_tail(char* path, int lines){}

char* get_file_name(char* path) {
	char *buf;
	
	buf=(char*)malloc(128);
	int endpos = strlen(path)-1;
	int startpos=0;
	while(path[endpos] == '/') {
		endpos--;
	}
	startpos=endpos;
	
	while(path[startpos] != '/') {
		startpos--;
		if(startpos==-1) {
			break;
		}
	}
	startpos++;
	int t=0;
	for(; startpos<=endpos; startpos++) {
		buf[t++] = path[startpos];
	}
	buf[t] = '\0';
	return buf;
}

char* get_dest_record_path(char* name, char* ip) {
	char *path;
	path = (char*) malloc(128);
	sprintf(path, "record/%s_%s.rcd", ip, name);
	return path;
}

char* get_current_time() {
	time_t t = time(0);
	return ctime(&t);
}

long get_total_size(char* path) {
	struct stat buf;
	int res = stat(path, &buf);
	if(res == -1) {
		write_log("get_total_size()", "", "-1");
		return -1;
	}
	return buf.st_size;
}
