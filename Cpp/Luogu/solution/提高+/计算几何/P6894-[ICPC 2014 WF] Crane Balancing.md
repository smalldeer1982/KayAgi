# [ICPC 2014 WF] Crane Balancing

## 题目描述

无论在哪里进行大规模的建筑施工，你都会看到起重机在进行吊装。人们很少会想到起重机是多么奇妙的工程范例：一个（相对）重量较轻的结构可以举起更重的负载。但即使是建造得最好的起重机也可能对它们能举起的重量有一个限制。

起重机制造商协会（ACM）需要一个程序来计算起重机可以举起的重量范围。由于起重机是对称的，ACM 工程师决定只考虑每个起重机的截面，可以视为一个位于 $x$ 轴上的多边形。

![](https://cdn.luogu.com.cn/upload/image_hosting/2lyejm47.png)

图 1：起重机截面

图 1 显示了第一个样例输入中起重机的截面。假设每 $1 \times 1$ 单位的起重机截面重 1 千克，所要举起的重量将附着在多边形的一个顶点（图 1 中箭头所示）。编写一个程序来确定起重机不会向左或向右倾覆的重量范围。

## 说明/提示

时间限制：1000 毫秒，内存限制：1048576 KB。

国际大学生程序设计竞赛（ACM-ICPC）世界总决赛 2014。

题面翻译由 ChatGPT-4o 提供。

## 样例 #1

### 输入

```
7
50 50
0 50
0 0
30 0
30 30
40 40
50 40
```

### 输出

```
0 .. 1017
```

## 样例 #2

### 输入

```
7
50 50
0 50
0 0
10 0
10 30
20 40
50 40
```

### 输出

```
unstable
```

# 题解

## 作者：FangZeLi (赞：5)

## Link

[ [ICPC2014 WF]Crane Balancing](https://www.luogu.com.cn/problem/P6894)

## Solution

首先这题看着一股浓浓的计算几何味，而且题面里就给了一个谔谔的多边形，看起来非常不可做。

不过仔细分析一下，其实也不是很难。

如何判断一个物体是否稳定？

显然，只要质心在底部两个支点间，就是稳定的。

如何判断一个物体挂上一个重物是否稳定？

我们不妨先把多边形的质心求出来，然后考虑挂上重物后质心的移动，移动到的新点如果在两个支点内，那就是稳定的。

于是我们解决这道题的思路大致明确了：

1. 求出多边形面积 $S$，和质心 $P$。
2. 对质心和重物挂点的位置分类讨论（这里比较麻烦，尤其是这题还涉及到一个浮点数），通过解方程确定上下界。

然后就是一些细节上的问题。

求多边形面积可以用划分三角形然后叉积的方法，求质心可以考虑所有划分出的三角形做带权中心，但是要把式子化简一下。~~不然你很可能会像我一样交上一面才知道问题~~

## Code

```cpp
#include <cstdio>
#include <cmath>

#define _N 110
#define _EPS 1e-8
#define _INF 1e18

struct Vec {
	double x, y;
	Vec() {
		x = y = 0;
	}
	Vec(double a, double b) {
		x = a, y = b;
	}
};

typedef Vec Point;

Vec inline operator -(const Point& left, const Point& right) {
	return Vec(left.x - right.x, left.y - right.y);
}
Point inline operator +(const Point& left, const Vec& right) {
	return Point(left.x + right.x, left.y + right.y);
}
Vec inline operator *(const Vec& left, double right) {
	return Vec(left.x * right, left.y * right);
}
Vec inline operator /(const Vec& left, double right) {
	return Vec(left.x / right, left.y / right);
}
double inline operator %(const Vec& left, const Vec& right) {
	return left.x * right.y - left.y * right.x;
}

int n;

Point poly[_N];

double mass[_N];
Point pt[_N];

double curm;
Point ctr;

double l = _INF, r = -_INF;

int inline sgn(double v) {
	if (v > _EPS) {
		return 1;
	}
	if (v < -_EPS) {
		return -1;
	}
	return 0;
}

int main() {
	scanf("%d", &n);
	for (int i = 1; i <= n; i++) {
		scanf("%lf%lf", &poly[i].x, &poly[i].y);
		if (sgn(poly[i].y) == 0) {
			l = fmin(l, poly[i].x), r = fmax(r, poly[i].x);
		}
	}
	for (int i = 1; i <= n - 2; i++) {
		mass[i] = (poly[i] - poly[n]) % (poly[i + 1] - poly[n]);
		ctr = ctr + (poly[i] + poly[i + 1] + poly[n]) * mass[i];
		curm += mass[i];
	}
	ctr = ctr / curm / 3.0;
	curm = fabs(curm / 2);
	if (sgn(ctr.x - l) < 0) {
		double mn = curm * (l - ctr.x) / (poly[1].x - l), mx = curm * (r - ctr.x) / (poly[1].x - r);
		if (sgn(poly[1].x - l) <= 0) {
			puts("unstable");
		} else if (sgn(poly[1].x - r) > 0) {
			printf("%.0lf .. %.0lf\n", floor(mn + _EPS), ceil(mx - _EPS));
		} else {
			printf("%.0lf .. inf\n", floor(mn + _EPS));
		}
	} else if (sgn(ctr.x - r) > 0) {
		double mn = curm * (ctr.x - r) / (r - poly[1].x), mx = curm * (ctr.x - l) / (l - poly[1].x);
		if (sgn(poly[1].x - r) >= 0) {
			puts("unstable");
		} else if (sgn(poly[1].x - l) < 0) {
			printf("%.0lf .. %.0lf\n", floor(mn + _EPS), ceil(mx - _EPS));
		} else {
			printf("%.0lf .. inf\n", floor(mn + _EPS));
		}
	} else {
		if (sgn(poly[1].x - l) < 0) {
			double mx = curm * (ctr.x - l) / (l - poly[1].x);
			printf("0 .. %.0lf\n", ceil(mx - _EPS));
		} else if (sgn(poly[1].x - r) > 0) {
			double mx = curm * (r - ctr.x) / (poly[1].x - r);
			printf("0 .. %.0lf\n", ceil(mx - _EPS));
		} else {
			puts("0 .. inf");
		}
	}
	return 0;
}
```

## Inspiration

我认为首先是不能被这题的题面吓住，因为很多人对计算几何都有一个毒瘤的印象。其实冷静分析，这道题并不不可做。

核心结论：

- 把多边形化成三角形就可以简单的求出面积和质心

---

## 作者：wangyizhi (赞：3)

### 写在最前面

%%% 膜拜楼上巨佬 %%%

这篇题解的思路与楼上大佬相近，但感觉楼上大佬公式讲的不是很清楚（对 OIers 而言），于是本蒟蒻决定把公式推导一下 QwQ。

## 0.说明

可能的前置知识：

+ 向量运算

+ 三点共线定理

+ 物体的平衡条件（力矩平衡）

下文中记原点为 $O$。

## 1.求重心

对于重心，先考虑把多边形剖成小三角形求重心，然后根据它们的质量进行合并。

### 1.1 求三角形重心

考虑 $\triangle ABC$，记其重心为 $G$，如何用 $\overrightarrow{OA}$、$\overrightarrow{OB}$、$\overrightarrow{OC}$ 表示 $\overrightarrow{OG}$？

记 $BC$ 中点为 $D$，则 $G$ 在线段 $AD$ 上且满足 $AG=2DG$。由于 $B$、$C$、$D$ 三点共线且 $BD=CD$，则有 

$$\overrightarrow{OD}=\frac{1}{2}\overrightarrow{OB}+\frac{1}{2}\overrightarrow{OC}$$

又由于 $A$、$G$、$D$ 三点共线且 $AG=2DG$，则有 

$$\overrightarrow{OG}=\frac{2}{3}\overrightarrow{OD}+\frac{1}{3}\overrightarrow{OA}$$

综合两式，得

$$\overrightarrow{OG}=\frac{1}{3}\overrightarrow{OA}+\frac{1}{3}\overrightarrow{OB}+\frac{1}{3}\overrightarrow{OC}$$

### 1.2 求三角形质量

考虑 $\triangle ABC$，由题意得其质量可以表示为 $S_{\triangle ABC}$。由“二维向量叉积”（注：其实并没有这个概念，，，叉积其实只有三维向量有，，，）的几何意义得

$$m=S_{\triangle ABC}=\frac{1}{2}\overrightarrow{AB}\times \overrightarrow{AC}$$

### 1.3 合并两个多边形时的重心变化

记要合并的第一个多边形质量为 $m_1$，重心为 $G_1$，第二个多边形质量为 $m_2$，重心为 $G_2$，合并后的重心为 $G$。

由重心的定义，当合并后以 $G$ 为参考点时，合力矩为 $0$。因此有

$$m_1\overrightarrow{GG_1}=m_2 \overrightarrow{GG_2}$$

即

$$\frac{m_2}{m_1}=\frac{\overrightarrow{GG_1}}{\overrightarrow{GG_2}}$$

由三点共线定理，又有

$$\overrightarrow{OG}=\frac{1}{m_1+m_2}(m_1\overrightarrow{OG_1}+m_2\overrightarrow{OG_2})$$

当有多个多边形时，同理可以得出

$$\overrightarrow{OG}=\frac{1}{m_1+m_2+m_3+...}(m_1\overrightarrow{OG_1}+m_2\overrightarrow{OG_2}+m_3\overrightarrow{OG_3}+...)$$

因此我们就可以把物体的重心位置和质量求出来啦。

## 2.求答案

设支撑面为 $l\sim r$，重心所在横坐标为 $x_0$，起重机质量为 $m_0$，第一个点的坐标为 $(x,y)$，挂的物体的质量为 $m$。

分情况讨论：

### a) $x_0>r$

+ 若 $x>r$，则显然一定会倒。

+ 若 $l\le x \le r$，由于需满足力矩平衡，以 $(0,r)$ 为参考点，有

$$(r-x)\times m_{min}=(x_0-r)\times m_0$$

即

$$m\ge \frac{x_0-r}{r-x}m_0$$

+ 若 $x<l$，则最小值时以 $(r,0)$ 为参考点平衡，最大值时以 $(l,0)$ 为参考点平衡，因此

$$(r-x)\times m_{min}=(x_0-r)\times m_0$$

$$(l-x)\times m_{max}=(x_0-l)\times m_0$$

即

$$\frac{x_0-r}{r-x}m_0\le m \le\frac{x_0-l}{l-x}m_0$$

### b) $x_0<l$

求法同 a），不再赘述。

### c) $l\le x_0\le r$

+ 若 $x>r$，则最大值时以 $(r,0)$ 为参考点平衡。因此有

$$(r-x_0)\times m_0=(x-r)\times m_{max}$$

即

$$m\le \frac{r-x_0}{x-r}m_0$$

+ 若 $x<l$，同上可以得出

$$m\le \frac{x_0-l}{l-x}m_0$$

+ 若 $l\le x \le r$，则无论如何都会平衡。

---

OK，那到这里这个问题我们就推完了，剩下的就是代码实现的问题了。

~~代码就不放了，看楼上大佬的吧。~~

---

