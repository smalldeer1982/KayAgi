#include<bits/stdc++.h>
using namespace std;
int n,m,s[500005];
int lowbit(int x){
	return x&-x;
}
void update(int x,int k){
	while(x<=n){
		s[x]+=k;
		x+=lowbit(x);
	}
}
int query(int x){
	int t=0;
	while(x){
		t+=s[x];
		x-=lowbit(x);
	}
	return t;
}
int main(){
	cin>>n>>m;
	int op,x,y;
	for(int i=1;i<=n;i++){
		cin>>x;
		update(i,x);
	} 
	for(int i=1;i<=m;i++){
		cin>>op>>x>>y;
		if(op==1){
			update(x,y);
		}
		else{
			cout<<query(y)-query(x-1)<<endl;
		}
	}
	return 0;
}