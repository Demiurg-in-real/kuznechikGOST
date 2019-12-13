#include<stdio.h>
#include<unistd.h>
#include<stdint.h>
#include<sys/stat.h>
#include<sys/mman.h>
#include<fcntl.h>
#include<math.h>
void maiN(int l){
	struct stat st;
	fstat(l, &st);
	uint8_t *ptr;
	uint8_t block[4];
//	block = new uint8_t [4];
	ptr=(uint8_t*)mmap(NULL,st.st_size, PROT_READ | PROT_WRITE,MAP_PRIVATE, l,0);
	if(ptr == NULL) perror("mmap");
//	block = ((ptr+0));
	for(int j=0; j<st.st_size;j++)printf("%2x\n", block[j]);
	fsync(l);
	printf("%i - %i\n", O_RDWR, st.st_mode);
	munmap(ptr, st.st_size);
}
int main(){
	long double res=log2l(12345);
	printf("%Lf\n", res);	
	return 0;
}

