	/* * * * * * * * * * * * * * * * * * * * * * * * * * * *
	 * 		LASAalloc.h
	 * 		LASAalloc class declaration.  
	 * 
	 * 		Do not change this file other than to add local varaibles and Functions.
	 *    Make any changes only in the provided block.
	 * * * * * * * * * * * * * * * * * * * * * * * * * * * */

#include<iostream>
#include<cstdlib>
#include "LASAalloc.h"

// Defines for LASAalloc buffer simulation.  
// Keep it simple, no changes to program break
#define INITIAL_MALLOC_SIZE 100000 //100000

using namespace std;


typedef unsigned char BYTE_t;

//BYTE_t buffer[MAX_MALLOC_SIZE];

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

	cout << "---------------------------------------------" << endl;

    cout << endl;
}

LASAalloc::~LASAalloc() { //TODO destructor
    free_list_header = nullptr;
    free(bufferBase);
}

void LASAalloc::display_node(struct block *p) { //NOLINT
    cout << "block: " << p << endl;
    cout << "\t\tsize: " << p->size << endl;
    cout << "\t\tnext: " << p->next << endl;
    cout << "\t\tprev: " << p->prev << endl;
    cout << "\t\tbuffer: " << p->space << endl;
}

void LASAalloc::printFreeList() {
	block * begin = free_list_header;
    struct block *p;
	if (begin == nullptr) {
		cout<<"List is empty\n\n\n";
		return;
	}
	p = begin;

	cout<<"List is:\n";
    //cout << "Global header: "; display_node(free_list_header);
	while(p != nullptr) {
		display_node(p);
		p=p->next;
	}
	cout << endl;
}

int LASAalloc::rounded(int x) {return ((x + 7) & (-8));} //NOLINT

void* LASAalloc::lalloc(int x) { //NOLINT
    block * header = free_list_header;
    x = rounded(x);

    while (header != nullptr) {
        if (x > header->size) {
            header = header->next;
            if (header == nullptr) {
                cout << "Out of memory" << endl;
                return nullptr; //preserves free list, no allocation
            }
            continue; //check next header for fit
        }

        if (x + 32 >= header->size) { //hijack

            //cout << "hijack" << endl;

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

        } else {
            auto * new_header = (struct block *) ((BYTE_t *) header + 32 + x);
            new_header->size = header->size - 32 - x;
            new_header->space = (BYTE_t *) new_header + 32;

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

            header->size = x;

            //cout << "new header size, non hijack: " << new_header->size << endl;
        }



       /* cout << "header size: " << header->size << endl;
        auto * str = (struct block *) ((BYTE_t *) header->space - 32);
        cout << "struct from space size: " << str->size << endl;*/

        return header->space;

    }

    cout << "Memory not allocated" << endl;
    return nullptr;

}

void LASAalloc::merge(block * p, block * n) { //NOLINT
    p->next = n->next;
    if (n->next != nullptr)
        n->next->prev = p;
    p->size = p->size + n->size + 32;
}

void LASAalloc::lfree(void * spc) {
    //cout << "Free list header: " << free_list_header << endl;

    block * header = free_list_header;
    auto * alloc = (struct block *) ((BYTE_t *) spc - 32); //memory to be freed

    //cout << "alloc: " << alloc->prev << endl;

    if (header == nullptr) { //initially empty list no merge
        free_list_header = alloc;
        //cout << "initially empty list" << endl;
        return;
    }

    while (true) {
        if (header->prev == nullptr) { //initially head (includes singular)
            if (alloc->space < header->space) {
                alloc->next = header;
                header->prev = alloc;
                free_list_header = alloc;
                //cout << "initially head (includes singular)" << endl;
                break;
            }
        } else if (header->next == nullptr) { //initially end (singular)
            if (alloc->space < header->space) {
                alloc->next = header;
                alloc->prev = header->prev;
                header->prev->next = alloc;
                header->prev = alloc;
                //cout << "initially end (singular)" << endl;
            } else {
                alloc->prev = header;
                header->next = alloc;
            }
            break;
        } else if (header->prev != nullptr && header->next != nullptr) { //initially nonsingular between
            if (alloc->space < header->space) {
                alloc->next = header;
                alloc->prev = header->prev;
                header->prev->next = alloc;
                header->prev = alloc;
                break;
            }
        }

        header = header->next; //none of cases satisfy
    }

    /*block * p;
    block * n;*/

    if (alloc->next != nullptr && (struct block *) ((BYTE_t *) alloc->space + alloc->size) == alloc->next) { // right-merge
        //cout << "Merge-R" << endl;
        merge(alloc, alloc->next);
    }
    if (alloc->prev != nullptr && (struct block *) ((BYTE_t *) alloc->prev->space + alloc->prev->size) == alloc) {// left-merge
        //cout << "Merge-L" << endl;
        merge(alloc->prev, alloc);
    }
}

/*
 *   >>>>>>  DO NOT CHANGE THIS SECTION  <<<<<<<
 * 
 * brk()
 * Function to simulate the libc brk() function to allocate memory for a buffer
 * 
 */

void * LASAalloc::brk(int size) {
	if (size != 0) {
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