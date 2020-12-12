
/*
 * LALLOC Main test
 * 
 * Choose test by using macro SIMPLETEST1 or SIMPLETEST2
 * 
 * Do not change anything else in this file
 */ 
#define SIMPLETEST1

#include <unistd.h>
#include <cstdlib>
#include <cstdio>
#include <iostream>
#include"LASAalloc.h"

#ifdef SIMPLETEST1
int main() {
    LASAalloc lasa;
	char *array;
	int i;

	array = (char *)lasa.lalloc(10);

	if (array == nullptr) {
		fprintf(stderr,"call to lasa.lalloc() failed\n");
		fflush(stderr);
		exit(1);
	}

	for(i=0; i < 9; i++) {
		array[i] = 'a' + i;
	}
	array[9] = 0;

	printf("here is my nifty new string: %s\n",array);

	lasa.printFreeList();

	lasa.lfree(array);
}

	
#endif //SIMPLETEST1

#ifdef SIMPLETEST2

#include <unistd.h>
#include <cstdlib>
#include <cstdio>

#include "LASAalloc.h"

int main(int argc, char *argv[])
{
	char *a1;
	char *a2;
	char *a3;
	char *a4;

	
	LASAalloc	lasa;



	a1 = (char *)lasa.lalloc(128);
	if(a1 == nullptr)
	{
		fprintf(stderr,"call to lasa.lalloc(128) failed\n");
		fflush(stderr);
		exit(1);
	}

	printf("FREE LIST after malloc(128)\n");
	lasa.printFreeList();

	a2 = (char *)lasa.lalloc(32);
	if(a2 == nullptr)
	{
		fprintf(stderr,"first call to lasa.lalloc(32) failed\n");
		fflush(stderr);
		exit(1);
	}

	printf("FREE LIST after malloc(32)\n");
	lasa.printFreeList();

	lasa.lfree(a1);

	printf("FREE LIST after free of first 128 malloc()\n");
	lasa.printFreeList();

	a3 = (char *)lasa.lalloc(104);
	if(a3 == nullptr)
	{
		fprintf(stderr,"call to lasa.lalloc(104) failed\n");
		fflush(stderr);
		exit(1);
	}

	printf("FREE LIST after malloc(104)\n");
	lasa.printFreeList();

	a4 = (char *)lasa.lalloc(8);
	if(a4 == nullptr)
	{
		fprintf(stderr,"call to lasa.lalloc(8) failed\n");
		fflush(stderr);
		exit(1);
	}
	printf("FREE LIST after malloc(8)\n");
	lasa.printFreeList();

	/*
	 * free it all -- notice that a1 is already free
	 */
	lasa.lfree(a2);
	lasa.lfree(a3);
	lasa.lfree(a4);
	printf("FREE LIST after all free\n");
	lasa.printFreeList();


	return(0);
}

	

#endif	//ACTIVE
