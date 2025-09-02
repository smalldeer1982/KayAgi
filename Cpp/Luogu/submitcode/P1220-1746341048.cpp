#include<bits/stdc++.h>
using namespace std;
int n,c,a[55],b[55],dp[55][55][3],x[55];
int main(){
	cin>>n>>c;
	for(int i=1;i<=n;i++){
		cin>>a[i]>>b[i];
		x[i]=x[i-1]+b[i];
	}
	memset(dp,0x3f3f3f,sizeof(dp));
	dp[c][c][0]=dp[c][c][1]=0;
	for(int len=2;len<=n;len++){
		for(int i=1;i<=n-len+1;i++){
			int j=i+len-1;
			dp[i][j][0]=min(dp[i+1][j][0]+(a[i+1]-a[i])*(x[n]-(x[j]-x[i])),dp[i+1][j][1]+(a[j]-a[i])*(x[n]-(x[j]-x[i])));
			dp[i][j][1]=min(dp[i][j-1][0]+(a[j]-a[i])*(x[n]-(x[j-1]-x[i-1])),dp[i][j-1][1]+(a[j]-a[j-1])*(x[n]-(x[j-1]-x[i-1])));
		}
	}
	cout<<min(dp[1][n][0],dp[1][n][1]);
	return 0;    
}
