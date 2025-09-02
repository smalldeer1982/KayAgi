# Little Artem and Random Variable

## 题目描述

Little Artyom decided to study probability theory. He found a book with a lot of nice exercises and now wants you to help him with one of them.

Consider two dices. When thrown each dice shows some integer from $ 1 $ to $ n $ inclusive. For each dice the probability of each outcome is given (of course, their sum is $ 1 $ ), and different dices may have different probability distributions.

We throw both dices simultaneously and then calculate values $ max(a,b) $ and $ min(a,b) $ , where $ a $ is equal to the outcome of the first dice, while $ b $ is equal to the outcome of the second dice. You don't know the probability distributions for particular values on each dice, but you know the probability distributions for $ max(a,b) $ and $ min(a,b) $ . That is, for each $ x $ from $ 1 $ to $ n $ you know the probability that $ max(a,b) $ would be equal to $ x $ and the probability that $ min(a,b) $ would be equal to $ x $ . Find any valid probability distribution for values on the dices. It's guaranteed that the input data is consistent, that is, at least one solution exists.

## 样例 #1

### 输入

```
2
0.25 0.75
0.75 0.25
```

### 输出

```
0.5 0.5 
0.5 0.5 
```

## 样例 #2

### 输入

```
3
0.125 0.25 0.625
0.625 0.25 0.125
```

### 输出

```
0.25 0.25 0.5 
0.5 0.25 0.25 
```

# 题解

## 作者：pigstd (赞：5)

前言：这个题超级没有素质，网上找到的题解都有一定的问题，或者根本没有说清楚。

题意：你有两个骰子，第一个骰子的数为 $x$ 的概率是 $a_x$，第二个骰子的数为 $x$ 的概率为 $b_x$，骰子的数字从 $1$ 到 $n$，设第一个骰子的数为 $a$，第二个骰子的数为 $b$。$p1_i$ 表示 $\max(a,b)=i$ 的几率，$p2_i$ 表示 $\min(a,b)=i$ 的几率。告诉你 $p1,p2$，求出序列 $a,b$。

这是一个构造题，考虑如果已知 $a$ 和 $b$，那么显然有：

$\displaystyle p1_i=(\sum_{j=1}^ia_i) \times (\sum_{j=1}^i b_i)-(\sum_{j=1}^{i-1}a_i) \times (\sum_{j=1}^{i-1} b_i)$

$\displaystyle p2_i = (\sum_{j=i}^n a_i) \times (\sum_{j=i}^n b_i)-(\sum_{j=i+1}^{n}a_i) \times (\sum_{j=i+1}^{n} b_i) = (1-\sum_{j=1}^{i-1}a_i) \times (1-\sum_{j=1}^{i-1} b_i)-(1-\sum_{j=1}^{i}a_i) \times (1-\sum_{j=1}^{i} b_i)$

注意到都是 $\sum$ 的形式，这个东西很有优化空间。设 $\displaystyle S1_i = \sum_{j=1}^i a_j,S2_i=\sum_{j=1}^i b_j$，那么显然算出 $S1,S2$ 就能得到 $a,b$ 了。把 $S1,S2$ 带入上式得：

$p1_i=S1_i\times S2_i - S1_{i-1}\times S2_{i-1},p2_i=(1-S1_{i-1})\times (1-S2_{i-1}) - (1-S1_i)\times (1-S2_i)$

发现这个东西长得很像差分的形式，很有优化空间：设 $ \displaystyle sp1_i =\sum_{j=1}^ip1_j,sp2_i = \sum_{j=1}^i p2_j$，带入上式得：

$sp1_i = S1_i \times S2_i,sp2_i = (1-S1_{i-1})\times (1-S2_{i-1})$。

那么有：

$sp2_{i+1}=(1-S1_i)\times (1-S2_i)=1-(S1_i+S2_i)+S1_i\times S2_i $

$S1_i+S2_i = sp1_i-sp2_{i+1}+1$。

结合以上内容可以得到：$\begin{cases} S1_i+S2_i = sp1_i-sp2_{i+1}+1 \\ S1_i \times S2_i = sp1_i \end{cases}$ 

解个方程就完事了。注意到有两个根，每次把小的给一边大的给一边就行。因为可能有略微的精度误差，求根的时候开根号的东西要和 $0$ 取 `max`。

```cpp
#include<bits/stdc++.h>
#define int long long
#define pb push_back
using namespace std;

inline int read()
{
    char c=getchar();int x=0;bool f=0;
    for(;!isdigit(c);c=getchar())f^=!(c^45);
    for(;isdigit(c);c=getchar())x=(x<<1)+(x<<3)+(c^48);
    if(f)x=-x;return x;
}

const int M=1e5+10;
int n;
double maxn[M],minn[M],sum1[M],sum2[M],p1[M],p2[M];

signed main()
{
	cin>>n;
	for (int i=1;i<=n;i++)cin>>maxn[i];
	for (int i=1;i<=n;i++)cin>>minn[i];
	for (int i=1;i<=n;i++)sum1[i]=maxn[i]+sum1[i-1];
	for (int i=n;i>=1;i--)sum2[i]=minn[i]+sum2[i+1];
	for (int i=1;i<=n;i++)
	{
		double x1=sum1[i],x2=sum1[i]-sum2[i+1]+1;
		double d=sqrt(max(x2*x2-4*x1,0.0));
		p1[i]=(x2-d)/2.0,p2[i]=(x2+d)/2.0;
	}
	for (int i=1;i<=n;i++)
		printf("%.8lf ",p1[i]-p1[i-1]);puts("");
	for (int i=1;i<=n;i++)
		printf("%.8lf ",p2[i]-p2[i-1]);puts("");
	return 0;
}
```

---

