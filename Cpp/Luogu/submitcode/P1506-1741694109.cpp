#include<bits/stdc++.h>
using namespace std;
int n,m;
char ch[505][505];
bool vis[505][505];
int dx[5]={0,0,1,-1};
int dy[5]={1,-1,0,0};
void dfs(int x,int y){
	if(vis[x][y]==true){
		return;
	} 
	vis[x][y]=true;
	for(int i=0;i<4;i++){
		int tx=x+dx[i];
		int ty=y+dy[i];
		if(tx<1||tx>n||ty<1||ty>m||ch[tx][ty]=='*' ) {
			continue;
		}
		dfs(tx,ty);
	}
}
int main(){
	cin>>n>>m;
	for(int i=1;i<=n;i++){
		for(int j=1;j<=m;j++){
			cin>>ch[i][j];
			if(ch[i][j]=='*') {
				vis[i][j]=true;
			}
		}
	}
	for(int j=1;j<=m;j++){
		if(vis[1][j]==false&&ch[1][j]=='0') {
			dfs(1,j);
		}
		if(vis[n][j]==false&&ch[n][j]=='0') {
			dfs(n,j);
		}
	}
	for(int i=1;i<=n;i++){
		if(vis[i][1]==false&&ch[i][1]=='0'){
			dfs(i,1);
		} 
		if(vis[i][m]==false&&ch[i][m]=='0') {
			dfs(i,m);
		}
	}
	int ans=0;
	for(int i=1;i<=n;i++){
		for(int j=1;j<=m;j++){
			if(vis[i][j]==false&&ch[i][j]=='0'){
				ans++;
			}
		}
	}
	cout<<ans;
	return 0;
}