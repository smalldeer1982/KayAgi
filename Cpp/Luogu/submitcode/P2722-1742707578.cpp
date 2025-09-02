#include<bits/stdc++.h>
using namespace std;
int n,m,v[10005],w[10005],dp[10005];
int main(){
	cin>>m>>n;
	for(int i=1;i<=n;i++){
		cin>>v[i]>>w[i];
	}
	for(int i=1;i<=n;i++){
		for(int j=m;j>=0;j--){
			for(int k=0;k<=j/w[i];k++){
				dp[j]=max(dp[j],dp[j-k*w[i]]+k*v[i]);
			}
		}
	}
	cout<<dp[m];
	return 0;
}
