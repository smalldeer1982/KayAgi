# Lengthening Sticks

## 题目描述

You are given three sticks with positive integer lengths of $ a,b $ , and $ c $ centimeters. You can increase length of some of them by some positive integer number of centimeters (different sticks can be increased by a different length), but in total by at most $ l $ centimeters. In particular, it is allowed not to increase the length of any stick.

Determine the number of ways to increase the lengths of some sticks so that you can form from them a non-degenerate (that is, having a positive area) triangle. Two ways are considered different, if the length of some stick is increased by different number of centimeters in them.

## 说明/提示

In the first sample test you can either not increase any stick or increase any two sticks by $ 1 $ centimeter.

In the second sample test you can increase either the first or the second stick by one centimeter. Note that the triangle made from the initial sticks is degenerate and thus, doesn't meet the conditions.

## 样例 #1

### 输入

```
1 1 1 2
```

### 输出

```
4
```

## 样例 #2

### 输入

```
1 2 3 1
```

### 输出

```
2
```

## 样例 #3

### 输入

```
10 2 1 7
```

### 输出

```
0
```

# 题解

## 作者：Reaepita (赞：16)

这道题直接求比较难，所以我们可以用容斥原理，求出总方案
减去不合法的方案数

#### ① 求总方案数
因为加上的数总和$≤L$ 所以我们可以枚举加上的数的和 $k$

> 我们就可以把 `将k分为3个整数` 的问题转化为求 $C(k+2,2)$

我们可以把 $k$ 想象成 $k$ 个小球，外加两个隔板，隔板之间有多少个小球，就表示这个数为多少，所以总共有 $k+2$ 个位置 ，要选择 $2$ 个位置成为隔板方案数为 $C(k+2,2)$

同时 0 0 0 也是一种方案也要加上

那么总方案数为

$ans=\sum_{k=1}^{L}C(k+2,2)+1$

#### ② 求不合法的方案数
不合法的情况一定满足，$a',b',c'$ 中存在一个数 ＞ 其它两个数的和
我们只需要枚举这个数，同时保证当前总长度加上其它两个数的和小于枚举的数，具体看代码注释

```cpp
#include<iostream>
#include<cstring>
#include<cstdio>
using namespace std;
long long a,b,c,l;
long long ans=0;
long long count(long long x,long long y,long long z,long long L)
{
	//z为最长边
	long long ret=0;
	for(long long i=max((long long)(0),x+y-z);i<=L;i++)
	{
		long long now=min(L-i,z+i-x-y);
        //now为当前长度
		ret+=(now+1)*(now+2)/2;
	}
	return ret;
}
int main()
{
	scanf("%lld%lld%lld%lld",&a,&b,&c,&l);
	ans++;
	for(long long i=1;i<=l;i++)ans+=(i+1)*(i+2)/2;
	ans-=count(a,b,c,l);//枚举三种情况，最后一个数为枚举的最大数
	ans-=count(a,c,b,l);
	ans-=count(c,b,a,l);
	printf("%lld\n",ans);
}
```


---

## 作者：wsyhb (赞：6)

## 前言

本文解法看似冗长，实际上**简单又自然**。（~~防止劝退读者~~）

## 题解

设三根木棍增加的长度分别为 $la,lb,lc \;(0 \le la,lb,lc \le l)$，由题意得：

$$
\begin{cases}
(a+la)+(b+lb)>(c+lc) \\
(a+la)+(c+lc)>(b+lb) \\
(b+lb)+(c+lc)>(a+la) \\
la+lb+lc \le l
\end{cases}
$$

由于 $l \le 3 \times 10^5$，可以枚举 $la,lb,lc$ 三个中的一个。不妨设 $\max(a,b,c)=a$，并枚举 $la$。（注意：**下文要用到 $a$ 是三者中的最大值**）

此时 $a,b,c,la$ 已知，于是进行如下移项（把未知数全部移到不等号左侧，已知量全部移到不等号右侧）：

$$
\begin{cases}
lb-lc>c-a-la-b \\
lc-lb>b-a-la-c \\
lb+lc>a+la-b-c \\
lb+lc \le l-la
\end{cases}
$$

为了方便，将所有 $>$ 改为 $\ge$（利用 $a>b \Leftrightarrow a \ge b+1$）：

$$
\begin{cases}
lb-lc \ge c-a-la-b+1 \\
lc-lb \ge b-a-la-c+1 \\
lb+lc \ge a+la-b-c+1 \\
lb+lc \le l-la
\end{cases}
$$

然后将上述式子表示成 $lb$ 的解的形式：

$$
\begin{cases}
lb \ge (c-a-la-b+1)+lc \\
lb \le lc-(b-a-la-c+1) \\
lb \ge (a+la-b-c+1)-lc \\
lb \le l-la-lc
\end{cases}
$$

令 $A=c-a-la-b+1$，$B=a+la-b-c+1$，$C=-(b-a-la-c+1)$，$D=l-la$（注意：**$B$ 和 $C$ 的顺序与上一个式子不同**），则式子转化为：

$$\max(A+lc,B-lc) \le lb \le \min(C+lc,D-lc)$$

考虑条件 $\max(A+lc,B-lc) \le \min(C+lc,D-lc)$：

$$
\begin{aligned}
& \max(A+lc,B-lc) \le \min(C+lc,D-lc) \\
\Leftrightarrow & A+lc \le C+lc \land A+lc \le D-lc \land B-lc \le C+lc \land B-lc \le D-lc \\
\Leftrightarrow & A \le C \land B \le D \land B-lc \le C+lc \land A+lc \le D-lc \\
\Leftrightarrow & A \le C \land B \le D \land \lceil \frac{B-C}{2} \rceil \le lc \le \lfloor \frac{D-A}{2} \rfloor
\end{aligned}
$$

（其中 $\land$ 表示逻辑与，即中文中的“且”）

上述式子即为 **$lb$ 有解的必要条件**。

至此，我们考虑了构成三角形的条件，$la$ 的值以及 $lb+lc$ 的上界，**还需考虑 $lb,lc$ 的下界**（即 $lb,lc \ge 0$）。

$lc \ge 0$ 可以直接加入到条件 $\lceil \dfrac{B-C}{2} \rceil \le lc \le \lfloor \dfrac{D-A}{2} \rfloor$ 中。

要使 $lb \ge 0$，则只需使其上界 $\min(C+lc,D-lc) \ge 0$（**这也是 $lb$ 有解的必要条件，而下界可以与 $0$ 取 $\max$**），即：使 $C+lc$ 和 $D-lc$ 都非负。

由于 $\max(a,b,c)=a$（不知道为什么就回去看第二段），则 $C=(a+la-b)+(c-1) \ge 0$，又因为 $lc \ge 0$，所以 $C+lc \ge 0$。

而 $D-lc \ge 0$ 等价于 $lc \le D$，同样可以加入到条件 $\lceil \dfrac{B-C}{2} \rceil \le lc \le \lfloor \dfrac{D-A}{2} \rfloor$ 中。

于是本题所求答案为：

$$\sum_{la=0}^{l}\sum_{lc=L}^{R}\min(C+lc,D-lc)-\max(\max(A+lc,B-lc),0)+1$$

其中 $[L,R]$ 表示满足 $\max(A+lc,B-lc) \le \min(C+lc,D-lc)$（**$lb$ 取值范围非空**）且 $\min(C+lc,D-lc)\ge 0$（**$lb$ 取值范围含有非负数**），$0 \le lc \le l-la$（**$lc$ 也满足限制**） 时，$lc$ 的取值范围。

由前文分析可知 $L=\max(\lceil \dfrac{B-C}{2} \rceil,0)$，$R=\min(\lfloor \dfrac{D-A}{2} \rfloor,D)$。

由于 $\max$ 和 $\min$ 是**一次函数组成的分段函数**，利用**等差数列求和**公式，可 **$O(1)$ 计算区间和**。

具体来说，以 $\max(A+lc,B-lc)$ 为例：

$$
\max(A+lc,B-lc)=
\begin{cases}
A+lc \quad (lc >\lfloor \frac{B-A}{2} \rfloor)\\
B-lc \quad (lc \le \lfloor \frac{B-A}{2} \rfloor)
\end{cases}
$$

于是有：

$$
\sum_{lc=L}^{R}\max(A+lc,B-lc)=
\begin{cases}
(R-L+1)A+\frac{(L+R)(R-L+1)}{2} \quad (R \le \lfloor \frac{B-A}{2} \rfloor) \\
(R-L+1)B-\frac{(L+R)(R-L+1)}{2} \quad (L \ge \lfloor \frac{B-A}{2} \rfloor) \\
(mid-L+1)A+\frac{(L+mid)(mid-L+1)}{2}+(R-(mid+1)+1)A+\frac{((mid+1)+R)(R-(mid+1)+1)}{2} \quad (\text{otherwise})
\end{cases}
$$

其中 $mid=\lfloor \frac{B-A}{2} \rfloor$。

说明：即分成**整个区间在 $mid$ 左边，整个区间在 $mid$ 右边，和跨越 $mid$ 三种情况**进行讨论。

$\min$ 类似处理即可。

另外，**记得把 $\max(A+i,B-i) \le 0$ 部分贡献的 $\max$ 减去**。

然后就做完了！总时间复杂度 $O(l)$。跑得很快！

## 代码

注意两个细节：

1. $a$ 应调整成 $\max(a,b,c)$。
2. C++ 中 `/` 是向零取整，而 `>>` 是向下取整。举个例子：`-1/2` 的值为 $0$，而 `-1>>2` 的值为 $-1$。（若把向下取整写成向零取整，会被**代码末尾的两组数据**卡掉）

``` cpp
#include<bits/stdc++.h>
using namespace std;
int main()
{
	int a,b,c,l;
	scanf("%d%d%d%d",&a,&b,&c,&l);
	if(b>a)
		swap(a,b);
	if(c>a)
		swap(a,c);
	long long ans=0;
	for(int la=0;la<=l;++la)
	{
		int x=c-(a+la)-b,y=b-(a+la)-c,z=(a+la)-b-c;
		int A=x+1,B=z+1,C=-y-1,D=l-la;
		int L=max((B-C+1)/2,0),R=min((D-A)/2,D);
		if(C<A||D<B||L>R)
			continue;
		ans+=R-L+1;
		int mid=(D-C)>>1;
		if(R<=mid)
			ans+=C*(R-L+1ll)+(L+R)*(R-L+1ll)/2;
		else if(L>mid)
			ans+=D*(R-L+1ll)-(L+R)*(R-L+1ll)/2;
		else 
		{
			ans+=C*(mid-L+1ll)+(L+mid)*(mid-L+1ll)/2;
			ans+=D*(R-(mid+1)+1ll)-((mid+1)+R)*(R-(mid+1)+1ll)/2;
		}
		mid=(B-A)>>1;
		if(R<=mid)
			ans-=B*(R-L+1ll)-(L+R)*(R-L+1ll)/2;
		else if(L>mid)
			ans-=A*(R-L+1ll)+(L+R)*(R-L+1ll)/2;
		else
		{
			ans-=B*(mid-L+1ll)-(L+mid)*(mid-L+1ll)/2;
			ans-=A*(R-(mid+1)+1ll)+((mid+1)+R)*(R-(mid+1)+1ll)/2;
		}
		if(B<=-A&&B<=R&&-A>=L)
		{
			L=max(B,L),R=min(-A,R);
			if(R<=mid)
				ans+=B*(R-L+1ll)-(L+R)*(R-L+1ll)/2;
			else if(L>mid)
				ans+=A*(R-L+1ll)+(L+R)*(R-L+1ll)/2;
			else
			{
				ans+=B*(mid-L+1ll)-(L+mid)*(mid-L+1ll)/2;
				ans+=A*(R-(mid+1)+1ll)+((mid+1)+R)*(R-(mid+1)+1ll)/2;
			}
		}
	}
	printf("%lld\n",ans);
	return 0;
}
/*
5 7 30 100
---
71696
*/
/*
17 28 19 5558
---
7396315389
*/

---

## 作者：Coros_Trusds (赞：5)

因为考虑到直接求正解比较困难，正难则反，我们考虑容斥。

所有组合的情况减去不满足条件的情况就是最终答案。

### 所有组合的情况

相当于把最多 $L$ 个小球,放入三个有标记的盒子，问方案数。

枚举 $L$，方案数就是 $C_{L+2}^{2}$。

这个方案数可以化成：

$$C_{L+2}^{2}$$

$$=\dfrac{(L+2)!}{2! \times (L+2-2)!}$$

$$=\dfrac{(L+2)!}{2!\times L!}$$

$$=\dfrac{(L+2)\times (L+1)\times \cdots \times 1!}{L\times(L-1)\times\cdots\times1\times2\times1}$$

$$=\dfrac{(L+2)\times(L+1)}{2}$$

### 对于不合法的情况

分别考虑 $a,b,c$ 做三角形最长边的情况。

比如 $c$ 取最长边，枚举 $i ∈ [0,L]$,那么就还有最多 $\min(c+i-a-b,L-i)$ 的部分可以分配给 $a$ 和 $b$，求出方案即可。

### 代码

```cpp
//2021/7/22

#include <cstdio>

#define int long long

using namespace std;

int l;

int a,b,c;

int ans;

inline int min(int x,int y)
{
	return x<y?x:y;
}

inline int solve(int a,int b,int c)
{
	int tp=0;
	
	for(register int i=0;i<=l;i++)
	{
		int x=min(l-i,c+i-a-b);
		
		if(x>=0)
		{
			tp+=(x+2)*(x+1)/(2*1);
		}
	}
	
	return tp;
}

#undef int

int main(void)
{
	#define int long long
	
	int a,b,c,ans=0;
	
	scanf("%lld%lld%lld%lld",&a,&b,&c,&l);
	
	for(register int i=0;i<=l;i++) //总的方案数 
	{
		ans+=(i+2)*(i+1)/(2*1);
	}
	
	ans=ans-(solve(a,b,c)+solve(a,c,b)+solve(b,c,a));//分别减去不满足的三种情况 
	
	printf("%lld\n",ans);
	
	return 0;
}

#undef int
```

---

## 作者：流水行船CCD (赞：4)

正难为什么要反！正着做明明如此套路，而且不用分讨，不用微调！

枚举 $a,b,c$ 延长后哪一个作为最大值（可并列）。

设 $a,b,c$ 延长量分别为 $x,y,z$，且 $a+x \ge b+y,c+z$，则 $y,z$ 有限制如下：

$$
\begin{array}{l} 
 \left\{\begin{matrix} 
 y \ge 0
 \\ z \ge 0
 \\ y + b \le a + x \Leftrightarrow y \ le a + x - b
 \\ z + c \le a + x \Leftrightarrow z \ le a + x - c
 \\ y + z + b + c \ge a + x + 1 \Leftrightarrow z \le a + x + 1 - b - c - y
 \\ x + y + z \le L \Leftrightarrow z \le L - x - y
\end{matrix}\right. 
\end{array}
$$

其中 $x$ 可以枚举确定，剩下 $y,z$ 的二元不等式组。而如果我们将 $y$ 看作 $x$ 坐标，$z$ 看作 $y$ 坐标，就是一个标准线性规划问题，每一个合法解可以看作一个整点 $(y,z)$，每一个不等式等价于一条直线，要求合法的点必须在该直线的一侧。不难发现答案即为这些直线半平面交的凸包（或者为一条直线或点）内整点个数，形状如下：

![](https://cdn.luogu.com.cn/upload/image_hosting/58yxy1mc.png)

但是发现直线或点的情况很难判，直接把直线全部向外平移一格，也就是将约束条件中的 $\le,\ge$ 转化为 $<,>$ 即可不用判断半平面交为直线或点的特殊情况。

最后一个问题：一个凸包中整点个数（不含边缘上的）应该怎么算？发现本题的半平面交凸包是个格点多边形，边缘上的点个数等于凸包上相邻两点切比雪夫距离和，面积可以多边形面积直接求，已知这两个就可以用皮克公式直接推出这个多边形内格点个数（也就是答案）了。

> 皮克公式 $S=A-\frac{B}{2}-1$。其中 $A$ 是多边形内格点个数；$B$ 是多边形边缘上的个点个数；$S$ 是多边形的面积。

但是这样过不了，延长后的 $a',b',c'$ 是等腰三角形且腰是三边中最长的情况或者 $a',b',c'$ 是等边三角形的情况会算重，简单容斥即可。

[ac link](https://mirror.codeforces.com/problemset/submission/571/302252140)。

---

## 作者：mzgwty (赞：4)

题解中都用了减法原理，这里来一个非常莽的做法（就是直接算）

假设$a$增加了$x$，$b$增加了$y$，$c$增加了$z$  （$x,y,z$均非负）

可以列出一系列不等式

$$\left\{
\begin{array}{l}
a+x<b+y+c+z\\
b+y<a+x+c+z\\
c+z<a+x+b+y\\
x+y+z \le l
 \end{array}
\right.
$$

令

$$
m=c-a-b,n=b-a-c,p=a-b-c
$$

化简有

$$\left\{
\begin{array}{l}
x+y-z>m\\
x+z-y>n\\
y+z-x>p\\
x+y+z \le l
 \end{array}
\right.
$$

令 $w=x-y,s=x+y$

我们可以枚举$w$，再来计算在这个$w$的情况下有多少种方案

那么有$z>max(n-w,p+w)$

因为$x,y$都是正数，所以$|w|\le s\le l-z$

接下来考虑把答案分成两部分来计算

第一部分是$s\ge\lceil \frac{l+m+1}{2}\rceil$，这个时候$x+y+z\le l$的限制比$x+y-z\ge m+1$的限制更紧

因为$x=\frac{s+w}{2},y=\frac{s-w}{2}$，所以$w,s$的奇偶应该一致

那么就是一个等差数列求和的形式了，首项与公差为$1$，项数就是$\frac{l-max(n-w,p+w)-max(\lceil \frac{l+m+1}{2}\rceil,|w|))}{2}$但由于奇偶需要一致，所以需要微调一下，详见代码

第二部分是$s\le$ 刚才那个值，这个时候$x+y-z\ge m+1$的限制更紧，求答案总数的方法同上

这种做法细节比较多，还是看下代码

```cpp
#include<bits/stdc++.h>
#define R register
#define int long long
#define max(a,b) (a>b?a:b)
#define min(a,b) (a<b?a:b)
using namespace std;

inline int read() {
	int res=0,f=1;char ch;
	while(!isdigit(ch=getchar())) if(ch=='-') f=-1;
	do {
		res=res*10+ch-'0';
	} while(isdigit(ch=getchar()));
	return res*f;
}

inline void init() {
	freopen("triangle.in","r",stdin);
	freopen("triangle.out","w",stdout);
}

int a,b,c,L;

signed main() {
//	init();
	a=read(),b=read(),c=read(),L=read();
	int m=c-a-b,n=b-a-c,p=a-b-c;
	int ans=0;
	for(R int w=-L ; w<=L ; ++w) {
		int mx=max(-1,max(n-w,p+w)),Smin=labs(w),Smax=L;
		int S1=(L+m+1)/2+((L+m+1)&1),S=max(Smin,S1);Smax=min(Smax,L-mx);
		if(w&1) {
			if(!(S&1)) ++S;
			if(!(Smax&1)) --Smax;//这一行和上一行是微调
			if(S<=Smax) ans+=((Smax-S)/2+1)*(L-mx)-(S+Smax)*((Smax-S)/2+1)/2;
		}
		else {
			if(S&1) ++S;
			if(Smax&1) --Smax;//这里也是
			if(S<=Smax) ans+=((Smax-S)/2+1)*(L-mx)-(S+Smax)*((Smax-S)/2+1)/2;
		}
		Smax=L,--S1,S=min(Smax,S1),Smin=max(Smin,m+1);
		if(w&1) {
			if(!(S&1)) --S;
			if(!(Smin&1)) ++Smin;//这里也还是
			if(S>=Smin) ans+=(S+Smin)*((S-Smin)/2+1)/2-((S-Smin)/2+1)*(m+1+mx);
		}
		else {
			if(S&1) --S;
			if(Smin&1) ++Smin;//这里仍然是
			if(S>=Smin) ans+=(S+Smin)*((S-Smin)/2+1)/2-((S-Smin)/2+1)*(m+1+mx);
		}
	}
	printf("%lld",ans);
	return 0;
}
```














---

## 作者：262620zzj (赞：1)

# 前置知识

$$\Delta f(x)=f(x+1)-f(x)$$

$$\sum_{x=a}^{b}\Delta f(x)=f(b+1)-f(a)$$

$$x^{\underline{n}}=x(x-1)(x-2)\dots(x-n+1)$$

$$x^{\underline{n}}=\Delta (\frac{x^{\underline{n+1}}}{n+1})$$


# 基础思路
容斥原理，先计算出所有情况，再减去不合法的情况。（也就是不符合两边之和大于第三边这个三角形规律）。

三边分别当作最长边，枚举分配给最长边的长度，可以轻松算出不合法方案数，时间复杂度 $O(L)$。

代码其他题解写的非常清楚。

# 优化

可以发现这个算法瓶颈就在于有一个循环枚举了一遍长度。可以发现循环内的运算是很具有规律的，所以尝试一下简化。

记 $A=a+b-c$

```cpp
for(int x=max(0,A);x<=L;x++){
	int y=min(L-x,x-A);
	ans-=(y+1)*(y+2)/2;
}
```

这段代码中把 $x$ 看成自变量，$-x+L,x-A$ 看成一次函数，$y$ 取值的变化过程画在一个坐标系内，可以有所发现。

![](https://cdn.luogu.com.cn/upload/image_hosting/wha1bdw2.png)

红色是 $x-A$，蓝色是 $-x+L$。

$y$ 取较小值，是图中绿色的点。根据红蓝交点的横坐标 $x=\frac{L+A}{2}$ 的不同，函数的形态有 $4$ 种情况。**先考虑 $x$ 是整数的情况。**

- $L<x\Rightarrow A>L$，循环一次也不会执行，所以无事发生，答案不会有任何变化。

- $\frac{L}{2}\le x<L\Rightarrow 0\le A<L$，图象是这样的。

![](https://cdn.luogu.com.cn/upload/image_hosting/f2v2ekve.png)

根据 $x=\frac{L+A}{2}$ 记 $lim=\frac{L-A}{2}$ 为转折点的纵坐标。可以分两段求和，先看上升段。

$$\sum_{y=0}^{lim}\frac{(y+1)(y+2)}{2}$$

$$=\sum_{y=2}^{lim+2}\frac{y(y-1)}{2}$$

$$=\sum_{y=2}^{lim+2}\frac{y^{\underline{2}}}{2}$$

$$=\sum_{y=2}^{lim+2}\Delta(\frac{x^{\underline{3}}}{6})$$

$$=\frac{(lim+3)^{\underline{3}}}{6}-\frac{2^{\underline{3}}}{6}$$

$$=\frac{(lim+3)^{\underline{3}}}{6}$$

下降段反着看其实就是上升段，所以最终不合法方案数翻倍，再减重复计算的点 $lim$，不合法数量是

$$\frac{(lim+3)^{\underline{3}}}{3}-\frac{(lim+1)(lim+2)}{2}$$

- $0\le x<\frac{L}{2}\Rightarrow -L\le A<0$，图象是这样的。

![](https://cdn.luogu.com.cn/upload/image_hosting/y0gfn8tq.png)

所有的减去黄色点就是绿色点。所有点刚才已经求出了，黄色点的求法类似。

$$\sum_{y=0}^{-1-A}\frac{(y+1)(y+2)}{2}$$

$$\cdots$$

$$=\frac{(2-A)^{\underline{3}}}{6}$$

那么不合法方案数只需在上一条基础上减去它即可。

- $x<0\Rightarrow -A<L$ 最长边与其余两边的和之差大于 $L$，无论怎么分配也不可能构成一个三角形。所以直接 $ans\gets0$。

---

接下来就是 $x$ 不是整数的情况了。显然只对 $0\le x<L$ 的两种情况有影响。

![](https://cdn.luogu.com.cn/upload/image_hosting/rzt3zmwd.png)

可以发现其他不变，只是 $lim$ 变成了它的上一个点。并且，也不用担心 $lim$ 被重复计算了。所以 $x$ 不是整数的情况下，只需要对刚才第二、三种情况的式子稍加修改即可。

去掉

$$\frac{(lim+1)(lim+2)}{2}$$

再改 $lim$。

$$\frac{(lim+3)^{\underline{3}}}{3}\to \frac{(lim+2)^{\underline{3}}}{3}$$

理论时间复杂度 $O(1)$，可以通过大约 $L\le 10^{12}$ 的数据。因为太大会爆 `__int128`。

# 代码

```cpp
#include<bits/stdc++.h>
using namespace std;
typedef long long ll;
ll _3(ll x){return x*(x-1)*(x-2);}//3次下降幂
ll a,b,c,L,ans;
void figure(ll A,ll L){
	ll lim=(L-A+1)/2;//上取整
	double x=1.0*(L+A)/2;
	if(x<0){ans=0;return;}
	if(x>L)return;
	if((L+A)%2)ans-=_3(lim+2)/3;//判断x是否是整数
	else{
		ans-=_3(lim+3)/3;
		ans+=(lim+1)*(lim+2)/2;
	}
	if(x<1.0*L/2)ans+=_3(2-A)/6;
}
int main(){
	scanf("%lld%lld%lld%lld",&a,&b,&c,&L);
	ans=_3(L+3)/6;
	figure(a+b-c,L);
	figure(b+c-a,L);
	figure(c+a-b,L);
	printf("%lld\n",ans);
	return 0;
}
```


---

## 作者：Siegerkranz_2735 (赞：1)

$O(1)$ 算法，理论上的最优解。

#### 前置知识

差分运算：

$$\Delta f(x)=f(x+1)-f(x)$$

定和式：

$$\Sigma_{a}^{b}f(x)\delta x=\sum_{k=a}^{b-1}f(k)$$

$$\Sigma_{a}^{b}\Delta f(x)\delta x=f(b)-f(a)$$

下降幂：

$$x^{\underline{n}}=\begin{cases}
  x(x-1)(x-2)\dots(x-n+1) & (x >0) \\
  1 & (x=0) \\
  \frac{1}{(x+1)(x+2)\dots(x-n)} & (x <0)
\end{cases}$$

$$x^{\underline{n}}=\Delta (\frac{x^{\underline{n+1}}}{n+1})$$

#### 正文

这道题直接求比较难，可以考虑先求总的方案数，再求不合法的方案数，然后相减得到答案。

##### 总方案数

可以把问题转换为枚举 $0\sim l$ 分成 $3$ 个自然数。

$$\sum_{i=0}^{l} C_{i+2}^{2}=\sum_{i=0}^{l} \frac{(i+2)(i+1)}{2}=\sum_{i=2}^{l+2} \frac{i^{\underline{2}}}{2}=\Sigma_{2}^{l+3} \Delta (\frac{x^{\underline{3}}}{6})\delta x=\frac{(l+3)^{\underline{3}}}{6}$$

##### 不合法的方案数

可以利用三角形两边之和大于第三边的性质，分别枚举每个边是最长边的情况，枚举给最长边加多少长度，然后求出剩下的长度。

这里求分配剩下的长度，就是 ```min(c+i-a-b,l-i)``` （其中 $c$ 是最长边， $i$ 是分给最长边的个数）

于是有这样的代码：

```
for(int i=max(0,a+b-c);i<=l;i++){
	int x=min(c+i-a-b,l-i);
	ans-=(x+1)*(x+2)/2;
}
```

可以发现这是可以优化的。

令 $A=a+b-c$ 将 $-A+i$ 和 $l-i$ 画在坐标系上。

![](https://cdn.luogu.com.cn/upload/image_hosting/k3kqmi4s.png)

计算它们的交点 $l-x=-A+x$ 得到 $x=\frac{l+A}{2} ,y=\frac{l-A}{2}$ 要分几种情况考虑：

- $\frac{l+A}{2}>l$ 此时无解，$ans$ 就不需要减。

- $\frac{l}{2}\le \frac{l+A}{2}\le l$ 此时是 $2\Sigma_{0}^{\lfloor\frac{l-A}{2}+1\rfloor} \frac{(x+1)(x+2)}{2}\delta x=2\Sigma_{0}^{\lfloor\frac{l-A}{2}+1\rfloor}C_{x+2}^{2}\delta x=2\Sigma_{2}^{\lfloor\frac{l-A}{2}+3\rfloor}C_{x}^{2}\delta x=2\Sigma_{2}^{\lfloor\frac{l-A}{2}+3\rfloor}\frac{x^{\underline{2}}}{2}\delta x=2\Sigma_{2}^{\lfloor\frac{l-A}{2}+3\rfloor}\Delta (\frac{x^{\underline{3}}}{6})\delta x=\frac{(\lfloor\frac{l-A}{2}+3\rfloor)^{\underline{3}}}{3}$ 这里注意，如果 $\frac{l-A}{2}$ 是整数就要减去 $\frac{(l-A+2)(l-A+2)}{8}$ 因为他重复算了一次，不是整数的话要减两次。

- $0<\frac{l+A}{2}<\frac{l}{2}$ ![](https://cdn.luogu.com.cn/upload/image_hosting/21mropwd.png) 于是可以直接套用第二种情况，再减去蓝色部分。蓝色部分是 $\Sigma_{0}^{-A}C_{x+2}^{2}\delta x=\frac{(2-A)^{\underline{3}}}{6}$。最终就要减 $\frac{(\lfloor \frac{l-A}{2}\rfloor +3)^{\underline{3}}}{3}-\frac{(2-A)^{\underline{3}}}{6}$ 注意跟第二条结尾一样，重复的部分减去，没有就见减两次。

- $\frac{l+A}{2}\le 0$ 这个时候就是不管怎么分配都形成不了三角形，图像上看就是紫色的线的最低点高于红色的线的最高点，全部选红线，求出来就是减去总方案数，正好对上了，可以直接特判让 $ans=0$。

CF571A
```cpp
#include<bits/stdc++.h>
#define int long long
using namespace std;
int power3(int x){return x*(x-1)*(x-2);}
int a,b,c,l,ans;
void figure(int a,int b,int c){
	int A=a+b-c;
	int y=(l-A+1)/2;
	double x=1.0*(l+A)/2;
	if(x<0||x>l){
		if(x<0)ans=0;
		return;
	}
	if(l+A&1){
		if(x<1.0*l/2)ans-=power3(y+2)/3-power3(2-A)/6;
		else if(x<l)ans-=power3(y+2)/3;
	}
	else{
		if(x<1.0*l/2)ans-=power3(y+3)/3-power3(2-A)/6-(y+1)*(y+2)/2;
		else ans-=power3(y+3)/3-(y+1)*(y+2)/2;
	}
}
signed main(){
	cin>>a>>b>>c>>l;
	ans=power3(l+3)/6;
	figure(a,b,c);
	figure(c,a,b);
	figure(b,c,a);
	cout<<ans;
	return 0;
}
```
```

---

## 作者：几何微粒子 (赞：1)

~~组合题！毁我青春~~

这道题很明显需要采取优化，但是却不能直接累加方案求解。

所以我们可以用**总方案数-不成立方案数**的方法来做。

---

>求总方案数（算出 $x+y+z\le l$的方案数）

用**隔板法**解决，三个隔板分出四个区域。

- $a$ 增加的长度

- $b$ 增加的长度

- $c$ 增加的长度

- 增加总长度和 $l$ 的差

所以总方案数即为 $C_{l+3}^3$

---

>求不合法的方案数

众所周知，三角形两条短边之和 $>$ 第三边

所以分 $a$ 最长，$b$ 最长，$c$ 最长三种情况。

不妨设 $a$ 和 $b$ 短一点，$c$ 最长，

则对于每一种情况，枚举给 $c$ 加上的长度。

然后可以用插板法求出剩下的长度的方案数：

- 两个隔板分出三个区域。

- $a$ 增加的长度

- $b$ 增加的长度

- 增加总长度和 $l$ 的差

但是由于**剩下的长度仍可能成立**，所以要和 $c+i-a-b$ 取最小值，保证不会求出存在解。

最后把总方案数**减去三个边最长的情况**即可。

---

#### code:

```cpp
#include<bits/stdc++.h>
using namespace std;
int a,b,c,l;
int jc[300010];
int ans;
int getc(int x,int y){//C[a][b]
	return jc[x]/(jc[y]*jc[x-y]);
}
void did(){
	int s=a+b;
	for(int i=max(0,s-c);i<=l;i++){//有时不是三角形，a+b-c<0所以要和0比大小 
		int nowlen=l-i;
		nowlen=min(nowlen,(c+i)-s);//避免计算到可行解 
		ans-=getc(nowlen+2,2);
	}
}
int main(){
	scanf("%d%d%d%d",&a,&b,&c,&l);
	jc[0]=1;
	for(int i=1;i<=l+5;i++){
		jc[i]=jc[i-1]*i;
	}
	ans=getc(l+3,3);
	did();//a b c
	swap(a,c);
	did();//c b a
	swap(a,b);
	did();//a c b
	printf("%d",ans);

return 0;
}

```


---

## 作者：Create_Random (赞：1)

[A. Lengthening Sticks](https://codeforces.ml/problemset/problem/571/A)

解法：

直接考虑合法的三角形并不好做，

那么可以用容斥原理解决，

用总方案数减去不合法方案数得出合法三角形数。

因为加上的边总长度不超过 $l$ ,

所以问题就相当于是将数字 $l$ 分为三份。（允许为空）

现在就不能直接用朴素的插板法来做了，

更换思路：

将 $l$ 个元素加至 $l+3$ 个,

使加上的 $3$ 表示为 $3$ 个“不存在的元素”，

因为 $l+3$ 个元素是互不干扰的，

所以可以直接使用插板法划分出 $3$ 个集合，

当此集合中只有那个“不存在的元素”时即为空。

总方案数即为 $\sum \limits_{i=0}^l C_{l+2}^2$ .

现在考虑不合法的方案数，

因为三角形两边之和大于第三边，

所以只需分 $3$ 类枚举加上的最长边中所有两边之和小于等于第三边的情况即可。

时间复杂度 $O(l)$ .

$Code$:
```cpp
#include<bits/stdc++.h>
#define int long long
using namespace std;
int a,b,c,l;
int ans;
void calc(int a,int b,int c)
{
	for(int i=max(0ll,a+b-c);i<=l;i++)
	{
		int x=min(c+i-a-b,l-i);
		ans-=(x+1)*(x+2)/2;
	}
}
signed main()
{
	scanf("%lld%lld%lld%lld",&a,&b,&c,&l);
	for(int i=0;i<=l;i++)
	{
		ans+=(i+1)*(i+2)/2;
	}
	calc(a,b,c);
	calc(a,c,b);
	calc(b,c,a);
	printf("%lld",ans);
	return 0;
}
```


---

## 作者：BigSmall_En (赞：0)

### [CF571A](https://codeforces.com/contest/571/problem/A) Lengthening Sticks

> 你有三根木棍，长度分别为 $a,b,c$ （单位：厘米）。你可以选择把这些木棍加长一些长度，但是加长部分总和不能超过 $l$ 厘米。现在给出 $a,b,c,l$，求有多少种加长的方案使得加上后的 $a',b',c'$ 可以围成一个面积为正的三角形（即不能退化成线段或者为不成三角形）。
>
> 数据范围 $1\leq a,b,c\leq 3\times 10^5,0\leq l\leq 3\times 10^5$。

数学低手想不到容斥和 $O(1)$ 做法，只能直接做了，实际上也并不难而且思路比较直接。

#### step1

首先我们枚举一条边 $c$ 加长长度为 $i$，即先固定一条边的长度。则问题转化为

> 有三个木棍，长度分别为 $a,b,c$，可以对长为 $a,b$ 的木棍加长一些长度，加长部分总和不能超过 $l$，满足三条木棍可以围成三角形。

（注意其中 $c,l$ 的值与原题有所不同，它们均可以通过枚举的 $i$ 计算出来）

现在我们假设长 $a$ 的木棍加长 $x$，长 $b$ 的木棍加长 $y$。先计算出 $b+y\geq a+x$ 的情况下的答案，再计算出 $b+y< a+x$ 情况下的答案。

#### step2

假设 $b+y\geq a+x$，可以得到以下若干个不等式
$$
b+y\geq a+x\\
x+y\leq l\\
c-(a+x)< b+y< c+(a+x)\\
x\geq 0,y\geq 0
$$
整理成直线的形式，并改写 $<,>$ 为 $\leq,\geq$，可以得到
$$
\begin{cases}
y\geq x+a-b\\
y\leq x+c+a-b-1\\
y\geq -x+c-a-b+1\\
y\leq -x+l\\
x\geq 0\\
y\geq 0
\end{cases}
$$
则理论上我们平面上满足这些条件的整点 $(x,y)$ 个数即可。这个玩意可以使用半平面交解决。

#### step3

由于我是计算几何低手，不会半平面交、皮克公式，也不会分类讨论求面积，只能看看有没有其他方法了。

一个朴素的想法是对于每个 $x$，求一个 $y$ 的范围区间，这个区间可以根据约束条件 $O(1)$ 求得，这样就可以枚举 $x$ 求了。

我们真的需要枚举每个 $x$ 吗？答案显然是否定的。我们将上面若干条直线（即半平面对应直线）的所有交点求出来，然后交点的按横坐标 $x$ 排序，容易发现相邻的两个横坐标之间，$y$ 的范围大小是一个等差数列（挺显然的，可以自己画一下）。由于横坐标知道，等差数列的项数知道，又两端的 $y$ 范围大小也知道，即等差数列首项末项均知道，则可以直接求和公式算出来两个横坐标直接有多少点满足条件。然后枚举两个相邻的横坐标即可。

可能说的比较抽象，这个示意图意会一下吧，将夹在 $l_1,l_2,l_3,l_4,x=0,y=0$ 的面积按横坐标分成 $4$ 块。

![](https://cdn.luogu.com.cn/upload/image_hosting/5tz3zm39.png)

#### 最后

现在我们计算好了 $b+y\geq a+x$ 的情况，对于 $b+y<a+x$ 的情况，只需要改变一个约束条件即可同理做。

交点的个数最多为 $8$ 个是常数，因此复杂度为 $O(l)$。

#### 实现

代码的变量名定义和题解中不太一样，参考即可，[提交记录](https://codeforces.com/contest/571/submission/311624020)。

```cpp
#include <bits/stdc++.h>

using namespace std;

typedef long long ll;
typedef pair<int,int>ttfa;
const int N=1000006;
const int INF=0x3f3f3f3f;

inline ll calc(ll a,ll b,ll c,ll d){
	auto dw=[a,c](ll x){return max(max(x+a,-x+c),0ll);};
	auto up=[b,d](ll x){return min(x+b,-x+d);};

	if(b<a||c>d)return 0;
	vector<ll>lis;
	lis.push_back(-a);
	lis.push_back(-b);
	lis.push_back(c);
	lis.push_back(d);
	lis.push_back((c-a)/2ll);
	lis.push_back((d-a)/2ll);
	lis.push_back((c-b)/2ll);
	lis.push_back((d-b)/2ll);
	sort(lis.begin(),lis.end());
	lis.erase(unique(lis.begin(),lis.end()),lis.end());
	lis.erase(lis.begin(),upper_bound(lis.begin(),lis.end(),0));
	ll len=up(0)-dw(0)+1,las=0,ans=0ll;
	if(len>0)ans+=len;
	len=up(1)-dw(1)+1,las=1;
	for(auto x:lis){
		ll lenx=up(x)-dw(x)+1ll;
		if(lenx>0){
			if(len>0)ans+=(len+lenx)*(x-las+1)/2ll;
			else ans+=lenx;
		}
		len=up(x+1)-dw(x+1)+1ll,las=x+1;
	}
	return ans;
}

inline ll solve(ll x,ll y,ll v,ll s,ll opt){//opt=0 x>=y; opt=1 x>y
	ll a=y-x+opt;
	ll b=v+y-x-1;
	ll c=max(max(v-x-y+1ll,0ll),a);
	ll d=s;
	return calc(a,b,c,d);
}
int main(){
	ll x,y,z,l;scanf("%lld%lld%lld%lld",&x,&y,&z,&l);
	ll ans=0;
	for(ll i=0;i<=l;++i){
		ans+=solve(y,z,x+i,l-i,0);
		ans+=solve(z,y,x+i,l-i,1);
	}
	printf("%lld\n",ans);
	return 0;
}
```

---

## 作者：Cyx20110930 (赞：0)

# 题意简述

有四个数 $a,b,c,l$，询问 $|S|$，其中 $S$ 为 $\set {(a',b',c')|a \le a',b\le b',c\le c',a'+b'+c'\le a+b+c+l}$。

# Sol

很明显不能暴力算出满足的数量。

正难则反，尝试算出总共的，再减去不满足的就行。

总共的数量为 $C_{l+3}^3$。

其中，不满足的一定满足 $\max(a',b',c')>a'+b'+c'-\max(a',b',c')$，那么挨个求解即可。

# Code

```
#include<bits/stdc++.h>
using namespace std;
#define int long long
int ans;
int C(int a,int b){
	if(a<b)return 0;
	if(b==2){
		return a*(a-1)/2;
	}
	if(b==3){
		return a*(a-1)*(a-2)/6;
	}
}
void minus(int x,int y,int z,int ll){//z 长边
	for(int i=max(0,x+y-z);i<=ll;i++){
		ans-=C(min(ll-i,z+i-x-y)+2,2);
	}
}
signed main(){
	int a,b,c,l;
	cin>>a>>b>>c>>l;
	ans=C(l+3,3);
	minus(a,b,c,l);minus(a,c,b,l);minus(b,c,a,l);
	cout<<ans;
}
```

---

## 作者：Erica_N_Contina (赞：0)

## 思路

cf 日常数学题了，不过是容斥原理。

像这种组合+求方案数的题目，第一眼就应该想到是容斥吧。我们先求出总方案，然后用其减去不合法的方案即可。

- 总方案

现在我们考虑 $a,b,c$，满足 $a+b+c≤l$ 的总方案数（这里的 $a,b,c$ 是增加的长度）。既然题目允许我们从 $0$ 到 $l$ 枚举，那么我们就可以枚举 $a+b+c=k,k\in[0,l]$。现在的问题就是求 $a+b+c=k$ 的三元组 $(a,b,c)$ 的数量了。

这里我们使用组合中常见的**隔板法**（这是个很常用的技巧了）：我们考虑现在是有 $k$ 个物品，我们在这 $k$ 个物品之间放置 $2$ 个隔板，这样我们就可以吧 $k$ 分成 $3$ 个数了。隔板有多少种放法，那么 $(a,b,c)$ 的数量就有多少。这里还要注意隔板可以放的位置实际上有 $k+1$ 个，因为我们允许 $a,b,c$ 其中存在 $0$。

不对！实际上，可以放置的位置有 $k+2$ 个！我们想想，如果只有 $k+1$ 个空位，假设 $a+b+c=5$，那么怎么样同时可以表示 $(0,0,5)(0,5,0)(5,0,0)$，同样的，怎么样表示 $(i,0,j),i+j=5$ 呢。

这里用了一个很巧的方法：我们创建一个**形式补位**，这个位置是不固定的。当我们选定第一个隔板的位置时，形式补位就在这个隔板出新建一个空位。这样如果第二个隔板放在这个形式补位上，不就可以表示上面的情况了吗？

所以对于每个 $k$，情况数量就是 $C_{k+2}^{2}$。

- 不合法方案

我们枚举哪一条边过长了。从最小的有可能使得三角形不成立的增加量开始一直到 $l$ 枚举增加量，并且对于每一个被枚举的值 $i$ 计算 $x,y$ 被延长的最长长度 $t$，满足：如果小于等于这个长度，过长边增加的 $t-i$ 长度就使得过长边长度 $+(t-i)$ 大于等于其余两条边长度和 $+t$，就是不合法。

---

```C++
#include<bits/stdc++.h>
#define rep(l,r,i) for(int i=l,END##i=r;i<=END##i;++i)
#define per(r,l,i) for(int i=r,END##i=l;i>=END##i;--i)
using namespace std;
#define int long long
#define pii pair<int,int>

#define lc(x) (x<<1)
#define rc(x) (x<<1|1)

#define rd read()
inline int read()
{
	int xx=0,ff=1;
	char ch=getchar();
	while(ch<'0'||ch>'9') {if(ch=='-') ff=-1;ch=getchar();}
	while(ch>='0'&&ch<='9') xx=xx*10+(ch-'0'),ch=getchar();
	return xx*ff;
}
inline void write(int out)
{
	if(out<0) putchar('-'),out=-out;
	if(out>9) write(out/10);
	putchar(out%10+'0');
}

const int N=5e3+5;
const int INF=1e18+5;
const int MOD=998244353;
int ans,m;
int a,b,c,l;

int cal(int x,int y,int z){
	int ret=0;
	
	for(int i=max(0ll,x+y-z);i<=l;i++){
		//max(0ll,x+y-z)是最小的有可能使得三角形不成立的增加量，这里即枚举增加量
		int t=min(l-i,z+i-x-y);
			//x,y被延长的最长长度，如果小于等于这个长度，z增加的t-i长度就使得z+(t-i)大于x+y+t，就是不合法的情况
		ret+=(t+1)*(t+2)/2;
			//可以用组合数算
	}
	return ret;
}

signed main(){
	a=rd,b=rd,c=rd,l=rd;
	
	for(int i=1;i<=l;i++)ans+=(i+1)*(i+2)/2;
	ans-=cal(a,b,c)+cal(a,c,b)+cal(b,c,a);
		//最后一个参数是那个超长的边，只需要枚举3条边即可，前两个参数位置没有关系
	cout<<ans+1<<endl;
	return 0;
}

```




---

## 作者：xiaoyuchenp (赞：0)

容斥原理应用题。

**思路**

考虑用总方案数减去不合法的方案数，用容斥做法即可得出最终答案。

**求总方案数**

枚举加上的数的总和 $k$，就变成了把 $k$ 分为三个整数。这种用隔板法即可，易得 $k$ 的分配方案为 $C_{k+2}^k$ 个，则总方案为 $\Sigma^l_{k=1}C_{k+2}^k+1$。

为方便计算，可将 $C_{k+2}^k$ 化简为 $\dfrac{(k+2)\times(k+1)}{2}$。

同时由于三个数均为 0 的方案也要加上，所以最后输出答案时别忘了加 1。

**求不合法的方案数**

由三角形三边之和大于第三边定理求即可。注意要分三类枚举，代码实现较为简单，具体思路就不赘述了。

还有一个坑点：别忘了开 long long。

时间复杂度 $O(l)$，能够通过本题。

**code**

```cpp
#include<bits/stdc++.h>
#define int long long 
using namespace std;
int a,b,c,l,ans;
int f(int n){
	return (n+2)*(n+1)/2;
}
int solve(int a,int b,int c){
	int sum=0;
	for(int i=max((long long)0,a+b-c);i<=l;i++){
		int tmp=min(l-i,c+i-a-b);
		sum+=f(tmp);
	}
	return sum;
}

signed main(){
	cin>>a>>b>>c>>l;
	for(int i=1;i<=l;i++)ans+=f(i);
	ans-=(solve(a,b,c)+solve(a,c,b)+solve(b,c,a));
	cout<<ans+1;
	return 0;
}
```

---

## 作者：CRTL_xzh2009 (赞：0)

逆向思考，全部累加**不能**构成三角形的方案。

总累加方案：

$x+y+z+u=l$，表示 $a,b,c$ 分别累加 $x,y,z$，剩余 $u$ 的方案数。

排列组合中的档板法：$C_{l+3}^3$。

接下来枚举不能构成三角形的方案数：

设最大边为 $a$，则：

$b+c \le a$。

$b+y+c+z \le a+x$ 且 $y+z+x \le l$。

则 $y+z \le \min(l-x, a+x-b-c)$。

结果仍然是组合数：$C_{\min(l-x, a+x-b-c)}^2 $。



```cpp
#include<bits/stdc++.h>
#define int long long
using namespace std;
int maxs(int x,int y,int z)
{
	return max(max(x,y),z);
}
int tri(int x,int y,int z)
{
	if(2*maxs(x,y,z)<x+y+z)
	return 1;
	return 0;
}
signed main()
{
	    int ans=0,a,b,c,l;
	    cin>>a>>b>>c>>l;
	    for(int i=l;i>=0;i--)
	    ans+=(i+2)*(i+1)/2;
	    for(int i=0;i<=l;i++)
	    {
	    	int q=a-b-c+i,r=l-i;
	    	int s=min(q,r);
	    	if(s>=0)
	    	ans-=(s+1)*(s+1+1)/2;
	    	q=b-a-c+i;
	    	s=min(q,r);
	    	if(s>=0)
	    	ans-=(s+1)*(s+1+1)/2;
	    	q=c-a-b+i;
	    	s=min(q,r);
	    	if(s>=0)
	    	ans-=(s+1)*(s+1+1)/2;
		}
		cout<<ans<<endl;
}
```


---

## 作者：西卡洛斯 (赞：0)

很难直接求出合法方案数，考虑容斥原理，用总方案数减去不合法方案数。

### 总方案数

相当于把最多 $l$ 长度的木棍分成三段，枚举加长的长度 $i$ ，对于每个 $i$ 来说有 $C_{i+2}^i$ 种分法（插板法），求和后再加上 `0 0 0` 的方案（哪根也不加长）。总方案数即为 $ans=\Sigma^l_{i=1}C_{i+2}^i+1$，为了方便计算，把 $C_{i+2}^i$ 化简一下：

$$C_{i+2}^i$$ 

$$=\dfrac{(i+2)!}{2!\times(i+2-2)!}$$

$$=\dfrac{(i+2)!}{2\times i!}$$
 
$$=\dfrac{(i+2)\times(i+1)}{2}$$

### 不合法方案数

三角形两边之和大于第三边，分别对 $a,b,c$ 枚举最长边中所有两边之和小于等于第三边的情况即可。

别忘了开 long long 。

代码：

```cpp
#include <iostream>
#include <cstdio>
#include <algorithm>
#include <cstring>
using namespace std;
typedef long long ll;
ll a,b,c,l;
ll wrong(ll a,ll b,ll c)// 错位排序
{
	ll ret=0;
	for(ll i=0;i<=l;i++)
	{
		ll x=min(l-i,c+i-a-b);
		if(x>=0) ret+=(x+2)*(x+1)/2;
	}
	return ret;
}
int main()
{
	ll ans=0;
	scanf("%lld%lld%lld%lld",&a,&b,&c,&l);
	for(ll i=0;i<=l;i++) ans+=(i+1)*(i+2)/2;
	ans=ans-wrong(a,b,c)-wrong(a,c,b)-wrong(b,c,a);
	printf("%lld",ans);
	return 0;
}
```


---

## 作者：swiftc (赞：0)

我们先求出来所有可能的方案，共有 $C(l+3,3)$ 种（插板法），再减去不合法的方案数

不合法的方案数要分三类讨论，$a$ 为最长边; $b$ 为最长边; $c$ 为最长边;对于每一种情况，枚举给最长边加多少长度，然后求出剩下的长度（注意，需要和$c+i-a-b$ ( $c$ 为最长边)取$min$，因为我们需要保证这种情况不合法)，然后就可以用插板法求了

__代码:__

```cpp
#include<bits/stdc++.h>
#define int long long
#define max(a,b) a>b?a:b
using namespace std;
int ans;
int C(int a,int b){
	if(a<b)return 0;
	if(b==2){
		return a*(a-1)/2;
	}
	else{
		return a*(a-1)*(a-2)/6;
	}
}
void work(int a,int b,int c,int l){
	for(int i=max(0,a+b-c);i<=l;i++){
		int tmp=min(l-i,c+i-a-b);
		ans-=C(tmp+2,2);
	}
}
main(){
	
	int a,b,c,l;
	cin>>a>>b>>c>>l;
	ans+=C(l+3,3);
	work(a,b,c,l);
	work(a,c,b,l);
	work(b,c,a,l);
	cout<<ans<<endl;
}
```


---

