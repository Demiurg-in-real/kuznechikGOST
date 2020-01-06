#include <stddef.h>
#include <stdint.h>
#include <stdio.h>
#include<string.h>
/*
  Name  : CRC-32
  Poly  : 0x04C11DB7    x^32 + x^26 + x^23 + x^22 + x^16 + x^12 + x^11
                       + x^10 + x^8 + x^7 + x^5 + x^4 + x^2 + x + 1
  Init  : 0xFFFFFFFF
  Revert: true
  XorOut: 0xFFFFFFFF
  Check : 0xCBF43926 ("123456789")
  MaxLen: 268 435 455 байт (2 147 483 647 бит) - обнаружение
   одинарных, двойных, пакетных и всех нечетных ошибок
*/
uint32_t Crc32(unsigned char *buf, size_t len)
{
    uint32_t crc_table[256];
    uint32_t crc; int i, j;

    for (i = 0; i < 256; i++)
    {
        crc = i;
        for (j = 0; j < 8; j++)
            crc = crc & 1 ? (crc >> 1) ^ 0xEDB88320UL : crc >> 1;

        crc_table[i] = crc;
    };

    crc = 0xFFFFFFFFUL;

    while (len--)
        crc = crc_table[(crc ^ *buf++) & 0xFF] ^ (crc >> 8);

    return crc ^ 0xFFFFFFFFUL;
}
uint32_t crc32c(unsigned char *buf, size_t len){
	uint32_t crc = 0xffffffff;
	uint32_t pol = 0xedb88320;
	for(int i = 0; i<len;i++){
		for(int k = 7; k != -1; k--)printf("%i",(buf[i]>>k)&0x1);
		printf(" - buf[%i]\n",i);
		uint32_t c = (crc ^ buf[i])&0xff;
		for(int r = 0; r<8;r++){
			for(int k=31; k!=-1;k--)printf("%i",((c^0xffffffff)>>k)&0x1);
			printf(" - the begin of operation\n");
			c = (c&1) != 0 ? pol^(c>>1) : c>>1;
			for(int k = 31;k!=-1;k--) printf("%i", ((c^0xffffffff)>>k)&0x1);
			printf(" - result\n");
		}
		printf("\n");
		for(int k=31; k!= -1; k--) printf("%i", ((crc^0xffffffff)>>k)&0x1);
		printf(" - %i crc operation\n\n",i);
		crc = c^(crc>>8);
	}
	return crc ^ 0xffffffff;
}
int main(){
	unsigned char kek[256];
	fgets(kek,256,stdin);
	for(int i = 0; i<strlen(kek); i++) printf("%x ", kek[i]);	
	unsigned char kuku[4] = {0x5f,0x34,0x1d,0x8c};
	printf("%x - crc32\n", Crc32(kek,strlen(kek)));
	return 0;
}
