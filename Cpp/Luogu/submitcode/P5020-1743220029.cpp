#include<bits/stdc++.h>
using namespace std;
int t,n,a[105],dp[25005],ans;
int main(){
	cin>>t;
	for(int i=1;i<=t;i++){
		cin>>n;
		for(int j=1;j<=n;j++){
			cin>>a[j];
		}
		sort(a+1,a+n+1);
		memset(dp,0,sizeof(dp));
		dp[0]=1;
		for(int j=1;j<=n;j++){
			for(int k=a[j];k<=a[n];k++){
				dp[k]+=dp[k-a[j]];
			}
		}
		ans=0;
		for(int j=1;j<=n;j++){
			if(dp[a[j]]==1){
				ans+=1;
			}
		}
		cout<<ans<<endl;
	}
	return 0;
}
