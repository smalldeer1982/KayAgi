#include<bits/stdc++.h>
using namespace std;
int n,r[6005],in[6005],root;
int dp[6005][2];
vector<int>g[6005];
void dfs(int u){
	dp[u][0]=0;
	dp[u][1]=r[u];
	for(int v:g[u]){
		dfs(v);
		dp[u][0]+=max(dp[v][0],dp[v][1]);
		dp[u][1]+=dp[v][0];
	}
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
		in[l]+=1;
	}
	for(int i=1;i<=n;i++){
		if(!in[i]){
			root=i;
		}
	}
	dfs(root);
	cout<<max(dp[root][0],dp[root][1]);
	return 0;
}
