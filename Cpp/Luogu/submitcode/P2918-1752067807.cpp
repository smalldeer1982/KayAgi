#include<bits/stdc++.h>
using namespace std;
#define int long long
int n,m,dp[50005],v[105],w[105];
signed main(){
	ios::sync_with_stdio(false);
	cin.tie(0);
	cout.tie(0);
	cin>>n>>m;
	for(int i=1;i<=n;i++){
		cin>>v[i]>>w[i];
	}
	for(int i=1;i<=n;i++){
		for(int j=w[i];j<=50000;j++){
			dp[j]=max(dp[j],dp[j-w[i]]+v[i]);
		}
	}
	for(int i=1;i<=50000;i++){
		if(dp[i]>=m){
			cout<<i<<endl;
			return 0;
		}
	}
	return 0;
}
