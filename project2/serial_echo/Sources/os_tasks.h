/* ###################################################################
**     Filename    : os_tasks.h
**     Project     : serial_echo
**     Processor   : MK64FN1M0VLL12
**     Component   : Events
**     Version     : Driver 01.00
**     Compiler    : GNU C Compiler
**     Date/Time   : 2017-02-13, 16:56, # CodeGen: 1
**     Abstract    :
**         This is user's event module.
**         Put your event handler code here.
**     Settings    :
**     Contents    :
**         serial_task - void serial_task(os_task_param_t task_init_data);
**
** ###################################################################*/
/*!
** @file os_tasks.h
** @version 01.00
** @brief
**         This is user's event module.
**         Put your event handler code here.
*/         
/*!
**  @addtogroup os_tasks_module os_tasks module documentation
**  @{
*/         

#ifndef __os_tasks_H
#define __os_tasks_H
/* MODULE os_tasks */

#include "fsl_device_registers.h"
#include "clockMan1.h"
#include "pin_init.h"
#include "osa1.h"
#include "mqx_ksdk.h"
#include "uart1.h"
#include "fsl_mpu1.h"
#include "fsl_hwtimer1.h"
#include "MainTask.h"
#include "SerialTask.h"
#include "myUART.h"
#include "UserTask.h"

#ifdef __cplusplus
extern "C" {
#endif 

// CUSTOM CODE

#include <message.h>
#include <mqx.h>
#include <bsp.h>
#include <mutex.h>
#include "access_functions.h"

#define HANDLER_QUEUE 8
#define PUTLINE_QUEUE 9
#define GETLINE_QUEUE 10

#define BUFFER_SIZE 256

// this struct is also used for putline and getline
typedef struct my_messsage
{
	MESSAGE_HEADER_STRUCT HEADER;
	unsigned char DATA[64];
} MESSAGE, * MESSAGE_PTR;

MESSAGE_PTR msg_ptr; // ISR message
_queue_id          	handler_qid; // For the isr
_queue_id          	putline_qid; // For putline (when a user task writes)

_pool_id   			message_pool;

// Message Buffer(s)
unsigned char msgBuf[BUFFER_SIZE];
unsigned char txBuf[BUFFER_SIZE];

// The characters that are typed in, and edited with special keywords
unsigned char handleBuf[BUFFER_SIZE] = "";

// Number of User Tasks
static int num_of_tasks = 0;

MUTEX_STRUCT accessmutex;
MUTEX_ATTR_STRUCT mutexattr;

/*
** ===================================================================
**     Callback    : serial_task
**     Description : Task function entry.
**     Parameters  :
**       task_init_data - OS task parameter
**     Returns : Nothing
** ===================================================================
*/
void serial_task(os_task_param_t task_init_data);


/*
** ===================================================================
**     Callback    : user_task
**     Description : Task function entry.
**     Parameters  :
**       task_init_data - OS task parameter
**     Returns : Nothing
** ===================================================================
*/
void user_task(os_task_param_t task_init_data);

/* END os_tasks */

#ifdef __cplusplus
}  /* extern "C" */
#endif 

#endif 
/* ifndef __os_tasks_H*/
/*!
** @}
*/
/*
** ###################################################################
**
**     This file was created by Processor Expert 10.5 [05.21]
**     for the Freescale Kinetis series of microcontrollers.
**
** ###################################################################
*/
