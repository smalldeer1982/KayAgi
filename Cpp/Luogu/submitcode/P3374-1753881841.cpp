#include<bits/stdc++.h>
using namespace std;
#define int long long
const int maxn=5e5+5;
int n,m,op,x,y;
int w[maxn],s[maxn];
int lowbit(int x){
	return x&-x;
}
void change(int x,int k){
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
signed main(){
	ios::sync_with_stdio(false);
	cin.tie(0);
	cout.tie(0);
	cin>>n>>m;
	for(int i=1;i<=n;i++){
		cin>>w[i];
		change(i,w[i]);
	}
	for(int i=1;i<=m;i++){
		cin>>op>>x>>y;
		if(op==1){
			change(x,y);
		}
		else{
			cout<<query(y)-query(x-1)<<endl;
		}
	}
	return 0;
}