/* 
* File Name: uid.c
* Description: Definition functions of uid functions
* Developer: Guy Chen
* Date: 27.06.2020
*/


#include <assert.h> /* assert */
#include "uid.h"

#define FAIL_TIME (time_t)(-1)

/*****************************************************************************/

unique_id_t UIDCreate(void)
{
	static size_t counter = 0;
	
	unique_id_t uid = UIDGetBadUID();  
	
	uid.time = time(NULL);
	
	if(FAIL_TIME != uid.time)
	{
		uid.counter = ++counter;
		uid.pid = getpid();
	}

	
	return (uid);
}

/*****************************************************************************/

int UIDIsSame(unique_id_t uid1, unique_id_t uid2)
{
	assert(uid1.time);
	assert(uid2.time);
	
	return(uid1.counter == uid2.counter && uid1.time == uid2.time && 
		   uid1.pid == uid2.pid);
}

/*****************************************************************************/

unique_id_t UIDGetBadUID(void)
{	
	unique_id_t uid = {0, 0, FAIL_TIME};
	return(uid);
}
	
/*****************************************************************************/

 






















