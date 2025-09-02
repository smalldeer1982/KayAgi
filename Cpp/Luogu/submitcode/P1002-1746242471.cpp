#include<bits/stdc++.h>
using namespace std;
long long n,m,mx,my,vis[25][25],dp[25][25];
int dx[10]={0,-2,-2,-1,-1,1,1,2,2};
int dy[10]={0,-1,1,-2,2,-2,2,-1,1};
int main(){
	cin>>n>>m>>mx>>my;
	mx+=1,my+=1;
	n+=1,m+=1;
	for(int i=0;i<=8;i++){
		vis[mx+dx[i]][my+dy[i]]=1;
	}
    dp[1][1]=1;
    for(int i=1;i<=n;i++){
        for(int j=1;j<=m;j++){
        	if(i==1&&j==1){
				continue;
			}
        	if(vis[i][j]==0){
				dp[i][j]=dp[i-1][j]+dp[i][j-1];
			}
        }
    }
    cout<<dp[n][m];
	return 0;
}
