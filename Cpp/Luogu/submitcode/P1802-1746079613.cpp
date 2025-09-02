#include<bits/stdc++.h>
using namespace std;
long long n,x,a[1005],b[1005],c[1005];
long long dp[1005];
int main(){
	cin>>n>>x;
	for(int i=1;i<=n;i++){
		cin>>a[i]>>b[i]>>c[i];
	}
	for(int i=1;i<=n;i++){
		for(int j=x;j>=c[i];j--){
			dp[j]=max(dp[j]+a[i],dp[j-c[i]]+b[i]);
		}
		for(int j=c[i]-1;j>=0;j--){
			dp[j]+=a[i];
		}
	}
	cout<<5*dp[x];
	return 0;
}
