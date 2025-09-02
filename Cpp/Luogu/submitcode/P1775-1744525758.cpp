#include<bits/stdc++.h>
using namespace std;
int n,a[305],q[305];
int dp[305][305];
int main(){
	cin>>n;
	for(int i=1;i<=n;i++){
		cin>>a[i];
		q[i]=q[i-1]+a[i];
	}
	memset(dp,0x3f3f3f,sizeof(dp));
	for(int i=1;i<=n;i++){
		dp[i][i]=0;
	}
	for(int len=2;len<=n;len++){
		for(int i=1;i<=n;i++){
			int j=i+len-1;
			if(j>n){
				break;
			}
			for(int k=i;k<j;k++){
				dp[i][j]=min(dp[i][j],dp[i][k]+dp[k+1][j]+q[j]-q[i-1]);
			}
		}
	}
	cout<<dp[1][n];
	return 0;
}
