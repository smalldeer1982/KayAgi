---
title: "【MX-S1-T3】电动力学"
layout: "post"
diff: 省选/NOI-
pid: P10674
tag: ['动态规划 DP', '数学', 'O2优化', '树形 DP', '双连通分量', '组合数学', '圆方树', '梦熊比赛']
---
# 【MX-S1-T3】电动力学
## 题目背景

原题链接：<https://oier.team/problems/S1C>。
## 题目描述

给定一张包含 $n$ 个点 $m$ 条边的简单无向连通图，点的编号为 $1\sim n$。

你需要求出有多少集合对 $S,T\sube \{1,2,\dots,n\}$，满足对于任意的 $i\in S$，要么 $i$ 也 $\in T$，要么存在 $x,y\in T$（$x\neq y$），满足存在一条从 $x$ 到 $y$ 的简单路径经过 $i$。

注意，集合对 $S,T$ 可以为空集。

输出答案对 $998244353$ 取模后的结果。

## 输入格式

第一行两个正整数 $n,m$。

接下来 $m$ 行，每行两个正整数 $u_i,v_i$，描述图上的一条边。保证图连通，无自环、重边。
## 输出格式

共一行一个整数，表示满足题目条件的集合对 $S,T$ 的数量对 $998244353$ 取模后的结果。
## 样例

### 样例输入 #1
```
2 1
1 2
```
### 样例输出 #1
```
9
```
### 样例输入 #2
```
9 10
8 3
6 8
8 5
1 6
6 2
4 6
8 2
1 7
9 6
5 3
```
### 样例输出 #2
```
80995
```
### 样例输入 #3
```
20 36
4 7
2 13
18 11
6 14
4 20
5 4
1 9
19 4
6 8
11 15
4 11
4 18
16 9
16 4
18 15
3 18
4 6
5 7
20 6
20 8
8 14
19 13
12 9
4 8
4 15
20 14
3 10
12 1
17 16
13 4
4 14
10 18
4 2
16 12
19 2
1 16
```
### 样例输出 #3
```
211240350
```
## 提示

__【样例解释 1】__

所有合法的集合 $S,T$ 为：

1. $S=\{\},T=\{\}$。
2. $S=\{\},T=\{1\}$。
3. $S=\{\},T=\{2\}$。
4. $S=\{\},T=\{1,2\}$。
5. $S=\{1\},T=\{1\}$。
6. $S=\{1\},T=\{1,2\}$。
7. $S=\{2\},T=\{2\}$。
8. $S=\{2\},T=\{1,2\}$。
9. $S=\{1,2\},T=\{1,2\}$。 

__【数据范围】__

__本题使用子任务捆绑测试。__

对于 $100\%$ 的数据，$2\le n\le 5\times 10^5$，$n-1\le m\le 10^6$，$1\le u_i,v_i\le n$。保证图连通，无自环、重边。

| 子任务编号 | $n\le $        | $m\le $            | 特殊性质        | 分值 |
| ---------- | -------------- | ------------------ | --------------- | ---- |
| $1$        | $10$           | $\frac{n(n-1)}{2}$ | 无              | $10$ |
| $2$        | $20$           | $\frac{n(n-1)}{2}$ | 无              | $10$ |
| $3$        | $5\times 10^5$ | $n-1$              | $u_i=i,v_i=i+1$ | $10$ |
| $4$        | $5\times 10^5$ | $n-1$              | 无              | $20$ |
| $5$        | $5\times 10^5$ | $n$                | 无              | $20$ |
| $6$        | $5\times 10^5$ | $10^6$             | 无              | $30$ |



---

---
title: "[HAOI2018] 苹果树"
layout: "post"
diff: 省选/NOI-
pid: P4492
tag: ['2018', '河南', '各省省选', 'O2优化', '树形 DP', '双连通分量', '概率论']
---
# [HAOI2018] 苹果树
## 题目背景

HAOI2018 Round2 第一题
## 题目描述

小 C 在自己家的花园里种了一棵苹果树, 树上每个结点都有恰好两个分支. 经过细心的观察, 小 C 发现每一天这棵树都会生长出一个新的结点.

第一天的时候, 果树会长出一个根结点, 以后每一天, 果树会随机选择一个当前树中没有长出过结点 的分支, 然后在这个分支上长出一个新结点, 新结点与分支所属的结点之间连接上一条边.

小 C 定义一棵果树的不便度为树上两两结点之间的距离之和, 两个结点之间 的距离定义为从一个点走到另一个点的路径经过的边数.

现在他非常好奇, 如果 $N$ 天之后小 G 来他家摘苹果, 这个不便度的期望 $E$ 是多少. 但是小 C 讨厌分数, 所以他只想知道 $E \times N !$ 对 $P$ 取模的结果, 可以证明这是一个整数.
## 输入格式

从标准输入中读入数据. 一行两个整数 $N$, $P$ .
## 输出格式

输出到标准输出中. 输出一个整数表示答案．
## 样例

### 样例输入 #1
```
3 610745795
```
### 样例输出 #1
```
24
```
### 样例输入 #2
```
305 1000000007
```
### 样例输出 #2
```
865018107
```
## 提示

![Explanation](https://cdn.luogu.com.cn/upload/pic/18067.png)

以上是所有 $N = 3$ 时可能的苹果树形态, 其中编号表示这个结点是第几天生
长出来的, 显然每种情况两两结点的距离均为 $4$ .

### 数据范围与约定
| 测试点编号   | $N$  | $P$  |
| :--------: | :--: | :--: |
| $1$ |  $\le 10$    |  $\le 10^9 + 7$    |
| $2$ |  $\le 10$    |   $\le 10^9 + 7$    |
| $3$ |  $\le 500$    |  $\le 10^9 + 7$     |
| $4$ |  $\le 500$    |   $\le 10^9 + 7$    |
| $5$ |  $\le 500$    |   $\le 10^9 + 7$    |
| $6$ |  $\le 2000$    |   $= 10^9 + 7$    |
| $7$ |  $\le 2000$    |   $= 10^9 + 7$    |
| $8$ |  $\le 2000$    |   $\le 10^9 + 7$    |
| $9$ |  $\le 2000$    |   $\le 10^9 + 7$    |
| $10$ | $\le 2000$     |    $\le 10^9 + 7$   |




---

---
title: "[SDOI2018] 战略游戏"
layout: "post"
diff: 省选/NOI-
pid: P4606
tag: ['2018', '各省省选', '山东', 'O2优化', '深度优先搜索 DFS', '双连通分量', '虚树', '圆方树']
---
# [SDOI2018] 战略游戏
## 题目描述

省选临近，放飞自我的小 Q 无心刷题，于是怂恿小 C 和他一起颓废，玩起了一款战略游戏。

这款战略游戏的地图由 $n$ 个城市以及 $m$ 条连接这些城市的双向道路构成，并且从任意一个城市出发总能沿着道路走到任意其他城市。

现在小 C 已经占领了其中至少两个城市，小 Q 可以摧毁一个小 C 没占领的城市，同时摧毁所有连接这个城市的道路。只要在摧毁这个城市之后能够找到某两个小 C 占领的城市 $u$ 和 $v$，使得从 $u$ 出发沿着道路无论如何都不能走到 $v$，那么小 Q 就能赢下这一局游戏。

小 Q 和小 C 一共进行了 $q$ 局游戏，每一局游戏会给出小 C 占领的城市集合 $S$，你需要帮小 Q 数出有多少个城市在他摧毁之后能够让他赢下这一局游戏。
## 输入格式

第一行包含一个正整数 $T$，表示测试数据的组数。

对于每组测试数据：

第一行是两个整数 $n$ 和 $m$ ，表示地图的城市数和道路数。

接下来 $m$ 行，每行包含两个整数 $u$ 和 $v (1 \le u < v \le n)$，表示第 $u$ 个城市和第 $v$ 个城市之间有一条道路，同一对城市之间可能有多条道路连接。


第 $m + 1$ 是一个整数 $q$，表示游戏的局数，

接下来 $q$ 行，每行先给出一个整数 $|S| (2 \le |S| \le n)$，表示小 C 占领的城市数量，然后给出 $|S|$ 个整数 $(1 \le S_1 < S_2 < \cdots < S_{|S|} ≤ n)$，表示小 C 占领的城市。
## 输出格式

对于每一局游戏，输出一行，包含一个整数，表示这一局游戏中有多少个城市在小 Q 摧毁之后能够让他赢下这一局游戏。
## 样例

### 样例输入 #1
```
2
7 6
1 2
1 3
2 4
2 5
3 6
3 7
3
2 1 2
3 2 3 4
4 4 5 6 7
6 6
1 2
1 3
2 3
1 4
2 5
3 6
4
3 1 2 3
3 1 2 6
3 1 5 6
3 4 5 6

```
### 样例输出 #1
```
0
1
3
0
1
2
3
```
## 提示

- $1 \le T \le 10$；
- $2 \le n \le 10^5$ 且 $n - 1 \le m \le 2\times 10 ^ 5$；
- $1 \le q \le 10^5$；
- 对于每组测试数据，有 $\sum|S| \le 2 \times 10^5$。

### Subtasks

- 子任务 1 (30 分)：对于每组测试数据，满足 $\sum|S| \le 20$；
- 子任务 2 (45 分)：对于每一次询问，满足 $|S| = 2$；
- 子任务 3 (25 分)：没有任何附加的限制。



---

---
title: "[APIO2018] 铁人两项"
layout: "post"
diff: 省选/NOI-
pid: P4630
tag: ['2018', 'APIO', '双连通分量']
---
# [APIO2018] 铁人两项
## 题目描述

比特镇的路网由 $m$ 条双向道路连接的 $n$ 个交叉路口组成。

最近，比特镇获得了一场铁人两项锦标赛的主办权。这场比赛共有两段赛程：选手先完成一段长跑赛程，然后骑自行车完成第二段赛程。

比赛的路线要按照如下方法规划：

1. 先选择三个两两互不相同的路口 $s$、$c$ 和 $f$，分别作为比赛的起点、切换点（运动员在长跑到达这个点后，骑自行车前往终点）、终点。
2. 选择一条从 $s$ 出发，经过 $c$ 最终到达 $f$ 的路径。考虑到安全因素，选择的路径经过同一个点至多一次。

在规划路径之前，镇长想请你帮忙计算，总共有多少种不同的选取 $s$、$c$ 和 $f$ 的方案，使得在第 $2$ 步中至少能设计出一条满足要求的路径。

## 输入格式

第一行包含两个整数 $n$ 和 $m$，分别表示交叉路口和双向道路的数量。

接下来 $m$ 行，每行两个整数 $v_i, u_i$。表示存在一条双向道路连接交叉路口 $v_i, u_i$（$1 \le v_i, u_i \le n$，$v_i \neq u_i$）。

保证任意两个交叉路口之间，至多被一条双向道路直接连接。
## 输出格式

输出一行，包括一个整数，表示能满足要求的不同的选取 $s$、$c$ 和 $f$ 的方案数。
## 样例

### 样例输入 #1
```
4 3
1 2
2 3
3 4

```
### 样例输出 #1
```
8

```
### 样例输入 #2
```
4 4
1 2
2 3
3 4
4 2

```
### 样例输出 #2
```
14

```
## 提示

**提示**

在第一个样例中，有以下 $8$ 种不同的选择 $(s, c, f)$ 的方案：

- $(1, 2, 3), (1, 2, 4), (1, 3, 4), (2, 3, 4), (3, 2, 1)$；
- $(4, 2, 1), (4, 3, 1), (4, 3, 2)$。

在第二个样例中，有以下 $14$ 种不同的选择 $(s, c, f)$ 的方案：

- $(1, 2, 3), (1, 2, 4), (1, 3, 4), (1, 4, 3), (2, 3, 4)$；
- $(2, 4, 3), (3, 2, 1), (3, 2, 4), (3, 4, 1), (3, 4, 2)$；
- $(4, 2, 1), (4, 2, 3), (4, 3, 1), (4, 3, 2)$。

**子任务（注：这里给出的子任务与本题在这里的最终评测无关，仅供参考）**

- Subtask 1（points: $5$）：$n \leq 10$，$m \leq 100$。
- Subtask 2（points: $11$）：$n \leq 50$，$m \leq 100$。
- Subtask 3（points: $8$）：$n \leq 100000$，每个交叉路口至多作为两条双向道路的端点。
- Subtask 4（points: $10$）：$n \leq 1000$，在路网中不存在环（存在环是指存在一个长度为 $k$（$k \ge 3$）的交叉路口序列 $v_1, v_2, \ldots, v_k$，序列中的路口编号两两不同，且对于 $i$ 从 $1$ 到 $k - 1$，有一条双向道路直接连接路口 $v_i$ 和 $v_{i+1}$，且有一条双向道路直接连接路口 $v_k$ 和 $v_1$）。
- Subtask 5（points: $13$）：$n \leq 100000$，在路网中不存在环。
- Subtask 6（points: $15$）：$n \leq 1000$，对于每个交叉路口，至多被一个环包含。
- Subtask 7（points: $20$）：$n \leq 100000$，对于每个交叉路口，至多被一个环包含。
- Subtask 8（points: $8$）：$n \leq 1000$，$m \leq 2000$。
- Subtask 9（points: $10$）：$n \leq 100000$，$m \leq 200000$。


---

---
title: "[COCI 2007/2008 #1] STAZA"
layout: "post"
diff: 省选/NOI-
pid: P6335
tag: ['动态规划 DP', '2007', 'O2优化', 'Tarjan', '双连通分量', '仙人掌', 'COCI（克罗地亚）']
---
# [COCI 2007/2008 #1] STAZA
## 题目描述

一场自行车比赛将在一个国家举行。全国的交通网络由 $n$ 个城市组成，编号为 $1\sim n$，由 $m$ 条双向道路连接。我们定义以下术语：

- 一条路线是一系列道路，当且仅当这些道路每条都从上一条道路的结束城市出发。

- 一条简单路线是指一条不经过一个城市一次以上的道路。

- 环是一条起点与终点相同的简单路线。

对于任意两个城市之间，保证至少有一条路线，且每条整个交通系统中的每条道路最多是一个环的一部分。


你的任务是找到满足以下两个约束条件的最长路线：

- 路线可以从任何城市开始，但必须在城市 $1$ 结束。

- 这条路线可以多次访问同一个城市，但不能经过同一条道路超过一次。

请你输出最长的路线的长度。
## 输入格式

输入第一行为两个整数 $n,m$，表示城市的数量和道路的数量。

接下来的 $m$ 行，每行两个整数 $a,b$，描述一条连接 $a,b$ 的双向道路。

保证不会出现两个城市直接由多条道路连接。
## 输出格式

输出最长路线的长度。
## 样例

### 样例输入 #1
```
4 3
1 2
1 3
2 4
```
### 样例输出 #1
```
2
```
### 样例输入 #2
```
6 6
1 2
1 3
2 4
3 4
3 5
5 6
```
### 样例输出 #2
```
5
```
### 样例输入 #3
```
5 6
1 2
2 3
3 4
4 5
5 3
3 1
```
### 样例输出 #3
```
6
```
## 提示

#### 数据规模与约定

对于 $100\%$ 的数据，保证 $2\le n\le 10^4$，$1\le m\le 2n-2$，$1\le a,b\le n$。

#### 说明

**题目译自 [COCI2007-2008](https://hsin.hr/coci/archive/2007_2008/) [CONTEST #1](https://hsin.hr/coci/archive/2007_2008/contest1_tasks.pdf) *T6 STAZA***


---

---
title: "[ICPC 2020 Shanghai R] Traveling Merchant"
layout: "post"
diff: 省选/NOI-
pid: P9829
tag: ['2020', '上海', 'O2优化', '双连通分量', '最近公共祖先 LCA', 'ICPC']
---
# [ICPC 2020 Shanghai R] Traveling Merchant
## 题目描述

Mr. Lawrence is a traveling merchant who travels between cities and resells products. Basically, to earn from it, he needs to buy products at a very low price and sell them at a higher price. Your task is to tell him whether there exists an endless traveling path that can earn money all the time.

To make things simple, suppose there are $n$ cities named from $0$ to $n-1$ and $m$ undirected roads each of which connecting two cities. Mr. Lawrence can travel between cities along the roads. Initially he is located at city $0$ and each of the city $i$ has a starting price $c_i$, either $\text{Low}$ or $\text{High}$. Due to the law of markets, the price status at city $i$ will change (i.e. $\text{High}$ price will become $\text{Low}$ price, or vice versa) after he departs for a neighboring city $j$ from $i$. (City $j$ is a neighboring city of city $i$ when one of the $m$ roads connects city $i$ and city $j$.) For some reasons (e.g. product freshness, traveling fee, tax), he $\textbf{must}$:

- Start at city $0$ and buy products at city $0$. It is guaranteed that $c_0$ is $\text{Low}$.
- When he arrives some city, he either sells products or buys products. It is not allowed for him to do nothing before he leaves the city.
- After buying products at some city $i$, he must travel to some neighboring city $j$ whose price $c_j$ is $\text{High}$ and sell the products at city $j$.
- After selling products at some city $i$, he must travel to some neighboring city $j$ whose price $c_j$ is $\text{Low}$ and buy the products at city $j$.

As a result, the path will look like an alternation between ``buy at low price'' and ``sell at high price''.

An endless earning path is defined as a path consisting of an endless sequence of cities $p_0, p_1,\dots$ where city $p_i$ and city $p_{i+1}$ has a road, $p_0=0$, and the price alternates, in other words $c_{p_{2k}}=\text{Low}$ (indicates a buy-in) and $c_{p_{2k+1}}=\text{High}$ (indicates a sell-out) for $k\geq0$. Please note here $c_{p_i}$ is the price when $\textbf{arriving}$ city $p_i$ and this value may be different when he arrives the second time.

Your task is to determine whether there exists any such path.
## 输入格式

There are several test cases. The first line contains a positive integer $T$ indicating the number of test cases. Each test case begins with two positive integers $n$ and $m$ indicating the number of cities and the number of roads. 

The next line is a string $c$ of length $n$ containing `H' or `L'. The $i$-th ($0\le i<n$) charactor of $c$ is $H$ if the starting price $c_i$ at city $i$ is $\text{High}$. The $i$-th ($0\le i<n$) charactor of $c$ is $L$ if the starting price $c_i$ at city $i$ is $\text{Low}$. 

The $i$-th line ($1\le i\le m$) of the following $m$ lines contains two different cities $u_i$ and $v_i$, indicating a road between $u_i$ and $v_i$.

The sum of the values of $n$ over all test cases is no more than $200,000$. The sum of the values of $m$ over all test cases is no more than $200,000$. For each test case, $c_i\in\{\text{H},\text{L}\}$ holds for each $i\in \{0, \ldots, n-1\}$. $c_0$ is always $L$. $0\leq u_i,v_i<n$ and $u_i\neq v_i$ hold for each $i\in \{1,\ldots, m\}$. No two roads connect the same pair of cities.
## 输出格式

For each test case, output a line of ``yes`` or ``no``, indicating whether there exists an endless earning path.
## 样例

### 样例输入 #1
```
2
4 4
LHLH
0 1
1 2
1 3
2 3
3 3
LHH
0 1
0 2
1 2
```
### 样例输出 #1
```
yes
no
```
## 提示

In the first sample test case, the endless earning path is $0\rightarrow 1\rightarrow 2\rightarrow 3\rightarrow 1\rightarrow 2\rightarrow 3\rightarrow \dots$. In the illustration, cities with $\text{Low}$ price are filled with stripe.

![](https://cdn.luogu.com.cn/upload/image_hosting/2ohq2wfi.png)

In the second sample test case, Mr. Lawrence can only make one move from city $0$ and after that all cities will have $\text{High}$ price. Thus, no further moves can be made.

![](https://cdn.luogu.com.cn/upload/image_hosting/fcv1tw87.png)

## 题目翻译

### 题目描述

劳伦斯先生是一位在不同城市转售商品的旅行商人。基本地，为了赚钱，他需要以低价买进商品，再以高价卖出。现在请你为他规划一条可以一直盈利的旅行路线。

简单地说，假设有 $n$ 座城市，标号为 $0$ 到 $n-1$ ，以及 $m$ 条连接特定两座城市的路，劳伦斯先生可以通过这些路到访每座城市。最初劳伦斯先生位于第 $0$ 座城市，并且对于城市 $i$ 都有一个起始价格 $c_i$ 。根据市场规律，当他从城市 $i$ 来到相邻的城市 $j$ 时（当且仅当城市 $i$ 与城市 $j$ 之间有路径相连时，才称 $i$ 与 $j$ 为相邻城市），城市 $i$ 的价格状况会发生变化（高价会变成低价，低价也可能变成高价）。而因为一些原因（比如商品的新鲜程度，旅行费用，税务等），他**必须**：

- 从城市 $0$ 出发并在城市 $0$ 购买一些商品。保证城市 $0$ 的起始价格很**低**。
- 每当他到达一座城市后，他**必须**售卖**或**购买一些商品。
- 若他在城市 $i$ 购买了商品，他就必须去一座与 $i$ 相邻且价格 $c_j$ **高于** $c_i$ 的城市 $j$ ，并在那里卖掉手中来自城市 $i$ 的商品。
- 若他在城市 $i$ 售卖了商品，他就必须去一座与 $i$ 相邻且价格 $c_j$ **低于** $c_i$ 的城市 $j$，并在那里购买一些商品。


因此，最终路径会始终重复 ``低价购入`` 和 ``高价卖出`` 。

一条无尽的盈利路线由无尽的城市序列 $p_0,p_1 \dots$ 组成。其中，城市 $p_i$ 与城市 $p_{p+1}$ 之间有路径相连，$p_0 = 0$，且价格高低是交替循环的，也就是说当 $k \ge 0$ 时，城市 $p_{2k}$ 的价格 $c_{p_{2k}} = \text{Low}$ (要在这个城市购买商品) 而相邻城市 $p_{2k+1}$ 的价格 $c_{p_{2k+1}} = \text{Hign}$ (要在这个城市卖出商品)。

**注意**：$c_{p_i}$ 是 **到达** 城市 $p_i$ 时的价格，而当他第二次到达城市 $p_i$ 时，这个价格可能会因为市场规律而变化。

你需要写一个程序，判断是否有这样一条永远盈利的路径存在。
### 输入格式

输入有多组数据。所有数据的第一行是一个整型 $T$ 表示数据组数。每组数据的第一行是两个整型 $n$ 和 $m$，表示城市的数量和道路的数量。

每组数据的第二行是一个长度为 $n$ ，由 $H$ 或 $L$ 组成的字符串 $c$ 。字符串 $c$ 的第 $i$ 个字符若为 $H$，则表示城市 $i$ 的起始价格 $c_i$ **高**，反之若为 $L$ 则表示城市 $i$ 的起始价格 $c_i$ **低**。

接下来 $m$ 行，每行输入一组 $u_i$ 和 $v_i$ ，表示一条连接城市 $u_i$ 和城市 $v_i$ 的双向路径。

所有数据中 $n$ 的总和不超过 $200,000$ ，$m$ 的总和也不超过 $200,000$ 。对于每组数据，$c_i\in\{\text{H}, \text{L}\}$ 对应每个 $i\in\{0, \dots, n-1\}$ ，保证 $c_0$ 总为 $L$ 。保证对于每个 $i\in\{1,\dots,m\}$ ，都有 $0 \leq u_i,v_i < n$ 且 $u_i \neq v_i$ 。保证每两座城市之间只有一条路径相连。

### 输出格式
对于每组数据，输出一行 ``yes`` 或者 ``no`` ，表示是否存在一条无尽的盈利路径。


---

