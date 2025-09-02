# Lihmuf Balling

## 题目描述

在一家工厂（Lihmuf Sorting）工作后，Lihmuf 想和他的好朋友 Pak Chanek 玩一个游戏。有$N$个盒子，编号从$1$到$N$。

第$i$个盒子里有$i$个球。Pak Chanek 和 Lihmuf 将用这些盒子玩一个游戏。从$1$到$N$共有 $N$个回合。在每一轮中，Pak Chanek 选择一个盒子并从该盒子中取出所有的球，然后 Lihmuf 对他选择的一个盒子做同样的事情（有可能选择的两个盒子是相同的）。

给定一个整数$M$。在游戏开始之前，Lihmuf 必须选择一个满足 $1 \leq K \leq M$的整数 $K$。众所周知，在第$j$个回合中，Pak Chanek 会选择第$j$个方格，而 Lihmuf 会选择第$y$个方格，即$y=((j \times K - 1) \bmod N) + 1$。帮助 Lihmuf 选择正确的$K$值，这样他就能得到尽可能多的球！如果有多个可能的$K$值会导致总球数最大，请找出最小的$K$值。

请记住，每个盒子可以被选择多次，但在第一次选择后，盒子就会变成空的。

## 说明/提示

在第一个例子中，如果 Lihmuf 选择$K=1$，对局过程如下：

1.  Pak Chanek 选择第$1$个盒子，得到$1$个球，然后 Lihmuf 选择第$1$个盒子，得到$0$个球。
2.  Pak Chanek 选择第$2$个盒子，得到$2$个球，然后 Lihmuf 选择第$2$个盒子，得到$0$个球。
3.  Pak Chanek 选择第$3$个盒子，得到$3$个球，然后 Lihmuf 选择第$3$个盒子，得到$0$个球。

Lihmuf 总共得到 $0+0+0=0$个球。

由于他只能选择$K=1$个球，所以 Lihmuf 能得到的最大球数是$0$个。因此，$K=1$是导致总球数最大的$K$的最小可能值。

在第二个例子中，如果 Lihmuf 选择$K=3$，对局将如下进行：

1.  Pak Chanek 选择第$1$个盒子，得到$1$个球，然后 Lihmuf 选择第$3$个盒子，得到$3$个球。
2.  Pak Chanek 选择第$2$个盒子，得到$2$个球，然后 Lihmuf 选择第$1$个盒子，得到$0$个球。
3.  Pak Chanek 选择第$3$个盒子，得到$0$个球，然后 Lihmuf 选择第$4$个盒子，得到$4$个球。
4.  Pak Chanek 选择第$4$个盒子，得到$0$个球，然后 Lihmuf 选择第$2$个盒子，得到$0$个球。
5.  Pak Chanek选择第$5$个盒子，得到$5$个球，然后Lihmuf选择第$5$个盒子，得到$0$个球。

Lihmuf 总共得到 $3+0+4+0+0=7$个球。

由此可以得出，$7$是 Lihmuf 能得到的最大总球数。导致$7$总球数的$K$的可能值是$3$和$4$。因此，$K=3$是导致最大总球数的$K$的最小可能值。



------------

by quchenming

## 样例 #1

### 输入

```
3 1```

### 输出

```
1```

## 样例 #2

### 输入

```
5 4```

### 输出

```
3```

# 题解

## 作者：Register_int (赞：5)

先把所有盒子编号 $-1$。容易发现，当小 L 拿 $jk\bmod n$ 号箱子的球时，$0\sim j$ 的盒子都已经没球了。所以拿到球的情况只可能是 $jk\bmod n>j$。显然小 L 拿球有循环节 $\gcd(k,n)$，所以只能对前 $t=n/\gcd(k,n)$ 种情况求和。那么答案为：

$$
\begin{aligned}
&\sum^t_j[jk\bmod n>j](j+1)\\
=&\sum^t_j[jk-\left\lfloor\dfrac{jk}n\right\rfloor n>j](j+1)\\
\end{aligned}
$$

考虑到这一范围内，不同的 $\left\lfloor\dfrac{jk}n\right\rfloor$ 实际上最多 $k+1$ 个，所以可以直接枚举这个的值来计算。里层解决，外层枚举 $k$ 计算最优方案即可，时间复杂度 $O(m^2)$。

# AC 代码

```cpp
#include <bits/stdc++.h>

using namespace std;

typedef long long ll;

const int MAXN = 2e3 + 10;

inline 
ll calc(ll n, ll t, ll k) {
	ll ans = 0, l, r;
	for (int i = 0; i <= k; i++) {
		l = max((n * i + k) / k, (n * i + k - 1) / (k - 1)), r = min(n * (i + 1) / k, t);
		if (l <= r) ans += (r - l + 1) * (l + r) / 2 * k - (r - l + 1) * i * n;
	}
	return ans;
}

int n, m, p = 1; ll ans, x;

int main() {
	scanf("%d%d", &n, &m);
	for (int k = 2; k <= m; k++) {
		x = calc(n, n / __gcd(n, k), k);
		if (x > ans) ans = x, p = k;
	}
	printf("%d", p);
}
```

---

