# [ICPC 2015 WF] Asteroids

## 题目背景

今年是 $2115$ 年。小行星通信中继系统是十年前由小行星通信部建立的。有一个小问题——小行星太多，它们很危险！比较小的小行星不仅不断干扰中继站的信号，而且对在中继站之间飞行的所有维修飞机也是一种危险。这些小行星必须被摧毁！防止危险的星际联盟（ICPC）已被下达移除这些危险的小行星的指令，并请了一支精英团队来完成这项工作。Han Duo 是这个小行星驱逐舰小组的队长。Han Duo 带着他的导弹飞过小行星带，炸毁了 ICPC 认为的令人讨厌的任何小行星。

## 题目描述

ICPC 没那么多钱。后果是 Han Duo 和他的团队没有他们想要的那么多导弹，因此他们无法炸毁所有麻烦的小行星。但是小行星很小，导弹也很强大。因此，如果两颗小行星彼此靠近并正确排列，就有可能用一枚导弹将两者都摧毁。

Han Duo 的屏幕将小行星显示为非旋转的二维简单凸多边形，每个多边形都以固定速度移动。他认为撞击两颗小行星的最佳时间是两个多边形的重叠达到最大值时。例如，图 $1$ 演示了样例输入 $1$，显示了两颗小行星及其后续的位置，间隔 $1$ 秒。两颗小行星在 $33$ 秒后开始接触，最大重叠区域出现在 $44$ 到 $55$ 秒之间。

图 $1$：样例输入 $1$。两颗有交叉路径的小行星。

计算两颗小行星的最大重叠时间需要计算机来完成，但不幸的是，Han Duo 在飞行学院的大部分程序设计课中都在睡大觉。现在把这个任务交由你。

## 说明/提示

时间限制：$2000$ 毫秒，内存限制：$1048576$ kB。

2015年国际大学生编程大赛（ACM-ICPC）世界总决赛。

## 样例 #1

### 输入

```
6 3 2 2 4 3 6 6 6 7 4 6 2 2 2
4 18 5 22 9 26 5 22 1 -2 1
```

### 输出

```
4.193518
```

## 样例 #2

### 输入

```
4 0 0 0 2 2 2 2 0 -1 1
4 10 0 10 2 12 2 12 0 1 1
```

### 输出

```
never
```

# 题解

## 作者：H3PO4 (赞：1)

题意：求两个以固定速度移动的凸多边形 $P$ 和 $Q$ 的面积交达到最大的最早时间。

面积交对于时间显然是单峰的，所以考虑三分时间。

$P$ 与 $Q$ 接触可转化为它们的闵可夫斯基差包含原点，所以先求闵可夫斯基差 $D$，把 $P$ 和 $Q$ 的速度转化为原点相对于 $D$ 的速度，即可 $O(n)$ 求出接触时间的范围。

在这个范围上三分，利用半平面交可得到某个时刻的面积交。

数据较强，可用此题来检验板子的正确性（我之前的半平面交板子就被卡掉了）。

```cpp
#include <algorithm>
#include <cmath>
#include <cstdio>
#include <deque>
#include <vector>

const double eps = 1e-8;
const int N = 200;

int sgn(double x) { return x < -eps ? -1 : x > eps ? 1 : 0; }

struct P {
  double x, y;
  P(double x = 0, double y = 0) : x(x), y(y) {}
};

using Vp = std::vector<P>;

typedef const P &Pr;
bool operator==(Pr a, Pr b) { return !sgn(a.x - b.x) && !sgn(a.y - b.y); }
P operator+(Pr a, Pr b) { return {a.x + b.x, a.y + b.y}; }
P operator-(Pr a, Pr b) { return {a.x - b.x, a.y - b.y}; }
P operator*(double k, const P &a) { return P{k * a.x, k * a.y}; }
double dot(const P &a, const P &b) { return a.x * b.x + a.y * b.y; }
double cr(const P &a, const P &b) { return a.x * b.y - a.y * b.x; }

struct Hp {
  P p, dir;
  double angle;
  Hp() {}
  Hp(Pr a, Pr b) : p(a), dir(b - a) { angle = std::atan2(dir.y, dir.x); }
  bool operator<(const Hp &b) const { return !sgn(angle - b.angle) ? cr(b.p - p, b.p + b.dir - p) > 0 : angle < b.angle; }
};

bool inside(Pr p, const Hp &h) { return sgn(cr(h.dir, p - h.p)) >= 0; }
P inter(const Hp &a, const Hp &b) { return a.p + cr(b.p - a.p, b.dir) / cr(a.dir, b.dir) * a.dir; }

int main() {
  int n, m;
  P va, vb;

  scanf("%d", &n);
  Vp a(n);
  for (int i = 0; i < n; i++) scanf("%lf %lf", &a[i].x, &a[i].y);
  scanf("%lf %lf", &va.x, &va.y);

  scanf("%d", &m);
  Vp b(m);
  for (int i = 0; i < m; i++) scanf("%lf %lf", &b[i].x, &b[i].y);
  scanf("%lf %lf", &vb.x, &vb.y);

  // 求闵可夫斯基差
  auto a_ = a;
  auto b_ = b;

  auto re = [&](Vp &a) {
    int k = 0;
    for (int i = 1; i < a.size(); i++)
      if (a[i].y < a[k].y || (a[i].y == a[k].y && a[i].x < a[k].x))
        k = i;
    std::rotate(a.begin(), a.begin() + k, a.end());
  };

  for (int i = 0; i < m; i++) b[i] = P{0, 0} - b[i];

  re(a);
  re(b);
  a.push_back(a[0]), a.push_back(a[1]);
  b.push_back(b[0]), b.push_back(b[1]);
  Vp d;
  for (int i = 0, j = 0; i < n || j < m;) {
    d.push_back(a[i] + b[j]);
    double xx = cr(a[i + 1] - a[i], b[j + 1] - b[j]);
    if (xx <= 0 && i < n) i++;
    if (xx >= 0 && j < m) j++;
  }
  int t = d.size();

  a = a_;
  b = b_;

  // 转化速度
  P v = {vb.x - va.x, vb.y - va.y};
  if (!sgn(v.x) && !sgn(v.y)) return puts("never"), 0;

  auto ll = [&](P a1, P d1, P a2, P d2) {
    return d1 == d2 ? (sgn(cr(a2 - a1, d1)) ? Vp{} : Vp{a1, a1}) : Vp{a1 + cr(a2 - a1, d2) / cr(d1, d2) * d1};
  };

  auto in = [&](P p, P a, P b) {
    return ((a.x <= p.x && p.x <= b.x) || (b.x <= p.x && p.x <= a.x)) &&
           ((a.y <= p.y && p.y <= b.y) || (b.y <= p.y && p.y <= a.y));
  };

  // 求闵可夫斯基差与速度方向的交点
  Vp vv;
  d.push_back(d[0]);
  for (int i = 0; i < t; i++) {
    P aa = d[i], bb = d[i + 1];
    if (ll(aa, bb - aa, {0, 0}, v).size() == 2) {
      vv.push_back(aa);
      vv.push_back(bb);
      goto lb;
    }
  }
  for (int i = 0; i < t; i++) {
    auto vp = ll(d[i], d[i + 1] - d[i], {0, 0}, v);
    if (vp.size() == 1 && in(vp[0], d[i], d[i + 1])) vv.push_back(vp[0]);
  }
lb:
  std::sort(vv.begin(), vv.end(), [](Pr a, Pr b) { return a.x < b.x; });
  vv = Vp(vv.begin(), std::unique(vv.begin(), vv.end()));
  
  // 求接触时间的范围
  if (vv.size() == 1) return printf("%lf\n", sgn(v.x) ? vv[0].x / v.x : vv[0].y / v.y), 0;
  if (vv.size() != 2) return puts("never"), 0;
  double l = sgn(v.x) ? vv[0].x / v.x : vv[0].y / v.y, r = sgn(v.x) ? vv[1].x / v.x : vv[1].y / v.y;
  if (l > r) std::swap(l, r);
  if (l < 0) l = 0;
  if (r < 0) return puts("never"), 0;

  // 求半平面交
  auto hps_inter = [](std::vector<Hp> &hps) {
    std::sort(hps.begin(), hps.end());
    hps = std::vector<Hp>(hps.begin(), std::unique(hps.begin(), hps.end(), [](const Hp &a, const Hp &b) { return !sgn(a.angle - b.angle); }));
    struct Q : std::deque<Hp> {
      Hp &at_impl(int pos) { return pos >= 0 ? *next(begin(), pos) : *prev(end(), -pos); }
      Hp &operator[](int pos) { return at_impl(pos); }
      const Hp &operator[](int pos) const { return ((Q *)this)->at_impl(pos); }
    } q;
    for (auto &hp : hps) {
      while (q.size() >= 2 && !inside(inter(q[-1], q[-2]), hp)) q.pop_back();
      while (q.size() >= 2 && !inside(inter(q[0], q[1]), hp)) q.pop_front();
      q.push_back(hp);
    }
    while (q.size() >= 3 && !inside(inter(q[-1], q[-2]), q[0])) q.pop_back();
    while (q.size() >= 3 && !inside(inter(q[0], q[1]), q[-1])) q.pop_front();
    if (q.size() < 3) return Vp();
    Vp ret(q.size());
    for (int i = 0; i < q.size(); i++) ret[i] = inter(q[i], q[(i + 1) % q.size()]);
    return Vp(ret.begin(), std::unique(ret.begin(), ret.end()));
  };

  // 求时刻 o 的面积交
  auto ar = [&](double o) {
    auto a_ = a;
    auto b_ = b;
    for (int i = 0; i < n; i++) a[i] = {a[i].x + va.x * o, a[i].y + va.y * o};
    for (int i = 0; i < m; i++) b[i] = {b[i].x + vb.x * o, b[i].y + vb.y * o};
    std::vector<Hp> hps;
    for (int i = 0; i < n; i++) hps.push_back(Hp(a[(i + 1) % n], a[i]));
    for (int i = 0; i < m; i++) hps.push_back(Hp(b[(i + 1) % m], b[i]));
    a = a_;
    b = b_;
    auto cv = hps_inter(hps);
    double area = 0.0;
    for (int i = 0; i < cv.size(); i++) area += cr(cv[i], cv[(i + 1) % cv.size()]);
    return area / 2;
  };

  // 三分
  while (r - l > 1e-3) {
    double h = (l + r) / 2, la = ar(h - eps), ra = ar(h + eps);
    (sgn((ra - la) * 100) > 0 ? l : r) = h;
  }
  printf("%lf\n", (l + r) / 2);
  return 0;
}
```

---

