# 「PEOI Rd1」k 叉堆（heap）

## 题目背景

**数据范围较赛时加强**。

- 2023.04.25：发现 1.50s 时限过于卡常，扩大到 2.00s。

## 题目描述

给定一个 $1 \sim n$ 的序列，每个位置 $i$ 有 $k$ 个参数 $a_{i,1},a_{i,2},\dots,a_{i,k}$。已知这个序列是一个按照大根堆的 bfs 序得到的序列。

bfs 序，即按照下图中**红色数字编号的顺序**：

![](https://cdn.luogu.com.cn/upload/image_hosting/73ot5iox.png)

一个大根堆满足条件，当且仅当所有子节点的**所有** $k$ 个权值都小于等于父节点，即 $\forall u\in[1,n],\forall v\in son(u),\forall j \in [1,k],a_{v,j} \leq a_{u,j}$。

假设这个大根堆是**完全 $m$ 叉树**，求所有 $m \in [1,n-1]$，使得这个 $m$ 叉堆**满足条件**的 $m$ 的取值。

## 说明/提示

#### 样例解释

样例 $1$ 中，$1,2$ 叉堆显然都符合条件。

---

#### 数据范围

|子任务编号|$n \leq$|分值|
|:-:|:-:|:-:|
|$1$|$10^3$|$20$|
|$2$|$5 \times 10^4$|$20$|
|$3$|$2 \times 10^5$|$60$|

对于 $100\%$ 的数据，保证 $1 \leq n \leq 2 \times 10^5$，$1 \leq k \leq 8$，$-10^7 \leq a_{i,j} \leq 10^7$。

## 样例 #1

### 输入

```
3 2
1 1 1
1 1 1```

### 输出

```
2
1 2```

## 样例 #2

### 输入

```
6 1
2 1 2 1 1 2```

### 输出

```
2
2 5```

# 题解

## 作者：AtomAlpaca (赞：2)

## 题意

[link](https://www.luogu.com.cn/problem/P9224)

## 题解

提供一个不需要根号分治的做法。

首先考虑 $k$ 叉堆的情况下，每个点的儿子的区间。考虑这样构造 $k$ 叉堆：维护一个没被成为儿子的节点队列，从小到大考虑每个点，将队列中前 $k$ 个树拎出来成为它的儿子。

那么对于节点 $n$，它前面有 $(n - 1)\times k$ 个节点被分配了，而 $1$ 节点不能被分配为其它节点的儿子，所以节点 $n$ 的儿子区间是 $[k(x - 1) + 2, kx + 1]$ 这一段。于是我们考虑对每一维信息维护一个 st 表，从小到大枚举叉数，检查每个节点的儿子区间内是否有比自己大的就可以了。

复杂度是 $O(k(\sum_{i=1}^{n-1}{\frac{n}{i}})) = O(knH_n)$，其中 $H$ 是调和数。考虑到调和数增长很慢，几乎是 $\log$ 级别的，这个做法应该是比出题人题解更优的。

## 代码
```c++
#include <bits/stdc++.h>

const int MAX = 2e5 + 5;

int n, k;
int a[MAX], st[21][MAX];
std::bitset <MAX> ans;

int mx(int l, int r)
{
  r = std::min(r, n); int lg = log2(r - l + 1);
  return std::max(st[lg][l], st[lg][r - (1 << lg) + 1]);
}

void solve()
{
  for (int i = 1; i <= n; ++i) { scanf("%d", &a[i]); st[0][i] = a[i]; }
  for (int i = 1; (1 << i) <= n; ++i)
  {
    for (int j = 1; j + (1 << i) - 1 <= n; ++j)
    {
      st[i][j] = std::max(st[i - 1][j], st[i - 1][j + (1 << (i - 1))]);
    }
  }
  for (int k = 1; k < n; ++k)
  {
    if (!ans[k]) { continue; }
    for (int i = 1; k * (i - 1) + 2 <= n; ++i)
    {
      if (mx(k * (i - 1) + 2, k * i + 1) > a[i]) { ans[k] = false; break; }
    }
  }
}

int main()
{
  scanf("%d%d", &n, &k);
  for (int i = 1; i <  n; ++i) { ans[i] = true; }
  for (int i = 1; i <= k; ++i) { solve(); }
  printf("%ld\n", ans.count());
  for (int i = 1; i <  n; ++i) { if (ans[i]) { printf("%d ", i); } }
}

```

---

## 作者：E1_de5truct0r (赞：0)

## 前言

出题人来一篇。

这道题主要是考查根号分治。赛时 std 复杂度假了没查出来，是我的锅/kk。现在数据加强了之后应该是卡掉了暴力和多一只 $\log$ 的做法。

## 正文

### Subtask 1

直接枚举 $k$，然后把那个堆建出来，暴力检查即可。

复杂度 $O(n^2 k)$。

### Subtask 2&3

考虑进行根号分治。

1. 对于叉数 $\leq \lceil \sqrt{n} \rceil$ 的，可以暴力的做，一共 $\sqrt{n}$ 种 $k$ 的取值，每次 $O(nk)$ 检查，则复杂度为 $O(nk \sqrt{n})$。

2. 对于叉数 $\gt \lceil \sqrt{n} \rceil$ 的，容易发现这个堆建出来只有两层。

	所以我们考虑对所有有儿子的点，对他的儿子进行检查。容易发现最多有 $\dfrac{n-\sqrt{n}}{\sqrt{n}}=\sqrt{n}$ 个点会被检查到。

	考虑怎么检查呢？我们只需要让儿子的参数的最大值小于等于当前节点的值就可以了。由于 bfs 序中，一个点的儿子的 bfs 序和下标的相对关系一样，是连续的，所以按照 bfs 序维护 $k$ 个 RMQ 即可。
    
这里就体现出 ST 表和线段树的区别了。

- 线段树只能做到 $O(\log n)$ 查询，复杂度为 $O(nk\sqrt{n}\log{n})$，只能通过 Subtask 2；

- ST 表预处理 $O(nk \log n)$，查询 $O(1)$，可以做到 $O(nk\sqrt{n})$，能够拿到满分。

---

