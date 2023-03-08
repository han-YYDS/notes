// func.h
#ifndef __func_H__
#define __func_H__

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/stat.h>
#include <unistd.h>
#include <sys/types.h>
#include <dirent.h>
#include <pwd.h>
#include <grp.h>
#include <time.h>
#include <fcntl.h>
#include <sys/mman.h>
#include <sys/select.h>
#include <sys/time.h>
#include <sys/wait.h>
#include<sys/ipc.h>
#include<sys/shm.h>
#include<signal.h>
#include<pthread.h>
#include<sys/socket.h>
#include <arpa/inet.h>
#include <netdb.h>
#include <errno.h>
#include <sys/epoll.h>
#include <assert.h>
#include <stdbool.h>
#include <sys/uio.h>
#include <mysql/mysql.h>
#include <shadow.h> 

#define ARGS_CHECK(argc,n) \
{                        \
    if(argc!=n) \
    {          \
        fprintf(stderr,"args error: expected %d arguments\n",argc); \
        exit(1);  \
    } \
}

#define ERROR_CHECK(retVal,val,msg)  {\
    if(retVal==val) { \
    perror(msg);\
    exit(1);\
    }\
}

#define THREAD_ERROR_CHECK(ret,msg) do\
{\
   if(ret!=0)\
    {\
       fprintf(stderr,"%s:%d\n",msg,strerror(ret));\
       exit(1);\
    }}while(0)

#endif


