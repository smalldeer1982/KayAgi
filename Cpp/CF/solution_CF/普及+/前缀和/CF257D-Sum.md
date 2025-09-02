# Sum

## 题目描述

Vasya has found a piece of paper with an array written on it. The array consists of $ n $ integers $ a_{1},a_{2},...,a_{n} $ . Vasya noticed that the following condition holds for the array $ a_{i}<=a_{i+1}<=2·a_{i} $ for any positive integer $ i $ ( $ i&lt;n $ ).

Vasya wants to add either a "+" or a "-" before each number of array. Thus, Vasya will get an expression consisting of $ n $ summands. The value of the resulting expression is the sum of all its elements. The task is to add signs "+" and "-" before each number so that the value of expression $ s $ meets the limits $ 0<=s<=a_{1} $ . Print a sequence of signs "+" and "-", satisfying the given limits. It is guaranteed that the solution for the problem exists.

## 样例 #1

### 输入

```
4
1 2 3 5
```

### 输出

```
+++-```

## 样例 #2

### 输入

```
3
3 3 5
```

### 输出

```
++-```

# 题解

## 作者：123456zmy (赞：3)

题意：  
给一个数组 $a$，对于任意的 $1\le i<n$，满足 $a_i\le a_{i+1}\le2a_i$。

你要为其中每个数加一个符号，使得它们的和在 $0$ 到 $a_1$ 之间。
___
考虑从后往前贪心。设当前状态下 $i$ 位及以后的数的和为 $s_i$，当 $s_{i+1}>a_i$ 时，$a_i$ 符号设为 `-`，否则将符号设为 `+` 并将 $i$ 位以后的数符号反转。题目保证了 $a_i\le a_{i+1}\le2a_i$，所以 $s_i$ 一定不大于 $a_i$。

代码：
```cpp
#include<bits/stdc++.h>
#define int long long
using namespace std;
int n,a[100001],s,ans[100001],b[100001],tmp;
signed main()
{
	scanf("%lld",&n);
	for(int i=1;i<=n;i++)scanf("%lld",&a[i]);
	s=a[n];
	for(int i=n-1;i;i--)
	{
		if(s>a[i])ans[i]=1;
		else b[i+1]=1;
		s=abs(s-a[i]);
	}
	for(int i=1;i<=n;i++)tmp^=b[i],putchar(tmp^ans[i]?'-':'+');
	return 0;
}
```

---

## 作者：_acat_ (赞：1)

## 题目大意

给定一个长度为 $n$ 的数组 $a$，且数组 $a$ 满足 $a_i\le a_{i+1}\le 2a_i$，在数组前加 `+` 或 `-` ，使得它们的和 $s$ 满足 $s \in [0,a_i]$。

## 分析

首先想到暴力，可以获得约 $24$pts 的好成绩。

---------
数学 $+$ 贪心。

由 $a_i\le a_{i+1}\le 2a_i$，可得 $a_n - a_{n-1} \le a_{n-1}$。

再用这个差值 $s$ 去与 $a_{n-2}$ 作差，易得 $s \le a_{n-2}$，然后依次递推。

### 证明：

设 $a_{n}=x+y+z$，$a_{n-1}=x+y$，$a_{n-2}=x$，则 $z \le x+y$。

当 $z \ge x$ 时，$0 \le z-x \le y \le x$。

当 $z < x$ 时，$0 < x-z < x$。

所以只要从末尾开始大的减去小的得到的最后一个数就能满足大于等于 $0$ 且小于等于 $a_1$。

---

