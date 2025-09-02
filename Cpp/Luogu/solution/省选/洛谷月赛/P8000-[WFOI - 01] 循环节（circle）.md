# [WFOI - 01] 循环节（circle）

## 题目背景

简化题意：[$\texttt{Link}$](https://www.luogu.com.cn/paste/v7gqdh44)。

出题人注：これは非常に嫌な質問なので、あまり時間をかけたくない場合は、この質問を見る前に他の質問を終えることをお勧めします。

## 题目描述

给你一个坐标系上的点集 $a$，你需要找出一个子点集 $b$ 和一个向量 $x$，使得 $\exist\ z\in N^+,\{b\cup b+x\cup b+2x\cup\dots\cup b+zx=a\}$。

现在想让你求出任意一对 $b_0,x_0,z_0$，其中 $z_0$ 为所有满足条件的三元组中 $z$ 最大的，$b_0$ 中任意三点不共线，任意四点不构成梯形或平行四边形且 $b_0\cap b_0+x_0=\varnothing,b_0\cap b_0+2x_0=\varnothing,\dots,b_0\cap b+yx_0=\varnothing|{y\to+\infty}$。

其中 $b+x$ 的意思是，$b$ 中的所有点都平移向量 $x$ 后组成的点集。

## 说明/提示

由于本题有样例解释也只是照着念一遍，并且相信既然您都做到这一题来了应该能读懂题目含义，所以本题不提供样例解释（~~其实是出题人懒~~）。

**本题采用 Subtask 捆绑测试。**
Subtask 编号 | 数据规模与约定
:-: | :-:
**Subtask #0($\text{20 pts}$)** | $1\le n\le10$；$-10\le x_i,y_i \le 10$
**Subtask #1($\text{20 pts}$)** | $1\le n\le10^3$
**Subtask #2($\text{30 pts}$)** | $z>1$
**Subtask #3($\text{30 pts}$)** | 无特殊限制

对于 $100\%$ 的数据，$1\le n\le10^5$，点的坐标范围 $\in\left(-10^9,10^9\right)$，数据保证有解。

## 样例 #1

### 输入

```
4
0 0
0 1
1 0
1 1```

### 输出

```
2
1 3
0 1
1```

## 样例 #2

### 输入

```
3
0 0
0 1
1 0```

### 输出

```
3
1 2 3
0 0
0```

# 题解

## 作者：€€£ (赞：12)

### 题解（circle）

考虑我们对 $a$ 点集求一个凸包；

然后我们对这个凸包做一次旋转卡壳：

如果某次旋转卡壳经过了 $\ge 4$ 个点，那么必定存在连线重合或平行；

根据这条线点数可以求出 $z$；

再根据两点距离，我们就可以找出对应的 $x$；

然后拿个 map 维护一下，看看一个点 $+(-x)$ 的地方有没有点，没有则说明这个点 $\in b$；

然后输出就可以了。

时间复杂度 $O(n \log n)$

所有点在一条直线上的情况需要分类讨论特判一下。

---

## 作者：TonyYin (赞：4)



给出稍微详细一点的解释，并附代码实现。

# 题意

[题面地址](https://www.luogu.com.cn/problem/P8000)

给定点集 $a$，已知 $a$ 是由任意三点不共线，任选四点均非梯形或平行四边形的点集 $b$ 延向量 $\vec x$ 连续移 $z$ 次得到的。每次移动后，原来的点集仍存在。

求 $(b,\vec x,z)$，用坐标形式表示 $\vec x$.

若有多解，求出 $z$ 最大的；若还有多解，输出任意一组即可。

保证无论 $b$ 延 $\vec x$ 移多少次，都不会有重点。

$1\leq n\leq 10^5$，点的坐标范围 $\in(-10^9, 10^9)$，均为整数，保证有解。

# 写在前面

代码中使用了向量类，可参考题解最后一部分的代码。

为方便取模等操作，代码中下标均从 $0$ 开始记录。

可以先看 [€€£的题解](https://www.luogu.com.cn/blog/ccfnb/solution-p8000)，简明扼要地说明了思路。

# 求 $b$

假设我们已经求出了 $\vec x$ 和 $z$，现在想求出原点集 $b$。

可以发现，点 $p\in b \Leftrightarrow p-\vec x\notin a$，因为如果一个点是经过平移操作后才得到的，$p-\vec x$ 一定存在于点集 $a$ 中。

坐标范围较大，需要用到 `std::map` 并重载运算符。

注意特殊处理 $z=0$ 的情况。

```cpp
vector<int> b;
void calc_b() { //利用 map 求 b 集合
	map<Point, bool> mp;
	if(z == 0) x.x = inf, x.y = inf;
	for(int i = 0; i < n; i++) mp[p[i]] = 1;
	for(int i = 0; i < n; i++) {
		if(mp[p_in[i] - x] == 0) {
			b.push_back(i);
		}
	}
}
```

# 求 $\vec x$ 和 $z$

求 $\vec x$ 和 $z$ 的过程较为复杂。

一种暴力的方法是，$\mathcal{O}(n^2)$ 枚举所有点对 $(u,v)$，检验 $\vec x=<u,v>$ 是否合法。

注意到，由于点都是平移出来的，所以 $\vec x$ 会被枚举到很多遍，但我们只需要一遍。

可以先随便举例观察一些性质。

![P8000-1](https://cdn.tonyyin.top/2022/01/25/e5631d4956448.svg)

## 旋转卡壳

如上图，$\vec x=(2, 1)$，$b=\{A,B,C,D\}$，$a=\{A,A^{\prime},A^{\prime\prime},B,B^{\prime},B^{\prime\prime},C,C^{\prime},C^{\prime\prime},D,D^{\prime},D^{\prime\prime}\}$.

可以发现，$\vec x$ 一定会出现在凸包的边界上。并且，存在凸包上的一条边，完整地包含：某个起点以及由其平移 $z$ 次得到的所有点。

又注意到题目限制：**没有任意四个起点构成梯形或平行四边形**。

所以先求凸包，然后在凸包上跑一遍旋转卡壳。若当前的两条平行线经过 $\geq 4$ 个点，则这些点一定不都是起点。我们取出平行线通过的点，利用其求出 $\vec x$ 和 $z$，方法见下一部分。

形式化地，假设凸包上的点按逆时针顺序编号，当前枚举到的线段是 $(i,i+1)$，通过旋转卡壳，我们找到最大的范围 $[j,k]$，其满足：编号在 $[j,k]$ 区间内的点共线，它们所在的直线与线段 $(i,i+1)$ 平行。若 $k-j>0$，则我们利用 $[j,k]$ 这些点求出 $\vec x$ 和 $z$.

## 处理直线上的问题

进一步把问题抽象，我们得到有 $n$ 个共线的点 $p_0,p_1,\cdots,p_{n-1}$，要利用它们求出 $\vec x$ 和 $z$.

分类讨论，共三种情况，分别 $\rm{check}$ 一下就行了。

### 情况一

![P8000-2](https://cdn.tonyyin.top/2022/01/25/73ff54ddc0d90.svg)

只包含一个起点，$\vec x$ 为 $p_0$ 和 $p_1$ 之间的向量。

因为凸包编号有序，所以起点为 $p_0$，$x=(p_{1x}-p_{0x}, p_{1y}-p_{0y})$，$z=n-1$.

```cpp
curx = p[1] - p[0], ok = 1;
for(int t = 1; t < n; t++) {
    if(p[t] != p[0] + t * curx) {
        ok = 0, tmp = t;
        break;
    }
}
if(ok) {
    if(n - 1 > z) z = n - 1, x = curx;
    return;
}
```

### 情况二

![P8000-3](https://cdn.tonyyin.top/2022/01/25/0a4be64757ad6.svg)

$\vec x$ 依旧为 $p_0$ 和 $p_1$ 之间的向量

包含两个起点，且两个起点延伸出来的线段，互相不交叉。

在情况一中，我们用 $\rm{tmp}$ 存储了第一个不满足情况一的点的编号。

由此，所以起点为 $p_0$ 和 $p_{\operatorname{tmp}}$，$x=(p_{1x}-p_{0x}, p_{1y}-p_{0y})$，在 $\rm{check}$ 的同时计算 $z$ 就可以了。

```cpp
curx = p[1] - p[0];
ok = 1, cnt1 = 0, cnt2 = 0;
for(int t = 1; t < n; t++) if(t != tmp) {
    if(p[t] == p[0] + (cnt1 + 1) * curx) cnt1++;
    else if(p[t] == p[tmp] + (cnt2 + 1) * curx) cnt2++;
    else { ok = 0; break; }
}
if(ok) {
    z = cnt1, x = curx;
    return;
}
```

### 情况三

![P8000-4](https://cdn.tonyyin.top/2022/01/25/89aa7add26f5c.svg)

$\vec x$ 为 $p_0$ 和 $p_2$ 之间的向量，思考一下可知，这并不会被包含到情况二中。

起点为 $p_0$ 和 $p_1$，$\vec x=(p_{2x}-p_{0x}, p_{2y}-p_{0y})$.

$\rm{check}$ 方法类似，注意要保证 $n>2$.

```cpp
curx = p[2] - p[0];
ok = 1, cnt1 = 0, cnt2 = 0;
for(int t = 2; t < n; t++) {
    if(p[t] == p[0] + (cnt1 + 1) * curx) cnt1++;
    else if(p[t] == p[1] + (cnt2 + 1) * curx) cnt2++;
    else { ok = 0; break; }
}
if(ok) {
    z = cnt1, x = curx;
    return;
}
```

## 代码实现

需特殊处理所有点共线的情况。在我的 [这份AC代码](https://www.luogu.com.cn/paste/v3ozrf87) 中，分开处理了所有点共线的部分，可以参考。

下面的实现将特殊情况在旋转卡壳中一并处理，详见代码注释。

由于旋转卡壳的循环性，下面的实现中有大量取模运算，并不利于阅读。**分类讨论中的代码风格更适合阅读。**

```cpp
int n, z; Point x;
Point p_in[MAXN], p[MAXN], ch[MAXN];
void calc_x_and_z() { //求 x和 z
	bool collinear = true; //collinear = true <-> 所有点都共线
	for(int i = 1; i < n; i++) {
		if((p[i - 1] - p[0]) * (p[i] - p[0]) != 0) {
			collinear = false;
		}
	}
	int siz, j, k; //siz凸包大小, j/k用于旋转卡壳
	int ok, tmp, cnt1, cnt2; //flag, 第一个不满足条件的点, 两个起点时用到的指针
	Point curx;
	if(collinear) { //所有点共线，特殊处理，认为所有点都在凸包里
		siz = n;
		memcpy(ch, p, sizeof(p)); sort(ch, ch + n);
	} else { //不都共线，求凸包
		siz = Convex_hull(n, p, ch), j = 1, k = 1;
		ch[siz] = ch[0]; ch[siz + 1] = ch[1];
	}
	for(int i = 0; i < siz; i++) { //旋转卡壳，(i, i+1)
		if(collinear) { //所有点共线时，只需要算一遍
			if(i > 0) break;
			j = 0, k = n - 1;
		} else { //否则正常旋转卡壳
			j = k;
			while((ch[i] - ch[j+1]) * (ch[i+1] - ch[j+1]) >
				(ch[i] - ch[j  ]) * (ch[i+1] - ch[j  ]))
				j = (j + 1) % siz;
			k = j;
			while((ch[i] - ch[k+1]) * (ch[i+1] - ch[k+1]) ==
				(ch[i] - ch[k  ]) * (ch[i+1] - ch[k  ]))
				k = (k + 1) % siz;
		}
		//[j, k]内的点均共线，所在直线与(i, i+1)平行
		if(k == j) continue;
		if(k == (j + 1) % siz) {
			if(1 > z) z = 1, x = ch[j+1] - ch[j];
			continue;
		}
		//1. 只有一个起点，curx = ch[j+1] - ch[j]
		curx = ch[j + 1] - ch[j];
		ok = 1, cnt1 = 0;
		for(int t = (j + 1) % siz; t != (k + 1) % siz; t = (t + 1) % siz) {
			if(ch[t] != ch[j] + (cnt1 + 1) * curx) {
				ok = 0, tmp = t;
				break;
			} cnt1++;
		}
		if(ok) {
			if(cnt1 > z) z = cnt1, x = curx;
			continue;
		}
		//2. 有两个起点 & curx = ch[j+1] - ch[j]，起点为 ch[j] 和 ch[tmp]
		curx = ch[j + 1] - ch[j];
		ok = 1, cnt1 = 0, cnt2 = 0;
		for(int t = (j + 1) % siz; t != (k + 1) % siz; t = (t + 1) % siz) if(t != tmp) {
			if(ch[t] == ch[j] + (cnt1 + 1) * curx) cnt1++;
			else if(ch[t] == ch[tmp] + (cnt2 + 1) * curx) cnt2++;
			else { ok = 0; break; }
		}
		if(ok && cnt1 == cnt2) {
			if(cnt1 > z) z = cnt1, x = curx;
			continue;
		}
		//3. 两个起点 & curx = ch[j+2] - ch[j]，起点为 ch[j] 和 ch[j+1]
		curx = ch[j + 2] - ch[j];
		ok = 1, cnt1 = 0, cnt2 = 0;
		for(int t = (j + 2) % siz; t != (k + 1) % siz; t = (t + 1) % siz) {
			if(ch[t] == ch[j] + (cnt1 + 1) * curx) cnt1++;
			else if(ch[t] == ch[j + 1] + (cnt2 + 1) * curx) cnt2++;
			else { ok = 0; break; }
		}
		if(ok && cnt1 == cnt2) {
			if(cnt1 > z) z = cnt1, x = curx;
			continue;
		}
	}
}
```

# 其他部分的代码实现

两个主要函数的代码，在上文已经给出。

这里**仅包含**：向量类的定义、凸包的求法、主函数。

```cpp
const int MAXN = 1e5 + 10, inf = 0x3f3f3f3f;
struct Point{ //向量类
	int x, y;
	Point(){};
	Point(int a, int b): x(a), y(b) {}
	Point(Point a, Point b): x(b.x - a.x), y(b.y - a.y) {}
	friend Point operator + (const Point &a, const Point &b) {
		return Point(a.x + b.x, a.y + b.y);
	}
	friend Point operator - (const Point &a, const Point &b) {
		return Point(a.x - b.x, a.y - b.y);
	}
	friend bool operator == (const Point &a, const Point &b) {
		return a.x == b.x && a.y == b.y;
	}
	friend bool operator != (const Point &a, const Point &b) {
		return a.x != b.x || a.y != b.y;
	}
	friend Point operator * (const int &a, const Point &b) {
		return Point(a * b.x, a * b.y);
	}
	friend Point operator * (const Point &a, const int &b) {
		return Point(a.x * b, a.y * b);
	}
	friend int operator * (const Point &a, const Point &b) {
		return a.x * b.y - a.y * b.x;
	}
	friend int operator & (const Point &a, const Point &b) {
		return a.x * b.x + a.y * b.y;
	}
	friend bool operator < (const Point &a, const Point &b) {
		return (a.x < b.x) || (a.x == b.x && a.y < b.y);
	}
};

inline bool check(Point s1, Point s2, Point p) {
	return Point(s2, s1) * Point(s1, p) >= 0; //凸包保留共线的点
}
int Convex_hull(int n, Point *p, Point *ret) { //求二维凸包，返回值为凸包大小
	sort(p, p + n);
	int top = -1;
	for (int i = 0; i < n; i++) {
		while (top > 0 && !check(ret[top], ret[top - 1], p[i]))
			top--;
		ret[++top] = p[i];
	}
	int k = top;
	for (int i = n - 2; i >= 0; i--) {
		while (top > k && !check(ret[top], ret[top - 1], p[i]))
			top--;
		ret[++top] = p[i];
	}
	return top;
}
```

```cpp
signed main() {
	n = read();
	for(int i = 0; i < n; i++) p_in[i].x = read(), p_in[i].y = read();
	for(int i = 0; i < n; i++) p[i] = p_in[i];

	calc_x_and_z();
	calc_b();

	printf("%lld\n", (long long)b.size());
	for(int i = 0; i < b.size(); i++) printf("%lld ", b[i] + 1); putchar('\n');
	printf("%lld %lld\n%lld\n", x.x, x.y, z);
	return 0;
}
```



---

