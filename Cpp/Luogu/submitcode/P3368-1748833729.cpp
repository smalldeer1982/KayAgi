#include<bits/stdc++.h>
using namespace std;
const int maxn=5e5+5; 
int n,m,a[maxn],s[maxn];
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
	int op,x,y,k;
	for(int i=1;i<=n;i++){
		cin>>a[i];
	} 
	for(int i=1;i<=m;i++){
		cin>>op>>x;
		if(op==1){
			cin>>y>>k;
			update(x,k);
			update(y+1,-k);
		}
		else{
			cout<<a[x]+query(x)<<endl;
		}
	}
	return 0;
}