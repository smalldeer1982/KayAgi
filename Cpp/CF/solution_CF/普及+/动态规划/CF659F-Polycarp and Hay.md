# Polycarp and Hay

## 题目描述

The farmer Polycarp has a warehouse with hay, which can be represented as an $ n×m $ rectangular table, where $ n $ is the number of rows, and $ m $ is the number of columns in the table. Each cell of the table contains a haystack. The height in meters of the hay located in the $ i $ -th row and the $ j $ -th column is equal to an integer $ a_{i,j} $ and coincides with the number of cubic meters of hay in the haystack, because all cells have the size of the base $ 1×1 $ . Polycarp has decided to tidy up in the warehouse by removing an arbitrary integer amount of cubic meters of hay from the top of each stack. You can take different amounts of hay from different haystacks. Besides, it is allowed not to touch a stack at all, or, on the contrary, to remove it completely. If a stack is completely removed, the corresponding cell becomes empty and no longer contains the stack.

Polycarp wants the following requirements to hold after the reorganization:

- the total amount of hay remaining in the warehouse must be equal to $ k $ ,
- the heights of all stacks (i.e., cells containing a non-zero amount of hay) should be the same,
- the height of at least one stack must remain the same as it was,
- for the stability of the remaining structure all the stacks should form one connected region.

The two stacks are considered adjacent if they share a side in the table. The area is called connected if from any of the stack in the area you can get to any other stack in this area, moving only to adjacent stacks. In this case two adjacent stacks necessarily belong to the same area.

Help Polycarp complete this challenging task or inform that it is impossible.

## 说明/提示

In the first sample non-zero values make up a connected area, their values do not exceed the initial heights of hay stacks. All the non-zero values equal $ 7 $ , and their number is $ 5 $ , so the total volume of the remaining hay equals the required value $ k=7·5=35 $ . At that the stack that is on the second line and third row remained unaltered.

## 样例 #1

### 输入

```
2 3 35
10 4 9
9 9 7
```

### 输出

```
YES
7 0 7 
7 7 7 
```

## 样例 #2

### 输入

```
4 4 50
5 9 1 1
5 1 1 5
5 1 5 5
5 5 7 1
```

### 输出

```
YES
5 5 0 0 
5 0 0 5 
5 0 5 5 
5 5 5 0 
```

## 样例 #3

### 输入

```
2 4 12
1 1 3 1
1 6 2 4
```

### 输出

```
NO
```

# 题解

## 作者：Crazyouth (赞：0)

## 分析

一个和边哥不同的做法。

对于一个点 $(i,j)$，如果它的值能整除 $k$，且仅通过走大于等于它的点能去到的点数大于等于 $\frac{k}{a_{i,j}}$，那么就可以把它能去到的那些大于等于它的点（包括自身）中的 $\frac k {a_{i,j}}$ 个变为 $a_{i,j}$，然后就完成目标了。

这样我们只需要知道仅经过大于等于它的点能去到几个点这个问题就解决了。不妨考虑让相邻的点连边，边权为这两个点的点权的较小值，这样我们就相当于要求一个图上仅经过边权大于等于 $a_{i,j}$ 的边能去到的点数，这是典型的 kruskal 重构树问题，建出最大生成树再建重构数即可。

当我们发现了一个点之后，就可以 bfs 它周围的比它大的点，找到其中 $\frac k {a_{i,j}}$ 个即可。

时空复杂度均为 $O(nm \log (nm))$，注意常数。

## AC Code
```cpp
#include <bits/stdc++.h>
using namespace std;
const int N=1010;
#define hs(i,j) (i-1)*m+j
struct edge
{
	int u,v,w;
}e[N*N<<1];
int a[N][N],dx[4]={1,0,-1,0},dy[4]={0,1,0,-1},fa[N*N<<2],ncnt=0,ch[N*N<<2][2],W[N*N<<2],f[N*N<<2][25],sz[N*N<<2],vis[N][N];
int n,m;
void bfs(int u)
{
	queue<int> q;
	q.push(u);
	while(q.size())
	{
		int v=q.front();
		q.pop();
		for(int i=1;i<=24;i++) f[v][i]=f[f[v][i-1]][i-1];
		if(ch[v][0])
		{
			f[ch[v][0]][0]=f[ch[v][1]][0]=v;
			q.push(ch[v][0]);q.push(ch[v][1]);
		}
		else sz[v]=1;
	}
}
void print(int sx,int sy,int num)
{
	queue<pair<int,int>> q;
	q.push({sx,sy});
	vis[sx][sy]=1;
	num--;
	while(q.size()&&num)
	{
		int x=q.front().first,y=q.front().second;
		q.pop();
		for(int i=0;i<4;i++)
		{
			int nx=x+dx[i],ny=y+dy[i];
			if(vis[nx][ny]||nx<1||nx>n||ny<1||ny>m||a[nx][ny]<a[sx][sy]) continue;
			num--;
			q.push({nx,ny});
			vis[nx][ny]=1;
			if(!num) goto E;
		}
	}
	E:;
	for(int i=1;i<=n;i++)
	{
		for(int j=1;j<=m;j++)
		cout<<(vis[i][j]?a[sx][sy]:0)<<' ';
		cout<<'\n';
	}
}
int find(int x)
{
	if(x==fa[x]) return x;
	fa[x]=find(fa[x]);
	return fa[x];
}
int main()
{
	int cnt=0;
	long long k;
	cin>>n>>m>>k;
	for(int i=1;i<=n;i++)
	for(int j=1;j<=m;j++)
	cin>>a[i][j];
	for(int i=1;i<=n;i++)
	{
		for(int j=1;j<=m;j++)
		{
			for(int l=0;l<2;l++)
			{
				int x=i+dx[l],y=j+dy[l];
				if(x<1||x>n||y<1||y>m) continue;
				e[++cnt]={hs(i,j),hs(x,y),min(a[i][j],a[x][y])};
			}
		}
	}
	sort(e+1,e+cnt+1,[](edge a,edge b){return a.w>b.w;});
	for(int i=1;i<2*n*m;i++) fa[i]=i;
	ncnt=n*m;
	for(int i=1;i<=cnt;i++)
	{
		int u=e[i].u,v=e[i].v,w=e[i].w;
		int fu=find(u),fv=find(v);
		if(fu==fv) continue;
		ncnt++;
		ch[ncnt][0]=fu;ch[ncnt][1]=fv;W[ncnt]=w;
		fa[fu]=fa[fv]=ncnt;
	}
	f[ncnt][0]=ncnt;
	bfs(ncnt);
	for(int i=n*m+1;i<=ncnt;i++) sz[i]=sz[ch[i][0]]+sz[ch[i][1]];
	for(int i=1;i<=n;i++)
	for(int j=1;j<=m;j++)
	{
		if(k%a[i][j]) continue;
		int u=hs(i,j);
		for(int l=24;~l;l--) if(W[f[u][l]]>=a[i][j]) u=f[u][l];
		if(k/a[i][j]<=sz[u])
		{
			cout<<"YES\n";
			print(i,j,k/a[i][j]);
			return 0;
		}
	}
	cout<<"NO";
}

---

## 作者：_edge_ (赞：0)

首先我们先分析一下题目的条件。

连通块里面的 $a_{i,j}$ 都必须相等，并且有一个 $a_{i,j}$ 不变，这意味着我们可以钦定一个 $a_{i,j}$ 不变，并且把与他相邻的都给统计一下。

因为当前只有减法操作，所以每一个 $a_{i,j}$ 能变成比他小的，但是不能变大。

因此，我们可以随便选择一个格子，然后暴力求出能变成他的与他相邻的有多少个，然后就可以进行 check 了。

check 的时候判一下 $k$ 能不能被当前这个格子的数整除，并且够不够。

这样暴力搞我们得到了 $O(n^2m^2)$ 的做法。

考虑进行优化，我们复杂度的瓶颈在于寻找与他相邻的有多少个。

那么怎么样可以比较快速的搞这个呢？

考虑一个问题如果一个比 $a_{i,j}$ 大的都可以扩展到的点，是不是 $a_{i,j}$ 也可以扩展得到？

考虑将权值从大到小排序，如果一个点被选定，则把它和它相邻的都给加入一个并查集内，这样就能快速的维护连通性。

这里的并查集要稍微搞一搞，因为还要维护当前连通块个数。

```cpp
#include <iostream>
#include <cstdio>
#include <algorithm>
#define int long long 
using namespace std;
const int INF=1e3+5;
const int INFN=1e6+5;
const int fx[]={0,0,-1,1};
const int fy[]={1,-1,0,0};
struct _node_data{
	int v,x,y;
}b[INFN];
bool cmp(_node_data xx,_node_data yy) {
	return xx.v>yy.v;
}
int n,m,k,a[INF][INF],fa_set[INFN],num[INFN],vis[INF][INF],sum,kk,tot,A[INF][INF];
int ys(int x,int y) {
	return (x-1)*m+y;	
}
int find_set(int x) {return x==fa_set[x]?x:fa_set[x]=find_set(fa_set[x]);}
void mer(int x,int y) {
	x=find_set(x);y=find_set(y);
	if (x==y) return ;
	num[y]+=num[x];num[x]=0;
	fa_set[x]=y;
}
void DFS(int x,int y) {
	if (vis[x][y]) return ;
	if (sum<=0) return ;
	if (a[x][y]>=kk) vis[x][y]=2,sum--;
	else vis[x][y]=1;
	if (vis[x][y]==1) return ;
	if (sum<=0) return ;
	for (int i=0;i<4;i++) {
		int gx=x+fx[i],gy=y+fy[i];
		if (gx<1 || gy<1 || gx>n || gy>m) continue;
		DFS(gx,gy);
	}
}
void solve(int x,int y,int z,int zz) {
	sum=z;kk=zz;
	DFS(x,y);
	for (int i=1;i<=n;i++) {
		for (int j=1;j<=m;j++)
			if (vis[i][j]==2) cout<<zz<<" ";
			else cout<<"0 ";
		cout<<"\n";
	}
	return ;
}
signed main()
{
	ios::sync_with_stdio(false);
	cin>>n>>m>>k;
	for (int i=1;i<=1e6;i++) fa_set[i]=i,num[i]=1;
	for (int i=1;i<=n;i++)
		for (int j=1;j<=m;j++) {
			cin>>a[i][j];
			b[++tot]=(_node_data){a[i][j],i,j};
		}
	sort(b+1,b+1+tot,cmp);
	for (int i=1;i<=tot;i++) {
		int xx=b[i].x,yy=b[i].y;A[xx][yy]=1;
		for (int j=0;j<4;j++) {
			int gx=xx+fx[j],gy=yy+fy[j];
			if (gx<1 || gy<1 || gx>n || gy>m) continue;
			if (A[gx][gy]==0) continue;
			int X=ys(xx,yy),Y=ys(gx,gy);
			mer(X,Y);
		}
		int X=ys(xx,yy);X=find_set(X);
		if (num[X]*b[i].v<k) continue; 
		if (k%b[i].v) continue;
		cout<<"YES\n";
		solve(xx,yy,k/b[i].v,b[i].v);
		return 0;
	}
	cout<<"NO\n";
	return 0;
}
```



---

