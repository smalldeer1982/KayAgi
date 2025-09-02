# [USACO07FEB] Lilypad Pond G

## 题目描述

FJ has installed a beautiful pond for his cows' aesthetic enjoyment and exercise.

The rectangular pond has been partitioned into square cells of M rows and N columns (1 ≤ M ≤ 30; 1 ≤ N ≤ 30). Some of the cells have astonishingly sturdy lilypads; others have rocks; the remainder are just beautiful, cool, blue water.

Bessie is practicing her ballet moves by jumping from one lilypad to another and is currently located at one of the lilypads. She wants to travel to another lilypad in the pond by jumping from one lilypad to another.

Surprising only to the uninitiated, Bessie's jumps between lilypads always appear as a chess-knight's move: one move in one direction and then two more in the orthogonal direction (or perhaps two in one direction and then one in the orthogonal direction).

Farmer John is observing Bessie's ballet drill and realizes that sometimes she might not be able to jump to her destination lilypad because intermediary lilypads are missing.

Ever thrifty, he wants to place additional lilypads so she can complete her quest (perhaps quickly, perhaps by using a large number of intermediate lilypads). Of course, lilypads cannot be placed where rocks already intrude on a cell.

Help Farmer John determine the minimum number of additional lilypads he has to place, and in how many ways he can place that minimum number.


## 说明/提示

### 样例解释

池塘分成四行五列，贝西的起点在第二行第一列，想去的终点在第四行第四列，池塘里一共有三朵莲花和一块石头。

最少需要两朵莲花，有三种方式可以放置，

如下 $\verb!X!$ 所示：

$$\begin{bmatrix}
\verb!10000! \\
\verb!30X00! \\
\verb!00200! \\
\verb!0X040! \\
\end{bmatrix},\begin{bmatrix}
\verb!10X00! \\
\verb!30000! \\
\verb!0X200! \\
\verb!00040! \\
\end{bmatrix},\begin{bmatrix}
\verb!10X00! \\
\verb!3000X! \\
\verb!00200! \\
\verb!00040! \\
\end{bmatrix}
$$

## 样例 #1

### 输入

```
4 5
1 0 0 0 0
3 0 0 0 0
0 0 2 0 0
0 0 0 4 0
```

### 输出

```
2
3
```

# 题解

## 作者：D_14134 (赞：35)

#### ~~关于spfa，它还没有凉透~~

拿道题，第一眼你会觉得跑bfs，但很快你发现原有的荷花会让你看起来很烦，尤其第二问的方案数统计需要两遍bfs

然后你就开始考虑联通块，能不嫩把荷花缩成联通块。但很快你发现问题有出在第二问上。例如：

0 0 x 0 0

1 0 0 0 1

0 0 y 0 0

上面的例子，假如从x到y，可以看出在左边和右边的1是两个联通块，但方案数只有在x和y加荷花一种。

然后~~不小心~~看一下标签，发现是spfa。


我们可以去避免遇到那些原本存在的荷花，我们就预处理出每个起点以及水位置的花费1个荷叶能到的地方，然后建边跑spfa就可以了

这样可以有效避免有环的情况，上面的例子就直接从x到y，不会重复算情况了

# code
```cpp
#include<queue>
#include<cstdio>
#include<cstring>
#include<algorithm>
#define re register
#define IN inline
using namespace std;
const int maxn=50;
const int inf=0x7f7f7f;
int dx[8]={2,2,-2,-2,1,-1,1,-1},dy[8]={-1,1,-1,1,2,2,-2,-2};
struct node{
	int to,next;
}a[100010];
int len,head[maxn*maxn],x,y,st,ed;
void adde(int x,int y){a[++len].to=y;a[len].next=head[x];head[x]=len;}
int n,m,mp[maxn][maxn],d[maxn*maxn],p[maxn][maxn];
long long f[maxn*maxn];
bool b[maxn][maxn],vis[maxn*maxn];
IN void dfs(int o,int x,int y){
	b[x][y]=1;
	for(re int k=0;k<8;k++){
		int xx=x+dx[k],yy=y+dy[k];
		if(xx<1 || yy<1 || xx>n || yy>m || b[xx][yy])continue;
		if(mp[xx][yy]==1) dfs(o,xx,yy);
		else b[xx][yy]=1,adde(o,p[xx][yy]);
	}
}
IN void init(){
	for(re int i=1;i<=n;i++)
		for(re int j=1;j<=m;j++)
			p[i][j]=(i-1)*m+j;
	for(re int i=1;i<=n;i++){ 
		for(re int j=1;j<=m;j++){
			scanf("%d",&mp[i][j]);
			if(mp[i][j]==3) st=p[i][j];
			if(mp[i][j]==4) ed=p[i][j];
		}
	}
	for(re int i=1;i<=n;i++)
		for(re int j=1;j<=m;j++){
		if(mp[i][j]==0||mp[i][j]==3){
			memset(b,0,sizeof(b));
			dfs(p[i][j],i,j);
		}
	}
}
queue<int> q;
IN void spfa(){
	memset(d,63,sizeof(d));
	d[st]=0,vis[st]=f[st]=1;
	q.push(st);
	while(!q.empty()){
		x=q.front(); q.pop(); vis[x]=0;
		for(re int k=head[x];k;k=a[k].next){
			int v=a[k].to;
			if(d[v]>d[x]+1){
				d[v]=d[x]+1;f[v]=f[x];
				if(!vis[v]){
					vis[v]=1;
					q.push(v);
				}
			}
			else if(d[v]==d[x]+1) f[v]+=f[x];
		}
	}
}
int main(){
	scanf("%d%d",&n,&m);
	init();spfa();
	if(d[ed]<inf)printf("%d\n%lld\n",d[ed]-1,f[ed]);
	else printf("-1\n");
	return 0;
}

```

---

## 作者：s_ShotღMaki (赞：12)

听说这题用bfs直接跑两遍更快？？？

不！虽然更快我承认，但是我只想证明给大家

# 关于spfa，他没有死

咳咳，进入正题

这道题还是很难的，首先我相信大家都做过类似最短路的题或者是最短路计数的题吧？如果没有做过，那么可以直接去[p1144](https://www.luogu.org/problemnew/show/P1144)还有[p4779](https://www.luogu.org/problemnew/show/P4779)去做一下再来哦！（~~或者直接复制我的题解也好！）~~

好了，开始这一道题，思路来自我的同机房大佬（已经退役的

想要跑spfa或者最短路计数，可以在一个二维数组的图上，我们没法直接跑（所以我想到的是bfs可以一直wa四个点），因此我们必须要对抽象的二维数组进行建图，建成有向图，然后直接跑spfa和最短路计数就好了。

------------


好了，那我们就有思路了

## 输入 -> 建图 -> spfa + 最短路计数 -> 输出答案

------------


**那么问题来了，如何建图呢，想要建图就要有点的编号，因此我们在输入的时候要对点们进行编号，编号方法就是一般方法，很多题里面都有der!**

```cpp
for (int i = 1; i <= n; i ++)
	 for (int j = 1; j <= m; j ++)
	 {
	 	if (map[i][j] == 0 || map[i][j] == 3) 
	 	{
	 		memset (used, 0, sizeof (used));
	 		This_is_for_you(bianhao[i][j], i, j);
		}
	 }
```

**用递归dfs来实现建图**

```cpp
void This_is_for_you (int num, int x, int y)
{
	if (used[x][y]) return ;
	used[x][y] = true;
	for (int i = 0; i < 8; i ++)
	{
		int nowx = x + fx[i]; int nowy = y + fy[i];
		if (nowx >= 1 && nowx <= n && nowy >= 1 && nowy <= m && !used[nowx][nowy])
		{
			if (map[nowx][nowy] == 1) This_is_for_you (num, nowx, nowy);
			else
			if (map[nowx][nowy] != 2)
			{
				used[nowx][nowy] = true;
				int zd = bianhao[nowx][nowy];
				add (num, zd);
			}
		}
	}
}
```

**然后直接跑spfa和最短路计数就好了**
（~~建议直接复制自己在p1144里的提交）~~

## 完整代码

```cpp
#include<cstdio>
#include<cstring>
#include<iostream>
#include<algorithm>
#include<queue>

#define man 35
#define maxn 1233333

using namespace std;

inline int read ()
{
    int f = 1, x = 0;
	char ch;
    do {ch = getchar (); if (ch== '-') f = -1;} while (ch < '0' || ch > '9');
    do {x = x * 10 + ch - '0'; ch = getchar ();} while (ch >= '0' && ch <= '9');
    return f * x;
}

struct node
{
	int q, z, next;
} edge[maxn * 5];

int n, m;
int map[man][man];
int bianhao[man][man];
int qx, qy, zx, zy;
bool used[man][man];
int head[maxn];
int fx[] = {2, -2, 2, -2, -1, 1, -1, 1};
int fy[] = {1, 1, -1, -1, 2, 2, -2, -2};
int cnt;

int d[maxn];
long long tot[maxn];
bool in_que[maxn];

queue < int > q;

void add (int q, int z)
{
	edge[++ cnt].q = q;
	edge[cnt].z = z;
	edge[cnt].next = head[q];
	head[q] = cnt;
}

void This_is_for_you (int num, int x, int y)
{
	if (used[x][y]) return ;
	used[x][y] = true;
	for (int i = 0; i < 8; i ++)
	{
		int nowx = x + fx[i]; int nowy = y + fy[i];
		if (nowx >= 1 && nowx <= n && nowy >= 1 && nowy <= m && !used[nowx][nowy])
		{
			if (map[nowx][nowy] == 1) This_is_for_you (num, nowx, nowy);
			else
			if (map[nowx][nowy] != 2)
			{
				used[nowx][nowy] = true;
				int zd = bianhao[nowx][nowy];
				add (num, zd);
			}
		}
	}
}

void so_go_and_do_it ()
{
	int sta = bianhao[qx][qy]; int en = bianhao[zx][zy];
	memset (d, 0x3f, sizeof (d));
	d[sta] = 0;
	in_que[sta] = true;
	tot[sta] = 1;
	q.push (sta);
	while (!q.empty ())
	{
		int now = q.front (); q.pop (); in_que[now] = false;
		for (int i = head[now]; i; i = edge[i].next)
		{
			int end = edge[i].z;
			int newd = d[now] + 1;
			if (d[end] > newd)
			{
				d[end] = newd;
				tot[end] = tot[now];
				if (in_que[end] == false)
				{
					q.push (end);
					in_que[end] = true;
				}
			}
			else
			if (d[end] == newd) tot[end] += tot[now];
		}
	}
}

int main ()
{
	n = read (); m = read ();
	
	for (int i = 1; i <= n; i ++)
	 for (int j = 1; j <= m; j ++)
	 {
	 	map[i][j] = read ();
	 	bianhao[i][j] = (i - 1) * m + j;
	 	if (map[i][j] == 3) qx = i, qy = j;
	 	if (map[i][j] == 4) zx = i, zy = j;
	 }
	
	for (int i = 1; i <= n; i ++)
	 for (int j = 1; j <= m; j ++)
	 {
	 	if (map[i][j] == 0 || map[i][j] == 3) 
	 	{
	 		memset (used, 0, sizeof (used));
	 		This_is_for_you(bianhao[i][j], i, j);
		}
	 }
	so_go_and_do_it ();
	if (d[bianhao[zx][zy]] == 1061109567) puts("-1");
	else printf ("%d\n%lld", d[bianhao[zx][zy]] - 1, tot[bianhao[zx][zy]]);
	return 0;
}
```

## 一定要开long long！！！！！！！

最后挂一下变量说明，更好理解，不太懂的同学看看这个！

```cpp
int n, m; // 这个不用解释 
int map[man][man]; // 输入的地图1,2,3,4 
int bianhao[man][man]; // 每一个点的编号 
int qx, qy, zx, zy; // 起点坐标和终点坐标 
bool used[man][man]; // 有没有使用过 
int head[maxn]; // 邻接表需要的 
int fx[] = {2, -2, 2, -2, -1, 1, -1, 1}; // 8方向 
int fy[] = {1, 1, -1, -1, 2, 2, -2, -2}; // 8方向 
int cnt; // 边的总数 

int d[maxn]; // 每个点的距离 
long long tot[maxn]; // 最短路的数目！会爆int，一定要开long long  
bool in_que[maxn]; // 在不在队列里面 
```


---

## 作者：顾z (赞：9)

# [顾](https://www.luogu.org/blog/RPdreamer/#)[z](https://www.cnblogs.com/-guz/)

~~你没有发现两个字里的blog都不一样嘛~~ qwq

这道题不错啊,表示很考思维.

首先,我们需要知道放多少莲花,如何放.

因此考虑最短路,方案数,我们就考虑最短路计数.(想信大家都会的)

这题的难点在于**如何建边**.

> 因为贝西可以跳任何一个位置,(任何一个有水的位置都可以放莲花)
>
> 所以我们不能单纯地从起点开始向其他点连边,所以我们要从每一个有水的地方开始.
>
> 由于岩石对答案没有贡献,所以不考虑连边.

多次$dfs$对整个图连边.

既然想到这了,你可能会发现,这是一个二维的最短路,记录状态不太好记录.

因此我们给每一个格子编号,像这样.

![](https://i.loli.net/2018/10/14/5bc32e5e3ec76.png)

当然,还有其他编号方法,这样比较简单罢了.

算某一位置$(x,y)$的编号的话,式子为$idx[x][y]=(x-1)\times m+y$

这样建边操作就简单多了.

然后后面只需要敲一个裸的最短路和最短路计数问题就好了.

**输出添加的荷花的最小的数量的时候要$-1$**

这是因为,这个数量实际上是点权,而我们跑最短路用的是边权.

一个点与两条边相连,所以要$-1$。

``代码``

```c++
#include<cstdio>
#include<cctype>
#include<queue>
#include<cstring>
#define int long long
#define clear(a,b) memset(a,b,sizeof a)
#define R register
using namespace std;
inline void in(int &x)
{
	int f=1;x=0;char s=getchar();
	while(!isdigit(s)){if(s=='-')f=-1;s=getchar();}
	while(isdigit(s)){x=x*10+s-'0';s=getchar();}
	x*=f;
}
int n,m,res[35][35],tot,idx[35][35],dis[1008611];
int sx,sy,fx,fy,s,t,head[1008611],to[1008611];
const int ax[]={2,1,-1,-2,2,1,-1,-2};
const int ay[]={1,2,2,1,-1,-2,-2,-1};
bool vis[35][35],inq[1008611];
struct coc{int u,v;}edge[1008611];
inline void add(int x,int y)
{
	edge[++tot].u=head[x];
	edge[tot].v=y;
	head[x]=tot;
}
void dfs(int id,int x,int y)
{
	if(vis[x][y])return;
	vis[x][y]=true;
	for(R int i=0;i<8;i++)
	{
		R int nx=x+ax[i],ny=y+ay[i];
		if(nx<1 || nx>n || ny>m || ny<1 || vis[nx][ny])continue;
        //刚开始写成return,尴尬死了 emm
		if(res[nx][ny]==1)dfs(id,nx,ny);
		else if(res[nx][ny]!=2)
		{
			vis[nx][ny]=true;
			add(id,idx[nx][ny]);
		}
	}
}
inline void spfa()
{
	queue<int>q;
	for(R int i=1;i<=n*m;i++)dis[i]=2147483647;dis[s]=0;
	inq[s]=true;q.push(s);to[s]=1;
	while(!q.empty())
	{
		int u=q.front();q.pop();inq[u]=false;
		for(R int i=head[u];i;i=edge[i].u)
		{
			if(dis[edge[i].v]>dis[u]+1)
			{
				dis[edge[i].v]=dis[u]+1;
				to[edge[i].v]=to[u];
				if(!inq[edge[i].v])
				{
					q.push(edge[i].v);
					inq[edge[i].v]=true;
				}
			}
			else if(dis[edge[i].v]==dis[u]+1)
				to[edge[i].v]+=to[u];
		}
	}
	if(dis[t]<2147483647)printf("%lld\n%lld",dis[t]-1,to[t]);
	else printf("-1");
}
signed main()
{
	in(n),in(m);
	for(R int i=1;i<=n;i++)
		for(R int j=1;j<=m;j++)
		{
			in(res[i][j]);
			idx[i][j]=(i-1)*m+j;
			if(res[i][j]==3)sx=i,sy=j;
			if(res[i][j]==4)fx=i,fy=j;
		}
	for(R int i=1;i<=n;i++)
		for(R int j=1;j<=m;j++)
			if(!res[i][j] or res[i][j]==3)
				clear(vis,0),dfs(idx[i][j],i,j);
	s=idx[sx][sy];t=idx[fx][fy];
	spfa();
}
```

---

## 作者：赵晨洋 (赞：8)

/\*
用spfa算路径，在过程中统计最短路径数，但是如果从一个点向周围的荷叶建边就会出现0边，直接统计路径数会出错，最重要的是问的是荷叶拜放的方案数，

（并不是路径数!!!!!）所以忽略与荷叶建的边，把一个连通块的荷叶周围的水与该点建边，再跑spfa

\*/
```cpp
#include<cmath>
#include<cstdio>
#include<cstring>
#include<algorithm>
using namespace std;
int n,m;
int map[40][40];
int dx[9]={-1,-2,-2,-1,1,2,2,1};
int dy[9]={-2,-1,1,2,2,1,-1,-2};
int link[40][40][40][40];
long long plan[40][40];
bool visit1[40][40];
int quex[100000],quey[100000];
bool visit[40][40];
int dist[40][40];
int qt=0,qh=0,sx,sy,tx,ty;
void fill(int x,int y)
{
    memset(visit1,0,sizeof(visit1));
    qt=qh=0;
    quex[++qt]=x,quey[qt]=y;
    while(qh<qt)
    {
        int px=quex[++qh],py=quey[qh];
        for(int i=0;i<=7;i++)
        {
            int ddx=px+dx[i],ddy=py+dy[i];
            if(ddx>n||ddy<1||ddy>m||ddx<1||visit1[ddx][ddy]) continue;
            if(map[ddx][ddy]==0||(ddx==tx&&ddy==ty))
            link[x][y][ddx][ddy]=1;
            else if(map[ddx][ddy]==1)
            quex[++qt]=ddx,quey[qt]=ddy,visit1[ddx][ddy]=true;
        }
    }
}
int main()
{
    scanf("%d%d",&n,&m);
    for(int i=1;i<=n;i++)
    for(int j=1;j<=m;j++)
    {
        scanf("%d",&map[i][j]);
        if(map[i][j]==3) sx=i,sy=j;
        if(map[i][j]==4) tx=i,ty=j;
    }
    fill(sx,sy);
    for(int i=1;i<=n;i++)
    for(int j=1;j<=m;j++)
    if(!map[i][j])
    fill(i,j);
    memset(dist,0x7f7f7f,sizeof(dist));
    dist[sx][sy]=qh=qt=0;
    quex[++qt]=sx;
    quey[qt]=sy;
    plan[sx][sy]=1;
    while(qh<qt)
    {
        int px=quex[++qh],py=quey[qh];
        visit[px][py]=false;
        for(int i=1;i<=n;i++)
        for(int j=1;j<=m;j++)
        {
            if(!link[px][py][i][j]) continue;
            if(dist[i][j]>dist[px][py]+1)
            {
                plan[i][j]=plan[px][py];
                dist[i][j]=dist[px][py]+1;
                if(!visit[i][j]&&(i!=tx||j!=ty))
                {
                    visit[i][j]=true;
                    quex[++qt]=i,quey[qt]=j;
                }
            }
            else if(dist[i][j]==dist[px][py]+1)
            plan[i][j]+=plan[px][py];
        }    
    }
    if(dist[tx][ty]>100000000)
    printf("-1");
    else
    printf("%d\n%lld",dist[tx][ty]-1,plan[tx][ty]);
}
```

---

## 作者：1jia1 (赞：7)

诡异的建边方法大佬们都讲过了，这里提供一个dijkstra的最短路计数。

```cpp
#include <cstdio>
#include <algorithm>
#include <queue>
#define N 51
#define inf 1926081764
#define point(x,y) (x-1)*m+y
using namespace std;
int n,m,map[N][N],beg,end,fx[9]={0,1,2,2,1,-1,-2,-2,-1},fy[9]={0,2,1,-1,-2,-2,-1,1,2},
	h[N*N],cnt, dis[N*N],vis[N*N];
long long counts[N*N];
struct edge{
	int next,to,val;
}e[N*N<<5];
inline void adde(int u,int v,int w)
{
//																printf("(%d,%d)->(%d,%d)\n",u/m+1,(u-1)%m+1,v/m+1,(v-1)%m+1);
	if(v==beg||v==end)w=0;
	e[++cnt].next=h[u];
	h[u]=cnt;
	e[cnt].to=v;
	e[cnt].val=w;
	return;
}
inline void dfs(int x,int y,int now)
{
	vis[point(x,y)]=now;
	for(int k=1,xx,yy;k<=8;k++)
	{
		xx=x+fx[k],yy=y+fy[k];
		if(xx<=0||xx>n||yy<=0||yy>m||map[xx][yy]==2)continue;
		if(vis[point(xx,yy)]==now)continue;
		if(map[xx][yy]==0||map[xx][yy]==3||map[xx][yy]==4)adde(now,point(xx,yy),1),vis[point(xx,yy)]=now;
		if(map[xx][yy]==1)dfs(xx,yy,now);
	}
}
priority_queue<pair<int,int> >q;
inline void dijkstra()
{
	for(int i=1;i<=n*m;i++)dis[i]=inf,vis[i]=counts[i]=0;
	dis[beg]=0,counts[beg]=1;
	q.push(make_pair(0,beg));
	while(q.size())
	{
		int x=q.top().second;q.pop();
		if(vis[x])continue;
		vis[x]=1;
		for(int i=h[x],v;i;i=e[i].next)
		{
			v=e[i].to;
			if(dis[x]+e[i].val<dis[v])
			{
				dis[v]=dis[x]+e[i].val;
				counts[v]=counts[x];
				q.push(make_pair(-dis[v],v));
			}
			else if(dis[x]+e[i].val==dis[v])
			{
				counts[v]+=counts[x];
			}
		}
	}
	return;
}
int main()
{
	scanf("%d%d",&n,&m);
	for(int i=1;i<=n;i++)
	{
		for(int j=1;j<=m;j++)
		{
			scanf("%d",&map[i][j]);
			if(map[i][j]==3)beg=point(i,j);
			if(map[i][j]==4)end=point(i,j);
		}
	}
	for(int i=1,xx,yy;i<=n;i++)for(int j=1;j<=m;j++)
	{
		if(map[i][j]==0||map[i][j]==3||map[i][j]==4)dfs(i,j,point(i,j));
	}
	dijkstra();
	if(counts[end]==0)printf("-1\n");
	else printf("%d\n%lld\n",dis[end],counts[end]);
	return 0;
}
```

---

## 作者：寒鸽儿 (赞：6)

### 其实第一眼看到就可以想到最短路径计数问题。没有听过的同学可以先看一下[p1608 路径统计](https://www.luogu.org/problemnew/show/P1608)。
### 然而这道题中存在无向0边(也可以理解为有向图中的0权回路或者0权环)。在spfa中，因为更新采用的是d[ver[i]] > d[cur] + wei[i]，所以不用忌惮双向的0边(或者称为0权环)。而如果跑最短路径计数，则需要顾及d[ver[i]] == d[cur] + wei[i], 而且需要入队，所以双向0边(即0权环)的存在会使spfa陷入死循环，正如spfa无法解决负权环那样。spfa的运行意义也是不同的有意义的路径，因此当跑最短路径计数时会遍及所有的最短路径。而在没有特殊定义的情况下，0权环无论跑多少个周期都可以称为一条全新的回路，所以spfa会一直运行下去，陷入死循环。
### 而在本题，由于我们关心的是莲花的放置方法，所以0环跑多少次都只能看作一次(原有的莲花当然不构成影响),因而可以跳过荷叶建边，用dfs解决它。关于dfs，其实就是寻找对于某个点，放置1个荷叶可以到达的点。
### 要注意结束点(4)是不用放置荷叶的。
### 我们可以发现，spfa之于带权图的意义正如dfs/bfs之于无权图的意义一样，因此在spfa中增减一些东西，可以变出很多有意思的东西。
### 我们可以发现对于head,d这种平时写成一维的数组，在用点作为关键字的时候写成二维是个不错的选择，这一点很妙。
### 说实话这是本蒟蒻靠自己AC的第一道紫题QaQ。
### 最后附上代码：
```cpp
#include <cstdio>
#include <cstring>
#include <queue>
#define pii pair<int, int>

using namespace std;

const int mov[8][2] = {{1, -2}, {2, -1}, {2, 1}, {1, 2}, {-1, 2}, {-2, 1}, {-2, -1}, {-1, -2}};
long long d[40][40], ud[40][40], cnt[40][40];
int g[40][40], head[40][40], vx[810000], vy[810000], nex[810000], tot, n, m, sx, sy, ex, ey;
bool inq[40][40], vis[40][40];

inline void add(int x, int y, int tx, int ty) {
	vx[tot] = tx; vy[tot] = ty; nex[tot] = head[x][y]; head[x][y] = tot++;
}

void dfs(int nx, int ny, int tx, int ty) {
	if(g[tx][ty] == 2 || g[tx][ty] == 3) return;
	if(g[tx][ty] == 0 || g[tx][ty] == 4) {
		add(nx, ny, tx, ty); return;
	}

	for(int i = 0; i < 8; i++) {
		int dx = mov[i][0], dy = mov[i][1];
		if(tx + dx < 0 || tx + dx >= n || ty + dy < 0 || ty + dy >= m) continue;
		if(!vis[tx+dx][ty+dy]) {
			vis[tx+dx][ty+dy] = true;
			dfs(nx, ny, tx+dx, ty+dy);
		}
	}
}

void spfa() {
	queue<pii> q;
	ud[sx][sy] = 1; d[sx][sy] = 0; inq[sx][sy] = true; cnt[sx][sy] = (long long)1;
	q.push(make_pair(sx, sy));
	while(!q.empty()) {
		int nx = q.front().first, ny = q.front().second; q.pop(); inq[nx][ny] = false;
		if(nx == ex && ny == ey) continue;
		for(int i = head[nx][ny]; i != -1; i = nex[i]) {
			int tx = vx[i], ty = vy[i], w = 1;
			if(!ud[tx][ty] || d[tx][ty] > d[nx][ny] + w) {
				ud[tx][ty] = 1; d[tx][ty] = d[nx][ny] + w; cnt[tx][ty] = cnt[nx][ny];
				if(!inq[tx][ty]) inq[tx][ty] = true, q.push(make_pair(tx, ty));
			} else if(ud[tx][ty] && d[tx][ty] == d[nx][ny] + w) {
				cnt[tx][ty] = cnt[tx][ty] + cnt[nx][ny];
				if(!inq[tx][ty]) inq[tx][ty] = true, q.push(make_pair(tx, ty));
			}
		}
		cnt[nx][ny] = (long long)0;
	}
}

int main() {
	scanf("%d %d", &n, &m);
	for(int i = 0; i < n; i++)
		for(int j = 0; j < m; j++) {
			scanf("%d", &g[i][j]);
			if(g[i][j] == 3) sx = i, sy = j;
			else if(g[i][j] == 4) ex = i, ey = j;
		}
	memset(ud, 0, sizeof(ud)); memset(inq, 0, sizeof(inq));
	memset(head, -1, sizeof(head));
	for(int i = 0; i < n; i++)
		for(int j = 0; j < m; j++)
			if(g[i][j] == 0 || g[i][j] == 3) {
				memset(vis, 0, sizeof(vis));
				vis[i][j] = true;
				for(int k = 0; k < 8; k++) {
					int dx = mov[k][0], dy = mov[k][1];
					if(i + dx < 0 || i + dx >= n || j + dy < 0 || j + dy >= m) continue;
					if(!vis[i+dx][j+dy]) {
						vis[i+dx][j+dy] = true;
						dfs(i, j, i+dx, j+dy);
					}
				}
			}
	memset(cnt, 0, sizeof(cnt));
	spfa();
	if(!ud[ex][ey]) printf("-1\n");
	else printf("%lld\n%lld\n", d[ex][ey]-1, cnt[ex][ey]);
	return 0;
}
```
### 欢迎互相关注(然而在oi界蒟蒻的圈很小)。
### 最后安利一下[蒟蒻的洛谷博客](https://www.luogu.org/blog/oldherd/)

---

## 作者：wurzang (赞：3)

md这题打得我手都流汗了

发现这题可以这样建图，对于一条边 $(u,v)$ ，如果 $v$ 是水那么就赋这条边的边权为 $1$，如果不是那么就赋 $0$，并且 $u$，$v$ 都不能是岩石。

题意转为最短路与最短路计数

发现有 $0$ 边就很不好搞，那么就把有 $0$ 边的一些节点合并在一起，直接 `dfs` 即可

非常奇怪的是我写了个并查集做法，挂了，写了 `dfs` 做法，又挂了，最后写了大概一两个小时才打出来，写一次挂一次，写到第十次左右的时候才过了样例，心态爆炸了


还有这题样例实在是太...人肉模拟的时候给整吐了

以下是代码：

```cpp
#include<bits/stdc++.h>
using namespace std;
int a[35][35],dfn[35][35],tot,simati[3535];
int di[8]={-2,-2,-1,-1,1,1,2,2};
int dj[8]={-1,1,-2,2,-2,2,-1,1};
queue<int> q;
int dis[30005],vis[30005];
long long cnt[30005];
vector<int> e[30005];
void spfa(int st){
	memset(dis,0x3f,sizeof(dis));
	q.push(st);dis[st]=0;cnt[st]=1;
	while(!q.empty()){
		int u=q.front();q.pop();
		vis[u]=0;
		for(int i=0;i<e[u].size();++i){
			int v=e[u][i];
			if(dis[v]>dis[u]+1){
				dis[v]=dis[u]+1;cnt[v]=cnt[u];
				if(!vis[v]) q.push(v),vis[v]=1;
			}
			else if(dis[v]==dis[u]+1) cnt[v]+=cnt[u];
		}
	}
}
int n,m;
int num(int i,int j){
	return (i-1)*m+j;
}
bool check(int i,int j){
	return 1<=i&&i<=n&&1<=j&&j<=m;
}
void dfs(int id,int i,int j){
	if(dfn[i][j]) return;
	dfn[i][j]=1;
	for(int k=0;k<8;++k){
		int ti=i+di[k],tj=j+dj[k];
		if(!check(ti,tj)) continue;
		if(dfn[ti][tj]) continue;
		//cout<<i<<" "<<j<<" "<<ti<<" "<<tj<<endl;
		if(a[ti][tj]==1) dfs(id,ti,tj);
		else if(a[ti][tj]!=2) dfn[ti][tj]=1,e[id].push_back(num(ti,tj));
	}
}
int main(){
	int st,ed;
	cin>>n>>m;
	for(int i=1;i<=n;++i)
		for(int j=1;j<=m;++j){
			cin>>a[i][j];
			if(a[i][j]==3) st=num(i,j);
			if(a[i][j]==4) ed=num(i,j);
		}
	for(int i=1;i<=n;++i)
		for(int j=1;j<=m;++j)
			if(a[i][j]==3||a[i][j]==0)
				memset(dfn,0,sizeof(dfn)),
				dfs(num(i,j),i,j);
	spfa(st);
	if(dis[ed]!=0x3f3f3f3f) cout<<dis[ed]-1<<endl<<cnt[ed];
	else cout<<-1;
	return 0;
}
```


---

## 作者：cghAndy (赞：3)

这道题挺好玩的 写个题解吧

一开始 你可能会想到直接bfs 但是 因为原本荷叶的存在 你会很烦

第一问还好说 统计方案数就GG

然后 你可能会想到把这些荷叶缩成连通块。。。

可是！！！！ 你又会发现有问题大哭

比如这种

0 0 y 0 0


1 0 0 0 1


0 0 x 0 0


x和y都是清水 从x去到y 可以经过左边的联通块去 可以经过右边的联通块去 答案有两种但其实就只有x，y放荷叶一种


是不是很TM爽！


最后 我来告诉你这个世界的真相微笑


因为它是统计放荷叶的方案数啊


我们可以去避免遇到那些原本存在的嘛  我们就预处理出每个起点以及水位置的花费1个荷叶能到的地方 然后建边 跑spfa就可以了~


为什么呢...因为这样就肯定没有环了 而且上面那种情况其实就是从x直接到y 就不怕算多情况了


觉得我的代码还是挺好看的（毕竟挺快的）


~~你看我写的那么辛苦 是不是要帮我水一波访问量~~ http://blog.csdn.net/cgh\_andy/article/details/52957019


---

## 作者：HRLYB (赞：2)

这几天写题是真的自闭，连图都不会建了

[P1606 [USACO07FEB]白银莲花池](https://www.luogu.org/problem/P1606)




## 解题思路

  
  
$bfs$预处理+状态连边建图+最短路算法求解

这是这类题一个非常重要的思想.

通过$bfs$建图将各个状态连接，然后用最短路算法求出最优的状态.

### $bfs$预处理+状态连边建图部分：

一开始我的想法很简单，就是每个点都进行$bfs$，处理出每个点能够到达的点.

```cpp
			if(j-2>=1&&i-1>=1){
				if(mp[i-1][j-2]!=2&&!check[num[i][j]][num[i-1][j-2]]){
					check[num[i][j]][num[i-1][j-2]]=true;
					check[num[i-1][j-2]][num[i][j]]=true;
					if(mp[i-1][j-2]==0||mp[i][j]==0)add(num[i][j],num[i-1][j-2],1);
					else add(num[i][j],num[i-1][j-2],0);
				}
			}//其中的一部分代码
```
但是这种方法不可行. 为什么呢？因为这样会有0边权边的出现. 这对于我们统计最短路数是非常不利的.

而且我们会发现一个问题：什么情况下的边应该赋值为1，什么情况应该赋值为0呢？这也是不清楚的. 

![在这里插入图片描述](https://img-blog.csdnimg.cn/2019090309415189.png?x-oss-process=image/watermark,type_ZmFuZ3poZW5naGVpdGk,shadow_10,text_aHR0cHM6Ly9ibG9nLmNzZG4ubmV0L3FxXzQ0NzY1NzEx,size_16,color_FFFFFF,t_70#pic_center)

>如图所示，如果按照如上代码的写法，会出现明明只需要2的值但却算出来3的情况，这就需要我们从同一个方向（这样才能真正反映需要填上荷叶的水的数量）统计.比如说我们如果只在指向点为0的时候总边权+1，那么答案就没有错

我们考虑上面那张图，可以发现，我们可以每个0节点为起点，预处理出花费1个荷叶能到达的点，这样就保证了边权全都为1.

同样地，由于每次我们都只是从当前点往前一个点，所以上述“同一个方向统计”的要求也满足. 只不过现在因为以每个0节点为起点，所以我们的“花费一个荷叶”指的就是用一个荷叶把我们0脚下的水填了.

不难发现，如此一来我们就要用$bfs$找到八个方向每个方向第一个不能不加荷叶跳过去的点（也就是0点）了.

```cpp
bool tocheck(int x,int y){
	if(x<1||y<1||x>n||y>m||mp[x][y]==2||vis[x][y])return false;//注意如果是mp=2即一块石头，跳过去是没有意义的
	return true;
}
void build_map(int x,int y,int u){
	for(int i=0;i<8;i++){
		int a=x+drc[i][0],b=y+drc[i][1];
		if(tocheck(a,b)){
			vis[a][b]=true;//防止重复走
			if(mp[a][b]==1)build_map(a,b,u);//如果当前还能不加荷叶继续走，那么就继续往前走
			else add(u,num[a][b]);//如果是终点mp=4的话，那么就连一条边过去好了；否则说明只加一个荷叶最多就只能走到mp=0的这个位置，要继续往前走，就要加荷叶了
		}
	}
	return ;
}
```
                          
                          
>相当于我们只计起点的0变成1，所以就保证了要填荷叶的水和每点间的边权等




### 最短路算法：P1606 [USACO07FEB]白银莲花池

由于我们需要在求最短路的同时求最短路的数目，那么这就是一个最短路计数问题了.

解题关键是，每一个点的最短路径数是由连接它的前一个点决定的.

>在边权为1的情况下$spfa$才成立，否则老老实实用$dp$吧

若还没学过最短路计数：[P1144 最短路计数](https://www.luogu.org/problemnew/show/P1144)

```cpp
bool check[1010];
int dis[1010];
ll sum[1010];
void spfa(int st){
	memset(dis,inf,sizeof dis);
	memset(check,false ,sizeof check);
	queue<int >q;
	q.push(st);
	check[st]=true;
	dis[st]=0;
	sum[st]=1;
	while(!q.empty()){
		int u=q.front();
		for(int i=head[u];i;i=e[i].next ){
			int v=e[i].v ;
			if(dis[v]>dis[u]+1){
				dis[v]=dis[u]+1;
				sum[v]=sum[u];//修改当前最短路数量，此时前面的记录都得推翻重做
				if(!check[v]){
					check[v]=true;
					q.push(v);
				}
			}
			else if(dis[v]==dis[u]+1)sum[v]+=sum[u];//根据加法原理，最短路数量增加
		}
		check[u]=false;
		q.pop();
	}
}
```


### 其他
编号方法：如表格

|1|2 |3|
|--|--|--|
|  4|5  |6|
|7|8|9|
|10|11|12|

```cpp
num[i][j]=(i-1)*m+j;
```

## 程序实现


```cpp
#include<bits/stdc++.h>
#define ll long long
#define inf 0x3f3f3f3f
using namespace std;
struct edge{
	int v,next;
}e[100010];//考虑30*30*k，k为可以直接到达的点，可能不止8个（一个可以外拓的子节点又可以有8个），所以数组尽量开大
int drc[8][2]={{-2,1},{2,-1},{-1,2},{1,-2},{-2,-1},{-1,-2},{2,1},{1,2}};//预设八个方向
int head[1010],tot;
int tx,ty,sx,sy;
int n,m,ans1;
ll ans2;
void add(int u,int v){
	e[++tot].v =v;
	e[tot].next =head[u];
	head[u]=tot;
}
int mp[51][51],num[51][51];
bool vis[51][51];
bool tocheck(int x,int y){
	if(x<1||y<1||x>n||y>m||mp[x][y]==2||vis[x][y])return false;
	return true;
}
void build_map(int x,int y,int u){
	for(int i=0;i<8;i++){
		int a=x+drc[i][0],b=y+drc[i][1];
		if(tocheck(a,b)){
			vis[a][b]=true;
			if(mp[a][b]==1)build_map(a,b,u);
			else add(u,num[a][b]);
		}
	}
	return ;
}//bfs+连边操作
void prepare(){
	for(int i=1;i<=n;i++){
		for(int j=1;j<=m;j++){
			if(!mp[i][j]||mp[i][j]==3){//找空节点或起点，起点多算的1在spfa后减回来就行了
				memset(vis,false ,sizeof vis);
				vis[i][j]=true;
				build_map(i,j,num[i][j]);
			}
		}
	}
}
bool check[1010];
int dis[1010];
ll sum[1010];//不开long long见祖先
void spfa(int st){
	memset(dis,inf,sizeof dis);
	memset(check,false ,sizeof check);
	queue<int >q;
	q.push(st);
	check[st]=true;
	dis[st]=0;
	sum[st]=1;
	while(!q.empty()){
		int u=q.front();
		for(int i=head[u];i;i=e[i].next ){
			int v=e[i].v ;
			if(dis[v]>dis[u]+1){
				dis[v]=dis[u]+1;
				sum[v]=sum[u];
				if(!check[v]){
					check[v]=true;
					q.push(v);
				}
			}
			else if(dis[v]==dis[u]+1)sum[v]+=sum[u];
		}
		check[u]=false;
		q.pop();
	}
}
int main(){
	scanf("%d%d",&n,&m);
	for(int i=1;i<=n;i++){
		for(int j=1;j<=m;j++){
			scanf("%d",&mp[i][j]);
			num[i][j]=(i-1)*m+j;
			if(mp[i][j]==3)sx=i,sy=j;
			if(mp[i][j]==4)tx=i,ty=j;
		}
	}
	prepare();
	spfa(num[sx][sy]);
	ans1=dis[num[tx][ty]];
	ans2=sum[num[tx][ty]];
	if(ans1==inf)printf("-1\n");
	else printf("%d\n%lld\n",ans1-1,ans2);//记得把起点的边多算的1减回来
	return 0;
}
```

## 题后总结

建图真的很重要！以后看到这一类型的题，就想一下可不可以建图抽象化地表示状态，然后通过最短路算法表示状态的改变，从而求解.

可以通过条件推知要建什么样的图，建的图没有一定的要求，不要产生定势思维. 比如说双向图啊，单向图啊，都是不一定的.

另外，送一道同为巧妙建图，然后使用最短路求解的题目：[P1979 华容道](https://www.luogu.org/problem/P1979)

~~双倍经验什么的是不可能的~~


---

## 作者：Porsche (赞：1)

数据过水，建议增强数据。
90%以上AC代码都能被下面这组数据卡掉
```
10 10
2 2 0 2 1 2 1 2 1 1 
0 0 0 0 2 2 0 2 2 2 
1 3 1 1 0 1 1 0 1 0 
1 1 0 4 0 2 1 2 1 1 
1 2 2 1 2 1 1 0 2 2 
2 0 1 1 0 2 2 2 0 1 
0 2 2 0 1 0 0 1 0 1 
2 1 1 2 0 1 2 2 1 1 
1 1 2 0 2 0 2 0 0 0
1 0 0 1 1 2 1 1 0 1
```
前两份题解更是被我校OJ极端数据卡到58分。

下面贴一份正确的代码：
```


#include<bits/stdc++.h>
using namespace std;
struct rec
{
	long long nxt;
	long long to;
	long long w;
}e[100000],ee[100000];
long long head[5000],cnt,headw[5000],cntw;
long long n,m;
long long st,ed;
long long Map[100][100],wzc[100][100];
long long dis[5000];
bool vis1[5000],vis2[5000],spfa[5000],con[5000][5000];
long long que[5000],h[5000][5000];
bool qj[5000][5000];
long long ans[5000];
void add(long long x,long long y,long long w)
{
	e[++cnt].nxt=head[x];
	e[cnt].to=y;
	e[cnt].w=w;
	head[x]=cnt;
}
void add_w(long long x,long long y)
{
	ee[++cntw].nxt=headw[x];
	ee[cntw].to=y;
	headw[x]=cntw;
}
void SPFA()
{
	queue<long long>q;
	q.push(st);
	spfa[st]=1;
	dis[st]=0;
	ans[st]=1;
	while(!q.empty())
	{
		long long flag=q.front();
		q.pop();
		spfa[flag]=0;
		for(long long i=headw[flag];i;i=ee[i].nxt)
			if(dis[ee[i].to]>dis[flag]+1)
			{
				dis[ee[i].to]=dis[flag]+1;
				ans[ee[i].to]=ans[flag];
				if(!spfa[ee[i].to])
				{
					q.push(ee[i].to);
					spfa[ee[i].to]=1;
				}
			}
			else if(dis[ee[i].to]==dis[flag]+1)ans[ee[i].to]+=ans[flag];
	}
}
void dfs1(long long x)
{
	vis1[x]=1;
	for(long long i=head[x];i;i=e[i].nxt)
	{
		if(!vis1[e[i].to])
		{
			if(e[i].w)que[++que[0]]=e[i].to;
			else dfs1(e[i].to);
		}
	}
}
void dfs2(long long x)
{
	vis2[x]=1;
	for(long long i=1;i<=que[0];i++)
		if(!con[x][que[i]])
		{
			h[x][++h[x][0]]=que[i];
			con[x][que[i]]=1;
		}
	for(long long i=head[x];i;i=e[i].nxt)
		if(!e[i].w&&!vis2[e[i].to])
			dfs2(e[i].to);
}
int main()
{
	for(long long i=1;i<=3000;i++)dis[i]=20020923002002092300;
	scanf("%lld%lld",&n,&m);
	for(long long i=1;i<=n;i++)
		for(long long j=1;j<=m;j++)
		{
			scanf("%lld",&Map[i][j]);
			wzc[i][j]=++wzc[0][0];
			if(Map[i][j]==3)
			{
				st=wzc[i][j];
				Map[i][j]=0;
			}
			if(Map[i][j]==4)
			{
				ed=wzc[i][j];
				Map[i][j]=0;
			}
		}
	for(long long i=1;i<=n;i++)
		for(long long j=1;j<=m;j++)
		{
			if(Map[i][j]==2)continue;
			if(i-1>0&&j-2>0&&Map[i-1][j-2]!=2)
			{
				if(Map[i-1][j-2])add(wzc[i][j],wzc[i-1][j-2],0);
				else add(wzc[i][j],wzc[i-1][j-2],1);
			}
			if(i-2>0&&j-1>0&&Map[i-2][j-1]!=2)
			{
				if(Map[i-2][j-1])add(wzc[i][j],wzc[i-2][j-1],0);
				else add(wzc[i][j],wzc[i-2][j-1],1);
			}
			if(i-1>0&&j+2<=m&&Map[i-1][j+2]!=2)
			{
				if(Map[i-1][j+2])add(wzc[i][j],wzc[i-1][j+2],0);
				else add(wzc[i][j],wzc[i-1][j+2],1);
			}
			if(i-2>0&&j+1<=m&&Map[i-2][j+1]!=2)
			{
				if(Map[i-2][j+1])add(wzc[i][j],wzc[i-2][j+1],0);
				else add(wzc[i][j],wzc[i-2][j+1],1);
			}
			if(i+1<=n&&j-2>0&&Map[i+1][j-2]!=2)
			{
				if(Map[i+1][j-2])add(wzc[i][j],wzc[i+1][j-2],0);
				else add(wzc[i][j],wzc[i+1][j-2],1);
			}
			if(i+2<=n&&j-1>0&&Map[i+2][j-1]!=2)
			{
				if(Map[i+2][j-1])add(wzc[i][j],wzc[i+2][j-1],0);
				else add(wzc[i][j],wzc[i+2][j-1],1);
			}
			if(i+1<=n&&j+2<=m&&Map[i+1][j+2]!=2)
			{
				if(Map[i+1][j+2])add(wzc[i][j],wzc[i+1][j+2],0);
				else add(wzc[i][j],wzc[i+1][j+2],1);
			}
			if(i+2<=n&&j+1<=m&&Map[i+2][j+1]!=2)
			{
				if(Map[i+2][j+1])add(wzc[i][j],wzc[i+2][j+1],0);
				else add(wzc[i][j],wzc[i+2][j+1],1);
			}
		}
	for(long long i=1;i<=n;i++)
		for(long long j=1;j<=m;j++)
			if(Map[i][j]==1&&!vis1[wzc[i][j]])
			{
				que[0]=0;
				dfs1(wzc[i][j]);
				memset(vis2,0,sizeof(vis2));
				dfs2(wzc[i][j]);
			}
	for(long long i=1;i<=n;i++)
		for(long long j=1;j<=m;j++)
		{
			if(Map[i][j]==2||Map[i][j]==1)continue;
			for(long long k=head[wzc[i][j]];k;k=e[k].nxt)
				if(e[k].w)
				{
					if(!qj[wzc[i][j]][e[k].to])
					{
						qj[wzc[i][j]][e[k].to]=1;
						add_w(wzc[i][j],e[k].to);
					}
				}
				else
				{
					for(long long l=1;l<=h[e[k].to][0];l++)
						if(!con[wzc[i][j]][h[e[k].to][l]]&&!qj[wzc[i][j]][h[e[k].to][l]])
						{
							qj[wzc[i][j]][h[e[k].to][l]]=1;
							add_w(wzc[i][j],h[e[k].to][l]);
							con[wzc[i][j]][h[e[k].to][l]]=1;
						}
				}
		}
	SPFA();
	if(dis[ed]==20020923002002092300)puts("-1");
	else cout<<dis[ed]-1<<endl<<ans[ed]<<endl;
	return 0;
}

```


---

## 作者：wwlw (赞：1)

[Link](https://www.luogu.org/problemnew/solution/P1606?page=2)

--------------

~~考场上把我送走的一道题~~

考试时，晃眼一看，这不是裸的最短路计数吗？！赶忙写好了代码，自信地关闭了文件。然后，0分……

那么回过头来，到底错在哪里？只有新加的荷叶才会被统计，而原来就有的荷叶不算在方案数里（学长把题目魔改了，并且说的不是很清楚，一直没搞懂样例，然后我就挂了）

那怎么样才能使得不把原来就有的荷叶作为状态算在方案数里？因为原来有的荷叶直接可以跳，不需要花费，所以不把它与它可以跳到的点连边，而是把它作为中转节点，把它可以到达的所有点互相连边，最后转化为最短路计数。

可是就这样过了吗？并没有，还有一种情况没有考虑。就是两个原本就有的荷叶可以相互到达的情况，此时就相当于有两个中转节点，需要把它们可以到达的至多16个点互相连边（此过程可以用bfs解决）。如果是三个及三个以上呢？以此类推罢了。

--------------

Code:
```cpp
#include<stdio.h>
#include<string.h>
#include<queue>
using namespace std;
#define ll long long
#define INF 0x3f3f3f3f
#define N 100

template<class T>
inline void read(T &x){
	x=0;char c=getchar();T flag=1;
	while(c<'0'||c>'9'){if(c=='-')flag=-1;c=getchar();}
	while(c>='0'&&c<='9'){x=(x<<1)+(x<<3)+c-48;c=getchar();}
	x*=flag;
}

struct E{
	int next,to;
	ll dis;
}e[(N*N)<<4];

int dx[10]={-2,-2,-1,-1,1,1,2,2},
	dy[10]={-1,1,-2,2,-2,2,-1,1};
int n,m,a[N][N],s,t,top,sta[N*N],head[N*N],cnt;
bool in[N*N],vis[N*N],mark[N*N][N*N];
ll dis[N*N],ans[N*N];
queue<int> Q;

inline bool check(int x,int y){
	if(x<1||x>n||y<1||y>m) return 0;
	if(a[x][y]==2) return 0;
	return 1;
}
inline void add(int id,int to,int dis){
	e[++cnt]=(E){head[id],to,dis};
	head[id]=cnt;
} 
void dfs(int x,int y){
	for(int op=0;op<8;op++){
		int xx=x+dx[op],yy=y+dy[op];
		if(!check(xx,yy)) continue;
		if(!a[xx][yy]&&!in[(xx-1)*m+yy]){
			in[(xx-1)*m+yy]=1;
			sta[++top]=(xx-1)*m+yy;
		}
		if(a[xx][yy]==1&&!vis[(xx-1)*m+yy]){
			vis[(xx-1)*m+yy]=1;
			dfs(xx,yy);
		}
	}
}
void bfs(){
	memset(dis,INF,sizeof(dis));
	memset(vis,0,sizeof(vis));
	Q.push(s);
	ans[s]=1,dis[s]=0,vis[s]=1;
	while(!Q.empty()){
		int u=Q.front();Q.pop();
		for(int i=head[u];i;i=e[i].next){
			int v=e[i].to;
			if(dis[v]==dis[u]+e[i].dis){
				ans[v]+=ans[u];
				if(!vis[v]&&v!=t){
					vis[v]=1;
					Q.push(v);
				}
			}
			if(dis[v]>dis[u]+e[i].dis){
				dis[v]=dis[u]+e[i].dis;
				ans[v]=ans[u];
				if(!vis[v]&&v!=t){
					vis[v]=1;
					Q.push(v);
				}
			}
		}
	}
}
int main(){
//	freopen("chess.in","r",stdin);
//	freopen("chess.out","w",stdout);
	read(n),read(m);
	for(int i=1;i<=n;i++)
		for(int j=1;j<=m;j++){
			read(a[i][j]);
			if(a[i][j]==3){
				s=(i-1)*m+j;
				a[i][j]=0;
			}
			if(a[i][j]==4){
				t=(i-1)*m+j;
				a[i][j]=0;
			}
		}
	for(int i=1;i<=n;i++)
		for(int j=1;j<=m;j++){
			if(a[i][j]) continue;
			for(int op=0;op<8;op++){
				int x=i+dx[op],y=j+dy[op];
				if(check(x,y)&&(!a[x][y]))
					add((i-1)*m+j,(x-1)*m+y,1);
			}
		}
	for(int i=1;i<=n;i++)
		for(int j=1;j<=m;j++)
			if(a[i][j]==1&&(!vis[(i-1)*m+j])){
				top=0;
				memset(in,0,sizeof(in));
				vis[(i-1)*m+j]=1;
				dfs(i,j);
				for(int k=1;k<=top;k++)
					for(int p=k+1;p<=top;p++)
						if(!mark[sta[k]][sta[p]]){
							mark[sta[k]][sta[p]]=mark[sta[p]][sta[k]]=1;
							add(sta[k],sta[p],1),add(sta[p],sta[k],1);
						}
			}
	bfs();
	if(!ans[t]) printf("-1");
	else printf("%lld\n%lld",dis[t]-1,ans[t]);
}
/*
3 4
3 0 0 0
0 0 1 4
2 2 2 0
*/
```

---

## 作者：LlLlCc (赞：0)

**最短路计数**的变形题

第一问很容易，对于每个点向各个方向建边，如果目标点是石头或终点就建$0$边，如果是杂草就建$1$边，花则跳过。建好图后从起点到终点跑一遍最短路就$OK$了，$n,m\leq 30$，想怎么刷就怎么刷

所以第二问也是这样建图然后跑最短路计数？

然后就愉快的$WA$了

为什么呢？

容易发现，这样建图都是双向边，也就是说会出现$0$环

看式子：

$if\;dis_v=dis_u+w_i\;:\;cnt_v+=cnt_u$

$if\;dis_v>dis_u+w_i\;:\;dis_v=dis_u+w_i,cnt_v=cnt_u$

因为更新最短路是小于号，$0$环是不会影响最短路的，但更新最短路数量是等于号，所以$0$环会影响最短路计数，所以我们不能让图中出现$0$边， 让每条边都强制为$1$

即对每个点用$dfs$搜索一遍，有哪些点是放一块石头能到的，然后连$1$的边，这样刷最短路计数就不会出问题

## code
```
#include<bits/stdc++.h>
#define maxn 1005
#define maxe 1000005
#define ll long long
using namespace std;
const int flg[8][2]={{1,2},{-1,2},{1,-2},{-1,-2},{2,1},{-2,1},{2,-1},{-2,-1}};
int n,m,X,Y,Xx,Yy,Ans,x,Q[maxe],y,lnk[maxn],w[maxe],nxt[maxe],son[maxe],tot,a[maxn][maxn];
bool vis[maxn],v[35][35];
ll G[maxn],dis[maxn];
inline int read(){
	int ret=0;char ch=getchar();
	while (ch<'0'||ch>'9') ch=getchar();
	while (ch<='9'&&ch>='0') ret=ret*10+ch-'0',ch=getchar();
	return ret;
}
inline int Get(int x,int y){return (x-1)*m+y;}
inline void add(int x,int y){nxt[++tot]=lnk[x];lnk[x]=tot;son[tot]=y;}
inline void Spfa(int S,int T){
	for (int i=1;i<=n*m;i++) dis[i]=1e16;
	dis[S]=0,G[S]=1;int hed=0,til=1;ll INF=1e16;Q[1]=S;
	while (hed<til){
		hed=(hed+1)%maxe;vis[Q[hed]]=0;
		for (int i=lnk[Q[hed]];i;i=nxt[i])
		  if (dis[son[i]]==dis[Q[hed]]+1) G[son[i]]+=G[Q[hed]];
	      else if (dis[son[i]]>dis[Q[hed]]+1){
	      	dis[son[i]]=dis[Q[hed]]+1;
	      	G[son[i]]=G[Q[hed]];
	      	if (!vis[son[i]]) Q[til=(til+1)%maxe]=son[i],vis[son[i]]=1;
		  }
	}
	if (dis[T]==INF){printf("-1");exit(0);}
	return;
}
inline bool check(int x,int y){return x<1||x>n||y<1||y>m||a[x][y]==2||a[x][y]==3;}
inline void Dfs(int S,int x,int y){
    v[x][y]=1;
    for (int i=0;i<8;i++){
    	int X=x+flg[i][0],Y=y+flg[i][1];
    	if (check(X,Y)||v[X][Y]) continue;
    	if (a[X][Y]==1) Dfs(S,X,Y);
    	else v[X][Y]=1,add(S,Get(X,Y));
	}
}
int main(){
	n=read(),m=read();
	for (int i=1;i<=n;i++)
	for (int j=1;j<=m;j++) a[i][j]=read();
    for (int i=1;i<=n;i++)
    for (int j=1;j<=m;j++){
    	if (a[i][j]&&a[i][j]<=2) continue;
    	if (a[i][j]==4){Xx=i,Yy=j;continue;}
    	if (a[i][j]==3) X=i,Y=j;
    	memset(v,0,sizeof v);Dfs(Get(i,j),i,j);
	}
	Spfa(Get(X,Y),Get(Xx,Yy));
    printf("%lld\n%lld",dis[Get(Xx,Yy)]-1,G[Get(Xx,Yy)]);
    return 0;
}
```


---

