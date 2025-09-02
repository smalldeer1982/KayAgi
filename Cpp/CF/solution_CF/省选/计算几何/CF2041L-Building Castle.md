# Building Castle

## 题目描述

A-Ju 拥有一座美丽的城堡，她经常在其中生活。然而，长时间住在城堡让她感到无聊，所以她想将城堡重建为更漂亮的形状。

在二维平面上，我们用一个凸多边形来表示 A-Ju 的城堡。现在，她希望将城堡改造成一个具有点对称性质的凸多边形。所谓的点对称多边形，指的是存在某个中心点 $c$，使得多边形中任意一个点 $p$，其关于 $c$ 的对称点 $p^\prime$ 也在这个多边形内。

虽然设计一个点对称凸多边形并不难，但重建的花费却是非常大的。根据估算，重建的成本与原城堡和新形状之间的对称差集的面积有关。请参见下面的图示：

![](https://cdn.luogu.com.cn/upload/vjudge_pic/CF2041L/cc81c15b80e191d8f11f35ce9dd6d735fd831b60.png)

在上面的例子中，A-Ju 的城堡是由点 $(3, 7) - (2, 1) - (6, 3)$ 组成的凸多边形。经过重建，新的城堡变成由点 $(3, 7) - (\frac{7}{3}, 3) - (\frac{13}{3}, \frac{1}{3}) - (5, \frac{13}{3})$ 构成的多边形。这两个形状之间的对称差集的面积为 $\frac{11}{3}$。这个面积包含了新增的区域（绿色网格表示）以及被削减的区域（红色线条表示）。

请设计一个程序，帮助 A-Ju 规划新的城堡形状，使得原城堡与新城堡之间的对称差集面积达到最小。你只需要输出这个最小面积值，因为 A-Ju 需要先估算一下潜在的改造成本。

## 样例 #1

### 输入

```
3
2 1
6 3
3 7```

### 输出

```
3.666666666667```

## 样例 #2

### 输入

```
4
0 0
5 0
5 5
0 5```

### 输出

```
0.000000000000```

# 题解

## 作者：Register_int (赞：5)

你发现样例解释给比较奶龙。事实上这个新的多边形 $T'$ 可以被严格包含在原多边形 $T$ 内。因为假设我们现在有一个有一部分在 $T$ 外的 $T'$，那么可以根据他的重心对称性，将超出去的部分从两边一起删掉，代价是不变的。

事实上，$T'$ 可以这样生成：选择一个点 $O$，将 $T$ 按 $O$ 中心对称后与自己求交，交的部分就是一种合法的 $T'$。问题转化为最大化这个交的面积大小。

容易发现这个交的大小关于 $O$ 是单峰的，所以可以直接在平面上三分套三分，内部半平面交求多边形面积，时间复杂度 $O(n\log n\log^2 V)$。

然而并过不去，因为这题精度卡的很死，$\epsilon$ 要开到 $10^{-9}$。考虑如何去掉一个 $\log$。发现原多边形和新多边形的边本来就极角排序好了，那半平面角的时候不用排序，归并即可。时间复杂度 $O(n\log^2V)$。

```cpp
#include <bits/stdc++.h>

using namespace std;

typedef long long ll;

const int MAXN = 5e2 + 10;
const double eps = 2e-9;
const double PI = acosl(-1);

inline int sgn(double x) { return x < -eps ? -1 : x > eps ? 1 : 0; }

typedef struct Point {
	double x, y;
	Point(double x = 0, double y = 0) : x(x), y(y) {}
	Point operator + (const Point &rhs) const { return Point(x + rhs.x, y + rhs.y); }
	Point operator - (const Point &rhs) const { return Point(x - rhs.x, y - rhs.y); }
	double operator * (const Point &rhs) const { return x * rhs.x + y * rhs.y; }
	double operator ^ (const Point &rhs) const { return x * rhs.y - y * rhs.x; }
	Point operator * (const double &rhs) const { return Point(x * rhs, y * rhs); }
	Point operator / (const double &rhs) const { return Point(x / rhs, y / rhs); }
	bool operator == (const Point &rhs) const { return !sgn(x - rhs.x) && !sgn(y - rhs.y); }
	double ang() { return atan2l(y, x); }
	double mod() { return hypotl(x, y); }
} Vector;

struct Line {
	Point u, v; Vector p; double ang;
	Line(Point u = Point(0, 0), Point v = Point(0, 0)) : u(u), v(v) { p = v - u, ang = p.ang(); }
	bool operator < (const Line &rhs) const { return sgn(ang - rhs.ang) < 0; }
	bool operator == (const Line &rhs) const { return u == rhs.u && v == rhs.v; }
};

inline 
Point Intersection(Line a, Line b) {
	return a.v - a.p * ((a.v - b.v) ^ b.p) / (a.p ^ b.p);
}

inline 
bool onRight(Point a, Line b) {
	return sgn((a - b.u) ^ b.p) > 0;
}

int n; Point a[MAXN], b[MAXN], t[MAXN << 1]; Line ta[MAXN], la[MAXN << 1], s[MAXN << 1];

inline 
double f(Point o) {
	for (int i = 0; i < n; i++) la[i] = ta[i];
	for (int i = 0; i < n; i++) la[n + i] = Line(o * 2 - ta[i].u, o * 2 - ta[i].v);
	int m = n * 2, l = 1, r = 1; sort(la, la + m), s[1] = la[0];
	for (int i = 1; i < m; i++) {
		if (la[i] == la[i - 1]) continue;
		for (; l < r && onRight(t[r], la[i]); r--);
		for (; l < r && onRight(t[l + 1], la[i]); l++);
		s[++r] = la[i];
		if (!sgn(s[r].p ^ s[r - 1].p)) {
			if (onRight(s[r - 1].u, s[r]) && sgn(s[r - 1].p * s[r].p) < 0) return 0;
			r--;
			if (!onRight(la[i].u, s[r])) s[r] = la[i];
		}
		if (l < r) t[r] = Intersection(s[r - 1], s[r]);
	}
	for (; l < r && onRight(t[r], s[l]); r--);
	if (r - l <= 1) return 0; double ans = 0; t[l] = Intersection(s[l], s[r]);
	for (int i = l + 1; i < r; i++) ans += (t[i] - t[l]) ^ (t[i + 1] - t[l]);
	return ans / 2;
}

inline 
double calc(double x) {
	double l = 1e18, r = -1e18, ans = 0;
	for (int i = 0; i < n; i++) {
		double tl = min(a[i].x, a[i + 1].x), tr = max(a[i].x, a[i + 1].x);
		if (sgn(x - tl) >= 0 && sgn(tr - x) >= 0) {
			if (!sgn(tl - tr)) return 0;
			double y = a[i].y + (a[i + 1] - a[i]).y * (x - a[i].x) / (a[i + 1].x - a[i].x);
			l = min(l, y), r = max(r, y);
		}
	}
	for (; r - l > eps; ) {
		double lmid = l + (r - l) / 3, rmid = r - (r - l) / 3;
		double v1 = f(Point(x, lmid)), v2 = f(Point(x, rmid));
		ans = max(ans, v1), ans = max(ans, v2);
		if (sgn(v2 - v1) > 0) l = lmid; else r = rmid;
	}
	return ans;
}

double sum, ans, l, r; Point o;

int main() {
	scanf("%d", &n), l = 1e18, r = -1e18;
	for (int i = 0; i < n; i++) scanf("%lf%lf", &a[i].x, &a[i].y); a[n] = a[0];
	for (int i = 0; i < n; i++) sum += a[i] ^ a[i + 1]; sum /= 2;
	for (int i = 0; i < n; i++) l = min(l, a[i].x), r = max(r, a[i].x);
	for (int i = 0; i < n; i++) ta[i] = Line(a[i], a[i + 1]); sort(ta, ta + n);
	for (; r - l > eps; ) {
		double lmid = l + (r - l) / 3, rmid = r - (r - l) / 3;
		double v1 = calc(lmid), v2 = calc(rmid);
		ans = max(ans, v1), ans = max(ans, v2);
		if (sgn(v2 - v1) > 0) l = lmid; else r = rmid;
	}
	printf("%.10lf", sum - ans);
}
```

你聪明的，告诉我，横纵坐标才一万精度卡 $10^{-9}$ 是什么题，$n\le 500$ 且三只老哥冲不过去十秒是什么题。——一位痛失模拟赛场切的同学。

---

## 作者：ケロシ (赞：4)

神秘题搞了一个首 A。

首先考虑如果固定了对称中心，其最小代价是什么，设原凸多边形为 $A$，其最后对称中心为 $M$，那么计算凸多边形 $A'$，使得 $A$ 与 $A'$ 以点 $M$ 对称，那么最小代价即为 $S(A)-S(A\cap A')$，其中 $S(A)$ 表示面积。

为什么呢，随便画张图：

![](https://cdn.luogu.com.cn/upload/image_hosting/zmwra91v.png)

黑色三角形是原图形，按照某点 $M$ 反转后变为深蓝色三角形。

考虑两浅蓝色部分，这两部分对于点 $M$ 是对称的，然后考虑要使得更改后的图形以点 $M$ 中心对称，那么要么需要删去上面的部分红色区域，以及下面需要添加部分绿色区域。

不难发现删掉的部分和添加的部分是**互补**的，面积和即为一个浅蓝色三角形面积。

而这类浅蓝色三角形面积和即为 $S(A)-S(A\cap A')$。

这部分需要[半平面交](https://www.luogu.com.cn/problem/P4196)求解。

接下来就是找这个最优的对称中心了，根据数学直觉，凸多边形其代价在二维上是**单峰**的（求证明）。所以可以考虑爬山算法等方法找到最优中心即可（比如设置变化量 $\Delta d$，每次上下左右移动 $\Delta d$ 来找最优解，找不到更优的就 $\Delta d$ 除以二）。

代码太丑陋了，[代码](https://codeforces.com/contest/2041/submission/293056027)放这里。

---

