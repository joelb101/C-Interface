#include<stdio.h>
#include<stdlib.h>
#include "mem.h"
#include "except.h"

int main(){
	
	int *p;
	
	TRY
		p = ALLOC(sizeof(*p)*10);
	EXCEPT(Assert_Failed)
		printf("Assertion Failed\n");
		exit(0);
	EXCEPT(Mem_failed)
		printf("Allocation Failed\n");
		exit(0);
	END_TRY;
	
	printf("Allocated memory\n");
	for(int i=0;i<10;++i)
		p[i]=i;
	for(int i=0;i<10;++i)
		printf("%d\n",p[i]);
	
	FREE(p);
	
	return 0;
}
