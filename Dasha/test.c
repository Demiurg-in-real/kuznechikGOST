#include<stdio.h>
#include<stdint.h>
#include<math.h>
void check(uint32_t num){
	for(int i=31; i>-1; i--) printf("%i",(num>>i)&0x1);
	printf("\n");
}
int main(){
	uint64_t kek=0x13579fed;
	uint64_t heh=0xfedcba34;
	uint64_t resu = (kek + heh)%0xffffffff;
	uint32_t res = kek+heh;
	uint8_t hehe=19, hehe1=245;
	uint16_t ruk = hehe+hehe1;
	check(hehe);
	check(hehe1);
	printf("--------------------\n");
	check(ruk);
	printf("%u\n", ruk%256);
//	printf("%lu == %u\n", resu,res);

	return 0;
}
