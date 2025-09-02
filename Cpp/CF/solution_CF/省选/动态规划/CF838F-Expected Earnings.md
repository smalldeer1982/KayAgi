# Expected Earnings

## 题目描述

You are playing a game with a bag of red and black balls. Initially, you are told that the bag has $ n $ balls total. In addition, you are also told that the bag has probability $ p_{i}/10^{6} $ of containing exactly $ i $ red balls.

You now would like to buy balls from this bag. You really like the color red, so red balls are worth a unit of $ 1 $ , while black balls are worth nothing. To buy a ball, if there are still balls in the bag, you pay a cost $ c $ with $ 0<=c<=1 $ , and draw a ball randomly from the bag. You can choose to stop buying at any point (and you can even choose to not buy anything at all).

Given that you buy optimally to maximize the expected profit (i.e. # red balls - cost needed to obtain them), print the maximum expected profit.

## 说明/提示

Here, there is equal probability for the bag to contain 0,1,2,3 red balls. Also, it costs 0.2 to draw a ball from the bag.

## 样例 #1

### 输入

```
3 200000
250000 250000 250000 250000
```

### 输出

```
0.9000000000
```

# 题解

## 作者：素质玩家孙1超 (赞：6)

~~这大概这题中文的第一篇题解~~

标签：期望，$\rm dp$。（做的人太少cf上都没标签）

题目大意：

有 $n$ 个球，包含黑球和红球，给出 $p_i (0 \leq i \leq n)$ 表示初始有 $i$ 个红球的概率 和 $c$ 取出一个球的花费。若取出红球可以获得 $1$ 的收益，那么最优策略下期望可以得到多少的收益。（$n \leq 10000$）。

---

在cf中，常数偏小的 $O(n^2)$ 的算法可以在 $\rm 250ms$ 不到跑完，更何况题目中开了 $\rm 2s$。

所以我们直接设 $dp_{i,j}$ 表示总共取了 $i$ 个球，已经取了 $j$ 个红球时以后的最大收益，那么答案为 $dp_{0,0}$ 且第一维可以滚存。

在这个局面下我们考虑策略（取或者不取），有如下的转移：

$$dp_{i,j}=\max(0,P_{i,j}\times(dp_{i+1,j+1}+1)+(1-P_{i,j})\times dp_{i+1,j} - c)$$

其中 $P_{i,j}$ 为在共取了 $i$ 个球，已经取了 $j$ 个红球时下一个球是红球的概率。



$$P_{i,j}=\sum_{k\leq j}^{n-i+j} \dfrac{P(\text{总共有 k 个红球 | 取 i 个球中有 j 个红球 })\times (k-j) }{n-i}$$

这个式子比较好懂，可以自行理解。其中 $P(A|B)$ 表示在发生 $B$ 的条件下 $A$ 发生的概率，那么根据贝叶斯公式有

$$P(A|B)=P(A) \frac{P(B|A)}{P(B)}$$


把分子上的 $P$ 展开就可以搞到一个 $O(n^3)$ 的算法了。

我们要获得更好的时间复杂度必须优化计算 $P_{i,j}$ 的过程。

这个 $\Sigma$ 看起来很坏，我们把它搞掉（本质上就是减少重复计算）。

我们发现，当 $i=n-1$ 时候 $k$ 只有 $j+1$ 和 $j$ 两种取法。

那么 $P_{n-1,j}=P(\text{总共有 j+1 个红球 | 取 n-1 个球中有 j 个红球})$

$=P(\text{总共有 j+1 个红球}) \dfrac{P(\text{取 n-1 个球中有 j 个红球 | 总共有 j+1 个红球})}{P(\text{取 n-1 个球中有 j 个红球})}$


$=\dfrac{P(\text{总共有 j+1 个红球})}{P(\text{取 n-1 个球中有 j 个红球})} \times \dfrac{j+1}{n}$

那如果 $i \not = n-1$  又如何？

根据上面所推可以得知 $P_{i,j}=\dfrac{P(\text{ i+1 个球中有 j+1 个红球})}{P(\text{ i 个球中有 j 个红球})} \times \dfrac{j+1}{i+1}$

这里应该已经可以看出做法了，设一个 $q_{i,j}$ 表示在 $i$ 个球中有 $j $ 个红球的概率，其中 $q_{n,i}=p_i$ 。

那么这个 $q_{i,j}$ 的转移就是 

$$q_{i,j}=\frac{j+1}{i+1}q_{i+1,j+1}+\frac{i+1-j}{i+1}q_{i+1,j}$$

最后滚掉 $q,dp$ 的第一位就好了。

---

核心代码：

```cpp
#define u (i&1)
scanf("%d%lf",&n,&c);c/=1e6;
for(int i=0;i<=n;i++)scanf("%lf",&q[n%2][i]),q[n%2][i]/=1e6;
for(int i=n-1;i>=0;i--)
for(int j=0;j<=i;j++){D p;
	//i总取了多少,j表示取了多少红球 
	q[u][j]=1.0*(j+1  )/(i+1)*q[u^1][j+1]+
			1.0*(i+1-j)/(i+1)*q[u^1][j  ];
	if(q[u][j]<1e-18) continue;//防止div0 
	p=q[u^1][j+1]*(j+1)/q[u][j]/(i+1);
	dp[u][j]=max(0.0,dp[u^1][j]*(1-p)+(dp[u^1][j+1]+1)*p-c);
}
printf("%.10f",dp[0][0]);

```






---

## 作者：不知名用户 (赞：2)

### 做法

显然这种期望最大化问题考虑逆推 DP。记 $f_{i,j}$ 表示取了 $i$ 个球，有 $j$ 个是红球的概率。显然如果我们知道了下一次取到红球的概率为 $p_{i,j}$，那么 $f_{i,j}=\max(0,(1-p_{i,j})f_{i+1,j}+p_{i,j}(f_{i+1,j+1}+1)-X$。下面讨论如何求解 $p_{i,j}$。

记 $R_{i,j}$ 表示取了 $i$ 个球，有 $j$ 个是红球的事件。

条件概率 $P(A|B)$ 表示在事件 $B$ 发生的前提下 $A$ 事件发生的概率。由定义有 $P(B)P(A|B)=P(AB)=P(A)P(B|A)$，$P(AB)$ 表示 $A,B$ 同时发生的概率。不懂的自己搜一下，这里不作展开。变形可得 $P(A|B)=\frac{P(A){P(B|A)}}{P(B)}$。

根据条件概率的定义显然 $p_{i,j}=P(R_{i+1,j+1}|R_{i,j})$。作上面的变形得 $p_{i,j}=\frac{P(R_{i+1,j+1})P(R_{i,j}|R_{i+1,j+1})}{P(R_{i,j})}$。由定义可得 $P(R_{i,j}|R_{i+1,j+1})$ 等价于第 $i+1$ 个球选了红球，由于红黑均匀可知 $P(R_{i,j}|R_{i+1,j+1})=\frac{j+1}{i+1}$。显然只用关心 $P(R_{i,j})$，记 $q_{i,j}=P(R_{i,j})$。

显然 $q_{n,i}=p_i$。可以逆推 $q$。显然 $q_{i,j}$ 只可能来自 $q_{i+1,j+1}$ 和 $q_{i+1,j}$，故有 $q_{i,j}=P(R_{i,j}R_{i+1,j})+P(R_{i,j}R_{i+1,j})=q_{i+1,j+1}P(R_{i,j}|R_{i+1,j+1})+q_{i+1,j}P(R_{i,j}|R_{i+1,j})$。$P(R_{i,j}|R_{i+1,j})$ 即最后一次选了黑球的概率，由于红黑是均匀的，$P(R_{i,j}|R_{i+1,j})=\frac{i+1-j}{i+1}$。

综上，$q_{i,j}=q_{i+1,j+1}\cdot\frac{j+1}{i+1}+q_{i+1,j}\cdot\frac{i+1-j}{i+1},p_{i,j}=\frac{q_{i+1,j+1}}{q_{i,j}}\cdot\frac{j+1}{i+1},f_{i,j}=\max(0,(1-p_{i,j})f_{i+1,j}+p_{i,j}(f_{i+1,j+1}+1)-X$。$p_{i,j}$ 要用的时候拿出来计算即可，不需要开数组。发现都是 $i$ 从大到小推所以可以滚动掉 $i$ 这一维。时间复杂度 $\Theta(n^2)$，空间复杂度 $\Theta(n)$。

### 代码

<https://codeforces.com/contest/838/submission/315706248>

```cpp
#include<bits/stdc++.h>
using namespace std;
using lf = double;
const int N = 10010;
lf f[N], F[N], q[N], Q[N];

void rd(lf &a){int b;scanf("%d",&b);a=1.0*b/1000000;}

int main()
{
	int n, i, j;
	lf s;
	scanf("%d", &n);
	rd(s);
	for(i=0;i<=n;i++) rd(q[i]);
	for(i=n-1;i>=0;i--)
	{
		for(j=0;j<=i+1;j++) F[j] = f[j], Q[j] = q[j];
		for(j=0;j<=i;j++) q[j] = Q[j+1] * (j + 1) / (i + 1) + Q[j] * (i + 1 - j) / (i + 1);
		for(j=0;j<=i;j++)
		{
			lf p = Q[j+1] / q[j] * (j + 1) / (i + 1);
			f[j] = max(0.0,F[j]*(1.0-p)+(F[j+1]+1)*p-s);
		}
	}
	printf("%.10f", f[0]);
	return 0;
}
```

#### 闲话

一直用 C++17 交 >=2000ms，结果换 C++20 390ms。

Fun fact：上文一共出现了 6 个“显然”。希望大家能理解条件概率的定义及可以作等价转换如 $P(R_{i,j}|R_{i+1,j+1})=\frac{j+1}{i+1}$。条件概率真有点抽象。

---

