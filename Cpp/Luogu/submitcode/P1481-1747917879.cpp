#include<bits/stdc++.h>
#include<string.h>
using namespace std;
int n,dp[2005];
string s[2005];
int main(){
	cin>>n;
	for(int i=1;i<=n;i++){
		cin>>s[i];
	}
	for(int i=1;i<=n;i++){
		dp[i]=1;
		for(int j=1;j<i;j++){
			if(s[j]==s[i].substr(0,s[j].size())){
				dp[i]=max(dp[j]+1,dp[i]);
			}
		}
	}
	int ans=0;
	for(int i=1;i<=n;i++){
		ans=max(ans,dp[i]);
	}
	cout<<ans;
	return 0;
}
