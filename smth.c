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

	for (int i=0;i<3;i++){
		a=(int*)malloc(si:zeof(int)*3);
	copy(*c);
	c[2][2]*=2;
	printf("%i - %i\n",c[2][2],gu[2][2]);
	return 0;
}
