# [NOI Online #1 提高组] 序列

## 题目背景

## 由于本题数据较难构造，所以无法保证卡掉所有错误做法。



## 题目描述

小 D 有一个长度为 $n$ 的整数序列 $a_{1 \dots n}$，她想通过若干次操作把它变成序列 $b_i$。

小 D 有 $m$ 种可选的操作，第 $i$ 种操作可使用三元组 $(t_i,u_i,v_i)$ 描述：若 $t_i=1$，则她可以使 $a_{u_i}$ 与 $a_{v_i}$ 都加一或都减一；若 $t_i=2$，则她可以使 $a_{u_i}$ 减一、$a_{v_i}$ 加一，或是 $a_{u_i}$ 加一、$a_{v_i}$ 减一，因此当 $u_i=v_i$ 时，这种操作相当于没有操作。

小 D 可以以任意顺序执行操作，且每种操作都可进行无限次。现在给定序列与所有操作，请你帮她判断是否存在一种方案能将 $a_i$ 变为 $b_i$。题目保证两个序列长度都为 $n$。若方案存在请输出 `YES`，否则输出 `NO`。

## 说明/提示

#### 样例 1 解释

第一组数据：使用一次操作 $1$。  
第二组数据：使用三次操作 $1$。  
第三组数据：使用三次操作 $1$，令 $a_1,a_2$ 都增加 $3$，再使用一次操作 $2$，令 $a_1,a_3$ 都增加 $1$。

---

#### 数据范围与提示

对于测试点 $1 \sim 5$：$n=2$，$m=1$，$a_i,b_i \le 99$，$u_1 \ne v_1$，$t_1=1$。  
对于测试点 $6 \sim 10$：$n=2$，$m=1$，$a_i,b_i \le 99$，$u_1 \ne v_1$，$t_1=2$。  
对于测试点 $11 \sim 12$：$n=2$，$a_i,b_i \le 99$，$u_i \ne v_i$。  
对于测试点 $13 \sim 16$：$t_i=2$。  
对于测试点 $17$：$n,m \le 20$。  
对于测试点 $18$：$n,m \le 10^3$。  
对于所有测试点：$1 \le T \le 10$，$1 \le n,m \le 10^5$，$1 \le a_i,b_i \le 10^9$，$t_i \in \{1,2\}$，$1\le u_i,v_i \le n$。

## 样例 #1

### 输入

```
3
1 1
1
3
1 1 1
2 3
1 2
4 5
1 1 2
2 1 2
1 1 2
3 3
1 2 3
5 5 4
1 1 2
1 1 3
2 2 3```

### 输出

```
YES
YES
YES```

# 题解

## 作者：xht (赞：81)

把每个位置看成一个点。

首先对于 $2$ 操作连边。

如果两个位置连通则意味着可以使一个位置 $+1$ 另一个位置 $-1$。

即对于一个连通块，我们可以在保证**总和**不变的情况下任意的加减，因此并查集将一个连通块缩成一个点。

再对于 $1$ 操作连边。

如果形成的图是二分图，则可以在保证**左部点总和与右部点总和的差**不变的情况下任意的加减。

如果形成的图不是二分图，则可以在保证**总和奇偶性**不变的情况下任意的加减。

```cpp
const int N = 1e5 + 7;
int n, m, a[N], b[N], f[N], p[N], q[N], t, v[N];
ll s[N], c[3];
vi e[N];

int get(int x) {
	return x == f[x] ? x : (f[x] = get(f[x]));
}

inline bool dfs(int x, int k) {
	v[x] = k, c[k] += s[x];
	bool ok = 1;
	for (ui i = 0; i < e[x].size(); i++) {
		int y = e[x][i];
		if (v[y] == v[x]) ok = 0;
		if (!v[y] && !dfs(y, 3 - k)) ok = 0;
	}
	return ok;
}

inline bool solve() {
	rd(n), rd(m), rda(a, n), rda(b, n), t = 0;
	for (int i = 1; i <= n; i++) f[i] = i, s[i] = v[i] = 0, e[i].clear();
	for (int i = 1, o, x, y; i <= m; i++) {
		rd(o), rd(x), rd(y);
		if (o == 2) f[get(x)] = get(y);
		else p[++t] = x, q[t] = y;
	}
	for (int i = 1; i <= n; i++) s[get(i)] += b[i] - a[i];
	for (int i = 1; i <= t; i++) {
		int x = get(p[i]), y = get(q[i]);
		e[x].pb(y), e[y].pb(x);
	}
	for (int i = 1; i <= n; i++)
		if (get(i) == i && !v[i]) {
			c[1] = c[2] = 0;
			bool ok = dfs(i, 1);
			if (ok && c[1] != c[2]) return 0;
			if (!ok && ((c[1] ^ c[2]) & 1)) return 0;
		}
	return 1;
}

int main() {
	int T;
	rd(T);
	while (T--) prints(solve() ? "YES" : "NO");
	return 0;
}
```

---

## 作者：灵梦 (赞：56)

不妨把所有的 $b_i$ 变成 $b_i-a_i$，这样所有 $a_i$ 就变成 $0$ 了。然后考虑建图。把 $i$ 号点的权值设为 $a_i$ 的值，对于每个 $t_i=2$ 的操作，在图中连一条无向边 $(u_i,v_i)$。那么每条这样的边的意义就是把它其中一个端点的部分权值“转运”到另一个端点，但对总权值没有影响。可以看出每个连通块中的任意两点的权值都是可以互相转运的。若某个连通块内所有点的权值之和等于 $b_i$ 之和，这个连通块就是有解的。答案为 `YES` 当且仅当所有连通块都有解。下面记点 $u$ 所在的连通块编号为 $bel_u$。

而 $t_i=1$ 的操作就可以对总权值产生影响了。我们把它也看成这张图里的一条边，由上面的内容容易看出 $u_i$ 或 $v_i$ 连在同一个连通块中的任意一点都是相同的（对该连通块的权值和贡献相同）。那么我们把连通块缩点，在新图上连边 $(bel_{u_i},bel_{v_i})$ 即可。若 $u_i$ 和 $v_i$ 所在连通块相同，则将这个连通块打上标记 $tag=1$，表示该连通块内部可以对自身权值和产生 $2$ 的倍数的贡献。

考虑新图的一条路径 $(x,y)$（不一定是简单路径），发现若这条路径长度为偶数，则 $x$ 与 $y$ 之间的权值也是可以相互转运的（可以画图看一下）。那么对于新图中包含奇环的连通块，任意两点间一定存在一条长度为偶数的路径。也就是说，可以将这个大的连通块再次缩成一个点。由于这个连通块里一定有 $t_i=1$ 的边，所以可以认为它的 $tag=1$，那么它有解的条件就是权值和为偶数。

而对于不包含奇环的连通块，它一定是一个二分图。将其黑白染色，那么黑点到黑点、白点到白点的权值都可以互相转运，我们将黑点集和白点集分别缩点。黑点与白点之间只有长度为奇数的路径，即可以将黑点集的权值和 与 白点集的权值和同时加上一个值。那么我们现在已经可以得出这个连通块有解的条件了：

1. 权值和为偶数；
2. 若该连通块中所有点的 $tag$ 都为 $0$，则黑点和白点的 $b_i$ 之和相等。

证明比较显然。第二次的“缩点”不需要真缩，DFS 判断一下就可以了。

于是这道题就做完了，复杂度 $O(Tn)$。记得开 long long。

代码：

```cpp
#include <cstdio>
#include <cstring>
#include <vector>
using namespace std;
typedef long long ll;
const int MAXN=110000;
struct Edge
{
	int u, v;
	Edge() {}
	Edge(int a, int b): u(a), v(b) {}
} e[MAXN];
vector<int> g[MAXN], h[MAXN];
int a[MAXN];
int bel[MAXN], bw[MAXN];
ll sum[MAXN];
bool tag[MAXN];
void dfs1(int u, int c)
{
	bel[u]=c, sum[c]+=a[u];
	for (int i=0; i<g[u].size(); i++)
	{
		int v=g[u][i];
		if (!bel[v]) dfs1(v, c);
	}
}
bool dfs2(int u, int c, bool& t, ll& sb, ll& sw)
{
	if (~bw[u]) return bw[u]==c;
	bw[u]=c, t|=tag[u];
	if (c==0) sb+=sum[u];
	else sw+=sum[u];
	bool ret=1;
	for (int i=0; i<h[u].size(); i++)
	{
		int v=h[u][i];
		ret&=dfs2(v, c^1, t, sb, sw);
	}
	return ret;
}
int main()
{
	freopen("sequence.in", "r", stdin);
	freopen("sequence.out", "w", stdout);
	int T;
	scanf("%d", &T);
	while (T--)
	{
		int n, m, p=0, k=0;
		scanf("%d%d", &n, &m);
		for (int i=1; i<=n; i++) scanf("%d", &a[i]);
		for (int i=1; i<=n; i++)
		{
			int x; scanf("%d", &x); a[i]=x-a[i];
			g[i].clear(), h[i].clear();
		}
		for (int i=1; i<=m; i++)
		{
			int t, u, v;
			scanf("%d%d%d", &t, &u, &v);
			if (t==1) e[++p]=Edge(u, v);
			else g[u].push_back(v), g[v].push_back(u);
		}
		memset(bel, 0, sizeof bel);
		memset(sum, 0, sizeof sum);
		memset(tag, 0, sizeof tag);
		for (int i=1; i<=n; i++)
			if (!bel[i]) dfs1(i, ++k);
		for (int i=1; i<=p; i++)
			if (bel[e[i].u]==bel[e[i].v]) tag[bel[e[i].u]]=1;
			else
			{
				h[bel[e[i].u]].push_back(bel[e[i].v]);
				h[bel[e[i].v]].push_back(bel[e[i].u]);
			}
		memset(bw, -1, sizeof bw);
		bool ans=1;
		for (int i=1; i<=k; i++)
			if (bw[i]==-1)
			{
				bool tg=0; ll sumb=0, sumw=0;
				if (dfs2(i, 0, tg, sumb, sumw))
					if (tg) ans&=(sumb+sumw)%2==0;
					else ans&=sumb==sumw;
				else ans&=(sumb+sumw)%2==0;
			}
		puts(ans?"YES":"NO");
	}
	return 0;
}
```



---

## 作者：Sangber (赞：46)

刚刚在洛谷上翻了翻这题的题解，发现没有人用我这种做法，所以来分享一下。

我这个做法代码实现上相对要简单得多（不需要过于巧妙的建图方式以及并查集、二分图染色等操作）。

首先我们来分析一下这两种操作：

我们发现2操作可以看成是两个点 $u, v$ 之间相互传递一部分数值，前者加上的刚好等于后者减去的。

我们便尝试连边 $(u, v)$ 表示这两个点之间有传递关系 **注意本文讲到的连边都是指连双向边**

1操作的话就不太好办了，因为我们无法通过直接连边，来确保两个点的值同时变化相同的数值。

那么1操作能不能转变成2操作呢？

我们回到题面：要求若干次操作后 $a_i = b_i$ 。

一般的想法都是直接去弥补 $a_i, b_i$ 间的差值，我们知道，两个数同时加上或减去一个数，它们的差值不变。

所以我们可以拓宽思路，把 $a_i$ 向 $b_i$ 的单向转变，化作 $a_i$ 和 $b_i$ 的数值在两者经过若干次操作后的相等。

接下来我们就要通过改变 $a_i$ 和 $b_i$ 的值来实现单个位置 +1 或 -1 的操作了。

下面我们就用 $i$ 来代表 $a_i$ 对应的点的编号，$i^{\prime}$ 来表示 $b_i$ 对应的点的编号。

那么首先对于可以执行2操作的一对点 $(u, v)$ ，我们就可以连边 $(u, v), (u^{\prime}, v^{\prime})$ 表示这两个点的 $a_i$ 和 $b_i$ 之间都分别可以进行上文讲到的数值传递。

对于1操作的一对点 $(u, v)$ ，我们这样连边：

如果我们是想让 $a_u$ 和 $a_v$ 的值都加上1，那么连边 $(u^{\prime}, v)$；

如果我们是想让 $a_u$ 和 $a_v$ 的值都减去1，那么连边 $(u, v^{\prime})$；

为什么这样可行呢？因为我们之前提到了，$a_i$ 和 $b_i$ 需要在各自经过若干次操作后相等，那么我们可以认为 $a_i$ 和 $b_i$ 的大小是相对的，通过改变其中一个的值，就可以达到改变另一个值的目的。

那么我们再来分析一下这样的连边过程：连边 $(u^{\prime}, v)$ ，表示 $b_u$ 和 $a_v$ 之间可以传递数值。

那么我们如果让 $b_u$ 加上1，$a_v$ 减去1，进行这样一次数值传递的话，就 $a_u$ 和 $b_u$ 的相对大小而言，$b_u$ 加上1，等价于让 $a_u$ 减去1，也就是说我们整体上就实现了两个位置同时-1的操作，+1 的操作同理。

那么我们就得到了一张图。

这张图可能有很多个连通块，那么根据之前对于数值传递的定义，**同一个连通块内的任意两个点都可以直接或间接地进行数值传递** 。

而且不难发现所有连出来的边都是对称的，也就是说 **这张图是轴对称的** 。

既然图是对称的，那么 $i$ 和 $i^{\prime}$ 要么在同一个连通块内，要么就是分居两个对称的连通块。

如果这两个点位于同一个连通块，我们就只需要让这个大联通块的内部数值总和为偶数即可。

因为在这个联通块内，我们可以随意地进行数值传递操作，所以我们只需要关心数值的总和，又因为这个连通块是对称的，我们就需要得出一种可以让两边的数值也对称的方案，那么很显然只有总和为偶数的时候才能做到。

分居两个连通块就更好判断了，直接判断两个连通块各自的内部数值总和是否相等即可。

那么到这里我们就完美地解决了这道题了，复杂度 $O(Tn)$ 。

参考代码：

```cpp
#include <cstring>
#include <cstdio>
#define rg register
#define file(x) freopen(x".in", "r", stdin), freopen(x".out", "w", stdout)
template < class T > inline void read(T& s) {
    s = 0; int f = 0; char c = getchar();
    while ('0' > c || c > '9') f |= c == '-', c = getchar();
    while ('0' <= c && c <= '9') s = s * 10 + c - 48, c = getchar();
    s = f ? -s : s;
}

typedef long long LL;
const int _ = 2e5 + 5;

int tot, head[_]; struct Edge { int v, nxt; } edge[_ << 1];
inline void Add_edge(int u, int v) { edge[++tot] = (Edge) { v, head[u] }, head[u] = tot; }
inline void link(int u, int v) { Add_edge(u, v), Add_edge(v, u); }

int n, m, val[_], num, pos[_]; LL sum[_];

inline void init() {
    num = tot = 0;
    memset(head, 0, sizeof head);
    memset(sum, 0, sizeof sum);
    memset(pos, 0, sizeof pos);
}

inline void dfs(int u, int p) {
    sum[pos[u] = p] += val[u];
    for (rg int i = head[u]; i; i = edge[i].nxt)
        if (!pos[edge[i].v]) dfs(edge[i].v, p);
}

inline void solve() {
    init(), read(n), read(m);
    for (rg int i = 1; i <= n << 1; ++i) read(val[i]);
    for (rg int t, x, y, i = 1; i <= m; ++i) {
    	read(t), read(x), read(y);
        if (t == 1) link(x, y + n), link(y, x + n);
        if (t == 2) link(x, y), link(x + n, y + n);
    }
    for (rg int i = 1; i <= n << 1; ++i) if (!pos[i]) dfs(i, ++num);
    int flag = 1;
    for (rg int i = 1; i <= n; ++i) {
    	if (pos[i] != pos[i + n])
            flag &= sum[pos[i]] == sum[pos[i + n]];
        else
            flag &= sum[pos[i]] % 2 == 0;
    }
    puts(flag ? "YES" : "NO");
}

int main() {
//  file("sequence");
    int T; read(T);
    while (T--) solve();
    return 0;
}

```

---

## 作者：dengyaotriangle (赞：17)

[梦 幻 联 动](https://www.luogu.com.cn/blog/EntropyIncreaser/solution-p6187)

首先发现我们只关心 $a$、$b$ 的差，故令 $c_i=b_i-a_i$

考虑把两种操作规约到同一种限制中

第一种操作：$u\leftarrow u+d$、$v\leftarrow v+d$，看上去挺顺眼

第二种操作：$u\leftarrow u+d$、$v\leftarrow v-d$，就需要把它艹掉

具体来讲，对于每一个第二种操作的数对，$(x,y)$，建立一个新数 $z$ ，并使 $c_z=0$ ，添加两个第一种操作：$(x,z)$、$(y,z)$，并删除原来的第二种

很显然这样改变是等价的，故下文中假设只有第一种操作

我们考虑以每对可以操作的边建图

首先，这个图的联通块间是独立的，只有每一个联通块都合法才可以

故我们对一个联通块 $S$ 讨论其合法性

首先，$2\mid\sum\limits_{u\in S}c_u$，因为每次总数增加的都是 2 的倍数

接下来呢，发现不太好整了，还有啥玩意性质呢

根据做类似的题的人参经验，我们考虑提取出这个联通块的任意一个有根生成树

那么如果我们只考虑树上的边的操作，那么发现，我们可以从叶子节点一步一步反推出来每一条边的 $d_i$，具体来讲，若 $d_u$ 为 $u$ 与它祖先的边的 $d$，那么 $d_u=c_u-\sum\limits_{u\rightarrow v}d_v$ （指对于 $u$ 的每一个儿子）

那么令根为 $r$ ，合法的充要条件是 $d_r=0$，因为 $r$ 没有向祖先的边

然后我们就发现 $d_r=\sum\limits_{u} c_u\times (-1)^{dep_u}$ 其中 $dep_u$ 为 $u$ 点深度，从0开始

故只需要判断深度为奇数和偶数的点各自的 $\sum c_u$ 是否相同即可

但是！不只有树上的边，还有其它的边，这些边就对判定就有了一些影响

对于一个不在树上的边 $(x,y)$，那么使用它的效果就是 $c_x\leftarrow c_x+\lambda$，$c_y\leftarrow c_y+\lambda$

然后看看它对 $d_r$ 的贡献，$c_x$ 和 $c_y$ 的系数分别是 $(-1)^{dep_x}$ 与 $(-1)^{dep_y}$，故加起来对于 $d_r$ 的效果就是 $d_r\leftarrow d_r+\lambda\left((-1)^{dep_x}+(-1)^{dep_y}\right)$

当 $dep_x \equiv dep_y \pmod{2}$ 时，我们惊奇的发现发现贡献就是 $d_r\leftarrow d_r \pm2\lambda$ ，而 $\lambda$ 可以取任意值，这就说明 $d_r$ 可以变成任意值！所以如果选出来的这棵树外有连接深度差为2的倍数的边，那么一定可行。有连接深度差为2的倍数的边这件事其实就相当于原联通块中有奇环，也就相当于原来的联通块不是二分图

否则呢？$dep_x \not\equiv dep_y \pmod{2}$ 是，我们发现贡献是 $0$，故一个偶环对答案没有影响

所以总结起来就是：
- 把操作2建虚点，全变成操作1
- 把操作1当成边建图
- 对于每一个联通块分开考虑
- 如果一个联通块的 $c_u$ 的和为奇数则不可行
- 如果一个联通块是二分图且两侧 $c_u$ 的和不相等则不可行
- 其余情况都可行
- 如果所有联通块都可行答案才是YES

另外，说句题外话，我觉得这个样例非常强。

---

## 作者：封禁用户 (赞：16)

# 思路
大家都太强了……看了半天都是图论大神。

我只好写一个蒟蒻的做法，小小的 __带权并查集__。

我是这么想哒，考虑 $i,j$ 和 $j,k$ 两种操作，能够给 $i,k$ 带来什么：

- 如果 $i,j$ 是可以同时增加的，而 $j,k$ 也是可以同时减少的，那么 $i,j$ 同时增加 $x$ ，$j,k$ 同时减少 $x$ ，完美地做到了 $i,k$ 一个增加、一个减少。
- 如果 $i,j$ 是可以同时增加的，而 $j,k$ 是一加一减的，那么 $i,k$ 通过 $j$ 这个中介，就可以做到 $i$ 增加一、$k$ 也增加一。
- 如果都是一加一减型，那么可以认为存在一个 $i,k$ 的一加一减型。

所以说，对于这种三个点的关系，其中一个作为中介的时候，如果 $i,j$ 和 $j,k$ 的状态不同，就可以做到同时增加；否则得到一增一减的结果。

于是，__把同时增加设为$1$、一增一减设为$0$，连边之后，二者的关系为路径的异或和__。而且，这也是自洽的，因为自己到自己的长度是$0$，相当于增加了又减少，没有问题。

然后就有了带权并查集的思路，因为 __所有的操作可以等价于直接与并查集的根操作__，毕竟是异或和，$dis(a,rt)\oplus dis(b,rt)=dis(a,b)$ 嘛，所以 $a,b$ 本来就可以选择 $root$ 作为中介点。

加出来一个环怎么办？如果这会导致一个长度为$1$的环，那么在根节点上打一个标记，表示“__可以自行消化偶数权值__”。否则，没什么鸟用，因为每个节点本身就有一个隐藏的长度为零的自环。

最后，暴力检查每一个根节点是否达到了要求即可，因为根节点就已经没有人能够跟它操作了，除了自环消化偶数。

我没有打启发式合并，普通的路径压缩，最坏是 $\mathcal O(n\log n)$ 的。还是能过。

~~却因为没有清空挂掉了。事实上，三道题都因为奇怪的原因挂掉了~~

# 代码
实现的时候，可以只存储 $b_i-a_i$ ，也就是 $a_i$ 需要的变化量。

```cpp
#include <cstdio>
#include <iostream>
#include <vector>
using namespace std;
inline long long readint(){
	long long a = 0; char c = getchar(), f = 1;
	for(; c<'0'||c>'9'; c=getchar())
		if(c == '-') f = -f;
	for(; '0'<=c&&c<='9'; c=getchar())
		a = (a<<3)+(a<<1)+(c^48);
	return a*f;
}
inline void writeint(long long x){
	if(x < 0) putchar('-'), x = -x;
	if(x > 9) writeint(x/10);
	putchar((x%10)^48);
}

# define MB template < typename T >
MB void getMax(T &a,const T &b){ if(a < b) a = b; }
MB void getMin(T &a,const T &b){ if(b < a) a = b; }

const int MaxN = 100005;

int fa[MaxN], val[MaxN];
inline int findSet(int a){
	if(fa[a] == a) return a;
	int root = findSet(fa[a]);
	val[a] ^= val[fa[a]];
	return fa[a] = root;
}
bool win[MaxN]; // 是否有长度为1的自环
void unionSet(int a,int b,int c){
	int x = findSet(a), y = findSet(b);
	int dis = val[a]^c^val[b];
	if(x == y) win[x] = win[x] or dis == 1;
	else{
		fa[x] = y, val[x] = dis;
		win[y] = win[y] or win[x];
	}
}

long long a[MaxN]; int n, m;
int main(){
	// freopen("sequence.in","r",stdin);
	// freopen("sequence.out","w",stdout);
	for(int T=readint(); T; --T){
		n = readint(), m = readint();
		for(int i=1; i<=n; ++i){
			a[i] = readint();
			fa[i] = i, val[i] = 0;
			win[i] = false;
		}
		for(int i=1; i<=n; ++i)
			a[i] = readint()-a[i];
		for(int opt,x; m; --m){
			opt = readint()%2, x = readint();
			unionSet(x,readint(),opt);
		}
		for(int i=1,rt; i<=n; ++i){
			rt = findSet(i);
			if(rt == i) continue;
			if(val[i] == 1) // a[i]-=a[i],a[rt]-=a[i]
				a[rt] -= a[i]; // 权值同时增加a[i] ...
			else a[rt] += a[i]; // ... 需求便减少了
		}
		bool ok = true;
		for(int i=1,rt; i<=n and ok; ++i){
			rt = findSet(i);
			if(rt != i) continue;
			if(win[rt]) a[rt] %= 2;
			if(a[rt] != 0) ok = false;
		}
		if(ok) puts("YES"); else puts("NO");
	}
	return 0;
}
```

也许是错的——希望有大佬在看出错误之后 ~~心狠手辣地、尖酸刻薄地~~ 指出，受教了！

---

## 作者：wrpwrp (赞：16)

本来考场切了的，结果代码没保存，爆炸成80，自闭了。  
考场上我是一个一个部分分做的，所以这里我也一个一个部分分写。
## 0pts $n=1$
这个档位是针对样例写的。。。因为不写我就过不了样例。。。
显然如果有一个1操作就输出YES，没有就看相不相等完事。。。
贴一个没有什么用的代码。
```cpp
inline void Solve_0pts()
{
	if(flg1==1) 
	{
		printf("YES\n");
	}
	else 
		if(a[1]==b[1])
		{
			printf("YES\n");
		}
		else
		{
			printf("NO\n");
		}
		return ;
}
```
  
## 60pts $n=2$
### 分类讨论：  
1.如果只有1操作，那很显然，只要$a1-b1=a2-b2$就完事了。   
2.如果只有2操作，那也很显然，只要$a1-b1==b2-a2$就完事了。  
3.如果1,2操作都有，那么假设$a1+k1+k2=b1$,$a2+k1-k2=b2$,合并一下就可以得到$a1+a2-b1-b2=-2*k2$,所以只要作差然后判定一下是不是偶数就可以了。  
贴一个有点用的代码。
```cpp
inline void Solve_60pts()
{
	if(flg1)
	{
		if(a[1]-b[1]==a[2]-b[2])
		{
			printf("YES\n");
			return;
		}
	}
	if(flg2)
	{
		if(a[1]-b[1]==b[2]-a[2])
		{
			printf("YES\n");
			return;
		}
	}
	if(flg1&&flg2)
	{
		if((a[1]+a[2]-b[1]-b[2])%2==0)
		{
			printf("YES\n");
			return;
		}
	}
	printf("NO\n");
}
```
## 80pts $ti=2$
发现被链接的两个点的值可以互相流动，于是把链接的点在a和b数列里分别缩点，这里用并查集实现。由于同一个集合里的点的值可以互相流动，所以这里只要a数列和b数列每个对应集合里的点权和相同，那么就一定是合法的，否则不合法，代码也比较好写。  
```cpp
inline int find(int x) 
{
	return x==fa[x]?x:fa[x]=find(fa[x]);
}

inline void merge(int x,int y)
{
	int fx=find(x);
	int fy=find(y);
	va[fy]+=va[fx];
	va[fx]=0;fa[fx]=fy;
}

inline void Solve_80pts()
{
	for(R int i=1;i<=n*2;i++) fa[i]=i;
	for(R int i=1;i<=n;i++) va[i]=a[i];
	for(R int i=1;i<=n;i++) va[n+i]=b[i];
	for(R int i=1;i<=m;i++)
	{
		int x=u[i],y=v[i];
		if(find(x)==find(y)) continue;
		merge(x,y);
		merge(x+n,y+n);
	}
	for(R int i=1;i<=n;i++)
		if(find(i)==i)
		{
			if(va[i]!=va[i+n])
			{
				printf("NO\n");
				return;
			}
		}
	printf("YES\n");
}
```
## 100pts
为了方便，先用一个sm数组存下a与b对应位置的差值。
发现80分缩点的做法十分舒适，所以先把操作2缩点，然后就只剩下操作1了。由于操作2已经缩点，操作1再缩点感觉不太现实，于是考虑连边（~~好玄学~~）。  把1操作的两个点连边之后（注意是连缩点之后的）。然后继续开始手玩样例，发现假如有两个点$(x,y)$,使得这两个点之间有一条长度为偶数的路径，那这两个点之间也是可以相互交流权值的。更特别一点的是，如果一个联通块里面有一个长度为奇数的环，那任意两个点之间都会有一条长度为偶数的路径。为什么呢，因为环上的点显然是有的，环外的点如果到一个点不经过环长度为奇数，那就去跑一边环就变成偶数了，所以这个命题成立。然后就可以把有奇环的联通块看成一个点了。那么这样的一个块，
如果差值的和或者差是偶数，就是可以的，否则就不行。注意如果一个点连成了自环，那么也是可以的算成这一种块。如果这个块恰好是一个二分图，那么黑白染色之后，权值就只可以在黑点集合中的点之间和白点集合中的点之间各自流动，因为同一个集合中的任意两个点的距离必定是偶数。所以就计算黑点差值之和与白点的差值之和是否相同就可以了。我的代码中没有统计和，是直接一边染色一边相减的。对于单独的点，我们也把它看成一个二分图来处理即可。部分代码就懒得丢了，就是完整代码里100pts的部分（突然反应过来，那我上面丢代码干啥？？？）
## 完整代码
```cpp
#include <cstdio>
#include <cstdlib>
#include <cstring>

using namespace std;

#define R register
#define ll long long
const int MAXN=2e5+10;

int n,m;
int a[MAXN],b[MAXN];
int opt[MAXN],u[MAXN],v[MAXN];

int flg1=0,flg2=0;

inline void Init()
{
	scanf("%d%d",&n,&m);
	for(R int i=1;i<=n;i++) scanf("%d",&a[i]);
	for(R int i=1;i<=n;i++)	scanf("%d",&b[i]);
	flg1=flg2=0;
	for(R int i=1;i<=m;i++)
	{
		scanf("%d%d%d",&opt[i],&u[i],&v[i]);
		if(opt[i]==1) flg1=1;
		if(opt[i]==2) flg2=1;
	}

}

inline void Solve_0pts()
{
	if(flg1==1) 
	{
		printf("YES\n");
	}
	else 
		if(a[1]==b[1])
		{
			printf("YES\n");
		}
		else
		{
			printf("NO\n");
		}
		return ;
}

inline void Solve_60pts()
{
	if(flg1)
	{
		if(a[1]-b[1]==a[2]-b[2])
		{
			printf("YES\n");
			return;
		}
	}
	if(flg2)
	{
		if(a[1]-b[1]==b[2]-a[2])
		{
			printf("YES\n");
			return;
		}
	}
	if(flg1&&flg2)
	{
		if((a[1]+a[2]-b[1]-b[2])%2==0)
		{
			printf("YES\n");
			return;
		}
	}
	printf("NO\n");
}

int fa[MAXN];
ll va[MAXN];

inline int find(int x) 
{
	return x==fa[x]?x:fa[x]=find(fa[x]);
}

inline void merge(int x,int y)
{
	int fx=find(x);
	int fy=find(y);
	va[fy]+=va[fx];
	va[fx]=0;fa[fx]=fy;
}

inline void Solve_80pts()
{
	for(R int i=1;i<=n*2;i++) fa[i]=i;
	for(R int i=1;i<=n;i++) va[i]=a[i];
	for(R int i=1;i<=n;i++) va[n+i]=b[i];
	for(R int i=1;i<=m;i++)
	{
		int x=u[i],y=v[i];
		if(find(x)==find(y)) continue;
		merge(x,y);
		merge(x+n,y+n);
	}
	for(R int i=1;i<=n;i++)
		if(find(i)==i)
		{
			if(va[i]!=va[i+n])
			{
				printf("NO\n");
				return;
			}
		}
	printf("YES\n");
}

int To[MAXN+MAXN],Next[MAXN+MAXN],Head[MAXN],cnt;

inline void add(int x,int y)
{
	cnt++;
	To[cnt]=y;
	Next[cnt]=Head[x];
	Head[x]=cnt;
}

int sm[MAXN];
int co[MAXN];

int sum,tag;

inline void dfs(int x,int col)
{
	co[x]=col;
	if(col) sum+=sm[x];
	else sum-=sm[x];
	for(R int i=Head[x];i;i=Next[i])
	{
		int y=To[i];
		if(co[y]==-1)
			dfs(y,col^1);
		else
			if(co[x]==co[y]) tag=1;
	}
}

inline void Solve_100pts()
{
	memset(Head,0,sizeof(Head));
	memset(co,-1,sizeof(co));
	cnt=0;
	for(R int i=1;i<=n;i++)
		sm[i]=a[i]-b[i];
	for(R int i=1;i<=n;i++)
		fa[i]=i;
	for(R int i=1;i<=m;i++)
	{
		if(opt[i]==1) continue;
		int x=u[i],y=v[i];
		if(find(x)==find(y)) continue;
		int fx=find(x),fy=find(y);
		fa[fx]=fy;sm[fy]+=sm[fx];sm[fx]=0;
	}
	for(R int i=1;i<=m;i++)
	{
		if(opt[i]==2) continue;
		int x=u[i],y=v[i];
		x=find(x);y=find(y);
		add(x,y);add(y,x);
	}
	bool flg=1;
	for(R int i=1;i<=n;i++)
		if(find(i)==i&&co[i]==-1)
		{
			sum=tag=0;
			dfs(i,0);
			for(R int j=Head[i];j;j=Next[j])
				if(To[j]==i) tag=1;
			if(tag==1)
			{
				if(sum%2!=0) flg=0;
			}
			else
			{
				if(sum!=0) flg=0;
			}

		}
	if(flg) printf("YES\n");
	else printf("NO\n");
}

int main()
{
	freopen("sequence.in","r",stdin);
	freopen("sequence.out","w",stdout);
	int test;scanf("%d",&test);
	while(test--)
	{
		Init();
		if(n==1) {Solve_0pts(); continue;}
		if(n<=2) {Solve_60pts();continue;}
		if(flg1==0&&flg2==1) {Solve_80pts();continue;}
		Solve_100pts();
	}
	return 0;
}
```
然而这并不能改变我总分100的事实，自闭了。。。


---

## 作者：Natsuzora (赞：13)

## 纯并查集做法
- 对于操作2，可以直接将u、v合并，形象地打个比喻，若两叠盘子可以互相把自己任何数量碟子放到对方那叠中，如果要使这两叠盘子的数量分别为某值，显然只需要关心他们的数量之和即可。

- 对于操作1，假定有(a, b), (b, c)这两条边，考虑转化为操作2，把a++、b++，再把b--、c--，相当于将a++，c--，或者反之，这样就转化为了操作2的(a, c)，因此，把与一个点相连的其他所有点并起来即可。具体地说，假设a与b、c、d、e相连，则把b、c、d、e依次并起来。

但是这样做要考虑到，如果存在(a, b), (c, d)这两条边，而且b, c被合并了，那么可能会没有将a, d并起来。比如以下我的考场代码就是错误的（还是要感谢CCF给我的错误做法慷慨地赠送了80分）
```cpp
	for(register int i = 1; i <= n; i++) rd(a[i]);
	for(register int i = 1; i <= n; i++) rd(b[i]);
	while(m--){
		rd(t), rd(u), rd(v);
		if(t == 1){
			addedge(u, v);
			addedge(v, u);
		}else merge(u, v);
	}
	for(register int i = 1; i <= n; i++){
		u = find(to[head[i]]);
		for(register int e = nxt[head[i]]; e; e = nxt[e]){
			v = find(to[e]);
			merge(u, v);
			u = v;
		}
	}
	bool flag = true;
	for(register int i = 1; flag && i <= n; i++) if(head[i]){
		u = find(i), v = find(to[head[i]]);
		flag = u == v ? !((a[u] - b[u]) & 1) : (a[u] - b[u]) == (a[v] - b[v]);
		vis[u] = vis[v] = true;
	}
	for(register int i = 1; flag && i <= n; i++)
		if(fa[i] == i && !vis[i]) flag = a[i] == b[i];
	puts(flag ? "YES" : "NO");
```
怎么解决这个问题呢？先将操作2缩点，然后再把操作1的边加到缩过的点上，再按照操作1合并即可。

为什么这样就可以解决问题了？还是考虑 (a, b)，(c, d)，不过此时是经过操作2缩点后的四个点。如果要造成合并的遗漏，就需要将b和c并起来，又不能通过操作2来并，只能通过操作1来并，那么最简单的情况就是再加两条边(b, e)，(c, e)，然而画图可以发现此时实际上会被正确合并。更加复杂的情况可以手推一下，可以发现依然是成立的。

- 最后就是如何检验答案的问题。可以发现，此时图中的所有边都是独立的了（每个点的度数最多为1）。对于(u, u)自环，则u的点权可以任意+-2，即要求a[u]-b[u]为偶数。对于(u, v)非自环，要求a[u]-b[u]=a[v]-b[v]，对于度数为0的点，要求a[u]=b[u]。任意一个位置的条件不成立，答案为NO。

## Code
据说数据可能不完美，如果我的思路有问题，欢迎大家Hack！
```cpp
#include <cstdio>
#include <cctype>
using namespace std;
const int N = 1e5 + 1;

template<typename type>
inline void rd(type &x){
	x = 0;
	char c = getchar();
	while(!isdigit(c)) c = getchar();
	do{
		x = (x << 1) + (x << 3) + c - '0';
		c = getchar();
	}while(isdigit(c));
}

int T, n, m, t, u, v, x[N], y[N], fa[N], head[N], nxt[N << 1], to[N << 1], eid;
long long a[N], b[N];
inline void addedge(int u, int v){
	to[eid] = v;
	nxt[eid] = head[u];
	head[u] = eid++;
}

int find(int x){
	return x == fa[x] ? x : fa[x] = find(fa[x]);
}

inline void merge(int u, int v){
	u = find(u), v = find(v);
	if(u != v){
		fa[v] = u;
		a[u] += a[v];
		b[u] += b[v];
	}
}

int main(){
	rd(T);
	while(T--){
		rd(n), rd(m);
		eid = 1;
		for(int i = 1; i <= n; i++) rd(a[i]), fa[i] = i, head[i] = 0;
		for(int i = 1; i <= n; i++) rd(b[i]);
		for(int i = 1; i <= m; i++){
			rd(t), rd(x[i]), rd(y[i]);
			if(t == 2){
				merge(x[i], y[i]);
				--i, --m;
			}
		}
		for(int i = 1; i <= m; i++){
			u = find(x[i]), v = find(y[i]);
			addedge(u, v), addedge(v, u);
		}
		for(int i = 1; i <= n; i++){
			u = find(to[head[i]]);
			for(int e = nxt[head[i]]; e; e = nxt[e])
				merge(u, find(to[e]));
		}
		bool flag = true;
		for(int i = 1; flag && i <= n; i++) if(head[i]){
			u = find(i), v = find(to[head[i]]);
			flag = u == v ? !((a[u] - b[u]) & 1) : (a[u] - b[u]) == (a[v] - b[v]);
		}else if(fa[i] == i) flag = a[i] == b[i];
		puts(flag ? "YES" : "NO");
	}
	return 0;
}
```


---

## 作者：George_Plover (赞：11)

## 这场神奇的比赛要从一只蝙蝠说起？
### 题意：

给出一个长度为$n$序列$a_i$，需要通过一系列操作，把该序列变为目标序列$b_i$

操作一共有$m$种，每种操作描述为$(t,u,v)$

* $t=1$  ，则可以令$a_u$与$a_v$同时加$1$或减$1$，当$u=v$时相当于这个位置加或减了$2$

* $t=2$  ，则可以令$a_u$与$a_v$一个加$1$另一个减$1$，当$u=v$时相当于这个位置不发生变化

每种操作的使用次数无限制。

$n,m\leq 10^5  \ \  \ \ a_i,b_i\leq 10^9$

------

这个题一读起来就非常$amazing$啊，感觉不怎么好直接下手，乍一看连搜索都不怎么好写，所以要尝试挖掘一下性质。

首先映入眼帘的的当然是操作$t=2$的时候，两个元素可以相互传递任意的数值，互帮互助，完全就是形成了 **命运共同体** 嘛！对于这样的两个位置$u$和$v$，我们就可以放宽限制了，因为只需要满足$a_u+a_v=b_u+b_v$之后，两者之间交换一些数值，就能使得          $ a_u=b_u , a_v=b_v$ 。所以我们能将这两个位置看成一个整体。

接下来，我们再来考虑一下操作$t=1$的时候有什么性质。

说实话我觉得这个性质不那么明显，我在家里来回兜圈的时候突然意识到了这个性质……

如果我们有操作$(1,i,j)$与$(1,j,k)$可以使用，如果我让$a_i,a_j$同增1，$a_j,a_k$同减1，那么就实现了$a_i$增1,$a_k$减1。同理，可以实现$a_i$减1,$a_k$增1。也就是说，利用$j$这个位置，我们实现了$i$和$k$的**命运共同体**！相当于拥有了操作$(2,i,k)$,可以把$i$和$k$位置看成一个整体了。

进一步，如果我们把每个操作$(1,u,v)$视为一条边，那么对任意一个点$u$，我们发现，所有与u直接相连的点必定属于同一个~~命**运共同体**~~ 集合。

于是我们运用图论知识，只对操作$t=1$考虑并且建边。如果一个连通图是二分图，利用上述性质，该连通图的点集一定会被划分为两个集合。如果不是二分图，那么这个连通图的所有点一定会被划分在同一个集合。

我们上面已经分析过了，每个集合可以看成一个需要让$\sum a_i$变成$\sum b_i$的点。

这么看来，我们建的图可能有很多个连通块，而每个连通块都可以被处理成为单点或者双点图。

但是还有一个问题，有一些操作是$t=2$，我们没法通过建图实现这个条件……我想到的解决办法，是对每个$t=2$的操作建虚拟点。把操作$(2,u_i,v_i)$拆为操作$(1,u_i,n+i)$和$(1,v_i,n+i)$。并且令$a_{n+i}=b_{n+i}=0$。这样，就准确的将每个$t=2$操作拆成了两个$t=1$操作，也就可以愉快的通过建边来满足题目要求了。

最后我们对每个连通子图进行考虑。

一共三种情况：

* **孤儿点**  $\ \ \ \ $ 这个连通子图由单独的一个点组成，连自环都没有，只能听天由命，如果$a_i \ne b_i$就可以直接输出”$NO$“了

* **单集合** $\ \ \ \ $ 这个连通块所有点属于同一个集合，内部存在边，于是能且仅能实现自增2的倍数的操作，所以如果$\sum a_i-\sum b_i$不是2的倍数，就可以输出“$NO$”了。

* **双集合** $\ \ \ \ $ 这个连通块是个二分图，能分成两个集合，（注意这两个集合的内部是没有边的，否则就不是二分图了）两个集合之间有连边，所以可以实现同增同减。如果$\sum a_{i_1}-\sum b_{i_1}\ne\sum a_{i_2}-\sum b_{i_2}$,那么也可以输出“$NO$”了

考察了所有情况之后，如果没有问题的话，输出YES即可。

再考虑复杂度，这里划分集合可以采用并查集，带上路径压缩，由于此题数据范围不大，这里可以视为常数级别。而所有的建边都是基于操作数$m$和序列长度$n$的，复杂度可视为$\Omega (n+m)$

代码是比赛的时候写的，在中途变化过思路，比较丑陋，仅作参考


```cpp
#define George_Plover
#include <cstdio>
#include <cstring>
#include <iostream>
#include <algorithm>
#define LL long long
#define MAXN 200001
#define MAXM 400001

using namespace std;
int n,m,T;
int tot,pre[MAXN],to[MAXM],lin[MAXM];
LL a[MAXN],b[MAXN];
int fa[MAXN];
struct OP{
    int t,u,v;
}p[MAXN];
int find(int x)
{
    return fa[x]==x?x:fa[x]=find(fa[x]);
}
void add(int x,int y)
{
    tot++;
    lin[tot]=pre[x];
    pre[x]=tot;
    to[tot]=y;
}
void merge(int x,int y)
{
    int u=find(x),v=find(y);
    if(u==v)return;
    a[u]+=a[v];
    b[u]+=b[v];
    fa[v]=u;
}
void init()
{
    for(int i=1;i<=n+m;i++)
        fa[i]=i;
    memset(pre,0,sizeof(pre));
    tot=0;
}
int main()
{
    freopen("sequence.in","r",stdin);
    freopen("sequence.out","w",stdout);
    scanf("%d",&T);
    while(T--)
    {
        scanf("%d%d",&n,&m);
        init();
        for(int i=1;i<=n;i++)
        {
            scanf("%lld",&a[i]);
        }
        for(int i=1;i<=n;i++)
        {
            scanf("%lld",&b[i]);
        }
        for(int i=1;i<=m;i++)
        {
            scanf("%d%d%d",&p[i].t,&p[i].u,&p[i].v);
            a[i+n]=b[i+n]=0;
            if(p[i].t==1)
            {
                add(p[i].u,p[i].v);
                add(p[i].v,p[i].u);
            }
            else
            {
                add(i+n,p[i].v);
                add(p[i].v,i+n);
                add(i+n,p[i].u);
                add(p[i].u,i+n);
            }
        }
        
        for(int i=1;i<=n+m;i++)
        {
            int tmp=0;
            for(int j=pre[i];j;j=lin[j])
            {
                int v=to[j];
                if(tmp)
                {
                    merge(tmp,v);
                }
                tmp=v;
            }
        }
        bool flag=1;
        for(int i=1;i<=n;i++)
        {
            int j=to[pre[i]];
            if(!pre[i])
            {
                if(a[i]!=b[i])
                {
                    flag=0;
                    break;
                }
                continue;
            }
            int l=find(i),r=find(j);
            if(l==r)
            {
                if((a[l]-b[l])&1)
                {
                    flag=0;
                    break;
                }
                continue;
            }
            if(a[l]-b[l]!=a[r]-b[r])
            {
                flag=0;
                break;
            }
        }
        if(flag)
        {
            printf("YES\n");
        }
        else
        {
            printf("NO\n");
        }
    }
    return 0;
}

```



---

## 作者：ylxmf2005 (赞：8)

### Description
[Link](https://www.luogu.com.cn/problem/P6185)

###  Solution
对于操作二，如果有三个数 $a_1 \sim a_3$ 有 $(a_1,a_2, 2)$ 和 $a(a_2,a_3,2)$，那么可以将 $a_1 + 1, a_2 - 1, a_2 + 1, a_3 - 1 	\Rightarrow (a_1,a_3,2)$。这意味着如果用并查集将有传递性的数加入一个联通块中，那么会有若干个联通块，每个联通块中任意两个数都可以进行操作二。那么如果一个联通块中需要加的值与需要减的值相同，那么一定是合法的。所以把每个联通块缩成一个点，点权为要加的值减去要减的值。

可能有的点权不合法，考虑操作一。如果有 $(a_1,a_2,1),(a_1,a_3,1),(a_2,a_3,1)$，那么可以构成 $a_i \pm 2$，然后 $a_1,a_2,a_3$ 所在的联通块中任意一个数可以通过 $a_1,a_2,a_3$ 来白嫖 $a_i \pm 2$。如果将操作一对应的点连起来，那么这三个点构成了奇环，原图就不是二分图了，这个可以 bfs 或 dfs 染色求。

不过可能有自环，要特判一下。因为自环相当于 $(a_1,a_2,1)$ 和 $(a_1,a_2,2)$ 那么 $a_1 + 1, a_2 - 1, a_1+1,a_2+1$ 同样也可以构成 $a_i \pm 2$。

如果是二分图，那么两边只能同时加一或减一，所以有边相连的差值相同才能 YES。如果不是二分图，那么还可以白嫖加二或减二，所以有边相连的差值是偶数也是 YES。对于所有没边相连的点，点权必须为 $0$ 才能是 YES。

时间复杂度 $O(n \log n)$。我没按秩合并 /kk。

### Code


```cpp
#include <bits/stdc++.h>
using namespace std;
#define int long long
const int N = 2e5 + 5, INF = 0x3f3f3f3f;
inline int read() {
	int x = 0, f = 0; char ch = 0;
	while (!isdigit(ch)) f |= ch == '-', ch = getchar();
	while (isdigit(ch)) x = (x << 3) + (x << 1) + (ch ^ 48), ch = getchar();
	return f ? -x : x;
}
struct edge{
	int to, nxt;
}e[N];
int head[N], tot;
void addedge(int x, int y) {
	e[++tot].to = y, e[tot].nxt = head[x], head[x] = tot; 
}
int a[N], b[N], f[N], t[N], x[N], y[N], val[N];
int find(int x) {
	if (f[x] == x) return x;
	return f[x] = find(f[x]);
}
void merge(int x, int y) {
	x = find(x), y = find(y);
	if (x != y) f[x] = y, val[y] += val[x]; 
} 
int col[N], sum, flg;
void dfs(int x, int c) {
	col[x] = c;
	if (c) sum += val[x];
	else sum -= val[x]; 
	for (int i = head[x]; i; i = e[i].nxt) {
		int y = e[i].to;
		if (col[y] == -1) dfs(y, c ^ 1);
		else if (col[x] == col[y]) flg = 1;
	}
}
signed main() {
	int T = read();
	while (T--) {
		memset(col, -1, sizeof(col)); 
		memset(head, 0, sizeof(head)); tot = 0;
		int n = read(), m = read();
		for (int i = 1; i <= n; i++) a[i] = read();
		for (int i = 1; i <= n; i++) b[i] = read();
		for (int i = 1; i <= n; i++) f[i] = i, val[i] = a[i] - b[i];
		for (int i = 1; i <= m; i++) {
			t[i] = read(), x[i] = read(), y[i] = read();
			if (t[i] == 2) merge(x[i], y[i]);
		}
		for (int i = 1; i <= m; i++) 
			if (t[i] == 1) addedge(find(x[i]), find(y[i])), addedge(find(y[i]), find(x[i]));
		bool ok = 1;
		for (int i = 1; i <= n; i++) 
			if (find(i) == i && col[i] == -1) {
				sum = flg = 0;
				dfs(i, 0); 
				for (int j = head[i]; j; j = e[j].nxt)
					if (e[j].to == i) {
						flg = 1; break;
					}
				if (head[i] == 0) ok &= (sum == 0);
				else if (flg) ok &= (sum % 2 == 0);
				else ok &= (sum == 0);
			}
		if (ok) puts("YES");
		else puts("NO");
	} 
	return 0;
}
```

---

## 作者：AC_Evil (赞：3)

### [来AC-Evil的博客园康康吧](https://www.cnblogs.com/ac-evil/p/12436833.html)

　　不错的题8~~（不知为啥到我手上特判的贼多）~~

　　简述题意：给你$n$个结点，每个结点有一个初始值$a_i$，以及目标值，并且给定两种边$(u_i,v_i)$，第一种边使$a_{u_i}$和$a_{v_i}$同时加一，第二种边使$a_{u_i}$和$a_{v_i}$一个加一，一个减一。问最后能否使所有结点变成目标状态。

　　以下是我在当时测试时的思路。

　　首先到达最终的目标，也就是说使得对应的结点的数值增加$b_i-a_i$，让每个结点表示这个值，问题就转化成了能否使所有的数值变成$0$了。

　　看两种边有什么特别之处。一下子看第一种边没发现什么，第二种边相当于可以将一个结点上的**部分数字**“传输”到与其相邻的结点之处，稍加拓展不难发现第二种边构成的连通图中，任意一个结点可将其数字传到另外的任意一个结点，如下图：

![](https://img2020.cnblogs.com/blog/1508633/202003/1508633-20200307202100581-575490115.png)

　　这样的意义在于：能**自由分配**连通图中所有的数值（都转移到一个结点、或者分配到若干个点），可以无需关心具体的分配情况，于是将他们**缩成一个点**，其权值为$\sum w_i$。

　　这样就只剩下第一种边了。它们只有两种情况：（1）连接两个连通块（即缩点后连接两个点），这个的影响是让连接的两个缩点加或减相等的数字；（2）在某个连通块内，这个的影响是让这个缩点加或减一个**偶数**。我们还是用传输的思想，手算会发现（1）可以将某个点的数值**隔两个点**传过去，如下图：

![](https://img2020.cnblogs.com/blog/1508633/202003/1508633-20200307202157988-788089773.png)

　　对于缩过点的图，每个由第一种边构成的连通块，仔细想想会发现：如果这个连通块**不能**被黑白染色，则一定可以将数值放到**某一个奇环上的一个点**，同样这个也是**可逆的**，故一个数一定可以借助奇环把另一个**相等的**数消除；反之，如果**能**被黑白染色，显然可以将所有**黑点**的数值和**白点**的数值移到一条**相邻**的边，然后再一起消掉。没有（2）情况的干扰下，对于每个连通块，按照上面分类讨论，如果仍然不能完全消除，那显然输出 NO 了。所有的都满足才输出 YES。

　　加上（2），其实就是可以对权值调整，在有（2）的连通块下，不一定要全部消除，只要消到能剩余$2$的倍数就好啦（可以依靠这样的边在连通块内部就消除掉）。于是我们整理一下：

　　1、根据第二种边求出所有的连通块并且缩起来；

　　2、根据第一种边求出所有的连通块，对每个连通块判断能否黑白染色，如果能就染色，求出所有黑点和白点的权值和，顺便看看有没有情况（2）；

　　3、检查该连通块是否满足要求：a.如果不能黑白染色，只需要看这个连通块的权值和是不是偶数；b.如果能，判断黑点权值和和白点权值和的关系，如果有（2），那么只需差为偶数即可；否则必须相等（具体详见上文）；

　　4、如果所有的连通块都能通过测试，输出 YES；否则输出 NO。

　　时间复杂度$\text{O}(Tn)$。可以通过。

```cpp
#include <bits/stdc++.h>

#define ll long long
#define rep(i, a, b) for (int i = a, i##end = b; i <= i##end; ++i)
#define rep0(i, a) for (int i = 0, i##end = a; i < i##end; ++i)

const int maxn = 114514;

int n, m;
std::vector<int> G1[maxn], G2[maxn], G[maxn];
int id[maxn], delta[maxn], tag[maxn], col[maxn], idcnt = 0;
// id为连通块编号、delta表示a[i]-b[i](相反亦可)，tag表示有没有（2）情况，col为染色情况，idcnt表示连通块个数
ll sum[maxn]; // 每个连通块内的权值总和

void dfs(int u) {
	sum[id[u] = idcnt] += delta[u]; // 标记连通块并且合并权值
	rep0(i, G2[u].size()) if (!id[G2[u][i]]) dfs(G2[u][i]);
}

int paint(int u, ll &white, ll &black, int &flag) {
	int ok = 1; // 表示是否染色成功
	col[u] == 1 ? white += sum[u] : black += sum[u]; flag |= tag[u]; // 计算white,black点的权值
	rep0(i, G[u].size()) {
		int v = G[u][i];
		if (col[v]) { if (col[v] == col[u]) ok = 0; continue; } // 失败
		col[v] = 3-col[u];
		ok &= paint(v, white, black, flag);
	}
	return ok;
}

int main() {
	for (int T = read(); T; T--) {
		n = read(), m = read();
		rep(i, 1, n) delta[i] = read();
		rep(i, 1, n) delta[i] -= read();
		rep(i, 1, n) G1[i].clear(), G2[i].clear(); // 清空
		rep(i, 1, m) {
			int t = read(), u = read(), v = read();
			if (t == 1) G1[u].push_back(v), G1[v].push_back(u);
			if (t == 2) G2[u].push_back(v), G2[v].push_back(u);
		}
		memset(id, 0, sizeof id); idcnt = 0;
		rep(i, 1, n) if (!id[i]) G[++idcnt].clear(), sum[idcnt] = tag[idcnt] = col[idcnt] = 0, dfs(i); // 初始化+标记
		rep(u, 1, n)
			rep0(i, G1[u].size()) {
				int v = G1[u][i];
				if (id[u] == id[v]) tag[id[u]] = 1; else G[id[u]].push_back(id[v]);
			}
		int ans = 1;
		rep(i, 1, idcnt) {
			if (col[i]) continue; // 染过色直接跳过
			ll white = 0, black = 0; int flag = 0;
			col[i] = 1;
			if (paint(i, white, black, flag)) { // 染色成功
				if (flag) { if ((white ^ black) & 1) { ans = 0; break; } } // 有（2）情况判断差是否为偶数
				else if (white != black) { ans = 0; break; } // 没有就判断是否相等
			} else if ((white ^ black) & 1) { ans = 0; break; } // 不成功判断差是否为偶数
		}
		printf("%s\n", ans ? "YES" : "NO");
	}
	return 0;
}
```

---

## 作者：gSE2xWE (赞：2)

# 题目

[传送门](https://www.luogu.com.cn/problem/P6185)

# 思路

[更好的阅读体验](https://www.cnblogs.com/loney-s/p/12439030.html)

可以考虑先用二操作进行连边

现在我们就面对了一个个的块

因为二操作不会改变整个块的和

所以我们就可以将一个块缩成一个点

之后我们在考虑1操作

一样的，我们用1操作针对缩了之后的点进行连边

很明显，如果有环（包括自环），这一个块的和可以任意的+2或者-2

考虑无解的情况

一个块的和为奇数，肯定无解

或者是一个块的和为偶数，但是其中并没有环

# 代码

```cpp
#include<iostream>
#include<vector>
#include<cstdio>
using namespace std;
struct node
{
    int t;
    int u;
    int v;
}opt[100005];
int t;
int n,m;
int a[100005];
int b[100005];
long long c[100005];
int fa[2][100005];
bool vis[100005];
bool f[100005];
vector<int> g[100005];
void makeset()
{
    for(int i=1;i<=n;i++)
    {
    	c[i]=0;
        g[i].clear();
        vis[i]=0;
        f[i]=0;
        fa[0][i]=fa[1][i]=i;
    }
}
int findset(int _ind,int u)
{
    if(fa[_ind][u]!=u)
        fa[_ind][u]=findset(_ind,fa[_ind][u]);
    return fa[_ind][u];
}
void unionset(int _ind,int a,int b)
{
    int u=findset(_ind,a);
    int v=findset(_ind,b);
    fa[_ind][v]=u;
}
void dfs(int u)
{
    f[u]=1;
    for(int i=0;i<g[u].size();i++)
    {
        int v=g[u][i];
        if(f[v]==0)
        {
            dfs(v);
            if(vis[v])
                vis[u]=1;
            c[u]-=c[v];
        }
    }
}
void c_in()
{
    scanf("%d %d",&n,&m);
    makeset();
    for(int i=1;i<=n;i++)
        scanf("%d",&a[i]);
    for(int i=1;i<=n;i++)
        scanf("%d",&b[i]);
    for(int i=1;i<=m;i++)
    {
        scanf("%d %d %d",&opt[i].t,&opt[i].u,&opt[i].v);
        if(opt[i].u>opt[i].v)
            swap(opt[i].u,opt[i].v);
    }
    for(int i=1;i<=m;i++)
        if(opt[i].t==2)
            if(findset(0,opt[i].u)!=findset(0,opt[i].v))
                unionset(0,opt[i].u,opt[i].v);
    for(int i=1;i<=m;i++)
    {
        if(opt[i].t==1)
        {
            int fau=findset(0,opt[i].u);
            int fav=findset(0,opt[i].v);
            if(findset(1,fau)!=findset(1,fav))
            {
                unionset(1,fau,fav);
                g[fau].push_back(fav);
                g[fav].push_back(fau);
            }
            else
            {
                vis[fau]=1;
            }
        }
    }
    for(int i=1;i<=n;i++)
        c[findset(0,i)]+=(a[i]-b[i]);
    for(int i=1;i<=n;i++)
    {
        if(f[findset(0,i)]==0)
        {
            int u=findset(0,i);
            dfs(u);
            if(c[u]<0)
				c[u]=-c[u]; 
            if(c[u]!=0)
            {
                if(c[u]%2==1||(c[u]%2==0&&vis[u]==0))
                {
                    printf("NO\n");
                    return;
                }
            }
        }
    }
    printf("YES\n");
}
int main()
{
	//freopen("sequence.in","r",stdin);
	//freopen("sequence.out","w",stdout);
    scanf("%d",&t);
    for(int i=1;i<=t;i++)
        c_in();
    return 0;
}

```


---

