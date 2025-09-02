#include<bits/stdc++.h>
using namespace std;
#define int long long
int n,v,a[505],dp[45005];
signed main(){
	ios::sync_with_stdio(false);
	cin.tie(0);
	cout.tie(0);
	cin>>v>>n;
	for(int i=1;i<=n;i++){
		cin>>a[i];
	}
	for(int i=1;i<=n;i++){
		for(int j=v;j>=a[i];j--){
			if(dp[j]<dp[j-a[i]]+a[i]){
				dp[j]=max(dp[j],dp[j-a[i]]+a[i]);
			}
		}
	}
	cout<<dp[v];
	return 0;
}
