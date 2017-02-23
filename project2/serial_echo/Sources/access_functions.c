/*
 * access_functions.c
 *
 *  Created on: Feb 16, 2017
 *      Author: coltonp
 */

#include "access_functions.h"
//http://www.zentut.com/c-tutorial/c-linked-list/#Search_for_a_node
node_ptr create(_queue_id data ,node_ptr next)
{
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
        _mem_free(tmp);
    }
    return head;
}

// Nice function!
void print_list(node_ptr head) {
	node_ptr trav = head;
	int c = 0;
	while (trav != NULL) {
		printf("Count:%d, Item: %d, Qid:%d, Next:%d\n",c,trav,trav->data, trav->next);
		trav = trav->next;
		c++;
	}
}

// User Tasks access serial channel for reading
// Returns True if a read spot was available
// Returns false if
bool OpenR(_queue_id stream_no){

	if (OpenRStatus == false) {
		OpenRStatus = true;
		if (count(read_head) == 0) {
			read_head = create(stream_no, NULL);}
			if (read_head->next == NULL) {
			}
		else {read_head = append(read_head,stream_no);}
		return true;
	}
	else {
		return false;
	}
}


// blocking function
// User Task actually gets data from serial channel
bool _getline(char * string, _queue_id qid){ // every task has a unique Q id
	node_ptr caller = search(read_head,qid);
	if (caller == NULL) {return false;} // no read priviledge
	getlineStatus = true;

	MESSAGE_PTR get_msg_ptr = _msgq_receive(qid, 0);
			if (get_msg_ptr == NULL) {
					 printf("\nCould not receive an ISR message\n");
					 return false;
			}
	strcpy(string,get_msg_ptr->DATA);
	_msg_free(get_msg_ptr);
	return true;

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

		if (count(read_head) <= 1) {
			printf("count is now:%d\n",count(read_head));
			OpenRStatus = false;
			getlineStatus = false;
			OpenWStatus = false;
		}
		print_list(read_head);
		read_head = remove_any(read_head,to_delete);
		print_list(read_head);

		printf("count is now:%d\n",count(read_head));
		return true;
	}
}
