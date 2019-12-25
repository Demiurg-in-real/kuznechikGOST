#include<iostream>
#include<sys/types.h>
#include<stdlib.h>//-?
#include<sys/stat.h>//for fstat
#include<fcntl.h>//for fd=open
#include<unistd.h>//for close(fd)
#include<signal.h>//for signals)
#include<string.h>//for strsignal
#include<sys/mman.h>//for mmap and munmap
#include<filesystem>//for fs traversal
#include<sha.h>
const static uint8_t Pi[256] = {252, 238, 221, 17, 207, 110, 49, 22, 251, 196, 250, 218, 35, 197, 4, 77, 233, 119, 240, 219, 147, 46, 153, 186, 23, 54, 241, 187, 20, 205, 95, 193, 249, 24, 101, 90, 226, 92, 239, 33, 129, 28, 60, 66, 139, 1, 142, 79, 5, 132, 2, 174, 227, 106, 143, 160, 6, 11, 237, 152, 127, 212, 211, 31, 235, 52, 44, 81, 234, 200, 72, 171, 242, 42, 104, 162, 253, 58, 206, 204, 181, 112, 14, 86, 8, 12, 118, 18, 191, 114, 19, 71, 156, 183, 93, 135, 21, 161, 150, 41, 16, 123, 154, 199, 243, 145, 120, 111, 157, 158, 178, 177, 50, 117, 25, 61, 255, 53, 138, 126, 109, 84, 198, 128, 195, 189, 13, 87, 223, 245, 36, 169, 62, 168, 67, 201, 215, 121, 214, 246, 124, 34, 185, 3, 224, 15, 236, 222, 122, 148, 176, 188, 220, 232, 40, 80, 78, 51, 10, 74, 167, 151, 96, 115, 30, 0, 98, 68, 26, 184, 56, 130, 100, 159, 38, 65, 173, 69, 70, 146, 39, 94, 85, 47, 140, 163, 165, 125, 105, 213, 149, 59, 7, 88, 179, 64, 134, 172, 29, 247, 48, 55, 107, 228, 136, 217, 231, 137, 225, 27, 131, 73, 76, 63, 248, 254, 141, 83, 170, 144, 202, 216, 133, 97, 32, 113, 103, 164, 45, 43, 9, 91, 203, 155, 37, 208, 190, 229, 108, 82, 89, 166, 116, 210, 230, 244, 180, 192, 209, 102, 175, 194, 57, 75, 99, 182};

const static uint8_t inPi[256]{165, 45, 50, 143, 14, 48, 56, 192, 84, 230, 158, 57, 85, 126, 82, 145, 100, 3, 87, 90, 28, 96, 7, 24, 33, 114, 168, 209, 41, 198, 164, 63, 224, 39, 141, 12, 130, 234, 174, 180, 154, 99, 73, 229, 66, 228, 21, 183, 200, 6, 112, 157, 65, 117, 25, 201, 170, 252, 77, 191, 42, 115, 132, 213, 195, 175, 43, 134, 167, 177, 178, 91, 70, 211, 159, 253, 212, 15, 156, 47, 155, 67, 239, 217, 121, 182, 83, 127, 193, 240, 35, 231, 37, 94, 181, 30, 162, 223, 166, 254, 172, 34, 249, 226, 74, 188, 53, 202, 238, 120, 5, 107, 81, 225, 89, 163, 242, 113, 86, 17, 106, 137, 148, 101, 140, 187, 119, 60, 123, 40, 171, 210, 49, 222, 196, 95, 204, 207, 118, 44, 184, 216, 46, 54, 219, 105, 179, 20, 149, 190, 98, 161, 59, 22, 102, 233, 92, 108, 109, 173, 55, 97, 75, 185, 227, 186, 241, 160, 133, 131, 218, 71, 197, 176, 51, 250, 150, 111, 110, 194, 246, 80, 255, 93, 169, 142, 23, 27, 151, 125, 236, 88, 247, 31, 251, 124, 9, 13, 122, 103, 69, 135, 220, 232, 79, 29, 78, 4, 235, 248, 243, 62, 61, 189, 138, 136, 221, 205, 11, 19, 152, 2, 147, 128, 144, 208, 36, 52, 203, 237, 244, 206, 153, 16, 68, 64, 146, 58, 1, 38, 18, 26, 72, 104, 245, 129, 139, 199, 214, 32, 10, 8, 0, 76, 215, 116};

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
	static inline void copy(uint8_t **res,uint8_t matr[16][16]){
		for (uint8_t i=0;i<16;i++){
			for (uint8_t j=0;j<16;j++){
				res[i][j]=matr[i][j];
			}
		}
	};
//------------------------------------------------------------------------------------------------------------------------------------------------------------------------
//Работает верно, одобрено
	static void generateMatrix(uint8_t matr[16][16]){
		uint8_t smezh;
		uint8_t **exponMatrix;
		exponMatrix=new uint8_t*[16];
		for (uint8_t i=0;i<16;i++){
			exponMatrix[i] = new uint8_t[16];
		}
		for(uint8_t i=0; i<4;i++){
			copy(exponMatrix,matr);
			for (uint8_t l=0;l<16;l++){
				for (uint8_t j=0;j<16;j++){
					smezh=0x0;
					for(uint8_t r=0;r<16;r++){
						smezh^=polinMultiple[exponMatrix[l][r]][exponMatrix[r][j]];
					}
					matr[l][j]=smezh;
				}
			}
		}
		//очищаем память для вспомогательного массива
		for(uint8_t i=0; i<16;i++){
			delete [] exponMatrix[i];
		}
		delete [] exponMatrix;
		exponMatrix = NULL;
	};
//------------------------------------------------------------------------------------------------------------------------------------------------------------------------
	class LSX{
		public:
			void X (uint8_t *key, uint8_t *block,uint8_t &order);
			void S (uint8_t *block, uint8_t const pi[256]);
			void L (uint8_t *block,uint8_t matr[16][16]);
			void generate_key(uint8_t *key,uint8_t &order,uint8_t matr[16][16]);
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

	void LSX::S(uint8_t *block,const uint8_t pi[256]){
		for(uint8_t i=0; i<16;i++){
			block[i]=pi[block[i]];
		}
	}

//----------------------------------------------------------------------------------------------------------------------------------------------------------------
//проверенная функция.

	void LSX::L(uint8_t *block,uint8_t matr[16][16]){
		for (uint8_t j=0; j<16;j++){
			for(uint8_t k=0; k<16;k++){
				newVector[j]^=polinMultiple[matr[k][j]][block[k]];
			}
		}
		reset(block);
	}
//---------------------------------------------------------------------------------------------------------------------------------------------------------------
//Проверенная функция.
	void LSX::swap(uint8_t *key,uint8_t *second_key){
		for(uint8_t oran=0;oran<16;oran++){
			key[oran+16]=second_key[oran];
		}
	}
//-------------------------------------------------------------------------------------------------------------------------------------------------------------
//Проверенная функция.
	void LSX::generate_key(uint8_t *key,uint8_t &order,uint8_t matr[16][16]){
		for(uint8_t i=order*8; i<((order+1)*8);i++){
			for(int j=0; j<16;j++) {
				swap_key[j]=key[j];
			}
			vector_for_key[15]=i+1;
			uint8_t ord=0;
			L(vector_for_key,matr);
			X(vector_for_key,key,ord);
			S(key,Pi);
			L(key,matr);
			for(uint8_t j=0; j<16;j++){
				key[j]^=key[16+j];
			}
			swap(key,swap_key);
			for (int l=0;l<16;l++) vector_for_key[l]=0x0;
		}
	}
//-------------------------------------------------------------------------------------------------------------------------------------------------------------
//Проверенная функция.			
		
	/*class EncDec{
		public:
			EncDec(uint8_t *key);
			void encrypt(uint8_t *block);
			~EncDec();
			void decrypt(uint8_t *block);
			void inline eninit();
			void inline deinit();// при множественном использовании encrypt/decrypt матрицы перемножения генерируются непозволительно много раз, вдобавок на каждой н-ой операции выскакивает невалиднсоть.
			//Метод сработал.
		protected:
			LSX deffight;
			uint8_t **cop;
	};*/
	
	class EncDec{
		public:
			void encrypt(uint8_t *block);
			~EncDec();
			void decrypt(uint8_t *block);
			void inline eninit(uint8_t *key);
			void inline deinit(uint8_t *key);// при множественном использовании encrypt/decrypt матрицы перемножения генерируются непозволительно много раз, вдобавок на каждой н-ой операции выскакивает невалиднсоть.
			//Метод сработал.
		protected:
			LSX deffight;
			uint8_t **cop;
			uint8_t kos;
			void makekeys(uint8_t *key);
	};

	void EncDec::makekeys(uint8_t *key){
		cop = new uint8_t* [5];
		for(uint8_t i=0; i <5; i++){
			cop[i] = new uint8_t[32];
			for(uint8_t y=0; y<32;y++)cop[i][y]=key[y];
			for(uint8_t j=0; j<i; j++)deffight.generate_key(cop[i],j,matrix);
		}
	}

	EncDec::~EncDec(){
		for(uint8_t i = 0; i<5; i++) delete [] cop[i];
		delete []cop;
		cop=NULL; // - Надо адаптировать
	}
	
	void inline EncDec::eninit(uint8_t *key){
		generateMatrix(matrix);
		makekeys(key);
	}


	void inline EncDec::deinit(uint8_t *key){
		generateMatrix(matrix);
		generateMatrix(inmatrix);
		makekeys(key);
	}

	void EncDec::encrypt(uint8_t *block){
		for(uint8_t i=0; i<5 ; i++){
			for(uint8_t j=0; j<2; j++){
				deffight.X(cop[i],block,j);
				if( (i==4) && (j==1)) break;
				deffight.S(block,Pi);
				deffight.L(block,matrix);
			}
		}
	}

	void EncDec::decrypt(uint8_t *block){
		for(int8_t i=4; i>-1;i--){
			for(int8_t y=1;y>-1;y--){
				kos=y;
				if (i == 4 && y == 1){
					deffight.X(cop[i],block,kos);
					continue;
				}
				deffight.L(block,inmatrix);
				deffight.S(block,inPi);
				deffight.X(cop[i],block,kos);
			}
		}
	}
	/*void EncDec::decrypt(uint8_t *block,uint8_t *key){
		uint8_t kostil;
		for(int8_t i=4;i>-1;i--){
			for(int ref=0;ref<32;ref++) cop[ref]=key[ref];
			if (i != 0){
				kostil=i;
				for(uint8_t l=0;l<kostil;l++){
					deffight.generate_key(cop,l,matrix);
				}
			}
			for(int8_t j=1;j>-1;j--){
				kostil=j;
				if (i == 4 && j == 1){
					deffight.X(cop,block,kostil);
					continue;
				}
				deffight.L(block,inmatrix);
				deffight.S(block,inPi);
				deffight.X(cop,block,kostil);
			}
		}
	}*/
//_____________________________________________________________________________________________________________________________________________________________
};
//Перепроверить на сокрытие и на оптимизацию.
namespace CryptoModes{

	class mode{
		public:
			template <typename railway>mode(railway from);
			~mode();
			virtual void encr()=0;
			virtual void decr()=0;
		protected:
			uint8_t *block;
			uint8_t *key;
			uint8_t *copykey;
//			uint64_t size;
			uint64_t fd;
			uint8_t *ptr;
			struct stat st;//ни наю, надо ли сюда это впихивать... или в конструкторе оставить...
			blockKuz::EncDec soldier;
//		public:
			void inline padding();
			void inline antipadding();
//			void inline copy();
	};
	template <typename railway>mode::mode(railway from){
		fd=from;
		fstat(fd,&st);
//		size=st.st_size;
		ptr=(uint8_t*)mmap(NULL, st.st_size, PROT_READ | PROT_WRITE,MAP_SHARED, fd,0);
		if(ptr == MAP_FAILED){
			perror("mmap");
			exit(-1);
		}
		key = new uint8_t [32];
		copykey = new uint8_t [32];
		int check = open("key.bin", O_RDONLY);
		while(read(check,key,32) != 32);//Проверка, что ключ точно считался... точнее вынуждаю прогу хотя бы раз его считать ПОЛНОСТЬЮ и ПРАВИЛЬНО!
		printf("Hi!\n");
		close(check);
	}
	mode::~mode(){
		int c = munmap(ptr,st.st_size);
		if(c == -1){
			perror("munmap");
			exit(-1);
		}
		delete [] key;
		delete [] copykey;
		block = NULL;
		key = NULL;
		copykey = NULL;
		std::cout<<"Очищено!";
	}
//-------------------------------------------------------------------------------------------------------------------------------------------------------------
//Проверено. Работает. Оптимизировано.
//	void inline mode::copy(){for(uint8_t gg=0; gg<32;gg++)copykey[gg]=key[gg];}
//-------------------------------------------------------------------------------------------------------------------------------------------------------------
//Проверено. Работает. Оптимизировано.
	void mode::padding(){
		if( (st.st_size%16) != 0){
			uint8_t one=0x1;
			uint8_t zero=0x0;
			uint8_t dopis=16-st.st_size%16;
			lseek(fd, 0,SEEK_END);
			write(fd, &one, 1);
			for(uint8_t i=0; i<dopis-1; i++){
				write(fd, &zero, 1);
			}
			fsync(fd);
			st.st_size+=dopis;
			lseek(fd,0,SEEK_SET);
		}
	}
//-------------------------------------------------------------------------------------------------------------------------------------------------------------
//Проверено. Работает. Оптимизировано.
	void inline mode::antipadding(){
		uint8_t check=0x0;
		for(uint8_t i=1; i<16;i++){
			lseek(fd,-i,SEEK_END);
			read(fd, &check,1);
			if( (check>0x1) ) {
				if( i!= 1) printf("Wrong padding.\nThere are some troubles with it.\nThere may be information loss.\n");
				break;
			}
			else{
				if( check == 0x1 ){
					st.st_size -= i;
					break;
				}
			}
		}
		ftruncate(fd,st.st_size);
	}
//-------------------------------------------------------------------------------------------------------------------------------------------------------------
//Работает корректно.
	class EFB:public mode{
		public:
			void encr();
			void decr();
			template<typename kek> EFB(kek hek):mode(hek){};//хороший пример наследования конструкторов)))
	};
	void EFB::encr(){
		padding();
		soldier.eninit(key);
		for(int tr=0; tr<(st.st_size/16);tr++){
			block = (ptr+tr*16);
			soldier.encrypt(block);
		}
		fsync(fd);
	}
	void EFB::decr(){
		soldier.deinit(key);
		for(int tr=0; tr<(st.st_size/16);tr++){
			block = (ptr+tr*16);
			soldier.decrypt(block);
		}
		antipadding();
	}
//-------------------------------------------------------------------------------------------------------------------------------------------------------------
	class CTR:public mode{
		public:
			void encr();
			void decr(){};
			template <typename heh> CTR(heh hek):mode(hek){
				int ini = open ("vect.bin",O_RDONLY);
				read(ini,vec,8);
				close(ini);
				for(uint8_t i=8;i<16;i++) vec[i]=0x0;
			}
		protected:
			uint8_t vec[16];
			uint8_t nvec[16];
			uint64_t swp=-1;
			void copyvect();
			uint64_t hm;	// just for size. Очередной костыль на ниже...
	};
//-------------------------------------------------------------------
//Костыльная хрень. Надо перебрать. Без хаков - некрасиво...
	void CTR::copyvect(){
		uint8_t kostil=15;
		swp++;
		for (uint8_t i=0; i<8;i++){
			vec[kostil]=*((uint8_t*)(&swp)+i);
			kostil--;
		}
		for (uint8_t i=0; i<16;i++)nvec[i]=vec[i];
	}
//-------------------------------------------------------------------
//Работает, но вроде с костылями....
	void CTR::encr(){//this funcion is just for encrypt and decrypt.
		soldier.eninit(key);
		uint64_t size=0x0,end;
		if((st.st_size%16) != 0) st.st_size+=(16-st.st_size%16);
		for(uint64_t i=0; i<(st.st_size/16); i++){
			copyvect();
			soldier.encrypt(nvec);
			for(uint8_t g=0;g<16;g++){
				if (size == st.st_size) return;
				*(ptr+size)^=nvec[g];
				size++;
			}
		}
	}
//--------------------------------------------------------------------
//Режим гаммирования с обратной связью по выходу
	class OFB:public mode{
		public:
			void encr();
			void decr(){};
			template<typename heh> OFB(heh hek):mode(hek){
				int cel=open("posil.bin",O_RDONLY);
				read(cel,synk,32);
				close(cel);
				for (uint8_t i=0;i<16;i++) blok[i]=synk[i];
			}
		protected:
			uint8_t synk[32];
			uint8_t blok[16];
	};
	void OFB::encr(){
		uint64_t size=0,end;
		if((st.st_size%16) !=0) end=((st.st_size+st.st_size%16)/16);
		else end=st.st_size/16;
		soldier.eninit(key);
		for(uint64_t i=0;i<end;i++){
			//soldier.encrypt((synk+(i%2)*16));
			//for(int j=0;j<16;j++)printf("%2x ",synk[j+(i%2)*16]);
			soldier.encrypt((synk+(i%2)*16));
			for(uint8_t kl=0;kl<16;kl++){
				if(size == st.st_size) return;
				*(ptr+i*16+kl)^=synk[kl+(i%2)*16];
				size++;
			}
		}
	}

//Режим простой замены с зацеплением
	class CBC:public mode{
		public:
			template<typename heh>CBC(heh hek):mode(hek){
				int rid=open("posil.bin", O_RDONLY);
				read(rid,vector,32);
				close(rid);
			}
			void encr();
			void decr();
		protected:
			uint8_t vector[32];
			uint8_t old[16];
	};

	void CBC::encr(){
		uint8_t l=0;
		soldier.eninit(key);
		padding();
		for(uint8_t i=0;i<2;i++){
			for(l=0;l<16;l++)*(ptr+i*16+l)^=vector[l+i*16];
			soldier.encrypt((ptr+i*16));
		}
		for(uint64_t i=2; i<(st.st_size/16); i++){
			for(l=0;l<16;l++) *(ptr+i*16+l)^=*(ptr+(i-2)*16+l);
			soldier.encrypt((ptr+i*16));
		}
	}

	void CBC::decr(){
		uint8_t l;
		soldier.deinit(key);
		for(uint64_t i=0; i<(st.st_size/16);i++){
			for(l=0;l<16;l++) old[l]=*(ptr+i*16+l);
			soldier.decrypt((ptr+i*16));
			for(l=0;l<16;l++){
				*(ptr+i*16+l)^=vector[l+(i%2)*16];
				vector[l+(i%2)*16]=old[l];
			}
		}
		antipadding();
	}

//режим гаммирования с обратной связью по шифротексту
	class CFB{};
//Режим выработки имитовствки
	class MAC{};
//---------------------------------------------------------------------
};

//-------------------------------------------------------------------------------------------------------------------------------------------------------------
namespace fs=std::filesystem;

void ma(int sig){
	printf("\n%s - res\n",strsignal(sig));
	exit(-1);
}
void seg(int sig){
	printf("by!\n");
	exit(-1);
}
int main(int argc, char* argv[]){
	signal(SIGSEGV, ma);
	signal(SIGTERM,seg);
	int sl;
	for(int i = 1; i < argc; i++){
	        if(fs::is_directory(argv[i]))
	        {
	            for(auto& p: fs::recursive_directory_iterator(argv[i]))
	            {
	                if(fs::is_regular_file(p.path()))
	                {
				fs::path file=fs::path(p.path());
	                    	sl=open(file.c_str(), O_RDWR);
				CryptoModes::OFB rm(sl);
				rm.encr();
				close(sl);
	                }
	            }
	        }
	        if(fs::is_regular_file(argv[i])) {
			sl=open(argv[i],O_RDWR);
			CryptoModes::OFB rm(sl);
			rm.encr();
			close(sl);
		}
	}
	return 0;
}
