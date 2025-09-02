#include<bits/stdc++.h>
using namespace std;
int n,k,x;
int dp[10005][3];
vector<int>g[10005];
void dfs(int u,int f){
	bool flag=0;
	int t=0x3f3f3f;
	for(int i=0;i<g[u].size();i++){
		int v=g[u][i];
		if(v==f){
			continue;
		}
		dfs(v,u);
		dp[u][0]+=min(dp[v][1],dp[v][2]);
		dp[u][1]+=min(dp[v][0],min(dp[v][1],dp[v][2]));
		if(dp[v][1]<=dp[v][2]){
            flag=1;
            dp[u][2]+=dp[v][1];
        }
        else {
            t=min(t,dp[v][1]-dp[v][2]);
            dp[u][2]+=dp[v][2];
        }
	}
	if(flag==0){
		dp[u][2]+=t;
	}
	dp[u][1]+=1;
	return;
}
int main(){
	cin>>n;
	for(int i=2;i<=n;i++){
		cin>>k>>x;
		g[k].push_back(x);
		g[x].push_back(k);
	}
	dfs(1,0);
	cout<<min(dp[1][1],dp[1][2]);
	return 0;
}
