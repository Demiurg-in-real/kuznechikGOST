#include<stdio.h>
int main(){
	short int l=48634;
	short int c = l;
	for (int i=0; i<16;i++){
		printf("%x",((c<<i)>>15)&0x1);
	}
	return 0;
}
