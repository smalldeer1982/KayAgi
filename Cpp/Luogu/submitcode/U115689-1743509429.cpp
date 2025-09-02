#include<bits/stdc++.h>
using namespace std;
int n,m,w[35],v[35],p[35];
int dp[205];
int main(){
	cin>>m>>n;
	for(int i=1;i<=n;i++){
		cin>>w[i]>>v[i]>>p[i];
	}
	for(int i=1;i<=n;i++){
		if(p[i]==0){
			for(int j=w[i];j<=m;j++){
				dp[j]=max(dp[j],dp[j-w[i]]+v[i]);
			}
		}
		else{
			for(int k=1;k<=p[i];k*=2){
				p[i]-=k;
				for(int j=m;j>=k*w[i];j--){
					dp[j]=max(dp[j],dp[j-k*w[i]]+k*v[i]);
				}
			}
			if(p[i]>0){
				for(int j=m;j>=p[i]*w[i];j--){
					dp[j]=max(dp[j],dp[j-p[i]*w[i]]+p[i]*v[i]);
				}
			}
		}
	}
	cout<<dp[m];
	return 0;
}