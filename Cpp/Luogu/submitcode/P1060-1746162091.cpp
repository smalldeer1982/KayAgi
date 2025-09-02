#include<bits/stdc++.h>
using namespace std;
int m,n,v[35],w[35],sum[35];
int dp[35][30005];
int main(){
	cin>>m>>n;
	for(int i=1;i<=n;i++){
		cin>>v[i]>>w[i];
		sum[i]=v[i]*w[i];
	}
	for(int i=1;i<=n;i++){
		for(int j=m;j>=1;j--){
			if(j>=v[i]){
				dp[i][j]=max(dp[i-1][j],dp[i-1][j-v[i]]+sum[i]);
			}
			else{
				dp[i][j]=dp[i-1][j];
			}
		}
	}
	cout<<dp[n][m];
	return 0;
}
