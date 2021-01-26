#define _POSIX_C_SOURCE 200112L
#include <stdio.h> /* printf */
#include <stdlib.h> /* setenv */
#include <time.h>
#include <fcntl.h>
#include <signal.h> /* signals */
#include <sys/types.h> /* pid_t */
#include <sys/wait.h>
#include <pthread.h>
#include <string.h>
#include <semaphore.h>

#include "wd_service.h"
#include "scheduler.h"

#define WD_PATH "/home/guy/git/projects/watchdog/wd/wd.Debug.out"
#define CLIENT_PATH "client.Debug.out"

typedef struct sigaction sigact_t;

struct thread_info
{
  char *path_to_other_process;
  pid_t other_process_pid;
  size_t timeout_g;
  size_t frequency_g;
	sem_t *sem;
  sch_t *my_sched;
  size_t no_response_counter;
  pthread_t thread_id;
  int creator;
};

thread_info_t *thread_info_g = NULL;

/******************************************************************************/

void HandleUSR1(int sig, siginfo_t *info, void *context) 
{ 
  (void)sig;
  (void)context;
  thread_info_g->other_process_pid = info->si_pid;
  thread_info_g->no_response_counter = 0;  
  puts("handling sigusr1\n"); 
} 

/******************************************************************************/

void HandleUSR2(int sig, siginfo_t *info, void *context) 
{ 
  (void)sig;
  (void)context;
  (void)info;
  printf("handling sigusr2 from process %d\n", getpid());
  SchStop(thread_info_g->my_sched);
  SchDestroy(thread_info_g->my_sched);
  pthread_cancel(thread_info_g->thread_id);
  free(thread_info_g);
} 

/******************************************************************************/

static int Sig1Task(sch_t *sch, unique_id_t uid, void *param)
{
    (void)sch;
    (void)uid;
    (void)param;

    if(thread_info_g->no_response_counter < thread_info_g->timeout_g)
    {
        kill(thread_info_g->other_process_pid, SIGUSR1);
        ++thread_info_g->no_response_counter;
        printf("task - sent sigusr1 from process %d\n", getpid());
        return (1);     /*reschedule task */
    }
    
    /* in case timeout reached */
    printf("task - timeout reached, from process %d\n", getpid());
    kill(thread_info_g->other_process_pid, SIGTERM);
    thread_info_g->creator = 1;
    /*sem_destroy(thread_info_g->sem);*/
    thread_info_g->other_process_pid = fork();
    if(thread_info_g->other_process_pid == 0) /* in child */
    {
      printf("task - will exec now, from process %d\n", getpid());
      execlp(thread_info_g->path_to_other_process, "NULL", NULL);
    }
    else if(thread_info_g->other_process_pid > 0) /* in parent */
    {
      thread_info_g->no_response_counter = 0;
      sem_wait(thread_info_g->sem);
      printf("parent process after semwait - from task\n");
      return (1);
    }
}

/******************************************************************************/

static int StopSchTask(sch_t *sch, unique_id_t uid, void *param)
{
    (void)sch;
    (void)uid;
    (void)param;

    SchStop(thread_info_g->my_sched);
    return 0;
}

/******************************************************************************/

void *ThreadFunc(void *arg)
{
    (void)arg;
    thread_info_g->my_sched = SchCreate();
    SchTimerStart(thread_info_g->my_sched, thread_info_g->frequency_g, Sig1Task, thread_info_g);
    SchTimerStart(thread_info_g->my_sched, 40, StopSchTask, thread_info_g);
    SchRun(thread_info_g->my_sched);
    return NULL;
}

/******************************************************************************/

thread_info_t *MMI(const char *client_path, 
                size_t frequency, 
                size_t timeout, int argc, char **argv)
{
    sigact_t sig1;
    sigact_t sig2;
    pid_t pid;
    printf("starting MMI from pid %d\n", getpid());

    sig1.sa_sigaction = HandleUSR1;
    sig1.sa_flags = SA_SIGINFO;
    sigemptyset(&sig1.sa_mask);
    sig2.sa_sigaction = HandleUSR2;
    sig2.sa_flags = SA_SIGINFO;
    sigemptyset(&sig2.sa_mask);
    
    sigaction(SIGUSR1, &sig1, NULL);
    sigaction(SIGUSR2, &sig2, NULL);

    thread_info_g = (thread_info_t*) malloc(sizeof(thread_info_t));
    if(!thread_info_g)
    {
      printf("malloc failed\n");
      return NULL;
    }		
    
    thread_info_g->no_response_counter = 0;
    thread_info_g->timeout_g = timeout;
    thread_info_g->frequency_g = frequency;
    thread_info_g->path_to_other_process = (strcmp(client_path, WD_PATH) == 0) ? CLIENT_PATH: WD_PATH; 
    thread_info_g->sem = sem_open("/sem", O_CREAT, 0664, 0);
    if (NULL == thread_info_g->sem)
    {
      free(thread_info_g);
      return (NULL);
    }

    if(!getenv("WD_UP"))
    {
        printf("inside setenv\n");
        setenv("WD_UP", "1", 1);
        thread_info_g->creator = 1;
        
        pid = fork(); /* first run */
        if(0 == pid) /* in child */
        {
            execvp(WD_PATH, argv);
            printf("after exec, failure?\n");
        }
    }
    printf("from MMI creator = %d\n", thread_info_g->creator);
    if(thread_info_g->creator == 1)
    {
      thread_info_g->other_process_pid = pid;
      sem_wait(thread_info_g->sem);
      printf("parent process after semwait - from MMI creator = 1\n");
    }
    else
    {
      thread_info_g->other_process_pid = getppid();
      printf("child process before sempost - from MMI creator = 0 my pid %d and other process pid %d\n", getpid(), thread_info_g->other_process_pid);
      sem_post(thread_info_g->sem);
    }
    
    pthread_create(&thread_info_g->thread_id, NULL, &ThreadFunc, NULL);
    pthread_join(thread_info_g->thread_id, NULL); 
    
    return(thread_info_g);
}

/******************************************************************************/

void DNR(thread_info_t *thread_info)
{
  kill(thread_info->other_process_pid, SIGUSR2);
  SchStop(thread_info->my_sched);
  SchDestroy(thread_info->my_sched);
  pthread_cancel(thread_info->thread_id);
  free(thread_info);
}

/******************************************************************************/

