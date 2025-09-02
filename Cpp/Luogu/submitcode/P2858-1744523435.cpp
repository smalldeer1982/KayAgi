#include<bits/stdc++.h>
using namespace std;
int n,a[2005];
int dp[2005][2005];
int solve(int l,int r,int k){
	if(dp[l][r]>0){
		return dp[l][r];
	}
	if(l==r){
		return a[l]*k;
	}
	else{
		return dp[l][r]=max(solve(l,r-1,k+1)+a[r]*k,solve(l+1,r,k+1)+a[l]*k);
	}
}
int main(){
	cin>>n;
	for(int i=1;i<=n;i++){
		cin>>a[i];
	}
	cout<<solve(1,n,1);
	return 0;
}
