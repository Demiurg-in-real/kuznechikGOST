#include<stdint.h>
#include<unistd.h>
#include<sys/types.h>
#include<sys/stat.h>
#include<fcntl.h>
#include<stdlib.h>
#include<stdio.h>
#include<string.h>
#include<stdbool.h>
#include<dirent.h>
#include<signal.h>
const static uint8_t Pi[256] = {252, 238, 221, 17, 207, 110, 49, 22, 251, 196, 250, 218, 35, 197, 4, 77, 233, 119, 240, 219, 147, 46, 153, 186, 23, 54, 241, 187, 20, 205, 95, 193, 249, 24, 101, 90, 226, 92, 239, 33, 129, 28, 60, 66, 139, 1, 142, 79, 5, 132, 2, 174, 227, 106, 143, 160, 6, 11, 237, 152, 127, 212, 211, 31, 235, 52, 44, 81, 234, 200, 72, 171, 242, 42, 104, 162, 253, 58, 206, 204, 181, 112, 14, 86, 8, 12, 118, 18, 191, 114, 19, 71, 156, 183, 93, 135, 21, 161, 150, 41, 16, 123, 154, 199, 243, 145, 120, 111, 157, 158, 178, 177, 50, 117, 25, 61, 255, 53, 138, 126, 109, 84, 198, 128, 195, 189, 13, 87, 223, 245, 36, 169, 62, 168, 67, 201, 215, 121, 214, 246, 124, 34, 185, 3, 224, 15, 236, 222, 122, 148, 176, 188, 220, 232, 40, 80, 78, 51, 10, 74, 167, 151, 96, 115, 30, 0, 98, 68, 26, 184, 56, 130, 100, 159, 38, 65, 173, 69, 70, 146, 39, 94, 85, 47, 140, 163, 165, 125, 105, 213, 149, 59, 7, 88, 179, 64, 134, 172, 29, 247, 48, 55, 107, 228, 136, 217, 231, 137, 225, 27, 131, 73, 76, 63, 248, 254, 141, 83, 170, 144, 202, 216, 133, 97, 32, 113, 103, 164, 45, 43, 9, 91, 203, 155, 37, 208, 190, 229, 108, 82, 89, 166, 116, 210, 230, 244, 180, 192, 209, 102, 175, 194, 57, 75, 99, 182};

const static uint8_t inPi[256] = {165, 45, 50, 143, 14, 48, 56, 192, 84, 230, 158, 57, 85, 126, 82, 145, 100, 3, 87, 90, 28, 96, 7, 24, 33, 114, 168, 209, 41, 198, 164, 63, 224, 39, 141, 12, 130, 234, 174, 180, 154, 99, 73, 229, 66, 228, 21, 183, 200, 6, 112, 157, 65, 117, 25, 201, 170, 252, 77, 191, 42, 115, 132, 213, 195, 175, 43, 134, 167, 177, 178, 91, 70, 211, 159, 253, 212, 15, 156, 47, 155, 67, 239, 217, 121, 182, 83, 127, 193, 240, 35, 231, 37, 94, 181, 30, 162, 223, 166, 254, 172, 34, 249, 226, 74, 188, 53, 202, 238, 120, 5, 107, 81, 225, 89, 163, 242, 113, 86, 17, 106, 137, 148, 101, 140, 187, 119, 60, 123, 40, 171, 210, 49, 222, 196, 95, 204, 207, 118, 44, 184, 216, 46, 54, 219, 105, 179, 20, 149, 190, 98, 161, 59, 22, 102, 233, 92, 108, 109, 173, 55, 97, 75, 185, 227, 186, 241, 160, 133, 131, 218, 71, 197, 176, 51, 250, 150, 111, 110, 194, 246, 80, 255, 93, 169, 142, 23, 27, 151, 125, 236, 88, 247, 31, 251, 124, 9, 13, 122, 103, 69, 135, 220, 232, 79, 29, 78, 4, 235, 248, 243, 62, 61, 189, 138, 136, 221, 205, 11, 19, 152, 2, 147, 128, 144, 208, 36, 52, 203, 237, 244, 206, 153, 16, 68, 64, 146, 58, 1, 38, 18, 26, 72, 104, 245, 129, 139, 199, 214, 32, 10, 8, 0, 76, 215, 116};

static uint8_t matrix[16][16]={
	{148,1,0,0,0,0,0,0,0,0,0,0,0,0,0,0},
	{32,0,1,0,0,0,0,0,0,0,0,0,0,0,0,0},
	{133,0,0,1,0,0,0,0,0,0,0,0,0,0,0,0},
	{16,0,0,0,1,0,0,0,0,0,0,0,0,0,0,0},
	{194,0,0,0,0,1,0,0,0,0,0,0,0,0,0,0},
	{192,0,0,0,0,0,1,0,0,0,0,0,0,0,0,0},
	{1,0,0,0,0,0,0,1,0,0,0,0,0,0,0,0},
	{251,0,0,0,0,0,0,0,1,0,0,0,0,0,0,0},
	{1,0,0,0,0,0,0,0,0,1,0,0,0,0,0,0},
	{192,0,0,0,0,0,0,0,0,0,1,0,0,0,0,0},
	{194,0,0,0,0,0,0,0,0,0,0,1,0,0,0,0},
	{16,0,0,0,0,0,0,0,0,0,0,0,1,0,0,0},
	{133,0,0,0,0,0,0,0,0,0,0,0,0,1,0,0},
	{32,0,0,0,0,0,0,0,0,0,0,0,0,0,1,0},
	{148,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
	{1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0},
};

static uint8_t inmatrix[16][16]={
	{0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
	{1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,148},
	{0,1,0,0,0,0,0,0,0,0,0,0,0,0,0,32},
	{0,0,1,0,0,0,0,0,0,0,0,0,0,0,0,133},
	{0,0,0,1,0,0,0,0,0,0,0,0,0,0,0,16},
	{0,0,0,0,1,0,0,0,0,0,0,0,0,0,0,194},
	{0,0,0,0,0,1,0,0,0,0,0,0,0,0,0,192},
	{0,0,0,0,0,0,1,0,0,0,0,0,0,0,0,1},
	{0,0,0,0,0,0,0,1,0,0,0,0,0,0,0,251},
	{0,0,0,0,0,0,0,0,1,0,0,0,0,0,0,1},
	{0,0,0,0,0,0,0,0,0,1,0,0,0,0,0,192},
	{0,0,0,0,0,0,0,0,0,0,1,0,0,0,0,194},
	{0,0,0,0,0,0,0,0,0,0,0,1,0,0,0,16},
	{0,0,0,0,0,0,0,0,0,0,0,0,1,0,0,133},
	{0,0,0,0,0,0,0,0,0,0,0,0,0,1,0,32},
	{0,0,0,0,0,0,0,0,0,0,0,0,0,0,1,148}
};



const static unsigned short int polynom=451;

static uint8_t polinMultiple[256][256];


void generateTable()
{

	uint32_t smth=0x0, fir,sec;
	uint8_t res=0x0;
	for(int x = 0; x<256;x++)
	{
		for(int y=0; y<256;y++)
		{
			for(int i = 7; i!=(-1); i--)
			{
				fir=x;
				sec=y;
				if ( ((fir>>i)&0x1) == 0x1)
				{
					smth^=(sec<<(i));
				}
			}
			int ord=0;
			for (int i = 15; i!=(-1);i--)
			{
				if( ((smth>>i)&0x1) == 0x1)
				{
					ord = i;
					break;
				}
			}
			for(int i=ord;i!=(-1); i--)
			{
				smth^=(polynom<<(ord-8));
				for(int j=i; j!=(-1);j--)
				{
					if( ((smth>>j)&0x1) == 0x1)
					{
						ord = j;
						break;
					}
				}
				if (ord <= 7)
				{
					polinMultiple[x][y] = smth;
					smth = 0x0;
					break;
				}
			}
		}
	}
}

static inline void copy(uint8_t **res,uint8_t matr[16][16])
{
	for (uint8_t i=0;i<16;i++)
	{
		for (uint8_t j=0;j<16;j++)
		{
			res[i][j]=matr[i][j];
		}
	}
};
static void generateMatrix(uint8_t matr[16][16])
{
	uint8_t smezh;
	uint8_t **exponMatrix;
	exponMatrix=(uint8_t**)malloc(16*sizeof(uint8_t*));
	for (uint8_t i=0;i<16;i++)
	{
		exponMatrix[i] = (uint8_t*)malloc(16);
	}
	for(uint8_t i=0; i<4;i++)
	{
		copy(exponMatrix,matr);
		for (uint8_t l=0;l<16;l++)
		{
			for (uint8_t j=0;j<16;j++)
			{
				smezh=0x0;
				for(uint8_t r=0;r<16;r++)
				{
					smezh^=polinMultiple[exponMatrix[l][r]][exponMatrix[r][j]];
				}
				matr[l][j]=smezh;
			}
		}
	}
	for(uint8_t i=0; i<16;i++)
	{
		free(exponMatrix[i]);
	}
	free(exponMatrix);
	exponMatrix = NULL;
};
struct lsx{
	uint8_t *newVector;
	uint8_t *swap_key;
	uint8_t vector_for_key[16];
} LSX;
static void iniLSX()
{
	LSX.newVector = (uint8_t*)malloc(16);
	LSX.swap_key = (uint8_t*)malloc(16);
	for(int i=0;i<16;i++) 
	{
		LSX.newVector[i]=0x0;
		LSX.swap_key[i]=0x0;
	}
};
static void deiniLSX()
{
	free(LSX.newVector);
	LSX.newVector = NULL;
	free(LSX.swap_key);
	LSX.swap_key = NULL;
}
void reset(uint8_t *block)
{
	for(uint8_t i=0; i<16; i++)
	{
		block[i]=LSX.newVector[i];
		LSX.newVector[i]=0x0;
	}
}
void X(uint8_t *key, uint8_t *block, uint8_t order)
{ 
	for (uint8_t i=0; i<16; i++)
	{
		block[i]^=key[order*16+i];
	}
}
void S(uint8_t *block,const uint8_t pi[256])
{
	for(uint8_t i=0; i<16;i++)
	{
		block[i]=pi[block[i]];
	}
}

void L(uint8_t *block,uint8_t matr[16][16])
{
	for (uint8_t j=0; j<16;j++)
	{
		for(uint8_t k=0; k<16;k++)
		{
			LSX.newVector[j]^=polinMultiple[matr[k][j]][block[k]];
		}
	}
	reset(block);
}
void swap(uint8_t *key,uint8_t *second_key)
{
	for(uint8_t oran=0;oran<16;oran++)
	{
		key[oran+16]=second_key[oran];
	}
}
void generate_key(uint8_t *key,uint8_t order,uint8_t matr[16][16])
{
	for(uint8_t i=order*8; i<((order+1)*8);i++)
	{
		for(int j=0; j<16;j++) 
		{
			LSX.swap_key[j]=key[j];
		}
		LSX.vector_for_key[15]=i+1;
		uint8_t ord=0;
		L(LSX.vector_for_key,matr);
		X(LSX.vector_for_key,key,ord);
		S(key,Pi);
		L(key,matr);
		for(uint8_t j=0; j<16;j++)
		{
			key[j]^=key[16+j];
		}
		swap(key,LSX.swap_key);
		for (int l=0;l<16;l++) 
		{
			LSX.vector_for_key[l]=0x0;
		}
	}
}
void eninit()
{
	generateMatrix(matrix);
}

void  deinit()
{
	generateMatrix(matrix);
	generateMatrix(inmatrix);
}

void encrypt(uint8_t *block, uint8_t *key)
{
	iniLSX();
	for(uint8_t i=0; i<5 ; i++)
	{
		for(uint8_t j=0; j<2; j++)
		{
			X(key,block,j);
			if( (i==4) && (j==1)) break;
			S(block,Pi);
			L(block,matrix);
		}
		generate_key(key,i,matrix);
	}
	deiniLSX();
}
void decrypt(uint8_t *block,uint8_t *key)
{
	iniLSX();
	uint8_t *cop;
	cop=(uint8_t*)malloc(sizeof(uint8_t)*16);
	uint8_t bad;
	for(int8_t i=4;i>-1;i--)
	{
		for(int ref=0;ref<32;ref++) 
		{
			cop[ref]=key[ref];
		}
		if (i != 0)
		{
			bad=i;
			for(uint8_t l=0;l<bad;l++)
			{
				generate_key(cop,l,matrix);
			}
		}
		for(int8_t j=1;j>-1;j--)
		{
			bad=j;
			if (i == 4 && j == 1)
			{
				X(cop,block,bad);
				continue;
			}
			L(block,inmatrix);
			S(block,inPi);
			X(cop,block,bad);
		}
	}
	free(cop);
	cop=NULL;
}

void encr(int fd,int sig,uint8_t *key)
{		
	uint8_t *copykey;
	uint8_t *block;
	uint8_t synk[32];
	uint8_t blok[16];
	copykey=(uint8_t*)malloc(32);
	block=(uint8_t*)malloc(16);
	int kuk;
	uint64_t size=0,end;
	struct stat st;
	fstat(fd,&st);
	if(sig == 1) 
	{
		kuk=open("/dev/urandom", O_RDONLY);
		read(kuk,synk,32);
		printf("\tReading synk...\n\t ");
		for(int i=0;i<32;i++)printf("%2x ", synk[i]);
		printf("\n");
		close(kuk);
	}
	if(sig == 2)
	{
		lseek(fd,-32,SEEK_END);
		read(fd,synk,32);
		printf("\tReading synk..\n\t ");
		for(int i=0; i<32;i++)printf("%2x ",synk[i]);
		printf("\n");
		st.st_size-=32;
		ftruncate(fd,st.st_size);
		lseek(fd,0,SEEK_SET);
	}
	if(sig == 3)
	{
		kuk = open("posil.bin",O_RDONLY);
		read(kuk,synk,32);
		close(kuk);
	}
	printf("\n\tBegin the process of ");
	if(sig == 1)printf("encryption\n");
	if(sig == 2)printf("decryption\n");

	uint8_t *csynk;
	csynk=(uint8_t*)malloc(32);
	for(int i=0;i<32;i++)csynk[i]=synk[i];
	if((st.st_size%16) !=0) end=((st.st_size+st.st_size%16)/16);
	else end=st.st_size/16;
	eninit();
	for(uint64_t i=0;i<end;i++)
	{
		read(fd,block,16);
		lseek(fd,-16,SEEK_CUR);
		for(int i=0;i<32;i++)
		{
			copykey[i]=key[i];
		}
		encrypt((synk+(i%2)*16),copykey);
		for(uint8_t kl=0;kl<16;kl++)
		{
			if(size == st.st_size) return;
			*(block+kl)^=synk[kl+(i%2)*16];
			size++;
			write(fd,(block+kl),1);
		}
	}
	if(sig == 1)
	{
		lseek(fd,0,SEEK_END);
		write(fd,csynk,32);
	}
	free(block);
	free(copykey);
	printf("\tThe end of process\n");
}

uint32_t  rotr(uint32_t cn,int how){
	return (cn>>how) | (cn<<(32-how));
}

void sha256(uint8_t *str,uint8_t *key)
{
	uint32_t h0 = 0x6A09E667;
	uint32_t h1 = 0xBB67AE85;
	uint32_t h2 = 0x3C6EF372;
	uint32_t h3 = 0xA54FF53A;
	uint32_t h4 = 0x510E527F;
	uint32_t h5 = 0x9B05688C;
	uint32_t h6 = 0x1F83D9AB;
	uint32_t h7 = 0x5BE0CD19;
	uint32_t k[64]={0x428a2f98, 0x71374491, 0xb5c0fbcf, 0xe9b5dba5, 0x3956c25b, 0x59f111f1, 0x923f82a4, 0xab1c5ed5, 0xd807aa98, 0x12835b01, 0x243185be, 0x550c7dc3, 0x72be5d74, 0x80deb1fe, 0x9bdc06a7, 0xc19bf174, 0xe49b69c1, 0xefbe4786, 0x0fc19dc6, 0x240ca1cc, 0x2de92c6f, 0x4a7484aa, 0x5cb0a9dc, 0x76f988da, 0x983e5152, 0xa831c66d, 0xb00327c8, 0xbf597fc7, 0xc6e00bf3, 0xd5a79147, 0x06ca6351, 0x14292967, 0x27b70a85, 0x2e1b2138, 0x4d2c6dfc, 0x53380d13, 0x650a7354, 0x766a0abb, 0x81c2c92e, 0x92722c85, 0xa2bfe8a1, 0xa81a664b, 0xc24b8b70, 0xc76c51a3, 0xd192e819, 0xd6990624, 0xf40e3585, 0x106aa070, 0x19a4c116, 0x1e376c08, 0x2748774c, 0x34b0bcb5, 0x391c0cb3, 0x4ed8aa4a, 0x5b9cca4f, 0x682e6ff3, 0x748f82ee, 0x78a5636f, 0x84c87814, 0x8cc70208, 0x90befffa, 0xa4506ceb, 0xbef9a3f7, 0xc67178f2};
	uint64_t size = strlen(str) - 1;
	if ( (size%(512/8)) == 0 )
	{
		str = realloc(str,size+(512/8));
		str[size]=0x80;
		size+=(512/8);
		uint64_t help=size - 64;
		*((uint64_t*)(str+size-8))=(size - (512/8))*8;
		uint8_t swap;
		
		swap = str[size-1];
		str[size-1] = str[size-8];
		str[size-8] = swap;

		swap = str[size-2];
		str[size-2] = str[size-7];
		str[size-7] = swap;

		swap = str[size-3];
		str[size-3] = str[size-6];
		str[size-6] = swap;

		swap = str[size-4];
		str[size-4] = str[size-5];
		str[size-5] = swap;
	}
	else{
		if ( (size%(512/8)) > 0)
		{
			if ( (64-(size%(512/8))) >= 9)
			{
				uint8_t r = size % 64;
				str = realloc(str, size+((512/8) - (size%(512/8))));
				str[size] = 0x80;
				uint64_t l = size;
				size+=((512/8) - (size%(512/8)));
				*((uint64_t*)(str+size-8))=l*8;
				uint8_t swap;

				swap = str[size-1];
				str[size-1] = str[size-8];
				str[size-8] = swap;

				swap = str[size-2];
				str[size-2] = str[size-7];
				str[size-7] = swap;
				
				swap = str[size-3];
				str[size-3] = str[size-6];
				str[size-6] = swap;
				
				swap = str[size-4];
				str[size-4] = str[size-5];
				str[size-5] = swap;
			}
			else{
				if ( (64-(size%(512/8))) < 9)
				{
					uint64_t diff = 64 -size%(512/8);
					uint64_t l = size;
					str = realloc(str, size+diff+(512/8));
					str[size] = 0x80;
					size+=(diff+(512/8));
					*((uint64_t*)(str+size-8))=l*8;
					uint8_t swap;
					
					swap = str[size-1];
					str[size-1] = str[size-8];
					str[size-8] = swap;

					swap = str[size-2];
					str[size-2] = str[size-7];
					str[size-7] = swap;

					swap = str[size-3];
					str[size-3] = str[size-6];
					str[size-6] = swap;

					swap = str[size-4];
					str[size-4] = str[size-5];
					str[size-5] = swap;
				}
			}
		}
	}
	uint32_t w[64];
	uint32_t a,b,c,d,e,f,g,h;
	uint32_t e0,ma,t2,e1,ch,t1;
	for(int iter=0; iter<(size/64); iter++){
		uint32_t s0, s1, kuk;
		for(int i = 0; i<16; i++) {
			for(int j=0; j<4;j++){
				w[i] = (w[i]<<8)^(str[j+iter*64+i*4]);
			}
		}
		for(int l = 16; l<64; l++){
			s0 = (rotr(w[l-15],7))^(rotr(w[l-15],18))^(w[l-15]>>3);
			s1 = (rotr(w[l-2],17))^(rotr(w[l-2],19))^(w[l-2]>>10);
			w[l] = w[l-16] + s0 + w[l-7] + s1;
		}
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
			
			h = g;
			g = f;
			f = e;
			e = d + t1;
			d = c;
			c = b;
			b = a;
			a = t1 + t2;
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
	uint32_t H[8]={h0,h1,h2,h3,h4,h5,h6,h7};
	int iter=0;
	for(int i = 0; i < 8; i++){
		for(int j = 3; j > -1; j--){
			key[iter]=((H[i]>>(j*8))&0xff);
			iter++;
		}
	}
}
void handler (int sig){
	printf("%s\n", strerror(sig));
	exit(-1);
}
void smtr (int sig){
	printf("Why are you killing me?(\nThe process of encrypting/decrypting are damaged. Some Files will be lost.\n");
	exit(-1);
}

int main(int argc,char* argv[]){
	generateTable();
	
	signal(SIGTERM, smtr);
	signal(SIGSEGV, handler);

	uint8_t *pass;
	uint8_t *key;
	pass = (uint8_t*)malloc(sizeof(uint8_t)*256);
	key = (uint8_t*)malloc(sizeof(uint8_t)*32);
	printf("Please, write a password.\n*NOTE* : no longer than 256 characters\n\n");
	fgets(pass,256-1,stdin);	
	sha256(pass,key);
	printf("\nThe key: ");
	for(int i = 0 ; i<32; i++)printf("%x ", key[i]);
	free(pass);
	
	printf("\nInitializating table...\t");
	generateTable();
	printf("Ready.\n");

	int sig = atoi(argv[1]);	
	int kak;
	int vnutri, kolvo=1,end=0;

	char *exep1=".";
	char *exep2="..";

	uint8_t *dirname;

	uint8_t  **dirnamebuf;
	dirnamebuf=malloc(kolvo*sizeof(char*));
	dirnamebuf[0]=malloc(1);
	dirnamebuf[0]=argv[2];


	struct dirent **scan;
	struct stat st;
	printf("Startin process.\n");
	do{
		vnutri=scandir(dirnamebuf[end],&scan,NULL,alphasort);
		printf("In directory: %s\n", dirnamebuf[end]);
		while(vnutri--){
			if ( strcmp(scan[vnutri]->d_name,exep1) != 0 && strcmp(scan[vnutri]->d_name,exep2) != 0 && scan[vnutri]->d_type == DT_DIR){
				kolvo++;
				dirnamebuf=realloc(dirnamebuf, kolvo*sizeof(char*));
				dirnamebuf[kolvo-1]=malloc(sizeof(scan[vnutri]->d_name)+sizeof(dirnamebuf[end]));
				snprintf(dirnamebuf[kolvo-1],sizeof(scan[vnutri]->d_name)+sizeof(dirnamebuf[end])+1,"%s/%s",dirnamebuf[end],scan[vnutri]->d_name);
			}
			else{
				dirname=malloc(sizeof(dirnamebuf[end])+sizeof(scan[vnutri]->d_name));
				snprintf(dirname,256, "%s/%s", dirnamebuf[end],scan[vnutri]->d_name);
				if(scan[vnutri]->d_type==DT_REG)
				{
					kak=open(dirname,O_RDWR);
					if(kak == -1){
						perror("open");
						continue;
					}
					printf("\t-Target = %s\n", dirname);
					encr(kak,sig,key);
					if(close(kak) != 0){
						perror("close");
						exit(-1);
					}
				}
				free(dirname);
			}
		}
		end++;
	}
	while(end!=kolvo);

	return 0;
}
