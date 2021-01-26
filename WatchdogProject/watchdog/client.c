#include <stdio.h> /* printf */
#include <unistd.h> 
#include <stdlib.h> 
#include <signal.h> /* signals */
#include <sys/types.h> /* pid_t */
#include <sys/wait.h>
#include <pthread.h>

#include "scheduler.h" 
#include "wd_service.h"

#define TIMEOUT 6	/* signals sent and not responded */
#define FREQUENCY 5 /* time interval between sigusr1 signals sent */

int main(int argc, char **argv)
{
   int i = 0;
   thread_info_t *thread_info = NULL;
   
   thread_info = MMI(argv[0], FREQUENCY, TIMEOUT, argc, argv); 
   printf("printing from client process after MMI call, pid: %d\n", getpid());

   for(i = 0; i < 12; ++i)
   {
	   sleep(1);
   }
	
	puts("main process terminated properly");

   DNR(thread_info); /* this will kill the thread */

   printf("after DNR call in main process\n");

   return (0); 

}
