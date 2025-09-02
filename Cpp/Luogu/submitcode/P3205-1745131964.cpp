#include<bits/stdc++.h>
using namespace std;
long long n,a[1005],dp[1005][1005][3];
int main(){
	cin>>n;
	for(int i=1;i<=n;i++){
		cin>>a[i];
	}
	for(int i=1;i<=n;i++){
		dp[i][i][0]=1;
	}
	for(int len=2;len<=n;len++){
		for(int i=1;i<=n;i++){
			int j=i+len-1;
			if(j>n){
				break;
			}
			if(a[i]<a[i+1]){
				dp[i][j][0]+=dp[i+1][j][0];
			}
			if(a[i]<a[j]){
				dp[i][j][0]+=dp[i+1][j][1];
			}
			if(a[j]>a[j-1]){
				dp[i][j][1]+=dp[i][j-1][1];
			}
			if(a[j]>a[i]){
				dp[i][j][1]+=dp[i][j-1][0];
			}
			dp[i][j][0]%=19650827;
			dp[i][j][1]%=19650827;
		}
	}
	cout<<(dp[1][n][0]+dp[1][n][1])%19650827;
	return 0;
}
