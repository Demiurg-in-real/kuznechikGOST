#include<stdio.h>
#include<stdlib.h>
#include<stdint.h>
#include<string.h>
#include<error.h>
#include<signal.h>
#include<iostream>
#include<vector>
uint32_t  rotr(uint32_t cn,int how){
	return ((cn>>how)&0xffffffff)^((cn<<(32-how))&0xffffffff);
}

void sha256(uint8_t *res, std::string stri){
	uint32_t H[8]={0x6A09E667, 0xBB67AE85, 0x3C6EF372, 0xA54FF53A, 0x510E527F, 0x9B05688C, 0x1F83D9AB, 0x5BE0CD19};
	uint32_t k[64]={
		0x428A2F98, 0x71374491, 0xB5C0FBCF, 0xE9B5DBA5, 0x3956C25B, 0x59F111F1, 0x923F82A4, 0xAB1C5ED5,
		0xD807AA98, 0x12835B01, 0x243185BE, 0x550C7DC3, 0x72BE5D74, 0x80DEB1FE, 0x9BDC06A7, 0xC19BF174,
		0xE49B69C1, 0xEFBE4786, 0x0FC19DC6, 0x240CA1CC, 0x2DE92C6F, 0x4A7484AA, 0x5CB0A9DC, 0x76F988DA,
		0x983E5152, 0xA831C66D, 0xB00327C8, 0xBF597FC7, 0xC6E00BF3, 0xD5A79147, 0x06CA6351, 0x14292967,
		0x27B70A85, 0x2E1B2138, 0x4D2C6DFC, 0x53380D13, 0x650A7354, 0x766A0ABB, 0x81C2C92E, 0x92722C85,
		0xA2BFE8A1, 0xA81A664B, 0xC24B8B70, 0xC76C51A3, 0xD192E819, 0xD6990624, 0xF40E3585, 0x106AA070,
		0x19A4C116, 0x1E376C08, 0x2748774C, 0x34B0BCB5, 0x391C0CB3, 0x4ED8AA4A, 0x5B9CCA4F, 0x682E6FF3,
		0x748F82EE, 0x78A5636F, 0x84C87814, 0x8CC70208, 0x90BEFFFA, 0xA4506CEB, 0xBEF9A3F7, 0xC67178F2
	};
	uint64_t size = stri.size();
	std::vector<uint8_t> str(size);
	for(uint32_t i = 0; i<size; i++)str[i]=*(stri.data()+i);
	if ( (64-(size%(512/8))) >= 9){
		uint8_t r = size % 64;
		str.resize(size+((512/8) - (size%(512/8))));
		str[size] = 0x80;
		uint64_t l = size;
		size+=((512/8) - (size%(512/8)));
		*((uint64_t*)(str.data()+size-8))=l*8;
	}
	else{
		if ( (64-(size%(512/8))) < 9){
			uint64_t diff = 64 -size%(512/8);
			uint64_t l = size;
			str.resize( size+diff+(512/8));
			str[size] = 0x80;
			size+=(diff+(512/8));
			*((uint64_t*)(str.data()+size-8))=l*8;
		}
	}
	uint8_t swap;
	for(int x=1, y=8,iter=0;iter<4;iter++,x++,y--){
		swap=str[size-x];
		str[size-x]=str[size-y];
		str[size-y]=swap;
	}
	uint32_t w[64];
	uint32_t a,b,c,d,e,f,g,h;
	uint32_t e0,ma,t2,e1,ch,t1;
	for(int iter=0; iter<(size/64); iter++){
		uint32_t s0, s1, kuk;
		a=H[0];
		b=H[1];
		c=H[2];
		d=H[3];
		e=H[4];
		f=H[5];
		g=H[6];
		h=H[7];
		for(int i=0; i<64;i++){
			if( i<16){
				for(int j=0; j<4;j++){
					w[i] = (w[i]<<8)^(str[j+iter*64+i*4]);
				}
			}
			else{
				s0 = (rotr(w[i-15],7))^(rotr(w[i-15],18))^(w[i-15]>>3);
				s1 = (rotr(w[i-2],17))^(rotr(w[i-2],19))^(w[i-2]>>10);
				w[i] = w[i-16] + s0 + w[i-7] + s1;
			}
			e0 = (rotr(a,2))^(rotr(a,13))^(rotr(a,22));
			ma = (a & b)^(a & c)^(b & c);
			e1 = (rotr(e,6))^(rotr(e,11))^(rotr(e,25));
			ch = (e & f)^((~e) & g);
			t2 = e0 + ma;
			t1 = h + e1 + ch + k[i] + w[i];
			
			h = g;
			g = f;
			f = e;
			e = d + t1;
			d = c;
			c = b;
			b = a;
			a = t1 + t2;
		}
		H[0]+=a;
		H[1]+=b;
		H[2]+=c;
		H[3]+=d;
		H[4]+=e;
		H[5]+=f;
		H[6]+=g;
		H[7]+=h;
	}
	printf("%x %x %x %x %x %x %x %x\n", H[0],H[1],H[2],H[3],H[4],H[5],H[6],H[7]);
	uint8_t counter = 0;
	for(uint8_t i=0; i<8; i++){
		for(int8_t j=3; j != (-1); j--){
			res[counter]=(H[i]>>(j*8))&0xff;
			counter++;
		}
	}
}
void handler (int sig){
	printf("%s\n", strerror(sig));
	exit(-1);
}
int main(){
	signal(SIGABRT,handler);
	uint8_t *res;
	res = new uint8_t[32];
	std::string str;
	std::getline(std::cin,str);
	sha256(res,str);
	for(int i = 0; i<32; i++)printf("%x ", *(res+i));//*(reinterpret_cast<uint8_t*>(res)+i));
	return 0;
}
