#include<bits/stdc++.h>
using namespace std;
#define int long long 
int n,a[1005];
int dp[1005],divi[1005];
void solve(){
	for(int i=1;i<=1000;i++){
		for(int j=1;j<=1000;j++){
			if(i%j==0){
				divi[i]+=j;		
			}
		}
	}
	for(int i=1;i<=1000;i++){
		divi[i]-=i;
	}
}
signed main(){
	ios::sync_with_stdio(false);
	cin.tie(0);
	cout.tie(0);
	solve();
	cin>>n;
	for(int i=1;i<=n;i++){
		for(int j=n;j>=i;j--){
			dp[j]=max(dp[j],dp[j-i]+divi[i]);
		}
	}
	cout<<dp[n];
	return 0;
}
