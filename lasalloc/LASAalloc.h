	/* * * * * * * * * * * * * * * * * * * * * * * * * * * *
	 * 		LASAalloc.h
	 * 		LASAalloc class declaration.  
	 * 
	 * 		Do not change this file other than to add local variables and Functions.
	 *    Make any changes only in the provided block.
	 * * * * * * * * * * * * * * * * * * * * * * * * * * * */

#ifndef LALLOC_H
#define LALLOC_H

using namespace std;

typedef unsigned char byte_t;

struct block {
	struct block *prev;
	struct block *next;
	int size;
	void * space;
};

class LASAalloc {
	void* 	bufferBase = nullptr;
	int		bufferSize = 0;
	block*	freeList = nullptr;
	
	// Helper function
	static void display_node(struct block *p);
	
	/* * * * * * * * * * * * * * * * * * * * * * * * * * * *
	 * 		Student supplied local instance variables
	 * 		and functions. 
	 * 
	 * 		These must only be private.
	 */



	/*
	 *    End student changes 
	 *
	 * * * * * * * * * * * * * * * * * * * * * * * * * * * */

public:
	LASAalloc();
	~LASAalloc();

	void * lalloc(int x);
	void* lfree(void* userBlock);

    static void printFreeList();
	void* brk(int size);
};

#endif // LALLOC_H