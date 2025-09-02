#include<bits/stdc++.h>
using namespace std;
#define int long long
const int maxn=1e5+5;
int m,n,a[maxn],dp[maxn];
signed main(){
	ios::sync_with_stdio(false);
	cin.tie(0);
	cout.tie(0);
	memset(dp,0x3f3f3f,sizeof(dp));
	cin>>m;
	int n=sqrt(sqrt(m))+2;
	for(int i=1;i<=n;i++){
		a[i]=i*i*i*i;
	}
	dp[0]=0;
	for(int i=1;i<=n;i++){
		for(int j=a[i];j<=m;j++){
			dp[j]=min(dp[j],dp[j-a[i]]+1);
		}
	}
	cout<<dp[m];
	return 0;
}
