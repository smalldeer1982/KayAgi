#include<bits/stdc++.h>
using namespace std;
const int maxn=5e4+5;
int n,m,k,l,r,s=-1;
int a[maxn],b[maxn],f[maxn];
struct node{
	int l,r,v;
}d[maxn];
bool cmp(node x,node y){
	if(x.l==y.l){
		return x.r<y.r;
	}
	return x.l<y.l;
}
int main(){
	ios::sync_with_stdio(false);
	cin.tie(0),cout.tie(0);
	cin>>n>>m>>k;
	for(int i=1;i<=n;i++){
		cin>>a[i];
	}
	for(int i=1;i<=m;i++){
		d[i].v=i;
		cin>>d[i].l>>d[i].r;
	}
	sort(d+1,d+m+1,cmp);
	for(int i=1;i<=m;i++){
		while(r<d[i].r){
			s+=b[a[++r]]++<<1|1;
		}
		while(l>d[i].l){
			s+=b[a[--l]]++<<1|1;
		}
		while(l<d[i].l){
			s-=--b[a[l++]]<<1|1;
		}
		while(r>d[i].r){
			s-=--b[a[r--]]<<1|1;
		}
		f[d[i].v]=s;
	}
	for(int i=1;i<=m;i++){
		cout<<f[i]<<endl;
	}
	return 0;
} 