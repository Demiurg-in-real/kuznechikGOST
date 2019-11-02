#include<stdio.h>
#include<unistd.h>
#include<inttypes.h>
int main(int argc,char* argv[]){
	char key[10];
	char strok[10];
	char xor[10];
	FILE *ptr=fopen(argv[1],"rb");
	if (ptr == NULL){
		perror("fopen");
		return 0;
	}
	fread(key,sizeof(char),9,ptr);
	fread(strok,sizeof(char),9,ptr);
	printf("%s\n",key);
	for(int i=0;i<10;i++)printf("%2x ",key[i]);
	printf("\n%s\n",strok);
	for(int i=0;i<10;i++) printf("%2x ",strok[i]);
	printf("\n\n");
	for(int i=0;i<10;i++){
		xor[i]=key[i] ^ strok[i];
		printf("%2x ",xor[i]);
	}
	return 0;
}
