/* 
* File Name: uid_test.c
* Description: Definition of test functions of uid functions
* Developer: Guy Chen
* Date: 27.06.2020
*/

#include <stdio.h> /* printf */
#include <stdlib.h> /* ctime */
#include "uid.h"
	

/************************** Functions Decleration ****************************/

static void PrintUID(unique_id_t uid);

/*****************************************************************************/

static unique_id_t UIDCreateTest(void);
static void  UIDIsSameTest(void);
static void UIDGetBadUIDTest(void);





/**************************** main function **********************************/

int main(void)
{
	unique_id_t new_uid = {0, 0, 0};

	new_uid = UIDCreateTest();
	UIDIsSameTest();
	UIDGetBadUIDTest();
	return (0);
}	






/************************** Functions Defenition ****************************/
/******************** utility function to print the new uid *****************/ 

static void PrintUID(unique_id_t uid)
{
	char *time = NULL;
		
	time = ctime(&uid.time);
	printf("the new uid is: %lu ,%d ,%s\n", uid.counter, uid.pid, time); 
}

/*****************************************************************************/

static unique_id_t UIDCreateTest(void)
{
	unique_id_t new_uid = {0, 0, 0};
		
	new_uid = UIDCreate();
	
	if(UIDIsSame(new_uid, UIDGetBadUID()))
	{	
		printf("The created of new unique ID didn't succeed\n");
	}
	else
	{
		printf("The created of new unique ID succeeded\n");
	}
	PrintUID(new_uid);
	return (new_uid);
}

/*****************************************************************************/

static void  UIDIsSameTest(void)
{
	unique_id_t uid1 = {0, 0, 0};
	unique_id_t uid2 = {0, 0, 0};

	uid1 = UIDCreate();
	PrintUID(uid1);	
	uid2 = UIDCreate();
	PrintUID(uid2);
	
	if(UIDIsSame(uid1,uid2))
	{
		printf("The UIDs are not unique :(\n");
	}
	else
	{
		printf("The UIDs are unique :)\n");
	}
}

/*****************************************************************************/

static void UIDGetBadUIDTest(void)
{
	unique_id_t uid = {0, 0, 0};
	
	uid = UIDGetBadUID();
	printf("When we bad uid these are his values\n");
	PrintUID(uid);
}












