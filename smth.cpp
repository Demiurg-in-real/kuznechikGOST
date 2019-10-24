#include<stdio.h>
static int gu[3][3]={
	{1,2,3},
	{4,5,6},
	{9,8,7}
};
static inline void copy(int **a){
	for (int i=0;i<3;i++){
		for(int j=0;j<3;j++){
			a[i][j]=gu[i][j];
		}
	}
}
int main(){
	int **c;
//	int **gu;
	c= new int*[3];
//	c=(int**)malloc(sizeof(int)*3);
	for (int i=0;i<3;i++){
		c[i]= new int[3];//(int*)malloc(sizeof(int)*3);
	}
	copy(c);
	c[2][1]*=2;
	printf("%i - %i\n",c[2][1],gu[2][1]);
	for(int i=0; i<3;i++){
		delete [] c[i];
	}
	delete [] c;
//	delete [] gu[1];
	return 0;
}
