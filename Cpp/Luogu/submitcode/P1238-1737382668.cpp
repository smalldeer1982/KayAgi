#include<bits/stdc++.h>
using namespace std;
int n,m,a[20][20],vis[20][20];
int t=2,tx[505],ty[505];
int sx,sy,ex,ey;
int dx[5]={0,-1,0,1},dy[5]={-1,0,1,0};
bool flag=0;
void dfs(int x,int y){
	if(x==ex&&y==ey){
		flag=1;
		for(int i=1;i<=t-2;i++){
			cout<<"("<<tx[i]<<","<<ty[i]<<")->";
		}
		cout<<"("<<ex<<","<<ey<<")"<<endl;
	}
	for(int i=0;i<4;i++){
		int nx=x+dx[i];
		int ny=y+dy[i];
		if(nx>=1&&nx<=n&&ny>=1&&ny<=m&&a[nx][ny]==1&&vis[nx][ny]==0){
			tx[t]=nx,ty[t]=ny;
			t+=1;
			vis[nx][ny]=1;
			dfs(nx,ny);
			tx[t]=0,ty[t]=0;
			t-=1;
			vis[nx][ny]=0;
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
	cin>>sx>>sy>>ex>>ey;
	tx[1]=sx,ty[1]=sy;
	vis[sx][sy]=1;
	dfs(sx,sy);
	if(flag==0){
		cout<<-1;
	}
	return 0;
}