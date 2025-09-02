#include<bits/stdc++.h>
#define int long long
using namespace std;
int n;
int mark[20]={1};
void init(){
	for(int i=1;i<=17;i++){
		mark[i]=mark[i-1]*2;
	}
}
void dfs(int x){
	int flag=0;
	while(x>=mark[flag]){
		flag+=1;
	}
	flag-=1;
	x-=mark[flag];
	cout<<2;
	if(flag!=1){
		cout<<"(";
	}
	if(flag==0||flag==2){
		cout<<flag<<")";
	}
	if(flag>=3){
		dfs(flag);
		cout<<")";
	}
	if(x!=0){
		cout<<"+";
		dfs(x);
	}
}
signed main(){
	cin>>n;
	init();
	dfs(n);
	return 0;
}
