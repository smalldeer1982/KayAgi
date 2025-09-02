#include<bits/stdc++.h>
#define int long long
using namespace std;
const int mod=1e9+7;
int n,k;
int dp[100005][3];
vector<int>g[100005];
void dfs(int u,int f){
	for(int i=0;i<g[u].size();i++){
		int v=g[u][i];
		if(v==f){
			continue;
		}
		dfs(v,u);
		dp[u][0]=dp[u][0]*((dp[v][1]+dp[v][2])%mod)%mod;
		dp[u][1]=dp[u][1]*((dp[v][0]+dp[v][2])%mod)%mod;
		dp[u][2]=dp[u][2]*((dp[v][1]+dp[v][0])%mod)%mod;
	}
}
signed main(){
	cin>>n>>k;
	for(int i=1;i<n;i++){
		int x,y;
		cin>>x>>y;
		g[x].push_back(y);
		g[y].push_back(x);
	}
	for(int i=1;i<=n;i++){
		for(int j=0;j<3;j++){
			dp[i][j]=1;
		}
	}
	for(int i=1;i<=k;i++){
		int x,y;
		cin>>x>>y;
		y-=1;
		for(int j=0;j<3;j++){
			if(j!=y){
				dp[x][j]=0;
			}
		}
	}
	dfs(1,0);
	cout<<(dp[1][0]+dp[1][1]+dp[1][2])%mod;
	return 0;
}
