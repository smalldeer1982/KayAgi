# Speedbreaker Counting (Medium Version)

## 题目描述

[DRG - Limbo](https://soundcloud.com/drg72711/limbo)

⠀



This is the medium version of the problem. In the three versions, the constraints on $ n $ and the time limit are different. You can make hacks only if all the versions of the problem are solved.

This is the statement of Problem D1B:

- There are $ n $ cities in a row, numbered $ 1, 2, \ldots, n $ left to right.
  - At time $ 1 $ , you conquer exactly one city, called the starting city.
  - At time $ 2, 3, \ldots, n $ , you can choose a city adjacent to the ones conquered so far and conquer it.
  
  You win if, for each $ i $ , you conquer city $ i $ at a time no later than $ a_i $ . A winning strategy may or may not exist, also depending on the starting city. How many starting cities allow you to win?

For each $ 0 \leq k \leq n $ , count the number of arrays of positive integers $ a_1, a_2, \ldots, a_n $ such that

- $ 1 \leq a_i \leq n $ for each $ 1 \leq i \leq n $ ;
- the answer to Problem D1B is $ k $ .

The answer can be very large, so you have to calculate it modulo a given prime $ p $ .

## 说明/提示

In the first test case,

- arrays with $ 1 $ good starting city: $ [1] $ .

In the second test case,

- arrays with $ 0 $ good starting cities: $ [1, 1] $ ;
- arrays with $ 1 $ good starting city: $ [1, 2] $ , $ [2, 1] $ ;
- arrays with $ 2 $ good starting cities: $ [2, 2] $ .

In the third test case,

- arrays with $ 0 $ good starting cities: $ [1, 1, 1] $ , $ [1, 1, 2] $ , $ [1, 1, 3] $ , $ [1, 2, 1] $ , $ [1, 2, 2] $ , $ [1, 3, 1] $ , $ [1, 3, 2] $ , $ [2, 1, 1] $ , $ [2, 1, 2] $ , $ [2, 2, 1] $ , $ [2, 2, 2] $ , $ [2, 3, 1] $ , $ [2, 3, 2] $ , $ [3, 1, 1] $ ;
- arrays with $ 1 $ good starting city: $ [1, 2, 3] $ , $ [1, 3, 3] $ , $ [2, 1, 3] $ , $ [3, 1, 2] $ , $ [3, 1, 3] $ , $ [3, 2, 1] $ , $ [3, 3, 1] $ ;
- arrays with $ 2 $ good starting cities: $ [2, 2, 3] $ , $ [2, 3, 3] $ , $ [3, 2, 2] $ , $ [3, 3, 2] $ ;
- arrays with $ 3 $ good starting cities: $ [3, 2, 3] $ , $ [3, 3, 3] $ .

## 样例 #1

### 输入

```
11
1 998244353
2 998244353
3 998244353
4 998244353
5 998244353
6 998244353
7 998244353
8 998244353
9 998244353
10 102275857
10 999662017```

### 输出

```
0 1 
1 2 1 
14 7 4 2 
183 34 19 16 4 
2624 209 112 120 48 12 
42605 1546 793 992 468 216 36 
785910 13327 6556 9190 4672 2880 864 144 
16382863 130922 61939 94992 50100 36960 14256 4608 576 
382823936 1441729 657784 1086596 583344 488700 216000 96480 23040 2880 
20300780 17572114 7751377 13641280 7376068 6810552 3269700 1785600 576000 144000 14400 
944100756 17572114 7751377 13641280 7376068 6810552 3269700 1785600 576000 144000 14400```

# 题解

## 作者：EuphoricStar (赞：1)

考虑如何解决 D1B。

发现我们可以使用这样的策略（称其为策略 1）：设当前扩展到的区间为 $[i, j]$，若区间右侧存在一个 $k$ 使得 $a_k = k - i + 1$（即若下一步不往右走那么这个点的限制就无法满足），就往右走；否则往左走。这样对于一个固定的 $a$ 和出发点，移动的序列是确定的，于是可以考虑对移动序列计数。

大眼观察或者打表可以发现**关键结论：合法的出发点一定是一段区间**。我们有更强的结论：**设 $I = \bigcap\limits_{i = 1}^n [i - a_i + 1, i + a_i - 1]$，那么合法的出发点集合要么是 $I$，要么是空集。**

证明大概就是，首先 $I$ 之外的点一定不合法，然后考虑使用这样一种策略（称其为策略 2）：设当前扩展到的区间为 $[i, j]$，若区间左侧存在一个 $k$ 使得 $a_k = j - k + 1$ 就往左走，若区间右侧存在一个 $k$ 使得 $a_k = k - i + 1$ 就往右走，若都不满足就往任意一个方向走。按照策略 2，在 $I$ 中任意一个点出发，都会先走完 $I$ 中的所有点，再走到其他点（走到 $I$ 的左端点或者右端点时一定可以往另一个方向走）。所以 $I$ 中的出发点，要么全部合法，要么全部不合法。

得到这个结论和移动的策略，计数就相对套路了。钦定一个合法区间 $[l, r]$，计算出 $[l, r]$ 都是合法出发点的方案数 $f_{l, r}$，最后做一个二维前缀和状物（容斥）即可算出每个区间 $[l, r]$ 恰好是合法出发点集合的方案数。

考虑钦定完合法区间后如何计数。直接按照策略 1 对移动序列计数。考虑区间 DP，设 $g_{i, j, 0/1}$ 表示当前扩展到的区间为 $[i, j]$，下一步是否被钦定往右走的移动方案数。有转移：

- $g_{i, j + 1, 1} \gets g_{i, j, 1} \times (n - (j - i + 2) + 1)$，转移系数的意义是 $a_{j + 1} \ge j - i + 2$。
- $g_{i, j + 1, 0} \gets g_{i, j, 1}$，表示 $a_{j + 1}$ 就是那个要求往右走的点，需要满足 $a_{j + 1} = j - i + 2$。
- $g_{i - 1, j, 0} \gets g_{i, j, 0} \times (n - (j - i + 2) + 1)$，转移系数的意义是 $a_{i - 1} \ge j - i + 2$。
- $g_{i - 1, j, 1} \gets g_{i, j, 0} \times (n - (j - i + 2) + 1)$，转移系数意义同上。

初值为 $g_{l, r, 0} = g_{l, r, 1} = 1$，表示钦定一开始扩展的区间就是 $[l, r]$（因为我们知道若 $[l, r]$ 是合法出发点区间那么一定可以先访问完 $[l, r]$ 中的所有点再访问其他点）。别忘了 $[l, r]$ 中 $a$ 的取值也需要确定。对于 $i \in [l, r]$，$a_i$ 需要 $\ge \max(i - l + 1, r - i + 1)$，所以 $f_{l, r} = g_{1, n, 0} \times \prod\limits_{i = l}^r (n - \max(i - l + 1, r - i + 1) + 1)$。

枚举 $[l, r]$ 再区间 DP，时间复杂度 $O(n^4)$，可以通过 Easy Version。

发现枚举 $[l, r]$ 再 DP 太浪费了。发现 DP 形式都相同，考虑使用**反推贡献系数**的 trick（这个 trick 在 [CF1810G](https://www.luogu.com.cn/problem/CF1810G) 也用到过）。更改 $g_{i, j, 0/1}$ 的定义，它表示原来 DP 数组的这一位对答案的贡献。初值为 $g_{1, n, 0} = 1$，转移倒过来即可。设 $h_i = \prod\limits_{j = 1}^i (n - \max(j, i - j + 1) + 1)$，那么 $f_{l, r} = (g_{l, r, 0} + g_{l, r, 1}) h_{r - l + 1}$。

时间复杂度 $O(n^2)$。

[$O(n^4)$ 代码](https://codeforces.com/problemset/submission/2018/286455722)

[$O(n^2)$ 代码](https://codeforces.com/problemset/submission/2018/286456124)

---

## 作者：larsr (赞：0)

感觉会了 B 就会 F 了。

性质 $1$：初始城市集合一定是一个区间。容易证。

性质 $2$：不管从哪个初始城市开始一定是先把初始城市集合遍历完。也容易证。

考虑 $ans_{l,r}$ 为初始城市集合包含 $[l,r]$ 的方案数，最后计算答案时差分一下即可。由于性质 $2$，所以一定是先把初始城市集合遍历完，那么 $a_{l\sim r}$ 的值和外部无关，可以预处理出 $a_{l\sim r}$ 的方案数为 $z_{r - l + 1}$，再考虑处理 $[l,r]$ 之外的 $a$。

考虑建立数组 $b$：若 $i<l$，那么 $b_i=\min(a_i,b_{i-1}-1)$，若 $i>r$，那么 $b_i=\min(a_i,b_{i+1}-1)$，若 $l\le i\le r$，那么 $b_i=1$。

会发现如果 $a_{l\sim r}$ 合法，数组 $b$ 和数组 $a$ 是等价的。数组 $b$ 合法，当且仅当 $\forall l^{'}<l,r<r^{'}$，满足 $\max_{l^{'} \le i\le r^{'}}b_i \le r^{'} - l^{'}+1$。

又可以通过 $b$ 反推出能变成 $b$ 的数组 $a$ 的方案数（除去 $[l,r]$）。应该很简单，不细说了。

那么可以列出状态 $f_{l,r,k,0/1,0/1}$ 代表 $b_{l\sim r}\le k$，$[l,r]$ 之外的 $b$ 大于 $k$，$b_{l-1}$ 是否等于 $k+1$，$b_{r+1}$ 是否等于 $k+1$， $[l,r]$ 之外的 $a$ 的方案数。然后 $ans_{l,r}=f_{l,r,r-l+1,0/1,0/1}z_{r-l+1}$。复杂度 $O(n^3)$。

[sub](https://codeforces.com/contest/2018/submission/303732188)

---

