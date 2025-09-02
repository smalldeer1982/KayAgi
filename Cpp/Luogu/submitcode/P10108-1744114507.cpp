#include<bits/stdc++.h>
using namespace std;
int n,m,a[105],b[20005],dp[20005];
int maxm=-1;
int main(){
	cin>>n>>m;
	for(int i=0;i<=m-1;i++){
		cin>>a[i];
		maxm=max(maxm,a[i]);
	}
	for(int i=0;i<=n-1;i++){
		cin>>b[i];
	}
	for(int i=0;i<=n*2;i++){
		dp[i]=-1e9-5;
	}
	dp[0]=0;
	int ans=-1e9-5;
	for(int i=0;i<=n-1;i++){
		for(int j=0;j<=m-1;j++){
			if(i+a[j]>=n){
				ans=max(ans,dp[i]+b[i]);
			}
			dp[i+a[j]]=max(dp[i]+b[i],dp[i+a[j]]);
		}
	}
	cout<<ans;
	return 0;
}
