#include<bits/stdc++.h>
using namespace std;
int n,l,a[250],dp[250][250];
int main(){
	cin>>n;
	for(int i=1;i<=n;i++){
		cin>>a[i];
	}
	memset(dp,-1,sizeof(dp));
	for(int i=1;i<=n;i++){
		dp[i][i]=a[i];
	}
	for(int len=2;len<=n;len++){
		for(int i=1;i<=n-len+1;i++){
			int j=i+len-1;
			if(j>n){
				break;
			}
			for(int k=i;k<=j;k++){
				if(dp[i][k]==dp[k+1][j]&&dp[i][k]!=-1&&dp[k+1][j]!=-1){
					dp[i][j]=dp[i][k]+1;
				}
			}
		}
	}
	int ans=0;
	for(int i=1;i<=n;i++){
		for(int j=1;j<=n;j++){
			ans=max(ans,dp[i][j]);
		}
	}
	cout<<ans;
	return 0;    
}
