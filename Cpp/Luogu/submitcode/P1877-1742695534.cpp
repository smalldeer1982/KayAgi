#include<bits/stdc++.h>
using namespace std;
int n,bl,ml,a[55],dp[1005][1005],maxx=-1;
int main(){
	cin>>n>>bl>>ml;
	for(int i=1;i<=n;i++){
		cin>>a[i];
	}
	dp[0][bl]=1;
	for(int i=1;i<=n;i++){
		for(int j=0;j<=ml;j++){
			if(dp[i-1][j]&&j+a[i]<=ml){
				dp[i][j+a[i]]=1;
			}
			if(dp[i-1][j]&&j-a[i]>=0){
				dp[i][j-a[i]]=1;
			}
		}
	}
	bool flag=0;
	for(int i=ml;i>=0;i--){
		if(dp[n][i]==1){
			cout<<i;
			flag=1;
			break;
		}
	}
	if(flag==0){
		cout<<-1;
	}
	return 0;
}
