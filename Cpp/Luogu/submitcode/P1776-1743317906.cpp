#include<bits/stdc++.h>
using namespace std;
int n,W,w[100005],v[100005],m[100005],dp[100005];
int main(){
	cin>>n>>W;
	for(int i=1;i<=n;i++){
		cin>>v[i]>>w[i]>>m[i];
	}
	for(int i=1;i<=n;i++){
		for(int k=1;k<=m[i];k*=2){
			m[i]-=k;
			for(int j=W;j>=k*w[i];j--){
				dp[j]=max(dp[j],dp[j-k*w[i]]+k*v[i]);
			}
		}
		if(m[i]>0){
			for(int j=W;j>=m[i]*w[i];j--){
				dp[j]=max(dp[j],dp[j-m[i]*w[i]]+v[i]*m[i]);
			}
		}
	}
	cout<<dp[W];
	return 0;
}
