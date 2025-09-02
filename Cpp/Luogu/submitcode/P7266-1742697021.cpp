#include<bits/stdc++.h>
using namespace std;
int n,a[205][205],dp[205][205][3],x[205],maxx=-1;
int main(){
    cin>>n;
    for(int i=1;i<=n;i++){
        for(int j=1;j<=i+n-1;j++){
            cin>>a[i][j];
            x[i]=max(x[i],a[i][j]);
        }
    }
    for(int i=n+1;i<=2*n-1;i++){
        for(int j=1;j<=2*n-1-(i-n);j++){
            cin>>a[i][j];
            x[i]=max(x[i],a[i][j]);
        }
    }
    for(int i=1;i<=n;i++) {
	    dp[1][i][0]=a[1][i];
	    dp[1][i][1]=x[1];
	}
    for(int i=2;i<=n;i++){
        for(int j=1;j<=n+i-1;j++){
            dp[i][j][0]=a[i][j]+max(dp[i-1][j][0],dp[i-1][j-1][0]);
            dp[i][j][1]=max(max(dp[i-1][j][0],dp[i-1][j-1][0])+x[i],max(dp[i-1][j][1],dp[i-1][j-1][1])+a[i][j]);
        }
    }
    for(int i=n+1;i<=n*2-1;i++){
        for(int j=1;j<=2*n-1-(i-n);j++){
        	dp[i][j][0]=a[i][j]+max(dp[i-1][j][0],dp[i-1][j+1][0]);
            dp[i][j][1]=max(max(dp[i-1][j][0],dp[i-1][j+1][0])+x[i],max(dp[i-1][j][1],dp[i-1][j+1][1])+a[i][j]);
        }
    }
    for(int i=1;i<=n;i++){
        maxx=max(maxx,dp[n*2-1][i][1]);
    }
    cout<<maxx;
    return 0;
}