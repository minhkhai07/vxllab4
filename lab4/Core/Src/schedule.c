/*
 * schedule.c
 *
 *  Created on: Nov 25, 2024
 *      Author: Admin
 */
#include "schedule.h"
uint8_t cur_taskID=0;
sTask SCH_tasks_G[SCH_MAX_TASKS];
void SCH_Init (void){
	for(uint8_t i=0; i<SCH_MAX_TASKS;i++)
	{
		SCH_delete_task(i);
	}
cur_taskID=0;
error_code_G = 0;
}

void SCH_Add_Task ( void (*pFunction) () , uint32_t DELAY, uint32_t PERIOD){
	if(cur_taskID<SCH_MAX_TASKS){
		SCH_tasks_G[cur_taskID].pTask = pFunction ;
		SCH_tasks_G[cur_taskID].delay = DELAY;
		SCH_tasks_G[cur_taskID].period = PERIOD;
		SCH_tasks_G[cur_taskID].runme = 0;
		SCH_tasks_G[cur_taskID].taskID = cur_taskID;
		cur_taskID++;
	}
	else
	{
		error_code_G=ERROR_SCH_TOO_MANY_TASKS;
		return;
	}
}
void SCH_Update(void)
{
		for(uint8_t ind=0; ind<cur_taskID; ind++)
		{
			if(SCH_tasks_G[ind].pTask){
				if(SCH_tasks_G[ind].delay<=0)
				{
					SCH_tasks_G[ind].runme+=1;
					if(SCH_tasks_G[ind].period>0){
						SCH_tasks_G[ind].delay=SCH_tasks_G[ind].period;
					}
				}
				else{
				SCH_tasks_G[ind].delay-=1;
				}
			}
		}
}
void SCH_dispatch_tasks(void)
{
	for(uint8_t ind=0; ind<cur_taskID; ind++)
	{
		if(SCH_tasks_G[ind].runme>0)
		{
			(*SCH_tasks_G[ind].pTask)();
			SCH_tasks_G[ind].runme-=1;
			if(SCH_tasks_G[ind].period==0)
			{
				SCH_delete_task(ind);
				ind--;
			}
		}
	}
	SCH_rp_status();
}

void SCH_delete_task (const tByte TASK_INDEX) {
	if(TASK_INDEX >= cur_taskID || SCH_tasks_G[TASK_INDEX].pTask==0){
		error_code_G = ERROR_SCH_CANNOT_DELETE_TASK;
		return;
	}
	SCH_tasks_G[TASK_INDEX].pTask = 0x0000;
	SCH_tasks_G[TASK_INDEX].delay = 0;
	SCH_tasks_G[TASK_INDEX].period = 0;
	SCH_tasks_G[TASK_INDEX].runme = 0;
	error_code_G = 0;
}

void SCH_rp_status(void)
{
#ifdef SCH_REPORT_ERRORS
	if(error_code_G!=Last_error_code_G)
	{
		error_port->ODR = 255 - error_code_G;
		Last_error_code_G=error_code_G;
		if(error_code_G!=0){
			Error_tick_count_G = 60000;
		}else{
			Error_tick_count_G = 0;
		}
	}else{
		if(Error_tick_count_G!=0){
			if(--Error_tick_count_G == 0)
			{
				error_code_G=0;
			}
		}
	}
#endif
}



