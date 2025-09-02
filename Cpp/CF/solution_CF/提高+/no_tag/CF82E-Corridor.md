# Corridor

## 题目描述

考虑一个房屋的平面设计图。

房屋可以表示为一个无限宽的水平长条，其范围由不等式 $-h \le y \le h$ 确定。在房屋的上方和下方，有两个分别位于 $(0, f)$ 和 $(0, -f)$ 的光源。墙上开有窗户，窗户的位置用在直线 $y = h$ 和 $y = -h$ 上的线段表示，并且这些窗户关于 $y = 0$ 对称排列。

你的任务是计算地板上被光源照亮的区域面积。

## 样例 #1

### 输入

```
1 1 2
-1 1
```

### 输出

```
10.0000000000
```

## 样例 #2

### 输入

```
2 2 4
-1 0
1 2
```

### 输出

```
23.3333333333
```

# 题解

## 作者：rEdWhitE_uMbrElla (赞：0)

---

题记： ~~(一般是废话，那就别看了吧)~~

似乎我写题解除了模板就几乎都是计算几何题了。。。也许没几天还能搞出一篇计算几何的日报？~~咕咕咕~~

---

emmm...题解终于正式开始了。。。

这屑题可能是计算几何题中的难得的良心题了。。。这题其实就是灯照进去每个窗的面积总和减去灯光相交、重叠部分的面积。

1. 灯照进去每个窗的面积总和

	我们很容易发现这题灯照进去每个窗的面积其实就是一个梯形的面积，这个梯形的高就是```2h```，而一个底就是窗户的长度，而我们其实可以算出在窗户边缘的两束光(其实就是两个一次函数)的函数解析式，从而算出这个梯形的另外一个底的起始点和终止点，然后就可以算出这个底的长度。就这样算出每个梯形的面积，然后全部加起来就是总和了。
    
2. 重叠面积
	
    重叠部分一般为三角形，但如果有光束的交点的纵坐标在```-h~h```之外时，是梯形。计算面积是用之前求出的函数解析式求出两条边缘光束的交点、边缘光束与x轴的交点，然后计算面积即可。
    
最后容斥原理计算一下面积就行了。

上代码：

```cpp
#include<bits/stdc++.h>
#define eps 1e-8
#define SGN(x) ((x)>eps?1:((x)>-eps?0:-1))
using namespace std;

struct point {
	double x, y;
	point() {}
	point(double _x, double _y):x(_x), y(_y) {}
	point operator - (const point p1) {
		return point(x - p1.x, y - p1.y);
	}
};

double cross(const point &a,const point &b,const point &c) {
	return (b.x-a.x)*(c.y-a.y)-(b.y-a.y)*(c.x-a.x);
}

double cross(const point &a,const point &b) {
	return a.x*b.y-a.y*b.x;
}

double dot(const point &a,const point &b) {
	return a.x*b.x+a.y*b.y;
}

point its(const point &a, const point &b, const point &c, const point &d) {
	point ret = a;
	double t = ((c.x - a.x)*(d.y - c.y) - (c.y - a.y)*(d.x - c.x)) / ((b.x - a.x)*(d.y - c.y) - (b.y - a.y)*(d.x - c.x));
	ret.x += (b.x - a.x) * t;
	ret.y += (b.y - a.y) * t;
	return ret;
}

int n;
point p[1010][4];

pair<double, int> e[5000];
int cnt;

inline void insert(point &s, point &t, point X, int inc) {
	double ratio = SGN(t.x - s.x) ? (X.x - s.x) / (t.x - s.x) : (X.y - s.y) / (t.y - s.y);
	e[cnt++] = make_pair(ratio, inc);
}

double h, f;

int main() {
	scanf("%d%lf%lf", &n, &h, &f);
	point p1(0, -f), p2(0, f);
	for (int i = 0; i < n; ++i) {
		double l, r;
		scanf("%lf%lf", &l, &r);
		p[i * 2][0] = point(l, -h);
		p[i * 2][1] = point(r, -h);
		p[i * 2][2] = its(p1, point(r, -h), point(0, h), point(100, h));
		p[i * 2][3] = its(p1, point(l, -h), point(0, h), point(100, h));
		p[i * 2 + 1][0] = point(r, h);
		p[i * 2 + 1][1] = point(l, h);
		p[i * 2 + 1][2] = its(p2, point(l, h), point(0, -h), point(100, -h));
		p[i * 2 + 1][3] = its(p2, point(r, h), point(0, -h), point(100, -h));
	}
	n *= 2;
	double ans = 0.0;
	int cp0, cp1, cp2;
	for (int i = 0; i < n; i++) {
		for (int k = 0; k < 4; k++) {
			point &s = p[i][k], &t = p[i][k==3?0:k+1];
			cnt = 0;
			e[cnt++] = make_pair(0.0, 1);
			e[cnt++] = make_pair(1.0, -1);
			for (int j = 0; j < n; j++) if (i != j) {
					for (int l = 0; l < 4; l++) {
						cp0 = SGN(cross(s, t, p[j][l==0?3:l-1]));
						cp1 = SGN(cross(s, t, p[j][l]));
						cp2 = SGN(cross(s, t, p[j][l==3?0:l+1]));
						if (cp1 * cp2 < 0)
							insert(s, t, its(s, t, p[j][l], p[j][l==3?0:l+1]), cp2);
						else if (!cp1 && cp0 * cp2 < 0)
							insert(s, t, p[j][l], cp2);
						else if (!cp1 && !cp2 && j > i && dot(t - s, p[j][l==3?0:l+1] - p[j][l]) > -eps) {
							insert(s, t, p[j][l], -1);
							insert(s, t, p[j][l==3?0:l+1], 1);
						}
					}
				}
			sort(e, e + cnt);
			int acc = 0;
			double total = 0.0, last;
			for (int j = 0; j < cnt; j++) {
				acc += e[j].second;
				if (acc == 0 && e[j].second < 0)
					total += e[j].first - last;
				last = e[j].first;
			}
			ans += cross(s, t) * total;
		}
	}
	printf("%.10lf\n", ans * 0.5);
}
```

正好100行的程序。。

---

