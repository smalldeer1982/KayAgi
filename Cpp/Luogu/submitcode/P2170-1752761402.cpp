#include<bits/stdc++.h>
using namespace std;
#define int long long
const int maxn=2e4+5;
int n,m,k,cnt=0;
int a[maxn],b[maxn],x[maxn],fa[maxn],dp[maxn];
void init(){
	for(int i=1;i<=20000;i++){
		fa[i]=i;
	}
}
int find(int x){
	return fa[x]==x?x:fa[x]=find(fa[x]);
}
void merge(int x,int y){
	int fx,fy;
	fx=find(x);
	fy=find(y);
	if(fx!=fy){
		fa[fy]=fx;
	}
}
signed main(){
	ios::sync_with_stdio(false);
	cin.tie(0);
	cout.tie(0);
	init();
	cin>>n>>m>>k;
	for(int i=1;i<=k;i++){
		cin>>a[i]>>b[i];
	}
	for(int i=1;i<=k;i++){
		if(a[i]>b[i]){
			swap(a[i],b[i]);
		}
		merge(a[i],b[i]);
	}
	for(int i=1;i<=k;i++){
		merge(a[i],b[i]);
	}
	for(int i=1;i<=n;i++){
		x[fa[i]]+=1;
	}
	for(int i=1;i<=n;i++){
		for(int j=n;j>=x[i];j--){
			dp[j]=max(dp[j],dp[j-x[i]]+x[i]);
		}
	}
	int sum=1e5+5,ans=1e5+5;
	for(int i=0;i<=n;i++){
		if(abs(dp[i]-m)==sum){
			ans=min(ans,dp[i]);
		}
		if(abs(dp[i]-m)<sum){
			sum=abs(dp[i]-m);
			ans=dp[i];
		}
	}
	cout<<ans;
	return 0;
}