	/* * * * * * * * * * * * * * * * * * * * * * * * * * * *
	 * 		LASAalloc.h
	 * 		LASAalloc class declaration.  
	 * 
	 * 		Do not change this file other than to add local varaibles and Functions.
	 *    Make any changes only in the provided block.
	 * * * * * * * * * * * * * * * * * * * * * * * * * * * */

#include<iostream>
#include<stdlib.h>
#include "LASAalloc.h"

// Defines for LASAalloc buffer simulation.  
// Keep it simple, no changes to program break
#define INITIAL_MALLOC_SIZE 100000
#define MAX_MALLOC_SIZE 100000 //100000

using namespace std;

block *free_list_header;
typedef unsigned char BYTE_t;

BYTE_t buffer[MAX_MALLOC_SIZE];

LASAalloc::LASAalloc() {
	brk(INITIAL_MALLOC_SIZE);
	
	// Point to where first node will be located.
	free_list_header = (block*)bufferBase;
	freeList = free_list_header;
	
	// Configure first node on freeList
	free_list_header->size = (int)(bufferSize - sizeof(block));
	free_list_header->prev = nullptr;
	free_list_header->next = nullptr;
	free_list_header->space = (void*)((long long int)bufferBase+(long long int)sizeof(block));

    /*freeList = (struct block *)buffer;
    freeList->next_block = nullptr;
    freeList->prev_block = nullptr;
    freeList->size = sizeof(buffer) - sizeof(struct block);
    freeList->this_block_data = (BYTE_t *)(buffer + sizeof(struct block));*/

	// Show initial statistics
	cout<<"buffer allocation: "<< bufferBase << " - " << brk(0) << endl;
	cout<<"free_list_header: "<< freeList << " - " << brk(0) << endl;
	cout<<"block header size " << sizeof(block) << endl;
	cout<<"integer size " << sizeof(int) << endl;
	
	display_node(freeList);
}

LASAalloc::~LASAalloc() { //TODO destructor

}

void LASAalloc::display_node(struct block *p) {
    cout << "Prev: " << p->prev;
    cout << "\tNext: " << p->next;
    cout << "\tSize: " << p->size;
    cout << "\tThis: " << p->space << endl;
    cout << endl;
}

void LASAalloc::printFreeList() {
	block * begin = free_list_header;
    struct block *p;
	if(begin == nullptr) {
		cout<<"List is empty\n";
		return;
	}
	p = begin;
	cout<<"List is:\n";
	while(p != nullptr) {
		display_node(p);
		p=p->next;
	}
	cout<<"\n";
}

void* LASAalloc::lalloc(int x) { //NOLINT
    block * header = free_list_header;

    //cout << header->size << endl;

    while (header != nullptr) {
        if (x > header->size) {
            header = header->next;
            if (header == nullptr)
                return nullptr; //preserves free list, no allocation
            continue; //check next header for fit
        }

        if (x + 32 >= header->size) { //hijack
            header->size = x;

            if (header->next == nullptr && header->prev == nullptr) {
                free_list_header = nullptr;
            } else if (header->next == nullptr && header->prev != nullptr) { //at end of list
                header->prev->next = nullptr;
                header->prev = nullptr;
            } else if (header->next != nullptr && header->prev == nullptr) { //head of list
                header->next->prev = nullptr;
                free_list_header = header->next;
                header->next = nullptr;
            } else {
                header->next->prev = header->prev;
                header->prev->next = header->next;
                header->prev = nullptr;
                header->next = nullptr;
            }

            return header;

        } else {
            block * new_header = header + 32 + x;
            new_header->size = header->size - 32 - x;

            if (header->next == nullptr && header->prev == nullptr) {
                new_header->next = nullptr;
                new_header->prev = nullptr;
                free_list_header = new_header;
            } else if (header->next == nullptr && header->prev != nullptr) { //at end of list
                new_header->next = nullptr;
                new_header->prev = header->prev;
            } else if (header->next != nullptr && header->prev == nullptr) { //head of list
                new_header->next = header->next;
                new_header->prev = nullptr;
                free_list_header = new_header;
            } else {
                new_header->next = header->next;
                new_header->prev = header->prev;
            }

            return new_header;
        }
    }

    return nullptr;
}

void* LASAalloc::lfree(void* userBlock) { //TODO lfree and merge
	
}

/*
 *   >>>>>>  DO NOT CHANGE THIS SECTION  <<<<<<<
 * 
 * brk()
 * Function to simulate the libc brk() function to allocate memory for a buffer
 * 
 */

void * LASAalloc::brk(int size) {
	if (size !=0) {
		if (bufferBase == nullptr) {
			bufferBase = malloc(size);
			bufferSize = size;
		}
		else {
			cout<<"buffer already locked\n";
			return nullptr;
		}
		
	}
	return bufferSize + (char*) bufferBase;
}