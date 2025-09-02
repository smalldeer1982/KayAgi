#include<bits/stdc++.h>
using namespace std;
#define int long long
const int maxn=5e4+5;
int n,m,k,a[maxn];
int sum=0,cnt[maxn];
int ans1[maxn],ans2[maxn];
int f[maxn];
struct node{
	int l,r,id;
}q[maxn];
bool cmp(node s,node t){
	if(s.r/k==t.r/k){
		return s.l<t.l;
	}
	return s.r<t.r;
}
void add(int x){
	sum+=cnt[x];
	cnt[x]++;
}
void del(int x){
	cnt[x]--;
	sum-=cnt[x];
}
signed main(){
	ios::sync_with_stdio(false);
	cin.tie(0);
	cout.tie(0);
	cin>>n>>m;
	for(int i=1;i<=n;i++){
		cin>>a[i];
	}
	k=sqrt(n);
	for(int i=1;i<=m;i++){
		cin>>q[i].l>>q[i].r;
		q[i].id=i;
	}
	sort(q+1,q+m+1,cmp);
	int l=1,r=0;
	for(int i=1;i<=m;i++){
		while(l>q[i].l){
			add(a[--l]);
		}
		while(r<q[i].r){
			add(a[++r]);
		}
		while(l<q[i].l){
			del(a[l++]);
		}
		while(r>q[i].r){
			del(a[r--]);
		}
		ans1[q[i].id]=sum;
		ans2[q[i].id]=(q[i].r-q[i].l+1)*(q[i].r-q[i].l)/2;
		if(q[i].l==q[i].r){
			f[q[i].id]=1;
		}
	}
	for(int i=1;i<=m;i++){
		int x=__gcd(ans1[i],ans2[i]);
		if(f[i]==1){
			cout<<"0/1"<<'\n';
		}
		else{
			cout<<ans1[i]/x<<'/'<<ans2[i]/x<<'\n';
		}
	}
	return 0;
}
