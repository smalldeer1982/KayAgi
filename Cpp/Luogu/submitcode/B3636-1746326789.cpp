#include<bits/stdc++.h>
using namespace std;
int n,dp[1000005];
int main(){
	cin>>n;
	dp[1]=0;
	dp[2]=1;
	for(int i=1;i<=n;i++){
		if(i%2==1){
			dp[i]=dp[i-1]+1;
		}
		else{
			dp[i]=dp[i/2]+1;
		}	
	}
	cout<<dp[n]-1;
	return 0;
}
