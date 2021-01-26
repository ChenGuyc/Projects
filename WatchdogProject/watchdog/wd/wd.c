#include <stdio.h> /* printf */
#include <unistd.h> 
#include <stdlib.h> 
#include <signal.h> /* signals */
#include <sys/types.h> /* pid_t */
#include <sys/wait.h>
#include <pthread.h>
#include <semaphore.h>

#include "scheduler.h" 
#include "wd_service.h"

#define TIMEOUT 6	/* signals sent and not responded */
#define FREQUENCY 5 /* time interval between sigusr1 signals sent */

int main(int argc, char **argv)
{
   	int i = 0;
   	thread_info_t *thread_info = NULL;

   printf("printing from wd process, pid: %d\n", getpid());
   thread_info = MMI(argv[0], FREQUENCY, TIMEOUT, argc, argv); 
   
   for (i = 0; i < 10000; ++i)
	{
		sleep(1);
	}

	puts("watch dog process terminated properly");

   return (0); 

}
