#include<bits/stdc++.h>
using namespace std;
int n,dp[1000005];
int main(){
	cin>>n;
	dp[1]=1,dp[5]=1,dp[11]=1;
	for(int i=1;i<=n;i++){
		if(i>=11){
			dp[i]=min(dp[i-11]+1,min(dp[i-5]+1,dp[i-1]+1));
		}
		else if(i>=5){
			dp[i]=min(dp[i-5]+1,dp[i-1]+1);
		}
		else{
			dp[i]=dp[i-1]+1;
		}
	}
	cout<<dp[n];
	return 0;
}
