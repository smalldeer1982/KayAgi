# [JRKSJ R3] 琴琴的树

## 题目描述

琴琴有一棵二叉树，满足：

* 该树有无穷多个结点。
* 每个结点都有编号和权值。初始所有结点的权值为 $0$。
* 树根的编号为 $1$。
* 若一个结点的编号为 $i$，则该结点的左右儿子的编号分别是 $2i,2i+1$。

琴琴要对树进行共 $m$ 次操作，每次操作是二者之一：

1. 将编号为 $x$ 的结点为根的子树中的每个结点的权值都加 $v$。
2. 求树上编号为 $x$ 的结点到编号为 $y$ 的结点的路径上每个结点的权值和。答案对 $2^{32}$ 取模。

不过琴琴不会直接给出 $x,y$。她再给出一个长度为 $n$ 的 $01$ 序列 $a$，每次给出 $x$ 或 $y$ 时给出一个区间 $[l_x,r_x]$ 或 $[l_y,r_y]$，这个数就是将这个区间视作二进制数的值。

## 说明/提示

### 样例解释

该树的前四层如图所示：

![](https://cdn.luogu.com.cn/upload/image_hosting/394f62g7.png)

第一个操作：将以 $2$ 为根的子树中的结点权值加上 $5$。\
第二个操作：求 $2\rightarrow 10$ 的路径上的点的权值和。\
第三个操作：将以 $2$ 为根的子树中的结点权值加上 $3$。\
第四个操作：求 $10\rightarrow 1$ 的路径上的点的权值和。\
第五个操作：求 $1\rightarrow 2$ 的路径上的点的权值和。

### 数据规模与约定

**本题采用捆绑测试。**

| $\text{Subtask}$ | $n\le$ | $m\le $ | 分值 |
| :----------: | :----------: | :----------: | :----------: | 
| $1$ | $10$ | $10^3$ | $5$ |
| $2$ | $20$ | $10^5$ | $5$ |
| $3$ | $10^4$ | $10^4$ | $20$ |
| $4$ | $4\times 10^5$ | $4\times 10^5$ | $70$ |

对于 $100\%$ 的数据，$1\le n,m\le 4\times 10^5$，$1\le v \le 10^9$，$1\le l_x\le r_x\le n$，$1\le l_y\le r_y\le n$，保证 $x,y\ne 0$。

## 样例 #1

### 输入

```
5 5
01010
1 4 5 5
2 1 3 2 5
1 2 3 3
2 1 5 1 2
2 3 4 4 5```

### 输出

```
15
24
8```

# 题解

## 作者：critnos (赞：4)

可以看出链求和要差分吧。。$x,y$ 的 LCA 就是两区间去掉前导 $0$ 的 LCP。

先对 $x,y$ 去掉前导 $0$。

然后到根的和就是区间的每个前缀对应的结点的和。

不过维护区间和结点的对应关系过于复杂，所以我们直接维护区间即可。即实质上的，对于一个结点加，其实是把序列上所有等价于这个结点的区间加。

子树加的话首先要找到 $x$ 在序列上所有相同的区间。SA 的话要找到所有 $lcp(l_x,y)\ge r_x-l_x+1$ 的后缀 $y$。这个显然是在 height 数组上的一个区间。

有两个线性空间的做法：height 数组线性空间，$O(\log n)$ 时间的 $O(n)-O(1)$ RMQ 上二分或者线段树二分，和离线排序，每次加入所有 $\ge r_x-l_x+1$ 的 $height_i$，然后用并查集维护连续段（这个做法可以用线性树上并查集优化到线性时间，不过不是瓶颈，所以不重要）。

其实每个后缀的所有非 $0$ 前缀都组成了一条从根往下的链。所以对每个后缀进行操作，就是将这个后缀的所有长度 $\ge r_x-l_x+1$ 的前缀加。

看做二维平面，将每个后缀平移到同样的位置（或者说是每个后缀的前缀从都从 $1$ 开始编号），那么就是一个矩形加。

设二分出的区间为 $L,R$，二维平面为 $a_{x,y}$，那么就是 $\forall x\in [L,R],y\in [r_x-l_x+1,n],a_{x,y}$ 加上 $v$。

至于链求和，就是求这个后缀所有长度 $\le r-l+1$ 的前缀的和。设这个区间为 $[l,r]$，那么就是求 $\sum_{i=1}^{r-l+1} a_{rk_l,i}$。

这个 CDQ+树状数组，随便拆一下贡献即可，$O(n\log ^2n)$ 时间，线性空间。

代码可以找我要。

常数的话，线段树 $O(n\log^2 n)$ 找区间有被卡常的风险。空间需要精细实现。其他应该还好。

---

## 作者：Alex_Wei (赞：2)

> [P7982 [JRKSJ R3] 琴琴的树](https://www.luogu.com.cn/problem/P7982)

以下仅讨论子串开头字符为 $\texttt 1$ 的情况，若非则令左端点 $l\gets rt_l$，其中 $rt_i$ 表示 $i$ 右边第一个 $\texttt 1$ 的位置。

设 $L_x = r_x - l_x + 1$，$L_y = r_y - l_y + 1$，$s[l_x, r_x]$ 对应 SAM 节点 $x$，$y$ 同理。

操作一将所有以 $s[l_x, r_x]$ 为前缀的字符串的权值增加 $v$，操作二查询 $s[l_x, r_x]$ 和 $s[l_y, r_y]$ 的所有长度不小于 $A = lcp(s[l_x, r_x], s[l_y, r_y])$ 的前缀的权值之和。

考虑到所有涉及到的字符串均为 $s$ 的子串，建出 $s$ 的 SAM，问题相当于裸子树加链求和。直接做，时间复杂度 $\mathcal{O}(n + q\log ^ 2 n)$，空间复杂度 $\mathcal{O}(n + q)$。

因为 SAM link 树上一个节点对应多个子串，所以需要特殊处理端点处的修改和贡献：

- 非端点处修改对非端点处查询的贡献：子树加，链求和，注意一个点的权值 $a_i$ 加 $v$ 则其贡献增加 $vstr_i$，其中 $str_i$ 表示节点 $i$ 子串个数。相当于对 $a_i$ 区间加，区间求 $a_ib_i$ 的和。用线段树写会被卡常卡空间，对 $b_i$ 做前缀和拆贡献可以用两个 BIT 维护，类似 BIT 区间加区间求和。
- 非端点处修改对端点处查询的贡献：维护 $c_i$ 表示 $i$ 作为非端点的修改值之和，修改时区间修改 $c$。对于 $x$ 贡献加上 $(L_x - len(fa(x)))c_x$，其中 $L_x - len(fa(x))$ 表示本次查询涉及到节点 $x$ 的子串数量。对于 $y$ 同理。注意特判 $x = y$ 的情况，此时贡献为 $(\max(L_x, L_y) - \min(L_x, L_y) + 1)c_x$。
- 端点处修改对非端点处查询的贡献：维护 $d_i$ 表示 $i$ 作为端点的修改值之和，注意乘以产生贡献的子串数量。修改给 $d_x$ 加上 $(len(x) - L_x + 1) v$，查询区间查询。
- 端点处修改对端点处查询的贡献：为每个 $x$ 开线段树 $T_x$ 维护 $x$ 在作为端点被修改时每个子串的权值，修改对 $T_x$ 区间加，查询对 $T_x$ 区间查询。空间复杂度无法接受，离线 BIT 处理。

注意当 $x, y$ 不为祖先后代关系时，它们的 LCA $D$ 仅有最长串产生贡献，所以需维护 $e_i$ 表示 $i$ 作为端点的修改值之和以快速求出贡献，这部分是单点修改单点查询。

这题最大的难点在于只给了 64MB：

- SAM 五个数组：`son * 2, len, fa, ed`。
- 树剖六个数组：`sz, son, dep, dfn, rev, top`，`fa` 算在 SAM 部分。
- 两个单点修改区间查询 / 区间修改单点查询 BIT：`c, d`。
- 一个区间修改区间查询 BIT，三个数组：`Sb, a1, a2`，其中 $Sb$ 表示 $b$ 前缀和。
- 建树的链式前向星 `hd, nxt, to`。
- 第四部分离线询问 BIT 的链式前向星 `hd, nxt, l, r, v` 和一个布尔数组 `type` 表示修改或查询。注意链式前向星是反着的，所以为按时间顺序处理，记录 `pre` 实现双向链表。BIT 可直接用之前的区间修改区间查询 BIT。
- 一些杂七杂八的数组：字符串 `s`，端点修改值 `e`，离线 BIT 答案数组 `ans`，还有一开始的 `rt`。

因为 SAM 有两倍节点，所以一些数组是 $2n$ 的。算一下空间复杂度肯定炸了，需要极其精细地实现才可通过，包括但不限于重复利用不会同时使用的数组，将大小为 $X$ 且值域 $\leq 10 ^ 6$ 的数组用大小为 $\dfrac {2X} 3$ 的数组代替（但是不能代替太多否则跑得太慢），用 `bitset` 代替布尔数组。

卡空间 + 卡常花了四个小时，建议出题人自裁，或者时间开到 2s，空间开到至少 128MB。

```cpp
// 卡你妈空间啊
// 卡你妈常啊
#include <bits/stdc++.h>
using namespace std;
using ll = long long;
using uint = unsigned int;
bool Mbe;
char buf[1 << 16], *p1 = buf, *p2 = buf;
#define gc (p1 == p2 && (p2 = (p1 = buf) + fread(buf, 1, 1 << 16, stdin), p1 == p2) ? EOF : *p1++)
inline int read() {
  int x = 0;
  char s = gc;
  while(!isdigit(s)) s = gc;
  while(isdigit(s)) x = x * 10 + s - '0', s = gc;
  return x;
}
constexpr int N = 8e5 + 5;
constexpr int M = 4e5 + 5;
struct ArrayM {
  int val[M * 2 / 3];
  ArrayM () {memset(val, 0, sizeof(val));}
  void assign(int x, int v) {
    int c = x / 3, r = x % 3;
    if(r == 0) val[c << 1] |= v;
    if(r == 1) val[c << 1] |= (v & 1023) << 20, val[c << 1 | 1] |= v >> 10;
    if(r == 2) val[c << 1 | 1] |= v << 10;
  }
  int operator [] (int x) {
    int c = x / 3, r = x % 3;
    if(r == 0) return val[c << 1] & 1048575;
    if(r == 1) return (val[c << 1] >> 20) | ((val[c << 1 | 1] & 1023) << 10);
    if(r == 2) return val[c << 1 | 1] >> 10;
  }
} ed, suf;
struct ArrayN {
  int val[N * 2 / 3];
  ArrayN () {memset(val, 0, sizeof(val));}
  void assign(int x, int v) {
    int c = x / 3, r = x % 3;
    if(r == 0) val[c << 1] |= v;
    if(r == 1) val[c << 1] |= (v & 1023) << 20, val[c << 1 | 1] |= v >> 10;
    if(r == 2) val[c << 1 | 1] |= v << 10;
  }
  int operator [] (int x) {
    int c = x / 3, r = x % 3;
    if(r == 0) return val[c << 1] & 1048575;
    if(r == 1) return (val[c << 1] >> 20) | ((val[c << 1 | 1] & 1023) << 10);
    if(r == 2) return val[c << 1 | 1] >> 10;
  }
} top;
int cnt = 1, len[N], fa[N];
namespace SAM {
  int las = 1, son[2][N];
  void ins(int it) {
    int cur = ++cnt, p = las;
    ed.assign(len[cur] = len[p] + 1, cur);
    las = cur;
    while(!son[it][p]) son[it][p] = cur, p = fa[p];
    if(!p) return fa[cur] = 1, void();
    int q = son[it][p];
    if(len[p] + 1 == len[q]) return fa[cur] = q, void();
    int cl = ++cnt;
    son[0][cl] = son[0][q], son[1][cl] = son[1][q];
    len[cl] = len[p] + 1, fa[cl] = fa[q], fa[q] = fa[cur] = cl;
    while(son[it][p] == q) son[it][p] = cl, p = fa[p];
  }
}
char s[M];
int n, m, Q;
uint ans[M], c[N];
int *son = SAM::son[0], *sz = SAM::son[1], dep[N];
int dn, dfn[N], *rev = son;
uint E, hd[N], nxt[N], to[N];
void add(int u, int v) {nxt[++E] = hd[u], hd[u] = E, to[E] = v;}
bool isanc(int u, int v) {return dfn[u] <= dfn[v] && dfn[v] < dfn[u] + sz[u];}
void dfs1(int id) {
  sz[id] = 1, dep[id] = dep[fa[id]] + 1;
  for(int i = hd[id]; i; i = nxt[i]) {
    dfs1(to[i]), sz[id] += sz[to[i]];
    if(sz[son[id]] < sz[to[i]]) son[id] = to[i];
  }
}
void dfs2(int id, int tp) {
  dfn[id] = ++dn, top.assign(id, tp);
  if(son[id]) dfs2(son[id], tp);
  for(int i = hd[id]; i; i = nxt[i]) if(to[i] != son[id]) dfs2(to[i], to[i]); 
}
int locate(int l, int r) {
  if(l > r) return 0;
  int x = ed[r], L = r - l + 1;
  while(1) {
    int tp = top[x];
    if(len[fa[tp]] >= L) {x = fa[tp]; continue;}
    l = dfn[tp], r = dfn[x];
    while(l < r) {
      int m = l + r >> 1;
      len[rev[m]] >= L ? r = m : l = m + 1;
    }
    return rev[l];
  }
}
struct BIT1 {
  uint *c = hd, *c2 = nxt, *val = to;
  void init(int type) {
    memset(c, 0, N << 2);
    memset(c2, 0, N << 2);
    memset(val, 0, N << 2);
    for(int i = 1; i <= cnt; i++) { // 2 -> 1
      val[i] = val[i - 1];
      if(type == 1) val[i] += len[rev[i]] - len[fa[rev[i]]];
      else val[i] += 1;
    }
  }
  void add(int x, uint v) {
    uint v2 = v * val[x - 1];
    while(x <= cnt) c[x] += v, c2[x] += v2, x += x & -x;
  }
  void add(int l, int r, int v) {add(l, v), add(r + 1, -v);}
  uint query(int x) {
    uint s = 0, s2 = 0, coef = val[x];
    while(x) s += c[x], s2 += c2[x], x -= x & -x;
    return coef * s - s2;
  }
  uint query(int l, int r) {return query(r) - query(l - 1);}
} tr;
struct BIT2 {
  uint c[N];
  void add(int x, uint v) {while(x <= cnt) c[x] += v, x += x & -x;}
  void add(int l, int r, uint v) {add(l, v), add(r + 1, -v);}
  uint query(int x) {uint s = 0; while(x) s += c[x], x -= x & -x; return s;}
  uint query(int l, int r) {return query(r) - query(l - 1);}
} val, sumv;
uint *pre = val.c;
struct OFFLINE {
  int cnt, hd[N], v[N];
  ArrayN nxt, l, r;
  bitset<N> type;
  void add(int u, bool _t, int _l, int _r, int _v) {
    nxt.assign(++cnt, hd[u]), hd[u] = cnt;
    type[cnt] = _t;
    l.assign(cnt, _l);
    r.assign(cnt, _r);
    v[cnt] = _v;
  }
} e;
bool Med;
int main() {
  fprintf(stderr, "%.4lf MB\n", (&Mbe - &Med) / 1048576.0);
  #ifdef ALEX_WEI
    freopen("1.in", "r", stdin);
    freopen("1.out", "w", stdout);
  #endif
  cin >> n >> m >> s + 1;
  suf.assign(n + 1, n + 1); // add this line
  for(int i = n; i; i--) suf.assign(i, s[i] == '0' ? suf[i + 1] : i);
  for(int i = n; i; i--) SAM::ins(s[i] - '0');
  for(int i = 2; i <= cnt; i++) add(fa[i], i);
  memset(SAM::son, 0, N << 3); // add this line
  dfs1(1), dfs2(1, 1);
  for(int i = 1; i <= cnt; i++) rev[dfn[i]] = i;
  tr.init(1);
  for(int i = 1; i <= m; i++) {
    int op, l, r, x, lx, y, ly;
    op = read(), l = suf[read()], r = read();
    Q += op == 2;
    x = locate(n - r + 1, n - l + 1), lx = r - l + 1;
    if(op == 1) {
      y = read();
      if(l > r) continue;
      tr.add(dfn[x] + 1, dfn[x] + sz[x] - 1, y);
      sumv.add(dfn[x], 1u * y * (len[x] - lx + 1)); // delete one dfn[x]
      val.add(dfn[x] + 1, dfn[x] + sz[x] - 1, y), c[dfn[x]] += y;
      e.add(x, 1, lx, len[x], y);
    }
    else {
      l = suf[read()], r = read();
      if(l > r || !x) continue;
      y = locate(n - r + 1, n - l + 1), ly = r - l + 1;
      if(dep[x] < dep[y]) swap(x, y), swap(lx, ly);
      int u = x, v = y;
      if(u == v) {
        if(lx > ly) swap(x, y), swap(lx, ly);
        ans[Q] += val.query(dfn[x]) * (ly - lx + 1); // add this line
        e.add(x, 0, min(lx, ly), max(lx, ly), Q);
        continue;
      }
      ans[Q] += val.query(dfn[x]) * (lx - len[fa[x]]);
      e.add(x, 0, len[fa[x]] + 1, lx, Q), u = fa[u];
      if(!isanc(y, x)) v = fa[v];
      while(1) {
        int tpu = top[u], tpv = top[v];
        if(tpu == tpv) break;
        if(dep[tpu] < dep[tpv]) swap(u, v), swap(tpu, tpv);
        ans[Q] += tr.query(dfn[tpu], dfn[u]);
        ans[Q] += sumv.query(dfn[tpu], dfn[u]);
        u = fa[tpu];
      }
      if(dfn[u] > dfn[v]) swap(u, v);
      ans[Q] += tr.query(dfn[u] + 1, dfn[v]);
      ans[Q] += sumv.query(dfn[u] + 1, dfn[v]); // add this line
      if(isanc(y, x)) {
        e.add(y, 0, ly, len[y], Q);
        ans[Q] += val.query(dfn[y]) * (len[y] - ly + 1);
      }
      else {
        e.add(y, 0, len[fa[y]] + 1, ly, Q);
        ans[Q] += val.query(dfn[u]); // v -> u
        ans[Q] += c[dfn[u]]; // v -> u
        ans[Q] += val.query(dfn[y]) * (ly - len[fa[y]]); // swap ly - len[fa[y]] and len[y] - ly + 1
      }
    }
  }
  tr.init(2);
  memset(pre, 0, N << 2);
  for(int i = 1; i <= cnt; i++) {
    int lst = 0;
    for(int j = e.hd[i]; j; j = e.nxt[j]) pre[j] = lst, lst = j;
    for(int j = lst; j; j = pre[j]) {
      int t = e.type[j], l = e.l[j], r = e.r[j], v = e.v[j];
      if(t == 1) tr.add(l, r, v);
      else ans[v] += tr.query(l, r);
    }
    for(int j = lst; j; j = pre[j]) {
      int t = e.type[j], l = e.l[j], r = e.r[j], v = e.v[j];
      if(t == 1) tr.add(l, r, -v);
    }
  }
  for(int i = 1; i <= Q; i++) printf("%u\n", ans[i]);
  return cerr << 1e3 * clock() / CLOCKS_PER_SEC << " ms\n", 0;
}
/*
2022/7/24
start coding at 11:48
finish debugging at ??:??
*/
```

---

## 作者：Y_B_X (赞：0)

[原题链接](https://www.luogu.com.cn/problem/P7982)

修改的串 $s$ （去掉前导 $0$）只会对以 $s$ 为前缀的子串产生贡献。

把原串反过来建 $\text{SAM}$，那修改就会对 $\text{parent tree}$ 子树内所有等价类，以及当前等价类中长度 $\geq |s|$ 的串产生贡献。

这大体是个子树加，链求和的东西，然后把链求和差分，就是四个点到根的查询。


对长为 $len$，等价类为 $x$ 的查询串，之前长为 $len'$，等价类为 $y$ 的修改串，对其的贡献为 $[x\in \operatorname{subtree}_y](len'-len+1)\times v$。

拍到 $dfs$ 序上，一次修改将子树内节点 $w_x+=(len'+1)\times v,c_x+=v$。那查询答案就是 $w_x-c_x\times len$，两个树状数组容易实现。

而同一个等价类的会算多，对每个等价类离线下来，按长度限制用树状数组减掉多余贡献即可。

时间复杂度 $O(n\log n)$，空间 $\text{64MB}$ 有点麻（n）烦（t）。

为了让空间线性，瓶颈在于定位等价类的倍增与求 $\operatorname{lca}$。

把倍增换成离线二分，具体的，要定位的串离线到右端点所属节点，$dfs$ 时时维护出当前节点到根的链，然后在链上二分 $\geq len$ 的 $mxlen$ 最小的点。

求 $\operatorname{lca}$ 换成 $\text{Tarjan}$ 求，于是空间能线性了。

但还是容易爆，毕竟数组过多。重复利用数组（如转移边与两次树状数组），离线过程用加边代替，并精细实现，再开 $\text{C++98}$ 应该能过了。

~~空间开这么小搞啥啊，还不如给单 log 放大点数据范围来的实在。~~

```cpp
#include<bits/stdc++.h>
using namespace std;
const int N=4e5+10;
int x,y,xx,l,r;
int last=1,tot=1,tmp;
int mxlen[N<<1],link[N<<1];
unsigned t[N<<1][2];
void extend(bool a){
	y=last,tmp=++tot;
	mxlen[tmp]=mxlen[y]+1;
	for(;!t[y][a];y=link[y])t[y][a]=tmp;
	if(!y)link[tmp]=1;
	else {
		x=t[y][a];
		if(mxlen[x]==mxlen[y]+1)link[tmp]=x;
		else {
			xx=++tot;mxlen[xx]=mxlen[y]+1;
			memcpy(t[xx],t[x],8);
			for(;t[y][a]==x;y=link[y])t[y][a]=xx;
			link[xx]=link[x];link[tmp]=link[x]=xx;
		}
	}
	last=tmp;
}
#define lowbit(i) i&(-i)
unsigned res_t,ress_t;int n_t;
inline void update_t(int i,unsigned v,unsigned vv){
	for(;i<=n_t;i+=lowbit(i))t[i][0]+=v,t[i][1]+=vv;
}
inline void inquiry_t(int i){
	for(res_t=ress_t=0;i;i-=lowbit(i))
		res_t+=t[i][0],ress_t+=t[i][1]; 
}
unsigned ans[N],res;
inline void rupdate_t(int i,unsigned v){
	unsigned vv=v*i;
	for(;i;i-=lowbit(i))t[i][0]+=v,t[i][1]+=vv;
}
inline void rinquiry_t(int x){
	res_t=ress_t=0;
	for(int i=x+1;i<=n_t;i+=lowbit(i))
		res_t+=t[i][0],ress_t+=t[i][1];
	res=res_t*(x+1)-ress_t;
}
inline void rclear_t(int i){
	for(;i;i-=lowbit(i))t[i][0]=t[i][1]=0;
}
bool a[N];
int son[N<<1][2],dep[N<<1];
int dfn[N<<1],dfnr[N<<1],ttime;
inline void add(int x,int y){
	son[x][0]?son[x][1]=y:son[x][0]=y;
}
void init(int x){
	dfn[x]=++ttime;
	dep[x]=dep[link[x]]+1;
	if(son[x][0])init(son[x][0]);
	if(son[x][1])init(son[x][1]);
	dfnr[x]=ttime+1;
}
struct inq{int lx,ly,x,y,z;}qq[N];
int h[N<<1],nextn[N<<2],to[N<<2],edg;
char qb[N<<2];
inline void addq(int x,int i,char bb){
	to[++edg]=i,nextn[edg]=h[x],h[x]=edg,qb[edg]=bb;
}
inline void update(int x,int lx,unsigned v){
	update_t(dfn[x],v,v*lx);
	update_t(dfnr[x],-v,-v*lx);
}
inline void inquiry(int x,int lx){
	inquiry_t(dfn[x]);
	res+=res_t*(lx+1)-ress_t;
}
int s[N<<2],sz;
int L,R,Mid,Res;
void find(int len){
	L=1,R=sz,Res=0;
	while(L<=R){
		Mid=(L+R)>>1;
		mxlen[s[Mid]]>=len?
		Res=Mid,R=Mid-1:L=Mid+1;
	}
	Res=s[Res];
}
int f[N<<1];
inline int getf(int x){
	while(x!=f[x])x=f[x]=f[f[x]];
	return x;
}
void dfs(int x){
	s[++sz]=x;f[x]=x;
	for(int i=h[x];i;i=nextn[i]){
		inq &q=qq[to[i]];qb[i]?
		(find(q.lx),q.x=Res):
		(find(q.ly),q.y=Res);
		if(q.x&&q.y){
			static int xx,yy;
			xx=getf(q.x);
			yy=getf(q.y);
			q.z=dep[xx]<dep[yy]?xx:yy;
		}
	}
	if(son[x][0])dfs(son[x][0]);
	if(son[x][1])dfs(son[x][1]);
	--sz;f[x]=link[x];
}
char ch;
inline void read(int &x){
	x=0;ch=getchar();while(ch<48)ch=getchar();
	while(ch>47)x=(x<<1)+(x<<3)+(ch^48),ch=getchar();
}
inline void read(bool &x){
	ch=getchar();while(ch<48)ch=getchar();
	x=ch^50;
}
void write(unsigned x){if(x>9)write(x/10);putchar(48|x%10);}
int main(){
	int n,m,i,x,y,z,lz;
	read(n),read(m);f[n+1]=n+1;
	while(ch<48)ch=getchar();
	for(i=1;i<=n;++i)a[i]=ch^48,ch=getchar();
	for(i=n;i>=1;--i){
		extend(a[i]),s[i]=tmp;
		a[i]?f[i]=i:f[i]=f[i+1]; 
	}
	n_t=tot;
	memset(t,0,sizeof(t));
	for(i=2;i<=tot;++i)add(link[i],i);
	init(1);
	for(i=1;i<=m;++i){
		read(a[i]);
		read(l),read(r);l=f[l];
		if(l>r){
			read(l);
			if(!a[i])read(l);
			continue;
		}
		qq[i].lx=r-l+1;
		addq(s[l],i,1);
		if(a[i]){read(qq[i].z);continue;}
		read(l),read(r);l=f[l];
		if(l>r)continue;
		qq[i].ly=r-l+1;
		addq(s[l],i,0);
	}
	dfs(1);
	for(i=1;i<=tot;++i)h[i]=0;edg=0;
	for(i=1;i<=m;++i){
		if(a[i]&&qq[i].x){
			update(qq[i].x,qq[i].lx,qq[i].z);
			addq(qq[i].x,i,1);
		}
		if(!a[i]&&qq[i].x&&qq[i].y){
			x=qq[i].x,y=qq[i].y,z=qq[i].z;
			inquiry(x,qq[i].lx);
			inquiry(y,qq[i].ly);
			addq(x,i,1);addq(y,i,2);
			ans[i]=res;res=0;
			if(z!=x&&z!=y)inquiry(z,lz=mxlen[z]);
			else if(z!=y)inquiry(z,lz=qq[i].lx);
			else if(z!=x)inquiry(z,lz=qq[i].ly);
			else inquiry(z,lz=min(qq[i].lx,qq[i].ly));
			qq[i].x=lz;addq(z,i,3);
			lz-1>mxlen[link[z]]?
			(inquiry(z,lz-1),addq(z,i,4)):
			(inquiry(link[z],lz-1),addq(link[z],i,4));
			qq[i].y=lz-1;ans[i]-=res;res=0;
		}
	}
	memset(t,0,sizeof(t));
	for(x=1;x<=tot;++x)if(h[x]){
		sz=0;n_t=mxlen[x];
		for(i=h[x];i;i=nextn[i])
			s[++sz]=to[i],link[sz]=i;
		for(i=sz;i;--i){
			inq &q=qq[s[i]];
			if(a[s[i]])rupdate_t(q.lx,q.z);
			else {
				switch(qb[link[i]]){
					case 1:{rinquiry_t(q.lx);break;}
					case 2:{rinquiry_t(q.ly);break;}
					case 3:{rinquiry_t(q.x);break;}
					case 4:{rinquiry_t(q.y);break;}
				}
				ans[s[i]]+=qb[link[i]]<3?-res:res;
			} 
		}
		for(i=sz;i;--i)if(a[s[i]])rclear_t(qq[s[i]].lx);
	}
	for(i=1;i<=m;++i)if(!a[i])write(ans[i]),putchar('\n');
}
```

---

