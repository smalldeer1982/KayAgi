#include<bits/stdc++.h>
using namespace std;
#define int long long
const int maxn=1e4+5,maxm=5e3+5;
int n,m,w;
int c[maxn],d[maxn],v[maxm],u[maxm],fa[maxn],dp[maxn];
void init(){
	for(int i=1;i<=10000;i++){
		fa[i]=i;
	}
}
int find(int x){
	return fa[x]==x?x:fa[x]=find(fa[x]);
}
void merge(int x,int y){
	int fx,fy;
	fx=find(x);
	fy=find(y);
	if(fx!=fy){
		fa[fy]=fx;
	}
}
signed main(){
	ios::sync_with_stdio(false);
	cin.tie(0);
	cout.tie(0);
	init();
	cin>>n>>m>>w;
	for(int i=1;i<=n;i++){
		cin>>c[i]>>d[i];
	}
	for(int i=1;i<=m;i++){
		cin>>v[i]>>u[i];
	}
	for(int i=1;i<=m;i++){
		merge(v[i],u[i]);
	}
	for(int i=1;i<=n;i++){
		if(find(i)!=i){
			c[find(i)]+=c[i];
			d[find(i)]+=d[i];
			c[i]=0;
			d[i]=0;
		}
	}
	for(int i=1;i<=n;i++){
		for(int j=w;j>=c[i];j--){
			dp[j]=max(dp[j],dp[j-c[i]]+d[i]);
		}
	}
	cout<<dp[w];
	return 0;
}