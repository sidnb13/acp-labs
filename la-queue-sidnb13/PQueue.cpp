#include <__bit_reference>
/*
 * LaQueue
 * 
 * 
 * This is part of a series of labs for the Liberal Arts and Science Academy.
 * The series of labs provides a mockup of an POSIX Operating System
 * referred to as LA(SA)nix or LAnix.
 *  
 * (c) copyright 2018, James Shockey - all rights reserved
 * 
 * */

#include <iostream>
#include "PQueue.h"

using namespace std;

/*
 * Class Priority Queue
 */

/*
* Insert into Priority Queue
*/
void PQueue::push(void *item, int priority) {
	/* Your code here */
	node *start = front;

	node *temp = new node;
    temp->priority = priority;
    temp->data = item;

	if (front == nullptr) {
	    front = temp;
    } else if (front->priority > priority) { //case to insert at front
	    temp->next = front;
	    front = temp;
	} else {
        while (start->next != nullptr && start->next->priority < priority) //find insertion point
            start = start->next;
        //fit into LL
        temp->next = start->next;
        start->next = temp;
	}
}

/*
 * Delete from Priority Queue
 */
void* PQueue::top() {
	/* Your code here */
	if (front == nullptr)
        return nullptr;
	return front->data;
}
/*
 * Delete from Priority Queue
 */
void PQueue::pop() {
	/* Your code here */
	if (front != nullptr) {
        node *temp = front;
        front = front->next;
        delete temp;
    }
}

/*
 * Print Priority Queue
 */
void PQueue::display() {
	/* Your code here */
	node *temp = front;
	if (temp == nullptr)
        return;
	while (temp->next != nullptr) {
        std::cout<<temp->priority<<" "<<(char*)temp->data<<std::endl;
	    temp = temp->next;
	}
	/* Use the following out command for the data */
	//std::cout<<ptr->priority<<" "<<(char*)ptr->data<<std::endl;
}
	