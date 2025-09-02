# [ICPC 2014 WF] Messenger

## 题目描述

平面上有两个移动的点 A,B，其中 A 想要向 B 发送一条信息。两个点会同时出发，各自沿着一个折线移动到终点为止。A 会在移动的途中发送一条信息，这条信息可以视作一个点 C，它会沿一条射线匀速运动，当 C 与 B 重合时，B 即可收到该信息。

A,B,C 的移动速度都是 1 单位长度每秒，A 最晚在它到达终点时发出信息，B 最晚需要在它到达终点时收到信息。令 $t_A$ 代表发送信息的时间，$t_B$ 代表接收信息的时间，那么你需要最小化 $t_B-t_A$ 的值。特别地，如果 B 无论如何都无法收到信息，你需要输出 `impossible`。

## 样例 #1

### 输入

```
2
0 0
0 10
2
4 10
4 0
```

### 输出

```
4.00000
```

## 样例 #2

### 输入

```
2
0 0
1 0
3
2 0
3 0
3 10
```

### 输出

```
5.00000
```

# 题解

## 作者：FangZeLi (赞：1)

## Link

[[ICPC2014 WF]Messenger](https://www.luogu.com.cn/problem/P6897)

## Solution

~~咳咳咳，为啥ICPC这么喜欢几何题~~

言归正传，我们分析下这道题目。

显然这题的计算几何部分不是重点，那么我们主要分析这个运动过程。

题目中是两个人同时在运动，然后随便分析一下，我们就可以看出：由于两个人都是匀速直线运动，那么我们直接将一个人选作参考系，就可以转化为只有一个人运动。

那么现在问题已经弱化很多了，可是还是不是非常好处理。

一个关键的想法：这个送邮递的过程，可以这样转化一下。我们不妨直接把邮递员~~这个工具人~~直接删了，把这个过程转换为Nadia提前了$t$出发，那么，在这种情况下，只要Misha（现在一直在原点）到Nadia路径的任何一段距离小于$t$，那么$t$的送货时间就是可行的。

然后就是一些细节问题。由于每次涉及到提前一个人，所以每次的相对路径需要重新计算。然后由于是浮点数，需要注意一下精度问题。~~但凡涉及到浮点数的题目我必定要交两三面。~~最终复杂度 $\mathcal{O}(n\log n)$。

## Code

```cpp
#include <cstdio>
#include <cmath>

#define _N 50010
#define _EPS 1e-8

struct Tuple {
	double x, y;
	Tuple() {
		x = y = 0;
	}
	Tuple(double a, double b) {
		x = a, y = b;
	}
};

Tuple inline operator +(const Tuple& left, const Tuple& right) {
	return Tuple(left.x + right.x, left.y + right.y);
}
Tuple inline operator -(const Tuple& left, const Tuple right) {
	return Tuple(left.x - right.x, left.y - right.y);
}
Tuple inline operator *(const Tuple& left, double right) {
	return Tuple(left.x * right, left.y * right);
}
double inline operator *(const Tuple& left, const Tuple& right) {
	return left.x * right.x + left.y * right.y;
}
Tuple inline operator /(const Tuple& left, double right) {
	return Tuple(left.x / right, left.y / right);
}
double inline operator %(const Tuple& left, const Tuple& right) {
	return left.x * right.y - left.y * right.x;
}

typedef Tuple Point;
typedef Tuple Vec;

int n, m;

Point misha[_N];
Point nadia[_N];
double disn[_N];

int inline sgn(double val) {
	if (val > _EPS) {
		return 1;
	}
	if (val < -_EPS) {
		return -1;
	}
	return 0;
}

double inline dist(Point left, Point right) {
	return sqrtl((right.x - left.x) * (right.x - left.x) + (right.y - left.y) * (right.y - left.y));
}
double inline len(Vec val) {
	return sqrtl(val.x * val.x + val.y * val.y);
}
double inline dist(Point p, Point left, Point right) {
	double len = dist(left, right);
	if (len > _EPS && sgn((p - left) * (right - left)) >= 0 && sgn((p - right) * (left - right)) >= 0) {
		return fabsl((p - left) % (right - left)) / len;
	}
	return fminl(dist(p, left), dist(p, right));
}
Point inline at(Point from, Point to, double len) {
	return from + (to - from) * len / dist(from, to);
}
Vec inline unit(Vec val) {
	return val / len(val);
}

bool check(double delay) {
	int ptm = 1, ptn = 1;
	double remm = 0, remn = delay;
	Point lastm = misha[1], lastn;
	while (ptn < m && disn[ptn] < delay + _EPS) {
		ptn++;
	}
	if (ptn == m) {
		return true;
	}
	remn -= disn[ptn - 1];
	lastn = at(nadia[ptn], nadia[ptn + 1], remn);
	while (ptm < n && ptn < m) {
		if (dist(lastm, lastn) < delay + _EPS) {
			return true;
		}
		double timm = dist(lastm, misha[ptm + 1]), timn = dist(lastn, nadia[ptn + 1]);
		Vec relamov = (unit(nadia[ptn + 1] - lastn) - unit(misha[ptm + 1] - lastm)) * fminl(timm, timn);
		if (timm > _EPS && timn > _EPS && dist(lastm, lastn, lastn + relamov) < delay + _EPS) {
			return true;
		}
		int cmp = sgn(timm - timn);
		if (cmp == 1) {
			remm += timn, remn = 0;
			lastm = at(misha[ptm], misha[ptm + 1], remm), lastn = nadia[++ptn];
		} else if (cmp == -1) {
			remn += timm, remm = 0;
			lastn = at(nadia[ptn], nadia[ptn + 1], remn), lastm = misha[++ptm];
		} else {
			remm = remn = 0;
			lastm = misha[++ptm], lastn = nadia[++ptn];
		}
	}
	return false;
}

int main() {
	scanf("%d", &n);
	for (int i = 1; i <= n; i++) {
		scanf("%lf%lf", &misha[i].x, &misha[i].y);
	}
	scanf("%d", &m);
	for (int i = 1; i <= m; i++) {
		scanf("%lf%lf", &nadia[i].x, &nadia[i].y);
	}
	for (int i = 1; i < m; i++) {
		disn[i] = dist(nadia[i], nadia[i + 1]);
		disn[i] += disn[i - 1];
	}
	double l = 0, r = disn[m - 1];
	if (dist(misha[1], nadia[m]) > r + _EPS) {
		puts("impossible");
		return 0;
	}
	while (r - l > _EPS) {
		double mid = (l + r) / 2;
		if (check(mid)) {
			r = mid;
		} else {
			l = mid;
		}
	}
	printf("%.4lf\n", (l + r) / 2);
	return 0;
}
```

## Inspiration

我认为这题的转化如果是第一次接触还是有点难度的，不过其他的部分都不难。

关键结论：

- 两个匀速直线运动可以通过变换参考系变成静止和一个匀速直线运动。
- 邮递员可以通过转化简单的考虑

---

## 作者：JoshAlMan (赞：1)

无解判断显然是如果从 A 起点出发直接走直线最快都无法截断（在 B 到终点前到达）。

直接做不好做（无法刻画距离时间间隔对等的关系），考虑二分答案 $x$，判断邮递时间是否存在 $\le x$。

问题等价于，A 从起点出发，B 从原线路走到 $x$ 时刻出发（时刻对齐），是否有一个时刻使两者的距离 $\le x$。证明： 如果满足，显然存在（不断缩小间隔让距离和间隔相同即可）。反过来如果存在一个答案 $ans \le x$，你可能通过拉长时间间隔让他们变成 $x$，由于然后他们距离的变化不会超过时间间隔（你考虑两点 $a, b$ 之间的距离，当 $a$ 移动 $d$ 长度，距离变动会小于等于 $d$） ，所以可以得到一个时间间隔是 $x$ 然后距离 $\le x$ 的答案。

我们将时间段按照 $n + m$ 个两人走的转折点分成若干段，每段 A、B 都是在一条直线上做匀速直线运动。

运 动 是 相 对 的。 

可以转化为 A 静止，B 匀速直线运动。

即求 A 在 B 运动线段轨迹距离最小值，即点到线段最小值，就能做了。

时间复杂度 $O(n \log n)$。

---

