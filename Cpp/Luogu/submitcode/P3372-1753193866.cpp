#include<bits/stdc++.h>
using namespace std;
#define int long long
#define lc u<<1
#define rc u<<1|1
const int maxn=1e5+5;
int n,m,op,x,y,k;
int w[maxn];
struct tree{
	int l,r,data,lazy;
}tr[4*maxn];
void pushup(int u){
	tr[u].data=tr[lc].data+tr[rc].data;
}
void pushdown(int u){
	if(tr[u].lazy){
		tr[lc].data+=tr[u].lazy*(tr[lc].r-tr[lc].l+1);
		tr[rc].data+=tr[u].lazy*(tr[rc].r-tr[rc].l+1);
		tr[lc].lazy+=tr[u].lazy;
		tr[rc].lazy+=tr[u].lazy;
		tr[u].lazy=0;
	}
}
void build(int u,int l,int r){
	tr[u]={l,r,w[l],0};
	if(l==r){
		return;
	}
	int c=(l+r)/2;
	build(lc,l,c);
	build(rc,c+1,r);
	pushup(u);
}
void change(int u,int l,int r,int k){
	if(l<=tr[u].l&&tr[u].r<=r){
		tr[u].data+=k*(tr[u].r-tr[u].l+1);
		tr[u].lazy+=k;
		return;
	}
	int c=(tr[u].l+tr[u].r)/2;
	pushdown(u);
	if(l<=c){
		change(lc,l,r,k);
	}
	if(r>c){
		change(rc,l,r,k);
	}
	pushup(u);
}
int query(int u,int l,int r){
	if(l<=tr[u].l&&tr[u].r<=r){
		return tr[u].data;
	}
	int c=(tr[u].l+tr[u].r)/2;
	int sum=0;
	pushdown(u);
	if(l<=c){
		sum+=query(lc,l,r);
	}
	if(r>c){
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
	for(int i=1;i<=m;i++){
		cin>>op>>x>>y;
		if(op==1){
			cin>>k;
			change(1,x,y,k);
		}
		else{
			cout<<query(1,x,y)<<endl;
		}
	}
	return 0;
}