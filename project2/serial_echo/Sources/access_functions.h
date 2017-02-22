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
//#include <mutex.h>
#include <message.h>
//#include "os_tasks.c"

// TODO: Mutex/Sem the data structures to prevent race conditions

// Linked List
typedef struct mynode {
	_queue_id data;
	struct node* next;
} node, * node_ptr;

node_ptr create (_queue_id data, node_ptr next);
node_ptr prepend(node_ptr head,_queue_id data);
unsigned int count(node_ptr head);
node_ptr append(node_ptr head, _queue_id data);
node_ptr search(node_ptr head,_queue_id data);
node_ptr remove_front(node_ptr head);
node_ptr remove_back(node_ptr head);
node_ptr remove_any(node_ptr head,node_ptr nd);

// Access Memory
bool OpenRStatus = false; // whether someone has access to R or W
bool getlineStatus = false;
bool OpenWStatus = false;
node_ptr  read_head;

// Access functions
bool OpenR(_queue_id stream_no);
bool _getline(char * string, _queue_id qid);
_queue_id OpenW();
_queue_id _putline(_queue_id qid, char * string);
bool Close(_queue_id qid);

#endif /* SOURCES_ACCESS_FUNCTIONS_H_ */
