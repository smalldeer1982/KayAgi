#include<bits/stdc++.h>
using namespace std;
#define int long long
int t,dp[105][50005],v[50005],c[50005];
void init(){
	memset(dp,0,sizeof(dp));
}
void solve(){
	int n,p,q;
	init();
	cin>>n>>p>>q;
	for(int i=1;i<=n;i++){
		cin>>v[i]>>c[i];
	}
	for(int i=1;i<=n;i++){
		for(int j=1;j<=q;j++){
			dp[i][j]=dp[i-1][j];
			if(c[i]<=j){
				dp[i][j]=max(dp[i][j],dp[i-1][j-c[i]]+v[i]);
			}
		}
	}
	for(int i=1;i<=q;i++){
		if(dp[n][i]>=p){
			cout<<i<<endl;
			return;
		}
	}
	cout<<-1<<endl;
	return;
}
signed main(){
	ios::sync_with_stdio(false);
	cin.tie(0);
	cout.tie(0);
	cin>>t;
	while(t--){
		solve();
	}
	return 0;
}
