#include<bits/stdc++.h>
using namespace std;
#define int long long
int n,m,a[3505],b[3505],dp[13005];
signed main(){
	ios::sync_with_stdio(false);
	cin.tie(0);
	cout.tie(0);
	cin>>n>>m;
	for(int i=1;i<=n;i++){
		cin>>a[i]>>b[i];
	}
	for(int i=1;i<=n;i++){
		for(int j=m;j>=a[i];j--){
			dp[j]=max(dp[j],dp[j-a[i]]+b[i]);
		}
	}
	int ans=0;
	for(int i=1;i<=m;i++){
		ans=max(dp[i],ans);
	}
	cout<<ans;
	return 0;
}
