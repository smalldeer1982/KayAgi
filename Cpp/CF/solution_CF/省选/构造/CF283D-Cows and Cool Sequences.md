# Cows and Cool Sequences

## 题目描述

Bessie and the cows have recently been playing with "cool" sequences and are trying to construct some. Unfortunately they are bad at arithmetic, so they need your help!

A pair $ (x,y) $ of positive integers is "cool" if $ x $ can be expressed as the sum of $ y $ consecutive integers (not necessarily positive). A sequence $ (a_{1},a_{2},...,a_{n}) $ is "cool" if the pairs $ (a_{1},a_{2}),(a_{2},a_{3}),...,(a_{n-1},a_{n}) $ are all cool.

The cows have a sequence of $ n $ positive integers, $ a_{1},a_{2},...,a_{n} $ . In one move, they may replace some $ a_{i} $ with any other positive integer (there are no other limits on the new value of $ a_{i} $ ). Determine the smallest number of moves needed to make the resulting sequence cool.

## 说明/提示

In the first sample, the sequence is already cool, so we don't need to change any elements. In the second sample, we can change $ a_{2} $ to 5 and $ a_{3} $ to 10 to make (20, 5, 10, 4) which is cool. This changes 2 elements.

## 样例 #1

### 输入

```
3
6 4 1
```

### 输出

```
0
```

## 样例 #2

### 输入

```
4
20 6 3 4
```

### 输出

```
2
```

# 题解

## 作者：newbiewzs (赞：6)

我们首先考虑对于 $(x,y)$ 它们合法的条件是什么

设 $t$ 为连续数的开头，那么我们就可以写出 $x=\frac{y(y-1)}{2}+ty$ 

移项，得到 $\frac{2x-y^2}{y}=2t-1$ ，即我们要求 $\frac{2x}{y}-y$ 为 **奇数** 

考虑将每个数内的 2 的次幂分离出来，设 $v(x)$ 表示 $x$ 中 2的指数，$p(x)$ 为 $x$ 中最大的奇数因子，即每个 $x$ 都可以被写成 $2^{v(x)}\cdot p(x)$ 

那么我们就可以将原式写成 $2^{v(x)-v(y)+1}\cdot \frac{p(x)}{p(y)} -2^{v(y)}\cdot p(y)$   ，不难发现我们首先要满足的条件就是 $p(y)|p(x)$  ，剩下的限制分类讨论：

1. $y$ 为奇数，即 $v(y)=0$ ，那么我们要求前面一项为偶数，所以 $v(x)-v(y)+1\geq 0$ ，得到 $v(x)\geq -1$ ，即 $v(x)$ 任取
2. $y$ 为偶数，那么要求前面一项为奇数，所以 $v(x)-v(y)+1=0$ ，得到 $v(y)=v(x)+1$ 

综上所述， $(x,y)$ 合法当且仅当 $p(y)|p(x)$ 并且 $v(y)=0$ 与 $v(y)=v(x)+1$ 中有一个条件被满足

那么我们设 $f(i)$ 表示以 $i$ 为结尾且 $[1,i]$ 中的数都变好的最小修改次数，每次转移枚举一个 $j$ ，我们就需要 $\text{check}$ 一下 $[j,i]$ 中，能否不修改 $a_j,a_i$ 且修改 $[j+1,i-1]$ 中全部的数得到合法序列，我们根据前面得到的性质可以推出该区间首先满足 $p(a_i)|p(a_j)$，
其次还需要满足 $v(a_i)\leq j-i+1$ 或 $v(a_i)-v(a_j)=i-j$ ，这个推导就很容易了。



---

## 作者：SFlyer (赞：3)

口胡的。这里 $x,y$ 是下标。

首先充要条件是 $x=\frac{y(y-1)}{2}+ky$，$k$ 是整数。反解 $k$，解出 $2k=\frac{2x-y^2+y}{y}$，即 $\frac{2x}{y}-y+1$ 是偶数，即 $y\mid 2x$，$\frac{2x}{y}$ 和 $y$ 奇偶性不同。

这个奇偶性不同启发我们，把数表示成 $2^{a(x)}\times b(x)$，其中 $b(x)$ 是一个奇数。整理一下我们的条件：$(x,y)$ 是好的当且仅当：

- $b(y)\mid b(x)$。

- $a(x)+1\ge a(y)$。

- $a(x)+1-a(y)$ 和 $a(y)$ 中至少有一个是 $0$。

第三个有点难表达，分类讨论一下：

- 如果 $a(y)=0$，则 $a(x)+1\ge 0$，可以任取。

- 否则 $a(x)+1-a(y)=0$，即 $a(x)=a(y)-1$。

考虑 dp。遇见「最少操作数」平常有两个着手点：$dp_{i,j}$ 表示前 $i$ 个最后一个是 $j$ 的最小次数，这个显然不可做；$dp_{i}$ 表示 $i$ 一定不改变，最小次数，枚举上一个不改变的 $j$ 即可。这个很好做啊！

现在就是要 $\mathcal{O}(1)$ 判断 $[j+1,i-1]$ 可不可以任意操作变成 $[j,i]$ 好的。显然有充要条件：

- $b(j)\mid b(i)$。

- 第二个限制，我们发现，一定是 $i\rightarrow j$ 时 $a$ 一直减 $1$，直到 $0$，然后维持 $0$，最后可以任意变成一个数。有两种情况：变不成 $0$，则要满足 $a(i)-a(j)=i-j$；可以变成 $0$，那么一定满足条件，变成 $0$ 的条件是 $a(i)\le i-j-1$。

---

## 作者：CLZY (赞：3)

> [题目链接（洛谷）](https://www.luogu.com.cn/problem/CF283D) [题目链接（CF）](https://codeforces.com/problemset/problem/283/D)
>
> 给你一个长为 $n$ 的序列 $A$，你可以修改 $A$ 中某些位置上的数，使得 $\forall i \in [1,n)$，$A_i$ 可以被表示为 $A_{i+1}$ 个连续的整数的和（可以包括负数），求最少的修改次数。
>
> $n \le 5000,a_i \le 10^{15}$

$\and$ 是逻辑与，$\or$ 是逻辑或。

根据各位~~小学二年级~~学过的知识，连续的整数的和就等于这些数的平均值乘上数的总数，那么对于 $A_i$ 和 $A_{i+1}$ 而言：

- 如果 $A_{i+1}$ 是奇数，要满足条件，那么 $A_{i+1}|A_i$。

- 如果 $A_{i+1}$ 是偶数，那么这些连续的数的平均数就是一个小数 $x.5$，这个小数乘上 $A_{i+1}$ 是 $A_i$，

  那么 $A_i \equiv \frac {A_{i+1}}2 \pmod {A_{i+1}}$ ，也就是 $A_{i+1} \not |\ A_i \and A_{i+1}|2A_i$。

我们设 $A_i = c \cdot2 ^ {k_1},A_{i+1} = d \cdot 2 ^ {k_2}$，（其中的 $c$ 和 $d$ 都是奇数）。

- 如果满足第一个条件：$d \cdot 2 ^ {k2}$ 是奇数且 $(d \cdot 2 ^ {k_2}) | (c \cdot 2^{k_1})$，可知 $d | c \and k2 = 0$。

- 如果满足第二个条件：
  $$
  (d \cdot 2 ^ {k_2}) \not |\ (c \cdot2 ^ {k_1}),(1)\\(d \cdot 2 ^ {k_2}) | (c \cdot2 ^ {k_1+1}),(2)
  $$
  可知 $d | c \and k2 = k1 + 1$，因为 $k_2$ 多了会不满足 $(2)$ 式，少了会不满足 $(1)$ 式。

整理可得 ，如果 $A_i = c \cdot 2^{k_1}$，那么 $A_{i+1}$ 只能是 $d$ 或 $d \cdot 2^{k_1+1}$（$d$ 是 $c$ 的约数，下同）。

于是我们发现 $A_{i+1}$ 最大为 $2A_i$。

现在我们考虑在确定 $A_i$ 和 $A_j$ （$j < i$）时，给 $A_{i+1},A_{i+2},\cdots,A_{j-1}$ 赋值，能够有哪些合法构造。

设 $A_i = c \cdot2 ^ {k_1},A_{i+1} = d \cdot 2 ^ {k_2}$。

首先，根据我们刚刚推出的结论可得 $d | c$。

考虑从 $A_k$ 到 $A_{k+1}$ ，$2$ 的指数要么 $+1$，要么变成 $0$。

所以 $A_j$ 中 $2$ 的指数 $k_2$，只能通过指数逐次 $+1$ 得到（除非它是0），那么我们发现，要么从 $A_i$ 开始，往后每一项 $2$ 的指数都 $+1$，然后到 $j$ 时刚好为 $k_2$，要么从 $A_i$ 开始 $2$ 的指数随便变化（$+1$ 或者清零），直到中间某处 $k$，此时它的指数为 $0$，之后再从 $0$ 增加到 $k_2$，可以证明只有这两种情况是合法的。

设 $x$ 表示要给多少个数赋值，显然 $x = i - j - 1$。

就是说如果 $i$ 和 $j$ 之间有合法的构造，那么充要条件是
$$
d | c\\ k2 - k1 = x + 1 \or k2 \le x
$$
于是我们定义 ```dp``` 状态 $f[i]$ 表示 $1-i$ 都合法的最小修改次数，我们只需要在 $1-i-1$ 中找到一个 $j$ 满足上述条件，然后假定 $[i+1,j-1]$ 的位置都不合法，来计算 $f[j]$ 对 $f[i]$ 的贡献就行了。

## 细节

我们会发现有时一个 $i$ 根本找不到我们想要的 $j$，那么初始化 $f[i]=i-1$ 即可。

有时最优方案是从某处开始到 $n$ 位置全部修改，这种情况只需要从 $1$ 到 $n$ 扫一遍，取 $f[i]+n-i$ 的最小值作为答案。

## 参考代码

```cpp
#include<bits/stdc++.h>
using namespace std ;
#define ll long long
#define rep(i,l,r) for(ll i=(l);i<=(r);++i)
#define req(i,r,l) for(ll i=(r);i>=(l);--i)
#define wif while
const ll inf = INT_MAX , df = 5005 ;
inline ll read()	{
	ll x = 0 , y = 1 ; char ch = getchar() ;
	wif( ch > '9' || ch < '0' ) y = (ch=='-') ? -1 : 1 , ch = getchar() ;
	wif( ch >= '0' && ch <= '9' ) x = (x<<3) + (x<<1) + ch - '0' , ch = getchar() ;
	return x * y ;	}
ll i,j,k,l,m,n,o,p,q,r,s,t,u,v,w,x,y,z,a[df],b[df],f[df],c[df];
int main()	{
	n = read() ;
	rep(i,1,n)	a[i] = read() ;
	rep(i,1,n)	{
		b[i] = 0 ;
		wif( ! ( a[i] & 1 ) )	a[i] >>= 1 , b[i] ++ ;
	}
	f[0] = f[1] = 0 ;
	rep(i,2,n)	f[i] = i - 1 ;
	rep(i,2,n)	{
		req(j,i-1,1)	{
 			ll x = i - j - 1 ;
			if ( a[j] % a[i] == 0 && ( b[i] - b[j] == x + 1 || b[i] <= x ) )	{
				f[i] = min( f[i] , f[j] + x ) ;
			}
		}
	}
	ll ans = inf ;
	rep(i,1,n)	ans = min( ans , f[i] + ( n - i ) ) ;
	return printf( "%lld\n" , ans ) , 0 ;
}
```

---

