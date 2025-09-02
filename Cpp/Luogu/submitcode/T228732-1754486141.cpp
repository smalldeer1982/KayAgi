#include<bits/stdc++.h>
using namespace std;
#define int long long
const int maxn=1e5+5;
int n,k,l,r;
int a[maxn],dp[maxn];
int ans=2e9+5;
bool check(int x){
	if(x==0){
		int sum=0;
		for(int i=1;i<=n;i++){
			sum+=a[i];
		}
		if(sum<=k){
			return true;
		}
		return false;
	}
	x++;
	deque<int>q;
	q.push_back(0);
	for(int i=1;i<=n+1;i++){
		dp[i]=dp[q.front()]+a[i];
		while(!q.empty()&&q.front()<=i-x){
			q.pop_front();
		}
		while(!q.empty()&&dp[q.back()]>=dp[i]){
			q.pop_back();
		}
		q.push_back(i);
	}
	if(dp[n+1]<=k){
		return true;
	}
	return false;
}
signed main(){
	ios::sync_with_stdio(false);
	cin.tie(0);
	cout.tie(0);
	cin>>n>>k;
	for(int i=1;i<=n;i++){
		cin>>a[i];
	}
	a[0]=0,a[n+1]=0;
	int L=1,R=n;
	while(L<=R){
		int mid=(L+R)/2;
		if(check(mid)){
			ans=min(ans,mid);
			R=mid-1;	
		}
		else{
			L=mid+1;
		}
	}
	cout<<ans<<endl;
	return 0;
}
