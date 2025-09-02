#include<bits/stdc++.h>
#define int long long
using namespace std;
const int maxn=5e6+5;
int n,dp[maxn],sz[maxn];
vector<int>g[maxn];
void dfs(int u,int f){
	sz[u]=1;
	for(auto v:g[u]){
		if(v==f){
			continue;
		}
		dfs(v,u);
		sz[u]+=sz[v];
		dp[u]+=dp[v]+sz[v];
	}
}
void dfs1(int u,int f){
	for(auto v:g[u]){
		if(v==f){
			continue;
		}
		dp[v]=dp[u]-sz[v]+n-sz[v];
		dfs1(v,u);
	}
}
signed main(){
	ios::sync_with_stdio(false);
	cin.tie(0);
	cout.tie(0);
	cin>>n;
	for(int i=1;i<n;i++){
		int x,y;
		cin>>x>>y;
		g[x].push_back(y);
		g[y].push_back(x);
	}
	dfs(1,0);
	dfs1(1,0);
	int ans=0,pos=0;
	for(int i=1;i<=n;i++){
		if(dp[i]>ans){
			ans=dp[i];
			pos=i;
		}
	}
	cout<<pos;
	return 0;
}
