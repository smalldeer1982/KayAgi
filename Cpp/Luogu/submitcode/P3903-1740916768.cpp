#include<bits/stdc++.h>
using namespace std;
int n,a[1005],dp[1005][2];
int main(){
	cin>>n;
	for(int i=1;i<=n;i++){
		cin>>a[i];
		dp[i][1]=1;
	}
	for(int i=1;i<=n;i++){
		for(int j=1;j<i;j++){
			if(a[i]<a[j]){
				dp[i][0]=max(dp[i][0],dp[j][1]+1);
			}
			if(a[i]>a[j]){
				dp[i][1]=max(dp[i][1],dp[j][0]+1);
			}
		}
	}
	int ans=0;
	for(int i=1;i<=n;i++){
		ans=max(max(dp[i][0],dp[i][1]),ans);
	}
	cout<<ans;
	return 0;
}