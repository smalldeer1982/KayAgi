# Ship's Shortest Path

## 题目描述

你找到了一份新工作，非常有趣——你成为了一名船长。你的第一个任务是将你的船从一个点移动到另一个点，当然你希望以最小的代价完成这个任务。

众所周知，任意两个点之间的最短距离是这两个点之间线段的长度。但不幸的是，海上有一个岛屿，所以有时候你无法沿着两点之间的直线路径航行。

你只能移动到**安全点**。一个点被称为安全的，当且仅当它在起点和终点之间的线段上，或在岛屿的边界上。

不过你很幸运，你拥有一些聪明且强壮的工人，他们可以在旅途中协助你。他们可以帮助你在海上推动船只，这部分每移动一个单位花费 1 埃镑；他们也可以抬着船穿过岛屿，每移动一个单位花费 2 埃镑。由于工人之间会分摊这笔费用，所以工人的数量在这里并不重要。

你可以在岛屿的边界上移动船只，这将被视为在海上移动。

现在你有一张海图，你需要决定从起点到终点最小的行程花费。

起点为 $$(xStart, yStart)$$，终点为 $$(xEnd, yEnd)$$，这两个点不同。

岛屿是一个**凸多边形**，且任意一条直线上不会有超过两个多边形顶点。此外，起点和终点不会在岛屿的内部或边界上。多边形的顶点按逆时针顺序给出。

## 说明/提示

翻译由 GPT-4o 提供。

## 样例 #1

### 输入

```
1 7 6 7
4
4 2 4 12 3 12 3 2
```

### 输出

```
6.000000000
```

## 样例 #2

### 输入

```
-1 0 2 0
4
0 0 1 0 1 1 0 1
```

### 输出

```
3.000000000
```

# 题解

## 作者：rEdWhitE_uMbrElla (赞：0)

计算几何方法存点、算边来建图，然后跑一边最短路就行了。这题水到Floyd都能过。。。
	
我们先连接起始点(s)和终点(t)。如果st不与多边形相交或与多边形的一条边重合，则直接输出st的长度。否则，建一个由s、t、st与多边形的两个交点、多边形的端点组成的图。若这张图中有两点为端点的线段不与多边形相交，则这两个点之间建一条边权为从一点走到另一点费用的边。最后求s、t两点的最短路即可。

代码如下：

```
#include <bits/stdc++.h>
#define cross(a,b) ((conj(a)*(b)).imag())
#define X real()
#define Y imag()
using namespace std;

typedef complex<double> point;

const double eps = 1e-9;

int cmp(double a, double b) {
	if (fabs(a - b) < eps)
		return 0;
	return a > b ? 1 : -1;
}

struct set_cmp {
	bool operator()(const point &A, const point &B) const {
		if (cmp(A.X, B.X))
			return A.X < B.X;
		if (cmp(A.Y, B.Y))
			return A.Y < B.Y;
		return 0;
	}
};

double len(point A, point B) {
	return hypot(A.X - B.X, A.Y - B.Y);
}

bool segement(point A, point B, point R) {
	return cmp(len(A, B), len(A, R) + len(B, R)) == 0;
}

bool inter(point A, point B, point P, point Q, point &R) {
	double d1 = cross(P-A,B-A);
	double d2 = cross(Q-A,B-A);
	if (cmp(d1, d2) == 0)
		return false;
	R = (d1 * Q - d2 * P) / (d1 - d2);
	if (!segement(A, B, R) || !segement(P, Q, R))
		return false;
	return true;
}

int n;
point st, en;
vector<point> pol;

double g[34][34];

int main() {
	int x, y;
	cin >> x >> y;
	st = point(x, y);
	cin >> x >> y;
	en = point(x, y);
	cin >> n;
	for (int i = 0; i < n; i++) {
		cin >> x >> y;
		pol.push_back(point(x, y));
	}
	double ans = len(st, en);
	set<point, set_cmp> intrs;
	for (int i = 0; i < n; i++) {
		point R;
		if (inter(st, en, pol[i], pol[(i + 1) % n], R))
			intrs.insert(R);
	}
	if (intrs.size() == 2) {
		point p1 = *intrs.begin();
		point p2 = *(++intrs.begin());
		for (int i = 0; i < n + 4; i++) {
			for (int j = 0; j < n + 4; j++)
				g[i][j] = 1 << 30;
			g[i][i] = 0;
		}
		if (cmp(len(p2, st), len(p1, st)) < 0)
			swap(p1, p2);
		g[0][2] = g[2][0] = len(st, p1);
		g[1][3] = g[3][1] = len(en, p2);
		g[2][3] = g[3][2] = len(p1, p2) * 2;
		for (int i = 0; i < n; i++) {
			int i1 = i + 4;
			int i2 = (i + 1) % n + 4;
			g[i1][i2] = g[i2][i1] = len(pol[i1 - 4], pol[i2 - 4]);
			if (segement(pol[i1 - 4], pol[i2 - 4], p1)) {
				if (segement(pol[i1 - 4], pol[i2 - 4], p2)) return printf("%.9lf\n", ans),0;
				g[2][i1] = g[i1][2] = len(pol[i1 - 4], p1);
				g[2][i2] = g[i2][2] = len(pol[i2 - 4], p1);
			}
			if (segement(pol[i1 - 4], pol[i2 - 4], p2)) {
				g[3][i1] = g[i1][3] = len(pol[i1 - 4], p2);
				g[3][i2] = g[i2][3] = len(pol[i2 - 4], p2);
			}
		}
		n += 4;
		for (int k = 0; k < n; k++)
			for (int i = 0; i < n; i++)
				for (int j = 0; j < n; j++)
					g[i][j] = min(g[i][j], g[i][k] + g[k][j]);
		ans = g[0][1];
	}
	printf("%.9lf\n", ans);
}

```

---

