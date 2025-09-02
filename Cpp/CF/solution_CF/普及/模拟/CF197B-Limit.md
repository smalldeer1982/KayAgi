# Limit

## 题目描述

You are given two polynomials:

- $ P(x)=a_{0}·x^{n}+a_{1}·x^{n-1}+...+a_{n-1}·x+a_{n} $ and
- $ Q(x)=b_{0}·x^{m}+b_{1}·x^{m-1}+...+b_{m-1}·x+b_{m} $ .

Calculate limit ![](https://cdn.luogu.com.cn/upload/vjudge_pic/CF197B/c4175ff9e67dcea784338cdf48751a5246b376e3.png).

## 说明/提示

Let's consider all samples:

1. ![](https://cdn.luogu.com.cn/upload/vjudge_pic/CF197B/fa0398edff13cf2c92e5c43221f39e276c660081.png)
2. ![](https://cdn.luogu.com.cn/upload/vjudge_pic/CF197B/c67cf94a1cc8bcaea0f1fad4d1517e71a16c059c.png)
3. ![](https://cdn.luogu.com.cn/upload/vjudge_pic/CF197B/10f72864aeb3074d34f0800e3222dff4f843160b.png)
4. ![](https://cdn.luogu.com.cn/upload/vjudge_pic/CF197B/40209670dcba21fdfb878390c6903f068a0dc416.png)
5. ![](https://cdn.luogu.com.cn/upload/vjudge_pic/CF197B/9292f5d3f957b00c90b246f44689b5ebc7f89abc.png)

You can learn more about the definition and properties of limits if you follow the link: http://en.wikipedia.org/wiki/Limit\_of\_a\_function

## 样例 #1

### 输入

```
2 1
1 1 1
2 5
```

### 输出

```
Infinity
```

## 样例 #2

### 输入

```
1 0
-1 3
2
```

### 输出

```
-Infinity
```

## 样例 #3

### 输入

```
0 1
1
1 0
```

### 输出

```
0/1
```

## 样例 #4

### 输入

```
2 2
2 1 6
4 5 -7
```

### 输出

```
1/2
```

## 样例 #5

### 输入

```
1 1
9 0
-5 2
```

### 输出

```
-9/5
```

# 题解

## 作者：Limit (赞：8)

~~题目撞名~~

# 题目大意:

给出两个函数 $P(x),Q(x)$.

$P(x)=a_0 \times x^N+a_1 \times x^{N-1}+a_2 \times x^{N-2} \cdots a_{N-1} \times x+a_N$

$Q(x)=b_0 \times x^M+b_1 \times x^{M-1}+b_2 \times x^{M-2} \cdots b_{M-1} \times x+b_M$

计算 $\lim_{x \to +\infty}\frac{P(x)}{Q(x)}$

# 分析

先看一下[极限的定义](https://baike.baidu.com/item/极限/3564509?fr=aladdin):设函数 $f(x)$ 在点 $x_0$ 的某一[去心邻域](https://baike.baidu.com/item/去心邻域)内有定义,如果存在常数 $a$,$\forall \varepsilon \in \mathbb{N}$,$\exists \delta>0$,使不等式$|f(x)-a|<\varepsilon$,在 $|x-x_0|\in(0,\delta)$ 时恒成立,那么常数 $a$ 就叫做函数 $f(x)$ 当 $x \to x_0$ 时的极限,记作 $\lim_{x \to x_0}f(x)=a$.(~~根本就不是人话~~)

定义非常简(kan)单(bu)明(dong)了,于是肯定会有人会用一种非常简单粗暴的方法去解决这道题,将一个非常大的数带入,然后计算,答案取一个近似值,那么问题来了,需要带怎样的一个数进去呢,又如何计算呢.所以这个方法显然就是错误的,那么就要从这两个函数入手了,可以发现 $\lim_{x \to +\infty}\frac{P(x)}{a_0 \times x^N}=1$ 具体证明见[洛必达法则](https://baike.baidu.com/item/洛必达法则/7646700?fr=aladdin),所以当 $x \to +\infty$ 时,$P(x)=a_0 \times x^N$,$Q(x)=b_0 \times x^M$,所以就直接取比较这两个值就好了.当 $N>M$时结果为 $+\infty$ 或 $-\infty$,结果与 $a_0$ 和 $b_0$ 的正负性有关,如果 $a_0*b_0>0$ 结果为 $+\infty$,反之为 $-\infty$.如果 $N<M$ 时结果为 $0$,当 $N=M$ 时结果自然就是 $\frac{a_0}{b_0}$ 了.

# 代码

```cpp
#include<bits/stdc++.h>
#define REP(i,first,last) for(int i=first;i<=last;++i)
#define DOW(i,first,last) for(int i=first;i>=last;--i)
using namespace std;
int N,M;
int a0,b0;//只要记录a0和b0
int Gcd(int a,int b)//需要约分
{
	if(!b)
	{
		return a;
	}
	return Gcd(b,a%b);
}
int main()
{
	scanf("%d%d",&N,&M);
	int air;//没用的值
	scanf("%d",&a0);
	REP(i,1,N)
	{
		scanf("%d",&air);
	}
	scanf("%d",&b0);
	REP(i,1,M)
	{
		scanf("%d",&air);
	}
	if(N<M)//如果N<M时最后的答案为0
	{
		printf("0/1");
		return 0;
	}
	if(a0*b0<0)//如果a0*b0<时需要输出符号
	{
		printf("-");
		a0=abs(a0);
		b0=abs(b0);
	}
	if(N>M)//如果N>M时最终的结果为无穷大
	{
		printf("Infinity");
		return 0;
	}
	int gcd=Gcd(a0,b0);//约分
	a0/=gcd;
	b0/=gcd;
	printf("%d/%d",a0,b0);//输出答案
	return 0;
}

```

---

## 作者：rui_er (赞：3)

题意：给定两个多项式 $P(x),Q(x)$，求 $\displaystyle\lim_{x\to+\infty}\frac{P(x)}{Q(x)}$ 的值。

---

乍一看好像很难，但考虑当 $x$ 趋近于无穷大时，多项式除最高次项以外的影响可以忽略。

经过少许数学推导~~和大量猜测~~，当 $P$ 的次数低于 $Q$ 时，这个极限为 $0$；当 $P$ 的次数高于 $Q$ 时，这个极限为 $\infty$ 或 $-\infty$；当次数相同时，这个极限为 $P$ 最高次项与 $Q$ 最高次项的比值，记得约分。


---

代码：

养成了一个习惯，就是用 `veryImportantVariable` 来存一些完全没用但要读入的东西（（（

```cpp
//By: Luogu@rui_er(122461)
#include <bits/stdc++.h>
#define loop while(true)
#define rep(x,y,z) for(ll x=y;x<=z;x++)
#define per(x,y,z) for(ll x=y;x>=z;x--)
#define fil(x,y) memset(x, y, sizeof(x))
using namespace std;
typedef long long ll;

int n, m, a, b, veryImportantVariable;

int main() {
	scanf("%d%d", &n, &m);
	if(n < m) return puts("0/1"), 0;
	scanf("%d", &a); rep(i, 1, n) scanf("%d", &veryImportantVariable);
	scanf("%d", &b); rep(i, 1, m) scanf("%d", &veryImportantVariable);
	if(a * b < 0) a = abs(a), b = abs(b), putchar('-');
	if(n > m) return puts("Infinity"), 0;
	int qwq = __gcd(a, b); a /= qwq; b /= qwq;
	printf("%d/%d\n", a, b);
	return 0;
}
```

---

## 作者：zhangyuxing (赞：3)

前言：洛谷评分真是太水了，尤其是CF，这道题竟然是黑题？
___
### 数学大水题

求$\lim\limits_{x\to\infty}\frac{p_x}{q_x}$ 
___
分类讨论：

(1)n<m:随着x增大，${p_x}$与${q_x}$的差距越来越大，比值趋近于${\frac{1}{\infty}}$或${\frac{1}{-\infty}}$,都为0。

(2)n>m:同理比值趋近于${\infty}$或${-\infty}$,需要再分类：

①${\frac{p_0}{q_0}}$>0，即${p_0}$与${q_0}$正负相同，此时比值趋近于${\infty}$。

②${\frac{p_0}{q_0}}$<0，即${p_0}$与${q_0}$正负不同,此时比值趋近于${-\infty}$。

(3)n=m:此时决定比值的是最高项系数${p_0}$与${q_0}$，${\frac{p_0}{q_0}}$的比值即为所求。
___
注意：
**要约分**
___
code of c++：

```cpp
#include<cstdio>
#include<algorithm>
using namespace std;
int p[105],q[105];
int divide(int x,int y)//约分
{
	bool flag=false;//比值为正,flag=0；比值为负,flag=1。
	if(x<0)x=-x,flag=!flag;
	if(y<0)y=-y,flag=!flag;
	if(flag)printf("-");
	int gcdxy;
	gcdxy=__gcd(x,y);
	x/=gcdxy;y/=gcdxy;
	printf("%d/%d",x,y);
	return 0;
}
int main()
{
	int n,m,i,j;
	scanf("%d%d",&n,&m);
	for(i=0;i<=n;++i)scanf("%d",&p[i]);
	for(i=0;i<=m;++i)scanf("%d",&q[i]);
	if(n<m)return printf("0/1")&0;
	else if(n==m)return divide(p[0],q[0]);
	else if((p[0]>0&&q[0]>0)||(p[0]<0&&q[0]<0))return printf("Infinity")&0;
	else printf("-Infinity");
	return 0;
}
```

---

## 作者：xyf007 (赞：2)

# 一道数学题
# 注意$$\lim_{x\rightarrow\infty}$$
### 分类讨论：
1.当$n$<$m$时，原式=$1/\infty$=0

2.当$n$>$m$时，若$a_0$/$b_0$>$0$，则原式=$\infty$；否则原式=$-\infty$

3.当$n$=$m$时，原式=$a_0$/$b_0$

# 注意约分！

```
#include <iostream>
#include <cstdio>
#include <algorithm>
#include <cstring>
using namespace std;
int n,m,a[200],b[200];
int gcd(int a,int b)
{
	if (a<b)
	{
		swap(a,b);
	}
	if (b==0)
	{
		return a;
	}
	return gcd(b,a%b);
}
int main(int argc, char const *argv[])
{
	scanf("%d%d",&n,&m);
	for (int i = 0; i <= n; ++i)
	{
		scanf("%d",&a[i]);
	}
	for (int i = 0; i <= m; ++i)
	{
		scanf("%d",&b[i]);
	}
	if (n<m)
	{
		printf("0/1\n");
		return 0;
	}
	if (n>m)
	{
		if (a[0]*b[0]>0)
		{
			printf("Infinity\n");
			return 0;
		}
		else
		{
			printf("-Infinity\n");
			return 0;
		}
	}
	if (a[0]*b[0]<0)
	{
		printf("-");
	}
	if (a[0]<0)
	{
		a[0]=-a[0];
	}
	if (b[0]<0)
	{
		b[0]=-b[0];
	}
	int GCD=gcd(a[0],b[0]);//也可以使用__gcd(a[0],b[0]);
	printf("%d/%d\n", a[0]/GCD,b[0]/GCD);
	return 0;
}
```

---

## 作者：lhjy666 (赞：2)

```cpp
#include<bits/stdc++.h>
#define ll long long
#define MOD 100000007
using namespace std;
int a[100005],b[100005];
int main()
{
	int n,m;
	scanf("%d%d",&n,&m);
	for (int i=0;i<=n;i++)
	{
		scanf("%d",&a[i]);
	}
	for (int i=0;i<=m;i++)
	{
		scanf("%d",&b[i]);
	}
	if(n>m)
	{
		if(a[0]<0&&b[0]>0||a[0]>0&&b[0]<0)
		{
			printf("-");
		}
		printf("Infinity");
	}
	else
	{
		if(n<m) printf("0/1");
		else
		{
			int gcd=__gcd(a[0],b[0]);
			a[0]=a[0]/gcd;
			b[0]=b[0]/gcd;
			int k=a[0]*b[0];
			if(k<0) printf("-");
			printf("%d/%d",abs(a[0]),abs(b[0]));
		}
	}
	return 0;
}
```

---

## 作者：lx_zjk (赞：1)

```cpp
#include<cstdio>
#include<iostream>
#include<cstdlib>
#include<cstring>

using namespace std;

typedef long long ll;

inline ll read(){
	ll x=0,f=1;char ch;
	do{ch=getchar();if(ch=='-')f=-1;}while(ch>'9'||ch<'0');
	do{x=x*10+ch-'0';ch=getchar();}while(ch>='0'&&ch<='9');
	return f*x;
}

const int maxn=100  + 5;

ll n,m,a[maxn],b[maxn];

inline ll gcd(ll a,ll b){
    if(b==0) return a;
    return gcd(b,a%b);
}

int main()
{
    n=read();m=read();
    for(int i=0;i<=n;i++){scanf("%I64d ",&a[i]);}
    for(int i=0;i<=m;i++){scanf("%I64d ",&b[i]);}
    if(m==n){if((a[0]>=0&&b[0]<0)||(a[0]<0&&b[0]>=0))cout<<"-";cout<<abs(a[0]/gcd(a[0],b[0]))<<"/"<<abs(b[0]/gcd(a[0],b[0]))<<endl;return 0;}
    else if(n>m){if((a[0]>=0&&b[0]<0)||(a[0]<0&&b[0]>=0))cout<<"-";puts("Infinity");return 0;}
    else {printf("0/1");return 0;}
}

```

---

