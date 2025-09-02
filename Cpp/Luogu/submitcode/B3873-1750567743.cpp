#include<bits/stdc++.h>
using namespace std;
#define int long long
const int maxn=2e6+5;
int n,l,a[maxn],b[maxn];
int dp[maxn],sum=0;
signed main(){
	ios::sync_with_stdio(false);
	cin.tie(0);
	cout.tie(0);
	memset(dp,0x3f3f3f,sizeof(dp));
	cin>>n>>l;
	for(int i=1;i<=n;i++){
		cin>>a[i]>>b[i];
		sum+=b[i];
		b[i]=min(b[i],l);
	}
	if(sum<l){
		cout<<"no solution";
		return 0;
	}
	dp[0]=0;
	for(int i=1;i<=n;i++){
		for(int j=2*l;j>=b[i];j--){
			dp[j]=min(dp[j-b[i]]+a[i],dp[j]);
		}
	}
	int ans=0x3f3f3f;
	for(int i=l;i<=2*l;i++){
		ans=min(ans,dp[i]);
	}
	if(ans==0x3f3f3f){
		cout<<"no solution";
		return 0;
	}
	cout<<ans;
	return 0;
}
