#include<bits/stdc++.h>
using namespace std;
int m,n,dp[5][50005];
int v[5005];
int main(){
	cin>>m>>n;
	for(int i=1;i<=n;i++){
		cin>>v[i];
	}
	for(int i=1;i<=n;i++){
		for(int j=1;j<=m;j++){
			if(j>=v[i]){
				dp[i%2][j]=max(dp[(i-1)%2][j],v[i]+dp[(i-1)%2][j-v[i]]);
			}
			else{
				dp[i%2][j]=dp[(i-1)%2][j];
			}
		}
	}
	cout<<dp[n%2][m];
	return 0;
}