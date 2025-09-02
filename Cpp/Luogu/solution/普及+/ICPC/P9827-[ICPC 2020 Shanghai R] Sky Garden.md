# [ICPC 2020 Shanghai R] Sky Garden

## 题目描述

杜教授和庞教授计划在 Allin 市附近建造一个空中花园。在花园中，将有一个由直路和环形路组成的植物迷宫。

在植物迷宫的蓝图上，杜教授画了 $n$ 个圆，表示环形路。所有圆的圆心都是 $(0, 0)$。第 $i$ 个圆的半径是 $i$。

同时，庞教授在蓝图上画了 $m$ 条直线，表示直路。所有的直线都经过 $(0, 0)$。每个圆被这些直线等分成 $2m$ 个部分。

设 $Q$ 为 $n+m$ 条道路的集合。设 $P$ 为 $Q$ 中两条不同道路的所有交点的集合。注意，每条环形路和每条直路都有两个交点。

对于两个不同的点 $a \in P$ 和 $b \in P$，我们定义 $dis(\{a, b\})$ 为沿着道路从 $a$ 到 $b$ 需要走的最短距离。请计算对于所有 $\{a, b\} \subseteq P$ 的 $dis(\{a, b\})$ 的和。

## 说明/提示

![](https://cdn.luogu.com.cn/upload/image_hosting/81sxvtcp.png)

$dis(p_1, p_2)=dis(p_2, p_3)=dis(p_3, p_4)=dis(p_1, p_4)=\frac{\pi}{2}$

$dis(p_1, p_5)=dis(p_2, p_5)=dis(p_3, p_5)=dis(p_4, p_5)=1$

$dis(p_1, p_3)=dis(p_2, p_4)=2$。

题面翻译由 ChatGPT-4o 提供。

## 样例 #1

### 输入

```
1 2```

### 输出

```
14.2831853072```

## 样例 #2

### 输入

```
2 3```

### 输出

```
175.4159265359```

# 题解

## 作者：Nuyoah_awa (赞：8)

题解区目前都是 $\mathcal O(n^3)$ 的做法，但是我觉得 $\mathcal O(n)$ 的挺好想的，来写发 $\mathcal O(n)$ 的题解。

### 题目大意

有 $n$ 个半径为 $1\sim n$ 的同心圆，且有 $m$ 条过圆心直线将圆平分。

对于所有线与圆的交点，从中任取两个，求两点最短路的和。

### 题目分析

我们不难发现，每个圆上有 $2m$ 个点，一共 $n$ 个圆，很容易想到 DP，并且在圆上有对称性，对于每个圆，我们其实只需要算出一个点的贡献，剩下的可以根据对称性得到。

#### DP 大体思路

首先，我们规定圆根据半径从小到大编号为 $1 \sim n$。

我们设 $f_i$ 表示第 $i$ 个圆上一点到第 $1 \sim i$ 个中所有点的最短路和。

对于每个 $f_i$，我们分成同层与不同层两种情况得出。

#### DP 转移

对于这个点与本层的点的最短路，不难发现，要么通过圆上走来，要么通过半径走来，每个点的最短路通过两值取较小得出，如下图。

![P9827-1](https://z1.ax1x.com/2023/11/08/pi1LX8J.png)

对于这个点 $x$ 与半径更小的圆上的点 $y$，我们观察下图，发现两中路径中，先从 $y$ 到 $x$ 所在的圆上，然后再从这个点到 $x$ 与先从 $y$ 到 $y$ 所在的圆上 $x$ 对应的点，然后再到 $x$相比，很明显后者更优，原因如下：

首先，我们发现，如果在较小的圆中，这两点的最短路径是从圆上走的，那么另一个圆对应的两点也是从圆上走的，反之同理。于是，我们可以分为两类讨论：

1. 两点从圆上走，观察下图，很明显蓝色更优，因为半径更小的弧长也更小。

![P9827-2](https://z1.ax1x.com/2023/11/08/pi1LOC4.png)

2. 下图中，两点从半径走，则蓝色更优，因为他没必要先向外走再走回来。

![P9827-3](https://z1.ax1x.com/2023/11/08/pi1Lq5F.png)

综上，我们先从 $y$ 走到 $x$ 对应的点，然后通过半径的一段走到 $x$。

于是，我们可以得到 $f_i$ 的递推式：

$$f_i = f_{i-1} + (i-1) \times (2 \times m) \times 1 + g_i$$

其中，$g_i$ 表示一个点到这个圆上的点的距离和。根据以上分析，$g_i$ 是通过枚举得来的，但是，我们发现根据上述的两类讨论可以得出“如果在较小的圆中，这两点的最短路径是从圆上走的，那么另一个圆对应的两点也是从圆上走的，反之同理。”也就是说 $g_i$ 也可以递推得出。

又经过观察发现，$g_i$ 其实都可以 $\mathcal O(1)$ 求出，即 $g_i = i \times g_1$，其中 $g_1$ 通过枚举得出。

#### 边界状况

首先，对于 $g_1$，$g_1 = \sum\limits_{i = 0}^{i \le 2m} \min\{2 , \dfrac{i}{2m} \times 2π, \dfrac{2m - i}{2m} \times 2π\}$。

根据圆的轴对称性，式子可化简为 $g_1$，$g_1 = (\sum\limits_{i = 0}^{i < m} \min\{2 , \dfrac{i}{2m} \times 2π\}) \times 2 + 2$。

而对于 $f_1$，没有半径比其小的圆，所以 $f_1 = g_1$。

#### 答案求值

答案依旧可以分为两部分算，原理同上，式子为：

$$ans = \sum\limits_{i = 1}^{i \le n} 2m \times (f_i - g_i) + m \times g_i + i \times 2m (m > 1)$$

所以时间复杂度为 $\mathcal O(m)$ 预处理，$\mathcal O(n)$ 递推，$\mathcal O(n)$ 求答案。总时间复杂度是 $\mathcal O(n)$ 的。

### code
```cpp
#include <iostream>
#include <cstdio>
#include <algorithm>
#include <vector>
#define int long long
#define double long double

using namespace std;

const int N = 505;
int n, m;
double ans = 0, f[N], g[N], tmp, pi = 3.141592653589;

signed main()
{
	scanf("%lld %lld", &n, &m);
	for(int i = 1;i < m;i++)
		tmp += min(i * pi / m, 2.0L);
	tmp *= 2;
	tmp += 2;
	f[1] = g[1] = tmp;
	for(int i = 2;i <= n;i++)
	{
		g[i] = g[1] * i;
		f[i] = f[i-1] + 2 * m * (i - 1) + g[i];
	}
	for(int i = 1;i <= n;i++)
		ans += 2 * m * (f[i] - g[i]) + m * g[i] + (m > 1 ? 2 * m * i : 0);
	printf("%.10Lf", ans);
	return 0;
}
```

---

## 作者：Ydoc770 (赞：5)

## 题解：[Luogu P9827](https://www.luogu.com.cn/problem/P9827) [ICPC2020 Shanghai R] Sky Garden 

本题解试图给出 **$O(1)$ 做法**的推导过程。

我们的思路便是把欲求值分成几个可以用**形如和式**来表达的值，再把和式**化成封闭形式**。
考虑以下几个部分：
1. 一个点在圆上，一个点在圆心上的部分；
2. 两个点在同一个圆上的部分；
3. 一个点在外圆，一个点在内圆的部分。

可以覆盖所有情况，下面考虑列式子并化简。
### PART 1：
每个圆与直线交有 $2m$ 个点，从小到大枚举半径 $i$，有：
$$
\begin{aligned}
\sum_{i=1}^n 2mi&=2m\frac{n(n+1)}{2}\\
&=mn(n+1)
\end{aligned}
$$

### PART 2：
考虑**一个圆上**两个点可能出现的**相对位置**情况：
![image.png](https://s2.loli.net/2024/11/22/B4gVdCJzTaDcGhR.png)


对于圆上两点：若夹角 $\theta$ 较小，则 $dist=l$ ；若夹角 $\theta$ 较大，则 $dist=2r$ 。则临界状态 $l=\theta r=2r$， $\theta=2$。
设有**单位夹角** $\alpha=\frac{2\pi}{2m}=\frac{1}{m}\pi$，**符合 $\theta\le2$ 的交点数量**为 $k$ 。
根据定义，则 $k$ 满足 $k\alpha\le2,(k+1)\alpha>2$ ，解得 $k=\lfloor \frac{2m}{\pi}\rfloor $ 。
所以我们枚举每一个圆 $i$ ，圆上 $2m$ 个位置**左右分别枚举 $k$ 个交点**，这 $2k$ 个 $dist$ 是弧长；剩余**除去自己** $2m-2k-1$ 个 $dist$ 是两倍半径。
注意所有 $dist$ **重复算了两次**，要在最外面乘以 $\frac12$ ，即有：
$$
\begin{aligned}
&\ \ \ \ \ \frac{1}{2}\sum_{i=1}^n\Big\{2m\Big [(2\sum_{j=1}^kj\alpha\cdot  i)+(2m-2k-1)\cdot2i\Big]\Big\}\\
&=\frac{1}{2}\cdot2m\sum_{i=1}^n\Big[2\alpha\cdot i\frac{k(k+1)}{2}+(2m-2k-1)\cdot2i\Big]\\
&=m\Big[\alpha\cdot k(k+1)\cdot\frac{n(n+1)}{2}+(2m-2k-1)\cdot2\frac{n(n+1)}{2} \Big]\\
&=\frac{1}{2}m\alpha\cdot k(k+1)\cdot n(n+1)+m(2m-2k-1)\cdot n(n+1)\\

&由于 \alpha=\frac1m\pi ，有 m\alpha=\pi ，即：\\&=\frac{1}{2}\pi\cdot k(k+1)\cdot n(n+1)+m(2m-2k-1)\cdot n(n+1)
\end{aligned}
$$
### PART 3：
同样要考虑**两个点的相对位置**分类讨论，这里沿用 $PART\ 2$ 的 $\alpha$ 和 $k$。
![image.png](https://s2.loli.net/2024/11/22/SjcuphCn5aLMvWK.png)
处于内、外圆上的两点之间的距离取值同样有两种情况： $\theta>2$ 和 $\theta\le2$ 。
枚举**内圆 $j$**，**外圆 $l$**。$\theta>2$ 时显然有 $dist=l+j$ 。 
我们来观察 $\theta\le2$ 时几种可能的距离，分别是橙弧、黄弧、绿弧加上半径之差。因为橙弧一定最短，那么有 $dist = \theta\cdot j + l-j$ 。
但是两点**处于圆上同一相对位置**的情况考虑漏了，补上 $l-j$ ，即有：

$$
\begin{aligned}
&\ \ \ \ \ \sum_{1\le j<l\le n}2m\Big[2\sum_{c=1}^k(c\alpha \cdot j + l-j)+(2m-2k-1)(2j + l - j)+l-j\Big]\\
&=2m\sum_{1\le j<l\le n}\Big[2\alpha \cdot j\cdot\frac{k(k+1)}{2} + 2kl-2kj+(2m-2k-1)(l + j)+l-j\Big]\\
&=2m\sum_{1\le j<n}\sum_{j < l\le n}\Big[\alpha \cdot j\cdot k(k+1) + 2kl-2kj+(2m-2k-1)(l + j)+l-j\Big]\\
&=2m\sum_{1\le j<n}\Big[\alpha \cdot j\cdot k(k+1)\cdot(n-j)+2k\cdot\frac{(n+j+1)(n-j)}{2} -2kj\cdot(n-j)\\
&+(2m-2k-1)\cdot\frac{(n+j+1)(n-j)}{2} + (2m-2k-1)j\cdot(n-j)+\frac{(n+j+1)(n-j)}{2}-j\cdot(n-j)\Big]\\
&合并同类项，有：\\
&=2m\sum_{1\le j<n}\Big[\alpha\cdot j\cdot k(k+1)\cdot(n-j)+m\cdot(n-j)(n+j+1)+j\cdot(n-j)(2m-4k-2)\Big]\\
&=2m\Big\{\alpha\cdot k(k+1)\Big[n\cdot\frac{n(n-1)}{2}-\frac{n(n-1)(2n-1)}{6}\Big]+m\sum_{1\le j<n}j(2n-j+1)\\&+(2m-4k-2)\Big[n\cdot\frac{n(n-1)}{2}-\frac{n(n-1)(2n-1)}{6}\Big]\Big\}\\
&=2m\alpha\cdot k(k+1)\cdot n\cdot \frac{n(n-1)}{2}-2m\alpha\cdot k(k+1)\cdot\frac{n(n-1)(2n-1)}{6}+m^2(2n+1)\cdot\frac{n(n-1)}{2}\\
&-2m^2\cdot\frac{n(n-1)(2n-1)}{6}+2m(2m-4k-2)\cdot n\cdot\frac{n(n-1)}{2}-2m\cdot(2m-4k-2)\cdot \frac{n(n-1)(2n-1)}{6}\\
&再代入 m\alpha=\pi,即：\\
&= \pi\cdot k(k+1)\cdot n^2(n-1)-\pi\cdot k(k+1)\cdot\frac{n(n-1)(2n-1)}{3}+m^2n(2n+1)(n-1)-m^2\cdot\frac{n(n-1)(2n-1)}{3}\\
&+mn^2(n-1)(2m-4k-2)-m(2m-4k-2)\cdot\frac{n(n-1)(2n-1)}{3}
\end{aligned}
$$
----
实现时把含 $\pi$ 的项和常数项分开加处理即可 $O(1)$ ！注意 $m = 1$ 时圆心没有交点，所以不统计 $PART\ 1$ 。
## AC代码：
```cpp
#include<bits/stdc++.h>
using namespace std;
typedef long double db;

inline int read() {
	int f = 1, otto = 0;
	char a = getchar();
	while(!isdigit(a)) {
		if(f == '-') f = -1;
		a = getchar();
	}
	while(isdigit(a)) {
		otto = (otto << 1) + (otto << 3) + (a ^ 48);
		a = getchar();
	}
	return f * otto;
}

const db pi = 3.1415926535897932;

int main() {
	db n = read(), m = read(), ans1 = 0, ans2 = 0;
	const int k = int(2 * m / pi);
	//对圆心 
	if(m >= 2) ans2 += n * m * (n + 1);
	//对同一圆
	ans1 += 0.5 * n * k * (k + 1) * (n + 1);
	ans2 += n * m * (n + 1) * (2 * m - 2 * k - 1);
	//对内外圆
	ans1 += n * n * k * (k + 1) * (n - 1) - n * k * (k + 1) * (n - 1) * (2 * n - 1) / 3;
	ans2 += n * m * m * (n - 1) * (2 * n + 1) + n * n * m * (n - 1) * (2 * m - 4 * k - 2) - n * m * m * (n - 1) * (2 * n - 1) / 3 - 2 * n * m * (n - 1) * (2 * n - 1) * (m - 2 * k - 1) / 3;
	printf("%.10Lf", ans1 * pi + ans2);
} 
```
**特别感谢：同机房xwb倾情讲解的柿子\bx\bx**

---

## 作者：lailai0916 (赞：2)

## 原题链接

- [洛谷 P9827 [ICPC2020 Shanghai R] Sky Garden](https://www.luogu.com.cn/problem/P9827)

## 解题思路

[@Nuyoah_awa](https://www.luogu.com.cn/user/551108) 的 [题解](https://www.luogu.com.cn/article/ucxonbjp) 提供了 $O(n)$ 的做法。

观察发现其代码中的 DP 是线性的，经过整理可以 $O(1)$ 实现。

$$
O(n^3)\to O(1)
$$

令：

$$
t=\left\lfloor\frac{2m}{\pi}\right\rfloor
$$


则：

$$
p=\frac{t(t+1)\times n(n+1)(2n+1)}{6}
$$

$$
q=\frac{mn(n+1)(6mn-4tn-2t-2n-1+3\times[m\not=1])}{3}
$$

$$
S=p\pi+q
$$

至此，已成艺术。

接下来看看 [人工队](https://www.luogu.com.cn/article/xcv1fnch) 的表现。

## 参考代码

```cpp
#include <bits/stdc++.h>
using namespace std;

using ll=long long;
const double pi=acos(-1);
int main()
{
	ios::sync_with_stdio(false);
	cin.tie(nullptr);
	ll n,m;
	cin>>n>>m;
	ll t=m*2/pi;
	ll p=t*(t+1)*n*(n+1)*(n*2+1)/6;
	ll q=m*n*(n+1)*(m*n*6-t*n*4-t*2-n*2-1+(m>1)*3)/3;
	cout<<fixed<<setprecision(12)<<p*pi+q<<'\n';
	return 0;
}
```

---

## 作者：Y204335 (赞：2)

# \[ICPC2020 Shanghai R] Sky Garden

给个 $O(1)$ 的做法。

## 题目大意

有 $n$ 个半径从 $1$ 到 $n$ 的同心圆和 $m$ 条过圆心且平分这些圆（把每个圆都分为相等的 $2m$ 段弧）的直线，构成 $n+m$ 条道路，问所有道路的交叉点两两间最短距离的和。

## 题目分析

由于有 $\pi$，可能有精度问题，所以先将答案写成 $ans_1\pi+ans_2$ 的形式，最后再计算结果。

先考虑 $A\to B$ 什么时候距离最短（设 $A$ 所在圆的半径为 $a$，$B$ 所在圆的半径为 $b$，相隔 $k$ 段弧，钦定 $a\ge b$），有两种候选路径：先走到 $B$ 所在的圆，再走一段弧到 $B$；直接走到圆心，再走到 $B$。考虑两种路径的距离：

$$s_1=\left(a-b\right)+\frac{kb\pi}{m}$$

$$s_2=a+b$$

显然，当 $k<\frac{2m}{\pi}$ 时 $s_1<s_2$，当 $k>\frac{2m}{\pi}$ 时 $s_1>s_2$，分别考虑两种走法的贡献（设 $x=\left\lfloor\frac{2m}{\pi}\right\rfloor$）：

1. 对于每一个距离圆心 $c$ 的点 $C$（$c>0$），$C$ 会被所有与 $C$ 在同一射线且 $a\ge c$ 的 $A$ 经过，并且从 $C$ 可以到达 $2x+1$ 个点，对 $ans_1$ 的贡献为 $\left(n-c+1\right)\times2\times\sum_{i=1}^{x}\frac{ic}{m}$，对 $ans_2$ 的贡献为 $\left(2x+1\right)\times\sum_{i=1}^{n-c}i$。在同一个圆上共有 $2m$ 个 $C$，单个圆上的对 $ans_1$ 的贡献为 $c\left[2\left(n-c\right)+1\right]x\left(x+1\right)$（$A$ 和 $C$ 在同一圆上会把贡献算两遍，要减去），对 $ans_2$ 的贡献为 $2m\left(2x+1\right)\frac{\left(n-c+1\right)\left(n-c\right)}{2}$。

2. 对于每对 $A_1,A_2$（一个圆与一条直线的两个交点），在每个 $b$（$b\le a$）可以走到 $\left(m-x-1\right)\times 4+2$ 个 $B$（等下去重），对 $ans_2$ 的总贡献为 $\sum_{i=1}^{a}\left[\left(m-x-1\right)\times4+2\right]\left(a+i\right)$，同一圆上共有 $m$ 对，总贡献为 $m\times\left\{\sum_{i=1}^{a-1}\left[\left(m-x-1\right)\times4+2\right]\left(a+i\right)\right\}+\frac{\left[\left(m-x-2\right)\times4+1\right]\times2am}{2}$，化简得到对 $ans_2$ 的贡献为 $m\left[\left(m-x-1\right)\times4+2\right]\left[a^2+\frac{i\left(i-1\right)}{2}\right]$。

此外当 $m>1$ 时圆心会有交点，对 $ans_2$ 的贡献为 $\sum_{i=1}^{n}2mi$。

分别化简 $m=1$ 与 $m>1$ 的贡献式：

1. $m=1$:

$$\begin{aligned}ans_2&=\sum_{c=1}^{n}\left(2\times\sum_{i=1}^{c-1}c+i\right)+2c\\&=\sum_{c=1}^{n}2c\left(c-1\right)+\left(c-1\right)c+2c\\&=\sum_{c=1}^{n}4c^2-2c\\&=4\times\frac{2n^3+3n^2+n}{6}+2\times\frac{n\left(n+1\right)}{2}\\&=\frac{4n^3+3n^2-n}{3}\end{aligned}$$

2. $m>1$：

$$\begin{aligned}ans_1&=\sum_{c=1}^{n}c\left[2\left(n-c\right)+1\right]x\left(x+1\right)\\&=\sum_{c=1}^{n} x\left(x+1\right)\left[c^2+\left(2n-1\right)c\right]\\&= x\left(x+1\right)\left\{\left(\sum_{c=1}^{n}c^2\right)+\left[\left(2n-1\right)\sum_{c=1}^{n}c\right]\right\}\\&= x\left(x+1\right)\left[\frac{2n^3+3n^2+n}{6}+\left(2n-1\right)\frac{n\left(n+1\right)}{2}\right]\\&=\frac{\left(2n^3+3n^2+n\right)x^2+\left(2n^3+3n^2+n\right)x}{6}\end{aligned}$$

$$\begin{aligned}ans_2&=\left\{\sum_{c=1}^{n}2m\left(2x+1\right)\frac{\left(n-c+1\right)\left(n-c\right)}{2}+m\left[\left(m-x-1\right)\times4+2\right]\left[a^2+\frac{i\left(i-1\right)}{2}\right]\right\}+\sum_{i=1}^{n}2mi\\&=m\left(2x+1\right)\left(\sum_{c=1}^{n}c^2-c\right)+m\left[\left(m-x-1\right)\times2+1\right]\left(\sum_{c=1}^{n}3c^2-c\right)+2m\left(\sum_{i=1}^{n}i\right)\\&=m\left(2x+1\right)\left[\frac{2n^3+3n^2+n}{6}-\frac{n\left(n+1\right)}{2}\right]+m\left[\left(m-x-1\right)\times2+1\right]\left[\frac{2n^3+3n^2+n}{2}-\frac{n\left(n+1\right)}{2}\right]+2m\frac{n\left(n+1\right)}{2}\\&=\frac{6m^2n^2+2mn-\left(4mn^3+6mn^2+2mn\right)x-\left(2m-6m^2\right)n^3}{3}\end{aligned}$$

注：$\sum_{i=1}^{n}i^2$ 可用拉格朗日插值法计算出为 $\frac{2n^3+3n^2+n}{6}$，$\pi$ 可用 `acos(-1)` 来计算。

直接计算即可，时间复杂度 $O(1)$。

## 代码

```cpp
#include <bits/stdc++.h>
#define ll long long
using namespace std;
ll n, m, x, ans1, ans2, temp;
int main()
{
    ios::sync_with_stdio(0);
    cin.tie(nullptr);
    cin >> n >> m;
    if (m == 1) {
        ans2 = (4 * n * n * n + 3 * n * n - n) / 3;
        cout << ans2;
        return 0;
    }
    x = 1.0l * 2 * m / acos(-1);
    ans1 = (2 * n * n * n + 3 * n * n + n) * (x + 1) * x / 6;
    ans2 = (6 * m * m * n * n + 2 * m * n - (4 * m * n * n * n + 6 * m * n * n + 2 * m * n) * x - (2 * m - 6 * m * m) * n * n * n) / 3;
    cout << fixed << setprecision(20) << 1.0l * ans1 * acos(-1) + ans2;
    return 0;
}
```

---

## 作者：chen_zhe (赞：2)

以下内容转载自官方题解：

介绍一种 $O(n^3)$ 的做法，考虑从里到外第 $i$ 层，这层的每个节点都是一样的，所以我们统计其中一个对答案的贡献即可。那么对于第 $i$ 层的一个点，它到小于第 $i$ 层的点的最短路的第一步，一定是它往里走一层（在外面走圆环肯定比里面距离远）；它到第 $i$ 层的点的最短路，有两种情况，一种是直接走这层的圆环，另一种是往里先走一步，然后里面走一走，再钻出来，也就是说我们可以用第 $i-1$ 层的值来更新第 $i$ 层的值，dp 一下可以做到 $O(n^3)$。

这题其实可以直接 $O(1)$，大致来说就是往里走的每一层其实省的距离都是一样的，大家可以自己悟一悟！

---

## 作者：ycy1124 (赞：2)

前言：又是模考题，切了加强版的，上 $100$ 了 qwq。
### 题意
在平面上有 $n$ 个以 $(0,0)$ 为圆心的半径分别为 $1\sim n$ 的圆，还有 $m$ 条直线，每条直线都经过 $(0,0)$ 并且将每个圆分成等长的 $2\times m$ 条圆弧，对于圆与直线的交点集 $S$，求 $S$ 中任意两点之间**只能**经过圆弧或直线的距离最小和。
### 思路
考虑分讨，对于每两个点，他们可以直接通过一条圆弧或者直线直接到达的情况有两种，一种是在同一条圆弧上，一种是在同一条直线上。

1. 当这两个点在同一条直线上，他们的最小距离一定是 $dis_{i,j}=|x_i-x_j|$。
2. 当这两个点在同一条圆弧上，假定他们之间隔了 $k$ 份圆弧($k\le m$)，其 $dis_{i,j}=\min(\frac{2\times\pi\times r_i\times k}{2\times m},2\times r_i)$。
3. 当他们既不在同一条直线，也不在同一条圆弧上时，我们可以考虑先将他们移到同一条圆弧上然后再按照第二种情况计算。$dis_{i,j}=|x_i-x_j|+\min(\frac{2\times\pi\times r_i\times k}{2\times m},\frac{2\times\pi\times r_j \times k}{2\times m},2\times r_i,2\times r_j)$。

对于第二种情况的式子我们可以将它化简一下：
$$dis_{i,j}=\min(\frac{2\times\pi\times r_i\times k}{2\times m},2\times r_i)$$
$$dis_{i,j}=r_i\times\min(\frac{\pi\times k}{ m},2)$$
此时，$\min$ 式子内所有的变量被消到只剩一个 $k$ 了。我们可以利用这个式子，预处理出 $k$ 的最大值使得 $\frac{\pi\times k}{m}\le 2$。

由于在计算时直接计算 $\pi$ 很容易丢失精度，于是我们考虑先计算出答案的常数项与 $\pi$ 前面的系数最后在计算答案。

考虑如何计算系数，这里用 $sum_1$ 表示 $\pi$ 前面的系数，$sum_2$ 表示常数项。首先，我们可以提前将两个点移到一个圆上带来的贡献提前计算，不难发现他们移动一定是移动到小的圆上是最优的，于是这一段的贡献是：
```cpp
int w=(m+n*m)*n;//最初时原点距离所有点的距离总和
sum2+=w*(m>1);//加入有在原点的交点
for(int i=1;i<=n;i++){
  w-=(n-i+1)*2*m;//每次向外拓展一个圆
  sum2+=w*2*m;//加上贡献
}
```
然后我们考虑将点移至同一个圆之后的贡献计算。

由于是将点尽量的往内部移动，所以我们还是可以从内往外枚举计算贡献。对于一个点，我们发现与他一开始就在同一个圆上的点直接计算会需要进行容斥，而其他圆上后面移过来的点不需要，所以我们优先考虑从其他环上移过来的点。

首先考虑对于移过来以后与它之间的圆弧份数小于等于 $k$ 的其贡献将会要加到 $sum_1$ 中。对于第 $i$ 个环上的一点，移动过来后与其的距离份数 $1\sim k$ 的各有 $(n-i)\times 2$ 个,并且这个环上的每个点的这个贡献都是相同的，所以这里的计算式子是
$$
sum_1+=(n-i)\times 2\times (1+k)\times k\div 2 \times 2 \times i\div 2\div m \times 2 \times m
$$
化简一下：
$$
sum_1+=(n-i)\times (1+k)\times k\times i\times 2
$$
然后我们考虑转移过来之后距离大于 $k$ 的点。同上面的求法很容易得到这些点的个数是 $2\times m - 2\times k - 1$，计算式子就是：
$$
sum_2+=(2\times m -2\times k -1)\times 2 \times i
$$
接下来考虑在同一个环上的点并且距离小于等于 $k$。发现其只需要考虑向左距离小于等于 $k$ 的点就行了，因为是个环，最后会由右边的点将这份贡献加上，计算公式为：
$$
sum_1+=(1+k)\times k \times i\times 2\times m \div 2 \div m
$$
化简：
$$
sum_1+=(i+k)\times k\times i
$$
最后一种情况就是在同一个环上且距离大于 $k$ 的，这时我们可以发现只有当距离等于 $m$ 时对于每个点向左计算会重复计算一个，减去即可。计算公式为：
$$
2\times i\times (2\times m - 2\times k -1)\times m
$$
### 代码
```cpp
#include<bits/stdc++.h>
#define pi 3.141592654
#define int long long 
using namespace std;signed main(){
	int n,m;
	long long sum1=0,sum2=0;
	cin>>n>>m;
	int k=2*m/pi;
	int w=(m+n*m)*n;
	sum2+=w*(m>1);
	for(int i=1;i<=n;i++){
		w-=(n-i+1)*2*m;
		sum1+=(n-i)*(1+k)*k*2*i+(1+k)*k*i;
		sum2+=w*2*m;
		sum2+=(2*m-2*k-1)*2*m*2*i*(n-i)+2*i*(m*2-k*2-1)*m;
	}
	printf("%.10lf",pi*sum1+sum2);
	return 0;
}//NOIP2024 rp++
```
[AC 记录](https://www.luogu.com.cn/record/189758124)。

复杂度 $\mathcal{O}(n)$。

---

## 作者：Silvestorm (赞：2)

### 本蒟蒻（真）的第一篇题解，排版和解析多有不足，望包涵。
要轻松过这道题，需要弄清楚两个结论。

结论一：对于同一个圆上的不同的两个点，如果它们的弧长小于圆的直径，那么它们的最短路就是弧。

结论二：对于不同圆上的两个点，需要将离圆心远的点降到另一个点所在的圆上，然后依据结论1进行操作。

由这两个结论可以求出任意两个点的最短路。

例如。 ![一个n=3,m=2的图](https://cdn.luogu.com.cn/upload/image_hosting/ot3g38zs.png)
弧长BD为 $\lfloor 3\times 2\times Π\div 4 \rfloor$，比直径 $2\times 3$ 要短，所以  $dis(B,D)$ 的最短路是弧长BD。

而对于 $dis(B,F)$，对B降层到G，再按照结论一，可知   $dis(B,F)=dis(B,G)+dis(G,F)$。

接下来上代码。

```cpp
#include <bits/stdc++.h>
using namespace std;
long long n, m;
double ans = 0, sum = 0, average; // sum为一个圆上所有点对的最短距离之和
const double p = acos(-1);//这是Π
int main()
{
	cin >> n >> m;
	average = p / m;
	for (int i = 1; i <= m; i++)
	{
		if (average * i < 2)
			sum += average * i;
		else
			sum += 2;
	}
	sum = (sum * 2 - 2) * m;
	for (int i = 1; i <= n; i++)
	{
		ans += sum * i;
		for (int j = 1; j < i; j++)
		{
			ans += 4 * m * m * (i - j);
			ans += sum * 2 * j;
		}
	}
	if (m > 1)
		for (int i = 1; i <= n; i++)
		{
			ans += m * i * 2;
		}
	printf("%.10f", ans);
	return 0;
}
```
接下来是核心代码的解析。
![一个n=3,m=2的图](https://cdn.luogu.com.cn/upload/image_hosting/ot3g38zs.png)
```cpp
	average = p / m;
	for (int i = 1; i <= m; i++)
	{
		if (average * i < 2)
			sum += average * i;
		else
			sum += 2;
	}
	sum = (sum * 2 - 2) * m;
```

单位圆被分为 $2\times m$ 份，每份的弧长就是 $average$，后面计算只要乘半径就行。任取一个点，从某一边开始枚举第二个点，直到第 $m+1$ 个点。
```cpp
	for (int i = 1; i <= m; i++)
	{
		if (average * i < 2)//结论一
			sum += average * i;
		else
			sum += 2;//单位圆的直径
	}
  	 sum = (sum * 2 - 2) * m;
```

完全版 $sum$，因为诸如 $dis(B,C)$ 和 $dis(C,B)$ 本质一样，所以 $2\times sum$ 时要舍去一个，最后还要乘以 $m$ 才能枚举完这个圆上的所有点。

```cpp
	for (int i = 1; i <= n; i++)
	{
		ans += sum * i;
		for (int j = 1; j < i; j++)
		{
			ans += 4 * m * m * (i - j);
			ans += sum * 2 * j;
		}
	}
```
从最里层开始枚举，里面嵌套一个循环是为了计算所有位于该层圆的一个点与位于另一层（在里面）圆的另一个点的最短路之和。

 $4\times m\times m\times(i-j)$ 是外层点降层所要走的距离，$(2\times m)^2$ 是外层点与内层点的所有组合数，各位dalao都能理解吧。

例如 $dis(B,F)$ 和 $dis(E,G)$ 降层之后各有 $dis(G,F)$ 和 $dis(F,G)$，这两个并不能舍掉一个，所以 $sum\times 2\times j$ 中多乘了一个 $2$。

```cpp
	if (m > 1)
		for (int i = 1; i <= n; i++)
		{
			ans += m * i * 2;
		}
```
当 $m$ 至少为 $2$ 时，圆心才真正算得上是一个点，此时要加上圆心到其余各个点的距离。

---

## 作者：niuzh (赞：1)

### 重点思路

对于两个点，他们的最短路只有两种可能性：

- 两个点在同一个圆上，此时最短路为直径与弧线长度的最小值。

- 两点不在同一圆上，此时需将靠外的点走到靠内的点的圆上，让后跟第 $1$ 种相等。

剩下见代码：

### 代码

```cpp
/*
 * @FilePath: P9827 Sky Garden.cpp
 * @Author: niu-zh
 */
#include<bits/stdc++.h>
using namespace std;
const int N=500+10;
const double pi=3.1415926535897932384626433832795;
int main()
{
	double n,m,ans=0;
	cin>>n>>m;
	for (int i=1; i<=n; i++)
	{
		for (int j=i; j>=1; j--)//遍历两个圆，求出固定圆后的答案并累加。
		{
			double cnt=0;
			for (int k=1; k<m; k++)//求出离一个点与另一个圆上分别1~m-1个格的点的最短路。
			{
				cnt+=i-j+min(2.0*j,(1/(2*m)*k)*pi*j*2.0);
			}
			clog<<cnt<<endl;
			if (i==j)//如果两个圆是同一个
			{
				ans+=cnt*2*m;//会重复
				ans+=(i+j)*m;//i-j=0
			}
			else
			{
				ans+=cnt*4*m;//不会
				ans+=(i+j+i-j)*2*m;
			}
		}
		if(m!=1)
		{
			ans+=i*2*m;//到圆心
		}
	}
	cout<<fixed<<setprecision(10)<<ans;
	return 0;
}
```

---

## 作者：锦依卫小生 (赞：1)

# P9827
## 题意理解
第一眼看过去，我天，计算几何。仔细一看，发现都是同心圆，直线过圆心且等分圆，问题不那么复杂了。
## 做法
考虑点之间的距离有两种情况，同一圆上的距离与不同圆间点的距离。  
先考虑同一圆间点的情况。同一圆上的点之间的路径有两种可能。通过半径到达或者通过通过弧到达。列出计算公式，不难发现当两点到圆心连线夹角小于 $2$ 时，走弧上路径，否则走半径。将点分成两部分（前 $m$ 个与后 $m$ 个）对前 $m$ 个点，顺时针遍历算出它到其直径所对的另一边的点的距离和（弧上距离同样也是顺时针算）。对后 $m$ 个点，处理类似，只是不包括直径对应的点（否则重复计算）。最后我们发现，对不同半径的圆，我们算出的值与半径成正比例，那么不妨只计算其系数，然后乘上各个半径之和。  
对不同圆上的距离，我们从最外圆向最内圆考虑。每次计算该圆到其内部所有圆的所有点的距离和。我们发现，某一个圆上一个点到另一个圆上所有点的距离和，等于两圆间的距离加上内圆中一点到其它点的距离和。（即外圆上一点先沿半径下到内圆，后只考虑内圆间点距离）。而这里的距离和同样于半径成正比，系数可预先算好（从一点出发，计算后 $m-2$ 个点到它的距离，再把该值乘以 $2$ 加上直径）。
## 关于复杂度
担心 $O(n^{3})$ 被卡，所以写了个 $O(n^{2})$ 的。

## 代码
```cpp
#include<bits/stdc++.h>
using namespace std;
const long double pi=acos(-1.0);
int n,m;
long double sum,ans,s;
int main(){
	cin>>n>>m;
	for(int i=1;i<=m;++i){
		int k=1;
		long double res=0;
		while(k*pi/m<=2){
			res+=k*pi/m;
			k++;
		}
		res+=2*(m-(k-1));
		sum+=res;
	}
	
	for(int i=1;i<=m;++i){
		int k=1;
		long double res=0;
		while(k*pi/m<=2){
			res+=k*pi/m;
			k++;
		}
		res+=2*(m-1-(k-1));
		sum+=res;
	}
	
	int p=1;
	while(p*pi/m<=2){
		s+=p*pi/m;
		p++;
	}
	s+=2*(m-1-(p-1));
	s=s*2+2;
	
	ans+=(1+n)*n/2*sum;
	
	for(int i=n;i>=1;--i){
		for(int j=i-1;j>=1;--j){
			ans+=2*m*((i-j)*2*m+s*j);
		}
		if(m>1)
			ans+=2*m*i;//注意当只有一条直线的时候没有中心点。
	}
	printf("%.10Lf",ans);
}
```





---

## 作者：lzqy_ (赞：1)

好像做麻烦了，难过。

首先考虑对于任意两个点怎么计算答案。那么肯定是靠外的点先走到靠内的点的圆上，然后两个点再一起往内走 $k$ 步（$k$ 可能为 $0$），然后再走过对应的圆弧。

比较难搞的是一起往内走的部分。但观察到往内走时我们只关心当前在第几个圆以及两个点相差了几段。这是 $O(n^2)$ 个状态，可以先 $O(n^3)$ 预处理掉。

这样就能够 $O(1)$ 计算任意两点的距离了。不过这是 $O(n^4)$ 的，考虑优化。

随便取两条直线，尝试 $O(n)$ 计算它们的答案。枚举一条线上的点，若它在第 $i$ 个圆上，那么这个点的贡献为 $\sum\limits_j f_{d,\min(i,j)}+|i-j|$。$d$ 是两条线相差的格子，这关于两条直线是一个常数，而剩下的绝对值和 $\min$ 直接按照值域拆开，维护一下前缀和就好。

记得特判 $m=1$ 即点集不包含圆心的情况。

----

**extra:**

这玩意儿显然还有很多优化空间。

首先那个预处理的 DP 是可以递推的，那一部分可以优化到 $O(n^2)$。

计算答案时，本质不同的点对数量只有 $O(n)$ 个（因为一个点对所需要用到的信息只有 $d$，$d$ 是 $O(n)$ 级别的），所以这里又可以变成 $O(n^2)$。

不过 $n \le 500$ 所以就懒得写了。

据说还有 $O(1)$ 做法，挺厉害的。那估计需要观察向内走的特征了，不想思考。

--------

以下是 $O(n^3)$ 蠢笨代码。

```cpp
#include<bits/stdc++.h>
#define db double
using namespace std;
const int maxn=510;
const db PI=acos(-1.0);
int n,m;
db p1[maxn],p2[maxn];
db f[maxn][maxn];
db ans; 
void init(){
	for(int i=1;i<=m;i++)
		for(int j=1;j<=n;j++){
			f[i][j]=1e30;
			for(int k=0;k<=j;k++)
				f[i][j]=min(f[i][j],(PI/m*i)*k+2*(j-k));
		}
}
int main(){
	scanf("%d%d",&n,&m);
	//same line
	for(int i=1;i<=m;i++)
		for(int j=2;j<=n+n+1;j++)
			ans+=j*(j-1)/2;
	if(m==1){
		ans-=n*(n+1)/2;
		ans-=n*(n+1)/2;
		printf("%.10lf\n",ans);
		return 0;
	}
//	printf("!!!%.3lf\n",ans);
	//same-size
	init();
	for(int i=1;i<=m;i++)
		for(int j=i+1;j<=m;j++){
			if(i==j) continue;
			db sum=0; int d=min(j-i,i+m-j);
			for(int k=1;k<=n;k++){
				p1[k]=p1[k-1]+k;
				p2[k]=p2[k-1]+f[d][k];
			}
			for(int k=1;k<=n;k++){
				sum+=p2[k]+k*k-p1[k];
				sum+=(n-k)*f[d][k]+(p1[n]-p1[k])-(n-k)*k;
			}	
			ans+=sum*2;		
		}
	//dif-size
	for(int i=1;i<=m;i++)
		for(int j=i+1;j<=m;j++){
			if(i==j) continue;
			db sum=0; int d=max(j-i,i+m-j);
			for(int k=1;k<=n;k++){
				p1[k]=p1[k-1]+k;
				p2[k]=p2[k-1]+f[d][k];
			}
			for(int k=1;k<=n;k++){
				sum+=p2[k]+k*k-p1[k];
				sum+=(n-k)*f[d][k]+(p1[n]-p1[k])-(n-k)*k;
			}	
			ans+=sum*2;
		}
	printf("%.10lf\n",ans);
	return 0;
}
```

---

## 作者：Mrkn_chenyx12 (赞：0)

这道题的出题人非常良心，只要是时间复杂度在 $O(n^3)$ 以内的算法就能通过，然而事实上这道题可以做到 $O(1)$，本篇题解是 $O(1)$ 算法。

## 解题思路

### 1. 特殊情况

我们特殊处理 $m=1$ 的情况，因为此时中心点不是交点之一。共有 $2n$ 个点分布在同一条直线上，除第 $n$ 个点和第 $n+1$ 的点间隔为 $2$ 以外，相邻的点间隔均为 $1$。不妨视那条特殊的线段的长度也为 $1$，最后再加上路径包含这条线段的点对数量。所以，我们可以很容易地推断出答案为：

$$
n^2+\sum_{i=1}^{2n-1}i(2n-i)
$$

经过化简，可以得到如下的式子：

$$
n^2-\frac{n(2n-1)(4n-1)}{3}+2n^2(2n-1)
$$

### 2. 一般情况

剩下的情况中，我们视 $m$ 条直线为 $2m$ 条端点为中心点的射线。另外，由于路径只经过圆弧和长度为整数的线段，不妨设答案为 $p\pi+q$。

特殊处理两点在同一射线上（包括其中一点在中心点上）的情况，不难得到此部分答案 $q_1$ 为：

$$
\begin{aligned}
q_1&=2m\sum_{i=1}^ni(n-i+1)\\
&=2m(\frac{n(n+1)^2}{2}-\frac{n(n+1)(2n+1)}{6})\\
&=mn(n+1)^2-\frac{mn(n+1)(2n+1)}{3}
\end{aligned}
$$

然后，考虑将其余情况分为**两点在同圆上**的和**两点不在同圆上**的。

对于**两点在同圆上**的情况，可以证明最优路径一定是**两点之间的劣弧**和**中心点与两点之间的两条线段**这两种情况之一。如果两点之间的劣弧隔了 $x-1$ 个点，或者说 $x$ 段长度为 $\frac{\pi r}{m}$ 的弧，那么两种情况的代价分别是 $\frac{x\pi r}{m}$ 和 $2r$。不难发现哪种更优仅与 $x$ 有关。由此，设 $k$ 表示当 $x\geq k$ 时后者更优，否则前者更优。此处的 $k$ 可以在 $O(1)$ 的时间复杂度内求得其值为 $\lceil\frac{2m}{\pi}\rceil$。

考虑在半径为 $r$ 的圆上的情况，两两点对之间最优路径的长度和为 $a_r\pi+b_r$，其中：

$$
a_r=\frac{1}{2}\times2m\times2\sum_{i=1}^{k-1}\frac{ir}{m}=kr(k-1)\\
b_r=\frac{1}{2}\times2m\times(2m-2k+1)\times 2r=2mr(2m-2k+1)
$$

考虑**两点不在同圆上**的情况，可以证明先让处于更外侧的圆上的点向内走到另一个点所在的圆上，然后按照两点在同圆上的方法做一定是最优的。

因此，枚举两点所在的圆，一定有 $2n-2r+1$ 种情况使得最后按照两点都在半径为 $r$ 的圆上的情况做，那么忽略两点不在同圆的情况中外侧圆上的点走向内侧圆的代价，总代价为 $p\pi+q_2$，其中：

$$
\begin{aligned}
p&=\sum_{i=1}^ni(2n-2i+1)a_i\\
&=\sum_{i=1}^nik(2n-2i+1)(k-1)\\
&=k\sum_{i=1}^n(2-2k)i^2+(2n+1)(k-1)i\\
&=\frac{nk(n+1)(2n+1)(1-k)}{3}+\frac{nk(n+1)(2n+1)(k-1)}{2}\\
&=\frac{nk(n+1)(2n+1)(k-1)}{6}
\end{aligned}\\
\begin{aligned}
q_2&=\sum_{i=1}^ni(2n-2i+1)b_i\\
&=\sum_{i=1}^n2im(2n-2i+1)(2m-2k+1)\\
&=2m\sum_{i=1}^n(4k-4m-2)i^2+(2m-2k+1)(2n+1)i\\
&=2m(\frac{n(n+1)(2n+1)(2k-2m-1)}{3}+\frac{n(n+1)(2n+1)(2m-2k+1)}{2})\\
&=\frac{mn(n+1)(2n+1)(2m-2k+1)}{3}
\end{aligned}
$$

再考虑两点不在同圆的情况中外侧圆上的点走向内侧圆的代价 $q_3$，考虑枚举内外两圆，任取不在同一射线上的点对，故其为：

$$
\begin{aligned}
q_3&=\frac{1}{2}\times2m\times(2m-1)\times\sum_{i=1}^n\sum_{j=i+1}^n(j-i)\\
&=m(2m-1)\sum_{i=1}^n(n-i)(n-i+1)\\
&=m(2m-1)\sum_{i=0}^{n-1}i(i+1)\\
&=m(2m-1)\sum_{i=1}^ni(i-1)\\
&=\frac{m(2m-1)(n(n+1)(2n+1)-3n(n+1))}{3}\\
&=\frac{mn(2m-1)(n+1)(n-1)}{3}
\end{aligned}
$$

综上所述，答案 $p\pi+q$ 至此已经可以在 $O(1)$ 的时间复杂度内计算完毕。其中 $q$ 可以由前面的 $q_1+q_2+q_3$ 得到，具体为：

$$
\begin{aligned}
q&=q_1+q_2+q_3\\
&=\frac{1}{3}mn(n+1)(3(n+1)-(2n+1)+(2n+1)(2m-2k+1)+(n-1)(2m-1))\\
&=\frac{1}{3}mn(n+1)(3(n+1)+2(2n+1)(m-k)+(n-1)(2m-1))
\end{aligned}
$$

## 参考代码

```cpp
#define _USE_MATH_DEFINES

#include <bits/stdc++.h>
using namespace std;

int main() {
    long long n, m;
    scanf("%lld %lld", &n, &m);
    if (m == 1) {
        printf("%lld\n", n * n - n * (2 * n - 1) * (4 * n - 1) / 3 + 2 * n * n * (2 * n - 1));
        return 0;
    }
    long long k = ceil(2 * m / M_PI);
    long long p = n * (n + 1) * (2 * n + 1) / 6 * k * (k - 1);
    long long q = m * n * (n + 1) * (3 * (n + 1) + 2 * (2 * n + 1) * (m - k) + (n - 1) * (2 * m - 1)) / 3;
    printf("%.10lf\n", p * M_PI + q);
    return 0;
}
```

---

## 作者：sintle (赞：0)

## 题目链接

- [洛谷 P9827 [ICPC2020 Shanghai R] Sky Garden](https://www.luogu.com.cn/problem/P9827)

## 解题思路

本题的 $O(n)$ 做法已有，不多说。

[@lailai0916](https://www.luogu.com.cn/user/455474) 在他的[题解](https://www.luogu.com.cn/article/tidjp770)中给出了使用数学工具进行归纳的 $O(1)$ 做法，十分优雅，下面来看看人工队的表现。

设点 $a$ 在第 $a_i$ 个圆上，点 $b$ 在第 $b_i$ 个圆上，二者之间相隔 $x$ 条直线（包括点 $b$ 所在的直线，不包括点 $a$ 所在的直线），$p$ 为 $\left\lceil\dfrac{2m}{\pi}\right\rceil$。

因此 $dis({a,b})=\displaystyle\min_{i=1}^{n}|a_i-i|+|b_i-i|+\dfrac{\pi ix}{m}$

所以此时题目要求的就是：

$$
\displaystyle\sum_{a_i=0}^{n}\sum_{b_i=0}^{n}\sum_{x=0}^{2m}\min_{i=0}^{n}(|a_i-i|+|b_i-i|+\dfrac{\pi ix}{m})\times 2m
$$

我们注意到，$i$ 必定小于等于 $\min(a_i,b_i)$，并且两点之间的最短路一定是经过圆心或者只经过一条线段再经过一条圆弧（仅取决于两个点所在直线的角度大小）的，于是我们就得到：

$$
\begin{aligned}
  	ans &= 
  		4m\times
        \sum_{a_i=1}^{n}\sum_{b_i=a_i+1}^{n}\sum_{x=1}^{m-1}\begin{cases}
        a_i+b_i & \dfrac{\pi x}{m}>2 \\
        b_i-a_i+\dfrac{\pi a_ix}{m} & \dfrac{\pi x}{m}<2
        \end{cases}
        +2m\times\sum_{a_i=1}^{n}\sum_{b_i=a_i+1}^{n}2b_i
        +\sum_{b_i=1}^{n}b_i\times2m
        +2m\times
        \sum_{a_i=1}^{n}\sum_{x=1}^{m-1}\begin{cases}
        2a_i & \dfrac{\pi x}{m}>2 \\
        \dfrac{\pi a_ix}{m} & \dfrac{\pi x}{m}<2
        \end{cases}
        +2m\times\sum_{a_i=1}^{n}a_i \\
  	&= 
  		2m\times(
        2\times\sum_{a_i=1}^{n}\sum_{b_i=a_i+1}^{n}\sum_{x=1}^{m-1}\begin{cases}
        a_i+b_i & \dfrac{\pi x}{m}>2 \\
        b_i-a_i+\dfrac{\pi a_ix}{m} & \dfrac{\pi x}{m}<2
        \end{cases}
        +\sum_{a_i=1}^{n}\sum_{b_i=a_i+1}^{n}2b_i
        +\sum_{b_i=1}^{n}b_i
        +\sum_{a_i=1}^{n}\sum_{x=1}^{m-1}\begin{cases}
        2a_i & \dfrac{\pi x}{m}>2 \\
        \dfrac{\pi a_ix}{m} & \dfrac{\pi x}{m}<2
        \end{cases}
        +\sum_{a_i=1}^{n}a_i) \\
  	&=
    	2m\times(
        2\times(
        \sum_{a_i=1}^{n}\sum_{b_i=a_i+1}^{n}\sum_{x=1}^{p-1}(b_i-a_i+\dfrac{\pi a_ix}{m})
        +\sum_{a_i=1}^{n}\sum_{b_i=a_i+1}^{n}\sum_{x=p}^{m-1}(a_i+b_i))
        +\sum_{a_i=1}^{n}\sum_{b_i=a_i+1}^{n}2b_i
        +\sum_{b_i=1}^{n}b_i
        +\sum_{a_i=1}^{n}\sum_{x=1}^{p-1}\dfrac{\pi a_ix}{m}
        +\sum_{a_i=1}^{n}\sum_{x=p}^{m-1}2a_i
        +\sum_{a_i=1}^{n}a_i) \\
\end{aligned}
$$

- 然后开始化简：

$$
\begin{aligned}
\sum_{a_i=1}^{n}\sum_{b_i=a_i+1}^{n}\sum_{x=1}^{p-1}(b_i-a_i+\dfrac{\pi a_ix}{m})
	&=
    	\sum_{a_i=1}^{n}\sum_{b_i=a_i+1}^{n}\sum_{x=1}^{p-1}\dfrac{\pi a_ix}		
    	{m}+\sum_{a_i=1}^{n}\sum_{b_i=a_i+1}^{n}\sum_{x=1}^{p-1}(b_i-a_i)\\
  	&=
    	\dfrac{\pi}{m}\sum_{a_i=1}^{n}\sum_{b_i=a_i+1}^{n}\sum_{x=1}^{p-1}a_ix
    	+\sum_{a_i=1}^{n}\sum_{b_i=a_i+1}^{n}\sum_{x=1}^{p-1}(b_i-a_i)\\
  	&=
    	\dfrac{\pi}{m}\sum_{a_i=1}^{n}a_i\sum_{b_i=a_i+1}^{n}\sum_{x=1}^{p-1}x
    	+\sum_{a_i=1}^{n}\sum_{b_i=a_i+1}^{n}\sum_{x=1}^{p-1}(b_i-a_i)\\
  	&=
  		\dfrac{\pi}{m}\sum_{a_i=1}^{n}a_i\dfrac{p(n-a_i)(p-1)}{2}
    	+\sum_{a_i=1}^{n}\sum_{b_i=a_i+1}^{n}\sum_{x=1}^{p-1}(b_i-a_i)\\
\end{aligned}
$$

- 分别化简：

$$
\begin{aligned}
  	\dfrac{\pi}{m}\sum_{a_i=1}^{n}a_i\dfrac{p(n-a_i)(p-1)}{2}
  	&=
  		\dfrac{\pi}{2m}\sum_{a_i=1}^{n}a_ip(n-a_i)(p-1) \\
  	&=
  		\dfrac{\pi}{2m}\sum_{a_i=1}^{n}(a_in-a_i^2)(p^2-p) \\
  	&=
  		\dfrac{\pi(p^2-p)}{2m}\sum_{a_i=1}^{n}a_in-a_i^2 \\
  	&=
  		\dfrac{\pi(p^2-p)}{2m}(\sum_{a_i=1}^{n}a_in-\sum_{a_i=1}^{n}a_i^2) \\
  	&=
  		\dfrac{\pi(p^2-p)}{2m}(\dfrac{n^2(n+1)}{2}-\dfrac{n(n+1)(2n+1)}{6}) \\
  	&=
  		\dfrac{\pi(p^2-p)}{2m}(\dfrac{3n^2(n+1)-n(n+1)(2n+1)}{6}) \\
  	&=
  		\dfrac{(p^2-p)(3n^2(n+1)-n(n+1)(2n+1))\pi}{12m} \\
  	&=
  		\dfrac{(p^2-p)(3n^3+3n^2-n(2n^2+3n+1))\pi}{12m} \\
  	&=
  		\dfrac{(p^2-p)(3n^3+3n^2-2n^3-3n^2-n)\pi}{12m} \\
  	&=
  		\dfrac{(p^2-p)(n^3-n)\pi}{12m} \\
\end{aligned}
$$

$$
\begin{aligned}
\sum_{a_i=1}^{n}\sum_{b_i=a_i+1}^{n}\sum_{x=1}^{p-1}(b_i-a_i)
	&=
    	(p-1)\sum_{a_i=1}^{n}\sum_{b_i=a_i+1}^{n}(b_i-a_i)\\
  	&=
    	(p-1)(\sum_{a_i=1}^{n}\sum_{b_i=a_i+1}^{n}b_i-\sum_{a_i=1}^{n}\sum_{b_i=a_i+1}^{n}a_i)\\
  	&=
    	(p-1)(\sum_{a_i=1}^{n}\dfrac{(n-a_i)(a_i+n+1)}{2}-\sum_{a_i=1}^{n}\sum_{b_i=a_i+1}^{n}a_i)\\
  	&=
  		(p-1)(\dfrac{\sum_{a_i=1}^{n}(n^2+n-a_i^2-a_i)}{2}-\sum_{a_i=1}^{n}\sum_{b_i=a_i+1}^{n}a_i)\\
  	&=
  		(p-1)(\dfrac{\sum_{a_i=1}^{n}n^2+\sum_{a_i=1}^{n}n-\sum_{a_i=1}^{n}a_i^2
  		-\sum_{a_i=1}^{n}a_i}{2}-\sum_{a_i=1}^{n}\sum_{b_i=a_i+1}^{n}a_i)\\
  	&=
  		(p-1)(\dfrac{n^3+n^2-\dfrac{n(n+1)(2n+1)}{6}
  		-\dfrac{n(n+1)}{2}}{2}-\sum_{a_i=1}^{n}\sum_{b_i=a_i+1}^{n}a_i)\\
  	&=
  		(p-1)(\dfrac{6n^3+6n^2-n(n+1)(2n+1)
  		-3n(n+1)}{12}-\sum_{a_i=1}^{n}\sum_{b_i=a_i+1}^{n}a_i)\\
  	&=
  		(p-1)(\dfrac{6n^3+6n^2-n(n+1)(2n+1)-3n(n+1)}{12}
  		-\sum_{a_i=1}^{n}a_i(n-a_i))\\
  	&=
  		(p-1)(\dfrac{6n^3+6n^2-n(n+1)(2n+1)-3n(n+1)}{12}
  		-\sum_{a_i=1}^{n}a_in-a_i^2)\\
  	&=
  		(p-1)(\dfrac{6n^3+6n^2-n(n+1)(2n+1)-3n(n+1)}{12}
  		-\sum_{a_i=1}^{n}a_in+\sum_{a_i=1}^{n}a_i^2)\\
  	&=
  		(p-1)(\dfrac{6n^3+6n^2-n(n+1)(2n+1)-3n(n+1)}{12}
  		-\dfrac{n^2(n+1)}{2}+\dfrac{n(n+1)(2n+1)}{6})\\
  	&=
  		(p-1)(\dfrac{6n^3+6n^2-n(n+1)(2n+1)-3n(n+1)}{12}
  		-\dfrac{6n^2(n+1)}{12}+\dfrac{2n(n+1)(2n+1)}{12})\\
  	&=
  		(p-1)(\dfrac{6n^3+6n^2-n(n+1)(2n+1)-3n(n+1)
  		-6n^2(n+1)+2n(n+1)(2n+1)}{12})\\
  	&=
  		(p-1)(\dfrac{6n^3+6n^2-3n^2-3n-6n^3-6n^2+n(2n^2+3n+1)}{12})\\
  	&=
  		(p-1)(\dfrac{6n^3+6n^2-3n^2-3n-6n^3-6n^2+2n^3+3n^2+n}{12})\\
  	&=
  		(p-1)(\dfrac{n^3-n}{6})\\
\end{aligned}
$$

- 合并回原式：

$$
\begin{aligned}
\sum_{a_i=1}^{n}\sum_{b_i=a_i+1}^{n}\sum_{x=1}^{p-1}(b_i-a_i+\dfrac{\pi a_ix}{m})
	&=
    	\dfrac{(p^2-p)(n^3-n)\pi}{12m}+(p-1)(\dfrac{n^3-n}{6})\\
  	&=
    	(p-1)(\dfrac{p(n^3-n)\pi}{12m}+\dfrac{n^3-n}{6})\\
  	&=
    	(p-1)(\dfrac{p(n^3-n)\pi}{12m}+\dfrac{2m(n^3-n)}{12m})\\
  	&=
    	(p-1)(\dfrac{p(n^3-n)\pi+2m(n^3-n)}{12m})\\
    &=
    	(p-1)(n^3-n)(\dfrac{p\pi+2m}{12m})\\
\end{aligned}
$$

- 化简 $\sum_{a_i=1}^{n}\sum_{b_i=a_i+1}^{n}\sum_{x=p}^{m-1}(a_i+b_i))$：

$$
\begin{aligned}
\sum_{a_i=1}^{n}\sum_{b_i=a_i+1}^{n}\sum_{x=p}^{m-1}(a_i+b_i)
	&=
    	(m-p)\sum_{a_i=1}^{n}\sum_{b_i=a_i+1}^{n}(a_i+b_i)\\
  	&=
    	(m-p)(\sum_{a_i=1}^{n}\sum_{b_i=a_i+1}^{n}a_i+\sum_{a_i=1}^{n}\sum_{b_i=a_i+1}^{n}b_i)\\
  	&=
    	(m-p)(\dfrac{n^2(n+1)}{2}-\dfrac{n(n+1)(2n+1)}{6}+\dfrac{6n^3+6n^2-n(n+1)(2n+1)-3n(n+1)}{12})\\
  	&=
    	(m-p)(\dfrac{6n^2(n+1)}{12}-\dfrac{2n(n+1)(2n+1)}{12}+\dfrac{6n^3+6n^2-n(n+1)(2n+1)-3n(n+1)}{12})\\
    &=
    	(m-p)\dfrac{6n^2(n+1)-2n(n+1)(2n+1)+6n^3+6n^2-n(n+1)(2n+1)-3n(n+1)}{12}\\
    &=
    	(m-p)\dfrac{6n^3+6n^2-3n(2n^2+3n+1)+6n^3+6n^2-3n^2-3n}{12}\\
    &=
    	(m-p)\dfrac{6n^3+6n^2-3n(2n^2+3n+1)+6n^3+6n^2-3n^2-3n}{12}\\
    &=
    	(m-p)\dfrac{6n^3+6n^2-6n^3-9n^2-3n+6n^3+6n^2-3n^2-3n}{12}\\
    &=
    	(m-p)\dfrac{n^3-n}{2}\\
\end{aligned}
$$

化简 $\sum_{a_i=1}^{n}\sum_{b_i=a_i+1}^{n}2b_i$：
$$
\begin{aligned}
\sum_{a_i=1}^{n}\sum_{b_i=a_i+1}^{n}2b_i
	&=
    	2\sum_{a_i=1}^{n}\sum_{b_i=a_i+1}^{n}b_i\\
  	&=
    	\dfrac{6n^3+6n^2-n(n+1)(2n+1)-3n(n+1)}{6}\\
  	&=
    	\dfrac{6n^3+6n^2-2n^3-3n^2-n-3n^2-3n}{6}\\
  	&=
    	\dfrac{4n^3-4n}{6}\\
    &=
    	\dfrac{2n^3-2n}{3}\\
\end{aligned}
$$

化简 $\sum_{b_i=1}^{n}b_i$：
$$
\begin{aligned}
\sum_{b_i=1}^{n}b_i
	&=
    	\dfrac{n(n+1)}{2}\\
\end{aligned}
$$

- 化简 $\sum_{a_i=1}^{n}\sum_{x=1}^{p-1}\dfrac{\pi a_ix}{m}$：
  $$
  \begin{aligned}
  \sum_{a_i=1}^{n}\sum_{x=1}^{p-1}\dfrac{\pi a_ix}{m}
  	&=
      	\dfrac{\pi}{m}\sum_{a_i=1}^{n}a_i\sum_{x=1}^{p-1}x\\
    	&=
      	\dfrac{\pi}{m}\sum_{a_i=1}^{n}a_i\sum_{x=1}^{p-1}x\\
    	&=
      	\dfrac{\pi}{m}\sum_{a_i=1}^{n}a_i\dfrac{p(p-1)}{2}\\
    	&=
      	\dfrac{p(p-1)\pi}{2m}\sum_{a_i=1}^{n}a_i\\
      &=
      	\dfrac{n(n+1)p(p-1)\pi}{4m}\\
  \end{aligned}
  $$

- 化简 $\sum_{a_i=1}^{n}\sum_{x=p}^{m-1}2a_i$：
  $$
  \begin{aligned}
  \sum_{a_i=1}^{n}\sum_{x=p}^{m-1}2a_i
  	&=
      	2\sum_{a_i=1}^{n}\sum_{x=p}^{m-1}a_i\\
    	&=
      	2(m-p)\sum_{a_i=1}^{n}a_i\\
    	&=
      	(m-p)n(n+1)\\
  \end{aligned}
  $$

- 化简 $\sum_{a_i=1}^{n}a_i)$：
  $$
  \begin{aligned}
  \sum_{a_i=1}^{n}a_i
  	&=
      	\dfrac{n(n+1)}{2}\\
  \end{aligned}
  $$

- 全部代入回原式：
  $$
  \begin{aligned}
  ans 
    	&=
      	2m\times(
          2\times(
          \sum_{a_i=1}^{n}\sum_{b_i=a_i+1}^{n}\sum_{x=1}^{p-1}(b_i-a_i+\dfrac{\pi a_ix}{m})
          +\sum_{a_i=1}^{n}\sum_{b_i=a_i+1}^{n}\sum_{x=p}^{m-1}(a_i+b_i))
          +\sum_{a_i=1}^{n}\sum_{b_i=a_i+1}^{n}2b_i
          +\sum_{b_i=1}^{n}b_i
          +\sum_{a_i=1}^{n}\sum_{x=1}^{p-1}\dfrac{\pi a_ix}{m}
          +\sum_{a_i=1}^{n}\sum_{x=p}^{m-1}2a_i
          +\sum_{a_i=1}^{n}a_i) \\
      &=
      	2m\times(
      	2\times((p-1)(n^3-n)(\dfrac{p\pi+2m}{12m})
      	+(m-p)\dfrac{n^3-n}{2})
      	+\dfrac{2n^3-2n}{3}
      	+\dfrac{n(n+1)}{2}
      	+\dfrac{n(n+1)p(p-1)\pi}{4m}
      	+(m-p)n(n+1)
      	+\dfrac{n(n+1)}{2})\\
      &=
      	2m\times(
      	(p-1)(n^3-n)(\dfrac{p\pi+2m}{6m})
      	+(m-p)(n^3-n)
      	+\dfrac{2n^3-2n}{3}
      	+\dfrac{n(n+1)}{2}
      	+\dfrac{n(n+1)p(p-1)\pi}{4m}
      	+(m-p)n(n+1)
      	+\dfrac{n(n+1)}{2})\\
      &=
      	\dfrac{1}{6}(
      	2(p-1)(n^3-n)(p\pi+2m)
      	+12m(m-p)(n^3-n)
      	+4m(2n^3-2n)
      	+6mn(n+1)
      	+3n(n+1)p(p-1)\pi
      	+12m(m-p)n(n+1)
      	+6mn(n+1))\\
      &=
      	\dfrac{1}{6}(
      	2(p-1)(pn^3\pi+2mn^3-pn\pi-2mn)
      	+12m(mn^3-mn-pn^3+pn)
      	+8mn^3-8mn
      	+6mn^2+6mn
      	+3np(np-n+p-1)\pi
      	+12mn(mn+m-pn-p)
      	+6mn^2+6mn)\\
      &=
      	\dfrac{1}{6}(
      	2(p^2n^3\pi+2pmn^3-p^2n\pi-2pmn-pn^3\pi-2mn^3+pn\pi+2mn)
      	+12m^2n^3-12m^2n-12pmn^3+12pmn
      	+8mn^3-8mn
      	+6mn^2+6mn
      	+(3n^2p^2-3n^2p+3np^2-3np)\pi
      	+12m^2n^2+12m^2n-12pmn^2-12pmn
      	+6mn^2+6mn)\\
      &=
      	\dfrac{1}{6}(
      	2p^2n^3\pi
      	+4pmn^3
      	-2p^2n\pi
      	-4pmn
      	-2pn^3\pi
      	-4mn^3
      	+2pn\pi
      	+4mn
      	+12m^2n^3
      	-12m^2n
      	-12pmn^3
      	+12pmn
      	+8mn^3-8mn
      	+6mn^2+6mn
      	+(3n^2p^2-3n^2p+3np^2-3np)\pi
      	+12m^2n^2
      	+12m^2n
      	-12pmn^2
      	-12pmn
      	+6mn^2
      	+6mn)\\
      &=
      	\dfrac{1}{6}(
      	4pmn^3
      	-4pmn
      	-4mn^3
      	+4mn
      	+12m^2n^3
      	-12m^2n
      	-12pmn^3
      	+12pmn
      	+8mn^3-8mn
      	+6mn^2+6mn
      	+12m^2n^2
      	+12m^2n
      	-12pmn^2
      	-12pmn
      	+6mn^2
      	+6mn
      	+(3n^2p^2-3n^2p+3np^2-3np)\pi
      	+2p^2n^3\pi
      	-2p^2n\pi
      	-2pn^3\pi
      	+2pn\pi)\\
      &=
      	\dfrac{1}{6}(4mn^3-8pmn^3-4pmn+8mn+12m^2n^3+12mn^2+12m^2n^2-12pmn^2
      	+(3n^2p^2-3n^2p+np^2-np+2p^2n^3-2pn^3)\pi)\\
  \end{aligned}
  $$

- 最后得出结论：

$$
q=\dfrac{1}{6}(4mn^3-8pmn^3-4pmn+8mn+12m^2n^3+12mn^2+12m^2n^2-12pmn^2)
$$

$$
p=\dfrac{1}{6}(3n^2p^2-3n^2p+np^2-np+2p^2n^3-2pn^3)
$$

## 参考代码

```cpp
#include <bits/stdc++.h>
using namespace std;

long long n , m;
inline long long tw(long long x) return x * x;
inline long long th(long long x) return x * x * x;

int main()
{
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    cin >> n >> m;
    long long p = 2 * m / acos(-1) + 1 , p , q;
    q = ((4 * m * th(n) - 8 * p * m * th(n) - 4 * p * m * n + 8 * m * n + 12 * tw(m) * th(n) + 12 * m * tw(n) + 12 * tw(m) * tw(n) - 12 * p * m * tw(n)) / 6 - ((m * n) * (n + 1)) * (m == 1));
    p = ((3 * tw(n) * tw(p) - 3 * tw(n) * p + n * tw(p) - n * p + 2 * tw(p) * th(n) - 2 * p * th(n)) / 6);
    cout << fixed << setprecision(12) << p * acos(-1) + q << '\n';
    return 0;
}
```

---

