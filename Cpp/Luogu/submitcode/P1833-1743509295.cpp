#include<bits/stdc++.h>
using namespace std;
int t1,t2,t3,t4;
int n,m,w[10005],v[10005],p[10005];
int dp[1005];
char c;
int main(){
	cin>>t1>>c>>t2>>t3>>c>>t4>>n;
	m=60*(t3-t1)+t4-t2;
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