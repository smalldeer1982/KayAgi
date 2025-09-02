# [ABC207D] Congruence Points

## 题目描述

[problemUrl]: https://atcoder.jp/contests/abc207/tasks/abc207_d

要素数が共に $ N $ であるような二次元平面上の点の集合 $ S=\{(a_1,b_1),(a_2,b_2),\ldots,(a_N,b_N)\} $ と $ T=\{(c_1,d_1),(c_2,d_2),\ldots,(c_N,d_N)\} $ が与えられます。

$ S $ に対して以下の操作を $ 0 $ 回以上任意の順に好きなだけ繰り返すことで、$ S $ と $ T $ を一致させられるかを判定してください。

- 実数 $ p\ (0\ \lt\ p\ \lt\ 360) $ を定め、 $ S $ に含まれる全ての点を、原点を中心に時計回りに $ p $ 度回転させる。
- 実数 $ q,r $ を定める。$ S $ に含まれる全ての点を、$ x $ 軸方向に $ q $, $ y $ 軸方向に $ r $ 移動させる。$ q $, $ r $ の値域に制約はなく、特に正/負/零のいずれになってもよい。

## 说明/提示

### 制約

- $ 1\ \leq\ N\ \leq\ 100 $
- $ -10\ \leq\ a_i,b_i,c_i,d_i\ \leq\ 10 $
- $ i\ \neq\ j $ なら $ (a_i,b_i)\ \neq\ (a_j,b_j) $
- $ i\ \neq\ j $ なら $ (c_i,d_i)\ \neq\ (c_j,d_j) $
- 入力は全て整数

### Sample Explanation 1

$ S $ に含まれる点を赤で、$ T $ に含まれる点を緑で塗った場合、与えられる点集合は以下の図の通りになります。 !\[\](https://img.atcoder.jp/ghi/39ad67d4e10490f509f252a1f0e4935b.png) この場合、以下の手順によって $ S $ を $ T $ に一致させることができます。 1. $ S $ に含まれる全ての点を、原点を中心に時計回りに $ 270 $ 度回転させる。 2. $ S $ に含まれる全ての点を、$ x $ 軸方向に $ 3 $, $ y $ 軸方向に $ 0 $ 移動させる。

### Sample Explanation 2

入力に対応する図は以下の通りです。 !\[\](https://img.atcoder.jp/ghi/02c4ca4a8329110dc131b37720283d2a.png) $ S $ と $ T $ は $ y $ 軸に対して線対称ですが、問題文中に書かれているような回転操作、移動操作によって $ S $ と $ T $ を一致させることはできません。

## 样例 #1

### 输入

```
3
0 0
0 1
1 0
2 0
3 0
3 1```

### 输出

```
Yes```

## 样例 #2

### 输入

```
3
1 0
1 1
3 0
-1 0
-1 1
-3 0```

### 输出

```
No```

## 样例 #3

### 输入

```
4
0 0
2 9
10 -2
-6 -7
0 0
2 9
10 -2
-6 -7```

### 输出

```
Yes```

## 样例 #4

### 输入

```
6
10 5
-9 3
1 -5
-6 -5
6 9
-9 0
-7 -10
-10 -5
5 4
9 0
0 -10
-10 -2```

### 输出

```
Yes```

# 题解

## 作者：Rnfmabj (赞：4)

## ABC207D

### 题意

在一个平面直角坐标系上，有两个点的集合 $S,T$，对于 $S$， 我们采用${[a_1,b_1],[a_2,b_2],...,[a_n,b_n]}$ 表示 $S$ 中每个点的坐标 ，对于 $T$， 我们采用$[c_1,d_1],[c_2,d_2],...,[c_n,d_n]$ 表示 $T$ 中每个点的坐标。

现在我们想要知道经过数次如下的操作（操作类型可自由选择，操作次数可为 0 ）后，是否可使 $S, T$ 重合：

- 任选一个实数 $p(0<p\leq360)$，并将 $S$ 中的每个点围绕原点顺时针旋转 $p$ 度。

- 选择实数 $q$ 和 $r$，将 $S$ 中的每个点在 $x$ 方向上移动 $q$，在 $y$ 方向上移动 $r$ 。这里，$q$ 和 $r$ 可以是任何实数，无论是正数、负数还是零。

如果可使 $S, T$ 重合，输出 $Yes$， 否则，请输出 $No$。

### 题解

考虑两个点集可以重合的条件是什么。

当点集大小不大于 $2$ 时，则点集大小相等并且两点距离相等时点集即可重合。

而当点集大小大于 $2$ 时，只需要验证每个点到其他点的距离集合是否相等即可判断是否大致重合（翻转的情况是不合题意的）。证明的话，可以将点集建立完全图然后拆成若干个三角形，这些三角形都可以靠等边长来证明全等，也就是三个边长唯一确定一个三角形。只要对应三角形全等，那么整个完全图（也就是点集）就是大致重合的。

当然还有更感性也是更简单粗暴的理解：相当于求出点集中两两的相对距离。

这一步实现上可以哈希也可以排序，反正范围很小绝对够用。

考虑怎么判转角度。实际上只需要先确定一个点然后暴力枚举剩下的点的对应关系就行了，也可以选择极角排序后旋转序列。

这两步都满足的话那么两个点集就是符合题意的了。

---

## 作者：yemuzhe (赞：0)

注意到值域很小，所以坐标之差 $\le 20$。

如果想象以其中一个点作为旋转中心进行旋转，可以推导出旋转的角度必定可以表示为 $x + \arctan \frac a b + \arctan \frac c d$ 的形式（$x \in \big \{0, {\pi \over 2}, \pi, {3 \pi \over 2} \big \}$，$0 \le a, b, c, d \le 20$），因为相对这个点来说，其它点的方位角必定为 $x + \arctan \frac a b$ 的形式。

我们可以打出来这个表，然后枚举每一种旋转角度。去重后的旋转角度不超过 $10 ^ 5$ 种。

怎么旋转坐标系？设一个点与原点之间连线的长度为 $len$，与 $x$ 轴夹角为 $\theta$，旋转角为 $\theta ^ \prime$，可以直接正交分解，得出新点坐标为 $(len \cdot \cos (\theta + \theta ^ \prime), len \cdot \sin (\theta + \theta ^ \prime))$。

怎么判断是否重合？可以把旋转后的点都按双关键字排好序，再判断坐标之差是否为定值。

设值域 $m = 20$，则时间复杂度为 $\text O (n m ^ 4 \log n)$。

注意判相等和不等需要考虑精度误差。

```cpp
#include <cstdio>
#include <algorithm>
#include <cmath>
#define N 105
#define N2 405
#define DEG 350005
using namespace std;

const int m = 20;
const double eps = 1e-8, pi = acos (-1);

int n, tot, to;
double f[N2], g[DEG];

int sgn (double x)
{
	if (fabs (x) < eps) return 0;
	return x > 0 ? 1 : -1;
}

struct point
{
	double x, y;
	bool operator < (point a) {return sgn (x - a.x) ? x < a.x : y < a.y;}
} a[N], b[N], c[N];

bool check (double theta)
{
	for (int i = 1; i <= n; i ++)
	{
		double len = hypot (a[i].x, a[i].y);
		double otheta = atan2 (a[i].y, a[i].x);
		c[i].x = len * cos (otheta + theta);
		c[i].y = len * sin (otheta + theta);
	}
	sort (c + 1, c + n + 1);
	for (int i = 1; i <= n; i ++)
	{
		if (sgn ((c[i].x - b[i].x) - (c[1].x - b[1].x))) return 0;
		if (sgn ((c[i].y - b[i].y) - (c[1].y - b[1].y))) return 0;
	}
	return 1;
}

int main ()
{
	scanf ("%d", &n);
	for (int i = 1; i <= n; i ++)
	{
		scanf ("%lf%lf", &a[i].x, &a[i].y);
	}
	for (int i = 1; i <= n; i ++)
	{
		scanf ("%lf%lf", &b[i].x, &b[i].y);
	}
	sort (b + 1, b + n + 1);
	f[++ tot] = 0, f[++ tot] = pi / 2;
	for (int i = 1; i <= m; i ++)
	{
		for (int j = 1; j <= m; j ++)
		{
			f[++ tot] = atan ((double) i / j);
		}
	}
	sort (f + 1, f + tot + 1);
	tot = unique (f + 1, f + tot + 1) - f - 1;
	for (int i = 1; i <= tot; i ++)
	{
		for (int j = i; j <= tot; j ++)
		{
			g[++ to] = f[i] + f[j];
			g[++ to] = pi / 2 + f[i] + f[j];
			g[++ to] = pi + f[i] + f[j];
			g[++ to] = pi / 2 * 3 + f[i] + f[j];
		}
	}
	sort (g + 1, g + to + 1);
	to = unique (g + 1, g + to + 1) - g - 1;
	for (int i = 1; i <= to; i ++)
	{
		if (check (g[i])) return 0 * puts ("Yes");
	}
	puts ("No");
	return 0;
}
```

---

