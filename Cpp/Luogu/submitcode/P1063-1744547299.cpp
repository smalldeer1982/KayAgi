#include<bits/stdc++.h>
using namespace std;
int n,a[505];
int dp[505][505];
int maxx=0;
int main(){
	cin>>n;
	for(int i=1;i<=n;i++){
		cin>>a[i];
		a[i+n]=a[i];
	}
	for(int len=3;len<=n+1;len++){
		for(int i=1;i+len-1<=2*n;i++){
			int j=i+len-1;
			if(j>2*n){
				break;
			}
			for(int k=i+1;k<j;k++){
				dp[i][j]=max(dp[i][j],dp[i][k]+dp[k][j]+a[i]*a[j]*a[k]);
			}
		}
	}
	for(int i=1;i<=n;i++){
		maxx=max(dp[i][n+i],maxx);
	}
	cout<<maxx;
	return 0;
}
