#include<bits/stdc++.h>
using namespace std;
#define int long long
int n,m,t,a[105],b[105],dp[205][205];
signed main(){
	ios::sync_with_stdio(false);
	cin.tie(0);
	cout.tie(0);
	cin>>n>>m>>t;
	for(int i=1;i<=n;i++){
		cin>>a[i]>>b[i];
	}
	for(int i=1;i<=n;i++){
		for(int j=m;j>=a[i];j--){
			for(int k=t;k>=b[i];k--){
				dp[j][k]=max(dp[j][k],dp[j-a[i]][k-b[i]]+1);
			}
		}
	}
	cout<<dp[m][t];
	return 0;
}
