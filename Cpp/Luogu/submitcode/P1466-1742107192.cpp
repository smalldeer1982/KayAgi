#include<bits/stdc++.h>
using namespace std;
long long n,t,dp[45005];
int main(){
	cin>>n;
	t=(1+n)*n/2;
	if(t%2){
		cout<<0;
		return 0;
	}
	dp[0]=1;
	for(int i=1;i<=n;i++){
		for(int j=t/2;j>=i;j--){
			dp[j]=dp[j]+dp[j-i];
		}
	}
	cout<<dp[t/2]/2;
	return 0;
}
