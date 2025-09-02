#include<bits/stdc++.h>
using namespace std;
#define x first
#define y second
const int maxn=810;
int t,n,m;
char g[maxn][maxn];
int vis[maxn][maxn];
pair<int,int>boy,girl,ghost[2];
int dx[4]={-1,0,1,0},dy[4]={0,1,0,-1};
bool check(int x,int y,int tim){
	if(x<0||x>=n||y<0||y>=m||g[x][y]=='X'){
		return false;
	}
	for(int i=0;i<2;i++){
		if(abs(x-ghost[i].x)+abs(y-ghost[i].y)<=tim*2){
			return false;
		}
	}
	return true;
}
int bfs(){
	int tim=0;
	memset(vis,0,sizeof(vis));
	queue<pair<int,int> >qb,qg;
	qb.push(boy);
	qg.push(girl);
	while(qb.size()||qg.size()){
		tim++;
		for(int i=0;i<3;i++){
			for(int j=0,s=qb.size();j<s;j++){
				pair<int,int> t=qb.front();
				qb.pop();
				int x=t.x;
				int y=t.y;
				if(!check(x,y,tim)){
					continue;
				}
				for(int k=0;k<4;k++){
					int a=x+dx[k],b=y+dy[k];
					if(check(a,b,tim)){
						if(vis[a][b]==2){
							return tim;
						}
						if(!vis[a][b]){
							vis[a][b]=1,qb.push({a,b});
						}
					}
				}
			}
		}
		for(int i=0;i<1;i++){
			for(int j=0,s=qg.size();j<s;j++){
				pair<int,int> t=qg.front();
				qg.pop();
				int x=t.x;
				int y=t.y;
				if(!check(x,y,tim)){
					continue;
				}
				for(int k=0;k<4;k++){
					int a=x+dx[k],b=y+dy[k];
					if(check(a,b,tim)){
						if(vis[a][b]==1){
							return tim;
						}
						if(!vis[a][b]){
							vis[a][b]=2,qg.push({a,b});
						}
					}
				}
			}
		}
	}
	return -1;
}
int main(){
	ios::sync_with_stdio(false);
	cin.tie(0),cout.tie(0);
	cin>>t;
	while(t--){
		cin>>n>>m;
		for(int i=0;i<n;i++){
			for(int j=0;j<m;j++){
				cin>>g[i][j];
			}
		}
		for(int i=0,t=0;i<n;i++){
			for(int j=0;j<m;j++){
				if(g[i][j]=='M'){
					boy={i,j};
				}
				else if(g[i][j]=='G'){
					girl={i,j};
				}
				else if(g[i][j]=='Z'){
					ghost[t++]={i,j};
				}
			}
		}
		cout<<bfs()<<'\n';
	}
	return 0;
}
