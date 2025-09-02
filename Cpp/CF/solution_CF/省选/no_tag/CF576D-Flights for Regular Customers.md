# Flights for Regular Customers

## 题目描述

In the country there are exactly $ n $ cities numbered with positive integers from $ 1 $ to $ n $ . In each city there is an airport is located.

Also, there is the only one airline, which makes $ m $ flights. Unfortunately, to use them, you need to be a regular customer of this company, namely, you have the opportunity to enjoy flight $ i $ from city $ a_{i} $ to city $ b_{i} $ only if you have already made at least $ d_{i} $ flights before that.

Please note that flight $ i $ flies exactly from city $ a_{i} $ to city $ b_{i} $ . It can not be used to fly from city $ b_{i} $ to city $ a_{i} $ . An interesting fact is that there may possibly be recreational flights with a beautiful view of the sky, which begin and end in the same city.

You need to get from city $ 1 $ to city $ n $ . Unfortunately, you've never traveled by plane before. What minimum number of flights you have to perform in order to get to city $ n $ ?

Note that the same flight can be used multiple times.

## 样例 #1

### 输入

```
3 2
1 2 0
2 3 1
```

### 输出

```
2
```

## 样例 #2

### 输入

```
2 1
1 2 100500
```

### 输出

```
Impossible
```

## 样例 #3

### 输入

```
3 3
2 1 0
2 3 6
1 2 0
```

### 输出

```
8
```

# 题解

## 作者：⚡current⚡ (赞：35)

由于题解里 dalao 们讲的都很简短，代码又没有注释，所以来写一篇详细一点的，我这种萌新都能看得懂的题解，dalao 就可以不用看了

#### 前置知识1：多源bfs

在 bfs 时，在```while(!q.empty())```之前，将多个而非一个点加入队列，最后得到的结果就是从这些点同时出发的最短路，也可以看成是将这些点与一个虚拟节点连边（边权为0），从这个虚拟结点出发计算最短路

#### 前置知识2：矩阵在图论中的应用

矩阵与图论关系密切，这点从邻接矩阵的名字和 floyd 的过程中就可以看出。而矩阵在图论中的应用本质上是对 dp 的优化

比如计算走 $k$ 步从 $s$ 走到 $t$ 的方案数，设 $f(i,j,k)$ 为从 $i$ 走 $k$ 步到 $j$ 的方案数，那么我们就有这样的一个方程 $f(i,j,p+q) =  \sum_{1 \leq k \leq n} f(i,k,p) * f(k,j,q)$，这与矩乘的过程是很像的。我们设置这样一个矩阵 $A$，$A[i][j] = f(i,j,1)$，那么 $A^k[i][j] = f(i,j,k)$

同理，通过重载矩乘的运算和更改初始矩阵的值，还可以维护更多图上的信息，比如经过 $k$ 步的最短路，[[USACO07NOV]Cow Relays G](https://www.luogu.com.cn/problem/P2886)，[[NOI Online #3 提高组]魔法值](https://www.luogu.com.cn/problem/P6569)和[NOI2020美食家](https://www.luogu.com.cn/problem/P6772)也用到了这种方法

#### 前置知识3：bitset优化

有如下矩乘过程，其矩阵中的量只有0和1两种，我们可以用 bitset 优化它的速度

```
bitset<MAXN> res[MAXN], a[MAXN], b[MAXN];
for(int i = 1; i <= n; ++i)
	for(int j = 1; j <= n; ++j)
		for(int k = 1; k <= n; ++k)
			res[i][j] |= a[i][k] & b[k][j];
```

这与下面的代码是等价的

```
bitset<MAXN> res[MAXN], a[MAXN], b[MAXN];
for(int i = 1; i <= n; ++i)
	for(int k = 1; k <= n; ++k)
		for(int j = 1; j <= n; ++j)
			if(a[i][k])
				res[i][j] |= b[k][j];
```

我们发现最后一行的运算中```res```与```b```的第二维```[j]```对齐了，所以我们就可以把这一维优化掉，交给 STL 去计算

```
bitset<MAXN> res[MAXN], a[MAXN], b[MAXN];
for(int i = 1; i <= n; ++i)
	for(int k = 1; k <= n; ++k)
		if(a[i][k])
			res[i] |= b[k];
```

#### 正式题解

我们回到这道题，考虑在这张图上游走，所有的边一定是按 $d_i$ 从小到大的顺序解锁。

所以我们对边排序，然后枚举每一条遍，假设此时已经走过了 $t$ 条边，那以走过 $t$ 条边后所在的每一个可能位置为起点，在只有前 $i$ 条边的图上跑一遍 多源bfs，再将每一个 $d[j]$ 加上 $t$ 即可得到解锁前 $i$ 条边后的最短路（如果路径长度已经超过了下一条边的解锁条件，那么算出来的答案有可能是不准确的，但这并没有影响，因为在枚举到下一条边时还会被计算一次）

至于走过 $t$ 条边之后的可能位置，可以用矩阵来维护，并用矩阵快速幂来加速。不过注意，每解锁一条新的边后转移矩阵都会改变。由于时间复杂度还是不够优秀，我们用 bitset 来优化矩乘的过程，这道题就做完了。

思路还是比较清晰的，但我由于把有向图当成了无向图，卡了好久...

$\text{CODE}\downarrow$

```c++
#include<bitset>
#include<stdio.h>
#include<algorithm>
using namespace std;
 
typedef long long ll;
const int MAXN = 155;
const ll INF = 1000000000000000;
ll d[MAXN], t, dt, ans = INF;
int q[1000], l, r, n;

inline int read()
{
    int x = 0;
    char ch = getchar();
    while(ch < '0' || ch > '9')
        ch = getchar();
    while(ch >= '0' && ch <= '9')
    {
        x = x * 10 + ch - 48;
        ch = getchar();
    }
    return x;
}

inline ll llread()
{
    ll x = 0;
    char ch = getchar();
    while(ch < '0' || ch > '9')
        ch = getchar();
    while(ch >= '0' && ch <= '9')
    {
        x = x * 10 + ch - 48;
        ch = getchar();
    }
    return x;
}

struct edge//存边，方便排序和枚举，w表示解锁条件
{
    int u, v; ll w;
    friend bool operator<(edge a, edge b) { return a.w < b.w; }
    void get() { u = read(), v = read(), w = llread(); }
} e[MAXN];
 
struct mrx
{
    bitset<MAXN> v[MAXN];
 
    mrx()
    {
        for (int i = 1; i <= n; ++i)
            for (int j = 1; j <= n; ++j)
                v[i][j] = 0;
    }
 
    void one()
    {
        for (int i = 1; i <= n; ++i)
            v[i][i] = 1;
    }
 
    friend mrx operator * (mrx a, mrx b)
    {
        mrx res;
        for (int i = 1; i <= n; ++i)
            for (int k = 1; k <= n; ++k)
                if(a.v[i][k])
                    res.v[i] |= b.v[k];
        return res;
    }

    /*
    不用bitset优化的矩阵乘法，便于理解
    friend mrx operator * (mrx a, mrx b)
    {
        mrx res;
        for (int i = 1; i <= n; ++i)
            for(int j = 1; j <= n; ++j)
                for (int k = 1; k <= n; ++k)
                    res.v[i][j] |= a.v[i][k] & b.v[k][j];
        return res;
    }
    */
} a, g;
/*
矩阵a维护可达性信息
a.v[i][j]表示经过特定边数后从i是否能到j
矩阵g维护途中边的信息
g.v[i][j]表示图中是否存在从i到j的边
*/

mrx pow(mrx x, ll y)
{
    mrx res;
    res.one();
    while(y)
    {
        if(y&1) res = res * x;
        x = x * x;
        y >>= 1;
    }
    return res;
}
 
void bfs() //多源bfs，将结果存在数组d中
{
    int x;
    l = r = 1;
    for (int i = 1; i <= n; ++i)
        d[i] = INF; //记得初始化
    for (int i = 1; i <= n; ++i)
        if (a.v[1][i])
            q[r++] = i, d[i] = 0;//从起点出发经过t步后到的点作为起点
    while(r > l)//正常的bfs过程
    {
        x = q[l++];
        for (int y = 1; y <= n; ++y)
            if(g.v[x][y] && d[y] == INF)
                d[y] = d[x] + 1, q[r++] = y;
    }
}
 
int main()
{
    int m;
    n = read(), m = read();
    for (int i = 1; i <= m; ++i)
        e[i].get();
    sort(e + 1, e + m + 1);
    a.v[1][1] = 1; d[n] = INF;
    for (int i = 1; i <= m; ++i)//枚举
    {
        if(ans < e[i].w)
            break;
        dt = e[i].w - t;//dt->delta_t，过去的时间/边数
        t = e[i].w;
        a = a * pow(g, dt);//用矩阵快速幂维护t时刻可以在的位置
        g.v[e[i].u][e[i].v] = 1;//解锁新边，会对接下来的bfs和矩阵a的维护都产生影响
        if(i == m || e[i+1].w != e[i].w) bfs();
        ans = min(ans, t + d[n]);
    }
    if(ans == INF) puts("Impossible");
    else printf("%lld\n", ans);
    return 0;
}
```

P.S.我在做图论题时会把经过的路程与时间混起来，这两者是等价的，而且我认为把距离看成时间会更容易理解图论算法，所以在代码注释里的时间指的就是距离

---

## 作者：xht (赞：19)

> [CF576D Flights for Regular Customers](https://codeforc.es/contest/576/problem/D)

## 题意

- 给定一张 $n$ 个点 $m$ 条边的有向图。
- 一开始你在 $1$ 号节点，你要走到 $n$ 号节点去。
- 只有当你已经走过了至少 $d_i$ 条边时，你才能走第 $i$ 条边。
- 问最少要走多少条边，或判断无法到达。
- $n,m \le 150$，$d_i \le 10^9$。

## 题解

首先对边排序，然后从小到大依次加入每条边。

考虑只有当前存在的边时，答案怎么求。

假设此时加入的边的 $d$ 值为 $t$，首先要求的是经过恰好 $t$ 条边时可以到达哪些点。

这个可以从加入上一条边时的答案递推过来，这个递推式可以矩阵加速。

求出恰好 $t$ 条边时可以到达哪些点后，对整个图进行一次 bfs 即可求出当前的答案。

这样时间复杂度是 $\mathcal O(n^3m \log d)$ 的，无法通过。

注意到每个点的状态只有 $0/1$ 两种，分别对应着无法到达和可以到达。

因此可以 bitset 优化，时间复杂度 $\mathcal O(\frac{n^3m \log d}w)$。

## 代码

```cpp
const int N = 150;
const ll inf = 1e18;
int n, m;
struct E {
	int x, y, z;
	inline void input() { rd(x), rd(y), rd(z), --x, --y; }
	inline friend bool operator < (E a, E b) { return a.z < b.z; }
} e[N];
ll d[N], ans;
#define bt bitset<N>
bt v;
struct mt {
	bt a[N];
	inline friend bt operator * (bt x, mt y) {
		bt z;
		for (int i = 0; i < n; i++) z[i] = (x & y.a[i]).any();
		return z;
	}
	inline friend mt operator * (mt x, mt y) {
		mt z;
		for (int i = 0; i < n; i++)
			for (int j = 0; j < n; j++)
				if (x.a[i][j]) z.a[i] |= y.a[j];
		return z;
	}
} a;

inline void ksm(mt x, int y, bt &z) {
	while (y) {
		if (y & 1) z = z * x;
		x = x * x, y >>= 1;
	}
}

int main() {
	rd(n), rd(m);
	for (int i = 0; i < m; i++) e[i].input();
	sort(e, e + m);
	v[0] = 1;
	ans = inf;
	for (int i = 0, t = 0; i < m; i++) {
		if (e[i].z >= ans) break;
		int o = e[i].z - t;
		ksm(a, o, v);
		a.a[e[i].y][e[i].x] = 1;
		t = e[i].z;
		queue<int> q;
		for (int x = 0; x < n; x++)
			if (v[x]) q.push(x), d[x] = 0;
			else d[x] = inf;
		while (q.size()) {
			int x = q.front();
			q.pop();
			for (int y = 0; y < n; y++)
				if (a.a[y][x] && d[y] == inf)
					d[y] = d[x] + 1, q.push(y);
		}
		ans = min(ans, t + d[n-1]);
	}
	if (ans == inf) prints("Impossible");
	else print(ans);
	return 0;
}
```

---

## 作者：namespace_std (赞：11)

看了一下，题解区都是使用 ```bitset``` 优化的矩阵乘法，复杂度  $O(n^3mlog_2d/\omega)$ 。

这里有一个 $O((n^3+n^2m)·log_2d)$ 的做法：

我们首先将边按照 $d_i$ 从小到大排序，这样排在前面的边一定在排在后面的边之前加入。

之后，我们对于每个 $d_i$ ，求出从 $1$ 出发走过恰好 $d_i$ 条边后能到达哪些点。

显然求出这个点集之后可以从这些点出发各做一次bfs（或者多起点bfs，但是此处不影响瓶颈复杂度，因此效率相差不大），之后得到走 $d_i$ 步之后得到的图上再走多少步可以到达 $n$ 。将所有 $d_i$ 产生的答案比较，取最优的作为答案。如果无论哪一个 $d_i$ 都到达不了 $n$ ，那答案就是 ```Impossible``` 。

现在主要的问题就是如何更高效率地求出这个点集。

用邻接矩阵做矩阵乘法可以得到一个 $O(n^3mlog_2d/\omega)$ 的算法，但是还不够优。考虑优化。

我们发现，我们可以 $O(n^2)$ 地通过一个邻接矩阵和一个可到达点集 $S$ 推出 $S$ 在经过一次邻接矩阵上的边之后的生成可到达点集 $T$。（枚举起点和出边直接暴力转移即可）

对于邻接矩阵的 $2^k$ 次方也同理：我们可以 $O(n^2)$ 地通过一个邻接矩阵的 $f$ 次方和一个可到达点集 $S$ 推出 $S$ 在经过 $f$ 次邻接矩阵上的边之后的生成可到达点集 $T$。

于是我们可以考虑动态加边的过程中维护这个邻接矩阵的 $2^k$ 次方。

直接矩阵乘法维护显然还是 $O(n^3mlog_2d)$ 的，无法取得本质优化。

我们记邻接矩阵的 $k$ 次方为 $M[k][x][y]$。

考虑加一条边的影响。

我们设加的一条边为 $(u,v)$ 。显然这一步操作会把 $M[0][u][v]$ 置为 $1$ 。接下来要考虑这次加边对 $M[1,2,...,k][x][y]$ 的影响。

我们假设现在将 $M[k][s][t]$ 由 $0$ 更新为 $1$ 。

接下来，我们枚举可以经过 $2^k$ 步走到 $s$ 的点 $p$ 和 $t$ 经过 $2^k$ 步可以走到的点 $q$ 。

有转移 $M[k+1][p][t]|=M[k][p][s]\&\&M[k][s][t]$ 和 $M[k+1][s][q]|=M[k][s][t]\&\&M[k][t][q]$ 。

如果成功地将 $M[k+1][s][t]$ 由 $0$ 更新为 $1$ ，就可以继续用 $M[k+1][s][t]$ 更新 $M[k+2][x][y]$ 的答案。

这个过程不太容易迭代进行，但是可以用递归很容易实现。

复杂度证明：

bfs的复杂度：$nmlog_2d$ 或 $mlog_2d$ 次bfs，每次 $O(n)$

复杂度 $O(n^2mlog_2d)$ 或者 $O(nmlog_2d)$ 。

（取决于是否是多源点bfs）

转移 经过恰好 $d_i$ 步，可到达点集的复杂度：$m$ 次转移，每次转移复杂度 $O(n^2log_2d)$ ，总复杂度 $O(n^2mlog_2d)$。

动态维护邻接矩阵的 $2^k$ 次方的复杂度：

每个状态 $M[k][x][y]$ 至多被更新为 $1$ 一次，且它枚举其他状态进行转移的复杂度为 $O(n)$ ，因此复杂度上限为 状态数 * 单次转移复杂度，即 $O(n^2k*n)=O(n^3k)=O(n^3log_2d)$ 。

于是我们在 $O((n^3+n^2m)·log_2d)$ 的时间复杂度内解决了本题。

Code:
```cpp
#include<cstdio>
#include<cstring>
#define inlien inline
#define retrun return
#define cpnst const
bool valid[33][166][166];
bool enl[166][166];
bool can[166];
int n,m;
void upd(int x,int y,int dep=0)
{
	if(valid[dep][x][y])return;
	valid[dep][x][y]=1;
	if(dep==30)return;
	register int i;
	for(i=1;i<=n;i++)
	{
		if(valid[dep][y][i])
			upd(x,i,dep+1);
		if(valid[dep][i][x])
			upd(i,y,dep+1);
	}
		
}
bool tmp[166];
void jump(bool*x,int lev)
{
	register int i,ii;
	for(i=1;i<=n;i++)tmp[i]=0;
	for(i=1;i<=n;i++)
		if(x[i])
			for(ii=1;ii<=n;ii++)
				if(valid[lev][i][ii])tmp[ii]=1;
	for(i=1;i<=n;i++)x[i]=tmp[i];
}
void trans(bool*x,int tim)
{
	register int i;
	for(i=30;~i;i--)
		if(tim&(1<<i))jump(x,i);
}
int dis[166];
#include<queue>
std::queue<int>q;
int bfs(int f)
{
	register int i;
	for(i=1;i<=n;i++)dis[i]=2e9;
	dis[f]=0,q.push(f);
	while(q.size())
	{
		int t=q.front();q.pop();
		for(i=1;i<=n;i++)
			if(enl[t][i])
				if(dis[i]>1.9e9)
					dis[i]=dis[t]+1,q.push(i);	
	}return dis[n];
}
int solve(int t)
{
	int ret=2e9;
	register int i;
	for(i=1;i<=n;i++)
		if(can[i])
		{
			int rm=bfs(i);
			
			if(rm<ret)ret=rm;
		}
	if(ret<1.9e9)ret+=t;
	return ret;
}
struct pii
{
	int x,y,d;
}p[11111];
bool operator<(cpnst pii x,cpnst pii y)
{return x.d<y.d;}
#include<algorithm>
int main()
{
	scanf("%d%d",&n,&m);
	register int i;
	for(i=1;i<=m;i++)
		scanf("%d%d%d",&p[i].x,&p[i].y,&p[i].d);
	std::sort(p+1,p+m+1);
	int ans=2e9;
	can[1]=1;
	for(i=1;i<=m;i++)
	{
		trans(can,p[i].d-p[i-1].d);
		enl[p[i].x][p[i].y]=1,upd(p[i].x,p[i].y);
		int t=solve(p[i].d);
		if(t<ans)ans=t;
	}(ans>1.9e9)?puts("Impossible"):printf("%d\n",ans);
}
```

---

## 作者：翼德天尊 (赞：3)

题目关心的只有走过的边数，相当于每条边的边权都为 $1$。很熟悉的感觉。

又观察到数据范围。更熟悉了。矩阵加速的味道十分浓重。

如果将当前走过的边数看作时间戳，可以先思考一下若每条边的时间戳都为 $0$，即每条边一开始就存在时，该如何做。

显然，跑一边 bfs 即可解决。无解的情况很好判断，只要 $1$ 号节点在边全都存在的情况下不能到达 $n$ 号节点，则在任意时间戳上皆无法达到。

那么有解的时候呢？我们设 $dp_{i,j}$ 表示走到节点 $j$ 时，长度为 $i$ 的路径是否存在，则显然 $dp_{i,j}$ 可以通过 $j$ 号节点的所有相邻节点 $k$ 的 $dp_{i-1,k}$ 或运算过来。由于递推式子恒定，所以可以考虑矩阵乘法，并且用 与和或 代替 乘和加。

那有 $d_i$ 该怎么做呢？考虑到将所有的 $d_i$ 排序，则两个 $d_i$ 之间的转移方程显然是不变的，我们在每到一个时间戳的时候停止转移，然后从目前所有能到的地方跑一边向终点跑一边多源 bfs，将 bfs 到的最短距离与目前已经走过的边数相加即为当前的答案，修改转移矩阵之后再继续转移即可。注意由于每个时间戳边数不同，所以先到达终点时的答案不一定最优，需要将每个时间戳上的答案全部算出来，取最小值就是答案。

时间复杂度 $O(n^3\log |d|\times m)$，好像过不了。

观察到 $dp$ 值只有 $0$ 和 $1$，所以用 bitset 优化转移即可，时间复杂度会乘上 $\frac{1}{w}=\frac{1}{32}$，差不多能过。

注意用 bitset 的写法需要将两个矩阵对齐，大概可以这么写：

```cpp
node operator *(const node&x,const node&y){
	node z;
	for (int k=1;k<=n;k++)
		for (int i=1;i<=n;i++)
			if (x.a[i][k]) z.a[i]|=y.a[k];
	return z; 
}
```

总体代码如下：

```cpp
#include <bits/stdc++.h> 
using namespace std;
typedef long long ll;
const int N=155;
const ll INF=1e16;
int n,m;
ll ans=INF,dis[N];
struct node{
	bitset<N> a[N];
	node(){
		memset(a,0,sizeof(a));
	}
	void init(){
		for (int i=1;i<=n;i++) a[i][i]=1;
	}
}P,F;
struct node1{
	int u,v,ti;
}e[N];
struct node2{
	int head[N],to[N<<1],next[N<<1],tot;
	void adde(int u,int v){
		to[++tot]=v,next[tot]=head[u],head[u]=tot;
	}
}S;
node operator *(const node&x,const node&y){
	node z;
	for (int k=1;k<=n;k++)
		for (int i=1;i<=n;i++)
			if (x.a[i][k]) z.a[i]|=y.a[k];
	return z; 
}
ll read(){
	ll w=0,f=1;
	char c=getchar();
	while (c>'9'||c<'0'){
		if (c=='-') f=-1;
		c=getchar();
	}
	while (c>='0'&&c<='9'){
		w=(w<<3)+(w<<1)+(c^48);
		c=getchar();
	}
	return w*f;
}
bool cmp(node1 x,node1 y){
	return x.ti<y.ti;
}
node ksm(node H,int k){
	node P;
	P.init();
	while (k){
		if (k&1) P=P*H;
		H=H*H;
		k>>=1;
	}
	return P;
}
ll bfs(){
	queue<int> q;
	for (int i=1;i<=n;i++)
		if (F.a[1][i]==1) q.push(i),dis[i]=0;
		else dis[i]=INF;
	while (!q.empty()){
		int u=q.front();
		q.pop();
		for (int i=S.head[u];i;i=S.next[i]){
			int v=S.to[i];
			if (dis[v]==INF) dis[v]=dis[u]+1,q.push(v);
		}
	}
	return dis[n];
}
int main(){
	n=read(),m=read();
	for (int i=1;i<=m;i++){
		e[i].u=read(),e[i].v=read(),e[i].ti=read();
	}
	sort(e+1,e+1+m,cmp);
	F.a[1][1]=1;
	ll now=1,nowt=0,lat=0;
	while (now<=m){
		F=F*ksm(P,nowt-lat);
		while (now<=m&&e[now].ti==nowt){
			S.adde(e[now].u,e[now].v);
			P.a[e[now].u][e[now].v]=1;
			++now;
		}
		lat=nowt,nowt=e[now].ti;
		ans=min(ans,bfs()+lat);
//		for (int j=1;j<=n;j++){
//			for (int k=1;k<=n;k++)
//				cout<<F.a[j][k]<<" ";
//			puts("ok");
//		}
	}
	if (ans!=INF) cout<<ans<<'\n';
	else puts("Impossible");
	return 0;
}

```

---

## 作者：chenxia25 (赞：3)

开始挖 tzc 遗产（？

这好像是上个赛季的一个 jxd 作业。

---

首先直接 BFS 肯定是不行的，因为你会一边走边会一边增加，那就要加一维步数，那肯定吃不消的。

显然，边集只有 $\mathrm O(m)$ 种，而且对应着若干个连续的时间段。我们不妨枚举最优答案的最后一步是在哪个时间段里面。然后对于每个时间段，它的边集显然是固定的了，那么就可以直接 BFS 了。

那么现在瓶颈在于，该时间段左端点的时候哪些点是可以从 $1$ 出发走到的，这个怎么求，求出来就 BFS 就行了。

这个就是比较套路的东西了。某些萌新可能迷惑邻接矩阵到底有什么用，它明明能被邻接表代替。它终究是一个矩阵，满足这样一个性质：两个邻接矩阵相乘，所得积的 $(i,j)$ 表示若先走前者代表的边集，后走后者代表的边集，那么 $i\to j$ 的路径数。这也太容易理解了，就是矩乘的定义。然后如果用 `bool` 型存的话就表示可达性，它相当于是一个广义矩乘，也是满足性质的。

那么每个时间段的初始点集就是之前的若干个邻接矩阵相乘看第一行就可以了。这个可以从前往后扫的过程中一路乘，对于每个时间段乘快速幂。那复杂度就是 $\mathrm O\!\left(n^3m\log\right)$，过不去。然后是另一个 trick：矩阵里都是 `bool`，于是可以搞出乘法中前者的行和后者的列的 `bitset`，然后查询的话复杂度就除以了一个  $w$。

**_[code](https://www.luogu.com.cn/paste/73bdavqv)_**

---

upd. 2020.12.16：

之前就看到题解区里面有复杂度更优的算法，一直鸽到现在。

复杂度的瓶颈显然在于「那么现在瓶颈在于，该时间段左端点的时候哪些点是可以从 $1$ 出发走到的，这个怎么求」。我们希望搞出不需要 `bitset` 优化的方法。注意到我们虽然维护了邻接矩阵的积，但是最终我们想要的答案确是 $[1\ 0\ 0\ \cdots\ 0]$ 乘以这个矩阵。那么我们很套路的联想到 NOI D1T1，通过向量乘矩阵是 $\mathrm O\!\left(n^2\right)$ 的这个性质来优化。

套路的方法是考虑二进制光速幂，预处理出矩阵的 $2$ 的整次幂的幂。那么现在如果任意时刻，这个维护的东西都是正确的话，那么复杂度显然是 $\mathrm O\!\left(n^2m\log\right)$ 了。那么如何在加边的过程中实时更新这个维护的东西呢？先从最底层考虑，加一条边 $(i,j)$ 对 $0$ 次方的影响显然就是 $(i,j)$ 变成 `true`。然后如果成功改变它了，那么对 $1$ 次方影响是啥呢？回想矩阵乘法公式 $C_{i,j}=\bigvee\limits_{k}A_{i,k}\land B_{k,j}$，那么分为两种情况，$(i,j)$ 充当 $\bigvee$ 后面式子的左项还是右项。前者通过与 $(j,k)$ 配合影响 $1$ 次方的 $(i,k)$，后者通过与 $(k,i)$ 的配合影响 $(k,j)$。然后考虑 $1$ 次方如何影响 $2$ 次方，其实就是对于每次成功修改像 $0\to 1$ 那样套娃就可以了，可以递归写。

如何证明复杂度是对的呢。感觉上觉得很对，也很好证。它的复杂度由两部分构成：每次循环寻找成功修改对象的时间，和成功修改次数。后者来说的话，显然满打满算也是总的是平方对数了，那么前者就是每次成功修改（注意只有成功修改才会尝试影响下一个次方，否则 wyy）都花 $\mathrm O(n)$，总的就是三方对数了。

是不是「思维共套路一色」？

**_[code](https://www.luogu.com.cn/paste/vl8vcj7o)_**

---

## 作者：关怀他人 (赞：3)

#### CF 576D
#### Lemma
一个有向图中从$u$走到$v$经过恰好$k$步的方案数是邻接矩阵$G$的$k$次方中$G^k[u][v]$的值，因为矩阵乘法本质上等于转移的过程。
#### Solution
首先定义两个矩阵，矩阵$A$中$A[i][j]$表示当前走$d$步能否从$i$到达$j$，矩阵$B$中$B[i][j]$表示当前$i\to j$的这条边已经被解锁。

先将所有边按照$d_i$从小到达排序，然后考虑每次加入一条边时，让$A$乘上$B^{d_i-d_{i-1}}$，相当于得出了在第$i$条边解锁之前两点之间经过$d$步的状态。然后对整个图进行一次$bfs/floyd$即可求出当前$1$到$n$的最短路来更新答案。

这样做的时间复杂度是$\mathcal O(n^4\log d)$，无法通过本题。

注意到矩阵中每个点的值只可能为$0$或者$1$，所以用$bitset$优化矩阵乘法即可，时间复杂度$\mathcal O(\frac{n^4\log d}{\omega})$
#### Code
```cpp
int n,m,ans = INF;
int dis[MAXN][MAXN];

struct Edge{
    int u,v,d;

    bool operator < (const Edge &rhs) const{
        return d < rhs.d;
    }
} e[MAXN];

struct Matrix{
    bitset<MAXN> a[MAXN];

    Matrix(){
        for(int i = 1;i <= n;i++)
            a[i].reset();
    }

    friend Matrix operator * (const Matrix &x,const Matrix &y){
        Matrix res;
        for(int i = 1;i <= n;i++){
            for(int j = 1;j <= n;j++){
                if(x.a[i][j])
                    res.a[i] |= y.a[j];
            }
        }
        return res;
    }
} A;

int main(){
    scanf("%d%d",&n,&m);
    for(int i = 1;i <= m;i++)
        scanf("%d%d%d",&e[i].u,&e[i].v,&e[i].d);
    sort(e + 1,e + 1 + m);
    for(int i = 1;i <= n;i++)
        A.a[i][i] = 1;
    for(int x = 1;x <= m;x++){
        Matrix B;
        for(int i = 1;i < x;i++)
            B.a[e[i].u][e[i].v] = 1;
        int y = e[x].d - e[x - 1].d;
        while(y){
            if(y & 1) A = A * B;
            B = B * B;
            y >>= 1;
        }
        for(int i = 1;i <= n;i++){
            for(int j = 1;j <= n;j++)
                dis[i][j] = INF;
            dis[i][i] = 0;
        }
        for(int i = 1;i <= x;i++)
            dis[e[i].u][e[i].v] = 1;
        for(int k = 1;k <= n;k++){
            for(int i = 1;i <= n;i++){
                for(int j = 1;j <= n;j++)
                    dis[i][j] = min(dis[i][j],dis[i][k] + dis[k][j]);
            }
        }
        for(int i = 1;i <= n;i++){
            if(A.a[1][i])
                ans = min(ans,e[x].d + dis[i][n]);
        }
    }
    if(ans < INF) printf("%d\n",ans);
    else printf("Impossible\n");
    return 0;
}
```

---

## 作者：lhm_ (赞：2)

对每条边来说，可以走这条边的限制解除是按$d$的顺序，所以先对每条边按$d$排序。

然后考虑每两条边之间的处理，用一个矩阵表示当前走$d$步是否可以从一个点到另一个点，称其为状态矩阵，用另一个矩阵表示当前解除了限制的边，称其为边矩阵。

每次新加入一条边时，让状态矩阵乘上当前边矩阵的$d_i-d_{i-1}$次方，即可更新走当前步数$d$步点与点之间到达的状态，这一过程可以用矩阵快速幂和$bitset$进行优化。

然后用$floyd$处理出以当前解除限制的边的最短路，若起点能通过$d$步到达一个点，那么就用这个点到终点的最短路径加上$d$来更新答案。

具体实现看代码吧。

$code:$

```cpp
#include<bits/stdc++.h>
#define maxn 200
#define all 150
#define inf 200000000000
using namespace std;
typedef long long ll;
template<typename T> inline void read(T &x)
{
    x=0;char c=getchar();bool flag=false;
    while(!isdigit(c)){if(c=='-')flag=true;c=getchar();}
    while(isdigit(c)){x=(x<<1)+(x<<3)+(c^48);c=getchar();}
    if(flag)x=-x;
}
ll n,m,ans=inf;
ll f[maxn][maxn];
struct edge
{
    int x,y,d;
}ed[maxn];
bool cmp(const edge &x,const edge &y)
{
    return x.d<y.d;
}
struct matrix
{
	bitset<maxn> a[maxn];
	matrix()
	{
        for(int i=1;i<=all;++i) a[i].reset();
	}
}t;
matrix operator *(const matrix &x,const matrix &y)
{
    matrix z;
    for(int k=1;k<=n;++k)
    	for(int i=1;i<=n;++i)
        	if(x.a[i][k])
        		z.a[i]|=y.a[k];
	return z;
}
int main()
{
    read(n),read(m);
    for(int i=1;i<=m;++i)
        read(ed[i].x),read(ed[i].y),read(ed[i].d);
    sort(ed+1,ed+m+1,cmp);
    for(int i=1;i<=n;++i) t.a[i][i]=1;
    for(int p=1;p<=m;++p)
    {
        matrix e;
        for(int i=1;i<p;++i) e.a[ed[i].x][ed[i].y]=1;
        ll k=ed[p].d-ed[p-1].d;
        while(k)
        {
            if(k&1) t=t*e;
            e=e*e,k>>=1;
        }
        for(int i=1;i<=n;++i)
        {
            for(int j=1;j<=n;++j)
            {
                if(i==j) f[i][j]=0;
                else f[i][j]=inf;
            }
        }
        for(int i=1;i<=p;++i) f[ed[i].x][ed[i].y]=1;
        for(int k=1;k<=n;++k)
            for(int i=1;i<=n;++i)
                for(int j=1;j<=n;++j)
                    f[i][j]=min(f[i][j],f[i][k]+f[k][j]);
        for(int i=1;i<=n;++i)
            if(t.a[1][i])
                ans=min(ans,ed[p].d+f[i][n]);
    }
    if(ans==inf) puts("Impossible");
    else printf("%lld",ans);
    return 0;
}
```


---

## 作者：RainsAFO (赞：2)

题意：

一张$n$个点，$m$条边的有向图，每条边有一个权值$d_i$，一条边只有在走过的边数不小于$d_i$时才能被经过，求从$1$到$n$的最小步数。

这个题一眼就很矩阵快速幂。

我们将边按$d_i$排序，开临接矩阵，按大小遍历每条边；

把遍历到的边加入邻接矩阵。

运用一个结论:

对邻接矩阵$X$，$X^ki,j$表示是否能从$i$经过$k$步到$j$。

直接矩阵快速幂即可。

```cpp
for(int i = 1; i < m; i++) {
	T[e[i].u][e[i].v] = 1;//加入一条边
		for(int j = 1; j < n + 2 && ans < e[i + 1].w; j++ , ans++){
			tim(x , T);
			if(x[1][n] == 1) {
				cout << ans + 1;
				return 0;
			}
		}//对前n步暴力乘
		for(int j = 1 ; j <= n; j++)
			y[j] = T[j];
		qpow(y , e[i + 1].w - ans);
		tim(x , y);
		now = e[i + 1].w;
	}
```


---

## 作者：情非昔比 (赞：2)

## 题目大意:
给出一张有向图，现在在点$1$，要去点$n$。

每条路如果你要走必须在之前走过$d_i$条路。

问至少需要走过多少条路你才能到达目的地。
## 解题思路：
由于邻接矩阵的性质，邻接矩阵$A^k$中第$i$行第$j$列的元素表示是否能够恰好经过$k$步从$i$走到$j$

那我们首先让路对$d_i$排序，这样就能对邻接矩阵一个一个往上加了。

因为对于每一种可以走的路的情况，最多只需要走$n$条路就能够走到目的地了。所以：

- 如果两个排序后相邻的路的$d$值之差小于$n$，那我们就暴力作矩阵乘法。

- 如果两个排序后相邻的路的$d$值之差大于$n$，我们先暴力作$n$次矩阵乘法，然后剩下的就交给矩阵快速幂

这样的复杂度是$O(n^3mlogd)$的，不够优秀。

对于矩阵乘法我们可以用$bitset$实现。复杂度就变成了$O(\frac{n^3mlogd}{w})$
# Code:
```cpp
#include<cstdio>
#include<bitset>
#include<algorithm>
using std::sort;
using std::bitset;
int n,m;
bitset<160>a[160],b[160],T[160];
struct Edge{
	int from,to,w;
	bool operator<(Edge x)const{
		return w<x.w;
	}
}edge[160];
void times(bitset<160>*a,bitset<160> *b){
	bitset<160>res[160];
	for(int i=1;i<=n;i++)
		for(int j=1;j<=n;j++)
			if(a[i][j])res[i]|=b[j];
	for(int i=1;i<=n;i++)a[i]=res[i];
}
void quickpow(bitset<160>*a,int b){
	bitset<160>res[160];
	for(int i=1;i<=n;i++)res[i][i]=1;
	while(b){
		if(b&1)times(res,a);
		times(a,a);
		b>>=1;		
	}
	for(int i=1;i<=n;i++)a[i]=res[i];
}
int main(){
	scanf("%d%d",&n,&m);
	for(int i=1;i<=m;i++)
		scanf("%d%d%d",&edge[i].from,&edge[i].to,&edge[i].w);
	sort(edge+1,edge+m+1);
	for(int i=1;i<=n;i++)
		a[i][i]=1;
	int now=0;
	if(edge[1].w>0)return puts("Impossible"),0;
	for(int i=1;i<m;i++){
		T[edge[i].from][edge[i].to]=1;
		if(edge[i].w==edge[i+1].w)continue;
		for(int j=1;j<=n+1&&now<edge[i+1].w;j++,now++){
			times(a,T);
			if(a[1][n]==1)return printf("%d\n",now+1),0;
		}
		for(int j=1;j<=n;j++)
			b[j]=T[j];
		quickpow(b,edge[i+1].w-now);
		times(a,b);
		now=edge[i+1].w;
	}
	T[edge[m].from][edge[m].to]=1;
	for(int j=1;j<=n+1;j++,now++){
		times(a,T);
		if(a[1][n]==1)return printf("%d\n",now+1),0;
	}
	return puts("Impossible"),0;
}
```

---

## 作者：SunnyYuan (赞：1)

## 思路

首先我们可以按边的权值对边从小到大进行排序。

然后，我们可以从前往后枚举每一条边 $i$，假设边 $i$ 需要经过至少 $d_i$ 条边才能经过这条边，我们就需要将 $1\sim i - 1$ 这些边建成一个图然后看一看走 $d_i$ 步能到达的点有哪些，这是一道经典的矩阵题目，不会的可以看看[P2886](https://www.luogu.com.cn/problem/P2886)。

因为我们已经走了 $d_i$ 条边了，我们可以将边 $i$ 放入图中，然后我们以从 $1$ 走 $d_i$ 步可以到达的点为源点在新图上进行 bfs，看能不能到 $n$ 点，如果能，那么用 $dis_n + d_i$ 更新答案，表示我要先走 $d_i$ 步加入了边 $i$，再走 $dis_n$ 步就到了 $n$。

同时要注意，这个题目的矩阵乘法不进行优化会 TLE，那么我们怎么优化呢？

看以下代码：

```cpp
for (int i = 1; i <= n; i++)
    for (int j = 1; j <= n; j++)
        for (int k = 1; k <= n; k++)
            res.a[i][j] |= (a.a[i][k] & b.a[k][j]);
```

我们发现 `j` 与 `a.a[i][k]` 毫无关系，所以当 `a.a[i][k]` 成立时，整个 `b.a[k]` 都可以与 `res.a[i]` 进行异或，所以这一步就交给 `bitset` 来做就好了。

```cpp
for (int i = 1; i <= n; i++)
    for (int k = 1; k <= n; k++)
        if (a.a[i][k])
            res.a[i] |= b.a[k];
```

## 代码

```cpp
/*******************************
| Author:  SunnyYuan
| Problem: Flights for Regular Customers
| Contest: Luogu
| URL:     https://www.luogu.com.cn/problem/CF576D
| When:    2023-10-09 14:46:28
| 
| Memory:  250 MB
| Time:    4000 ms
*******************************/

#include <bits/stdc++.h>

using namespace std;

const int N = 160, INF = 0x3f3f3f3f;

struct matrix {
    bitset<N> a[N];
} g, ans;

int n, m;

matrix operator*(matrix a, matrix b) {
    matrix res;
    memset(res.a, 0, sizeof(res.a));
    for (int i = 1; i <= n; i++)
        for (int k = 1; k <= n; k++)
            if (a.a[i][k])
                res.a[i] |= b.a[k];
    return res;
}

void pow(matrix& ans, matrix a, int b) {
    while (b) {
        if (b & 1) ans = ans * a;
        a = a * a;
        b >>= 1;
    }
}

struct edge {
    int u, v, w;
} e[N];

int d[N];
queue<int> q;

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    cin >> n >> m;
    for (int i = 1; i <= m; i++) cin >> e[i].u >> e[i].v >> e[i].w;
    sort(e + 1, e + m + 1, [](const edge e1, const edge e2) { return e1.w < e2.w; });
    memset(ans.a, 0, sizeof(ans.a));
    for (int i = 1; i <= n; i++) ans.a[i][i] = 1;
    int pass = 0, res = INF;
    for (int i = 1; i <= m; i++) {
        int u = e[i].u, v = e[i].v, w = e[i].w;
        int take = w - pass;
        pow(ans, g, take);
        g.a[u][v] = 1;

        memset(d, 0x3f, sizeof(d));
        for (int i = 1; i <= n; i++){
            if (ans.a[1][i]) d[i] = 0, q.push(i);
        }

        while (q.size()) {
            int t = q.front();
            q.pop();

            for (int i = 1; i <= n; i++)
                if (g.a[t][i] && d[i] == INF) {
                    d[i] = d[t] + 1;
                    q.push(i);
                }
        }
        pass = w;
        res = min(res, pass + d[n]);
    }
    if (res == INF) cout << "Impossible\n";
    else cout << res << '\n';
    return 0;
}
```

---

## 作者：RQ。。。 (赞：1)

# T1 CF576D Flights for Regular Customers

- 给定一张 n 个点 m条边的有向图。
- 一开始你在 1 号节点，你要走到 n 号节点去。
- 只有当你已经走过了至少 d_i 条边时，你才能走第 i 条边。
- 问最少要走多少条边，或判断无法到达。
- $n , m \le 150 \ \ d_i \le 10^9$。

**solution**

简单来说就是，

- 将边按照限制从小到大排序，依次加入

- 用矩阵快速幂维护可达性，再用一个bitset维护1号点可以到达的点。
- 但是矩乘复杂度有点高，又因为矩乘只用维护0 / 1 ， 所以可以用bitset优化。
- 每加入一个边之后，用bfs求一遍ans，更新即可。

```cpp
#include<bits/stdc++.h>
using namespace std;
const int N = 155;
inline int read()
{
	register int x = 0 , f = 0; register char c = getchar();
	while(c < '0' || c > '9') f |= c == '-' , c = getchar();
	while(c >= '0' && c <= '9') x = (x << 3) + (x << 1) + (c ^ 48) , c = getchar();
	return f ? -x : x;
}
int n , m;
int dis[N];
struct edge{ int u , v , c; }e[N];
bitset<N> to;
queue<int> q;
struct Matrix
{
	bitset<N> a[N];
	bitset<N> friend operator * (const bitset<N> &A , const Matrix &B)
	{
		bitset<N> C;
		for(int i = 0 ; i < n ; ++i) C[i] = (A & B.a[i]).any();
		return C;
	}
	Matrix friend operator * (const Matrix &A , const Matrix &B)
	{
		Matrix C;
		for(int i = 0 ; i < n ; ++i)
			for(int j = 0 ; j < n ; ++j)
				if(A.a[i][j]) C.a[i] |= B.a[j];
		return C;
	}
}mp;

void ksm(Matrix A , int k , bitset<N> &to)
{
	for( ; k ; k >>= 1 , A = A * A)
		if(k & 1) to = to * A;
}

int main()
{
	n = read(); m = read();
	for(int i = 1 ; i <= m ; ++i) e[i].u = read() - 1 , e[i].v = read() - 1 , e[i].c = read();
	sort(e + 1 , e + 1 + m , [&](const edge &A , const edge &B) { return A.c < B.c; });
	to[0] = 1; int ans = 2e9 , lst = 0;
	for(int i = 1 ; i <= m ; ++i)
	{
		if(e[i].c >= ans) break; ksm(mp , e[i].c - lst , to); lst = e[i].c;
		mp.a[e[i].v][e[i].u] = 1;
		for(int j = 0 ; j < n ; ++j) if(to[j]) dis[j] = 0 , q.push(j); else dis[j] = 2e9;
		while(q.size())
		{
			int x = q.front(); q.pop();
			for(int i = 0 ; i < n ; ++i) if(mp.a[i][x] && dis[i] == 2e9) dis[i] = dis[x] + 1 , q.push(i);
		}
		if(dis[n - 1] < 2e9) ans = min(ans , lst + dis[n - 1]);
	}
	if(ans == 2e9) puts("Impossible"); else cout << ans << '\n';
	return 0;	
}
```



---

## 作者：intel_core (赞：0)

每条边解锁的时刻是不同的，所以要把会出现的 $m$ 张图分开考虑。

维护一个 $f_{1,2,\cdots,n}$ 表示当前时刻能走到哪些节点。

如果我们处理出来了当前时刻图的邻接矩阵，那么我们只需要做一次矩阵乘法就能推出下一时刻所有节点的可达性。

但如果我们每次往后一个时刻，都需要一次矩阵乘法的话，那显然就寄了。

> 结论：假设刚解锁这条边在 $l$ 时刻解锁，下一条边要到 $r$ 时刻才能解锁；如果 $r-l>n$，且在 $l,l+1,\cdots,l+n $ 时刻时都无法走到 $n$ 节点，那么 $l+n+1,\cdots,r$ 时刻也不行。

> 证明：若不然，设存在一种走法，在 $l$ 时刻时在 $x$，$t$ 时刻时走到了 $n(t \ge l+n+1)$，且在 $1,2,\cdots,t-1$ 时刻里 $n$ 节点都不可达。

> 那么在 $l,l+1,\cdots,t$ 时刻里经过的点里，一定有两个是重复的，把两次走到重复的点间的点从路径中删掉，可以在更早的时刻到达 $n$ 节点，与最小性矛盾！

> 故结论成立。

有了这个结论，我们每次加一条边之后，只需要最多 $n$ 次矩阵乘法，剩下的交给矩阵快速幂就行。

这时复杂度 $O(n^3m \log T)$，会 $\text{TLE on 10}$。

矩阵乘法维护的是前往每个点的方案数，但你并不用知道方案数。

所以可以用 `bitset` 优化矩阵乘法，复杂度 $O(\frac{n^3m \log T}{w})$。

```cpp
#include<bits/stdc++.h>
using namespace std;
const int NR=200;
int n,m;
struct edge{
	int x,y,t;
	bool operator <(const edge &T)const{
		return t<T.t;
	}
}g[NR];

struct mat{
	int H,W;
	bitset<NR>a[NR];
	void clear(int x=0,int y=0){
		H=x;W=y;
		for(int i=1;i<=H;i++)a[i].reset();
	}
	void init(){
		clear(n,n);
		for(int i=1;i<=n;i++)a[i][i]=1;
	}
};
mat times(mat r1,mat r2){
	//bitset 优化矩阵乘法
	mat res;res.clear(r1.H,r2.W);
	for(int i=1;i<=r1.H;i++)
		for(int k=1;k<=r2.W;k++)
			if(r1.a[i][k])
				res.a[i]|=r2.a[k];
	return res;
}
mat quickpow(mat x,int y){
	mat res;res.init();
	while(y){
		if(y&1)res=times(res,x);
		x=times(x,x);
		y>>=1;
	}
	return res;
}

int main(){
	cin>>n>>m;
	for(int i=1;i<=m;i++)
		scanf("%d%d%d",&g[i].x,&g[i].y,&g[i].t);
	sort(g+1,g+1+m);
	mat now,W;W.clear(n,n);now.clear(1,n);now.a[1][1]=1;
	if(g[1].t){
		puts("Impossible");
		return 0;
	}
	g[m+1].t=2e9;
	for(int i=1;i<=m;i++){
		W.a[g[i].x][g[i].y]=1;
		for(int j=1;j<=min(n,g[i+1].t-g[i].t);j++){
			now=times(now,W);
			bool flag=0;
			for(int k=1;k<=n;k++)flag|=now.a[1][k];
			if(!flag){
				puts("Impossible");
				return 0;
			}
			if(now.a[1][n]){
				cout<<g[i].t+j<<endl;
				return 0;
			}
		}
		now=times(now,quickpow(W,max(0,g[i+1].t-g[i].t-n)));
		bool flag=0;
		for(int k=1;k<=n;k++)flag|=now.a[1][k];
		if(!flag){
			puts("Impossible");
			return 0;
		}
	}
	puts("Impossible");
	return 0;
}
```

---

## 作者：KokiNiwa (赞：0)

[更好阅读体验](https://www.cnblogs.com/YouthRhythms/p/13307435.html)
# 题目链接

[点击打开链接](https://codeforces.com/problemset/problem/576/D)

# 题目解法

考虑枚举最优状态是哪些边解锁了，哪些边没有。这样真的有 $2^n$ 种情况吗？并不是的。将所有边按照解锁需要走过边的数量排序。解锁边的顺序必然是排好序的这样。所以考虑只解锁前 $i$ 条边，走到 $n$ 的最短距离是多少。

所以我们可以这样：每次枚举新解锁了哪一条边，如果当前边需要走 $i$ 步才能解锁，那么看走 $i$ 条边并解锁这个边后可以到哪些点，用那些点跑一边多源 `dfs` 寻找到终点的最短路，更新答案即可。

然而这时间复杂度 $\mathcal O(n^3m\log n)$ 并不能过去。瓶颈是矩阵快速幂。由于矩阵是`0/1` 矩阵，所以使用`bitset`优化即可。比较无脑的`bitset`可以维护矩阵的行和列，维护两个`bitset`数组，这样比较方便写。当然也可以只维护一个`bitset`，这样难理解，而且非常非常没必要。

# 总结

+ `bitset` 优化`0/1`矩阵的乘法。
+ 解锁顺序可以去掉一些边的解锁状态。

# 代码

```cpp
#include <cstdio>
#include <bitset>
#include <queue>
#include <algorithm>
using namespace std;
typedef long long ll;
const int NM = 155;
const ll infll = 0x3f3f3f3f3f3f3f3fll;
typedef bitset<150> bt;
int n, m;
struct Edge {
	int u, v, w;
	inline bool operator < (const Edge &d) const { return w < d.w; }
} eg[NM];
struct Mat {
	bt A[150];
	inline bt & operator [] (const int i) { return A[i]; }
	inline const bt & operator [] (const int i) const { return A[i]; }
	//因为 Mat * 不能保存 const Mat * 的东西
	//所以必须有一种返回 const Mat * 的调用方法 
} A;
bt operator * (const Mat &A, const bt &B) {
	static bt ret;
	for (int i = 0; i < n; ++i) ret[i] = (A[i] & B).any();
	return ret;
}
Mat operator * (const Mat &A, const Mat &B) {
	static Mat ret;
	for (int i = 0; i < n; ++i) ret[i].reset();
	for (int i = 0; i < n; ++i)
		for (int j = 0; j < n; ++j)
			if (A[i][j]) ret[i] |= B[j];
	return ret;
}
void ksm(bt &A, Mat B, int c) {
	for (; c; c >>= 1, B = B * B)
		if (c & 1) A = B * A;
}
bt go;
queue<int> Q;
ll dis[NM];
int main() {
	scanf("%d%d", &n, &m);
	for (int i = 1; i <= m; ++i) {
		scanf("%d%d%d", &eg[i].u, &eg[i].v, &eg[i].w);
		--eg[i].u, --eg[i].v;
	}
	sort(eg + 1, eg + m + 1);
	go[0] = 1;
	ll ans = infll;
	for (int i = 1, t = 0; i <= m; ++i) {
		if (eg[i].w >= ans) break ;
		if (eg[i].w != t) ksm(go, A, eg[i].w - t);
		t = eg[i].w;
		A[eg[i].v][eg[i].u] = 1;
		for (int j = 0; j < n; ++j)
			if (go[j]) Q.push(j), dis[j] = 0;
			else dis[j] = infll;
		while (Q.size()) {
			int u = Q.front();
			Q.pop();
			for (int j = 0; j < n; ++j)
				if (A[j][u] && dis[j] == infll) {
					dis[j] = dis[u] + 1;
					Q.push(j);
				}
		}
		ans = min(ans, t + dis[n - 1]);
	}
	if (ans == infll) printf("Impossible\n");
	else printf("%lld\n", ans);
	return 0;
}
```


---

