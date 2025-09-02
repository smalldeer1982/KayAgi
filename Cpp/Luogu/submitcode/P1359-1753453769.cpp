#include<bits/stdc++.h>
using namespace std;
#define int long long
int n,a[205][205],dp[205];
signed main(){
	ios::sync_with_stdio(false);
	cin.tie(0);
	cout.tie(0);
	cin>>n;
	for(int i=1;i<=n;i++){
		for(int j=i+1;j<=n;j++){
			cin>>a[i][j];
		}
	}
	memset(dp,0x3f3f3f,sizeof(dp));
	dp[n]=0;
	for(int i=n-1;i>=1;i--){
		for(int j=i+1;j<=n;j++){
			dp[i]=min(dp[i],dp[j]+a[i][j]);
		}
	}
	cout<<dp[1];
	return 0;
}
