#include<bits/stdc++.h>
#define int long long
using namespace std;
int n,q,dp[105][105];
vector<pair<int,int>>k[105];
void dfs(int x,int f){
	for(vector<pair<int,int>>::iterator it=k[x].begin();it!=k[x].end();it++){
		pair<int,int>i=*it;
		if(i.first==f){
			continue;
		}
		dfs(i.first,x);
		for(int j=q;j>=0;j--){
			for(int k=0;k<j;k++){
				dp[x][j]=max(dp[x][j],dp[i.first][k]+dp[x][j-k-1]+i.second);
			}
		}
	}
}
signed main(){
	ios::sync_with_stdio(false);
	cin.tie(0);
	cout.tie(0);
	cin>>n>>q;
	for(int i=1;i<n;i++){
		int x,y,z;
		cin>>x>>y>>z;
		k[x].push_back({y,z});
		k[y].push_back({x,z});
	}
	dfs(1,0);
	cout<<dp[1][q];
	return 0;
}
