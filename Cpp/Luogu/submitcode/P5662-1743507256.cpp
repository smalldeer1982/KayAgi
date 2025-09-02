#include<bits/stdc++.h>
using namespace std;
int t,n,m,p[105][105],dp[10005],ans;
int main(){
	cin>>t>>n>>m;
	ans=m;
	for(int i=1;i<=t;i++){
		for(int j=1;j<=n;j++){
			cin>>p[i][j];
		}
	}
	for(int i=1;i<=t;i++){
		memset(dp,0,sizeof(dp));
		dp[ans]=ans;
		for(int j=1;j<=n;j++){
			for(int k=ans;k>=p[i][j];k--){
				dp[k-p[i][j]]=max(dp[k-p[i][j]],dp[k]+(p[i+1][j]-p[i][j]));
			}
		}
		int maxn=-1;
		for(int j=0;j<=ans;j++){
			maxn=max(maxn,dp[j]);
		}
		ans=maxn;
	}
	cout<<ans;
	return 0;
}
