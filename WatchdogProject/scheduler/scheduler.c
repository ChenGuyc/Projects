/* 
* File Name: scheduler.c
* Description: Definition of  scheduler API functions
* Developer: Guy Chen
* Date: 28.06.2020
*/

#include <assert.h> /* assert */
#include <stdlib.h> /* malloc */
#include "scheduler.h" 
#include "pqueue.h"
#define TRUE 1
#define FALSE 0

struct scheduler
{
	pqueue_t * pq;
};

typedef struct timer
{
	unique_id_t uid;	
	sch_task_func_t task_func;
	time_t interval;
	time_t time_to_wakeup;
	void* param;
}timerr_t;

int SchCompare(const void *data1, const void *data2, void *param)
{
	time_t time1 = 0;
	time_t time2 = 0;	
	param = param;	
	time1 = (*(timerr_t**)data1)->time_to_wakeup;
	time2 = (*(timerr_t**)data2)->time_to_wakeup;
	if(time1 <= time2)
	{
		return (0);
	}
	
	return (1); /* time1 > time2 */
}

int TimerIsMatch(const void *timer, const void *UID, void *param)
{
	timerr_t *timer_temp = NULL;
	(void)param;
	timer_temp = (timerr_t*)timer;
	if(UIDIsSame(timer_temp->uid, *(unique_id_t*)UID))
	{
		return (TRUE);
	}
	return (FALSE);
}

int stop_task(sch_t *sch, unique_id_t uid, void *param)
{
	assert(sch);
	uid = uid;
	param = param;
	sch = sch;
	
	return (-1); /* failure which will cause run to stop */
}

/* Task function return values:
* -1 : task failed.
*  0 : task is finished.
*  1 : re-run task.

typedef int (*sch_task_func_t)(sch_t *sch, unique_id_t uid, void *param);*/


/*---------------------------------------------------------------------------*/

sch_t *SchCreate(void)
{
	sch_t * scheduler = (sch_t *)malloc(sizeof(sch_t));
	if(scheduler)
	{
		scheduler->pq = PQCreate(SchCompare, NULL);
		if(scheduler->pq)
		{
			return (scheduler);
		}
		else
		{
			free(scheduler);			
			scheduler = NULL;
		}
	}
	return (scheduler);
}

/*---------------------------------------------------------------------------*/

void SchDestroy(sch_t *sch)
{
	while (!PQIsEmpty(sch->pq))
	{
		free(PQDequeue(sch->pq));
	}	
	PQDestroy(sch->pq);
	free(sch);
	sch = NULL;
}

/*---------------------------------------------------------------------------*/

int SchRun(sch_t *sch)
{
	int task_result = 0;
	size_t time_to_sleep = 0;
	timerr_t *curr_timer;	
	assert(sch);

	while(!PQIsEmpty(sch->pq) && task_result != (-1))
	{
		curr_timer = (timerr_t*)PQDequeue(sch->pq);
		time_to_sleep = curr_timer->time_to_wakeup - time(0);
		curr_timer->time_to_wakeup = time(0) + curr_timer->interval;
		sleep(time_to_sleep);

		task_result = curr_timer->task_func(sch, curr_timer->uid, curr_timer->param);
		if(1 == task_result)
		{
			if(PQEnqueue(sch->pq, curr_timer))
			{
				return (1); /* failure to restart timer, run stops */
			}
		}
		if(0 == task_result)
		{
			free(curr_timer);
			curr_timer = NULL;	
		}
	}
	if(task_result == (-1)) 
	{
		free(curr_timer);
		curr_timer = NULL;		
		return (1); /* failure of task, run stops */	
	}
	return (0); /* success */
}

/*---------------------------------------------------------------------------*/

int SchStop(sch_t *sch)
{
	unique_id_t UID;
	assert(sch);
	
	UID = SchTimerStart(sch, 0, stop_task, NULL);
	if(!UIDIsSame(UID, UIDGetBadUID()))
	{
		return (1); /* scheduler stopped successfully */
	}
	return (0); /* scheduler was not stopped */
}
/*---------------------------------------------------------------------------*/

unique_id_t SchTimerStart(sch_t *sch, 
                                size_t interval_in_sec,
                                sch_task_func_t task,
                                void* param)
{
  	timerr_t *timer;
	unique_id_t UID;
	assert(sch);
	timer = malloc(sizeof(timerr_t));
	if(timer)
	{
		UID = UIDCreate();
		if(!UIDIsSame(UID, UIDGetBadUID()))
		{
			timer->uid = UID;
			timer->task_func = task;
			timer->interval = interval_in_sec;
			timer->time_to_wakeup = time(0) + interval_in_sec;
			timer->param = param;
			if(PQEnqueue(sch->pq, timer) == 0)
			{
				return (timer->uid);
			}
		}
		free(timer);
		timer = NULL;
	}
	return(UIDGetBadUID());
}

/*---------------------------------------------------------------------------*/

void SchTimerCancel(sch_t *sch, unique_id_t UID)
{
	free(PQErase(sch->pq, &UID, &TimerIsMatch, NULL));
}


























