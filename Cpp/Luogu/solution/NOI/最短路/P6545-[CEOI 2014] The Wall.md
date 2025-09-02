# [CEOI 2014] The Wall

## 题目背景

CEOI2014 Day2 T3，译者：小粉兔

## 题目描述

Rectos 岛经常遭受洪水的泛滥和海盗的侵扰，所以 Rectos 的国王想要建造一堵城墙以保护岛上所有的村庄。

Rectos 是一个矩形岛屿，所以城墙的设计师将岛屿看作一个正方形网格。每个村庄都位于其中的某个方格中，并且首都村庄位于整座岛的西北角，也就是最左上角的方格中。

必须保证从外部（也就是整个网格的外部）在不越过城墙的条件下，是到达不了任何一个村庄的。

设计师计划城墙将只沿着网格线建造，更具体地说是按照如下方法：他将第一段城墙置于最左上角延伸出的两条网格线之一上，并且下一段城墙总是和上一段城墙首尾相连，不断重复这一过程直到又一次回到最左上角为止。这一过程可能会导致一段网格线上放置了大于一段的城墙，总而言之，城墙是沿着网格线上的一条连续闭曲线建造的。

地势测量表明，在每一段网格线上建造一段城墙都需要一定的花费。建造城墙的总花费就是建造每一段城墙的花费之和。如果在某一段网格线上建造了 $t$ 段城墙，则花费也要重复计算 $t$ 次。

国王想要花费尽量少的钱建好城墙。请你帮助国王，编写一个程序，给出村庄的位置以及每一段网格线上的建造花费，计算建造城墙所需最小的花费。

## 说明/提示

**【样例 #1 解释】**

![](https://cdn.luogu.com.cn/upload/image_hosting/njtyjnbp.png)

**【样例 #2 解释】**

![](https://cdn.luogu.com.cn/upload/image_hosting/568orkwb.png)

**【数据范围与提示】**

对于所有数据，保证 $1 \le n, m \le 400$，对于所有的建造花费 $v$，有 $1 \le v \le {10}^9$。

| 子任务编号 | 分值 | 特殊限制 |
| :-: | :-: | :-: |
| $1$ | $30$ | $n, m \le 40$ 且村庄的数量不超过 $10$ |
| $2$ | $30$ | $n, m \le 40$ |
| $3$ | $40$ | 无特殊限制 |

## 样例 #1

### 输入

```
3 3
1 0 0
1 0 0
0 0 1
1 4 9 4
1 6 6 6
1 2 2 9
1 1 1
4 4 4
2 4 2
6 6 6```

### 输出

```
38```

## 样例 #2

### 输入

```
3 3
1 0 1
0 0 0
0 1 0
2 1 1 3
5 6 1 1
2 1 1 3
2 1 1
3 4 1
4 1 1
5 1 2```

### 输出

```
22```

# 题解

## 作者：yzc2005 (赞：20)

# 一、定义
- **点**：每个方格的四个角
- 一种筑墙方案的**区域**：被墙框柱的点集

我们的任务即是要确定一种合法的筑墙方案（其区域包含了所有关键方格的四个角），使得筑墙的代价最小
# 二、引理
- 此筑墙方案一定包含最左上角的点到每个方格的左上角的点的最短路。

- 证明：

我们用归纳调整的思想。假设我们**已经**求出一个合法的筑墙方案，且存在一个关键方格 $u$，满足左上角到此点左上角的最短路不被包含在区域内。显然地，此最短路一定被这道墙分割成了若干段，在墙内的段和在墙外的段交替出现。我们把区域扩展到在墙外的段（即用这部分在墙外的段**代替**连接这一段两端点的墙的部分），相当于把原墙和最短路部分**合并**。这样，不仅墙的区域扩大了，而且**由最短路的定义**，新方案的代价肯定**不劣**于原方案。于是新的方案肯定不劣。一直这样调整下去直到无法继续进行优化，最终得到的结果便满足原命题的任意一个状态。

引理即得证。

![](https://cdn.luogu.com.cn/upload/image_hosting/ihmcqcgf.png)

# 三、做法

现在我们的任务就是，给定一些最短路，求出包含这些最短路（即墙的区域包含所有最短路上的点）的方案的最小代价。

又因为所有最短路构成了一棵最短路树，所以我们只要满足筑墙方案**不穿过**最短路即可。考虑把每一个点再拆成四个小点（一个方格对应 16 个点），在原图基础上再在相邻的、**不穿过任意一条最短路树**的边两点之间连一条边权为 0 的边，跑最短路即可。

![](https://cdn.luogu.com.cn/upload/image_hosting/ofy6s9ch.png)

# 四、代码

实在太难实现了，先鸽子了.jpg（


---

## 作者：Exber (赞：9)

首先有个结论，**筑的墙一定会把 $(1,1)$ 到所有别的关键点的左上角的最短路都围进去**。例如：

![](https://cdn.luogu.com.cn/upload/image_hosting/njbo3wd9.png)

若当前墙包含的是深蓝色区域，而 $(1,1)$ 到关键点 $u$ 的左上角的最短路是绿色的线，那么显然把浅蓝色区域也包含进墙里是更优的，因为红色段肯定是比代替它的五小段绿色段的长度和要长的，因为绿色的线是最短路。

**为什么是左上角？**其实**四个角都没关系**，这个之后再证明。

求出了 $(1,1)$ 到别的关键点的左上角的最短路之后，问题就转化为最小化筑墙的花费，使得筑出的墙可以圈住所有的最短路和关键点。

那么考虑**把一个网格线的交点都拆成四个点，点之间顺时针连边权为 $0$ 的有向边，属于不同交点的点之间连边权为原权值的有向边**，但是要注意**经过关键点和最短路的边都不能连**：

![](https://cdn.luogu.com.cn/upload/image_hosting/7pge7w6m.png)

容易发现，这样建好图之后，从网格左上角的交点拆出来的 $1$ 号点出发，走到它的 $3$ 号点，就能筑出合法的墙。那么花费最小的方案显然就是这两点之间的最短路。

最后说一下之前留下来的悬念：

>为什么要走到左上角？？？为什么走到哪个角都没关系？？？

不妨先钦定一定从左上角那个关键点的左上角出发，显然**走到右上角的最短路一定“围着”走到左上角的最短路**，即绿色的线不可能越过红色的线再回来，因为那样不优。

那么分两种情况讨论：

- 走到左上角的最短路**是**先走到右上角再往左走：

  ![](https://cdn.luogu.com.cn/upload/image_hosting/dbig07s2.png)

  这时由于最后筑的墙要包含所有关键点，所以左上角和右上角之间的那条边不会被筑墙，也就是说，红线和绿线有用的部分是完全相等的，那么自然对答案没有任何影响；

- 走到左上角的最短路**不是**先走到右上角再往左走：

  ![](https://cdn.luogu.com.cn/upload/image_hosting/jhra5dtg.png)

  这时考虑最后跑的最短路，即筑的墙，用紫色的线标识。显然，由于走到左上角的最短路不是先走到右上角再往左走，所以走左上角和右上角的那条边一定是不优的；并且走红线和绿线中间也是不优的，因为红线和绿线是最短路。那么最终的墙只有可能是这样：

  ![](https://cdn.luogu.com.cn/upload/image_hosting/iyknhdig.png)

  所以对最终的答案没有影响；

参考这样的证明方法，容易得出从哪个角出发，走到哪个角都是没有任何关系的。所以为了好写，干脆直接钦定从左上角开始和结束。

代码如下：

```cpp
#include <iostream>
#include <cstdio>
#include <cstring>
#include <queue>

using namespace std;

const int S=5000005,MS=405;

int n,m;
int a[MS][MS];
long long dnval[MS][MS],rgval[MS][MS];
int esum,to[S],nxt[S],h[S];
long long c[S],dis[S];
bool vis[S];
bool dntag[MS][MS],rgtag[MS][MS];

inline int getid(int x,int y)
{
	return (x-1)*(m+1)+y;
}

inline int getx(int id)
{
	return (id-1)/(m+1)+1;
}

inline int gety(int id)
{
	return (id-1)%(m+1)+1;
}

inline void add(int x,int y,long long w)
{
	to[++esum]=y;
	c[esum]=w;
	nxt[esum]=h[x];
	h[x]=esum;
}

inline void dijkstra(int s)
{
	memset(dis,127,sizeof(dis));
	memset(vis,0,sizeof(vis));
	dis[s]=0;
	priority_queue<pair<long long,int> > q;
	q.push(make_pair(-dis[s],s));
	while(!q.empty())
	{
		int u=q.top().second;
		q.pop();
		if(vis[u]) continue;
		vis[u]=true;
		for(int i=h[u];i;i=nxt[i])
		{
			int v=to[i];
			long long w=c[i];
			if(dis[u]+w<dis[v])
			{
				dis[v]=dis[u]+w;
				q.push(make_pair(-dis[v],v));
			}
		}
	}
}

void dfs(int u)
{
	vis[u]=true;
	for(int i=h[u];i;i=nxt[i])
	{
		int v=to[i];
		long long w=c[i];
		if(dis[u]==dis[v]+w)
		{
			int ux=getx(u),uy=gety(u),vx=getx(v),vy=gety(v);
			if(vx!=ux) dntag[min(ux,vx)][uy]=true;
			else rgtag[ux][min(uy,vy)]=true;
			if(!vis[v]) dfs(v);
			break;
		}
	}
}

int main()
{
	scanf("%d%d",&n,&m);
	for(int i=1;i<=n;i++) for(int j=1;j<=m;j++) scanf("%d",&a[i][j]);
	for(int i=1;i<=n;i++)
	{
		for(int j=1;j<=m+1;j++)
		{
			scanf("%lld",&dnval[i][j]);
			int idu=getid(i,j),idv=getid(i+1,j);
			add(idu,idv,dnval[i][j]);
			add(idv,idu,dnval[i][j]);
		}
	}
	for(int i=1;i<=n+1;i++)
	{
		for(int j=1;j<=m;j++)
		{
			scanf("%lld",&rgval[i][j]);
			int idu=getid(i,j),idv=getid(i,j+1);
			add(idu,idv,rgval[i][j]);
			add(idv,idu,rgval[i][j]);
		}
	}
	dijkstra(getid(1,1));
	memset(vis,0,sizeof(vis));
	for(int i=1;i<=n;i++) for(int j=1;j<=m;j++) if(a[i][j]==1&&!vis[getid(i,j)]) dfs(getid(i,j));
	esum=0;
	memset(h,0,sizeof(h));
	for(int i=1;i<=n+1;i++)
	{
		for(int j=1;j<=m+1;j++)
		{
			int bg=(getid(i,j)-1)*4;
			int _0=bg+1,_1=bg+2,_2=bg+3,_3=bg+4;
			if(!dntag[i-1][j]&&a[i-1][j-1]==0&&a[i-1][j]==0) add(_0,_1,0);
			if(!rgtag[i][j]&&a[i-1][j]==0&&a[i][j]==0) add(_1,_2,0);
			if(!dntag[i][j]&&a[i][j]==0&&a[i][j-1]==0) add(_2,_3,0);
			if(!rgtag[i][j-1]&&a[i][j-1]==0&&a[i-1][j-1]==0) add(_3,_0,0);
			if(i>1)
			{
				int ubg=(getid(i-1,j)-1)*4;
				int u2=ubg+3,u3=ubg+4;
				add(u2,_1,dnval[i-1][j]);
				add(_0,u3,dnval[i-1][j]);
			}
			if(j>1)
			{
				int lbg=(getid(i,j-1)-1)*4;
				int l1=lbg+2,l2=lbg+3;
				add(l1,_0,rgval[i][j-1]);
				add(_3,l2,rgval[i][j-1]);
			}
		}
	}
	dijkstra(2);
	printf("%lld\n",dis[4]);
	return 0;
}
```



---

## 作者：Rubyonly (赞：5)

## 题解

一开始以为是神仙插头 $dp$，发现环可以**自交**，插头 $dp$ 就不是很可做了

不妨考虑一下最短路，容易发现从 $(1,1)$ 到每个 $UFO$ 的左上角的最短路径要么被包含，要么作为了边界

然后建一棵以 $(1,1)$ 为根的最短路径树，树上的边就是我们要求的若干条最短路径

问题是怎么从 $(1,1)$ 出去再回来，不妨去拆点

将一个点拆成左上、右上、左下、右下四个点，正常的点四个点互相建一条边权为 $0$ 的边，原图中存在的边正常建就行

但是我们要保证不能穿过那若干条最短路径，也不能穿过每个 $UFO$ 矩形的四条边，建出图来跑一遍从 $(1,1)$ 右上到 $(1,1)$ 左下的最短路就行了

也要注意 $(1,1)$ 的四个点，左上不能向右上和左下连边，不然最后答案就是 $0$ 了

## 代码

```c++
#include <cstdio>
#include <cstring>
#include <iostream>
#include <algorithm>
#include <queue>

typedef long long ll;

using namespace std;

const ll INF = 0x3f3f3f3f3f3f3f3f;

inline int read () {
	register int x = 0, w = 1;
	register char ch = getchar ();
	for (; ch < '0' || ch > '9'; ch = getchar ()) if (ch == '-') w = -1;
	for (; ch >= '0' && ch <= '9'; ch = getchar ()) x = x * 10 + ch - '0';
	return x * w;
}

int n, m, nodecnt;
int dx[4] = {-1, 0, 1, 0};
int dy[4] = {0, 1, 0, -1};
int w1[405][405], w2[405][405], id[405][405][5];
bool a[405][405], black[405][405][4];

inline int ID (register int x, register int y) { return (x - 1) * (m + 1) + y; }

struct Edge {
	int to, next, w;
} e[8000005];

struct Node {
	int id;
	ll dis;
	Node () {}
	Node (register int a, register ll b) { id = a, dis = b; }
	friend bool operator < (const Node &x, const Node &y) { return x.dis > y.dis; }
};

int tot, head[2000005];

inline void Add (register int u, register int v, register int w) {
	e[++ tot].to = v;
	e[tot].w = w;
	e[tot].next = head[u];
	head[u] = tot;
}

ll dis[2000005];
int from[2000005];
bool vis[2000005];
priority_queue <Node> q;

inline void Dijkstra (register int x) {
	memset (dis, 0x3f, sizeof dis), memset (vis, 0, sizeof vis), q.push (Node (x, 0)), dis[x] = 0;
	while (! q.empty ()) {
		register Node t = q.top (); q.pop ();
		register int u = t.id;
		if (vis[u]) continue;
		vis[u] = 1;
		for (register int i = head[u]; i; i = e[i].next) {
 			register int v = e[i].to;
			if (dis[v] > dis[u] + e[i].w) dis[v] = dis[u] + e[i].w, from[v] = u, q.push (Node (v, dis[v]));
		}
	}
}

inline void FindPath (register int u) {
	while (u != 1) {
		register int v = from[u], x = (u - 1) / (m + 1) + 1, xx = (v - 1) / (m + 1) + 1, y = u % (m + 1) ? u % (m + 1) : m + 1, yy = v % (m + 1) ? v % (m + 1) : m + 1;
		if (u - v == m + 1) black[x][y][0] = black[xx][yy][2] = 1;
		else if (v - u == m + 1) black[x][y][2] = black[xx][yy][0] = 1;
		else if (u - v == 1) black[x][y][3] = black[xx][yy][1] = 1;
		else if (v - u == 1) black[x][y][1] = black[xx][yy][3] = 1;
		u = v;
	}
}

inline void Init () {
	for (register int i = 1; i <= n; i ++) for (register int j = 1; j <= m; j ++) a[i][j] = read();
	for (register int i = 1; i <= n; i ++) for (register int j = 1; j <= m + 1; j ++) w1[i][j] = read(), Add (ID (i, j), ID (i + 1, j), w1[i][j]), Add (ID (i + 1, j), ID (i, j), w1[i][j]);
	for (register int i = 1; i <= n + 1; i ++) for (register int j = 1; j <= m; j ++) w2[i][j] = read(), Add (ID (i, j), ID (i, j + 1), w2[i][j]), Add (ID (i, j + 1), ID (i, j), w2[i][j]);
	Dijkstra (1);
	for (register int i = 1; i <= n; i ++) for (register int j = 1; j <= m; j ++) if (a[i][j]) FindPath (ID (i, j));
}

inline void Build () {
	tot = 0, memset (head, 0, sizeof head);	
	for (register int i = 1; i <= n + 1; i ++) {
		for (register int j = 1; j <= m + 1; j ++) {
			id[i][j][1] = ++ nodecnt, id[i][j][2] = ++ nodecnt, id[i][j][3] = ++ nodecnt, id[i][j][4] = ++ nodecnt;
			if (! black[i][j][0] && ! a[i - 1][j - 1] && ! a[i - 1][j] && (i != 1 || j != 1)) Add (id[i][j][1], id[i][j][2], 0), Add (id[i][j][2], id[i][j][1], 0);
			if (! black[i][j][1] && ! a[i - 1][j] && ! a[i][j]) Add (id[i][j][2], id[i][j][3], 0), Add (id[i][j][3], id[i][j][2], 0);
			if (! black[i][j][2] && ! a[i][j - 1] && ! a[i][j]) Add (id[i][j][3], id[i][j][4], 0), Add (id[i][j][4], id[i][j][3], 0);
			if (! black[i][j][3] && ! a[i - 1][j - 1] && ! a[i][j - 1] && (i != 1 || j != 1)) Add (id[i][j][4], id[i][j][1], 0), Add (id[i][j][1], id[i][j][4], 0);
		}
	}
	for (register int i = 1; i <= n + 1; i ++) {
		for (register int j = 1; j <= m + 1; j ++) {
			for (register int k = 0; k <= 3; k ++) {
				register int xx = i + dx[k], yy = j + dy[k];
				if (xx <= 0 || yy <= 0 || xx > n + 1 || yy > m + 1) continue;
				if (k == 0) Add (id[i][j][1], id[xx][yy][4], w1[xx][yy]), Add (id[i][j][2], id[xx][yy][3], w1[xx][yy]);
				else if (k == 1) Add (id[i][j][2], id[xx][yy][1], w2[i][j]), Add (id[i][j][3], id[xx][yy][4], w2[i][j]);
				else if (k == 2) Add (id[i][j][3], id[xx][yy][2], w1[i][j]), Add (id[i][j][4], id[xx][yy][1], w1[i][j]);
				else if (k == 3) Add (id[i][j][1], id[xx][yy][2], w2[xx][yy]), Add (id[i][j][4], id[xx][yy][3], w2[xx][yy]);
			}
		}
	}
}

int main () {
	n = read(), m = read(), Init (), Build (), Dijkstra (2), printf ("%lld\n", dis[4]);
	return 0;
}
```

---

## 作者：NY2025 (赞：1)

## $\text{Task}$

题目链接：[[CEOI 2014] The Wall](https://www.luogu.com.cn/problem/P6545)

给定网格图上若干关键点与每条边的边权，格子 $(1,1)$ 一定为关键点，求包围所有关键点的一个多边形（不一定为简单多边形）的最小边权和。

## $\text{Solution}$

约定：对于**格子** $(x,y)$，其四个顶点的**格点**坐标分别为：

- 左上角：$(x-1,y-1)$
- 左下角：$(x,y-1)$
- 右上角：$(x-1,y)$
- 右下角：$(x,y)$

最小边权和提示到解法应该是**最短路**，因此可以将路径视作从格点 $(0,0)$ 出发回到自身的一条回路。

这样的转换即可解决多边形的限制，只用考虑怎样使得回路包围所有关键点。

首先给出结论：

- 在最小边权的要求下，要是回路包含关键点 $(x,y)$，则必使回路完全包含关键点 $(x,y)$ 四个顶点到起点 $(0,0)$ 的最短路径。

说明：若回路不包含这样的最短路径，即最短路径的某一部分在回路之外，用最短路径在回路之外的部分替换当前路径对应部分，则路径总长度减少且包围的面积扩大，比原方案更优。

再考虑如何使得最短路径一定被包含，显然只需使回路与所有被标记出的最短路径不相交即可。

于是通过拆点处理，将每个格点拆分为四个小点，按下图方式连边：

![](https://cdn.luogu.com.cn/upload/image_hosting/1jfb9o60.png)

即四个小点间若没有被标记出的最短路径边则顺时针相连，否则不连边。

答案即为从 $(0,0)$ 拆出的左上角顶点出发，回到左下角顶点的最短路径。

## $\text{Code}$

```c++
#include <bits/stdc++.h>
using namespace std;

namespace IO {
	int len = 0;
	char ibuf[(1<<20)+1], *iS, *iT, out[(1<<25)+1];
#define gh()\
	(iS==iT?iT=(iS=ibuf)+fread(ibuf,1,(1<<20)+1,stdin), \
	(iS==iT?EOF:*iS++):*iS++)
#define reg register
	inline int read() {
		reg char ch = gh();
		reg int x = 0;
		reg char t = 0;
		while (ch < '0' || ch > '9') t |= ch=='-', ch = gh();
		while (ch >= '0' && ch <= '9') x = x*10+(ch^48), ch=gh();
		return t ? -x : x;
	}
	inline void putc(char ch) {
		out[len++] = ch;
	}
	template <class T> inline void write(T x) {
		if (x < 0) putc('-'), x=-x;
		if (x > 9) write(x/10);
		out[len++] = x%10+48;
	}
	inline void flush() {
		fwrite(out, 1, len, stdout);
		len = 0;
	}
}
using namespace IO;

typedef long long LL;
const int N = 410;
const int M = N*N;
#define I inline

int n, m;
int mat[N][N], a[N][N], b[N][N]; // * a: 纵向边权 b: 横向边权
bool mark1[N][N], mark2[N][N];
/*
 * mark1: 横向边是否为最短路边
 * mark2: 纵向边是否为最短路边
*/

template<const int MAXN> class Graph {
private:
    struct Edge { int to, w, next; } e[MAXN*5];
    int head[MAXN], cnt;
    struct Node {
        int x; LL d;
        I friend bool operator < (const Node& x, const Node& y) {
            return x.d > y.d;
        }
    };
    priority_queue<Node> q;
public:
    LL dis[MAXN];
    int vis[MAXN], pre[MAXN];
    I void init() {
        memset(head, -1, sizeof head);
        cnt = 0;
    }
    I void add(int u, int v, int w) {
        e[cnt] = Edge{v, w, head[u]};
        head[u] = cnt++;
    }
    I void dijkstra(int s) {
        memset(dis, 63, sizeof dis);
        memset(vis, 0, sizeof vis);
        memset(pre, -1, sizeof pre);
        q.push(Node{s, dis[s] = 0});
        while (!q.empty()) {
            int u = q.top().x;
            q.pop();
            if (vis[u]) continue;
            vis[u] = true;
            for (int i = head[u]; ~i; i = e[i].next) {
                int v = e[i].to, w = e[i].w;
                if (dis[u]+w < dis[v]) {
                    pre[v] = u;
                    q.push(Node{v, dis[v] = dis[u]+w});
                }
            }
        }
    }
};

namespace FindPath {
    Graph<M> G1;
    int idx[N][N], R[M], C[M], tot;
    void init() {
        for (int i = 0; i <= n; i++) {
            for (int j = 0; j <= m; j++) {
                idx[i][j] = ++tot;
                R[tot] = i; C[tot] = j;
            }
        }
    }
    void solve() {
        G1.init();
        for (int i = 0; i < n; i++) {
            for (int j = 0; j <= m; j++) {
                G1.add(idx[i][j], idx[i+1][j], a[i][j]);
                G1.add(idx[i+1][j], idx[i][j], a[i][j]);
            }
        }
        for (int i = 0; i <= n; i++) {
            for (int j = 0; j < m; j++) {
                G1.add(idx[i][j], idx[i][j+1], b[i][j]);
                G1.add(idx[i][j+1], idx[i][j], b[i][j]);
            }
        }
        G1.dijkstra(idx[0][0]);
        for (int i = 1; i <= n; i++) {
            for (int j = 1; j <= m; j++) {
                if (!mat[i][j]) continue;
                int u = idx[i-1][j-1]; // * 左上角点位置
                mark1[i-1][j-1] = true; mark1[i][j-1] = true;
                mark2[i-1][j-1] = true; mark2[i-1][j] = true; // ! 关键点四周的边不可被穿过
                while (G1.pre[u] != -1) {
                    if (G1.pre[u]-u == 1) mark1[R[u]][C[u]] = true;
                    else if (u-G1.pre[u] == 1) mark1[R[u]][C[u]-1] = true;
                    else if (G1.pre[u]-u == m+1) mark2[R[u]][C[u]] = true;
                    else mark2[R[u]-1][C[u]] = true;
                    u = G1.pre[u];
                }
            }
        }
    }
}

namespace GetAnswer {
    Graph<M*4> G2;
    int idx[N][N][4], tot;
    void init() {
        for (int i = 0; i <= n; i++) {
            for (int j = 0; j <= m; j++) {
                idx[i][j][0] = ++tot; idx[i][j][1] = ++tot;
                idx[i][j][2] = ++tot; idx[i][j][3] = ++tot;
            }
        }
    }
    void solve() {
        G2.init();
        for (int i = 0; i <= n; i++) {
            for (int j = 0; j <= m; j++) {
                if (!i || !mark2[i-1][j]) G2.add(idx[i][j][0], idx[i][j][1], 0);
                if (j == m || !mark1[i][j]) G2.add(idx[i][j][1], idx[i][j][2], 0);
                if (i == n || !mark2[i][j]) G2.add(idx[i][j][2], idx[i][j][3], 0);
                if (!j || !mark1[i][j-1]) G2.add(idx[i][j][3], idx[i][j][0], 0);
                // ! 关键点四周的点顺时针连边 
            }
        }
        for (int i = 0; i < n; i++) {
            for (int j = 0; j <= m; j++) {
                G2.add(idx[i][j][2], idx[i+1][j][1], a[i][j]);
                G2.add(idx[i+1][j][0], idx[i][j][3], a[i][j]);
            }
        }
        for (int i = 0; i <= n; i++) {
            for (int j = 0; j < m; j++) {
                G2.add(idx[i][j][1], idx[i][j+1][0], b[i][j]);
                G2.add(idx[i][j+1][3], idx[i][j][2], b[i][j]);
            }
        }
        G2.dijkstra(idx[0][0][0]);
        LL rst = G2.dis[idx[0][0][3]];
        printf("%lld", rst);
    }
}

int main() {
    n = read(); m = read();
    for (int i = 1; i <= n; i++)
        for (int j = 1; j <= m; j++) mat[i][j] = read();
    for (int i = 0; i < n; i++)
        for (int j = 0; j <= m; j++) a[i][j] = read();
    for (int i = 0; i <= n; i++)
        for (int j = 0; j < m; j++) b[i][j] = read();
    FindPath::init(); FindPath::solve();
    GetAnswer::init(); GetAnswer::solve();
    return 0;
}
```

---

## 作者：Leasier (赞：1)

当关键点很少，我们可以从每个位置出发引射线并状压路径经过其次数的奇偶性，但显然不能通过。

下面设 $(i, j)$ 的左上角为 $(i - 1, j - 1)$，右上角为 $(i - 1, j)$，左下角为 $(i, j - 1)$，右下角为 $(i, j)$。

注意到如下结论：

- $(0, 0)$ 到其他所有关键点左上角的最短路一定在墙内（可能位于边界）。

证明：如果有一个关键点不满足条件，则把外面的一段替换成到它左上角的最短路的一部分不劣。

于是考虑先把 $(0, 0)$ 到所有关键点的最短路跑出来，然后对于每个关键点抓出它到 $(0, 0)$ 的一条最短路，则我们现在需要：

- 求一个最小的包含 $(0, 0)$ 的环，满足环包含了所有关键点和上文找出的最短路。

考虑拆点，用 $(i, j, 1)$ 表示 $(i, j)$ 左上方一点点的位置，$(i, j, 2)$ 表示 $(i, j)$ 右上方一点点的位置，$(i, j, 3)$ 表示 $(i, j)$ 右下方一点点的位置，$(i, j, 4)$ 表示 $(i, j)$ 左下方一点点的位置。

建图分为两种情况：

- 同一个 $(i, j)$ 的 $(1, 2), (2, 3), (3, 4), (4, 1)$ 之间连边，边权为 $0$。此时需要满足对应跨过的边不在最短路上且对应的两个点不是关键点。
- $(i, j)$ 与旁边的 $(i', j')$ 的 $(1, 4), (2, 1), (3, 2), (4, 3)$ 之间连边，边权为它贴着的那个位置的边权。此时需要满足对应点不是关键点。

注意到这个环一定会从 $(0, 0, 1)$ 出发，最后通过 $(0, 0, 4)$ 回到起点，于是我们以 $(0, 0, 1)$ 为源点求其到 $(0, 0, 4)$ 的最短路即可。时间复杂度为 $O(nm \log nm)$。

代码：
```cpp
#include <iostream>
#include <queue>

using namespace std;

typedef long long ll;

typedef struct {
	int nxt;
	int end;
	int dis;
} Edge;

typedef struct Node_tag {
	ll dis;
	int pos;
	Node_tag(ll dis_, int pos_){
		dis = dis_;
		pos = pos_;
	}
} Node;

int cnt;
int id1[407][407], refx[160807], refy[160807], down[407][407], head[643207], rt[407][407], id2[407][407][7];
ll dis1[160807], dis2[643207];
bool mark[407][407], vis1[643207], vis2[160807], insidex[407][407], insidey[407][407];
Edge edge[2569617];
priority_queue<Node> q;

bool operator <(const Node a, const Node b){
	return a.dis > b.dis;
}

inline void init(int n, ll dis[]){
	cnt = 0;
	for (register int i = 1; i <= n; i++){
		head[i] = 0;
		dis[i] = 0x7fffffffffffffffll;
		vis1[i] = false;
	}
}

inline void add_edge(int start, int end, int dis){
	cnt++;
	edge[cnt].nxt = head[start];
	head[start] = cnt;
	edge[cnt].end = end;
	edge[cnt].dis = dis;
}

inline void dijkstra(int start, ll dis[]){
	dis[start] = 0;
	q.push(Node(0, start));
	while (!q.empty()){
		int cur = q.top().pos;
		q.pop();
		if (vis1[cur]) continue;
		vis1[cur] = true;
		for (register int i = head[cur]; i != 0; i = edge[i].nxt){
			int x = edge[i].end;
			ll y = dis[cur] + edge[i].dis;
			if (dis[x] > y){
				dis[x] = y;
				q.push(Node(y, x));
			}
		}
	}
}

void dfs(int u){
	vis2[u] = true;
	for (register int i = head[u]; i != 0; i = edge[i].nxt){
		int x = edge[i].end;
		if (dis1[u] == dis1[x] + edge[i].dis){
			if (refx[u] == refx[x]){
				insidex[refx[u]][max(refy[u], refy[x])] = true;
			} else {
				insidey[refy[u]][max(refx[u], refx[x])] = true;
			}
			if (!vis2[x]) dfs(x);
			break;
		}
	}
}

int main(){
	int n, m, cnt1 = 0, cnt2 = 0;
	cin >> n >> m;
	for (register int i = 0; i <= n; i++){
		for (register int j = 0; j <= m; j++){
			cnt1++;
			id1[i][j] = cnt1;
			refx[cnt1] = i;
			refy[cnt1] = j;
		}
	}
	init(cnt1, dis1);
	for (register int i = 1; i <= n; i++){
		for (register int j = 1; j <= m; j++){
			int a;
			cin >> a;
			if (a == 1) mark[i][j] = true;
		}
	}
	for (register int i = 1; i <= n; i++){
		for (register int j = 0; j <= m; j++){
			cin >> down[i][j];
			add_edge(id1[i - 1][j], id1[i][j], down[i][j]);
			add_edge(id1[i][j], id1[i - 1][j], down[i][j]);
		}
	}
	for (register int i = 0; i <= n; i++){
		for (register int j = 1; j <= m; j++){
			cin >> rt[i][j];
			add_edge(id1[i][j - 1], id1[i][j], rt[i][j]);
			add_edge(id1[i][j], id1[i][j - 1], rt[i][j]);
		}
	}
	dijkstra(id1[0][0], dis1);
	for (register int i = 0; i < n; i++){
		for (register int j = 0; j < m; j++){
			if (!vis2[id1[i][j]] && mark[i + 1][j + 1]) dfs(id1[i][j]);
		}
	}
	for (register int i = 0; i <= n; i++){
		for (register int j = 0; j <= m; j++){
			for (register int k = 1; k <= 4; k++){
				id2[i][j][k] = ++cnt2;
			}
		}
	}
	init(cnt2, dis2);
	for (register int i = 0; i <= n; i++){
		for (register int j = 0; j <= m; j++){
			if (!insidey[j][i] && !mark[i][j] && !mark[i][j + 1]){
				add_edge(id2[i][j][1], id2[i][j][2], 0);
				add_edge(id2[i][j][2], id2[i][j][1], 0);
			}
			if (!insidex[i][j + 1] && !mark[i][j + 1] && !mark[i + 1][j + 1]){
				add_edge(id2[i][j][2], id2[i][j][3], 0);
				add_edge(id2[i][j][3], id2[i][j][2], 0);
			}
			if (!insidey[j][i + 1] && !mark[i + 1][j + 1] && !mark[i + 1][j]){
				add_edge(id2[i][j][3], id2[i][j][4], 0);
				add_edge(id2[i][j][4], id2[i][j][3], 0);
			}
			if (!insidex[i][j] && !mark[i + 1][j] && !mark[i][j] && (i != 0 || j != 0)){
				add_edge(id2[i][j][4], id2[i][j][1], 0);
				add_edge(id2[i][j][1], id2[i][j][4], 0);
			}
			if (i > 0 && !mark[i][j]){
				add_edge(id2[i][j][1], id2[i - 1][j][4], down[i][j]);
				add_edge(id2[i - 1][j][4], id2[i][j][1], down[i][j]);
			}
			if (j < m && !mark[i][j + 1]){
				add_edge(id2[i][j][2], id2[i][j + 1][1], rt[i][j + 1]);
				add_edge(id2[i][j + 1][1], id2[i][j][2], rt[i][j + 1]);
			}
			if (i < n && !mark[i + 1][j + 1]){
				add_edge(id2[i][j][3], id2[i + 1][j][2], down[i + 1][j]);
				add_edge(id2[i + 1][j][2], id2[i][j][3], down[i + 1][j]);
			}
			if (j > 0 && !mark[i + 1][j]){
				add_edge(id2[i][j][4], id2[i][j - 1][3], rt[i][j]);
				add_edge(id2[i][j - 1][3], id2[i][j][4], rt[i][j]);
			}
		}
	}
	dijkstra(id2[0][0][1], dis2);
	cout << dis2[id2[0][0][4]];
	return 0;
}
```

---

