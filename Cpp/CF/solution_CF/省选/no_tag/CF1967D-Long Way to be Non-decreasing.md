# Long Way to be Non-decreasing

## 题目描述

Little R is a magician who likes non-decreasing arrays. She has an array of length $ n $ , initially as $ a_1, \ldots, a_n $ , in which each element is an integer between $ [1, m] $ . She wants it to be non-decreasing, i.e., $ a_1 \leq a_2 \leq \ldots \leq a_n $ .

To do this, she can perform several magic tricks. Little R has a fixed array $ b_1\ldots b_m $ of length $ m $ . Formally, let's define a trick as a procedure that does the following things in order:

- Choose a set $ S \subseteq \{1, 2, \ldots, n\} $ .
- For each $ u \in S $ , assign $ a_u $ with $ b_{a_u} $ .

Little R wonders how many tricks are needed at least to make the initial array non-decreasing. If it is not possible with any amount of tricks, print $ -1 $ instead.

## 说明/提示

In the first case, the initial array $ a_1, \ldots, a_n $ is $ [1, 6, 3, 7, 1] $ . You can choose $ S $ as follows:

- first trick: $ S = [2, 4, 5] $ , $ a = [1, 1, 3, 5, 2] $ ;
- second trick: $ S = [5] $ , $ a = [1, 1, 3, 5, 3] $ ;
- third trick: $ S = [5] $ , $ a = [1, 1, 3, 5, 5] $ .

 So it is possible to make $ a_1, \ldots, a_n $ non-decreasing using $ 3 $ tricks. It can be shown that this is the minimum possible amount of tricks.In the second case, it is impossible to make $ a_1, \ldots, a_n $ non-decreasing.

## 样例 #1

### 输入

```
3
5 8
1 6 3 7 1
2 3 5 8 7 1 5 6
3 3
1 3 2
2 1 3
10 10
2 8 5 4 8 4 1 5 10 10
6 7 2 6 3 4 1 1 3 5```

### 输出

```
3
-1
3```

# 题解

## 作者：BPG_ning (赞：6)

## CF1967D

题意：给定长度为 $ n $ 的序列 $ a $ 和长度为 $ m $ 的序列 $ b $ ，一次操作能选出部分 $ i $ 使得 $ b_{a_i} \to a_i $，求最小的操作次数使得 $ a $ 单调不降。



题解：显然可以考虑二分答案，二分的 $ mid $ 具体含义是每个点**至多**变化 $ mid $ 次。

建图，将 $ i \to b_i $ 连一条有向边，至多变化 $ mid $ 次即为在图上至多走 $ mid $ 步。

并且容易发现这张图是一个内向基环树森林。（每个点的出度恰好为 $ 1 $）

我们考虑贪心的枚举第 $ i $ 个值能变成的最小值，并且满足 $ a'_{i-1} \leq a'_i $。

发现这就是求后继，考虑在树上用树剖维护，在环上好维护，复杂度为 $ n\log^2_2 n $。

在代码难写的同时常数起飞，难以通过。

发现 $ a'_i $ 单调不减，可以双指针维护最小值，于是只需要判断 $ a_i $ 到达 $ p $ 的距离。（即在 $ mid $ 距离之内能否到达 $ p $）

考虑分类讨论，若两点在同一棵树上，那么只有祖宗关系才可到达。

若两点在同一个环上，距离容易统计。

若两点分别在树上和这棵树的环上，那么将距离分解成点到树根的距离+树根到环上的距离。

然后做完了!

---

## 作者：XuYueming (赞：5)

## 题意简述

yzh 喜欢单调不降序列。

她有一个序列 $a$，最初为 $a_1, \ldots, a_n$，其中每个元素都在 $[1, m]$ 内。

她希望使序列变得单调不降，为此，她有一个序列 $b_1, \ldots, b_m$，每个元素也在 $[1, m]$ 内。她可以进行若干次操作，一次操作定义为：

1. 选择一个集合 $S \subseteq \lbrace 1, 2, \ldots, n \rbrace$。
1. $\forall i \in S$，$a_i \leftarrow b_{a_i}$。

yzh 想知道至少需要多少次操作可以使 $a$ 变单调不降。如果不可能，输出 $-1$。

多组数据，$\sum n,\sum m \leq 10^6$。

## 题目分析

[更好的阅读体验？](https://www.cnblogs.com/XuYueming/p/18180887)

首先能想到，每次选择一个集合操作是唬人的，不妨按照每一个位置来算。发现这样操作的总步数是所有位置中操作次数最多的那一个，最大值最小，很容易想到二分。那么如何 `check` 呢？

设当前判断能否在 $mid$ 次操作内使 $a$ 变得单调不降。有一个贪心的想法，从左向右考虑，设 $a_i$ 操作 $mid$ 次所能到达的集合（包括一次也不操作，即 $a_i$ 本身）为 $S$，那么令 $a_i \leftarrow \min \lbrace x \mid x \in S \wedge x \geq a_{i - 1} \rbrace$，当然，$a_1$ 没有 $a_1 \geq a_0$ 的限制，可以直接当 $a_0 = 0$。什么时候无解呢？当某一位的 $S = \varnothing$，即 $a_i$ 没有任何一个可行解的时候无解。一个 native 的想法就是每一位干 $mid$ 次然后判断一下取最小值，显然超时，考虑优化。

考虑倒着考虑，枚举 $a_i$ 能否在 $mid$ 步之内变成 $a_{i - 1}, a_{i - 1} + 1, \ldots, m$。发现，当 $a_i$ 取了一个值，那么 $a_{i + 1}$ 就会从 $a_i$ 开始考虑，这显然是单调的。所以考虑从左向右枚举的时候维护一个指针 $j$，当 $\operatorname{dist}(a_i, j) > mid$ 时，就让 $j \leftarrow j + 1$，其中 $\operatorname{dist}(xym, yzh)$ 表示 $xym$ 变换到 $yzh$ 的操作数。

考虑实现 $\operatorname{dist}(xym, yzh)$。很容易地连边 $i \rightarrow b_i$，形成一个内向基环树森林。

1. 当 $xym$ 和 $yzh$ 不在一棵基环树内时，$\operatorname{dist}(xym, yzh) = \infty$。
1. 当 $xym$ 和 $yzh$ 在同一棵基环树内时：
    1. $yzh$ 是 $xym$ 的祖先，$\operatorname{dist}(xym, yzh) = dpt_{xym} - dpt_{yzh}$。
    1. $yzh$ 是环上一点，设 $xym$ 是环上 $p$ 的子孙，$\operatorname{dist}(xym, yzh) = dpt_{xym} - dpt_{p} + \operatorname{dis}(p, yzh)$，实现换上距离 $\operatorname{dis}(a, b)$ 是 native 的。
    1. 其他情况 $\operatorname{dist}(xym, yzh) = \infty$。

到此为止，我们已经能完成这道题了。但是，我要讲另一种更方便求得基环树森林中两点距离的方法，一下只考虑 $xym$ 和 $yzh$ 在同一棵基环树内。

考虑拆环成树，断开环上任意一条边 $u \rightarrow b_u$，再以 $u$ 为根，做一遍内向树上的深搜。考虑这时候计算 $\operatorname{dist}(xym, yzh)$。

1. 若 $xym \in \operatorname{subtree}(yzh)$，则 $\operatorname{dist}(xym, yzh) = dpt_{xym} - dpt_{yzh}$，$\operatorname{subtree}(yzh)$ 可以用 dfs 序实现。
1. 若 $\exists \operatorname {Path}(xym \rightarrow u \rightarrow b_u \rightarrow yzh)$，则 $\operatorname{dist}(xym, yzh) = dpt_{xym} - dpt_{u} + 1 + dpt_{b_u} - dpt_{yzh}$。
1. 其他情况 $\operatorname{dist}(xym, yzh) = \infty$。

这显然是正确的，可以配合下图理解。

![yzh I love you!](https://cdn.luogu.com.cn/upload/image_hosting/ssh3kwo6.png)

令 $n$ 和 $m$ 同阶，两种方法时间复杂度 $\Theta(n (\alpha(n) + \log n))$，空间复杂度 $\Theta(n)$。

## 代码

实际连边的时候是连的外向树，这样才能做 dfs。挺快的，卡卡常洛谷 [Rank1](https://www.luogu.com.cn/record/158439008)，下面略去了快读快写。

```cpp
#pragma GCC optimize(3)
#pragma GCC optimize("Ofast", "inline", "-ffast-math")
#pragma GCC target("avx", "sse2", "sse3", "sse4", "mmx")
#include <iostream>
#include <cstdio>
#define debug(a) cerr << "Line: " << __LINE__ << " " << #a << endl
#define print(a) cerr << #a << "=" << (a) << endl
#define file(a) freopen(#a".in", "r", stdin), freopen(#a".out", "w", stdout)
#define main Main(); signed main(){ return ios::sync_with_stdio(0), cin.tie(0), Main(); } signed Main
using namespace std;

struct Graph{
	struct node{
		int to, nxt;
	} edge[1000010];
	int eid, head[1000010];
	inline void add(int u, int v){
		edge[++eid] = {v, head[u]};
		head[u] = eid;
	}
	inline node & operator [] (const int x){
		return edge[x];
	}
} xym;

int n, m;
int val[1000010], trans[1000010];
int del[1000010], L[1000010], R[1000010], timer;
int dpt[1000010];

void dfs(int now){
    L[now] = ++timer;
    for (int i = xym.head[now], to; to = xym[i].to, i; i = xym[i].nxt) dpt[to] = dpt[now] + 1, dfs(to);
    R[now] = timer;
}

int fa[1000010];
int get(int x){
    return fa[x] == x ? x : fa[x] = get(fa[x]);
}
bool merge(int x, int y){
    return x = get(x), y = get(y), x != y && (fa[x] = y, true);
}

inline bool insub(int v, int u){
    // v 在不在 u 的子树里
    return L[u] <= L[v] && L[v] <= R[u];
}

inline int dis(int x, int y){
    if (get(x) != get(y)) return 0x3f3f3f3f;
    if (insub(x, y)) return dpt[x] - dpt[y];
    // x 在 y 的子树里，直接往上跳
    if (insub(trans[del[get(x)]], y)) return dpt[x] + 1 + dpt[trans[del[get(x)]]] - dpt[y];
    // 看看能不能跳过断掉的边
    return 0x3f3f3f3f;
}

bool check(int k){
    // j  即是维护的指针
	for (int i = 1, j = 1; i <= n; ++i){
        while (j <= m && dis(val[i], j) > k) ++j;
        if (j > m) return false;
	}
	return true;
}

void solve(){
	read(n), read(m), timer = 0, xym.eid = 0;
	for (int i = 1; i <= n; ++i) read(val[i]);
	for (int i = 1; i <= m; ++i) read(trans[i]), fa[i] = i, del[i] = 0, xym.head[i] = 0, dpt[i] = 0;
    for (int i = 1; i <= m; ++i)
        if (!merge(i, trans[i])) del[get(i)] = i;
        // 如果找到了环，那么把 i -> trans[i] 这条边删除
        else xym.add(trans[i], i);
        // 否则建出内向树森林
    for (int i = 1; i <= m; ++i) if (fa[i] == i) dfs(del[i]); // 跑 dfs 序
	int l = 0, r = m, mid, ans = -1;
	while (l <= r){
		mid = (l + r) >> 1;
		if (check(mid)) ans = mid, r = mid - 1;
		else l = mid + 1;
	}
    // 简单二分
    if (ans == -1) putchar('-'), putchar('1'), putchar('\n');
    else write(ans), putchar('\n');
}

signed main(){
	int t; read(t);
	while (t--) solve();
	return 0;
}
```

---

## 作者：xyin (赞：2)

首先二分的性质很容易看出来，二分一个 $mid$ 后，看看每个数能不能在 $mid$ 次转换内，变成一个单调不降序列。

我们根据样例手模，每次由 $i$ 向 $b_i$ 连一条右向边，发现它是基环树森林，而且每个点的出度都为 $1$，它还是一颗内向基环树。证明：如果某一颗树不存在环的话，则一定有某个点的出度为 $0$，与题目特性不符。（~~我也不知道我当时怎么想的，一定要把它的环拆开成链做~~）

重点是怎么 check？首先对于每一个 $a_i$ 遍历一遍它在 $mid$ 次内能通向的点，然后再去维护一个 LIS 的这种做法显然是不可取的。还是贪心大法好啊，利用它的单调性，我们只需用一个指针从 $1\sim m$ 遍历一遍即可（之前没取上的后面也不可能取）。

最后的问题就是怎么判断 $x$ 到 $y$ 是否能在 $mid$ 次内到达，由于要进行 dfs，我们对于原图的边建反边，变成外向基环树森林，然后直接开始分类讨论：

* $x,y$ 不是同一颗基环树，此时 $x$ 不可能到达 $y$。

* $x,y$ 都是环上的点，我们最开始预处理环的时候，直接对它们编一个号，$O(1)$ 查询与 $mid$ 比较即可。

* $x$ 是环上的点，$y$ 是链上的点，由于这是一颗内向基环树，$x$ 一定到不了 $y$。

* $x$ 是链上的点，$y$ 是环上的点，可以由 $x$ 先跳到环上，再加上从 $x'$ 到 $y$ 的距离，预处理时对每个点记录一下深度 $depp$ 即可。

* $x,y$ 都是链上的点，$x$ 能到 $y$ 当且仅当 $y$ 是 $x$ 的祖先。判断祖先关系，可以记录一下 dfs 序 的 $in_i$ 和 $out_i$，然后判断包含关系即可。如果可以到达，那直接就是比较 $depp_x-deep_y$ 和 $mid$ 的大小。

综上时间复杂度为 $O((n+m)\log n)$，实际上由于本人常数的问题，调了接近一天，CF 它还拿不到数据。。。

---

## 作者：Kevin911 (赞：2)

这题竟然 *2800？蒟蒻不才，所以用了一大堆的分类讨论。

## 思路
首先一条边只有一条出边可以转化为很多棵树插在一个环上的基环树森林。然后可以转化一下题面选择最少的点集相当于操作次数最多的点操作次数最少。考虑二分答案，二分在每个点至多操作 $t$ 次内，能否是序列单调不降。

称这个位置最终变为的数为目标点，而目标点具有单调性，可以用双指针解决。

对于环上的点，先都跑一边 dfs，把环都拆成一条链，然后检查目标点是否在一个或两个连续的区间。

而对于不是环上的点就可以转化为树上问题：

+ 到达环之前的部分，检查目标点是否是该点祖先且距离小于可操作数。

+ 环上部分和之前的处理方法一样。

显然两者只需满足一个即可。

代码如下：

```cpp
#include<bits/stdc++.h>
using namespace std;
const int maxn=1e6+10;
int n,m,cnt,ans;
int a[maxn],b[maxn],c[maxn],d[maxn],in[maxn],p[maxn],f[maxn],mx[maxn],mn[maxn],rt[maxn],dfn[maxn],sz[maxn];
bool vis[maxn];
vector<int> g[maxn];
queue<int> q;
void topsort()
{
	for(int i=1;i<=m;i++)
		if(!in[i]) q.push(i);
	while(!q.empty())
	{
		int u=q.front();
		q.pop();
		vis[u]=0;
		in[b[u]]--;
		if(!in[b[u]]) q.push(b[u]); 
	}
}
void dfs1(int u,int id)
{
	if(p[u]) return;
	d[u]=0,p[u]=++cnt,f[u]=id,mx[id]=max(mx[id],cnt),mn[id]=min(mn[id],cnt);
	dfs1(b[u],id);
}
void dfs2(int u,int f)
{
	if(!vis[f]) rt[u]=rt[f];
	else rt[u]=u;
	d[u]=d[f]+1;
	dfn[u]=++cnt;
	sz[u]=1;
	for(int i=0;i<g[u].size();i++)
	{
		int v=g[u][i];
		if(v==f) continue;
		dfs2(v,u);
		sz[u]+=sz[v];
	}
}
bool is_son(int x,int y)
{
	return dfn[x]<=dfn[y]&&dfn[x]+sz[x]-1>=dfn[y];
}
bool check(int x)
{
	int j=1;
	for(int i=1;i<=n;i++)
	{
		if(vis[a[i]])
		{
			while(j<m&&!vis[j]) j++;
			if(x<=mx[f[a[i]]]-p[a[i]])
			{
				while(j<m&&!(p[j]>=p[a[i]]&&p[j]<=p[a[i]]+x)) j++;
				if(!(p[j]>=p[a[i]]&&p[j]<=p[a[i]]+x)) return 0;
			}
			else if(x<=mx[f[a[i]]]-mn[f[a[i]]]+1)
			{
				while(j<m&&!((p[j]>=p[a[i]]&&p[j]<=mx[f[a[i]]])||(p[j]>=mn[f[a[i]]]&&p[j]<=mn[f[a[i]]]+x-(mx[f[a[i]]]-p[a[i]]+1)))) j++;
				if(!((p[j]>=p[a[i]]&&p[j]<=mx[f[a[i]]])||(p[j]>=mn[f[a[i]]]&&p[j]<=mn[f[a[i]]]+x-(mx[f[a[i]]]-p[a[i]]+1)))) return 0;
			}
			else
			{
				while(j<m&&!(p[j]>=mn[f[a[i]]]&&p[j]<=mx[f[a[i]]])) j++;
				if(!(p[j]>=mn[f[a[i]]]&&p[j]<=mx[f[a[i]]])) return 0;
			}
		}
		else
		{
			if(x<d[a[i]])
			{
				while(j<m&&!(is_son(j,a[i])&&d[a[i]]-d[j]<=x)) j++;
				if(!(is_son(j,a[i])&&d[a[i]]-d[j]<=x)) return 0;
			}
			else
			{
				int y=b[rt[a[i]]];
				if(x<=d[a[i]]+mx[f[y]]-p[y])
				{
					while(j<m&&!(is_son(j,a[i])||(p[j]>=p[y]&&p[j]<=p[y]+x-d[a[i]]))) j++;
					if(!(is_son(j,a[i])||(p[j]>=p[y]&&p[j]<=p[y]+x-d[a[i]]))) return 0;
				}
				else if(x<=d[a[i]]+mx[f[y]]-mn[f[y]]+1)
				{
					while(j<m&&!(is_son(j,a[i])||(p[j]>=p[y]&&p[j]<=mx[f[y]])||(p[j]>=mn[f[y]]&&p[j]<=mn[f[y]]+x-d[a[i]]-(mx[f[y]]-p[y]+1)))) j++;
					if(!(is_son(j,a[i])||(p[j]>=p[y]&&p[j]<=mx[f[y]])||(p[j]>=mn[f[y]]&&p[j]<=mn[f[y]]+x-d[a[i]]-(mx[f[y]]-p[y]+1)))) return 0;
				}
				else
				{
					while(j<m&&!(is_son(j,a[i])||(p[j]>=mn[f[y]]&&p[j]<=mx[f[y]]))) j++;
					if(!(is_son(j,a[i])||(p[j]>=mn[f[y]]&&p[j]<=mx[f[y]]))) return 0;
				}
			}
		}
	}
	return 1;
}
signed main()
{
	int t;
	cin>>t;
	while(t--)
	{
		cnt=ans=0;
		cin>>n>>m;
		for(int i=1;i<=m;i++) in[i]=p[i]=f[i]=mx[i]=rt[i]=dfn[i]=sz[i]=0,mn[i]=1e9,vis[i]=1,g[i].clear();
		for(int i=1;i<=n;i++) cin>>a[i];
		for(int i=1;i<=m;i++) cin>>b[i],in[b[i]]++,g[b[i]].push_back(i);
		topsort();
		for(int i=1;i<=m;i++)
			if(vis[i]&&!p[i]) dfs1(i,i);
		for(int i=1;i<=m;i++)
			if(!vis[i]&&vis[b[i]]) dfs2(i,b[i]);
		if(check(0))
		{
			cout<<0<<endl;
			continue;
		}
		if(!check(m))
		{
			cout<<-1<<endl;
			continue;
		}
		for(int i=20;i>=0;i--)
			if(ans+(1ll<<i)<m&&!check(ans+(1ll<<i))) ans+=(1ll<<i);
		cout<<ans+1<<endl;
	}
}
```

---

## 作者：raincity (赞：2)

这题有 *2800？

先把问题转化为一个图论模型：建一张 $m$ 个点的有向图，$i$ 向 $b_i$ 连边。则题目转化为求最小的 $k$，满足从 $a_i$ 开始走不超过 $k$ 步，走到的点的编号 $a'_i$ 单调不降。

因为每个点的出度都等于 $1$，所以这张图是根向基环树森林。

二分答案。考虑如何 check。容易想到贪心，令 $a_i$ 走到能走到的不小于 $a'_{i - 1}$ 的最小的点。但是 $a'_i$ 并不好求（不弱于静态二维数点），并且主席树肯定跑不了 $10^7$，考虑找一些性质。

观察到 $\sum (a'_i - a'_{i - 1}) \le m$，所以只需 $O(m)$ 次判断 $u \rightsquigarrow v$ 的路径长度是否不超过 $k$。这是容易的，若 $v$ 是 $u$ 的祖先则路径长度等于 $dep_u - dep_v$，否则若 $v$ 在从 $u$ 出发可达的环上则路径长度等于 $dep_u$ + 环上距离。简单预处理即可。

时间复杂度 $O((m + n) \log m)$。

[提交记录](https://codeforces.com/contest/1967/submission/276417046)

---

## 作者：yuanruiqi (赞：2)

首先考虑二分答案。

从 $1$ 到 $n$ 依次将 $a_i$ 改为在 $mid$ 步内可以到达，且不小于 $a_{i-1}$ 的最小取值。直接做可以通过某些复杂数据结构在双 $\log$ 的时间解决，但不存在优化空间。

考虑双指针，现在的问题是判断 $dis(i,j)\le mid$。

对于所有的 $u$，从 $u$ 到 $b_u$ 连接单向边，容易发现形成内向基环树森林。可以对 $i,j$ 的相对位置进行分讨。

- 若 $i,j$ 位于在环上挂载的同一棵树上，且 $i$ 在 $j$ 的子树内，则距离等于深度差，判断包含关系可以使用 $dfn$ 序。

- 对于在同一个环上的  $i$ 和 $j$，可以对每个环预处理点的遍历顺序。

- 若 $i$ 和 $j$ 在一个连通块，且 $j$ 在环上，$i$ 在某棵树内，记 $k$ 为 $i$ 在环上的祖先，有 $dis(i,j)=dis(i,k)+dis(k,j)$。

在 $O((n+m)\log m)$ 的复杂度内可以解决。

```cpp
#include <bits/stdc++.h>
using namespace std;
using i64 = long long;
constexpr int maxn = 1000000 + 10;
int a[maxn], b[maxn];
int d[maxn];
int id[maxn];
int fa[maxn], siz[maxn];
int find(int x)
{
    return x == fa[x] ? x : fa[x] = find(fa[x]);
}
struct edge
{
    int v, nxt;
} e[maxn << 1];
int h[maxn];
int tot;
int dfn[maxn], ed[maxn];
int dep[maxn];
int col[maxn];
int cnt;
void dfs(int u, int c)
{
    col[u] = c;
    dfn[u] = ++cnt;
    for (int i=h[u];i;i=e[i].nxt)
    {
        int v = e[i].v;
        if (d[v]) continue;
        dep[v] = dep[u] + 1;
        dfs(v, c);
    }
    ed[u] = cnt;
}
constexpr int inf = 0x3f3f3f3f;
int n, m;
int dis(int i, int j)
{
    if (i == j) return 0;
    if (d[i])
    {
        if (!d[j]) return inf;
        if (fa[i] != fa[j]) return inf;
        int y = id[j] - id[i];
        return y < 0 ? y + siz[fa[i]] : y;
    }
    if (dfn[j] <= dfn[i] && ed[i] <= ed[j]) return dep[i] - dep[j];
    else if (d[j] && fa[col[i]] == fa[j])
    {
        int y = id[j] - id[col[i]];
        return dep[i] + (y < 0 ? y + siz[fa[j]] : y);
    }
    return inf;
}
int q[maxn];
void solve()
{
    cin >> n >> m;
    cnt = tot = 0;
    memset(d, 0, sizeof(d[0]) * (m + 5));
    memset(siz, 0, sizeof(siz[0]) * (m + 5));
    memset(id, 0, sizeof(id[0]) * (m + 5));
    memset(h, 0, sizeof(h[0]) * (m + 5));
    iota(fa + 1, fa + m + 1, 1);
    for (int i=1;i<=n;++i) cin >> a[i];
    for (int i=1;i<=m;++i) cin >> b[i], ++d[b[i]], e[++tot].nxt = h[b[i]], e[h[b[i]] = tot].v = i;
    int l = 1, r = 0;
    for (int i=1;i<=m;++i) if (d[i] == 0) q[++r] = i;
    while (l <= r)
    {
        int u = q[l++];
        if (--d[b[u]] == 0) q[++r] = b[u];
    }
    for (int i=1;i<=m;++i)
        if (d[i]) fa[find(i)] = find(b[i]);
    for (int i=1;i<=m;++i) if (d[i]) ++siz[find(i)];
    for (int i=1;i<=m;++i) if (d[i])
    {
        if (id[i]) continue;
        id[i] = 1;
        int u = b[i], cnt = 1;
        while (u != i)
        {
            id[u] = ++cnt;
            u = b[u];
        }
    }
    for (int i=1;i<=m;++i) if (d[i]) dep[i] = 0, dfs(i, i);
    l = 0, r = m + 10;
    while (l < r)
    {
        int mm = (l + r) >> 1, ok = 1;
        for (int i=1,p=1;i<=n&&ok;++i)
        {
            while (p <= m && dis(a[i], p) > mm) ++p;
            if (p > m) ok = 0;
        }
        if (ok) r = mm;
        else l = mm + 1;
    }
    if (r > m) r = -1;
    cout << r << '\n';
}
int main()
{
    ios::sync_with_stdio(0);
    cin.tie(0);
    int t;
    cin >> t;
    while (t--) solve();
    return 0;
}
```

---

## 作者：JPGOJCZX (赞：1)

节选自：[图论做题记录（三）（2025.5.24 - 2025.31）](https://www.luogu.com.cn/article/2xi85b8k)

[安利一下我的博客](https://www.cnblogs.com/JPGOJCZX/p/18904065)

首先，如果 $x$ 次操作可以将 $a$ 序列变成单调不降的，那么第 $x + 1$ 次时，我们可以把序列中一个 $a$ 赋值成它本身，此时序列仍是单调不降的（有点废话，但是是有用的废话），这说明这道题目具有单调性，我们可以先二分答案，那么原问题就变成了判断进行 $x$ 次操作，能否将 $a$ 序列变成单调不降的。

此时我们就有了一个贪心的想法，对于序列的第 $i$ 个位置，它最终变成的这个数一定大于第 $i - 1$ 个位置，且是最小的，这样才能让后面能变的数字变多。当无论如何进行这 $x$ 次操作，$a_i$ 都比 $a_{i - 1}$ 小的时候，那么就无解了。

不过这样直接判断 $a_i$ 进行 $x$ 次操作能变成哪些数肯定会超时，我们考虑优化它。由于有连续将一个数变成另一个数的操作，那么我们考虑将复值的过程建成图，从每个 $i$ 向 $b_i$ 连边，此时就构成了一棵基环树森林，一个数变成另一个数需要的操作数，也就变成了基环树上两点距离。

于是我们正着扫一遍整个序列，枚举 $now$ 为当前可以填的最小的数，如果 $a_i$ 到 $now$ 的距离小于 $x$，那么 $now$ 就不变，否则 $now$ 就不断增加直到 $a_i$ 到 $now$ 的距离小于 $x$，如果 $now$ 已经大于 $m$，那就无解了，否则就有解。由于 $now$ 是单调不降的，因此二分答案 `check` 一次是 $O(n)$ 的，于是我们用 $O(T n \log n)$ 的时间复杂度解决了这个问题。

关于如何在有向基环树上求两点间的距离，见[图论学习笔记（五）：特殊图](https://www.luogu.com.cn/article/j0qscjhf) / 基环树 / 基环树上两点距离 / 有向图。

完整代码：

```cpp
#include <bits/stdc++.h>
using namespace std;
#define MAXSIZE (1 << 20)
char buf[MAXSIZE], *p1, *p2;
char pbuf[MAXSIZE], *pp;
#define gc() (p1 == p2 && (p2 = (p1 = buf) + fread(buf, 1, MAXSIZE, stdin), p1 == p2) ? EOF : *p1++)
#define pc putchar
inline int read(){
	int x = 0;
	char ch = gc();
	while(!isdigit(ch))
		ch = gc();
	while(isdigit(ch)){
		x = (x << 1) + (x << 3) + (ch ^ 48);
		ch = gc();
	}
	return x;
}
inline void write(int x){
    if(x < 0){
		pc('-');
		x = -x;
	}
	if(x > 9)
		write(x / 10);
	pc(x % 10 + '0');
}
const int N = 1e6 + 9, INF = 0x3f3f3f3f;
struct Edge{
    int v, nex;
} e[N << 1];
int head[N], ecnt;
void addEdge(int u, int v){
    e[++ecnt] = Edge{v, head[u]};
    head[u] = ecnt;
}
int a[N], b[N], fa[N], del[N], L[N], R[N], dep[N], dfncnt, n, m, T;
int find(int x){
    return fa[x] == x ? x : fa[x] = find(fa[x]);
}
void dfs(int u){
    L[u] = ++dfncnt;
    for(int i = head[u]; i; i = e[i].nex){
        int v = e[i].v;
        dep[v] = dep[u] + 1;
        dfs(v);
    }
    R[u] = dfncnt;
}
bool pd(int v, int u){
    return L[u] <= L[v] && R[u] >= L[v];
}
int ask(int u, int v){
    if(find(u) != find(v))
        return INF;
    if(pd(u, v))
        return dep[u] - dep[v];
    if(pd(b[del[find(u)]], v))
        return dep[u] + 1 + dep[b[del[find(u)]]] - dep[v];
    return INF;
}
int check(int mid) {
	int now = 1;
	for(int i = 1; i <= n; ++ i) {
		while(now <= m && ask(a[i], now) > mid)
            now++;
		if(now > m)
            return 0;
	}
	return 1;
}
void init(){
    for(int i = 1; i <= m; i++)
        head[i] = del[i] = dep[i] = 0;
    dfncnt = ecnt = 0;
}
int main(){
    T = read();
    while(T--){
        init();
        n = read();
        m = read();
        for(int i = 1; i <= n; i++)
            a[i] = read();
        for(int i = 1; i <= m; i++){
            fa[i] = i;
            b[i] = read();
        }
        for(int i = 1; i <= m; i++){
            int x = find(i), y = find(b[i]);
            if(x != y){
                fa[x] = y;
                addEdge(b[i], i);
            } else
                del[x] = i;
        }
        for(int i = 1; i <= m; i++){
            if(fa[i] == i){
                dfncnt = 0;
                dfs(del[i]);
            }
        }
        int l = 0, r = m, ans = - 1;
        while(l <= r) {
            int mid = ((l + r) >> 1);
            if(check(mid)){
                ans = mid;
                r = mid - 1;
            }
            else
                l = mid + 1;
        }
        write(ans);
        pc('\n');
    }
    return 0;
}
```

---

## 作者：Add_Catalyst (赞：1)

# CF1967D Long Way to be Non-decreasing 题解

---

## 知识点

二分答案，基环树。

---

## 题意分析

给定一个包含 $n$ 个元素的数组 $\{ a_i \}$ 和一个 $m$ 个元素的数组 $\{ b_i \}$。

定义每次操作为：在 $\{ a_i \}$ 中选择任意个数，假设某个选的数为 $a_i$，那么将其变为 $b_{a_i}$。

问使 $\{ a_i \}$ 变为单调不降的最少操作次数。

---

## 思路分析

看到“最少”这个词语就应该考虑二分答案，再看性质，它明显满足单调性，那就是二分答案无疑了。

那么考虑二分的检验过程：

设现在二分的次数为 $x$，一开始的 $mx=m$。

我们可以从最后一个开始检验，如果不能到 $mx$ 或到 $mx$ 的距离大于 $x$，就将 $mx$ 减一，再继续重复，做一个尺取操作，如果 $mx$ 有降到 $0$ 及以下，就说明不合法。

我们现在再考虑如何求距离。

明显，如果我们建图，生成 $m$ 个点，再往第 $i$ 个点上连一条向 $b_i$ 的边，那么就生成了一个内向基环森林，在这里，有两种求距离的方式：

1. 把环上的每一个点都作为一棵子树的根，将距离分为环上距离与树上距离；
2. 把环上某个点连向父节点的边砍掉，重新建树，就可以转换为新树上的距离。

至此，思路已经结束。

---

## CODE

下面分别给出两种基环树（森林）上求距离的方法代码。

1. 把环上的每一个点都作为一棵子树的根，将距离分为环上距离与树上距离；

   ```cpp
   #include<bits/stdc++.h>
   #define INF 0x3f3f3f3f
   #define ll long long
   #define max(a,b) ((a)<(b)?(b):(a))
   #define min(a,b) ((a)>(b)?(b):(a))
   #define tomax(a,b) ((a)=max((a),(b)))
   #define tomin(a,b) ((a)=min((a),(b)))
   #define RCL(a,b,c,d) memset((a),(b),sizeof(c)*(d))
   #define FOR(i,a,b) for(register int i=(a);i<=(b);++i)
   #define DOR(i,a,b) for(register int i=(a);i>=(b);--i)
   #define EDGE(g,i,u,x) for(register int (i)=(g).h[(u)],(x)=(g).v[(i)];(i);(i)=(g).nxt[(i)],(x)=(g).v[(i)])
   #define main Main();signed main(){ios::sync_with_stdio(0);cin.tie(0);return Main();}signed Main
   using namespace std;
   constexpr int N=1e6+10;
   int T,n,m,idx;
   int a[N],b[N],dl[N],dr[N],dep[N],head[N];
   struct CFS{
   	int tot,h[N],v[N],nxt[N];
   	void Clear(int n){
   		tot=0,RCL(h,0,int,n+5);
   	}
   	void att(int U,int V){
   		v[++tot]=V,nxt[tot]=h[U],h[U]=tot;
   	}
   }g;
   struct DSU{
   	int fa[N],siz[N];
   	int operator [](int i){
   		return get(i);
   	}
   	void Init(int n){
   		FOR(i,1,n)fa[i]=i,siz[i]=1;
   	}
   	int get(int x){
   		return fa[x]^x?fa[x]=get(fa[x]):x;
   	}
   	bool Check(int u,int v){
   		return get(u)==get(v);
   	}
   	bool Merge(int u,int v){
   		int x=get(u),y=get(v);
   		if(x==y)return 0;
   		if(siz[x]>siz[y])swap(x,y);
   		return fa[y]=x,siz[x]+=siz[y],head[x]|=head[y],1;
   	}
   }D;
   void Build(int u){
   	dl[u]=++idx;
   	EDGE(g,i,u,v)dep[v]=dep[u]+1,Build(v);
   	dr[u]=idx;
   }
   bool Rela(int u,int v){
   	return dl[v]<=dl[u]&&dl[u]<=dr[v];
   }
   int Dis(int u,int v){
   	if(!D.Check(u,v))return INF;
   	if(Rela(u,v))return dep[u]-dep[v];
   	return Rela(b[head[D[u]]],v)?dep[u]+1+(dep[b[head[D[u]]]]-dep[v]):INF;
   }
   bool Check(int x){
   	int tim=m;
   	DOR(i,n,1){
   		while(tim&&Dis(a[i],tim)>x)--tim;
   		if(!tim)return 0;
   	}return 1;
   }
   signed Cmain(){
   	cin>>n>>m,idx=0,D.Init(m),g.Clear(m),RCL(head,0,int,m+5);
   	FOR(i,1,n)cin>>a[i];
   	FOR(i,1,m)cin>>b[i];
   	FOR(i,1,m){
   		if(D.Merge(i,b[i]))g.att(b[i],i);
   		else head[D[i]]=i;
   	}
   	FOR(i,1,m)if(D[i]==i)dep[head[i]]=0,Build(head[i]);
   	int ans=-1;
   	for(int l=0,r=m,mid=l+r>>1;l<=r;mid=l+r>>1)Check(mid)?ans=mid,r=mid-1:l=mid+1;
   	cout<<ans<<endl;
   	return 0;
   }
   signed main(){
   	for(cin>>T;T;--T)Cmain();
   	return 0;
   }
   ```

2. 把环上某个点连向父节点的边砍掉，重新建树，就可以转换为新树上的距离。

   ```cpp
   #include<bits/stdc++.h>
   #define INF 0x3f3f3f3f
   #define ll long long
   #define max(a,b) ((a)<(b)?(b):(a))
   #define min(a,b) ((a)>(b)?(b):(a))
   #define tomax(a,b) ((a)=max((a),(b)))
   #define tomin(a,b) ((a)=min((a),(b)))
   #define RCL(a,b,c,d) memset((a),(b),sizeof(c)*(d))
   #define FOR(i,a,b) for(register int i=(a);i<=(b);++i)
   #define DOR(i,a,b) for(register int i=(a);i>=(b);--i)
   #define EDGE(g,i,u,x) for(register int (i)=(g).h[(u)],(x)=(g).v[(i)];(i);(i)=(g).nxt[(i)],(x)=(g).v[(i)])
   #define main Main();signed main(){ios::sync_with_stdio(0);cin.tie(0);return Main();}signed Main
   using namespace std;
   constexpr int N=1e6+10;
   int T,n,m,idx,cnt;
   int a[N],b[N],d[N],dl[N],dr[N],id[N],num[N],rt[N],siz[N],dep[N],head[N];
   queue<int> q;
   struct CFS{
   	int tot,h[N],v[N],nxt[N];
   	void Clear(int n){
   		tot=0,RCL(h,0,int,n+5);
   	}
   	void att(int U,int V){
   		v[++tot]=V,nxt[tot]=h[U],h[U]=tot;
   	}
   }g;
   struct DSU{
   	int fa[N],siz[N];
   	int operator [](int i){
   		return get(i);
   	}
   	void Init(int n){
   		FOR(i,1,n)fa[i]=i,siz[i]=1,head[i]=0;
   	}
   	int get(int x){
   		return fa[x]^x?fa[x]=get(fa[x]):x;
   	}
   	bool Check(int u,int v){
   		return get(u)==get(v);
   	}
   	bool Merge(int u,int v){
   		int x=get(u),y=get(v);
   		if(x==y)return 0;
   		if(siz[x]>siz[y])swap(x,y);
   		return fa[y]=x,siz[x]+=siz[y],head[x]|=head[y],1;
   	}
   }D;
   void Build(int u){
   	dl[u]=++idx;
   	EDGE(g,i,u,v)if(!d[v])rt[v]=rt[u],dep[v]=dep[u]+1,Build(v);
   	dr[u]=idx;
   }
   void Circle(int u){
   	id[u]=cnt,++siz[cnt];
   	if(!id[b[u]])num[b[u]]=num[u]+1,Circle(b[u]);
   }
   bool Rela(int u,int v){
   	return dl[v]<=dl[u]&&dl[u]<=dr[v];
   }
   int Dis(int u,int v){
   	if(!D.Check(u,v))return INF;
   	if(Rela(u,v))return dep[u]-dep[v];
   	return rt[v]!=v?INF:num[v]-num[rt[u]]+(num[v]>=num[rt[u]]?0:siz[id[rt[u]]])+dep[u]-dep[rt[u]];
   }
   bool Check(int x){
   	int tim=m;
   	DOR(i,n,1){
   		while(tim&&Dis(a[i],tim)>x)--tim;
   		if(!tim)return 0;
   	}return 1;
   }
   signed Cmain(){
   	cin>>n>>m,idx=0,cnt=0,D.Init(m),g.Clear(m),RCL(d,0,int,m+5),RCL(id,0,int,m+5);
   	FOR(i,1,n)cin>>a[i];
   	FOR(i,1,m)cin>>b[i],++d[b[i]];
   	FOR(i,1,m){
   		g.att(b[i],i);
   		if(!D.Merge(i,b[i]))head[D[i]]=i;
   	}
   	FOR(i,1,m)if(!d[i])q.push(i);
   	while(!q.empty()){
   		int u=q.front();q.pop();
   		if(!(--d[b[u]]))q.push(b[u]);
   	}
   	FOR(i,1,m)if(d[i])rt[i]=i,Build(i);
   	FOR(i,1,m)if(D[i]==i)dep[head[i]]=0,Build(head[i]);
   	FOR(i,1,m)if(D[i]==i)siz[++cnt]=0,num[head[i]]=1,Circle(head[i]);
   	int ans=-1;
   	for(int l=0,r=m,mid=l+r>>1;l<=r;mid=l+r>>1)Check(mid)?ans=mid,r=mid-1:l=mid+1;
   	cout<<ans<<endl;
   	return 0;
   }
   signed main(){
   	for(cin>>T;T;--T)Cmain();
   	return 0;
   }
   ```

---

## 总结

这题最难的部分在于二分答案的检验过程与基环森林的构建，攻克后就十分简单，十分适合练手。

---

## 作者：david0911 (赞：0)

由于一次操作是对于一个下标集合，即对多个数同时操作，那么设位置 $i$ 要被操作 $c_i$ 次，答案应当为 $\max\limits_i c_i$。

要最小化这个式子，套路地想到二分一个数的最大操作次数。

观察这个操作，如果将 $x$ 向 $b_x$ 连边，就会得到内向基环树森林。于是从一个数变化到另一个数的操作次数就是两点在内向基环树上的距离。

这里需要处理一下基环树。分类讨论一下祖先后代关系和环上的情况即可 $O(1)$ 求距离，注意判断不可达的情况。

在二分判定中，贪心地将当前的数变成在操作次数限制之内最小的可达的数。可以在值域上用指针扫来实现。由于指针单调不降，一次判定是 $O(m)$ 的。

于是复杂度是 $O(m\log m)$。

---

## 作者：Shunpower (赞：0)

这太 CNOI 了。

---------------

显然考虑 $i\to b_i$ 地连边，造出一棵内向基环树。那么每个 $a_i$ 就相当于基环树上的一枚棋子，我们每次可以选择一堆棋子往前移动一步。

考虑转化一下需要的步数。我们把贡献摊开，显然就是所有棋子中的最大步数，进一步地想到可以二分这个步数，于是我们只需判定能否在 $x$ 步以内将序列变成单调不降的。

因为限制已经摊开，所以显然应该从前往后贪心，每次在步数内走向一个最小的位置，但要比前一个大。

使用非常麻烦的数据结构可以做，但是常数很大，而且很难写。

考虑我们不用数据结构来维护可达性，转而维护值域。那么我们可以双指针，我们从上一个位置的值开始往后扫，扫到一个值如果可以在步数之内到达就选用，以此类推。如果 $m$ 个数不够用了就说明步数不够。

于是只需快速求内向基环树上两点距离，环和树拆开随便写一下就可以了。

```cpp
int tc;
int n,m;
int a[N],b[N];
vector <int> p[N],anp[N];
int rt[N];
bool onloop[N],vis[N];
int f[N];
int len[N],pos[N],dep[N],in[N];
int dfn[N],siz[N];
int t;
int find(int x){return f[x]=(f[x]==x?f[x]:find(f[x]));}
void dfs(int x,int fa,int r){
	rt[x]=r;
	t++;
	dfn[x]=t;
	siz[x]=1;
	for(auto y:anp[x]){
		if(onloop[y]||y==fa) continue;
		dep[y]=dep[x]+1;
		dfs(y,x,r);
		siz[x]+=siz[y];
	}
}
int dis(int x,int y){
	if(find(x)!=find(y)) return 1e9;
	if(onloop[x]&&onloop[y]){
		return (pos[y]-pos[x]>=0?pos[y]-pos[x]:len[find(x)]+pos[y]-pos[x]);
	}
	else if(onloop[x]) return 1e9;
	else if(onloop[y]){
		return dep[x]+dis(rt[x],y);
	}
	else{
		if(dfn[x]<dfn[y]||dfn[x]>=dfn[y]+siz[y]) return 1e9;
		return dep[x]-dep[y];
	}
}
bool check(int x){
	int j=1;
	fr1(i,1,n){
		while(j<=m&&dis(a[i],j)>x) j++;
		if(j>m) return 0;
	}
	return 1;
}
void solve(){
	cin>>n>>m;
	fr1(i,1,m) p[i].clear(),anp[i].clear();
	fr1(i,1,m) f[i]=i;
	fr1(i,1,m) onloop[i]=1,in[i]=0,vis[i]=0,dep[i]=0;
	fr1(i,1,n) cin>>a[i];
	fr1(i,1,m) cin>>b[i];
	fr1(i,1,m){
		f[find(i)]=find(b[i]);
		p[i].pb(b[i]);
		anp[b[i]].pb(i);
		in[b[i]]++;
	}	
	queue <int> q;
	fr1(i,1,m) if(!in[i]) q.push(i);
	while(!q.empty()){
		int x=q.front();
		q.pop();
		onloop[x]=0;
		for(auto y:p[x]){
			in[y]--;
			if(!in[y]) q.push(y);
		}
	}
	fr1(i,1,m){
		if(onloop[i]&&!vis[i]){
			vector <int> loop;
			int x=i;
			do{
				loop.pb(x);
				for(auto y:p[x]){
					if(onloop[y]){
						x=y;
						break;
					}
				}
			}while(x!=i);
			len[find(i)]=loop.size();
			fr1(j,0,(int)loop.size()-1) pos[loop[j]]=j;
			for(auto j:loop) dfs(j,j,j);
			for(auto j:loop) vis[j]=1;
		}
	}
	int l=0,r=m,ans=-1;
	while(l<=r){
		int mid=(l+r>>1);
		if(check(mid)) ans=mid,r=mid-1;
		else l=mid+1;
	}
	cout<<ans<<'\n';
}
```

---

## 作者：irris (赞：0)

> 数据结构 / 双指针 / 二分答案 / 贪心 / 基环树

首先不能独立考虑每一轮操作，所以考虑二分答案，我们要判定 $k$ 轮是否合法。

首先要贪心。依次考虑 $1 \leq i \leq n$，找到 $a_1$ 的最小值，然后是 $a_2 \geq a_1$ 的最小值......

建立 $i \to b_i$ 的关系，形成基环树，我们可以拆分成 $\mathcal O(1)$ 条链。愚蠢的做法是主席树查询最小值，$\mathcal O(n\log n\log m)$。

事实上 $m$ 不算太大，那么就可以依次 **在值域上做双指针**，找到下一个最小值。问题变成了 $\mathcal O(n\log m)$ 次判定 $u \to v$ 的最小步数，具体地：

- 如果这是一棵树，那么可以通过 dfn 序和子树大小判断 $u$ 是否在 $v$ 子树内，如果是，那么 $dep_u - dep_v$ 即为答案。
- 考虑基环树的做法，加入走到环后的分类讨论即可。

---

## 作者：hh弟中弟 (赞：0)

简单分析后，就是求最小的最大操作次数，因为别的操作可以在它操作时一起带上，直接二分。\
考虑怎么 check 这个序列的单调性，比较直接的方法是倍增，然后找到比上一位大的最小的数，但是这个根本不知道该怎么维护啊，并且也不太像 $\mathcal{O}(n\log^2n)$ 的复杂度。\
发现对于最后序列的值域是已知的，考虑直接用值域来刻画这个答案，直接从小到大枚举每一位的最后数字 $x$，范围在 $[1,m]$，如果当前位可以在 $mid$ 次操作内到达 $x$，就可以，否则 $x\gets x+1$。\
现在只剩求 $dis(x,y)$ 了，给这个操作建个图，是内向基环树森林，内向不太好处理距离，考虑建个反边，这样就成了环上的每个节点挂了一棵向外的子树，此时既可以统计连通性，又可以统计距离了。\
对于环上的距离，直接求即可，对于链上的距离，检查祖先关系后直接深度相减即可，时间复杂度 $\mathcal{O}(n\log n)$。
```cpp
#include<bits/stdc++.h>
#define fi first
#define se second
#define pii std::pair<int,int>
#define eb emplace_back
#define pb push_back
typedef long long ll;
typedef unsigned long long ull;
std::mt19937 myrand(std::chrono::high_resolution_clock::now().time_since_epoch().count());
inline int R(int n){return myrand()%n+1;}
inline int read(){char ch=getchar();int x=0,f=1;for(;ch<'0'||ch>'9';ch=getchar())if(ch=='-')f=-1;for(;ch>='0'&&ch<='9';ch=getchar())x=(x<<3)+(x<<1)+(ch^48);return x*f;}
const int N=1e6+10,mod=998244353,inf=1e9;
inline void Min(int &x,int y){if(x>y)x=y;}
inline void Max(int &x,int y){if(x<y)x=y;}
bool vis[N];
int n,m,a[N],b[N],in[N],rt,fa[N],bl[N],man;
int dfn[N],dn,ri[N],dep[N],id[N],len[N];
std::vector<int> e[N],g[N];
inline void topo(){
	std::queue<int> q;
	for(int i=1;i<=m;++i)if(!in[i])q.push(i);
	while(!q.empty()){
		int x=q.front();q.pop();vis[x]=1;
		for(int v:e[x]){
			if(!--in[v])q.push(v);
		}
	}
}
inline void dfs(int x){
	dfn[x]=++dn;fa[x]=rt;
	for(int v:g[x]){
		if(!vis[v]&&!dfn[v])dep[v]=dep[x]+1,dfs(v);
	}
	ri[x]=dn;
}
inline void search(int x){
	id[x]=++len[man];bl[x]=man;
	for(int v:e[x]){
		if(vis[v]&&!bl[v])search(v);
	}
}
inline int dis_huan(int x,int y){
	if(bl[x]!=bl[y])return inf;
	if(id[y]<id[x])return len[bl[x]]-(id[x]-id[y]);
	return id[y]-id[x];
}
inline int dis_lian(int x,int y){
	if(dfn[x]>=dfn[y]&&dfn[x]<=ri[y]){
		return dep[x]-dep[y];
	}return inf;
}
inline int dis(int x,int y){
	if(vis[x]&&vis[y])return dis_huan(x,y);
	if(vis[x]&&!vis[y])return inf;
	if(!vis[x]&&vis[y])return dep[x]+dis_huan(fa[x],y);
	if(!vis[x]&&!vis[y])return dis_lian(x,y);
}
inline bool check(int mid){
	int now=1;
	for(int i=1;i<=n;++i){
		while(now<=m){
			if(dis(a[i],now)<=mid)break;
			now++;
		}
		if(now>m)return 0;
	}
	return true;
}
signed main(){
    // freopen("in.in","r",stdin);freopen("out.out","w",stdout);
    std::ios::sync_with_stdio(false);std::cin.tie(0);std::cout.tie(0);
    int T=read();
    while(T--){
	    n=read(),m=read();
	    for(int i=1;i<=n;++i)a[i]=read();
	    for(int i=1;i<=m;++i)b[i]=read();
	   	dn=0;rt=0;man=0;
	    for(int i=1;i<=m;++i)e[i].clear(),g[i].clear(),in[i]=0,dfn[i]=0,vis[i]=0,dep[i]=0,ri[i]=0,id[i]=0,fa[i]=0,len[i]=0,bl[i]=0;
	    for(int i=1;i<=n;++i)e[a[i]].eb(b[a[i]]),g[b[a[i]]].eb(a[i]),in[b[a[i]]]++;	
	    for(int i=1;i<=m;++i)e[b[i]].eb(b[b[i]]),g[b[b[i]]].eb(b[i]),in[b[b[i]]]++;
	    topo();
		for(int i=1;i<=m;++i)vis[i]=!vis[i];
	    for(int i=1;i<=m;++i)if(vis[i]&&!dfn[i])dfs(rt=i);
	    for(int i=1;i<=m;++i)if(vis[i]&&!bl[i]){man++;search(i);}
	    int l=0,r=m,ans=-1;
		while(l<=r){
			int mid=l+r>>1;
			if(check(mid))ans=mid,r=mid-1;
			else l=mid+1;
		}
		std::cout<<ans<<'\n';
    }
}
```

---

## 作者：tzl_Dedicatus545 (赞：0)

irris /bx/bx/bx

把图建出来，$i\to b_i$。

二分答案，判定是否可以在 $k$ 步以内让最终的 $a'_i$ 单调递增。

普通的思路是用一些重科技数据结构，维护往上 $k$ 步的最小值，判断是否递增，但这样是 $\Theta(n\log^2 n)$ 的，而且常数巨大。

但是我们注意到值域 $m$ 是非常小的！而且最终的序列具有单调性！这其实我们维护一个指针 $p$，代表当前最小取值。

我们只需判断 $\Theta((n+m)\log n)$ 次 $i$ 到 $j$ 的距离是否小于 $k$ 即可。这显然可以 $\Theta(1)$。

总复杂度 $\Theta((n+m)\log n)$

---

## 作者：TernaryTree (赞：0)

并不是很难的 *2800？但是基环树处理一遍写对真的爽。

先假设每个 $a_i$ 进行操作的次数为 $c_i$，则这种操作方法的答案是 $\max c_i$。最小化最大值，考虑二分。转为判定 $mid$ 步之内能否完成。

套路式地，$i\to b_i$ 连边得到一个内向基环树森林，并将 $a_i$ 扔到对应的点上。一次操作即为沿当前点的出边走过去。

大概会有个贪心的思路，即 $a_1$ 走到 $mid$ 步以内编号最小的点，$a_2$ 走到 $mid$ 步以内编号 $\ge a_1$ 且最小的点，然后你理所当然地想到了数据结构。事实上大概是可以做的，但是会不可避免地多几只 $\log$ 再加上二分的一只，你巨大长的代码喜提 TLE。

但是注意到值域是基环树结点数即为 $m$，于是想到拿一个指针出来，暴力匹配。具体地，令指针 $p$ 初始时为 $1$，遍历 $i\in [1,n]$，若 $dis(i\to p)\le mid$ 则匹配成功，处理下一个 $i$；否则 $p\gets p+1$ 继续尝试匹配。若某次无法匹配则判定失败，否则成功。因为 $p$ 移动不超过 $m$ 次所以该判定方法时间复杂度 $\Theta(n+m)$。

接下来只需要解决外向基环树上 $dis(u\to v)$ 的问题。首先，若 $u,v$ 不在同一连通块内无解；否则，不妨将所有环边断开，得到一个森林，若 $u,v$ 在同一棵树内且 $v$ 是 $u$ 祖先，答案为 $dep_u-dep_v$；否则 $v$ 必须是一棵树的根，即在环上。找到 $u$ 所在树的根，其与 $v$ 都在环上，环上任意两点距离通过预处理容易得出，再加上 $dep_u$ 即可。至于判定祖先，等价于判断是否在子树内，使用 dfn 序即可。

```cpp
#include <bits/stdc++.h>
#define int long long
#define fs first
#define sc second
#define ls (u << 1)
#define rs (u << 1 | 1)
#define mid ((l + r) >> 1)
#define lc ls, l, mid
#define rc rs, mid + 1, r
#define rep(i, l, r) for (int i = (l); i <= (r); ++i)
#define per(i, r, l) for (int i = (r); i >= (l); --i)
#define gc getchar
#define pc putchar

using namespace std;
using pii = pair<int, int>;
using vi = vector<int>;

const int maxn = 1e6 + 10;
const int inf = 1e18;
const bool multidata = 1;

int read() {
	int x = 0, f = 1; char c = gc();
	while (c < '0' || c > '9') { if (c == '-') f = -f; c = gc(); }
	while (c >= '0' && c <= '9') x = x * 10 + c - '0', c = gc();
	return x * f;
}

void write(int x) {
	if (x < 0) pc('-'), x = -x;
	if (x < 10) return void (pc(x + '0'));
	write(x / 10), pc(x % 10 + '0');
}

int n, m;
int a[maxn], b[maxn];
int deg[maxn];
int col[maxn], ind[maxn], cnt;
int len[maxn];
int dfn[maxn], siz[maxn], dep[maxn], idx;
int vis[maxn], rt[maxn], top[maxn];
vector<int> g[maxn];

void dfs1(int u, int c) {
	col[u] = c, vis[u] = rt[u] = 1, ind[u] = len[c]++;
	if (!vis[b[u]]) dfs1(b[u], c);
}

void dfs2(int u, int d, int t) {
	dep[u] = d, siz[u] = 1, top[u] = t, dfn[u] = ++idx;
	for (int v : g[u]) {
		col[v] = col[u];
		dfs2(v, d + 1, t);
		siz[u] += siz[v];
	}
}

int dis(int u, int v) {
	if (col[u] != col[v]) return inf;
	if (top[u] == top[v] && dfn[v] <= dfn[u] && dfn[u] <= dfn[v] + siz[v] - 1) {
		return dep[u] - dep[v];
	} else {
		if (!rt[v]) return inf;
		return dep[u] + (ind[v] - ind[top[u]] + len[col[v]]) % len[col[v]];
	}
}

bool check(int x) {
	int p = 1;
	rep(i, 1, n) {
		while (p <= m) {
			if (dis(a[i], p) <= x) break;
			++p;
		}
		if (p > m) return 0;
	}
	return 1;
}

void fake_main() {
	n = read(), m = read();
	rep(i, 1, m) deg[i] = len[i] = vis[i] = rt[i] = 0;
	rep(i, 1, m) g[i].clear();
	cnt = idx = 0;
	rep(i, 1, n) a[i] = read();
	rep(i, 1, m) b[i] = read(), ++deg[b[i]];
	queue<int> q;
	rep(i, 1, m) if (!deg[i]) q.push(i), vis[i] = 1;
	while (!q.empty()) {
		int u = q.front(); q.pop();
		--deg[b[u]];
		if (!deg[b[u]]) q.push(b[u]), vis[b[u]] = 1;
	}
	rep(i, 1, m) if (!vis[i]) ++cnt, dfs1(i, cnt);
	rep(i, 1, m) if (!(rt[i] && rt[b[i]])) g[b[i]].push_back(i);
	rep(i, 1, m) if (rt[i]) dfs2(i, 0, i);
	int l = 0, r = m;
	if (!check(m)) return void (puts("-1"));
	while (l < r) {
		if (check(mid)) r = mid;
		else l = mid + 1;
	}
	write(l), pc('\n');
}

signed main() {
	int T = multidata ? read() : 1;
	while (T--) fake_main();
	return 0;
}

```

---

