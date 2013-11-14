#ifndef WRITELOG
#define WRITELOG _

#include <string.h>
#include <stdio.h>
#include <unistd.h>
#include <fcntl.h>
#include <sys/stat.h>
#include <sys/types.h>
#include <time.h>


/*
  测试用的宏
  */
#define LOGPATH 3

#ifndef BOOL
#define BOOL int
#endif

#ifndef TRUE
#define TRUE 1
#endif

#ifndef FALSE
#define FALSE 0
#endif

/*
  初始化log模块
  @返回值:  日志句柄是否可用
  */
BOOL log_init();

/*
  写log
  @function_name:  记录log时所在的函数
  @detail:  出错的详细信息
  @other:  错误号，等其它信息
  */
void write_log(char* function_name, char* detail, char* other);

/*
  关闭log文件句柄
  */
void log_close();

#endif
