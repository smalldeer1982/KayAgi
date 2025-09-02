#include<bits/stdc++.h>
using namespace std;
int n,m,vis[1005][1005],b[1005][1005],c[1000005],cnt=0;
char a[1005][1005];
int dx[5]={0,0,1,-1};
int dy[5]={1,-1,0,0};
void dfs(int x,int y){
	if(x<1||x>n||y<1||y>n||a[x][y]=='.'){
		return;
	}
	a[x][y]='.';
	for(int i=0;i<4;i++){
		dfs(x+dx[i],y+dy[i]);
	}
}
int main(){
	cin>>n;
	for(int i=1;i<=n;i++){
		for(int j=1;j<=n;j++){
			cin>>a[i][j];
		}
	}
	for(int i=1;i<=n;i++){
		for(int j=1;j<=n;j++){
			if(a[i][j]=='#'&&a[i-1][j]=='#'&&a[i+1][j]=='#'&&a[i][j-1]=='#'&&a[i][j+1]=='#'){
				dfs(i,j);
			}
		}
	}
	for(int i=1;i<=n;i++){
		for(int j=1;j<=n;j++){
			if(a[i][j]=='#'){
				cnt+=1;
				dfs(i,j);
			}
		}
	}
	cout<<cnt;
	return 0;
}