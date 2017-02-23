/* ###################################################################
**     Filename    : Events.c
**     Project     : serial_echo
**     Processor   : MK64FN1M0VLL12
**     Component   : Events
**     Version     : Driver 01.00
**     Compiler    : GNU C Compiler
**     Date/Time   : 2017-02-13, 16:45, # CodeGen: 0
**     Abstract    :
**         This is user's event module.
**         Put your event handler code here.
**     Settings    :
**     Contents    :
**         No public methods
**
** ###################################################################*/
/*!
** @file Events.c
** @version 01.00
** @brief
**         This is user's event module.
**         Put your event handler code here.
*/         
/*!
**  @addtogroup Events_module Events module documentation
**  @{
*/         
/* MODULE Events */

#include "Cpu.h"
#include "Events.h"
#include "rtos_main_task.h"
#include "os_tasks.h"

#ifdef __cplusplus
extern "C" {
#endif 


/* User includes (#include below this line is not maintained by Processor Expert) */
#include <stdio.h>
#include <mqx.h>
#include <bsp.h>
#include "os_tasks.h"
#include <message.h>

/*
** ===================================================================
**     Callback    : myUART_RxCallback
**     Description : This callback occurs when data are received.
**     Parameters  :
**       instance - The UART instance number.
**       uartState - A pointer to the UART driver state structure
**       memory.
**     Returns : Nothing
** ===================================================================
*/
void myUART_RxCallback(uint32_t instance, void * uartState)
{
	// Allocate a message
	msg_ptr = (MESSAGE_PTR)_msg_alloc(message_pool);
	 if (msg_ptr == NULL) {
		 printf("\nCould not allocate a message\n");
		 _task_block();
	  }

	 // Populate a message
	 msg_ptr->HEADER.SOURCE_QID = 0;
	 msg_ptr->HEADER.TARGET_QID = _msgq_get_id(0, HANDLER_QUEUE);
	 msg_ptr->HEADER.SIZE = sizeof(MESSAGE_HEADER_STRUCT) +
		 strlen((char *)msg_ptr->DATA) + 1;
	 sprintf(msg_ptr->DATA , myRxBuff);

	  // Send the message
	  if (!_msgq_send(msg_ptr)) {
	  	 printf("\nCould not send a message\n");
	  	 _task_block();
	  }

}

/* END Events */

#ifdef __cplusplus
}  /* extern "C" */
#endif 

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
