#include<bits/stdc++.h>
using namespace std;
int n,a[205],q[205];
int dp[205][205];
int minn=INT_MAX,maxx=-1;
int main(){
	cin>>n;
	for(int i=1;i<=n;i++){
		cin>>a[i];
		a[i+n]=a[i];
	}
	for(int i=1;i<=2*n;i++){
		q[i]=q[i-1]+a[i];
	}
	memset(dp,0x3f3f3f,sizeof(dp));
	for(int i=1;i<=2*n;i++){
		dp[i][i]=0;
	}
	for(int len=2;len<=n;len++){
		for(int i=1;i<=2*n;i++){
			int j=i+len-1;
			if(j>2*n){
				break;
			}
			for(int k=i;k<j;k++){
				dp[i][j]=min(dp[i][j],dp[i][k]+dp[k+1][j]+q[j]-q[i-1]);
			}
		}
	}
	for(int i=1;i<=n;i++){
		minn=min(dp[i][n+i-1],minn);
	}
	cout<<minn<<endl;
	memset(dp,0,sizeof(dp));
	for(int i=1;i<=2*n;i++){
		dp[i][i]=0;
	}
	for(int len=2;len<=n;len++){
		for(int i=1;i<=2*n;i++){
			int j=i+len-1;
			if(j>2*n){
				break;
			}
			for(int k=i;k<j;k++){
				dp[i][j]=max(dp[i][j],dp[i][k]+dp[k+1][j]+q[j]-q[i-1]);
			}
		}
	}
	for(int i=1;i<=n;i++){
		maxx=max(dp[i][n+i-1],maxx);
	}
	cout<<maxx<<endl;
	return 0;
}