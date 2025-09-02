#include<bits/stdc++.h>
using namespace std;
int n,m,a[105],c[105],dp[100005];
int main(){
	while(true){
		memset(dp,0,sizeof(dp));
		cin>>n>>m;
		if(n==0&&m==0){
			break;
		}
		for(int i=1;i<=n;i++){
			cin>>a[i];
		}
		for(int i=1;i<=n;i++){
			cin>>c[i];
		}
		for(int i=1;i<=n;i++){
			for(int k=1;k<=c[i];k*=2){
				c[i]-=k;
				for(int j=m;j>=k*a[i];j--){
					dp[j]=max(dp[j],dp[j-k*a[i]]+k*a[i]);
				}
			}
			if(c[i]>0){
				for(int j=m;j>=c[i]*a[i];j--){
					dp[j]=max(dp[j],dp[j-c[i]*a[i]]+a[i]*c[i]);
				}
			}
		}
		int ans=0;
		for(int i=1;i<=m;i++){
			if(dp[i]!=dp[i-1]){
				ans+=1;
			}
		}	
		cout<<ans<<endl;
	}
	return 0;
}
