#ifndef GETIP
#define GETIP _


#include <stdio.h>    
#include <stdlib.h>    
#include <sys/types.h>    
#include <sys/socket.h>    
#include <netinet/in.h>    
#include <netdb.h>    
#include <arpa/inet.h>    
#include <signal.h>    
   
#include <sys/ioctl.h>    
#include <linux/if.h>    

union ipu {   
    long ip; 
    unsigned char ipchar[4]; 
};   

long getlocalhostip();


char* getip();


#endif
