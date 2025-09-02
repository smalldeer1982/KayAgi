#include<bits/stdc++.h>
using namespace std;
int n,a[15][15],dp[15][15][15][15];
int main(){
	cin>>n;
	while(true){
		int x,y,k;
		cin>>x>>y>>k;
		if(x==0&&y==0&&k==0){
			break;
		}
		a[x][y]=k;
	}
	for(int x=1;x<=n;x++){
		for(int y=1;y<=n;y++){
			for(int x2=1;x2<=n;x2++){
				for(int y2=1;y2<=n;y2++){
					dp[x][y][x2][y2]=a[x][y]+a[x2][y2]+max(dp[x-1][y][x2-1][y2],max(dp[x-1][y][x2][y2-1],max(dp[x][y-1][x2-1][y2],dp[x][y-1][x2][y2-1])));
					if(x==x2&&y==y2){
						dp[x][y][x2][y2]-=a[x][y];
					}
				}
			}
		}
	}
	cout<<dp[n][n][n][n];
	return 0;
}
