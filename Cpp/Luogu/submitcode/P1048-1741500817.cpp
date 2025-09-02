#include<bits/stdc++.h>
using namespace std;
int m,n,dp[105][1005];
int v[105],w[105];
int main(){
	cin>>m>>n;
	for(int i=1;i<=n;i++){
		cin>>v[i]>>w[i];
	}
	for(int i=1;i<=n;i++){
		for(int j=1;j<=m;j++){
			if(j>=v[i]){
				dp[i][j]=max(dp[i-1][j],w[i]+dp[i-1][j-v[i]]);
			}
			else{
				dp[i][j]=dp[i-1][j];
			}
		}
	}
	cout<<dp[n][m];
	return 0;
}