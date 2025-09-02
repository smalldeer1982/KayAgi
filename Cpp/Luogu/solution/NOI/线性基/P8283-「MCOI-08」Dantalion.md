# 「MCOI-08」Dantalion

## 题目背景

And thus it is Tairitsu's turn to gain  the upper hand.

## 题目描述

给定一个长为 $n$（$1\le n\le 6\times 10^5$）的非负整数序列 $a_0,a_1,\dots,a_{n-1}$（$0\le a_i<2^{30}$）。

有 $q$ 个问询（$1\le q\le 10^6$）。

每次问询两个整数 $l,r$（$0\le l\le r<n$），有多少对整数 $x,y$ 满足：

 - $l\le x\le y\le r$；
 - $\forall i,j\in S\ :i\oplus j\in S$，其中 $S:=\{a_k\}_{k=x}^y$。
 
Tip: 本题总时限较大，故请减少无意义提交量（如高复杂度暴力或是直接提交所给尚需完善的代码等）。

## 说明/提示

#### 数据规模与约定

对于 $100\%$ 的数据，$1\leq n\le 6\times 10^5,1\le q\leq 10^6$，$0 \le a_i < 2^{30}$，$0 \le l \le r < n$。

对于 $100\%$ 的数据，输入合法。

- Subtask 1（5 pts,~~Tutorial~~）：$1\le n,q\le 10^2$。
- Subtask 2（7 pts,~~Tutorial~~）：$1\leq n,q\leq 10^3$
- Subtask 3（11 pts,~~PST 5.0~~）：$1\leq n,q\leq 10^4$。
- Subtask 4（17 pts,~~PRS 8.2~~）：$1\leq n,q\leq 10^5$。
- Subtask 5（61 pts,~~FTR 10.8~~）：$1\leq n\le 6\times 10^5,1\le q\leq 10^6$。

为什么要多个 $1$ 分呢，因为谱师打本曲时性了 $1$ Lost.

Idea: Powerless; Solution: ccz181078&noip&w33z; Code: w33z; Data: w33z

This problem was added on 2022.4.10. Thanks for their help.

The data was strengthened on 2022.4.27 by w33z.

2022.4.10 - 2022.5.4 : 25 days 1st kill (水军带你飞).

2022.4.10 - 2022.5.17 : 38 days 2nd kill (WhisperingSnowflakes).

2022.4.10 - 2022.6.9 : 61 days 3rd kill (Verdandi).

## 样例 #1

### 输入

```
5 10 2
0000000001000020000300004```

### 输出

```
4834712607666044912```

## 样例 #2

### 输入

```
20 100 16500242824326557842
0000500006000070000800000000010000200003000040000000001000020000300004000090000:0000;0000<0000=0000>```

### 输出

```
5449866856465492064```

# 题解

## 作者：w33z8kqrqk8zzzx33 (赞：2)

通过一系列转换问题变成：对于 $n<2^{21}$ 以及一个形如 $S=\{[A_i,B_i]\times i\}$ 的点集，如何用 $16n+o(\dots)$ 字节预处理出 $O(1)$ 统计 $S\cap[L,R]^2$。

而 $S$ 是一个差 $S_1-S_2$，$S_1=\{[1,B_i]\times i\}$, $S_2=\{[1,A_i-1]\times i\}$。对于 $S_1$ 可以算出 $B_i$ 前缀和以及 $h_L=\min \{i:B_i\ge L\}$ 得到 $S_1\cap[L,R]^2=\{[L,B_i]\times i,i\in[h_L,R]\}$ 的大小，$S_2$ 同理。

因为 $\max h\times \max\sum B<2^{64}$ 可以把所有信息压到一个 `ulong` 里面，每一个集合使用 $8n$ 字节预处理，总共使用 $16n$ 字节。

```cpp
long long solve(int l, int r) {
  long long c = 1ll * LOGN * (r - l + 1);
  if (l) {
    for (int b = 0; b < LOGN; b++) {
      int bo;
      bo = max(l, min(r + 1, (int)(maxL[l - 1][b]&1048575)));
      c += (maxL[r][b]>>20) - (maxL[bo - 1][b]>>20) + 1ll * (l - 1) * (bo - l);
      bo = max(l, min(r + 1, (int)(minL[l][b]&1048575)));
      c -= (minL[r][b]>>20) - (minL[bo - 1][b]>>20) + 1ll * l * (bo - l);
    }
  } else {
    for (int b = 0; b < LOGN; b++)
      c += (maxL[r][b]>>20) - (minL[r][b]>>20);
  }
  return c;
}
```

---

## 作者：EuphoricStar (赞：1)

一点也不卡常的小清新题。

考虑如何判定一个区间是好的。显然充要条件是，把所有数插入线性基后，设线性基元素个数为 $k$，那么区间内有 $2^k$ 种不同的数。

考虑预处理。扫描线枚举右端点 $i$，维护一个前缀线性基（[CF1100F 第一篇题解](https://www.luogu.com.cn/problem/solution/CF1100F)），那么将 $pos$ 数组排序后，对于每个 $k$，左端点在 $[pos_{k + 1} + 1, pos_k]$ 中的区间的线性基恰好有 $k$ 个元素（$pos$ 下标从 $1$ 开始，且认为 $pos_0 = i$）。如果我们能求出 $h_{i, k}$ 表示，$[1, i]$ 中每种数从右往左第一次出现的位置中的第 $2^k$ 大的值，那么对于一个 $(i, k)$，合法左端点区间就是 $[pos_{k + 1} + 1, h_{i, k}]$。

首先前缀线性基插入的时候 $pos$ 数组至多删除一个数、加入一个数，所以可以使用类似插入排序的方法。这部分复杂度为 $O(n \log V)$。

接下来的问题是求出 $h_{i, k}$。我们维护一个集合 $S$，里面的数是 $[1, i]$ 中每种数从右往左第一次出现的位置。每次右端点变化（$i - 1 \to i$）时，设 $a_i$ 上一次出现位置为 $x$，那么对 $S$ 的修改就是删除 $x$ 再加入 $i$。设集合中 $> x$ 的元素个数为 $c$，那么 $h_{i, \ast}$ 相较于 $h_{i - 1, \ast}$ 的变化是，$\forall j \in [0, \left\lfloor{\log c}\right\rfloor]$，$h_{i, j}$ 变为 $h_{i - 1, j}$ 在 $S$ 中的后继，其他的数不变。特别地，若 $[1, i]$ 不同的数的数量为 $2^k$ 且 $a_i$ 在 $[1, i]$ 中第一次出现，那么 $h_{i, k}$ 变为 $S$ 的最小值。可以用树状数组维护 $S$。这部分复杂度为 $O(n \log n)$。

这样我们能求出对于每个 $(i, k)$ 的合法左端点区间 $[L_{i, k}, R_{i, k}]$。

考虑查询。先写个暴力，枚举右端点 $i$，答案即为 $\sum\limits_{i = l}^r \sum\limits_{k = 0}^{\left\lfloor{\log n}\right\rfloor} \max(0, R_{i, k} - \max(L_{i, k}, l) + 1)$。

考虑优化。先枚举第二维 $k$。首先一个比较显然的性质是，$L_{i, k}$ 和 $R_{i, k}$ 是递增的。那么我们可以把 $[l, r]$ 所有区间分成右端点 $< l$、右端点 $\ge l$ 且左端点 $< l$ 和左端点 $\ge l$ 三部分。对于第一部分的区间无贡献；对于第二部分的区间，贡献为 $\sum R - l + 1$；对于第三部分的区间，贡献为 $\sum R - L + 1$。我们可以预处理出，对于每个 $(x, k)$ 第一个 $L_{i, k} \ge x$ 的 $i$ 和第一个 $R_{i, k} \ge x$ 的 $i$，还有 $L_{i, k}, R_{i, k}$ 的前缀和，那么就可以 $O(1)$ 对每个 $k$ 回答询问。这部分复杂度为 $O(q \log n)$。

总时间复杂度为 $O(n \log V + (n + q) \log n)$。至于空间，我们只需要开 $2$ 个值域为 $O(n)$、大小为 $n \times \log n$ 的数组和 $2$ 个值域为 $O(n^2)$、大小为 $n \times \log n$ 的数组，以及 $O(1)$ 个大小为 $n$ 的数组，瓶颈在于前者。可以把它们压成 $2$ 个 `unsigned long long` 数组，这样空间大约为 200MB。

代码可以在 QOJ 上看。

---

