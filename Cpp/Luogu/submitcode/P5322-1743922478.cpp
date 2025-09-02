#include<bits/stdc++.h>
using namespace std;
int s,n,m,a[105][105],dp[20005];
int main(){
	cin>>s>>n>>m;
	for(int i=1;i<=s;i++){
		for(int j=1;j<=n;j++){
			cin>>a[j][i];
		}
	}
	for(int i=1;i<=n;i++){
		sort(a[i]+1,a[i]+s+1);
	}
	for(int i=1;i<=n;i++){
		for(int j=m;j>=0;j--){
			for(int k=1;k<=s;k++){
				if(j>a[i][k]*2){
					dp[j]=max(dp[j-a[i][k]*2-1]+k*i,dp[j]);
				}
			}
		}
	}
	cout<<dp[m];
	return 0;
}
