/*
 * schedule.h
 *
 *  Created on: Nov 25, 2024
 *      Author: Admin
 */

#ifndef INC_SCHEDULE_H_
#define INC_SCHEDULE_H_
#include <stdint.h>
#include <stdlib.h>
#include "main.h"
#include "error.h"


typedef uint8_t tByte;
typedef struct {
void (*pTask) (void);
uint32_t delay;
uint32_t period;
uint8_t runme;
uint32_t taskID;
} sTask;

#define SCH_MAX_TASKS 5
#define NO_TASK_ID 	  0


void SCH_Init (void);
void SCH_Add_Task ( void (*pFunction) () , uint32_t DELAY, uint32_t PERIOD);
void SCH_Update (void);
void SCH_dispatch_tasks(void);
void SCH_delete_task (const tByte TASK_INDEX);
void SCH_rp_status(void);

#endif /* INC_SCHEDULE_H_ */
