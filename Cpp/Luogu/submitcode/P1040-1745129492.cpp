#include<bits/stdc++.h>
using namespace std;
long long n,a[35],dp[35][35];
int solve(int l,int r){
	if(l>r){
		return dp[l][r]=1;
	}
	if(l==r){
		return dp[l][r]=a[l];
	}
	if(dp[l][r]>0){
		return dp[l][r];
	}
	for(int k=l;k<=r;k++){
		dp[l][r]=max(dp[l][r],solve(l,k-1)*solve(k+1,r)+a[k]);
	}
	return dp[l][r];
}
void dfs(int l,int r){
	if(l>r){
		return;
	}
	if(l==r){
		cout<<l<<" ";
		return;
	}
	for(int k=l;k<=r;k++){
		if(dp[l][r]==dp[l][k-1]*dp[k+1][r]+a[k]){
			cout<<k<<" ";
			dfs(l,k-1);
			dfs(k+1,r);
			break;
		}
	}
}
int main(){
	cin>>n;
	for(int i=1;i<=n;i++){
		cin>>a[i];
	}
	cout<<solve(1,n)<<endl;
	dfs(1,n);
	return 0;
}
