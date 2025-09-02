# 「KDOI-04」Again Counting Set

## 题目背景

![](https://cdn.luogu.com.cn/upload/image_hosting/s502kfip.png)

## 题目描述

小 S 不喜欢集合，不喜欢自然数，不喜欢求和，不喜欢求积，不喜欢最小值，不喜欢最大值，不喜欢 $\operatorname{mex}$，所以有了这题。

给出 $n,k$，求有多少个可重**整数**集合 $S$ 满足：

* $|S|=k$；
* 对于任意 $x\in S$，$0\le x\le n$；
* $\displaystyle{\prod_{x\in S} x=\min_{x\in S} x}$；
* $\displaystyle{\sum_{x\in S} x=\min_{x\in S} x+\max_{x\in S}x+{\operatorname{mex}}(S)}$。

**注： $\bf{mex}$ 指集合中没有出现过的最小的自然数。**

## 说明/提示

**【补充说明】**

为了更好的让选手理解题面，给出若干合法/不合法集合例子：

+ $\{0,1,2,2\}$。

该集合是一个符合要求的集合，因为 $0\times 1\times 2\times 2=0=\min\{0,1,2,2\}$，$0+1+2+2=5,\min\{0,1,2,2\}+\max\{0,1,2,2\}+\operatorname{mex}\{0,1,2,2\}=0+2+3=5$。

+ $\{3,5\}$

该集合不是一个符合要求的集合，因为虽然 $3+5=8,\min\{3,5\}+\max\{3,5\}+\operatorname{mex}\{3,5\}=3+5+0=8$，但是 $3\times 5\not=\min\{3,5\}$。

+ $\{1,9,1,9,8,1,0\}$。

该集合不是一个符合要求的集合，因为虽然 $1\times 9\times 1\times 9\times 8\times 1\times 0=0=\min\{1,9,1,9,8,1,0\}$，但是其和为 $29$ 而并非 $\min+\max+\operatorname{mex}=0+9+2=11$。

**【数据范围】**  

对于 $100\%$ 的数据，保证 $1\le T\le10^6$，$1\le n,k\le10^{18}$。

|测试点编号|分值|$T\le$|$k\le$|$n$|
|:-:|:-:|:-:|:-:|:-:|
|$1$|$10$|$5$|$5$|$\le5$|
|$2$|$10$|$10^5$|$10^{18}$|$=1$|
|$3$|$10$|$10^5$|$10^{18}$|$=2$|
|$4$|$10$|$10^5$|$10^{18}$|$=3$|
|$5$|$10$|$10^5$|$10^{18}$|$=4$|
|$6$|$10$|$10^5$|$10^{18}$|$=5$|
|$7$|$10$|$10^5$|$10$|$\le10$|
|$8$|$10$|$10^5$|$10^3$|$\le10^3$|
|$9$|$10$|$10^6$|$10^{18}$|$\le10^{8}$|
|$10$|$10$|$10^6$|$10^{18}$|$\le10^{18}$|

## 样例 #1

### 输入

```
7
1 4
2 4
5 3
2 100
3 8
20 50
499122178 4```

### 输出

```
1
2
0
3
5
39
998244353
```

# 题解

## 作者：Alex_Wei (赞：18)

条件四要求 $k \geq 2$，结合条件三要求 $\min x \leq 1$（反证法易证）。

当 $\min x = 1$ 时，条件三要求集合内所有数均为 $1$，结合条件四，合法集合仅有 $S = \{1, 1\}$。

当 $\min x = 0$ 时，条件三满足，条件四形如 $\sum x = \max x + \operatorname{mex}(S)$。

设 $S$ 所有非最大值且非零数集合为 $T$。

感性理解 $\operatorname{mex}(S)$ 不会太大（$\operatorname{mex}(S)$ 增长时，$\sum_{x\in T} x$ 的最小值以平方级别增长）。手玩可知：

- $\operatorname{mex}(S) = 1$ 不可能。
- $\operatorname{mex}(S) = 2$ 时，$T = \{1, 1\}$（最大值可为 $1$ 或 $3\sim n$ 任意值）。
- $\operatorname{mex}(S) = 3$ 时，$T = \{1, 2\}$（最大值可为 $2$ 或 $4\sim n$ 任意值）或 $\{1, 1, 1\}$（最大值为 $2$）。
- $\operatorname{mex}(S) = 4$ 时，$T = \{1, 1, 2\}$（最大值为 $3$）。
- $\operatorname{mex}(S) = 5$ 时，就算最大值为 $4$，那么 $T$ 中所有数之和也至少为 $1 + 2 + 3 > 5$。
- 类似可证对于更大的 $\operatorname{mex}(S)$，同样无解。

注意集合内可以有任意正整数个 $0$。根据上述分析计算答案即可。

时间复杂度 $\mathcal{O}(1)$。

```cpp
#include <bits/stdc++.h>
using namespace std;
long long n, k;
long long solve() {
  cin >> n >> k;
  if(k == 1) return 0;
  long long ans = 0;
  if(k >= 4) {
    ans += 1 + max(0ll, n - 2);
    if(n >= 2) ans += 1 + max(0ll, n - 3);
  }
  if(k >= 5) {
    if(n >= 2) ans++;
    if(n >= 3) ans++;
  }
  if(k == 2) ans++;
  return ans;
}
int main() {
  #ifdef ALEX_WEI
    freopen("1.in", "r", stdin);
    freopen("1.out", "w", stdout);
  #endif
  ios::sync_with_stdio(0);
  cin.tie(0), cout.tie(0);
  int T;
  cin >> T;
  while(T--) cout << solve() << "\n";
  return 0;
}
```

---

## 作者：Jusc (赞：3)

[题目传送门](https://www.luogu.com.cn/problem/P9034)

## 题外话

忘了 $0$ 是自然数，还以为样例错了，还在赛时答疑上质疑了一下，尴尬。

## 正文

### 分析

我们默认序列是有序的，这显然对结果没有影响。

对于 $\displaystyle{\prod_{x\in S} x=\min_{x\in S} x}$，我们可以知道 $0$ 是一定要选的，但也有一个例外，后面会写。

对于 $\displaystyle{\sum_{x\in S} x=\min_{x\in S} x+\max_{x\in S}x+{\operatorname{mex}}(S)}$，我们可以将左右两边的最大与最小值去除，那么这个式子就告诉我们需要使序列中除去最值外的数相加等于 ${\operatorname{mex}(S)}$。

显然的，这需要 $ {\operatorname{mex}(S)} $ 大于序列 $ S $ 中除去最大值后的最大值。

对于除去最大值的序列，我们姑且称其位 $ T $。序列 $ S $ 中的最大值，我们姑且称其为 $smax$。序列 $ T $中的最大值称为 $ tmax $。

如果序列 $ T $ 不是从 $0$ 开始连续的自然数组成的，那么就会存在 $ {\operatorname{mex}(S)} < tmax $，这样无法满足条件。

如果 $T$ 是从 $0$ 开始的连续自然数组成的，那 ${\operatorname{mex}(S)}$ 就会有三种可能。

1. ${\operatorname{mex}(S)}=tmax+1$。即 $smax>tmax+1$ 时。

1. ${\operatorname{mex}(S)}=smax+1=tmax+2$。即 $smax=tmax+1$ 时。

1. ${\operatorname{mex}(S)}=tmax+1=smax+1$。即 $smax=tamx$ 时。

容易发现，只有较小的数才能满足 $\sum_{i=1}^nT_i={\operatorname{mex}(S)}$。

#### 对于第一种情况：

因为 ${\operatorname{mex}(S)}-tmax=1$，所以必然存在一个 $1$。为了保证连续性，所以 $tmax=1$ 或 $tmax=2$。

即 $T=\{0,1,2\}$ 或 $T=\{0,1,1\}$。

此时 $smax$ 最小值分别为 $4$ 和 $3$，最大值为 $n$。因为在此区间内 $smax$ 的大小不会影响条件的满足，任取一个都能够满足，所以方案数可分别加上 $n-3$ 和 $n-2$。当然 $k$ 都需要满足大于等于 $4$，大于 $4$ 时，只需添加 $0$ 即可。

#### 对于第二种情况：

因为 ${\operatorname{mex}(S)}-tmax=2$，所以是必然存在两个 $1$ 的。因为需要保证连续，所以 $tmax=1$ 或 $tmax=2$。

即 $S=\{0,1,1,1,2\}$ 或 $S=\{0,1,1,2,3\}$。

$k$ 都要满足大于等于 $5$，方案数加一，$k$ 大于 $5$ 时，添加 $0$ 即可。

#### 对于第三种情况：

因为 ${\operatorname{mex}(S)}-tmax=1$，所以必然存在一个 $1$。因为$smax=tmax$，所以两个相同的保证连续性的数，即两个 $1$ 或 $2$。

即 $S=\{0,1,2,2\}$ 或 $S=\{0,1,1,1\}$。

同理要满足 $k \geqslant 4$。$k>4$ 时添加 $0$即可。

#### 特殊情况：

前面所有的都选了 $0$。有一种不需要选，需要特殊判断。即 $S=\{1,1\}$。

### 综上所述：

1. 当 $n \geqslant 4 ,k \geqslant 4$ 时，方案数加 $n-3$。

1. 当 $n \geqslant 3 ,k \geqslant 4$ 时，方案数加 $n-2$。

1. 当 $n \geqslant 2 ,k \geqslant 5$ 时，方案数加一。

1. 当 $n \geqslant 3 ,k \geqslant 5$ 时，方案数加一。

1. 当 $n \geqslant 2 ,k \geqslant 4$ 时，方案数加一。

1. 当 $n \geqslant 1 ,k \geqslant 4$ 时，方案数加一。

1. 当 $ k=2 $ 时，方案数加一。

注意 $n$ 也有限制条件。

## Code：
```cpp
#include<bits/stdc++.h>

using namespace std;

int main() 
{
	int T;
	scanf("%d",&T);
	while(T--)
	{
		long long n,k;
		scanf("%lld%lld",&n,&k);
		long long ans=0;
		if(n>=2&&k>=5) ans++;
		if(n>=3&&k>=5) ans++;
		if(n>=4&&k>=4) ans+=n-3;
		if(n>=3&&k>=4) ans+=n-2;
		if(n>=2&&k>=4) ans++;
		if(k>=4) ans++;//n一定大于1，不用判断
		if(k==2) ans++;
		printf("%lld\n",ans);
	}
	return 0;
}
```

---

## 作者：_shy (赞：2)

## [P9034 「KDOI-04」Again Counting Set](https://www.luogu.com.cn/problem/P9034)
### 思路
1. **以 $\operatorname{Mex}(S)$ 作为讨论依据**。
2. 当 $\operatorname{Mex}(S)=0$ 时，由 $\prod\limits_{x\in S}x=\min\limits_{x\in S}\{x\}$ 知，$S$ 中元素的值只能为 $1$；又根据最后一条说明 $S$ 只能为 $\{1,1\}$，当且仅当 $k=2$ 时存在这种方案。当 $\operatorname{Mex}(S)=1$ 时，由最后一条知，$\sum\limits_{x\in S} x-\max\limits_{x\in S}{x}=1$，显然除最大值外其他值的和要不为 $0$，要不大于 $1$，故无解。当 $\operatorname{Mex}(S)=2$ 时，$0,1\in S$，若 $1$ 为 $S$ 中的最大值，则 $S$ 为 $\{0,1,1,1\}$；否则，$S$ 为 $\{0,1,1,x\},x>2$。当 $\operatorname{Mex}(S)=3$ 时，$0,1,2\in S$，若 $2$ 为 $S$ 中的最大值，则 $S=\{0,1,1,1,2\}$ 或 $\{0,1,2,2\}$；否则，$S=\{0,1,1,1,x\},x>3$。当 $\operatorname{Mex}(S)=4$ 时，$0,1,2,3\in S$，则 $3$ 一定为 $S$ 的最大值，故 $S=\{0,1,1,2,3\}$。当 $\operatorname{Mex}(S)>4$ 时，由于 $\frac{(n-2)(n-1)}{2}>\operatorname{Mex}(S)=n$，故无解。
3. 当 $\operatorname{Mex}(S)=2$ 或 $3$ 或 $4$ 时，集合中的零元素，其可以是任意个。
4. 时间复杂度为 $\mathcal O(T)$。

### 代码

```cpp
#include <bits/stdc++.h>
using namespace std;
long long n, k, t;
void read (long long &x) 
{
	x = 0; int w = 1;
	char ch = getchar ();
	while (ch < '0' || ch > '9') 
	{
		if (ch == '-') w = -1;
		ch = getchar ();
	}
	while (ch >= '0' && ch <= '9') 
	{
		x = (x << 1) + (x << 3) + ch - 48;
		ch = getchar (); 
	}
	x *= w;
} 
int main ()
{
	read (t);
	while (t--) 
	{
		long long ans = 0;
		read (n), read (k);
		if (k == 2 && n >= 1) ans ++;
		if (k >= 4 && n >= 1) ans ++;
		if (k >= 5 && n >= 2) ans ++;
		if (k >= 4 && n >= 2) ans ++;
		if (k >= 5 && n >= 3) ans ++;
		if (n > 2 && k >= 4) ans += (n - 2);
		if (n > 3 && k >= 4) ans += (n - 3);
		printf ("%lld\n", ans);
	}
	return 0;
}

```

---

## 作者：SunsetGlow95 (赞：2)

# 题解 - P9034 「KDOI-04」Again Counting Set

## 再述题意

给出正整数 $n,k$，求有多少个可重整数集合 $S$ 满足：

- $|S|=k$；
- 对于任意 $x\in S$，$0\le x\le n$；
- $\prod_{x\in S} x=\min_{x\in S} x$；
- $\sum_{x\in S} x=\min_{x\in S} x+\max_{x\in S}x+{\operatorname{mex}}(S)$。

## 分析

前两个条件，显然说明：$k$ 是集合的大小，$[0,n]$ 是集合的值域。

我们考虑第三个条件。假设 $a=\min_{x\in S} x$，$pa=\prod_{x\in S} x$。也就是说，$a$ 是集合最小值，$p$ 是其余元素的积，可以得到 $pa=a$。

当 $a=0$ 时，显然等式成立，否则 $p=1$。

也就是说，集合**要么存在 $0$，要么全都是 $1$**。

---

接着来看第四个条件。

当集合全都是 $1$ 时，代入这个式子，得：

$$\sum_{x\in S} x=2$$

所以这个情况**只有 $k=2$ 的时候**合法。

否则必然存在 $0$。设 $m=\max_{x\in S}x$，$r+m=\sum_{x\in S} x$，也就是说 $m$ 是集合最大值，$r$ 是其余元素的和。代入式子，可以得到：

$$r+m=m+{\operatorname{mex}}(S)$$

$$r={\operatorname{mex}}(S)$$

所以我们要求的集合特征很明显：**去除一个最大值，剩下所有数的和就是 ${\operatorname{mex}}(S)$**。

接下来就比较简单了。我们分类讨论一下。

---

当 ${\operatorname{mex}}(S)=m+1$。

这意味着，集合包含 $[0,m-1]$ 的所有整数。所以：

$$m+1=r\ge \frac{1}{2}m(m-1)$$

$m$ 的自然数取值只有 $[0,1,2,3]$。所以我们根据每个取值，求出 $r$，并且根据集合包含 $[0,m-1]$ 的所有整数，可以枚举这样的集合数。

- $m=0$ 意味着全部数都是 $0$，则 $r=0$，所以这是不可能合法的；
- $m=1$ 的时候，$r=2$，集合应该长这样：$\{0,\ldots,0,1,1,1\}$；
- $m=2$ 的时候，$r=3$，并且集合包含一个 $1$，有两种可能：$\{0,\ldots,0,1,1,1,2\}$，或 $\{0,\ldots,0,1,2,2\}$；
- $m=3$ 的时候，$r=4$，并且集合包含一个 $1$ 和一个 $2$，应该长这样：$\{0,\ldots,0,1,1,2,3\}$。

这些集合在 $n,k$ 足够的时候都可以唯一构造。

---

当 ${\operatorname{mex}}(S)=r<m$。

这意味着，集合包含 $[0,r-1]$ 的所有整数，且不包含 $r$。所以：

$$r\ge \frac{1}{2}r(r-1)$$

$$r\le 3$$

- 因为集合存在 $0$，所以 ${\operatorname{mex}}(S)\neq 0$。
- $r=1$ 的时候，集合没有 $1$，所以元素和不能为 $1$，矛盾。
- $r=2$ 的时候，集合包含一个 $1$，又要 $r=2$，则集合应该长成 $\{0,\ldots,0,1,1,m\}$。
- $r=3$ 的时候，集合包含一个 $1$ 和一个 $2$，长成 $\{0,\ldots,0,1,2,m\}$。

在后两种情况中，集合的数目与 $m$ 的取值数目有关，$m$ 只需要满足 $m>r$ 即可。

---

综上，我们来梳理一下答案的构成：

- $k=2$ 时，$\{1,1\}$ 为合法集合，贡献为 $1$；
- $k\ge 4$ 时，$\{0,\ldots,0,1,1,1\}$ 为合法集合，贡献为 $1$；
- $n\ge 2$ 且 $k\ge 5$ 时，$\{0,\ldots,0,1,1,1,2\}$ 为合法集合，贡献为 $1$;
- $n\ge 2$ 且 $k\ge 4$ 时，$\{0,\ldots,0,1,2,2\}$ 为合法集合，贡献为 $1$；
- $n\ge 3$ 且 $k\ge 5$ 时，$\{0,\ldots,0,1,1,2,3\}$ 为合法集合，贡献为 $1$；
- $n>2$ 且 $k\ge 4$ 时，$\{0,\ldots,0,1,1,m\}$ 为合法集合，贡献为 $n-2$；
- $n>3$ 且 $k\ge 4$ 时，$\{0,\ldots,0,1,2,m\}$ 为合法集合，贡献为 $n-3$。

---

## 作者：TernaryTree (赞：1)

好题。好题。Orz zxx。

前两个限制都不用看，很简要了。

**不妨看看第三个。**

考虑分类讨论 $\min$，当 $\min=0$ 时显然成立，当 $\min=1$ 时，集合中的其他元素乘积也只能是 $1$，所以集合里面全是 $1$。当 $\min\ge 2$ 时有集合中的其他元素乘积是 $1$，但是由于最小值是 $2$ 所以其他元素只能 $\ge 2$，矛盾舍去。

**接下来来看第四个（重点）。**

首先显然的，当 $k\ge 3$ 且 $\min=1$ 时，不满足第四个等式，舍去。

接下来讨论的默认是 $\min=0$ 的情况。

我们将集合按从小到大排成一排。

然后是几个定义：

- $\min$，$\max$ 表示最左边和最右边的元素，也就是最小值和最大值。

- $\rm mid$ 表示去掉最左边和最右边的和。即总和减去 $\min+\max$。

- $\rm M$ 表示去掉最左边和最右边，剩下元素构成的集合。

- $\rm last$ 表示 $\rm M$ 中的最大值。

要想满足第四个等式，将等式两端同时减去 $\min+\max$，则得到 $\rm mid=mex$。

再证明几个结论：

- 中间这一段 $\rm M$ 值域连续。即，不存在 $x\not\in \rm M$ 且 $x\lt \rm last$。

  考虑反证。如果存在这样的 $x$，那么最小的 $x$ 就是 $\rm mex$。此时一定有 $\rm mex\lt mid$，因为 $\rm mid\ge last$。不满足，得证。
  
- $\rm last$ 不超过 $2$。

  显然的，$\rm mid\ge \dfrac{last(last+1)}2$，$\rm mex\le last+2$。而若 $\rm last\ge 3$，不等式组无解。得证。
  
- $\rm M$ 中大于 $0$ 的数不超过 $3$ 个。

  与上一个结论同理，不等式组无解。故得证。
  
然后我们简单枚举一下几种情况，大概是：

$$\rm S=\{0\ (\min),\overbrace{0,0,0,\dots,1,1\ (\rm last)}^{\rm M}, \{1,3,4,5,\dots n\}\ (\max)\}$$

$$\rm S=\{0\ (\min),\overbrace{0,0,0,\dots,1,2\ (\rm last)}^{\rm M}, \{2,4,5,6,\dots n\}\ (\max)\}$$

$$\rm S=\{0\ (\min),\overbrace{0,0,0,\dots,1,1,1\ (\rm last)}^{\rm M}, 2\ (\max)\}$$

$$\rm S=\{0\ (\min),\overbrace{0,0,0,\dots,1,1,2\ (\rm last)}^{\rm M}, 3\ (\max)\}$$

特判有点多，具体可以见丑陋无比的赛时代码。

```cpp
#include <bits/stdc++.h>
#define int long long

using namespace std;

struct ios {
    inline char read() {
        static const int inlen = 1 << 18 | 1;
        static char buf[inlen], *s, *t;
        return (s == t) && (t = (s = buf) + fread(buf, 1, inlen, stdin)), s == t ? -1 : *s++;
    }
    template<typename T> inline ios& operator>> (T &x) {
        static char c11, boo;
        for (c11 = read(), boo = 0; !isdigit(c11); c11 = read()) {
            if (c11 == -1) return *this;
            boo |= c11 == '-';
        }
        for (x = 0; isdigit(c11); c11 = read()) x = x * 10 + (c11 ^ '0');
        boo && (x = -x);
        return *this;
    }
} fin;

struct exios {
    template<typename _CharT, typename _Traits = char_traits<_CharT>>
    struct typ {
        typedef basic_ostream<_CharT, _Traits>& (* end) (basic_ostream<_CharT, _Traits>&);
    };

    template<typename T> friend exios &operator<<(exios &out, T num) {
        if (num < 0) putchar('-'), num = -num;
        if (num >= 10) out << num / 10;
        putchar(num % 10 + '0');
        return out;
    }

    friend exios &operator<<(exios &out, const char * s) { printf("%s", s); return out; }
    friend exios &operator<<(exios &out, string s) { cout << s; return out; }
    friend exios &operator<<(exios &out, typ<char>::end e) { puts(""); return out; }
} fout;

int t, n, k;
int ans = 0;

int ge(int x) {
    return x > n ? 0 : n - x + 1;
}

signed main() {
    fin >> t;
    while (t--) {
        fin >> n >> k;
        if (k == 1) {
            puts("0");
            continue;
        }
        if (k == 2) {
            puts("1");
            continue;
        }
        if (k == 3) {
            puts("0");
            continue;
        }
        if (k == 4) {
            ans = 1 + ge(3) + ge(4) + (n >= 2);
            cout << ans << endl;
            continue;
        }
        ans = 1 + ge(3) + ge(4) * (n >= 2) + (n >= 2) + (n >= 2) + (n >= 3) * (n >= 2);
        fout << ans << endl;
    }
    return 0;
}
```

---

## 作者：daniEl_lElE (赞：1)

**官方题解**

按 $\operatorname{mex}$ 枚举：

+ $\operatorname{mex}_{x\in S}x=0$：

容易发现 $\{S\}$ 仅包含 $1$。

枚举可得，符合要求的方案是 $\{1,1\}$。

+ $\operatorname{mex}_{x\in S}x=1$：

$\{S\}$ 包含 $0$，不包含 $1$，此时已经满足 $\min_{x\in S}x=\prod_{x\in S}x$ 了。

考虑 $\max_{x\in S}x+\operatorname{mex}_{x\in S}x=\sum_{x\in S}x$，$\max$ 可以和最大值抵消，也就是说除最大值以外所有数和为 $\operatorname{mex}$。即除最大值以外和为 $1$，这是不可能的。

+ $\operatorname{mex}_{x\in S}x=2$：

$\{S\}$ 包含 $0,1$，不包含 $2$。

尝试枚举 $\max$。容易发现符合要求的有 $\{0,1,1,1\},\{0,1,1,3\},\{0,1,1,4\}\dots$ 等。同时，当 $k>4$，在集合中添加 $0$ 依然符合要求。

+ $\operatorname{mex}_{x\in S}x=3$：

$\{S\}$ 包含 $0,1,2$，不包含 $3$。

容易发现集合内元素已经和 $\operatorname{mex}$ 抵消了，我们只需要做到其他和为 $\max$。一种情况是 $\max=2$，可以选择添加 $\{1,1\}$ 或 $\{2\}$。也可以是 $\max\geq4$，此时添加 $\max$ 即可。

+ $\operatorname{mex}_{x\in S}x=4$：

$\{S\}$ 包含 $0,1,2,3$，不包含 $4$。

此时和大于 $\operatorname{mex}$，故 $\max=3$。

仅 $\{0,1,1,2,3\}$ 符合要求。

+ $\operatorname{mex}_{x\in S}x=5$：

容易发现此时和大于 $\operatorname{mex}+\max$，显然不符合要求，同理更大也不符合要求。

**代码**

```cpp
#include <bits/stdc++.h>
#define int long long
#define double long double
using namespace std;
int read(){
	char c; int ans=0; int z=1;
	while(!isdigit(c=getchar()))z-=2*(c=='-');
	do{ans=(ans*10+c-'0');}while(isdigit(c=getchar()));
	return ans*z;
}
void print(int x){
	if(x<0) putchar('-');
	if(llabs(x)>=10) print(llabs(x)/10);
	putchar((llabs(x)%10)+'0');
}
void endl(){
	putchar(10);
}
signed main(){
	int t=read();
	while(t--){
		int n=read(),k=read();
		int ans=0;
		if(n>=1&&k==2) ans++;//mex=0
		if((n==1||n==2)&&k>=4) ans++;
		else if(n>=3&&k>=4) ans+=n-1;//mex=2
		if(n>=2&&k>=4) ans++;
		if(n>=2&&k>=5) ans++;
		if(n>=4&&k>=4) ans+=n-3;//mex=3
		if(n>=3&&k>=5) ans++;//mex=4
		print(ans),endl();
	}
	return 0;
}
```

---

## 作者：Austin0116 (赞：0)

# 分析
由条件3可知，$S$ 中必然有一个 $0$ 或全是 $1$。

由条件4可知，$\displaystyle{{\operatorname{mex}}(S) = \sum_{x\in S} x-\min_{x\in S} x-\max_{x\in S}x}$ 

根据这两个性质，感觉 ${\operatorname{mex}}(S)$ 不会很大，所以可以对其进行枚举。

当 ${\operatorname{mex}}(S) = 0$ 时，$S= \{ 1,1 \} $ 方案数为 $1$。

当 ${\operatorname{mex}}(S) = 1$ 时，$S$ 无解

当 ${\operatorname{mex}}(S) = 2$ 时，$S= \{ 0,1,1 \} $ 和一个不等于 $2$ 和 $0$ 的值。方案数为 $n-1$。

当 ${\operatorname{mex}}(S) = 3$ 时，$S= \{0,1,2\} $ 和一个不等于 $3$、$1$ 和 $0$ 的值。方案数为 $n-2$。或 $S=\{0,1,1,1,2\}$，方案数为 $1$。

当 ${\operatorname{mex}}(S) = 4$ 时，$S= \{0,1,1,2,3\} $，方案数为 $1$。

当 ${\operatorname{mex}}(S) \ge 5$ 时，$S$ 无解。

对上述情况根据 $n$，$k$ 的大小进行分类讨论即可，时间复杂度为 $O(1)$。

# 代码


```cpp
#include <bits/stdc++.h>
using namespace std;
int t;
long long n,m,sum;
int main(){
	scanf("%d",&t);
	while(t--){
		scanf("%lld%lld",&n,&m);
		sum=0;
		if(m==2) sum++;//{1,1}
		if(m>3&&n>=1){//{0,1,1,任选}
			if(n<2) sum+=n;
			else sum+=n-1;
		} 
		if(m>=5&&n>=3) sum++;//{0,1,1,2,3}
		if(m>=5&&n>=2) sum++;//{0,1,1,1,2}
		if(m>3&&n>=2){//{0,1,2,任选}
			if(n<3) sum+=n-1;
			else sum+=n-2;
		} 
		printf("%lld\n",sum);
	}
	return 0;
}
```

---

## 作者：Binaerbaka (赞：0)

## 题目

求出满足下列条件的可重复元素数列个数。

1. 集合 $S$ 元素个数为 $k$。
2. 集合元素大小在 $0 \le S_i \le n$ 之间。
3. 集合所有元素相乘等于集合最小值。
4. 集合所有元素相加等于集合最小值加最大值加未出现的最小自然数。

## 分析

可以先从条件三下手，只有两种情况满足条件三。

- 情况一，集合内元素全为 $1$

- 情况二，集合内元素有一个为 $0$

再从第四条件下手。

当情况一时。

- 最小值等于最大值等于一，最小自然数为零，满足条件，但由于最大值最小值最少会相加两次，所以 $k = 1$ 无解。

- 当 $k = 2$ 时，有且仅有一个集合 $S = \left\{ 1,1 \right\}$ 满足。

可证明其他集合在情况一下不可能有解。

当情况二时。

- 条件四整体等价于除开最大值以外所有元素相加等于未出现最小自然数。

- 当 $\operatorname{mex}(S) = 1$ 时，元素内除最大值外相加为 $1$，但元素内又不包含 $1$，显然无解。

- 当 $\operatorname{mex}(S) = 2$ 时，可以发现集合中满足 $S = \left\{ 0,1,1,a \right\}$ 且 $a>2$ 是可行的，当然在集合内添加 $0$ 不影响整体。

- 当 $\operatorname{mex}(S) = 3$ 时，可以发现集合中满足 $S = \left\{ 0,1,2,a \right\}$ 且 $a>3$ 是可行的，或者满足 $S = \left\{ 0,1,2,1,1 \right\}$，别忘记添加两种可能性方案，记得讨论 $k$ 是否满足第二种情况。

- 当 $\operatorname{mex}(S) = 4$ 时，有且仅有 $S = \left\{ 0,1,1,2,3 \right\}$ 满足条件。

- 当 $\operatorname{mex}(S) \ge 5$ 时，集合内至少已出现的元素相加一定大于 $5$，所以无论如何都必定不存在。

然后把所有可能情况分别相加即可。

## STD
```cpp
#include<bits/stdc++.h>
#define int long long
#define debug cout<<"FK"
#define end return 0
using namespace std;
const int maxn=1e6+5;
const int inf=2147483647;
int t,n,k;
int cal(int x){return x>n?0:n-x+1;}
void sol(){
	cin>>n>>k;
	switch(k){
		case 1:
			cout<<0;
			break;
		case 2:
			cout<<1;
			break;
		case 3:
			cout<<0;
			break;
		case 4:
			cout<<(1+cal(3)+cal(4)+(n>=2));
			break;
		default:
			cout<<(1+cal(3)+cal(4)*(n>=2)+(n>=2)+(n>=2)+(n>=3)*(n>=2));
			break;
	}
	cout<<"\n";
	return ;
}
signed main(){
	ios::sync_with_stdio(false);
	cin.tie(nullptr),cout.tie(nullptr);
	cin>>t;
	while(t--){
		sol();
	}
	return 0;
}
```






---

