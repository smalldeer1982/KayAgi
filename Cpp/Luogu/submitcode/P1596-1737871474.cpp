#include<bits/stdc++.h>
using namespace std;
int n,m,vis[205][205],cnt=0;
char a[205][205];
int dx[10]={0,0,1,-1,1,1,-1,-1};
int dy[10]={1,-1,0,0,1,-1,1,-1};
void dfs(int x,int y){
	for(int i=0;i<8;i++){
		int fx=dx[i]+x;
		int fy=dy[i]+y;
		if(fx>=1&&fx<=n&&fy>=1&&fy<=m&&vis[fx][fy]==0&&a[x][y]=='W'){
			vis[fx][fy]=1;
			dfs(fx,fy);
		}
	}
}
int main(){
	cin>>n>>m;
	for(int i=1;i<=n;i++){
		for(int j=1;j<=m;j++){
			cin>>a[i][j];
		}
	}
	for(int i=1;i<=n;i++){
		for(int j=1;j<=m;j++){
			if(a[i][j]=='W'&&vis[i][j]==0){
				dfs(i,j);
				cnt+=1;
			}
		}
	}
	cout<<cnt;
	return 0;
}