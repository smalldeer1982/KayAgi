# Painting Edges

## 题目描述

Note the unusual memory limit for this problem.

You are given an undirected graph consisting of $ n $ vertices and $ m $ edges. The vertices are numbered with integers from $ 1 $ to $ n $ , the edges are numbered with integers from $ 1 $ to $ m $ . Each edge can be unpainted or be painted in one of the $ k $ colors, which are numbered with integers from $ 1 $ to $ k $ . Initially, none of the edges is painted in any of the colors.

You get queries of the form "Repaint edge $ e_{i} $ to color $ c_{i} $ ". At any time the graph formed by the edges of the same color must be bipartite. If after the repaint this condition is violated, then the query is considered to be invalid and edge $ e_{i} $ keeps its color. Otherwise, edge $ e_{i} $ is repainted in color $ c_{i} $ , and the query is considered to valid.

Recall that the graph is called bipartite if the set of its vertices can be divided into two parts so that no edge connected vertices of the same parts.

For example, suppose you are given a triangle graph, that is a graph with three vertices and edges $ (1,2) $ , $ (2,3) $ and $ (3,1) $ . Suppose that the first two edges are painted color $ 1 $ , and the third one is painted color $ 2 $ . Then the query of "repaint the third edge in color $ 1 $ " will be incorrect because after its execution the graph formed by the edges of color $ 1 $ will not be bipartite. On the other hand, it is possible to repaint the second edge in color $ 2 $ .

You receive $ q $ queries. For each query, you should either apply it, and report that the query is valid, or report that the query is invalid.

## 样例 #1

### 输入

```
3 3 2 5
1 2
2 3
1 3
1 1
2 1
3 2
3 1
2 2
```

### 输出

```
YES
YES
YES
NO
YES
```

# 题解

## 作者：xht (赞：22)

> [CF576E Painting Edges](https://codeforc.es/contest/576/problem/E)

## 题意

- 给定一张 $n$ 个点 $m$ 条边的无向图。
- 一共有 $k$ 种颜色，一开始，每条边都没有颜色。
- 定义**合法状态**为仅保留**染成 $k$ 种颜色中的任何一种颜色**的边，图都是一张二分图。
- 有 $q$ 次操作，第 $i$ 次操作将第 $e_i$ 条边的颜色染成 $c_i$。
- 但并不是每次操作都会被**执行**，只有当执行后仍然合法，才会执行本次操作。
- 你需要判断每次操作是否会被执行。
- $n,m,q \le 5 \times 10^5$，$k \le 50$。

## 题解

类似 [P5787 二分图 /【模板】线段树分治](https://www.luogu.com.cn/problem/P5787)（[学习笔记 & 题解](https://www.xht37.com/线段树分治-学习笔记/)）。

只是一个可撤销并查集变成了 $k$ 个，以及要多加一个判断。

这个判断不太好弄，考虑把判断和区间操作分开进行。

区间操作其实就是，对于一条边的两次染色 $x,y$，染色区间为 $[x+1,y-1]$，颜色有两种可能：

1. 染上去了，则颜色是 $x$ 染色时的颜色。
2. 没染上去，则颜色是上一次染色的颜色。

那么判断变成一个单点判断了，分治到那个叶子的时候进行判断就好了。

总时间复杂度 $\mathcal O(m \log n \log q)$。

## 代码

```cpp
const int N = 5e5 + 7, K = 51;
int n, m, k, q, f[K][N<<1], d[K][N<<1], u[N], v[N], a[N], c[N], p[N];
struct T {
	int l, r;
	vi e;
} t[N<<2];
struct S {
	int c, x, z;
	inline S() {}
	inline S(int c, int x, int z) : c(c), x(x), z(z) {}
};
stack< S > s;

void build(int p, int l, int r) {
	t[p].l = l, t[p].r = r;
	if (l == r) return;
	build(ls, l, md), build(rs, md + 1, r);
}

void ins(int p, int l, int r, int x) {
	if (t[p].l >= l && t[p].r <= r) return t[p].e.pb(x), void();
	if (l <= md) ins(ls, l, r, x);
	if (r > md) ins(rs, l, r, x);
}

inline int get(int o, int x) {
	while (x ^ f[o][x]) x = f[o][x];
	return x;
}

inline void merge(int o, int x, int y) {
	if (x == y) return;
	if (d[o][x] > d[o][y]) swap(x, y);
	int z = d[o][x] == d[o][y];
	s.push(S(o, x, z)), f[o][x] = y, d[o][y] += z;
}

void dfs(int p, int l, int r) {
	ui o = s.size();
	for (ui i = 0; i < t[p].e.size(); i++) {
		int x = t[p].e[i], a = ::a[x], c = ::c[x], u = ::u[a], v = ::v[a];
		if (c) merge(c, get(c, u + n), get(c, v)), merge(c, get(c, v + n), get(c, u));
	}
	if (l == r) {
		int a = ::a[l], c = ::c[l], u = ::u[a], v = ::v[a];
		if (get(c, u) == get(c, v)) prints("NO"), ::c[l] = ::p[a];
		else prints("YES"), ::p[a] = ::c[l];
	} else dfs(ls, l, md), dfs(rs, md + 1, r);
	while (s.size() > o) {
		int c = s.top().c, x = s.top().x, z = s.top().z;
		s.pop(), d[c][f[c][x]] -= z, f[c][x] = x;
	}
}

int main() {
	rd(n), rd(m), rd(k), rd(q);
	build(1, 1, q);
	for (int i = 1; i <= n; i++)
		for (int j = 1; j <= k; j++)
			f[j][i] = i, f[j][i+n] = i + n;
	for (int i = 1; i <= m; i++) rd(u[i]), rd(v[i]), p[i] = q + 1;
	for (int i = 1; i <= q; i++) rd(a[i]), rd(c[i]);
	for (int i = q; i; i--) {
		int a = ::a[i];
		if (i < p[a] - 1) ins(1, i + 1, p[a] - 1, i);
		p[a] = i;
	}
	for (int i = 1; i <= m; i++) p[i] = 0;
	dfs(1, 1, q);
	return 0;
}
```

---

## 作者：Kinandra (赞：15)

标签: 线段树分治, 并查集.

### Part 1

显然不同颜色的边互不影响, 我们只要对每种颜色分别判断合法即可, 判断一个图是否为二分图只需要判断这个图中有没有奇环. 这个可以用并查集来维护.

具体地, 将图中所有边依次加入并查集, 维护每个节点到父亲节点的距离的奇偶性, 加边时若两个点在同一个集合内就判断一下是否为奇环即可.

### Part 2

然而普通并查集不能维护本题所涉及的删边操作(即将某种颜色的边变成另一种颜色), 我们就需要使用可撤销的并查集, 并且借助线段树分治来解决.

对操作按先后顺序进行线段树分治后, 发现我们不能预先知道每个操作是否被执行, 且不能确定某个操作的影响范围(即下一个作用在同一条边上的操作可能不会被执行).

对于第一个问题, 我们可以在分治到在叶子节点的时候判断操作的合法性.

对于第二个问题, 我们可以边进行判断, 边用操作覆盖线段树上的区间. 具体的, 若有操作 $i$ 和操作 $j$ 作用于同一条边(其中 $i$ 被**执行**了且 $(i,j)$ 中没有其他作用于该边的操作, 显然 $i$ 至少作用到了 $[i,j-1]$ , 所以我们在分治到 $i$ 的叶子节点时将操作 $i$ 覆盖 $[i,j-1]$ , $j$ 之后的部分受哪个操作影响可以在分治到 $j$ 的叶子节点的时候判断出来, 并将这个操作覆盖到之后的一段.

所以线段树分治写出来是这样的.

```cpp
void work(int l, int r, int k, int d) {
    ins(k, d);
    if (l == r) {
        int id = p[l].e;
        ++pos[id], dsu[p[l].c].check(id) ? (puts("YES"), e[id].c = p[l].c)
                                         : (puts("NO"));
        return modi(root, l + 1, (*pos[id]) - 1, e[id]), del(k, d);
    }
    int mid = l + r >> 1;
    work(ls, d + 1), work(rs, d + 1), del(k, d);
}
```

`ins` 为将改区间的操作作用到并查集上, `del` 为撤销 `ins` 的操作.

时间复杂度(视 $n,m,q$ 同级) $\mathcal O(n\log^2n)$, 两个 $\log$ 分别是线段树分治的和可撤销的并查集的.

```cpp
#include <bits/stdc++.h>
#define root 1, q, 1
#define ls l, mid, k << 1
#define rs mid + 1, r, k << 1 | 1
using namespace std;
int read();
int n, m, k, q;
struct E {
    int u, v, c;
} e[500005];

struct P {
    int e, c;
} p[500005];

vector<int> chan[500005];
vector<int>::iterator pos[500005];

struct Dsu {
    int fa[500005];
    bool fw[500005];
    short h[500005];
    bool check(int id) {
        int u = e[id].u, v = e[id].v, w = 0;
        while (fa[u]) w ^= fw[u], u = fa[u];
        while (fa[v]) w ^= fw[v], v = fa[v];
        return u != v || w;
    }
    E merge(int u, int v) {
        int w = 1;
        while (fa[u]) w ^= fw[u], u = fa[u];
        while (fa[v]) w ^= fw[v], v = fa[v];
        if (u == v) return (E){0};
        h[u] > h[v] ? swap(u, v) : void(), fa[u] = v, fw[u] = w;
        return (E){u, v, (h[u] == h[v]) ? h[v]++ : h[v]};
    }
} dsu[51];

struct Seg {
    vector<E> t[2000006], rec[202];
    void ins(int k, int d) {
        rec[d].clear();
        for (int i = 0; i < t[k].size(); ++i)
            rec[d].push_back(dsu[t[k][i].c].merge(t[k][i].u, t[k][i].v));
    }
    void del(int k, int d) {
        for (int i = t[k].size() - 1; i >= 0; --i) {
            if (!rec[d][i].u) continue;
            int u = rec[d][i].u, v = rec[d][i].v, c = t[k][i].c;
            dsu[c].fa[u] = dsu[c].fw[u] = 0, dsu[c].h[v] = rec[d][i].c;
        }
    }
    void modi(int l, int r, int k, int st, int en, E v) {
        if (st > r || en < l) return;
        if (st <= l && en >= r) return t[k].push_back(v);
        int mid = l + r >> 1;
        modi(ls, st, en, v), modi(rs, st, en, v);
    }
    void work(int l, int r, int k, int d) {
        ins(k, d);
        if (l == r) {
            int id = p[l].e;
            ++pos[id], dsu[p[l].c].check(id) ? (puts("YES"), e[id].c = p[l].c)
                                             : (puts("NO"));
            return modi(root, l + 1, (*pos[id]) - 1, e[id]), del(k, d);
        }
        int mid = l + r >> 1;
        work(ls, d + 1), work(rs, d + 1), del(k, d);
    }
} seg;

int main() {
    n = read(), m = read(), k = read(), q = read();
    for (int i = 1; i <= m; ++i) e[i].u = read(), e[i].v = read();
    for (int i = 1; i <= q; ++i)
        p[i].e = read(), p[i].c = read(), chan[p[i].e].push_back(i);
    for (int i = 1; i <= m; ++i)
        chan[i].push_back(q + 1), pos[i] = chan[i].begin();
    seg.work(root, 0);
    return 0;
}

int read() {
    int x = 0, f = 1;
    char c = getchar();
    while (c < '0' || c > '9') f = (c == '-') ? -1 : f, c = getchar();
    while (c >= '0' && c <= '9') x = x * 10 + c - '0', c = getchar();
    return x * f;
}
```

---

## 作者：WeLikeStudying (赞：6)

**题意**
- [题目链接](https://www.luogu.com.cn/problem/CF576E)。
- 给定一个 $n$ 个点 $m$ 条边无向图，一开始边无色透明。
- $q$ 次操作，每次将一条边染成某个颜色，如果发现只保留这个颜色的边后图不是二分图就不进行该操作。
- 对每个操作输出该操作能否正常进行。
- 颜色数不大于 $50$，$n,m,q\le 5\times 10^5$。

**分析**
- 与[这道](https://www.luogu.com.cn/blog/luo1gu1zui1bang1/solution-p5787)其实很相似，都是线段树分治套可撤销并查集的样子，但操作略有不同，所以重点讲实现细节。
- 由于 $k$ 很小考虑开 $k$ 个可撤销并查集维护。
- 还是类似地，把操作放到一个时间的线段树里，但是我们不知道每个操作要干啥呀。
- 仔细思考一下发现~~十分困难所以作者决定放弃改用在线做法。~~
- 作者首先尝试在线段树分治的基础上能否判断操作的内容是啥的思路。
- 简单地讲，对于一个操作 $u$（被编码在 $u$ 时刻），它在 $v$ 时刻已经不存在了（被覆盖），我们知道在 $[u,v-1]$ 时段的标记可能有两种，一种是新的颜色另一种是原来的，如果我们仍然使用可撤销并查集加上判断操作是否成立的话，那么在 $u$ 时刻，它需要最后被放进去（来判断是否可行），在 $[u+1,v-1]$ 时段里，它需要提前放进去，以免后来的加入然后让新加的不可行。
- 于是就相对明显了，操作变成了 $[u+1,v-1]$ 时间段的操作，它取决于 $u$ 时刻的判断，而这个可以在递归到叶节点的时候顺便完成。
- 总的时间复杂度是 $O(nk+q\lg q\lg n)$，空间复杂度是 $O(nk)$ 可以通过本题。
- ~~作者觉得挺神奇的，不知道为啥有人觉得很简单。~~

**代码**
- 想通了，就可以 $1A$，感觉挺神奇的。
- [代码实现](https://www.luogu.com.cn/paste/62w8pkau)。

---

## 作者：Sol1 (赞：5)

可以看出不弱于加边删边二分图判定，考虑线段树分治。

因为边的颜色只有 $50$ 种，所以考虑对每一种颜色，开一个可撤销扩展域并查集来维护二分图判定。

但是这题有一个地方比较烦：不知道一个修改之后图是否仍然合法，也就不知道后面边的颜色到底应该是什么。

也就是说我们只能在分治到一次修改的时候知道这条边的颜色。

那么我们既然只能这时知道那就这时再改呗，每次分治到 $i$，判断是否合法，然后就可以知道 $i$ 的颜色；此时再向 $(i,\text{nxt}_i)$ 加入这条边以及对应的颜色就可以了。

所以这题就做完了，时间复杂度 $O(nk+n\log^2n)$，空间复杂度 $O(nk)$。

```cpp
#include <iostream>
#include <cmath>
#include <cstring>
#include <cstdio>
#include <vector>
#include <stack>
using namespace std;

#define getchar() (p1==p2&&(p2=(p1=buf)+fread(buf,1,1<<21,stdin),p1==p2)?EOF:*p1++)
char buf[1 << 21], *p1 = buf, *p2 = buf;

inline int qread() {
	register char c = getchar();
	register int x = 0, f = 1;
	while (c < '0' || c > '9') {
		if (c == '-') f = -1;
		c = getchar();
	}
	while (c >= '0' && c <= '9') {
		x = (x << 3) + (x << 1) + c - 48;
		c = getchar();
	}
	return x * f;
}

inline int Abs(const int& x) {return (x > 0 ? x : -x);}
inline int Max(const int& x, const int& y) {return (x > y ? x : y);}
inline int Min(const int& x, const int& y) {return (x < y ? x : y);}

int n, m, k, q, nxt[500005], lst[500005];
struct UndoDSU {
	int f[1000005];
	short dep[1000005];
	inline void Init(int n) {
		for (int i = 1;i <= 2 * n;i++) {
			f[i] = i;
			dep[i] = 1;
		}
	}
	stack <pair <int, int> > stk;
	inline int GetRoot(int v) {
		return (f[v] == v ? v : GetRoot(f[v]));
	}
	inline void Merge(int x, int y) {
		int u = GetRoot(x), v = GetRoot(y);
		if (u != v) {
			if (dep[u] < dep[v]) swap(u, v);
			stk.push(make_pair(v, f[v]));
			stk.push(make_pair(u + n * 2, dep[u]));
			f[v] = u;
			dep[u] = Max(dep[u], dep[v] + 1);
		} else {
			stk.push(make_pair(0, 0));
			stk.push(make_pair(0, 0));
		}
	}
	inline void Backroll() {
		pair <int, int> cur = stk.top();
		if (cur.first <= 2 * n) f[cur.first] = cur.second;
		else dep[cur.first - 2 * n] = cur.second;
		stk.pop();
		cur = stk.top();
		if (cur.first <= 2 * n) f[cur.first] = cur.second;
		else dep[cur.first - 2 * n] = cur.second;
		stk.pop();
	}
};
UndoDSU dsu[51];
struct Edge {
	int u, v, c;
};
Edge e[500005];
struct Query {
	int e, c;
};
Query qry[500005];

struct Segtree {
	vector <Query> vc[2000005];
	inline void Modify(int p, int pl, int pr, int l, int r, Query v) {
		if (l > r) return;
		if (pl == l && pr == r) {
			vc[p].push_back(v);
			return;
		}
		int mid = pl + pr >> 1;
		if (mid >= r) Modify(p << 1, pl, mid, l, r, v);
		else if (mid + 1 <= l) Modify(p << 1 | 1, mid + 1, pr, l, r, v);
		else {
			Modify(p << 1, pl, mid, l, mid, v);
			Modify(p << 1 | 1, mid + 1, pr, mid + 1, r, v);
		}
	}
	inline void Dfs(int p, int pl, int pr) {
		//printf("%d %d %d\n", p, pl, pr);
		int siz = vc[p].size();
		vector <int> col;
		for (int i = 0;i < siz;i++) {
			int eid = vc[p][i].e;
			dsu[e[eid].c].Merge(e[eid].u, e[eid].v + n);
			dsu[e[eid].c].Merge(e[eid].u + n, e[eid].v);
			col.push_back(e[eid].c);
		}
		if (pl == pr) {
			Edge cur = e[qry[pl].e];
			if (dsu[qry[pl].c].GetRoot(cur.u) != dsu[qry[pl].c].GetRoot(cur.v)) {
				puts("YES");
				e[qry[pl].e].c = qry[pl].c;
				//dsu[e[qry[pl].e].c].Merge(e[qry[pl].e].u, e[qry[pl].e].v + n);
				//dsu[e[qry[pl].e].c].Merge(e[qry[pl].e].u + n, e[qry[pl].e].v);
			} else {
				qry[pl].c = e[qry[pl].e].c;
				puts("NO");
			}
			//printf("%d %d\n", pl + 1, nxt[pl] - 1);
			Modify(1, 1, q, pl + 1, nxt[pl] - 1, qry[pl]);
			while (!col.empty()) {
				dsu[col.back()].Backroll();
				dsu[col.back()].Backroll();
				col.pop_back();
			}
			return;
		}
		int mid = pl + pr >> 1;
		Dfs(p << 1, pl, mid);
		Dfs(p << 1 | 1, mid + 1, pr);
		while (!col.empty()) {
			dsu[col.back()].Backroll();
			dsu[col.back()].Backroll();
			col.pop_back();
		}
	}
};
Segtree sgt;

inline void Read() {
	n = qread(); m = qread(); k = qread(); q = qread();
	for (int i = 1;i <= m;i++) {
		e[i].u = qread(); e[i].v = qread();
	}
	for (int i = 1;i <= q;i++) {
		qry[i].e = qread(); qry[i].c = qread();
	}
}

inline void Prefix() {
	for (int i = 1;i <= m;i++) lst[i] = q + 1;
	for (int i = q;i >= 1;i--) {
		nxt[i] = lst[qry[i].e];
		lst[qry[i].e] = i;
	}
	for (int i = 1;i <= k;i++) dsu[i].Init(n);
}

int main() {
	Read();
	Prefix();
	sgt.Dfs(1, 1, q);
	#ifndef ONLINE_JUDGE
	while (1);
	#endif
	return 0;
}
```

---

## 作者：ListenSnow (赞：4)

[原题链接](https://www.luogu.com.cn/problem/CF576E)

## 题意

给定一张 $n$ 个点 $m$ 条边的无向图。

一共有 $k$ 种颜色，一开始，每条边都没有颜色。

定义合法状态为仅保留染成 $k$ 种颜色中的任何一种颜色的边，图都是一张二分图。

有 $q$ 次操作，第 $i$ 次操作将第 $e_i$	条边的颜色染成 $c_i$。

但并不是每次操作都会被执行，只有当执行后仍然合法，才会执行本次操作。

你需要判断每次操作是否会被执行。

### 数据范围

$n,m,q \leq 5 \times 10^5,k \leq 50$。

## 思路

注意到本题中第 $i$ 次染色操作只会对保留颜色为 $c_i$ 的边能否形成二分图产生影响，同时颜色的总数也很小，就可以考虑类似于 [P5787](https://www.luogu.com.cn/problem/P5787) 的技巧，用 $k$ 个**扩展域并查集**分别维护每一种颜色的情况。

考虑对于一条边相邻的染色操作（记为操作 $i$ 和操作 $j$），操作 $i$ 所能直接影响的范围为 $[i,j-1]$，而其对染色操作 $[i+1,j-1]$ 的影响取决于操作 $i$ 能否被执行。

于是就可以将操作 $i$ 覆盖到 $[i+1,j-1]$ 中，在分治到叶子节点时判断操作 $i$ 能否被执行，如果不能被执行。此时虽然操作没有执行，但边还是存在的，还是需要判断原来的颜色是否为二分图。

可以发现操作不被执行实际上也就是把上一次执行的染色操作重新执行了一遍，那么直接把 $c[i]$ 改为上一次操作的颜色即可。

## code：

```cpp
#include<cstdio>
#include<cstring>
#include<algorithm>
#include<vector>
using namespace std;
const int N=5e5+10,K=55;
vector<int>e[N<<2];
int pos[N],top,u[N],v[N],a[N],c[N],n,m,k,q,f[K][N<<1],height[K][N<<1];
int find(int c,int x){return f[c][x]==x?x:find(c,f[c][x]);}
struct node{int c,x,y,add;}stk[N];
void merge(int c,int x,int y)
{
	if(x==y) return ;
    if(height[c][x]>height[c][y]) swap(x,y);
    stk[++top]=node{c,x,y,height[c][x]==height[c][y]};
    f[c][x]=y;height[c][y]+=height[c][x]==height[c][y];
}
void update(int p,int l,int r,int nl,int nr,int k)
{
	if(nl<=l&&r<=nr){e[p].push_back(k);return ;}
	int mid=l+r>>1;
	if(nl<=mid) update(p<<1,l,mid,nl,nr,k);
	if(nr>mid) update(p<<1|1,mid+1,r,nl,nr,k);
}
void solve(int p,int l,int r)
{
	int back=top,mid=l+r>>1;
	for(auto i:e[p])
	{
		int fx=find(c[i],u[a[i]]),fy=find(c[i],v[a[i]]);
		merge(c[i],find(c[i],u[a[i]]),find(c[i],v[a[i]]+n));
		merge(c[i],find(c[i],u[a[i]]+n),find(c[i],v[a[i]]));
	}
	if(l==r)
	{
		if(find(c[r],u[a[r]])==find(c[r],v[a[r]])) puts("NO"),c[r]=pos[a[r]]; 
		else puts("YES"),pos[a[r]]=c[r];
	}
	else solve(p<<1,l,mid),solve(p<<1|1,mid+1,r);
	while(top>back)
	{
		int c=stk[top].c,x=stk[top].x,z=stk[top].add;top--;
		height[c][f[c][x]]-=z;f[c][x]=x;
	}
}
int main()
{
//	freopen("in.txt","r",stdin);
	scanf("%d%d%d%d",&n,&m,&k,&q);
	for(int j=1;j<=k;j++)
	    for(int i=1;i<=n;i++)
	        f[j][i]=i,f[j][i+n]=i+n;
	for(int i=1;i<=m;i++) scanf("%d%d",&u[i],&v[i]),pos[i]=q+1;
	for(int i=1;i<=q;i++) scanf("%d%d",&a[i],&c[i]);
	int cnt=0;
	for(int i=q;i>=0;i--)
	{
		if(i+1<pos[a[i]]) update(1,1,q,i+1,pos[a[i]]-1,i);
		//i+1是因为如果判断i时直接把它加进来，这时的颜色是新的颜色，但后面撤销的就是原来的颜色，就会产生错误 
		pos[a[i]]=i;
	}
	memset(pos,0,sizeof(pos));solve(1,1,q);
	return 0;
}
```


---

## 作者：p_b_p_b (赞：4)

[$$\large \color{purple} My\; Blog$$](https://www.cnblogs.com/p-b-p-b/p/10359721.html)

---------

建议阅读[这篇博客](https://www.cnblogs.com/p-b-p-b/p/10358515.html)作为预备。~~无耻地打广告~~

------------

## 思路

与bzoj4025很相似，思路也差不多，可以看上面那篇博客。

仍然是用二分图的充要条件：没有奇环。

然而这题难在每条边的存在时间不固定，无法一开始知道。

可以每次在加入这条边的时间点判断能否成功修改，确定接下来一段时间它的颜色是什么。

具体见代码。

------------

## 代码

```cpp
#include<bits/stdc++.h>
namespace my_std{
	using namespace std;
	#define pii pair<int,int>
	#define fir first
	#define sec second
	#define MP make_pair
	#define rep(i,x,y) for (int i=(x);i<=(y);i++)
	#define drep(i,x,y) for (int i=(x);i>=(y);i--)
	#define go(x) for (int i=head[x];i;i=edge[i].nxt)
	#define sz 505050
	typedef long long ll;
	template<typename T>
	inline void read(T& t)
	{
		t=0;char f=0,ch=getchar();
		double d=0.1;
		while(ch>'9'||ch<'0') f|=(ch=='-'),ch=getchar();
		while(ch<='9'&&ch>='0') t=t*10+ch-48,ch=getchar();
		if(ch=='.')
		{
			ch=getchar();
			while(ch<='9'&&ch>='0') t+=d*(ch^48),d*=0.1,ch=getchar();
		}
		t=(f?-t:t);
	}
	template<typename T,typename... Args>
	inline void read(T& t,Args&... args){read(t); read(args...);}
	void file()
	{
		#ifndef ONLINE_JUDGE
		freopen("a.txt","r",stdin);
		#endif
	}
//	inline ll mul(ll a,ll b){ll d=(ll)(a*(double)b/mod+0.5);ll ret=a*b-d*mod;if (ret<0) ret+=mod;return ret;}
}
using namespace my_std;

int n,m,K,Q;
struct hh{int u,v,col;}edge[sz];
int id[sz],las[sz],L[sz],R[sz],pre[sz],col[sz];

struct hhhh{int x,y,col;bool s;};

struct hhh
{
	int fa[sz],f[sz],dep[sz];
	int getfa(int x){return x==fa[x]?x:getfa(fa[x]);}
	int getdis(int x){return x==fa[x]?0:f[x]^getdis(fa[x]);}
	void cancel(hhhh a){f[fa[a.x]=a.x]=0;dep[a.y]-=a.s;}
	bool connected(int x,int y){return getfa(x)==getfa(y);}
	hhhh merge(int x,int y,int col)
	{
		int fx=getfa(x),fy=getfa(y);
		if (dep[fx]>dep[fy]) swap(fx,fy),swap(x,y);
		int w=getdis(x)^getdis(y)^1;
		hhhh ret=(hhhh){fx,fy,col,0};
		f[fx]=w;fa[fx]=fy;
		if (dep[fx]==dep[fy]) ++dep[fy],ret.s=1;
		return ret;
	}
}G[55];
void cancel(stack<hhhh>S){while (!S.empty()) G[S.top().col].cancel(S.top()),S.pop();}

vector<int>v[sz<<2];
#define ls k<<1
#define rs k<<1|1
#define lson ls,l,mid
#define rson rs,mid+1,r
void insert(int k,int l,int r,int x,int y,int e)
{
	if (x<=l&&r<=y) return (void)(v[k].push_back(e));
	int mid=(l+r)>>1;
	if (x<=mid) insert(lson,x,y,e);
	if (y>mid) insert(rson,x,y,e);
}
void solve(int k,int l,int r)
{
	stack<hhhh>S;
	rep(i,0,(int)v[k].size()-1) 
	{
		hh e=edge[v[k][i]];
		if (!e.col) continue;
		int x=e.u,y=e.v,col=e.col;
		if (G[col].connected(x,y)) continue;
		S.push(G[col].merge(x,y,col));
	}
	if (l==r)
	{
		hh e=edge[id[l]];
		int w=G[col[l]].getdis(e.u)^G[col[l]].getdis(e.v)^1;
		bool t=G[col[l]].connected(e.u,e.v);
		cancel(S);
		if (!t||!w) return (void)(puts("YES"),edge[id[l]].col=col[l]);
		return (void)puts("NO");
	}
	int mid=(l+r)>>1;
	solve(lson);solve(rson);
	cancel(S);
}

int main()
{
	file();
	int x,y;
	read(n,m,K,Q);
	rep(i,1,K) rep(j,1,n) G[i].fa[j]=j;
	rep(i,1,m) read(x,y),edge[i]=(hh){x,y,0}; 
	rep(i,1,Q)
	{
		read(x,y);
		id[i]=x;col[i]=y;
		if (las[x]) R[las[x]]=i-1;
		pre[i]=las[x];las[x]=i;
		L[i]=i+1,R[i]=Q;
	}
	rep(i,1,Q) if (L[i]<=R[i]) insert(1,1,Q,L[i],R[i],id[i]);
	solve(1,1,Q);
	return 0;
}
```



---

## 作者：foreverlasting (赞：4)

[题面](https://www.luogu.org/problemnew/show/CF576E)

线段树分治。

这题的难点在于如何判断染色撤销的问题，其实是很好处理的。我们只需要用一个栈去保存它染色的情况，如果失败，则直接出栈就行了。

~~然后我这题忘记改颜色之后对应的位置都变了的问题，调了三小时。~~

code:
```
//2018.8.10 by ljz
#include<bits/stdc++.h>
using namespace std;
#define res register int
#define LL long long
#define inf 0x3f3f3f3f
#define eps 1e-15
inline int read(){
    res s=0;
    bool w=0;
    char ch=getchar();
    while(ch<'0'||ch>'9'){if(ch=='-')w=1;ch=getchar();}
    while(ch>='0'&&ch<='9')s=s*10+ch-'0',ch=getchar();
    return w?-s:s;
}
inline void _swap(res &x,res &y){
    x^=y^=x^=y;
}
inline int _abs(const res &x){
    return x>0?x:-x;
}
inline int _max(const res &x,const res &y){
    return x>y?x:y;
}
inline int _min(const res &x,const res &y){
    return x<y?x:y;
}
const int M=5e5+10,Q=5e5+10,N=5e5+10,K=50+10;
int n,m,k,q;
struct E{
    int u,v;
    E() {}
    E(res u,res v):u(u),v(v) {}
}edge[M];
struct MOD{
    int s,col,id,l,r;
    MOD() {}
    MOD(res s,res col,res id,res l):s(s),col(col),id(id),l(l) {}
}mod[Q];
int las[M],pre[Q],nxt[Q];
vector<MOD> F[Q<<2];
void insertmodify(res rt,res l,res r,res L,res R,MOD id){
    if(L<=l&&r<=R){
        F[rt].push_back(id);
        return;
    }
    if(l==r)return;
    res mid=(l+r)>>1;
    if(L<=mid)insertmodify(rt<<1,l,mid,L,R,id);
    if(R>mid)insertmodify(rt<<1|1,mid+1,r,L,R,id);
}
int st[Q][3],top;
namespace UNOINSET{
    int fa[K][M],H[K][M];
    bool va[K][M];
    int find(res x,res col,bool &flag){
    	while(fa[col][x])flag^=va[col][x],x=fa[col][x];
    	return x;
    }
    inline void unoin(res x,res y,res col,bool flag){
        if(H[col][x]>H[col][y])_swap(x,y);
        fa[col][x]=y,va[col][x]=flag,st[++top][0]=x,st[top][1]=col,st[top][2]=0;
        if(H[col][x]==H[col][y])H[col][y]++,st[top][2]=1;
    }
}
using namespace UNOINSET;
inline void solve(vector<MOD>G){
    if(!G.size())return;
    for(res i=0;i<G.size();i++){
        if(!mod[G[i].id].col)continue;
        res x=edge[G[i].s].u,y=edge[G[i].s].v,col=mod[G[i].id].col;
        bool flag=1;
        res fx=find(x,col,flag),fy=find(y,col,flag);
//		printf("%d %d\n",fx,fy);
        if(fx==fy)continue;
        unoin(fx,fy,col,flag);
    }
}
inline void remove(res now){
    while(top>now){
        if(st[top][2])st[top][2]=0,H[st[top][1]][fa[st[top][1]][st[top][0]]]--;
        fa[st[top][1]][st[top][0]]=0,top--;
    }
}
void segdiv(res rt,res l,res r){
    res now=top;
    solve(F[rt]);
    if(l==r){
        res x=edge[mod[l].s].u,y=edge[mod[l].s].v,col=mod[l].col;
        bool flag=1;
        res fx=find(x,col,flag),fy=find(y,col,flag);
//		printf("%d %d\n",fx,fy);
//		printf("%d\n",flag);
        if(fx==fy&&flag)puts("NO"),mod[l].col=mod[pre[l]].col;
        else puts("YES");
        remove(now);
        return;
    }
    res mid=(l+r)>>1;
    segdiv(rt<<1,l,mid),segdiv(rt<<1|1,mid+1,r);
    remove(now);
}
int main(){
    n=read(),m=read(),k=read(),q=read();
    for(res i=1;i<=m;i++){
        res u=read(),v=read();
        edge[i]=E(u,v);
    }
    for(res i=1;i<=q;i++){
        res s=read(),col=read();
        mod[i]=MOD(s,col,i,i+1);
        if(las[s])pre[i]=las[s],nxt[las[s]]=i-1;
        las[s]=i,nxt[i]=q;
    }
    for(res i=1;i<=q;i++)if(mod[i].l<=(mod[i].r=nxt[i]))insertmodify(1,1,q,mod[i].l,mod[i].r,mod[i]);
//	for(res i=1;i<=q;i++)printf("%d %d %d %d %d\n",mod[i].id,mod[i].l,mod[i].r,mod[i].s,mod[i].col);
    segdiv(1,1,q);
    return 0;
}
```

---

