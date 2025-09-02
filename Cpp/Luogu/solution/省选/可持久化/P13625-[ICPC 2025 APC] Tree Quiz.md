# [ICPC 2025 APC] Tree Quiz

## 题目描述

你的朋友想考考你。给你一棵有 $n$ 个节点的有根树，节点编号从 $1$ 到 $n$。对于每个节点 $i$，它的父节点是 $p_i$，除了根节点（没有父节点的节点）的 $p_i=0$。如果节点 $u=v$，或者节点 $u$ 是节点 $v$ 的父节点（如果存在）的祖先，那么我们说节点 $u$ 是节点 $v$ 的一个祖先。

如果节点 $z$ 同时是节点 $x$ 和节点 $y$ 的祖先，我们称节点 $z$ 是节点 $x$ 和 $y$ 的一个共同祖先。如果节点 $z$ 是节点 $x$ 和 $y$ 的一个共同祖先，并且节点 $x$ 和 $y$ 的任何一个共同祖先也都是节点 $z$ 的祖先，那么我们称节点 $z$ 是节点 $x$ 和 $y$ 的最近共同祖先。我们将节点 $x$ 和 $y$ 的最近共同祖先表示为 $\operatorname{LCA}(x,y)$。特别地，$\operatorname{LCA}(x,x)=x$。

你的朋友想要运行以下伪代码：

```
let L be an empty array
for x = 1 to n
  for y = 1 to n
    append ((x-1)*n*n + (LCA(x,y)-1)*n + (y-1)) to L
sort L in non-decreasing order
```

你的朋友有 $q$ 个问题，编号从 $1$ 到 $q$。在第 $j$ 个问题中，会给你一个整数 $k_j$，并要求你找出数组 $L$ 中的第 $k_j$ 个元素。请注意，$L$ 是以 $1$ 为起始下标的，所以其下标范围从 $1$ 到 $n^2$。为了通过测试，你必须回答所有问题。

## 说明/提示

输入中的树如图 K.1 所示。

![](https://cdn.luogu.com.cn/upload/image_hosting/3xe1w5tx.png)

$L$ 的元素为 $(0, 6, 8, 12, 14, 30, 31, 32, 33, 34, 56, 58, 60, 62, 64, 80, 81, 82, 84, 93, 106, 108, 110, 112, 124)$。

## 样例 #1

### 输入

```
5 3
3 0 2 2 3
1
18
25```

### 输出

```
0
82
124```

# 题解

## 作者：lzyqwq (赞：0)

::::info[题意]
给出 $n$ 个点的有根树，考虑一个 $n\times n$ 的二维数组，其中对于 $1\le x,y\le n$ 满足 $a_{x,y}=(x-1)n^2+(\text{LCA}(x,y)-1)n+y-1$。$q$ 次询问二维数组中第 $k$ 小的值。

$n,q\le 10^5$。
::::

首先不难注意到 $x$ 大的 $a_{x,y}$ 更大。同理在 $x$ 相同时 $\text{LCA}$ 大的 $a_{x,y}$ 更大。所以容易找到每组询问对应的 $x$。在 $x$ 固定后考虑 $\text{LCA}$ 会是哪个点。这里先把 $k$ 减掉 $x$ 更小的点对个数。

考虑对树做深搜，维护当前点 $x$ 根链信息。记 $\text{sz}_x$ 为以 $x$ 为根的子树大小，显然，对于根链上的一对父子结点 $u,v$，有 $\text{sz}_u-\text{sz}_v$ 个 $y$ 满足其与 $x$ 的 $\text{LCA}$ 为 $u$。对于 $x$ 本身而言则是有子树内 $\text{sz}_x$ 个点与其的 $\text{LCA}$ 为 $x$。于是用线段树维护每个祖先有多少个能贡献的 $y$，线段树二分出第 $k$ 小位置的所在的 $\text{LCA}$。然后再把 $k$ 减去 $\text{LCA}$ 更小的点对个数。

那么最后就是求 $x$ 和 $\text{LCA}$ 固定情况下 $y$ 的第 $k$ 小值，此时 $y$ 所在区域是一个子树或者两个子树的差集，主席树维护即可。

认为 $n,q$ 同阶，时空复杂度 $\mathcal{O}(n\log n)$。

```cpp
#include <bits/stdc++.h>
#define int long long
template<class T> void read(T &x) {
    x = 0; T f = 1; char c = getchar();
    for (; c < 48 || c > 57; c = getchar()) if (c == 45) f = -1;
    for (; c > 47 && c < 58; c = getchar()) x = x * 10 + c - 48; x *= f;
}
template<class T> void write(T x) {
    if (x > 9) write(x / 10); putchar(x % 10 + 48);
}
template<class T> void print(T x, char ed = '\n') {
    if (x < 0) putchar('-'), x = -x; write(x), putchar(ed);
}
using namespace std; const int N = 100005; vector<int> qr[N], g[N];
int n, q, p[N], k[N], ax[N], ay[N], rt, lca[N], sz[N], dfn[N], rv[N], c, s[N];
struct SGT {
    int s[N << 2];
    int ls(int x) { return x << 1; } int rs(int x) { return x << 1 | 1; }
    void U(int x, int l, int r, int k, int v) {
        if (l == r) return void(s[x] += v); int m = l + r >> 1;
        if (k <= m) U(ls(x), l, m, k, v); else U(rs(x), m + 1, r, k, v);
        s[x] = s[ls(x)] + s[rs(x)];
    }
    pair<int, int> Q(int x, int l, int r, int k) {
        if (l == r) return {l, k}; int m = l + r >> 1;
        return s[ls(x)] >= k ?
               Q(ls(x), l, m, k) : Q(rs(x), m + 1, r, k - s[ls(x)]);
    }
} t1;
struct CMT {
    int rt[N], ls[N << 5], rs[N << 5], a[N << 5], cnt;
    void U(int &x, int y, int l, int r, int k, int v) {
        x = ++cnt; a[x] = a[y] + v; if (l == r) return; int m = l + r >> 1;
        if (k <= m) U(ls[x], ls[y], l, m, k, v), rs[x] = rs[y];
        else U(rs[x], rs[y], m + 1, r, k, v), ls[x] = ls[y];
    }
    int Q(int xl, int xr, int yl, int yr, int l, int r, int k) {
        if (l == r) return l;
        int m = l + r >> 1, v = a[ls[xr]] - a[ls[xl]] - a[ls[yr]] + a[ls[yl]];
        return v >= k ? Q(ls[xl], ls[xr], ls[yl], ls[yr], l, m, k) :
                        Q(rs[xl], rs[xr], rs[yl], rs[yr], m + 1, r, k - v);
    }
} t2;
void dfs(int u) {
    dfn[u] = ++c; rv[c] = u; sz[u] = 1;
    for (int v : g[u]) dfs(v), sz[u] += sz[v];
}
void calc(int u) {
    t1.U(1, 1, n, u, sz[u]);
    for (int i : qr[u]) {
        auto [x, y] = t1.Q(1, 1, n, k[i]);
        lca[i] = x;
        if (s[x]) ay[i] = t2.Q(t2.rt[dfn[x] - 1], t2.rt[dfn[x] + sz[x] - 1],
                               t2.rt[dfn[s[x]] - 1],
                               t2.rt[dfn[s[x]] + sz[s[x]] - 1], 1, n, y);
        else ay[i] = t2.Q(t2.rt[dfn[x] - 1], t2.rt[dfn[x] + sz[x] - 1],
                          0, 0, 1, n, y);
    }
    t1.U(1, 1, n, u, -sz[u]);
    for (int v : g[u]) {
        t1.U(1, 1, n, u, sz[u] - sz[v]); s[u] = v;
        calc(v); t1.U(1, 1, n, u, sz[v] - sz[u]);
    }
}
signed main() {
    read(n); read(q);
    for (int i = 1; i <= n; ++i) {
        read(p[i]); if (!p[i]) rt = i; else g[p[i]].emplace_back(i);
    }
    for (int i = 1; i <= q; ++i) {
        read(k[i]); qr[ax[i] = (k[i] - 1) / n + 1].emplace_back(i);
        k[i] = (k[i] - 1) % n + 1;
    }
    dfs(rt);
    for (int i = 1; i <= n; ++i) t2.U(t2.rt[i], t2.rt[i - 1], 1, n, rv[i], 1);
    calc(rt);
    for (int i = 1; i <= q; ++i)
        print((ax[i] - 1) * n * n + (lca[i] - 1) * n + ay[i] - 1);
    return 0;
}
```

---

