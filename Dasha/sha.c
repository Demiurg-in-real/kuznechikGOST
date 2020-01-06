#include<stdio.h>
#include<stdlib.h>
#include<stdint.h>
#include<string.h>
#include<error.h>
#include<signal.h>
uint32_t  rotr(uint32_t cn,int how){
	return /*(cn>>how) | (cn<<(32-how));*/((cn>>how)&0xffffffff)^((cn<<(32-how))&0xffffffff);
}

void sha256(uint8_t *str){
	uint32_t h0 = 0x6A09E667;
	uint32_t h1 = 0xBB67AE85;
	uint32_t h2 = 0x3C6EF372;
	uint32_t h3 = 0xA54FF53A;
	uint32_t h4 = 0x510E527F;
	uint32_t h5 = 0x9B05688C;
	uint32_t h6 = 0x1F83D9AB;
	uint32_t h7 = 0x5BE0CD19;
//	uint32_t k[64]={
//		0x428A2F98, 0x71374491, 0xB5C0FBCF, 0xE9B5DBA5, 0x3956C25B, 0x59F111F1, 0x923F82A4, 0xAB1C5ED5,
//		0xD807AA98, 0x12835B01, 0x243185BE, 0x550C7DC3, 0x72BE5D74, 0x80DEB1FE, 0x9BDC06A7, 0xC19BF174,
//		0xE49B69C1, 0xEFBE4786, 0x0FC19DC6, 0x240CA1CC, 0x2DE92C6F, 0x4A7484AA, 0x5CB0A9DC, 0x76F988DA,
//		0x983E5152, 0xA831C66D, 0xB00327C8, 0xBF597FC7, 0xC6E00BF3, 0xD5A79147, 0x06CA6351, 0x14292967,
//		0x27B70A85, 0x2E1B2138, 0x4D2C6DFC, 0x53380D13, 0x650A7354, 0x766A0ABB, 0x81C2C92E, 0x92722C85,
//		0xA2BFE8A1, 0xA81A664B, 0xC24B8B70, 0xC76C51A3, 0xD192E819, 0xD6990624, 0xF40E3585, 0x106AA070,
//		0x19A4C116, 0x1E376C08, 0x2748774C, 0x34B0BCB5, 0x391C0CB3, 0x4ED8AA4A, 0x5B9CCA4F, 0x682E6FF3,
//		0x748F82EE, 0x78A5636F, 0x84C87814, 0x8CC70208, 0x90BEFFFA, 0xA4506CEB, 0xBEF9A3F7, 0xC67178F2
//	};
	uint32_t k[64]={0x428a2f98, 0x71374491, 0xb5c0fbcf, 0xe9b5dba5, 0x3956c25b, 0x59f111f1, 0x923f82a4, 0xab1c5ed5, 0xd807aa98, 0x12835b01, 0x243185be, 0x550c7dc3, 0x72be5d74, 0x80deb1fe, 0x9bdc06a7, 0xc19bf174, 0xe49b69c1, 0xefbe4786, 0x0fc19dc6, 0x240ca1cc, 0x2de92c6f, 0x4a7484aa, 0x5cb0a9dc, 0x76f988da, 0x983e5152, 0xa831c66d, 0xb00327c8, 0xbf597fc7, 0xc6e00bf3, 0xd5a79147, 0x06ca6351, 0x14292967, 0x27b70a85, 0x2e1b2138, 0x4d2c6dfc, 0x53380d13, 0x650a7354, 0x766a0abb, 0x81c2c92e, 0x92722c85, 0xa2bfe8a1, 0xa81a664b, 0xc24b8b70, 0xc76c51a3, 0xd192e819, 0xd6990624, 0xf40e3585, 0x106aa070, 0x19a4c116, 0x1e376c08, 0x2748774c, 0x34b0bcb5, 0x391c0cb3, 0x4ed8aa4a, 0x5b9cca4f, 0x682e6ff3, 0x748f82ee, 0x78a5636f, 0x84c87814, 0x8cc70208, 0x90befffa, 0xa4506ceb, 0xbef9a3f7, 0xc67178f2};
	printf("\"%s\r\"\n",str);
	uint64_t size = strlen(str) - 1;
	if ( (size%(512/8)) == 0 ){
		str = realloc(str,size+(512/8));
		str[size]=0x80;
		size+=(512/8);
		uint64_t help=size - 64;
//		for(int i=1; i<9; i++){
//			str[size-i]=help>>8;
//			help=help>>8;
			*((uint64_t*)(str+size-8))=(size - (512/8))*8;
			uint8_t swap;
			for(int x=1,y=8,iter=0;iter<4;iter++,x++,y--){
				swap=str[size-x];
				str[size-x]=str[size-y];
				str[size-y]=swap;
			}
//		}
	}
	else{
		if ( (size%(512/8)) > 0){
			if ( (64-(size%(512/8))) >= 9){
				uint8_t r = size % 64;
				str = realloc(str, size+((512/8) - (size%(512/8))));
				str[size] = 0x80;
				uint64_t l = size;
				size+=((512/8) - (size%(512/8)));
//				for(int i = 0; i<8;i++){
//					str[size-i]=l>>8;
//					l=l>>8;
//				}
				*((uint64_t*)(str+size-8))=l*8;
			uint8_t swap;
			for(int x=1, y=8,iter=0;iter<4;iter++,x++,y--){
				swap=str[size-x];
				str[size-x]=str[size-y];
				str[size-y]=swap;
			}
			}
			else{
				if ( (64-(size%(512/8))) < 9){
					uint64_t diff = 64 -size%(512/8);
					uint64_t l = size;
					str = realloc(str, size+diff+(512/8));
					str[size] = 0x80;
					size+=(diff+(512/8));
//					for(int i=1;i<9;i++){
//						str[size-i]=l>>8;
//						l=l>>8;
//					}
					*((uint64_t*)(str+size-8))=l*8;
			uint8_t swap;
			for(int x=1, y=8,iter=0;iter<4;iter++,x++,y--){
				swap=str[size-x];
				str[size-x]=str[size-y];
				str[size-y]=swap;
			}
				}
			}
		}
	}
	for(int i = 0; i<size; i++) printf("%x ", str[i]);
	printf("\n%lu - size\n",size);
	uint32_t w[64];
	uint32_t a,b,c,d,e,f,g,h;
	uint32_t e0,ma,t2,e1,ch,t1;
	for(int iter=0; iter<(size/64); iter++){
		uint32_t s0, s1;
		for(int i = 0; i<16; i++) {
			for(int j=0; j<4;j++){
				w[i] = (w[i]<<8)^(str[j+iter*64+i*4]);//w[i] = *((uint32_t*)(str+iter*64)+i);
			}
		}
//		for(int i = 0; i<64; i++)printf("%x ",w[i]);
		printf("\n");
//		for(int i=31;i>-1;i--)printf("%i",(rotr(0x7fd4,1)>>i)&0x1);
		printf("\nw[i] printed\n-----------\n");
		for(int l = 16; l<64; l++){
			for(int i=31;i>-1;i--)printf("%i",((w[l-15])>>i)&0x1);
			printf(" - begin\n");
			for(int i=31;i>-1;i--)printf("%i",(rotr(w[l-15],7)>>i)&0x1);
			printf("\n");
			for(int i=31;i>-1;i--)printf("%i",(rotr(w[l-15],18)>>i)&0x1);
			printf("\n");
			for(int i=31;i>-1;i--)printf("%i",((w[l-15]>>3)>>i)&0x1);
			printf("\n");
			s0 = (rotr(w[l-15],7))^(rotr(w[l-15],18))^(w[l-15]>>3);
			printf("%x = s0\n",s0);
			printf("\n");
			for(int i=31;i>-1;i--)printf("%i",((w[l-2])>>i)&0x1);
			printf(" - begin\n");
			for(int i=31;i>-1;i--)printf("%i",(rotr(w[l-2],17)>>i)&0x1);
			printf("\n");
			for(int i=31;i>-1;i--)printf("%i",(rotr(w[l-2],19)>>i)&0x1);
			printf("\n");
			for(int i=31;i>-1;i--)printf("%i",((w[l-2]>>10)>>i)&0x1);
			printf("\n");
			s1 = (rotr(w[l-2],17))^(rotr(w[l-2],19))^(w[l-10]>>10);
			printf("%x = s1\n%x = w[%i]\n%x = w[%i]\n\n",s1,w[l-16],l-16,w[l-7],l-7);
			w[l] = w[l-16] + s0 + w[l-7] + s1;
			printf("%x - result on %i\n\n\n",w[l],l);
		}
		for(int i=0; i<64;i++)printf("%x ", w[i]);
		printf("\n");
		a=h0;
		b=h1;
		c=h2;
		d=h3;
		e=h4;
		f=h5;
		g=h6;
		h=h7;
		for(int i=0; i<64;i++){
			e0 = (rotr(a,2))^(rotr(a,13))^(rotr(a,22));
			ma = (a & b)^(a & c)^(b & c);
			e1 = (rotr(e,6))^(rotr(e,11))^(rotr(e,25));
			ch = (e & f)^((~e) & g);
			t2 = e0 + ma;
			t1 = h + e1 + ch + k[i] + w[i];
			
			//printf("\n\n%x %x %x %x %x %x %x %x - %i\n",a,b,c,d,e,f,g,h,i-1);

			h = g;
			g = f;
			f = e;
			e = d + t1;
			d = c;
			c = b;
			b = a;
			a = t1 + t2;
			//printf("%x %x %x %x %x %x %x %x - %i -------- k[%i] = %x\n",a,b,c,d,e,f,g,h,i,i,k[i]);
		}
		h0+=a;
		h1+=b;
		h2+=c;
		h3+=d;
		h4+=e;
		h5+=f;
		h6+=g;
		h7+=h;
	}
	printf("%x %x %x %x %x %x %x %x\n", h0,h1,h2,h3,h4,h5,h6,h7);
}
void handler (int sig){
	printf("%s\n", strerror(sig));
	exit(-1);
}
int main(){
	signal(SIGSEGV,handler);
	uint8_t *str;
	str=(uint8_t*)malloc(sizeof(uint8_t)*128);
	if (str == NULL){
		perror("malloc");
		exit(-1);
	}
	uint32_t kuk = 0x12345678;
	for(int i = 31; i>-1;i--)printf("%i",(kuk>>i)&0x1);
	kuk=rotr(kuk,3);
	printf("\n");
	for(int i = 31; i>-1;i--)printf("%i",(kuk>>i)&0x1);
	printf("\n");
//	printf("%x == %x\n", (kuk>>23)&0xff, *((uint32_t*)(&kuk)));
	fgets(str, 128,stdin);
	sha256(str);
	return 0;
}
