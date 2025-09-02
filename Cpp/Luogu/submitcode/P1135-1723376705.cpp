#include <bits/stdc++.h>
using namespace std;
int n,a,b,tmp;
struct floors
{
	int up,down,step;
	bool visit;
}fs[205];
int main()
{
	cin>>n>>a>>b;
	for(int i=1;i<=n;i++)
	{
		cin>>tmp;
		fs[i].up=i+tmp;
		fs[i].down=i-tmp;
		fs[i].step=-1;
		fs[i].visit=false;
	}
	queue<floors>q;
	fs[a].step=0;
	fs[a].visit=true;
	q.push(fs[a]);
	while(!q.empty())
	{
		floors f=q.front();
		q.pop();
		int u=f.up,d=f.down;
		if(u>=1&&u<=n&&fs[u].visit==false)
		{
			fs[u].visit=true;
			fs[u].step=f.step+1;
			q.push(fs[u]);
		}
		if(d>=1&&d<=n&&fs[d].visit==false)
		{
			fs[d].visit=true;
			fs[d].step=f.step+1;
			q.push(fs[d]);
		}
		if(u==b||d==b)
		{
			break;
		}
	}
	cout<<fs[b].step;
}