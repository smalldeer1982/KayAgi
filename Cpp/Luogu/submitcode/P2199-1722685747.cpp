#include <bits/stdc++.h>
using namespace std;
const int INF=2e9;
string a[17000];
vector<int>ans[17000];
int dx[4]={-1,1,0,0};
int dy[4]={0,0,-1,1};
int dx2[8]={-1,1,0,0,-1,1,1,-1};
int dy2[8]={0,0,-1,1,1,1,-1,-1};
int n,m,sx,sy,tx,ty;
struct node
{
	int x,y,step;
};
queue<node> q;
bool ok(int x,int y)
{
	if(x>=1&&x<=n&&y>=1&&y<=m&&a[x][y-1]=='O') 
	{
		return 1;
	}
	else
	{
		return 0;
	}
}
void bfs(int tx,int ty)
{
	for(int i=1;i<=n;i++)
	{
		for(int j=1;j<=m;j++)
		{
			ans[i][j]=INF;
		}
	}
	q.push(node{tx,ty,0});
	ans[tx][ty]=0;
	while (!q.empty())
	{
		node tmp=q.front();
		q.pop();
		for (int i=0;i<=3;i++)
		{
			int nx=tmp.x+dx[i];
			int ny=tmp.y+dy[i];
			if (ok(nx,ny)&&ans[nx][ny]==INF)
			{
				q.push(node{nx,ny,tmp.step+1});
				ans[nx][ny]=tmp.step+1;
			}
		}
	}
}
int main()
{
	cin>>n>>m;
	for(int i=1;i<=n;i++)
	{
		cin>>a[i];
		ans[i].resize(m+1);
	}
	while(cin>>sx>>sy>>tx>>ty)
	{
		if(sx==0&&sy==0&&tx==0&&ty==0)
		{
			break;
		}
		bfs(tx,ty);
		if(ans[sx][sy]==INF)
		{
			cout<<"Poor Harry"<<endl;
		}
		else
		{
			int answer=ans[sx][sy];
			for(int i=0;i<=7;i++)
			{
				int tmpx=sx+dx2[i],tmpy=sy+dy2[i];
				while(ok(tmpx,tmpy))
				{
					answer=min(answer,ans[tmpx][tmpy]);
					tmpx+=dx2[i];
					tmpy+=dy2[i];
				}
			}
			cout<<answer<<endl;
		}
	}
    return 0;
}