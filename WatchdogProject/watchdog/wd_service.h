#ifndef ILRD_WD_H
#define ILRD_WD_H

#include <stddef.h>	/* size_t */	
#include <sys/types.h> /* pid_t */

typedef struct thread_info thread_info_t;

thread_info_t *MMI(const char *client_path, 
                size_t frequency, 
                size_t timeout, int argc, char **argv);

void DNR(thread_info_t *thread_info);

#endif /* ILRD_WD_H */
