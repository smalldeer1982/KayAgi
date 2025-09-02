#include<bits/stdc++.h>
using namespace std;
int n,r[16005],ans=-2147483647;
int dp[16005];
vector<int>g[16005];
void dfs(int u,int f){
	dp[u]=r[u];
	for(int i=0;i<g[u].size();i++){
		int v=g[u][i];
		if(v==f){
			continue;
		}
		dfs(v,u);
		if(dp[v]>0){
			dp[u]+=dp[v];
		}
	}
	ans=max(ans,dp[u]);
	return;
}
int main(){
	cin>>n;
	for(int i=1;i<=n;i++){
		cin>>r[i];
	}
	for(int i=1;i<=n-1;i++){
		int l,k;
		cin>>l>>k;
		g[k].push_back(l);
		g[l].push_back(k);
	}
	dfs(1,0);
	cout<<ans;
	return 0;
}
