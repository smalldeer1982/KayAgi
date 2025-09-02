# 【MX-X9-T7】『GROI-R3』此花绽放之时

## 题目背景

在盛开的樱花树下，

属于我们的最后一场演奏会开始了。

## 题目描述

樱乃给你一棵 $n$ 个点的树，点的编号为 $1\sim n$。每个点初始有点权 $a_i=0$ 和颜色 $c_i$。你需要维护三种操作：

- `1 x y c`：把点 $x\sim y$ 最短路径上所有点颜色改为 $c$。
- `2 x w`：把点 $x$ 所属极大相同颜色连通块中的所有点的点权增加 $w$。
- `3 x`：查询点 $x$ 点权。

## 说明/提示

**【样例解释】**

![](https://cdn.luogu.com.cn/upload/image_hosting/jkwu7bmq.png)

样例的树如图。

一开始所有点颜色均为 $1$。

- 第 $1$ 次操作：询问 $1$ 的点权。答案为 $0$；
- 第 $2$ 次操作：把 $1$ 所处极大连通块所有点点权加 $1$。当前点权序列为 $[1,1,1,1,1]$；
- 第 $3$ 次操作：查询 $2$ 的点权。答案为 $1$；
- 第 $4$ 次操作：把 $3\sim 5$ 最短路径所有点颜色改为 $2$。当前颜色序列为 $[2,2,2,1,2]$；
- 第 $5$ 次操作：把 $1$ 所处极大连通块所有点点权加 $2$。当前点权序列为 $[3,3,3,1,3]$；
- 第 $6$ 次操作：查询 $1$ 的点权。答案为 $3$；
- 第 $7$ 次操作：查询 $4$ 的点权。答案为 $1$。

**【数据范围】**

**本题采用捆绑测试。**

| 子任务编号 |   $n,q\leq$    | 特殊性质 | 分值 |
| :----------: | :--: | :------------: | :------: |
|     1      |     $5000$     |        | $10$ |
|     2      | $2\times 10^5$ |    A     | $20$ |
|     3      | $2\times 10^5$ |    B     | $10$ |
|     4      | $5\times 10^4$ |        | $30$ |
|     5      | $2\times 10^5$ |        | $30$ |

- 特殊性质 A：保证 $f_i=i-1$。
- 特殊性质 B：保证没有 1 操作。

对于 $100\%$ 的数据，保证 $2\leq n,q\leq 2\times 10^5$，$1\leq c_i\leq n$，$1\leq f_i\leq i-1$，$1 \le x, y, c \le n$，$1 \le w \le 10^9$，保证至少有一次 3 操作。

## 样例 #1

### 输入

```
5 7
1 1 1 1 1
1 2 2 1
3 1
2 1 1
3 2
1 3 5 2
2 1 2
3 1
3 4
```

### 输出

```
0
1
3
1
```

## 样例 #2

### 输入

```
10 20
1 1 1 1 1 1 1 1 1 1
1 1 1 2 1 5 2 1 2
2 8 614463136
1 8 2 6
2 1 694700038
2 10 835675175
1 2 6 1
2 1 890463929
2 3 371010342
3 8
1 6 5 7
3 10
2 5 933771207
1 6 4 7
3 2
3 8
3 7
3 10
3 10
3 7
3 2
3 7```

### 输出

```
614463136
2711612582
2809708614
614463136
1875937407
2711612582
2711612582
1875937407
2809708614
1875937407
```

# 题解

## 作者：lsj2009 (赞：5)

## Preface

验题人题解。

## Description

给定一棵 $n$ 个节点的树，每个点有点权和颜色，你需要支持如下操作：
- 修改一条路径上所有节点的颜色为 $c$。
- 将点 $u$ 所在的极大的同色连通块的所有节点权值加上 $x$。
- 求点 $u$ 的权值。

共有 $q$ 次操作。

$1\le n,m,q\leq 2\times 10^5$。

## Solution
		
考虑一个暴力：每次修改时找到极大同色连通块的根，给他打上一个 tag，形如：
- $(t,c,v)$ 表示若在 $t$ 时刻时颜色为 $c$，则将权值加上 $v$。

每次询问时，从上往下遍历 $u$ 的到根链，将所有 tag pushdown 即可（pushdown tag $(t,c,v)$ 从 $fa_v$ 到 $v$ 时就需要满足在 $t$ 时刻 $v$ 颜色为 $c$）。

一个非常严重的问题：由于有颜色、时间的限制，**tag 难以合并**。

我们尝试将 tag 更改为 $(c,v)$ 表示：若当前时刻颜色为 $c$，则将权值加上 $v$。

**直接更改为何有错？**

![](https://s21.ax1x.com/2025/02/22/pEllnJA.png)

如图，初始时所有点颜色均相同，对连通块加上一个权值 $v$，tag 被打在 $1$ 号点处，随后我们修改路径 $3\leftrightarrow 4$ 的颜色。

则此时再 pushdown $5$ 到根链上的 tag，tag 根本无法作用在 $5$ 上。

仔细分析，发现修改路径 $u\leftrightarrow v$ 的颜色会使得一个在 $u\leftrightarrow v$ 上方的点 $x$ 的 tag 无法正常（可能是该加的没加，也可能是不该加的加了）作用在 $u\leftrightarrow v$ 下方的一个点 $y$ 上。

故而我们只需要在修改 $u\leftrightarrow v$ 的颜色前分别将 $u,v$ 到根链上的 tag 不断 pushdown 到 $u\leftrightarrow v$ 之下即可（下面称之为 $\operatorname{access}(u),\operatorname{access}(v)$ 操作）。

则此时 tag 不再有时间 $t$ 的限制，而 **仅受到当前颜色的限制**。**而颜色相同的 tag 可以直接加和合并**。

考虑对上述暴力算法进行优化。

套路地，我们进行树剖，对于每种颜色各开一个动态开点线段树维护每个位置的 tag。

每次将一个点附加上 tag 时将其所在重链应当附加上这个 tag 的点全部加上，则被影响的点对应一个区间，使用线段树/ODT 容易快速找到。

此时一个点上的 tag 仅会影响其轻子树；则我们在做一个 $\operatorname{access}(u)$ 时**只会在轻边处进行 pushdown 操作** 即可。

若 pushdown 一个节点的 tag 复杂度为 $\mathcal{O}(K)$，则我们获得了一个 $\mathcal{O}(qK\log{n})$ 的做法。

然而暴力做 $K$ 是 $\mathcal{O}(deg\log{n})$ 的，$deg$ 可能达到 $\mathcal{O}(n)$ 级别，复杂度仍然无法接受。

注意到我们在做 $\operatorname{access}(u)$ 操作时，如果在做 $\operatorname{pushdown}(x)$，那么我们 **暂且只需要把 tag pushdown 至 $x$ 到 $u$ 的下一个节点 $y$ 即可**（而且只需要 pushdown $y$ 对应颜色的 tag），$x$ 的其余轻子树可以暂且不 pushdown。

这样子我们 $K$ 就降到了 $\mathcal{O}(\log{n})$，仅有线段树操作带了的 $\log$。

则这样子做我们 pushdown 后 **不应把标记清空**，否则 $x$ 其余轻子树无法收到 tag。

而 **为了避免标记重复下传**，我们应记一个 $c_{x,u}$ 表示 $u$ 上次从父亲获得颜色为 $x$ 的 tag 的值，每次扣掉这个才是新加的真实值。

在更新 $u\leftrightarrow v$ 路径颜色为 $x$ 时，为了防止之前已有的关于 $x$ 的 tag 下传，我们也需要更新路径上所有作为轻儿子的 $w$ 的 $c_{x,w}$ 的值。

然后就做完了，使用线段树实现，时空复杂度均为 $\mathcal{O}(n\log^2{n})$。 

### Code

[code link](https://www.luogu.me/paste/sy98t2zu)。

其实并不难写（出题人和独立验题人都只写了 4k），但是我写了 9k，不知道什么原因。/ng

---

## 作者：xxxxxzy (赞：4)

写篇学习笔记。

套路的考虑给每个极大连通块选最上面点的作为代表元，每次给同色连通块修改，将 $u$ 的标记表示为 $(c,v)$， 代表如果 $col_u = c$，就 $a_u \to a_u + v$。

考虑到，修改链上的颜色会对标记的下传造成影响，比如修改点 $w$ 下方的与 $w$ 同连通块的 $(u,v)$，会导致 $w$ 的标记无法下传到 $(u,v)$ 以下的地方。

又观察到，颜色修改只会对链进行修改，所以可以考虑把链上方的标记全部下放至链下方，也就是对链的两个端点 $(u,v)$ 进行 $(rt,u)$ 和 $(rt,v)$ 的标记下放，记这个操作为 $\text{pway}(u),\text{pway}(v)$。

考虑标记如何进行合并，第一维 $c$ 对每种颜色开一颗动态开点线段树，这样标记就可以合并了。观察到，每次对 $u$ 标记下放，只需要下放当前 $col_u$ 的标记，因为其他的标记并没有意义，这样下放的 $tag$ 也是一个 $(c,v)$ 的形式。

套路地，树剖并维护非轻儿子。

考虑对重链中的一个点 $u$ 加上标记 $(c,v)$ 如何快速更新，首先找到 $u$ 以下的且和 $u$ 形成连通块的极长 $\text{dfn}$ 序区间全部加上标记 $(c,v)$，为了统计答案，再开一个树状数组来区间修改。

快速维护单点颜色和 $\text{dfn}$ 序上极大连通块可以采用 ODT 快速实现，不过值得注意的是，每次应将两个相邻的同颜色区间合并。

再考虑如何更新轻儿子，会发现原来的标记会对轻儿子多次下放，或者会下放不了，为了解决这个问题，拿一个 map 记录 $s_{u,col}$ 代表 $u$ 从父亲节点接受了多少 $c=col$ 的标记。

这样链修改颜色的操作就维护完了，继续考虑剩下两个操作，首先是连通块加，通过不断往上跳重链找到连通块的代表元并打上标记；其次是查询，只需要对查询节点 $u$ 进行 $\text{pway(u)}$ 然后输出 $u$ 的值即可。

代码部分参考了 @lsj2009 的代码。

```cpp
#include <bits/stdc++.h>
#define ll long long
#define IOS ios::sync_with_stdio(0), cin.tie(0), cout.tie(0)
#define pii pair<ll, ll>
#define mp make_pair
#define pb emplace_back
#define ld lower_bound
#define rep(i, a, b) for (int i = (a); i <= (b); i++)
#define drep(i, a, b) for (int i = (a); i >= (b); i--)
#define U(i, a, b) for (int i = (a); i < (b); i++)
#define F for
#define W while
#define ud upper_bound
#define mem(s, k) memset(s, k, sizeof(s))
#define fi first
#define se second
#define ull unsigned long long
#define vec vector <int>
#define fv inline void
#define fn inline static
using u16 = unsigned short; using u32 = unsigned; using u64 = unsigned ll; using u128 = __uint128_t;
using i16 = short; using i32 = int; using i64 = ll; using i128 = __int128_t;
using namespace std;
const i32 N = 2e5 + 5;
i32 n;
struct SGT {
  struct node { i32 ls, rs; i64 t; }seg[N * 80];
  i32 tot;
  i32 newnode() { return ++tot; }
  fv upd(i32 &p, i32 ql, i32 qr, i64 v, i32 l = 1, i32 r = n) {
    if (ql > r || qr < l) return ;
    if (!p) p = newnode();
    if (ql <= l && r <= qr) return (void)(seg[p].t += v);
    i32 mid = (l + r) >> 1;
    upd(seg[p].ls, ql, qr, v, l, mid);
    upd(seg[p].rs, ql, qr, v, mid + 1, r);
  }
  inline i64 qry(i32 p, i32 x, i32 l = 1, i32 r = n) {
    if (!p || x > r || x < l) return 0;
    if (l == r) return seg[p].t;
    i32 mid = (l + r) >> 1;
    return qry(seg[p].ls, x, l, mid) + qry(seg[p].rs, x, mid + 1, r) + seg[p].t;
  }
}T;
struct node { i32 l, r; mutable i32 v; };
bool operator < (const node &x, const node &y) { return x.l < y.l; }
struct ODT {
  set <node> S;
  inline auto split(i32 pos) {
    auto it = S.ld({pos, -1, 0});
    if (it != S.end() && it->l == pos) return it;
    --it; i32 l = it->l, r = it->r, v = it->v;
    S.erase(it); S.insert({l, pos - 1, v});
    return S.insert({pos, r, v}).fi;
  }
  fv emerge(i32 l, i32 r, i32 x) {
    auto itr = split(r + 1), itl = split(l);
    for (auto it = itl; it != itr; it++);
    S.erase(itl, itr);
    auto p = S.insert({l, r, x}).fi; itl = itr = p;
    bool L = 0, R = 0;
    while (itl -> v == p -> v) itl--;
    while (itr -> v == p -> v) itr++; --itr;
    if (!L) itl++;
    l = itl -> l, r = itr -> r, x = p -> v;
    S.erase(itl, ++itr), S.insert({l, r, x});
  }
  inline pii qryLR(i32 x) { auto it = --S.ud({x, -1, 0}); return mp(it->l, it->r); }
  inline i32 qry(i32 x) { auto it = --S.ud({x, -1, 0}); return it->v; }
} S[N];
struct BIT {
  i64 c[N];
  fv upd(i32 x, i64 v) { for (; x < N; x += x & -x) c[x] += v; }
  inline i64 qry(i32 x) { i64 ans = 0; for (; x; x -= x & -x) ans += c[x]; return ans; }
  fv upd(i32 l, i32 r, i64 v) { upd(l, v), upd(r + 1, -v); }
}B;
map <i32, i64> c[N];
i32 son[N], dfn[N], tp[N], siz[N], rt[N], dep[N], fa[N], id[N], ed[N], tot;
vec G[N];
fv dfs1(i32 u, i32 f) {
  fa[u] = f, dep[u] = dep[f] + 1, siz[u] = 1;
  for (i32 v : G[u]) {
    if (v == f) continue;
    dfs1(v, u), siz[u] += siz[v];
    if (siz[v] > siz[son[u]]) son[u] = v;
  }
}
fv dfs2(i32 u, i32 top) {
  tp[u] = top, dfn[u] = ++tot, id[tot] = u;
  ed[top] = max(ed[top], tot);
  if (son[u]) dfs2(son[u], top);
  for (i32 v : G[u]) {
    if (v == fa[u] || v == son[u]) continue;
    dfs2(v, v);
  }
}
fv upd(i32 u, i64 k, i32 op = 1) {
  i32 col = S[tp[u]].qry(dfn[u]);
  auto [l, r] = S[tp[u]].qryLR(dfn[u]);
  l = max((i32)l, (i32)dfn[u]);
  if (op != 2) c[col][u] += k;
  if (op) T.upd(rt[col], l, r, k), B.upd(l, r, k);
}
fv pd(i32 u, i32 op = 1) { //fa -> u
  if (u == 1) return ;
  i32 col = S[tp[u]].qry(dfn[u]);
  i64 tag = T.qry(rt[col], dfn[fa[u]]) - c[col][u];
  upd(u, tag, op);
}
i32 stk[N], stp;
fv pway(i32 u) {
  stp = 0;
  while (tp[u] != 1) stk[++stp] = tp[u], u = fa[tp[u]];
  drep (i, stp, 1) pd(stk[i]);
}
fv upd1(i32 u, i32 v, i32 c) {
  pway(u), pway(v);
  while (tp[u] != tp[v]) {
    if (dep[tp[u]] < dep[tp[v]]) swap(u, v);
    S[tp[u]].emerge(dfn[tp[u]], dfn[u], c);
    pd(tp[u], 0), u = fa[tp[u]];
  }
  if (dep[u] > dep[v]) swap(u, v);
  S[tp[u]].emerge(dfn[u], dfn[v], c);
  if (u == tp[u]) pd(u, 0);
}
fv upd2(i32 u, i64 k) {
  i32 up = 1, c = S[tp[u]].qry(dfn[u]);
  while (u) {
    auto [l, r] = S[tp[u]].qryLR(dfn[u]);
    if (S[tp[u]].qry(dfn[u]) != c) break;
    if (l != dfn[tp[u]]) { up = id[l]; break; }
    up = tp[u], u = fa[tp[u]];
  }
  upd(up, k, 2);
}
fn i64 qsum(i32 u) { pway(u); return B.qry(dfn[u]); }
i32 op, u, v, k, q, col[N];
int main() {
  IOS;
  cin >> n >> q;
  rep (i, 1, n) cin >> col[i];
  rep (i, 2, n) cin >> u, G[u].pb(i);
  dfs1(1, 0), dfs2(1, 1);
  rep (i, 1, n) if (tp[i] == i) S[i].S.insert({0, n + 1, 0});
  rep (i, 1, n) S[tp[i]].emerge(dfn[i], dfn[i], col[i]);
  rep (i, 1, q) {
    cin >> op >> u;
    if (op == 1) cin >> v >> k, upd1(u, v, k);
    else if (op == 2) cin >> k, upd2(u, k);
    else cout << qsum(u) << "\n";
  }
}
```

---

