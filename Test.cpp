#include<stdio.h>
#include<unistd.h>
#include<stdint.h>
#include<sys/stat.h>
#include<sys/mman.h>
#include<fcntl.h>
struct he{
	uint8_t tes[32];
}__attribute__((packed));
int main(){
	uint8_t c[4];
	*((uint16_t*)((uint16_t*)(c)))=0x1234;
	printf("%2x %2x", c[0],c[1]);
	return 0;
}

