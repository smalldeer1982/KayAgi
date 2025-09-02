# [JOISC 2021] IOI 熱の感染拡大 (Day1)

## 题目背景

本题数据保留一部分，请在 [此处](https://www.ioi-jp.org/camp/2021/2021-sp-tasks/day1/fever-data.zip) 获取完整数据。

## 题目描述

JOI 王国有 $N$ 个宫殿，第 $i$ 个宫殿坐标为 $(X_i,Y_i)$，每个宫殿居住着一个王子，第 $i$ 个宫殿里的王子为 $i$ 号王子。从第 $0$ 时刻开始，每个王子将会从自己的宫殿出发开始走动，他们可以选择东南西北：

- 如果选择东，则 $t$ 时刻过后坐标位置从 $(x,y)$ 变为 $(x+t,y)$。
- 如果选择西，则 $t$ 时刻过后坐标位置从 $(x,y)$ 变为 $(x-t,y)$。
- 如果选择南，则 $t$ 时刻过后坐标位置从 $(x,y)$ 变为 $(x,y-t)$。
- 如果选择北，则 $t$ 时刻过后坐标位置从 $(x,y)$ 变为 $(x,y+t)$。

$t$ 不一定是整数。 

方向不会给定，你可以自己规划。

不幸的是，$1$ 号王子染上了 IOVID-114514 病毒，在 $0$ 时刻只有 $1$ 号王子感染了该病毒。

IOVID-114514 病毒按照如下方式进行传播：

- 如果某一个时刻 $a$ 号王子和 $b$ 号王子在同一个坐标上，且 $a$ 号王子感染了病毒，$b$ 号王子没有感染病毒，则 $a$ 号王子会将病毒传染给 $b$ 号王子。

IOVID-114514 病毒没有其他传染方式，可怜的国王 JOI 114514 世也没有发现治愈方法。

（消毒水也不能治愈！）

JOI 114514 世想问问你求第 $10^{100}$ 个时刻的时候最多会有多少个王子感染 IOVID-114514 病毒。

## 说明/提示

#### 样例 1 解释

![](https://cdn.luogu.com.cn/upload/image_hosting/vi1nasol.png)

我们规划 $1$ 号王子向东，$2$ 号王子向西。

不难发现，不论怎么移动 $1$ 都无法与 $2$ 相遇，只有 $1$ 号王子一个感染者。

#### 样例 2 解释

![](https://cdn.luogu.com.cn/upload/image_hosting/na76sh3g.png)

我们规划 $1$ 号王子向东，$2$ 号王子向北，$3$ 号王子向西。

- 时刻 $0$，$1$ 号王子是感染者。
- 时刻 $1$，$1$ 号王子与 $2$ 号王子坐标重合，$2$ 号王子感染。
- 时刻 $2$，$2$ 号王子与 $3$ 号王子坐标重合，$3$ 号王子感染。

#### 样例 3 解释

我们规划 $1$ 号王子向北，$2$ 号王子向南。

- 时刻 $0$，$1$ 号王子是感染者。
- 时刻 $0.5$，$1$ 号王子和 $2$ 号王子坐标重合，$2$ 号王子感染。

#### 数据规模与约定

**本题采用捆绑测试。**

- Subtask 1（5 pts）：$N \le 7$，满足性质 A。
- Subtask 2（8 pts）：$N \le 15$，满足性质 A。
- Subtask 3（6 pts）：$N \le 100$，满足性质 A 和 B。
- Subtask 4（6 pts）：$N \le 100$，满足性质 A。
- Subtask 5（12 pts）：$N \le 3000$。
- Subtask 6（32 pts）：满足性质 A。
- Subtask 7（31 pts）：无特殊限制。

对于 $100\%$ 的数据，$1 \le N \le 10^5$，$0 \le X_i,Y_i \le 5 \times 10^8$，宫殿坐标互不重合。

其中性质分别为：

- 性质 A：$X_i \ne X_j$，$Y_i \ne Y_j$。
- 性质 B：$1$ 号宫殿坐标为原点。

#### 说明

翻译自 [第２０回日本情報オリンピック　春季トレーニング合宿](https://www.ioi-jp.org/camp/2021/2021-sp-tasks/index.html) [Day1 B IOI 熱の感染拡大 (IOI Fever) 的英文版本](https://www.ioi-jp.org/camp/2021/2021-sp-tasks/day1/fever-en.pdf)。

## 样例 #1

### 输入

```
2
0 0
4 3```

### 输出

```
1```

## 样例 #2

### 输入

```
3
1 2
2 1
4 3```

### 输出

```
3```

## 样例 #3

### 输入

```
2
20 20
20 21```

### 输出

```
2```

## 样例 #4

### 输入

```
15
5 6
2 9
12 0
4 11
3 12
6 5
0 8
9 10
11 13
8 7
13 2
1 1
7 14
10 4
14 3```

### 输出

```
9```

## 样例 #5

### 输入

```
30
275810186 246609547
122805872 99671769
243507947 220373844
281305347 252104708
237805644 214671541
172469077 149334974
222589229 229887956
160653451 208404690
241378966 211098219
144302355 224755786
186392385 163258282
199129390 169928751
294937491 265736852
196096122 172962019
314342944 285142305
202720470 166337671
157037485 133903382
263858979 240724876
210720220 181519581
296402036 267201397
186021287 183036854
195081930 173976211
328293029 299092390
261195361 238061258
323595085 294394446
299933764 270733125
240976723 128081418
188501753 165367650
277832422 248631783
119896220 96762117```

### 输出

```
11```

# 题解

## 作者：RiverHamster (赞：2)

[在我的 cnblogs 上阅读](https://www.cnblogs.com/RiverHamster/p/sol-JOISC2021d1t2.html)

首先考虑固定每个点的方向。

平移坐标系，使 $1$ 号点为原点，则 $t$ 时刻 $1$ 号点可能**直接或间接**影响的范围是 $\{(x, y)\mid |
x| + |y| \le t\}$。

**注意到不存在重复点**，那么可以枚举 $1$ 号点的方向，并旋转坐标系使 $1$ 号点向 $x$ 轴正方向。

那么如果初始方向和影响范围扩大的两个方向之一相同，那么不可能被感染。

进一步地，对于 $|x| \ne |y|$ 的点，应该朝向垂直于 $|x|$, $|y|$ 中较大的一个坐标轴的方向，否则仍然不能进入影响范围。

对于 $|x| = |y|$ 的点，如果在第一象限或第四象限，那么应该朝垂直 $x$ 轴方向走，否则应该朝垂直 $y$ 轴方向走（注意到没有重复点，若向 $x$ 轴方向则恰好不能被感染；如下图所示，$A, C$ 可以在 $M$ 相遇）。

![](https://cdn.luogu.com.cn/upload/image_hosting/ag2fpnbi.png)

两个人能相遇，当且仅当满足一下两种条件之一：

- 两人 $x$ 或 $y$ 坐标相同，且初始相向而行；
- 两人在同一条斜线上，即 $x + y = x' +y'$ 或 $x - y = x' - y'$，且方向恰好相对。

构造无向图，若 $u, v$ 两人在 $t$ 时刻相遇，则在 $(u, v)$ 之间连一条权值为 $t$ 的边。

考虑贪心。每次选取被感染时间最小的点 $u$，设其时间为 $t$，则对于 $u$ 的所有出边 $\{(u, v, t') \mid t' \ge t\}$，更新 $v$ 的最小感染时间 $t'$。

直接实现边数 $\mathcal O(N^2)$。存在几种优化方法，下面只介绍最容易理解的一种：

对于每条横线、竖线、斜线上的 $4$ 种方向的点，分别建立线段树。每个点会加入恰好 $3$ 棵线段树（两条斜线和初始方向所在的横线或竖线）。

每次转移相当于对一棵线段树上的一个前缀或后缀的点的值对一条**斜率固定**的线段取 $\min$，支持查询全局最小值和删除某个点。

维护每个区间的最左（右）点和最小的能完全覆盖区间的线段，用堆等数据结构维护每个线段树的最小值即可。

如果按值域建立线段树，则空间 $\mathcal O(N \log V)$，如直接按下标建立，则空间 $\mathcal O(N)$。两种方法都可以通过，但空间上常数很大。时间为 $\mathcal O(N(\log N + \log V))$ 或 $\mathcal O(N \log N)$。

实现十分复杂。

```cpp
#include <cstdio>
#include <cctype>
#include <cstring>
#include <algorithm>
#include <numeric>
#include <vector>
#include <cassert>
using namespace std;

#define LOG(f...) fprintf(stderr, f)
#define all(cont) begin(cont), end(cont)

using ll = long long;

const int N = 100005;
const ll IINF = 2e9;
const ll INF = 1e17;

struct pt { int x, y; };

struct discretizer {
  vector<int> v;
  void clear() { v.clear(); }
  void add(int x) { v.push_back(x); }
  void init() { sort(all(v)); v.erase(unique(all(v)), end(v)); }
  int operator()(int x) const { return lower_bound(all(v), x) - begin(v); }
};

struct min_seg_tree {
  static const int LEN = 1 << 21;
  pair<int, pair<int, int>> t[LEN * 2];
  void init() { memset((void *)t, 0x3f, sizeof(t)); }
  min_seg_tree() { init(); }
  void update(int p, ll v, int id) {
    if (v > 0x3f3f3f3f) return;
    p += LEN;
    if (t[p].first <= v) return;
    t[p].first = v; t[p].second = {p - LEN, id};
    for (p >>= 1; p; p >>= 1)
      t[p] = t[p << 1].first < t[p << 1 | 1].first ? t[p << 1] : t[p << 1 | 1];
  }
  void assign(int p, ll v, int id) {
    if (v > 0x3f3f3f3f) return;
    p += LEN;
    if (t[p].first == v && t[p].second.second == id) return;
    t[p].first = v; t[p].second = {p - LEN, id};
    for (p >>= 1; p; p >>= 1)
      t[p] = t[p << 1].first < t[p << 1 | 1].first ? t[p << 1] : t[p << 1 | 1];
  }
  void erase(int p) {
    p |= LEN; t[p].first = 0x3f3f3f3f;
    for (p >>= 1; p; p >>= 1)
      t[p] = t[p << 1].first < t[p << 1 | 1].first ? t[p << 1] : t[p << 1 | 1];
  }
  pair<int, pair<int, int>> top() const { return t[1]; }
};

struct seg_node {
  ll b;
  pair<ll, int> mn;
  int pos, pos_id;
  int lc, rc;
} t[N * 32 * 3];
int nc = 0;

int n;
pt p[N];
discretizer dx, dy, d0, d1;
min_seg_tree H;
int idx[N], idy[N], id0[N], id1[N];
int rtx[N][4], rty[N][4], rt0[N][4], rt1[N][4];

template<int k>
struct seg_op {
  static const ll pos_init = k < 0 ? -IINF : IINF;
  static ll pos_v(int x) { return x ? t[x].pos : pos_init; }
  static int new_node() {
    ++nc;
    t[nc].mn = {INF, 0}; t[nc].b = INF; t[nc].pos = pos_init; t[nc].lc = t[nc].rc = 0;
    return nc;
  }
  static void up(int x) {
    auto &u = t[x], &lc = t[t[x].lc], &rc = t[t[x].rc];
    t[x].mn = min(lc.mn, rc.mn);
    if (k > 0) {
      if (pos_v(t[x].lc) < pos_v(t[x].rc)) u.pos = pos_v(t[x].lc), u.pos_id = lc.pos_id;
      else u.pos = pos_v(t[x].rc), u.pos_id = rc.pos_id;
    }
    else {
      if (pos_v(t[x].lc) > pos_v(t[x].rc)) u.pos = pos_v(t[x].lc), u.pos_id = lc.pos_id;
      else u.pos = pos_v(t[x].rc), u.pos_id = rc.pos_id;
    }
    t[x].mn = min(t[x].mn, make_pair((ll)k * t[x].pos + t[x].b, t[x].pos_id));
  }
  static void insert(int &x, int l, int r, int p, ll mn, int id) {
    if (!x) x = new_node();
    if ((k > 0 && p < t[x].pos) || (k < 0 && p > t[x].pos))
      t[x].pos = p, t[x].pos_id = id;
    t[x].mn = min(t[x].mn, make_pair(mn, id));
    if (l == r) return;
    int mid = (l + r) >> 1;
    p <= mid ? insert(t[x].lc, l, mid, p, mn, id) : insert(t[x].rc, mid + 1, r, p, mn, id);
  }
  static void erase(int &x, int l, int r, int p) {
    if (l == r) { x = 0; return; }
    int mid = (l + r) >> 1;
    p <= mid ? erase(t[x].lc, l, mid, p) : erase(t[x].rc, mid + 1, r, p);
    if (!t[x].lc && !t[x].rc) x = 0;
    else up(x);
  }
  static void update(int &x, int l, int r, int ql, int qr, ll b) {
    if (!x || ql > qr) return;
    if (ql <= l && r <= qr) {
      t[x].b = min(t[x].b, b);
      if (t[x].pos != pos_init) t[x].mn = min(t[x].mn, make_pair(t[x].b + t[x].pos * k, t[x].pos_id));
      return;
    }
    int mid = (l + r) >> 1;
    if (ql <= mid) update(t[x].lc, l, mid, ql, qr, b);
    if (qr > mid) update(t[x].rc, mid + 1, r, ql, qr, b);
    up(x);
  }
};

int min_x, max_x, min_y, max_y;

int dir[N];

// rt0 : -2 -2 2 2
// rt1 : -2 2 2 -2

void insert_pt(int i) {
  int D = dir[i];
  ll V = i == 0 ? 0 : INF;
  D & 2 ? seg_op<2>::insert(rt0[id0[i]][D], min_x, max_x, p[i].x, V, i)
        : seg_op<-2>::insert(rt0[id0[i]][D], min_x, max_x, p[i].x, V, i);
  D == 1 || D == 2 ? seg_op<2>::insert(rt1[id1[i]][D], min_x, max_x, p[i].x, V, i)
                   : seg_op<-2>::insert(rt1[id1[i]][D], min_x, max_x, p[i].x, V, i);
  if (D == 0) seg_op<-1>::insert(rty[idy[i]][D], min_x, max_x, p[i].x, V, i);
  else if (D == 2) seg_op<1>::insert(rty[idy[i]][D], min_x, max_x, p[i].x, V, i);
  else if (D == 1) seg_op<-1>::insert(rtx[idx[i]][D], min_y, max_y, p[i].y, V, i);
  else if (D == 3) seg_op<1>::insert(rtx[idx[i]][D], min_y, max_y, p[i].y, V, i);
}

void heap_up(int id, int tid) {
  H.update(id, t[tid].mn.first, t[tid].mn.second);
}

void heap_assign(int id, int tid) {
  H.assign(id, t[tid].mn.first, t[tid].mn.second);
}

void erase_pt(int i) {
  int D = dir[i];
  D & 2 ? seg_op<2>::erase(rt0[id0[i]][D], min_x, max_x, p[i].x)
        : seg_op<-2>::erase(rt0[id0[i]][D], min_x, max_x, p[i].x);
  heap_assign(id0[i] << 4 | 8 | D, rt0[id0[i]][D]);
  D == 1 || D == 2 ? seg_op<2>::erase(rt1[id1[i]][D], min_x, max_x, p[i].x)
                   : seg_op<-2>::erase(rt1[id1[i]][D], min_x, max_x, p[i].x);
  heap_assign(id1[i] << 4 | 12 | D, rt1[id1[i]][D]);
  if (D == 0) seg_op<-1>::erase(rty[idy[i]][D], min_x, max_x, p[i].x);
  else if (D == 2) seg_op<1>::erase(rty[idy[i]][D], min_x, max_x, p[i].x);
  else if (D == 1) seg_op<-1>::erase(rtx[idx[i]][D], min_y, max_y, p[i].y);
  else if (D == 3) seg_op<1>::erase(rtx[idx[i]][D], min_y, max_y, p[i].y);
  if (D == 0 || D == 2)
    heap_assign(idy[i] << 4 | 4 | D, rty[idy[i]][D]);
  else
    heap_assign(idx[i] << 4 | 0 | D, rtx[idx[i]][D]);
}

void update_pt(int i, int dis) {
  int slen = (dis + 1) / 2, slen_v = slen * 2;
  switch (dir[i]) {
    case 0:
      seg_op<2>::update(rt0[id0[i]][3], min_x, max_x, p[i].x + slen, max_x, slen_v - 2LL * (p[i].x + slen));
      heap_up(id0[i] << 4 | 8 | 3, rt0[id0[i]][3]);
      seg_op<2>::update(rt1[id1[i]][1], min_x, max_x, p[i].x + slen, max_x, slen_v - 2LL * (p[i].x + slen));
      heap_up(id1[i] << 4 | 12 | 1, rt1[id1[i]][1]);
      seg_op<1>::update(rty[idy[i]][2], min_x, max_x, p[i].x + dis, max_x, dis - (p[i].x + dis));
      heap_up(idy[i] << 4 | 4 | 2, rty[idy[i]][2]);
      break;
    case 1:
      seg_op<2>::update(rt0[id0[i]][2], min_x, max_x, p[i].x + slen, max_x, slen_v - 2LL * (p[i].x + slen));
      heap_up(id0[i] << 4 | 8 | 2, rt0[id0[i]][2]);
      seg_op<-2>::update(rt1[id1[i]][0], min_x, max_x, min_x, p[i].x - slen, slen_v + 2LL * (p[i].x - slen));
      heap_up(id1[i] << 4 | 12 | 0, rt1[id1[i]][0]);
      seg_op<1>::update(rtx[idx[i]][3], min_y, max_y, p[i].y + dis, max_y, dis - (p[i].y + dis));
      heap_up(idx[i] << 4 | 0 | 3, rtx[idx[i]][3]);
      break;
    case 2:
      seg_op<-2>::update(rt0[id0[i]][1], min_x, max_x, min_x, p[i].x - slen, slen_v + 2LL * (p[i].x - slen));
      heap_up(id0[i] << 4 | 8 | 1, rt0[id0[i]][1]);
      seg_op<-2>::update(rt1[id1[i]][3], min_x, max_x, min_x, p[i].x - slen, slen_v + 2LL * (p[i].x - slen));
      heap_up(id1[i] << 4 | 12 | 3, rt1[id1[i]][3]);
      seg_op<-1>::update(rty[idy[i]][0], min_x, max_x, min_x, p[i].x - dis, dis + (p[i].x - dis));
      heap_up(idy[i] << 4 | 4 | 0, rty[idy[i]][0]);
      break;
    case 3:
      seg_op<-2>::update(rt0[id0[i]][0], min_x, max_x, min_x, p[i].x - slen, slen_v + 2LL * (p[i].x - slen));
      heap_up(id0[i] << 4 | 8 | 0, rt0[id0[i]][0]);
      seg_op<2>::update(rt1[id1[i]][2], min_x, max_x, p[i].x + slen, max_x, slen_v - 2LL * (p[i].x + slen));
      heap_up(id1[i] << 4 | 12 | 2, rt1[id1[i]][2]);
      seg_op<-1>::update(rtx[idx[i]][1], min_y, max_y, min_y, p[i].y - dis, dis + (p[i].y - dis));
      heap_up(idx[i] << 4 | 0 | 1, rtx[idx[i]][1]);
      break;
  }
}

bool vis[N];

int solve() {
  dir[0] = 0;
  for (int i = 1; i < n; ++i) {
    if (abs(p[i].x) == abs(p[i].y))
      dir[i] = p[i].x < 0 ? 0 : (p[i].y > 0 ? 3 : 1);
    else if (abs(p[i].x) > abs(p[i].y))
      dir[i] = p[i].x > 0 ? 2 : 0;
    else
      dir[i] = p[i].y > 0 ? 3 : 1;
  }
  dx.clear(); dy.clear(); d0.clear(); d1.clear();
  for (int i = 0; i < n; ++i)
    dx.add(p[i].x), dy.add(p[i].y), d0.add(p[i].x - p[i].y), d1.add(p[i].x + p[i].y);
  dx.init(); dy.init(); d0.init(); d1.init();
  for (int i = 0; i < n; ++i)
    tie(idx[i], idy[i], id0[i], id1[i]) = make_tuple(dx(p[i].x), dy(p[i].y), d0(p[i].x - p[i].y), d1(p[i].x + p[i].y));
  min_x = IINF; max_x = -IINF;
  for (int i = 0; i < n; ++i) {
    min_x = min(min_x, p[i].x), max_x = max(max_x, p[i].x);
    min_y = min(min_y, p[i].y), max_y = max(max_y, p[i].y);
  }
  nc = 0;
  memset(rtx, 0, sizeof(rtx)); memset(rty, 0, sizeof(rty)); memset(rt0, 0, sizeof(rt0)); memset(rt1, 0, sizeof(rt1));
  for (int i = 0; i < n; ++i)
    insert_pt(i);
  H.update(idy[0] << 4 | 4 | 0, 0, 0);
  H.update(id0[0] << 4 | 8 | dir[0], 0, 0);
  H.update(id1[0] << 4 | 12 | dir[0], 0, 0);
  fill(vis, vis + n, false);
  int res = 0;
  while (H.top().first != 0x3f3f3f3f) {
    int val = H.top().first;
    int id = H.top().second.first;
    int x = H.top().second.second;
    H.erase(id);
    if (vis[x]) continue;
    erase_pt(x);
    vis[x] = true;
    ++res;
    update_pt(x, val);
  }
  return res;
}

int main() {
#ifndef ONLINE_JUDGE
  freopen("input.txt", "r", stdin);
  freopen("output.txt", "w", stdout);
#endif
  scanf("%d", &n);
  for (int i = 0; i < n; ++i)
    scanf("%d%d", &p[i].x, &p[i].y);
  for (int i = 1; i < n; ++i)
    p[i].x -= p[0].x, p[i].y -= p[0].y;
  p[0].x = 0; p[0].y = 0;
  t[0].mn = {INF, 0};
  int res = 0;
  for (int i = 0; i < 4; ++i) {
    res = max(res, solve());
    transform(p, p + n, p, [](const pt &p) ->pt { return {-p.y, p.x}; });
  }
  printf("%d\n", res);
  return 0;
}
```



---

## 作者：intel_core (赞：0)

懒得喷出题人。

先钦定 $1$ 号的初始方向。对于 $i$ 号四个方向的决策，我们对于每个方向分别求出如果这么走最早什么时候会被传染，然后把所有可能被感染的决策 $(i,dir)$ 按照感染事件排序，依次取出然后更新其它决策。最后判断 $i$ 有没有被更新过即可。

直观的可以感受到这种做法的正确性，现在来严格证明一下：

这个做法可能的问题是一个人可能分身去更新其它人，因此我们只需要说明一个人最多只会有一种可能被传染的决策即可。

我们变换坐标系使得 $1$ 号与原点重合且 $1$ 号行动方向与 $x$ 轴正方向一致。

因为携带病毒的人的速度是 $1$，因此 $(x,y)$ 被携带病毒的人经过的最早时刻一定不早于 $|x|+|y|$。

注意到一个在 $(x,y)$ 的人至多只有两种可能的决策使得会被传染；而又因 $|x|\not= |y|$ 时，两种可能的决策一定有一种决策对应的向量在与坐标轴相交时不再病毒的传染范围内，而向量跨过坐标轴的部分显然不可能再被传染。

![](https://cdn.luogu.com.cn/upload/image_hosting/2wc6lol4.png)

因此有两种可能被传染的决策只有可能是 $|x|=|y|$ 的情况。

又因为没有重复的点，且 $|x|=|y|$ 的点只能被 $1$ 号传染，所以也至多只有一种可能被传染的决策。

直接对所有 $(i,dir)$ 向所有可以被传染的决策连边，跑 dijkstra 可以做到 $O(n^2\log n)$。

注意到连边的两个点 $(x_1,y_1)$ 和 $(x_2,y_2)$ 一定满足 $x_1+y_1=x_2+y_2$ 或者 $x_1-y_1=x_2-y_2$ 其中之一，也就是说一个决策点影响的范围是一条斜率为 $1/-1$ 的射线上的点。

我们过每个点分别做斜率为 $1/-1$ 的直线之后去重，把每条线上的点拿出来；不难发现影响范围是这条线上的点按照 $x$ 排序后的一个前缀/后缀。可以直接取出影响范围内的第一个点，记录是从哪条线转移过来的。在 dijkstra 取出一个点更新最短路时把下一个点也扔进堆里。

这样边数降至 $O(n)$，复杂度 $O(n\log n)$。

说起来不难，写起来就是另外一回事了。。

```cpp
#include<bits/stdc++.h>
using namespace std;
#define int long long
const int NR=1e5+10;
const int INF=1e18;
#define pb push_back
int n,ans,x[NR],y[NR];
int cnt1[NR],cnt2[NR],rnk1[NR],rnk2[NR],a[NR],b[NR];
int X[NR],Y[NR],rnk3[NR],rnk4[NR],cnt3[NR],cnt4[NR];
int dis[4][NR][3],vis[4][NR][3];
int v1[NR],len1,v2[NR],len2,vx[NR],len3,vy[NR],len4;
struct point{
	int y,x,from,dis;
	bool operator <(const point &T)const{
		return dis>T.dis;
	}
};
priority_queue<point>q;
const int dx[]={1,0,-1,0};
const int dy[]={0,-1,0,1};
struct task{
	int x,id;
	bool operator <(const task &T)const{
		return x<T.x;
	}
};
vector<task>buc1[NR],buc2[NR],buc3[NR],buc4[NR]; 

void FindNxt(int x,int y,int from,int v){
	int nxt,val;
	if(from==0){
		if(y==3||y==2){
			if(cnt1[a[x]]==rnk1[x])return;
			nxt=buc1[a[x]][rnk1[x]+1].id;
			val=v+buc1[a[x]][rnk1[x]+1].x-buc1[a[x]][rnk1[x]].x;
		}
		else{
			if(rnk1[x]==1)return;
			nxt=buc1[a[x]][rnk1[x]-1].id;
			val=v-buc1[a[x]][rnk1[x]-1].x+buc1[a[x]][rnk1[x]].x;
		}
	}
	if(from==1){
		if(y==1||y==2){
			if(cnt2[b[x]]==rnk2[x])return;
			nxt=buc2[b[x]][rnk2[x]+1].id;
			val=v+buc2[b[x]][rnk2[x]+1].x-buc2[b[x]][rnk2[x]].x;
		}
		else{
			if(rnk2[x]==1)return;
			nxt=buc2[b[x]][rnk2[x]-1].id;
			val=v-buc2[b[x]][rnk2[x]-1].x+buc2[b[x]][rnk2[x]].x;
		}
	}
	if(from>=2){
		if(y==0){
			if(rnk4[x]==1)return;
			nxt=buc4[Y[x]][rnk4[x]-1].id;
			val=((from-2)-vx[X[nxt]]+1)/2;
		}
		if(y==1){
			if(rnk3[x]==cnt3[X[x]])return;
			nxt=buc3[X[x]][rnk3[x]+1].id;
			val=(vy[Y[nxt]]-(from-2)+1)/2;
		}
		if(y==2){
			if(rnk4[x]==cnt4[Y[x]])return;
			nxt=buc4[Y[x]][rnk4[x]+1].id;
			val=(vx[X[nxt]]-(from-2)+1)/2;
		}
		if(y==3){
			if(rnk3[x]==1)return;
			nxt=buc3[X[x]][rnk3[x]-1].id;
			val=((from-2)-vy[Y[nxt]]+1)/2;
		}
	}
	int wxb=min(2ll,from);
	if(dis[y][nxt][wxb]<=val)return;
	dis[y][nxt][wxb]=val;q.push((point){y,nxt,from,val});
}

signed main(){
	cin>>n;
	for(int i=1;i<=n;i++){
		cin>>x[i]>>y[i];x[i]*=2;y[i]*=2;
		v1[++len1]=x[i]+y[i];v2[++len2]=x[i]-y[i];
		vx[++len3]=x[i];vy[++len4]=y[i];
	}
	x[n+1]=x[1];y[n+1]=y[1];
	v1[++len1]=x[1]+y[1];v2[++len2]=x[1]-y[1];
	vx[++len3]=x[1];vy[++len4]=y[1];
	sort(v1+1,v1+1+len1);sort(v2+1,v2+1+len2);
	len1=unique(v1+1,v1+1+len1)-v1-1;len2=unique(v2+1,v2+1+len2)-v2-1;
	sort(vx+1,vx+1+len3);sort(vy+1,vy+1+len4);
	len3=unique(vx+1,vx+1+len3)-vx-1;len4=unique(vy+1,vy+1+len4)-vy-1;
	for(int i=1;i<=len1;i++)buc1[i].pb((task){-INF,0});
	for(int i=1;i<=len2;i++)buc2[i].pb((task){-INF,0});
	for(int i=1;i<=len3;i++)buc3[i].pb((task){-INF,0});
	for(int i=1;i<=len4;i++)buc4[i].pb((task){-INF,0});
	for(int i=1;i<=n+1;i++){
		a[i]=lower_bound(v1+1,v1+1+len1,x[i]+y[i])-v1;
		b[i]=lower_bound(v2+1,v2+1+len2,x[i]-y[i])-v2;
		X[i]=lower_bound(vx+1,vx+1+len3,x[i])-vx;
		Y[i]=lower_bound(vy+1,vy+1+len4,y[i])-vy;
		if(i>1){
			buc1[a[i]].pb((task){x[i],i});buc2[b[i]].pb((task){x[i],i});
			buc3[X[i]].pb((task){y[i],i});buc4[Y[i]].pb((task){x[i],i});
			cnt1[a[i]]++;cnt2[b[i]]++;cnt3[X[i]]++;cnt4[Y[i]]++;
		}
	}
	for(int i=1;i<=len1;i++)sort(buc1[i].begin(),buc1[i].end());
	for(int i=1;i<=len2;i++)sort(buc2[i].begin(),buc2[i].end());
	for(int i=1;i<=len3;i++)sort(buc3[i].begin(),buc3[i].end());
	for(int i=1;i<=len4;i++)sort(buc4[i].begin(),buc4[i].end());
	for(int i=2;i<=n+1;i++){
		rnk1[i]=lower_bound(buc1[a[i]].begin(),buc1[a[i]].end(),(task){x[i],i})-buc1[a[i]].begin();
		rnk2[i]=lower_bound(buc2[b[i]].begin(),buc2[b[i]].end(),(task){x[i],i})-buc2[b[i]].begin();
		rnk3[i]=lower_bound(buc3[X[i]].begin(),buc3[X[i]].end(),(task){y[i],i})-buc3[X[i]].begin();
		rnk4[i]=lower_bound(buc4[Y[i]].begin(),buc4[Y[i]].end(),(task){x[i],i})-buc4[Y[i]].begin();
	}
	for(int T=0;T<4;T++){
		memset(dis,999999,sizeof(dis));
		memset(vis,0,sizeof(vis));
		dis[T][1][0]=dis[T][1][1]=1;
		q.push((point){T,1,0,1});q.push((point){T,1,1,1});
		while(!q.empty()){
			int id=q.top().x,dir=q.top().y,lcy=q.top().from,d=q.top().dis;
			q.pop();
			int wxb=min(lcy,2ll);
			if(vis[dir][id][wxb])continue;
			vis[dir][id][wxb]=1;
			if(id!=1)FindNxt(id,dir,lcy,d);
			if(dir==0){
				int tmp1=lower_bound(buc2[b[id]].begin(),buc2[b[id]].end(),(task){d+x[id],0})-buc2[b[id]].begin();
				if(tmp1<=cnt2[b[id]]){
					int to1=buc2[b[id]][tmp1].id;
					if(dis[1][to1][1]>x[to1]-x[id]){
						dis[1][to1][1]=x[to1]-x[id];
						q.push((point){1,to1,1,dis[1][to1][1]});
					}
				}			
				int tmp2=lower_bound(buc1[a[id]].begin(),buc1[a[id]].end(),(task){d+x[id],0})-buc1[a[id]].begin();
				if(tmp2<=cnt1[a[id]]){
					int to2=buc1[a[id]][tmp2].id;
					if(dis[3][to2][0]>x[to2]-x[id]){
						dis[3][to2][0]=x[to2]-x[id];
						q.push((point){3,to2,0,dis[3][to2][0]});
					}
				}
				int tmp=lower_bound(buc4[Y[id]].begin(),buc4[Y[id]].end(),(task){2*d+x[id],0})-buc4[Y[id]].begin();
				if(tmp<=cnt4[Y[id]]){
					int nxt=buc4[Y[id]][tmp].id,val=(x[nxt]-x[id]+1)/2;
					if(dis[2][nxt][2]>val){
						dis[2][nxt][2]=val;
						q.push((point){2,nxt,x[id]+2,val});
					}
				}		
			}
			if(dir==1){
				int tmp1=upper_bound(buc2[b[id]].begin(),buc2[b[id]].end(),(task){x[id]-d,0})-buc2[b[id]].begin()-1;
				if(tmp1){
					int to1=buc2[b[id]][tmp1].id;
					if(dis[0][to1][1]>x[id]-x[to1]){
						dis[0][to1][1]=x[id]-x[to1];
						q.push((point){0,to1,1,dis[0][to1][1]});
					}
				}
				int tmp2=lower_bound(buc1[a[id]].begin(),buc1[a[id]].end(),(task){d+x[id],0})-buc1[a[id]].begin();
				if(tmp2<=cnt1[a[id]]){
					int to2=buc1[a[id]][tmp2].id;
					if(cnt1[a[id]]>=tmp2&&to2&&dis[2][to2][0]>x[to2]-x[id]){
						dis[2][to2][0]=x[to2]-x[id];
						q.push((point){2,to2,0,dis[2][to2][0]});
					}
				}
				int tmp=upper_bound(buc3[X[id]].begin(),buc3[X[id]].end(),(task){y[id]-2*d,0})-buc3[X[id]].begin()-1;
				if(tmp){
					int nxt=buc3[X[id]][tmp].id,val=(y[id]-y[nxt]+1)/2;
					if(dis[3][nxt][2]>val){
						dis[3][nxt][2]=val;
						q.push((point){3,nxt,y[id]+2,val});
					}
				}	
			}
			if(dir==2){
				int tmp1=upper_bound(buc1[a[id]].begin(),buc1[a[id]].end(),(task){x[id]-d,0})-buc1[a[id]].begin()-1;
				if(tmp1){
					int to1=buc1[a[id]][tmp1].id;
					if(tmp1&&dis[1][to1][0]>x[id]-x[to1]){
						dis[1][to1][0]=x[id]-x[to1];
						q.push((point){1,to1,0,dis[1][to1][0]});
					}
				}
				int tmp2=upper_bound(buc2[b[id]].begin(),buc2[b[id]].end(),(task){x[id]-d,0})-buc2[b[id]].begin()-1;
				if(tmp2){
					int to2=buc2[b[id]][tmp2].id;
					if(tmp2&&dis[3][to2][1]>x[id]-x[to2]){
						dis[3][to2][1]=x[id]-x[to2];
						q.push((point){3,to2,1,dis[3][to2][1]});
					}
				}
				int tmp=upper_bound(buc4[Y[id]].begin(),buc4[Y[id]].end(),(task){x[id]-2*d,0})-buc4[Y[id]].begin()-1;
				if(tmp){
					int nxt=buc4[Y[id]][tmp].id,val=(x[id]-x[nxt]+1)/2;
					if(dis[0][nxt][2]>val){
						dis[0][nxt][2]=val;
						q.push((point){0,nxt,x[id]+2,val});
					}
				}
			}
			if(dir==3){
				int tmp1=upper_bound(buc1[a[id]].begin(),buc1[a[id]].end(),(task){x[id]-d,0})-buc1[a[id]].begin()-1;
				if(tmp1){
					int to1=buc1[a[id]][tmp1].id;
					if(tmp1&&dis[0][to1][0]>x[id]-x[to1]){
						dis[0][to1][0]=x[id]-x[to1];
						q.push((point){0,to1,0,dis[0][to1][0]});
					}
				}
				int tmp2=lower_bound(buc2[b[id]].begin(),buc2[b[id]].end(),(task){x[id]+d,0})-buc2[b[id]].begin();
				if(tmp2<=cnt2[b[id]]){
					int to2=buc2[b[id]][tmp2].id;
					if(tmp2<=cnt2[b[id]]&&tmp2&&dis[2][to2][1]>x[to2]-x[id]){
						dis[2][to2][1]=x[to2]-x[id];
						q.push((point){2,to2,1,dis[2][to2][1]});
					}
				}
				int tmp=lower_bound(buc3[X[id]].begin(),buc3[X[id]].end(),(task){2*d+y[id],0})-buc3[X[id]].begin();
				if(tmp<=cnt3[X[id]]){
					int nxt=buc3[X[id]][tmp].id,val=(y[nxt]-y[id]+1)/2;
					if(dis[1][nxt][2]>val){
						dis[1][nxt][2]=val;
						q.push((point){1,nxt,y[id]+2,val});
					}
				}
			}
		}
		int res=0;
		for(int i=1;i<=n;i++){
			int flag=0;
			for(int x=0;x<4;x++)
				for(int y=0;y<3;y++)flag|=vis[x][i][y];
			res+=flag|(i==1);
		}
		ans=max(ans,res);
	}
	cout<<ans<<endl;
	return 0;
}
```

---

## 作者：7KByte (赞：0)

大模拟，需要肝。

我们一步步分解。

首先最开始只有第一个个点被感染了，那么我们最先固定第一个人的方向，有 $4$ 种选择。

对于第一个点初始方向上的点，一定与 $1$ 号点相向运动，否则它们既不会被感染，也不会感染别人，没有任何作用。我们称这类点为 $\mathbf{A}$ 类节点

对于第一个点初始方向的相反反向上节点，必定向 $1$ 号点方向移动。

对于剩下点，每个点的方向有两种选择，第一种是垂直于 $1$ 号点的初始方向运动，第二种是平行于 $1$ 号点，并向 $1$ 号点运动。

但是每种点都有两种选择，状态数仍然太大了。

结论：$1$ 号点初始值位置 $(a,b)$ ，则当前点一定选择到直线 $x=a$ 和直线 $y=b$ 中较长的一个。

手动模拟一下发现向另一个走不可能被感染。

对于两个方向相同的点，只可能垂直于初始方向运动，且可以根据相对位置 $\mathcal{O}(1) $ 判断是否被感染。

对于原本就在直线 $x=a$ 或直线 $y=b$ 的直线，只可能向 $1$ 号点方向运动 。

这样我们就固定了所有点的运动方向。

垂直于初始方向运动的点，我们称为 $\mathbf{C}$ 类点。平行运动的我们称为 $\mathbf{D}$ 号点。

那么什么情况下会发生传染？

首先被 $1$ 号点传染的，一定是在初始方向上的，或在过 $1$ 点，且斜率为 $1$ 或 $-1$ 的直线上。 注意这是必要条件，并不充分。

那么两个点之间发生传染，过两点直线的斜率为 $1/-1$ ，或过两点直线平行坐标轴。

基于一个显而易见的事实，$i$ 被感染后才能传染别人，所以我们可以运用类似于最短路算法， $d_i$ 表示节点 $i$ 被感染的时间。然后讨论感染别人的三个方向的点。

用堆优化 $\rm Dijkstra$ 算法即可。

但是直接建图的边数可能是 $n^2$ 的。一个小优化是直线上出现的同向的点，或垂直同向的点可以直接略过。这样每对相向的点只能只会被更新一次，边数为 $\mathcal{O}(n)$，总时间复杂度 $\mathcal{O}(n\log n)$ 。

优化的具体做法是对于每条直线 $x=k$，$y=k$ ，$y=x$ ，$y=-x$ ，从左向右排序，然后扫一遍，同时记录各个初始方向的第一个点 。



---

