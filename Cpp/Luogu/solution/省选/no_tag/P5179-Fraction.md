# Fraction

## 题目描述

给你四个正整数 $a,\,b,\,c,\,d$ ，求一个最简分数 $\frac{p}{q}$ 满足 $\frac{a}{b} < \frac{p}{q} < \frac{c}{d}$。

若有多组解，输出 $q$ 最小的一组，若仍有多组解，输出 $p$ 最小的一组。

## 说明/提示

|测试点编号|数据组数|$a,b,c,d$|
|:-:|:-:|:-:|
|$1 \sim 3$|$\leqslant 100$|$\leqslant 100$|
|$4 \sim 10$|$\leqslant 500$|$\leqslant 10^9$|

数据保证至少存在一个最简分数符合条件。

## 样例 #1

### 输入

```
1 3 1 2
2 1 3 1
2 1 4 1
1000 1001 1001 1002
```

### 输出

```
2/5
5/2
3/1
2001/2003```

# 题解

## 作者：derta (赞：66)

## 前言（闲话）

我在题解区看到这样一句话：

> 本题乍一看很简单：这不就是小学数学题吗……

其实这位老哥说得对，这确实是一道小学奥数题。那时我所见的题面是这样的：

> 求 $p+q$ 最小的整数 $(p,q)$ 使得 $\dfrac{p}{q}$ 前几位为 $3.14$

它相当于 $a=314,b=100,c=315,d=100$ 的情况，并且正解也是迭代。当时觉得这个做法很美妙，遂将其改写成 OI 题的形式，并写了（错误的）std。这也就成为了我题库中的第一道题。

## 题解

建议：看一步之后自己向下思考，不会了再继续看

不妨考虑一个例子：

$$\frac{314}{100}<\frac{p}{q}<\frac{315}{100}$$

首先看这个假分数就不顺眼，统一减 $3$！

$$\frac{14}{100}<\frac{p-3q}{q}<\frac{15}{100}$$

看这个分子上的 $p-3q$ 也不顺眼，换元，令 $r=p-3q$！

$$\frac{14}{100}<\frac{r}{q}<\frac{15}{100}$$

之后就又回到了题目的形式，但是两边变成了真分数，怎么办？

这是关键的一步，请务必自行思考。

（其实有些初联题也用到了类似的套路，可能让 MOer 来做更好一点）

答案是：取倒数。由此得到

$$\frac{100}{15}<\frac{q}{r}<\frac{100}{14}$$

之后用类似的方法迭代：

$$\frac{10}{15}<\frac{q-6r}{r}<\frac{15}{14}$$

等等，一边是真分数，一边是假分数，这又该怎么办？

其实已经结束了。可以发现，$q-6r=1,r=1$ 是最优解，回溯：

$$q-6r=1 \Longrightarrow q=7$$

$$p-3q=r \Longrightarrow p=22$$

至此，我们得出答案。

但是还有关键性的一步没有解决：该问题是否满足最优子结构？证明附于文末，请读者自行思考。

至于代码，有些题解分类比较繁琐，其实可以像求 $\gcd$ 一样合并在一起。时间复杂度的分析也与 $\gcd$ 相同，单次 $O(\log n)$。

```cpp
void gcd(int a, int b, int& p, int& q, int c, int d) {
	if(a < b && c > d) //边界情况
		p = 1, q = 1;
	else {
		gcd(d%c, c, q, p, b - (d/c)*a, a); //真分数-（取倒数）->假分数-（化简）->真分数。类似gcd，如果进来的是假分数会取倒数变成真分数，不会死循环
		q += (d/c)*p; //回溯时反解出q
	}
}
```

证明：当 $q$ 尽量小时，$p$ 也会随之变小。若不满足最优子结构，设换元时 $p=kq+r$，$(q,r)$ 为可以使 $p$ 最优的解，最优子结构为 $(q',r')$，有 $q' \leq q,r'\geq r$（否则 $(q,r)$ 显然不是最优解），故

$$\frac{a}{b}<\frac{r}{q}\leq\frac{r}{q'}\leq\frac{r'}{q'}<\frac{c}{d}$$

故 $q=q'$，所以 $r=r'$，满足最优子结构

---

## 作者：Siyuan (赞：25)

[$$\Large\texttt{My Blog}$$](https://hydingsy.github.io/articles/problem-Luogu-5179-Fraction/)

---

## Description

> 题目链接：[Luogu 5179](https://www.luogu.org/problemnew/show/P5179)

给你四个正整数 $a,b,c,d$，求一个最简分数 $\frac{p}{q}$ 满足 $\frac{a}{b}<\frac{p}{q}<\frac{c}{d}$。

若有多组解，输出 $q$ 最小的一组，若仍有多组解，输出 $p$ 最小的一组。数据保证至少存在一个最简分数符合条件。

本题 $T$ 组数据。

数据范围：$1\le T\le 500$，$1\le a,b,c,d\le 10^9$

------

## Solution

其实这个问题的本质是**类欧几里德算法**。我们分为如下 $3$ 种情况考虑：

1. $\left\lfloor\frac{a}{b}\right\rfloor+1\le\left\lceil\frac{c}{d}\right\rceil-1$

   这意味着 $\left(\frac{a}{b},\frac{c}{d}\right)$ 之间存在一个整数，我们直接让 $p=1,p=\left\lfloor\frac{a}{b}\right\rfloor+1$ 即可。

2. $a=0$

   这意味着只需要满足 $\frac{p}{q}<\frac{c}{d}$，即为 $q>\frac{pd}{c}$。我们为了取得最优解，可以直接取 $p=1,q=\left\lfloor\frac{d}{c}\right\rfloor+1$。

3. $a\le b$ 且 $c\le d$

   这意味着我们无法直接求解，需要进行一个**转化**：将原式 $\frac{a}{b}<\frac{p}{q}<\frac{c}{d}$ 的每个分数都取倒数，由于每个数都是正数，那么可以得到 $\frac{d}{c}<\frac{q}{p}<\frac{b}{a}$，直接**递归处理**即可。

4. $a\ge b$

   这意味着第 $1$ 个分数和第 $3$ 个分数的整数部分都大于 $0$。接下来要进行一个**重要的转化**：我们可以将每个分数减去 $\left\lfloor\frac{a}{b}\right\rfloor$，直接递归处理 $\frac{a\bmod b}{b}<\frac{p}{q}-\left\lfloor\frac{a}{b}\right\rfloor<\frac{c}{d}-\left\lfloor\frac{a}{b}\right\rfloor$ 即可。注意递归处理完后，需要将 $p$ 加上 $q\times \left\lfloor\frac{a}{b}\right\rfloor$。

这个过程中形式上极其类似于欧几里德算法，将 $(a,b)$ 转化为 $(a\bmod b,b)$ 正是其精髓所在。

------

## Code

```cpp
#include <cstdio>
typedef long long LL;

LL gcd(LL x,LL y) {
	return y?gcd(y,x%y):x;
}
void sim(LL &x,LL &y) {
	LL d=gcd(x,y); x/=d,y/=d;
}
void solve(LL a,LL b,LL c,LL d,LL &p,LL &q) {
	sim(a,b),sim(c,d);
	LL x=a/b+1,y=(c-1)/d;
	if(x<=y) p=x,q=1;
	else if(!a) p=1,q=d/c+1;
	else if(a<=b&&c<=d) solve(d,c,b,a,q,p);
	else solve(a%b,b,c-d*(a/b),d,p,q),p+=q*(a/b);
}
int main() {
	LL a,b,c,d,p,q;
	while(~scanf("%lld%lld%lld%lld",&a,&b,&c,&d)) {
		solve(a,b,c,d,p,q);
		printf("%lld/%lld\n",p,q);
	}
	return 0;
}
```



---

## 作者：WeLikeStudying (赞：16)

**题意**
- 求一个有理数 $\dfrac pq$ ，满足：
$$a<\frac pq<b\quad(a,b\in\mathbf{Q^+})$$
- 输出结果优先使 $q$ 最小，在这个基础上使 $p$ 最小。
- 数据相对还是比较大，而且如果枚举则较难考虑边界。

**基础性质的发现**：
- 这道题的条件看似比较难以处理，但实际上，我们没有必要计较优先级。
- 也就是说：对于满足条件的答案 $\dfrac pq$ 。不存在最简分数 $a<\dfrac xy<b$ ，使得 $x<p$ 且 $y>q$，或使得 $x>p$ 且 $y<q$ 。
- 证明：若存在最简分数 $a<\frac xy<b$ ，使得 $x<p$ 且 $y>q$，则 $\frac xy<\frac xq<\frac pq$ ，$\frac xq$ 显然更优。
- 若存在最简分数 $a<\frac xy<b$ ，使得 $x>p$ 且 $y<q$，则 $\frac xy>\frac py>\frac pq$ ，$\frac py$ 显然更优。
- 这个性质保证了最优解分子和分母一定同时是最小的。
- **这个性质才是我们后面状态转移的依据**。

**欧几里得**
- 回顾辗转相除的状态转移过程，它为什么如此之快？
- 因为 $F(x,y)\rightarrow F(y,x\bmod y)$ （这类函数）中参数减小的速度很快，以至于如此迅速就到达了边界。
- 于是我们尝试对这些式子进行类似 gcd 运算的状态转移，也称类欧几里得。
- 当然，递归是需要一些条件的，我们将尝试寻找。

**边界**
- 这里的边界相当显然，当 $\exists n\in\mathbf{Z^{+}}$ 使得 $a<n<b$ 时，$p=$ 能取到的最小 $n,q=1$ 就是答案。
- 不过你会发现这比较难以表述，我们后面会专门处理。

**第一个可用于转移的性质**
- 我们希望能直接找到参数相互取模的转移。
- 这并没有看起来这么困难，因为去掉整数部分的操作就满足这样的性质。
$$a<\dfrac xy<b\rightarrow a-\lfloor a\rfloor<\dfrac {x-\lfloor a\rfloor}y<b-\lfloor a\rfloor$$
- 由于特判了之前的边界情况， $0<b-\lfloor a\rfloor\leq 1$ 。
- 由于之前的性质，子问题的最优解仍然是该问题的最优解。
- 此时你几乎可以想到我们怎么得到正解了，不过我们先等一下，完成一个理解复杂度的操作。

**重新思考**
- 继续思考吧，我们要处理的 $a<\dfrac xy<b$ 式子现在有限制 $0\le a<1,0<b\leq 1$ 。
- 我们得到了一个类似 $F(x,y)\rightarrow F(x\bmod y,y)$ （a，b 的分子分别被分母取模）的转移，这个时候尝试做出把分子分母交换的举动或许是一种正确的方向，也就是 $F(x,y)\rightarrow F(x\bmod y,y)\rightarrow F(y,x\bmod y)$。
- 这样以后，转移显然就没有困难了，函数可以按照辗转相除的模式递归到边界。

**再次尝试转移**
- 现在我们要解决的问题的范围已经缩小到了 $a,b\leq c$ 的情况。
- 这次我们尝试得到将 $a$ 或 $b$ 分子分母交换的转移。
- 这会要推的式子仍然特别显然！
- 我们直接取倒数就可以
$$a<\dfrac xy<b\rightarrow \frac1b<\frac yx<\frac 1a$$
- 这状态转移不知道比 [P5170](https://www.luogu.com.cn/problem/P5170) 的模板简单多少倍。

**讨论另一些特别情况**
- 复杂度理解：两个参数的分子分母部分都在交替以辗转相除的形式减小，所以很容易减小到边界，单次 $O(\log_2n)$ 。
- 经过几次转移可能会出现 $a=0$ ，此时可以将 $\frac 1a$ 看作 $+\infty$ ，而且此时下一步一定会出解。
- 如何方便地判断边界情况？先去整再判断 $b>1$ 是否成立即可，多简单。
- 需不需要考虑溢出？显然不需要。
- 咱们需不需要考虑算出来之后分子分母？考虑辗转相除的情况，你就会发现我们始终是把两个互质的数一个加上另一个。
- 另外本题的数据范围是不是有点水，不过好像没有比它更简单的算法了。

**代码实现**
```cpp
#include<fstream>
#define f(x) x.a/x.b
#define m(x,y) x.a+=y*x.b 
#define s(x) swap(x.a,x.b)
using namespace std;
struct frac
{
	int a,b;
};
void fight(frac &l,frac &r,frac &x)
{
	int t=f(l);
	m(l,-t),m(r,-t);
	if(r.a>r.b)
	{
		x.a=t+1;
		x.b=1;
		return;
	}
	s(l),s(r);
	fight(r,l,x);
	s(x);
	m(x,t);
}
int main()
{
	frac l,r,x;
	while(scanf("%d%d%d%d",&l.a,&l.b,&r.a,&r.b)!=EOF)
	{
		fight(l,r,x);
		printf("%d/%d\n",x.a,x.b);
	}
	return 0;
} 
```

---

## 作者：YONIC (赞：13)

这题虽然看样子是标了黑，但是有一个比较轻巧的思路。

试想一下，在什么时候我们可以不加思考的直接填上这个目标分数？当然是在一眼就能看出 $a<b$ 且 $d<c$ 的时候，可以直接 $p=1,q=1$ 输出。所以最后不管我们要干什么，目标都是要把刚开始给出的两个分数化为一者小于一，一者大于一的形式。

废话不多说，开工，先举一个浅显的例子：
$$\frac{19}{117}<\frac{p}{q}<\frac{14}{85}$$
拿到这么一个式子，我们先对它取倒数：
$$\frac{117}{19}>\frac{q}{p}>\frac{85}{14}$$
然后把 $\ge 1$ 的部分给剪掉：
$$\frac{3}{19}>\frac{q-6p}{p}>\frac{1}{14}$$
这样我们就把两边的分数变成了更小的真分数，继续循环：
$$\frac{19}{3}<\frac{p}{q-6p}<\frac{14}{1}$$
$$\frac{1}{3}<\frac{p-6(q-6p)}{q-6p}<\frac{8}{1}$$
从而得出 $p-6(q-6p)=q-6p=1$ 再一步步倒回去即可。
```cpp
#include<bits/stdc++.h>
#define int long long//不开long long见祖宗（尤其数学题更要如此）
using namespace std;
void work(int a,int b,int&p,int&q,int c,int d){
	if(a<b&&c>d) p=1,q=1;
	else{
		work(d%c,c,q,p,b-(d/c)*a,a);//取倒数并减去整数部分
		q+=(d/c)*p;//回溯
	}
}
signed main() {
	int a,b,c,d,p,q;
	while(~scanf("%lld%lld%lld%lld",&a,&b,&c,&d)){//数据组数不确定的读入方法
		work(a,b,p,q,c,d);
		printf("%lld/%lld\n",p,q);
	}
	return 0;//好习惯
}
```

---

## 作者：JerryTcl (赞：8)

一片的都是类欧的题解，让我来写一篇 Stern-Brocot 树的

容易想到，在 Stern-Brocot 树上二分，直到当前子树的树根处于 $\dfrac ab$ 与 $\dfrac cd$ 之间时，输出答案

但是直接这样写会 TLE，原因在于假如分数与一个分母较小的分数挨得过近，则在 Stern-Brocot 树上收敛缓慢

但是，容易发现这种情况只会出现在连续数次递归到同一个左/右儿子的情况下出现，于是可以每次二分时计算接下来连续几次递归到左/右儿子，即可 AC

代码：

```cpp
#include <bits/stdc++.h>
using namespace std;
int t, a, b, c, d, lp, lq, rp, rq, mp, mq, xl, xr, yl, yr, f, ml, mr;
int cmp(int a, int b, int c, int d) {
	int x = a * d - b * c;
	return x < 0 ? -1 : x == 0 ? 0 : 1;
}
int findL(int a, int b, int lp, int lq, int rp, int rq) {
	long long u = 1ll * b * rp - 1ll * a * rq;
	long long d = 1ll * a * lq - 1ll * b * lp;
	return d ? u / d : INT_MAX;
}
int findR(int a, int b, int lp, int lq, int rp, int rq) {
	long long u = 1ll * a * lq - 1ll * b * lp;
	long long d = 1ll * b * rp - 1ll * a * rq;
	return d ? u / d : INT_MAX;
}
int main() {
	while(~scanf("%d %d %d %d", &a, &b, &c, &d)) {
		lp = 0, lq = 1, rp = 1, rq = 0, f = 1;
		while(f) {
			xl = findL(a, b, lp, lq, rp, rq), xr = findR(a, b, lp, lq, rp, rq);
			yl = findL(c, d, lp, lq, rp, rq), yr = findR(c, d, lp, lq, rp, rq);
			ml = min(xl, yl), mr = min(xr, yr);
			if(xl > 0 && yl > 0) rp += lp * ml, rq += lq * ml;
			else if(xr > 0 && yr > 0) lp += rp * mr, lq += rq * mr;
			else printf("%d/%d\n", lp + rp, lq + rq), f = 0;
		}
	}
	return 0;
}
```

---

## 作者：CXY07 (赞：8)

# 一个奇怪的做法

## 题目链接：[P5179 【Fraction】](https://www.luogu.com.cn/problem/P5179)

> **本题解同步发布于 [My Blog](http://www.cxy07.blog/index.php/archives/27/)**

反正也有一个 $log$ 的题解了，我就来搞一个比较好玩的两个 $log$ 做法。

题目要我们求满足 $\frac{a}{b} < \frac{p}{q} < \frac{c}{d}$ 的最简分数 $\frac{p}{q}$，并满足 $q$ 最小，然后满足 $p$ 最小。

可以放在平面直角坐标系里面，把 $(q,p)$ 当做一个点表示出来。发现若两侧取等，则 $(q,p)$ 分别过直线 $p=\frac{a}{b}q$ 和 $p=\frac{c}{d}q$，其中 $q$ 是自变量。

比如样例中的 ``a=1,b=3,c=1,d=2``，可以表示为：

![图1](https://cdn.luogu.com.cn/upload/image_hosting/n8g6q6rl.png)

那么点 $(q,p)$ 一定严格在两条直线中间，并显然这个点是一个整点 ~~废话~~。

那么现在我们希望得到的是满足条件的整点中最左边的那一个，因为他能满足 $q$ 最小的条件。能够发现这个点 $(q,p)$ 一定满足 $gcd(p,q)=1$，因为如果 $gcd(p,q) \ne 1$，那么一定有 $(\frac{q}{gcd(p,q)},\frac{p}{gcd(p,q)})$ 也满足条件，并且他在更左边。

如果把直线 $x=q$ 加入图像，并计算这三条直线围成图形中的整点个数（直线 $x=q$ 上的整点算入总数，其他两条直线上的整点不算）。

当 ``a=1,b=3,c=1,d=2,q=5`` 时，重合的部分如下：

![图2](https://cdn.luogu.com.cn/upload/image_hosting/t886xerm.png)

~~好丑的图~~

不难发现两个直线中间的整点个数随着 $q$ 的增大而单调不减，所以我们可以二分 $q$，找出最小的 $q$ 满足范围内的整点个数 $\ge 1$ 即可。

如何求这个区间内的整点个数呢？

可以考虑差分，分别计算两个正比例函数下方的整点个数，再相减。

现在的问题转化为：求正比例函数 $y=\frac{a}{b}x$ 下方的整点个数。其实就是：

$$\sum_{i=0}^{q} \lfloor \frac{a\times i}{b} \rfloor$$

这就是个类欧几里得的板子。

那么我们对两个正比例函数分别做一次类欧，然后进行差分，如果整点个数 $\ge 1$，说明这个 $q$ 满足条件，二分右端点左移，否则二分左端点右移。

需要注意的是，类欧几里得的板子会计算到直线上的整点，我们需要减去他们，但只需要减去在上方的直线上的整点个数即可，因为下方直线上的点也需要被减去，所以不需要特殊考虑。

现在我们就可以找到最小的 $q$ 了，最小的 $p$ 是多少呢？若令 $\frac{a}{b} > \frac{c}{d}$，那么显然 $p=\lfloor \frac{c \times q}{d} \rfloor + 1$。

因此复杂度为 $O(T\ log^2\ \text{值域})$ ~~的样子吧~~。

注意二分上界的问题，要尽量开大，同时需要考虑爆 $\texttt{long long}$ 的情况，懒人 $\texttt{CXY07}$ 用了 __$\texttt{int128}$。

```cpp
//Code By CXY07
#include<bits/stdc++.h>
using namespace std;

//#define FILE
#define int __int128
#define LL long long
#define pii pair<int,int>
#define mp make_pair
#define pb push_back
#define fst first
#define scd second
#define inv(x) ksm(x,mod - 2)
#define lowbit(x) (x & (-x))

const int MAXN = 1;
const int INF = 4e9;
const double PI = acos(-1);
//const int mod = 1e9 + 7;
//const int mod = 998244353;
//const int G = 3;

LL a,b,c,d;

template<typename T> inline void read(T &a) {
	a = 0; char c = getchar(); int f = 1;
	while(c < '0' || c > '9') {if(c == '-') f = -1; c = getchar();}
	while(c >= '0' && c <= '9') {a = a * 10 + (c ^ 48); c = getchar();}
	a *= f;
}

void out(int x) {
	if(!x) return;
	out(x / 10);
	putchar(x % 10 + '0');
}

int gcd(int x,int y) {
	if(!y) return x;
	return gcd(y,x % y);
}

int calc(int n,int a,int b,int c) {
	if(!a) return (n + 1) * (b / c);
	if(a >= c || b >= c) return (n + 1) * n / 2 * (a / c) + (n + 1) * (b / c) + calc(n,a % c,b % c,c);
	int m = (a * n + b) / c;
	return n * m - calc(m - 1,c,c - b - 1,a);
}

bool chk(int x) {
	int res = calc(x,a,0,b) - calc(x,c,0,d);
	res -= x / b;//减去上方直线上的整点
	return (res >= 1);
}

void solve() {
	int L = 1,R = INF,mid;//注意R的上界
	while(L < R) {
		mid = (L + R) >> 1;
		if(chk(mid)) R = mid;
		else L = mid + 1;
	}
	out(c * L / d + 1); putchar('/'); out(L);
	putchar('\n');
}

signed main () {
#ifdef FILE
	freopen(".in","r",stdin);
	freopen(".out","w",stdout);
#endif
	while(~scanf("%lld%lld%lld%lld",&a,&b,&c,&d)) {
		//read(a); read(b); read(c); read(d);
		int ab = gcd(a,b),cd = gcd(c,d);
		a /= ab,b /= ab,c /= cd,d /= cd;//把分数化简
		if(a * d < b * c) swap(a,c),swap(b,d);//强行让 (a / b) > (c / d)
		solve();
	}
	return 0;//sto zxyhymzg orz
}

```

---

## 作者：Link_Cut_Y (赞：6)

## 题目描述

给你四个正整数 $a,\,b,\,c,\,d$ ，求一个最简分数 $\frac{p}{q}$ 满足 $\frac{a}{b} < \frac{p}{q} < \frac{c}{d}$。

若有多组解，输出 $q$ 最小的一组，若仍有多组解，输出 $p$ 最小的一组。

## 前置知识：Stern-Brocot 树

首先引入**分数逼近**。这里的分数逼近是指用用一个分数来逼近另一个分数，使得误差趋于零。例如，假设需要逼近的分数为 $\dfrac{r}{s}$，有分数 $\dfrac{u}{v} > \dfrac{r}{s}$。那么有以下结论：

$$\dfrac{r}{s} \leq \dfrac{r + u}{s + v} \leq \dfrac{u}{v}$$

具体等号能不能取到记不清了，不过不影响。结论很好证明，下面证一下。

-------------------------

将 $\dfrac{r + u}{s + v}$ 与 $\dfrac{r}{s}$ 做减法，得到 $\dfrac{r + u}{s + v} - \dfrac{r}{s} = \dfrac{(r + u)s - r(s + v)}{s(s + v)} = \dfrac{us- vr}{s(s + v)}$。

因为 $\dfrac{r}{s} < \dfrac{u}{v}$，两边同时乘以 $sv$，得 $vr < us$，即 $us - vr > 0$。

又因为 $s(s + v) > 0$，所以 $\dfrac{us - vr}{s(s + v)} > 0$。证毕。

注意上面结论和证明成立的条件是 $u, v, s, r > 0$。

------------

接下来引入 Stern-Brocot 树这个概念。

Stern-Brocot 树可以维护所有的正分数。这一点可以被我们用来解决这道题目。

首先介绍一下 Stern-Brocot 树。这个树由 $\dfrac{0}{1}$ 和 $\dfrac{1}{0}$ 两个分数开始。$\dfrac{1}{0}$ 不大好定义，暂且把它当做 $+ \infty$。将这两个分数作为**源节点**。

接下来，像我们刚才讨论的分数逼近，将 $\dfrac{0}{1}$ 和 $\dfrac{1}{0}$ 的分子分母分别相加，得到另外一个分数 $\dfrac{1}{1}$。这个分数确实在 $\dfrac{0}{1}$ 与 $\dfrac{1}{0}$ 之间。$\dfrac{1}{1}$ 被成为第 $1$ 层迭代后的节点。

同样的，将 $\dfrac{1}{1}$ 与 $\dfrac{0}{1}, \dfrac{1}{0}$ 分别进行操作，得到两个分数，称为第二次迭代。

所以我们得到了 Stern-Brocot 树的构建基础：将 $\dfrac{a}{b}$ 与 $\dfrac{c}{d}$ 分子分母分别相加，得到 $\dfrac{a + c}{b + d}$ 作为下一轮迭代的节点。

例如，进行三次操作后，这棵树就会变成这样：

$$\begin{array}{c} \dfrac{0}{1}, \dfrac{1}{1}, \dfrac{1}{0} \\\\ \dfrac{0}{1}, \dfrac{1}{2}, \dfrac{1}{1}, \dfrac{2}{1}, \dfrac{1}{0} \\\\ \dfrac{0}{1}, \dfrac{1}{3}, \dfrac{1}{2}, \dfrac{2}{3}, \dfrac{1}{1}, \dfrac{3}{2}, \dfrac{2}{1}, \dfrac{3}{1}, \dfrac{1}{0} \end{array}$$

注意，某些节点（就是第 $i$ 层存在，第 $i + 1$ 层也存在的节点），实际上在第 $i + 1$ 层是不会出现的。只是为了方便比较加了上去。

可以看到，第三层的第二个分数 $\dfrac{1}{3}$ 就是左右两边两个数分子分母分别相加的和。第四个，第六个和第八个以此类推。

下面是来自 OI-wiki 的一张图。

![Stern-Brocot树](https://oi-wiki.org/math/number-theory/images/stern-brocot1.png)

刚才所提到的不存在的节点就是虚线相连的那些节点。可以看到，这棵树具有二叉结构。因此在这棵树上搜索只需要花费 $O(\log_2 n)$ 的时间。非常优秀。

关于最简性的证明可以看 [OI-wiki](https://oi-wiki.org/math/number-theory/stern-brocot/) 上的解释。这里不再赘述。


------------

对于这道题，显然可以在 Stern-Brocot 树上二分来求解。具体的，如果当前结果 $\dfrac{x}{y}$ 在左端点 $\dfrac{A}{B}$ 的左边，则向右递归，反之亦然。于是可以写出这样的代码：

```
void solve(int a = 0, int b = 1, int c = 1, int d = 0) {
	int x = a + c, y = b + d;
	long double now = (long double)x / y;
	long double L = (long double)A / B, R = (long double)C / D;
	if (now > L && now < R) {
		ans = {x, y}; return;
	}
	if (now <= L) solve(x, y, c, d);
	else solve(a, b, x, y);
}
```

交上去以后发现只有 $60$ 分。说明我们需要继续优化算法。

如果把递归时的路径打印出来，我们发现可能会连续地向左（向右）递归很多次。这很不好，因为浪费了许多时间。那么是否可以用较短的复杂度计算出接下来需要连续向左（向右）递归多少次呢？

答案是可以的。假设当前的递归函数是 $(a, b, c, d)$，当前分数 $\dfrac{x}{y} = \dfrac{a + c}{b + d}$。假设 $\dfrac{A}{B} < \dfrac{x}{y} < \dfrac{C}{D}$，这是最好的，可以直接输出了。但是如果 $\dfrac{x}{y} \le \dfrac{A}{B}$，显然需要向右递归。假设向右递归的次数为 $t$，那么 $\dfrac{x + ct}{y + dt} \ge \dfrac{A}{B}$。解一下这个不等式：

$$\begin{array}{c} \dfrac{x + ct}{y + dt} \ge \dfrac{A}{B} \\\\ (x + ct)B \ge (y + dt)A \\\\ xB + cBt \ge yA + dAt \\\\ t \ge \dfrac{yA - xB}{cB - dA} \end{array}$$

同理，如果 $\dfrac{x}{y} \ge \dfrac{C}{D}$，那么需要连续向左递归的次数 $t \ge \dfrac{yC - xD}{aD - bC}$。

如此，我们用 $O(1)$ 的时间求出了连续向左（向右）递归的次数。


------------

## 代码

```cpp
#include <algorithm>
#include <cstdio>
#include <iostream>

using namespace std;

using PII = pair<int, int>;
PII ans;
int A, B, C, D;

void solve(int a = 0, int b = 1, int c = 1, int d = 0) {
    int x = a + c, y = b + d;
    long double now = (long double)x / y;
    long double L = (long double)A / B, R = (long double)C / D;
    if (now > L && now < R) {
        ans = {x, y}; return;
    }
    if (now <= L) {
        int t = (int)(y * A - x * B) / (c * B - d * A);
        solve(x + c * t, y + d * t, c, d);
    }
    else {
        int t = (int)(y * C - x * D) / (a * D - b * C);
        solve(a, b, x + a * t, y + b * t);
    }
}
signed main() {
    while (scanf("%d%d%d%d", &A, &B, &C, &D) != EOF) {
        solve();
        printf("%d/%d\n", ans.first, ans.second);
    }
    return 0;
}
```

简短精炼得代码后面有个小坑：别忘了用 `long double`。

最后留个 Stern-Brocot 树的练习题：P1298 最接近的分数。

---

## 作者：⚡Sagimune⚡ (赞：3)

+ 若存在整数$z\in(\frac ab,\frac cd)$则 $p=z=\lfloor \frac ab \rfloor +1,q=1$

+ 若$a=0$,则$\frac pq\lt\frac cd$化简得$q>\frac dc\times p={dp\over c}$

  $\therefore q=\lfloor {dp\over c}\rfloor +1,p=1$

+ 若$a\ge b$且$c\ge d$,则${a\%b\over b}\lt\frac pq-\lfloor\frac ab\rfloor\lt\frac cd-\lfloor\frac ab\rfloor={c\times d\lfloor\frac ab\rfloor\over d}$

+ 颠倒为$\frac dc\lt\frac qp\lt\frac ba$递归操作

```cpp
#include<bits/stdc++.h>
using namespace std;
typedef long long ll;
ll gcd(ll a,ll b) {return b?gcd(b,a%b):a;}
void Calc(ll a,ll b,ll c,ll d,ll &p,ll &q)
{
	ll g=gcd(a,b); a/=g,b/=g;
	g=gcd(c,d),c/=g,d/=g;
	ll L=a/b+1,R=c/d+(c%d>0)-1;
	if(L<=R) p=L,q=1;
	else if(!a) p=1,q=d/c+1;
	else if(a<=b&&c<=d) Calc(d,c,b,a,q,p);
	else Calc(a%b,b,c-d*(a/b),d,p,q),p+=q*(a/b);
}
int main()
{
	ll a,b,c,d,p,q;
	while(scanf("%lld%lld%lld%lld",&a,&b,&c,&d)!=EOF)
	{
		Calc(a,b,c,d,p,q);
		printf("%lld/%lld\n",p,q);
	}
	return 0;
}
```

---

## 作者：ncwzdlsd (赞：1)

## P5179题解

看到这道题，突然产生了一种梦回小学时代的感觉。

首先我们考虑一种最简单的情况，如果左右两边的分数一个小于 $1$，一个大于 $1$，那么显然 $p=1$，$q=1$。

于是乎，我们可以对这个问题进行简化：我们通过一系列操作，把原问题转化为左右两边的分数一个小于 $1$，一个大于 $1$，问题就能迎刃而解啦！

我们举个栗子，详细地解释一下这个流程：$\dfrac{123}{456}<\dfrac{p}{q}<\dfrac{456}{789}$，遇到这样的情况怎么办呢？我们先对它取倒数，得到 $\dfrac{789}{456}<\dfrac{q}{p}<\dfrac{456}{123}$，为了满足上面的条件我们把左右两边减去左边比 $1$ 大的部分，把问题转化为 $\dfrac{333}{456}<\dfrac{q-p}{p}<\dfrac{333}{123}$，满足条件了，于是乎我们可以令 $q-p=1$，$p=1$，得到正确答案。其他操作也大同小异，递归函数即可。

代码如下：

```cpp
#include <bits/stdc++.h>
using namespace std;

void work(int a,int b,int &p,int &q,int c,int d)//注意这里的p、q前要加取地址符
{
	if(a<b&&c>d) p=1,q=1;
	else
		work(d%c,c,q,p,b-(d/c)*a,a),q+=(d/c)*p;
}

int main()
{
	int a,b,c,d,p,q;
	while(cin>>a>>b>>c>>d)
	{
		work(a,b,p,q,c,d);
		cout<<p<<'/'<<q<<endl;
	}
	return 0;
}
```

---

## 作者：w33z8kqrqk8zzzx33 (赞：1)

我太菜了不会一个 log。

考虑二分答案的 $q$，也就是判断“给一个上线 $q$，有没有任何 $P,Q$ 使得 $Q\le q$ 并且 $\frac{a}{b}<\frac{P}{Q}<\frac{c}{d}$"。  
很显然这个判断问题是一个单调，可二分函数。这样我们肯定会找到最小的 $q$，可以用最小的 $q$ 直接找出来最小的 $p=\lfloor\frac{a}{b}\rfloor+1$。这样 $p,q$ 也必须互质，否则 $q$ 可以更小，和前面的“最小$q$”结论矛盾。

假设固定 $Q$。有多少个合法 $P$ 呢？推柿子：

$$\#(\frac{a}{b}<\frac{P}{Q}<\frac{c}{d})$$
$$\#(\frac{aQ}{b}<P<\frac{cQ}{d})$$
$$\#(P<\frac{cQ}{d})-\#(P\le\frac{aQ}{b})$$
$$\#(P\le\frac{cQ-1}{d})-\#(P\le\frac{aQ}{b})$$
$$\lfloor\frac{cQ-1}{d}\rfloor-\lfloor\frac{aQ}{b}\rfloor$$

那就可以用这个柿子计算 $Q\le q$ 时候的答案了：
$$\sum_{q=1}^Q\lfloor\frac{cQ-1}{d}\rfloor-\lfloor\frac{aQ}{b}\rfloor$$
$$\sum_{q=0}^{Q-1}\lfloor\frac{cQ+c-1}{d}\rfloor-\lfloor\frac{aQ+a}{b}\rfloor$$
$$\sum_{q=0}^{Q-1}\lfloor\frac{cQ+c-1}{d}\rfloor-\sum_{q=0}^{Q-1}\lfloor\frac{aQ+a}{b}\rfloor$$
直接用类欧即可。

代码：

```cpp
int f(int a, int b, int c, int n) {
    assert(0 <= a && 0 <= b && 0 < c);
    if(!a) return (n+1)*(b/c);
    if(a >= c || b >= c) 
        return ((a/c)*(n*(n+1)/2) + \
                (b/c)*(n+1) + \
                f(a%c,b%c,c,n));
    return (((a*n+b)/c)*n - f(c,c-b-1,a,(a*n+b)/c-1));
}

int A, B, C, D;
int coun(int m) { return f(C, C-1, D, m-1) - f(A, A, B, m-1); }
signed main() {
    ios_base::sync_with_stdio(false); cin.tie(0);
    while(cin >> A >> B >> C >> D) {
        int low = 1, high = 2e9, ans = 0;
        while(low <= high) {
            int mid = (low + high) / 2;
            if(coun(mid)) ans = mid, high = mid - 1;
            else low = mid + 1;
        }
        cout << (A*ans/B)+1 << '/' << ans << endl;
    }
}

```

---

## 作者：_HL_ (赞：0)

$\dfrac{a}{b}<\dfrac{p}{q}<\dfrac{c}{d}$


首先可以证明最小化 $p$ 等价于最小化 $q$

证明如下：

假设 $p$ 与 $q$ 最小化不等价 则存在 $\dfrac{p}{x}$ 和 $\dfrac{y}{q}$ 分别使 $p$ 和 $q$ 最小化 且有 $x>q \text{  } y>p$

所以 $\dfrac{a}{b}<\dfrac{p}{x}<\dfrac{p}{q}<\dfrac{y}{q}<\dfrac{c}{d}$

所以与假设矛盾 故得证

然后分离常数

$\dfrac{a-\lfloor \frac{a}{b} \rfloor\cdot b}{b}+\lfloor \dfrac{a}{b} \rfloor<\dfrac{p}{q}<\dfrac{c}{d}-\lfloor \dfrac{a}{b} \rfloor$

若后一项大于 $1$ 则 $q_{min}=1$

否则有 $\lfloor\dfrac{p}{q}\rfloor=\lfloor\dfrac{a}{b}\rfloor=\lfloor\dfrac{c}{d}\rfloor$

我们对于分数 $\dfrac{x}{y}$ 令 $x'=x-\lfloor \frac{x}{y} \rfloor\cdot y$

则有 $\dfrac{a'}{b}<\dfrac{p'}{q}<\dfrac{c'}{d}$

将三个翻转 即 $\dfrac{b}{a'}>\dfrac{q}{p'}>\dfrac{d}{c'}$

再次进行上述操作 类似欧几里得算法 边界之后可全部反解出 $q$

```cpp
#include<bits/stdc++.h>
using namespace std;
void gcd(int a,int b,int c,int d,int &p,int &q)
{
	int t=a/b;
	a=a-t*b;
	c=c-t*d;
	if(c>d)
	{
		q=1,p=t+1;
		return;
	}
	gcd(d,c,b,a,q,p);
	p+=t*q;
}
signed main()
{
	int a,b,c,d,p,q;
	while(~scanf("%d%d%d%d",&a,&b,&c,&d))
	{
		gcd(a,b,c,d,p,q);
		printf("%d/%d\n",p,q);
	}
	return 0;
}
```




---

## 作者：Mars_Dingdang (赞：0)

本题乍一看很简单：这不就是小学数学题吗……再一看发现不会做了。不过其实分好类，解法就明朗了。

## 题目大意
给你四个正整数 $a,b,c,d$，求一个最简分数 $\dfrac p q$ 满足 $\dfrac a b <\dfrac p q <\dfrac c d$，且 $q$ 尽可能小，在此基础上 $p$ 尽可能小。

多组数据，数据范围：$a,b,c,d\le 10^9$。

## 大体思路
用 $\omega$ 表示值域，$\omega$ 与 $10^9$ 同阶。

首先有许多种 $O(T\log^2 \omega)$ 的做法。比如本题编号是 $5179$，而前几道题就有类欧几里得的模板 $P5170$，因而顺理成章的想到类欧几里得，套上二分即可。

这里介绍一种 $\Theta(T\log \omega)$ 的算法。对 $\dfrac a b,\dfrac c d$ 进行分类。首先对 $\dfrac a b,\dfrac c d$ 利用欧几里得算法约分。

```cpp
inline ll gcd(ll a,ll b){//求最大公因数
	if(!b) return a;
	return gcd(b,a%b);
}
inline void Div(ll &a,ll &b){//约分
	ll g=gcd(a,b);
	a/=g;
	b/=g;
}
inline void work(ll a,ll b,ll c,ll d,ll &p,ll &q){
	Div(a,b);Div(c,d);//未完待续
```

1. 最基本的：若 $\left\lfloor\dfrac a b\right\rfloor +1\le \left\lceil\dfrac c d\right\rceil-1$，即这两个分数之间存在整数。由于题目要求正整数 $q$ 尽可能小，因此 $\dfrac p q$ 为整数，即 $q=1$ 时必然满足。因此 $p\leftarrow \left\lfloor\dfrac a b\right\rfloor +1,q\leftarrow 1$。

```cpp
	ll x=(a/b)+1,y=(c-1)/d;
	if(x<=y) p=x,q=1;
```

2. 若 $a=0$，只需满足 $\dfrac p q<\dfrac c d$，由于均为正整数，移项可得 $q>\dfrac{pd}c$。由整数的离散性，$q\ge \left\lfloor\dfrac {pd}c\right\rfloor+1$，因此当 $p=1$ 时，$q$ 取最小值。

```cpp
else if(a==0) p=1,q=(d/c)+1;
```

3. 若 $\dfrac a b,\dfrac c d$ 均为真分数，即 $a<b\ and\ c<d$，则无法直接求出。由于均为正整数，取倒数将式子变换得到 $\dfrac d c<\dfrac q p<\dfrac b a$，此时三个分数均为假分数（即分子比分母大），可通过递归求解。处理带分数的方法在 $4$ 中将会介绍。

```cpp
else if(a<=b && c<=d) work(d,c,b,a,q,p);
//取倒数
```

4. 若 $a\ge b$，由于 $\dfrac a b<\dfrac c d$，此时三个分数均为带分数。令三个分数均减去 $\left\lfloor\dfrac a b\right\rfloor$，可以得到：
$$\dfrac{a}b-\left\lfloor\dfrac a b\right\rfloor<\dfrac p q-\left\lfloor\dfrac a b\right\rfloor<\dfrac c d-\left\lfloor\dfrac a b\right\rfloor$$
$$\therefore\dfrac{a\bmod b}b<\dfrac p q-\left\lfloor\dfrac a b\right\rfloor<\dfrac{c-d\times \left\lfloor\dfrac a b\right\rfloor}d$$

在递归时，不需要处理中间项 $\dfrac p q-\left\lfloor\dfrac a b\right\rfloor$，求出 $p,q$ 后，令 $p\leftarrow p+q\times \left\lfloor\dfrac a b\right\rfloor$ 即可。

```cpp
else work(a%b,b,c-(d*(a/b)),d,p,q), //减去 a/b
	p+=(q*(a/b)); //处理 p
```

这样就可以在 $\Theta(T\log \omega)$ 的复杂度下求解。但该算法本质仍是 $O(T\log^2 \omega)$，因为 $\gcd$ 函数的复杂度是 $O(\log \max(a,b))$，即 $O(\log \omega)$，而递归求解时的 $a\bmod b$ 共有 $\log \max(a,b)$ 层，因此总复杂度仍为 $O(T\log^2 \omega)$，但实际效率优于此。

## 完整代码
```cpp
#include<bits/stdc++.h>
using namespace std;
#define rep(ii,aa,bb) for(re int ii = aa; ii <= bb; ii++)
#define Rep(ii,aa,bb) for(re int ii = aa; ii >= bb; ii--)
typedef long long ll;
typedef unsigned long long ull;
//const int maxn = ;
namespace IO_ReadWrite {
	#define re register
	#define gg (p1 == p2 && (p2 = (p1 = buf) + fread(buf, 1, 1<<21, stdin), p1 == p2) ? EOF :*p1++)
	char buf[1<<21], *p1 = buf, *p2 = buf;
	template <typename T>
	inline void read(T &x){
		x = 0; re T f=1; re char c = gg;
		while(c > 57 || c < 48){if(c == '-') f = -1;c = gg;}
		while(c >= 48 &&c <= 57){x = (x<<1) + (x<<3) + (c^48);c = gg;}
		x *= f;return;
	}
	inline void ReadChar(char &c){
		c = gg;
		while(!isalpha(c)) c = gg;
	}
	template <typename T>
	inline void write(T x){
		if(x < 0) putchar('-'), x = -x;
		if(x > 9) write(x/10);
		putchar('0' + x % 10);
	}
	template <typename T>
	inline void writeln(T x){write(x); putchar('\n');}
}
using namespace IO_ReadWrite;
inline ll gcd(ll a,ll b){
	if(!b) return a;
	return gcd(b,a%b);
}//最大公因数
inline void Div(ll &a,ll &b){
	ll g=gcd(a,b);
	a/=g;
	b/=g;
}//约分
inline void work(ll a,ll b,ll c,ll d,ll &p,ll &q){
	Div(a,b);Div(c,d);
	ll x=(a/b)+1,y=(c-1)/d;
    //分类
	if(x<=y) p=x,q=1;
	else if(a==0) p=1,q=(d/c)+1;
	else if(a<=b && c<=d) work(d,c,b,a,q,p);
	else work(a%b,b,c-(d*(a/b)),d,p,q), p+=(q*(a/b));
}//递归求解
ll a,b,c,d,p,q;
int main(){
	while(~scanf("%lld%lld%lld%lld",&a,&b,&c,&d)){//多组数据
		work(a,b,c,d,p,q);
		printf("%lld/%lld\n",p,q);
	}
	return 0;
}
```

## 后记
1. 这道题如果没有 $p,q$ 最优的限制就是一道红题，直接通分即可（最多像 NOIp 那样卡个高精）。

2. 这题的题解写起来比代码还烦，$\rm{\LaTeX}$ 极其恶心。

---

