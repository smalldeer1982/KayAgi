#include<bits/stdc++.h>
using namespace std;
#define int long long
int n,dp[40005];
struct node{
	int h,b,c;
}a[405];
bool cmp(node x,node y){
	return x.b<y.b;
}
signed main(){
	ios::sync_with_stdio(false);
	cin.tie(0);
	cout.tie(0);
	cin>>n;
	for(int i=1;i<=n;i++){
		cin>>a[i].h>>a[i].b>>a[i].c;
	}
	sort(a+1,a+n+1,cmp);
	for(int i=1;i<=n;i++){
		for(int k=1;k<=a[i].c;k++){
			for(int j=a[i].b;j>=a[i].h;j--){
				dp[j]=max(dp[j],dp[j-a[i].h]+a[i].h);
			}
		}
	}
	int ans=0;
	for(int i=1;i<=a[n].b;i++){
		ans=max(dp[i],ans);
	}
	cout<<ans;
	return 0;
}
