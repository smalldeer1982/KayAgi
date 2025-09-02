#include<bits/stdc++.h>
using namespace std;
string s;
int dp[1005][1005];
int solve(int l,int r){
	if(dp[l][r]!=0){
		return dp[l][r];
	}
	if(l>=r){
		return 0;
	}
	if(s[l]==s[r]){
		return dp[l][r]=solve(l+1,r-1);
	}
	else{
		return dp[l][r]=min(solve(l,r-1),solve(l+1,r))+1;
	}
}
int main(){
	cin>>s;
	cout<<solve(0,s.size()-1);
	return 0;
}
