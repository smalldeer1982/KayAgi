#include<bits/stdc++.h>
using namespace std;
#define int long long
int n,m,a[1005][1005];
int dp[1005][1005][3];
signed main(){
	ios::sync_with_stdio(false);
	cin.tie(0);
	cout.tie(0);
	cin>>n>>m;
	for(int i=1;i<=n;i++){
		for(int j=1;j<=m;j++){
			cin>>a[i][j];
		}
	}
	for(int i=0;i<=n;i++){
		for(int j=0;j<=m;j++){
			dp[i][j][0]=dp[i][j][1]=dp[i][j][2]=INT_MIN;
		}
	}
	dp[1][0][0]=0;
	for(int j=1;j<=m;j++){
		for(int i=1;i<=n;i++){
			dp[i][j][0]=max(dp[i][j-1][0],max(dp[i][j-1][1],dp[i][j-1][2]))+a[i][j];
		}
		for(int i=1;i<=n;i++){
			dp[i][j][1]=max(dp[i-1][j][0],dp[i-1][j][1])+a[i][j];
		}
		for(int i=n-1;i>=1;i--){
			dp[i][j][2]=max(dp[i+1][j][0],dp[i+1][j][2])+a[i][j];
		}
	}
	cout<<max(dp[n][m][0],dp[n][m][1]);
	return 0;
}
