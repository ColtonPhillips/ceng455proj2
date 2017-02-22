/*
 * access_functions.c
 *
 *  Created on: Feb 16, 2017
 *      Author: coltonp
 */

#include "access_functions.h"

node_ptr create(_queue_id data ,node_ptr next)
{
	//node_ptr new_node = (node*)malloc(sizeof(node));
	node_ptr new_node = _mem_alloc(sizeof(node));
    if(new_node == NULL)
    {
        printf("Error creating a new node.\n");
        exit(0);
    }
    new_node->data = data;
    new_node->next = next;

    return new_node;
}

node_ptr prepend(node_ptr head,_queue_id data)
{
    node_ptr new_node = create(data,head);
    head = new_node;
    return head;
}

unsigned int count(node_ptr head)
{
    node_ptr cursor = head;
    int c = 0;
    while(cursor != NULL)
    {
        c++;
        cursor = cursor->next;
    }
    return c;
}

node_ptr append(node_ptr head, _queue_id data)
{
    // go to the last node
    node_ptr cursor = head;
    while(cursor->next != NULL)
        cursor = cursor->next;

    // create a new node
    node_ptr new_node =  create(data,NULL);
    cursor->next = new_node;

    return head;
}

node_ptr search(node_ptr head,_queue_id data)
{

	node_ptr cursor = head;
    while(cursor!=NULL)
    {
        if(cursor->data == data)
            return cursor;
        cursor = cursor->next;
    }
    return NULL;
}

node_ptr remove_back(node_ptr head)
{
    if(head == NULL)
        return NULL;

    node_ptr cursor = head;
    node_ptr back = NULL;
    while(cursor->next != NULL)
    {
        back = cursor;
        cursor = cursor->next;
    }
    if(back != NULL)
        back->next = NULL;

    // if this is the last node in the list
    if(cursor == head)
        head = NULL;

    //free(cursor);
    _mem_free(cursor);

    return head;
}

node_ptr remove_front(node_ptr head)
{
    if(head == NULL)
        return NULL;
    node_ptr front = head;
    head = head->next;
    front->next = NULL;
    // is this the last node in the list
    if(front == head)
        head = NULL;
    _mem_free(front);
//    free(front);
    return head;
}

node_ptr remove_any(node_ptr head,node_ptr nd)
{
    // if the node is the first node
    if(nd == head)
    {
        head = remove_front(head);
        return head;
    }

    // if the node is the last node
    if(nd->next == NULL)
    {
        head = remove_back(head);
        return head;
    }

    // if the node is in the middle
    node_ptr cursor = head;
    while(cursor != NULL)
    {
        if(cursor->next = nd)
            break;
        cursor = cursor->next;
    }

    if(cursor != NULL)
    {
        node* tmp = cursor->next;
        cursor->next = tmp->next;
        tmp->next = NULL;
       // free(tmp);
        _mem_free(tmp);
    }
    return head;
}


// User Tasks access serial channel for reading
// Returns True if a read spot was available
// Returns false if
bool OpenR(_queue_id stream_no){

	if (OpenRStatus == false) {
		OpenRStatus = true;
		if (count(read_head) == 0) { read_head = create(stream_no, read_head);}
		else {read_head = append(read_head,stream_no);}
		return true;
	}
	else {
		return false;
	}
}

// User Task actually gets data from serial channel
bool _getline(char * string, _queue_id qid){ // every task has a unique Q id
	//if (getlineStatus == false) {
		//getlineStatus = true;
		//return
	//}
}
// Access serial channel for writing
// Returns true if a write spot was available , else false
_queue_id OpenW(){
	if (OpenWStatus == false) {
		OpenWStatus = true;
		return true;
		}
	else {
		return false;
	}
}
// Actually put a string onto the serial channel
_queue_id _putline(_queue_id qid, char * string){
	return 1;
}

// Revoke read and/or write priveledges
bool Close(_queue_id qid) {
	node_ptr to_delete = search(read_head,qid);
	if (to_delete == NULL) {return false;}
	else {
		remove_any(read_head,to_delete);
		if (count(read_head) == 0) {OpenRStatus = false;}
	}
	return true;
}
