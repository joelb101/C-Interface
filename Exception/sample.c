#include<stdio.h>
#include "except.h"
#include <stdlib.h>

Except_T Failed={"error"};

void di(){
	RAISE(Failed);
}

int main(){
	
	TRY
		printf("Inside Try\n");
		di();
		printf("Executed div()\n");
	EXCEPT(Failed)
		printf("inside except block\n");
		printf("div thrown error\n");
		exit(0);
	FINALLY
		printf("Inside finally\n");
	END_TRY;
	
	printf("Outside try\n");
	
	return 0;

}
