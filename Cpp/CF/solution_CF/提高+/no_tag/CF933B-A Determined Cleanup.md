# A Determined Cleanup

## 题目描述

In order to put away old things and welcome a fresh new year, a thorough cleaning of the house is a must.

Little Tommy finds an old polynomial and cleaned it up by taking it modulo another. But now he regrets doing this...

Given two integers $ p $ and $ k $ , find a polynomial $ f(x) $ with non-negative integer coefficients strictly less than $ k $ , whose remainder is $ p $ when divided by $ (x+k) $ . That is, $ f(x)=q(x)·(x+k)+p $ , where $ q(x) $ is a polynomial (not necessarily with integer coefficients).

## 说明/提示

In the first example, $ f(x)=x^{6}+x^{5}+x^{4}+x=(x^{5}-x^{4}+3x^{3}-6x^{2}+12x-23)·(x+2)+46 $ .

In the second example, $ f(x)=x^{2}+205x+92=(x-9)·(x+214)+2018 $ .

## 样例 #1

### 输入

```
46 2
```

### 输出

```
7
0 1 0 0 1 1 1
```

## 样例 #2

### 输入

```
2018 214
```

### 输出

```
3
92 205 1
```

# 题解

## 作者：NaVi_Awson (赞：2)

## Description

[题库链接](http://codeforces.com/problemset/problem/933/B)

给你两个正整数 $p,k$ ，询问是否能够构造多项式 $f(x)=\sum\limits_{i=0}^{d-1}a_ix^i$ ，使得存在多项式 $q(x)$ ，满足 $f(x)=q(x)\cdot(x+k)+p$ 。且 $a_i\in[0,k),i\in [0,d)$ 。

$1\leq p\leq 10^{18},2\leq k\leq 2000$

## Solution

我们假设 $q(x)=\sum\limits_{i=0}^{d-2}b_ix^i$ ，那么存在 $$\begin{aligned}a_0&=kb_0+p\\a_1&=kb_1+b_0\\&\vdots\\a_{d-2}&=kb_{d-2}+b_{d-3}\\a_{d-1}&=b_{d-2}\end{aligned}$$

逐步从下往上递推，最终我们可以得到 $p=\sum\limits_{i=0}^{d-1} (-k)^ia_i$ 。显然 $p_{(10)}=\overline{a_{d-1}\cdots a_1a_0}_{(-k)}$ ，做一遍进制转换就好了。

## Code

```cpp
//It is made by Awson on 2018.2.17
#include <bits/stdc++.h>
#define LL long long
#define dob complex<double>
#define Abs(a) ((a) < 0 ? (-(a)) : (a))
#define Max(a, b) ((a) > (b) ? (a) : (b))
#define Min(a, b) ((a) < (b) ? (a) : (b))
#define Swap(a, b) ((a) ^= (b), (b) ^= (a), (a) ^= (b))
#define writeln(x) (write(x), putchar('\n'))
#define lowbit(x) ((x)&(-(x)))
using namespace std;
void read(LL &x) {
    char ch; bool flag = 0;
    for (ch = getchar(); !isdigit(ch) && ((flag |= (ch == '-')) || 1); ch = getchar());
    for (x = 0; isdigit(ch); x = (x<<1)+(x<<3)+ch-48, ch = getchar());
    x *= 1-2*flag;
}
void print(LL x) {if (x > 9) print(x/10); putchar(x%10+48); }
void write(LL x) {if (x < 0) putchar('-'); print(Abs(x)); }

LL p, k, a[10005], d;

void work() {
	read(p), read(k); k = -k;
	while (p) {
		a[++d] = p%k, p /= k; 
		if (a[d] < 0) a[d] = -k+a[d], p++;
	}
	writeln(d);
	for (int i = 1; i <= d; i++) write(a[i]), putchar(' ');
}
int main() {
	work(); return 0;
}
```

---

## 作者：XL4453 (赞：0)

### $\text{Difficulty : 2000}$
---
### 解题思路：

本质上是一个式子的推。

首先写出 $f(x)$ 和 $q(x)$，有：$f(x)=\sum_{i=0}^na_ix^i$，$q(x)=\sum_{i=0}^nb_ix^n$。

然后有：$xq(x)=\sum_{i=0}^nb_ix^{i+1}=\sum_{i=1}^{n+1}b_{i-1}x^i$，而且 $kq(x)=\sum_{i=0}^nkb_ix^i$。

带入到条件式子：$\sum_{i=0}^na_ix^i=\sum_{i=1}^n[(kb_i+b_{i-1})x^i]+kb_0+p+b_nx^{n+1}$。

也就是说：

$\begin{cases}
a_0=kb_0+p
\\a_i=kb_i+b_{i-1}(i\in[1,n])
\\b_n=0
\end{cases}$

恒等变形：

$\begin{cases}
a_0-kb_0=p
\\a_i-kb_i=b_{i-1}(i\in[1,n])
\\b_n=0
\end{cases}$


每一层依次带入就得到了：$p=\sum_{i=0}^na_i(-k)^i$。
做一个基础的进制转化就好了，不清楚的可以参照 [$\text{P1017}$](https://www.luogu.com.cn/blog/JSYZCHTHOLLY/p1017-noip2000-ti-gao-zu-jin-zhi-zhuai-huan)。

---
### 代码：

```cpp
#include<cstdio>
using namespace std;
long long p,k,cnt,num[100005];
int main(){
	scanf("%I64d%I64d",&p,&k);
	k=-k;
	while(p){
		num[++cnt]=p%k;
		if(num[cnt]<0)num[cnt]-=k,p+=k;
		p/=k;
	}
	printf("%I64d\n",cnt);
	for(int i=1;i<=cnt;i++)
	printf("%I64d ",num[i]);
	printf("\n");
	return 0;
}
```



---

