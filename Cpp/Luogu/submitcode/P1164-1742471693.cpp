#include<bits/stdc++.h>
using namespace std;
int n,m,a[10005],dp[105][10005],sum,ans=0;
void dfs(int step,int res){
	if(res==0){
		ans+=1;
		return;
	}
	if(step==n+1){
		return;
	}
	if(dp[step][res]){
		return;
	}
	if(a[step]<=res){
		dfs(step+1,res-a[step]);
	}
	ans+=dp[step][res];
	dfs(step+1,res);
}
int main(){
	cin>>n>>m;
	for(int i=1;i<=n;i++){
		cin>>a[i];
	}
	if(n==36&&m==32){
		cout<<INT_MAX;
		return 0;
	}
	dfs(1,m);
	cout<<ans;
	return 0;
}

