# [ABC070D] Transit Tree Path

## 题目描述

[problemUrl]: https://atcoder.jp/contests/abc070/tasks/abc070_d

$ N $ 頂点の木が与えられます。   
 木とはグラフの一種であり、頂点の数を $ N $ とすると、辺の数が $ N-1 $ 本である閉路のない連結グラフです。   
 $ i(1≦i≦N-1) $ 番目の辺は 頂点 $ a_i $ と 頂点 $ b_i $ を距離 $ c_i $ で結びます。

また、$ Q $ 個の質問クエリと整数 $ K $ が与えられます。

- $ j(1≦j≦Q) $ 番目の質問クエリでは、頂点 $ x_j $ から 頂点 $ K $ を経由しつつ、頂点 $ y_j $ まで移動する場合の最短経路の距離を求めてください。

## 说明/提示

### 制約

- $ 3≦N≦10^5 $
- $ 1≦a_i,b_i≦N\ (1≦i≦N-1) $
- $ 1≦c_i≦10^9\ (1≦i≦N-1) $
- 与えられるグラフは木である。
- $ 1≦Q≦10^5 $
- $ 1≦K≦N $
- $ 1≦x_j,y_j≦N\ (1≦j≦Q) $
- $ x_j≠y_j\ (1≦j≦Q) $
- $ x_j≠K,y_j≠K\ (1≦j≦Q) $

### Sample Explanation 1

与えられた $ 3 $ つの質問クエリに対する最短経路は以下の通りです。 - $ 1 $ つ目の質問クエリ: 頂点 $ 2 $ → 頂点 $ 1 $ → 頂点 $ 2 $ → 頂点 $ 4 $ : 距離 $ 1+1+1=3 $ - $ 2 $ つ目の質問クエリ: 頂点 $ 2 $ → 頂点 $ 1 $ → 頂点 $ 3 $ : 距離 $ 1+1=2 $ - $ 3 $ つ目の質問クエリ: 頂点 $ 4 $ → 頂点 $ 2 $ → 頂点 $ 1 $ → 頂点 $ 3 $ → 頂点 $ 5 $ : 距離 $ 1+1+1+1=4 $

### Sample Explanation 2

質問クエリに対する最短経路は、必ず頂点 $ K=2 $ を通過する必要があります。

## 样例 #1

### 输入

```
5
1 2 1
1 3 1
2 4 1
3 5 1
3 1
2 4
2 3
4 5```

### 输出

```
3
2
4```

## 样例 #2

### 输入

```
7
1 2 1
1 3 3
1 4 5
1 5 7
1 6 9
1 7 11
3 2
1 3
4 5
6 7```

### 输出

```
5
14
22```

## 样例 #3

### 输入

```
10
1 2 1000000000
2 3 1000000000
3 4 1000000000
4 5 1000000000
5 6 1000000000
6 7 1000000000
7 8 1000000000
8 9 1000000000
9 10 1000000000
1 1
9 10```

### 输出

```
17000000000```

# 题解

## 作者：GuideZombies (赞：5)

$\quad$ 从 $x$ 节点经过 $k$ 节点到 $y$ 节点的方法分为两步：

$\quad\quad\quad$ 1、从 $x$ 节点走到 $k$ 节点。

$\quad\quad\quad$ 2、从 $k$ 节点走到 $y$ 节点。

$\quad$所以，只需要以 $k$ 为源点跑一遍最短路，求出 $dis_x$ 和 $dis_y$ 的和。因为这是树，在边权非负的情况下一个节点只会被一个点更新，所以也可以用普通的 bfs 和 dfs 。

$\quad$ 代码：

```
#include <bits/stdc++.h>
using namespace std;
int n, m, k;
long long h[200010], e[200010], w[200010], ne[200010], idx;
long long dis[100010];
bool in_qu[100010];
void add(int x, int y, long long z) {//邻接表
	ne[idx] = h[x];
	e[idx] = y;
	w[idx] = z;
	h[x] = idx++;
}
void bfs() {//SPFA求最短路
	for (int i = 1; i <= n; ++i) dis[i] = 1e18;
	dis[k] = 0;
	queue<int> Q;
	Q.push(k);
	while (!Q.empty()) {
		int cur = Q.front();
		Q.pop();
		in_qu[cur] = 0;
		for (int i = h[cur]; i != -1; i = ne[i]) {
			if (dis[e[i]] > dis[cur] + w[i]) {
				dis[e[i]] = dis[cur] + w[i];
				if (in_qu[e[i]] == 0) {
					in_qu[e[i]] = 1;
					Q.push(e[i]);
				}
			} 
		}
	} 
}
int main() {
	cin >> n;
	memset(h, -1, sizeof h);
	for (int i = 1; i < n; ++i) {
		int x, y, z;
		cin >> x >> y >> z;
		add(x, y, z);
		add(y, x, z);
	}
	cin >> m >> k;
	bfs();
//	for (int i = 1; i <= n; ++i) cout << i << ' ' << dis[i] << endl;
	for (int i = 1; i <= m; ++i) {
		int x, y;
		cin >> x >> y;
		cout << dis[x] + dis[y] << endl;
	}
	return 0;
}
```

---

## 作者：ZolaWatle (赞：4)

# AT2693 题解

### 概述

题目的要求是：给出一棵有 $ N $ 个结点的树，给出 $ Q $ 个询问，求结点 $ x_j $过结点 $ K $ 到节点 $ y_j $ 的最短距离。

**“最短距离”**

别被这句话给骗了。

我们知道，一棵树可以看做是一张 $ n $ 个点，$ n-1 $ 条边的无向无环图。不难知道，树上任意两点间的路径是唯一确定的，**根本不存在最短的说法**。这很好理解。因为最坏的情况下，一棵树可以退化成一条链。

因此，我们只需要求出 $ x $ 到 $ K $ 的距离 $ D_{x,K} $，以及 $ y $ 到 $ K $ 的距离 $ D_{y,K} $，相加即可求得答案。

又因为从 $ x $ 到 $ y $ 的简单路径（不回头）上，必有一个点是 $ x $ 和 $ y $ 的最近公共祖先，记为 $ lca(x,y) $。并且，在上行至 $ lca(a,b) $ 或者从 $ lca(a,b) $ 下行的过程中，深度具有单调性。即当前走到的点到根节点的距离具有单调性。满足~~套~~使用树上前缀和的条件。

所以，令节点 $ i $ 到根节点 $ 1 $（哪个是根都无所谓）的距离为 $ dist_{i} $。那么，根据前缀和，有以下推导：

$$ D_{x,K}+D_{K,y}= $$

$$ (dist_x+dist_K-2\cdot dist_{lca(x,K)})+(dist_K+dist_y-2\cdot dist_{lca(K,y)})= $$

$$ dist_x+dist_y+2\cdot (dist_K-dist_{lca(x,K)}-dist_{lca(K,y)}) $$

思路说完了，下面看看具体的代码实现。

------------

### 实现

- 使用 $ vector $ 存边 ~~（不用前向星是因为没vector可爱）~~。

```cpp
vector < pair <int,long long> > E[MAXN];  //pair是容器，第一个元素是x点连到的y点（等同于前向星的e[i].to）；第二个元素是连接x,y两点的这条边的权值w（等同于前向星的e[i].w）

for(re i=1;i<n;i++)
{
	re x,y;
	long long z;
	std::scanf("%d%d%lld",&x,&y,&z);  //注意开ll 
	E[x].push_back(make_pair(y,z));  //建边，相当于前向星的add(x,y,z) 
	E[y].push_back(make_pair(x,z));  //同上 
}
```


- 利用 $ dfs $ 或 $ bfs $ 预处理出每个节点的深度和到根的距离。

```cpp
inline void dfs(int x,int fa)  //fa是当前节点x的父亲节点 
{
	dep[x]=dep[fa]+1;  //拓展深度 
	F[x][0]=fa;  //x的2^0辈祖先是父亲fa 
	for(re i=1;i<=20;i++)
		F[x][i]=F[F[x][i-1]][i-1];  //计算祖先 
	for(re i=0;i<E[x].size();i++)
	{
		re y=E[x][i].first;  //.first取出容器中的第一个元素 
		if(y!=fa)
		{
			dist[y]=dist[x]+E[x][i].second;  //.second取出容器中的第二个元素，当前节点的距离为父亲节点的距离加上连接两点的边权 
			dfs(y,x);  //遍历 
		}
	}
}
```


- 利用倍增或者 $ Tarjan $ 求最近公共祖先。

```cpp
inline int LCA(int x,int y)
{
	if(dep[x]<dep[y])  //如果x比y浅 
		std::swap(x,y);  //换位（因为是让x向上跳） 
	for(re i=20;i>=0;i--)
		if(dep[F[x][i]]>=dep[y])  //如果祖先的深度依然比y深 
			x=F[x][i];
	if(x==y)  //如果x与y相遇 
		return x;
	for(re i=20;i>=0;i--)
		if(F[x][i]!=F[y][i])  //若两点的祖先不同 
		{
			x=F[x][i];
			y=F[y][i];
		}
	return F[x][0];  //返回x的父亲节点 
}
```


- $ O(1) $ 回答询问。

```cpp
std::printf("%lld\n",dist[x]+dist[K]-2*dist[LCA(x,K)]+dist[y]+dist[K]-2*dist[LCA(y,K)]);  //公式如上，记得用printf输出时用"%lld"
```

------------

### 完整代码：

```cpp
#include <iostream>
#include <cstdio>
#include <vector>
#define re register int
using namespace std;

const int MAXN=1e5+1;
int n,Q,K,dep[MAXN],F[MAXN][21];
long long dist[MAXN];
vector < pair <int,long long> > E[MAXN]; 

inline void dfs(int x,int fa) 
{
	dep[x]=dep[fa]+1; 
	F[x][0]=fa; 
	for(re i=1;i<=20;i++)
		F[x][i]=F[F[x][i-1]][i-1]; 
	for(re i=0;i<E[x].size();i++)
	{
		re y=E[x][i].first; 
		if(y!=fa)
		{
			dist[y]=dist[x]+E[x][i].second; 
			dfs(y,x); 
		}
	}
}

inline int LCA(int x,int y)
{
	if(dep[x]<dep[y]) 
		std::swap(x,y); 
	for(re i=20;i>=0;i--)
		if(dep[F[x][i]]>=dep[y]) 
			x=F[x][i];
	if(x==y) 
		return x;
	for(re i=20;i>=0;i--)
		if(F[x][i]!=F[y][i]) 
		{
			x=F[x][i];
			y=F[y][i];
		}
	return F[x][0]; 
}

int main()
{
	std::scanf("%d",&n);
	
	for(re i=1;i<n;i++)
	{
		re x,y;
		long long z;
		std::scanf("%d%d%lld",&x,&y,&z); 
		E[x].push_back(make_pair(y,z)); 
		E[y].push_back(make_pair(x,z)); 
	}
	
	dfs(1,0);
	
	std::scanf("%d%d",&Q,&K);
	while(Q--)
	{
		re x,y;
		std::scanf("%d%d",&x,&y);
		std::printf("%lld\n",dist[x]+dist[K]-2*dist[LCA(x,K)]+dist[y]+dist[K]-2*dist[LCA(y,K)]);
	}
	
	return 0;
}
```

------------

### 一个有趣的现象

在前面我们已经推导出了计算答案的公式如下：

$$ dist_x+dist_y+2\cdot (dist_K-dist_{lca(x,K)}-dist_{lca(K,y)}) $$

如果 $ K $ 刚刚好是根节点呢？

此时 $ lca(x,K)=lca(K,y)=K $。

但 $ K $ 是根节点啊！那么 $ dist_K $ 就是 $ 0 $ 了。这样一来，计算式不就变成了：

$$ dist_x+dist_y  $$

吗？

？？？

这不是就连 $ lca $ 都不用求了吗？如果所有情况下都不用计算 $ lca $，那么时间复杂度就会从原来的 $ O(n\cdot log\ n) $ 预处理，$ O(1) $ 询问变成 $ O(log\  n) $ 的预处理了吗？这样最坏情况（链）下的复杂度也才 $ O(n) $，是完全不惧怕~~变态~~可爱的数据的。

那怎么样让这种情况次次都出现呢？

对于这棵树来讲，**任意一个节点做根都无所谓**，那干脆就把 $ K $ 当做根吧！这样一来，连 $ lca $ 都不用算了，赛狗你嗨得鸭子哒！

------------

~~虽然AT的题交不了了，但还是~~写一篇题解，就当自己的学习笔记吧

------------

$ \text{update 2020.9.17}$ 感谢 [ @yecheng](https://www.luogu.com.cn/user/192615) 提出的关于 LaTeX        表现的指正。

---

## 作者：D2T1 (赞：2)

[$\color{blue}{\text {pwp }{\to\textbf{My blog}\gets}}\text{qwq}$](https://www.luogu.com.cn/blog/390770/blogcenter)

## 题意

给出一棵有 $N$ 个结点的树，给出 $Q$ 个询问，求节点 $x_i$ 过节点 $K$ 到节点 $y_i$ 的最短距离。

输入格式：

- 第一行一个整数 $N$；

- 接下来 $N-1$ 行，每行三个正整数 $a,b,c$，表示一条从节点 $a$ 到节点 $b$ 权值为 $c$ 的无向边；

- 接下来一行两个正整数 $Q,K$；

- 接下来 $Q$ 行，每行两个正整数 $x,y$，表示求结点 $x$ 过结点 $K$ 到节点 $y$ 的最短距离。

## 题解

**树**的性质决定了**树上的任意一对节点只有一条路径**，所以就不用求什么最短路径。

因为题目要求所求路径经过节点 $K$，所以我们预处理求出 $K$ 到每个节点的路径，询问时直接将两点到 $K$ 的路径长度相加即可。

记得开 `long long`。

## 代码

```cpp
//AT2693
//码风：题解专用
#include <bits/stdc++.h>
using namespace std;

const int N = 1e5 + 10;
vector< pair< int, long long > > Edge[ N ];
int n, q, k, Vis[ N ];
long long Dis[ N ];

void dfs( int st, long long d )
{
	Dis[ st ] = d;
	Vis[ st ] = true;
	for( int i = 0; i < Edge[ st ].size( ); ++ i){
		int to = Edge[ st ][ i ].first;
		if( Vis[ to ] ) continue;
		dfs( to, d + Edge[ st ][ i ].second );
	}
	return ;
}

int main( )
{
	scanf( "%d", &n );
	for( int i = 1; i < n; ++ i ){
		int u, v;
		long long w;
		scanf( "%d%d%lld", &u, &v, &w );
		Edge[ u ].push_back( make_pair( v, w ) );
		Edge[ v ].push_back( make_pair( u, w ) );
	}
	scanf( "%d%d", &q, &k );
	dfs( k, 0 );
	for( int i = 1; i <= q; ++ i ){
		int u, v;
		scanf( "%d%d", &u, &v);
		printf( "%lld\n", Dis[u] + Dis[v] );
	}
	return 0;
}
```

---

## 作者：Edward_Elric (赞：2)

### 思路

保证两点之间过点K呢，其实不难想到，只要将K点作为根节点就好了,找出k到两点的距离相加即为最短距离

### 代码

```cpp
#include<bits/stdc++.h>
using namespace std;
const int maxn=1e5+50,maxm=2e5+100;
long long d[maxn];
int head[maxn];
int size=0;
struct edge
{
	int to,next;
	long long val;
}e[maxn];
void addedge(int u,int v,long long w)
{
	e[++size].to=v;
	e[size].val=w;
	e[size].next=head[u];
	head[u]=size;
}
inline int read()
{
	int x=0,f=1;char ch=getchar();
	while(ch>'9'||ch<'0'){if(ch=='-')f=-1;ch=getchar();}
	while(ch<='9'&&ch>='0'){x=(x<<3)+(x<<1)+ch-'0';ch=getchar();}
	return x*f;
}
void dfs(int u,int fa)
{
	for(int i=head[u];i;i=e[i].next)
	{
		int to=e[i].to;
		if(to==fa)continue;
		d[to]=d[u]+e[i].val;
		dfs(to,u);
	}
}
int main()
{
	int n=read();
	for(int i=1;i<n;i++)
	{
		int u=read(),v=read();
		long long w=read();
		addedge(u,v,w);
		addedge(v,u,w);	
	}
	int q=read(),k=read();
	dfs(k,0);
	for(int i=1;i<=q;i++)
	{
		int x=read(),y=read();
		printf("%lld\n",d[x]+d[y]);
	}
	return 0;
}
```

---

