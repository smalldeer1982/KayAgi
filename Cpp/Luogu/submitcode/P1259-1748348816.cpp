#include<bits/stdc++.h>
#define int long long
using namespace std;
int n,sum=0;
char ans[205];
void print(){
	for(int i=1;i<=2*n+2;i++){
		cout<<ans[i];
	}
	cout<<endl;
}
void mo(int y){
	for(int i=0;i<=1;i++){
		ans[sum+i]=ans[y+i];
		ans[y+i]='-';
	}
	sum=y;
	print();
}
void run(int x){
	if(x==4){
		mo(4);
		mo(8);
		mo(2);
		mo(7);
		mo(1);
	}
	else{
		mo(x);
		mo(x*2-1);
		run(x-1);
	}
}
signed main(){
	cin>>n;
	for(int i=1;i<=n;i++){
		ans[i]='o';
	}
	for(int i=n+1;i<=2*n;i++){
		ans[i]='*';
	}
	ans[2*n+1]='-';
	ans[2*n+2]='-';
	print();
	sum=2*n+1;
	run(n);
	return 0;
}
