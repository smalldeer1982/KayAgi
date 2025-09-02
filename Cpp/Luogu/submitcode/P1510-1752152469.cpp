#include<bits/stdc++.h>
using namespace std;
#define int long long
int v,n,c,dp[50005],k[10005],m[10005];
signed main(){
	ios::sync_with_stdio(false);
	cin.tie(0);
	cout.tie(0);
	cin>>v>>n>>c;
	for(int i=1;i<=n;i++){
		cin>>k[i]>>m[i];
	}
	for(int i=1;i<=n;i++){
		for(int j=c;j>=m[i];j--){
			dp[j]=max(dp[j],dp[j-m[i]]+k[i]);
		}
	}
	for(int i=1;i<=c;i++){
		if(dp[i]>=v){
			cout<<c-i;
			return 0;
		}
	}
	cout<<"Impossible";
	return 0;
}
