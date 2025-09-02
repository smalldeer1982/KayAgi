#include<bits/stdc++.h>
using namespace std;
#define int long long
const int maxn=1e5+5;
int n,k,l,r;
int a[maxn],sum[maxn];
int dp[maxn][2],q[maxn];
signed main(){
	ios::sync_with_stdio(false);
	cin.tie(0);
	cout.tie(0);
	cin>>n>>k;
	for(int i=1;i<=n;i++){
		cin>>a[i];
		sum[i]=sum[i-1]+a[i];
	}
	l=1,r=1;
	for(int i=1;i<=n;i++){
		dp[i][0]=max(dp[i-1][0],dp[i-1][1]);
		while(q[l]<i-k&&l<=r){
			l++;
		}
		dp[i][1]=dp[q[l]][0]-sum[q[l]]+sum[i];
		while(dp[i][0]-sum[i]>dp[q[r]][0]-sum[q[r]]&&l<=r){
			r--;
		}
		q[++r]=i;
	}
	cout<<max(dp[n][0],dp[n][1]);
	return 0;
}
