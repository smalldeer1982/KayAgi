#include<bits/stdc++.h>
using namespace std;
long long n,sum=0,a[65];
void fun(long long res){
	if(a[res]!=0){
		sum+=a[res];
		return;
	}
	if(res==0){
		sum+=1;
		return;
	}
	if(res>=3){
		fun(res-3);
	}	
	if(res>=2){
		fun(res-2);
	}
	if(res>=1){
		fun(res-1);
	}
}
int main(){
	for(int i=1;i<=60;i++){
		sum=0;
		fun(i);
		a[i]=sum;
	}
	cin>>n;
	cout<<a[n];
	return 0;
}
