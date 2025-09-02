# Go Learn! (Easy Version)

## 题目描述

本题的简单版与困难版的区别在于 $n$ 和 $n$ 的总和的限制。在本题中，$n \leq 3000$，且所有 $n$ 的总和不超过 $10^4$。只有在两种版本都通过后，才能进行 hack。

让我们看看 Bessie 是如何管理她的财务的。她似乎陷入了困境！幸运的是，她正在申请 Moogle 的工作来解决这个问题。Moogle 的面试需要对晦涩算法和复杂数据结构有深入了解，但 Bessie 从一位 LGM 那里得到了确切的学习建议。

Bessie 写了如下代码，用于在一个可能无序的数组 $[a_1, a_2, \ldots, a_n]$ 中二分查找某个元素 $k$：

```
let l = 1
let h = n

while l < h:
  let m = floor((l + h) / 2)

  if a[m] < k:
    l = m + 1
  else:
    h = m

return l
```

Bessie 将她的代码提交给 Farmer John 的问题，并进行了 $m$（$1 \leq m \leq n$）组测试。第 $i$ 组测试为 $(x_i, k_i)$（$1 \leq x, k \leq n$）。保证所有 $x_i$ 互不相同，所有 $k_i$ 也互不相同。

第 $i$ 组测试是正确的，当且仅当满足以下条件：

1. 数组的第 $x_i$ 个元素为 $k_i$。
2. 如果 Bessie 按上述代码对 $k_i$ 进行二分查找，返回值为 $x_i$。

可能无法让所有 $m$ 个测试在同一个数组上都正确，因此 Farmer John 允许移除其中一些测试，使得 Bessie 能够通过。设 $r$ 为需要移除的最少测试数，使得存在一个数组 $[a_1, a_2, \ldots, a_n]$，$1 \leq a_i \leq n$，使得剩下的所有测试都正确。

除了求出 $r$，Farmer John 还希望你统计有多少个数组 $[a_1, a_2, \ldots, a_n]$，$1 \leq a_i \leq n$，存在一种移除恰好 $r$ 个测试的方法，使得剩下的测试都正确。由于答案可能很大，请对 $998\,244\,353$ 取模。

## 说明/提示

考虑第一个样例。

在第一个测试用例中，数组 $[1,2,2,3,4]$ 能满足所有 $m$ 个测试，因此 Bessie 需要移除的测试数最少为 $0$。注意，这也是唯一能满足所有 $m$ 个测试的数组。

在第二个测试用例中，最少需要移除 $1$ 个测试。Bessie 只能移除测试 $(2,5)$。如果 Bessie 移除了测试 $(2,5)$，则能满足剩下 $m-1$ 个测试的数组有 $[2,2,3,1,4]$、$[2,2,3,2,4]$、$[2,2,3,3,4]$。

由 ChatGPT 4.1 翻译

## 样例 #1

### 输入

```
2
5 4
1 1
2 2
4 3
5 4
5 4
5 4
2 5
1 2
3 3```

### 输出

```
0 1
1 3```

## 样例 #2

### 输入

```
2
6 6
1 3
2 5
3 1
4 2
5 4
6 6
30 8
19 22
6 12
12 1
28 27
3 4
14 25
29 14
11 15```

### 输出

```
3 78
3 839271911```

# 题解

## 作者：Milmon (赞：5)

## Statement

给定 $n$，$a$ 是一个未知的长度为 $n$ 的值域为 $[1, n]$ 的整数数列。

有 $m$ 个测试点，第 $i$ 个测试点用 $x_i, k_i$ 表示。能通过某个测试点，当且仅当 $a_{x_i} = k_i$，并且在 $a$ 上二分查找 $k_i$ 得到的位置是 $x_i$。

请求出：

- 至少要删除多少个测试点才可以使得存在一个数列 $a$ 能够通过所有测试点，记为 $P$。
- 有多少个不同的数列 $a$ 满足存在一种删除 $P$ 个测试点的方案使得 $a$ 能够通过所有测试点。答案对 $998244353$ 取模。

数据范围：数据组数 $T \leq 10^4$，$1 \leq m \leq n \leq 3 \times 10^3$，$\sum n \leq 10^4$，$1 \leq x_i, k_i \leq n$ 并且所有 $k_i$ 互不相同，所有 $x_i$ 也互不相同。

## Solution

首先将所有测试点按照 $x_i$ 排序。下面给出一个结论：能通过所有测试点的必要条件是保留的测试点的 $k_i$ 递增。这是因为考虑两个测试点 $i < j$ 满足 $x_i < x_j$，由于一定存在一个 $l, r$ 得出的分界点 $m$ 满足 $l \leq x_i \leq m$ 并且 $m < x_j \leq r$，根据二分条件得出 $k_i \leq a_m < k_j$，故 $k_i < k_j$。

若对于一个数列 $a$ 存在两种删除 $P$ 个测试点的方案，那么该数列至少同时满足 $m - P + 1$ 个测试点，与 $P$ 的最优性矛盾。所以对于任意数列 $a$ 至多存在一种删除 $P$ 个测试点的方案。

考虑 dp 计算最后一个测试点为某个测试点时最多选择的测试点数量以及合法数列的方案数。

记当前测试点为 $i$，转移考虑枚举上一个测试点 $j < i$，需要满足 $k_j < k_i$，转移的系数即为 $x_j + 1$ 和 $x_i - 1$ 之间的位置上填数的方案数。设 $S_i$ 表示二分找到 $i$ 所需检验的所有位置，则 $|S_i| = \Theta(\log n)$。枚举 $S_i, S_j$ 中所有在区间内的位置计算方案数，剩下的位置可以任意填数。这样单次转移时间复杂度 $O(\log n)$。

统计答案只需要枚举最后一个选择的测试点并计算最后一段区间的填数方案数即可。需要注意的一点是，要忽略所有 $k_i = 1$ 但是 $x_i \neq 1$ 的测试点，因为当 $k = 1$ 时总是找到第一个位置。总时间复杂度 $O(m^2 \log n)$，可以通过 Easy Version。

Hard Version 的做法以及代码见 [此处](https://www.luogu.com.cn/article/xg7z6hkp)。

## Solution (English)

First, sort all the test points according to $x_i$. The following conclusion is given: a necessary condition to pass through all test points is that the retained test points' $k_i$ are in increasing order. This is because considering two test points $i < j$ satisfying $x_i < x_j$, there must exist a boundary point $m$ derived from some $l, r$ that satisfies $l \leq x_i \leq m$ and $m < x_j \leq r$. According to the binary division condition, we conclude $k_i \leq a_m < k_j$, hence $k_i < k_j$.

If there exist two deletion schemes for $P$ test points in a sequence $a$, then the sequence must satisfy at least $m - P + 1$ test points, contradicting the optimality of $P$. Therefore, for any sequence $a$, there exists at most one scheme to delete $P$ test points.

Consider using dynamic programming to calculate the maximum number of test points that can be selected when the last test point is a certain test point, as well as the number of valid sequences.

Let the current test point be $i$. For the transition, consider enumerating the previous test point $j < i$, which needs to satisfy $k_j < k_i$. The transition coefficient is the number of ways to fill numbers between $x_j + 1$ and $x_i - 1$. Let $S_i$ represent all positions that need to be checked for finding $i$ using binary search, then $|S_i| = \Theta(\log n)$. Enumerating all positions within $S_i, S_j$ to calculate the number of ways, while the remaining positions can be filled freely. Thus, the time complexity for a single transition is $O(\log n)$.

To count the answer, we only need to enumerate the last selected test point and calculate the number of filling ways for the last segment of the interval. It is important to note that all test points with $k_i = 1$ but $x_i \neq 1$ should be ignored, as when $k = 1$, we always find the first position. The total time complexity is $O(m^2 \log n)$, which can be accepted by the Easy Version.

The methods and code for the Hard Version can be found [here](https://www.luogu.com.cn/article/xg7z6hkp).

---

