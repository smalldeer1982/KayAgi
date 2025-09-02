# [USACO22JAN] Farm Updates G

## 题目描述

Farmer John 经营着总共 $N$ 个农场（$1\le N\le 10^5$），编号为 $1\ldots N$。最初，这些农场之间没有道路连接，并且每个农场都在活跃地生产牛奶。

由于经济的动态性，Farmer John 需要根据 $Q$ 次更新操作（$0\le Q\le 2\cdot 10^5$）对他的农场进行改造。更新操作有三种可能的形式：

- `(D x)` 停用一个活跃的农场 $x$，使其不再生产牛奶。

- `(A x y)` 在两个活跃的农场 $x$ 和 $y$ 之间添加一条道路。

- `(R e)` 删除之前添加的第 $e$ 条道路（$e = 1$ 是添加的第一条道路）。

一个农场 $x$ 如果正在活跃地生产牛奶，或者可以通过一系列道路到达另一个活跃的农场，则称之为一个「有关的」农场。对于每个农场 $x$，计算最大的 $i$（$0\le i\le Q$），使得农场 $x$ 在第 $i$ 次更新后是有关的。

## 说明/提示

【样例解释】

在这个例子中，道路以顺序 $(2,3), (1,2), (2,4)$ 被删除。

- 农场 $1$ 在道路 $(1,2)$ 被删除之前是有关的。

- 农场 $2$ 在道路 $(2,4)$ 被删除之前是有关的。

- 农场 $3$ 在道路 $(2,3)$ 被删除之前是有关的。

- 农场 $4$ 和 $5$ 在所有更新结束后仍然是活跃的。所以它们一直保持为有关的，两者的输出均应为 $Q$。

【数据范围】

- 测试点 2-5 满足 $N\le 10^3$，$Q\le 2\cdot 10^3$。

- 测试点 6-20 没有额外限制。


## 样例 #1

### 输入

```
5 9
A 1 2
A 2 3
D 1
D 3
A 2 4
D 2
R 2
R 1
R 3```

### 输出

```
7
8
6
9
9```

# 题解

## 作者：清小秋ovo (赞：12)

# USACO 金组 T2 题解

谁又能想到这题 BFS 能过呢，而且还跑的挺快（笑）。

只会打暴力的选手狂喜。

那就直接进入正题了。

## 题意简化

这篇题解 `active` 定义为 开着的点，把 `relevant` 称为活点。

给你一张无向无权图，有三种操作：

$1$: 在某两个活点之间加边。

$2$: 在某两个点之间删一条边。

$3$: 关掉某一个点。

初始每个点直接无边，且每个点都为开启状态。

对于一个活点的定义如下：当一个点为开启状态时，或可以通过一条存在的边走到任意一个开着的点时，该点为活点。求每一个点在哪次操作之后不为活点。如果一直都没有关闭则直接输出操作总次数。

## 思路解析

一看到这个条件立马想到了并查集。但是问题就在于删边之后的处理。并查集在连通块查询上有很大优势，可这题中不光有加边，还有删边。赛场上也没想太多，就换了个思路去想。


其实可以先按照题目里的指令把图建起来，对于删边和关点的操作，我们分别各自开一个数组来计录下某一条边或某一个点在什么时刻被关闭。随后我们按照点关闭时间从大到小依次遍历整张图，更新答案。

这么说可能有些抽象，那么我们可以画个图来推推样例。

首先按照指令建图，并存下点，边的开关时间: 

[![HZ6SYt.png](https://s4.ax1x.com/2022/02/04/HZ6SYt.png)](https://imgtu.com/i/HZ6SYt)

然后我们从最后关的点进行遍历。
这里的话因为 $5$ 号点没有出边，就直接跳过从 $4$ 号点开始了。

[![HZcRa9.png](https://s4.ax1x.com/2022/02/04/HZcRa9.png)](https://imgtu.com/i/HZcRa9)

就这样一路推下去，就可以得到最终的答案了。

之所以这样做是可行的，是因为在每次遍历时我们都是从最大的点开始倒着遍历，所以对于一个连通块来讲，一定是从最大的点开始进行搜索的。同时题目里也提到了加边操作只在两个开着的点（注意这里是开着的点，而**不是活点**）有了这些性质，我们才可以这样做。

## Code

代码实现整体上不是很难，唯独需要注意的是边别开小了，另外还有一些小细节。写在注释里了。

```cpp
#include <bits/stdc++.h>

using namespace std;
typedef long long ll;
typedef vector<int> vi;
typedef queue<int> qi;
typedef pair<int, int> P;

#define dbg(x) cout << #x << " = " << x << endl
#define PB push_back
#define MP make_pair
#define sz(x) (int)(x).size()
#define INF (int)1e9
#define EPS 1e-9
#define REP(name, st, ed, inc) for (int name = st; name <= ed; name += inc)
#define RREP(name, st, ed, dec) for (int name = st; name >= ed; name -= inc)
#define all(cont) cont.begin(), cont.end()

inline int read()
{
   char ch = getchar();
   int x = 0, cf = 1;
   while (ch < '0' || ch > '9')
   {
      if (ch == '-')
         cf = -1;
      ch = getchar();
   }
   while (ch >= '0' && ch <= '9')
   {
      x = (x << 3) + (x << 1) + (ch ^ 48);
      ch = getchar();
   }
   return x * cf;
}

inline void write(int x)
{
   char ch[20];
   int len = 0;
   if (x < 0)
   {
      putchar((1 << 5) + (1 << 3) + (1 << 2) + 1);
      x = ~x + 1;
   }
   do
   {
      ch[len++] = x % 10 + (1 << 4) + (1 << 5);
      x /= 10;
   } while (x > 0);
   for (int i = len - 1; i >= 0; i--)
      putchar(ch[i]);
   return;
}

//以上快读快写

const int N = 100000 + 20;
const int M = 4 * 100000 + 20; //这个一定要开对... 因为是无向图

int head[N], nxt[M], to[M], ed[M], vis[N], ans[N]; // ed[i] 表示 i边关闭时间
int ti[N]; //某个点的关闭时间
int n, Q, x, y, tot = 0;

struct node
{
   int ans, id;
   bool operator<(const node &b) const
   {
      return ans < b.ans;
   }
} a[N]; //存点的结构体, ans表示某个点的关闭时间，id为编号

priority_queue<node> t; //用大根堆维护每个点，每次取到最大的点 

char T;

void add(int u, int v)
{
   tot++;
   to[tot] = v;
   ed[tot] = Q; //如果开了这条边默认设置对应的关闭值, 以防后面不关
   nxt[tot] = head[u];
   head[u] = tot;
}

int main()
{
   n = read(), Q = read();
   for (int i = 1; i <= n; i++)
   {
      ti[i] = Q; //初始化，如果不动的话就到Q才关
   }
   
   for (int i = 0; i < Q; i++) //注意是从0开始的
   {
      T = getchar();
      if (T == 'A')
      {
         x = read(), y = read(); // x -> y, y -> x 双向建边
         add(x, y);
         add(y, x);
      }
      else if (T == 'D')
      {
         x = read(); //关闭x号点
         ti[x] = i;
      }
      else
      {
         x = read(); //删除x号边, x号边对应的两条边为x*2和x*2-1
         ed[x * 2] = i;
         ed[x * 2 - 1] = i;
      }
   }
   //将数据推入大根堆
   for (int i = 1; i <= n; i++)
   {
      a[i].ans = ti[i];
      a[i].id = i;
      t.push(a[i]);
   }
   //BFS
   while(!t.empty())
   {
      node cur = t.top();
      int id = cur.id;
      int tt = cur.ans; //对应的关闭时间
      t.pop();
      if (vis[id]) continue;
      vis[id] = 1;
      for (int i = head[id]; i; i = nxt[i])
      {
         int y = to[i];
         int prev = min(ed[i], a[id].ans); //别的边的贡献
         a[y].ans = max(a[y].ans, prev); //那么那个点的最大时间设为 自己点关的时间和别的边时间的最大值
         t.push(a[y]);
      }
   }
   for (int i = 1; i <= n; i++)
   {
      write(a[i].ans);
      putchar('\n');
   }
   return 0;
}
```

总体来讲，这题说难不难，说简单不简单。前提是要有思路。

细节也挺多的，反正就很 USACO。

---

## 作者：zhiyangfan (赞：11)

> 给出一张 $n$ 个点的无向图，刚开始所有点的权值都是 $1$，没有边。共有 $q$ 次操作，操作分以下三种：
> - `R x` 将一个点的权值变为 $0$。
> - `A x y` 在两点 $x,y$ 之间连一条边，保证 $x,y$ 的权值均为 $1$。
> - `D e` 删除加入的第 $e$ 条边，边从 $1$ 开始编号。
> 
> 如果一个点权值为 $1$ 或与权值为 $1$ 的点连通，则定义这个点是「关联的」。对于每个点求最大的 $i(0\le i\le q)$，使得在这次操作后该点是「关联的」。($1\le n\le 10^5,1\le q\le 2\times10^5$)

分析一波这些操作，我们能发现第二个操作似乎并不会改变每个点的关联性。注意到一个连通块内的点关联性都是相同的，而二操作相当于合并两个均为「关联的」的连通块，当然不会改变连通性。所以现在我们要维护的东西就变为了单点修改和删边。显然加边更好处理，所以考虑改成倒序处理。

我们来分析一下倒序的这些操作。
- 将一个点的权值从 $0$ 变为 $1$。此时该点所在的连通块都会变为「关联的」。
- 删除 $x,y$ 之间的边，保证 $x,y$ 的权值均为 $1$。（注意这里依然有这个保证是因为正向做的时候就不会影响 $0,1$）显然不会对关联性造成什么影响，可以忽略。
- 加入第 $e$ 条边。这个操作影响关联性的条件是这条边两边的连通块关联性不同，合并之后就会全变为「关联的」。其他情况就没有影响，直接合并连通块即可。

想一下我们现在的操作，遍历一个连通块，合并两个连通块，而这些一个并查集就可以做到。而倒序操作从非「关联的」变为「关联的」的时间点的上一个时间，就是最终的答案。（注意一个点一旦变为「关联的」就不会再变回去了，因为上面的操作并不会影响到这一点）

实现时不要忘了倒序操作前加入在最后没有删除的边。时间复杂度是均摊的 $\mathcal{O}(n+q)$。
```cpp
#include <cstdio>
#include <vector>
#include <cstdlib>
const int N = 2e5 + 10; int f[N]; std::vector<int> vec[N];
struct query{ int op, x; }q[N]; int ans[N], vis[N];
struct edge{ int x, y; }e[N]; int tp, del[N];
int getf(int x) { return x == f[x] ? x : f[x] = getf(f[x]); }
inline void link(int u, int v, int now)
{
	u = getf(u), v = getf(v); if (u == v) return ;
	if ((!vis[u]) ^ (!vis[v]))
	{
		if (!vis[u]) for (auto x : vec[u]) vis[x] = now;
		else for (auto x : vec[v]) vis[x] = now;
	}
	if (vec[u].size() > vec[v].size()) { f[v] = u; for (auto x : vec[v]) vec[u].push_back(x); }
	else { f[u] = v; for (auto x : vec[u]) vec[v].push_back(x); }
}
int main()
{
	char op[5]; int x, y, n, Q; scanf("%d%d", &n, &Q);
	for (int i = 1; i <= n; ++i) f[i] = i, vis[i] = Q, vec[i].push_back(i);
	for (int i = 1; i <= Q; ++i)
	{
		scanf("%s", op);
		if (op[0] == 'A') scanf("%d%d", &x, &y), e[++tp].x = x, e[tp].y = y;
		else scanf("%d", &x), q[i].op = op[0] == 'D' ? 1 : 2, q[i].x = x;
	}
	for (int i = 1; i <= Q; ++i) 
		if (q[i].op == 1) vis[q[i].x] = 0;
		else del[q[i].x] = 1;
	for (int i = 1; i <= tp; ++i) if (!del[i]) link(e[i].x, e[i].y, Q);
	for (int i = Q; i >= 1; --i)
	{
		if (!q[i].op) continue;
		if (q[i].op == 1)
		{
			int u = getf(q[i].x);
			if (!vis[u]) for (auto x : vec[u]) vis[x] = i - 1;
		}
		else link(e[q[i].x].x, e[q[i].x].y, i - 1);
	}
	for (int i = 1; i <= n; ++i) printf("%d\n", vis[i]);	
	return 0;
}
```

---

## 作者：Alex_Wei (赞：7)

> **[P8097 [USACO22JAN] Farm Updates G](https://www.luogu.com.cn/problem/P8097)*

相比于官方线性 sol，我的做法仅供大家看个乐子。

加边删边考虑线段树分治，用可持久化并查集维护每个叶子结点的联通情况。注意到我们仅在活跃农场之间加边，故若一个农场变得不相关，则它永远不会再相关，因此具有可二分性。对每个农场二分答案即可。

如何判断一个农场与一个活跃农场相连？考虑将农场重标号为其被停用的次序，即第 $i$ 个被停用的农场标号为 $i$，则对于当前农场 $p$ 和二分的时刻 $t$，设此时已经有 $d_t$ 个农场被停用，那么 $p$ 与活跃农场相连等价于 $p$ 所在连通块节点标号最大值 $> d_t$。可持久化并查集可以维护标号最大值。 

一次查询的复杂度为 $\log ^ 2 n$，因此时间复杂度 $\mathcal{O}(n\log n\log ^ 2 Q)$，空间复杂度 $\mathcal{O}(n\log n\log Q)$。时空双双爆炸。

由于询问离线，考虑 **整体二分**。即对于 **时刻区间** $[0, Q]$，设其中点为 $m$，线段树分治到叶子结点时刻 $m$，查询所有农场是否相关，将不相关的农场丢到 **时刻区间** $[0, m - 1]$，相关的农场丢到时刻区间 $[m, Q]$。再向两侧递归。

线段树上需要从时刻 $p\to q$，就从 $p$ 向上跑到 $p, q$ 在线段树上的 LCA，再向下跑到叶子结点 $q$。向上跑的时候离开一个节点要撤销该节点所存储的边的贡献，向下跑的时候加入一个节点要算上该节点所存储的边的贡献，类比普通线段树分治。

乍一看，在分治线段树上的移动复杂度似乎不可接受，但是类似决策单调性分治在贡献难算时的复杂度分析， 线段树上每个节点均只会被经过常数次。配合可撤销并查集，视 $n, q$ 同阶，时间复杂度 $\mathcal{O}(n \log ^ 2 n)$，空间复杂度 $\mathcal{O}(n\log n)$。比线性劣了很多，但大概启发性在于将线段树分治和整体二分相结合（可能已经烂大街了吧？从来没见过这个套路，赛时还分析了好长时间复杂度，是我才疏学浅了）。

```cpp
#include <bits/stdc++.h>
using namespace std;

#define pii pair <int, int>
const int N = 2e5 + 5;
int n, q, num[N], pos[N], ans[N];
int p[N], x[N], y[N]; char op[N];
vector <pii> ed[N << 2];
void build(int l, int r, int x) {
	if(l == r) return pos[l] = x, void();
	int m = l + r >> 1;
	build(l, m, x << 1), build(m + 1, r, x << 1 | 1);
}
void modify(int l, int r, int ql, int qr, int x, pii v) {
	if(ql <= l && r <= qr) return ed[x].push_back(v), void();
	int m = l + r >> 1;
	if(ql <= m) modify(l, m, ql, qr, x << 1, v);
	if(m < qr) modify(m + 1, r, ql, qr, x << 1 | 1, v);
}

struct dat {int u, v, omx;};
struct dsu {
	int fa[N], sz[N], mx[N];
	int find(int x) {return fa[x] == x ? x : find(fa[x]);}
	void init() {for(int i = 1; i <= n; i++) fa[i] = i, mx[i] = i, sz[i] = 1;}
	dat merge(int u, int v) {
		if(sz[u] < sz[v]) swap(u, v);
		dat ret = {u, v, mx[u]};
		sz[u] += sz[v], fa[v] = u;
		if(mx[v] > mx[u]) mx[u] = mx[v];
		return ret;
	} void undo(dat d) {
		sz[d.u] -= sz[d.v], fa[d.v] = d.v, mx[d.u] = d.omx;
	}
} f;

int cur = 1, lg[N << 2], top, stc[N];
dat oper[N];
bool ances(int anc, int p) {
	if(lg[anc] > lg[p]) return 0;
	return anc == (p >> lg[p] - lg[anc]);
}
void move(int aim) {
	while(!ances(cur, aim)) {
		assert(cur != 1);
		while(stc[top] == cur) f.undo(oper[top]), top--;
		cur >>= 1;
	} while(cur != aim) {
		if(ances(cur << 1, aim)) cur <<= 1;
		else cur = cur << 1 | 1;
		for(pii it : ed[cur]) {
			int u = f.find(it.first), v = f.find(it.second);
			if(u == v) continue;
			stc[++top] = cur, oper[top] = f.merge(u, v);
		}
	}
}
void solve(int l, int r, vector <int> &arr) {
	if(arr.empty()) return;
	if(l == r) {for(int it : arr) ans[it] = l; return;}
	int m = l + r + 1 >> 1;
	move(pos[m]);
	vector <int> left, right;
	for(int it : arr) {
		int val = f.mx[f.find(it)];
		if(val <= num[m]) left.push_back(it);
		else right.push_back(it);
	} solve(l, m - 1, left), solve(m, r, right);
}

int main() {
	cin >> n >> q, f.init(), build(1, q, 1);
	for(int i = 2; i < N << 2; i++) lg[i] = lg[i >> 1] + 1;
	for(int i = 1, cur = 0, ed = 0; i <= q; i++) {
		static int st[N]; cin >> op[i] >> x[i];
		if(op[i] == 'A') cin >> y[i], st[++ed] = i;
		if(op[i] == 'D') p[x[i]] = ++cur; num[i] = cur;
		if(i == q) {
			for(int j = 1; j <= n; j++) if(!p[j]) p[j] = ++cur;
			for(int j = 1; j <= q; j++)
				if(op[j] == 'A') x[j] = p[x[j]], y[j] = p[y[j]];
				else if(op[j] == 'R') modify(1, q, st[x[j]], j - 1, 1, {x[st[x[j]]], y[st[x[j]]]}), st[x[j]] = -1;
			for(int j = 1; j <= ed; j++) if(st[j] != -1)
				modify(1, q, st[j], q, 1, {x[st[j]], y[st[j]]});
		}
	} for(pii it : ed[1]) {
		int u = f.find(it.first), v = f.find(it.second);
		if(u == v) continue;
		stc[++top] = cur, oper[top] = f.merge(u, v);
	} vector <int> arr;
	for(int i = 1; i <= n; i++) arr.push_back(i);
	solve(0, q, arr);
	for(int i = 1; i <= n; i++) cout << ans[p[i]] << "\n";
	return 0;
}
```

---

## 作者：耶梦加得 (赞：5)

容易想到倒着做，问题在于本题还有 Add 操作，怎么处理？

不处理。

题目有一条限制是只会在两个**活跃**的农场中间添加道路~~我就是没看到这个保龄了~~，这就意味着我们在倒着操作的过程中，删去这条边不会导致任何农场失活，换而言之，在倒着操作的过程中不会有任何农场失活。

先正着记录下每条边最终的状态（连接与否）和每个农场最后的状态，然后遍历整张图计算出此刻哪些农场是活跃的，最后倒着操作，遇到 Delete 就改一下状态再从这个点出发遍历联通块，遇到 Remove 就加边，如果至少有一个端点是活跃的，就从它出发再遍历联通块。

实现上，由于不会有农场失活，一旦激活就不需要再次遍历，用一个 vis 数组记录是否激活过这个点。每个点最多被激活一次，因此 dfs 复杂度为 $O(N)$，总复杂度 $O(N + Q)$。

答案可以在 dfs 的过程中顺便更新。

```cpp
#include<algorithm>
#include<cstdio>
#include<cstring>
#include<iostream>
#include<queue>
#include<vector>
using namespace std;
int n, m;
char ch[7];
int ans[100007];
int act[100007]; //农场活跃与否
pair<int, int> e[200007];
int eid; 
int stat[200007]; //边是否断开，断开为0，连接为1
pair<int, int> q[200007];
vector<int> g[100007];
bool vis[100007];
void dfs(int x, int t) { //t 代表操作时间
    vis[x] = 1; if(!ans[x]) ans[x] = t; //最后一个活跃的时刻，对于倒序操作就是第一个
    for(int i = 0; i < g[x].size(); ++i) {
        int to = g[x][i];
        if(vis[to]) continue;
        act[to] |= act[x];
        dfs(to, t);
    }
} //易知不存在一个点被遍历过却没有激活
signed main() {
    scanf("%d %d", &n, &m);
    for(int i = 1; i <= n; ++i) act[i] = 1;
    for(int i = 1; i <= m; ++i) {
        scanf("%s", ch + 1); 
        int x, y;
        switch(ch[1]) {
        case 'A' :
            scanf("%d %d", &x, &y);
            e[++eid] = make_pair(x, y);
            stat[eid] = 1;
            break;
        case 'R' :
            scanf("%d", &x);
            q[i] = make_pair(1, x);
            stat[x] = 0;
            break;
        case 'D' :
            scanf("%d", &x);
            act[x] = 0;
            q[i] = make_pair(2, x);
            break;
        }
    }
    for(int i = 1; i <= eid; ++i) {
        if(stat[i]) {
            g[e[i].first].push_back(e[i].second);
            g[e[i].second].push_back(e[i].first);
        }
    }
    for(int i = 1; i <= n; ++i) {
        if(act[i] && !vis[i]) dfs(i, m);
    }
    for(int i = m; i; --i) {
        int x, y;
        switch(q[i].first) {
        case 1:
            x = e[q[i].second].first, y = e[q[i].second].second;
            g[x].push_back(y);
            g[y].push_back(x);
            if(act[x]) dfs(x, i - 1);
            if(act[y]) dfs(y, i - 1);
            break;
        case 2:
            x = q[i].second;
            act[x] = 1;
            dfs(x, i - 1);
            break;
            //A操作不管
        }
    }
    for(int i = 1; i <= n; ++i) printf("%d\n", ans[i]);
    return 0;
}

```


---

## 作者：Purslane (赞：2)

## Solution

如果只有删边和删点 , 那么可以时光倒流来做 .

> 时光倒流 : 数据结构等东西都很支持合并 , 但分裂比较困难 . 那么可以离线倒着做 , 将分裂变为合并 .

可是这有一个加边 . 线段树分治 ? 不用 .

我们发现 , 加边的两端都是有效点 . 那么这条边贯通的两个连通块肯定都满足要求 , 加不加边不影响结果 . 所以加边操作可以移到最开始进行 .

关于标记答案 , 本来想用并查集 , 但发现倒着操作只要每次加边看两边是否一遍有标记另一边没标记 , 加点只要看这个连通块有没有标记即可 . 可以 `DFS` . 复杂度 $\text{O(n+q)}$ .

code ;

```cpp
#include<bits/stdc++.h>
#define ffor(i,a,b) for(int i=(a);i<=(b);i++)
#define roff(i,a,b) for(int i=(a);i>=(b);i--)
using namespace std;
const int MAXN=2e5+10;
struct Edge {
	int st,x,y;
}e[MAXN];
struct Operate {
	int op,x,y;
}op[MAXN<<1];
int n,q,cnt,tot,st[MAXN],ans[MAXN];
vector<int> G[MAXN];
void dfs(int u,int val) {
	if(ans[u]) return ;ans[u]=val;
	for(auto to:G[u]) dfs(to,val);return ;
}
int main() {
	ios::sync_with_stdio(false),cin.tie(0),cout.tie(0);
	cin>>n>>q;
	ffor(i,1,q) {
		char ch;int x,y;cin>>ch;
		if(ch=='D') {cin>>x;st[x]=1,op[++tot]={1,x,0};}
		if(ch=='A') {cin>>x>>y;e[++cnt]={0,x,y},++tot;}
		if(ch=='R') {cin>>x;op[++tot]={-1,e[x].x,e[x].y},e[x].st=1;}
	}
	ffor(i,1,cnt) if(!e[i].st) G[e[i].x].push_back(e[i].y),G[e[i].y].push_back(e[i].x);
	ffor(i,1,n) if(!st[i]) dfs(i,q);
	roff(i,q,1) {
		if(op[i].op==1) dfs(op[i].x,i-1);
		if(op[i].op==-1) {
			if(ans[op[i].x]) dfs(op[i].y,i-1);if(ans[op[i].y])dfs(op[i].x,i-1);
			G[op[i].x].push_back(op[i].y),G[op[i].y].push_back(op[i].x);
		}
	}
	ffor(i,1,n) cout<<ans[i]<<'\n';
	return 0;
}
```

---

## 作者：DengDuck (赞：0)

鉴定为语文阅读题。

注意到操作 `A x y` 一定是链接两个活跃农场这启示了我们几点。

首先一个点肯定不会在停产之后进行 `A` 操作。

进一步地，一个点变得无关，只可能是经历了 `D x` 操作且断掉了所有与活跃农场的边的路径，而且变得无关就不会建边，所以一个农场的有关的时间是一个形如 $[1,age_x]$ 的东西。

同时我们发现建边之前两个端点都是活跃的，所以这条边的建立时间不会对答案产生影响，但是删除是会的，我们可以记录它的删除时间 $r_i$。

其实这里做法就可以分成两种了，一种是倒过来，删点变成加点，删边变成加边们可以用并查集。

我的做法复杂一点，我们发现题目中所有输出的最大值一定是最大的 $age_x$，而每个点的输出值也不会小于 $age_x$，我们将 $age_x$ 初始化答案 $ans_x$。

接下来，我们用优先队列维护，每个点只取一次，每次取出一个最大值的点尝试更新相连的点。

只要我还有关，我们的边还在，你就还是有关的，所以我们更新点的方式也就是尝试 $ans_y=\min(ans_x,r_{(x,y)})$。

我们就这样一直更新就行了，时间复杂度是 $O(n\log n)$，没有并查集做法那么优秀。

但是好写好理解！

```cpp
#include<bits/stdc++.h>
#define LL long long
#define val first
#define num second
using namespace std;
const LL N=2e5+5;
LL n,q,ans[N],x,y,cnt,e[N][2],r[N],vis[N],age[N];
char c[15];
vector<pair<LL,LL> >v[N];
priority_queue<pair<LL,LL> >p;
int main()
{
	scanf("%lld%lld",&n,&q);
	for(int i=1;i<=N;i++)
	{
		age[i]=-1,r[i]=-1;
	}
	for(int Q=1;Q<=q;Q++)
	{
		scanf("%s",c);
		if(c[0]=='D')
		{
			scanf("%lld",&x);
			if(age[x]==-1)age[x]=Q-1;
		}
		if(c[0]=='A')
		{
			scanf("%lld%lld",&x,&y);
			++cnt;
			v[x].push_back({y,cnt});
			v[y].push_back({x,cnt});
		}
		if(c[0]=='R')
		{
			scanf("%lld",&x);	
			r[x]=Q-1;
		}
	}
	for(int i=1;i<=cnt;i++)
	{
		if(r[i]==-1)r[i]=q;
	}
	for(int i=1;i<=n;i++)
	{
		if(age[i]==-1)age[i]=q;
	}
	for(int i=1;i<=n;i++)
	{	
		ans[i]=age[i];
		p.push({ans[i],i});
	}
	while(!p.empty())
	{
		LL t=p.top().num;
		p.pop();
		if(vis[t])continue;
		vis[t]=1;
		for(pair<LL,LL> i:v[t])
		{
			if(ans[i.val]<min(ans[t],r[i.num]))
			{
				ans[i.val]=min(ans[t],r[i.num]);
				p.push({ans[i.val],i.val});
			}
		}
	}
	for(int i=1;i<=n;i++)
	{
		printf("%lld\n",ans[i]);
	}
	return 0;
}
```

---

## 作者：Forever1507 (赞：0)

可以发现这几个操作都满足一个单调性，就是你考虑把这些操作反过来，一个有关的农场在操作后无论如何不会变得无关。

反转后的操作：
- 操作 $1: $ 让一个农场活跃
- 操作 $2:$ 把两个活跃的农场之间的边断开
- 操作 $3:$ 加边

这意味着我们完全可以把整个操作序列倒过来求答案！

然后你发现，操作二里面两个活跃的农场不会失活，所以这条边是否存在对答案毫无影响，那么我们完全可以无视这样的操作，然后就成了一个并查集题。

可以把并查集开成一个结构体：

```cpp
struct Node{
    int cur;
    bool opt;
    vector<int>it;
    //父亲节点，是否“有关”，元素集合
}fa[200005];
```

然后可以按照定义的操作写出合并函数 `unionn`

```cpp
void unionn(int a,int b,int p){
    int x=find(a),y=find(b);
    if(x==y)return;
    if(fa[x].it.size()<fa[y].it.size())swap(x,y);
    fa[y].cur=x;
    // fa[x].opt|=fa[y].opt;
    if(fa[x].opt==1){
        if(!fa[y].opt){
            for(auto to:fa[y].it)vis[to]=1,ans[to]=p;
        }
    }
    if(!fa[x].opt){
        if(fa[y].opt){
            for(auto to:fa[x].it)vis[to]=1,ans[to]=p;
            fa[x].opt=1;
        }
    }
    for(auto to:fa[y].it)fa[x].it.push_back(to);
    fa[y].it.clear();
    return;
}
```

利用启发式合并可以降低时间复杂度。

这个时候就有一个问题了：如何保证时间复杂度呢？每次合并要遍历元素的集合，理论上是非常耗时间的啊。

显然一个元素从一个集合被合并到另一个集合里的次数大致等于传统路径压缩并查集里调用 `find` 函数时递归的次数。这个时间复杂度是均摊 $O(n\log n)$ 的，足以顺利通过本题。

反操作前不要忘了处理初始状态！

以下是参考代码：
```cpp
#include<bits/stdc++.h>
using namespace std;
int n,m,tot;
struct node{
    char x;
    int a,b;
}p[200005];
pair<int,int>e[200005];
int ans[200005];
struct Node{
    int cur;
    bool opt;
    vector<int>it;
    //父亲节点，是否“有关”，元素集合
}fa[200005];
int find(int x){
    return fa[x].cur==x?x:fa[x].cur=find(fa[x].cur);
}
bool vis[200005],flg[200005];
void unionn(int a,int b,int p){
    int x=find(a),y=find(b);
    if(x==y)return;
    if(fa[x].it.size()<fa[y].it.size())swap(x,y);
    fa[y].cur=x;
    // fa[x].opt|=fa[y].opt;
    if(fa[x].opt==1){
        if(!fa[y].opt){
            for(auto to:fa[y].it)vis[to]=1,ans[to]=p;
        }
    }
    if(!fa[x].opt){
        if(fa[y].opt){
            for(auto to:fa[x].it)vis[to]=1,ans[to]=p;
            fa[x].opt=1;
        }
    }//处理状态
    for(auto to:fa[y].it)fa[x].it.push_back(to);
    fa[y].it.clear();//合并
    return;
}
int main(){
    ios::sync_with_stdio(0);
    cin.tie(0);
    cout.tie(0);
    cin>>n>>m;
    for(int i=1;i<=m;++i){
        cin>>p[i].x;
        if(p[i].x=='A'){
            cin>>p[i].a>>p[i].b;
            e[++tot]=make_pair(p[i].a,p[i].b);
        }
        else if(p[i].x=='D'){
            cin>>p[i].a;
            vis[p[i].a]=1;
        }
        else{
            cin>>p[i].a;
            flg[p[i].a]=1;
        }
    }
    for(int i=1;i<=n;++i){
        fa[i].cur=i;
        fa[i].opt=!vis[i];
        fa[i].it.push_back(i);
        if(!vis[i])ans[i]=m;
    }
    for(int i=1;i<=tot;++i){
        if(flg[i])continue;
        unionn(e[i].first,e[i].second,m);
    }//初始状态
    for(int i=m;i>=1;--i){
        if(p[i].x=='A')continue;
        if(p[i].x=='D'){
            if(ans[find(p[i].a)])continue;
            fa[find(p[i].a)].opt=1;
            for(auto x:fa[find(p[i].a)].it){
                ans[x]=i-1;
            }
        }
        else{
            unionn(e[p[i].a].first,e[p[i].a].second,i-1);
        }
    }
    for(int i=1;i<=n;++i)cout<<ans[i]<<'\n';
    return 0;
}
```



---

## 作者：E1_de5truct0r (赞：0)

提供一种线性（？）做法。

## 思路

### 1. 转化

首先我们假设把点变成停用的为“删点”。

我们发现：

1. 操作 $1$ 是删点，不太好办；

2. 操作 $2$ 是加边，保证了只加毁灭的点之间的，比较好处理；

3. 操作 $3$ 是删边，还不保证只删毁灭的点之间的，十分~~令人怄火~~，难以处理；

但是一个 $2$ 操作的后面，可能有有若干个 $1$ 操作和 $3$ 操作会对它造成影响，非常难办。

因此考虑一个经常在线性基等算法中应用的 trick：把操作倒过来。这样，我们可以先计算每一个 $2$ 操作后面的 $1$、$3$ 操作造成的影响，再处理 $2$ 操作。

同时，我们的 $1$ 和 $3$ 操作变成了加点、加边；操作 $2$ 只删除了“活跃的”两个点之间的边，所以并没有实际作用。

### 2. 处理

现在我们得到的问题变成了只有加点和加边的版本。

容易发现可以倒着枚举时间轴，这样每一个点只被计算一次即可。

我们可以每次看一下哪些点（$1$ 个 / $2$ 个）的状态发生了改变：

如果是加点就进行一次 bfs，更新所有能够到达它的并且没有答案的点；

如果是加边，就把这条边连接的两个点中，所有符合条件的点（即能够在这个时间之前就到达的）分别 bfs 一下即可。

容易发现一个点只会被遍历一次，所以所有的 bfs 加起来是 $O(n)$ 的，总复杂度就是 $O(n+q)$。

## 代码

```cpp
#include <bits/stdc++.h>

// 缺省源已省略qwq

using namespace std;

const int MAXN=300005;

struct Qu{
	int tp,x,y;
}q[MAXN];
int k[MAXN],ans[MAXN];
pair<int,int> e[MAXN];
vector<int> p[MAXN];

bool d[MAXN];

void bfs(int x,int y){
	queue<int> q; q.push(x);
	while(!q.empty()){
		int u=q.front(); q.pop();
		for(register int i=0;i<p[u].size();++i){
			if(ans[p[u][i]]) continue;
			q.push(p[u][i]);
			ans[p[u][i]]=y;
		}
	} 
}

int main(){
	int n,tot=0,m=0,Q; read(n,Q);
	
	for(register int i=1;i<=Q;++i){
		char ch=gc();
		if(ch=='D'){
			int x; read(x); k[x]=1;
			q[i]=(Qu){1,x,0};
		}else if(ch=='A'){
			int x,y; read(x,y);
			e[++m]=make_pair(x,y);
			q[i]=(Qu){2,x,y};
		}else{
			int x; read(x);
			q[i]=(Qu){3,x,0};
			d[x]=1;
		}
	}
	
	for(register int i=1;i<=m;++i){
		if(!d[i]){
			p[e[i].first].push_back(e[i].second);
			p[e[i].second].push_back(e[i].first);
		}
	}
	for(register int i=1;i<=n;++i) if(!k[i]) ans[i]=Q,bfs(i,Q);
	
	
	for(register int i=Q;i>=1;--i){
		if(q[i].tp==1){
			ans[q[i].x]=qmax(ans[q[i].x],i-1);
			p[0].push_back(q[i].x);
			bfs(q[i].x,i-1);
		}else if(q[i].tp==3){
			int u=e[q[i].x].first,v=e[q[i].x].second;
			p[u].push_back(v),p[v].push_back(u);
			if(ans[u]) bfs(u,i-1);
			if(ans[v]) bfs(v,i-1);
		}
	}
	
	for(int i=1;i<=n;i++) write(ans[i]);
	return flush(),0; // 这个 flush() 是缺省源后遗症
}
```

---

## 作者：StillEmpty (赞：0)

目标进度：第（3/100）篇USACO金组题解。

本题充分展现了转化思想。首先，这种连通性问题都是并查集解决的，问题在于并查集只支持合并和查询，无法分裂。我们就要充分利用原题的性质，转化成只有合并操作的问题。

我们称具有活跃节点的连通块是活跃的，显然一个活跃的连通块中所有节点都是有关的。**我们发现如果 `D` 操作不是停用而是启用的话，`R` 操作不是删除而是添加的话，`A` 操作根本没有影响。** 如果观察到这一点，就可以发现应该把所有操作反过来逆推。然后我们就会发现，如果倒着做，所有主要矛盾（雾）都解决了！

具体来说，我们先求出 $Q$ 次操作后的图，作为我们的初始情况。依次读入第 $Q, Q-1, Q-2, \cdots, 1$ 次操作，每次求出这次操作前的情况（也就是逆推）。此时，`A` 操作变成删边，而根据题目，删边后断开的两点都属于活跃的连通块，逆推情况下已经活跃的连通块不会变为不活跃，所以删边根本不影响答案。同理，连边实则可以理解为合并两个不活跃的块或者将一个不活跃的块活跃化（因为一个已经活跃的块再也不会有更新的必要了）。全都圆了。

代码中，使用启发式合并，可以做到 $q + n \log n$。然而其实一个已经活跃过（逆序）的点再也不会更新了，所以我们就不用在集合中再记录这样的点了。这样时间复杂度就 $O(N+ Q)$：
```cpp
#include <bits/stdc++.h>
using namespace std;

const int N = 1e5, Q = 2e5;
int n, q, fa[N+1], ans[N+1]; bool act[N+1], acted[N+1];
struct eT {bool deled; int u, v;};
vector<eT> e; vector<int> sons[N+1];
struct oT {
    char t; int x, y;
} op[Q+1];
int gr(int x) {
    if(x == fa[x]) return x;
    return fa[x] = gr(fa[x]);
}

int main() {
    ios::sync_with_stdio(false);
    cin >> n >> q;
    for(int i = 1; i <= n; ++i) {
        fa[i] = i; acted[i] = true;
    }
    for(int i = 1; i <= q; ++i) {
        cin >> op[i].t >> op[i].x;
        if(op[i].t == 'A') {
            cin >> op[i].y;
            e.push_back(eT{false, op[i].x, op[i].y});
        }
        if(op[i].t == 'D') acted[op[i].x] = false;
        if(op[i].t == 'R') {
            e[op[i].x-1].deled = true;
        }
    }
    for(const eT &i : e) {
        if(i.deled) continue;
        int u = gr(i.u), v = gr(i.v);
        if(u == v) continue;
        fa[u] = v;
    }
    for(int i = 1; i <= n; ++i) {
        act[gr(i)] |= acted[i];
    }
    for(int i = 1; i <= n; ++i) {
        if(act[gr(i)]) ans[i] = q;
        else sons[gr(i)].push_back(i);
    }
    for(int i = q; i >= 1; --i) {
        if(op[i].t == 'A') continue;
        if(op[i].t == 'D') {
            int x = gr(op[i].x);
            if(act[x]) continue;
            for(const int &j : sons[x]) ans[j] = i-1;
            sons[x].clear();
            act[x] = true;
        }
        if(op[i].t == 'R') {
            int u = gr(e[op[i].x-1].u), v = gr(e[op[i].x-1].v);
            if(u == v) continue;
            if(!(act[u] && act[v]) && (act[u] || act[v])) {
                if(act[v]) swap(u, v);
                for(const int &j : sons[v]) ans[j] = i-1;
                sons[v].clear();
            }
            for(const int &j : sons[u]) sons[v].push_back(j);
            sons[u].clear();
            act[v] |= act[u]; fa[u] = v;
        }
    }
    for(int i = 1; i <= n; ++i) cout << ans[i] << endl;
    return 0;
}
```

---

## 作者：I_am_Accepted (赞：0)

### Analysis

发现 A 操作只会两个活跃的农场之间添加一条道路，也就是说，把操作序列 reverse，A 操作只会断开两个活跃的农场之间的一条道路，发现对最终答案不影响。

发现操作 reverse 后只有两种操作：

* D 启用一个农场。

* R 在两个农场之间添加一条道路。

发现这不是并查集模板题吗？/xyx

因为在任意时刻，一个并查集内的点是否「有关」的状态是相同的，所以在根上标记一下即可。

当 「有关」并查集与「无关」并查集合并 或 启用一个农场 时，从根 DFS（所以每个点要用 vector 存儿子集）记录并查集内每个点的最晚时间为当前时刻 $-1$。

本蒟蒻认为本题不用路径压缩而用按秩合并（小的合到大的下面）$O(n\log n)$ 更方便（因为存儿子集合这事让改变树形态这件事变得麻烦）（虽然链表能做到 $O(n)$）。

### Code

```cpp
//Said no more counting dollars. We'll be counting stars.
#include<bits/stdc++.h>
using namespace std;
#define IOS ios::sync_with_stdio(0);cin.tie(0);cout.tie(0)
#define fir first
#define sec second
#define mkp make_pair
#define pb emplace_back
#define For(i,j,k) for(int i=j;i<=k;i++)
#define Rof(i,j,k) for(int i=j;i>=k;i--)
#define N 200010

vector<pair<int,int> > r; 

struct node{
	bool ca;
	int num,time;
};
vector<node> op;
vector<int> e[N];
vector<bool> pan;
char ch;
int f[N],sz[N],n,q;
bool l[N];
int ans[N];
inline int gf(int x){return x==f[x]?x:gf(f[x]);}
inline void dfs(int x,int time){
	ans[x]=time;
	for(int i:e[x]) dfs(i,time);
}
signed main(){IOS;
	cin>>n>>q;
	For(i,1,n) f[i]=i,sz[i]=1,l[i]=1;
	int x,y;
	r.pb(mkp(0,0));
	pan.pb(0);
	For(i,1,q){
		cin>>ch;
		if(ch=='A'){
			cin>>x>>y;
			r.pb(mkp(x,y));
			pan.pb(1);
			continue;
		}
		cin>>x;
		op.pb((node){ch=='D',x,i});
		if(ch=='D') l[x]=0;
		else pan[x]=0;
	}
	int len=r.size();
	For(i,0,len-1) if(pan[i]) op.pb((node){0,i,q+1});
	For(i,1,n) if(l[i]) ans[i]=q;
	reverse(op.begin(),op.end());
	for(auto i:op){
		if(i.ca){
			x=gf(i.num);
			if(!l[x]) l[x]=1,dfs(x,i.time-1);
		}else{
			x=gf(r[i.num].fir);
			y=gf(r[i.num].sec);
			if(x==y) continue;
			if(!l[x] && l[y]) dfs(x,i.time-1);
			if(l[x] && !l[y]) dfs(y,i.time-1);
			if(sz[x]<sz[y]) swap(x,y);
			f[y]=x;
			e[x].pb(y);
			l[x]|=l[y];
			sz[x]+=sz[y];
		}
	}
	For(i,1,n) cout<<ans[i]<<endl;
return 0;}
```

---

## 作者：YangHHao (赞：0)

## 题意简述

有一张图 $n$ 个点，初始都被激活，$q$ 次操作，每次做下列操作之一：
	
    1.使一个点失活
    2.连边
    3.断边
    
问每个点最后在哪个操作后与一个激活的点处于同一连通块，此时它是“有关的”

$1 \le n \le 10^5,1 \le q \le 2 \times 10^5$

## 分析

如果从前往后模拟，那 TLE 没跑了

考虑到要求的答案是一个点最后一次满足条件的时间，可以先读入，记录下每个点的状态，然后倒着模拟

每次加边或激活(失活倒过来就变成激活)时，dfs 遍历没有“有关”过的点

因为所有有关的点的可到达点都有关，故无关的点不与任何有关的点连通，故以上方法可以历经所有有关点

所有点都是最后一次有关时被遍历到，之后就不再被 dfs 到，故此部分时间复杂度为 $O(n)$

**但是**，如果用邻接表存边，删边时复杂度会爆到 $O(n)$，然后总复杂度变成 $O(n \times q)$!

考虑使用 multiset，插入和删除操作都是 $\log$ 级别，总复杂度为 $O(n + q \log n)$，可以通过本题

## 核心代码（已去除头文件）

```cpp
using namespace std;
const int N=1e5+10,Q=2e5+10;
int n,ans[N];
bool active[N];
int q,cnt=0;
int type[Q],cat[Q][2]; //cat的含义见读入 
int rk[Q];//第i条加入的道路所在操作的编号 
multiset<int>to[N];
void add(int x,int y){
	to[x].insert(y);
}
void remove(int x,int y){
	to[x].erase(y);
}
void AddEdge(int x,int y){
	add(x,y);
	add(y,x);
}
void RemoveEdge(int x,int y){
	remove(x,y);
	remove(y,x);
}
void dfs(int x,int time){
	for(auto nxt:to[x]){
		if(ans[nxt]!=-1)continue; //如果已经“有关”过就不用再访问了 
		ans[nxt]=time;
		dfs(nxt,time);
	}
}
int main(){
	ios::sync_with_stdio(false);
	memset(ans,-1,sizeof(ans));
	cin>>n>>q;
	for(int i=1;i<=n;i++)
		active[i]=1;
	string s; //不能直接用char,会读入换行符 
	for(int i=1;i<=q;i++){
		cin>s;
		switch(s[0]){
			case 'D':{
				type[i]=0;
				cin>>cat[i][0];
				active[cat[i][0]]=0;
				break;
			}
			case 'A':{
				type[i]=1;
				rk[++cnt]=i;
				cin>>cat[i][0]>>cat[i][1];
				AddEdge(cat[i][0],cat[i][1]);
				break;
			}
			case 'R':{
				type[i]=2;
				int cx;
				cin>>cx;
				cat[i][0]=cat[rk[cx]][0];
				cat[i][1]=cat[rk[cx]][1];
				RemoveEdge(cat[i][0],cat[i][1]);
				break;
			}
		}
	}
	for(int i=1;i<=n;i++){
		if(active[i]){
			ans[i]=q;
			dfs(i,q);
		}
	}
	for(int i=q;i>=1;i--){ //反过来跑一遍 
		switch(type[i]){
			case 0:{
				if(ans[cat[i][0]]==-1){
					ans[cat[i][0]]=i-1;
					dfs(cat[i][0],i-1);
				}
				break;
			}
			case 1:{
				RemoveEdge(cat[i][0],cat[i][1]);
				break;
			}
			case 2:{
				AddEdge(cat[i][0],cat[i][1]);
				if(ans[cat[i][0]]!=-1&&ans[cat[i][1]]==-1){  //更新其中一边 
					ans[cat[i][1]]=i-1;
					dfs(cat[i][1],i-1);
				}
				else if(ans[cat[i][1]]!=-1&&ans[cat[i][0]]==-1){ //另一边 
					ans[cat[i][0]]=i-1;
					dfs(cat[i][0],i-1);
				}
				break;
			}
		}
	}
	for(int i=1;i<=n;i++)
		cout<<ans[i]<<'\n';
	return 0;
}

```



---

