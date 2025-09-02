# Petya and Graph

## 题目描述

Petya 有一个简单图（即没有自环和重边的图），该图包含 $n$ 个顶点和 $m$ 条边。

第 $i$ 个顶点的权值为 $a_i$。

第 $i$ 条边的权值为 $w_i$。

一个子图是指图中某些顶点的集合以及某些边的集合。边的集合必须满足：集合中的每一条边的两个端点都属于所选的顶点集合。

子图的权值定义为其所有边的权值之和减去其所有顶点的权值之和。你需要求出给定图的子图的最大权值。保证图中没有自环和重边。

## 说明/提示

在第一个测试样例中，最优子图包含顶点 ${1, 3, 4}$，其权值为 $4 + 4 + 5 - (1 + 2 + 2) = 8$。在第二个测试样例中，最优子图为空。

由 ChatGPT 4.1 翻译

## 样例 #1

### 输入

```
4 5
1 5 2 2
1 3 4
1 4 4
3 4 5
3 2 2
4 2 2
```

### 输出

```
8
```

## 样例 #2

### 输入

```
3 3
9 7 8
1 2 1
2 3 2
1 3 3
```

### 输出

```
0
```

# 题解

## 作者：SfumatoCannon_ (赞：23)

题解区的一些大佬解释的有点难以理解，我来发表一下比较通俗易懂的另一种思路。

### 一、题意解释

从给定的图中选出一个子图，使得该子图中所有边的权值和减去所有点的权值和**最大**。

### 二、为什么是最小割？

大家都说这种题要用最小割——但是为什么呢？

我们要知道，对于任何一道（看起来不像是最小割的）题，它能用最小割算法来解决，有两个显著的特征：

* 每个```物体```**只有两种状态**，要么选，要么不选；

* **给定所有**```物体```**被选择的状态，则问题能够得到唯一的答案。**

（注：并不是说满足以上条件的都能用最小割求解，只是说发现以上两个性质时，思路可以往最小割靠拢一点）

我们知道，根据题意，图中所有的点要么被选择，要么没被选择，只有两种可能的状态，所以```条件(1)```是满足的；那么```条件(2)```呢？我们知道所有点的选择状态，就能推断出问题的答案吗？

答案是肯定的！因为你会发现，**知道了点的选择状态，也就知道了边的选择状态。**

这是因为，所有边的权值都是大于 $0$ 的。所以，对于任何一条边，如果它连接的点都被选中了，那么把它选上，一定会对答案产生贡献。

既然```条件(1)```和```条件(2)```都能满足，那么我们就可以尝试一下，从最小割这条路径来解题。

### 三、如何解决？

#### 第一步：理清逻辑关系（贡献/损失）

我们将问题转化成```如果...，则能对答案产生...的贡献/损失```的形式。

注意：理清逻辑关系的时候，首先，主语必须是你之前选定的那种```物体```（在这道题目中，它是图中的点）；其次，一定要**概括全面**！如果不能同时满足以上两点，那么这道题就几乎无法进行最小割（或你选择的这种```物体```无法进行最小割）

我们来理一下这道题的逻辑：

* 如果选择了一个点 $i$ ，则对答案产生 $a_i$ 的损失。

* 如果两个点 $u_i$ 和 $v_i$ 同时被选择，则对答案产生 $w_i$ 的贡献。

* 求最大贡献。

不难发现，以上就是这道题的全部内容了。

#### 第二步：将损失转化为贡献，将最大值转化为最小值

只要第一步进行成功，这道题就完成了一半了。不过题目要求的是最大值，而最小割是用来求最小值的。所以我们要转化问题，**将贡献最大转化成损失最小**。

为了求最小损失，我们先要**假设贡献达到了最大值**，也就是说，先假设所有点都没有选，而所有的边都被选择（虽然这种情况是不存在的），此时不难看出，$ans=\sum\limits_{i=1}^mw_i.$

接着就可以把把这道题的逻辑转换成：

* 如果选择了一个点 $i$ ，则对答案产生 $a_i$ 的损失。

* 如果**没有同时选择** $u_i$ 和 $v_i$ ，则对答案产生 $w_i$ 的损失。

* 求最小损失。

求出来最小损失之后，再把之前求得的极端情况下的最大值减去求出来的最小损失即可。

#### 第三步：根据逻辑关系建图，求最小割（最大流）

根据网络流套路，我们先设置一个源点 $s$ 和一个汇点 $t.$

对于一个点 $i$ ，若 $i\in s$ ，则代表节点 $i$ 被选择，否则（即当 $i\in t$ 时）则代表节点 $i$ 没被选择。

接下来我们看：

```如果选择了一个点 i ，则对答案产生 a_i 的损失。```


这个很好建图，直接从 $i$ 向 $t$ 连一条权值为 $a_i$ 的边即可，这样子，当 $i\in s$ 的时候，就必须要把这条边割掉。

难点在这里：

```如果没有同时选择 u_i 和 v_i ，则对答案产生 w_i 的损失。```

要做到这一点，还需要再创建一个额外的节点 $p$ ，然后 $s\to p$ 连一条边， $p\to u_i$ 连一条边， $p\to v_i$ 连一条边，这三条边的权值都是 $w_i$.

画画图模拟一下，你会发现确实可以实现。

到这里图就建好了，我们求一遍最小割（最大流）即可。

别忘了最后要拿理想情况去减哦

***

### Code

```cpp
#include <cstdio>
#include <queue>
#include <cstring>
using namespace std;
#define MAXN 500000
#define MAXM 500000
#define INF 0x7fffffff
struct Edge
{
    long long next, to, dis;
} bian[MAXM];
long long h[MAXN], used[MAXN], dep[MAXN];
long long s, t;
long long temp = 1;
void add(long long from, long long to, long long dis)
{
    temp++;
    bian[temp].dis = dis;
    bian[temp].next = h[from];
    bian[temp].to = to;
    h[from] = temp;
}
void addE(long long from, long long to, long long dis)
{
    add(from, to, dis);
    add(to, from, 0);
}
bool bfs()
{
    long long x, i;
    queue<long long> Q;
    Q.push(s);
    memset(dep, 0, sizeof(dep));
    dep[s] = 1;
    while (!Q.empty())
    {
        x = Q.front();
        Q.pop();
        for (i = h[x]; i; i = bian[i].next)
            if (bian[i].dis != 0 && dep[bian[i].to] == 0)
            {
                dep[bian[i].to] = dep[x] + 1;
                Q.push(bian[i].to);
            }
    }
    return dep[t] != 0;
}
long long dfs(long long x, long long in)
{
    long long out = 0, i, k;
    if (x == t)
        return in;
    for (i = used[x]; i && in != 0; i = bian[i].next, used[x] = i)
    {
        if (bian[i].dis != 0 && dep[bian[i].to] == dep[x] + 1)
        {
            k = dfs(bian[i].to, min(bian[i].dis, in));
            bian[i].dis -= k;
            bian[i ^ 1].dis += k;
            in -= k;
            out += k;
        }
    }
    if (out == 0)
        dep[x] = 0;
    return out;
}
long long getId(long long depth, long long x)
{
    return (depth - 1) * 5000 + x;
}
long long n, m;
int main()
{
    scanf("%lld%lld", &n, &m);
    long long i, j;
    long long x, y, z;
    long long tot = 0;
    s = MAXN - 1;
    t = MAXN - 2;
    for (i = 1; i <= n; i++)
    {
        scanf("%lld", &x);
        addE(getId(1, i), t, x);
    }
    for (i = 1; i <= m; i++)
    {
        scanf("%lld%lld%lld", &x, &y, &z);
        addE(s, getId(2, i), z);
        addE(getId(2, i), getId(1, x), z);
        addE(getId(2, i), getId(1, y), z);
        tot += z;
    }
    long long ans = 0;
    while (bfs())
    {
        memcpy(used, h, sizeof(h));
        ans += dfs(s, INF);
    }
    printf("%lld", tot - ans);
    return 0;
}
```


---

## 作者：Sooke (赞：9)

### 题意

定义图权 $=$ 图中边权总和 $-$ 图中点权总和（空图的图权 $= 0$），求 $n$ 个点 $m$ 条边的无向图最大权子图。

---

### 解题思路

本题同 [P4174](https://www.luogu.org/problemnew/show/P4174)。~~（别问我为什么，我也不知道为什么 $CF$ 弄出个 $NOI$ 原题出来，建议爆破）~~

最大权闭合子图模板题。

闭合子图，满足子图中的点的**入度**等于原图中对应的点。说白了，要选一个东西，必须把其依赖的东西全部先选上。

常见应用是有一类物品，有代价选择，但把指定的一组物品全选了会产生收益。

考虑用配合网络流的最小割 $=$ 最大流解决，把问题放在二分图上，连边如下：

> **源点**（$S$）往 **有代价物品**（$A$）连其代价。

> **有代价物品**（$A$）往选了它可能产生收益的**组**（$B$）连 $\infty$。

> **每个组**（$B$）往 **汇点**（$T$）连其收益。

先把全部收益加在一起，最后减去最大流（最小割），即为答案。

感性理解，如果某个组在代价处就已经割断了，通过最小割，我们增加了代价，但保住了收益，如果割掉收益，说明这个组的收益不优，宁愿不要它，于是抵消了收益，但没有代价。

---

回来看这道题，其实本质一模一样。

每条边 $=$ 一个组，收益 $=$ 边权，而组需要的物品 $=$ 点，代价 $=$ 点权。能看出来，交给模板就行啦。

---

### 代码实现

要开 $long\ long$！~~（当时直接粘模板 $WA$ 了两发）~~

```cpp
#include <cstdio>
#include <cstring>
#include <algorithm>

inline int read() {
    char c = getchar(); int n = 0; bool f = false;
    while (c < '0' || c > '9') { if (c == '-') { f = true; } c = getchar(); }
    while (c >= '0' && c <= '9') { n = (n << 1) + (n << 3) + (c & 15); c = getchar(); }
    return f ? -n : n;
}

const int maxN = 5005, maxE = 100005;

int n, m, s, t, dis[maxN], q[maxN];
long long ans;
bool vis[maxN];

struct List {
    int len, fst[maxN], nxt[maxE], v[maxE], w[maxE], fl[maxE];
    
    List() { memset(fst, -1, sizeof(fst)); }
    inline void insert(int u, int vv, int ww) { v[len] = vv, w[len] = ww, nxt[len] = fst[u], fst[u] = len++; }
    inline void connect(int u, int vv, int ww) { insert(u, vv, ww), insert(vv, u, 0); }
} ls;

bool bfs() {
    memset(dis, 0, sizeof(dis)); dis[q[1] = s] = 1;
    for (int l = 1, r = 1; l <= r; l++) {
        int u = q[l];
        for (int i = ls.fst[u]; ~i; i = ls.nxt[i]) {
            int v = ls.v[i], w = ls.w[i], fl = ls.fl[i];
            if (!dis[v] && fl < w) {
                dis[v] = dis[u] + 1;
                if (v == t) { return true; }
                q[++r] = v;
            }
        }
    }
    return false;
}
long long dinic(int u, long long f) {
    if (u == t) { return f; }
    long long lef = f;
    vis[u] = true;
    for (int i = ls.fst[u]; ~i; i = ls.nxt[i]) {
        int v = ls.v[i], w = ls.w[i], fl = ls.fl[i];
        if (dis[v] == dis[u] + 1 && fl < w && !vis[v]) {
            long long df = dinic(v, std::min(lef, (long long) w - fl));
            if (!df) { dis[v] = 0; continue; }
            lef -= df; ls.fl[i] += df; ls.fl[i ^ 1] -= df;
            if (!lef) { break; }
        }
    }
    vis[u] = false;
    return f - lef;
}

int main() {
    n = read(); m = read(); s = 0; t = n + m + 1;
    for (int i = 1; i <= n; i++) { ls.connect(s, i, read()); } // 源点 到 第一层 连 代价.
    for (int i = 1; i <= m; i++) {
        int u = read(), v = read(), w = read(); ans += w;
        ls.connect(u, n + i, 1e9); ls.connect(v, n + i, 1e9); // 第一层 到 第二层 连 inf.
        ls.connect(n + i, t, w); // 第二层 到 汇点 连 收益.
    }
    while (bfs()) { ans -= dinic(s, 1e18); }
    printf("%I64d\n", ans);
    return 0;
}
```

---

## 作者：_Fontainebleau_ (赞：4)

###  题意
- 给定一个 $n$ 点 $m$ 边无向图。点 $i$ 的点权为 $a_i$，边 $i$ 的边权为 $b_i$。
- 定义图权为图中边权和 $-$ 图中点权和，空图图权为 $0$。求该图的最大权子图。
- $1\le{n,m}\le10^3,1\le{a_i,b_i}\le{10^9}$。

### 做法

本题就是 [P4174](https://www.luogu.com.cn/problem/P4174)，是 **最大权闭合子图** 的模板题。

首先什么是闭合子图？

闭合子图指的是子图中的点的入度均与原图一样的子图。通俗而言就是，如果要选一个东西，必须把其所有依赖的东西都选上。

常见应用情景就是 [P4174](https://www.luogu.com.cn/problem/P4174) 这题。

怎么做呢？

- 建超级源点 $S$ 和超级汇点 $T$。
- $S$ 与需要代价的物品 $x_i$ 连权值为代价（是正的）的边，并将该物品的点权设为代价（是负的）。
- $x_i$ 与部分依赖于 $x_i$ 的那些收益  $y_i$ 连权值为无穷大的边，并将该收益的点权设为收益。
- $y_i$ 再与 $T$ 连权值为收益的边。
- 答案为，所有收益的和 $-$ 最小割。

为什么呢？我们看一张图就会了然。

![](https://cdn.luogu.com.cn/upload/image_hosting/j8yi1nv2.png)

显然，根据上面的过程，中间的边权值为 $\infty$，所以 **一定不会割中间的边**，一定是割连着 $S$ 或 $T$ 的边。而原图则被割成了分别与 $S$ 和 $T$ 相连的 $\color{Orchid}\text{Orchid}$ 和 $\color{yellow}\text{Yellow}$ 两部分。我们用 $W$ 表示收益，即 $\color{yellow}\text{Yellow}$ 中的点权和。设 $w_+$ 为 $\color{yellow}\text{Yellow}$ 中的正的点权和，$w_-$ 为 $\color{yellow}\text{Yellow}$ 中负的点权和，$W=w_++w_-$。设割中与 $S$ 相连的边权和为 $c_S$，与 $T$ 相连的为 $c_T$。则割 $C$ 为 $c_S+c_T$。**注意到 $\bm{c_S=-w_-}$**，所以 $W+C=w_++w_-+c_S+c_T=w_++c_T$，而 $w_++c_T$ 又恰好是所有收益的和，即图中所有正点权 $Sum$ 的和。所以 $W=Sum-C$，**正点权的和一定，割越小，收益越大**，所以我们要求的就是 **最小割**。

### 代码

```cpp
#include<bits/stdc++.h>
#define int long long
using namespace std;
const long long inf=2000000000000;
int n,m,T,S,cnt=1;
long long sum,maxflow,val[400005];
int h[60004],nxt[400005],t[400005];
int dep[60004],gap[60004],q[1001001],f,e;
int cur[60004];
inline void addedge(int a,int b,int c){t[++cnt]=b,val[cnt]=c,nxt[cnt]=h[a],h[a]=cnt;}
inline int read()
{
	int x=0,f=1;char c=getchar();
	while(c<'0'||c>'9'){if(c=='-')f=-f;c=getchar();}
	while(c>='0'&&c<='9'){x=x*10+c-'0';c=getchar();}
	return x*f;
}
inline void bfs()
{
	memset(dep,-1,sizeof(dep));
	memset(gap,0,sizeof(gap));
	dep[T]=0,gap[0]=1;
	f=e=1,q[1]=T;
	while(f<=e)
	{
		int u=q[f++];
		for(int p=h[u];p;p=nxt[p])
		{
			int v=t[p];
			if(dep[v]!=-1)	continue;
			q[++e]=v;
			dep[v]=dep[u]+1;
			gap[dep[v]]++;
		}
	}
	return ;
}
long long dfs(int u,long long flow)
{
	if(u==T)
	{
		maxflow+=flow;
		return flow;
	}
	int used=0;
	for(int p=cur[u];p;p=nxt[p])
	{
		cur[u]=p;
		int v=t[p];
		if(val[p]&&dep[v]+1==dep[u])
		{
			long long mi=dfs(v,min(flow-used,val[p]));
			if(mi)
			{
				val[p]-=mi;
				val[p^1]+=mi;
				used+=mi;
			}
			if(used==flow)	return used;
		} 
	}
	if(--gap[dep[u]]==0)	dep[S]=T+1;
	dep[u]++;
	gap[dep[u]]++;
	return used;
}
inline long long ISAP()
{
	maxflow=0;
	bfs();
	while(dep[S]<T)	memcpy(cur,h,sizeof(h)),dfs(S,inf);
	return maxflow;
}
signed main()
{
	n=read(),m=read();T=m+n+1,S=0;
	for(int i=1;i<=n;i++){int x=read();addedge(S,i,x),addedge(i,S,0);}
	for(int i=1;i<=m;i++)
	{
		int u=read(),v=read(),w=read();
		addedge(n+i,T,w),addedge(T,n+i,0),sum+=w;
		addedge(u,n+i,inf),addedge(n+i,u,0);
		addedge(v,n+i,inf),addedge(n+i,v,0);
	}
	printf("%lld\n",sum-ISAP());
	return 0;
}

```



---

## 作者：Z1qqurat (赞：2)

最大权闭合图板子题。

考虑这样一个问题：现在有 $n$ 个物品，每个物品有权值 $w_i$，权值可正可负。然后有 $m$ 条限制，就是类似于“选了物品 $u$ 就必须选择物品 $v$”之类的。现在要求你选择一些物品，并最大化总权值。

考虑没有限制啊怎么做。那就直接选择所有正权物品。所以发现限制只有在正权物品绑定了一个负权物品的时候会被选择。我们考虑如果有限制 $(u, v), w_u > 0, w_v < 0$，而且目前选择了物品 $u$，我们可以怎么做：

* 可以选择抛弃物品 $u$，损失 $w_u$ 的权值。
* 或者选择 $v$，损失 $|w_v|$ 的权值。

相当于我们要最小化这个损失的权值，而对于每个这样的限制我们都要这么做，二选一。这很最小割啊。

我们考虑这样一种建模：源点 $s$ 向所有正权物品 $u$ 连边，边权为 $w_u$，割这里表示抛弃物品 $u$；所有负权物品 $v$ 向汇点 $t$ 连边，边权为 $-w_v$，割这里表示为了选 $u$ 而选上 $v$；所有限制 $(u, v)$ 就 $u$ 向 $v$ 连边权为 $\infty$ 的边，所以肯定不会割这里。那么对全图跑一遍最小割得到的就是最小的损失权值，前提是选了所有正权物品的前提下。所以答案就是正权物品总权值减去最小割。

那这个题怎么做？把点，边都当作物品，其中边是正权的，点是负权的，限制就是选了边 $(u, v)$ 那么点 $u, v$ 都得选，连就是了。

```cpp
#include <bits/stdc++.h>
#define ll long long
using namespace std;
const int N = 4e5 + 5;
const ll inf = 2e18;
int n, m, s, t, tot = 1, head[N], to[N], nxt[N];
ll limit[N], ans;

void addedge(int u, int v, ll w) {
    to[++tot] = v, limit[tot] = w, nxt[tot] = head[u], head[u] = tot;
    to[++tot] = u, limit[tot] = 0, nxt[tot] = head[v], head[v] = tot;
    return ;
}

namespace Dinic{
    int cur[N], s, t, dis[N];
    queue <int> q;
    ll Augmenting(int u, ll rest) {
        if(u == t) return rest;
        ll ret = 0;
        for (int i = cur[u]; i && rest; i = nxt[i]) {
            cur[u] = i;
            int v = to[i]; ll c = min(rest, limit[i]);
            if(dis[v] == dis[u] + 1 && c) {
                ll f = Augmenting(v, c);
                rest -= f, ret += f;
                limit[i] -= f, limit[i ^ 1] += f;
            }
        }
        if(!ret) dis[u] = -1;
        return ret;
    }
    ll MaxFlow(int ss, int tt) {
        ll maxflow = 0; s = ss, t = tt;
        while(1) {
            while(!q.empty()) q.pop();
            memset(dis, -1, sizeof(dis));
            memcpy(cur, head, sizeof(head));
            dis[s] = 0, q.emplace(s);
            bool bl = 0;
            while(!q.empty()) {
                if(bl) break;
                int u = q.front(); q.pop();
                for (int i = head[u]; i; i = nxt[i]) {
                    int v = to[i], c = limit[i];
                    if(dis[v] == -1 && c) {
                        dis[v] = dis[u] + 1;
                        if(v == t) { bl = 1; break;}
                        q.emplace(v);
                    }
                }
            }
            if(dis[t] == -1) return maxflow;
            maxflow += Augmenting(s, 2e15);
        }
    }
}

int main() {
    ios::sync_with_stdio(0), cin.tie(0), cout.tie(0);
    cin >> n >> m; s = n + m + 1, t = s + 1;
    for (int i = 1, p; i <= n; ++i) {
        cin >> p; addedge(i, t, p);
    }
    for (int i = 1, a, b, c; i <= m; ++i) {
        cin >> a >> b >> c; ans += c, addedge(s, n + i, c);
        addedge(n + i, a, inf), addedge(n + i, b, inf);
    }
    cout << ans - Dinic::MaxFlow(s, t) << "\n";
    return 0;
}
```



---

## 作者：CmsMartin (赞：2)

## 题目描述

[题目传送门](codeforces.com/problemset/problem/1082/G)

## 思路

这道题和 [[NOI2006] 最大获利](https://www.luogu.com.cn/problem/P4174) 是一模一样的，做完记得去拿双倍经验。

这道题是一个经典的网络流模型：**最大权闭合子图**。

先说做法：

1. 新建原点 $s$ 与汇点 $t$；

2. 将 $s$ 与图中每一个正权点相连，权值为该正权点点权；

3. 将 $t$ 与图中每一个负权点相连，权值为该负权点点权的绝对值；

4. 根据输入连边，边权为 $\infty$。

最后，答案为正权点和 - 最大流。

下面给出证明：

设集合 $S$ 和集合 $T$ 是原图的 $s-t$ 割。

记 $w$ 为当前的收益 ， $Cnt$ 为当前的割。

则 $w = S_\text{正权和} - |S_\text{负权和}|$。

显然 $Cut = \text{正权和} - S_\text{正权和} + |S_\text{负权和}|$。

加起来就有：$w + Cut = \text{正权和}$。

移项得：$w = \text{正权和} - Cut$。

显然当 $Cut$ 取最小值（即最小割）时 $w$ 取最大值。

由最大流最小割定理得：$w = \text{正权和} - \text{最大流}$。

证必。

## 代码

```cpp
#include <bits/stdc++.h>
using namespace std;

#define int long long

const int MAXN = 50010 , MAXM = 500010 , INF = 1 << 30;

int N , M;

int Head[MAXN * 4];
int Cnt = 1;
struct Edge {
    int Next , To;
    int Val;
} G[MAXM * 15];

void _add(int u , int v , int w) {
    G[++Cnt].To = v;
    G[Cnt].Val = w;
    G[Cnt].Next = Head[u];
    Head[u] = Cnt;
}

void Add(int a , int b , int c) {
    _add(a , b , c);
    _add(b , a , 0);
}

int Dep[MAXN * 4];
int Hash[MAXN * 4];

int S , T;
int Max_Flow;

void Bfs() {
    memset(Dep , -1 , sizeof Dep);
    memset(Hash , 0 , sizeof Hash);
    queue<int> q;
    q.push(T);
    Dep[T] = 0;
    while(!q.empty()) {
        int u = q.front();
        q.pop();
        for(int i = Head[u]; i; i = G[i].Next) {
            int v = G[i].To;
            if(Dep[v] != -1) continue;
            q.push(v);
            Dep[v] = Dep[u] + 1;
            Hash[Dep[v]]++;
        }
    }
}

int Dfs(int u , int flow) {
    if(u == T) {
        Max_Flow += flow;
        return flow;
    }
    int used = 0;
    for(int i = Head[u]; i; i = G[i].Next) {
        int v = G[i].To;
        if(G[i].Val && Dep[v] + 1 == Dep[u]) {
            int Min = Dfs(v , min(flow - used , G[i].Val));
            if(Min) {
                G[i].Val -= Min;
                G[i ^ 1].Val += Min;
                used += Min;
            }
            if(used == flow) {
                return used;
            }
        }
    }
    Hash[Dep[u]]--;
    if(Hash[Dep[u]] == 0) Dep[S] = N + M + 10;
    Dep[u]++;
    Hash[Dep[u]]++;
    return used;
}

int ISAP() {
    Max_Flow = 0;
    Bfs();
    while(Dep[S] < N + M + 10) Dfs(S , INF);
    return Max_Flow;
}

int Sum;

signed main() {
    scanf("%lld%lld" ,&N ,&M);

    S = 0;
    T = N + M + 1;

    for(int i = 1 , k; i <= N; i++) {
        scanf("%lld" ,&k);
        Add(i + M , T , k);
    }

    for(int i = 1 , u , v , w; i <= M; i++) {
        scanf("%lld%lld%lld" ,&u ,&v ,&w);
        Sum += w;
        Add(S , i , w);
        Add(i , M + u , INF);
        Add(i , M + v , INF);
    }

    printf("%lld\n" ,Sum - ISAP());

    return 0;
}
```

---

## 作者：Mirasycle (赞：1)

数据范围小的匹配/选择类问题考虑网络流。匹配类的套路就是把不同类的放两边跑网络流，这题就是直接把边和点各放一边跑最小割，下面是说明。

我们可以先把边权都加上也就是 $\sum w_i$，然后就是选点了，我们每选一个点会使得答案减少 $a_i$，如果一条边的两个端点没有被同时选同样会使得答案减少 $w_i$。

考虑最小割，我们从源点 $s$ 向每条边连一条 $w_i$ 的边，从每条边向两个端点各连一条 $\infty$ 的边，同时每个点向 $t$ 连一条 $a_i$ 的边。

每个点和 $s$ 联通代表被选，和 $t$ 联通代表没有被选择了。

如果要选某点就要隔开和 $t$ 的边使得其和 $s$ 连通，也就要付出 $a_i$ 的代价割开和 $t$ 的边。选了边就必须选点，所以中间的边不可割。如果两点其一和 $t$ 联通就要用 $w_i$ 的代价和 $s$ 断开，完美符合题目要求。

![建图](https://cdn.luogu.com.cn/upload/image_hosting/xfe9imhm.png)


```cpp
#include<bits/stdc++.h>
using namespace std;
typedef long long ll;
const int maxn=2e3+10;
const int maxm=1e4+10;
const ll inf=1e15;
const ll INF=1e18;
struct edge{
	int from,to,Next; ll flow;
}edges[maxm<<1];
int head[maxn],a[maxn]; queue<int> q;
struct Dinic{
	int d[maxn],now[maxn],tot,n,s,t;
	bool vis[maxn]; ll a[maxn];
	void init(int n){
		this->n=n; tot=1;
		memset(head,0,sizeof(head));
	}
	void add_edge(int u,int v,ll w){
		edges[++tot]=(edge){u,v,head[u],w}; head[u]=tot;
		edges[++tot]=(edge){v,u,head[v],0}; head[v]=tot;
	}
	bool bfs(int s,int t){
		memset(d,0,sizeof(d));
		while(!q.empty()) q.pop(); 
		d[s]=1; now[s]=head[s]; q.push(s);
		while(!q.empty()){
			int u=q.front();  q.pop();
			for(int i=head[u];i;i=edges[i].Next){
				int v=edges[i].to;
				if(!edges[i].flow||d[v]) continue;
				q.push(v); now[v]=head[v]; d[v]=d[u]+1;
				if(v==t) return 1;
			}
		}
		return 0;
	}
	ll dinic(int s,int t,ll flow){
		if(s==t) return flow;
		ll rest=flow,k;
		for(int i=now[s];i&&rest;i=edges[i].Next){
		  	int v=edges[i].to; now[s]=i;
		  	if(!edges[i].flow||d[v]!=d[s]+1) continue;//注意d的条件 
			k=dinic(v,t,min(rest,edges[i].flow));
			if(!k) d[v]=0;
			edges[i].flow-=k; edges[i^1].flow+=k; rest-=k;
		}
		return flow-rest;
	}
}DC;
ll solve(int s,int t){
	ll maxflow=0,flow=0;
	while(DC.bfs(s,t))
		while(flow=DC.dinic(s,t,INF)) maxflow+=flow;
	return maxflow;
}
int main(){
	ios::sync_with_stdio(false); cin.tie(0); cout.tie(0); 
	int n,m; cin>>n>>m; DC.init(n); ll sum=0;
	for(int i=1;i<=n;i++) cin>>a[i],DC.add_edge(i,n+1,a[i]);
	for(int i=1;i<=m;i++){
		int u,v,w; cin>>u>>v>>w; sum+=w;
		DC.add_edge(n+2,n+2+i,w); 
		DC.add_edge(n+2+i,u,inf);
		DC.add_edge(n+2+i,v,inf);
	}
	cout<<sum-solve(n+2,n+1);
	return 0;
}
```

---

## 作者：Forg1weN (赞：1)

很多题解光顾着介绍最大权闭合子图是啥了，这道题的模型都没介绍，其实一句话就够了。

假设我们选中了边权产生正贡献，那么边的两端 $u\rightarrow v$ 的点权就是割的容量，最好情况下就是所有的边权正贡献全部被选中，但是这样的话就要割去点权这些边，于是，要么割掉边权，要么割掉两个点权，模型建立。

建图如下：

- 原图点 $i$ 连向 $t$，容量 $a_i$。

- 边看做一个点 $x$，连向边的两端点，容量无限大。

- 源点 $s$ 连向边 $x$ 的那个点。

复杂度为 Dinic 的复杂度，$O(V^2\times E)$。

```cpp
#include<bits/stdc++.h>
using namespace std;
#define int long long
const int INF =2147483247;
const int maxn=2e5+10;
int n,m,s,t;
int maxflow;
int d[maxn];
queue<int>q;
struct EDGE {
	int nt,v,w;
}edge[maxn*2];
int hd[maxn],now[maxn],num_edge=1;
void addedge(int u,int v,int w) {
	edge[++num_edge].nt=hd[u];
	edge[num_edge].v=v;
	edge[num_edge].w=w;
	hd[u]=num_edge;
}
bool bfs() {
	memset(d,0,sizeof(d));
	while(!q.empty())q.pop();
	q.push(s),d[s]=1,now[s]=hd[s];
	while(!q.empty()) {
		int x=q.front();
		q.pop();
		for(int i=hd[x];i;i=edge[i].nt) {
			int v=edge[i].v;
			int w=edge[i].w;
			if(w&&!d[v]) {
				q.push(v);
				now[v]=hd[v];
				d[v]=d[x]+1;
				if(v==t)return 1; 
			}
		}
	}
	return 0;
}
int dinic(int x,int flow) {
	if(x==t)return flow;
	int rest=flow,k;
	for(int i=now[x];i&&rest;i=edge[i].nt) {
		now[x]=i;
		int v=edge[i].v;
		int w=edge[i].w;
		if(w&&d[v]==d[x]+1) {
			k=dinic(v,min(rest,w));
			if(!k)d[v]=0;
			edge[i].w-=k;
			edge[i^1].w+=k;
			rest-=k;
		}
	}
	return flow-rest;
}
void Add(int u,int v,int w) {
	addedge(u,v,w),addedge(v,u,0);
}
int sum;
int a[maxn];
signed main() {
	scanf("%lld%lld",&n,&m);
	s=n+m+1,t=s+1;
	for(int i=1,x;i<=n;i++) {
		scanf("%lld",&x);
		Add(i,t,x);
	}
	for(int i=1;i<=m;i++) {
		int a,b,w;
		scanf("%lld%lld%lld",&a,&b,&w);
		sum+=w;
		Add(i+n,a,INF);
		Add(i+n,b,INF);
		Add(s ,i+n, w);
	}
	int flow=0;
	while(bfs())
		while(flow=dinic(s,INF))
			maxflow+=flow;
	printf("%lld",sum-maxflow);
	return 0;
}
```

---

## 作者：UperFicial (赞：1)

[传送门](https://www.luogu.com.cn/problem/CF1082G)。

同步发表于我的 [$\text{cnblog}$](https://www.cnblogs.com/UperFicial/p/16120803.html)。

### $\texttt{Description}$

定义图权 $=$ 图中边权总和 $-$ 图中点权总和。求无向图最大权子图。

$1\le n,m\le 10^3$.

### $\texttt{Solution}$

最大权子图模型，考虑用最小割来解决。

所以说一个初步思路是选择所有边，然后

- 扣去一些边权（不选这个边）

- 扣去一些点权（选择了相应的边，但根据题意要减去点权）。

然后考虑抽象成一个二分图模型。

把边放到左边，点放到右边，进行匹配。

令第 $i$ 条边的序号为 $i+n$。

我们对于图中的第 $j$ 条边 $(u,v,w)$，假设说选了这条边，那么 $u,v$ 也都要选。

在最小割中一般用 $\infty$ 表示必须选择的关系。

则建图方式为：

- $s\to j+n$，流量为 $w$。

- $j+n\to u$，流量为 $\infty$。

- $j+n\to v$，流量为 $\infty$。

- 对于 $\forall i\in [1,n]$，连 $i\to t$ 边权为 $a_i$。

注意 $a_i\le 10^9$ 需要开 $\texttt{long long}$，并且数组不要开小。

代码就不给了，建完图就是 $\texttt{dinic}$ 的板子了。

$\texttt{AC}$ 记录：[$\texttt{Link}$](https://www.luogu.com.cn/record/73511646)。

$$\texttt{The End.by UF}$$

---

## 作者：LCuter (赞：1)

## CF1082G 题解

##### $\text{Description}$

给定一个 $n$ 点 $m$ 边无向图，边有边权 $b_i$，点有点权 $a_i$，要求选出一个点集，使得其导出子图的边权和减其点权和最大。

$1\le n,m\le 10^3$

##### $\text{Solution}$

若选择了一条边，则其两个端点也必须被选择，则问题可以转换为最大权闭合图。

考虑建立源点 $S$ 与汇点 $T$，原图中的每个点看作新图中的点，编号 $[1,n]$，原图中的每条边也看作新图中的点，编号 $[n+1,n+m]$。

对于原图中的每个点 $i$，连边 $(i,T,a_i)$。

对于原图中的每条边 $i(u,v)$，连边 $(S,n+i,b_i),(n+i,u,+\infty),(n+i,v,+\infty)$。

答案即边权和减去该流图的最小割。

首先由于原图中边与点对应的点间的边容量为 $+\infty$，故我们不会选择删这些边。

我们把删去原图中的点与汇点的边看作选择该点，那么，如果有一条原图中的边，其两端点有任意一个没有被选择（即与汇点的边没有被删除），那么源点到其在新图中对应的点的边就必须被删除，否则连通。

那么一个可行的割即为所有被选择的点的点权和，加上不在选出的点集的导出子图中的边的边权和。

用总边权和减去该割就是这个点集的权值。

为了让这个权值最大，我们需要让割最小，即最小割。

根据最大流最小割定理，我们只需跑一遍 Dinic 求出最大流。

##### $\text{Code}$

```cpp
#include<bits/stdc++.h>
#define REG register
using namespace std;
inline void read(int& x){
	REG char c;
	while(!isdigit(c=getchar()));x=c^48;
	while(isdigit(c=getchar()))x=(x*10)+(c^48);
}
typedef long long ll;
const int N=5005,M=100005;
const ll INF=0x3f3f3f3f3f3f3f3fll;

int n,m,s,t,u,v;

int Nv[N],Mv[M];

struct Edge{int v,nxt,w;}ed[M];
int head[N],cur[N],cnt=1;
inline void adde(int u,int v,int w){ed[++cnt]=(Edge){v,head[u],w},head[u]=cnt;}
inline void add(int u,int v,int w){adde(u,v,w),adde(v,u,0);}

ll Mf;

int dep[N];

queue<int> Q;

bool bfs(){
	memset(dep,0,sizeof dep);
	while(Q.size()) Q.pop();
	Q.push(s),dep[s]=1,cur[s]=head[s];
	while(Q.size()){
    	int now=Q.front();Q.pop();
    	for(REG int i=head[now];i;i=ed[i].nxt){
        	int v=ed[i].v,w=ed[i].w;
        	if((!w)||dep[v]) continue;
        	dep[v]=dep[now]+1,Q.push(v),cur[v]=head[v];
        	if(v==t) return 1;
        }
    }
	return 0;
}

ll dfs(int now,ll flow){
	if(now==t) return flow;
	ll rst=flow;
	for(REG int i=cur[now];i&&rst;i=ed[i].nxt){
    	int v=ed[i].v;
    	if(dep[v]!=dep[now]+1||!ed[i].w) continue;
    	cur[now]=i;
    	ll k=dfs(v,min(1ll*ed[i].w,rst));
    	if(!k) dep[v]=0;
    	ed[i].w-=k,ed[i^1].w+=k,rst-=k;
    }
	return flow-rst;
}

ll ans;

inline void Work(){
	read(n),read(m),s=n+m+1,t=s+1;
	for(REG int i=1;i<=n;++i) read(Nv[i]),add(i,t,Nv[i]);
	for(REG int i=1;i<=m;++i) read(u),read(v),read(Mv[i]),add(n+i,u,INF),add(n+i,v,INF),add(s,n+i,Mv[i]),ans+=Mv[i];
	while(bfs())
    	if(Mf=dfs(s,INF)) ans-=Mf;
	printf("%lld\n",ans);
}

int main(){Work();}
```



---

## 作者：JK_LOVER (赞：1)

## 题意
从图中选出一些边，使边权总和 $-$ 点权总和最小。[$QWQ$](https://www.luogu.com.cn/blog/xzc/solution-cf1082g)
## 分析
最大权闭合子图模板题了。
这个模型可以说是非常非常多了，我先抛出它的定义。

- 在一个图中，我们选取一些点构成集合，记为 $V$ ，且集合中的出边(即集合中的点的向外连出的弧)，所指向的终点(弧头)也在 $V$ 中，则我们称 $V$ 为闭合图。最大权闭合图即在所有闭合图中，集合中点的权值之和最大的 $V$ ，我们称 $V$为最大权闭合图 -- 选自网络。

- 先说一下处理方式。

- 设置超级源汇 $S,T$。

- 然后使 $S$ 和所有的正权的点连接容量为点权的边，所有点权为负的点和 $T$ 连接容量为点权绝对值的边。然后如果选择了某个 $v$ 点才可以选 $u$ 点，那么把 $u$ 向 $v$ 连接一条容量为 $inf$ 的边。

- 最大点权和 $=$ 正点权和 $-$ 最小割。

那么这道题如果选择了这一条边，那么必须选择两个端点，这不就是最大权闭合子图了吗。

## 证明
- 证明可以看网上的，我这里搬运一下

- 割边一定出现在与 $S,T$ 联接的边上，因为除开这些边，其余的边的容量都为 $inf$ 显然是不可能成为割边的。

- 我们假设跑完最小割之后的图中一共有两部分点
- $X$ 表示与 $S$ 相连的点， $Y$ 表示与 $T$ 相连的点，那么我们可以设 $X_0,Y_0$ 为负权点，$X_1,Y_1$ 为正权点。然后由于我们求了一遍最小割，根据上面简单割的证明我们发现不会割去中间 $inf$ 的边，所以我们可以求出：最小割 $=|X_0|+|Y_1|$ 

- 然后我们可以发现 $X$ 的权值和可以表示为 $Sum_X=X_1-|X_0|$ 我们把上面那个式子代入到这个式子里。 
$$Sum_X+\text{最小割}=X_1-|X_0|+|X_0|+Y_1$$ 

然后我们得出： 
$$
SumX+\text{最小割}=X1+Y1=\text{原图所有正权点权值之和}
$$
## 代码
```cpp
#include<bits/stdc++.h>
using namespace std;
#define int long long 
const int N = 31001,inf=0x3f3f3f3f3f3f3f3f;
struct Edge{int cap,flow,nxt,to;}e[N<<1];
int dis[N],head[N],cnt = 1,cur[N],n,m;
int read(){
	int x=0,f=0;char ch=getchar();
	while(!isdigit(ch)){if(ch=='-')f=1;ch=getchar();}
	while(isdigit(ch)){x=x*10+ch-'0';ch=getchar();}
	return f?-x:x;
}
void add(int x,int y,int c){
	e[++cnt].cap = c;e[cnt].flow = 0;e[cnt].to = y;e[cnt].nxt = head[x];head[x] = cnt;
	e[++cnt].cap = 0;e[cnt].flow = 0;e[cnt].to = x;e[cnt].nxt = head[y];head[y] = cnt;
}
queue<int> Q;
bool Bfs(int s,int t){
	while(Q.size()) Q.pop();memset(dis,0,sizeof(dis));
	Q.push(s);dis[s] = 1;while(Q.size()){
		int x = Q.front();Q.pop();
		for(int i = head[x];i;i=e[i].nxt){
			if(e[i].cap>e[i].flow && !dis[e[i].to]){
				dis[e[i].to] = dis[x]+1;Q.push(e[i].to);
				if(e[i].to == t) return true;
			}
		}
	}
	return false;
}
int Dfs(int x,int a,int t){
	if(x==t||a==0) return a;int flow=0,f;
	for(int i = cur[x];i;i=e[i].nxt){
		int y = e[i].to;
		if(dis[y]==dis[x]+1&&(f=Dfs(y,min(e[i].cap-e[i].flow,a),t))>0)
		{
			e[i].flow+=f;e[i^1].flow-=f;flow+=f;a-=f;cur[x]=i;
			if(!a) break;
		}
	}
	return flow;
}

signed main()
{
	n = read();m = read();
	int S = 0,T = n+m+1,tot = 0;
	for(int i = 1;i <= n;i++){
		int a = read();add(i,T,a);
	}
	for(int i = 1;i <= m;i++){
		int l=read(),r=read(),c=read();
		tot+=c;
		add(S,i+n,c);add(i+n,l,inf);add(i+n,r,inf);
	}
	int maxflow = 0;
	while(Bfs(S,T)){
		for(int i = 0;i <= T;i++) cur[i]=head[i];
		maxflow += Dfs(S,inf,T);
//		cout<<maxflow<<endl;
	}
	cout << tot - maxflow << endl;
	return 0;
}
```


---

## 作者：tder (赞：0)

问题可以转化成：

- 选第 $i$ 个点的贡献为 $-a_i$；
- 同时选第 $u_i$ 和 $v_i$ 个点的贡献为 $w_i$。

由于每个点只有选或不选两种状态，并且可以有贪心结论：若同时选了第 $u_i$ 和 $v_i$ 个点，则必定会选两点之间的边 $w_i$，这是由于数据范围保证 $w_i\ge1$。那么，不难想到最小割模型：

- $s$ 为源点，若 $s$ 与 $i$ 可达，则称 $i$ 被选；
- $t$ 为汇点，若 $t$ 与 $i$ 可达，则称 $i$ 不被选。

对于最小割模型，我们通常需要将贡献转化为代价。在本题中，我们可以先计算出「理想状态」下的最大答案，即为 $\text{ans}_0=\sum w_i-0=\sum w_i$。注意，这里的「理想状态」并不可能真实存在。

那么，问题轻松的转化为了：

- 选第 $i$ 个点的代价为 $a_i$；
- 不同时选第 $u_i$ 和 $v_i$ 个点的代价为 $w_i$。

我们记此时的总代价为 $\text{sum}$，则我们希望 $\text{ans}=\text{ans}_0-\text{sum}$ 尽可能大，即希望 $\text{sum}$ 尽可能小，于是可以用最小割解决。

接下来考虑建图即可。

首先对于第 $i$ 个点，选择它的代价为 $a_i$，那么我们连一条 $i\to t$ 的容量为 $a_i$ 的边。如果要选他，根据定义， $i$ 与 $s$ 可达，而不与 $t$ 可达，因此需要割掉这条边，有代价 $a_i$。

而后较难的是第二种情况，若 $u_i$ 和 $v_i$ 不同时选有三种可能性：

- $u_i$ 与 $s$ 不可达，但 $v_i$ 与 $s$ 可达；
- $v_i$ 与 $s$ 不可达，但 $u_i$ 与 $s$ 可达；
- $u_i$ 和 $v_i$ 均与 $s$ 不可达。

针对上述可能性，我们单纯建 $s\to u_i$ 和 $s\to v_i$ 的容量为 $w_i$ 的边并不可取，因为对于第三种可能性此时的代价变为了 $w_i+w_i=2\times w_i$，与题意不符。我们考虑新建一个点 $d$，连 $d\to u_i$、$d\to v_i$ 和 $s\to d$ 三条边，容量均为 $w_i$。如下图所示，其中 $u_i=1$ 且 $v_i=2$：

![](https://cdn.luogu.com.cn/upload/image_hosting/lq57ut3d.png)

如此一来，三种可能性分别对应着：

- 割 $d\to u_i$ 的边；
- 割 $d\to v_i$ 的边；
- 割 $s\to d$ 的边。

且代价均为 $w_i$。

于是跑最小割模型得出 $\text{sum}$，再计算 $\text{ans}=\text{ans}_0-\text{sum}$ 即可。

---

```cpp
#include <bits/stdc++.h>
using namespace std;
#define int long long
const int N = 1e6 + 5, M = 3e3 + 5, INF = 1e18;
namespace Dinic {
    int n, s, t, cnt = 1, h[N], d[N], v[N], f[N];
    struct Node {
        int v, w, h;
    } e[N];
    void make(int u, int v, int w = 1) {
        e[++cnt] = {v, w, h[u]}; h[u] = cnt;
        e[++cnt] = {u, 0, h[v]}; h[v] = cnt;
    }
    bool bfs() {
        for(int i = 1; i <= n; i++) d[i] = INF;
        queue<int> q;
        q.push(s); d[s] = 0; f[s] = h[s];
        while(!q.empty()) {
            int x = q.front(); q.pop();
            for(int i = h[x]; i; i = e[i].h) {
                int p = e[i].v;
                if(e[i].w > 0 && d[p] == INF) {
                    q.push(p);
                    d[p] = d[x] + 1; f[p] = h[p];
                    if(p == t) return 1;
                }
            }
        }
        return 0;
    }
    int dfs(int x, int l) {
        if(x == t) return l;
        int k, r = 0;
        for(int i = f[x]; i && l; i = e[i].h) {
            f[x] = i;
            int p = e[i].v;
            if(e[i].w > 0 && d[p] == d[x] + 1) {
                k = dfs(p, min(l, e[i].w));
                if(!k) d[p] = INF;
                e[i].w -= k; e[i ^ 1].w += k;
                r += k, l -= k;
            }
        }
        return r;
    }
    void init(int nn, int ss, int tt) {
        n = nn, s = ss, t = tt;
        cnt = 1;
        memset(h, 0, sizeof(h)); memset(d, 0, sizeof(d)); memset(v, 0, sizeof(v)), memset(f, 0, sizeof(f));
    }
    int dinic() {
        int ans = 0;
        while(bfs()) {
            int x;
            while((x = dfs(s, INF))) ans += x;
        }
        return ans;
    }
}
int n, m, ans;
signed main() {
    cin>>n>>m; int cnt = n + 2;
    Dinic::init(n, n + 1, n + 2);
    for(int i = 1; i <= n; i++) {
        int x; cin>>x;
        Dinic::make(i, n + 2, x);
    }
    for(int i = 1; i <= m; i++) {
        int u, v, w; cin>>u>>v>>w;
        cnt++; ans += w;
        Dinic::make(n + 1, cnt, w);
        Dinic::make(cnt, u, w);
        Dinic::make(cnt, v, w);
    }
    // cout<<"cnt = "<<cnt<<endl;
    Dinic::n = cnt; 
    cout<<ans - Dinic::dinic()<<endl;
}
```

---

## 作者：xishanmeigao (赞：0)

（[题目传送门](https://www.luogu.com.cn/problem/CF1082G)）

一道最大权闭合子图的模板题

把所有点当作负权点，所有边当作正权点。

考虑一条边 $e=(x,y,z)$ 能选择的条件，当 $x,y$ 均被选择时就可以选，那对应到最大权闭合子图的模型中，就可以将 $(e,x),(e,y)$ 当作原图中的边。从 $e\rightarrow x,y$ 连一条容量为 $+\infty$ 的边

建模完毕后用计算最大权闭合子图点权和即可

```cpp
#include<bits/stdc++.h>
using namespace std;

const int N=55010,M=65010,INF=1e9;

int n,m,s,t,d[N],maxflow,sum;
int head[N],ver[2*M],nxt[2*M],edge[2*M],now[N],tot=1;

void add(int x,int y,int z)
{
	ver[++tot]=y;  edge[tot]=z;  nxt[tot]=head[x];  head[x]=tot;
	ver[++tot]=x;  edge[tot]=0;  nxt[tot]=head[y];  head[y]=tot;
}

bool bfs()
{
	memset(d,0,sizeof(d));
	queue <int> q;
	d[s]=1;  q.push(s);
	now[s]=head[s];
	
	while(q.size())
	{
		int x=q.front();  q.pop();
		for(int i=head[x]; i; i=nxt[i])
		{
			if(edge[i] && !d[ver[i]])
			{
				int y=ver[i];
				d[y]=d[x]+1;
				now[y]=head[y];
				if(y==t)
					return 1;
				q.push(y);
			}
		}
	}
	
	return 0;
}

int dinic(int x,int flow)
{
	if(x==t)
		return flow;
		
	int rest=flow,k;
	for(int &i=now[x]; i && rest; i=nxt[i])
	{
		if(edge[i] && d[ver[i]]==d[x]+1)
		{
			int y=ver[i];
			k=dinic(y,min(rest,edge[i]));
			if(!k)
				d[y]=0;
			edge[i]-=k;
			edge[i^1]+=k;
			rest-=k;
			if(rest<=0)
				break;
		}
	}
	
	return flow-rest;
}

int Dinic()
{
	int flow=0;
	while(bfs())
		while(flow=dinic(s,INF))
			maxflow+=flow;
	return maxflow;
}

int main()
{
	scanf("%d%d",&n,&m);
	
	s=0;  t=n+m+1;
	for(int i=1; i<=n; i++)
	{
		int x;
		scanf("%d",&x);
		add(i,t,x); //负点权点向汇点连边
	}
	for(int i=1; i<=m; i++)
	{
		int x,y,z;
		scanf("%d%d%d",&x,&y,&z);
		sum+=z;
		add(s,i+n,z); //源点向正点权点连边
		add(i+n,x,INF);  add(i+n,y,INF); //e(即i+n)向x,y连边
	}
	
	printf("%d",sum-Dinic()); //正点权和-最小割
	
	return 0;
}
```




---

## 作者：Pwtking (赞：0)

[传送门](https://www.luogu.com.cn/problem/CF1082G)

知识点：**最大权闭合图模型**！

题目的翻译便是这个模型的适用条件。

- 此模型建图方式：

1. 首先建立超级源点 $s$，和超级汇点 $t$，并新建 $m$ 个点 $p_i,i \in [1,m]$ 使一一对应每一条边，将原来的 $n$ 个点的编号初始化为 $p_i,i \in[m+1,n+m]$。

2. 再将原来的第 $i$ 条边 $E_i(u,v)=w$ 在我们建的图上处理为 $s\longrightarrow i$，且边权处理为 $E(s,i)=w$，再将 $i\longrightarrow u+m,i\longrightarrow v+m$ 分别连一条边。

3. 最后将每一个点 $p_i,i\in [m+1,m+n]$ 向汇点连边权为该点点权的有向边，即 $ p_i ,i \in [m,m+n] \longrightarrow t$，且 $E(p_i,t)=V_{p_i}$。

这样建图之后答案即为**点权之和 $-$ 新建图的最小割**。

- 证明：

我们可以将这个模型转化为一个情景：有 $m$ 个人，$n$ 种使用需要付费的工具的花费分别为 $V_{n_i}$。这 $m$ 个人每个人做任务，完成后分别会得到 $w_{m_i}$ 的盈利，但会使用 $k_{m_i}$ 种工具。一个工具被多次使用时只需收费一次，请你安排一些人去做任务使的总获利最大。

如果我们选择了 $p$ 个人让他们不做任务，那么则需要付剩下的 $m-p$ 个人所需的全部工具的费用。转化到图上，即是构成了这张图的一个割，这个可以画图自证。那么此时的利润即为 **$m-p$ 个人的利润 $-$ 这 $m-p$ 个人工具费用 $=\sum w-p$ 个不工作的人的利润 $-$ 这 $(m-p)$ 个人工具费用 $=\sum w-$ 这张图的割**。

为了利润更大，则减去最小割即可。

证毕。


---

## 作者：intel_core (赞：0)

因为这个题的边权全都非负，可以想到选的节点集合为 $S$ ，那么边权和 $=\sum_{x,y\in S \& (x,y) \in E}val(x,y)$。

所以我们只需要确定选出节点的集合即可。

从边的角度来考虑这个问题，如果 $(x,y)$ 被选中，必然有 $x,y \in S$。

这是什么？最大权闭合子图对吧。

直接用网络流解决问题，复杂度上界 $O((n+m) \sqrt{n+m})$，可以轻松通过本题。

```cpp
#include<bits/stdc++.h>
using namespace std;
const int NR=1e4+10;
#define int long long
int n,m,s,t,ans,a[NR];

struct edge{
	int to,next;
	int flow;
}g[NR];
int tot=1,fte[NR];
void add(int x,int y,int z){
	g[++tot]=(edge){y,fte[x],z};fte[x]=tot;
	g[++tot]=(edge){x,fte[y],0};fte[y]=tot;
}
int dis[NR],cur[NR];
bool bfs(){
	memset(dis,-1,sizeof(dis));
	queue<int>q;q.push(s);
	dis[s]=0;cur[s]=fte[s];
	while(!q.empty()){
		int x=q.front();q.pop();
		for(int i=fte[x];i;i=g[i].next){
			int y=g[i].to;
			if(dis[y]==-1&&g[i].flow){
				q.push(y);dis[y]=dis[x]+1;
				cur[y]=fte[y];
				if(y==t)return true;
			}
		}
	}
	return false;
}
int dfs(int id,int Limit){
	if(id==t)return Limit;
	int flow=0;
	for(int i=cur[id];i&&flow<Limit;i=g[i].next){
		cur[id]=i;
		int y=g[i].to;
		if(g[i].flow!=0&&dis[y]==dis[id]+1){
			int f=dfs(y,min(g[i].flow,Limit-flow));
			if(!f)dis[y]=-1;
			g[i].flow-=f;g[i^1].flow+=f;
			flow+=f;
		}
	}
	return flow;
}
int Dinic(){
	int MaxFlow=0,flow=0;
	while(bfs())
		while(flow=dfs(s,1e18))MaxFlow+=flow;
	return MaxFlow;
}

signed main(){
	cin>>n>>m;s=n+m+1;t=s+1;
	for(int i=1;i<=n;i++)cin>>a[i],add(i+m,t,a[i]);
	for(int i=1;i<=m;i++){
		int x,y,z;cin>>x>>y>>z;ans+=z;
		add(i,x+m,1e9);add(i,y+m,1e9);add(s,i,z);
	}
	cout<<ans-Dinic()<<endl;
	return 0;
}
```

---

