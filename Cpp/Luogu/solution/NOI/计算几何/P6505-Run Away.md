# Run Away

## 题目描述

平面直角坐标系内有一个矩形，左下角坐标为 $(0, 0)$，右上角为 $(w, h)$，边平行于坐标轴。

矩形内有 $n$ 个已知点，第 $i$ 个点坐标为 $(x_i, y_i)$。

请找到矩形内一点，使得这个点到最近的已知点距离最远。输出这个距离的值即可。

## 说明/提示

#### 样例解释 1

所求点坐标为 $(50, 50)$，到已知最近点的距离为 $40 \sqrt{2} \approx 56.568542494923802$。

---

#### 数据范围

- 对于 $50\%$ 的数据，$n \le 50$。
- 对于 $100\%$ 的数据，$1 \le w, h \le 10\ 000$，$3 \le n \le 1000$，$0 \le x_i \le w$，$0 \le y_i \le h$。

输入数据中可能有重点。

---

来源：IOI 2006 国家集训队论文「王栋 —— 浅析平面 voronoi 图的构造及应用」。

## 样例 #1

### 输入

```
100 100 4
10 10
10 90
90 10
90 90
```

### 输出

```
56.5685424949
```

## 样例 #2

### 输入

```
3000 3000 4
1200 85
63 2500
2700 2650
2990 100
```

### 输出

```
1601.8805541731
```

# 题解

## 作者：hs_black (赞：15)

# P6505 Run Away

题解区给出的都是 Voronoi 图的神仙做法，但这里将介绍一种很玄学但很好写又很快的做法

首先看到最远距离，先进行二分这个距离，这是所有的点扩散成一个个圆，我们只需要判断这些圆是否完全填满了这个矩形，那么如何判断呢

那么很玄学的就来了，我们采用分治的思想，首先一个矩形，先判断它是否可以只被一个圆覆盖，然后判断四个角只要有一个角没被覆盖就不行，如果都被覆盖了，那么递归下去，将大矩形横竖切两刀分成四个小矩形继续判断，当矩形的长度小于精度要求时返回 false

这个看起来很玄学，但实际跑起来飞快，缺点是速度和精度有关，请谨慎使用

代码部分借鉴 Luitaryi

```cpp
#pragma GCC optimize(3, "inline")
#include <iostream>
#include <cstdio>
#define R register int
using namespace std;
inline int g() {
    R x = 0, f = 1;
    register char s;
    while (!isdigit(s = getchar())) f = s == '-' ? -1 : f;
    do
        x = x * 10 + (s ^ 48);
    while (isdigit(s = getchar()));
    return x * f;
}
const double E = 1e-7;
const int N = 50001;
int n, L, W, a[N], b[N];
double c, d[N];
inline bool in(double x, double y, int i) {
    return (x - a[i]) * (x - a[i]) + (y - b[i]) * (y - b[i]) <= c;
}
inline bool ck(double x, double y, double l, double w) {
    if (l < E && w < E)
        return false;
    for (R i = 1; i <= n; ++i)
        if (in(x, y, i) && in(x + l, y, i) && in(x, y + w, i) && in(x + l, y + w, i))
            return true;
    register double L = l / 2, W = w / 2;
    return ck(x, y, L, W) && ck(x + L, y, L, W) && ck(x, y + W, L, W) && ck(x + L, y + W, L, W);
}

signed main() {
    L = g(), W = g(), n = g();
    for (R i = 1; i <= n; ++i) a[i] = g(), b[i] = g();
    register double l = 0, r = 20000, md;
    while (r - l > 1e-6) {
        md = (l + r) / 2; c = md * md;
        if (ck(0, 0, L, W)) r = md;
        else l = md;
    }
    printf("%.6f\n", l);
    return 0;
}
```



---

## 作者：Tweetuzki (赞：13)

我们发现 Voronoi 图的定义正与我们本题要求的东西类似：平面上每个点归属于其最近已知点所代表的区域。

考虑到 Voronoi 图的形态。

[图片来源](https://www.cnblogs.com/xzyxzy/p/10349399.html)

![](https://i.loli.net/2020/04/12/CiKdzBtMZ3xU7Pa.gif)

上图中可以形象地看出，Voronoi 图上最晚被扩充到的点就是我们需要求的答案点。

我们考虑这样一个思路：找到所有可能成为答案的点，然后依次检查每个点到最近点的距离，更新答案。

我们可以想到，只有这样的点是可能最后被扩充到的：

1. 矩形的四个角，即 $(0, 0)$，$(0, h)$，$(w, 0)$ 和 $(w, h)$ 四个点。
2. Voronoi 图上的顶点。既包括一条边与矩形边界的交点，也包括同时归属于三个（或以上）区域的交点。

由于 Voronoi 图是 Delaunay 三角剖分的对偶图，因此 Voronoi 图上每个顶点就是 Delaunay 三角剖分剖出的一个三角形的外心，或是剖分出的一条边的垂直平分线与矩形边界的交点。

三角剖分剖出的三角形数不超过 $3n$，剖分出的边数不超过 $2n$，因此顶点数也是在 $\mathcal{O}(n)$ 级别的。

这样我们找到了 $\mathcal{O}(n)$ 个可能成为答案的点，对每一个点都找一遍最近点距离更新答案即可。

我的程序实现为了更方便地找出剖分后的三角形，使用了 Bowyer-Watson 算法，复杂度是 $\mathcal{O}(n ^ 2)$。

因此总时间复杂度是 $\mathcal{O}(n ^ 2)$。其实可以做到 $\mathcal{O}(n \log n)$，但代码长度得翻好几倍，就暂时作罢了。

$\mathcal{O}(n ^ 2)$ 代码：

```cpp
#include <algorithm>
#include <cmath>
#include <cstdio>
#include <cstdlib>
#include <cstring>
#include <map>
#include <utility>
#include <vector>

#ifdef Tweetuzki
#define debug(arg...) fprintf(stderr, arg)
#else
#define debug(arg...) void(0)
#endif

const int MaxN = 1005, MaxF = 100000;
const double eps = 1e-9;

typedef struct vec_t {
  double x, y;
  vec_t(double _x = 0, double _y = 0) { x = _x, y = _y; }
  inline friend vec_t operator+(const vec_t &a, const vec_t &b) { return vec_t(a.x + b.x, a.y + b.y); }
  inline friend vec_t operator-(const vec_t &a, const vec_t &b) { return vec_t(a.x - b.x, a.y - b.y); }
  inline friend vec_t operator*(const vec_t &a, double k) { return vec_t(a.x * k, a.y * k); }
  inline friend double dot(const vec_t &a, const vec_t &b) { return a.x * b.x + a.y * b.y; }
  inline friend double cross(const vec_t &a, const vec_t &b) { return a.x * b.y - a.y * b.x; }
  inline friend double mod(const vec_t &a) { return sqrt(a.x * a.x + a.y * a.y); }

  inline void shake() {
    if (rand() % 2 == 0) x += 1.0 * rand() / RAND_MAX * eps;
    else x -= 1.0 * rand() / RAND_MAX * eps;
    if (rand() % 2 == 0) y += 1.0 * rand() / RAND_MAX * eps;
    else y -= 1.0 * rand() / RAND_MAX * eps;
  }
} node_t;

struct line_t {
  node_t a, b;
  line_t(node_t _a = vec_t(), node_t _b = vec_t()) { a = _a, b = _b; }

  inline friend line_t perp(const line_t &l) {
    vec_t v = l.b - l.a;
    node_t m = (l.a + l.b) * 0.5;
    return line_t(m, m + vec_t(v.y, -v.x));
  }

  inline friend node_t intersect(const line_t &m, const line_t &n) {
    double s1 = cross(n.b - m.a, n.a - m.a), s2 = cross(n.a - m.b, n.b - m.b);
    return m.a + (m.b - m.a) * (s1 / (s1 + s2));
  }
};

typedef struct vec3_t {
  double x, y, z;
  vec3_t(double _x = 0, double _y = 0, double _z = 0) { x = _x, y = _y, z = _z; }
  inline friend vec3_t operator+(const vec3_t &a, const vec3_t &b) { return vec3_t(a.x + b.x, a.y + b.y, a.z + b.z); }
  inline friend vec3_t operator-(const vec3_t &a, const vec3_t &b) { return vec3_t(a.x - b.x, a.y - b.y, a.z - b.z); }
  inline friend vec3_t operator*(const vec3_t &a, double k) { return vec3_t(a.x * k, a.y * k, a.z * k); }
  inline friend vec3_t cross(const vec3_t &a, const vec3_t &b) { return vec3_t(a.y * b.z - a.z * b.y, a.z * b.x - a.x * b.z, a.x * b.y - a.y * b.x); }
  inline friend double dot(const vec3_t &a, const vec3_t &b) { return a.x * b.x + a.y * b.y + a.z * b.z; }
} node3_t;

struct triangle_t {
  int a, b, c;
  int la, lb, lc;

  triangle_t(int _a = 0, int _b = 0, int _c = 0, int _la = 0, int _lb = 0, int _lc = 0) {
    a = _a, b = _b, c = _c;
    la = _la, lb = _lb, lc = _lc;
  }
};

struct edge_t {
  int u, v;
  double w;
  edge_t(int _u = 0, int _v = 0, double _w = 0) { u = _u, v = _v, w = _w; }
  inline friend bool operator<(const edge_t &a, const edge_t &b) { return a.w < b.w; }
};

int W, H, N, CntF;
std::map<int, bool> Mp[10005];
node_t A[MaxN + 5], MemoryA[MaxN + 5];
triangle_t F[MaxF + 5];
bool Del[MaxF + 5];

template <typename Int>
inline Int max(Int a, Int b) { return a > b ? a : b; }

template <typename Int>
inline Int min(Int a, Int b) { return a < b ? a : b; }

inline vec3_t mapping(const vec_t &a) { return vec3_t(a.x, a.y, a.x * a.x + a.y * a.y); }

inline bool inCircumcircle(const node_t &a, const node_t &b, const node_t &c, const node_t &p) {
  node3_t _a = mapping(a), _b = mapping(b), _c = mapping(c), _p = mapping(p);
  if (cross(b - a, c - a) < 0) std::swap(_b, _c);
  node3_t normal = cross(_b - _a, _c - _a);
  if (dot(normal, _p - _a) > eps) return false;
  else return true;
}

inline node_t center(const triangle_t &t) {
  line_t a = perp(line_t(MemoryA[t.a], MemoryA[t.b])), b = perp(line_t(MemoryA[t.b], MemoryA[t.c]));
  return intersect(a, b);
}

inline bool inCircumcircle(const triangle_t &t, const node_t &p) { return inCircumcircle(A[t.a], A[t.b], A[t.c], p); }

void init() {
  int _N;
  scanf("%d %d %d", &W, &H, &_N);
  for (int i = 1; i <= _N; ++i) {
    int x, y;
    scanf("%d %d", &x, &y);
    if (Mp[x][y] == true) continue;
    A[++N] = vec_t(1.0 * x, 1.0 * y);
    Mp[x][y] = true;
    MemoryA[N] = A[N];
    A[N].shake();
  }
  A[N + 1] = node_t(-1, -1), A[N + 2] = node_t(-1, H + 1);
  A[N + 3] = node_t(W + 1, -1), A[N + 4] = node_t(W + 1, H + 1);
  F[++CntF] = triangle_t(N + 1, N + 3, N + 2, 2, 0, 0);
  F[++CntF] = triangle_t(N + 4, N + 2, N + 3, 1, 0, 0);
}

std::vector< std::pair<int, int> > Lk[MaxN + 5];
int To[MaxN + 5], Tof[MaxN + 5];
int NodeStk[MaxN + 5], NodeTp;

void dfs(int u, int f, int beg) {
  if (u == beg) {
    if (f != 0) return;
    NodeStk[NodeTp++] = u;
    auto p = *(Lk[u].begin());
    To[u] = p.first;
    Tof[u] = p.second;
    dfs(p.first, u, beg);
  } else {
    NodeStk[NodeTp++] = u;
    for (auto p : Lk[u]) {
      if (p.first == f) continue;
      To[u] = p.first;
      Tof[u] = p.second;
      dfs(p.first, u, beg);
    }
  }
}

inline bool cmp(int a, int b, int c, int d) {
  if (a == c && b == d) return true;
  if (a == d && b == c) return true;
  return false;
}

inline void insert(int insertNode) {
  static int stk[MaxF + 5];
  int tp = 0;
  for (int i = 1; i <= CntF; ++i)
    if (Del[i] == false && inCircumcircle(F[i], A[insertNode]) == true) {
      stk[++tp] = i;
      Del[i] = true;
    }
  static int e[MaxF + 5][3]; int cnte = 0;
  for (int i = 1; i <= tp; ++i) {
    int x = stk[i];
    if (F[x].la == 0) {
      cnte++;
      e[cnte][0] = F[x].b, e[cnte][1] = F[x].c, e[cnte][2] = 0;
    } else if (inCircumcircle(F[F[x].la], A[insertNode]) == false) {
      int y = F[x].la;
      cnte++;
      if (F[y].la == x) {
        F[y].la = -1;
        e[cnte][0] = F[y].b, e[cnte][1] = F[y].c, e[cnte][2] = y;
      } else if (F[y].lb == x) {
        F[y].lb = -1;
        e[cnte][0] = F[y].a, e[cnte][1] = F[y].c, e[cnte][2] = y;
      } else {
        F[y].lc = -1;
        e[cnte][0] = F[y].a, e[cnte][1] = F[y].b, e[cnte][2] = y;
      }
    }
    if (F[x].lb == 0) {
      cnte++;
      e[cnte][0] = F[x].a, e[cnte][1] = F[x].c, e[cnte][2] = 0;
    } else if (inCircumcircle(F[F[x].lb], A[insertNode]) == false) {
      int y = F[x].lb;
      cnte++;
      if (F[y].la == x) {
        F[y].la = -1;
        e[cnte][0] = F[y].b, e[cnte][1] = F[y].c, e[cnte][2] = y;
      } else if (F[y].lb == x) {
        F[y].lb = -1;
        e[cnte][0] = F[y].a, e[cnte][1] = F[y].c, e[cnte][2] = y;
      } else {
        F[y].lc = -1;
        e[cnte][0] = F[y].a, e[cnte][1] = F[y].b, e[cnte][2] = y;
      }
    }
    if (F[x].lc == 0) {
      cnte++;
      e[cnte][0] = F[x].a, e[cnte][1] = F[x].b, e[cnte][2] = 0;
    } else if (inCircumcircle(F[F[x].lc], A[insertNode]) == false) {
      int y = F[x].lc;
      cnte++;
      if (F[y].la == x) {
        F[y].la = -1;
        e[cnte][0] = F[y].b, e[cnte][1] = F[y].c, e[cnte][2] = y;
      } else if (F[y].lb == x) {
        F[y].lb = -1;
        e[cnte][0] = F[y].a, e[cnte][1] = F[y].c, e[cnte][2] = y;
      } else {
        F[y].lc = -1;
        e[cnte][0] = F[y].a, e[cnte][1] = F[y].b, e[cnte][2] = y;
      }
    }
  }
  for (int i = 1; i <= cnte; ++i) {
    Lk[e[i][0]].emplace_back(e[i][1], e[i][2]);
    Lk[e[i][1]].emplace_back(e[i][0], e[i][2]);
  }
  NodeTp = 0;
  dfs(e[1][0], 0, e[1][0]);
  for (int i = 0; i < NodeTp; ++i) {
    int id = CntF + (i % NodeTp) + 1;
    F[id] = triangle_t(insertNode, NodeStk[i], To[NodeStk[i]], Tof[NodeStk[i]], CntF + ((i + 1) % NodeTp) + 1, CntF + ((i - 1 + NodeTp) % NodeTp) + 1);
    if (Tof[NodeStk[i]] != 0) {
      int y = Tof[NodeStk[i]];
      if (F[y].la == -1 && cmp(NodeStk[i], To[NodeStk[i]], F[y].b, F[y].c)) F[y].la = id;
      if (F[y].lb == -1 && cmp(NodeStk[i], To[NodeStk[i]], F[y].a, F[y].c)) F[y].lb = id;
      if (F[y].lc == -1 && cmp(NodeStk[i], To[NodeStk[i]], F[y].a, F[y].b)) F[y].lc = id;
    }
  }
  CntF += NodeTp;
  for (int i = 0; i < NodeTp; ++i) Lk[NodeStk[i]].clear();
}

inline bool inConvex(int id) { return F[id].a <= N && F[id].b <= N && F[id].c <= N; }

inline double getMindis(const node_t &p) {
  double mindis = W + H;
  for (int i = 1; i <= N; ++i)
    mindis = min(mindis, mod(p - MemoryA[i]));
  debug("p = (%lf, %lf), mindis = %lf\n", p.x, p.y, mindis);
  return mindis;
}

inline double maxdis(const line_t &l) {
  line_t p = perp(l);
  double m = 0;
  auto inRange = [&](node_t a){ return -eps <= a.x && a.x <= W + eps && -eps <= a.y && a.y <= H + eps; };
  if (inRange(intersect(p, line_t(node_t(0, 0), node_t(0, H))))) m = max(m, getMindis(intersect(p, line_t(node_t(0, 0), node_t(0, H)))));
  if (inRange(intersect(p, line_t(node_t(0, 0), node_t(W, 0))))) m = max(m, getMindis(intersect(p, line_t(node_t(0, 0), node_t(W, 0)))));
  if (inRange(intersect(p, line_t(node_t(W, 0), node_t(W, H))))) m = max(m, getMindis(intersect(p, line_t(node_t(W, 0), node_t(W, H)))));
  if (inRange(intersect(p, line_t(node_t(0, H), node_t(W, H))))) m = max(m, getMindis(intersect(p, line_t(node_t(0, H), node_t(W, H)))));
  return m;
}

void solve() {
  for (int i = 1; i <= N; ++i) insert(i);
  double ans = 0;
  for (int _x = 0; _x <= 1; ++_x)
    for (int _y = 0; _y <= 1; ++_y) {
      node_t P = vec_t(_x * W, _y * H);
      ans = max(ans, getMindis(P));
    }
  for (int i = 1; i <= CntF; ++i) {
    if (Del[i] == true) continue;
    if (inConvex(i) == false) continue;
    debug("i = %d, (%lf, %lf), (%lf, %lf), (%lf, %lf)\n", i, MemoryA[F[i].a].x, MemoryA[F[i].a].y, MemoryA[F[i].b].x, MemoryA[F[i].b].y, MemoryA[F[i].c].x, MemoryA[F[i].c].y);
    ans = max(ans, maxdis(line_t(MemoryA[F[i].b], MemoryA[F[i].c])));
    ans = max(ans, maxdis(line_t(MemoryA[F[i].a], MemoryA[F[i].c])));
    ans = max(ans, maxdis(line_t(MemoryA[F[i].a], MemoryA[F[i].b])));
    node_t O = center(F[i]);
    if (0 <= O.x && O.x <= W && 0 <= O.y && O.y <= H) {
      debug("O = (%lf, %lf), r = %lf\n", O.x, O.y, mod(O - MemoryA[F[i].a]));
      ans = max(ans, mod(O - MemoryA[F[i].a]));
    }
  }
  printf("%lf\n", ans);
}

int main() {
#ifdef Tweetuzki
  freopen("input.txt", "r", stdin);
  freopen("output.txt", "w", stdout);
  freopen("errorfile.txt", "w", stderr);
#endif
  init();
  solve();
  return 0;
}
```

---

## 作者：FyFive (赞：5)

> 前言
>
> 学长曾言：写退火的都退役了。

### 思路

注：本文中所有的“距离”均为欧几里得距离。

记一个点的“答案”为这个点到所有关键点的距离的最小值，“答案点”为答案最大的点。

考虑到问题即为这种形式：固定若干个关键点，求一个点，使得这个点的答案最大。

那么很容易就能想到的一件事情是，对于答案点，若这个点向周围偏移很小的一段距离，那么偏移后的点的答案必定劣于答案点。那么，不妨猜测对于矩形内任意一点都有类似的结论，即往靠近答案点的方向偏移一小段距离会使得这个点的答案变大，反之则变小。不难发现答案与点坐标形成的图像会是单峰的（形似下图），那么朴素爬山就行了。

![sb.jpg](https://z1.ax1x.com/2023/10/07/pPj5T0S.png)

可事实真的如此吗？

从每个关键点出发向周围偏移一定会使答案变大，也就是说每两个关键点之间的连线上必然有至少一个峰值，也即沿着这两个点对图像竖直剖开，剖面上的函数必然有至少一个峰值。这就说明了一个问题，那就是真正的图像必然不是如上图一样理想的单峰，而是具有很多个峰。同时爬山也无法通过调大步长规避小峰的办法来解决，因为很容易就能想到的一个构造是，把点排成两个不交的圆，一个圆的半径比另一个稍小一些，那么真实图像会呈现两座高峰，如果只爬一次山，显然会有 $50\%$ 的概率选错。这时候又应该怎么办呢？

考虑到真正可能可以拿来当作峰的点很少，用笔者的话来说，就是可能产生答案的区域很少，每个区域也很小，那么我们直接考虑随机起点多跑几次，每次都有一定的概率命中答案，一直跑到快到时限的时候，就有很大的概率能跑出来。

至于为什么不用退火，~~（有一个原因是因为被学长威胁过不要写退火）~~ 一个主要的原因是退火会有一定的概率接受错解，虽然命中答案所在的峰的概率会大一些，但是接受错解的风险是有可能跑不到峰顶。

### Code

细节可以看代码。

```cpp
#include<bits/stdc++.h>
using namespace std;
int h,w,n;
double x[2003],y[2003];
double ans=0;
inline double gt(double X,double Y)
{
    double ret=1e18;
    for(int i=1;i<=n;++i) ret=min(ret,(X-x[i])*(X-x[i])+(Y-y[i])*(Y-y[i]));
    return sqrt(ret);
}
inline void work()
{
    double sx=1.0*rand()/RAND_MAX*h,sy=1.0*rand()/RAND_MAX*w;
    double T=1,delta=0.9985;
    while(T>1e-6)
    {
        double dx=T*h*(1.0*rand()/RAND_MAX*2-1),dy=T*h*(1.0*rand()/RAND_MAX*2-1);
        double nx=max(0.0,min(1.0*h,sx+dx)),ny=max(0.0,min(1.0*w,sy+dy));
        double XX=gt(nx,ny);
        if(XX>ans) ans=XX,sx=nx,sy=ny;
        if(clock()>0.95*CLOCKS_PER_SEC) break;
        T*=delta;
    }
}
int main()
{
    srand(time(0));
    freopen("teleport.in","r",stdin);
    freopen("teleport.out","w",stdout);
    cin>>h>>w>>n;
    for(int i=1;i<=n;++i) cin>>x[i]>>y[i];
    while(clock()<0.95*CLOCKS_PER_SEC) work();
    printf("%.8lf",ans);
    return 0;
}
```


---

## 作者：Piwry (赞：5)

话说我看到这道题就想到 [[SDOI2013]逃考](https://www.luogu.com.cn/blog/105254/solution-p3297)。

## 解析

首先我们需要找出每个点 “支配” 的区域（也就是可以产生贡献（计算距离）的区域）。

考虑两个点的支配区域的边界，可以发现就是它们的中垂线；于是可以考虑对一个点直接暴力求出其他点和它的中垂线并拉进半平面交跑一跑求出它的支配范围。

可以想到支配区域的多边形（其实一定是凸包）的顶点一定是（比边上或多边形内点）更优的，所以我们枚举顶点到支配点距离取最大就可以了。

上面求的是一个（支配）点最大的贡献，求一次是 $O(n)$ 的；对所有点求一次总的是 $O(n^2)$，过这题还是很轻松的。

（但另外一篇题解貌似最快可以做到 $O(nlogn)$ ！~~（所以毒瘤加强版预定？）~~）

## CODE

```cpp
#include <cstdio>
#include <cmath>
#include <algorithm>
#include <cstring>
using std::sort;
using std::pair;
using std::min;
typedef pair<int, int> pad;

/*------------------------------Computational geometry------------------------------*/

const double pi =acos(-1), eps =1e-7;

struct vect{
	double x, y;
	vect(){}
	vect(double xx, double yy):x(xx), y(yy){}
	vect operator + (vect v){ return vect(x+v.x, y+v.y); }
	vect operator - (vect v){ return vect(x-v.x, y-v.y); }
	vect operator * (double mu){ return vect(mu*x, mu*y); }
	double operator / (vect v){ return x*v.y-y*v.x; }/*叉积*/
};

struct line{
	vect u, v;
	double angle;
	line(){}
	line(vect uu, vect vv):u(uu), v(vv){ angle =atan2(vv.y-uu.y, vv.x-uu.x); }
};

inline short gtr(double a, double b){ return (a-b > eps); }

inline bool eq(double a, double b){ return (a-b < eps && a-b > -eps); }

inline bool onright(line f, vect w){ return (gtr((w-f.u)/(f.v-f.u), 0)); }

/*求交点*/
vect getIntersection(line f, line g){
	double w =((g.u-f.u)/(f.u-f.v))/((f.u-f.v)/(g.u-g.v));
	return g.u+(g.u-g.v)*w;
}

int cmp(line A, line B){
	if(eq(A.angle, B.angle)) return onright(B, A.u);/*有向直线最左的在最后面，会被保留*/
	else return (gtr(B.angle, A.angle));
}

/*求左侧交*/
inline pad getHPI(line ls[], int totl, line hull[]){
	sort(ls, ls+totl, cmp);
	int l =0, r =0;
	for(int i =0; i < totl; ++i){
		while(i < totl-1 && eq(ls[i].angle, ls[i+1].angle)) ++i;
		while(r-l > 1 && onright(ls[i], getIntersection(hull[r-1], hull[r-2]))) --r;
		if(eq(ls[i].angle-hull[r-1].angle, pi)) return pad(0, 0);/*判方向相反的平行*/
		hull[r++] =ls[i];
	}
	while(r-l > 1){
        if(onright(hull[r-1], getIntersection(hull[l], hull[l+1]))) ++l;
        else if(onright(hull[l], getIntersection(hull[r-1], hull[r-2]))) --r;
        else break;/*已经没有更新了*/
    }
	if(r-l < 3) return pad(0, 0);
	else return pad(l, r);
}

inline double dist(vect x, vect y){ return sqrt((y.x-x.x)*(y.x-x.x)+(y.y-x.y)*(y.y-x.y)); }

/*中垂线左包含 x*/
inline line getmidline(vect x, vect y){
	vect mid =vect((x.x+y.x)/2, (x.y+y.y)/2), v2 =vect((y-x).y, -(y-x).x)/*顺时针方向，与 (y-x) 垂直的向量*/;
	line ret(mid+v2, mid);
	return ret;
}

/*------------------------------Main------------------------------*/

const int MAXN =1000100, MAXN2 =1100;

inline void addbound(line ls[], int &totl, int w, int h){
	ls[totl++] =line(vect(w, h), vect(0, h));
	ls[totl++] =line(vect(0, h), vect(0, 0));
	ls[totl++] =line(vect(0, 0), vect(w, 0));
	ls[totl++] =line(vect(w, 0), vect(w, h));
}

inline double getFarthest(line hull[], int toth, vect p){
	hull[toth++] =hull[0];
	double ret =0;
	for(int i =0; i < toth-1; ++i){
		double res =dist(p, getIntersection(hull[i], hull[i+1]));
		if(gtr(res, ret)) ret =res;
	}
	return ret;
}

line ls[MAXN], hull[MAXN];

inline int read(){
	int x =0; bool f =0; char c =getchar();
	while(c < '0' || c > '9') (c == '-') ? f =1, c =getchar() : c =getchar();
	while(c >= '0' && c <= '9') x = (x<<3) + (x<<1) + (48^c), c =getchar();
	return (f) ? -x : x;
}

vect point[MAXN2];

int main(){
	int w =read(), h =read(), n =read();
	int totp =0;
	for(int i =0; i < n; ++i){
		int x =read(), y =read();
		/*反正总复杂度 n 方这里就暴力判重了（*/
		bool f =1;
		for(int j =0; j < totp; ++j) if(point[j].x == x && point[j].y == y) f =0;
		if(f) point[totp++] =vect(x, y);
	}
	double ans =0;
	for(int i =0; i < totp; ++i){
		int totl =0;
		for(int j =0; j < totp; ++j){
			if(j == i) continue;
			ls[totl++] =getmidline(point[i], point[j]);
		}
		addbound(ls, totl, w, h);
		pad H =getHPI(ls, totl, hull);
		double res =getFarthest(hull+H.first, H.second-H.first, point[i]);
		if(gtr(res, ans)) ans =res;
	}
	printf("%.10lf", ans);
}
```


---

## 作者：zhangjiting (赞：5)

## 题意

平面直角坐标系内有一个矩形，左下角坐标为 $(0, 0)$，右上角为 $(w, h)$，边平行于坐标轴。

矩形内有 $n$ 个已知点，第 $i$ 个点坐标为 $(x_i, y_i)$。

请找到矩形内一点，使得这个点到最近的已知点距离最远。输出这个距离的值即可。

## 思路

题目要求求最优解，想到模拟退火。

### `calc` 函数

求出当前最近的点。

```cpp
double calc(double x,double y){
    double ans=1000000.0;
    for(int i=1;i<=n;i++)
        ans=min(ans,sqrt((x-p[i].x)*(x-p[i].x)+(y-p[i].y)*(y-p[i].y)));
    return ans;
}
```


### 模拟退火函数


枚举当前点的坐标。

注意：当坐标超出范围时应直接降温并 `continue`。

```cpp
void sa(){
	t=1919;
	double xx=ansx,yy=ansy;
	while(t>1e-14){
		double nx=t*(rand()*2-RAND_MAX)+ansx;
		double ny=t*(rand()*2-RAND_MAX)+ansy;
		if(nx>x||nx<0.0||ny>y||ny<0.0){
            t*=0.999;
            continue;
        }
		double nw=calc(nx,ny);
		double delta=nw-answ;
		if(delta>0)ansx=nx,answ=nw,xx=nx,yy=ny,ansy=ny;
		else if(exp(-delta/t)*RAND_MAX>rand())xx=nx,yy=ny;
		t*=0.999;
	}
}
```

## 代码


```cpp
#include<bits/stdc++.h>
using namespace std;
int n;
double x,y,ansx,ansy,answ=INT_MIN,t;
struct node{
	int x,y;
}p[1005];
double calc(double x,double y){
    double ans=1000000.0;
    for(int i=1;i<=n;i++)
        ans=min(ans,sqrt((x-p[i].x)*(x-p[i].x)+(y-p[i].y)*(y-p[i].y)));
    return ans;
}
void sa(){
	t=1919;
	double xx=ansx,yy=ansy;
	while(t>1e-14){
		double nx=t*(rand()*2-RAND_MAX)+ansx;
		double ny=t*(rand()*2-RAND_MAX)+ansy;
		if(nx>x||nx<0.0||ny>y||ny<0.0){
            t*=0.999;
            continue;
        }
		double nw=calc(nx,ny);
		double delta=nw-answ;
		if(delta>0)ansx=nx,answ=nw,xx=nx,yy=ny,ansy=ny;
		else if(exp(-delta/t)*RAND_MAX>rand())xx=nx,yy=ny;
		t*=0.999;
	}
}
int main(){
	srand(time(0));
	cin>>x>>y>>n;
	for(int i=1;i<=n;i++) cin>>p[i].x>>p[i].y;
	for(int i=1;i<=5;i++)sa();
	cout<<fixed<<setprecision(6)<<answ<<endl;
	return 0;
}
```


---

## 作者：Mu_leaf (赞：3)

楼上大佬太强了！~~只不过这道题其实可以更简单一些。~~

## [思路]
看题面可以发现这题很适合用模拟退火写。

不明白模拟退火的可以往[这边走](https://www.luogu.com.cn/blog/Darth-Che/mu-ni-tui-huo-xue-xi-bi-ji)。这个大佬讲的模拟退火很详细。

模拟退火最难的也许是 ```calc``` 函数了。

但因为这里是求两点之间的距离所以直接计算就可以：

```cpp
double calc(double x,double y){
    double ans=1000000.0;
    for(int i=1;i<=n;i++)
        ans=min(ans,sqrt((x-p[i].x)*(x-p[i].x)+(y-p[i].y)*(y-p[i].y)));
    return ans;
}

```

其实已经做完了。在主函数多退几次火保证正确率。

# Code:


```cpp
#include<bits/stdc++.h>
using namespace std;
int n;
double x,y,ansx,ansy,answ=INT_MIN,t;
struct node{
	int x,y;
}p[1005];
double calc(double x,double y){
    double ans=1000000.0;
    for(int i=1;i<=n;i++)
        ans=min(ans,sqrt((x-p[i].x)*(x-p[i].x)+(y-p[i].y)*(y-p[i].y)));
    return ans;
}
void sa(){
	t=1919;
	double xx=ansx,yy=ansy;
	while(t>1e-14){
		double nx=t*(rand()*2-RAND_MAX)+ansx;
		double ny=t*(rand()*2-RAND_MAX)+ansy;
		if(nx>x||nx<0.0||ny>y||ny<0.0){
            t*=0.999;
            continue;
        }
		double nw=calc(nx,ny);
		double delta=nw-answ;
		if(delta>0)ansx=nx,answ=nw,xx=nx,yy=ny,ansy=ny;
		else if(exp(-delta/t)*RAND_MAX>rand())xx=nx,yy=ny;
		t*=0.999;
	}
}
int main(){
	srand(time(0));
		answ=INT_MIN;
		cin>>x>>y>>n;
		for(int i=1;i<=n;i++) cin>>p[i].x>>p[i].y;
		for(int i=1;i<=11;i++)sa();
		printf("%.6lf\n",answ);
	
	return 0;
}

```

---

## 作者：Aventurine_stone (赞：2)

这是一篇爬山的题解，~~虽然写的有一点像模拟退火~~。
## 1. 题目分析
做一道题如果你要用随机算法，那么你要先确定此题求的值是多峰函数还是单峰函数。  
#### 判定函数类型：
我们不妨设一个点是答案点，如果我们将这个点向四周平移，显而易见的，这个点必定劣于先前的点。那么，如果我们搜索的点越接近答案点，那么 $ans$ 的值便越大，所以这是单峰函数。  
证毕。


------------

## 2. 题目做法
我们初始先随机一个起始点，再根据当前的温度值对当前点进行平移，更优则替换。


------------

## 3. 贴代码
```cpp
#include<bits/stdc++.h>
#define x first
#define y second
using namespace std;
const int N=1010;
inline int read()
{
	int x=0;
	char c=getchar();
	while(c<'0'||c>'9')
		c=getchar();
	while(c>='0'&&c<='9')
	{
		x=(x<<3)+(x<<1)+c-'0';
		c=getchar();
	}
	return x;
}
inline void write(int x)
{
	if(x>9)
		write(x/10);
	putchar(x%10+'0');
}
int n,w,h;
typedef pair<double,double> P;
P point[N];
double ans;
inline double rand(double l,double r)//随机一个l到r间的浮点值 
{
	return (double)rand()/RAND_MAX*(r-l)+l;
}
inline double dis(P a1,P a2)//求两点间的距离 
{
	return sqrt(pow(a1.x-a2.x,2)+pow(a1.y-a2.y,2));
}
double maxx(P a)//求当前点与其他点距离的最小值 
{
	double minn=INT_MAX;
	for(int i=1;i<=n;i++)
		minn=min(minn,dis(a,point[i]));
	minn>ans?ans=minn:1;
	return minn;
}
double T;
P a,b;
double now,fu,dt;
void SA()
{
	T=max(w,h);
	a.x=rand(0,w),a.y=rand(0,h);
	now=maxx(a);
	while(T>1e-6)
	{
		b.x=rand(a.x-T,a.x+T),b.y=rand(a.y-T,a.y+T);
		b.x<0?b.x=0:1;//防止随机的点出边界 
		b.x>w?b.x=w:1;
		b.y<0?b.y=0:1;
		b.y>h?b.y=h:1;
		fu=maxx(b);
		dt=now-fu;
		if(dt<=0)//更优则替换 
			now=fu,a=b;
		T*=0.9997;//缓慢降温 
	}
}
int main()
{
	w=read(),h=read(),n=read();
	for(int i=1;i<=n;i++)
		point[i].x=read(),point[i].y=read();
	while(clock()*1.0/CLOCKS_PER_SEC*1000<800)//卡时，提高准确度 
		SA();
	printf("%lf",ans);
	return 0;
}
```

---

## 作者：TempestMiku (赞：2)

看到题目让求图上的一个点到其他点的最短距离最远，我们可以想到类似的题 
[P1337 平衡点 / 吊打XXX](https://www.luogu.com.cn/problem/P1337)，用[模拟退火](https://blog.csdn.net/qq_53893431/article/details/126776594)可做。

设计一个估价函数，就是对于当前点到图上其他点的最小距离，然后模拟退火求最大的答案即可。

代码中有注释。


```cpp
#include<bits/stdc++.h>
#define int long long
using namespace std;
namespace Testify{
    inline int read(){
        int f(1),x(0);
        char ch=getchar();
        for(;!isdigit(ch);ch=getchar()) if(ch=='-') f=-1;
        for(;isdigit(ch);ch=getchar()) x=(x<<1)+(x<<3)+(ch^48);
        return f*x;
    }
    inline void Write(int x){
        if(x>9) Write(x/10);
        putchar(x%10+48);
    }
    inline void write(int x){
        if(x<0) putchar('-'),x=-x;
        Write(x);
        putchar('\n');
    }
}
using namespace Testify;
int w,h,n;
const int N=1005;
mt19937 rd(chrono::system_clock::now().time_since_epoch().count());
inline int radom(int l,int r){
    return rd()%(r-l+1)+l;
}
struct node{
    double x,y;
}point[N];
struct Avantgarde{
    double x,y,ans;
}Ans,Tmp;
inline double getdis(Avantgarde a,node b){
    return sqrt((a.x-b.x)*(a.x-b.x)+(a.y-b.y)*(a.y-b.y));
}
inline double energy(){
    double res=1e9+7;
    for(register int i=1;i<=n;i++){
        res=min(res,getdis(Tmp,point[i]));
    }
    return res;
}
double ans=1e9;
inline void SA(){
    double T=1000;
    while(T>1e-30){
        if((double)clock()/CLOCKS_PER_SEC>0.995) break;
        double ra=(1.0*Ans.x+(radom(0,w)*2-w)*1.0*T);
        double rb=(1.0*Ans.y+(radom(0,h)*2-h)*1.0*T);
        if(ra>w*1.0||rb>h*1.0||ra<0.0||rb<0.0){
            T*=0.9995;
            continue;
        }
        Tmp.x=ra,Tmp.y=rb;
        double e=energy();
        double delta=e-Ans.ans;
        //delta的值是随机解减去当前最优解的值，因为要求最大的答案，所以当delta大于0的时候再更新最大值。
        //否则以一定的概率接受答案，只更新坐标不更新最优解。
        if(delta>0){
            Ans.x=ra,Ans.y=rb,Ans.ans=e;
            // cerr<<Ans.x<<"  "<<Ans.y<<endl;
        }
        else if(exp(delta/T)*RAND_MAX>radom(0,RAND_MAX)){
            Ans.x=ra,Ans.y=rb;
        }
        T*=0.9995;
    }
}
signed main(void){
    w=read(),h=read(),n=read();
    for(register int i=1;i<=n;i++){
        register int asd=read(),jkl=read();
        point[i].x=asd*1.0,point[i].y=jkl*1.0;
    }
    Ans.x=w,Ans.y=h;
    Ans.ans=energy();
    while((double)clock()/CLOCKS_PER_SEC<0.99){
        SA();
    }
    printf("%.10lf",Ans.ans);
    return 0;
}
```


---

## 作者：auroraaa (赞：1)

## [点此看题](https://www.luogu.com.cn/problem/P6505)
不会题解给的 $O(n\log n)$ 和 $O(n^2)$ 三角剖分做法啊，又感觉爬山和退火不靠谱，这里给出一个最暴力的 $O(n^2\log n)$ 的 Voronoi 图做法，正好能过。

对于每个点，取四个边框，以及与另外 $n-1$ 个点的中垂线，做一遍 $O(n\log n)$ 的半平面交，取凸包上所有点和当前点的距离更新答案即可，总复杂度 $O(n^2\log n)$。

特别注意数据里有重点，会导致求中垂线出问题，WA 掉一个点，所以要先去重再求 Voronoi 图。

事实上，如果将所有中垂线随机打乱后，再跑 $O(n^2)$ 的半平面交，复杂度看起来像 $O(n^3)$，实际上是 $O(n^2)$ 的，证明见这篇博客 [skip2004](https://www.cnblogs.com/skip2004/p/17831417.html)。

### 细节见代码

```cpp
#include<bits/stdc++.h>
using namespace std;
#define endl '\n'
//#define int long long

const int N=1e3+5;
//#define double long double
const double eps=1e-8;
int sgn(double x){
    if(abs(x)<=eps)return 0;
    return x<0?-1:1;
}
struct Point{       //点与向量
    double x,y;
    Point(){}
    Point(double x,double y):x(x),y(y){}
    bool operator==(const Point&a)const{return sgn(x-a.x)==0&&sgn(y-a.y)==0;}
    bool operator<(const Point&a)const{
        if(sgn(x-a.x)==0)return sgn(y-a.y)==-1;
        return sgn(x-a.x)==-1;
    }
    Point operator+(const Point&a)const{return {x+a.x,y+a.y};}
    Point operator-(const Point&a)const{return {x-a.x,y-a.y};}
    Point operator*(double t)const{return {x*t,y*t};}
    Point operator/(double a)const{return {x/a,y/a};}
    double dot(const Point&a)const{return x*a.x+y*a.y;}        //点积
    double cross(const Point&a)const{return x*a.y-y*a.x;}      //叉积
    double len2()const{return dot(*this);}          //长度平方
    double dis2(const Point&a)const{return ((*this)-a).len2();}     //两点距离平方
    double dis(const Point&a)const{return sqrt(dis2(a));}           //两点距离
    Point rotate()const{return {-y,x};}     // 逆时针旋转 90°
}p[N];
typedef Point Vector;
struct Line{
    Point p;
    Vector v;
    Line(){}
    Line(Point p,Vector v):p(p),v(v){}
    Point inter(const Line&a)const{return p+v*((a.v.cross(p-a.p))/(v.cross(a.v)));}
    bool operator<(const Line&a)const{      // 直线极角排序，极角相同时靠左的在前
        if(sgn(atan2(v.y,v.x)-atan2(a.v.y,a.v.x))==0)return (a.p-p).cross(a.p+a.v-p)>0;
        else return atan2(v.y,v.x)<atan2(a.v.y,a.v.x);
    }
};
vector<Point> vor[N];    // voronoi 图
Line bisector(Point a,Point b){return {(a+b)/2.0,(b-a).rotate()};}      // 中垂线
vector<Point> Cross(vector<Line>vec){     // nlogn 半平面交
    sort(vec.begin(),vec.end());
    deque<Line>dq;
    vector<Line>v;
    for(auto line:vec){     // 按极角去重
        if(v.empty() || sgn(atan2(v.back().v.y,v.back().v.x)- atan2(line.v.y,line.v.x))!=0)v.push_back(line);
    }
    auto illegal=[&](Point p,Line l){return (l.p-p).cross(l.p+l.v-p)<0;};
    for(auto line:v){
        while(dq.size()>=2 && illegal(dq.back().inter(dq.at(dq.size()-2)),line))dq.pop_back();
        while(dq.size()>=2 && illegal(dq.front().inter(dq.at(1)),line))dq.pop_front();
        dq.push_back(line);
    }
    while(dq.size()>=2 && illegal(dq.back().inter(dq.at(dq.size()-2)),dq.front()))dq.pop_back();
    while(dq.size()>=2 && illegal(dq.front().inter(dq.at(1)),dq.back()))dq.pop_front();
    vector<Point>ans;
    for(int i=0;i<dq.size();i++){
        ans.push_back(dq.at(i).inter(dq.at((i+1)%dq.size())));
    }
    return ans;
}
void Voronoi(int n,Point t){
    for(int i=1;i<=n;i++){
        vector<Line>vec;
        vec.emplace_back(Point(0,0),Vector(t.x,0));
        vec.emplace_back(Point(t.x,0),Vector(0,t.y));
        vec.emplace_back(Point(t.x,t.y),Vector(-t.x,0));
        vec.emplace_back(Point(0,t.y),Vector(0,-t.y));
        for(int j=1;j<=n;j++){
            if(i==j)continue;
            Line l=bisector(p[i],p[j]);
            vec.emplace_back(l.p,l.v);
        }
        vor[i]=Cross(vec);
    }
}

void solve(){
    int w,h,n;
    cin>>w>>h>>n;
    vector<Point>vec;
    for(int i=1;i<=n;i++){
        int x,y;
        cin>>x>>y;
        vec.emplace_back(x,y);
    }
    sort(vec.begin(), vec.end());
    vec.erase(unique(vec.begin(), vec.end()),vec.end());
    n=vec.size();
    for(int i=1;i<=n;i++)p[i]=vec[i-1];
    Voronoi(n,Point(w,h));
    double ans=0;
    for(int i=1;i<=n;i++){
        auto&t=vor[i];
        for(auto&j:t){
            ans=max(ans,p[i].dis(j));
        }
    }
    cout<<fixed<<setprecision(10)<<ans<<endl;
}

signed main(){
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    cout.tie(nullptr);
    solve();
}
```

---

## 作者：watcher_YBH (赞：1)

# 思路：
由于这道题是平面几何类的问题，所以我们考虑写一种比较经典的做法“模拟退火”。

**模拟退火**的本质就是玄学，每次利用随机函数和已知的点，来确定一个新的点，比较这个点是否可以成为最优答案，如果是，那么更新答案，否则，再计算一个**概率**，根据概率再决定是否跳转到这个点（没错就是这么玄学）。

另外，此题还有一个奇妙地方，就是**不需要利用概率跳转**（不知道为啥，如果此题以后增加了 hack 数据，那么本题解有一定概率不会正确）。

# 代码：

```cpp
#include<bits/stdc++.h>
#define int long long
#define dou double
#define max(a,b) ((a)>(b)?a:b)
#define min(a,b) ((a)<(b)?a:b)
using namespace std;
const int MAX = 1e5+5;
int w,h,n;
dou x[MAX],y[MAX];
dou ansx,ansy,ansf;
dou far(dou nowx,dou nowy){
	dou minn = 1e9;
	for(int i = 1; i<=n; i++){
		//求出这个点到其它点的最小距离
		dou subx = nowx-x[i];
		dou suby = nowy-y[i];
		minn = min(minn,sqrt(subx*subx+suby*suby));		
	}
	return minn;
}
void sa(){
	dou t = 2e3;
	while(t >= 1e-16){
		//利用随机函数和已知的点来确定一个新的点
		dou newx = (rand()*2-RAND_MAX)*t+ansx;
		dou newy = (rand()*2-RAND_MAX)*t+ansy;
		//计算新的最短距离 
		dou newf = far(newx,newy);
		//判断是否可成为最优答案 
		if(newf > ansf && newx<=w && newx>0 && newy<=h && newy>0)
		    ansx = newx,ansy = newy,ansf = newf;//更新 
		t *= 0.995;//降温 
	}
}
signed main(){
	cin>>w>>h>>n;
	for(int i = 1; i<=n; i++)
		cin>>x[i]>>y[i],ansx += x[i],ansy += y[i];
	//这里我将xy的平均值作为初始点 
	ansx /= n,ansy /= n,ansf = far(ansx,ansy);
	srand(time(NULL));//随机函数
	//这里我是利用判断程序运行时间是否超时来进行一定次数的模拟退火
	//注：洛谷的clock函数是以微秒为单位的，DEV c++的单位是毫秒 
	while(clock() < 9e5) sa();
	printf("%.7lf",ansf);
	return 0;
}
```

由于模拟退火本身比较玄学，所以通不过某些点很正常，多交几遍就可以了。

[提交记录](https://www.luogu.com.cn/record/123902937)



---

## 作者：DengDuck (赞：0)

相当天才的一道题。

考虑二分答案，看是否包含整个矩阵。

然后对于一个区域，如果有圆包围了四个角那肯定整个区间都包围了。

如果所有圆没有包围四个角，那肯定整个区间都没被包围了。

否则我们无法确定，就划分区域递归判断，如果划分到很小都不能确定那就是不行。

这个为啥这么快呢？首先似乎编译器有个优化，就是和操作有一个是 $0$ 就不会接着算了，我感觉是这个问题。

至于其他大神没加“如果所有圆没有包围四个角，那肯定整个区间都没被包围了。”这个优化是咋过的我也不知道，可能是因为大神太强了。

欢迎大家 Hack 我，反正我是看傻了。

```cpp
#include<bits/stdc++.h>
#define LL long long
#define LF long double
#define pLL pair<LL,LL>
#define pb push_back
#define LowBound lower_bound
#define UpBound upper_bound
//#define Fi first
//#define Se second
//#define Ls(x) (x<<1)
//#define Rs(x) (x<<1|1)
//#define Ls(x) t[x].Lson
//#define Rs(x) t[x].Rson
using namespace std;
//const LL Inf;
const LL N=1e5+5;
//const LL M;
//const LL Mod;
const LF eps=1e-7;
//const LL P;
LL A,B,n,X[N],Y[N];
inline bool In(LF x,LF y,LL k,LF R)
{
	return (X[k]-x)*(X[k]-x)+(Y[k]-y)*(Y[k]-y)<R*R;
}

bool Pd(LF x,LF y,LF X,LF Y,LF R)
{
	if(X<eps||Y<eps)return false;
	bool Flg1=false,Flg2=false,Flg3=false,Flg4=false;
	for(int i=1;i<=n;i++)
	{
		bool A=In(x,y,i,R),B=In(x+X,y,i,R),C=In(x,y+Y,i,R),D=In(x+X,y+Y,i,R);
		Flg1|=A,Flg2|=B,Flg3|=C,Flg4|=D;
		if(A&&B&&C&&D)return true;
	}
	if(!Flg1&&!Flg2&&!Flg3&&!Flg4)return false;
	X/=2,Y/=2;
	return Pd(x,y,X,Y,R)&&Pd(x,y+Y,X,Y,R)&&Pd(x+X,y,X,Y,R)&&Pd(x+X,y+Y,X,Y,R);
}
int main()
{
	scanf("%lld%lld%lld",&A,&B,&n);
	for(int i=1;i<=n;i++)scanf("%lld%lld",&X[i],&Y[i]);
	LF L=0,R=2e4;
	while(R-L>eps)
	{
		
		LF Mid=(L+R)/2;
	//	cout<<Mid<<endl;
		if(Pd(0,0,A,B,Mid))R=Mid;
		else L=Mid;
	}
	printf("%.6Lf",L);
	return 0;
}
//RP++
```

---

