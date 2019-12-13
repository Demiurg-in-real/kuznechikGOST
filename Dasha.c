#include<stdio.h>
#include <stdlib.h>
#include<math.h>
#include<signal.h>
int Fact();
//int graph();
int mulmat(int **M1, int **M2, int **SUM);
void handler(int sig){
	printf("Даш, у тебя опять косяк с памятью. Лошаааааааарааааа!\nYour brain was fuched by signal %i.\n%s\n",sig,strsignal(sig));
	abort();
}
void dante(int sig){
	printf("Smth wrong...\n");
	exit(EXIT_FAILURE);
}
int main(int argc,char* argv[]) {
	//signal(SIGSEGV, handler);
	//signal(SIGTERM, dante);
	int a , num;
	printf("что считать? : ");
	printf("\n 1 - посчитать факториал \n 2 - решить уравнение \n 3 - перемножение матриц \n" );
	scanf("%d", &num);
	if (num == 1) {
		Fact();
	}
	if (num == 2) {
//		graph();
	}

	if (num == 3) {
		int **r;
		int **c;
		int **d;
		mulmat(r,c,d);
	}
}
// переделот
int Fact() {
	int Fact2;
	printf("введи число: ");
	scanf("%d", &Fact2);
	int j = Fact2;
	for (int i = 1; i <= j ; i++) {
			Fact2 = Fact2 * i;
	}
	printf("%d\n", Fact2);

	return EXIT_SUCCESS;
}

/*int graph() {

	int a,b,c,x,i,d;
	double x1 , x2 , x3 , x4;
	printf("input numbers: ");
	scanf("%d %d %d", &a, &b , &c);
	d = (b*b - 4*a*c);
	if (d < 0) {
		printf(" mnimoe ");
	}
	if (d > 0) {
		x1 = ((- b + sqrt((double)d)) / (2 * a));
		x2 = ((- b - sqrt((double)d)) /(2*a));
		printf("\n уравнение: (x^2 * %d",a );
		printf(") + (x * %d",b);
		printf(") + %d",c );
		printf(" = 0\n" );
		printf("\n корни: %.2f %.2f \n", x1 , x2);
		char *x;
		x = (char*)malloc(3*sizeof(char));
		static int j;
		printf("dx: ");
		for (int j = 0; j < 3; ++j) {
			scanf("%s", &x[j]);
		}
		printf(" еще раз x: %d\n ", x[j]);
	}
return 0;
}*/

int mulmat(int **M1 , int **M2, int **MUL) {

	int m, n, n1 , m1,s1,s2, k;
	while (m1 != n) {
		printf("\nкол-во столбцов 1 матрицы должно быть = кол-ву строк 2 матрицы\n");
		printf("\nразмерность матрицы 1: \n");
		scanf("%d %d", &m , &m1);
		printf("размерность матрицы 2: \n");
		scanf("%d %d", &n, &n1);
	}

	M1 = (int**)malloc(m*sizeof(int*));
	M2 = (int**)malloc(n*sizeof(int*));
	MUL = (int**)malloc(n*sizeof(int*));

	for (int j = 0; j < m; j++) {
		M1[j] = (int*)malloc(m*sizeof(int));
	}

	for (int j = 0; j < m; j++) {
		MUL[j] = (int*)malloc(s1*sizeof(int));
	}

	for (int j = 0; j < n; j++) {
			M2[j] = (int*)malloc(n*sizeof(int));
		}
	printf("матрица 1:\n");
	for (int i = 0; i < m; i++ ) {
			for (int j = 0; j < m1; j++){
				printf("A %d%d: ", i+1, j+1);
				scanf("%d", &M1[i][j]);
			}
	}
	printf("матрица 2: \n");
	for (int i = 0; i < n; i++ ) {
			for (int j = 0; j < n1; j++){
				printf("B %d%d: ", i+1, j+1);
				scanf("%d", &M2[i][j]);
			}
	}
	
	printf("введенная матрица 1:\n");
	for(int i=0; i<m;i++){
		for(int j=0;j<m1;j++){
			printf(" %i ", M1[i][j]);
		}
		printf("\n");
	}

	printf("введенная матрица 2:\n");
	for(int i=0; i<n;i++){
		for(int j=0;j<n1;j++){
			printf("%i ", M2[i][j]);
		}
		printf("\n");
	}
	printf("Multiplication: \n");
	for(int i=0; i<m;i++)
	{
		for(int j=0;j<n1;j++)
		{
			for(k = 0; k < n; k++)
			{
MUL[i][j] += M1[i][k] * M2[k][j];
			}
			printf("%i ", MUL[i][j]);
		}
		printf("\n");
	}
//return 0;
free(M1);
	free(M2);
free(MUL);
											return 0;
}





















