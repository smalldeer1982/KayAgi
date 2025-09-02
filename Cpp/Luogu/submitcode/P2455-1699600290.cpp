#include <cstdio>
#include <cmath>
#include <iostream>
using namespace std;

double A[50][51];
int N;

int main(){
	scanf("%d", &N);
	for(int i =0; i < N; ++i) for(int j =0; j < N+1; ++j)
		scanf("%lf", &A[i][j]);
	int nwline =0;
	//k指主元序号(列) 
	for(int k =0; k < N; ++k){//需要考虑无穷解，循环到N 
		int maxi =nwline;
		for(int i =nwline+1; i < N; ++i)
			if(abs(A[i][k]) > abs(A[maxi][k])) maxi =i;
		if(A[maxi][k] == 0) continue;
		for(int j =0; j < N+1; ++j)
			swap(A[nwline][j], A[maxi][j]);
		for(int i =0; i < N; ++i){
			if(i == nwline) continue;
			double mul =A[i][k]/A[nwline][k];
			//A[nwline][i] =0;//这里判不判无所谓，因为这一列其他的项之后都可以推出来了(0)，不用再访问 
			for(int j =k+1; j < N+1; ++j)
				A[i][j] -=A[nwline][j]*mul;
		}
		++nwline;
	}
	//最后的元随机分配就行了，结果不会有差，不如说左边一定都是0
	if(nwline < N){
		while(nwline < N)
			if(A[nwline++][N] != 0) return puts("-1") && 0;
		return putchar('0') && 0;
	}
	for(int i =0; i < N; ++i){
		printf("x%d=", i+1);
		if(int(A[i][N]/A[i][i]*100) == 0) puts("0");
		else printf("%.2lf\n", A[i][N]/A[i][i]);
	}
}