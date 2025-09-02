#include<bits/stdc++.h>
using namespace std;
long long m,n,dp[10000005],v[10000005],w[10000005];
int main(){
	cin>>m>>n;
	for(int i=1;i<=n;i++){
		cin>>v[i]>>w[i];
	}
	for(int i=1;i<=n;i++){
		for(int j=1;j<=m;j++){
			if(j>=v[i]){
				dp[j]=max(dp[j],w[i]+dp[j-v[i]]);
			}
		}
	}
	cout<<dp[m];
	return 0;
}