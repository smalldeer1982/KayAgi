#include<bits/stdc++.h>
using namespace std;
int x,y,n,dp[55][405][405];
int h[55],t[55],w[55];
int main(){
	cin>>x>>y;
	cin>>n;
	for(int i=1;i<=n;i++){
		cin>>h[i]>>t[i]>>w[i];
	}
	for(int i=1;i<=n;i++){
		for(int j=1;j<=x;j++){
			for(int k=1;k<=y;k++){
				dp[i][j][k]=dp[i-1][j][k];
				if(j>=h[i]&&k>=t[i]){
					dp[i][j][k]=max(dp[i][j][k],w[i]+dp[i-1][j-h[i]][k-t[i]]);
				}			
			}
		}
	}
	cout<<dp[n][x][y];
	return 0;
}