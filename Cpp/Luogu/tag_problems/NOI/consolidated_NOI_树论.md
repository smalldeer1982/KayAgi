---
title: "『STA - R4』保险丝"
layout: "post"
diff: NOI/NOI+/CTSC
pid: P10121
tag: ['暴力数据结构', '线段树', 'O2优化', '树论', '虚树', '其它技巧']
---
# 『STA - R4』保险丝
## 题目背景

APJ：「？我家保险丝怎么又没了」

## 题目描述

给一棵 $n$ 个点的有根树，根是 $1$ 号结点。

定义两个点集 $S_1,S_2$ 的距离为从两个集合分别选出一个点，能得到两点间距离的最小值，即 $\displaystyle\operatorname{dist}(S_1,S_2)=\min_{\substack{u\in S_1\\v\in S_2}}\operatorname{dist}(u,v)$，其中 $\operatorname{dist}(u,v)$ 是点 $u,v$ 间的距离。

定义 $\operatorname{path}(u,v)$ 是 $u$ 到 $v$ 的简单路径上的所有点组成的集合，$\mathcal L$ 是所有叶子组成的集合。

对于固定正整数 $u$，定义满足如下条件的结点 $v$ 构成 $u$ 的半邻域 $\mathring U(u)$：
- $v$ 在 $u$ 子树内；
- $\operatorname{dist}(u,v)\le\operatorname{dist}(\operatorname{path}(1,v),\mathcal L)$。

即 $u$ 的半邻域 $\mathring U(u)$ 包含 $u$ 的子树内所有满足到 $u$ 的距离不大于它到根的路径上任意一点离最近叶子节点的距离的点。

进而定义：
$$f(x)=\sum_{u\in\mathring U(x)}\prod_{\substack{v\in\operatorname{subtree}(u)\\v\in\mathring U(x)}}F_{\deg v}$$
其中 $\operatorname{subtree}(u)$ 是 $u$ 子树中所有点组成的集合，$\deg u$ 是 $u$ 的度数（与 $u$ 有连边的点的数量），$F$ 是 Fibonacci 数列：
$$F_n=\begin{cases}1&n\le 2\\F_{n-1}+F_{n-2}&n\ge 3\end{cases}$$

即 $f(x)$ 对应 $x$ 的半邻域中点对 $x$ 的贡献之和。而一个点 $u$ 对 $x$ 的贡献的计算方式为：取出每个 $u$ 子树内处在 $x$ 半邻域中的点 $v$，若 $v$ 的度数为 $d$，则将 $u$ 的贡献乘上 $F_d$，所有 $u$ 的贡献之和为结果。

你需要求出 $f(1),f(2),\cdots,f(n)$ 的值，为减少输出量，你只需要输出它们模 $994007158$ 后的异或和，即 $\bigoplus_{x=1}^n(f(x)\bmod 994007158)$ 即可。

## 输入格式

第一行一个正整数 $n$ 表示点数。

第二行 $n - 1$ 个正整数，第 $i$ 个正整数代表了结点 $i + 1$ 的父亲结点。
## 输出格式

一行，表示 $\bigoplus_{x=1}^n(f(x)\bmod 994007158)$ 的值。
## 样例

### 样例输入 #1
```
7
1 1 2 2 3 3

```
### 样例输出 #1
```
8
```
### 样例输入 #2
```
14
1 2 3 3 2 6 6 6 9 9 10 11 12
```
### 样例输出 #2
```
25
```
## 提示

### 样例解释
第一组数据中 $f$ 在 $1\dots 7$ 处的取值：$8,2,2,1,1,1,1$。

第二组数据中 $f$ 在 $1\dots14$ 处的取值：$4,17,2,1,1,8,1,1,4,2,1,1,1,1$。
### 数据范围

**本题采用捆绑测试。**
- Subtask 1 (10pts)：$n\le 5000$。
- Subtask 2 (20pts)：树的叶子个数不大于 $30$。
- Subtask 3 (20pts)：树中没有恰有一个儿子的结点。
- Subtask 4 (50pts)：无特殊限制。

对于全部数据，$2\le n,q\le 10^6$，每个非根结点父亲的编号小于它的编号。



---

---
title: "【MX-X13-T7】「KDOI-12」No one can be anything without comparison."
layout: "post"
diff: NOI/NOI+/CTSC
pid: P13012
tag: ['O2优化', '深度优先搜索 DFS', '树论', '前缀和', '分块', '梦熊比赛']
---
# 【MX-X13-T7】「KDOI-12」No one can be anything without comparison.
## 题目描述

**请注意本题对 $\bm{n,k}$ 的特殊限制。**

$n$ 名选手参加了 $k$ 场 Tetris Tournament。每一场 Tetris Tournament 包含 $n-1$ 轮，每轮会选出两个目前还未淘汰的选手 $x,y$ 并让他们参加一场比赛，输的人淘汰。最后会有唯一胜者。你现在得知第 $j$ 个人在第 $i$ 场 Tetris Tournament 中被 $a_{i,j}$ 淘汰了。$j$ 是第 $i$ 场 Tetris Tournament 的胜者当且仅当 $a_{i,j}=0$。

选手们喜欢比较。他们都希望自己在某种意义上能够胜过别人，或至少跟别人水平差不多。

定义第 $i$ 场 Tetris Tournament 中 $x$ 严格吊打 $y$ 当且仅当存在 $x=p_1,p_2,\dots,p_m=y$（$m\ge 2$，也就是说 $x\neq y$），使得对于任意 $1\leq j<m$，$a_{i,p_{j+1}}=p_j$。

定义一个有序的选手 $k$ 元组 $(i_1,i_2,\dots,i_k)$ 是水平相似的当且仅当对于 $1\leq j<k$，$i_j$ 在第 $j$ 场比赛中严格吊打 $i_{j+1}$ 且 $i_k$ 在第 $k$ 场比赛中严格吊打 $i_1$。

求水平相似的 $k$ 元组数量，对 $998244353$ 取模。
## 输入格式

第一行，两个正整数 $n,k$。**保证 $\bm{3\leq k\leq 5}$**。

接下来 $k$ 行，第 $i$ 行 $n$ 个非负整数 $a_{i,1}, \ldots, a_{i,n}$。
## 输出格式

仅一行，一个非负整数，表示水平相似的 $k$ 元组数量，对 $998244353$ 取模。
## 样例

### 样例输入 #1
```
3 3
0 1 2
3 0 2
3 1 0
```
### 样例输出 #1
```
2
```
### 样例输入 #2
```
6 5
0 1 1 2 3 4
3 3 0 6 6 1
2 4 1 0 1 1
3 0 2 6 6 2
5 3 6 1 0 4
```
### 样例输出 #2
```
18
```
## 提示

**【样例解释 \#1】**

符合要求的三元组 $(i_1,i_2,i_3)$ 有：$(1,2,3)$，$(2,3,1)$。

**【数据范围】**

**本题使用捆绑测试。**

| 子任务编号 | 分值 | $n\leq$ | $k=$ | 特殊性质 |
|:--:|:--:|:--:|:--:|:--:|
| $1$ | $7$ | $100$ | $3$ | 无 |
| $2$ | $8$ | $500$ | $3$ | 无 |
| $3$ | $13$ | $3\times10^3$ | $3$ | 无 |
| $4$ | $14$ | $2.5\times10^5$ | $3$ | A |
| $5$ | $15$ | $10^5$ | $3$ | B |
| $6$ | $7$ | $10^5$ | $3$ | 无 |
| $7$ | $14$ | $2.5\times10^5$ | $3$ | 无 |
| $8$ | $7$ | $5\times10^4$ | $4$ | 无 |
| $9$ | $6$ | $7.5\times10^4$ | $4$ | 无 |
| $10$ | $9$ | $4\times10^4$ | $5$ | 无 |

* 特殊性质 A：对于 $1\leq i\leq n$，$a_{1,i}=a_{2,i}$；
* 特殊性质 B：对于 $1\leq i\leq k$，不存在 $1\leq j_1<j_2\leq n$ 使得 $a_{i,j_1}=a_{i,j_2}$。

对于所有数据：$1\leq n\leq2.5\times10^5$，$\bm{3\leq k\leq 5}$，保证 $a$ 数组符合题意，且：

* $k=3$ 时，$n\leq2.5\times10^5$；
* $k=4$ 时：$n\leq7.5\times10^4$；
* $k=5$ 时：$n\leq4\times10^4$。


---

---
title: "【XR-3】Namid[A]me"
layout: "post"
diff: NOI/NOI+/CTSC
pid: P5538
tag: ['图论', 'O2优化', '树论', '位运算']
---
# 【XR-3】Namid[A]me
## 题目描述

小 X 给了你一棵 $n$ 个点的树，点有点权。

你需要求出下列式子模 $786433$ 的值：

$\sum_{1\leq u\leq v\leq n}f(u,v)^{f(u,v)}$

其中 $f(u,v)$ 表示 $u$ 到 $v$ 的最短路径上所有点的点权按位与在一起之后的值。

提示：为了方便你的计算，这里我们认为 $0^0=0$。另外，$786433$ 是一个质数，同时也是一个不常用的 NTT 模数，它的原根为 $10$，如果你不知道什么是 NTT 或者不知道什么是原根，你可以忽略这个提示。
## 输入格式

第一行一个正整数 $n$，表示树的点数。

第二行 $n$ 个正整数 $a_{1\dots n}$，其中 $a_i$ 表示编号为 $i$ 的点的点权。

接下来 $n-1$ 行，每行 $2$ 个正整数 $u,v$，表示编号为 $u$ 和编号为 $v$ 的点之间有一条边。

**数据范围：**

- $2 \le n \le 2 \times 10^5$。
- 对于所有满足 $1\le i \le n$ 的 $i$ 都有 $1 \le a_i < 2^{30}$。
- $1 \le u,v \le n, u \ne v$。
- 设 $d$ 为树中叶子（度数为 $1$ 的点）的个数，数据保证 $4\le n \cdot d \le 3 \times 10 ^ 6$。
## 输出格式

一行一个整数，表示答案对 $786433$ 取模后的值。
## 样例

### 样例输入 #1
```
10
15 50 89 9 38 73 38 23 6 52
2 1
3 2
4 2
5 3
6 3
7 5
8 7
9 1
10 7

```
### 样例输出 #1
```
54184

```
### 样例输入 #2
```
20
17 56 72 12 16 43 33 8 28 90 21 12 7 43 55 95 25 65 63 77
2 1
3 2
4 1
5 3
6 5
7 1
8 7
9 7
10 3
11 5
12 7
13 5
14 7
15 11
16 6
17 3
18 15
19 15
20 13

```
### 样例输出 #2
```
503636

```


---

---
title: "[ICPC 2021 Macao R] Colorful Tree"
layout: "post"
diff: NOI/NOI+/CTSC
pid: P9665
tag: ['线段树', '2021', 'O2优化', '树论', 'ICPC', '澳门']
---
# [ICPC 2021 Macao R] Colorful Tree
## 题目描述

Your task is to maintain a colorful tree and process queries.

At the beginning, there is only one vertex numbered $1$ with color $C$ on the tree. Then there are $q$ operations of two types coming in order:
- $0$ $x$ $c$ $d$: Add a new vertex indexed $(n+1)$ with color $c$ to the tree, where $n$ is the current number of existing vertices. An edge connecting vertex $x$ and $(n+1)$ with length $d$ will also be added to the tree.
- $1$ $x$ $c$: Change the color of vertex $x$ to $c$.

After each operation, you should find a pair of vertices $u$ and $v$ ($1 \le u, v \le n$) with $\textbf{different}$ colors in the current tree so that the distance between $u$ and $v$ is as large as possible.

The distance between two vertices $u$ and $v$ is the length of the shortest path from $u$ to $v$ on the tree.
## 输入格式

There are multiple test cases. The first line of the input contains an integer $T$ indicating the number of test cases. For each test case:

The first line of the input contains two integers $q$ and $C$ ($1 \le q \le 5 \times 10^5$, $1 \le C \le q$) indicating the number of operations and the initial color of vertex $1$.

For the following $q$ lines, each line describes an operation taking place in order with $3$ or $4$ integers.
- If the $i$-th line contains $4$ integers $0$, $x_i$, $c_i$ and $d_i$ ($1 \le x_i \le n$, $1 \le c_i \le q$, $1 \le d \le 10^9$), the $i$-th operation will add a new vertex $(n + 1)$ with color $c_i$ to the tree and connect it to vertex $x_i$ with an edge of length $d_i$.
- If the $i$-th line contains $3$ integers $1$, $x_i$ and $c_i$ ($1 \le x_i \le n$, $1 \le c_i \le q$), the $i$-th operation will change the color of vertex $x_i$ to $c_i$.

It's guaranteed that the sum of $q$ of all test cases will not exceed $5 \times 10^5$.
## 输出格式

For each operation output the maximum distance between two vertices with different colors. If no valid pair exists output $0$ instead.
## 样例

### 样例输入 #1
```
2
1 1
0 1 1 1
5 1
0 1 1 1
0 1 2 1
0 3 3 1
1 4 1
1 3 1
```
### 样例输出 #1
```
0
0
2
3
2
0
```
## 题目翻译

**【题目描述】**

你的任务是维护一棵有色树并处理查询。

一开始，树上只有一个编号为 $1$ 的顶点，颜色为 $C$。然后按顺序进行 $q$ 个操作，有两种类型：
- $0$ $x$ $c$ $d$：向树中添加一个颜色为 $c$ 的新顶点，其编号为 $(n+1)$，其中 $n$ 是当前存在的顶点数。同时，添加一条连接顶点 $x$ 和 $(n+1)$ 的长度为 $d$ 的边。
- $1$ $x$ $c$：将顶点 $x$ 的颜色更改为 $c$。

在每次操作之后，你应该找到当前树中颜色 $\textbf{不同}$ 的两个顶点 $u$ 和 $v$（$1 \le u, v \le n$），使得它们之间的距离尽可能大。

两个顶点 $u$ 和 $v$ 之间的距离是树上从 $u$ 到 $v$ 的最短路径的长度。

**【输入格式】**

输入的第一行包含两个整数 $q$ 和 $C$（$1 \le q \le 5 \times 10^5$，$1 \le C \le q$），表示操作的数量和顶点 $1$ 的初始颜色。

接下来的 $q$ 行中，每行描述一个按顺序进行的操作，包含 $3$ 或 $4$ 个整数。
- 如果第 $i$ 行包含 $4$ 个整数 $0$、$x_i$、$c_i$ 和 $d_i$（$1 \le x_i \le n$，$1 \le c_i \le q$，$1 \le d \le 10^9$），则第 $i$ 个操作将向树中添加一个颜色为 $c_i$ 的新顶点 $(n + 1)$，并将其与顶点 $x_i$ 连接，边的长度为 $d_i$。
- 如果第 $i$ 行包含 $3$ 个整数 $1$、$x_i$ 和 $c_i$（$1 \le x_i \le n$，$1 \le c_i \le q$），则第 $i$ 个操作将顶点 $x_i$ 的颜色更改为 $c_i$。

保证所有测试用例中 $q$ 的总和不超过 $5 \times 10^5$。

**【输出格式】**

对于每个操作，输出两个不同颜色顶点之间的最大距离。如果不存在有效的顶点对，则输出 $0$。

翻译来自于：[ChatGPT](https://chatgpt.com/)


---

