#include<bits/stdc++.h>
using namespace std;

int n,m,a[105],b[20005],dp[20005];

int main(){
	cin>>n>>m;
	for(int i=0;i<m;i++){
		cin>>a[i];
	}
	for(int i=0;i<n;i++){
		cin>>b[i];
	}
	for(int i=0;i<=n;i++){
		dp[i]=-1e9-5;
	}
	dp[0]=0;
	int ans=-1e9-5;

	for(int i=0;i<n;i++){
		for(int j=0;j<m;j++){
			if(i+a[j]>=n){
				ans=max(ans,dp[i]+b[i]);  // 到达终点，记录答案
			}else{
				dp[i+a[j]]=max(dp[i+a[j]],dp[i]+b[i]); // 更新下一关
			}
		}
	}

	cout<<ans;
	return 0;
}
