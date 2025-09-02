#include<bits/stdc++.h>
using namespace std;
#define int long long
const int mod=1e6+7;
int n,m,a[105],dp[105][105];
signed main(){
	ios::sync_with_stdio(false);
	cin.tie(0);
	cout.tie(0);
	cin>>n>>m;
	for(int i=1;i<=n;i++){
		cin>>a[i];
	}
	dp[0][0]=1;
	for(int i=1;i<=n;i++){
		for(int j=0;j<=m;j++){
			for(int k=0;k<=min(a[i],j);k++){
				dp[i][j]=(dp[i][j]+dp[i-1][j-k])%mod;
			}
		}
	}
	cout<<dp[n][m];
	return 0;
}
