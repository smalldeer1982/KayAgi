# [CERC2014] Pork barrel

## 题目描述

赢得选举比你预期的要简单：只需承诺最终建立一个高质量的全国性道路基础设施，当然不能让预算瘫痪……然而你的快乐并没有持续多久：似乎市民们找到了一个方法，实际上让你对你的承诺负责！

在你的国家有 $n$ 个主要城市。交通部准备了一份详细的地图，列出了 $m$ 条可能的高速公路连接及其成本。质量保证委员会不会让你修建成本低于 $l$ 的高速公路，而国家支出监管委员会不会让你修建成本高于 $h$ 的高速公路。为了声称拥有一个“全国性”的网络，你必须在这两个限制内尽可能多地连接（可能是间接地）城市对。你必须找到最便宜的方法来做到这一点，而且必须快速找到！在所有满足限制并连接最多城市对的网络中，计算出最便宜的一个的成本。

更糟糕的是，这两个委员会都受到你愤怒的竞争对手的强烈影响：每次你公布你精心准备的计划时，他们立即改变他们的裁决 $l$ 和 $h$，你被迫从头开始。

## 说明/提示

题面翻译由 ChatGPT-4o 提供。

## 样例 #1

### 输入

```
1
5 7
1 2 2
2 3 4
3 4 3
4 5 1
5 1 3
2 5 4
1 4 5
5
1 2
4 7
11 12
11 13
18 19
```

### 输出

```
3
9
8
14
13```

# 题解

## 作者：Sampson_YW (赞：6)

一个小清新做法，不需要什么复杂的数据结构。

首先按边权从小到大排序。

然后对于每条边，我们要求出边权以它为最小值时构成的最小生成树的所有边。因为生成树最多只有 $n - 1$ 条边，所以可以花费 $O(nm)$ 的空间存下来。

考虑按边权从大到小做这件事情。

容易发现第 $i$ 条边的最小生成树可以直接从第 $i + 1$ 条边的最小生成树继承下来：要么去掉一条边再加入第 $i$ 条边，要么直接加入第 $i$ 条边。

于是只需要花费 $O(nm)$ 的时间即可求出 $m$ 棵生成树。

然后考虑询问，求边权在 $[L, R]$ 中的最小生成树边权值和。

那么你直接找到最小的那条边权 $\ge L$ 的边，它一定在最小生成树中。

然后你把它的最小生成树按边权从小到大排序，二分找到最大的 $\le R$ 的边，只需要求一个边权的前缀和即可。

但是直接做前缀和空间会爆掉。那么你考虑类似分段打表的方法，隔 $10$ 个数记录一次前缀和即可。

时间复杂度 $O((nm + q)\log n)$，空间复杂度 $O(nm)$，[code](https://www.luogu.com.cn/paste/zyakzq0f)。

---

## 作者：Arghariza (赞：3)

考虑 Kruskal 算法的过程，即边权从小到大依次加入边，每条边连接两个连通块。很重要的性质是每次加入的边边权**单调不降**。

于是权值 $[L,R]$ 内的边组成的最小生成树，相当于从权值为 $L$ 的边开始跑 Kruskal，取所有 $\ge L$ 的边组成的最小生成树，树上所有边权 $\le R$ 的边的边权之和。

将边从小到大排序，如果对于每个边权 $L$，求出边权 $\ge L$ 的一段后缀的边组成的最小生成树，就能够通过一些可持久化手段维护出此时边权 $\le R$ 的边的边权之和。

若已经求出 $L'\ge L$ 的最小生成树（$L'$ 是 $L$ 值域上的后继）$T'$，考虑新增 $(u,v,L)$ 这条边，得到新的最小生成树 $T$：

- 若 $u,v$ 在 $T'$ 中联通，找到 $u\to v$ 简单路径上边权最大的边，删去这条边，然后加入 $(u,v,L)$。
- 若 $u,v$ 在 $T'$ 中不连通，直接加入 $(u,v,L)$。

注意到 $n\le 10^3$，这允许我们在 $O(nm)$ 的时间内求出这 $m$ 棵最小生成树。

由于 $T'\to T$ 的边权变化是 $O(1)$ 的，于是只需要一个支持单点修改，区间求和的可持久化数据结构。使用可持久化权值线段树即可。

复杂度 $O(nm+(m+q)\log W)$。

```cpp
// Problem: P4764 [CERC2014] Pork barrel
// Contest: Luogu
// URL: https://www.luogu.com.cn/problem/P4764
// Memory Limit: 512 MB
// Time Limit: 5000 ms
// 
// Powered by CP Editor (https://cpeditor.org)

#include <bits/stdc++.h>
#define ll long long
using namespace std;

namespace vbzIO {
    char ibuf[(1 << 20) + 1], *iS, *iT;
    #if ONLINE_JUDGE
    #define gh() (iS == iT ? iT = (iS = ibuf) + fread(ibuf, 1, (1 << 20) + 1, stdin), (iS == iT ? EOF : *iS++) : *iS++)
    #else
    #define gh() getchar()
    #endif
    #define mt make_tuple
    #define mp make_pair
    #define fi first
    #define se second
    #define pc putchar
    #define pb emplace_back
    #define ins insert
    #define era erase
    typedef tuple<int, int, int> tu3;
    typedef pair<int, int> pi;
    inline int rd() {
        char ch = gh();
        int x = 0;
        bool t = 0;
        while (ch < '0' || ch > '9') t |= ch == '-', ch = gh();
        while (ch >= '0' && ch <= '9') x = (x << 1) + (x << 3) + (ch ^ 48), ch = gh();
        return t ? ~(x - 1) : x;
    }
    inline void wr(ll x) {
        if (x < 0) x = ~(x - 1), putchar('-');
        if (x > 9) wr(x / 10);
        putchar(x % 10 + '0');
    }
}
using namespace vbzIO;

const int N = 1e3 + 100;
const int M = 1e5 + 100;
const int W = 1e6;

struct edge {
	int u, v, w;
	edge () { }
	edge (int _u, int _v, int _w) : u(_u), v(_v), w(_w) { }
	bool operator < (const edge &rhs) const { return w < rhs.w; }
} e[M], st[N];
int n, m, q, fl, tar, tot, tp, rt[M];
set<pi> t[N];

struct seg { ll s; int lc, rc; } tr[M << 6];

#define ls tr[x].lc
#define rs tr[x].rc
#define mid ((l + r) >> 1)

void upd(int l, int r, int p, int op, int lt, int &x) {
	tr[x = ++tot] = tr[lt], tr[x].s += op * p;
	if (l == r) return;
	if (p <= mid) upd(l, mid, p, op, tr[lt].lc, ls);
	else upd(mid + 1, r, p, op, tr[lt].rc, rs);
}

int qry(int l, int r, int s, int t, int x) {
	if (!x) return 0;
	if (s <= l && r <= t) return tr[x].s;
	int res = 0;
	if (s <= mid) res += qry(l, mid, s, t, ls);
	if (t > mid) res += qry(mid + 1, r, s, t, rs);
	return res;
}

void dfs(int u, int fa) {
	if (u == tar) return fl = 1, void();
	for (pi p : t[u]) {
		int v = p.fi, w = p.se;
		if (v == fa) continue;
		st[++tp] = edge(u, v, w), dfs(v, u);
		if (fl) return;
		tp--;
	}
}

void init() {
	for (int i = 1; i <= m; i++) rt[i] = 0;
	for (int i = 1; i <= n; i++) t[i].clear();
	tot = 0;
}

void solve() {
	n = rd(), m = rd();
	for (int i = 1, u, v, w; i <= m; i++) 
		u = rd(), v = rd(), w = rd(), e[i] = edge(u, v, w);
	sort(e + 1, e + m + 1);
	for (int i = m; i; i--) {
		int u = e[i].u, v = e[i].v, w = e[i].w;
		fl = tp = 0, tar = v, dfs(u, 0), rt[i] = rt[i + 1];
		if (fl) {
			edge res = edge(0, 0, 0);
			for (int i = 1; i <= tp; i++)
				res = max(res, st[i]);
			t[res.u].era(mp(res.v, res.w)), t[res.v].era(mp(res.u, res.w));
			upd(1, W, res.w, -1, rt[i], rt[i]);
		}
		t[u].ins(mp(v, w)), t[v].ins(mp(u, w));
		upd(1, W, w, 1, rt[i], rt[i]);
	}
	q = rd();
	int lst = 0;
	while (q--) {
		int l = rd() - lst, r = rd() - lst;
		int p = lower_bound(e + 1, e + m + 1, edge(0, 0, l)) - e;
		if (p > m) { lst = 0, puts("0"); continue; }
		wr(lst = qry(1, W, l, r, rt[p])), pc('\n');
	}
	init();
}

int main() {
	int T = rd();
	while (T--) solve();
    return 0;
}
```

---

## 作者：loveJY (赞：1)

~~经过两天的努力终于码了出来~~

建议黑题

首先暴力的过程是把$[l,r]$中的边都提出来跑一遍最小生成树,但是这样肯定不行

# 结论

每一条代价为x的边一定存在一个**代价下界y**,满足对于询问的区间$[L,R]$,$y<L<=x,R>x$时一定会被算进去,y可以大于等于x

# 证明

感性理解,假设我们将边权从大到小加入,然后动态维护一颗最小生成树,那么会发现加入到边i的时候i因为i是此时最小的边,所以一定会被算上,同时随着时间再向前推移,总会有一个时间点(可能为0),i会因为不再优而被弹出

这个变化的过程是连续的,所以一定存在一个y,同时如果他一直没用则$y>x$,一直有用对应$y=0$

有了这个结论,假设求出了每条边的y,不难我们的问题就变成了一个二维数点问题

即支持

> 矩阵加
> 单点查询

其中单点查询$(L,R)$,矩阵加左下角$[y+1,y+1]$右上角$[x,\infty]$,我们可以使用二维差分实现

注意到题目强制在线,所以这个问题可以用主席树实现

现在我们如何求y呢?

其实直接模拟证明中的过程就是可以的!

因为一条边被删除的时刻,就是他**被弹出时刻**使其弹出的那条边的边权!

但是动态维护生成树,我们需要:

## LCT!

故综上,我们用LCT来求出每条边的y,再用主席树完成二维数点即可

# 题意补充:

强制在线方式:即lst为上次询问的答案,这次询问的l,r需要减去lst(题目中的letax不知道为啥是加?也可能是我英语太菜了)

# 细节补充

1. 清空的时候都要清空,小心二维差分数组没清空
2. 非常重要的一点是:

一般的题目中重边是没用的,而我们这个题重边是相当有用的!

而如果原本u,v间就有边了,再加入一条边会导致**重边成环!**

而显然的是用LCT寻找是找不到这种情况的!!

所以我们要特判掉,特判有些坑/xyx

3. 权值要离散化,然后把询问离散回来,而且左右端点离散结果还不一样.....
4. 建立主席树,我使用了每个版本只新建一个节点的写法,因为对于一个时刻可能有多个修改....具体可以看代码

3,4都是因为本题恶心的125mb空间限制(

下面是ACcode:

```cpp
#include<bits/stdc++.h>
#define ll long long
#define pb push_back
#define se second
#define fi first
#define mkp(x,y) (make_pair(x,y))
#define pii pair<int,int>
const int MAXN = 1e3 + 7;
const int MAXW = 2e5 + 7;
const int MAXM = 2e5 + 7;
const int MAXT = 4e6 + 7;
using namespace std;
int n, m, q;
struct rec {
	int x, y, z, w, k;
	bool operator<(const rec &X)const {
		return w < X.w;
	}
} e[MAXM];
namespace LoveJY_Catalan_Tmd {
#define L (ch[x][0])
#define R (ch[x][1])
	int ch[MAXM][2], f[MAXM], tag[MAXM], st[MAXM];
	int a[MAXM], id[MAXM];//子树中最大标号是啥
	inline bool nroot(int x) {
		return ch[f[x]][0] == x || ch[f[x]][1] == x;
	}
	inline void pushup(int x) {
		id[x] = a[id[L]] < a[id[R]] ? id[L] : id[R];
		id[x] = a[x] < a[id[x]] ? x : id[x];
	}
	inline void pushR(int x) {
		tag[x] ^= 1;
		L ^= R ^= L ^= R;
	}
	inline void pushdown(int x) {
		if(tag[x]) {
			if(L)pushR(L);
			if(R)pushR(R);
			tag[x] = 0;
		}
	}
	inline void rotate(int x) {
		int y = f[x], z = f[y], k = ch[y][1] == x, w = ch[x][!k];
		if(nroot(y))ch[z][ch[z][1] == y] = x;
		ch[x][!k] = y;
		ch[y][k] = w;
		f[y] = x;
		f[x] = z;
		if(w)f[w] = y;
		pushup(y);
	}
	inline void splay(int x) {
		int y = x, z = 0;
		st[++z] = y;
		while(nroot(y)) {
			st[++z] = f[y];
			y = f[y];
		}
		while(z) {
			pushdown(st[z]);
			z--;
		}
		while(nroot(x)) {
			y = f[x];
			z = f[y];
			if(nroot(y)) {
				rotate((ch[x][0] == y) ^ (ch[z][0] == y) ? y : x);
			}
			rotate(x);
		}
		pushup(x);
	}
	inline void access(int x) {
		for(int y = 0; x; x = f[y = x]) {
			splay(x); R = y; pushup(x);
		}
	}
	inline void makeroot(int x) {
		access(x);
		splay(x);
		pushR(x);
	}
	inline int findroot(int x) {
		access(x);
		splay(x);
		while(L)pushdown(x), x = L;
		splay(x);
		return x;
	}
	inline void split(int x, int y) {
		makeroot(x);
		access(y);
		splay(y);
	}
	inline void link(int x, int y) {//把y接到x上去
		makeroot(x);
		makeroot(y);
		f[y] = x;
	}
	inline void cut(int x, int y) {
		split(x, y);
		ch[y][0] = 0;
		f[x] = 0;
		pushup(y);
	}
#undef L
#undef R
}
using namespace LoveJY_Catalan_Tmd;
int mx;
vector<int> zhq;
inline int getid(int x) {
	return lower_bound(zhq.begin(), zhq.end(), x) - zhq.begin() + 1;
}
inline void init3() {
	for(int i = 1; i <= m; ++i) {
		zhq.pb(e[i].w);
	}
	sort(zhq.begin(), zhq.end());
	zhq.erase(unique(zhq.begin(), zhq.end()), zhq.end());
	for(int i = 1; i <= m; ++i) {
		e[i].k = e[i].w;
		e[i].w = getid(e[i].w);
	}
	return ;
}
int mp[MAXN][MAXN];
inline void init2() {
	sort(e + 1, e + m + 1);
	a[0] = 1e9 + 1;
	for(int i = 1; i <= n; ++i)a[i] = 1e9;
	for(int i = 1; i <= m; ++i) {
		int u = e[i].x;
		int v = e[i].y;
		mx = max(mx, e[i].w);
		if(u > v)swap(u, v);
		if(mp[u][v]) {
			e[i].z = a[mp[u][v]];
			a[mp[u][v]] = e[i].w;
			access(mp[u][v]);
			splay(mp[u][v]);
			continue;
		}
		makeroot(u);
		if(findroot(v) != u) {
			a[i + n] = e[i].w;
			link(i + n, u);
			link(i + n, v);
			e[i].z = 0;
			mp[u][v] = i + n;
		} else {
			split(u, v);
			int qwq = id[v];
			e[i].z = a[qwq];
			a[qwq] = 1e9;
			cut(qwq, e[qwq - n].x);
			cut(qwq, e[qwq - n].y);
			mp[e[qwq - n].x][e[qwq - n].y] = 0;
			a[i + n] = e[i].w;
			link(i + n, u);
			link(i + n, v);
			mp[u][v] = i + n;
		}
	}
	return ;
}
int T2;
int ls[MAXT], rs[MAXT], root[MAXW];
ll tr[MAXT];
#define fi first
#define se second
#define mid ((l+r)>>1)
vector<pii> v[MAXW];
inline void add(int &x, int y, int l, int r, int P, int V) {
	if(x == y || !x) {
		x = ++T2;
		tr[x] = tr[y];
		ls[x] = ls[y];
		rs[x] = rs[y];
	}
	tr[x] += V;
	if(l == r) {
		return ;
	}
	if(P <= mid)add(ls[x], ls[y], l, mid, P, V);
	else add(rs[x], rs[y], mid + 1, r, P, V);
}

inline ll qry(int k, int l, int r, int L, int R) {
	if(!k)return 0;
	if(L <= l && r <= R) {
		return tr[k];
	}
	if(R <= mid)return qry(ls[k], l, mid, L, R);
	else if(L > mid)return qry(rs[k], mid + 1, r, L, R);
	else return qry(ls[k], l, mid, L, R) + qry(rs[k], mid + 1, r, L, R);
}

inline void init() {
	for(int i = 1; i <= m; ++i) {
		if(e[i].z + 1 > e[i].w)continue;//剪 枝
		if(e[i].z + 1 <= mx)
			v[e[i].z + 1].pb(mkp(e[i].w, e[i].k));
		if(e[i].w + 1 <= mx)
			v[e[i].w + 1].pb(mkp(e[i].w, -e[i].k));
	}
	for(int i = 1; i <= mx; ++i) {
		if(v[i].size() == 0) {
			root[i] = root[i - 1];
			continue;
		}
		for(auto e : v[i])add(root[i], root[i - 1], 1, mx, e.fi, e.se);
		v[i].clear();
	}
	return;
}
inline void clear() {
	T2 = 0;
	mx = 0;
	memset(root, 0, sizeof(root));
	memset(tag, 0, sizeof(tag));
	memset(ch, 0, sizeof(ch));
	memset(f, 0, sizeof(f));
	memset(id, 0, sizeof(id));
	memset(ls, 0, sizeof(ls));
	memset(rs, 0, sizeof(rs));
	memset(tr, 0, sizeof(tr));
	memset(mp, 0, sizeof(mp));
	memset(e, 0, sizeof(e));
	zhq.clear();
}
int T;
int main() {
	scanf("%d", &T);
	while(T-- > 0) {
		scanf("%d%d", &n, &m);
		for(int i = 1; i <= m; ++i) {
			scanf("%d%d%d", &e[i].x, &e[i].y, &e[i].w);
			if(e[i].x > e[i].y)swap(e[i].x, e[i].y);
		}
		init3();
		init2();//预处理主席树呢
		init();//把所有的拿出来跑lct
		scanf("%d", &q);
		ll ans = 0, x, y;
		for(int i = 1; i <= q; ++i) {
			scanf("%lld%lld", &x, &y);
			x -= ans;
			y -= ans;
			x = getid(x);
			y = upper_bound(zhq.begin(), zhq.end(), y) - zhq.begin();
			if(y < x || x > mx)ans = 0;
			else ans = qry(root[x], 1, mx, 1, y);
			printf("%lld\n", ans);
		}
		clear();
	}
	return 0;
}

```


---

## 作者：Luciylove (赞：0)

最小生成树自然可以联想到 LCT。

考虑左端点扫描线维护最小生成树求出一条边什么时候有效。

注意到一条边 $e$ 有效的时候为 $R_i \geq e, L_i \in [pre_i + 1, e]$ 这提示我们在线二维数点，我们将贡献转为差分的形式即可。

使用主席树即可做到在线，复杂度线性对数。

---

## 作者：DaiRuiChen007 (赞：0)

# P4764 题解

[Problem Link](https://www.luogu.com.cn/problem/P4764)

**题目大意**

> $n$ 个点 $m$ 条边的带权无向图，强制在线 $q$ 次询问边权在 $[L,R]$ 中的边构成的最小生成森林的权值和。
>
> 数据范围：$n\le 1000,m\le 10^5,q\le 10^6$。

**思路分析**

观察到 $L$ 一定的询问，答案就是最小生成树中边权 $\le R$ 的所有边权和。

因此考虑倒序扫描线，每次加入一条边，删除环上最小边，相当于线段树上对于 $ans_R$ 区间修改，用主席树维护即可强制在线。

由于 $n$ 很小可以直接暴力找环上最小边。

数据范围 $\mathcal O(nm+(m+q)\log m)$，用 LCT 维护切边即可做到 $\mathcal O(m\log n+(m+q)\log m)$。

**代码呈现**

```cpp
#include<bits/stdc++.h>
using namespace std;
const int MAXN=1e5+5;
struct Edge { int u,v,w; } e[MAXN];
int n,m,q;
struct SegmentTree {
	struct Node {
		int ls,rs,sum;
	}	tr[MAXN*40];
	int tot;
	inline void add(int u,int k,int l,int r,int q,int &p) {
		tr[p=++tot]=tr[q],tr[p].sum+=k;
		if(l==r) return ;
		int mid=(l+r)>>1;
		if(u<=mid) add(u,k,l,mid,tr[q].ls,tr[p].ls);
		else add(u,k,mid+1,r,tr[q].rs,tr[p].rs);
	}
	inline int qry(int ul,int ur,int l,int r,int p) {
		if(ul<=l&&r<=ur) return tr[p].sum;
		int mid=(l+r)>>1,sum=0;
		if(ul<=mid) sum+=qry(ul,ur,l,mid,tr[p].ls);
		if(mid<ur) sum+=qry(ul,ur,mid+1,r,tr[p].rs);
		return sum;
	}
}	TR;
int rt[MAXN],dsu[MAXN];
inline int find(int x) { while(x^dsu[x]) x=dsu[x]=dsu[dsu[x]]; return x; }
vector <int> G[MAXN];
int fa[MAXN];
inline void solve() {
	scanf("%d%d",&n,&m),TR.tot=0;
	for(int i=1;i<=m;++i) scanf("%d%d%d",&e[i].u,&e[i].v,&e[i].w);
	sort(e+1,e+m+1,[&](auto i,auto j){ return i.w<j.w; });
	iota(dsu+1,dsu+n+1,1);
	unordered_set <int> Q;
	rt[m+1]=0;
	for(int i=m;i>=1;--i) {
		rt[i]=rt[i+1];
		if(find(e[i].u)!=find(e[i].v)) {
			TR.add(i,e[i].w,1,m,rt[i],rt[i]),Q.insert(i),dsu[find(e[i].u)]=find(e[i].v);
		} else {
			for(int u=1;u<=n;++u) G[u].clear();
			for(int p:Q) G[e[p].u].push_back(p),G[e[p].v].push_back(p);
			function<void(int,int)> dfs=[&](int u,int z) {
				fa[u]=z;
				for(int v:G[u]) if(v!=z) dfs(e[v].u^e[v].v^u,v);
			};
			dfs(e[i].u,0);
			int x=0;
			for(int p=e[i].v;p!=e[i].u;p=e[fa[p]].u^e[fa[p]].v^p) x=max(x,fa[p]);
			Q.erase(x),Q.insert(i);
			TR.add(i,e[i].w,1,m,rt[i],rt[i]),TR.add(x,-e[x].w,1,m,rt[i],rt[i]);
		}
	}
	scanf("%d",&q);
	function<int(int)> lo=[&](int x) {
		int l=1,r=m,res=-1;
		while(l<=r) {
			int mid=(l+r)>>1;
			if(x<=e[mid].w) res=mid,r=mid-1;
			else l=mid+1;
		}
		return res;
	};
	function<int(int)> hi=[&](int x) {
		int l=1,r=m,res=-1;
		while(l<=r) {
			int mid=(l+r)>>1;
			if(e[mid].w<=x) res=mid,l=mid+1;
			else r=mid-1;
		}
		return res;
	};
	for(int L,R,lst=0;q--;) {
		scanf("%d%d",&L,&R),L-=lst,R-=lst;
		int l=lo(L),r=hi(R);
		if(l==-1||r==-1) puts("0"),lst=0;
		else printf("%d\n",lst=TR.qry(l,r,1,m,rt[l]));
	}
}
signed main() {
	int T;
	scanf("%d",&T);
	while(T--) solve();
	return 0;
}
```

---

## 作者：LinkyChristian (赞：0)

从未如此小丑，受不了了，一拳把地球打爆！

首先想一个弱化版的问题，如果每次询问的是权值为 $[1,R]$ 的边构成的最小生成树，考虑做 kruskal，那么权值为 $[1,R]$ 的边构成的最小生成树必定为过程中的一个子局面，且必定存在于最终的生成树中，于是我们只需要在最终的生成树上查询边权在 $[1,R]$ 之内的边的权值和即可。

这启发我们在对边从小到大排序后，对每个 $i$ 维护第 $i \sim m$ 条边构成的最小生成树 $T_i$ ，对每个询问 $[L,R]$ 找到最小的 $w_i \ge L$ 的 $T_i$，在其上询问边权 $\le R$ 的边的权值和。

考虑从 $T_{i+1}$ 推到 $T_i$ 的过程，加入边 $(u_i,v_i)$ 前，如果 $u_i,v_i$ 已经连通，那么找到路径上最大的一条边删掉，之后加入 $(u_i,v_i)$。观察到每次最多会有两个值发生变化，使用可持久化权值线段树维护即可，复杂度为 $\operatorname{O}(nm+mlogV)$。

```cpp
#include<bits/stdc++.h>
#define M 100010
#define N 1010
#define pb insert
#define pii pair<int,int>
#define fi first
#define se second
#define mid (l+r)/2
#define V 1000000
using namespace std;
int T,n,m;
struct node{
    int u,v,w;
    bool operator <(node o) {return w>o.w;}
}e[M];
int read() {
    int x=0,f=1;char ch=getchar();
    while(!isdigit(ch)) f=ch=='-'?-1:1,ch=getchar();
    while(isdigit(ch)) x=x*10+ch-'0',ch=getchar();
    return x*f;
}
set<pii> to[N];
int fa[N],vf[N];
bool dfs1(int now,int t) {
//    printf("%d\n",now);
    if(now==t) return 1;
    int res=0;
    for(pii v:to[now]) if(v.fi!=fa[now]) fa[v.fi]=now,vf[v.fi]=v.se,res|=dfs1(v.fi,t);
    return res;
}
int rt[M];
struct segmentTree{
    int ls[(V+10)<<5],rs[(V+10)<<5],sum[(V+10)<<5],tot=0;
    int add(int las,int l,int r,int pos,int x) {
        int k=++tot;ls[k]=ls[las],rs[k]=rs[las],sum[k]=sum[las]+x;
        if(l==r) return k;
        if(pos<=mid) ls[k]=add(ls[las],l,mid,pos,x);
        else rs[k]=add(rs[las],mid+1,r,pos,x);
        return k;
    }
    int query(int k,int l,int r,int L,int R) {
        if(L<=l&&r<=R) return sum[k];
        int res=0;
        if(L<=mid) res+=query(ls[k],l,mid,L,R);
        if(R>mid) res+=query(rs[k],mid+1,r,L,R);
        return res;
    }
    void clear() {
        for(int i=1; i<=tot; i++) ls[i]=rs[i]=sum[i]=0;
        tot=0;
    }
}tr;
int main() {
    T=read();
    while(T--) {
        n=read(),m=read();
        for(int i=1; i<=m; i++) e[i]=node{read(),read(),read()};
        sort(e+1,e+m+1);
        int q=read();
        rt[1]=tr.add(rt[0],1,V,e[1].w,e[1].w);
        to[e[1].u].pb({e[1].v,1}),to[e[1].v].pb({e[1].u,1});
        for(int i=2; i<=m; i++) {
        	for(int j=1; j<=n; j++) fa[j]=vf[j]=0;
            if(dfs1(e[i].u,e[i].v)) {
                int tmp=e[i].v,mx=0,id=0;
                while(tmp!=e[i].u) {
                    if(e[vf[tmp]].w>mx) mx=e[vf[tmp]].w,id=vf[tmp];
                    tmp=fa[tmp];
                }
                rt[i]=tr.add(rt[i-1],1,V,e[id].w,-e[id].w);
                to[e[id].u].erase(to[e[id].u].find(pii{e[id].v,id}));
				to[e[id].v].erase(to[e[id].v].find(pii{e[id].u,id})); 
            }
            rt[i]=tr.add(rt[i]?rt[i]:rt[i-1],1,V,e[i].w,e[i].w);
            to[e[i].u].pb({e[i].v,i}),to[e[i].v].pb({e[i].u,i});
        }
        int las=0;
        for(int i=1; i<=q; i++) {
            int L=read()-las,R=read()-las,l=1,r=m,pos=0;
            while(l<=r) {
                if(e[mid].w>=L) pos=max(pos,mid),l=mid+1;
                else r=mid-1;
            }
            if(pos<1) {puts("0");las=0;continue;}
            las=tr.query(rt[pos],1,V,L,R);
            printf("%d\n",las);
        }
        for(int i=1; i<=n; i++) to[i].clear();
        for(int i=1; i<=m; i++) rt[i]=0;
        tr.clear();
    }
}
```




---

