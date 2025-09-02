# [JOI 2023 Final] 训猫 / Cat Exercise

## 题目描述

有 $N$ 个猫塔，编号从 $1$ 到 $N$。塔 $i$ 的高度为 $P_i$（$1 \le i \le N$）。这些塔的高度是 $1$ 到 $N$ 之间的不同整数。共有 $N - 1$ 对相邻的塔。对于每个 $j$（$1 \le j \le N - 1$），塔 $A_j$ 和塔 $B_j$ 是相邻的。最开始，可以通过从一个塔移动到相邻的塔，来从一个塔到达任何其他塔。

最开始，一只猫待在高度为 $N$ 的塔上。

然后我们进行**猫运动**。在猫运动中，我们反复选择一个塔并在其上放置一个障碍。然而，我们不能在已经放置障碍的塔上再放置障碍。在这个过程中，将发生以下情况：

- 如果猫不在所选的塔上，什么也不会发生。
- 如果猫在所选的塔上，并且所选塔的每个相邻塔上都有障碍，猫运动将结束。
- 否则，在猫可以通过从塔移动到相邻塔而不受障碍影响到达的塔中，猫将移动到除当前塔外最高的塔。过程中，猫会选择从塔移动到相邻塔的步数最少的路线。

给定塔的高度信息和相邻塔的对，编写程序计算在适当放置障碍的情况下，猫从塔移动到相邻塔的最大可能移动次数之和。

## 说明/提示

## 样例

### 样例 1

如果我们按以下方式进行猫运动，猫总共移动 3 次。

- 我们在塔 1 上放置一个障碍。猫不移动。
- 我们在塔 2 上放置一个障碍。猫从塔 2 移动到塔 3。然后，猫从塔 3 移动到塔 4。
- 我们在塔 4 上放置一个障碍。猫从塔 4 移动到塔 3。
- 我们在塔 3 上放置一个障碍。然后猫运动结束。

由于没有办法进行猫运动，使得猫从塔移动到相邻塔的次数大于或等于 4，因此输出 3。

此样例输入满足子任务 1、2、3、4、5、7 的约束。

### 样例 2

此样例输入满足子任务 4、6、7 的约束。

## 约束

- $2 \le N \le 2\times 10^5$。
- $1 \le P_i \le N$ ($1 \le i \le N$)。
- $P_i 
eq P_j$ ($1 \le i < j \le N$)。
- $1 \le A_j < B_j \le N$ ($1 \le j \le N - 1$)。
- 最开始，可以通过从一个塔移动到相邻塔，来从一个塔到达任何其他塔。
- 给定的值都是整数。

## 子任务

1. (7 分) $A_i = i, B_i = i + 1$ ($1 \le i \le N - 1$)，$N \le 16$。
2. (7 分) $A_i = i, B_i = i + 1$ ($1 \le i \le N - 1$)，$N \le 300$。
3. (7 分) $A_i = i, B_i = i + 1$ ($1 \le i \le N - 1$)，$N \le 5 000$。
4. (10 分) $N \le 5 000$。
5. (20 分) $A_i = i, B_i = i + 1$ ($1 \le i \le N - 1$)。
6. (23 分) $A_i =\left\lfloor\frac{i+1}2\right\rfloor, B_i = i + 1$ ($1 \le i \le N - 1$)。这里 $\\lfloor x \\rfloor$ 是小于或等于 $x$ 的最大整数。
7. (26 分) 无额外约束。

题面翻译由 ChatGPT-4o 提供。

## 样例 #1

### 输入

```
4
3 4 1 2
1 2
2 3
3 4
```

### 输出

```
3
```

## 样例 #2

### 输入

```
7
3 2 7 1 5 4 6
1 2
1 3
2 4
2 5
3 6
3 7
```

### 输出

```
7
```

# 题解

## 作者：liangbowen (赞：13)

[problem](https://www.luogu.com.cn/problem/P9352) & [blog](https://www.cnblogs.com/liangbowen/p/17571984.html)。

HerryHuang 的 DP 专题中最喜欢的一题，抢第一篇题解 /fendou。

关于题意：只有往猫那里扔路障，猫才会动，否则只会原地坐牢。猫如果要走动，是一下子走到最高点，而不是慢慢挪动。

---

假设猫在 $u$ 点。现在往 $u$ 扔路障，猫会跑去最高点，然后他**无法返回到** $u$ **的其他子树了**，因为 $u$ 被堵上了。

实际上，每次只给猫留一条活路，猫的行动点就是固定的。那么只需找到子树中能移动的次数最大的子树，然后过去即可。

显然可以 DP。设 $dp_u$ 表示以 $u$ 为根的子树中，猫在 $u$ 点，可以走的最长距离。令子树中点权最大的点是 $pos_u$，那么 $dp_u=\max\{dp_{pos_v}+\operatorname{dist}(u,v)\}$。

但有一个潜在条件是 $a_u>a_{pos_v}$，而 DP 又要先枚举小的 $a_u$，再枚举大的。这意味着 DP 顺序会跳来跳去，直接失去了正确性。

考虑连边 $(a_u,a_v)$。那么顺着枚举 $u=1\sim n$ 就是正确的。$pos_u$ 相当于找一个遍历过的最大的 $v$，上并查集即可，具体看代码。

[代码](https://www.luogu.com.cn/paste/vw3vxoyy)，时间复杂度 $O(n\log n)$。记得开 `long long`。

---

## 作者：lottle1212 (赞：11)

# [[JOI 2023 Final] Cat Exercise](https://www.luogu.com.cn/problem/P9352) 题解

根据题意，设开始时猫在最高点 $u$ 上。当在 $u$ 放了一个障碍之后，则猫会跑次高点上。**容易发现，当猫进入** $u$ **的其中一个子树后，就无法返回到** $u$ **的其他子树了，因为** $u$ **被堵上了。**

那么，给猫留下一条活路之后，猫的行走路线就一定是固定的了。那么，只需要找到子树中能移动次数最多的子树，然后让猫过去即可。

尝试使用 $\text{DP}$ 进行求解。设 $dp_{u}$ 为以 $u$ 为根的子树中，猫从 $u$ 点出发可以走的最长距离。令 $u$ 的子树中最高的节点为 $pos_u$，$v$ 为 $u$ 的子节点，则 $dp_{u} = \max\{dp_{pos_{v}} + \operatorname{dist(u, v)}\}$。

接下来考虑如何实现。**由于猫行走到的节点的高度呈单调递减**，则必须先转移较小的 $v$，才能对较大的 $u$ 进行转移。那么我们可以考虑在连边时连接 $p_u$ 和 $p_v$，这样我们从 $1$ 至 $n$ 对每一个节点进行转移，就一定可以满足条件 $p_u > p_{pos_v}$。对于 $pos_v$ 我们可以用**并查集**来维护，对于 $\operatorname{dist}$ 函数，我们使用 $\text{lca}$ 进行求解即可。

**Code**

```cpp
#include <iostream>
using namespace std;
typedef long long ll;
const ll mlg = 20, mxn = 2e5;
const ll lgN = mlg + 10, N = mxn + 10;
ll n, f[N], p[N], dp[N], head[N], cnt, fa[N][lgN], dep[N];
struct Edge { ll nxt, to; } e[N << 1];
void add(ll u, ll v) { e[++ cnt] = {head[u], v}; head[u] = cnt; }
ll rd() {
	ll sum = 0; bool f = 0; char ch = getchar();
	while (ch < '0' || ch > '9') f |= ch == '-', ch = getchar();
	while (ch >= '0' && ch <= '9') sum = (sum << 1) + (sum << 3) + (ch ^ 48), ch = getchar();
	return f ? -sum : sum;
}
void dfs(ll u, ll pre) {
	dep[u] = dep[pre] + 1, fa[u][0] = pre;
	for (ll i = 1; i <= mlg; ++ i) fa[u][i] = fa[fa[u][i - 1]][i - 1];
	for (ll i = head[u], v; i; i = e[i].nxt) {
		v = e[i].to;
		if (v == pre) continue;
		dfs(v, u);
	}
}
ll lca(ll u, ll v) {
	if (dep[u] < dep[v]) swap(u, v);
	for (ll i = mlg; ~ i; -- i)
		if (dep[fa[u][i]] >= dep[v])
			u = fa[u][i];
	if (u == v) return u;
	for (ll i = 20; ~ i; -- i)
		if (fa[u][i] != fa[v][i])
			u = fa[u][i], v = fa[v][i];
	return fa[u][0];
}//lca
ll get_fa(ll x) { return x == f[x] ? x : f[x] = get_fa(f[x]); }//并查集
ll dis(ll u, ll v) { return dep[u] + dep[v] - (dep[lca(u, v)] << 1); }//求距离
signed main() {
	n = rd();
	for (ll i = 1; i <= n; ++ i) f[i] = i, p[i] = rd();
	for (ll i = 1, u, v; i < n; ++ i) u = p[rd()], v = p[rd()], add(u, v), add(v, u);
	dfs(1, 0);
	for (ll u = 1; u <= n; ++ u)
		for (ll i = head[u], v; i; i = e[i].nxt) {
			v = get_fa(e[i].to);
			if (v < u) f[v] = u, dp[u] = max(dp[u], dp[v] + dis(u, v));
		}//如上文所述
	printf("%lld\n", dp[n]);
	return 0;
}
```


---

## 作者：Delusions_grandeur (赞：2)

注意到猫咪到达的点高度只会越来越低，因为每次会堵住最高的点。

进一步得到 $u$ 出发能到的点 $v$ 都保证：路径 $(u, v)$ 上没有比 $u$ 点权更大的。 

为了一个好的 DP 顺序，尝试以高度进行 DP；令 $u = p_u$，按 $1 \to n$ 的顺序 DP，每次 BFS 找到可以到达的最大的 $v$，直接做是 $O(n^2)$ 的。

一个经典的技巧是，确定了 $v$ 能转移到 $u$ 后，把 $v$ 并入 $u$ 的并查集，那么每次只需要遍历 $u$ 的出边 $(u, v)$，取并查集中最大的点，若小于 $u$ 则转移。

可以直接取最大点的原因是 DP 顺序为 $1 \to n$，若最大点比 $u$ 大则必然不能到达 $v$。

这样做是 $O(m + n\log n)$ 的，瓶颈在于求 LCA。

---
```cpp
#include <bits/stdc++.h>
#define rep(i, a, b) for (int i = (a); i <= (b); i ++)
#define dep(i, a, b) for (int i = (a); i >= (b); i --)
using namespace std;
const int N = 2e5 + 5;

char buf[1 << 23], *p1 = buf, *p2 = buf;
#define getchar() (p1 == p2 && (p2 = (p1 = buf) + fread(buf, 1, 1 << 21, stdin), p1 == p2) ? EOF : *p1 ++)
int read() {
  int s(0), f(1);
  char ch(getchar());
  while (!isdigit(ch)) f = ch == '-' ? -1 : 1, ch = getchar();
  while (isdigit(ch)) s = (s << 3) + (s << 1) + (ch ^ 48), ch = getchar();
  return s * f;
}

int n, p[N], dep[N], f[N][21], fa[N];
vector <int> G[N];
long long dp[N];

void pre(int u, int fu) {
  dep[u] = dep[fu] + 1, f[u][0] = fu;
  rep(i, 0, 19) f[u][i + 1] = f[f[u][i]][i];
  for (auto v : G[u]) if (v ^ fu) pre(v, u);
}

int Lca(int x, int y) {
  if (dep[x] < dep[y]) swap(x, y);
  dep(i, 20, 0) if (dep[f[x][i]] >= dep[y]) x = f[x][i];
  if (x == y) return x;
  dep(i, 20, 0) if (f[x][i] != f[y][i]) x = f[x][i], y = f[y][i];
  return f[x][0];
}

int dis(int u, int v) {return dep[u] + dep[v] - (dep[Lca(u, v)] << 1);}

int getf(int x) {return fa[x] == x ? x : fa[x] = getf(fa[x]);}

signed main() {
  n = read();
  rep(i, 1, n) p[i] = read(), fa[i] = i;
  rep(i, 2, n) {
    int u = p[read()], v = p[read()];
    G[u].push_back(v), G[v].push_back(u);
  }
  pre(1, 0);
  rep(u, 1, n) for (auto v : G[u]) {
    v = getf(v);
    if (v < u) fa[v] = u, dp[u] = max(dp[u], dp[v] + dis(u, v));
  }
  printf("%lld\n", dp[n]);
  return 0;
}
```

---

## 作者：MspAInt (赞：1)

[题目传送门](https://www.luogu.com.cn/problem/P9352)

第一次在 linux 上写题！

看完题面第一反应是搞一个最优的扔障碍策略，然后手玩了半个小时无果，糗大了。

考虑 dp。$dp_u$ 表示从 $u$ 出发一路堵能跑的最远距离。把 $u$ 堵上了喵喵就会跑到能到的最高节点 $pos_u$，这个点是固定的，可以从儿子 $v$ 的 $pos_v$ 得到。于是 $dp_u=\underset{v\in son_u}{\max}\{dp_{pos_v}+\operatorname{dist}(u,pos_v)\}$。

就这样吗？

喵喵是可以在树上反复横跳的，而且**显然其访问的点权序列必须单调下降**，所以以上都假了。

和 CF87D 类似的，考虑改变 dp 方式。我们对点权建边，按照点权从小到大用上面的方程转移，这样就能保证转移合法。取最高点有些麻烦，这里我参考了题解区的并查集做法，把一个集里最大的点权作为根，连带着父亲都考虑到了。最后把所有相邻点加入到 $u$ 的并查集里继续 dp。

答案就是 $dp_n$。

Code:（$\Theta(n\log n)$）

```cpp
#include<bits/stdc++.h>
#define LL long long
using namespace std;
const int N=2e5+10;
int n,h[N],f[N][19],dep[N],fa[N];
LL dp[N];
vector<int>e[N];
int getfa(int k){
	return k==fa[k]?k:(fa[k]=getfa(fa[k]));
}
void merge(int x,int y){
	if(x>y)swap(x,y);
	fa[x]=y;
	return;
}
void dfs(int u){
	dep[u]=dep[f[u][0]]+1;
	for(int i=1;(1<<i)<=dep[u];i++)
		f[u][i]=f[f[u][i-1]][i-1];
	for(int v:e[u])
		if(v!=f[u][0])f[v][0]=u,dfs(v);
	return;
}
int lca(int x,int y){
	if(dep[x]<dep[y])swap(x,y);
	for(int i=18;i>=0;i--)
		if(dep[f[x][i]]>=dep[y])x=f[x][i];
	if(x==y)return x;
	for(int i=18;i>=0;i--)
		if(f[x][i]!=f[y][i])x=f[x][i],y=f[y][i];
	return f[x][0];
}
int dis(int x,int y){
	return dep[x]+dep[y]-(dep[lca(x,y)]<<1);
}
signed main(){
	scanf("%d",&n);
	for(int i=1;i<=n;i++)
		scanf("%d",&h[i]);
	for(int i=1,x,y;i<n;i++)
		scanf("%d%d",&x,&y),e[h[x]].push_back(h[y]),e[h[y]].push_back(h[x]);
	dfs(n);
	for(int i=1;i<=n;i++)fa[i]=i;
	for(int u=1;u<=n;u++)
		for(int t:e[u]){
			int v=getfa(t);
			if(v<u)
				merge(u,v),dp[u]=max(dp[u],dp[v]+dis(u,v));
		}
	printf("%lld\n",dp[n]);
	return 0;
}
```

[record](https://www.luogu.com.cn/record/123285292)

---

## 作者：ningago (赞：1)

容易发现猫猫从 $k$ 节点跳到子树里就不能跳回 $k$ 了。

对于 $k$ 往哪里跳进行决策。不难得知在 $k$ 的一个儿子的子树内放大于一个障碍是不优的。所以可以钦定一个儿子，堵上其他的儿子，然后跳到这个子树中的最大值所在的位置。

记 $dp_k$ 表示当前在 $k$，将来能跳出的最大价值。你获得了一个 $O(n^2)$ 的暴力点分治。

发现从 $k$ 能跳到的位置（或者说 $k$ 为分治中心的点分树）是确定好的：仅保留权值 $\leq k$ 且的点后，与 $k$ 连通的点构成的子图（树）。

于是可以考虑时间倒流，用并查集维护每个点的点分树。在合并子树的过程中更新 $dp$ 即可。

```cpp
#include <cstdio>
#include <cstring>
#include <algorithm>
#include <cmath>
#include <ctype.h> 
#include <vector>
#include <numeric>

char _ST_;

//#define ll long long
//#define inf 0x3f3f3f3f
#define int long long
#define inf 0x3f3f3f3f3f3f3f3f
#define pii std::pair <int, int>
#define mkp std::make_pair
#define fi first
#define se second
#define debug(...) fprintf(stderr, __VA_ARGS__)
#define gline debug("now is #%d\n", __LINE__)

int read()
{
	int x = 0, f = 1;
	char c = getchar();
	for(; !isdigit(c); c = getchar()) if(c == '-') f = -1;
	for(;  isdigit(c); c = getchar()) x = (x << 3) + (x << 1) + (c ^ 48);
	return x * f;
}

void ckmax(int &x, int y) { x = x > y ? x : y; }
void ckmin(int &x, int y) { x = x < y ? x : y; }

//#define mod 998244353
#define mod 1000000007
void plus_(int &x, int y) { x = x + y >= mod ? x + y - mod : x + y; }
void mul_(int &x, int y) { x = 1ll * x * y % mod; }
int pls(int x, int y) { return x + y >= mod ? x + y - mod : x + y; }
int ml(int x, int y) { return 1ll * x * y % mod; }
int ksm(int a, int b) { int res = 1; for(; b; b >>= 1, mul_(a, a)) if(b & 1) mul_(res, a); return res; }

#define N 200010
int n;
int p[N];
int h[N], e[N << 1], ne[N << 1], idx = -1;
void add_edge(int x, int y) { ne[++idx] = h[x]; h[x] = idx; e[idx] = y; }
void add(int x, int y) { add_edge(x, y); add_edge(y, x); }
namespace LCA
{
	int top[N], dep[N], sz[N], hson[N], fa[N];
	void dfs1(int k, int f, int deep)
	{
		fa[k] = f, dep[k] = deep, sz[k] = 1;
		for(int i = h[k]; ~i; i = ne[i])
		{
			int nx = e[i]; if(nx == f) continue;
			dfs1(nx, k, deep + 1); sz[k] += sz[nx];
			if(sz[nx] > sz[hson[k]]) hson[k] = nx;
		}
	}
	void dfs2(int k, int tp)
	{
		top[k] = tp;
		if(hson[k]) dfs2(hson[k], tp);
		for(int i = h[k]; ~i; i = ne[i])
		{
			int nx = e[i]; if(nx == fa[k] || nx == hson[k]) continue;
			dfs2(nx, nx); 
		} 
	}
	int lca(int x, int y)
	{
		for(; top[x] != top[y]; x = fa[top[x]]) if(dep[top[x]] < dep[top[y]]) x ^= y ^= x ^= y;
		return dep[x] < dep[y] ? x : y;
	}
	int dis(int x, int y) { return dep[x] + dep[y] - 2 * dep[lca(x, y)]; }
}
int dp[N], fa[N];
int Find(int x) { return x == fa[x] ? x : fa[x] = Find(fa[x]); }

char _ED_;
signed main()
{
	memset(h, idx = -1, sizeof(h));
	n = read();
	for(int i = 1; i <= n; i++) p[i] = read();
	for(int i = 1, x, y; i < n; i++) x = read(), y = read(), add(p[x], p[y]);
	LCA::dfs1(1, 0, 1);
	LCA::dfs2(1, 1);
	std::iota(fa + 1, fa + 1 + n, 1);
	for(int k = 1; k <= n; k++)
	{
		for(int i = h[k]; ~i; i = ne[i])
		{
			int nx = e[i];
			if(nx > k) continue;
			nx = Find(nx);
			ckmax(dp[k], dp[nx] + LCA::dis(k, nx));
			fa[nx] = k;
		}
	}
	printf("%lld\n", dp[n]);
	return 0;
}
```

---

## 作者：serene_analysis (赞：0)

观察发现猫离开一个点 $x$ 之后不可能再回到 $x$，于是这个点将原树划分为了若干连通块。可以发现存在一种最优方案使得我们在 $x$ 时不会往我们要去的连通块放障碍物，证明是简单的，讨论一下要去的联通块的最大点放不放即可，这里略去。那么假如我们确定了要去的联通块是哪个，我们的最优决策就是堵住其他的子树之后再往当前点放障碍物。于是做一个类似点分治的过程就能做到 $\mathcal{O}(n^2)$，如下方代码所示。

```cpp
int pl[maxn];
bool vis[maxn];
int rt;
void findr(int x,int f){
	for(int i=h[x];i;i=qxx[i].next){
		int v=qxx[i].to;
		if(vis[v]||v==f)continue;
		findr(v,x);
	}
	if(!rt||pl[x]>pl[rt])rt=x;
	return;
}
ll tian(int x){
	vis[x]=true;
	ll ret=0;
	for(int i=h[x];i;i=qxx[i].next){
		int v=qxx[i].to;
		if(vis[v])continue;
		rt=0,findr(v,x),ret=std::max(ret,dis(rt,x)+tian(rt));
	}
	return ret;
}
//namespace burningContract
```

思考一下这个过程究竟是什么样的。把代码中算答案部分的 $x$ 和 $rt$ 连边会形成一个树形结构，我们只要知道这棵树的形态即可算出答案，而一个点 $v$ 的父亲是 $x$ 的条件是 $x$ 是满足 $P_x \gt P_v$ 且 $x$ 到 $v$ 路径上没有比 $v$ 更大的权值的点中 $P$ 最小的点，点分治即可做到 $\mathcal{O}(n \log^2 n)$。然后你发现这个就是 kruskal 重构树。

```cpp
#include<algorithm>
#include<cassert>
#include<cstdio>
#include<vector>
#include<set>
namespace burningContract{
//bool mbeg;
int read(){
	int x=0;
	char ch=getchar();
	while(ch>'9'||ch<'0')ch=getchar();
	while(ch>='0'&&ch<='9')x=x*10+ch-48,ch=getchar();
	return x;
}
typedef long long ll;
const int maxn=2e5+5;
const int edgm=maxn*2+5;
struct edge{int to,next;}qxx[edgm];
int qxx_cnt,h[maxn];
void add(int x,int y){
	qxx[++qxx_cnt]=(edge){y,h[x]},h[x]=qxx_cnt;
	return;
}
int d[maxn],fa[maxn],size[maxn],hson[maxn];
void divide(int x,int f){
	d[x]=d[f]+1,fa[x]=f,size[x]=1;
	for(int i=h[x];i;i=qxx[i].next){
		int v=qxx[i].to;
		if(v==f)continue;
		divide(v,x),size[x]+=size[v];
		if(size[v]>size[hson[x]])hson[x]=v;
	}
	return;
}
int top[maxn];
void topen(int x,int tp){
	top[x]=tp;
	if(hson[x])topen(hson[x],tp);
	for(int i=h[x];i;i=qxx[i].next){
		int v=qxx[i].to;
		if(v==fa[x]||v==hson[x])continue;
		topen(v,v);
	}
	return;
}
int lca(int x,int y){
	while(top[x]!=top[y]){
		if(d[top[x]]<d[top[y]])std::swap(x,y);
		x=fa[top[x]];
	}
	return d[x]<d[y]?x:y;
}
int dis(int x,int y){return d[x]+d[y]-2*d[lca(x,y)];}
int n;
int pl[maxn];
bool vis[maxn];
int mx[maxn];
int rt,tot;
void findr(int x,int f){
	size[x]=1,mx[x]=0;
	for(int i=h[x];i;i=qxx[i].next){
		int v=qxx[i].to;
		if(vis[v]||v==f)continue;
		findr(v,x),size[x]+=size[v],mx[x]=std::max(mx[x],size[v]);
	}
	mx[x]=std::max(mx[x],tot-size[x]);
	if(!rt||mx[x]<mx[rt])rt=x;
	return;
}
struct pii{
	int v,id;
	friend bool operator<(pii now,pii oth){return now.v==oth.v?now.id<oth.id:now.v<oth.v;}
};
std::set<pii>apr;
void put(int x,int f,int gmx){
	gmx=std::max(gmx,pl[x]);
	if(gmx==pl[x])apr.insert((pii){pl[x],x});
	for(int i=h[x];i;i=qxx[i].next){
		int v=qxx[i].to;
		if(v==f||vis[v])continue;
		put(v,x,gmx);
	}
	return;
}
int lfa[maxn];
void go(int x,int f,int gmx,int st){
	gmx=std::max(gmx,pl[x]);
	if(gmx==pl[x]&&!apr.empty()&&std::prev(apr.end())->v>=pl[x]){
		auto dt=apr.lower_bound((pii){pl[x],-1});
		if(dt!=apr.end()){
			int gf=dt->id;
			if(!lfa[x]||pl[gf]<pl[lfa[x]])lfa[x]=gf;
		}
	}
	if(gmx==pl[st]){
		int gf=st;
		if(!lfa[x]||pl[gf]<pl[lfa[x]])lfa[x]=gf;
	}
	for(int i=h[x];i;i=qxx[i].next){
		int v=qxx[i].to;
		if(v==f||vis[v])continue;
		go(v,x,gmx,st);
	}
	return;
}
int son[maxn],scnt;
void tian(int x){
	vis[x]=true,scnt=0,apr.clear();
	for(int i=h[x];i;i=qxx[i].next){
		int v=qxx[i].to;
		if(vis[v])continue;
		son[++scnt]=v;
	}
	for(int i=1;i<=scnt;i++)go(son[i],x,pl[x],x),put(son[i],x,pl[x]);
	auto dt=apr.lower_bound((pii){pl[x],-1});
	if(dt!=apr.end()){
		int gf=dt->id;
		if(!lfa[x]||pl[gf]<pl[lfa[x]])lfa[x]=gf;
	}
	std::reverse(son+1,son+scnt+1),apr.clear();
	for(int i=1;i<=scnt;i++)go(son[i],x,pl[x],x),put(son[i],x,pl[x]);
//	printf("x=%d,lfa[x]=%d\n",x,lfa[x]);
	for(int i=h[x];i;i=qxx[i].next){
		int v=qxx[i].to;
		if(vis[v])continue;
		findr(v,x),tot=size[v],rt=0,findr(v,x),tian(rt);
	}
	return;
}
std::vector<int>dw[maxn];
ll decide(int x){
	ll ret=0;
	for(int v:dw[x])ret=std::max(ret,dis(v,x)+decide(v));
	return ret;
}
//bool mend;
signed main(){
//	fprintf(stderr,"%lld",&mbeg-&mend);
	n=read();
	for(int i=1;i<=n;i++)pl[i]=read();
	for(int i=2;i<=n;i++){
		int x=read(),y=read();
		add(x,y),add(y,x);
	}
	divide(1,0),topen(1,0),tot=n,findr(1,0),tian(rt);
	int nrt=std::max_element(pl+1,pl+n+1)-pl;
	for(int i=1;i<=n;i++)if(i!=nrt)/*printf("lfa[%d]=%d\n",i,lfa[i]),*/dw[lfa[i]].push_back(i);
	printf("%lld",decide(nrt));
	return 0;
}
//namespace burningContract
}
signed main(){return burningContract::main();}
```

感谢你的阅读。

---

## 作者：D_F_S (赞：0)

平衡树做法
## Solution：
考虑猫的移动轨迹，是类似点分治的路径，只不过把当前块内最高的点视为重心。每次移动即从当前重心选定一个子树，移动到子树内最高的点。

考虑直接在点分树上 DP，唯一要解决的就是点分树的形态，即查询一个联通块内的最高点。容易发现，当从重心把联通块划分为更小的联通块时，可以按点的 dfs 序直接分裂成小区间，父亲方向的点则是将左右两端的区间合并，因此可使用平衡树按 dfs 序维护所有联通块。

## Code：
```cpp
#include<bits/stdc++.h>
#define inl inline
using namespace std;
typedef long long ll;
const int N=2e5+5;
struct TR {int lc,rc,ke,mp; }tr[N]; vector<int> e[N];
int n,a[N],dp[N],sz[N],st[N],ed[N],df[N],fa[N],so[N],tp[N]; bool vs[N];
inl int Read()
{
	int s=0; char c; while(!isdigit(c=getchar()));
	for(;isdigit(c);c=getchar()) s=s*10+c-'0'; return s;
}
inl void DFS1(int p,int f)
{
	sz[p]=1; dp[p]=dp[fa[p]=f]+1; df[st[p]=++n]=p;
	for(int v:e[p]) v!=f&&(DFS1(v,p),sz[p]+=sz[v],sz[v]>sz[so[p]]&&(so[p]=v));
	ed[p]=n;
}
inl void DFS2(int p,int t)
{
	tp[p]=t; for(int v:e[p]) v!=fa[p]&&(DFS2(v,v==so[p]?t:v),0);
}
inl int LCA(int x,int y)
{
	while(tp[x]!=tp[y]) dp[tp[x]]>dp[tp[y]]?x=fa[tp[x]]:y=fa[tp[y]];
	return dp[x]>dp[y]?y:x;
}
inl int Dis(int x,int y) {return dp[x]+dp[y]-dp[LCA(x,y)]*2; }
#define L (tr[p].lc)
#define R (tr[p].rc)
inl void Pushup(int p)
{
	tr[p].mp=p; a[tr[L].mp]>a[tr[p].mp]&&(tr[p].mp=tr[L].mp);
	a[tr[R].mp]>a[tr[p].mp]&&(tr[p].mp=tr[R].mp);
}
inl int Build()
{
	int rt=0,tp=0,st[N]; for(int i=1,t;i<=n;++i)
	{
		 for(t=df[i];tp>1&&tr[st[tp-1]].ke>tr[t].ke;) tr[st[tp-1]].rc=st[tp], Pushup(st[--tp]);
		tp&&tr[st[tp]].ke>tr[t].ke&&(tr[t].lc=st[tp--],Pushup(t),0); !tp&&(rt=t); st[++tp]=t;
	}
	while(tp>1) tr[st[tp-1]].rc=st[tp], Pushup(st[--tp]); return rt;
}
inl int Merge(int p,int t)
{
	if(!p||!t) return p|t;
	if(tr[p].ke<tr[t].ke) return R=Merge(R,t), Pushup(p), p;
	else return tr[t].lc=Merge(p,tr[t].lc), Pushup(t), t;
}
inl void Split(int p,int k,int &lp,int &rp)
{
	if(!p) return lp=rp=0, void();
	st[p]<=k?(lp=p,Split(R,k,R,rp)):(rp=p,Split(L,k,lp,L)); Pushup(p);
}
#undef L
#undef R
inl ll DP(int rt,int la)
{
	ll an=0; int p=tr[rt].mp,lp,rp; vs[p]=true;
	for(int v:e[p]) if(!vs[v]&&v==fa[p])
		Split(rt,st[p]-1,lp,rt), Split(rt,ed[p],rt,rp), an=max(an,DP(Merge(lp,rp),p));
	else if(!vs[v])
		Split(rt,st[v]-1,lp,rt), Split(rt,ed[v],rt,rp), an=max(an,DP(rt,p)), rt=Merge(lp,rp);
	return an+(la?Dis(p,la):0);
}
int main()
{
	n=Read(); for(int i=1;i<=n;++i) a[i]=Read(), tr[i]={0,0,rand(),i};
	for(int i=1,x,y;i<n;++i) e[x=Read()].push_back(y=Read()), e[y].push_back(x);
	n=0; DFS1(1,0); DFS2(1,1); printf("%lld\n",DP(Build(),0)); return 0;
}
```


---

