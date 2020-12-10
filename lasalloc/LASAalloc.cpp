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
#define MAX_MALLOC_SIZE 100000


using namespace std;

//typedef unsigned char BYTE_t;

LASAalloc::LASAalloc() {
	brk(INITIAL_MALLOC_SIZE);
	
	// Point to where first node will be located.
	auto* firstBlock = (block*)bufferBase;
	freeList = firstBlock;
	
	// Configure first node on freeList
	firstBlock->size = (int)(bufferSize);
	firstBlock->prev_block = nullptr;
	firstBlock->next_block = nullptr; 
	firstBlock->this_block_data = (void*)((long long int)bufferBase+(long long int)sizeof(block)); 
	firstBlock->freeFlag = true; 
	
	// Show initial statistics
	cout<<"buffer Allocation: "<< bufferBase << " - " << brk(0) << endl;
	cout<<"freeList: "<< freeList << " - " << brk(0) << endl;
	cout<<"Block header size " << sizeof(block) << endl;
	cout<<"integer size " << sizeof(int) << endl;
	
	display_node(freeList);

}

LASAalloc::~LASAalloc() {

}

void LASAalloc::display_node(struct block *p) {
		cout << "Prev: " << p->prev_block;
		cout << "\tNext: " << p->next_block;
		cout << "\tFree: " << p->freeFlag;
		cout << "\tSize: " << p->size;
		cout << "\tThis: " << p->this_block_data << endl;
		cout << endl;	
}

void LASAalloc::display(struct block *begin) {
	struct block *p;
	if(begin==nullptr) {
		cout<<"List is empty\n";
		return;
	}
	p=begin;
	cout<<"List is :\n";
	while(p!=nullptr) {
		display_node(p);
		p=p->next_block;
	}
	cout<<"\n";
}

void* LASAalloc::lalloc(int size) {
	
}


void* LASAalloc::lfree(void* userBlock) {
	
}

void* LASAalloc::findFit(int size) {
	
}

void* LASAalloc::split(block* target, int size) {
	
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
			cout<<"buffer already locked/n";
			return nullptr;
		}
		
	}
	return bufferSize + (char*) bufferBase;
}