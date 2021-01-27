/***********************************
 * file name: utils.cpp            *
 * developer: Guy Chen             *
 * date: 01.12.20                  *
 * version 0.1                     *
 ***********************************/


#include "utils.hpp"


#ifdef WORDS_BIGENDIAN
u_int64_t ntohll(u_int64_t a) 
{
  return a;
}

#else
u_int64_t ntohll(u_int64_t a)
{
  u_int32_t lo = a & 0xffffffff;
  u_int32_t hi = a >> 32U;
  lo = ntohl(lo);
  hi = ntohl(hi);
  return (static_cast<u_int64_t>(lo) << 32U | hi);
}

#endif
//#define htonll ntohll

int ReadAll(int fd, char* buf, size_t count)
{
    while (count > 0)
    {
        int bytesRead = read(fd, buf, count);
        if (!(0 < bytesRead))
        {
            throw "Read All";
        }
    buf += bytesRead;
    count -= bytesRead;
  }
  assert(count == 0);

  return 0;
}

int WriteAll(int fd, char* buf, size_t count)
{
  int bytes_written;

  while (count > 0)
  {
    bytes_written = write(fd, buf, count);
    assert(bytes_written > 0);
    
    buf += bytes_written;
    count -= bytes_written;
  }
  assert(count == 0);

  return 0;
}