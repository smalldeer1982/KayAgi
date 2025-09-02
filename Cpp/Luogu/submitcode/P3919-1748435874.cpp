#include<bits/stdc++.h>
using namespace std;
const int maxn=1e6+1000;
int a[maxn],tot,ls[maxn*30],rs[maxn*30];
int root[maxn],s[maxn*30];
void build(int &u,int L,int R){
	u=++tot;
	if(L==R){
		s[u]=a[L];
		return;
	}
	int mid=(L+R)/2;
	build(ls[u],L,mid);
	build(rs[u],mid+1,R);
}
void update(int &u,int v,int L,int R,int x,int y){
	u=++tot;
	if(L==R){
		s[u]=y;
		return;
	}
	ls[u]=ls[v];
	rs[u]=rs[v];
	int mid=(L+R)/2;
	if(x<=mid){
		update(ls[u],ls[v],L,mid,x,y);	
	}
	else{
		update(rs[u],rs[v],mid+1,R,x,y);
	}
}
int query(int u,int L,int R,int x){
	if(L==R){
		return s[u];
	}
	int mid=(L+R)/2;
	if(x<=mid){
		return query(ls[u],L,mid,x);	
	}
	else{
		return query(rs[u],mid+1,R,x);
	}
}
int main(){
	ios::sync_with_stdio(false);
	cin.tie(0);
	cout.tie(0);
	int n,m;
	cin>>n>>m;
	for(int i=1;i<=n;i++){
		cin>>a[i];
	}
	build(root[0],1,n);
	for(int i=1;i<=m;i++){
		int vi,op;
		cin>>vi>>op;
		if(op==1){
			int	x,y;
			cin>>x>>y;
			update(root[i],root[vi],1,n,x,y);
		}
		else{
			int x;
			cin>>x;
			cout<<query(root[vi],1,n,x)<<endl;
			root[i]=root[vi];
		}
	}
	return 0;
}