# [AGC028A] Two Abbreviations

## 题目描述

## AT4435 [AGC028A]两个缩写
给定一个长度为 _N_ 的字符串 _S_ 和一个长度为 _M_ 的字符串 _T_ ，这些字符串由小写英文字符组成。

当一个字符串 _X_ 满足以下条件时，称为好字符串 _**（good string）**_ 。

-  _X_ 的长度 _L_ 可以被 _N_ 和 _M_ 整除
- 连接 _X_ 的 1, _L_ / _N_ +1,2× _L_ / _N_ +1, ...( _N_ −1)× _L_ / _N_ +1 且不改变顺序，结果为 _S_
- 连接 _X_ 的 1, _L_ / _M_ +1,2× _L_ / _M_ +1, ...( _M_ −1)× _L_ / _M_ +1 且不改变顺序，结果为 _T_ 

判断是否存在好字符串。如果存在，请找到最短的此类字符串的长度。

------------

## 说明/提示

`accept` 字符串是一个好字符串。没有比这更短的字符串了，所以答案是6。

## 样例 #1

### 输入

```
3 2
acp
ae```

### 输出

```
6```

## 样例 #2

### 输入

```
6 3
abcdef
abc```

### 输出

```
-1```

## 样例 #3

### 输入

```
15 9
dnsusrayukuaiia
dujrunuma```

### 输出

```
45```

# 题解

## 作者：阿丑 (赞：3)

[题目传送门](https://www.luogu.com.cn/problem/AT4435)

#### 题意：

- 给出一个长为 $n$ 的字符串 $S$ 和一个长为 $m$ 的字符串 $T$。

- 问是否存在一个字符串 $X$ 满足：

  1. $X$ 的长度是 $l$ 是 $n$ 和 $m$ 的倍数；
  2. 将 $X$ 的第 $1$ 位，第 $\frac ln+1$ 位，第 $2\frac ln+1$ 位，$\dots$，第 $(n-1)\frac ln+1$ 位拼接起来得到的字符串为 $S$；
  2. 将 $X$ 的第 $1$ 位，第 $\frac lm+1$ 位，第 $2\frac lm+1$ 位，$\dots$，第 $(m-1)\frac lm+1$ 位拼起来得到的字符串为 $T$；
  
- 若存在，输出 $l$ 的最小值。若不存在，输出 $-1$。

- $n,m\le10^5$。

#### 分析：

首先，$l$ 既是 $n$ 的倍数，又是 $m$ 的倍数 $\Rightarrow$ $l$ 是 $n$ 和 $m$ 的最小公倍数的倍数。

设 $g$ 为 $n$ 和 $m$ 的最大公因数，则 $l=\dfrac{nm}gk$。

记 $P_i$ 表示字符串 $P$ 的第 $i+1$ 位。

则对 $X$ 的要求即为 $S_a=X_{a\cdot\frac ln}=X_{a\frac mgk}$，$T_b=X_{b\frac lm}=X_{b\frac ngk}$。

即，对于任意的 $i$，若 $i$ 可以表示为 $a\dfrac mgk$ 的形式，则要求 $X_i=S_a$；若 $i$ 可以表示为 $b\dfrac ngk$ 的形式，则要求 $X_i=T_b$。

对于任意的 $i$：

1. 若 $i$ 不能表示为上述形式的任意一种，则对于 $X_i$ 没有要求。
2. 若 $i$ 能且仅能表示为其中的一种，则对于 $X_i$ 仅有一个要求，只需让 $X_i$ 为对应的字符即可。
3. 若 $i$ 同时可以表示成两种形式，则有两个要求。若这两个要求不相同，则不存在同时满足两个条件的 $X_i$，即无解。

所以对于是否有解的问题，我们只需要考虑所有同时可以表示成两种形式的 $i$，即 $i=a\dfrac mgk=b\dfrac ngk$。此时有 $X_i=S_a=T_b$，所以若 $S_a\neq T_b$，则无解。

消掉 $k$，注意到 $g$ 是 $n$，$m$ 的最大公因数，故 $\dfrac mg$，$\dfrac ng$ 互质。所以 $a$ 是 $\dfrac ng$ 的倍数，设 $a=c\dfrac ng$。同理，设 $b=d\dfrac mg$。

带回，得到 $c\dfrac ng\dfrac mgk=d\dfrac mg\dfrac ngk$。即 $c=d$。

对于任意同时可以表示为两种形式的 $i$，都存在一个 $c$ 满足 $i=c\dfrac ng\dfrac mgk$，故枚举 $c$ 即可得到所有的 $i$。因为 $a<n$，所以 $c<n$，时间复杂度正确。

我们已经解决了无解的情况，现在处理最优解。注意到 $k$ 在上文中被消掉了，因此对于 $k$ 并没有限制。因此取 $k=1$ 即可得到最小解。

#### 思路：

1. 枚举所有的 $c$，根据 $c$ 得到 $i$ 以及 $i$ 对应的 $a$ 和 $b$。

2. 判断 $S_a$ 和 $T_b$ 是否相同。若存在不同则无解，否则有解，解为 $n$ 和 $m$ 的最小公倍数。

---

```cpp
#include <bits/stdc++.h>
using namespace std;
const int mN=1e5+9;
int n, m, g;
char s[mN], t[mN];

int gcd(int x, int y) {	//辗转相除求 gcd。也可以暴力枚举求解。
	for(int tmp; y; ) tmp=x%y, x=y, y=tmp;
	return n;
}

int main() {
	scanf("%d%d\n%s\n%s", &n, &m, s, t), g=gcd(n, m);
	for(int c=0; c<g; ++c)
		if(s[n/g*c]!=t[m/g*c]) {
			puts("-1");
			return 0;
		}
	printf("%lld\n", (long long) n*m/g);	//记得 long long
	return 0;
}
```

---

