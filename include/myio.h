#ifndef MYIO
#define MYIO _


#include <time.h>
#include <sys/stat.h>
#include <sys/types.h>
#include <unistd.h>
#include <fcntl.h>
#include <string.h>
#include <stdlib.h>
#include <stdio.h>
#include "writelog.h"

void write_into_record_file(char* name, char* ip, char* msg);

char* read_n_lines_from_tail(char* path, int lines);

char* get_file_name(char* path);

char* get_dest_record_path(char* ip, char* name);

char* get_current_time();

long get_total_size(char* path);



#endif
