# [USACO08MAR] Land Acquisition G

## 题目描述

Farmer John 准备扩大他的农场，眼前他正在考虑购买 $N$ 块长方形的土地。

如果 FJ 单买一块土地，价格就是土地的面积。但他可以选择并购一组土地，并购的价格为这些土地中最大的长乘以最大的宽。比如 FJ 并购一块 $3 \times 5$ 和一块 $5 \times 3$ 的土地，他只需要支付 $5 \times 5=25$ 元， 比单买合算。

FJ 希望买下所有的土地。他发现，将这些土地分成不同的小组来并购可以节省经费。 给定每份土地的尺寸，请你帮助他计算购买所有土地所需的最小费用。

## 说明/提示

将所有土地分为三组：

- 第一块土地为第一组，花费 $100 \times 1=100$；
- 第二，三块土地为第二组，花费 $20 \times 15=300$；
- 第四块土地为第三组，花费 $1 \times 100=100$；

总花费为 $500$，可以证明不存在更优的方案。

## 样例 #1

### 输入

```
4 
100 1 
15 15 
20 5 
1 100 
```

### 输出

```
500 
```

# 题解

## 作者：FlashHu (赞：106)

用两种不一样的思路立体地理解斜率优化，你值得拥有。

## 题意分析

既然所有的土地都要买，那么我们可以考虑到，如果一块土地的宽和高（其实是蒟蒻把长方形立在了平面上）都比另一块要小，那么肯定是直接并购，这一块对答案没有任何贡献。

我们先把这些给去掉，具体做法可以是，按高为第一关键字，宽为第二关键字从大到小排序，然后上双指针扫一遍。

于是，剩下的就是一个高度递减、宽度递增的矩形序列。考虑怎样制定它们的并购方案会最优。显然如果要并购，一定要挑序列中的一段区间，这样贡献答案的就只有最左边矩形的高乘上最右边矩形的宽，中间的又是没有贡献了。

设$f_i$为前$i$个矩形的最小花费，$w$为宽，$h$为高，直接写出一个$O(n^2)$的方程

$$f_i=\min\limits_{j=1}^i\{f_{j-1}+w_ih_j\}$$

一看貌似是一个决策单调性优化的式子。然而。。。。。。

## 初中生都会的函数图像法

这种理解方法是在决策单调性优化DP的基础上应运而生的。

或者说，（在大多数情况下）斜率优化可以看作决策单调性优化的一种特殊情形。蒟蒻建议还是先入手决策单调性再来斜率优化吧。

蒟蒻的[DP各种优化总结](https://www.cnblogs.com/flashhu/p/9480669.html)

蒟蒻之前写的一道经典（~~裸~~）决策单调性题的题解[戳这里](https://www.cnblogs.com/flashhu/p/9488184.html)（Lightning Conductor）

对于每一个$f_{j-1}+w_ih_j$，我们都可以把它视为一个直线$l_j:y=ax+b$，其中$a=h_j,b=f_{j-1}$。对于每一个$i$，我们就是需要求出所有$j\le i$的直线的$x$取$w_i$时最小的一个$y$值。仍然用KmPlot画一个我们需要维护的所有直线的样子，它们应该满足斜率依次递减。

$l_1:y=2x;$

$l_2:y=x+1;$

$l_3:y=\frac x 2+3;$

$l_4:y=\frac x 6+5.$

![](https://cdn.luogu.com.cn/upload/pic/29583.png)

真正有用的部分

![](https://cdn.luogu.com.cn/upload/pic/29584.png)

这样的话，我们就用单调队列维护若干个斜率递减的函数。我们仍然需要按照决策单调性的做法，维护相邻两个决策直线间的临界值（交点）$k$。难道还要维护决策二分栈，对每个临界值都二分么？

这些决策不是直线吗？求两个直线的交点。。。。。。初中数学就教了，是$O(1)$的。也就是对两个相邻决策直线$l_1,l_2$，我们求$\frac{b_2-b_1}{a_1-a_2}$。其它过程跟决策单调性是一模一样的。直线入队前，如果队尾不满足斜率递增则出队。求$f_i$之前，先把队首临界值$\le w_i$的决策出队，那么现在队首就是最优决策了。

这样求出$f_n$只需要$O(n)$的时间。

## 高中生都会的线性规划法

这才是理解斜率优化的正宗方法，因为上面并没有充分体现对斜率的处理过程。

上面对两个相邻直线求$\frac{b_2-b_1}{a_1-a_2}$，看起来有点像求什么东西。

我们原来把决策当成直线，斜率为$a$，截距为$b$。现在我们换一下。把决策$f_{j-1}+w_ih_j$看作一个点$p_j(x,y)$，其中$x=-h_j,y=f_{j-1}$。

现在要求解的问题又变成了什么样子呢？在平面上有若干个点，把$f_i$看成目标函数$z$，我们需要找到$f_i=w_ih_j+f_{j-1}$即$z=-w_ix+y$的最小值。这不是个线性规划么？

把式子变成$y=w_ix+f_i$，现在就让我们来最小化截距$f_i$。手(nao)动(dong)模拟一下，我们现在正在拿着一个斜率为$w_i$的直线，从下往上移动，当第一次经过某个决策点的时候，直线的在$y$轴上的截距就是我们要求的目标函数$f_i$的最小值了。

随便画一堆点就可以发现，无论直线以怎样的斜率向上靠，总有一些点永远都不会第一次与直线相交，也就是说这些决策是没用的。剩下的有用的决策点会构成一个凸包：（因为要画点所以换成了GeoGebra）

![](https://cdn.luogu.com.cn/upload/pic/29588.png)

凸包的性质就是斜率递增/递减。在此题中，因为$w$递增，所以我们的单调队列中存的是若干个点满足$x$递增（$h$递减），$y$递增，而且相邻两个点的斜率也递增。这和原序列的顺序是同向的。假设队尾下标为$t$，当需要在队尾加入一个新的决策点时，我们可能会遇到这样的情况：

![](https://cdn.luogu.com.cn/upload/pic/29589.png)

这时候$p_t$已经不优了，我们把它出队，如此直到满足斜率递增为止，$p_i$就可以入队了。和上面那种理解方法的写法差不多，求相邻两个点形成的直线斜率然后比一下大小。队首的处理跟上面那种理解方法的写法也差不多，如果队首与后一个的斜率小于$w_i$就出队。最后的队首依然是最优解。

## 实现

两种实现的代码长得都差不多，都要搞一个单调队列，都要求临界值/斜率。所以就放一个代码吧。。。

复杂度$O(n\log n)$，瓶颈竟然在sort上？！~~蒟蒻可不想来什么wys排序~~

```cpp
#include<cstdio>
#include<algorithm>
#define RG register
#define R RG int
#define G c=getchar()
#define Calc(i,j) (f[j-1]-f[i-1])/(a[i].h-a[j].h)
//method1:求出临界值
//method2:求出斜率
using namespace std;
const int N=1e5+9;
int q[N];
double f[N],k[N];
//method1:k_i为决策直线q_i与q_i+1的临界值（交点）
//method2:k_i为决策点q_i与q_i+1所连成直线的斜率
struct Land{
	int w,h;//结构体排序
	inline bool operator<(RG Land&x)const{
		return h>x.h||(h==x.h&&w>x.w);
	}
}a[N];
inline int in(){
	RG char G;
	while(c<'-')G;
	R x=c&15;G;
	while(c>'-')x=x*10+(c&15),G;
	return x;
}
int main(){
	R n=in(),i,h,t;
	for(i=1;i<=n;++i)
		a[i].w=in(),a[i].h=in();
	sort(a+1,a+n+1);
	for(h=i=1;i<=n;++i)//双指针扫描去除无用矩形
		if(a[h].w<a[i].w)a[++h]=a[i];
	n=h;
	for(h=i=1,t=0;i<=n;++i){
		while(h<t&&k[t-1]>=Calc(q[t],i))--t;//维护临界值/斜率单调
		k[t]=Calc(q[t],i);q[++t]=i;//加入决策直线/决策点
		while(h<t&&k[h]<=a[i].w)++h;//弹出已经不优的决策
		f[i]=(double)a[q[h]].h*a[i].w+f[q[h]-1];//求出最优解
	}
	printf("%.0lf\n",f[n]);
	return 0;
}
```

---

## 作者：花淇淋 (赞：57)

每块土地的长和宽分别用$l$和$h$数组表示。

因为一组土地购买的价格 $=$ 最大的长 $*$ 最大的宽，**所以对于一块土地$x$，如果存在一块土地$y$，满足$l[y]>=l[x]$且$h[y]>=h[x]$**，那么它只要把土地$x$和土地$y$合为一组，最大的长可以不取$l[x]$，最大的宽可以不取$h[x]$，**所以土地$x$的存在与否对答案是没有任何影响的。**

因此，可以把所有土地按长度从小到大排序，对于长度相同的按宽度从小到大排序。然后维护一个栈，将排序后的土地一个一个加入，每次加入之前，先把当前栈中宽小于等于它的土地全部删除（因为这些土地长肯定小于等于它），再加入它。最后留在栈里的土地就是有存在必要的土地。

**可以发现，此时留下的土地的宽度是从大到小排好的。所有还有一个结论：此时在最优决策下，每一组土地都是连续的一段。**为什么呢？举个例子：假设这时有三个土地$x$，$y$，$z$，是连续的三块土地，那么有：$l[x]<l[y]<l[z]$且$h[x]>h[y]>h[z]$。考虑把$x$和$z$分为一组，$y$单独一组，要花费$h[x]*l[z]+h[y]*l[y]$的费用。如果把$y$也分进$x$，$z$那一组呢？只要$h[x]*l[z]$的费用，省去了$y$单独一组的费用。

**因此，考虑$dp$。设$f[i]$表示前$i$个土地的最小费用。易得转移方程：$f[i]=min(f[i],f[j]+h[j+1]*l[i])$，然而这是$O(n^2)$的，过不去。**

考虑优化。求出$f[j]$之后，设$a=h[j+1]$，$b=f[j]$，就可以表示一条直线：$y=ax+b$，求$f[i]$等价于在已经表示出的所有直线中，找一个当$x=l[i]$时$y$最小的。**注意到$l[i]$是递增的，而$h[i]$是递减的。**如图1：

![](https://cdn.luogu.com.cn/upload/pic/24548.png)

可以发现，一旦$l[i]>p$的横坐标，较优的永远是直线$p2$，$p1$已经没有用了。**因此维护一个单调队列，对于每一个$i$，比较单调队列队头两个$j$生成的直线，只要当$x=l[i]$时，队头第一个不如队头第二个优，就把队头第一个删除了，直到队头第一个比第二个优。**

然而还有这样一种情况，如图2：

![](https://cdn.luogu.com.cn/upload/pic/24549.png)

按照之前的那种做法，过点$A$之前，都会选择直线$p1$最优，但是在过$B$点之后，$p1$已经不如$p3$优了。**所以每次把直线$i$加入队列作为以后备选的$j$之前，先判断队尾两条直线和直线$i$是否有如上图的关系，有的话删除队尾第一条，直到不存在上图情况，加入直线$i$。**

判断即：$p1$与$p2$交点横坐标是否大于$p1$与$p3$交点横坐标。需要用到除法，可以通过移项时它变为乘法，避免因交点横坐标不为整数带来的精度问题。

总结一下就是，先将土地排序，去掉没有存在必要的土地，然后进行$dp$，先删除队头不优的，删完之后队头就是此时最优的$j$，然后算出$f[i]$，生成直线$i$，然后删除队尾不优的，再将直线$i$放入队列，作为以后的$j$。

代码如下：
```cpp
#include <iostream>
#include <cstdio>
#include <cstring>
#include <algorithm>
#include <cstdlib>

using namespace std;

const int e = 5e4 + 5;
int n, q[e], t = 1, w = 1, tot;
long long a[e], b[e], f[e], h[e], l[e];

struct point
{
	long long w, l;
}c[e];

inline int read()
{
	char ch; int res;
	while (ch = getchar(), ch < '0' || ch > '9');
	res = ch - 48;
	while (ch = getchar(), ch >= '0' && ch <= '9')
	res = res * 10 + ch - 48;
	return res;
}

inline bool cmp(const point &c, const point &d)
{
	if (c.l == d.l) return c.w < d.w;
	else return c.l < d.l;
}

inline double calc(int i, int j)
{
	return f[j] + h[j + 1] * l[i];
}

inline bool slope(int p1, int p2, int p3)
{
	return (b[p3] - b[p1]) * (a[p2] - a[p1])
	- (b[p2] - b[p1]) * (a[p3] - a[p1]) >= 0;
}

int main()
{
	int i;
	n = read();
	for (i = 1; i <= n; i++)
	{
		c[i].w = read();
		c[i].l = read();
	}
	sort(c + 1, c + n + 1, cmp);
	for (i = 1; i <= n; i++)
	{
		while (tot && c[i].w >= h[tot]) tot--;
		h[++tot] = c[i].w; l[tot] = c[i].l;
	}
	a[0] = h[1];
	for (i = 1; i <= tot; i++)
	{
		while (t < w && calc(i, q[t]) >= calc(i, q[t + 1])) t++;
		f[i] = calc(i, q[t]);
		a[i] = h[i + 1];
		b[i] = f[i];
		while(t < w && slope(q[w - 1], q[w], i)) w--;
		q[++w] = i;
	}
	cout << f[tot] << endl;
	return 0;
}
```

---

## 作者：Siyuan (赞：52)

[$$\Large\texttt{My Blog}$$](https://hydingsy.github.io/articles/problem-Luogu-2900-Land-Acquisition/)

---

## Description

> 题目链接：[Luogu 2900](https://www.luogu.org/problemnew/show/P2900)

约翰准备扩大他的农场，眼前他正在考虑购买 $n$ 块长方形的土地，每块土地宽为 $w_i$、长为 $l_i$。如果约翰单买一块土地，价格就是土地的面积 $w_i\times l_i$。但他可以选择并购一组土地，并购的价格为这些土地中最大的长乘以最大的宽，即 $\max\{w_i\}\times \max\{l_i\}$。比如约翰并购一块 $3\times 5$ 和一块 $5\times 3$ 的土地，他只需要支付 $5\times 5=25$ 元， 比单买合算。约翰希望买下所有的土地。他发现，将这些土地分成不同的小组来并购可以节省经费。给定每份土地的尺寸，请你帮助他计算购买所有土地所需的最小费用。

数据范围：$1\le n\le 5\times 10^4$，$1\le w_i,l_i\le 10^6$

------

## Solution

我们首先可以发现一个性质：如果对于土地 $i,j$ 满足 $w_i\ge w_j$ 且 $l_i\ge l_j$，那么土地 $j$ 显然是无用的。那么最终有用的土地，如果在**宽递减**的前提下，一定是**长递增**的。这个过程可以通过排序简单预处理。

假设我们已经得到 $n$ 块土地满足 $w_i\le w_{i-1},l_i\ge l_{i-1}$，我们可以证明每一组土地一定是**连续的一段**。这个证明基本是显然的，因为我们可以将一块土地并入前后的组别，使得这块土地不需要额外花费。

由此，我们可以简单推出 $\text{DP}$ 方程：$f_i=\min\{f_j+w_{j+1}\times l_i\}\quad (0\le j<i)$，但是这个转移是 $O(n^2)$ 的，不能通过本题。

其实这个东西是有**决策单调性**的，我们考虑**斜率优化**。

我们任取 $j,k$ 满足 $0\le k<j<i$，如果此时 $j$ 比 $k$ 要**更好**，那么有如下不等式：
$$\begin{aligned}f_j+w_{j+1}\times l_i&\le f_k+w_{k+1}\times l_i \\f_j-f_k&\le l_i\times (w_{k+1}-w_{j+1})\end{aligned}$$
由于宽是递减的，那么 $w_{k+1}\ge w_{j+1}$，可以直接移项得到：
$$l_i\ge \frac{f_j-f_k}{w_{k+1}-w_{j+1}}$$
显然我们只要维护一个下凸壳就可以斜率优化啦！

**时间复杂度**：$O(n\log n)$（瓶颈竟然在排序上 QAQ）

------

## Code

```cpp
#include <cstdio>
#include <algorithm>

const int N=5e4+5;
int n,q[N];
long long f[N];
struct Land {
	int x,y;
	bool operator < (const Land &b) const {
		return x==b.x?y>b.y:x>b.x;
	}
} a[N];

void init() {
	std::sort(a+1,a+n+1);
	int m=0;
	for(int i=1;i<=n;++i) if(a[i].y>a[m].y) a[++m]=a[i];
	n=m;
}
double slope(int i,int j) {
	return 1.0*(f[i]-f[j])/(a[j+1].x-a[i+1].x);
}
int main() {
	scanf("%d",&n);
	for(int i=1;i<=n;++i) scanf("%d%d",&a[i].x,&a[i].y);
	init();
	int l=1,r=0;
	q[++r]=0;
	for(int i=1;i<=n;++i) {
		while(l<r&&slope(q[l],q[l+1])<=a[i].y) ++l;
		f[i]=f[q[l]]+1LL*a[q[l]+1].x*a[i].y;
		while(l<r&&slope(q[r-1],q[r])>=slope(q[r],i)) --r;
		q[++r]=i;
	}
	printf("%lld\n",f[n]);
	return 0;
}
```



---

## 作者：eternal风度 (赞：13)

# 土地征用题解(兼斜率优化详解)
这不是以解题为最主要目的(代码细节不讲)的题解谢谢

因为自己学的时候有一些觉得难懂

所以想用很通俗的方法教大家斜率优化，希望题解通过QwQ

链接题目：[洛谷土地征用](https://www.luogu.org/problemnew/show/P2900)

还有一些其他大家可能需要的东西哟。。。

[这里有$dp$的各种优化。。。](https://www.cnblogs.com/cjoierljl/p/9667951.html)

[这里是$Flash Hu$的dp优化博客](https://www.cnblogs.com/flashhu/p/9480669.html)

博客食用（阅读体验）：[eternal风度的土地征用](https://www.cnblogs.com/cjoierljl/p/9693156.html)

## 前期处理及一些小性质
我们这里直接把土地理解成一些矩形，显然如果一个大矩形可以把另一个小矩形包含住，那个小矩形肯定会被并购掉，可以直接不考虑，就去掉

可以在$O(nlogn)$的复杂度内解决掉：

按高度从大到小排序，如果当前的宽度比之前最宽的宽度要小，显然不要；如果要大，就加进需要考虑的矩形数组里，顺便更新宽度最大值
```
    int L=1;
    for(int i=1;i<=n;++i)
        if(ljl[L].w<ljl[i].w)ljl[++L]=ljl[i];//ljl是定义的矩形的结构体。。。
    n=L;
```

现在我们得到了一个高度单调递减，宽度单调递增的矩形序列对吧

那么是不是很容易发现一定是把一段下标连续的矩形并购更优

简单证明一下：如果并购不连续，那么中间那个断开的高度一定小于前一段，宽度一定小于后一段，把它并购到这一段不连续的里面不会产生费用，所以这种决策不会更差，只会更优。。。

## $dp$部分
有前面的那个简单性质，可以考虑$dp$了

设$dp[i]$表示买完前i块矩形的最小费用

显然有$dp$方程：$dp[i]=min_{j=2}^i${$dp[j-1]+h[j]*w[i]$}

表示我们把区间$[i,j]$上的矩形并购了
## 斜率优化
### 由来
直接做肯定是$O(n^2)$的复杂度

所以考虑优化

那么假设我们有$j$和$k$两个可能的转移状态，不妨设$j>k$

那么假设决策$j$比决策$k$更优，我们看要满足什么条件

$dp[j-1]+h[j]*w[i]<=dp[k-1]+h[k]*w[k]$

合并同类项化简之后会得到

$\frac{dp[j-1]-dp[k-1]}{h[j]-h[k]}=>w[i]$

嗯？这个式子怎么这么眼熟？这就是为什么我们叫他斜率优化
### 实现
是不是只要满足上面那个式子，决策$j$就一定优于决策$k$

那么我们把$(h[j],dp[j-1])$看做一个点,那么上面式子的左边可以看做点$j$和$k$的斜率(我觉得你们可以再看一下其他大佬的图)

而由于$w[i]$是单调不降的，所以我们的那个斜率要求单调递增（相等的话决策结果一样就不考虑了），并且大于等于$w[i]$对吧

这个可以用单调队列来维护

> 在队尾每次把点$i$加入其中，条件是与队尾的点斜率大于队尾与队尾-1的点(维护斜率单调递增)

> 在队首每次查询，条件是队首的斜率满足要求（大于$w[i]$(同样相等不考虑了)）

可能讲起来还很抽象，借助代码。。。

$calc$是按照上面的“斜率”定义来求斜率的函数

$k[tl-1]$表示队列中$Q[tl-1]$与$Q[tl]$的斜率

$ljl[i].w$就是$w[i]$辣。。。定义一个结构体而已。。。
```
    int hd=1,tl=0;
    for(int i=1;i<=n;++i)
    {
        while(hd<tl&&k[tl-1]>=calc(i,Q[tl]))--tl;
        k[tl]=calc(i,Q[tl]),Q[++tl]=i;
        while(hd<tl&&k[hd]<ljl[i].w)++hd;
        dp[i]=dp[Q[hd]-1]+ljl[Q[hd]].h*ljl[i].w;
    }
```
## 汇总
可能需要结合整个代码和这个题来理解。。。

**PS：如果还有不懂评论区留言吧。。。**
```
#include<bits/stdc++.h>
#define lst long long
#define ldb double
#define N 50050
using namespace std;
const int Inf=1e9;
int read()
{
    int s=0,m=0;char ch=getchar();
    while(ch<'0'||ch>'9'){if(ch=='-')m=1;ch=getchar();}
    while(ch>='0'&&ch<='9')s=(s<<3)+(s<<1)+(ch^48),ch=getchar();
    return m?-s:s;
}

int n;
ldb k[N];
int Q[N];
lst dp[N];
struct Land{lst h,w;}ljl[N];
bool cmp(const Land &a,const Land &b){return a.h==b.h?a.w>b.w:a.h>b.h;}
ldb calc(int x,int y){return (dp[x-1]-dp[y-1])/(ljl[y].h-ljl[x].h);}
int main()
{
    n=read();
    for(int i=1;i<=n;++i)
        ljl[i]=(Land){read(),read()};
    sort(ljl+1,ljl+n+1,cmp);
    int L=1;
    for(int i=1;i<=n;++i)
        if(ljl[L].w<ljl[i].w)ljl[++L]=ljl[i];
    n=L;int hd=1,tl=0;
    for(int i=1;i<=n;++i)
    {
        while(hd<tl&&k[tl-1]>=calc(i,Q[tl]))--tl;
        k[tl]=calc(i,Q[tl]),Q[++tl]=i;
        while(hd<tl&&k[hd]<ljl[i].w)++hd;
        dp[i]=dp[Q[hd]-1]+ljl[Q[hd]].h*ljl[i].w;
    }printf("%lld\n",dp[n]);
    return 0;
}
```

推广博客：[eternal风度的博客](https://www.cnblogs.com/cjoierljl/)


---

## 作者：Tgotp (赞：13)

思路：斜率优化dp。

这种题一般自己推一推比较好；

简单的，我们可以看出，

首先：对于x排序，可以提出某些被包含的土地块（直接打包买）

然后：可以发现dp思路：f[i] = min(f[j]+b[j+1].y\*b[i].x

但是可以很容易发现时间不够；

继续发现可以用斜率优化进行优化；

假设一个k < j 且 j 优于 k；

则f[j]+b[j+1].y\*b[i].x < f[k] + b[k+1].y\*b[i].x；

化简得到 (f[j]-f[k])/(b[j+1].y - b[j+1].y) < a[i];

此时斜率优化直接搞就对了！

用了双头队列...

博客：<http://tgotp.science>

c++代码如下：

```cpp
#include<iostream>
#include<algorithm>
#include<cstdio>
#include<queue>
using namespace std;
deque<int>s;
typedef long long ll;
inline void read(ll&x)
{
    x = 0;int sign = 1;char c;
    do{ c = getchar();if(c == '-')sign = -1; }
    while(c < '0' || c >'9');
    do{ x = x*10 + c - '0';c = getchar();}
    while(c <= '9' && c >='0');
    x *= sign;
}
const int N = 5e4 + 5;
int tot;
ll n,f[N];
struct data { ll x,y; }a[N],b[N];
inline bool cmp(data a,data b){ return a.x == b.x?a.y<b.y:a.x<b.x; }
inline double slop(int a,int c){ return double(f[c]-f[a])/(b[a+1].y - b[c+1].y); }
int main()
{
    read(n);
    for(int i = 1;i <= n;i++)read(a[i].x),read(a[i].y);
    sort(a+1,a+n+1,cmp);
    for(int i = 1;i <= n;i++)
    {
        while(tot && a[i].y >= b[tot].y) tot--;
        b[++tot].x = a[i].x;b[tot].y = a[i].y;
    }
    s.push_back(0);
    for(int i = 1;i <= tot;i++)
    {
        while(s.size() > 1 && slop(s[0],s[1]) < b[i].x) s.pop_front();
        int t = s[0],j;
        f[i] = f[t] + b[t + 1].y * b[i].x;
        while((j = s.size()) > 1 && slop(s[j-1],i) < slop(s[j-2],s[j-1])) s.pop_back();
        s.push_back(i); 
    }
    printf("%lld",f[tot]);
    return 0;
}
```

---

## 作者：Feyn (赞：12)

[link](https://www.luogu.com.cn/problem/P2900)

绝大部分题解都是用的斜率优化，至少第一页都用的是，剩下的懒得翻了。但我并不想使用斜率优化，哎就是玩……

那能用什么，似乎只剩决策单调性优化了。首先考虑它是否可以使用决策单调性优化，也就是说它的转移方程满不满足那个奇怪的不等式。

和其它题解一样，去除掉无用土地之后，假设我们剩下的这些土地满足每一块土地都比前一块长，却比前一块窄的性质(换句话说，假如用 a 数组代表长度， b 数组代表宽度则是：前者单调递减，后者单调递增)。可以写出方程：

$$f_x=\min\limits_{i=0}^{x-1}{f_i+a_{i+1}\times b_x}$$

而上述式子是符合那个奇怪不等式的，原因且听我分析一波，当然你跳过也行。由方程可以发现：

$$w[i,j]=a_{i+1}\times b_j$$

那么：

$$w[i,j+1]=a_{i+1}\times b_{j+1}$$
$$w[i,j+1]-w[i,j]=a_{i+1}\times(b_{j+1}-b_j)$$

同理：

$$w[i+1,j+1]-w[i+1,j]=a_{i+2}\times(b_{j+1}-b_j)$$

所以：

$$w[i+1,j+1]-w[i+1,j]-(w[i,j+1]-w[i,j])=(a_{i+2}-a_{i+1})\times (b_{j+1}-b_j)$$

由于 a 数组单增，所以第一个乘数是正的；因为 b 数组单减，所以第二个乘数是负的。综上，这个减法的结果是负的。所以有：

$$w[i+1,j+1]-w[i+1,j]-w[i,j+1]+w[i,j]<0$$
$$w[i+1,j+1]+w[i,j]<w[i+1,j]+w[i,j+1]$$

我们开心地发现上述式子就是那个可爱的不等式。得到这个之后我们就可以使用决策单调性来优化啦！

代码和[AC记录](https://www.luogu.com.cn/record/69682389):

```cpp
#include<cstdio>
#include<algorithm>
#define zczc
#define int long long
using namespace std;
const int N=50010;
inline void read(int &wh){
    wh=0;int f=1;char w=getchar();
    while(w<'0'||w>'9'){if(w=='-')f=-1;w=getchar();}
    while(w<='9'&&w>='0'){wh=wh*10+w-'0';w=getchar();}
    wh*=f;return;
}
inline void swap(int &s1,int &s2){int s3=s1;s1=s2;s2=s3;return;}
inline int max(int s1,int s2){return s1<s2?s2:s1;}

int m;
struct node{int a,b;}a[N];
inline bool cmp(node s1,node s2){return s1.a==s2.a?s1.b>s2.b:s1.a>s2.a;}
bool operator <(node s1,node s2){return s1.a<=s2.a&&s1.b<=s2.b;}

struct no{int id,l;}st[N];
int top,f[N];
int cost(int x,int y){return f[x]+a[y].a*a[x+1].b;}
int workf(int x){
	int l=1,r=top,mid;
	while(l<r)st[mid=l+r+1>>1].l<=x?l=mid:r=mid-1;
	return st[l].id;
}

signed main(){
	
	#ifdef zczc
	freopen("in.txt","r",stdin);
	#endif
	
	read(m);
	for(int i=1;i<=m;i++){read(a[i].a);read(a[i].b);}
	sort(a+1,a+m+1,cmp);int h=0;
	for(int i=1;i<=m;i++){if(i&&a[i]<a[h])continue;a[++h]=a[i];}
	m=h;for(int i=1;i<=m;i++)swap(a[i].a,a[i].b);
	st[++top]=(no){0,1};
	for(int i=1;i<=m;i++){
		f[i]=cost(workf(i),i);
		while(top&&cost(st[top].id,st[top].l)>=cost(i,st[top].l))top--;
		if(top==0){st[++top]=(no){i,i+1};continue;}
		int l=max(i+1,st[top].l),r=m,mid;
		while(l<r)cost(st[top].id,mid=l+r>>1)>=cost(i,mid)?r=mid:l=mid+1;
		if(cost(st[top].id,l)>=cost(i,l))st[++top]=(no){i,l};
	}
	printf("%lld\n",f[m]);
	
	return 0;
}
```

---

## 作者：DengDuck (赞：6)

不明白为啥没人写李超线段树。

斜率优化的题通常李超也能做，这题 $n$ 不大，长宽的值域也很小，所以完全可以李超。

状态转移方程是咋来的请看别的题解。

$$
f_i=f_j +H_iW_{j+1}
$$

其中 $H$ 是长，$W$ 是宽，我的排序方式和别人不太一样，可以看看我代码理解一下，这不是重点。

那么我们设 $K_j=W_{j+1},B_j=f_j$，那么每个位置都可以当做一个函数 $F_j(x)$，然后我们发现：

$$
f_i=\min_{j<i}F_j(H_i)
$$

所以我们就用李超维护这些直线，求最小值就很简单了。

时间复杂度是 $\mathcal O(n\log n)$ 的。

```cpp
#include<bits/stdc++.h>
#define LL long long
#define LF double
#define pLL pair<LL,LL>
#define pb push_back
//#define Fi first
//#define Se second
#define Ls(x) (x<<1)
#define Rs(x) (x<<1|1)
//#define Ls(x) t[x].Lson
//#define Rs(x) t[x].Rson
using namespace std;
const LL Inf=1e18;
const LL N=1e6+5;
const LL M=1e6;
//const LL Mod;
//const LF eps;
//const LL P;
struct Nd
{
	LL H,W;
}A[N],B[N];
LL n,tot,F[N];
struct Line
{
	LL k,b;
}L[N];
LL Cal(LL i,LL x)
{
	return L[i].k*x+L[i].b;
}
bool Pd(LL i,LL j,LL x)
{
	return Cal(i,x)<Cal(j,x);
}
LL Mn[N<<2];
void Upd(LL rt,LL l,LL r,LL x)
{
	if(l==r)
	{
		if(Pd(x,Mn[rt],l))Mn[rt]=x;
		return;
	}
	LL mid=l+r>>1;
	if(Pd(x,Mn[rt],mid))swap(x,Mn[rt]);
	if(Pd(x,Mn[rt],l))Upd(Ls(rt),l,mid,x);
	if(Pd(x,Mn[rt],r))Upd(Rs(rt),mid+1,r,x);
}
LL Qry(LL rt,LL l,LL r,LL x)
{
	LL t=Cal(Mn[rt],x);
	if(l==r)return t;
	LL mid=l+r>>1;
	if(x<=mid)return min(t,Qry(Ls(rt),l,mid,x));
	return min(t,Qry(Rs(rt),mid+1,r,x));
}
void Ins(LL x)
{
	L[x]={B[x+1].W,F[x]};
	Upd(1,1,M,x);
}
int main()
{
	scanf("%lld",&n);
	for(int i=1;i<=n;i++)
	{
		scanf("%lld%lld",&A[i].H,&A[i].W);
	}
	sort(A+1,A+n+1,[](Nd x,Nd y)
		{
			if(x.H!=y.H)return x.H<y.H;
			return x.W<y.W;
		});
	for(int i=n;i>=1;i--)
	{
		if(A[i].W>=B[tot].W)B[++tot]=A[i];
	}
	n=tot;
	sort(B+1,B+n+1,[](Nd x,Nd y)
		{
			if(x.H!=y.H)return x.H<y.H;
			return x.W<y.W;
		});
	L[0]={0,Inf};
	L[n+1]={B[1].W,0};
	Upd(1,1,M,n+1);
	F[1]=B[1].W*B[1].H;
	Ins(1);
	for(int i=2;i<=n;i++)
	{
		F[i]=Qry(1,1,M,B[i].H);
	//	cout<<B[i].H<<' '<<B[i].W<<' '<<F[i]<<endl;
		Ins(i);
	}
	printf("%lld\n",F[n]);
	return 0;
}
//RP++
```

---

## 作者：pengrui (赞：6)

先考虑普通dp，$f_i$表示购买到第$i$块土地的最小花费

$mw(i,j)$表示$i\sim j$土地中宽度的最大值，$ml(i,j)$表示$i\sim j$土地中高度的最大值

**状态转移方程：$f_i = min_{j \in [0, i)}\{f_j+ml(j + 1, i) * mw(j +1, i)\}$**

**方程解释：** 先将$j$之前的买完，再将$[j+1, i]$合并为一组买

对于两个土地$i,j$，若$w_i\geq w_j \bigwedge l_i \geq l_j$，$i,j$可同一组购买且不影响最优解，故想到：

将土地按$l_i$从大到小排序，再使$w_i$从小到大，保证一定不会出现土地相互包含

**部分代码：**
```cpp
//为了方便排序，使用结构体
struct S
{
	ll w, l;
	S(ll w = 0, ll l = 0) : w(w), l(l) {}
	bool operator < (const S &t) const	
	{
		if (l == t.l)
			return w > t.w;
		return l > t.l;
	}
}s[N], s1[N];
//排序
sort(s + 1, s + n + 1);
int n1 = 0;
for (int i = 1; i <= n; ++i)
	if (s[i].w > s1[n1].w)
		s1[++n1] = s[i];
```

此时的状态转移方程变为$f_i = min_{j \in [0, i)}\{f_j+l_{j+1}w_{i}\}$

**时间复杂度：$O(n^2)$**，不足以解决题目

于是想如何优化，因为出现$l_{j+1}w_{i}$项，很自然想到斜率优化

**决策单调性证明：**

$s(i,j) = l_{j+1}w_{i},\;s(i,j + 1) = l_{j+2}w_{i}$

$s(i + 1,j) = l_{j+1}w_{i + 1},\;s(i + 1,j + 1) = l_{j+2}w_{i + 1}$


$s(i + 1, j) + s(i, j + 1) - s(i, j) - s(i + 1, j + 1) $

$=l_{j+1}w_{i + 1}+l_{j+2}w_{i} - l_{j+1}w_{i} - l_{j+2}w_{i + 1}$

$=(w_{i+1} - w_i)(l_{j+1}-l_{j+2}) \geq 0$

$\therefore s(i,j)$满足四边形不等式

$\therefore\;$具有决策单调性

**优化：**

设$j1, j2$为$i$的决策点，$j2$优于$j1$，$0\leq j1 < j2 < i $

则$f_{j2} + l_{j2 + 1}w_i \leq f_{j1} + l_{j1 + 1}w_i$

移项得$w_i(l_{j2 + 1} - l_{j1 + 1}) \leq f_{j1} - f_{j2} $

$\Rightarrow -w_i \leq \frac{f_{j1} - f_{j2}}{l_{j1 + 1} - l_{j2 + 1}}$

维护上凸包（斜率递减）

**步骤：**

1. 单调队列维护凸包，因为具有决策单调性，所以可以不用二分

1. 每次检查队头，若队首元素没有第二个元素优，$pop$

1. 更新$f_i$

1. 向凸包中插入$f_i$，在此之前维护上凸包性质

**代码：**

```cpp
#include <iostream>
#include <cstdio>
#include <algorithm>

using namespace std;

typedef long long ll;
typedef long double ld;
const int N = 5e4 + 5;

struct S
{
	ll w, l;
	S(ll w = 0, ll l = 0) : w(w), l(l) {}
	bool operator < (const S &t) const	
	{
		if (l == t.l)
			return w > t.w;
		return l > t.l;
	}
}s[N], s1[N];

int n, head = 1, tail = 0, q[N];
ll f[N];

inline ld slope(int p1, int p2)
{	
	return (f[p2] - f[p1]) * 1.0 / (s1[p2 + 1].l - s1[p1 + 1].l) * 1.0;
}

int main()
{
	ios::sync_with_stdio(false);
	cin >> n;
	for (int i = 1; i <= n; ++i)
		cin >> s[i].w >> s[i].l;
	sort(s + 1, s + n + 1);
	int n1 = 0;
	for (int i = 1; i <= n; ++i)
		if (s[i].w > s1[n1].w)
			s1[++n1] = s[i];
	q[++tail] = 0;
	for (int i = 1; i <= n1; ++i)
	{
		while (head < tail && slope(q[head], q[head + 1]) >= -s1[i].w)
			++head;
		f[i] = f[q[head]] + s1[i].w * s1[q[head] + 1].l;
		while (head < tail && slope(q[tail - 1], q[tail]) <= slope(q[tail], i))
			--tail;
		q[++tail] = i;
	}
	cout << f[n1] << endl;
	return 0;
}
```
















---

## 作者：DimensionTripper (赞：6)

一道裸的斜率优化dp

首先对于i,j，若存在a[i].len(以下简写为l[i])>=a[j].len&&a[i].wid(以下简写为w[i])>=a[j].wid,则j这块土地是无用的，在预处理时应去掉这些无用的土地。同时在预处理时可以将数据按l降序排列，同时产生的结果是w必然按升序排列（有兴趣的dalao可以自己证明），这样可方便后面的过程。

然后就是对着数据手推状转方程了（建议先自己推一遍），可知假设用f[i]表示前i块土地的最小价值，则有**f[i]=min{f[j]+l[j+1]w[i]}**。

然后对数据化简可知假设j比k优，则有**f[j]+l[j+1]w[i]<f[k]+l[k+1]w[i]**,然后就可以得到**(f[k]-f[j])/(l[j+1]-l[k+1])>w[i]**

接着就是一个数形结合的思想了

    一些试题中繁杂的代数关系身后往往隐藏着丰富的几何背景，而借助背景图形的性质，可以使那些原本复杂的数量关系和抽象的概念，显得直观，从而找到设计算法的捷径。——周源
    
有兴趣的dalao可以阅读[浅谈数形结合思想在信息学竞赛中的应用](https://wenku.baidu.com/view/b97cd22d0066f5335a8121a3.html)

总之这里将关系式抽象为形如y=kx+b的式子，只要维护组成图形的下凸性就行了，如下图中就是一种要弹出队尾的情况，因为i节点的插入破坏了图形的下凸性
![](http://img.blog.csdn.net/20170122191654269?watermark/2/text/aHR0cDovL2Jsb2cuY3Nkbi5uZXQvQmlsbF9ZYW5nXzIwMTY=/font/5a6L5L2T/fontsize/400/fill/I0JBQkFCMA==/dissolve/70/gravity/SouthEast)

这里就要用到单调队列了，维护队列中的元素单调（然而我不会，所以请各位懂的大神指点

不多说见代码
```cpp
#include <bits/stdc++.h>
#pragma GCC optimize(3)
#define N 50010
using namespace std;
long long n,tot,q[N],head=1,tail=1,f[N];
struct node
{
    long long len,wid;
};struct node a[N];
struct node1
{
    long long lent,wide;
};struct node1 b[N];
bool mmp(node xx,node yy)
{
    return xx.len>yy.len||(xx.len==yy.len&&xx.wid>yy.wid);
}
double slope(int x,int y)
{
    return (double)(f[y]-f[x])/(double)(b[x+1].lent-b[y+1].lent);
}//slope 斜率，来自金山词霸
int main()
{
    scanf("%lld",&n);
    for(int i=1;i<=n;i++)
        scanf("%lld%lld",&a[i].len,&a[i].wid);
    sort(a+1,a+1+n,mmp);
    for(int i=1;i<=n;i++)
        if(a[i].wid>b[tot].wide)//注意！一定要这样维护b中w的升序排列
        {
            b[++tot].lent=a[i].len;
            b[tot].wide=a[i].wid;
        }
    for(int i=1;i<=tot;i++)//1~tot动规
    {
        while(head<tail&&slope(q[head],q[head+1])<=b[i].wide)
            head++;//如果队首不是最优，就弹出队首
        f[i]=f[q[head]]+b[i].wide*b[q[head]+1].lent;
        while(head<tail&&slope(q[tail-1],q[tail])>=slope(q[tail],i))
            tail--;//维护一个下凸包
        q[++tail]=i;//进队
    }
    printf("%lld\n",f[tot]);//这里也要用tot
    return 0;
}
```
可能没解释清楚（我自己也是有点蒙

望各位dalao谅解QWQ

[注] 图片、引文来源[[模板] 斜率优化Dp详解](http://blog.csdn.net/bill_yang_2016/article/details/54864284)

---

## 作者：_Sein (赞：3)

## 题面描述
[传送门](https://www.luogu.org/problemnew/show/P2900)
## 思路
## 瞎扯

乍一看，貌似找不到什么有序的东西。

先排序吧(第一关键字为$x$坐标，第二关键字为$y$坐标，都以从小到大排序)。

类似下图

![在这里插入图片描述](https://img-blog.csdnimg.cn/20190701143314753.PNG?x-oss-process=image/watermark,type_ZmFuZ3poZW5naGVpdGk,shadow_10,text_aHR0cHM6Ly9ibG9nLmNzZG4ubmV0L3p5c3psYjIwMDM=,size_16,color_FFFFFF,t_70)

发现相邻的两块土地(排序后)$i,i+1$,如果$y_i<y_{i+1}$，那么买第$i+1$块土地，顺便可以带上第$i$块土地(~~**岂不美哉！**，买一送一啊！~~)，

按照这样的思想，~~我们可以买一送~~$n$啊。

之后去掉送的土地，保留有用的(至于如何有用，详见上文)土地。

如下图

![在这里插入图片描述](https://cdn.luogu.com.cn/upload/pic/61983.png)

之后我们就可以~~愉快地~~推状态转移方程啦！

设离散化之后的数组为$b$(保证$x$坐标不下降)

$$F_i=\min(F_j+y_{b_{j+1}}*x_{b_i})$$

$y_{b_{j+1}}$保证是$b_{[j+1,i]}$后最大的纵坐标哦，因为后面如果有比它大的纵坐标，$b_{j+1}$根本不存在于数组中。

## 证明决策单调性

设有
$$F_k+y_{b_{k+1}}*x_{b_i}\le F_j+y_{b_{j+1}}*x_{b_i}
(j<k<i)$$

证明:对于未来状态$t$,都有

$$F_k+y_{b_{k+1}}*x_{b_t}\le F_j+y_{b_{j+1}}*x_{b_t}(j<k<i<t)$$

由于$x_{b_t},y_{b_{k+1}},y_{b_{j+1}}$不变，证毕。

~~这怕不是不用证明~~

## 踢队头
$$F_k+y_{b_{k+1}}*x_{b_i}\le F_j+y_{b_{j+1}}*x_{b_i}
(j<k<i)$$

$$F_j-F_k\ge y_{b_{k+1}}*x_{b_i}-y_{b_{j+1}}*x_{b_i}$$

由$y_{b_{k+1}}\le y_{b_{j+1}}$可知，

$$\frac{F_j-F_k}{y_{b_{k+1}}-y_{b_{j+1}}}\le x_{b_i}$$

因此，当上述不等式成立时，$k$优于$j$。

如果
$$calc(q_{head},q_{tail})=\frac{F_{head}-F_{head+1}}{y_{b_{head+1}}-y_{b_{head}}}\le x_{b_{i}}$$

说明$head+1$优于$head$。

## 踢队尾
我们首先一定要确定$i$这个状态，要优于$q_{tail}$

要维护的队列由于$q_{tail-1}$一定优于$q_{tail}$

现有一个标准值$x_{b_t}(tail<t)$

$calc(q_{tail-1},q_{tail)}\ge x_{b_t}$

如果$q_{tail}$要优于$i$，

则$calc(q_{tail},i)\ge calc(q_{tail-1},q_{tail})$

才能确保$q_{tail}$优于$i$

反之，当$calc(q_{tail},i)\le calc(q_{tail-1},q_{tail})$时，需要删去队尾。
貌似就没了哦。

## AC code
```cpp
#include<cstdio>
#include<cstring>
#include<algorithm>
#include<cstdlib>
#include<cmath>
#define gc getchar()
#define ll long long 
using namespace std;
const int N=5e4+10;
inline void qr(ll &x)
{
	x=0;int f=1;char c=gc;
	while(c<'0'||c>'9')c=gc;
	while(c>='0'&&c<='9'){x=x*10+(c^48);c=gc;}
	x*=f;
}
void qw(ll x)
{
	if(x/10)qw(x/10);
	putchar(x%10+48);
}
struct node
{
	ll x,y;
}a[N];
bool cmp(node a,node b){return a.x==b.x?a.y<b.y:a.x<b.x;}
ll f[N];int b[N],q[N],l,r;
inline double calc(int j,int k){return (f[j]-f[k])/(double)(a[b[k+1]].y-a[b[j+1]].y);}
int main()
{
	int n;scanf("%d",&n);
	for(int i=1;i<=n;i++)qr(a[i].x),qr(a[i].y);
	sort(a+1,a+n+1,cmp);
	int tot=0;
	for(int i=1;i<=n;i++)
	{
		while(tot&&a[b[tot]].y<=a[i].y)--tot;
		b[++tot]=i;
	}
	l=1;r=1;q[1]=0;
	for(int i=1;i<=tot;i++)
	{
		while(l<r&&calc(q[l],q[l+1])<=1.0*a[b[i]].x)++l;
		f[i]=f[q[l]]+a[b[i]].x*a[b[q[l]+1]].y;
		while(l<r&&calc(q[r],i)<=calc(q[r-1],q[r]))--r;
		q[++r]=i;
	}
	qw(f[tot]);puts("");
	return 0;
}
```

---

## 作者：Link_Space (赞：2)

一道斜率优化的上手题

首先观察：并购一堆土地的价格为最大的长乘以最大的宽，这一点在暗示（~~明示~~）我们排序，如何排序呢？对于这道题来说最简单的排序方式就是直接按照长或宽从小到大排序。

可以想到，如果我们选择了两块土地x和y以及中间的一堆土地作为一组同时购买，并且x的长是这里面最大的，y的宽是这里面最大的，那我们需要付出的就是x的长乘以y的宽的总代价，而这里面其它的所有土地都被白嫖了。

知道了这一点之后，思路就很显然了，假设我们选择了按照宽从小到大排序，然后我们用一个单调队列处理排好序之后的数组，从排好序的数组里面筛出一个长从大到小的序列，将他们存入一个数组中准备DP，假设该数组名为$needto$，而那些不遵守单调性的土地都不用管了，因为他们都可以被白嫖。
接下来你就可以写出一个暴力DP

```cpp
for (int i = 1; i <= cnt;i++)
	for (int j = 0; j < i;j++)
		dp[i] = min(dp[i], dp[j] + needto[j + 1].l * needto[i].w);
```
其中$dp[i]$代表买前$i$块土地需要用的最小的价钱。而状态的转移就是枚举上一组买的土地中的最后一块土地，假设为第$j$块，又假设我们这一次要买的一组土地的最后一块是第$i$块，那么我们这一次要买的一组土地包括了第$j+1$块到第$i$块中的所有土地，而由于$needto$是从按照宽从小到大排序的数组中根据长单调递减而筛出来的数组，那么第$j+1$块土地的长就是这一组土地中最大的，第$i$块的土地的宽就是最大的，所以这一组土地的花费就是$needto[j + 1].l * needto[i].w$，而$dp[i]$的最小值就是最小的$dp[j]+needto[j + 1].l * needto[i].w$，就得到了状态转移方程。

知道了这一点之后，后面的斜率优化就很轻松了，以下是本蒟蒻的代码。

```cpp
#include<iostream>
#include<cstdio>
#include<algorithm>
#include<cstring>
using namespace std;
typedef long long ll;
const int N = 1e6 + 5;
struct Node{
	ll w, l;
}Land[N];
ll dp[N];
Node needto[N];
ll q[N];
bool cmp(Node a,Node b)
{
	if(a.w!=b.w)
		return a.w < b.w;
	else
		return a.l < b.l;
}
int main()
{
	ll n;
	scanf("%lld", &n);
	for (int i = 1; i <= n;i++)
		scanf("%lld%lld", &Land[i].w, &Land[i].l);
	sort(Land + 1, Land + n + 1, cmp);
	int cnt = 0;
	for (int i = 1; i <= n;i++)
	{
		while(cnt>0&&Land[i].l>needto[cnt].l)
			cnt--;
		needto[++cnt] = Land[i];
	}
	for (int i = 1; i <= n;i++)
		dp[i] = 0x7fffffffffffffff;
	dp[0] = 0;
	int head = 0;
	int tail = 0;
	for (int i = 1; i <= cnt;i++)
	{
		// for (int j = 0; j < i;j++)
		// 	dp[i] = min(dp[i], dp[j] + needto[j + 1].l * needto[i].w);
		while(head<tail&&(dp[q[head]]-dp[q[head+1]]>=(-needto[i].w)*(needto[q[head]+1].l-needto[q[head+1]+1].l)))//别忘了这里面斜率前面那个负号，这是由于你将状态转移方程移项之后斜率会是负值，这个负号以及大于小于搞了我很久
			head++;
		int j = q[head];
		dp[i] = dp[j] + needto[i].w * needto[j + 1].l;
		while(head<tail&&((dp[q[tail]]-dp[q[tail-1]])*(needto[i+1].l-needto[q[tail-1]+1].l)<=(dp[i]-dp[q[tail-1]])*(needto[q[tail]+1].l-needto[q[tail-1]+1].l)))
			tail--;
		q[++tail] = i;
	}
	printf("%lld\n", dp[cnt]);
}
```


---

## 作者：suxxsfe (赞：2)

[my blog](https://www.cnblogs.com/suxxsfe/p/13155273.html)  

https://www.luogu.com.cn/problem/P2900  
$n$ 块地，给出每块的长和宽  
每次可以购买一个或多个地，此次购买的代价是这些地中最大的宽乘以最大的长  
问最小花费多少代价能把所有地都买到  

斜率优化dp  

首先想到，如果有一个地比另一个地的长和宽都要小，显然可以不考虑这块地了  
忽略这种地的过程，可以按 $l$ 为第一关键字，$w$ 为第二来升序排个序，然后用栈维护一下就好  
是这样一个过程：  

```cpp  
std::sort(a+1,a+1+n,cmp);
for(reg int i=1;i<=n;i++){
	while(top&&b[top].w<=a[i].w&&b[top].l<=a[i].l) top--;
	b[++top]=(data){a[i].w,a[i].l};
}
```  

这样处理完以后（按照在 `b` 数组里的顺序来看），$l$ 是单调不减的  
所以 $w$ 应该是单调减，因为如果它不变或者递增的话，就会被当作不用处理的地来忽略掉  

然后一次购买的多块地，在这种排序方式下，一定是连续的  
假设购买了 $x,x+2$ 两块地，那么花费是 $w_x l_{x+2}$，然后又因为 $w_{x+1}<w_x,l_{x+1}\le l_{x+2}$  
所以完全可以在不增加任何代价的情况下将第 $x+1$ 块地包括进去  

那么可以写出dp的转移方程了 $f_i=\min\{f_j+w_{j+1} l_i\}$  
但这样是 $O(n^2)$ 的，还需要个斜率优化  
首先可以确定 $b=f_i$，比较习惯最小化截距，不过题解区里好像还有最小化 $y$ 的？  
然后 $w_{j+1} l_i$ 肯定是解析式里的 $kx$  
而 $k$ 应该和 $i$ 有关，所以 $k=l_i,x=-w_{j+1}$  
那么 $y$ 就是 $f_j$ 了  

所以：$f_j=l_i(-w_{j+1})+f_i$  
因为 $l$ 递增，所以符合 $k$ 递增的条件，可以不用二分  
$w$ 递减，所以 $-w$ 递增，也符合 $x$ 递增的要求  

似乎就可以了，放上代码  

```cpp  
#include<cstdio>
#include<algorithm>
#include<iostream>
#include<cmath>
#include<map>
#include<iomanip>
#include<cstring>
#define reg register
#define EN std::puts("")
#define LL long long
inline int read(){
	register int x=0;register int y=1;
	register char c=std::getchar();
	while(c<'0'||c>'9'){if(c=='-') y=0;c=std::getchar();}
	while(c>='0'&&c<='9'){x=x*10+(c^48);c=std::getchar();}
	return y?x:-x;
}
#define N 50005
struct data{
	LL w,l;
}a[N],b[N];
int top,n;
int tail,head;
int q[N];
LL f[N];
inline int cmp(data a,data b){
	return a.l==b.l?a.w<b.w:a.l<b.l;
}
inline LL get_x(int i){return -b[i+1].w;}
inline LL get_y(int i){return f[i];}
int main(){
	n=read();
	for(reg int i=1;i<=n;i++) a[i].w=read(),a[i].l=read();
	std::sort(a+1,a+1+n,cmp);
	for(reg int i=1;i<=n;i++){
		while(top&&b[top].w<=a[i].w&&b[top].l<=a[i].l) top--;
		b[++top]=(data){a[i].w,a[i].l};
	}
	n=top;
	tail=head=0;q[0]=0;
	for(reg int i=1;i<=n;i++){//k=l[i]
		while(tail<head&&
		get_y(q[tail+1])-get_y(q[tail])<=b[i].l*(get_x(q[tail+1])-get_x(q[tail]))) tail++;
		int j=q[tail];
		f[i]=f[j]+b[j+1].w*b[i].l;
		while(tail<head&&(get_y(q[head])-get_y(q[head-1]))*(get_x(i)-get_x(q[head]))
		>=(get_y(i)-get_y(q[head]))*(get_x(q[head])-get_x(q[head-1]))) head--;
		q[++head]=i;
	}
	std::printf("%lld",f[n]);
	return 0;
}
```

---

## 作者：wangxuye (赞：2)

### 题目链接
[[USACO08MAR]土地征用Land Acquisition](https://www.luogu.org/problemnew/show/P2900)
### 题目大意
每次选一个矩阵集合，代价为最大的$x\times y$，求取完所有矩阵的最小代价。
### 题目思路
首先注意到如果有一个矩阵$i$和一个矩阵$j$，满足$x[i]\leq x[j]$并且$y[i]\leq y[j]$，那么$i$这个矩阵一定会和$j$一起被选，且$i$不会对答案有贡献，所以可以直接删去。  

删完后就只剩下了一些矩阵，且按$x$不降序排序一定会满足$y$单调不升。那么我们现在选矩阵一定是一段连续的区间，因为~~意会一下~~如果选了$i$和$j$，且$i<j$，那么$\forall k\in(i,j)$都有$x[k]\leq x[j]$且$y[k]\leq y[i]$，那么在这时候一起选了不会更差。  

所以可以设$dp[i]$表示选完前$i$个的最小代价。
$$dp[i]=min(dp[j]+x[j+1]\times y[i]),j\in[0,1)$$

这是一个$O(n^2)$的转移，~~然后我就当暴力交了一发，然后获得了90分的好成绩。。。~~显然需要优化。  
注意到$min$里面是一个$dp[j]$还有一个和$i$，$j$都相关的量，自然想到斜率优化。  
因为$x[i]$单调增，$y[i]$单调减，所以用单调队列维护。  
当决策$j$优于决策$k$时，则
$$dp[j]+x[j+1]\times y[i]\leq dp[k]+x[k+1]\times y[i]$$
$$\frac{dp[j]-dp[k]}{-x[j+1]+x[k+1]}\leq y[i]$$
设$Y(i)=dp[i],X(i)=-x[i+1],Slope(i,j)=1.0*(Y(i)-Y(j))/(X(i)-X(j))$  
然后单调队列维护队头队尾，然后。。。就没然后了。  

暴力代码：（$90$分）
```cpp
#include<bits/stdc++.h>
using namespace std;
typedef long long ll;
const int N=100010;
inline ll read();
inline void write(ll x);
inline void writeln(ll x);

int n,cnt=0;
ll dp[N];
struct aa{
	ll x,y;
} field[N],work[N];
inline bool operator<(const aa &a,const aa &b)
{
	if(a.x!=b.x) return a.x<b.x;
	return a.y<b.y;
}

inline ll read()
{
	ll s=0;
	bool flag=false;
	char ch=getchar();
	for(;ch<'0'||ch>'9';ch=getchar()) if(ch=='-') flag=true;
	for(;'0'<=ch&&ch<='9';ch=getchar()) s=(s<<3)+(s<<1)+(ch^48);
	if(flag) return -s;
	return s;
}
inline void write(ll x)
{
	if(!x)
	{
		putchar('0'),putchar(' ');
		return ;
	}
	if(x<0) putchar('-'),x=-x;
	char ch[20];
	int tot=0;
	while(x) ch[++tot]=x%10,x/=10;
	for(int i=tot;i;i--) putchar(ch[i]^48);
	putchar(' ');
}
inline void writeln(ll x)
{
	write(x);
	putchar('\n');
}

int main()
{
	n=read();
	for(int i=1;i<=n;i++) field[i].x=read(),field[i].y=read();
	sort(field+1,field+n+1);
	for(int i=1;i<=n;i++)
	{
		while(cnt&&field[i].y>=work[cnt].y) cnt--;
		work[++cnt]=field[i];
	}
	n=cnt;
	memset(dp,0x3f,sizeof(dp));
	dp[0]=0;
	for(int i=1;i<=n;i++)
	{
		for(int j=1;j<=i;j++)
		{
       		dp[i]=min(dp[i],dp[j-1]+work[i].x*work[j].y);
		}
	}
	writeln(dp[n]);
	return 0;
}
```

$100$分代码：
```cpp
#include<bits/stdc++.h>
using namespace std;
typedef long long ll;
const int N=100010;
inline ll read();
inline void write(ll x);
inline void writeln(ll x);

int n,cnt=0;
int q[N],head=1,tail=0;
ll dp[N];
struct aa{
	ll x,y;
} field[N],work[N];
inline bool operator<(const aa &a,const aa &b)
{
	if(a.x!=b.x) return a.x<b.x;
	return a.y<b.y;
}
#define Y(i) (dp[(i)])
#define X(i) (-work[(i)+1].y)
#define Slope(i,j) 1.0*(Y(i)-Y(j))/(X(i)-X(j))
#define calc(i,j) (dp[(j)]+work[i].x*work[j+1].y)

inline ll read()
{
	ll s=0;
	bool flag=false;
	char ch=getchar();
	for(;ch<'0'||ch>'9';ch=getchar()) if(ch=='-') flag=true;
	for(;'0'<=ch&&ch<='9';ch=getchar()) s=(s<<3)+(s<<1)+(ch^48);
	if(flag) return -s;
	return s;
}
inline void write(ll x)
{
	if(!x)
	{
		putchar('0'),putchar(' ');
		return ;
	}
	if(x<0) putchar('-'),x=-x;
	char ch[20];
	int tot=0;
	while(x) ch[++tot]=x%10,x/=10;
	for(int i=tot;i;i--) putchar(ch[i]^48);
	putchar(' ');
}
inline void writeln(ll x)
{
	write(x);
	putchar('\n');
}

int main()
{
	n=read();
	for(int i=1;i<=n;i++) field[i].x=read(),field[i].y=read();
	sort(field+1,field+n+1);
	for(int i=1;i<=n;i++)
	{
		while(cnt&&field[i].y>=work[cnt].y) cnt--;
		work[++cnt]=field[i];
	}
	n=cnt;
	memset(dp,0x3f,sizeof(dp));
	dp[0]=0;
	q[++tail]=0;
	for(int i=1;i<=n;i++)
	{
		for(;head<tail&&Slope(q[head],q[head+1])<=work[i].x;head++);
		dp[i]=calc(i,q[head]);
		for(;head<tail&&Slope(q[tail-1],q[tail])>=Slope(q[tail],i);tail--);
		q[++tail]=i;
	}
	writeln(dp[n]);
	return 0;
}
```


---

## 作者：是个汉子 (赞：2)

[洛谷传送门](https://www.luogu.com.cn/problem/P2900)

### Solution

发现对于一块土地 $x$ 和 $y$ ，如果 $l_y\geq l_x,h_y\geq h_x$ ，那么把 $x$ 和 $y$ 合在一组对答案是不会更劣的。

将土地按照长度和宽度排序，维护一个栈，将有必要存在的土地留下。

在最优决策下，每一组土地都是连续的。因为如果有 $x,y,z$ 三块连续土地，并且 $l_x<l_y<l_z,h_x>h_y>h_z$ ，把 $x$ 和 $z$ 一组， $y$ 自己一组，花费为 $h_x\cdot l_z+h_y\cdot l_y$ ，三个一组花费是 $h_x\cdot l_z$ ，显然更优。

考虑DP。设 $f_i$ 表示前 $i$ 个土地的最小费用，易得： $f_i=\min\{f_i,f_{j}+h_{j+1}\cdot l_{i}\}$ ，但是时间复杂度为 $O(n^2)$ ，过不去，考虑优化。

用斜率优化。设 $k=h_{j+1},b=f_j$ ，那么直线为 $y=kx+b$ ，那么之前的转移方程就相当于求 $x=l_i$ 时的 $y_{min}$ 

### Code

```c++
#include<cmath>
#include<cstdio>
#include<iostream>
#include<cstring>
#include<algorithm>
#define int long long

using namespace std;
const int N=5e4+10;
int n,a[N],b[N],f[N],q[N],hd,tl,stk[N],top;
struct node{
    int a,b;
    bool operator < (const node &x) {
        return a==x.a?b<x.b:a<x.a;
    }
}p[N];

inline int slope(int p,int t){
    return f[p]+a[t]*b[p+1];
}

inline bool cross(int t1,int t2,int i){
    return 1ll*(f[t1]-f[t2])*(b[i+1]-b[t1+1])<1ll*(f[i]-f[t1])*(b[t1+1]-b[t2+1]);
}

signed main(){
    scanf("%lld",&n);
    for(int i=1;i<=n;i++) scanf("%lld%lld",&p[i].a,&p[i].b);
    sort(p+1,p+n+1);
    stk[++top]=1;
    for(int i=2;i<=n;i++){
        while(top&&p[i].b>=p[stk[top]].b) --top;
        stk[++top]=i;
    }
    n=top;
    for(int i=1;i<=n;i++) a[i]=p[stk[i]].a,b[i]=p[stk[i]].b;
    hd=tl=0;
    for(int i=1;i<=n;i++){
        while(hd<=tl&&slope(q[hd],i)>slope(q[hd+1],i)) ++hd;
        f[i]=f[q[hd]]+a[i]*b[q[hd]+1];
        while(hd<=tl&&cross(q[tl],q[tl-1],i)) --tl;
        q[++tl]=i;
    }
    printf("%lld\n",f[n]);
    return 0;
}
```



---

## 作者：l_x_z2020 (赞：2)

本题适合刚接触并已经理解斜率优化+DP原理和过程的选手上手练习。


------------
看了题目，打包购买土地，价值为最大长与最大宽之积。这个地方就是本题的难点所在。

两块土地的长（a）与宽（b）共有下面几种情况：

1.两块土地长与宽大小分别相交。 即：a1<a2&&b1>b2或者a1>a2&&b1<b2
                                            
2.一块土地包含另一块。 即：a1<a2&&b1<b2或者a1>a2&&b1>b2;

第二种情况可以看出来，**被包含**的那一块土地实际上是可以与那块**包含**它的**大土地**一起购买，这样小土地价值即为0，称为“**免费购买**”

所以，在这样的情况下，我们可以以长度**从小到大**排序，借助一个单调栈，维护每块土地宽的**单调递减**（因为新进元素长度必定大于栈内元素，而宽度只要大于栈顶，即可包含该土地，使其价值为0，弹出。）

代码：
```cpp
for(i=1;i<=n;i++)scanf("%lld%lld",&p[i].a,&p[i].b);
sort(p+1,p+n+1,cmp);
for(i=1;i<=n;i++)
{
    while(top&&p[s[top]].b<=p[i].b)top--;
    s[++top]=i;
}
```


这样的话所有元素就仅仅剩下第一种情况了，我们可以用DP来考虑 。

设f[i]为购买第1~i块土地最小总价值

1.时间复杂度：O（n^2）

我们将栈内的元素由i从1到栈顶（top）枚举，j枚举0~i-1中元素，表示由第j块土地开始，将价值转移到f[i]上去

方程为：f[i]=f[j]+p[i].a*p[j+1].b（1<=i<=top&&0<=j<i）

(此刻最大的长必定是p[i].a,因为我们已经排过序了。最大的宽即为p[j+1].b,因为从0开始且由于单调栈以维护了1~j之间j元素的宽最大)

这时再看数据 1 ≤ N ≤ 50000  ~~（啊，推了这么久的初始化就炸了吗？！）~~

很容易可以看出来这时我们即可运用一种优化方法——**斜率优化**

------------
请读者在阅读一下思路前先了解一下斜率优化原理 ~~（否则可能会引起不适）~~

[留下一位大佬链接](https://blog.csdn.net/bill_yang_2016/article/details/54667902)

2.时间复杂度：O（n）

我们一样将i从1到top枚举，这时我们将i看做一个定值，把含有j的值表示出来，即可得到转移方程：

f[j]=-p[i].a*p[j+1].b+f[i];

乍一看，这有点像我们初中学的一次函数：y=kx+b

由于i确定，所以-p[i].a与f[i]均确定，而f[j]，p[j+1].b此时就成了变量。

因此y=f[j], x=p[j+1].b, k=-p[i].a, b=f[i],这个k的绝对值也就是我们所讲的斜率了。

于是我们大致得到这样一个函数图像：~~（初中数学不要问我为什么）~~
![无标题.png](https://i.loli.net/2019/06/14/5d0302a12d7d566617.png)
但在实际计算中，由于一个一个元素遍历，我们就必须维护这样一条直线，使得当前状态f[i]最小（回归题目所求）。

函数中：f[j]=-p[i].a*p[j+1].b+f[i];

当f[i]↓，f[j],p[j+1].b保持不变，则-p[i].a↑，即abs（-p[i].a）=p[i].a↓（用数学知识仔细想下）

所以我们要在算法中尽量维护斜率更小，这时可以用到数据结构：单调队列。
维护一个斜率递减的集合
即：

这时新进入一个元素，将存在这样两种情况需要维护

1.![无标题1.png](https://i.loli.net/2019/06/14/5d02f944ec70894916.png)

我们发现新进元素斜率必定小于队首，将其延长
![无标题2.png](https://i.loli.net/2019/06/14/5d02fa43e5b7431133.png)
则当前斜率下的直线与y轴交点即为b，也就是f[i],显然当前状态f[i]小于队首状态，维护单调性，将前面出队，只留下队尾元素和新进元素这一最优策略
代码：
```cpp
while(l<r&&f[s[q[l+1]]]-f[s[q[l]]]<=(p[s[q[l]+1]].b-p[s[q[l+1]+1]].b)*(p[s[i]].a))l++;
```
此时的队首元素j=q[l]即为最优决策，转移出f[i]的值
```cpp
j=q[l];
f[s[i]]=f[s[j]]+p[s[i]].a*p[s[j+1]].b;
```
2.![无标题4.png](https://i.loli.net/2019/06/14/5d02fe875b7ff91302.png)
可以发现此时有一个上凸点，不论直线斜率为多少，最优决策不可能是R，所以将其出队，并继续维护队尾的单调性。
```
while(l<r&&(f[s[q[r]]]-f[s[q[r-1]]])*(p[s[i+1]].b-p[s[q[r]+1]].b)<=(f[s[i]]-f[s[q[r]]])*(p[s[q[r]+1]].b-p[s[q[r-1]+1]].b))r--;
```
（这里代码看不懂程序里还有详解）
最后，我们再将当前元素i进队就可以啦！

上代码：
```cpp
#include<iostream>
#include<cstdio>
#include<cstring>
#include<algorithm>
using namespace std;
int n,q[2000005],s[2000005],top;long long f[50005];
struct node{
    long long a,b;
}p[50005];
bool cmp(node x,node y)
{return x.a<y.a;}//这里最好不用operator，有些网站编译器可能会CE
int main()
{
    int i,j,k,x,y;
    cin>>n;
    for(i=1;i<=n;i++)scanf("%lld%lld",&p[i].a,&p[i].b);
    sort(p+1,p+n+1,cmp);//按长度排序
    for(i=1;i<=n;i++)
    {
        while(top&&p[s[top]].b<=p[i].b)top--;
        s[++top]=i;
    }//初始化免费土地
    int l=0,r=0;
    for(i=1;i<=top;i++)
    {
        while(l<r&&f[s[q[l+1]]]-f[s[q[l]]]<=(p[s[q[l]+1]].b-p[s[q[l+1]+1]].b)*(p[s[i]].a))l++;//判断队首斜率与当前斜率大小关系，注意不等式符号的变化
        j=q[l];
        f[s[i]]=f[s[j]]+p[s[i]].a*p[s[j+1]].b;//状态转移
        while(l<r&&(f[s[q[r]]]-f[s[q[r-1]]])*(p[s[i+1]].b-p[s[q[r]+1]].b)<=(f[s[i]]-f[s[q[r]]])*(p[s[q[r]+1]].b-p[s[q[r-1]+1]].b))r--;//判断当前斜率与队尾关系，这里最好在草稿上解一解，符号的变化很可能导致错误
        q[++r]=i;
    }
//注意：1.我是将/号全换做了*号（看着舒服点）读者也可直接用tan三角函数计算斜率。
//	2.这里s数组存的是编号，i遍历的是栈的编号，关于i的引用，队列等均需套一个s数组。
    printf("%lld\n",f[s[top]]);//输出
}
```
小结：当见到一道斜率优化题，可以先将这道题的暴力代码和思路想出来，再根据暴力的状态转移方程，将i值确定，用函数方式表示枚举的j状态，将y，x与斜率分别指代的数值明确，注意在斜率以及截距b必须以带i的状态表示（因为已确定），带入套路求解即可。

---

## 作者：BillYang (赞：2)

剔除无用土地后进行动规

f[i]=min{f[j]+x[i]\*y[j+1]}

维护下凸包性质

详细见http://blog.csdn.net/bill\_yang\_2016/article/details/54864284

代码
```cpp
#include<algorithm>
#include<iostream>
#include<iomanip>
#include<cstring>
#include<cstdlib>
#include<vector>
#include<cstdio>
#include<cmath>
#include<queue>
using namespace std;
typedef long long LL;
inline const int Get_Int() {
    LL num=0,bj=1;
    char x=getchar();
    while(x<'0'||x>'9') {
        if(x=='-')bj=-1;
        x=getchar();
    }
    while(x>='0'&&x<='9') {
        num=num*10+x-'0';
        x=getchar();
    }
    return num*bj;
}
struct Land {
    LL x,y;
    bool operator < (const Land& b) const {
        return (x==b.x&&y<b.y)||(x<b.x);
    }
} a[50005],b[50005];
LL n,cnt=0,f[50005],Q[50005];
double Slope(LL j,LL k) {
    return (double)(f[j]-f[k])/(b[k+1].y-b[j+1].y);
}
int main() {
    n=Get_Int();
    for(int i=1; i<=n; i++) {
        a[i].x=Get_Int();
        a[i].y=Get_Int();
    }
    sort(a+1,a+n+1);
    for(int i=1; i<=n; i++) { //去除无用土地 
        while(cnt>0&&a[i].y>=b[cnt].y)cnt--;
        b[++cnt]=a[i];
    }
    int Left=1,Right=1;
    Q[1]=0;
    for(int i=1; i<=cnt; i++) {
        while(Left<Right&&Slope(Q[Left],Q[Left+1])<=b[i].x)Left++; //维护队首（删除非最优决策）
        int Front=Q[Left];
        f[i]=f[Front]+b[i].x*b[Front+1].y;
        while(Left<Right&&Slope(Q[Right-1],Q[Right])>=Slope(Q[Right],i))Right--; //维护队尾（维护下凸包性质）
        Q[++Right]=i;
    }
    printf("%lld\n",f[cnt]);
    return 0;
}

```

---

## 作者：HH_Halo (赞：1)

# [HH_Halo](https://www.cnblogs.com/hhhhalo/p/13512988.html)
## 思路分析
* 显然如果直接按原序列下手会很棘手，所以我们首先要将序列排好序
  * 为了方便合并，所以我们以长为关键字进行排序，这时候好像还是有点无从下手，所以尝试找一些性质
  * 不难想到，如果一块土地的长和宽均小于某一块土地，那这块土地其实是不会对答案产生任何影响的，所以我们在排好序以后可以将其去除，而只留下合并时会改变长宽的
  * 在进行完的排序和去除操作以后，这时候的序列一定满足这样的性质:**长是递减的，而宽是递增的**(自己模拟一下就好)
* 那么此时，对于一段区间，我们只需要取两端即可，因为一个长最大，一个宽最大，区间内的自然就一起合并了
  * 由此得出转移方程: $f[i] = min(f[i],f[j-1]+x_j*y_i)$  $(0<j<i)$($x$ 为长，$y$ 为宽)
  * 变一下型就是 $f[j-1]=f[i]-y_i*x_j$，这样就是一个很简单的可以进行斜率优化的式子了，斜率为 $y_i$

## $Code$
```c++
#include<cstdio>
#include<cstring>
#include<cmath>
#include<algorithm>
#define N 50010
using namespace std;
inline int read(){
	int x = 0,f = 1;
	char ch = getchar();
	while(ch>'9'||ch<'0'){if(ch=='-')f=-1;ch=getchar();}
	while(ch>='0'&&ch<='9'){x=(x<<1)+(x<<3)+(ch^48);ch=getchar();}
	return x*f;
}
int n,q[N];
long long f[N];
struct farm{
	int x,y;
}a[N];
inline bool cmp(farm a,farm b){
	return a.x==b.x ? a.y>b.y : a.x>b.x;
}
double slope(int x,int y){
	return (double)(f[x]-f[y])/(double)(a[y+1].x-a[x+1].x);
}
int main(){
	n = read();
	for(int i = 1;i <= n;i++){
		a[i].x = read(),a[i].y = read();
	}
	sort(a+1,a+1+n,cmp);
	int tot = 0;
	for(int i = 1;i <= n;i++)if(a[i].y>a[tot].y)a[++tot] = a[i]; //去除操作
	n = tot;
	int head = 0,tail = 0;
	for(int i = 1;i <= n;i++){ //按转移方程直接上斜率优化即可
		while(head<tail&&slope(q[head],q[head+1])<=a[i].y)head++;
		f[i] = f[q[head]]+1ll*a[q[head]+1].x*a[i].y;
		while(head<tail&&slope(q[tail-1],q[tail])>=slope(q[tail],i))tail--;
		q[++tail] = i;
	}
	printf("%lld",f[n]);
	return 0;
}
```

---

## 作者：LlLlCc (赞：1)

非常经典的斜率优化板子题，可以作为斜率优化的例题来讲解

------------
首先要明确，分组不需要连续，也就是说我们可以打乱顺序

所以什么顺序更方便我们求解问题呢？

显然，对于第$i$块土地，如果存在$j$，满足$w_{i}<=w_{j}$且$L_{i}<=L_{j}$，那么就可以忽视第$i$块土地

所以我们可以按$w$从小到大排序，如果$w$相同将$L$小的放在前面，排位序后，序列满足对于任意的$i$，满足$w_{i}<=w_{j}$且$L_{i}<=L_{j}$的$j$必定满足$\large j>i$，也就是其右边的所以土地$w$都比他大

这时我们只要知道右边是否有$L$比他大的就好，所以我们只要倒着枚举，记录一下当前的$L$最大值即可

现在序列已经满足了对于任意的$i,j(i<j)$，都满足$w_{i}<=w_{j},L_{i}>=L_{j}$

设： $\large f_{i}:$购买前$i$块地所需的最小值

转移方程也很容易：

$\Large f_{i}=\min(f_{j}+w_{i}\cdot L_{j+1})$

会斜率优化的大佬一眼就看出来了这个可以用斜率优化快速解决

不会也没关系，我们慢慢推

设两个决策$\large j_1,j_2$，且决策$\large j_1$优于决策$\large j_2$

即：


$\qquad \LARGE f_{j_1}+w_{i}\cdot L_{j_{1}+1}<f_{j_2}+w_{i}\cdot L_{j_{2}+1}$

$\LARGE =f_{j_1}-f_{j_2}<+w_{i}\cdot (L_{j_{2}+1}-L_{j_{1}+1})$

$\LARGE =f_{j_1}-f_{j_2}<+w_{i}\cdot (L_{j_{2}+1}-L_{j_{1}+1})$

$\LARGE =\dfrac{f_{j_1}-f_{j_2}}{L_{j_{2}+1}-L_{j_{1}+1}}<+w_{i}$

然后就是个典型的斜率优化

参考代码：
```
#include<bits/stdc++.h>
#define maxn 500005
#define ll long long
using namespace std;
int n,tot,N,Q[maxn],hed=1,til=1;
ll Ans,f[maxn];
struct lc{
	ll x,y;
	bool operator <(const lc b)const{return x<b.x||(x==b.x&&y<b.y);}
}A[maxn],B[maxn];
inline int read(){
	int ret=0;char ch=getchar();
	while (ch<'0'||ch>'9') ch=getchar();
	while (ch<='9'&&ch>='0') ret=ret*10+ch-'0',ch=getchar();
	return ret;
}
inline double Get(int x,int y){return (double)1.00*(f[x]-f[y])/(B[y+1].y-B[x+1].y);}
int main(){
	n=read();
	for (int i=1;i<=n;i++) A[i].x=read(),A[i].y=read();
	sort(A+1,A+n+1);ll Mx=0;
	for (int i=n;i;i--){
		if (A[i].y<=Mx) continue;
		B[++N].x=A[i].x,Mx=B[N].y=A[i].y;
	}
	sort(B+1,B+N+1);
	for (int i=1;i<=N;i++){
		while (hed<til&&(double)Get(Q[hed],Q[hed+1])<=B[i].x) hed++;
		f[i]=f[Q[hed]]+B[i].x*B[Q[hed]+1].y;
		while (hed<til&&(double)Get(Q[til-1],Q[til])>=Get(Q[til],i)) til--;
		Q[++til]=i;
	}
	printf("%lld",f[N]);
	return 0;
}
```


---

## 作者：rhdeng (赞：1)

[传送~](https://www.luogu.org/problemnew/show/P2900)

## Description

有$n$块土地,每块土地的长和宽分别为$l_i,w_i$.土地可以单独买也可以一起买.当购买的土地的组合为集合$S(size_S\geq 1)$时, 价格为$S$中**最大的长\*最大的宽**,即$l_{max}*w_{max}$ .求购买所有土地的最小费用.

$n\leq 5*10^4,l_i,w_i\leq 10^6$

## Solution

初看到这道题,我是****的,也列不出任何转移方程.但这毕竟是道斜率优化题,于是我们就要有点斜率优化的样子,于是...

### 操作一

由于费用与一组土地中长和宽的**最大值**有关,所以我们可以先将一维(如宽)拍好序,那么$w_i$即为$1$至$i$中的$w_{max}$.当$i$与$1$至$(i
-1)$的土地组合时,费用的一维就确定了.

尽管一维确定了,但由于可以随意组合,另一维是不确定的,所以我们仍毫无头绪.

### 结论一

接着由题意~~显然~~可以得到第一个结论:当$l_i\leq l_j$且$w_i\leq w_j$时$i$对费用是没有贡献的.所以我们可以把这样的土地**删除**.

为什么?

当$j$被购买时,设费用为$l_0*w_0,l_0\geq l_j,w_0\geq w_j$.若将$i$与$j$一同购买,费用是**不会增加的**.所以我们在购买$j$时自动购买$i$,就可以把$i$删掉了.

但这跟斜率优化,甚至跟DP有什么关系呢?

### 操作二

利用我们的排序操作和第一个结论,我们可以得到一个**宽单调递增,长单调递减**的土地的序列.~~宽单调递增很容易理解,因为这是排序的关键字~~.但为什么长单调递减?

因为排序后$\forall 1\leq j<i,w_j<w_i$,所以只要当$l_j\leq l_i$时,$j$就可以被删掉了.所以我们用单调栈维护,使栈中$l$递减.从前往后扫,扫到$i$时,把小于$l_i$的都弹掉.

### 结论二

这时我们就可以得到第二个结论了:每一个购买组合都必须是一段**连续**的土地序列.

为什么?

我们设$j<i$,若$i$与$j$一起买,由上面的一系列操作,我们可以知道价格为$w_i*l_j$.对于$\forall j<k<i$,由于**宽单调递增,长单调递减**,故$w_k<w_i,l_k<l_j$,所以$k$对于费用是没有影响的,所以我们不妨把这些$k$与$i$和$j$一起买,即购买区间$[j,i]$.

终于,我们可以开始推式子了...

### DP

设$f_i$为前$i$块土地都购买了的最小费用.由上面一波操作,我们可以得到如下的转移方程

$$f_i=\max_{1\leq j<i}\{f_j+w_i*l_{j+1}\}$$

在区间$(j,i]$中,$w_{max}=w_i,l_{max}=l_{j+1}$,故转移费用为$w_i*l_{j+1}$.

这已经不是斜率优化~~入门题~~了,所以我们直接上套路.

我们设$j>k$, 若从$j$转移比$k$更优,则必须满足
$$\begin{aligned}f_j+w_i*l_{j+1}&<f_k+w_i*l_{k+1}\\\Rightarrow f_j-f_k&<w_i*(l_{k+1}-l_{j+1})\\\Rightarrow \frac{f_j-f_k}{l_{k+1}-l_{j+1}}&<w_i\end{aligned}$$

由于$j>k$,$l$单调递减,故$l_{k+1}-l_{j+1}>0$,可以直接除过去.

很容易发现这是一次函数的点斜式.我们设$slope(j,k)$为上面的左式,即斜率.则当$j>k$且$slope(j,k)<w_i$时,$j$比$k$优.由于$w_i$单调递增,我们可以用单调队列维护斜率,使$slope(i+1, i)$单调递增,且队首最优.

## Code
```cpp
#include <bits/stdc++.h>
using namespace std;
const int maxn = 5e4;
typedef long long ll;
int n, cnt, l, r, q[maxn+10], tag[maxn+10];
ll f[maxn+10];
struct land {
	int wid, len;
} a[maxn+10], b[maxn+10];
int cmp(land x, land y) {
	return x.wid != y.wid ? x.wid < y.wid : x.len < y.len;
}
double slope(int j, int k) {
	return 1.0*(f[j]-f[k])/(b[k+1].len-b[j+1].len);
}
int main() {
	scanf("%d", &n);
	for (int i = 1; i <= n; ++i)
		scanf("%d%d", &a[i].wid, &a[i].len);
	sort(a+1, a+1+n, cmp); //按w排序
	for (int i = 1; i <= n; ++i) {
		while (cnt && a[i].len >= b[cnt].len) --cnt;
		b[++cnt] = a[i];
	} //单调栈
	for (int i = 1; i <= cnt; ++i) {
		while (l < r && slope(q[l+1], q[l]) < b[i].wid) ++l; //此时q[l]比q[l+1]更劣,由于x[i]递增,故之后一直更劣,弹出
		f[i] = f[q[l]]+1ll*b[i].wid*b[q[l]+1].len; //记得要1ll
		while (l < r && slope(q[r], q[r-1]) > slope(i, q[r])) --r; //保持队列中斜率单调递增
		q[++r] = i; 
	}
	printf("%lld\n", f[cnt]); //一定记得开longlong
	return 0;
}
```

> *THANK YOU FOR READING THIS!*

---

## 作者：QiFeng233 (赞：1)

# 前言

斜率优化的一道好题，同时具有一定的思维难度，适合作为斜率优化的入门练手题

# 思路分析

首先题目说代价是每组里最大的长乘上最大的宽，那么这也就意味着，对于任意一块土地，如果能找到另一块长和宽都比它大的土地，那么原来这块较小的土地是可以白嫖的~~下次一定~~（滑稽）

而具体的做法呢，就是先把所有土地按长为第一关键字，宽为第二关键字来升序排序，排序之后维护一个以宽度为关键字的单调递减的单调栈，到最后单调栈里的所有的元素就是真正能对答案产生贡献的元素了。

用 $x,y$ 表示长和宽，$f_i$ 表示前 $i$ 组土地的最小代价那么状态转移方程显而易见：

$f_i=\min(f_i,f_j+x_iy_{j+1})$

看起来这就是个斜率优化。把他写成直线方程的形式：

$f_j=-x_iy_{j+1}+f_i$

可是，好像第一眼看上去横坐标$y_{j+1}$和斜率$-x_i$都不是单调递增的啊，怎么用优先队列来维护凸壳呢？这也是我这个蒟蒻第一眼的直观想法。

>如果大山不会走向穆罕穆德，穆罕穆德可以走向大山

我们自己主动地变换一下思维方式，横坐标改为$-y_{j+1}$，斜率改为$x_i$，他们都单调递增，可以用优先队列维护。

至此，问题全部解决了，接下来就是斜率优化板子了。

# 代码时间
```cpp
#include<bits/stdc++.h>
using namespace std;
namespace QiFeng233{
	const int maxn=5e4+10;
	int n,q[maxn],head=1,tail=1;
	long long f[maxn];
	struct land{long long x,y;}a[maxn];
	stack<land> stk;
	bool operator<(land ld1,land ld2){return ld1.x==ld2.x?ld1.y<ld2.y:ld1.x<ld2.x;}
	double K(int i,int j){
		return -1.0*(f[i]-f[j])/(a[i+1].y-a[j+1].y);
	}
	void solve(){
		scanf("%d",&n);
		for(int i=1;i<=n;++i)scanf("%lld%lld",&a[i].x,&a[i].y);
		sort(a+1,a+n+1);
		for(int i=1;i<=n;++i){
			while(!stk.empty()&&stk.top().y<=a[i].y)stk.pop();
			stk.push(a[i]);
		}
		n=stk.size();
		for(int i=n;i;--i)a[i]=stk.top(),stk.pop(); 
		//y=f[j],k=a[i].x,x=(-a[j+1].y),b=-f[i]
		for(int i=1;i<=n;++i){
			while(head<tail&&K(q[head],q[head+1])<=a[i].x)++head;
			f[i]=f[q[head]]+a[i].x*a[q[head]+1].y;
			while(head<tail&&K(q[tail-1],q[tail])>=K(q[tail],i))--tail;
			q[++tail]=i;
		}
		printf("%lld",f[n]);
	}
}
signed main(){
	QiFeng233::solve();
	return 0;
}
```

---

## 作者：aiyougege (赞：1)

#### Solution
　　发现如果两块土地$a,b$满足$w_a\le w_b$并且$h_a\le h_b$.那么a完全是不需要的单独购买的.所以对于这样的$a$完全可以去掉因为不会对答案产生影响.

　　考虑怎么去掉这些$a$, 我们可以这么做, 将所有土地按长度排序, 若有一土地$i$满足$w_i\le w_{i-1}$, 因为按长度排序后$h_i\le h_{i-1}$.

　　将剩下的按长度或宽度从大到小排序会发现一件有趣的事情.   
![不能上传svg差评](https://cdn.luogu.com.cn/upload/pic/18939.png)
发现我们购买所有土地需要做的就是将排序后相邻的几块土地一起购买.所以就可以列出这样一个状态转移方程.
$$f(i)=\min f(j)+h_{j+1}\cdot w_{i},j<i$$
然而$n$太大以至于我们就只能开心的**斜率优化**了.

$$f(j)+h_{j+1}w_i>f(k)+h_{k+1}w_i$$
$$\Rightarrow w_i>\frac{f(k)-f(j)}{h_{j+1}-h_{k+1}}$$

然后开心的写完代码就开心的通过了这道题.所以这还是一个套路化的题目.
不会斜率优化的同学可以先看一下[斜率优化](https://www.luogu.org/blog/aiyoupass/solution-p3195).
#### Code
```c++
#include<algorithm>
#include<iostream>
#include<cstdio>
#define N 50005
#define int long long//这个题1e6*1e6会爆int
using namespace std;

int n,m;
struct Node{
    int h,w;//长度和宽度
    bool operator<(const Node &s)const{
        return h>s.h;
    }
}a[N],b[N];
namespace Sort{
    void init(){//用来去除无用的土地
        m=0;
        scanf("%lld",&n);
        for(int i=1;i<=n;++i)
            scanf("%lld%lld",&a[i].h,&a[i].w);
        sort(a+1,a+n+1);
        for(int i=1;i<=n;++i)
            if(a[i].w>b[m].w)
                b[++m]=(Node){a[i].h,a[i].w};
    }
};

int q[N],f[N];
int h,t;

double slope(int j,int k){
    return (double)(f[k]-f[j])/(double)(b[j+1].h-b[k+1].h);
}

main(){
    Sort::init();
    for(int i=1;i<=m;i++){
        while(h<t&&slope(q[h],q[h+1])<=b[i].w)h++;//将不满足式子w_i>balabala的剔除
        f[i]=f[q[h]]+b[i].w*b[q[h]+1].h;//计算当前答案
        while(h<t&&slope(q[t-1],q[t])>=slope(q[t],i))t--;//将当前状态插入
        q[++t]=i;
    }
    printf("%lld\n",f[m]);
    return 0;
}
```

---

## 作者：楠枫 (赞：0)

## 题解
不难想到本题要用 $DP$，但是它恶心在哪里就是如何处理最长成最宽。  

对于两块土地有以下两种可能：
$$
a_i \le a_j  (and)b_i \ge b_j
$$
$$
a_i \le a_j  (and)b_i \le b_j
$$
$a_i,a_j$ 表示长， $b_i,b_j$ 表示宽

(其余情况可转化为这两种情况)

此时对于第二种情况，我们可以发现 $i$ 这块土地可以被 $j$ 块土地包裹，所以 $i$ 块土地价格为 $0$ 。所以我们将 $i$ 块土地视为 $j$ 块土地的一部分。

此时我们可以进行一次预处理，先对长进行由小到大的排序（其实宽也可以），然后用单调队列维护宽单调递减。

因为长已经是单调递增的了，所以对于每一个将要进栈的元素，如它的宽比栈顶的宽大，则说明栈顶的土地一定能被新加入的土地所包裹，所以将栈顶弹出。  

 $CODE:$ 
 ```cpp
 struct earth{
	int c,k;
	bool operator<(const earth &e) const{
		if (e.c==c) return e.k>k;//小于等于也可以包裹，这句话很重要
		return e.c>c;
	}
}e[N],b[N];
void init() {
	sort(e+1,e+1+n);
	for (int i=1;i<=n;i++) {
		while(top&&e[s[top]].k<=e[i].k) top--;
		s[++top]=i;
	}
	for (int i=1;i<=top;i++) {
		b[i]=e[s[i]];//建议重新储存一下栈内元素，否则在进行dp的时候数组会套很多层，容易出错
	} 
}
 ```
处理完后就可以进行 $dp$ 了，这是只用对栈内元素操作。方程为：
$$
f_i=f_j+b_{j+1}×a_i
$$
其中 $(i > j)$ ， $f_i$ 表示选到第 $i$ 块土地所花最小费用，同时将 $j+1$ 到 $i$ 块土地打包为一组

因为长已经按着有小到大排序，宽按照由大到小排序，所以在 $j+1$ 到 $i$ 的土地中 $i$ 的长最大， $j+1$ 的宽最大。

再对方程进行观察，发现 $b_{j+1}×c_i$ 符合斜率优化的条件（安利一位大佬讲斜率优化的博客[辰星凌](https://www.cnblogs.com/Xing-Ling/p/11210179.html)）

$k=c_i,x=b_{j+1},y=f_j$ ，注意要保证 $x$ 递增。化简完后
$$
f_j=-b_{j+1}×c_i+f_i
$$
发现因为要维护最小值，所以我们要维护一个下凸包。

$AC \kern 0.5em CODE:$
```cpp
#include<bits/stdc++.h>
#define int long long//直接开long long
using namespace std;
const int N=50500;
inline int read() {
	int x=0,f=1;char ch=getchar();
	while(ch<'0'||ch>'9'){if (ch=='-') f=-1;ch=getchar();}
	while(ch>='0'&&ch<='9'){x=(x<<1)+(x<<3)+(ch^48);ch=getchar();}
	return x*f;
}
int n,s[N],que[N],top,f[N];
struct earth{
	int c,k;
	bool operator<(const earth &e) const{
		if (e.c==c) return e.k>k;//注意
		return e.c>c;
	}
}e[N],b[N];
void init() {
	sort(e+1,e+1+n);
	for (int i=1;i<=n;i++) {
		while(top&&e[s[top]].k<=e[i].k) top--;
		s[++top]=i;
	}
	for (int i=1;i<=top;i++) {
		b[i]=e[s[i]];
	} 
}
inline int x(int i) {return b[i+1].k;}
inline int y(int i) {return f[i];}
inline long double slope(int i,int j) {return (long double)(y(i)-y(j))/(x(i)-x(j));}
signed main() {
	n=read();
	for (int i=1;i<=n;i++) e[i].c=read(),e[i].k=read();
	init();
	int h=1,t=0;que[++t]=0;
	for (int i=1;i<=top;i++) {
		while(h<t&&slope(que[h+1],que[h])>=-b[i].c) h++;//我懒得把bi写成负的了，所以两边同乘了一个-1
		f[i]=f[que[h]]+b[que[h]+1].k*b[i].c;
		while(h<t&&slope(i,que[t])>=slope(que[t],que[t-1])) t--;//维护下凸包
		que[++t]=i;
	}
	printf("%lld\n",f[top]);
	return 0;
}
```

---

## 作者：MuYC (赞：0)

#### [这里体验更好哦](https://www.cnblogs.com/MYCui/p/13947754.html)


#### 题意简化：
给定许多个二元对，你可以把若干个二元对$(x,y)$归为一类，对于同一组的所有二元对，你需要付出同组内最大$x$乘以最大$y$的费用，求一种分组使得费用最少。

#### 思路:

先贪心一下，按照$x$从小到大排序，$x$相同的就按照$y$的升序排序，这时候我们会得到一个$x$单调上升的二元对序列。

倘若一个点$i$它的$x$小于等于点$j$的$x$并且它的$y$小于等于点$j$的$y$，那么很显然，这个点$i$就废了，因为把$i$和$j$放一组即可使得$i$完全失去对答案贡献的能力///

把那一些“废掉”的点全部删掉，我们得到的就会是一个$x$单调上升，$y$单调下降的二元组序列。

然后，我们的$DP$就出来了

状态设立:$dp[i]$表示把前$i$个二元组分好组需要的最小花费。

状态转移：$dp[i] = min(dp[i],dp[j] + x[i] * y[j + 1])(j < i)$

因为按照前面的排序以及删除元素，序列变为了$x$单调上升，$y$单调下降的二元组序列，所以直接按照这个方式转移即可。

考虑如何使用大杀器：斜率优化。

这个柿子都不用拆了，直接就已经帮我完成一半的工程了。。

然后思考，假如决策点$k$优于决策点$j$，$k$以及$j$的关系是怎么样的？

因为决策$k$优与决策$j$，所以：

$dp[k] + x[i] * y[k + 1] < dp[j] + x[i] * y[j + 1]$

接着移项。

$dp[k] - dp[j] < x[i] * (y[j + 1] - y[k + 1])$

$\frac{dp[k] - dp[j]}{y[j + 1]-y[k + 1]} < x[i]$

$\frac{dp[k] - dp[j]}{y[k + 1]-y[j + 1]} > -x[i]$
(因为你会发现前面的式子的结果是个负数)

求斜率的公式:$k = \frac{△y}{△x}$

那么想象现在平面上有两个点:$(y[k+1],dp[k])$ , $(y[j + 1],dp[j])$

这两个点连成的直线如果斜率大于$x[i]$，那么$k$就要比$j$更优

然后就可以斜率优化了，单调队列维护一个上凸包即可。

```cpp
#include <bits/stdc++.h>
using namespace std;
#define int long long
const int MAXN = 50005;

int n,N = 0;
int dp[MAXN],Q[MAXN];

struct Node {
	int x,y;
} T[MAXN],New[MAXN];

int cmp(Node A, Node B)
{
	if(A.x != B.x)return A.x < B.x;
	else return A.y < B.y;
}

double sploe(int a,int b)
{
	return (double)(dp[b] - dp[a]) / (double)(T[b + 1].y - T[a + 1].y);
}

signed main()
{
	cin >> n;
	for(int i = 1 ; i <= n ; i ++)
		cin >> T[i].x >> T[i].y;
	sort(T + 1 , T + 1 + n , cmp);
	for(int i = 1 ; i <= n ; i ++)
	{
		if(T[i].y < New[N].y)N ++ , New[N] = T[i];
		else 
		{
			while(N && New[N].y <= T[i].y)N --;
			N ++;
			New[N] = T[i];
		}
	}
    
	n = N;
	for(int i = 1 ; i <= n ; i ++)T[i] = New[i];
	int tail = 1 , head = 1;
	Q[1] = 0;
	for(int i = 1 ; i <= n ; i ++)
	{
		while(head < tail && sploe(Q[head],Q[head + 1]) >= (double) -T[i].x)head ++;//反一下符号
		dp[i] = dp[Q[head]] + T[i].x * T[Q[head] + 1].y;
		while(head < tail && sploe(Q[tail - 1],Q[tail]) >= sploe(Q[tail],i))tail --;
		tail ++ , Q[tail] = i;
	}
	cout << dp[n] << endl;
	return 0;
}
```


---

## 作者：shiroi (赞：0)

斜率优化DP入门题。  

观察题目发现如果有两块土地 $i, j$ 满足 $xi ≤ xj , yi ≤ yj$，$i$ 的影响就可以不用考虑。  
因此把土地按长度从小到大排序，则它们的宽度递减。可以发现每次购买的土地一
定是连续一段。  
我们设 $f(i)$ 表示买前 $i$ 块需要的最小代价，则 $f(i) = min \{f(j) + x_i * y_{j + 1}\}$，$f(j)= -x_i * y_{j+1}+f(i)$。  
因此点是 $(-y_{j+1}, f(j))$，斜率是 $x_i$。  

斜率优化，维护一个下凸包即可。  

```cpp
#include <bits/stdc++.h>
using namespace std;

inline int read()
{
	int x=0; int f=1; char ch=getchar();
	while(!isdigit(ch)) {if(ch=='-')f=-1; ch=getchar();}
	while(isdigit(ch)) {x=x*10+ch-'0'; ch=getchar();}
	return x*f;
}

const int MAXN = 100005;
struct data {long long x,y;} a[MAXN];
long long x[MAXN],y[MAXN],f[MAXN],q[MAXN];
int n,tot;

inline bool cmp(data a,data b)
{return a.x==b.x?a.y<b.y:a.x<b.x;}

inline double slop(int a,int b)
{return (double)(f[b]-f[a])/(y[a+1]-y[b+1]);}

int main(int argc, char const *argv[])
{
	n=read();
	for(int i=1; i<=n; i++)
		a[i].x=read(),a[i].y=read();
	sort(a+1,a+n+1,cmp);
	for(int i=1; i<=n; i++)
	{
		while(tot && a[i].y>=y[tot]) tot--;
		x[++tot]=a[i].x; y[tot]=a[i].y;
	}
	int l=0,r=0;
	for(int i=1; i<=tot; i++)
	{
		while(l<r && slop(q[l],q[l+1])<x[i]) l++;
		int t=q[l]; f[i]=f[t]+y[t+1]*x[i];
		while(l<r && slop(q[r],i)<slop(q[r-1],q[r])) r--;
		q[++r]=i;
	}
	printf("%lld",f[tot]);
	return 0;
}
```

---

## 作者：ModestCoder_ (赞：0)

如果一个土地的长宽分别小于另外一个，那么这个是没用的

按照长度为第一关键字从小到大，宽度为第二关键字从大到小排个序

可以用单调栈处理出这样一些土地：长度递增，宽度递减

然后总是选取一段连续的土地进行购买，因为如果你选了两个土地，那么这两个土地中间的土地可以不花费代价的顺带购买

然后就可以dp了

令$l_i,w_i$表示长宽，$dp_i$表示选到第i个的最小代价

暴力转移方程$dp_i=min(dp_j+w_{j+1}*l_i)$

套路斜率优化，若两个决策$x,y(x<y)$，y更优满足
$dp_x+w_{x+1}*l_i>=dp_y+w_{y+1}*l_i$

整理得$\frac{dp_x-dp_y}{w_{y+1}-w_{x+1}}<=l_i$

单调队列维护斜率递增的下凸壳即可

Code:

```cpp
#include <bits/stdc++.h>
#define maxn 50010
#define LL long long
using namespace std;
struct node{
	LL l, w;
}a[maxn];
int n, top, q[maxn];
LL dp[maxn];

inline int read(){
	int s = 0, w = 1;
	char c = getchar();
	for (; !isdigit(c); c = getchar()) if (c == '-') w = -1;
	for (; isdigit(c); c = getchar()) s = (s << 1) + (s << 3) + (c ^ 48);
	return s * w;
}

bool cmp(node x, node y){ return x.l == y.l ? x.w > y.w : x.l < y.l; }
double slope(int x, int y){ return 1.0 * (dp[x] - dp[y]) / (a[y + 1].w - a[x + 1].w); }

int main(){
	n = read();
	for (int i = 1; i <= n; ++i) a[i].l = read(), a[i].w = read();
	sort(a + 1, a + 1 + n, cmp);
	for (int i = 1; i <= n; ++i){
		while (top && a[top].w <= a[i].w) --top;
		a[++top] = a[i];
	}
	n = top;
	int h = 0, t = 0;
	for (int i = 1; i <= n; ++i){
		while (h < t && slope(q[h], q[h + 1]) <= a[i].l) ++h;
		dp[i] = dp[q[h]] + a[i].l * a[q[h] + 1].w;
		while (h < t && slope(q[t - 1], q[t]) >= slope(q[t], i)) --t;
		q[++t] = i;
	}
	printf("%lld\n", dp[n]);
	return 0;
}
```


---

## 作者：VenusM1nT (赞：0)

考虑先将数组排序并打包，将所有能一起买的土地打包成一份

用$x$表示长，$y$表示宽，可得转移方程如下：

$$f[i]=\sum_{j=1}^{i-1}min(f[j]+x[j+1]\times y[i])$$

显然，这个转移是$n^2$的，会超时，考虑斜率优化

假设决策$j$比$k$更优，当且仅当：

$$f[j]+x[j+1]\times y[i]<f[k]+x[k+1]\times y[i]$$

将含有$i$的项移到一边，其他的移到另一边：

$$(x[j+1]-x[k+1])\times y[i]<f[k]-f[j]$$

令左式只剩下与$i$有关的式子：

$$y[i]<\frac{f[k]-f[j]}{x[j+1]-x[k+1]}$$

于是就$get$了如何计算斜率

考虑原来的转移方程$f[j]+x[j+1]\times y[i]$，设直线方程为：

$$y=kx+b$$

可设$x=y[i]$，得$k=x[j+1]$，$b=f[j]$，斜率为正，因此维护一个下凸壳即可

见代码

```cpp
#include<bits/stdc++.h>
#define ll long long
using namespace std;
struct Node
{
	ll x,y;
	friend bool operator < (const Node &x,const Node &y)
	{
		return x.x^y.x?x.x>y.x:x.y>y.y;
	}
}a[50005],t[50005];
int n,tot,q[50005];
ll f[50005];
double Slope(int j,int k)
{
	return (double)(f[k]-f[j])/(double)(a[j+1].x-a[k+1].x);
}
int main()
{
	scanf("%d",&n);
	for(int i=1;i<=n;i++) scanf("%d %d",&t[i].x,&t[i].y);
	sort(t+1,t+n+1);
	for(int i=1;i<=n;i++) if(t[i].y>a[tot].y) a[++tot]=t[i];
	int head=1,tail=1;
	for(int i=1;i<=tot;i++)
	{
		while(head<tail && Slope(q[head],q[head+1])<=a[i].y) head++;
		f[i]=f[q[head]]+a[i].y*a[q[head]+1].x;
		while(head<tail && Slope(q[tail-1],q[tail])>=Slope(q[tail],i)) tail--;
		q[++tail]=i;
	}
	printf("%lld\n",f[tot]);
	return 0;
}
```

---

## 作者：i207M (赞：0)

## 题目总结

给定N个矩形，购买每个矩形的代价是他们的面积；有一种并购方案，并购的价格为这些土地中 最大的长 x 最大的宽；

## 数据范围

1 <= N <= 50,000

## 解题思路

一道斜率优化DP；

直接列方程发现较困难；

考虑每个矩形，我们发现有些矩形X是没有价值的，当且仅当存在某个矩形Y，Y的长宽均大于X的；

我们首先要剔除他们；方法是排序；

以L为第一关键字，W为第二；

然后维护一个栈，将排序后的土地一个一个加入，每次加入之前，先把当前栈中宽小于等于它的土地全部删除（因为这些土地长肯定小于等于它），再加入它。最后留在栈里的土地就是有存在必要的土地。

然后我们会发现，此时的序列中，L递增，W递减（比如L小的，假如W也小，那么它就被删了）

转移方程为：

$f[i] = f[j = q.front()] + land[i].l * land[j + 1].w;$

斜率优化乱搞一波

## 易错误区

此题的排序很有意思

想出来就OK

## 代码展示

```cpp
#include<iostream>
#include<cstdio>
#include<cstdlib>
#include<cmath>
#include<cstring>
#include<string>
#include<algorithm>
#include<vector>
#include<map>
#include<set>
#include<list>
#include<queue>
#include<stack>
#include<bitset>
#include<deque>
using namespace std;
#define ll long long
#define ull unsigned long long
#define inf 0x3f3f3f3f
#define ri register int
#define il inline
#define fi first
#define se second
#define mp make_pair
#define pi pair<int,int>
#define mem0(x) memset((x),0,sizeof (x))
#define mem1(x) memset((x),0x3f,sizeof (x))
#define int ll
il char gc() {
    static const int BS = 1 << 22;
    static unsigned char buf[BS], *st, *ed;
    if (st == ed) ed = buf + fread(st = buf, 1, BS, stdin);
    return st == ed ? EOF : *st++;
}
#define gc getchar
template<class T>void in(T &x)
{
    x = 0; bool f = 0; char c = gc();
    while (c < '0' || c > '9') {if (c == '-') f = 1; c = gc();}
    while (isdigit(c)) {x = (x << 3) + (x << 1) + (c ^ 48); c = gc();}
    if (f) x = -x;
}
#undef gc
void out(int x) {
    if (x < 0) putchar('-'), x = -x;
    if (x > 9) out(x / 10);
    putchar(x % 10 + '0');
}
#define N 50010
#define int ll
#define X(i) (land[i+1].w)
#define Y(i) (f[i])
#define K(i) (-land[i].l)
#define slope(i,j) ((double)(Y(i)-Y(j))/(double)(X(i)-X(j)))
int n;
struct Node {
    int l, w;
} a[N], land[N];
deque<int>q;
int top;
int f[N];
bool cmp(const Node &a, const Node &b) {
    if (a.l == b.l) return a.w < b.w;
    return a.l < b.l;
}
signed main() {
    in(n);
    for (ri i = 1; i <= n; ++i) {
        in(a[i].l), in(a[i].w);
    }
    sort(a + 1, a + 1 + n, cmp);
    for (ri i = 1; i <= n; ++i) {
        while (top && land[top].w <= a[i].w) --top;
        land[++top] = a[i];
    }
    q.push_front(0);
    for (ri i = 1, j; i <= top; ++i) {
        while (q.size() > 1 && slope(*(q.begin()), *(q.begin() + 1)) > K(i))
            q.pop_front();
        f[i] = f[j = q.front()] + land[i].l * land[j + 1].w;
        while (q.size() > 1 && slope(*(q.end() - 1), *(q.end() - 2)) < slope(*(q.end() - 2), i))
            q.pop_back();
        q.push_back(i);
    }
    printf("%lld", f[top]);
    return 0;
}
```

---

## 作者：寒鸽儿 (赞：0)

对于二维的坐标,一个很好的想问题的方法是把它画到坐标系中。  
然后可以发现,我们只需要取最外圈的轮廓即可,换言之,对于$(a,b)$ $\exists (x,y),x \geqslant a \space\&\&\space y\geqslant b$,显然$(a, b)$可以在购买$(x,y)$的时候一起买而不用消耗额外的代价。  
舍去这些点之后,我们发现坐标图中的点,若$x_i \geqslant x_j$则必有$y_i \leqslant y_j$。有一个性质,即我们应当购买连续的一段$x$的区间。即若$i \leqslant k \leqslant j$,购买$i,j$，则面积为$y_i * x_j$,显然$x_i \leqslant x_k \leqslant x_j, y_i \geqslant y_k \geqslant y_j$,显然应该把$k$带过而不需要消耗额外代价。  
所以可以枚举上段开始的位置按$x$升序进行dp。  
$f(i) = min\{f(j)\space + \space w(j+1, k)\}$  
$w(a, b) = x_b y_a$  
由于$x_a$单调递增,$y_a$单调递减，故$w$应当是凸的,或者说它满足四边形不等式。(可以暴力写出来证一下)  
所以用单调栈维护即可。  
复杂度$O(nlogn)$  
```cpp
#include <cstdio>
#include <cstring>
#include <deque>
#include <algorithm>
#define ll long long

using namespace std;

const int N = 56789;
struct pt{
	int x, y;
	pt() {x = 0; y = 0;}
	pt(int X, int Y): x(X), y(Y) {}
	bool operator < (const pt&o) const {
		return x == o.x ? y > o.y : x < o.x;
	}
	pt operator = (const pt&o) {
		x = o.x; y = o.y; return *this;
	}
};
struct node{
	int l, r, x;
	node() {}
	node(int L, int R, int X): l(L), r(R), x(X) {}
};
deque<node> sta;
pt inp[N], p[N];
ll f[N];
int up = 1;

inline ll getW(int x, int y) { return (ll)p[x].y * p[y].x; }
inline bool ckupd(int x, int y, int t) { return f[x] + getW(x+1, t) < f[y] + getW(y+1, t); }

int main() {
	int n;
	scanf("%d", &n);
	for(int i = 1; i <= n; ++i)
		scanf("%d %d", &inp[i].x, &inp[i].y);
	sort(inp + 1, inp + n + 1);
	ll ht = 0;
	for(int i = n; i; --i) {
		if(inp[i].y > ht) {
			p[up++] = inp[i];
			ht = inp[i].y;
		}
	}
	reverse(p+1, p+up);
	f[0] = 0;
	sta.push_back(node(1, up-1, 0)); 
	for(int i = 1; i < up; ++i) {
		while(sta.front().r < i) sta.pop_front();
		f[i] = f[sta.front().x] + getW(sta.front().x+1, i);
		while(!sta.empty()) {
			if(ckupd(i, sta.back().x, sta.back().l)) sta.pop_back();
			else break;
		}
		if(sta.empty()) {
			sta.push_back(node(i+1, up-1, i));
		} else if(ckupd(i, sta.back().x, sta.back().r)) {
			node tmp = sta.back();
			sta.pop_back();
			int l = tmp.l+1, r = tmp.r, mid;
			while(l < r) {
				mid = (l + r) >> 1;
				if(ckupd(i, tmp.x, mid)) r = mid;
				else l = mid + 1;
			}
			sta.push_back(node(tmp.l, l-1, tmp.x));
			sta.push_back(node(l, up-1, i));
		} else {
			if(sta.back().r < up-1) sta.push_back(node(sta.back().r+1, up-1, i));
		}
	}
	printf("%lld\n", f[up-1]);
	return 0;
}
```


---

## 作者：crashed (赞：0)

# 题目
&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;[点这里](https://www.luogu.org/problem/P2900)看题目。
# 分析
&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;我们把每一块土地想成一个矩形，然后把矩形的左下角与坐标系的原点对齐，这样一块土地就与坐标系中一个$(0,0,H,W)$的矩形对应。  
&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;然后，对于一个矩形$i$，如果存在一个矩形$j$，满足$H_i\leq H_j$并且$W_i\leq W_j$，则显然我们可以将$i$和$j$合在一组买，却只花了买$j$的钱。此时第$i$个矩形就相当于免费购买。我们可以用一个单调栈将原矩形集合简化为无法被免费购买的矩形集合。  
&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;在进行下面的步骤之前，我们把集合排序，使得$\forall i,H_i>H_{i+1}\ and\ W_i< W_{i+1}$  
&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;然后开始$DP$：  
&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;$DP(i)$：将前$i$个无法免费购买的矩形全部买下的最小花费。  
&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;则有$DP(i)=\min_{0\leq j<i}\{DP(j)+H_{j+1}W_i\}$  
&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;到此，已经可以~~水~~通过[P4959 [COCI2017-2018#6] Cover](https://www.luogu.org/problem/P4959)一题了。  
&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;不过对于此题的数据范围，$O(n^2)$的算法还不足以过掉它。所以我们考虑优化——斜率优化：  
&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;当$j<k$，有$H_j>H_k$，$W_j<W_k$，假如$j$比$k$优，则有：  
&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;$DP(j)+H_{j+1}W_i<DP(k)+H_{k+1}W_i$  
&nbsp;&nbsp;$\Rightarrow DP(j)-DP(k)<W_i(H_{k+1}-H_{j+1})$  
&nbsp;&nbsp;$\Rightarrow \frac{DP(j)-DP(k)}{H_{j+1}-H_{k+1}}<-W_i$  
&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;感性理解就是，如果当前的两点之间的斜率$<-W_i$，则靠前的点更优，否则就是靠后的点更优。  
&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;然后我们发现，我们需要维护的是一个上凸包。  
&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;然后用单调队列维护这个上凸包序列用于转移即可。
# 代码
```cpp
#include <cstdio>
#include <algorithm>

typedef long long LL;

const int MAXN = 50005;

template<typename _T>
void read( _T &x )
{
    x = 0;char s = getchar();int f = 1;
    while( s > '9' || s < '0' ){if( s == '-' ) f = -1; s = getchar();}
    while( s >= '0' && s <= '9' ){x = ( x << 3 ) + ( x << 1 ) + ( s - '0' ), s = getchar();}
    x *= f;
}

template<typename _T>
void write( _T x )
{
    if( x < 0 ){ putchar( '-' ); x = ( ~ x ) + 1; }
    if( 9 < x ){ write( x / 10 ); }
    putchar( x % 10 + '0' );
}

struct point
{
	int x, y;
	point(){}
	point( const int X, const int Y )
	{
		x = X, y = Y;
	}
	bool operator < ( const point & other ) const
	{
		return x < other.x || ( x == other.x && ( y < other.y ) );
	}
	bool operator > ( const point & other ) const
	{
		return x >= other.x && y >= other.y;
	}
}p[MAXN], np[MAXN];

struct vector
{
	LL x, y;
	vector(){}
	vector( const LL X, const LL Y )
	{
		x = X, y = Y;
	}
	LL mul( const vector & other ) const
	{
		return x * other.y - y * other.x;
	}
	bool operator < ( const vector & other ) const
	{
		return mul( other ) > 0;
	}
	bool operator > ( const vector & other ) const
	{
		return mul( other ) < 0;
	}
	bool operator >= ( const vector & other ) const
	{
		return mul( other ) >= 0;
	}
	bool operator <= ( const vector & other ) const
	{
		return mul( other ) <= 0;
	}
};

LL DP[MAXN];
int deq[MAXN], h, t;
int sta[MAXN], top;
int N, cnt;

LL X( const int indx )
{
	return np[indx + 1].y;
}

LL Y( const int indx )
{
	return DP[indx];
}

LL getDP( const int i, const int indx )
{
	return DP[indx] + 1ll * np[indx + 1].y * np[i].x;
}

int main()
{
	read( N );
	for( int i = 1 ; i <= N ; i ++ )
	{
		read( p[i].y ), read( p[i].x );
	}
	std :: sort( p + 1, p + 1 + N );
	top = 0;
	for( int i = 1 ; i <= N ; i ++ )
	{
		while( top && p[i] > p[sta[top]] ) 
			top --;
		sta[++top] = i;
	}
	cnt = top;
	while( top ) np[top] = p[sta[top]], top--;
	DP[0] = 0;
	t = 0, h = 1;
	deq[++t] = 0;
	for( int i = 1 ; i <= cnt ; i ++ )
	{
		while( h < t && Y( deq[h] ) - Y( deq[h + 1] ) >= -1ll * np[i].x * ( X( deq[h ] ) - X( deq[h + 1] ) ) ) 
			h ++;
		DP[i] = getDP( i, deq[h] );
		while( h < t && vector( X( i ) - X( deq[t] ), Y( i ) - Y( deq[t] ) ) <= vector( X( deq[t] ) - X( deq[t - 1] ), Y( deq[t] ) - Y( deq[t - 1] ) ) ) 
			t --;
		deq[++t] = i;
	}
	write( DP[cnt] ), putchar( '\n' );
	return 0;
}
```


---

## 作者：Boring__Zheng (赞：0)

一道神奇的斜率优化题~~好像所有斜率优化都很玄学？~~

## **预处理**
首先我们要把题目上的数据处理一下，不然没有任何思路

我们用l表示长方形的长，h表示长方形的宽，如果有l[x]<l[y]&&h[x]<h[y]，
那么实际上最后答案与x无关，所以我们可以对长方形以h为第一关键字，l为第二关键字进行排序，排序后如果有l[x]>l[x+1] 就把x+1删除掉，这个可以自己那一组数据试一下

## **转移方程**
我们用dp[i]来表示前i块土地最小花费，易得
dp[i]=min(dp[i],dp[j-1]+h[j]*l[i])
很明显，如果单独用这个转移方程的话时间复杂度是O(n^2)会超时，考虑优化

## **斜率优化**
首先，当从j转移到i最优时，一定有

dp[j-1]+h[j]*l[i]>=dp[k-1]+h[k]*l[i]

整理得：

(dp[j-1]-dp[k-1])/(h[j]-h[k])<=l[i]

所以，我们只需要维护一个单调队列保存斜率即可

单调队列具体操作可看注释

## **Code**

```cpp
#include<bits/stdc++.h>
using namespace std;
struct Node
{
    long long l,h;
}rec[50001];
long long dp[50001];
int q[50001];
double k[50001];
bool cmp(Node x,Node y)
{
    return x.h==y.h?x.l>y.l:x.h>y.h;
}
double cale(int x,int y)
{
    return (dp[x-1]-dp[y-1])/(rec[y].h-rec[x].h);
}
int main()
{
    int n;
    cin>>n;
    for(int i=1;i<=n;i++) cin>>rec[i].l>>rec[i].h;
    sort(rec+1,rec+n+1,cmp);	
    int now=1;
    for(int i=1;i<=n;i++)
        if(rec[now].l<rec[i].l) rec[++now]=rec[i];
    n=now; 
    int head=1,tail=0;
    for(int i=1;i<=n;i++)
    {
        while(head<tail&&k[tail-1]>=cale(i,q[tail])) tail--;
        k[tail]=cale(i,q[tail]); q[++tail]=i;
        //将i加入队列
        while(head<tail&&k[head]<rec[i].l) head++;
        //将队首不够优的删除
        dp[i]=dp[q[head]-1]+rec[q[head]].h*rec[i].l;
    }
    cout<<dp[n];
    return 0;
}
```


---

