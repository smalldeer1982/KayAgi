#include<bits/stdc++.h>
using namespace std;
int n,k,x,root;
int dp[1505][2];
vector<int>g[1505];
void dfs(int u,int f){
	dp[u][1]=1;
	for(int i=0;i<g[u].size();i++){
		int v=g[u][i];
		if(v==f){
			continue;
		}
		dfs(v,u);
		dp[u][1]+=min(dp[v][0],dp[v][1]);
		dp[u][0]+=dp[v][1];
	}
	return;
}
int main(){
	cin>>n;
	for(int i=1;i<=n;i++){
		cin>>k>>x;
		k+=1;
		int num;
		for(int j=1;j<=x;j++){
			cin>>num;
			num+=1;
			g[k].push_back(num);
			g[num].push_back(k);
		}
	}
	dfs(1,0);
	cout<<min(dp[1][0],dp[1][1]);
	return 0;
}
