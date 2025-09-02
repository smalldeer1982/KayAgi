# 1-Trees and Queries

## 题目描述

Gildong was hiking a mountain, walking by millions of trees. Inspired by them, he suddenly came up with an interesting idea for trees in data structures: What if we add another edge in a tree?

Then he found that such tree-like graphs are called 1-trees. Since Gildong was bored of solving too many tree problems, he wanted to see if similar techniques in trees can be used in 1-trees as well. Instead of solving it by himself, he's going to test you by providing queries on 1-trees.

First, he'll provide you a tree (not 1-tree) with $ n $ vertices, then he will ask you $ q $ queries. Each query contains $ 5 $ integers: $ x $ , $ y $ , $ a $ , $ b $ , and $ k $ . This means you're asked to determine if there exists a path from vertex $ a $ to $ b $ that contains exactly $ k $ edges after adding a bidirectional edge between vertices $ x $ and $ y $ . A path can contain the same vertices and same edges multiple times. All queries are independent of each other; i.e. the added edge in a query is removed in the next query.

## 说明/提示

The image below describes the tree (circles and solid lines) and the added edges for each query (dotted lines).

 ![](https://cdn.luogu.com.cn/upload/vjudge_pic/CF1304E/ae42a3afaaf846d868b755b8beca5100d46809fd.png)Possible paths for the queries with "YES" answers are:

- $ 1 $ -st query: $ 1 $ – $ 3 $ – $ 2 $
- $ 2 $ -nd query: $ 1 $ – $ 2 $ – $ 3 $
- $ 4 $ -th query: $ 3 $ – $ 4 $ – $ 2 $ – $ 3 $ – $ 4 $ – $ 2 $ – $ 3 $ – $ 4 $ – $ 2 $ – $ 3 $

## 样例 #1

### 输入

```
5
1 2
2 3
3 4
4 5
5
1 3 1 2 2
1 4 1 3 2
1 4 1 3 3
4 2 3 3 9
5 2 3 3 9```

### 输出

```
YES
YES
NO
YES
NO```

# 题解

## 作者：kradcigam (赞：34)

# 前言

这场比赛，在最后 $5$ 分钟，我想到了这道题的 $Idea$，但是，没有打完，比赛就结束了。

# 正文

## 题目意思

这道题目的意思就是说，一棵树上每次给 $x$ 和 $y$ 节点连 $1$ 条边，问 $a$ 到 $b$ 之间有没有长度为 $k$ 的边。

## 分析

一开始，我看到这道题就往基环树这里去想，可实际上，这道题的方法却是和[加工零件](https://www.luogu.com.cn/problem/P5663)这道题是有异曲同工之处，作者那道题里面也写了篇[题解](https://zhaohaikun.blog.luogu.org/solution-p5663)，不会的同学可以去看一看。

这道题难处理的地方就是加 $1$ 条边这个地方很难处理，但是我们可以想一想，实际上可能的路径一共就**3条**。

1. $a \implies b$ 这是最原始的路径。

2. $a \implies x \implies y \implies b$ 这是借助 $x,y$ 的路径

3. $a \implies y \implies x \implies b$ 这是借助 $y,x$ 的路径。

也就是
```cpp
bool check(int x,int y){
    if(x<=y&&x%2==y%2)return true;
    return false;
}
while(T--){
    int x,y,a,b,k;
    read(x);read(y);read(a);read(b);read(k);
    int ab=dist(a,b),ax=dist(a,x),yb=dist(b,y),ay=dist(a,y),bx=dist(b,x);
    if(check(ab,k)||check(ax+yb+1,k)||check(ay+bx+1,k))puts("YES");
    else puts("NO");
}
```

​    

​    

### 处理往回走



可能有读者会问，走到 $1$ 个点，再走回来，这个怎么办呢？我们发现走到 $1$ 个点再回来，这样 $1$ 次路径长度是 $2$。所以我们这 $3$ 条路径当中，只要有 $1$ 条路径满足一下 $2$ 个条件，就说明存在这样一条长度为 $k$ 的路径。

1. **路径长度 $\leq k$ 这一个很显然。**长度 $> k$，显然就是不合法的。

2. **路径长度和 $k$ 奇偶性相同。**这就是基于往回走的做法，奇偶性相同，就代表两个数的差是偶数，所以就是可以组成长度为 $k$ 路径。

### 预处理 $2$ 点之间的距离

我们刚才说了，两个点之间的距离显然是要求出来的，我们需要预处理 $LCA$，不会的同学可以左转[题解区](https://www.luogu.com.cn/problemnew/solution/P3379)，我用的是最朴素的倍增 $LCA$。

```cpp
void dfs(int x,int f){
    dep[x]=dep[f]+1;
    fa[x][0]=f;
    for(int i=1;(1<<i)<=dep[x];i++)
		fa[x][i]=fa[fa[x][i-1]][i-1];
    for(int i=head[x];i;i=nxt[i])
		if(t[i]!=f)dfs(t[i],x);
}
int lca(int x,int y){
    if(dep[x]<dep[y])swap(x,y);
    while(dep[x]>dep[y])x=fa[x][lg[dep[x]-dep[y]]-1];
    if(x==y)return x;
    for(int k=lg[dep[x]]-1;k>=0;k--)
		if(fa[x][k]!=fa[y][k])x=fa[x][k],y=fa[y][k];
    return fa[x][0];
}
int dist(int x,int y){//x号节点和y号节点的距离
    int z=lca(x,y);
    return dep[x]+dep[y]-dep[z]*2;
}
```

## 代码

```cpp
#include <bits/stdc++.h>
using namespace std;
template<typename T>inline void read(T &FF){
    T RR=1;FF=0;char CH=getchar();
    for(;!isdigit(CH);CH=getchar())if(CH=='-')RR=-1;
    for(;isdigit(CH);CH=getchar())FF=(FF<<1)+(FF<<3)+(CH^48);
    FF*=RR;
}//快读
template<typename T>void write(T x){
    if(x<0)putchar('-'),x*=-1;
    if(x>9)write(x/10);
    putchar(x%10+48);
}//快写
int dep[500010],fa[500010][22],lg[500010],head[500010],nxt[500010],t[500010],tot;
void add(int x,int y){
    t[++tot]=y;
    nxt[tot]=head[x];
    head[x]=tot;
}//连边
void dfs(int x,int f){
    dep[x]=dep[f]+1;
    fa[x][0]=f;
    for(int i=1;(1<<i)<=dep[x];i++)
		fa[x][i]=fa[fa[x][i-1]][i-1];
    for(int i=head[x];i;i=nxt[i])
		if(t[i]!=f)dfs(t[i],x);
}//预处理father
int lca(int x,int y){
    if(dep[x]<dep[y])swap(x,y);
    while(dep[x]>dep[y])x=fa[x][lg[dep[x]-dep[y]]-1];
    if(x==y)return x;
    for(int k=lg[dep[x]]-1;k>=0;k--)
		if(fa[x][k]!=fa[y][k])x=fa[x][k],y=fa[y][k];
    return fa[x][0];
}//LCA
int dist(int x,int y){
    int z=lca(x,y);
    return dep[x]+dep[y]-dep[z]*2;
}//x、y两点之间的距离
bool check(int x,int k){
    if(x<=k&&x%2==k%2)return true;
    return false;
}//检查长度为x的边是否满足前文讲得2个条件
int main(){
	int n;
    read(n);
    for(int i=1;i<n;i++){
        int x,y;
        read(x);read(y);
        add(x,y);add(y,x);
    }
    dfs(1,0);
    for(int i=1;i<=n;i++)lg[i]=lg[i-1]+(1<<lg[i-1]==i);//预处理除log
    int T;
    read(T);
    while(T--){
        int x,y,a,b,k;
        read(x);read(y);read(a);read(b);read(k);
        int ab=dist(a,b),ax=dist(a,x),yb=dist(b,y),ay=dist(a,y),bx=dist(b,x);//3条边
        if(check(ab,k)||check(ax+yb+1,k)||check(ay+bx+1,k))puts("YES");//有1条符合条件，就代表有
        else puts("NO");//3条都不符合就代表没有
    }
    return 0;
}
```

# 后记

这道题还是很有思考的价值，也算是积累了经验**看到一棵树加 $1$ 条边，未必一定要往基环树想**。希望觉得好的同学可以点赞，有问题请在评论区表述一下，是我的题解都够再完善一下。

---

## 作者：wucstdio (赞：8)

为啥感觉这次 Div2 出的有点像 Div3…… AK 的一片一片的。

### 题目大意

给定一个 $n$ 个点的树,相邻点的距离为 $1$。

$q$ 个询问，每个询问包含无个整数：$x,y,a,b,k$。表示询问如果在原树上新连上一条边 $(x,y)$，从 $a$ 点是否有距离为 $k$ 的到 $b$ 的路径。

### 数据范围

$3\le n\le 10^5,1\le q\le 10^5$

### 解题过程

首先考虑不连新边怎么做。

首先我们可以得到一条简单路径 $a\to b$，设它的长度为 $l$。

因为这条路径是最短路径，所以如果 $k<l$ 那就不合法。

接下来我们先给出一个结论：路径合法，当且仅当 $k-l$ 能被 $2$ 整除。

先证明必要性：如果 $k>l$，则必定有边被经过了大于 $1$ 次。考虑一条边 $(u,v)$，如果这条边在 $a\to b$ 的简单路径上，那就一定被经过了奇数次，否则一定被经过了偶数次。所以如果路径合法，$k-l$ 一定可以被 $2$ 整除。

再证明充分性：我们只需要走到 $b$ 之后，任意选择一条边并且来回走一次，路径长度就会增加 $2$，所以若 $k-l$ 可以被 $2$ 整除，我们一定能找到这么一条路径。

接下来考虑连新边。

基本思路还是不变的：先走出来一条长度尽可能短的路径，然后看是否能被 $2$ 整除。

由于新边的存在，有可能会出现奇环，所以需要考虑是否经过新边。

由于经过方向有两种，所以需要分情况讨论一下，只要有一个合法那就合法。

一句话题解：看 $d(a,b),d(a,x)+1+d(y,b),d(a,y)+1+d(x,b)$ 里面是否有一个 $\le k$ 并且和 $k$ 奇偶性相同。

写个 LCA 就行了，时间复杂度 $O(n\log n)$。~~（直接粘板子真爽）~~

### 代码

```cpp
#include<cstdio>
using namespace std;
struct Edge
{
	int to;
	int nxt;
}e[200005];
int n,m,edgenum,head[100005],f[100005][25],pa[100005],dep[100005];
void add(int u,int v)
{
	e[++edgenum].to=v;
	e[edgenum].nxt=head[u];
	head[u]=edgenum;
}
void dfs(int node,int depth)
{
	dep[node]=depth;
	for(int hd=head[node];hd;hd=e[hd].nxt)
	{
		if(e[hd].to==pa[node])continue;
		pa[e[hd].to]=f[e[hd].to][0]=node;
		dfs(e[hd].to,depth+1);
	}
}
int LCA(int a,int b)
{
	if(dep[a]<dep[b])return LCA(b,a);
	for(int i=0;(1<<i)<=dep[a]-dep[b];i++)
	  if((1<<i)&(dep[a]-dep[b]))
	    a=f[a][i];
	if(a==b)return a;
	for(int i=20;i>=0;i--)
	{
		if(f[a][i]!=f[b][i])
		{
			a=f[a][i];
			b=f[b][i];
		}
	}
	return pa[a];
}
int dis(int u,int v)
{
	int d=LCA(u,v);
	return dep[u]+dep[v]-2*dep[d];
}
int main()
{
	scanf("%d",&n);
	for(int i=1;i<n;i++)
	{
		int u,v;
		scanf("%d%d",&u,&v);
		add(u,v);
		add(v,u);
	}
	dfs(1,1);
	for(int i=1;i<=20;i++)
	{
		for(int j=1;j<=n;j++)
		  f[j][i]=f[f[j][i-1]][i-1];
	}
	scanf("%d",&m);
	for(int i=1;i<=m;i++)
	{
		int x,y,a,b,k;
		scanf("%d%d%d%d%d",&x,&y,&a,&b,&k);
		int d1=dis(a,b),d2=dis(a,x)+dis(b,y)+1,d3=dis(a,y)+dis(b,x)+1;
		if(k>=d1&&(k-d1)%2==0)puts("YES");
		else if(k>=d2&&(k-d2)%2==0)puts("YES");
		else if(k>=d3&&(k-d3)%2==0)puts("YES");
		else puts("NO");
	}
	return 0;
}
```

---

## 作者：dblark (赞：2)

判断一条长度为 $ k $ 的路径是否存在，需要用奇偶性判断，具体可以看[加工零件题解区](https://www.luogu.com.cn/problemnew/solution/P5663)

此题中有特殊之处：原图是一棵树，并且加边操作相互独立，那么我们直接用 LCA 求路径长度即可。

加边之后我们有两种路径：一种从原来的树上走，一种从新边走。

剩下的就是基本操作了。

```cpp
#include <cstdio>
#include <vector>
#include <algorithm>
#define N 100005

int n, q;
int d[N], lg[N], f[N][25];
std::vector<int> v[N];

void dfs(int x, int fa) {
    f[x][0] = fa;
    d[x] = d[fa] + 1;
    for (int i = 1; i <= lg[d[x]]; ++i) f[x][i] = f[f[x][i - 1]][i - 1];
    for (int i : v[x]) if (i != fa) dfs(i, x);
}
inline int lca(int x, int y) {
    if (d[x] < d[y]) std::swap(x, y);
    while (d[x] > d[y]) x = f[x][lg[d[x] - d[y]]];
    if (x == y) return x;
    for (int i = lg[d[x]]; ~i; --i)
        if (f[x][i] != f[y][i])
            x = f[x][i], y = f[y][i];
    return f[x][0];
}
inline int dis(int x, int y) {
    return d[x] + d[y] - (d[lca(x, y)] << 1);
}

/* 以上为 LCA 基本操作 */

int main() {
    scanf("%d", &n);
    for (int i = 1, x, y; i < n; ++i) {
        scanf("%d%d", &x, &y);
        v[x].push_back(y);
        v[y].push_back(x);
    }
    for (int i = 2; i <= n; ++i) lg[i] = lg[i >> 1] + 1;
    dfs(1, 0);
    scanf("%d", &q);
    for (int i = 0, x, y, a, b, k, Dis; i < q; ++i) {
        scanf("%d%d%d%d%d", &x, &y, &a, &b, &k);
        Dis = dis(a, b);
        if (Dis <= k && (Dis & 1) == (k & 1)) { puts("YES"); continue; }
        Dis = std::min(dis(a, x) + dis(b, y) + 1, dis(a, y) + dis(b, x) + 1); // 容易错的地方，注意两种可能中只有一种是较小的
        if (Dis <= k && (Dis & 1) == (k & 1)) { puts("YES"); continue; }
        puts("NO");
    }
    return 0;
}
```

---

## 作者：_ztyqwq (赞：2)

### Description

~~从前~~有一棵树。

~~从前~~还有 $ q $ 个询问。

每次询问，~~有一位高人~~在树上的 $ x $ 与 $ y $ 点之间连了一条边。

然后请问，$ a $ 与 $ b $ 点之间是否存在长度为 $ k $ 的路径。

一条边可以重复走，询问与询问之间无关。

### Solution

看上去这是一道基环树的题目。但是仔细一想就会发现，如果对每个询问都按基环树做一遍，因为每个基环树都是不同的，时间复杂度至少也是 $ O(nq) $。

又发现一条边可以重复走，求两点之间是否存在长度为 $ k $ 的路径，很容易想到奇偶性。

其实还容易想到今年 CSP-J ~~（普及）~~ 的 T4 [加工零件](https://www.luogu.com.cn/problem/P5663)。那道题的形式与此题类似，但是它用的是最短路，在这道题中就要跑 $ q $ 次最短路，显然不很合适。

我们先考虑不加一条边的情况，那么这样 $ a $ 与 $ b $ 之间的最短路只有一条，不妨设其长度为 $ dis1 $，且 $ a $ 与 $ b $ 间的所有路径，长度都与 $ dis1 $ 奇偶性相同。这些路径都可以看成是 $ a, b $ 最短路的延伸路径，因为它们都只是在最短路的基础上加了一些重复的边，长度 $ = dis1 + 2k, k \in \mathbb{N} $

加上一条边以后，我们发现，要想使新的路径与原本的那条最短路以及其延申有 **本质的不同**，就 **必须经过这条新加的边 $ (x, y) $**。

这样看来，（在加入一些重复边后）可能成为答案的路径有三种：

1. $ a \rightarrow b\ (dis1) $

2. $ a \rightarrow x \Rightarrow y \rightarrow b\ (dis2) $

3. $ a \rightarrow y \Rightarrow x \rightarrow b\ (dis3) $

其实后两种路径奇偶性是相同的，但是可能一个长度比 $ k $ 大，一个长度比 $ k $ 小，导致我们需要把两个都求出来，才能判断是否有一个可以成为答案。

注意所有的单箭头指的是 **原树中两点的最短路**，双箭头特指加入的新边。

如何判断一条路径是否可能成为答案？不妨设它的总长为 $ dis $。则这条路径（加入重复边后）能成为答案 $ \Leftrightarrow dis \geqslant k $ 且 $ dis $ 与 $ k $ 奇偶性相同。

那么我们只需要把三条路径的长度，即 $ dis1, dis2, dis3 $ 分别 `check` 一遍，如果至少有一个可能成为答案，就输出 `YES`，否则就是 `NO`。

什么？你问我怎么求树上最短路？？？ `dis(a, b) = dep[a] + dep[b] - dep[lca] * 2`。 [戳](https://www.luogu.com.cn/paste/jrcnrcqn)[这里](https://www.luogu.com.cn/problem/P3379)

时间复杂度：$ O(n\log n + q\log n) $（预处理 $ O(n\log n) $，每次求 `LCA` $ O(\log n) $。

### Code

```cpp
#include <bits/stdc++.h>
using namespace std;
struct Edge
{
	int to, nxt;
}e[200001];
int ecnt = 0, head[100001];
void addedge(int from, int to)
{
	e[ecnt].nxt = head[from];
	head[from] = ecnt;
	e[ecnt++].to = to;
}
int fa[100001], dep[100001];
void build(int u)
{
	for(int i = head[u]; i != -1; i = e[i].nxt)
	{
		int v = e[i].to;
		if(v == fa[u])
			continue;
		fa[v] = u;
		dep[v] = dep[u] + 1;
		build(v);
	}
}
int n, logn;
int st[100001][20];
void st_init()
{
	logn = ceil(log2(n));
	for(int i = 1; i <= n; i++)
		st[i][0] = i;
	for(int i = 1; i <= logn; i++)
		for(int j = 1; j <= n; j++)
			st[j][i] = st[fa[st[j][i - 1]]][i - 1];
}
void up(int &u, int &v)
{
	if(dep[u] < dep[v])
		swap(u, v);
	int du = dep[u], dv = dep[v];
	for(int i = logn; i >= 0; i--)
		if(du - (1 << i) >= dv)
		{
			du -= (1 << i);
			u = fa[st[u][i]];
		}
}
int LCA(int u, int v)
{
	up(u, v);
	for(int i = logn; i >= 0; i--)
		if(st[u][i] != st[v][i])
		{
			u = fa[st[u][i]];
			v = fa[st[v][i]];
		}
	return u;
}
int dis(int u, int v)
{
	int lca = LCA(u, v);
	return dep[u] + dep[v] - (dep[lca] << 1);
}
bool ok(int a, int b)
{
	return a >= b && !((a - b) & 1);
}
int main()
{
	memset(head, -1, sizeof(head));
	scanf("%d", &n);
	for(int i = 1; i < n; i++)
	{
		int u, v;
		scanf("%d %d", &u, &v);
		addedge(u, v);
		addedge(v, u);
	}
	dep[1] = 0;
	fa[1] = 1;
	build(1);
	st_init();
	int q;
	scanf("%d", &q);
	while(q--)
	{
		int x, y, a, b, k;
		scanf("%d %d %d %d %d", &x, &y, &a, &b, &k);
		int d1 = dis(a, b), d2 = dis(a, x) + 1 + dis(y, b), d3 = dis(a, y) + 1 + dis(x, b);
		if(ok(k, d1) || ok(k, d2) || ok(k, d3))
			printf("YES\n");
		else
			printf("NO\n");
	}
	return 0;
}
```

---

## 作者：Rossie65536 (赞：1)

[更好的阅读方式](https://www.cnblogs.com/ASTiKi/p/12315573.html)

# 题目大意
给你一棵无根树，然后询问Q次，每次把点$x$和点$y$连接，问你从点$a$到点$b$是否有一条长度为$k$的简单路径，每次询问完后会把新添加的边删除。

## 思路：树上LCA
题目跟2019pjt4很像，可以说这个就是那道题的树上版本。

因为每次讯问完都会把新添的边删去，所以我们只要想如何处理添完一条边后$a$到$b$的简单路径。

所以我们可以分两种情况讨论：

1. 把$\left ( x,y \right )$算进$\left ( a,b \right )$的路径。 
1. 只算$\left ( a,b \right )$的路径。 

简单来说就是求a->x->y->b或a->y->x->b或a->b的路径，众所周知树上两点之间的路径长度可以用LCA来求然后就没了。

然后我们想一下，如果$k$比路径长度大的话，我们就往父亲节点走，很容易发现，如果多出来的部分如果不是2的倍数的话，那么就不存在一条长度为$k$的路径。

不理解的可以自己画一下图。

# 代码
```cpp
#include <bits/stdc++.h>

#define RI register int

using namespace std;

template <class T>
inline void read(T &x) {
    T f = 1; x = 0; char c = getchar();
    while(c > '9' || c < '0') {
        if(c == '-')
            f = -f;
        c = getchar();
    }
    while(c >= '0' && c <= '9') {
        x = x * 10 + c - '0';
        c = getchar();
    }
    x *= f;
}

const int N = 1e5 + 7;
int n;
struct Edge {
    int nxt, to;
} edge[N << 1];
int head[N], tot;
int dep[N], st[N][21];

inline void add(int x, int y) {
    edge[++tot].nxt = head[x];
    edge[tot].to = y;
    head[x] = tot;
}

inline void Read() {
    read(n);
    for(RI i = 1; i < n; i++) {
        int x, y;
        read(x), read(y);
        add(x, y);
        add(y, x);
    }
}

inline void dfs(int x, int fa) {
    dep[x] = dep[fa] + 1;
    st[x][0] = fa;
    for(RI i = 1; i <= 20; i++)
        st[x][i] = st[st[x][i - 1]][i - 1];
    for(RI i = head[x]; i; i = edge[i].nxt) {
        int y = edge[i].to;
        if(y == fa)
            continue;
        dfs(y, x);
    }
}

inline int Lca(int x, int y) {
    if(dep[y] > dep[x])
        swap(x, y);
    for(RI i = 20; i >= 0; i--)
        if(dep[st[x][i]] >= dep[y])
            x = st[x][i];
    if(x == y)
        return x;
    for(RI i = 20; i >= 0; i--)
        if(st[x][i] != st[y][i])
            x = st[x][i], y = st[y][i];
    return st[x][0];
}

int main() {
    Read();
    dfs(1, 0);
    int T;
    read(T);
    while(T--) {
        int x, y, a, b, k;
        int res1, res2, res3;
        read(x), read(y), read(a), read(b), read(k);
        int Lca1 = Lca(a, b), Lca2_1 = Lca(a,x), Lca2_2 = Lca(y,b), Lca3_1 = Lca(a,y), Lca3_2 = Lca(x,b);
        
        res1 = dep[a] + dep[b] - 2 * dep[Lca1];
        res2 = dep[a] + dep[x] + dep[y] + dep[b] - 2 * dep[Lca2_1] - 2 * dep[Lca2_2] + 1;
        res3 = dep[a] + dep[x] + dep[y] + dep[b] - 2 * dep[Lca3_1] - 2 * dep[Lca3_2] + 1;

        if(res1 <= k && (k - res1) % 2 == 0) {
            puts("YES");
            continue;
        }
        if(res2 <= k && (k - res2) % 2 == 0) {
            puts("YES");
            continue;
        }
        if(res3 <= k && (k - res3) % 2 == 0) {
            puts("YES");
            continue;
        }
        puts("NO");
    }
    return 0;
}
```

---

## 作者：简单666 (赞：0)

我们首先来看一下一条链的情况
---------------------------
假如k>=dis(a,b)那么我们来画个图  
![](https://cdn.luogu.com.cn/upload/image_hosting/uhj7em38.png?x-oss-process=image/resize,m_lfit,h_170,w_225)  
显然k-d是偶数的时候，从左边的点是可以走到右边的  
可以考虑，假如走到右边，要凑齐k，就得往左边走，但是必须还得走回来，所以要*2，所以k-d必须要是偶数  
其实，在环上的都可以转换为链上的情况，只需要分离出环上的两条链转换成上面的那种方法就行  
代码很简单  
```cpp
		int x,y,a,b,k;
		cin>>x>>y>>a>>b>>k;
		int d1=caldis(a,b);
		if(d1<=k&&(k-d1)%2==0){
			cout<<"YES"<<endl;
			continue;
		}
		int d2=caldis(a,x)+1+caldis(b,y);
		if(d2<=k&&(k-d2)%2==0){
			cout<<"YES"<<endl;
			continue;
		}
		int d3=caldis(b,x)+1+caldis(a,y);
		if(d3<=k&&(k-d3)%2==0){
			cout<<"YES"<<endl;
			continue;
		}
		cout<<"NO"<<endl;
```

以下是完整代码  
```cpp
#include<bits/stdc++.h>
using namespace std;
const int maxn=1e5+5;
struct graph{
	int head[maxn],nxt[maxn<<1],to[maxn<<1],cnt;
	inline graph():cnt(1){}
	inline void add(int u,int v){
		nxt[++cnt]=head[u];
		to[cnt]=v;
		head[u]=cnt;
	}
}gr;
int up[maxn][25],dep[maxn],n,q;
void dfs(int u,int fa){
	for(int j=1;j<25;j++){
		up[u][j]=up[up[u][j-1]][j-1];
	}
	for(int i=gr.head[u];i;i=gr.nxt[i]){
		int v=gr.to[i];
		if(v==fa)continue;
		dep[v]=dep[u]+1;
		up[v][0]=u;
		dfs(v,u);
	}
}
int lca(int x,int y){
	if(dep[x]<dep[y])swap(x,y);
	for(int j=24;j>=0;j--){
		if(dep[up[x][j]]>=dep[y]){
			x=up[x][j];
		}
	}
	if(x==y)return x;
	for(int j=24;j>=0;j--){
		if(up[x][j]!=up[y][j]){
			x=up[x][j];
			y=up[y][j];
		}
	}
	return up[x][0];
}
int caldis(int x,int y){
	return dep[x]+dep[y]-2*dep[lca(x,y)];	
}
int main(){
	ios::sync_with_stdio(false);
	cin>>n;
	for(int i=1;i<n;i++){
		int u,v;
		cin>>u>>v;
		gr.add(u,v);
		gr.add(v,u);
	}
	dfs(1,0);
	cin>>q;
	while(q--){
		int x,y,a,b,k;
		cin>>x>>y>>a>>b>>k;
		int d1=caldis(a,b);
		if(d1<=k&&(k-d1)%2==0){
			cout<<"YES"<<endl;
			continue;
		}
		int d2=caldis(a,x)+1+caldis(b,y);
		if(d2<=k&&(k-d2)%2==0){
			cout<<"YES"<<endl;
			continue;
		}
		int d3=caldis(b,x)+1+caldis(a,y);
		if(d3<=k&&(k-d3)%2==0){
			cout<<"YES"<<endl;
			continue;
		}
		cout<<"NO"<<endl;
	}
	return 0;
}
```


---

## 作者：MyukiyoMekya (赞：0)

$dis(u,v)$ 表示 $u$ 到 $v$ 在原来那棵树上的距离，可以用倍增lca $O(\log n)$ 求

从 $a$ 走到 $b$

不走新边，那么距离 $len_1=dis(a,b)$

因为树上的边可以随便走，所以只要 $len_1$ 与 $k$ 同奇偶并且 $len_1 \le k$ 那么就可以输出 $\texttt{YES}$ 了

否则，就强制走新边

有两种情况，一种是从 $a$ 走到 $x$ ，再过新边走到 $y$ ，再从 $y$ 走到 $b$

$len_2=dis(a,x)+1+dis(y,b)$

一种是从 $a$ 走到 $y$ ，再过新边走到 $x$ ，再从 $x$ 走到 $b$

$len_3=dis(a,y)+1+dis(x,b)$

对于 $len_2$ 和 $len_3$ ，跟上面 $len_1$ 一样判断就行了

时间复杂度 $O(q\log n)$

```cpp
// This code wrote by chtholly_micromaker(MicroMaker)
#include <bits/stdc++.h>
#define reg register
#define int long long
using namespace std;
const int MaxN=300050;
struct Edge
{
	int nxt,to;
}E[MaxN<<2];
template <class t> inline void read(t &s)
{
	s=0;
	reg int f=1;
	reg char c=getchar();
	while(!isdigit(c))
	{
		if(c=='-')
			f=-1;
		c=getchar();
	}
	while(isdigit(c))
		s=(s<<3)+(s<<1)+(c^48),c=getchar();
	s*=f;
	return;
}
int hd[MaxN],en,n;
int up[MaxN][21],dep[MaxN];
inline void adde(int u,int v)
{
	++en;
	E[en]=(Edge){hd[u],v};
	hd[u]=en;
	return;
}
inline void dfs(int u,int fa)
{
	up[u][0]=fa;
	for(int i=hd[u];~i;i=E[i].nxt)
	{
		reg int v=E[i].to;
		if(v==fa)
			continue;
		dep[v]=dep[u]+1;
		dfs(v,u);
	}
	return;
}
inline void Init_lca()
{
	for(int k=1;k<21;++k)
		for(int i=1;i<=n;++i)
			up[i][k]=up[up[i][k-1]][k-1];
	return;
}
inline int lca(int u,int v)
{
	if(dep[u]<dep[v])
		swap(u,v);
	if(u!=v)
		for(int k=20;k>=0;--k)
			if(dep[up[u][k]]>=dep[v])
				u=up[u][k];
	if(u==v)
		return u;
	for(int k=20;k>=0;--k)
		if(up[u][k]!=up[v][k])
			u=up[u][k],v=up[v][k];
	return up[u][0];
}
inline int getdis(int u,int v)
{
	return dep[u]+dep[v]-2*dep[lca(u,v)];
}
signed main(void)
{
	memset(hd,-1,sizeof hd);
	reg int u,v;
	cin>>n;
	for(int i=1;i<n;++i)
	{
		read(u);read(v);
		adde(u,v);
		adde(v,u);
	}
	dep[1]=1;dfs(1,0);
	Init_lca();
	int q;cin>>q;
	reg int a,b,k;
	for(int i=1;i<=q;++i)
	{
		read(u);read(v);read(a);read(b);read(k);
		reg int len=getdis(a,b);
		if((len%2==k%2)&&len<=k)
		{
			puts("YES");
			continue;
		}
		reg int len1=getdis(a,u)+getdis(b,v)+1;
		if(len1==k)
		{
			puts("YES");
			continue;
		}
		reg int len2=getdis(a,v)+getdis(b,u)+1;
		if(len2==k)
		{
			puts("YES");
			continue;
		}
		if((len1%2==k%2)&&len1<=k)
		{
			puts("YES");
			continue;
		}
		if((len2%2==k%2)&&len2<=k)
		{
			puts("YES");
			continue;
		}
		// printf("<test> %d %d %d\n",len,len1,len2);
		puts("NO");
	}
	return 0;
}
```



---

