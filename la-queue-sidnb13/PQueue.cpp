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
    if (len + 1 <= max_mqsize && strlen((char*)item) <= max_msgsize) {
        node *start = front;

        node *temp = new node;
        temp->priority = priority;
        temp->data = item;

        //cout << (front == nullptr) << endl;

        if (front == nullptr) {
            //cout << "CASE 1" << endl;
            front = temp;
        } else if (front->priority > priority) { //case to insert at front
            //cout << "CASE 2" << endl;
            temp->next = front;
            front = temp;
        } else {
            //cout << "CASE 3" << endl;
            while (start->next != nullptr && start->next->priority <= priority) //find insertion point
                start = start->next;
            //fit into LL
            temp->next = start->next;
            start->next = temp;
        }
    }
}

/*
 * Delete from Priority Queue
 */
void* PQueue::top() {
	if (front == nullptr)
        return nullptr;
	return front->data;
}
/*
 * Delete from Priority Queue
 */
void PQueue::pop() {
	if (front == nullptr)
        return;
    //node *temp = front;
    front = front->next;
    //delete temp;
}

/*
 * Print Priority Queue
 */
__unused void PQueue::display() {
	node *temp = front;
	//cout << "TEST" << endl;
	while (temp != nullptr) {
        std::cout<<temp->priority<<" "<<(char*)temp->data<<std::endl;
	    temp = temp->next;
	}
	/* Use the following out command for the data */
	//std::cout<<ptr->priority<<" "<<(char*)ptr->data<<std::endl;
}