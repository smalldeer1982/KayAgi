#include<bits/stdc++.h>
using namespace std;
int n,dp[100005][3];
vector<int>g[100005];
int maxn,tmp;
void dfs(int u,int f,int step){
	if(step>maxn){
		maxn=step;
		tmp=u;
	}
	for(int v:g[u]){
		if(v!=f){
			dfs(v,u,step+1);
		}
	}
	return;
}
int main(){
	cin>>n;
	for(int i=1;i<=n-1;i++){
		int x,y;
		cin>>x>>y;
		g[x].push_back(y);
		g[y].push_back(x);
	}
	maxn=-1;
	dfs(1,-1,0);
	maxn=-1;
	dfs(tmp,-1,0);
	cout<<maxn;
	return 0;
}