# Zigzag MST

## 题目描述

[problemUrl]: https://atcoder.jp/contests/cf16-final/tasks/codefestival_2016_final_g

$ N $ 個の頂点からなるグラフがあり、頂点には $ 0～N-1 $ の番号が付けられています。辺はまだありません。

辺を追加するクエリを $ Q $ 個処理します。 $ i\ (1≦i≦Q) $ 番目のクエリでは $ A_i,\ B_i,\ C_i $ の $ 3 $ つの整数が与えられるので、以下のように辺を無限本追加します。

- $ A_i $ 番の頂点と $ B_i $ 番の頂点をつなぐ、重み $ C_i $ の無向辺を追加する。
- $ B_i $ 番の頂点と $ A_i+1 $ 番の頂点をつなぐ、重み $ C_i+1 $ の無向辺を追加する。
- $ A_i+1 $ 番の頂点と $ B_i+1 $ 番の頂点をつなぐ、重み $ C_i+2 $ の無向辺を追加する。
- $ B_i+1 $ 番の頂点と $ A_i+2 $ 番の頂点をつなぐ、重み $ C_i+3 $ の無向辺を追加する。
- $ A_i+2 $ 番の頂点と $ B_i+2 $ 番の頂点をつなぐ、重み $ C_i+4 $ の無向辺を追加する。
- $ B_i+2 $ 番の頂点と $ A_i+3 $ 番の頂点をつなぐ、重み $ C_i+5 $ の無向辺を追加する。
- $ A_i+3 $ 番の頂点と $ B_i+3 $ 番の頂点をつなぐ、重み $ C_i+6 $ の無向辺を追加する。
- ...

ただし、頂点番号は mod $ N $ で考えます。 たとえば、$ N $ 番とは $ 0 $ 番のことであり、$ 2N-1 $ 番とは $ N-1 $ 番のことです。

例えば、$ N=16,\ A_i=7,\ B_i=14,\ C_i=1 $ のときは下図のように辺を追加します。（図では最初の $ 7 $ 本のみ）

![](https://cdn.luogu.com.cn/upload/vjudge_pic/AT_codefestival_2016_final_g/21b7df6ea7b04d29d971fb41c7c8a0c5a11c69d3.png)

すべての辺を追加した後のグラフの最小全域木に含まれる辺の重みの和を求めて下さい。

## 说明/提示

### 制約

- $ 2≦N≦200,000 $
- $ 1≦Q≦200,000 $
- $ 0≦A_i,B_i≦N-1 $
- $ 1≦C_i≦10^9 $

### Sample Explanation 1

最小全域木は下図のようになります。 !\[\](https://atcoder.jp/img/code-festival-2016-final/f1a6c3cfd52c386e6da5c8c761a78521.png) 多重辺が存在しうることに注意して下さい。

### Sample Explanation 2

自己ループが存在しうることに注意して下さい。

## 样例 #1

### 输入

```
7 1
5 2 1```

### 输出

```
21```

## 样例 #2

### 输入

```
2 1
0 0 1000000000```

### 输出

```
1000000001```

## 样例 #3

### 输入

```
5 3
0 1 10
0 2 10
0 4 10```

### 输出

```
42```

# 题解

## 作者：zhiyangfan (赞：11)

### 题意
给出一个 $n$ 个点的无向图，点从 $0$ 到 $n-1$ 编号。给出 $q$ 组询问来加边，每次询问有 $A_i,B_i,C_i$ 三个参数，然后会加入形如 $(A_i,B_i,C_i),(B_i,A_i+1,C_i+1),(A_i+1,B_i+1,C_i+2),(B_i+1,A_i+2,C_i+3),(A_i+2,B_i+2,C_i+4)\cdot\cdot\cdot$ 的无限条无向边，这里的加法是在模 $n$ 意义下的。求出 $q$ 组询问后图的最小生成树边权和。($2\le n\le2\times10^6,1\le q\le2\times10^6,1\le C_i\le10^9$)

### 题解
这题需要画很多图。首先我们来画一下按照题目描述，一组询问 $A,B,C$ 会加入的边（后面的省略）：

![](https://cdn.luogu.com.cn/upload/image_hosting/un7xwzm2.png)

而注意到，如果 $(A+1,B,C+1)$ 这条边被加入的话，$(A,B,C)$ 也一定被考虑过了，不管加上没有，$A,B$ 一定是连通的，所以我们可以把 $(A+1,B,C+1)$ 改为 $(A+1,A,C+1)$ 而不影响结果，即：

![](https://cdn.luogu.com.cn/upload/image_hosting/goikki83.png)

类似地，考虑 $(A+1,B+1,C+2)$ 时，$A+1,A,B$ 一定连通了，所以可以把 $(A+1,B+1,C+2)$ 改为 $(B,B+1,C+2)$，即：

![](https://cdn.luogu.com.cn/upload/image_hosting/dzv5atza.png)

一直这么改下去，我们会得到这样一张图：

![](https://cdn.luogu.com.cn/upload/image_hosting/rjalsv1b.png)

注意到这张图的特点是：$A,B$ 之间有一条权值为 $C$ 的边，$A+i,A+i+1$ 之间有一条权值为 $C+1+2i$ 的边，$B+i,B+i+1$ 之间有一条权值为 $C+2+2i$ 的边。方便起见，我们下文把 $A,B$ 之间的边叫做红边，剩下的边叫做绿边。则加入所有的询问之后，原图应该长这样：

![](https://cdn.luogu.com.cn/upload/image_hosting/i8qfojx4.png)

其中加粗的绿边表示有无限条边。当然，因为是最小生成树，其实每两个点之间只有一条边是有用的，也就是权值最小的那条。所以我们接下来的任务就变为了找到两点之间边权值的最小值。

发现绿边其实都是由一个点 $S$ 出发，以 $x$ 为初始权值，每连接一组点给权值加 $2$ 得到的，形式化讲，$S+i,S+i+1$ 之间的权值为 $x+2i$。根据这个性质，我们可以考虑递推计算。我们设 $c_i$ 表示连接 $i$ 和 $i+1$ 的边中的最小权值，初始时均为无穷大。对于每组 $(S,x)$，我们更新一下 $c_S=\min(c_S,x)$。接着考虑连下去的边，则有 $c_{i+1}=\min(c_{i+1},c_{i}+2)(0\le i<n)$，这里的加法依然是模 $n$ 意义下。注意贡献是一个环，所以这个玩意要更新两遍。最终我们得到了 $n+q$ 条边，直接用 $\rm kruskal$ 跑最短路即可，时间复杂度 $\mathcal{O}((n+q)\log (n+q))$。
```cpp
#include <cstdio>
#include <cstring>
#include <algorithm>
const int N = 2e5 + 10; int cst[N], f[N], tp, tot;
struct edge
{ 
    int u, v, w; 
    edge(int u = 0, int v = 0, int w = 0) : u(u), v(v), w(w) { }
}E[N << 1]; long long ans;
int getf(int x) { return x == f[x] ? x : f[x] = getf(f[x]); }
int main()
{
    memset(cst, 0x7f, sizeof (cst)); int n, q; scanf("%d%d", &n, &q); 
    for (int i = 1, A, B, C; i <= q; ++i) 
    {
        scanf("%d%d%d", &A, &B, &C); E[++tp] = edge(A, B, C);
        cst[A] = std::min(cst[A], C + 1); cst[B] = std::min(cst[B], C + 2);
    }
    for (int i = 0; i < n; ++i) cst[(i + 1) % n] = std::min(cst[(i + 1) % n], cst[i] + 2);
    for (int i = 0; i < n; ++i) cst[(i + 1) % n] = std::min(cst[(i + 1) % n], cst[i] + 2);
    for (int i = 0; i < n; ++i) E[++tp] = edge(i, (i + 1) % n, cst[i]), f[i] = i;
    std::sort(E + 1, E + tp + 1, [&](const edge& e1, const edge& e2) { return e1.w < e2.w; });
    for (int i = 1, tx, ty; i <= tp; ++i)
    {
        tx = getf(E[i].u), ty = getf(E[i].v);
        if (tx != ty) ans += E[i].w, f[tx] = ty, ++tot;
        if (tot == n - 1) break;
    }
    printf("%lld\n", ans); return 0;
}
```

---

## 作者：wmy_goes_to_thu (赞：6)

这道题是无穷条边，暴力 Kruskal 肯定不行。

如果把每两点之间的边都取个 min 值，$\mathcal O(n^2)$ 也是不行的。如果我们能把一些没用用的边去掉或者是把一些边改一下两端的点，那么复杂度就降低了。

所以我们开始考虑改边。根据 Kruskal，如果 $x$ 和 $y$ 已经联通，那么现在有一条边 $x$ 和 $z$，可以改成 $y$ 和 $z$。

因为 $a_i$ 和 $b_i$ 在 $a_i$ 和 $b_i+1$ 前面已经出现过了，所以 $a_i$ 和 $b_i$ 已联通，那么 $a_i$ 和 $b_i+1$ 就可以改成 $b_i$ 和 $b_i+1$ 了！所以这变成了一条链（$a_i$ 和 $b_i$ 这条边除外），那么就可以用一个前缀和来做（想一想，为什么），然后跑 Kru 就可以了！复杂度是 $\mathcal O(n+q)$。

代码：

```cpp
#include<bits/stdc++.h>
using namespace std;
struct apple
{
	int x,y,z;
	apple(int x=0,int y=0,int z=0):x(x),y(y),z(z){}
	bool operator<(const apple &other)const
	{
		return z<other.z;
	}
}e[1000005];
int h[400005],fa[200005];
int findfather(int x){return x==fa[x]?x:fa[x]=findfather(fa[x]);}
int main()
{
	memset(h,127,sizeof(h));
	int n,q,m=0;
	cin>>n>>q;
	for(int i=0;i<n;i++)fa[i]=i;
	for(int i=1;i<=q;i++)
	{
		int a,b,c;
		scanf("%d%d%d",&a,&b,&c);
		e[++m]=apple(a,b,c);
		h[a+1]=min(h[a+1],c+1);
		h[b+1]=min(h[b+1],c+2);
	}
	for(int i=1;i<(n<<1);i++)h[i]=min(h[i],h[i-1]+2);
	for(int i=1;i<(n<<1);i++)
	{
		int l1=i%n,l2=(i-1)%n;
		e[++m]=apple(l1,l2,h[i]);
	}
	sort(e+1,e+m+1);
	long long ans=0;
	for(int i=1;i<=m;i++)
	{
		int x=e[i].x,y=e[i].y,z=e[i].z;
		int l1=findfather(x),l2=findfather(y);
		if(l1!=l2)
		{
			ans+=z;
			fa[l1]=l2;
		}
	}
	cout<<ans<<endl;
	return 0;
}
```

---

## 作者：i207M (赞：6)

## 题意

对一张 n 个点的空图 G 做 Q 次加边操作，每次给定 Ai, Bi, Ci，然后按照以下规则按顺序连 10233 条边：(Ai, Bi, Ci),(Bi, Ai + 1, Ci + 1),(Ai + 1, Bi + 1, Ci + 2)…… 以此类推，点的编号均为 mod n 意义下的，求图 G 的最小生成树；

## 实现

乍一看还是有点蒙蔽的，画图后发现，一次Q最多加入N条边，但是，$O(NQ)$依旧不可做呀；

膜拜大神……

方法是这样滴：

考虑一次Q：$(a,b,c)$画图：

![](https://cdn.luogu.com.cn/upload/pic/24175.png)

并没有什么收获……

但是！当我们把A1和B1连起来，**根据K氏法的顺序，我们会先考虑A1B1的边，再考虑A2B1的边，所以此时，A1B1一定在同一个联通块内，这样，A2B1的边，究竟连在B1上还是连在A1上就无所谓了**；

！！！我们就可以重新建边

![](https://cdn.luogu.com.cn/upload/pic/24177.png)

（看横向边）

同时，每一个相邻的边，都是指向i+1，权值都是上一个+2，我们就可以用一个数组记录下来，最后一次递推，求出环上所有边的最小值；

```
	for (ri i = 1, a, b, c; i <= q; ++i) {
        in(a), in(b), in(c);
        add(a, b, c);
        d[a] = min(d[a], c + 1);
        d[b] = min(d[b], c + 2);
    }
    for (ri i = 0; i < n; ++i) {
        d[i] = min(d[i], d[(i - 1 + n) % n] + 2);
    }
    for (ri i = 0; i < n; ++i) {
        d[i] = min(d[i], d[(i - 1 + n) % n] + 2);
    }
```

加边的递推；**一定最后要循环两遍，防止更新不及时**；

## 代码

```
#include<iostream>
#include<cstdio>
#include<cstdlib>
#include<cmath>
#include<cstring>
#include<string>
#include<algorithm>
#include<vector>
#include<map>
#include<set>
#include<list>
#include<queue>
#include<stack>
#include<bitset>
#include<deque>
using namespace std;
#define ll long long
#define inf 0x3f3f3f3f
#define ri register int
#define il inline
#define fi first
#define se second
#define mp make_pair
#define pi pair<int,int>
#define mem0(x) memset((x),0,sizeof (x))
#define mem1(x) memset((x),0x3f,sizeof (x))
#define pb push_back
#define gc getchar
template<class T>void in(T &x)
{
    x = 0; bool f = 0; char c = gc();
    while (c < '0' || c > '9') {if (c == '-') f = 1; c = gc();}
    while ('0' <= c && c <= '9') {x = (x << 3) + (x << 1) + (c ^ 48); c = gc();}
    if (f) x = -x;
}
#undef gc
#define N 200010
#define M N<<3
#define int ll
struct Edge {
    int u, v, w, nx;
    Edge() {}
    Edge(int uu, int vv, int ww, int nxt) {
        u = uu, v = vv, w = ww, nx = nxt;
    }
    friend bool operator<(const Edge& a, const Edge& b) {
        return a.w < b.w;
    }
} edge[M];
int cnt, head[M];
il void add(int u, int v, int w) {
    edge[++cnt] = Edge(u, v, w, head[u]);
    head[u] = cnt;
}
int f[N];
int find(int x) {
    return x == f[x] ? x : f[x] = find(f[x]);
}
bool cmpy(int x, int y) {
    int fx = find(x), fy = find(y);
    if (fx == fy) return 0;
    if (fy > fx) f[fy] = fx;
    else f[fx] = fy;
    return 1;
}
int n, q;
int d[N];
signed main() {
    in(n), in(q);
    mem1(d);
    for (ri i = 1, a, b, c; i <= q; ++i) {
        in(a), in(b), in(c);
        add(a, b, c);
        d[a] = min(d[a], c + 1);
        d[b] = min(d[b], c + 2);
    }
    for (ri i = 0; i < n; ++i) {
        d[i] = min(d[i], d[(i - 1 + n) % n] + 2);
    }
    for (ri i = 0; i < n; ++i) {
        d[i] = min(d[i], d[(i - 1 + n) % n] + 2);
    }
    for (ri i = 0; i <= n; ++i) {
        add(i, (i + 1) % n, d[i]);
    }
    sort(edge + 1, edge + 1 + cnt);
    for (ri i = 1; i < n; ++i) f[i] = i;
    int lt = n, ans = 0;
    for (ri i = 1; i <= cnt && lt > 1; ++i) {
        if (cmpy(edge[i].u, edge[i].v)) {
            ans += edge[i].w;
            --lt;
        }
    }
    printf("%lld", ans);
    return 0;
}
```

---

## 作者：Jryno1 (赞：5)

一种可能理解起来比较自然的做法。

## 题意

一张有 $N$ 个点的图，有 $Q$ 次建边。每次给定三个数 $(A_i,B_i,C_i)$ 表示在 $A_i$和$B_i$ 之间建一条权值为$C_i$的无向边。之后在 $(A_i+1,B_i,C_i+1),(A_i+1,B_i+1,C_i+2),(A_i+2,B_i+1,C_i+3)...$ 同样建边。即每次建边 $(A_i+k,B_i+k,C_i+2k),(A_i+k+1,B_i+k,C_i+2k+1)$ 其中 $0\le k \le \infty$。求这个图的最小生成树

$2\le N \le 200000$ $1 \le Q \le 200000$

## 题目分析

最小生成树，输入又和边密不可分，很容易想到 Kruscal。 但是问题是，无限条边，直接跑肯定不现实，肯定需要寻找更优秀的方法。

#### 性质1：总边数

我们可以尝试模拟一下一条边的情况，这里以 $n=4,A=0,B=2,C=1$ 为例

![](https://cdn.luogu.com.cn/upload/image_hosting/pw4vs0df.png)

 
会发现这时候第五条边和第一条边是重叠的，那么，第六条边和第二条边也会是重叠的。

证明也非常简单，因为是在模 $n$ 意义下的，有 $A+n\equiv A \mod n$ 所以**至多**到第 $2n$ 条边，就会和之前的边重合了。

也就是说，并不是无限条边，每次建边最多只会建 $2n$ 条。

这里还会发现一个小性质，就是一条边通过操作，一定能够把图上所有的点都连通，因为每次+1，所以可以保证每个点都覆盖到。

这个时候我们就有一个暴力的思路，就是把这些边建出来，然后跑最小生成树。~~AT没有暴力分你想什么呢~~

#### 性质2：增加的边权

既然不能直接跑最小生成树，思考如何优化。

思考我们平时跑 Kruscal 的过程。我们每次选择边权最短的边，判断其是否已经在一个连通块中，如果不在则选择这条边，否则忽略。

我们把“每一次边权+1”的限制应用到这里，可以这样操作：

首先把所有所有 $(A_i,B_i,C_i)$ 以 $C$ 为标准，从小到大排序。每次只使用前几个边，保证前几个边的 $C$ 值一定相等，对于这些边经进行和 Kruscal 一样的操作。使用完之后对 $A,B,C$ 进行相应的增加，如此操作，直到选择了 $n-1$ 个就结束了。

可能没有太理解，我们更形象的讲

如果我们三条边的权值分别是$C_1=4,C_2=4,C_3=7$，不管他们连接了什么，我们一定会先判断$C_1,C_2$着两条边，接着，这两个边会增加1，变成$C_1=5,C_2=5,C_3=7$，那么什么时候判断$C_3$？到$C_1=C_2=C_3$的时候就会开始判断$C_3$。

再结合我们提到的性质，因为每条边最多会被操作 $2n$ 次，因此我们对于每条边判断也不会超过 $2n$ 次。这样我们是不是就得到了 $O(m\log m+2n)$ 的算法了？并不是。由于可能有很多条边的边权都是一样的（尤其是在每次最小的边权还会增加的情况下），所以我们最劣的情况可能所有 $m$ 条边都扫一次，再都增加，再都扫一次。因此复杂度是$O(2mn)$。

#### 性质三：重复的边

【NOTE：以下的计算都是在模 $n$ 意义下的】

虽然复杂度不尽人意，但是我们还是可以在这个基础上继续探索。我们把目光集中到每条边连接的点的变化 $(x,y)\to (x+1,y) \to (x+1,y+1)$上面。

在上面的判断下，我们最不想看到的情况就是很多边连接的两个点已经相互连通了，我们称之为“差边”。我们很想把这种“差边”都给扔掉。但是直接扔掉会导致它后面演变出来边无法被统计，而演变出来的边可能不是“差边”。

我们仔细想一下，有没“差边”演变出来的还是“差边”的情况？

实际上是有的。

我们假设现在有一个连接 $(x,y)$ 且边权为 $k$ 的边。目前发现 $(x,y)$ 已经连通了。通过 $x\to a \to b \to y$ 这样一条边联通的。这说明了，一定有这样几条边权不大于 $k$ 的边分别连接了 $(x,a),(a,b),(b,y)$。那么我们观察 $(x+1,y+1)$，是不是同样一定会有几条边权不大于 $k+2$ 的边已经把 $(x+1,a+1),(a+1,b+1),(b+1,y+1)$ 连接了，即 $x+1\to a+1 \to b+1 \to y+1$已经被连接。

这里感性理解就是，你比人家慢一步，你前进一步，别人前进一步，你还是比人家慢一步。

所以我们发现一个“差边”，他后面 $(x+p,y+p)$ 都是“差边”。

#### 小策略：拆边

那么 $(x,y) \to (x+1,y)$ 这次变化呢？我们无法判断 $(x+1,y)$ 是否也是差的。

很简单，我们只想要 $x,y$ 同时增加。那么我们干脆吧这两种分开来！

也就是说，我们对于 $(A_i,B_i,C_i)$ 直接变成 $(A_i,B_i,C_i),(A_i+1,B_i,C_i+1)$，并且使其变化规律变为每次 $A,B$同时 $+1$ ，$C +2$。代码实现就是：


```cpp
for(int i=1;i<=m;i++){
    int u,v,w;
    scanf("%lld%lld%lld",&u,&v,&w);
    alled[++toted]=(edge){u,v,w};
    alled[++toted]=(edge){(u+1)%n,v,w+1};
} 
```


这样的好处是什么？我们虽然要看 $2m$ 个边，但是一旦一个边有一次变差了，我们就可以立刻把它扔掉，所以最后最多是看 $4m$ 次。

这里实现的方法就很多了，我个人用的是链维护。

判断空

```cpp
//ST=start,ED=end
if(nex[ST]==ED){
     pushfront(now);
     now++;
}
```

加入新的可用边，因为$C+2$所以可能有比现在边权还小的边，不过不用慌，最多也就小1，所以放到链首就好了

```cpp
while(now<=toted&&alled[now].w<alled[nex[ST]].w){
    pushfront(now);
    now++;
}
while(now<=toted&&alled[now].w==alled[pre[ED]].w){
    pushback(now);
    now++;
}
```

然后就是正常的 Kruscal 操作。如果它是差的，就把它弹出去。否则更新其数据，并且把它调到链尾。

```cpp
int tmp=nex[ST];
int u=alled[tmp].from,v=alled[tmp].to,w=alled[tmp].w;
if(find(u)==find(v)){
    popx(tmp);
} else {
    fa[find(u)]=find(v);
    ans+=w;
    conn++;
    alled[tmp].from+=1,alled[tmp].to+=1,alled[tmp].w+=2;
    alled[tmp].from%=n,alled[tmp].to%=n;
    popx(tmp);
    pushback(tmp);
}
```
最后输出 ans 就是答案


---

## 作者：wangruibo20 (赞：1)

读完题后应该先看数据范围：

> $2\le N\le200,000$
>
> $1\le Q\le200,000$

这意味着暴力建边条数会直接飙升到 $NQ$ 条，时间和空间都承受不了；这也意味着我们需要改变建边方式。

对于建边操作，若我们要建 $(B,A+1,C+1)$ 这条边，说明 $(A,B,C)$ 早已建好（先有初始才能有变化嘛），

而 Kruskal 算法并不挑剔这条边具体连的两个端点是什么，它只关心两个端点所处的连通块。如果边权为 $C$ 都不能作为最小生成树的边，那 $C+1$ 又怎么可能呢？

所以我们能将 $(B,A+1,C+1)$ 转换为 $(A,A+1,C+1)$ ，同理，$(A+1,B+1,C+2)$ 变为 $(B,B+1,C+2)$，$(B+1,A+2,C+3)$ 变为 $(A+1,A+2,C+3)\dots\dots$

然后边的数量就能从 $NQ$ 降到 $N+Q$ 条了，Kruskal 毫无压力地通过了这道题。

Code：

```cpp
#include<bits/stdc++.h>
using namespace std;
#define ll long long
ll n,m,x,y,z,fath[200005],a[200005],ans;
struct edge{
	ll u,v,qz;
}e[400005];
bool cmp(edge a,edge b){
	return a.qz<b.qz;
}ll gf(ll x){
	return fath[x]==x?x:fath[x]=gf(fath[x]);
}int main(){
	memset(a,0x3f3f3f3f,sizeof a);
	scanf("%lld%lld",&n,&m);
	for(ll i=1;i<=n;i++)fath[i]=i;
	for(ll i=1;i<=m;i++){
		scanf("%lld%lld%lld",&x,&y,&z);
		x++,y++;
		e[i].u=x,e[i].v=y,e[i].qz=z;
		a[x]=min(a[x],z+1),a[y]=min(a[y],z+2);
	}for(ll i=0;i<2*n;i++){
		a[i%n+1]=min(a[(i+n-1)%n+1]+2,a[i%n+1]);
		if(i>=n)e[m+i-n+1].u=i%n+1,e[m+i-n+1].v=(i+1)%n+1,e[m+i-n+1].qz=a[i%n+1];
	}sort(e+1,e+1+m+n,cmp);
	for(ll i=1,cnt=0;i<=m+n&&cnt<n-1;i++){
		ll x=gf(e[i].u),y=gf(e[i].v);
		if(x!=y){
			fath[x]=y;
			ans+=e[i].qz;
			cnt++;
		}
	}printf("%lld",ans);
	return 0;
} 
```



---

## 作者：rq_kyz (赞：1)

# 【题解】Zigzag MST

### 传送门

[Zigzag MST](https://www.luogu.com.cn/problem/AT_codefestival_2016_final_g)

---

### 题意

有 $n$ 个节点围成一圈，$m$ 次操作，每次给定数字 $A$、$B$、$C$，表示连接边 $(A,B,C)$、$(A+1,B,C+1)$、$(A+1,B+1,C+2)$、$(A+2,B+1,C+3)$……问最终图中的最小生成树大小。

---

### 分析

我们以操作 $(A,B,C)$ 为例，如下图所示：

![](https://s11.ax1x.com/2024/01/16/pFFifjs.png)

我们发现，一次操作最多只需要连接 $n-1$ 条边。为了方便，我们可以把点整理一下，得到下图：

![](https://s11.ax1x.com/2024/01/16/pFFi5Bq.png)

注意到，如果我们需要建 $(B,A+1,C+1)$ 这条边，$(A,B,C)$ 一定已经建好，也就是说建边 $(B,A+1,C+1)$ 时 $A$ 与 $B$ 一定联通，所以我们可以将 $(B,A+1,C+1)$ 变为 $(A,A+1,C+1)$，这个操作并不影响连通性，也不影响权值总和，所以是等价的。

接下来同理，我们把 $(A+1,B+1,C+2)$ 变为 $(B,B+1,C+2)$、$(B+1,A+2,C+3)$ 变为 $(A+1,A+2,C+3)$……

如下图：

![](https://freeimg.cn/bUFThV.gif)

最后再把变换完的边和点变为整理前的样子，如下图：

![](https://s11.ax1x.com/2024/01/16/pFFi4un.png)

所以我们拿到一个操作后只需要顺时针循环建边就行了。注意到，如果有多个操作，则不需要在两个相邻的点之间建多条边，只需要取权值最小的一条边就行了，这就是本题省边的策略。

再利用 Kruskal 算法求出最小生成树的大小，本题结束！

---

### 代码

```cpp
#include <bits/stdc++.h>
#define ll long long
using namespace std;
ll a[200001];
struct s{
	ll x,y,l;
}b[600001];
ll cd=0;
bool f(s num1,s num2){
	return num1.l<num2.l;
}
ll bcj[200001];
void init(ll n){
	for(ll i=1;i<=n;i++)
		bcj[i]=i;
}
ll getfather(ll x){
	if(bcj[x]==x)
		return x;
	return bcj[x]=getfather(bcj[x]);
}
void hb(ll x,ll y){
	bcj[getfather(y)]=getfather(x);
}
int main(){
	memset(a,0x7f,sizeof(a));
	ll n,m,k=2e5;
	scanf("%lld%lld",&n,&m);
	for(ll i=1;i<=m;i++){
		ll x,y,l;
		scanf("%lld%lld%lld",&x,&y,&l);
		x++;
		y++;
		k=min(k,min(x,y));
		b[++cd].x=x;
		b[cd].y=y;
		b[cd].l=l;
		a[x]=min(a[x],l+1);
		a[y]=min(a[y],l+2);
	}
	ll qz=2e9;
	for(ll i=1;i<=2*n;i++){
		if(a[k])
			qz=min(qz,a[k]);
		b[++cd].x=k;
		b[cd].y=k%n+1;
		b[cd].l=qz;
		k=k%n+1;
		qz+=2;
	}
	sort(b+1,b+cd+1,f);
	init(n);
	k=0;
	ll sum=0;
	for(ll i=1;i<=cd && k<n-1;i++){
		ll x=b[i].x,y=b[i].y,l=b[i].l;
		if(getfather(x)==getfather(y))
			continue;
		sum+=l;
		hb(x,y);
		k++;
	}
	printf("%lld",sum);
	return 0;
}
```

---

## 作者：Prophesy_One (赞：1)

### 题意：

在 $n$ 个点里的图做 $q$ 次操作。
令 $(a,b,c)$ 表示一条 $a$ 与 $b$ 之间的边权为 $c$ 的无向边，第 $i$ 次操作连接无限条边 $(a_i,b_i,c_i),(b_i,a_i+1,c_i+1),(a_i+1,b_i+1,c_i+2),(b_i+2,a_i+1,c_i+3),\dots$。

求最小生成树。

$n,q \leq 2 \times 10^5$。

### 思路：

把所有边建出显然不现实。考虑一次操作：

![](https://cdn.luogu.com.cn/upload/image_hosting/yritgxca.png)

因为从连通性来说，若存在边 $(x,y)$，新加入一条 $(y,z)$，那么等价于 $(x,z)$。故经过转化可以得到下图：

![](https://cdn.luogu.com.cn/upload/image_hosting/twh1hugl.png)

发现一次操作中环上相邻两边差值为 $2$。设 $f_i$ 表示 $i$ 与 $i+1$ 之间的最小边权，显然在加入时有 $f_a=\min(f_a,c+1),f_b=\min(f_b,c+2)$。

然后在环上递归转移有 $f_i=\min(f_i,f_{i-1}+2)$，转两次即可。

然后跑最小生成树即可。时间复杂度 $\text{O}(n+q)$。

### 代码：
```cpp
#include<cstdio>
#include<algorithm>
using namespace std;
typedef long long ll;
const int N=2e5+5;
const ll inf=1e18;
struct edge
{
	int x,y;
	ll z;
}e[N<<1];
int n,q,fa[N];
ll val[N];
int read()
{
	int res,f=1;
	char ch;
	while((ch=getchar())<'0'||ch>'9')
	if(ch=='-')
	f=-1;
	res=ch^48;
	while((ch=getchar())>='0'&&ch<='9')
	res=(res<<1)+(res<<3)+(ch^48);
	return res*f;
}
int find(int x)
{
	return fa[x]==x?x:fa[x]=find(fa[x]);
}
bool cmp(edge x,edge y)
{
	return x.z<y.z;
}
int main()
{
	int i,x,y,cnt=0;
	ll z,ans=0;
	n=read();q=read();
	for(i=0;i<=n-1;i++)
	{
		val[i]=inf;
		fa[i]=i;
	}
	for(i=1;i<=q;i++)
	{
		x=read();y=read();z=read();
		e[i]=(edge){x,y,z};
		val[x]=min(val[x],z+1);
		val[y]=min(val[y],z+2);
	}
	for(i=0;i<=n-1;i++)
	val[i]=min(val[i],val[(i+n-1)%n]+2);
	for(i=0;i<=n-1;i++)
	val[i]=min(val[i],val[(i+n-1)%n]+2);
	for(i=0;i<=n-1;i++)
	e[q+i+1]=(edge){i,(i+1)%n,val[i]};
	sort(e+1,e+q+n+1,cmp);
	for(i=1;i<=q+n;i++)
	{
		x=find(e[i].x);y=find(e[i].y);
		if(x==y)
		continue;
		fa[x]=y;ans+=e[i].z;cnt++;
		if(cnt==n-1)
		break;
	}
	printf("%lld",ans);
	return 0;
}
```

---

## 作者：Merge_all (赞：0)

# Solution
这道题一眼过去，显然的 MST，但注意到边过多，所以要考虑优化建图。

首先想到的便是确定边最多的个数，由于每次操作都会向某方向进行移动，因此最多的边数就是 $2n$ 条（如果继续走就一定连通）。那么对于 $m$ 次操作的总边数就有 $2nm$ 条边，但至少也不会变成无限加边了。

![](https://cdn.luogu.com.cn/upload/image_hosting/jv8x28eu.png)

从上方这张图（图中的 $A_1$ 表示 $A + 1$ 这个点，$B$ 同理）便可以发现：当考虑到一组边 $(A + 1, B + 1, C + 1)$，由于我们按照 kruskal 的贪心思想，则 $A$ 和 $B$ 两点一定已经连通。既然如此，我们便可以将 $(A + 1, B + 1, C + 1)$ 这组边转换成 $(A, A + 1, C + 1)$，这样答案所要维护的连通性也没有被破坏。

同理，上面这张图一定可以转换为一条从 $A$ 连到 $A + 1$、$A + 2$、$A + 3$ 直到连回自己的环，然后 $A$ 链接了另一个环 $B$。

这样一看，$A$ 环上的数为公差为 $2$，首项是 $C + 1$ 的等差数列；$B$ 环上的数为贡献为 $2$，首项是 $C + 2$ 的等差数列。

因此接下来的做法就很愉快了，直接连边和 kruskal 即可。
# Code
```
#include <bits/stdc++.h>
using namespace std;
using LL = long long;
using ULL = unsigned long long;
using pii = pair<int, int>;
using AR3 = array<int, 3>;
constexpr int N = 2e5 + 5;
int n, q, len, val[N], cnt, fa[N];
AR3 ev[N << 1];
LL ans;
int fd (int x) {return x == fa[x] ? x : fa[x] = fd (fa[x]);}

int main () {
	ios_base :: sync_with_stdio (false);
	*cin.tie (nullptr) << fixed << setprecision (20);
	
	cin >> n >> q, len = q;
    memset (val, 0x7f, sizeof val);
	for (int i = 1, u, v, w; i <= q; i ++) {
		cin >> u >> v >> w, ev[i][0] = u, ev[i][1] = v, ev[i][2] = w;
		val[u] = min (val[u], w + 1), val[v] = min (val[v], w + 2);
	}
	for (int i = 0; i < n; i ++) val[(i + 1) % n] = min (val[(i + 1) % n], val[i] + 2);
	for (int i = 0; i < n; i ++) val[(i + 1) % n] = min (val[(i + 1) % n], val[i] + 2);
	for (int i = 0; i < n; i ++) ev[++ len][0] = i, ev[len][1] = (i + 1) % n, ev[len][2] = val[i];
	sort (ev + 1, ev + len + 1, [] (auto x, auto y) {return x[2] < y[2];});
	iota (fa + 1, fa + n + 1, 1);
    // for (int i = 1; i <= len; i ++) cout << ev[i][0] << ' ' << ev[i][1] << ' ' << ev[i][2] << '\n';
	for (int i = 1, fx, fy; i <= len; i ++) {
		fx = fd (ev[i][0]), fy = fd (ev[i][1]);
		if (fx != fy) cnt ++, ans += ev[i][2], fa[fx] = fy;
		if (cnt == n - 1) break;
	}
	cout << ans << '\n';
	return 0;
}
```

---

## 作者：lovely_qiqi (赞：0)

## 思路

首先考虑暴力的 MST。发现 kruscal 做的话是 $O(M \log{M})$ 的。此时不加优化考虑所有边 $M=2mn$ 显然超时，但我们又没有其他好的优化手段，所以考虑**优化建边**。

![](https://cdn.luogu.com.cn/upload/image_hosting/j5a816n8.png)

如上图，首先发现 $c$ 是最小的，合并 $a$ 和 $b$。那么按照 kruscal 的做法 $a$ 和 $b$ 在合并之后可以看做一个点，说明把 $a+1$ 连到 $a$ 或 $b$ 是**等价**的，那么我们考虑都试图连到相邻的点来将原图变成一个环。所以把 $a+1$ 连到 $a$，同理现在 $a$，$b$，$a+1$ 是一个等价的点。于是把 $b+1$ 连到 $b$ 上。

由局部推到整体，我们有：

![](https://cdn.luogu.com.cn/upload/image_hosting/zacig3h9.png)

那么对于每一个操作，我们就发现在图中的等价于一条从 $a$ 到 $b$，权值是 $c$ 的边和从 $a$ 开始和从 $b$ 开始公差为 $2$ 的环。

此时我们只需要求出对于每一个 $i$ 和 $i+1$ 之间的最短的距离就可以了。递推地维护，先记录从每个点开始和下一个点之间最小的权值，然后挨着更新。**因为是环所以要跑两次**。

## 代码

```cpp
#include<bits/stdc++.h>
#define int long long 
using namespace std;
struct node{
	int u,v,w;
}a[500010],b[500010];
int n,q,rx,ry,cnt,ans,len,uu,vv,ww,fa[500010],cost[500010];
int find(int x){
	if(fa[x]==x) return x;
	return fa[x]=find(fa[x]);
}
bool cmp(node t1,node t2){
	return t1.w<t2.w;
}
signed main(){
	cin.tie(0);
	cout.tie(0);
	ios::sync_with_stdio(false);
	cin>>n>>q;
	for(int i=0;i<n;i++){
		fa[i]=i;
		cost[i]=1e15;
	}	
	for(int i=1;i<=q;i++){
		cin>>a[i].u>>a[i].v>>a[i].w;
		cost[a[i].u]=min(cost[a[i].u],a[i].w+1);
		cost[a[i].v]=min(cost[a[i].v],a[i].w+2);
	}
	len=q;
	for(int i=0;i<n;i++) cost[(i+1)%n]=min(cost[(i+1)%n],cost[i]+2);
	for(int i=0;i<n;i++) cost[(i+1)%n]=min(cost[(i+1)%n],cost[i]+2);
	for(int i=0;i<n;i++){
		len++;
		a[len].u=i;a[len].v=(i+1)%n;a[len].w=cost[i];
	}
	sort(a+1,a+1+len,cmp);
	for(int i=1;i<=len;i++){
		rx=find(a[i].u);
		ry=find(a[i].v);
		if(rx==ry) continue;
		ans+=a[i].w;
		fa[rx]=ry;
		cnt++;
		if(cnt==n-1) break;
	}
	cout<<ans;
	return 0;
}
```

---

## 作者：cwfxlh (赞：0)

# [AT_codefestival_2016_final_g](https://www.luogu.com.cn/problem/AT_codefestival_2016_final_g)      

非常神奇的思路！          

考虑克鲁斯卡尔算法。因为边是按边权从小往大加入，不连通就连上，所以在考虑 $(A_i+1,B_i)$ 的时候，$A_i$ 与 $B_i$ 已经连通了。于是这条边与 $(A_i+1,A_i)$ 等价！        

除了最开始那条边，其他的边都可以这样转化为环上的边，打上标记后从前往后跑一下，求出环上每段的最值，总共 $O(n+m)$ 条边，跑克鲁斯卡尔即可。           

代码：        


```cpp
#include<bits/stdc++.h>
#define int long long
using namespace std;
vector<int>lst[500003];
struct Edge{
	int st;
	int ed;
	int val;
}E[1000003];
int totE,bcj[500003];
int finf(int now){if(bcj[now]!=now)bcj[now]=finf(bcj[now]);return bcj[now];}
bool comp(Edge X,Edge Y){return X.val<Y.val;}
int n,q,k1,k2,k3,k4,k5,k6,k7,k8,k9,mxv,ans;
void add(int X,int Y){
	lst[X].emplace_back(Y);
	lst[0].emplace_back(Y+(n-X)*2);
	return;
}
signed main(){
	ios::sync_with_stdio(false);
	cin>>n>>q;
	while(q--){
		cin>>k1>>k2>>k3;
		E[++totE].st=k1;
		E[totE].ed=k2;
		E[totE].val=k3;
		add(k1,k3+1);
		add(k2,k3+2);
	}
	mxv=1000000000000ll;
	for(int i=0;i<n;i++){
		for(auto j:lst[i])mxv=min(mxv,j-i*2);
		if(mxv==1000000000000ll)continue;
		E[++totE].st=i;
		E[totE].ed=((i+1)%n);
		E[totE].val=i*2+mxv;
	}
	sort(E+1,E+totE+1,comp);
	for(int i=0;i<n;i++)bcj[i]=i;
	for(int i=1;i<=totE;i++){
		if(finf(E[i].st)==finf(E[i].ed))continue;
		ans+=E[i].val;
		bcj[finf(E[i].st)]=finf(E[i].ed);
	}
	k1=0;
	for(int i=0;i<n;i++)if(finf(i)==i)k1++;
	if(k1>1)cout<<-1;
	else cout<<ans;
	return 0;
}
```

---

