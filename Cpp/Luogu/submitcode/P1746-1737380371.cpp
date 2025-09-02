#include<bits/stdc++.h>
using namespace std;
int n,xs,ys,xe,ye;
int tx[5]={0,0,0,1,-1};
int ty[5]={0,1,-1,0,0};
bool vis[1005][1005];
char a[1005][1005];
struct zb{
	int x,y,step;
};
queue<zb>q;
int main(){
	cin>>n;
	for(int i=1;i<=n;i++){
		for(int j=1;j<=n;j++){
			cin>>a[i][j];
			if(a[i][j]=='1'){
				vis[i][j]=1;
			}
		}
	}
	cin>>xs>>ys>>xe>>ye;
	q.push({xs,ys,0});
	vis[xs][ys]=1;
	while(!q.empty()){
		zb now=q.front();
		q.pop();
		if(now.x==xe&&now.y==ye){
			cout<<now.step;
			break;
		}
		for(int i=1;i<=4;i++){
			int bx=now.x+tx[i];
			int by=now.y+ty[i];
			if(bx>=1&&bx<=n&&by>=1&&by<=n&&a[bx][by]=='0'&&vis[bx][by]==0){
				q.push({bx,by,now.step+1});
				vis[bx][by]=1;
			}
		}
	}
	return 0;
}
