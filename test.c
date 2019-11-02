#include<stdio.h>
#include<unistd.h>
#include<inttypes.h>
int main(){
	uint64_t *i = 0x1122334455667788;
	uint8_t l;
	l=(uint8_t*)(i);
	printf("%16x\n\n%16x\n",i,*i);
	return 0;
}
