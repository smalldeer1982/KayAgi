#include<bits/stdc++.h>
using namespace std;
int n,m,a[10005],ans=0,dp[105][10005];
int dfs(int step,int res){
    if(dp[step][res]>0){
	  	return dp[step][res];
	}
	if(a[step]>res){
		return 0;
	}
	if(a[step]==res){
		return 1;	
	}
	for(int i=step+1;i<=n;i++){
		dp[step][res]+=dfs(i,res-a[step]);
	}
	return dp[step][res];
}
int main(){
	cin>>n>>m;
	for(int i=1;i<=n;i++){
		cin>>a[i];
	}
	for(int i=1;i<=n;i++){
		ans+=dfs(i,m);
	}
	cout<<ans;
	return 0;
}
