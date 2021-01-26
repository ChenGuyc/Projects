/* 
* File Name: scheduler_test.c
* Description: Definition of test functions for scheduler API functions
* Developer: Guy Chen
* Date: 28.06.2020
*/


#include <stdio.h> /* printf */
#include <assert.h> /* assert */
#include "scheduler.h"


static int taskFunctionPrint5Times(sch_t *sch, unique_id_t uid, void *param);
static int taskFunctionPrintEvery3SecondsTotal3(sch_t *sch, unique_id_t uid, void *param);
static int RoosterTask(sch_t *sch, unique_id_t uid, void *param);
static int taskFunctionStop(sch_t *sch, unique_id_t uid, void *param);
static int StartAnotherTimerFunc(sch_t *sch, unique_id_t uid, void *param);
static int WaitForsToStopFunc(sch_t *sch, unique_id_t uid, void *param);

int main()
{ 
	sch_t *sch = NULL;
	unique_id_t UID;

	sch = SchCreate();
	printf("created scheduler address: %p\n", (void*)sch);


	SchTimerStart(sch, 3, &taskFunctionPrintEvery3SecondsTotal3, NULL);
	SchTimerStart(sch, 3, &taskFunctionPrint5Times, NULL);
	SchTimerStart(sch, 2, &StartAnotherTimerFunc, NULL);
	UID = SchTimerStart(sch, 3, &taskFunctionPrint5Times, NULL);
	SchTimerCancel(sch, UID);
	/*SchTimerStart(sch, 2, &WaitForsToStopFunc, NULL);*/
	SchTimerStart(sch, 20, &taskFunctionStop, NULL);

	SchRun(sch);
	
	SchDestroy(sch);

	return (0);
}


static int taskFunctionPrint5Times(sch_t *sch, unique_id_t uid, void *param)
{
 	static int counter = 8;
	sch = sch;
	uid = uid;
	param = param;

	printf("every second 8 Times\n");
	--counter;

	if(counter)
	{
		return (1);
	}
	return (-1);
}

static int taskFunctionPrintEvery3SecondsTotal3(sch_t *sch, unique_id_t uid, void *param)
{
 	static int counter = 3;
	sch = sch;
	uid = uid;
	param = param;

	printf("task Function Print Every 3 Seconds Total 3\n");
	--counter;

	if(counter)
	{
		return (1);
	}
	return (0);
}

static int taskFunctionStop(sch_t *sch, unique_id_t uid, void *param)
{
	sch = sch;
	uid = uid;
	param = param;

	printf("In STOP task\n");

	return (-1);
}

static int RoosterTask(sch_t *sch, unique_id_t uid, void *param)
{
	static int counter = 6;
	time_t rawtime;
	sch = sch;
	uid = uid;
	param = param;
	assert(sch);
	
	time (&rawtime);


	printf("kookoorikoo, time is now: %s\n", ctime(&rawtime));
	--counter;

	if(counter)
	{
		return (1);
	}
	return (0);
}

static int StartAnotherTimerFunc(sch_t *sch, unique_id_t uid, void *param)
{
	uid = uid;
	param = param;	
	printf("now starting rooster timer and task from within a running task\n");	
	SchTimerStart(sch, 3, &RoosterTask, NULL);
	return (0);
}



static int WaitForsToStopFunc(sch_t *sch, unique_id_t uid, void *param)
{
	char ch = '0';
	uid = uid;
	param = param;
	assert(sch);

	printf("Wait For s To Stop Func \n");

	ch = tolower(getchar());

	if(ch == 's')
	{
		printf("got the s, will stop now\n");		
		return (-1);
	}
	return (1);
}




























