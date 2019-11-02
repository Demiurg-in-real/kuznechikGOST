#include<cstdio>
class typ{
	public:
		void pri(char l){
			printf("Hi, %c!",l);
		}
};
class viz{
	public:
		void get(char k){
			typ r;
			r.pri(k);
		}
		viz(char l){printf("I'm created! - %c\n", l);}
};
int main(){
	char c=0x61;
	viz l(c);
	l.get(c);
	char &e=c;

	return 0;
}
