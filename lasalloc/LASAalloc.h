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
	struct block *prev_block;
	struct block *next_block;
	int size;
	bool freeFlag;					//Wasteful of memory but simple (in reality a bit field)
	void *this_block_data;
};

class LASAalloc {
	void* 	bufferBase= nullptr;
	int		bufferSize = 0;
	block*	freeList = nullptr;
	
	// Helper function
	void display_node(struct block *p);
	void* findFit(int size);
	void* split(block* target, int size);
	
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

	void* lalloc(int size);
	void* lfree(void* userBlock);

	void display(struct block *begin);
	void* brk(int size);
};

#endif // LALLOC_H