// util functions for Silver Lining project

#include <sys/types.h>  //u_int64_t
#include <arpa/inet.h>  //ntohl
#include <assert.h>     //assert
#include <unistd.h>     //read()

#ifndef __UTILS__
#define __UTILS__

#define htonll ntohll

u_int64_t ntohll(u_int64_t a);

int ReadAll(int fd, char* buf, size_t count);

int WriteAll(int fd, char* buf, size_t count);

#endif //__UTILS__