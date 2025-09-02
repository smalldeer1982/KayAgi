#include<bits/stdc++.h>
using namespace std;
#define int long long
#define lc u<<1
#define rc u<<1|1
const int maxn=1e5+5;
int n,m,op,x,y,k;
int w[maxn];
struct tree{
	int l,r,sum,add;
}tr[maxn*4];
void pushup(int u){
	tr[u].sum=tr[lc].sum+tr[rc].sum;
}
void pushdown(int u){
	if(tr[u].add){
		tr[lc].sum+=tr[u].add*(tr[lc].r-tr[lc].l+1);
	    tr[rc].sum+=tr[u].add*(tr[rc].r-tr[rc].l+1);
	    tr[lc].add+=tr[u].add;
	    tr[rc].add+=tr[u].add;
	    tr[u].add=0;   
	}
}
void build(int u,int l,int r){
	tr[u]={l,r,w[l],0};
	if(l==r){
		return;
	}
	int m=(l+r)/2;
	build(lc,l,m);
	build(rc,m+1,r);
	pushup(u);
}
void change(int u,int l,int r,int k){
	if(l<=tr[u].l&&tr[u].r<=r){
		tr[u].sum+=(tr[u].r-tr[u].l+1)*k;
		tr[u].add+=k;
		return;
	}
	int m=(tr[u].l+tr[u].r)/2;
	pushdown(u);
	if(l<=m){
		change(lc,l,r,k);
	}
	if(r>m){
		change(rc,l,r,k);
	}
	pushup(u);
}
int query(int u,int l,int r){
	if(l<=tr[u].l&&tr[u].r<=r){
		return tr[u].sum;
	}
	int m=(tr[u].l+tr[u].r)/2;
	pushdown(u);
	int sum=0;
	if(l<=m){
		sum+=query(lc,l,r);
	}
	if(r>m){
		sum+=query(rc,l,r);
	}
	return sum;
}
signed main(){
	ios::sync_with_stdio(false);
	cin.tie(0);
	cout.tie(0);
	cin>>n>>m;
	for(int i=1;i<=n;i++){
		cin>>w[i];
	}
	build(1,1,n);
	for(int I=1;I<=m;I++){
		cin>>op>>x>>y;
		if(op==1){
			cin>>k;
			change(1,x,y,k);
		}
		else{
			cout<<query(1,x,y)<<'\n';
		}
	}
	return 0;
}
