#include<bits/stdc++.h>
#define int long long
#define ls u<<1
#define rs ls|1
using namespace std;
const int maxn=1e5+5;
int t,mod;
struct tree{
	int l,r,mul;
}tr[maxn*4];
void pushup(int u){
	tr[u].mul=(tr[ls].mul*tr[rs].mul)%mod;
}
void build(int u,int l,int r){
	tr[u]={l,r,1};
	if(l==r){
		return;
	}
	int mid=(l+r)/2;
	build(ls,l,mid);
	build(rs,mid+1,r);
	pushup(u);
}
void change(int u,int x,int c){
	if(x==tr[u].l&&x==tr[u].r){
		tr[u].mul=c;
		return;
	}
	int mid=(tr[u].l+tr[u].r)/2;
	if(x<=mid){
		change(ls,x,c);
	}
	if(x>mid){
		change(rs,x,c);
	}
	pushup(u);
}
signed main(){
	ios::sync_with_stdio(false);
	cin.tie(0);
	cout.tie(0);
	cin>>t;
	for(int I=1;I<=t;I++){
		int q,op,m,pos;
		cin>>q>>mod;
		build(1,1,q);
		for(int i=1;i<=q;i++){
			cin>>op;
			if(op==1){
				cin>>m;
				change(1,i,m);
			}
			else{
				cin>>pos;
				change(1,pos,1);
			}
			cout<<tr[1].mul<<endl;
		}
	}
	return 0;
}
