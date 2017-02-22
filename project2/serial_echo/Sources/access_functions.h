/*
 * access_functions.h
 *
 *  Created on: Feb 16, 2017
 *      Author: coltonp
 */

#ifndef SOURCES_ACCESS_FUNCTIONS_H_
#define SOURCES_ACCESS_FUNCTIONS_H_

#include <stdio.h>
#include <mqx.h>
#include <bsp.h>
#include <mutex.h>
#include <message.h>
//#include "os_tasks.c"

// TODO: Mutex/Sem the data structures to prevent race conditions

// Access Memory
bool OpenRStatus = false; // whether someone has access to R or W
bool OpenWStatus = false;
_queue_id read_queue = -1;

// Access functions
bool OpenR(_queue_id stream_no);
bool _getline(char * string);
_queue_id OpenW();
_queue_id _putline(_queue_id qid, char * string);
bool Close();

#endif /* SOURCES_ACCESS_FUNCTIONS_H_ */
