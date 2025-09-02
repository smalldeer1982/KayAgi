#include<bits/stdc++.h>
using namespace std;
long long n,a[1005],dp[100005],cnt=0;
int main(){
	cin>>n;
	for(int i=1;i<=sqrt(n);i++){
		a[i]=i*i;
	}
	for(int i=1;i<=n;i++){
		dp[i]=INT_MAX;
	}
	for(int i=1;i<=sqrt(n);i++){
		for(int j=a[i];j<=n;j++){
			dp[j]=min(dp[j],dp[j-a[i]]+1);
		}
	}
	cout<<dp[n];
	return 0;
}
