# [ABC372G] Ax + By < C

## 题目描述

### 题目简述

给定三个数列 $(A_1, A_2, \cdots, A_N)$，$(B_1, B_2, \cdots, B_N)$，$(C_1, C_2, \cdots, C_N)$，求满足 $A_ix+B_iy<C_i$ ($1 \leq i \leq N$) 的有序正整数对 $(x,y)$ 的个数。

## 说明/提示

约定 $1 \leq T \leq 2\times 10^5$，$1 \leq \sum N \leq 2\times 10^5$，$1 \leq A_i, B_i, C_i \leq 10^9$。

对于样例 $1$，第一个数据组中满足条件的 $(x, y)$ 有 $(1, 1)$ 和 $(2, 1)$，故应当输出 $2$。第二个数据组中，没有满足条件的 $(x, y)$，故应当输出 $0$。

## 样例 #1

### 输入

```
2
2
1 1 4
1 2 5
1
1 1 2```

### 输出

```
2
0```

## 样例 #2

### 输入

```
3
7
138 16011 918976
5478 7748 499926
5234 17727 748589
1157 10511 643136
31200 3005 721285
28839 14469 798851
1933 5378 864127
9
17775 1665 386430
37001 863 922418
9756 4182 746671
12379 9106 807578
3984 4049 640539
25333 9869 780810
20372 7000 688738
16107 11974 827227
10779 10531 770510
5
4916 14132 460944
11856 45422 610561
56014 18216 825793
10363 6220 945356
37418 33866 851593```

### 输出

```
660
995
140```

# 题解

## 作者：Nt_Tsumiki (赞：8)

## Description

给定 $n$ 个形如 $Ax+By<C$ 的方程，求有多少组 $(x,y)$ 满足所有的方程。

## Solution

做法比较一眼，我这里使用了比较暴力的半平面交加类欧的做法。

### Part 1

这题的半平面交比较特化，当然正常的半平面交也是可过的，想学习的左转 [P4196](https://www.luogu.com.cn/problem/P4196) 题解区，本文只叙述特化解法。

可以发现本体给出的都是形如 $y=-\frac{A}{B}x+\frac{C}{B}$ 的直线，因为 $A,B,C$ 都是非负整数，所以所有直线的斜率都小于零，也即最后的解的范围是一个右上凸壳。

那我们就可以把每条直线按极角排序（或者斜率均可，本题没有区别），维护一个单调栈，每次加入一个新直线去看和上一条直线的交点的横坐标以及上一条直线和上上条直线交点的横坐标的大小关系，最后栈里的元素即是构成右上凸壳的直线。

### Part 2

关于类欧的部分，我们先来看一个简化版：

> 给定一个方程：$Ax+By\le C$，求解的数量。

我们转化一下答案有：

$$
\sum_{x=0}^{\lfloor\frac{C}{A}\rfloor}\left\lfloor\frac{-Ax+C}{B}\right\rfloor
$$

不妨先考虑一个更加形式化的，求：$\sum_{i=0}^{n}\left\lfloor\frac{Ai+B}{C}\right\rfloor$。

我们使用大力分讨求解，不妨设 $f(A,B,C,n)=\sum_{i=0}^{n}\left\lfloor\frac{Ai+B}{C}\right\rfloor$。

当 $A=0$ 时，有：

$$
f(A,B,C,n)=(n+1)\times \left\lfloor\frac{B}{C}\right\rfloor
$$

当 $A\ge C$ 或者 $B\ge C$ 时，有：

$$
\begin{aligned}
f(A,B,C,n)&=\sum_{i=0}^n\left\lfloor\frac{(A\bmod C)i+B\bmod C}{C}\right\rfloor+i\times\left\lfloor\frac{A}{C}\right\rfloor+\left\lfloor\frac{B}{C}\right\rfloor\\
&=f(A\bmod C,B\bmod C,C,n)+\frac{n(n+1)}{2}\times\left\lfloor\frac{A}{C}\right\rfloor+(n+1)\times\left\lfloor\frac{B}{C}\right\rfloor
\end{aligned}
$$

当 $A<B$ 且 $B<C$ 时，我们先设 $m=\left\lfloor\frac{An+B}{C}\right\rfloor$，有：

$$
\begin{aligned}
f(A,B,C,n)&=\sum_{i=0}^n\sum_{j=1}^m[j\le\left\lfloor\frac{Ai+B}{C}\right\rfloor]\\
&=\sum_{i=0}^n\sum_{j=1}^m[Cj\le Ai+B]\\
&=\sum_{j=1}^m\sum_{i=0}^n[Cj<Ai+B+1]\\
&=\sum_{j=1}^mn-\left\lfloor\frac{Cj-B-1}{A}\right\rfloor\\
&=\sum_{j=0}^{m-1}n-\left\lfloor\frac{Cj+C-B-1}{A}\right\rfloor\\
&=mn-f(C,C-B-1,A,m-1)
\end{aligned}
$$

另外还有负数的情况，直接套用上述第二个分讨转成正数即可。

回到本题，不难发现实际求的就是 $f(-A,C-1,B,r)-f(-A,C-1,B,l)$，直接套用上述式子即可。

$l,r$ 就是右上凸壳上线段左右端点的横坐标向下取整的取值。

### Part 3

最后我们简单说一下复杂度，不关心的同学可以直接跳过看代码了。

关于类欧的部分，不难发现 $A\ge C$ 或者 $B\ge C$ 的时候可以在 $O(1)$ 时间内变换至 $A<C$ 且 $B<C$，所以我们只对于后一种情况讨论。

而对于 $A<C$ 且 $B<C$ 情况的式子不难发现每次会有 $A,C$ 互换位置的操作，又因为 $A<C$，所以会有一个 $(A,C)\to (C,A)\to (C\bmod A,A)$ 的转移，不难发现这就是辗转相除，所以复杂度 $O(\log n)$。

关于半平面交的部分，显然有线段数量是 $O(n)$ 的结论，证明的话可以使用反证法，不再叙述。

综上我们得到了一个总复杂度 $O(n\log n)$ 的算法。

## Code

我这里直接套的半平面交板子，本题稍微卡点精度，不想被卡的可以手写分数类。

```cpp
#include <algorithm>
#include <iostream>
#include <cstring>
#include <cstdio>
#include <cmath>

#define LL long long
#define N 200005

using namespace std;
int n,a[N],b[N],c[N];

namespace CG {
    const long double eps=1e-11;

    template<typename T> struct Poi {
        T x,y;

        Poi(T _x=0,T _y=0) { x=_x,y=_y; }
        bool operator==(const Poi tmp) const { return x==tmp.x and y==tmp.y; }
        Poi operator+(const Poi tmp) const { return Poi(x+tmp.x,y+tmp.y); }
        Poi operator-(const Poi tmp) const { return Poi(x-tmp.x,y-tmp.y); }
    };

    template<typename T> T Cro(Poi<T> x,Poi<T> y) { return x.x*y.y-x.y*y.x; }

    template<typename T> struct Edge {
        Poi<T> x,y; int id;

        Edge(Poi<T> _x,Poi<T> _y,int _id=0) { x=_x,y=_y,id=_id; }
        Edge(T x1=0,T y1=0,T x2=0,T y2=0,int _id=0) { x=Poi<T>(x1,y1),y=Poi<T>(x2,y2),id=_id; }
        bool operator==(const Edge tmp) const {
            return fabsl(atan2(y.y-x.y,y.x-x.x)-atan2(tmp.y.y-tmp.x.y,tmp.y.x-tmp.x.x))<=eps;
        }
        bool operator<(const Edge tmp) const {
            return fabsl(atan2(y.y-x.y,y.x-x.x)-atan2(tmp.y.y-tmp.x.y,tmp.y.x-tmp.x.x))>eps
                ?atan2(y.y-x.y,y.x-x.x)<atan2(tmp.y.y-tmp.x.y,tmp.y.x-tmp.x.x)
                :Cro(x-tmp.x,y-tmp.x)<0;
        }
    };

    template<typename T> Poi<T> Cro(Edge<T> a,Edge<T> b) {
        T tmp1=Cro(b.y-a.x,a.y-a.x),tmp2=Cro(b.x-a.x,a.y-a.x);
        return Poi<T>((tmp1*b.x.x-tmp2*b.y.x)/(tmp1-tmp2),(tmp1*b.x.y-tmp2*b.y.y)/(tmp1-tmp2));
    }

    /**
     * 默认是左半平面
     */
    template<typename T>
    int getHPI(int n,Edge<T> *e,Poi<T> *ans1,Edge<T> *ans2) {
        sort(e+1,e+n+1); int tot=unique(e+1,e+n+1)-e-1;
        int head,tail,*q=new int[n+1];
        head=1,tail=2,q[1]=1,q[2]=2;
        for (int i=3;i<=tot;i++) {
            while (head<tail and Cro(e[i].x-Cro(e[q[tail]],e[q[tail-1]]),e[i].y-Cro(e[q[tail]],e[q[tail-1]]))<0) --tail;
            while (head<tail and Cro(e[i].x-Cro(e[q[head]],e[q[head+1]]),e[i].y-Cro(e[q[head]],e[q[head+1]]))<0) ++head;
            q[++tail]=i;
        }
        while (head<tail and Cro(e[head].x-Cro(e[q[tail]],e[q[tail-1]]),e[head].y-Cro(e[q[tail]],e[q[tail-1]]))<0) --tail;
        while (head<tail and Cro(e[tail].x-Cro(e[q[head]],e[q[head+1]]),e[tail].y-Cro(e[q[head]],e[q[head+1]]))<0) ++head;
        int cnt=0;
        ans1[++cnt]=Cro(e[q[tail]],e[q[head]]);
        for (int i=head+1;i<=tail;i++) 
            ans1[++cnt]=Cro(e[q[i]],e[q[i-1]]);
        for (int i=1;i<=cnt;i++) ans2[i]=Edge<T>(ans1[i],ans1[i%cnt+1],e[q[i+head-1]].id);
        delete[] q;
        return cnt;
    }
} using CG::Poi,CG::Edge;

Edge<long double> in[N],ans2[N];
Poi<long double> ans1[N];

LL f(LL a,LL b,LL c,LL n) {
    if (!n) return b/c;
    else if (a==0) return (n+1)*(b/c);
    else if (c<0) return f(-a,-b,-c,n);
	else if (a>=c or b>=c) return (n*(n+1)/2)*(a/c)+(n+1)*(b/c)+f(a%c,b%c,c,n);
	else if (a<0 or b<0) return (n*(n+1)/2)*(a/c-1)+(n+1)*(b/c-1)+f(a%c+c,b%c+c,c,n);
	else return n*((a*n+b)/c)-f(c,c-b-1,a,((a*n+b)/c)-1);
}

signed main() {
    int T; scanf("%d",&T);
    while (T--) {
        scanf("%d",&n);
        bool flag=0;
        for (int i=1;i<=n;i++) {
            scanf("%d%d%d",a+i,b+i,c+i); --c[i];
            long double x=(long double)1.0*c[i]/a[i],y=(long double)1.0*c[i]/b[i];
            in[i]=Edge<long double>(x,0,0,y,i);
            flag|=(x<=0 and y<=0);
        }
        if (flag) { printf("0\n"); continue; }
        in[++n]=Edge<long double>(0,1,0,0),in[++n]=Edge<long double>(0,0,1,0);
        int m=CG::getHPI(n,in,ans1,ans2);
        if (m<=2) { printf("0\n"); continue; }
        LL ans=0;
        for (int i=1;i<=m;i++)
            if (ans2[i].id) {
                int id=ans2[i].id;
                ans+=f(-a[id],c[id],b[id],max(floorl(ans2[i].x.x),(long double)0.0))
                    -f(-a[id],c[id],b[id],max(floorl(ans2[i].y.x),(long double)0.0));
            }
        printf("%lld\n",ans);
    }
    return 0;
}
```

---

## 作者：YipChip (赞：5)

这是一道类欧题，如果你想知道更多有关类欧的内容可以去看看我的博客“[类欧几里得算法](https://www.luogu.com.cn/article/6soj7ys3)”。

### part 1

对于常见的类欧形式：

$$f(a,b,c,n)=\sum_{i=0}^n\bigg\lfloor\frac{ai+b}{c}\bigg\rfloor$$

$\text{(I)}$ 当 $a < c$ 且 $b < c$ 时。

先化简 $f(a,b,c,n)$。

$$\begin{aligned}

f(a,b,c,n)&=\sum_{i=0}^n\bigg\lfloor\frac{ai+b}{c}\bigg\rfloor\\

&=\sum_{i=0}^n\sum_{j=1}^{\lfloor\frac{ai+b}{c}\rfloor}\bigg[j\le\bigg\lfloor\frac{ai+b}{c}\bigg\rfloor\bigg]\\

&=\sum_{i=0}^n\sum_{j=1}^{\lfloor\frac{an+b}{c}\rfloor}\bigg[j\le\bigg\lfloor\frac{ai+b}{c}\bigg\rfloor\bigg]\\

&=\sum_{i=0}^n\sum_{j=0}^{\lfloor\frac{an+b}{c}\rfloor-1}\bigg[j+1\le\bigg\lfloor\frac{ai+b}{c}\bigg\rfloor\bigg]\\

&=\sum_{i=0}^n\sum_{j=0}^{\lfloor\frac{an+b}{c}\rfloor-1}\bigg[cj+c\le{ai+b}\bigg]\\

&=\sum_{i=0}^n\sum_{j=0}^{\lfloor\frac{an+b}{c}\rfloor-1}\bigg[cj+c-b\le{ai}\bigg]\\

&=\sum_{i=0}^n\sum_{j=0}^{\lfloor\frac{an+b}{c}\rfloor-1}\bigg[cj+c-b-1<{ai}\bigg]\\

&=\sum_{i=0}^n\sum_{j=0}^{\lfloor\frac{an+b}{c}\rfloor-1}\bigg[\bigg\lfloor\frac{cj+c-b-1}{a}\bigg\rfloor<i\bigg]\\

&=\sum_{j=0}^{\lfloor\frac{an+b}{c}\rfloor-1}\sum_{i=0}^n\bigg[\bigg\lfloor\frac{cj+c-b-1}{a}\bigg\rfloor<i\bigg]\\

&=\sum_{j=0}^{\lfloor\frac{an+b}{c}\rfloor-1}\sum_{i=\lfloor\frac{cj+c-b-1}{a}\rfloor+1}^n1\\

&=\sum_{j=0}^{\lfloor\frac{an+b}{c}\rfloor-1}\bigg(n-\bigg\lfloor\frac{cj+c-b-1}{a}\bigg\rfloor\bigg)\\

&=n\bigg\lfloor\frac{an+b}{c}\bigg\rfloor-\sum_{j=0}^{\lfloor\frac{an+b}{c}\rfloor-1}\bigg\lfloor\frac{cj+c-b-1}{a}\bigg\rfloor\\

&=n\bigg\lfloor\frac{an+b}{c}\bigg\rfloor-f(c,c+b-1,a,\bigg\lfloor\frac{an+b}{c}\bigg\rfloor-1)

\end{aligned}$$

令 $m=\lfloor\frac{an+b}{c}\rfloor$，则有：

$$f(a,b,c,n) = nm-f(c,c-b-1,a,m-1)$$

$\text{(II)}$ 当 $a \ge c$ 或 $b \ge c$ 时，我们将式子完全展开，令 $a'=a \bmod c$，$b'=b \bmod c$。

$$\begin{aligned}

f(a,b,c,n) &= \sum_{i=0}^n\bigg\lfloor\frac{ai+b}{c}\bigg\rfloor\\

&=\sum_{i=0}^n\bigg(\bigg\lfloor\frac{a'i+b'}{c}\bigg\rfloor+i\bigg\lfloor\frac{a}{c}\bigg\rfloor+\bigg\lfloor\frac{b}{c}\bigg\rfloor\bigg)\\

&=f(a',b',c,n)+\frac{n(n+1)}{2}\bigg\lfloor\frac{a}{c}\bigg\rfloor+(n+1)\bigg\lfloor\frac{b}{c}\bigg\rfloor

\end{aligned}
$$

### part 2

首先我们来考虑对于单元 $ax + by < c$ 如何变换。

与[P5171 Earthquake](https://www.luogu.com.cn/problem/P5171)完全类似。

不过原题是给定 $a,\,b,\,c$，求满足方程 $ax+by \leqslant c$ 的非负整数解个数。

本题是给定 $a,\,b,\,c$，求满足方程 $ax+by<c$ 的正整数解个数。

同样的移项后可以得到：

$$0<x<\frac{c - by}{a},\,0<y<\frac{c - ax}{b}$$

而 $x,y$ 有限制为 $0<x\leqslant\lfloor\frac{c-b-1}{a}\rfloor,\,0<y\leqslant\lfloor\frac{c-a-1}{b}\rfloor$。

$$
\begin{aligned}
&\sum_{i=1}^{\lfloor\frac{c-b-1}{a}\rfloor}\sum_{j=1}^{\lfloor\frac{c-a-1}{b}\rfloor}\bigg[j\leqslant\bigg\lfloor\frac{c-ai-1}{b}\bigg\rfloor\bigg] \\

&=\sum_{i=1}^{\lfloor\frac{c-b-1}{a}\rfloor}\bigg\lfloor\frac{c-ai-1}{b}\bigg\rfloor

\end{aligned}
$$

为了使 $i$ 前的系数大于零，我们不妨考虑整体 $+i-i$。

$$
\begin{aligned}

&\sum_{i=1}^{\lfloor\frac{c-b-1}{a}\rfloor}\bigg\lfloor\frac{c-ai-1}{b}+i-i\bigg\rfloor \\

&=\sum_{i=1}^{\lfloor\frac{c-b-1}{a}\rfloor}\bigg\lfloor\frac{(b-a)i+c-1}{b}\bigg\rfloor-\sum_{i=1}^{\lfloor\frac{c-b-1}{a}\rfloor}i \\

&=\sum_{i=1}^{\lfloor\frac{c-b-1}{a}\rfloor}\bigg\lfloor\frac{(b-a)i+c-1}{b}\bigg\rfloor-\frac{\lfloor\frac{c-b-1}{a}\rfloor(\lfloor\frac{c-b-1}{a}\rfloor+1)}{2}

\end{aligned}
$$

对于 $\sum\limits_{i=1}^{\lfloor\frac{c-b-1}{a}\rfloor}\lfloor\frac{(b-a)i+c-1}{b}\rfloor$ 可以类欧快速求解 $f(b-a,\,c-1,\,b,\,\lfloor\frac{c-b-1}{a}\rfloor)-f(b-a,\,c-1,\,b,\,0)$，为了让 $b - a$ 不为负，由于 $a,\,b$ 等价，考虑 $b - a < 0$ 时 `swap(a, b)` 即可。

### part 3

以上是对于唯一 $a,\,b,\,c$ 的单次求解，那么多元呢？

我们不妨考虑对于每条直线 $A_ix+B_iy=C_i$ 本质上对空间进行了一次切割，我们想要找到的是所有直线在原点一侧的半平面交。

![Atcoder](https://img.atcoder.jp/abc372/90d90b12302e979d678e28cc1c579ecb.png)

引用ATCoder上的一张图片，我们实际上想要找到的是左下角的点集，如果我们按照斜率排序，可以找到相邻两条直线的交点 $[x1,\,x2,\,...,\,x_k]$，我们对于 $[x_j,\,x_{j+1})$ 必定属于一条直线 $l$，若 $a,\,b,\,c$ 为直线 $l$ 的三个参数，记 $g(x) = \sum\limits_{i=1}^{x}\lfloor\frac{-ai+c-1}{b}\rfloor$，那么对于 $[x_j, x_{j+1})$ 区间上直线 $l$ 下正整数点的个数为 $g(x_{j+1}-1) - g(x_j-1)$。

这样我们的问题就转变为了找到这样 $k$ 个点。

首先我们的点的横坐标有上下界 $[1,\min\{\lceil\frac{c_1}{a_1}\rceil,\,...,\,\lceil\frac{c_i}{a_i}\rceil,\,...,\,\lceil\frac{c_n}{a_n}\rceil\}]$。

维护一个单调栈使得栈内点横坐标单调递增，如果存在两条相邻斜率的直线交点的横坐标较小，那必然可以把大的舍去，因为不需要进行计算了。

这样这个问题就变成了对于交点集 $[x1,\,x2,\,...,\,x_k]$，求所有 $[x_j, x_{j+1})$ 区间上直线 $l$ 下正整数点的个数 $g(x_{j+1}-1) - g(x_j-1)$ 之和。

不过需要注意的是，我们的类欧的参数需要为正，此时的 $a,\,b$ 就不等价了，这如何做到呢？

事实上有：

$$
\begin{aligned}

&\sum_{i=1}^{\lfloor\frac{c-b-1}{a}\rfloor}\bigg\lfloor\frac{c-ai-1}{b}\bigg\rfloor \\

&=\sum_{i=1}^{\lfloor\frac{c-b-1}{a}\rfloor}\bigg\lfloor\frac{c-ai-1}{b}+ki-ki\bigg\rfloor \\

&=\sum_{i=1}^{\lfloor\frac{c-b-1}{a}\rfloor}\bigg\lfloor\frac{(kb-a)i+c-1}{b}\bigg\rfloor-\frac{k\lfloor\frac{c-b-1}{a}\rfloor(\lfloor\frac{c-b-1}{a}\rfloor+1)}{2}

\end{aligned}
$$

这样的 $k$ 是很好找的，只需要 $k = \lceil\frac{a}{b}\rceil$ 即可。

参考代码

```cpp
#include<bits/stdc++.h>
using namespace std;
typedef long long ll;
const int N = 2e5 + 10;
const ll INF = 1e18;
struct Node
{
	ll a, b, c;
}line[N];
ll x[N], q[N];
Node stk[N];

bool cmp(Node x, Node y)
{
	if (x.a * y.b == y.a * x.b) return x.c * y.a < y.c * x.a;
	return x.a * y.b < y.a * x.b;
}

ll calc(ll a, ll b, ll c, ll n)
{
	if (n < 0) return 0;
	if (!a) return b / c * (n + 1);
	if (a < c && b < c)
	{
		ll m = (a * n + b) / c;
		if (!m) return 0;
		return n * m - calc(c, c - b - 1, a, m - 1);
	}
	return calc(a % c, b % c, c, n) + (n + 1) * n / 2 * (a / c) + (n + 1) * (b / c);
}

ll get(Node line, ll l, ll r, ll xmin)
{
	l = min(xmin, max(1ll, l)) - 1, r = min(xmin, max(1ll, r)) - 1;
	ll a = line.a, b = line.b, c = line.c;
	ll k = (a + b - 1) / b;
	return calc(k * b - a, c - 1, b, r) - k * r * (r + 1) / 2 - calc(k * b - a, c - 1, b, l) + k * l * (l + 1) / 2;
}

ll inter(Node l1, Node l2)
{
	return (l2.c * l1.b - l1.c * l2.b - 1) / (l1.b * l2.a - l2.b * l1.a) + 1;
}

void solve()
{
	ll n, cntx = 0, cnt = 0, ans = 0, xmin = 1e18;
	cin >> n;
	for (int i = 1; i <= n; i ++ ) cin >> line[i].a >> line[i].b >> line[i].c;
	sort(line + 1, line + n + 1, cmp);
	for (int i = 1; i <= n; i ++ )
	{
		ll a = line[i].a, b = line[i].b, c = line[i].c;
		if (cnt && stk[cnt].a * b == stk[cnt].b * a) continue;
		while (cnt >= 2 && inter(stk[cnt], line[i]) <= x[cntx]) cnt -- , cntx -- ;
		xmin = min((c + a - 1) / a, xmin);
		stk[ ++ cnt] = line[i];
		if (!cntx) x[ ++ cntx] = -INF;
		else x[ ++ cntx] = inter(stk[cnt - 1], line[i]);
	}
	x[ ++ cntx] = INF;
	for (int i = 1; i <= cnt; i ++ ) ans += get(stk[i], x[i], x[i + 1], xmin);
	cout << ans << endl;
}

int main()
{
	int T;
	cin >> T;
	while (T -- ) solve();
	return 0;
}
```

---

## 作者：anthonyaaabc (赞：3)

这种多种限制的题可以先考虑简化问题，将简化后的问题解决后再解决加强后的问题。
本题中，简化后的问题就是一组限制怎么解决，简单的观察后可以将式子转化成 $ \sum\limits_{i=0}^{n}\lfloor \frac{ai+b}{c} \rfloor$。注意这里的 $a$，$b$，$c$，$n$，不是题目中的限制，只是说明一下可以转换成这样的形式。这个形式就是类欧几里得算法的一般形式，具体计算方法可以去看模板题。

问题的关键就变成了如何解决有多组限制的情况。容易发现不等式的限制当 $y$ 是确定的时候，对 $x$ 的限制有效的只有其中一组限制，而显然是取限制最紧的限制。这在启示我们可以维护最紧的性质，这样做法就变得和只有一组限制一模一样了。不妨考虑将限制进行变形。 

$ A_i\times\ x+B_i\times\ y\ <\ C_i $ 变形成
$ x + \frac {B_i}{A_i}\times\ y\ <\ \frac{C_i}{A_i} $ 。

转化后限制显然没有变化，于是计算就变成了类似直线取 $\min$ 了。套路的排序后使用二分单调栈维护这些类似直线就行，每次只需要考虑什么时候一条直线会比另一条直线优。直线交点就是最紧的限制变成另一条线段的时候，分数不用真的算出来，但是比较的时候最好使用交叉相乘保证精度，本质就是维护直线的凸包。

最后就变成每组限制只会限制一个区间，直接差分区间当单组限制求就行了。

我的赛时代码：

```cpp
#include<bits/stdc++.h>
using namespace std;
const __int128 N=200005;
__int128 _;
__int128 calc(__int128 a,__int128 b,__int128 c,__int128 N)
{
    if(a==0)
    {
        return (N+1)*(b/c);
    }
    else if(a>=c||b>=c)
    {
        return (N*(N+1)/2)*(a/c)+(N+1)*(b/c)+calc(a%c,b%c,c,N);

    }
    else 
    {
        const __int128 M=((a*N+b)/c);
        return N*M-calc(c,c-b-1,a,M-1);
    }
}
struct node
{
    __int128 a,b,c;
}a[N];
__int128 mx;

bool cmp(node a,node b)
{
    return (a.c*b.a)<(b.c*a.a);
}
__int128 num(node x,__int128 tp)
{
    return (x.c-tp*x.b)/x.a;
}
__int128 get(node a,__int128 x)
{
    __int128 tot=min(x,a.c/a.b);
    if(tot<=0)return 0;
    return calc(a.b,a.c-a.b*tot,a.a,tot-1);
}
__int128 solve(node a,__int128 l,__int128 r)
{
    return get(a,r)-get(a,l-1);
}
__int128 find(node a,node b)
{
    __int128 l=1,r=mx,as=-1;
    while(l<=r)
    {
        __int128 mid=(l+r)>>1;
        if((b.c-mid*b.b)*a.a<(a.c-mid*a.b)*b.a)
        {
            as=mid;
            r=mid-1;
        }
        else l=mid+1;
    }

    return as;
}
__int128 read()
{
    long long x;
    cin>>x;
    return x;
}
int main()
{
    ios::sync_with_stdio(false);
    cin.tie(0);
    cout.tie(0);
    _=read();
    while(_--)
    {
        __int128 n;
        n=read();
        mx=1e9+7;
        bool tg=0;
        for(__int128 i=1;i<=n;i++)
        {

            a[i].a=read();
            a[i].b=read();
            a[i].c=read();
            a[i].c--;
            if(a[i].c<a[i].b+a[i].a)tg=1;
            mx=min(mx,(a[i].c-a[i].a)/a[i].b);
        }
        if(tg)
        {
            cout<<0<<'\n';
            continue;
        }
        sort(a+1,a+1+n,cmp);
        vector<pair<__int128,__int128> >ss;
        for(__int128 i=1;i<=n;i++)
        {

            if(ss.empty())ss.push_back({i,1});
            else
            {
                if(find(a[ss.back().first],a[i])==-1)
                {
                    continue;
                }
                
                while(!ss.empty()&&find(a[ss.back().first],a[i])<=ss.back().second)
                {
                    ss.pop_back();
                }
                if(ss.empty())ss.push_back({i,1});
                else ss.push_back({i,find(a[ss.back().first],a[i])});
            }
        }
        __int128 ans=0;
        for(__int128 i=(__int128)(ss.size()-1);i>=0;i--)
        {
            if(ss[i].second<=mx)
            {
                __int128 l=ss[i].second,r=mx;
                ans+=solve(a[ss[i].first],l,r);

                mx=ss[i].second-1;
            }
        }

        cout<<(long long)(ans)<<'\n';
    }
}
```

---

## 作者：MYLHF (赞：2)

发现 $a_i\times x+b_i\times y<c$ 和直线的一般式很像，移项得 $y<\frac{c-a_i\times x}{b_i}$。

其实就是直线 $y=\frac{c-a_i\times x}{b_i}$ 下方的整点。

所以题目求的 $\big| \{ ~(x,y)~|~y< \frac{c-a_i\times x}{b_i},i∈[1,n] ~\} \big|$。

注意对于一条线段，$\min \{ \frac{c-a_i\times x}{b_i},i∈[1,n] ~\}=\frac{c-a_j\times x}{b_j}$ 的取值是一段连续的区间。所以我们考虑直接求出这段区间，再使用类欧几里得算法。

我们先把所有线段上李超树。枚举一个 $x=l$，求出当前取到的最小的 $y$ 选的是那一条线段。然后二分出右端点 $r$，计算答案，再把 $l$ 更新为 $r+1$。

贴个代码（使用了 `atcoder/math` 库代替类欧几里得算法）：

```cpp
#include<atcoder/math> 
#include<bits/stdc++.h>
#define int long long
#define tpe long double
#define de(x) cout<<#x<<": "<<x<<endl
#define rep(i,a,b) for(int i(a);i<=(b);++i)
#define REP(i,a,b) for(int i(a);i>=(b);--i)
using namespace std;

const int N=1e6 +7,M=1e7,INF=1e12;
int n,m,a[N],b[N],c[N];

struct Tree{
	#define PII pair<tpe,int>
	int tot,idx,rt;
	struct Line{ tpe k,b; }a[M],Const_Line;
	struct Seg{
		#define ls tr[u].lson
		#define rs tr[u].rson
		#define mid ((l+r)>>1)
		int id, lson,rson;
	}tr[M],Const_Seg;
	
	inline tpe func(int id,tpe x) { return a[id].k*x+a[id].b; }
	inline int cmp(int i,int j,tpe x) { return func(i,x)<func(j,x); }
	
	void add(int &u,int l,int r,int id)
	{
		if(!u) return tr[(u=++tot)].id=id,void();
		if(l==r) return cmp(id,tr[u].id,l) ? tr[u].id=id : 0,void();
		int &p=tr[u].id;
		cmp(id,p,mid) ? swap(id,p) : void();
		cmp(id,p,l) ? add(ls,l,mid,id) : add(rs,mid+1,r,id);
	} void insert(tpe k,tpe b) { a[++idx]={k,b},add(rt,0,INF,idx); }
	
	PII ask(int u,int l,int r,tpe x)
	{
		if(!u) return {1e18,0};
		return min({func(tr[u].id,x),tr[u].id}, x<=mid ? ask(ls,l,mid,x) : ask(rs,mid+1,r,x) );
	} PII ask(tpe x) { return ask(rt,0,INF,x); }
	
	void clear() { rep(i,1,tot) tr[i]=Const_Seg; rep(i,1,idx) a[i]=Const_Line; tot=idx=rt=0; }
    #undef mid
    void debug()
    {
    	return ;
	}
}q;

signed main()
{
	ios_base::sync_with_stdio(0),cin.tie(0),cout.tie(0);
	
	int T; cin>>T;
	while(T--)
	{
		cin>>n;
		rep(i,1,n)
		{
			cin>>a[i]>>b[i]>>c[i];
			tpe k=-a[i]*1.000/b[i], b=c[i]*1.000/::b[i];
			q.insert(k,b);
		}
		
		int l=1,ret=0;
		while(l<=INF)
		{
			int p=q.ask(l).second;
			if(a[p]*l>=c[p]) break;
			int ll=l,r=min(INF,(c[p]-1)/a[p]);
			while(ll<r)
			{
				int mid((ll+r+1)>>1);
				if(q.ask(mid).second==p) ll=mid;
				else r=mid-1;
			} 
			
			int A=r-l+1, B=b[p], C=a[p], D=c[p]-1-a[p]*r;
			ret+=atcoder::floor_sum(A,B,C,D), l=r+1;
		}
		
		cout<<ret<<endl;
		
		q.clear();
	}
	
	return 0;
}

```

---

## 作者：Hell0_W0rld (赞：1)

## [ABC372G] Ax + By < C
题目大意很简洁：求满足 $\forall i\in [1,n],A_ix+B_iy<C$ 且 $x,y\in \mathbb{Z}^+$ 的数对 $(x,y)$ 数量。

注意到整数的离散性，转化成 $Ax+By\leq C-1$。

发现这是一堆半平面的形式，而且这些半平面都完全包括了第三象限。所以可以直接写类似于斜优的凸壳维护，不必要动用半平面交。

对于一个半平面 $l:Ax+By=C$，不妨设其在区间 $[x_0,x_1]$ 范围内的纵坐标小于其他所有直线，则他对答案的贡献即为 $\sum_{i=x_0}^{x_1} \lfloor\frac{C-Ai}{B} \rfloor$，是一个类欧的形式，考虑 `atcoder::floor_sum`。（ACL 提供的类欧模板支持类欧系数为负，详见[这里](https://atcoder.github.io/ac-library/production/document_en/math.html)）

因为 $x=0$ 是取不到的，所以考虑让在凸壳上相邻两直线的交点归属于右边直线的计算。

注意实现上要用 __int128 和分数结构体。

```cpp
#include<bits/stdc++.h>
#include<atcoder/math>
#define ll long long
#define lll __int128_t
#define ull unsigned long long
#define ld long double
#define rep(i,l,r) for(register ll i=(l);i<=(r);++i)
#define Rep(i,l,r) for(register ll i=(r);i>=(l);--i)
#define all(x) x.begin(),x.end()
#define Set(x,y) memset(x,y,sizeof(x))
#define Cpy(x,y) memcpy(x,y,sizeof(x))
#define cll const long long
using namespace std;
template<class T>
void death(T s){cout<<s<<endl;exit(0);}
cll N=200009;
struct frac{
	lll u,d;
	frac(lll _u=0,lll _d=1){u=_u/__gcd(_u,_d),d=_d/__gcd(_u,_d); if(d<0)d=-d,u=-u; assert(d!=0); }
	bool operator<(const frac&x)const{return u*x.d<x.u*d;}
	bool operator>(const frac&x)const{return u*x.d>x.u*d;}
	bool operator==(const frac&x)const{return u==x.u&&d==x.d;}
	bool operator!=(const frac&x)const{return u!=x.u||d!=x.d;}
	frac operator+(const frac&x)const{return frac(u*x.d+d*x.u,d*x.d);}
	frac operator-(const frac&x)const{return frac(u*x.d-d*x.u,d*x.d);}
	frac operator/(const frac&x)const{assert(x.u!=0); return frac(u*x.d,d*x.u);}
};
lll flor(frac x){return x.u/x.d;}
lll cei(frac x){return (x.u-1)/x.d+1;}
bool integ(frac x){return x.d==1;}
struct Line{
	frac b,k; ll id;
	bool operator<(const Line&x)const{return k>x.k || k==x.k&&b<x.b;}
    bool operator==(const Line&x) const { return k==x.k; }
	#define b(u) lines[u].b 
	#define k(u) lines[u].k
}lines[N];
struct HalfPlane{ll a,b,c;} p[N];//ax+by<=c
frac X(ll u,ll v){
	return (b(v)-b(u))/(k(u)-k(v));
} 
ll n,q[N],tno;
void clr(){
	rep(i,0,tno){
		lines[i]=(Line){frac(),frac(),0};
		p[i]=(HalfPlane){0,0,0};
		q[i]=0;
	}
	n=tno=0;
}
void solve(){
	cin>>n; tno=n;
	rep(i,1,n){
		ll a,b,c;
		cin>>a>>b>>c;
		c--;
		lines[i]=(Line){frac(c,b),frac(-a,b),i};
		p[i]=(HalfPlane){a,b,c};
    }
	sort(lines+1,lines+1+n);
    n=unique(lines+1,lines+1+n)-lines-1;
	ll l=1,r=1;
	rep(i,1,n){
		while(r-l>=2&&(X(i,q[r-1])<X(q[r-1],q[r-2])||X(i,q[r-1])==X(q[r-1],q[r-2]))) r--;
		q[r++]=i;
	}
	rep(i,1,r-1)lines[i]=lines[q[i]];
	n=r-1;
	ll ans=0;
	rep(l,1,n){
		ll id=lines[l].id;
		lll x0=1,x1=flor(X(l,0));
		if(l!=1){
			frac a=X(l,l-1);
			x0=flor(a)+1;
		}
		if(l!=n){
			frac a=X(l,l+1);
			x1=flor(a);
		}
		if(x0<1)x0=1;
		x1=min(x1,flor(X(l,0)));
		if(x1<x0)continue;
		ll a=p[id].a,b=p[id].b,c=p[id].c;
		ans+=(atcoder::floor_sum((ll)x1+1,b,-a,c)-atcoder::floor_sum((ll)x0,b,-a,c));
	}
	cout<<ans<<endl;
}
int main(){
	ll T;
	cin>>T;
	while(T--){
		clr();
		solve();
	}
	return 0;
}
```

---

