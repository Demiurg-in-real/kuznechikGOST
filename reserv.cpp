#include<iostream>
#include<sys/types.h>

const static uint8_t Pi[256] = {252, 238, 221, 17, 207, 110, 49, 22, 251, 196, 250, 218, 35, 197, 4, 77, 233, 119, 240, 219, 147, 46, 153, 186, 23, 54, 241, 187, 20, 205, 95, 193, 249, 24, 101, 90, 226, 92, 239, 33, 129, 28, 60, 66, 139, 1, 142, 79, 5, 132, 2, 174, 227, 106, 143, 160, 6, 11, 237, 152, 127, 212, 211, 31, 235, 52, 44, 81, 234, 200, 72, 171, 242, 42, 104, 162, 253, 58, 206, 204, 181, 112, 14, 86, 8, 12, 118, 18, 191, 114, 19, 71, 156, 183, 93, 135, 21, 161, 150, 41, 16, 123, 154, 199, 243, 145, 120, 111, 157, 158, 178, 177, 50, 117, 25, 61, 255, 53, 138, 126, 109, 84, 198, 128, 195, 189, 13, 87, 223, 245, 36, 169, 62, 168, 67, 201, 215, 121, 214, 246, 124, 34, 185, 3, 224, 15, 236, 222, 122, 148, 176, 188, 220, 232, 40, 80, 78, 51, 10, 74, 167, 151, 96, 115, 30, 0, 98, 68, 26, 184, 56, 130, 100, 159, 38, 65, 173, 69, 70, 146, 39, 94, 85, 47, 140, 163, 165, 125, 105, 213, 149, 59, 7, 88, 179, 64, 134, 172, 29, 247, 48, 55, 107, 228, 136, 217, 231, 137, 225, 27, 131, 73, 76, 63, 248, 254, 141, 83, 170, 144, 202, 216, 133, 97, 32, 113, 103, 164, 45, 43, 9, 91, 203, 155, 37, 208, 190, 229, 108, 82, 89, 166, 116, 210, 230, 244, 180, 192, 209, 102, 175, 194, 57, 75, 99, 182};

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

const static unsigned short int polynom=451;

static uint8_t polinMultiple[256][256];

//const uint8_t vector_for_key[16]={0x1, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0};


namespace blockKuz{
//---------------------------------------------------------------------------------------------------------------------------------------------------------------------------
//Работает верно, одобрено

	void generateTable(){
		unsigned short int promez1, promez2, smeshenie;
		bool check;
		//Пробегаем по всем возможным вариантам перемножения полиномов
		for(short int i=1;i<256;i++){
			for(short int j=1;j<256;j++){
				promez1=0x0;
				promez2=0x0;
				smeshenie=0x1;	
				check=false;
				//умножение полиномов
			
				for (uint8_t l=0;l<8;l++){
					if( ((j>>l)&0x1) == 0x1){
						promez1^=(i<<l);
					}
				}

				//нахождение максимальной степени
					
				for (uint8_t l=15;l>6;l--){
					if( ((promez1>>l)&0x1) == 0x1 && (l > 7)){
						smeshenie=(smeshenie<<(l-8));
						break;
					}
					if(l==7){
						polinMultiple[i][j]=promez1;
						check = true;
					}
				}
				if(check) continue;

				//дальше надо реализовать второй блок с подбором целого для вычисления коэффициента (читать в тетради)

				for(;;){
					for (uint8_t l=0;l<8;l++){
						if((smeshenie>>l)&0x1){
							promez2^=(polynom<<l);
						}
					}

					promez2^=promez1;

					uint8_t c=15;
					while(c>6){
						if( ((promez2>>c)&0x1) == 0x1 && (c>7)){
							smeshenie++;
							promez2=0x0;
							break;
						}
						if(c <= 7){
							polinMultiple[i][j] = promez2;
							check=true;
							break;
						}
						c--;
					}
					if (check) break;
				}
			}
		}
	}
//-----------------------------------------------------------------------------------------------------------------------------------------------------------------------
//Работает верно, одобрено
	static inline void copy(uint8_t **res){
		for (uint8_t i=0;i<16;i++){
			for (uint8_t j=0;j<16;j++){
				res[i][j]=matrix[i][j];
			}
		}
	};
//------------------------------------------------------------------------------------------------------------------------------------------------------------------------
//Работает верно, одобрено
	static void generateMatrix(){
		uint8_t smezh;
		uint8_t **exponMatrix;
		exponMatrix=new uint8_t*[16];
		for (uint8_t i=0;i<16;i++){
			exponMatrix[i] = new uint8_t[16];
		}
		for(uint8_t i=0; i<4;i++){
			copy(exponMatrix);
			for (uint8_t l=0;l<16;l++){
				for (uint8_t j=0;j<16;j++){
					smezh=0x0;
					for(uint8_t r=0;r<16;r++){
						smezh^=polinMultiple[exponMatrix[l][r]][exponMatrix[r][j]];
					}
					matrix[l][j]=smezh;
				}
			}
		}
		//очищаем память для вспомогательного массива
		for(uint8_t i=0; i<16;i++){
			delete [] exponMatrix[i];
		}
		delete [] exponMatrix;
	};
//------------------------------------------------------------------------------------------------------------------------------------------------------------------------
	class LSX{
		public:
			void X (uint8_t *key, uint8_t *block,uint8_t &order);
			void S (uint8_t *block);
			virtual void L (uint8_t *block);
			void generate_key(uint8_t *key,uint8_t &order);
			LSX();
			~LSX();
		protected:
			uint8_t *newVector;
			uint8_t *swap_key;
			uint8_t vector_for_key[16]={0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0};
			void reset(uint8_t *block);
			void inline swap(uint8_t *key, uint8_t *second_key);
	};

	LSX::LSX(){
		generateTable();
		generateMatrix();
		newVector = new uint8_t [16];
		swap_key = new uint8_t [16];
		for(int i=0;i<16;i++) {
			newVector[i]=0x0;
			swap_key[i]=0x0;
		}
	};

	LSX::~LSX(){
		delete [] newVector;
		newVector = NULL;
		delete [] swap_key;
		swap_key = NULL;
	};
	
	void LSX::reset(uint8_t *block){
		for(uint8_t i=0; i<16; i++){
			block[i]=newVector[i];
			newVector[i]=0x0;
		}
	}
//---------------------------------------------------------------------------------------------------------------------------------------------------------------
// Проверенная функция
	void LSX::X(uint8_t *key, uint8_t *block, uint8_t &order){ // order  - для определния того, какой по счёту ключ используется
		for (uint8_t i=0; i<16; i++){
			block[i]^=key[order*16+i];
		}
	}

//---------------------------------------------------------------------------------------------------------------------------------------------------------------
//проверенная функция.

	void LSX::S(uint8_t *block){
		for(uint8_t i=0; i<16;i++){
			block[i]=Pi[block[i]];
		}
	}

//----------------------------------------------------------------------------------------------------------------------------------------------------------------
//проверенная функция.

	void LSX::L(uint8_t *block){
		for (uint8_t j=0; j<16;j++){
			for(uint8_t k=0; k<16;k++){
				newVector[j]^=polinMultiple[matrix[k][j]][block[k]];
			}
		}
		reset(block);
	}
//---------------------------------------------------------------------------------------------------------------------------------------------------------------
//Проверенная функция.
	void inline LSX::swap(uint8_t *key,uint8_t *second_key){
		for(uint8_t oran=0;oran<16;oran++){
			key[oran+16]=second_key[oran];
		}
	}
//-------------------------------------------------------------------------------------------------------------------------------------------------------------
//Проверенная функция.
	void LSX::generate_key(uint8_t *key,uint8_t &order){
		for(uint8_t i=order*8; i<((order+1)*8);i++){
			for(int j=0; j<16;j++) {
				swap_key[j]=key[j];
			}
			vector_for_key[15]=i+1;
			uint8_t ord=0;
			L(vector_for_key);
			X(vector_for_key,key,ord);
			S(key);
			L(key);
			for(uint8_t j=0; j<16;j++){
				key[j]^=key[16+j];
			}
			swap(key,swap_key);
			for (int l=0;l<16;l++) vector_for_key[l]=0x0;
		}
	}
//-------------------------------------------------------------------------------------------------------------------------------------------------------------
//Проверенная функция.			
		
	class EncDec{
		public:
			void encrypt(uint8_t *block, uint8_t *key);
	};

//-------------------------------------------------------------------------------------------------------------------------------------------------------------
//Проверено.ё
	void EncDec::encrypt(uint8_t *block, uint8_t *key){
		LSX fight;
		uint8_t promez=0;
		for(uint8_t i=0; i<5 ; i++){
			for(uint8_t j=0; j<2; j++){
				fight.X(key,block,j);
				if( (i==4) && (j==1)) break;
				fight.S(block);
				fight.L(block);
			}
			fight.generate_key(key,i);
		}
	}
//_____________________________________________________________________________________________________________________________________________________________
};
//-------------------------------------------------------------------------------------------------------------------------------------------------------------
int main(){
	FILE *rea=fopen("begin.bin","rb");
	FILE *wr=fopen("result.bin","wb");
	if (rea == NULL || wr == NULL) perror("fopen");
	uint8_t *block;
	uint8_t *key;
	key = new uint8_t [32];
	block = new uint8_t [16];
	fread(block,sizeof(uint8_t),16,rea);
	fread(key,sizeof(uint8_t),32,rea);
	uint8_t *reset;
	reset = new uint8_t [32];
	for (int i=0;i<32;i++) reset[i]=key[i];
	blockKuz::EncDec tir;
	tir.encrypt(block,key);
	fwrite(block,sizeof(uint8_t),16,wr);
	fwrite(reset,sizeof(uint8_t),32,wr);
	fclose(wr);
	fclose(rea);
	delete [] block;
	block = NULL;
	delete [] key;
	key = NULL;
	delete [] reset;
	reset = NULL;
	return 0;

}
