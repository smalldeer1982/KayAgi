---
title: "[NOIP 2012 提高组] 疫情控制"
layout: "post"
diff: 省选/NOI-
pid: P1084
tag: ['贪心', '树形数据结构', '2012', '倍增', '二分', 'NOIP 提高组', '排序']
---
# [NOIP 2012 提高组] 疫情控制
## 题目描述

H 国有 $n $ 个城市，这 $n$ 个城市用 $ n-1 $ 条双向道路相互连通构成一棵树，$1 $ 号城市是首都，也是树中的根节点。

H 国的首都爆发了一种危害性极高的传染病。当局为了控制疫情，不让疫情扩散到边境城市（叶子节点所表示的城市），决定动用军队在一些城市建立检查点，使得从首都到边境城市的每一条路径上都至少有一个检查点，边境城市也可以建立检查点。但特别要注意的是，首都是不能建立检查点的。

现在，在 H 国的一些城市中已经驻扎有军队，且一个城市可以驻扎多个军队。一支军队可以在有道路连接的城市间移动，并在除首都以外的任意一个城市建立检查点，且只能在一个城市建立检查点。一支军队经过一条道路从一个城市移动到另一个城市所需要的时间等于道路的长度（单位：小时）。

请问最少需要多少个小时才能控制疫情。注意：不同的军队可以同时移动。

## 输入格式

第一行一个整数 $ n$，表示城市个数。

接下来的 $n-1$ 行，每行 $ 3 $ 个整数，$u,v,w$，每两个整数之间用一个空格隔开，表示从城市 $u $ 到城市 $ v$ 有一条长为 $w$ 的道路。数据保证输入的是一棵树，且根节点编号为 $1$。

接下来一行一个整数 $m$，表示军队个数。

接下来一行 $m $ 个整数，每两个整数之间用一个空格隔开，分别表示这 $m$ 个军队所驻扎的城市的编号。

## 输出格式

一个整数，表示控制疫情所需要的最少时间。如果无法控制疫情则输出 $-1$。

## 样例

### 样例输入 #1
```
4 
1 2 1 
1 3 2 
3 4 3 
2 
2 2
```
### 样例输出 #1
```
3
```
## 提示

【输入输出样例说明】

第一支军队在 $2$ 号点设立检查点，第二支军队从 $2$ 号点移动到$ 3$ 号点设立检查点，所需时间为 $3$ 个小时。

 
【数据范围】

保证军队不会驻扎在首都。

- 对于 $20\%$ 的数据，$2 \le n\le 10$；
- 对于 $40\%$ 的数据，$2 \le n\le 50$，$0<w <10^5$；
- 对于 $60\%$ 的数据，$2 \le n\le 1000$，$0<w <10^6$；
- 对于 $80\%$ 的数据，$2 \le n\le 10^4$；
- 对于 $100\%$ 的数据，$2\le m\le n≤5\times 10^4$，$0<w <10^9$。


NOIP 2012 提高组 第二天 第三题



---

---
title: "[JRKSJ R9] 莫队的 1.5 近似构造"
layout: "post"
diff: 省选/NOI-
pid: P10880
tag: ['动态规划 DP', '2024', '洛谷原创', 'O2优化', '排序']
---
# [JRKSJ R9] 莫队的 1.5 近似构造
## 题目背景

> 二维莫队构造可以看作 $i,j$ 之间有权值为 $|l_i-l_j|+|r_i-r_j|$ 的完全图上的 TSP 问题。显然，任何莫队的边权都满足三角不等式。
\
\
>求出最小生成树，然后把所有度数为奇数的点拿出来，对这个导出子图跑最小权匹配得到 $E$，将 $E$ 加到最小生成树上，然后跑欧拉路径即可。
\
\
 注意到 $\text{MST}(S)\le \text{TSP}(S)$，$2E\le \text{TSP}(S)$（$E$ 的 $\text{TSP}$ 方案可以给出两组匹配，考虑其中的较小值）且欧拉路径的边权和不小于欧拉路径给出的方案的权值，就给出了 $\le 1.5\text{TSP}(S)$ 的结果。
## 题目描述

给你一个 $1\sim n$ 的排列 $a$ 和 $m$ 个该排列上的区间 $[l_i,r_i]$。

对于一个值域区间 $[L,R]$：
- 称「选取 $i$ 时该值域区间的价值」为 $a_{l_i},a_{l_i+1},\dots,a_{r_i}$ 中有多少个数属于值域区间 $[L,R]$；
- 定义值域区间 $[L,R]$ 的价值为 $\forall i\in[1,m]$，「选取 $i$ 时该值域区间的价值」的最大值。

即，值域区间 $[L,R]$ 的价值为 $\displaystyle\max_{i=1}^m \sum_{j=l_i}^{r_i} [L\le a_j\le R]$。

定义两个区间相交当且仅当至少有一个整数被这两个区间共同包含。请你选出若干个**互不相交**的值域区间，使得它们的价值的乘积最大。将该答案对 $998244353$ 取模后输出。
## 输入格式

第一行两个整数 $n,m$。

第二行 $n$ 个整数表示 $a_{1\dots n}$。

下面 $m$ 行，每行两个整数 $l_i,r_i$。
## 输出格式

一个整数表示答案。输出答案时对 $998244353$ 取模。
## 样例

### 样例输入 #1
```
3 3
1 2 3
1 2
1 3
2 3
```
### 样例输出 #1
```
3
```
### 样例输入 #2
```
10 10
7 9 4 5 8 3 2 1 6 10 
3 7
2 6
1 2
3 4
8 9
1 2
2 6
5 8
6 9
4 5
```
### 样例输出 #2
```
12
```
### 样例输入 #3
```
60 30
1 2 3 4 5 6 7 8 9 10 11 12 13 14 15 16 17 18 19 20 21 22 23 24 25 26 27 28 29 30 31 32 33 34 35 36 37 38 39 40 41 42 43 44 45 46 47 48 49 50 51 52 53 54 55 56 57 58 59 60 
34 57
2 17
3 16
18 50
18 54
8 45
8 56
14 39
22 33
12 33
27 49
33 33
9 11
12 52
11 17
23 31
14 39
19 57
25 32
15 22
2 48
14 21
51 59
28 48
26 31
31 60
41 58
36 46
49 53
44 48
```
### 样例输出 #3
```
328034228
```
## 提示

### 样例解释 1

选择值域区间 $[1,3]$。

### 样例解释 2

可以选择值域区间 $[1,3],[4,5],[8,10]$。

### 样例解释 3

样例 3 满足特殊性质。

### 数据规模与约定
**本题采用捆绑测试。**

| $\mathrm{Subtask}$ | $n,m\le$ | 特殊性质 | 分数 |
| :-----: | :-----: | :-----: | :-----: |
| $1$ | $20$ |  | $10$ |
| $2$ | $5\times 10^3$ |  | $15$ |
| $3$ | $3\times 10^5$ | $\checkmark$ | $10$ |
| $4$ | $5\times 10^4$ |  | $25$ |
| $5$ | $3\times 10^5$ |  | $40$ |

特殊性质：保证 $\forall i\in[1,n],a_i=i$。

对于所有数据，保证 $1\le n,m\le 3\times 10^5$，$1\le l_i\le r_i\le n$，$a$ 是一个 $1\sim n$ 的排列。


---

---
title: "【MX-S6-T4】「KDOI-11」彩灯晚会"
layout: "post"
diff: 省选/NOI-
pid: P11292
tag: ['动态规划 DP', 'O2优化', '动态规划优化', '拓扑排序', '组合数学', '容斥原理', '梦熊比赛']
---
# 【MX-S6-T4】「KDOI-11」彩灯晚会
## 题目背景

原题链接：<https://oier.team/problems/S6D>。
## 题目描述

小 K 家的房子还蛮大的，所以他举办了彩灯晚会。

彩灯晚会显然有彩灯。于是小 K 找来了 $n$ 盏彩灯。

小 K 不希望彩灯散在地上，于是他用 $m$ 条**有向边**连接了这些彩灯，使得他们连在一起。也就是说，在将有向边看成无向边的情况下，这些彩灯是连通的。保证该图为**有向无环图**。

小 K 的彩灯很厉害，每个都可以独立地发出 $k$ 种颜色中的任意一种。小 K 作为世界顶尖 Light Glowing Master（简称 LGM），决定将所有方案（共 $k^n$ 种）都尝试一下。

小 K 不喜欢很多的颜色，于是他给定了一个正整数 $l$，并定义一个方案的美丽度为每种颜色长度为 $l$ 的链数量的平方之和。形式化地讲，设第 $i$ 种颜色的长度为 $l$ 的链的数量为 $cnt_i$，则一个方案的美丽度为 $\sum_{i=1}^kcnt_i^2$。

现在小 K 想知道所有 $k^n$ 种方案的美丽度之和，对 $998244353$ 取模。

两种方案是不同的当且仅当存在某个彩灯在两种方案中发出不同的颜色。

一条长度为 $l$ 的链是一个 $2l-1$ 元组 $(v_1,e_1,v_2,e_2,\dots,e_{l-1},v_l)$，使得对于任意 $1\leq i<l$，第 $e_i$ 条有向边是由 $v_i$ 连向 $v_{i+1}$ 的。两条长度为 $l$ 的链 $(v_1,e_1,v_2,e_2,\dots,e_{l-1},v_l)$ 和 $(v'_1,e'_1,v'_2,e'_2,\dots,e'_{l-1},v'_l)$ 不同当且仅当存在 $1\leq i<l$ 满足 $e_i\neq e'_i$ 或存在 $1\leq i\leq l$ 满足 $v_i\neq v'_i$。

一种颜色 $x$ 的长度为 $l$ 的链是一条长度为 $l$ 的链 $(v_1,e_1,v_2,e_2,\dots,e_{l-1},v_l)$ 使得对于任意 $1\leq i\leq l$，$v_i$ 编号的彩灯发出颜色为 $x$。
## 输入格式

第一行，五个非负整数 $id,n,k,l,M$，其中 $id$ 表示测试点编号（所有样例满足 $id=0$），$n$ 表示彩灯数量，$k$ 表示颜色数量，$l$ 表示链的长度，$M$ 的意义如后文所示。

接下来 $M$ 行，第 $i$ 行三个正整数 $u_i,v_i,c_i$，表示有 $c_i$ 条 $u_i\to v_i$ 的有向边。也就是说，第 $\bigl(\sum_{j=1}^{i-1}c_j\bigr)+1$ 至第 $\bigl(\sum_{j=1}^ic_j\bigr)$ 条有向边由 $u_i$ 连向 $v_i$。

题面中 $m$ 满足 $m=\sum_{i=1}^Mc_i$。保证：$(u,v)$ 互不相同，给定图为有向无环图，在将有向边看成无向边的情况下，彩灯是连通的。
## 输出格式

仅一行，一个非负整数，表示所有 $k^n$ 种方案的美丽度之和，对 $998244353$ 取模。
## 样例

### 样例输入 #1
```
0 3 2 2 2
1 3 1
3 2 1
```
### 样例输出 #1
```
12
```
### 样例输入 #2
```
0 5 4 3 7
1 4 4
1 5 2
4 3 1
5 3 2
3 2 3
4 5 1
5 2 2
```
### 样例输出 #2
```
16096
```
## 提示

**【样例解释 #1】**

共有 $2^3=8$ 种不同的彩灯显示颜色的方案，如下表所示（不妨假设颜色为黑和白）：

| 编号 | $1$ 号彩灯颜色 | $2$ 号彩灯颜色 | $3$ 号彩灯颜色 | 美丽度 |
|:--:|:--:|:--:|:--:|:--:|
| $1$ | 黑 | 黑 | 黑 | $4$ |
| $2$ | 黑 | 黑 | 白 | $0$ |
| $3$ | 黑 | 白 | 黑 | $1$ |
| $4$ | 黑 | 白 | 白 | $1$ |
| $5$ | 白 | 黑 | 黑 | $1$ |
| $6$ | 白 | 黑 | 白 | $1$ |
| $7$ | 白 | 白 | 黑 | $0$ |
| $8$ | 白 | 白 | 白 | $4$ |

美丽度之和为 $4+0+1+1+1+1+0+4=12$。

**【样例 #3】**

见附件中的 `party/party3.in` 与 `party/party3.ans`。

该组样例满足测试点 $1$ 的约束条件。

**【样例 #4】**

见附件中的 `party/party4.in` 与 `party/party4.ans`。

该组样例满足测试点 $2\sim3$ 的约束条件。

**【样例 #5】**

见附件中的 `party/party5.in` 与 `party/party5.ans`。

该组样例满足测试点 $4\sim5$ 的约束条件。

**【样例 #6】**

见附件中的 `party/party6.in` 与 `party/party6.ans`。

该组样例满足测试点 $6\sim9$ 的约束条件。

**【样例 #7】**

见附件中的 `party/party7.in` 与 `party/party7.ans`。

该组样例满足测试点 $10\sim12$ 的约束条件。

**【样例 #8】**

见附件中的 `party/party8.in` 与 `party/party8.ans`。

该组样例满足测试点 $13\sim15$ 的约束条件。

**【样例 #9】**

见附件中的 `party/party9.in` 与 `party/party9.ans`。

该组样例满足测试点 $20\sim21$ 的约束条件。

**【数据范围】**

记 $P=998244353$，对于所有测试数据，保证：$1\leq n\leq300$，$1\leq M\leq\frac{n(n-1)}{2}$，$1\leq k<P$，$1\leq l\leq 20$，$1\leq c_i<P$，$(u_i,v_i)$ 互不相同，给定图为有向无环图，在将有向边看成无向边的情况下，彩灯是连通的。

| 测试点编号 | $n\leq$ | $k\leq$ | $l\leq$ | 特殊性质 |
|:--:|:--:|:--:|:--:|:--:|
| $1$ | $6$ | $6$ | $6$ | $m\leq10$，$c_i=1$ |
| $2\sim3$ | $300$ | $P-1$ | $1$ | 无 |
| $4\sim5$ | $300$ | $P-1$ | $2$ | 无 |
| $6\sim9$ | $300$ | $P-1$ | $3$ | 无 |
| $10\sim12$ | $300$ | $P-1$ | $20$ | $M=n-1$ 且有且仅有一个点入度为 $0$ |
| $13\sim15$ | $30$ | $P-1$ | $10$ | 无 |
| $16$ | $150$ | $P-1$ | $7$ | 无 |
| $17$ | $150$ | $P-1$ | $10$ | 无 |
| $18\sim19$ | $150$ | $P-1$ | $13$ | 无 |
| $20\sim21$ | $300$ | $P-1$ | $9$ | 无 |
| $22$ | $300$ | $P-1$ | $13$ | 无 |
| $23$ | $300$ | $P-1$ | $16$ | 无 |
| $24\sim25$ | $300$ | $P-1$ | $20$ | 无 |


---

---
title: "[UOI 2021] 数字图"
layout: "post"
diff: 省选/NOI-
pid: P12576
tag: ['博弈论', '2021', '拓扑排序', 'UOI（乌克兰）']
---
# [UOI 2021] 数字图
## 题目描述

瓦西里和彼得里克发现了一个数字图——这是一个连通的有向图，每个顶点上都标有一个数字。

两人急需一个数字，于是决定在图上游玩一个游戏。他们将棋子放在编号为 1 的顶点上。每一回合可以选择以下两种操作之一：
1. 结束游戏并获得当前顶点上的数字；
2. 沿着有向边将棋子移动到相邻顶点。

如果游戏进行到 $10^{100}$ 回合仍未结束，则自动终止并获得当前顶点上的数字。

瓦西里先手，他希望最大化最终获得的数字；而彼得里克则希望最小化这个数字。假设双方都采取最优策略，求游戏结束时他们将获得的数字。
## 输入格式

第一行包含两个整数 $n$ 和 $m$（$1 \leq n \leq 250\,000$，$1 \leq m \leq 500\,000$）——分别表示图的顶点数和边数。

第二行包含 $n$ 个整数 $a_i$（$1 \leq a_i \leq 10^9$）——表示每个顶点上的数字。

接下来的 $m$ 行，每行包含两个整数 $x$ 和 $y$（$1 \leq x, y \leq n$），表示存在一条从顶点 $x$ 指向 $y$ 的有向边。
## 输出格式

输出一个整数，表示在双方都采取最优策略时，游戏结束时获得的数字。
## 样例

### 样例输入 #1
```
4 4
1 10 4 5
1 2
2 3
2 4
3 1
```
### 样例输出 #1
```
4
```
### 样例输入 #2
```
2 2
1 2
1 2
2 1
```
### 样例输出 #2
```
1
```
## 提示

第一个样例的图示如图 1 所示，顶点标注格式为"顶点编号（数字）"：

![](https://cdn.luogu.com.cn/upload/image_hosting/ssfvk5ca.png)
1. 瓦西里先手，可以选择立即结束游戏或移动到顶点 2。最优选择是移动。
2. 彼得里克回合，最优选择是移动到顶点 3。
3. 最后如果瓦西里移动到顶点 1，彼得里克会结束游戏获得数字 1，因此瓦西里会选择直接结束游戏获得数字 4。

第二个样例的图示如图 2 所示：

![](https://cdn.luogu.com.cn/upload/image_hosting/9crldhqu.png)

双方将交替移动 $10^{100}$ 步，最终棋子停留在顶点 1。

### 评分标准

1. （$6$ 分）给定的图是一条所有边同向的直线；
2. （$8$ 分）给定的图是一棵以顶点 1 为根的树，所有边方向从根向下；
3. （$14$ 分）给定的图是一个环；
4. （$26$ 分）$1 \leq a_i \leq 2$；
5. （$46$ 分）无额外限制。

翻译由 DeepSeek V3 完成


---

---
title: "[UOI 2020] Topological Sorting of a Tree"
layout: "post"
diff: 省选/NOI-
pid: P12639
tag: ['动态规划 DP', '2020', '树形 DP', '拓扑排序', '组合数学', '前缀和', '容斥原理', 'UOI（乌克兰）']
---
# [UOI 2020] Topological Sorting of a Tree
## 题目描述

You are given a tree with $n$ vertices, numbered from $1$ to $n$. The root of the tree is the vertex with number $1$. For each $v$ from $2$ to $n$, let's define $p_v$ as the number of the vertex adjacent to $v$ that lies on the simple path between vertex $v$ and the root. Each edge $(p_v, v)$ is labeled with the symbol $\tt{<}$ or $\tt{>}$.

Find the number of ways to place the numbers from $1$ to $n$ in the vertices of the tree, such that each number is used exactly once and all the relationships indicated on the edges are satisfied. That is, for all edges with the symbol $\tt{<}$, $a[p_v] < a[v]$ should hold, and for all edges with the symbol $\tt{>}$, $a[p_v] > a[v]$ should hold.

Since the answer can be very large, output it modulo $10^9 + 7$.
## 输入格式

The first line contains a single integer $n$ ($1 \leq n \leq 3\,000$) - the number of vertices in the tree.

Each of the next $n-1$ lines contains a single integer $p_i$ ($1 \leq p_i < i$) and a character $c_i$ ($c_i \in \{\tt{<}, \tt{>}\}$), indicating that the edge between vertices with indices $p_i$ and $i$ is labeled with the symbol $c_i$. Note that the indexing starts from $2$.
## 输出格式

Output a single integer - the number of ways to arrange all numbers from $1$ to $n$ in the vertices of the tree such that all the relationships indicated on the edges are satisfied. Note that you should output the remainder of the division by $10^9 + 7$, not the actual answer.
## 样例

### 样例输入 #1
```
4
1 <
2 <
3 >
```
### 样例输出 #1
```
3
```
### 样例输入 #2
```
4
1 <
1 <
1 <
```
### 样例输出 #2
```
6
```
### 样例输入 #3
```
5
1 <
1 <
3 >
3 >
```
### 样例输出 #3
```
18
```
## 提示

- ($8$ points) $n \leq 10$;
- ($6$ points) $n \leq 18$;
- ($10$ points) $c_i = \tt{<}$;
- ($4$ points) $p_i = 1$;
- ($13$ points) $p_i = i - 1, 1 \leq n \leq 200$;
- ($19$ points) $p_i = i - 1$;
- ($24$ points) $n \leq 200$;
- ($16$ points) no additional constraints.


---

---
title: "[JOI Open 2025] 冒泡排序机 / Bubble Sort Machine"
layout: "post"
diff: 省选/NOI-
pid: P12865
tag: ['树状数组', '2025', '排序', '可持久化线段树', 'JOI（日本）']
---
# [JOI Open 2025] 冒泡排序机 / Bubble Sort Machine
## 题目背景

译自 [JOI Open 2025](https://contests.ioi-jp.org/open-2025/index.html) T1「[Bubble Sort Machine](https://www.luogu.com.cn/fe/api/problem/downloadAttachment/cm7aghex)」/ 「[バブルソート機](https://www.luogu.com.cn/fe/api/problem/downloadAttachment/gkrcwais)」。

## 题目描述


JOI 君——一名算法工程师，开发了冒泡排序机。

冒泡排序机操作长为 $N$ 的整数序列 $a=(a_1,a_2,\ldots,a_N)$。为了让机器能工作，给定 $A_i$ 作为 $a_i$（$1\le i\le N$）的初值。每当机器上的**按钮壹**被按下时，机器会按照如下方式修改序列 $a$：

> 对于 $i=1,2,\ldots,N-1$（按此顺序），若 $a_i\gt a_{i+1}$，交换 $a_i,a_{i+1}$ 的值。

为了使冒泡排序机更博人眼球，JOI 君决定加入以下功能：

> 当**按钮贰**被按下时，给定整数 $l,r$ 作为输入（须满足 $1\le l\le r\le N$），机器会输出 $a_{l}+a_{l+1}+\cdots+a_r$ 的值。

给定整数序列的初值和冒泡排序机的操作序列，编程计算按钮贰的输出值。

## 输入格式


输入格式如下所示：

> $N$ \
> $A_1$ $A_2$ $\cdots$ $A_N$ \
> $Q$ \
> $(\text{Query }1)$ \
> $(\text{Query }2)$ \
> $\vdots$ \
> $(\text{Query }Q)$

这里，$Q$ 指的是冒泡排序机的操作数。每个 $(\text{Query }j)$（$1\le j\le Q$）由若干个空格分隔的数字组成。令 $T_j$ 为 $(\text{Query }j)$ 的首个数字。这行的内容为以下二者之一：

- 若 $T_j=1$，这行再没有其他整数了。这意味着冒泡排序机的第 $j$ 次操作按下了按钮壹。
- 若 $T_j=2$，接下来还有两个整数，依次是 $L_j,R_j$。这意味着冒泡排序机的第 $j$ 次操作按下了按钮贰，给定的输入为 $L_j,R_j$。
## 输出格式


对每个按下按钮贰的操作［意思是，对每个满足 $T_j=2$ 的 $j$（$1\le j\le Q$）］，输出一行一个整数，表示冒泡排序机的输出。你的输出应与询问的顺序相符。
## 样例

### 样例输入 #1
```
4
5 3 5 2
6
2 1 3
1
2 1 1
2 2 4
1
2 1 2
```
### 样例输出 #1
```
13
3
12
5
```
### 样例输入 #2
```
5
1 1 2 1 2
5
2 2 3
1
2 2 4
1
2 2 4
```
### 样例输出 #2
```
3
4
4
```
## 提示


### 样例解释

#### 样例 $1$ 解释

初值为 $a_1=5,a_2=3,a_3=5,a_4=2$，$a=(5,3,5,2)$。接下来在冒泡排序机上操作：

1. 按下按钮贰，输入 $l=1,r=3$。机器输出 $a_1+a_2+a_3=13$。
2. 按下按钮壹。对 $i=1,2,3$，按此顺序进行如下操作：
    - $i=1$：由于 $a_1\gt a_2$，交换二者的值，操作后 $a=(3,5,5,2)$。
    - $i=2$：由于并没有 $a_2\gt a_3$，不操作 $a$。
    - $i=3$：由于 $a_3\gt a_4$，交换二者的值，操作后 $a=(3,5,2,5)$。
3. 按下按钮贰，输入 $l=1,r=1$。机器输出 $a_1=3$。
3. 按下按钮贰，输入 $l=2,r=4$。机器输出 $a_2+a_3+a_4=12$。
5. 按下按钮壹。对 $i=1,2,3$，按此顺序进行如下操作：
    - $i=1$：由于并没有 $a_1\gt a_2$，不操作 $a$。
    - $i=2$：由于 $a_2\gt a_3$，交换二者的值，操作后 $a=(3,2,5,5)$。
    - $i=3$：由于并没有 $a_3\gt a_4$，不操作 $a$。
6. 按下按钮贰，输入 $l=1,r=2$。机器输出 $a_1+a_2=5$。

样例 $1$ 满足子任务 $1,5,6$ 的限制。

#### 样例 $2$ 解释

样例 $2$ 满足子任务 $1,3,5,6$ 的限制。


### 数据范围

- $2\le N\le 500\, 000$；
- $1\le A_i\le 10^9\, (1\le i\le N)$；
- $1\le Q\le 500\, 000$；
- $T_j\in \{1,2\}\, (1\le j\le Q)$；
- 若 $T_j=2$，有 $1\le L_j\le R_j\le N\, (1\le j\le Q)$；
- 输入的值都是整数。

### 子任务

- $\text{Subtask 1 (5 pts)}$：满足 $T_j=1$ 的 $j\,(1\le j\le Q)$ 至多有 $10$ 个；
- $\text{Subtask 2 (11 pts)}$：$N,Q\le 150\, 000$，当 $T_j=2$ 时 $L_j=R_j=1\, (1\le j\le Q)$；
- $\text{Subtask 3 (15 pts)}$：$N,Q\le 150\, 000$，$1\le A_i\le 2\, (1\le i\le N)$；
- $\text{Subtask 4 (23 pts)}$：$N,Q\le 150\, 000$，当 $T_j=2$ 时 $L_j=R_j\, (1\le j\le Q)$；
- $\text{Subtask 5 (29 pts)}$：$N,Q\le 150\, 000$；
- $\text{Subtask 6 (17 pts)}$：无额外限制。




---

---
title: "[GCJ 2019 Finals] Sorting Permutation Unit"
layout: "post"
diff: 省选/NOI-
pid: P13124
tag: ['2019', 'Special Judge', '排序', 'Ad-hoc', 'Google Code Jam']
---
# [GCJ 2019 Finals] Sorting Permutation Unit
## 题目描述

You may have heard of Google's Tensor Processing Units, which are used to build neural networks. However, there is one research area that is even deeper and more important than machine learning: sorting!

We are working on a special new chip called the Sorting Permutation Unit, which is very fast at applying permutations to arrays of integers. Formally, a permutation is an ordering of the first $\mathbf{n}$ positive integers

$$\mathbf{p}_{1}, \mathbf{p}_{2}, \ldots, \mathbf{p}_{\mathbf{n}}$$

and applying it to an array of $\mathbf{n}$ integers

$$\mathbf{a}_{1}, \mathbf{a}_{2}, \ldots, \mathbf{a}_{\mathbf{n}}$$

yields the new array

$$\mathbf{a}_{\mathbf{p}_{1}}, \mathbf{a}_{\mathbf{p}_{2}}, \ldots, \mathbf{a}_{\mathbf{p}_{\mathbf{n}}}$$

For example, applying the permutation 3, 1, 2, 4 to the array 99, 234, 45, 800 would yield the new array 45, 99, 234, 800.

However, permutations are expensive to represent in the hardware, so the unit can only have access to at most $\mathbf{P}$ distinct permutations. We need your help figuring out what those permutations should be!

Given $\mathbf{K}$ arrays of $\mathbf{N}$ integers each, you must first specify up to $\mathbf{P}$ permutations (of size $\mathbf{N}$) of your choice. Then, for each of those $\mathbf{K}$ input arrays, you must provide one sequence of up to $\mathbf{S}$ instructions (each of which is a permutation from your specified set). When the instructions in this sequence are applied, in the given order, to the array, they must yield an array sorted in nondecreasing order. In each of your $\mathbf{K}$ sequences of instructions, you may use each of your $\mathbf{P}$ permutations zero or more times (not necessarily consecutively).
## 输入格式

The first line of the input gives the number of test cases, $\mathbf{T}$. $\mathbf{T}$ test cases follow. Each begins with one line with four integers $\mathbf{P}$, $\mathbf{S}$, $\mathbf{K}$, and $\mathbf{N}$: the maximum number of permutations allowed, the maximum number of instructions you are allowed to use to sort each array, the number of arrays, and the number of integers in each array. Then, there are $\mathbf{K}$ more lines of $\mathbf{N}$ integers $\mathbf{A}_{\mathbf{i}1}$, $\mathbf{A}_{\mathbf{i}2}$, ..., $\mathbf{A}_{\mathbf{iN}}$ each, where the j-th integer on the i-th line, $\mathbf{A}_{\mathbf{ij}}$, represents the j-th value of the i-th array.
## 输出格式

For each test case, first output the following, in this order:

* One line containing Case #x:, where $\mathbf{x}$ is the test case number (starting from 1).
* One line containing one integer $\mathbf{P}'$, where $1 \leq \mathbf{P}' \leq \mathbf{P}$: the number of permutations you have chosen to use.
* $\mathbf{P}'$ lines, the i-th of which contains $\mathbf{N}$ integers $\mathbf{p}_{\mathbf{i}1}$ $\mathbf{p}_{\mathbf{i}2}$ ... $\mathbf{p}_{\mathbf{iN}}$, where $\mathbf{p}_{\mathbf{ij}}$ is the j-th element of the i-th permutation.

Then, output $\mathbf{K}$ more lines. The i-th of these gives the instructions that you will apply to the i-th array given in the input. Each such line must begin with one integer $\mathbf{S}'$, where $0 \leq \mathbf{S}' \leq \mathbf{S}$, and must continue with $\mathbf{S}'$ integers $\mathbf{X}_{1}$, $\mathbf{X}_{2}$, ..., $\mathbf{X}_{\mathbf{S}'}$, where $1 \leq \mathbf{X}_{\mathbf{k}} \leq \mathbf{P}'$ for all $\mathbf{k}$. Here, $\mathbf{X}_{\mathbf{k}}$ represents that the k-th instruction you apply to the i-th array is the $\mathbf{X}_{\mathbf{k}}$-th permutation (counting starting from 1) in your list of permutations. These instructions must yield an array with the elements of the i-th input array, sorted in nondecreasing order.
## 样例

### 样例输入 #1
```
2
20 450 4 3
10 10 11
17 4 1000
999 998 997
10 10 11
20 450 5 5
1 2 3 4 5
2 3 4 5 1
3 4 5 1 2
4 5 1 2 3
5 1 2 3 4
```
### 样例输出 #1
```
Case #1:
2
3 1 2
2 1 3
0
1 2
2 2 1
1 2
Case #2:
1
5 1 2 3 4
0
1 1
2 1 1
3 1 1 1
4 1 1 1 1
```
## 提示

**Sample Explanation**

In Sample Case #1, we can define up to $\mathbf{P} = 20$ permutations. One viable strategy uses only these two:

1. 3 1 2
2. 2 1 3

We can handle the four arrays as follows:

* 10 10 11: This is already sorted in nondecreasing order, so we do not need to do anything.
* 17 4 1000: We can apply permutation #2 to yield 4 17 1000.
* 999 998 997: One option is to first apply permutation #2 to turn the array into 998 999 997, then apply permutation #1 to turn the array into 997 998 999.
* 10 10 11: This is the same as the first array. Applying permutation #2 also yields array sorted in nondecreasing order. (But we could have used the line 0 as we did before.)

In Sample Case #2, notice that we can use the same permutation instruction more than once on the same array, if desired.

**Limits**

- $1 \leq \mathbf{T} \leq 10$.
- $\mathbf{S} = 450$.
- $1 \leq \mathbf{K} \leq 30$.
- $2 \leq \mathbf{N} \leq 50$.
- $1 \leq \mathbf{A}_{\mathbf{ij}} \leq 1000$, for all $\mathbf{i}$ and $\mathbf{j}$.

**Test set 1 (5 Pts, Visible)**

- $\mathbf{P} = 20$.

**Test set 2 (22 Pts, Hidden)**

- $\mathbf{P} = 5$.


---

---
title: "[GCJ 2015 Finals] Pretty Good Proportion"
layout: "post"
diff: 省选/NOI-
pid: P13235
tag: ['动态规划 DP', '2015', '排序', 'Google Code Jam']
---
# [GCJ 2015 Finals] Pretty Good Proportion
## 题目描述

I have a sequence of $\mathbf{N}$ binary digits. I am looking for a substring with just the right proportion of 0s and 1s, but it may not exist, so I will settle for something that's just pretty good.

Can you find a substring where the fraction of 1s is as close as possible to the given fraction $\mathbf{F}$? Output the earliest possible index at which such a substring starts.

## 输入格式

The first line of the input gives the number of test cases, $\mathbf{T}$. $\mathbf{T}$ test cases follow. Each one starts with a line containing $\mathbf{N}$ and $\mathbf{F}$. $\mathbf{F}$ will be a decimal fraction between 0 and 1 inclusive, with exactly 6 digits after the decimal point. The next line contains $\mathbf{N}$ digits, each being either 0 or 1.

## 输出格式

For each test case, output one line containing "Case #x: y", where $\mathrm{x}$ is the test case number (starting from 1) and $\mathrm{y}$ is the 0-based index of the start of the substring with the fraction of 1s that is as close as possible to $\mathbf{F}$. If there are multiple possible answers, output the smallest correct value.
## 样例

### 样例输入 #1
```
5
12 0.666667
001001010111
11 0.400000
10000100011
9 0.000000
111110111
5 1.000000
00000
15 0.333333
000000000011000
```
### 样例输出 #1
```
Case #1: 5
Case #2: 5
Case #3: 5
Case #4: 0
Case #5: 6
```
## 提示

**Sample Explanation**

In Case #1, there is no substring that has exactly a $1$-proportion of exactly $666667/1000000$. The closest we can get is $2/3$. The input string has 5 substrings that achieve it -- $3$ substrings of length 3 that start at indices $5, 7,$ and $8$ ($101, 101,$ and $011$); as well as two substrings of length $6$ that start at indices $5$ and $6$ ($101011$ and $010111$). The smallest of these indices is $5$.

**Limits**

- $1 \leq \mathbf{T} \leq 100$.
- $0 \leq \mathbf{F} \leq 1$
- $\mathbf{F}$ will have exactly 6 digits after the decimal point.

**Small dataset**

- Time limit: ~~240~~ 5 seconds.
- $1 \leq \mathbf{N} \leq 1000$.

**Large dataset**

- Time limit: ~~480~~ 10 seconds.
- $1 \leq \mathbf{N} \leq 500,000$.


---

---
title: "[NWRRC 2023] Loops"
layout: "post"
diff: 省选/NOI-
pid: P13592
tag: ['平衡树', '2023', 'Special Judge', '排序', '构造', 'ICPC', 'Ad-hoc', 'NWRRC']
---
# [NWRRC 2023] Loops
## 题目描述

Consider four integers $A$, $B$, $C$, and $D$, such that $A < B < C < D$. Let's put them in the corners of a square in some order and draw a loop $A - B - C - D - A$. Depending on the arrangement of the integers, we can get different loop shapes, but some arrangements produce the same shape:

![](https://cdn.luogu.com.cn/upload/image_hosting/8hyu6a9v.png)

There are three possible loop shapes we can get:

![](https://cdn.luogu.com.cn/upload/image_hosting/ikan9lhl.png)

Now consider an $n\times m$ matrix filled with distinct integers from $1$ to $nm$, inclusive. Each $2\times 2$ square in this matrix can be seen as a square with integers in its corners. Let's build a loop for each of these squares like we did before:

![](https://cdn.luogu.com.cn/upload/image_hosting/y3rml1pm.png)

Your task is to perform the inverse operation. You are given the shape types for all $(n-1)(m-1)$ loops, and you need to build an $n\times m$ matrix filled with distinct integers from $1$ to $nm$, inclusive, that produces these shapes.
## 输入格式

The first line contains two integers $n$ and $m$ ($2\le n, m\le 500$).

Each of the next $n-1$ lines contains a string of $m-1$ characters without spaces. Each character is a digit from $1$ to $3$, denoting the type of the shape of the corresponding loop.
## 输出格式

Print an $n\times m$ matrix filled with distinct integers from $1$ to $nm$, inclusive, that produces the shapes of the loops in the input.

It can be shown that such a matrix always exists. If there are multiple answers, print any of them.
## 样例

### 样例输入 #1
```
3 4
113
231
```
### 样例输出 #1
```
9 11 7 12
4 6 1 8
2 10 5 3
```


---

---
title: "皇后游戏"
layout: "post"
diff: 省选/NOI-
pid: P2123
tag: ['贪心', '排序']
---
# 皇后游戏
## 题目背景

还记得 NOIP 2012 提高组 Day1 的国王游戏吗？时光飞逝，光阴荏苒，两年过去了。国王游戏早已过时，如今已被皇后游戏取代，请你来解决类似于国王游戏的另一个问题。

## 题目描述

皇后有 $n$ 位大臣，每位大臣的左右手上面分别写上了一个正整数。恰逢国庆节来临，皇后决定为 $n$ 位大臣颁发奖金，其中第 $i$ 位大臣所获得的奖金数目为第 $i - 1$ 位大臣所获得奖金数目与前 $i$ 位大臣左手上的数的和的较大值再加上第 $i$ 位大臣右手上的数。

形式化地讲：我们设第 $i$ 位大臣左手上的正整数为 $a_i$，右手上的正整数为 $b_i$，则第 $i$ 位大臣获得的奖金数目为 $c_i$ 可以表达为：

$$ c_{i} = \begin{cases} a_{1}+b_{1}  & ,i=1 \\ \displaystyle \max \left \{ c_{i-1},\sum_{j=1}^{i}a_{j} \right \} +b_{i} & ,2\leq i \leq n \end{cases} % ![](https://cdn.luogu.com.cn/upload/pic/1257.png) $$

当然，吝啬的皇后并不希望太多的奖金被发给大臣，所以她想请你来重新安排一下队伍的顺序，使得获得奖金最多的大臣，所获奖金数目尽可能的少。

注意：重新安排队伍并不意味着一定要打乱顺序，我们允许不改变任何一位大臣的位置。
## 输入格式

第一行包含一个正整数 $T$，表示测试数据的组数。

接下来 $T$ 个部分，每个部分的第一行包含一个正整数 $n$，表示大臣的数目。

每个部分接下来 $n$ 行中，每行两个正整数，分别为 $a_i$ 和 $b_i$，含义如上文所述。

## 输出格式

共 $T$ 行，每行包含一个整数，表示获得奖金最多的大臣所获得的奖金数目。

## 样例

### 样例输入 #1
```
1
3
4 1
2 2
1 2
```
### 样例输出 #1
```
8
```
### 样例输入 #2
```
2
5
85 100
95 99
76 87
60 97
79 85
12
9 68
18 45
52 61
39 83
63 67
45 99
52 54
82 100
23 54
99 94
63 100
52 68
```
### 样例输出 #2
```
528
902
```
## 提示

按照 $1,2,3$ 这样排列队伍，获得最多奖金的大臣获得奖金的数目为 $10$；

按照 $1,3,2$ 这样排列队伍，获得最多奖金的大臣获得奖金的数目为 $9$；

按照 $2,1,3$ 这样排列队伍，获得最多奖金的大臣获得奖金的数目为 $9$；

按照 $2,3,1$ 这样排列队伍，获得最多奖金的大臣获得奖金的数目为 $8$；

按照 $3,1,2$ 这样排列队伍，获得最多奖金的大臣获得奖金的数目为 $9$；

按照 $3,2,1$ 这样排列队伍，获得最多奖金的大臣获得奖金的数目为 $8$。

当按照 $3,2,1$ 这样排列队伍时，三位大臣左右手的数分别为：

$(1,2),(2,2),(4,1)$。

- 第 $1$ 位大臣获得的奖金为 $1+2=3$；
- 第 $2$ 位大臣获得的奖金为 $\max{3,3}+2=5$；
- 第 $3$ 为大臣获得的奖金为 $\max{5,7}+1=8$。

对于全部测试数据满足：$T\le10$，$1\le n\le 2\times 10^4$，$1\le a_i,b_i\le 10^9$。


---

---
title: "[SHOI2009] 舞会"
layout: "post"
diff: 省选/NOI-
pid: P2159
tag: ['动态规划 DP', '2009', '各省省选', '上海', '排序']
---
# [SHOI2009] 舞会
## 题目描述

OItown要举办了一年一度的超级舞会了，作为主办方的Constantine为了使今年的舞会规模空前，他邀请了许多他的好友和同学去。舞会那天，恰好来了n个男生n个女生。Constantine发现，一般情况下，舞伴之间，总是男伴总是比女伴长得高，不过，偶尔也是有特殊情况的。所以，Constantine现在想知道，如果把这2n个人恰好配成n对舞伴，有多少种搭配方法，而且他要求最多只有k对舞伴之间女伴比男伴高。现在，Constantine需要参加SHTSC的你帮助他算出这个答案，当然啦，他会先告诉你这2n个同学的身高。

## 输入格式

第一行：两个整数n、k，含义如问题中所示。 第2行到第n+1行：n个整数，表示n个男生的身高。 第n+2行到第2n+1行：n个整数，表示n个女生的身高。 表示身高的正整数，都不超过 。

## 输出格式

输出文件只有一个，即满足n对舞伴中最多只有k对舞伴之间女伴比男伴高的男女搭配方案数。

## 样例

### 样例输入 #1
```
3 0
178
188
176
168
178
170

```
### 样例输出 #1
```
4
```
## 提示

评分
如果你的输出文件与标准答案完全相符，你将获得该测试点的全部分数，否则得零分。


N< = 200

K< = N


---

---
title: "[SHOI2007] 书柜的尺寸"
layout: "post"
diff: 省选/NOI-
pid: P2160
tag: ['动态规划 DP', '数学', '2007', '各省省选', '上海', '排序']
---
# [SHOI2007] 书柜的尺寸
## 题目描述

Tom 不喜欢那种一字长龙式的大书架，他只想要一个小书柜来存放他的系列工具书。Tom 打算把书柜放在桌子的后面，这样需要查书的时候就可以不用起身离开了。

显然，这种书柜不能太大，Tom 希望它的体积越小越好。另外，出于他的审美要求，他只想要一个三层的书柜。为了物尽其用，Tom 规定每层必须至少放一本书。现在的问题是，Tom 怎么分配他的工具书，才能让木匠造出最小的书柜来呢？ 

Tom很快意识到这是一个数学问题。每本书都有自己的高度 $h_i$ 和厚度 $t_i$。我们需要求的是一个分配方案，也就是要求把所有的书分配在 $S_1$、$S_2$ 和 $S_3$ **三个非空集合**里面的一个，不重复也不遗漏，那么，很明显，书柜正面表面积（$S$）的计算公式就是：  

$$S=\left(\sum_{j=1}^3 \max_{i \in S_j} h_i\right) \times \left(\max_{j=1}^3 \sum_{i \in S_j} t_i\right) $$

由于书柜的深度是固定的（显然，它应该等于那本最宽的书的长度），所以要求书柜的体积最小就是**要求 $S$ 最小**。Tom 离答案只有一步之遥了。不过很遗憾，Tom 并不擅长于编程，于是他邀请你来帮助他解决这个问题。
## 输入格式

第一行一个整数 $n$，代表书本的个数。

接下来 $n$ 行每行有两个整数 $h_i$ 和 $t_i$，代表每本书的高度和厚度。
## 输出格式

只有一行，即输出最小的 $S$。
## 样例

### 样例输入 #1
```
4
220 29
195 20
200 9
180 30
```
### 样例输出 #1
```
18000
```
## 提示

对于全部数据，$3 \leq n \leq 70$，$150 \leq h_i \leq 300$，$5 \leq t_i \leq 30$。


---

---
title: "[HAOI2012] 道路"
layout: "post"
diff: 省选/NOI-
pid: P2505
tag: ['2012', '河南', '各省省选', '拓扑排序', '最短路']
---
# [HAOI2012] 道路
## 题目描述

C 国有 $n$ 座城市，城市之间通过 $m$ 条**单向**道路连接。一条路径被称为最短路，当且仅当不存在从它的起点到终点的另外一条路径总长度比它小。两条最短路不同，当且仅当它们包含的道路序列不同。我们需要对每条道路的重要性进行评估，评估方式为计算有多少条不同的最短路经过该道路。现在，这个任务交给了你。

## 输入格式

第一行包含两个正整数 $n, m$。

接下来 $m$ 行每行包含三个正整数 $u, v, w$，表示有一条从 $u$ 到 $v$ 长度为 $w$ 的道路

## 输出格式

输出应有 $m$ 行，第 $i$ 行包含一个数，代表经过第 $i$ 条道路的最短路的数目对 $10^9+7$ 取模后的结果。
## 样例

### 样例输入 #1
```
4 4
1 2 5
2 3 5
3 4 5
1 4 8
```
### 样例输出 #1
```
2
3
2
1
```
## 提示

数据规模

$30\%$ 的数据满足：$n\leq 15, m\leq 30$。

$60\%$ 的数据满足：$n\leq 300, m\leq 1000$。

$100\%$ 的数据满足：$n\leq 1500, m\leq 5000, w\leq 10000$。



---

---
title: "[ZJOI2012] 灾难"
layout: "post"
diff: 省选/NOI-
pid: P2597
tag: ['2012', '倍增', '各省省选', '浙江', 'O2优化', '拓扑排序', '最近公共祖先 LCA']
---
# [ZJOI2012] 灾难
## 题目背景

阿米巴是小强的好朋友。

阿米巴和小强在草原上捉蚂蚱。小强突然想，如果蚂蚱被他们捉灭绝了，那么吃蚂蚱的小鸟就会饿死，而捕食小鸟的猛禽也会跟着灭绝，从而引发一系列的生态灾难。

学过生物的阿米巴告诉小强，草原是一个极其稳定的生态系统。如果蚂蚱灭绝了，小鸟照样可以吃别的虫子，所以一个物种的灭绝并不一定会引发重大的灾难。
## 题目描述

我们现在从专业一点的角度来看这个问题。我们用一种叫做食物网的有向图来描述生物之间的关系：

- 一个食物网有 $n$ 个点，代表 $n$ 种生物，生物从 $1$ 到 $n$ 编号。
- 如果生物 $x$ 可以吃生物 $y$，那么从 $y$ 向 $x$ 连一个有向边。
- 这个图没有环。
- 图中有一些点没有连出边，这些点代表的生物都是生产者，可以通过光合作用来生存。
- 而有连出边的点代表的都是消费者，它们必须通过吃其他生物来生存。
- 如果某个消费者的所有食物都灭绝了，它会跟着灭绝。

我们定义一个生物在食物网中的“灾难值”为，如果它突然灭绝，那么会跟着一起灭绝的生物的种数。

举个例子：在一个草场上，生物之间的关系如下

![](https://cdn.luogu.com.cn/upload/image_hosting/oiw4lh97.png)

如果小强和阿米巴把草原上所有的羊都给吓死了，那么狼会因为没有食物而灭绝，而小强和阿米巴可以通过吃牛、牛可以通过吃草来生存下去。所以，羊的灾难值是 $1$。但是，如果草突然灭绝，那么整个草原上的 $5$ 种生物都无法幸免，所以，草的灾难值是 $4$。

给定一个食物网，你要求出每个生物的灾难值。
## 输入格式

第一行有一个整数，表示食物网的结点个数 $n$。

第 $2$ 到第 $(n + 1)$ 行，每行若干个互不相同的整数，第 $(i + 1)$ 行的整数 $a_{i, j}$ 表示编号为 $i$ 的生物可以吃编号为 $a_{i, j}$ 的生物。每行结尾有一个整数 $0$ 表示本行结束。
## 输出格式

输出 $n$ 行，每行一个整数，第 $i$ 行输出编号为 $i$ 的生物的灾难值。
## 样例

### 样例输入 #1
```
5
0
1 0
1 0
2 3 0
2 0

```
### 样例输出 #1
```
4
1
0
0
0
```
## 提示

### 样例 1 解释

样例输入描述了题目描述中举的例子。

### 数据规模与约定

- 对于 $50\%$ 的数据，保证 $n \leq 10^4$。
- 对于 $100\%$ 的数据，保证 $1 \leq n \leq 65534$，$1 \leq a_{i, j} \leq n$，输入的文件大小不超过 1 MB，且图上不存在环。


---

---
title: "[NOI2009] 植物大战僵尸"
layout: "post"
diff: 省选/NOI-
pid: P2805
tag: ['2009', 'NOI', '网络流', '图论建模', '拓扑排序', '最小割']
---
# [NOI2009] 植物大战僵尸
## 题目背景

Plants vs. Zombies（PVZ）是最近十分风靡的一款小游戏。Plants（植物）和 Zombies（僵尸）是游戏的主角，其中 Plants 防守，而 Zombies 进攻。该款游戏包含多种不同的挑战系列，比如 Protect Your Brain、Bowling 等等。其中最为经典的，莫过于玩家通过控制 Plants 来防守 Zombies 的进攻，或者相反地由玩家通过控制 Zombies 对 Plants 发起进攻。


## 题目描述

现在，我们将要考虑的问题是游戏中 Zombies 对 Plants 的进攻，请注意，本题中规则与实际游戏**有所不同**。游戏中有两种角色，Plants 和 Zombies，每个 Plant 有一个攻击位置集合，它可以对这些位置进行保护；而 Zombie 进攻植物的方式是走到植物所在的位置上并将其吃掉。

游戏的地图可以抽象为一个 $N$ 行 $M$ 列的矩阵，行从上到下用 $0$ 到 $N–1$ 编号，列从左到右用 $0$ 到 $M–1$ 编号；在地图的每个位置上都放有一个 $Plant$，为简单起见，我们把位于第 $r$ 行第 $c$ 列的植物记为 $P_{r, c}$。

Plants 分很多种，有「攻击类」「防守类」和「经济类」等等。为了简单的描述每个 Plant，定义 $\operatorname{Score}$ 和 $\operatorname{Attack}$ 如下：

* $\operatorname{Score}(P_{r, c})$ — Zombie 击溃植物 $P_{r, c}$ 可获得的能源。   
若 $\operatorname{Score}(P_{r, c})$ 为非负整数，则表示击溃植物 $P_{r, c}$ 可获得能源 $\operatorname{Score}(P_{r, c})$，若为负数表示击溃 $P_{r, c}$ 需要付出能源 $-\operatorname{Score}(P_{r, c})$。

* $\operatorname{Attack}(P_{r, c})$ — 植物 $P_{r, c}$ 能够对 Zombie 进行攻击的位置集合。

Zombies 必须从地图的右侧进入，且只能沿着水平方向进行移动。Zombies 攻击植物的唯一方式就是走到该植物所在的位置并将植物吃掉。因此 Zombies 的进攻总是从地图的右侧开始。也就是说，对于第 $r$ 行的进攻，Zombies 必须首先攻击 $P_{r, M-1}$；若需要对 $P_{r, c}$（$0 \le c < m - 1$）攻击，必须将 $P_{r,M-1}, P_{r, M-2} \cdots P_{r, c+1}$ 先击溃，并移动到位置 $(r, c)$ 才可进行攻击。

在本题的设定中，Plants 的攻击力是无穷大的，一旦 Zombie 进入某个 Plant 的攻击位置，该 Zombie 会被瞬间消灭，而该 Zombie 没有时间进行任何攻击操作。因此，即便 Zombie 进入了一个 Plant 所在的位置，但该位置属于其他植物的攻击位置集合，则 Zombie 会被瞬间消灭而所在位置的植物则安然无恙（在我们的设定中，Plant 的攻击位置不包含自身所在位置，否则你就不可能击溃它了）。

Zombies 的目标是对 Plants 的阵地发起进攻并获得最大的能源收入。每一次，你可以选择一个可进攻的植物进行攻击。本题的目标为，制定一套 Zombies 的进攻方案，选择进攻哪些植物以及进攻的顺序，从而获得最大的能源收入。
## 输入格式

第一行包含两个正整数 $N$ 和 $M$，分别表示地图的行数和列数。

接下来 $N \times M$ 行描述每个位置上植物的信息。第 $r \times M + c + 1$ 行按照如下格式给出植物 $P_{r, c}$ 的信息：

第一个整数为 $\operatorname{Score}(P_{r,c})$，第二个整数为集合 $\operatorname{Attack}(P_{r,c})$ 中的位置个数 $w$，接下来 $w$ 个位置信息 $(r', c')$，表示 $P_{r, c}$ 可以攻击位置第 $r'$ 行第 $c'$ 列。


## 输出格式

仅包含一个整数，表示可以获得的最大能源收入。注意，你也可以选择不进行任何攻击，这样能源收入为 $0$。
## 样例

### 样例输入 #1
```
3 2
10 0
20 0
-10 0
-5 1 0 0
100 1 2 1
100 0
```
### 样例输出 #1
```
25
```
## 提示

#### 数据规模与约定
- 对于 $20\%$ 的数据，保证 $ N, M \le 5$。
- 对于 $40\%$ 的数据，保证 $ N, M \le 10$。
- 对于 $100\%$ 的数据，保证 $1 \le N \le 20$，$1 \le M \le 30$，$-10^4 ≤ \operatorname{Score} \le 10^4$。

#### 说明
题面由 @syksykCCC 修改。


---

---
title: "[HEOI2016/TJOI2016] 排序"
layout: "post"
diff: 省选/NOI-
pid: P2824
tag: ['2016', '线段树', '二分', '各省省选', '河北', '排序']
---
# [HEOI2016/TJOI2016] 排序
## 题目描述

在 $2016$ 年，佳媛姐姐喜欢上了数字序列。因而她经常研究关于序列的一些奇奇怪怪的问题，现在她在研究一个难题，需要你来帮助她。  

这个难题是这样子的：给出一个 $1$ 到 $n$ 的排列，现在对这个排列序列进行 $m$ 次局部排序，排序分为两种：  

- `0 l r` 表示将区间 $[l,r]$ 的数字升序排序  
- `1 l r` 表示将区间 $[l,r]$ 的数字降序排序  

注意，这里是对**下标**在区间 $[l,r]$ 内的数排序。  
最后询问第 $q$ 位置上的数字。

## 输入格式

输入数据的第一行为两个整数 $n$ 和 $m$，$n$ 表示序列的长度，$m$ 表示局部排序的次数。  

第二行为 $n$ 个整数，表示 $1$ 到 $n$ 的一个排列。  

接下来输入 $m$ 行，每一行有三个整数 $\text{op},l,r$，$\text{op}$ 为 $0$ 代表升序排序，$\text{op}$ 为 $1$ 代表降序排序, $l,r$ 表示排序的区间。  

最后输入一个整数 $q$，表示排序完之后询问的位置

## 输出格式

输出数据仅有一行，一个整数，表示按照顺序将全部的部分排序结束后第 $q$ 位置上的数字。

## 样例

### 样例输入 #1
```
6 3
1 6 2 5 3 4
0 1 4
1 3 6
0 2 4
3
```
### 样例输出 #1
```
5
```
## 提示

河北省选2016第一天第二题。

对于 $30\%$ 的数据，$n,m\leq 1000$

对于 $100\%$ 的数据，$n,m\leq 10^5$，$1\leq q\leq n$


---

---
title: "[USACO10OPEN] Triangle Counting G"
layout: "post"
diff: 省选/NOI-
pid: P2992
tag: ['计算几何', '2010', 'USACO', '排序', '容斥原理']
---
# [USACO10OPEN] Triangle Counting G
## 题目描述

Bessie is standing guard duty after

the big bad wolf was spotted stalking

```cpp
cows over at Farmer Don's spread. 
Looking down from her guard tower in 
utter boredom, she's decided to 
perform intellectual exercises in 
```
order to keep awake.
After imagining the field as an X,Y

grid, she recorded the coordinates of

the N (1 <= N <= 100,000) 

conveniently numbered 1..N cows as

```cpp
X_i,Y_i (-100,000 <= X_i <= 100,000; 
-100,000 <= Y_i <= 100,000; 1 <= i <= 
N). She then mentally formed all possible triangles that could be made from subsets of the entire set of cow coordinates. She counts a triangle as 'golden' if it wholly contains the origin (0,0). The origin does not fall on the line between any pair of cows. Additionally, no cow is standing exactly on the origin. 
Given the list of cow locations, calculate the number of 'golden' triangles that contain the origin so Bessie will know if she's doing a good job. 
```
By way of example, consider 5 cows at these locations:
-5,0   0,2   11,2   -11,-6   11,-5

Below is a schematic layout of the field from Betsy's point of view:

```cpp
............|............ 
............*..........*. 
............|............ 
-------*----+------------ 
............|............ 
............|............ 
............|............ 
............|............ 
............|..........*. 
.*..........|............ 
............|............ 
```
All ten triangles below can be formed from the five points above:

By inspection, 5 of them contain the origin and hence are 'golden'.

在一只大灰狼偷偷潜入Farmer Don的牛群被群牛发现后，贝西现在不得不履行着她站岗的职责。从她的守卫塔向下瞭望简直就是一件烦透了的事情。她决定做一些开发智力的小练习，防止她睡着了。



想象牧场是一个X，Y平面的网格。她将N只奶牛标记为1…N (1 <= N <= 100,000)，每只奶牛的坐标为X\_i,Y\_i (-100,000 <= X\_i <= 100,000;-100,000 <= Y\_i <= 100,000; 1 <= i <=N)。然后她脑海里想象着所有可能由奶牛构成的三角形。如果一个三角形完全包含了原点(0,0)，那么她称这个三角形为“黄金三角形”。原点不会落在任何一对奶牛的连线上。另外，不会有奶牛在原点。

给出奶牛的坐标，计算出有多少个“黄金三角形”。

## 输入格式

\* Line 1: A single integer: N

\* Lines 2..N+1: Each line contains two integers, the coordinates of a single cow: X\_i and Y\_i

## 输出格式

\* Line 1: A single line with a single integer that is the count of the number of times a triangle formed by the cow locations contains the origin

## 样例

### 样例输入 #1
```
5 
-5 0 
0 2 
11 2 
-11 -6 
11 -5 

```
### 样例输出 #1
```
5 

```


---

---
title: "[USACO10DEC] Threatening Letter G"
layout: "post"
diff: 省选/NOI-
pid: P3002
tag: ['贪心', '2010', 'USACO', '排序']
---
# [USACO10DEC] Threatening Letter G
## 题目描述

FJ has had a terrible fight with his neighbor and wants to send him a nasty letter, but wants to remain anonymous. As so many before him have done, he plans to cut out printed letters and paste them onto a sheet of paper. He has an infinite number of the most recent issue of the Moo York Times that has N (1 <= N <= 50,000) uppercase letters laid out in a long string (though read in as a series of shorter strings). Likewise, he has a message he'd like to compose that is a single long string of letters but that is read in as a set of shorter strings.

Being lazy, he wants to make the smallest possible number of cuts. FJ has a really great set of scissors that enables him to remove any single-line snippet from the Moo York Times with one cut. He notices that he can cut entire words or phrases with a single cut, thus reducing his total number of cuts.

What is the minimum amount of cuts he has to make to construct his letter of M (1 <= M <= 50,000) letters?

It is guaranteed that it is possible for FJ to complete his task.

Consider a 38 letter Moo York Times:

```cpp
THEQUICKBROWNFOXDO 
GJUMPSOVERTHELAZYDOG 
from which FJ wants to construct a 9 letter message: 
FOXDOG 
DOG 
```
These input lines represent a pair of strings:
THEQUICKBROWNFOXDOGJUMPSOVERTHELAZYDOG 

FOXDOGDOG 

Since 'FOXDOG' exists in the newspaper, FJ can cut this piece out and then get the last 'DOG' by cutting out either instance of the word 'DOG'. 

Thus, he requires but two cuts.

FJ 刚刚和邻居发生了一场可怕的争吵，他咽不下这口气，于是决定佚名发给他的邻居一封脏话连篇的信。他有无限张完全相同的已经打印好的纸张，都包含 $N$ 个字母。他有一把举世无双的剪刀，可以从某张纸中通过一刀剪出连续的一段（也可以通过一刀获得整个字符串）。他想知道获得这封 $M$ 个字母的长信最少需要剪多少刀。保证这总是可能的。
## 输入格式

\* Line 1: Two space-separated integers: N and M

\* Lines 2..?: N letters laid out on several input lines; this is the text of the one copy of the Moo York Times. Each line will have no more than 80 characters.

\* Lines ?..?: M letters that are the text of FJ's letter. Each line will have no more than 80 characters.

## 输出格式

\* Line 1: The minimum number of cuts FJ has to make to create his message

## 样例

### 样例输入 #1
```
38 9 
THEQUICKBROWNFOXDO 
GJUMPSOVERTHELAZYDOG 
FOXDOG 
DOG 

```
### 样例输出 #1
```
2 

```


---

---
title: "[CQOI2012] 组装"
layout: "post"
diff: 省选/NOI-
pid: P3162
tag: ['数学', '贪心', '2012', '重庆', '各省省选', '排序']
---
# [CQOI2012] 组装
## 题目描述

数轴上有 $m$ 个生产车间可以生产零件。一共有 $n$ 种零件，编号为 $1\sim n$。第 $i$ 个车间的坐标为 $x_i$ ，生产第 $p_i$ 种零件（$1\le p_i\le n$）。你需要在数轴上的某个位置修建一个组装车间，把这些零件组装起来。为了节约运输成本，你需要最小化 $cost_1+cost_2+\ldots+cost_n$，其中 $cost_x$ 表示生产第 $x$ 种零件的车间中，到组装车间距离的平方的最小值。
## 输入格式

输入第一行为两个整数 $n$, $m$ ，即零件的种类数和生产车间的个数。以下 $m$ 行每行两个整数 $x_i$ 和 $p_i$（$1\le p_i\le n$）。输入按照生产车间从左到右的顺序排列（即 $x_i\le x_{i+1}$ 。注意车间位置可以重复）。输入保证每种零件都有车间生产。
## 输出格式

输出仅一行，即组装车间的最优位置（可以和某个生产车间重合），四舍五入保留四位小数。输入保证最优位置惟一。

## 样例

### 样例输入 #1
```
3 5
-1 3
0 1
2 3
4 2
5 2
```
### 样例输出 #1
```
2.0000
```
## 提示

- 测试点 $1 \sim 4$，满足 $n\le 15$，$m\le 25$，$x_i\le100$；
- 测试点 $5 \sim 10$，满足 $n\le 10^4,m\le 10^5,x_i\le10^5$。


---

---
title: "[HNOI2011] 数矩形"
layout: "post"
diff: 省选/NOI-
pid: P3217
tag: ['计算几何', '2011', '湖南', '枚举', '排序']
---
# [HNOI2011] 数矩形
## 题目描述

最近某歌手在研究自己的全球巡回演出计划，他将所有心仪的城市都用平面上的一个点来表示，并打算从中挑选出 4 个城市作为这次巡回演出的地点。

为了显示自己与众不同，他要求存在一个矩形使得挑选出的 4 个点恰好是这个矩形的 4 个顶点，并且希望这个矩形的面积最大。

这可急坏了其经纪人，于是他向全球歌迷征集方案，当然你这位歌迷一定不会错过这个机会。

## 输入格式

从文件input.txt中读入数据，输入文件的第一行是一个正整数$N$，表示平面上点的个数(即某歌手心仪的城市数)。接下来的$N$行，每行是由空格隔开的两个整数$X_i$和$Y_i$,表示其对应点的坐标。20%的数据满足$N\leq 500$，100%的数据满足$N\leq 1500$，$-10^8\leq X_i,Y_i\leq 10^8$，且输入数据保证答案存在。

## 输出格式

输出文件 output.txt 仅包含一个非负整数，表示最大的矩形面积。

## 样例

### 样例输入 #1
```
8
-2 3
-2 -1
0 3
0 -1
1 -1
2 1 
-3 1 
-2 1

```
### 样例输出 #1
```
10
```


---

---
title: "[HNOI2015] 落忆枫音"
layout: "post"
diff: 省选/NOI-
pid: P3244
tag: ['动态规划 DP', '递推', '2015', '湖南', '拓扑排序']
---
# [HNOI2015] 落忆枫音
## 题目背景

「恒逸，你相信灵魂的存在吗？」 郭恒逸和姚枫茜漫步在枫音乡的街道上。望着漫天飞舞的红枫，枫茜突然问出这样一个问题。

「相信吧。不然我们是什么，一团肉吗？要不是有灵魂......我们也不可能再见到你姐姐吧。」 恒逸给出了一个略微无厘头的回答。枫茜听后笑了笑。 「那你仔细观察过枫叶吗？」 说罢，枫茜伸手，接住了一片飘落的枫叶。

「其实每一片枫叶都是有灵魂的。你看，枫叶上不是有这么多脉络吗？我听说，枫叶上有一些特殊的位置，就和人的穴位一样。脉络都是连接在这些穴位之间的。枫树的灵魂流过每片枫叶的根部，沿着这些脉络，慢慢漫进穴位，沁入整片枫叶。也是因为这个原因，脉络才都是单向的，灵魂可不能倒着溜回来呢。」 恒逸似懂非懂地点了点头。枫茜接着说了下去。

「正是因为有了灵魂，每片枫叶才会与众不同。也正是因为有了灵魂，每片枫叶也都神似其源本的枫树，就连脉络也形成了一棵树的样子。但如果仔细看的话，会发现，在脉络树之外，还存在其它的非常细的脉络。虽然这些脉络并不在树上，但他们的方向也同样顺着灵魂流淌的方向，绝不会出现可能使灵魂倒流的回路。」  恒逸好像突然想到了什么。 「那这些脉络岂不是可以取代已有的脉络，出现在脉络树上？」 枫茜闭上了眼睛。

「是啊，就是这样。脉络树并不是唯一的。只要有一些微小的偏差，脉络树就可能差之万里，哪怕是在这同一片枫叶上。就像我们的故事，结局也不是唯一的。只要改变一个小小的选项，故事流程可能就会被彻底扭转。」

「真是深奥啊......」 恒逸盯着这片红枫，若有所思地说。枫茜继续说道。

「还不止如此呢。所有的脉络都不会永恒存在，也不会永恒消失。不管是脉络树上的脉络，还是之外的细小脉络，都是如此。存在的脉络可能断开消失，消失的脉络也可能再次连接。万物皆处在永恒的变化之中，人与人之间的羁绊也是。或许有一天，我们与大家的羁绊也会如同脉络一样，被无情地斩断。或许我们也终将成为”枫音乡的过客“。或许这一切都会是必然，是枫树的灵魂所决定的......」

枫茜的眼角泛起了几滴晶莹剔透的泪珠。恒逸看着这样的枫茜，将她抱入怀中。

「别这样想，枫茜。就算脉络断开，也有可能还会有新的脉络树，也还会与枫树的根相连。这样的话，我们的羁绊仍然存在，只是稍微绕了一些远路而已。无论如何，我都不会离开你的。因为你是我穷尽一生所寻找的，我的真恋啊！」

两人的目光对上了。枫茜幸福地笑了，把头埋进了恒逸的怀抱。从远方山上的枫林中，传来了枫的声音。
## 题目描述

不妨假设枫叶上有 $n$ 个穴位，穴位的编号为 $1\sim n$。有若干条有向的脉络连接着这些穴位。

穴位和脉络组成一个有向无环图——称之为**脉络图**（例如图 $1$），穴位的编号使得穴位 $1$ 没有从其他穴位连向它的脉络，即穴位 $1$ 只有连出去的脉络；由上面的故事可知，这个有向无环图存在一个树形子图，它是以穴位 $1$ 为根的包含全部 $n$ 个穴位的一棵树——称之为**脉络树**（例如图 $2$ 和图 $3$ 给出的树都是图 $1$ 给出的脉络图的子图）。

值得注意的是，脉络图中的脉络树方案可能有多种可能性，例如图 $2$ 和图 $3$ 就是图 $1$ 给出的脉络图的两个脉络树方案。

 ![](https://cdn.luogu.com.cn/upload/pic/11330.png) 

脉络树的形式化定义为：以穴位 $r$ 为根的脉络树由枫叶上全部 $n$ 个穴位以及 $(n-1)$ 条脉络组成，脉络树里没有环，亦不存在从一个穴位连向自身的脉络，且对于枫叶上的每个穴位 $s$，都存在一条唯一的包含于脉络树内的脉络路径，使得从穴位 $r$ 出发沿着这条路径可以到达穴位  $s$。 

现在向脉络图添加一条与已有脉络不同的脉络（**注意：连接 $2$ 个穴位但方向不同的脉络是不同的脉络**，例如从穴位 $3$ 到 $4$ 的脉络与从 $4$ 到 $3$ 的脉络是不同的脉络，因此，图 $1$ 中不能添加从 $3$ 到 $4$ 的脉络，但可添加从 $4$ 到 $3$ 的脉络）。这条新脉络**可以是从一个穴位连向自身的**（例如，图 1 中可添加从 $4$ 到 $4$ 的脉络）。

原脉络图添加这条新脉络后得到的新脉络图可能会出现脉络构成的环。 请你求出添加了这一条脉络之后的新脉络图的以穴位 $1$ 为根的脉络树方案数。

由于方案可能有太多太多，请输出方案数对 $(10^9+7)$ 取模后得到的结果。
## 输入格式

输入文件的第一行包含四个整数 $n,m,x,y$，依次代表枫叶上的穴位数、脉络数，以及要添加的脉络是从穴位 $x$ 连向穴位 $y$ 的。 

接下来 $m$ 行，每行两个整数，由空格隔开，代表一条脉络。

第 $i$ 行的两个整数为 $u_i$ 和 $v_i$，代表第 $i$ 条脉络是从穴位 $u_i$ 连向穴位 $v_i$ 的。
## 输出格式

输出一行，为添加了从穴位 $x$ 连向穴位 $y$ 的脉络后，枫叶上以穴位 $1$ 为根的脉络树的方案数对 $(10^9+7)$ 取模得到的结果。

## 样例

### 样例输入 #1
```
4 4 4 3
1 2
1 3
2 4
3 2
```
### 样例输出 #1
```
3
```
## 提示

对于所有测试数据，保证：

- $1 \leq n \leq 100000$；
- $n - 1 \leq m \leq \min(200000, n(n -1)/2)$；
- $1 \leq x, y, u_i, v_i \leq n$。

Fixed by Starrykiller.


---

---
title: "[HNOI2016] 大数"
layout: "post"
diff: 省选/NOI-
pid: P3245
tag: ['字符串', '2016', '离散化', '湖南', '排序']
---
# [HNOI2016] 大数
## 题目描述

小 B 有一个很大的数 $S$，长度达到了 $n$ 位；这个数可以看成是一个数字串，它可能有前导 $0$，例如 `00009312345`。小 B 还有一个素数 $p$。现在，小 B 提出了 $m$ 个询问，每个询问求 $S$ 的一个子串中有多少子串是 $p$ 的倍数（$0$ 也是 $p$ 的倍数）。例如 $S$ 为 `0077` 时，其子串 `007` 有 $6$ 个子串：`0,0,7,00,07,007`；显然 `0077` 的子串 `007` 有 $6$ 个子串都是素数 $7$ 的倍数。
## 输入格式

第一行一个整数：$p$。

第二行一个数字串：$S$。

第三行一个整数：$m$。接下来 $m$ 行，每行两个整数 $fr,to$，表示对 $S$ 的子串 $S[fr\dots to]$ 的一次询问。注意：$S$ 的最左端的数字的位置序号为 $1$；例如 $S$ 为 `213567`，则 $S[1\dots 3]$ 为 `213`。

## 输出格式

输出 $m$ 行，每行一个整数，第 $i$ 行是第 $i$ 个询问的答案。
## 样例

### 样例输入 #1
```
11
121121
3
1 6
1 5
1 4
```
### 样例输出 #1
```
5

3

2

//第一个询问问的是整个串，满足条件的子串分别有：121121,2112,11,121,121。
```
## 提示

#### 样例 1 解释

第一个询问问的是整个串，满足条件的子串分别有：`121121,2112,11,121,121`。

#### 数据范围

对于 $100\%$ 的数据，$1\le n,m\le 2\times 10^5$，$2\le p\le 10^9$，$S$ 中只有数字字符，$p$ 为素数。


---

---
title: "[POI 2006] PRO-Professor Szu"
layout: "post"
diff: 省选/NOI-
pid: P3436
tag: ['动态规划 DP', '2006', 'POI（波兰）', '拓扑排序', 'Tarjan']
---
# [POI 2006] PRO-Professor Szu
## 题目描述

某大学校内有一栋主楼，还有 $n$ 栋住宅楼。这些楼之间由一些单向道路连接，但是任意两栋楼之间可能有多条道路，也可能存在起点和终点为同一栋楼的环路。存在住宅楼无法到达主楼的情况。

现在有一位古怪的教授，他希望每天去主楼上班的路线不同。

一条上班路线中，每栋楼都可以访问任意多次。我们称两条上班路线是**不同的**，当且仅当两条路线中存在一条路是不同的（两栋楼之间的多条道路被视为是不同的道路）。

现在教授希望知道，从哪些住宅楼前往主楼的上班路线数最多。
## 输入格式

第一行两个整数 $n,m$，分别为大学内住宅楼的数量和道路的数量。大学内所有住宅楼编号为 $1 \sim n$，主楼编号为 $n+1$。

接下来 $m$ 行，第 $i$ 行两个整数 $u_i,v_i$，代表大学内存在一条从 $u_i$ 号楼到 $v_i$ 号楼的道路。
## 输出格式

第一行：如果存在一栋楼到主楼的上班路线数超过了 $36500$，输出 `zawsze`。否则输出一个整数，代表从一栋住宅楼前往主楼的最多上班路线数。

第二行：输出一个整数 $p$，代表有多少栋住宅楼能使前往主楼的上班路线数最大化。特别地，如果最大上班路线数超过了 $36500$，那么这一行请输出能使上班路线数超过 $36500$ 的住宅楼的数量。

第三行：按编号从小到大的顺序输出 $p$ 个整数，代表能使前往主楼的上班路线最大化的住宅楼的编号。特别地，如果最大上班路线数超过了 $36500$，那么这一行请输出所有能使上班路线数超过 $36500$ 的住宅楼的编号。
## 样例

### 样例输入 #1
```
3 5
1 2
1 3
2 3
3 4
3 4
```
### 样例输出 #1
```
4
1
1
```
## 题目翻译

$1 \leq n,m \leq 10^6$，$1 \leq u_i,v_i \leq n+1$。


---

---
title: "[POI 2015] PUS"
layout: "post"
diff: 省选/NOI-
pid: P3588
tag: ['2015', '线段树', 'POI（波兰）', 'Special Judge', '记忆化搜索', '拓扑排序']
---
# [POI 2015] PUS
## 题目描述

给定一个长度为 $n$ 的正整数序列 $a$，每个数都在 $1$ 到 $10^9$ 范围内，告诉你其中 $s$ 个数，并给出 $m$ 条信息，每条信息包含三个数 $l,r,k$ 以及接下来 $k$ 个正整数，表示 $a_l, a_{l+1}, \ldots, a_{r-1}, a_r$ 里这 $k$ 个数中的任意一个都比任意一个剩下的 $r-l+1-k$ 个数大（严格大于，即没有等号）。

请任意构造出一组满足条件的方案，或者判断无解。
## 输入格式

第一行包含三个正整数 $n,s,m$（$1 \leq s \leq n  \leq 10^5$，$1 \leq m \leq 2 \times 10^5$）。接下来 $s$ 行，每行包含两个正整数 $p_i,d_i$,表示已知 $a_{p_i}=d_i$，保证 $p_i$ 递增。

接下来 $m$ 行,每行一开始为三个正整数 $l_i,r_i,k_i$）$1 \leq l_i < r_i \leq n$，$1 \leq k_i \leq r_i-l_i$），接下来 $k_i$ 个正整数 $x_1..x_2...x_{k_i}$（$l_i \leq x_1 < x_2 < ... < x_{k_i} \leq r_i$），表示这 $k_i$ 个数中的任意一个都比任意一个剩下的 $r_i-l_i+1-k_i$ 个数大。（$\sum k \leq 3 \times 10^5$）
## 输出格式

若无解，则输出 `NIE`。否则第一行输出 `TAK`，第二行输出 $n$ 个正整数，依次输出序列 $a$ 中每个数。
## 样例

### 样例输入 #1
```
5 2 2
2 7
5 3
1 4 2 2 3
4 5 1 4
```
### 样例输出 #1
```
TAK
6 7 1000000000 6 3
```
### 样例输入 #2
```
3 2 1
2 3
3 5
1 3 1 2

```
### 样例输出 #2
```
NIE

```
### 样例输入 #3
```
2 1 1
1 1000000000
1 2 1 2
```
### 样例输出 #3
```
NIE

```
## 提示

原题名称：Pustynia。

本题另外提供两组额外样例，可以在附件中下载。


---

---
title: "[APIO2010] 信号覆盖"
layout: "post"
diff: 省选/NOI-
pid: P3630
tag: ['2010', 'APIO', 'Special Judge', '枚举', '排序']
---
# [APIO2010] 信号覆盖
## 题目描述

一家电信公司正在北京城搭建一个 GSM 网络。城市里共有 n 个房子需要被 信号覆盖。由于经费的限制，电信公司只能安装一个天线。 这里将每个房子用一个点坐标来表示。为了简化天线的放置，电信公司将会 选择其中的 3 个房子作一个外接圆，然后将天线放在圆的中心，所有位于这个圆 内或者圆的边界上的房子都将被天线的信号所覆盖。 电信公司将会随机选择城市中的 3 个房子来搭建天线，他们想知道在所有可 能放置天线的方案中平均会有多少个房子被信号覆盖。 例如，假设共有 4 个房子 A, B, C, D，它们的位置如下图：

  ![](https://cdn.luogu.com.cn/upload/pic/4405.png) 

如果我们选择ABC或者BCD三个点搭建的外接圆，所有的房子都会被覆盖。 如果我们选择 ACD 或者 ABD，剩下的房子将不会在天线的信号覆盖范围内。因 此平均有(4 + 4 + 3 + 3) / 4 = 3.50 个房子被信号覆盖。 给定所有房子的位置，你的任务是计算平均有多少个房子被信号覆盖。假定 每一个房子都有一个二维的整数坐标，并且保证任何三个房子都不在同一条直线 上，任何四个房子都不在同一个圆上。

## 输入格式

输入第一行包含一个正整数 n, 表示房子的总数。接下来有 n 行，分别表示 每一个房子的位置。对于 i = 1, 2, .., n, 第 i 个房子的坐标用一对整数 xi和 yi来表 示，中间用空格隔开。

## 输出格式

输出文件包含一个实数，表示平均有多少个房子被信号所覆盖，需保证输出 结果与精确值的绝对误差不超过 0.01。

## 样例

### 样例输入 #1
```
4
0 2 
4 4 
0 0 
2 0
```
### 样例输出 #1
```
3.500 
```
## 提示

【样例说明】

3.5, 3.50, 3.500, … 中的任何一个输出均为正确。此外，3.49, 3.51, 3.499999，…等也都是可被接受的输出。

【数据范围】

100%的数据保证，对于 i = 1, 2, .., n, 第 i 个房子的坐标(xi, yi)为整数且 –1,000,000 ≤ xi, yi ≤ 1,000,000. 任何三个房子不在同一条直线上，任何四个房子不 在同一个圆上；

40%的数据，n ≤ 100；

70%的数据，n ≤ 500；

100%的数据，3 ≤ n ≤ 1,500。



---

---
title: "Bushiroad的偶像派对"
layout: "post"
diff: 省选/NOI-
pid: P3696
tag: ['贪心', '排序', '洛谷月赛']
---
# Bushiroad的偶像派对
## 题目背景

Bushiroad又叫不许摸。

## 题目描述

Bushiroad的派对有N个校园偶像团体，可能来自编号1-N的学校。每个学校可能有多个团体参加，也有可能没有团体参加。在所有的团体都演出完后，进行人气投票。

我们已经掌握了中场时和结束时的两张人气排行表。给出排行表从人气高到低排序，并给出每个组的学校编号（你却不知道具体是哪个团体）

可是，结束时的表是不太准确的。因为基于这样的一个事实：某个团体的结束时的人气不会低于中场的人气，而且每个团体的学校不会改变。结束的表产生一些矛盾。

负责统计的人为了不想背锅，希望尽可能少修改结束时的排行表的某些团体的学校（人气值不能改），使其不矛盾，请问至少要修改多少个呢？

## 输入格式

第一行一个整数N，表示有N个团体。

接下来N行，每行两个整数，$Ta_i, Pa_i$，表示中场时的人气值排行，$Ta_i$表示学校名。$Pa_i$表示人气值，按照人气值高往低排列。

接下来N行，每行两个整数，$Tb_i, Pb_i$，表示结束时的人气值排行。

## 输出格式

一个整数表示答案。

## 样例

### 样例输入 #1
```
3
3 500
2 200
1 100
1 1000
3 700
3 400
```
### 样例输出 #1
```
1
```
## 提示

【数据范围】

对于20%的数据， $N\le16$，时限0.5s。

对于40%的数据， $N\le50$，时限0.5s。

对于70%的数据， $N\le5000$，时限1s。

对于全部测试数据， $N\le200000, A\le10^9$。最后3个点时限3s。



---

---
title: "[AH2017/HNOI2017] 影魔"
layout: "post"
diff: 省选/NOI-
pid: P3722
tag: ['2017', '线段树', '各省省选', '湖南', '排序', '栈']
---
# [AH2017/HNOI2017] 影魔
## 题目背景

影魔，奈文摩尔，据说有着一个诗人的灵魂。事实上，他吞噬的诗人灵魂早已成千上万。

千百年来，他收集了各式各样的灵魂，包括诗人、牧师、帝王、乞丐、奴隶、罪人，当然，还有英雄。

每一个灵魂，都有着自己的战斗力，而影魔，靠这些战斗力提升自己的攻击。
## 题目描述

奈文摩尔有 $n$ 个灵魂，他们在影魔宽广的体内可以排成一排，从左至右标号 $1$ 到 $n$。第 $i$ 个灵魂的战斗力为 $k_i$，灵魂们以点对的形式为影魔提供攻击力。对于灵魂对 $i, j\ (i<j)$ 来说，若不存在 $k_s\ (i<s<j)$ 大于 $k_i$ 或者 $k_j$，则会为影魔提供 $p_1$ 的攻击力。另一种情况，令 $c$ 为 $k_{i + 1}, k_{i + 2}, \cdots, k_{j -1}$ 的最大值，若 $c$ 满足：$k_i < c < k_j$，或者 $k_j < c < k_i$，则会为影魔提供 $p_2$ 的攻击力，当这样的 $c$ 不存在时，自然不会提供这 $p_2$ 的攻击力；其他情况的点对，均不会为影魔提供攻击力。

影魔的挚友噬魂鬼在一天造访影魔体内时被这些灵魂吸引住了，他想知道，对于任意一段区间 $[a, b]$，位于这些区间中的灵魂对会为影魔提供多少攻击力，即考虑所有满足 $a\le i<j\le b$ 的灵魂对 $i, j$ 提供的攻击力之和。

顺带一提，灵魂的战斗力组成一个 $1$ 到 $n$ 的排列：$k_1, k_1, \cdots, k_n$。
## 输入格式

第一行四个整数 $n,m,p_1,p_2$。  

第二行 $n$ 个整数 $k_1, k_2,\cdots, k_n$。

接下来 $m$ 行,每行两个数 $a,b$，表示询问区间 $[a,b]$ 中的灵魂对会为影魔提供多少攻击力。
## 输出格式

共输出 $m$ 行，每行一个答案，依次对应 $m$ 个询问。
## 样例

### 样例输入 #1
```
10 5 2 3
7 9 5 1 3 10 6 8 2 4
1 7
1 9
1 3
5 9
1 5
```
### 样例输出 #1
```
30
39
4
13
16
```
## 提示

对于 $30\%$ 的数据，$1\le n, m\le 500$。

另有 $30\%$ 的数据，$p_1 = 2p_2$。

对于 $100\%$ 的数据，$1\le n,m\le 200000, 1\le p_1, p_2\le 1000$。


---

---
title: "[HAOI2017] 供给侧改革"
layout: "post"
diff: 省选/NOI-
pid: P3732
tag: ['2017', '河南', '各省省选', '排序', '进制', '字典树 Trie']
---
# [HAOI2017] 供给侧改革
## 题目描述

你调查了某个产业近来 $n$ 个时期的供求关系平衡情况，每个时期的情况都用 $0$ 或 $1$ 中的一个数字来表示。于是这就是—个长度为 $n$ 的 $\texttt{01}$ 字符串 $S$。为了更好的了解这一些数据，你需要解决一些询问，我们令 $\text{data}(L,R)$ 表示：在字符串 $S$ 中，起始位置在 $[L,R]$ 之间的这些后缀之中，具有最长公共前缀的两个后缀的最长公共前缀的长度。

对于每一个询问 $L,R$，求：

$$ans = \sum_{L \leqslant i < R} \text{data}(i,R)$$

数据范围保证，串 $S$ 中的每一位都是在 $0$ 和 $1$ 之间随机产生的。
## 输入格式

第一行 $2$ 个整数 $n,Q$，表示字符串的长度，以及询问个数。

接下来一行长度为 $n$ 的一个 $\texttt{01}$ 串 $S$。

接下来 $Q$ 行，每行 $2$ 个整数 $L,R$，一个询问 $L,R$。
## 输出格式


共 $Q$ 行，每行一个整数，表示对应询问的答案。
## 样例

### 样例输入 #1
```
6 3
010110
2 5
1 6
1 2
```
### 样例输出 #1
```
4
6
0
```
## 提示

【数据规模与约定】

|数据点|$n$ 的规模|$Q$ 的规模|
|:-:|:-:|:-:|
|$1,2$|$\leqslant 20$|$\leqslant 20$|
|$3,4$|$\leqslant 100$|$\leqslant 100$|
|$5,6$|$\leqslant 5 \times 10^3$|$\leqslant 5 \times 10^3$|
|$7,8,9,10$|$\leqslant 10^5$|$\leqslant 10^5$|



对于所有的数据保证：$n \leqslant 10^5$，$Q \leqslant 10^5$，$1 \leqslant L < R \leqslant n$，$\texttt{01}$ 串随机生成。


---

---
title: "[CH弱省胡策R2] TATT"
layout: "post"
diff: 省选/NOI-
pid: P3769
tag: ['线段树', '平衡树', '分治', '排序', 'K-D Tree']
---
# [CH弱省胡策R2] TATT
## 题目描述

四维空间真是美妙。现在有 $n$ 个四维空间中的点，请求出一条最长的路径，满足任意一维坐标都是单调不降的。

注意路径起点是任意选择的，并且路径与输入顺序无关（路径顺序不一定要满足在输入中是升序）。

**路径的长度是经过的点的数量，任意点只能经过一次。**
## 输入格式

第一行一个整数 $n$。接下来 $n$ 行，每行四个整数 $a_i,b_i,c_i,d_i$。表示四维坐标。
## 输出格式

一行一个整数，表示最长路径的长度。
## 样例

### 样例输入 #1
```
4
2 3 33 2333
2 3 33 2333
2 3 33 2333
2 3 33 2333

```
### 样例输出 #1
```
4

```
## 提示

记 $m_i=\max(|a_i|,|b_i|,|c_i|,|d_i|),m=\max(m_i)$
|  测试点编号| $n\le$ | $m\le$ | 特殊说明 |
| :----------: | :----------: | :----------: | :----------: |
| $1$ | $2000$ | $10^9$ |  |
| $2$ |$5\times 10^4$  | $8$ |  |
| $3\sim 4$ | $5\times 10^4$ | $10^5$ |  所有点的第三，四维坐标相同|
| $5\sim 6$| $5\times 10^4$ | $10^5$ |  所有点的第四维坐标相同 |
| $7\sim 8$ | $5\times 10^4$ |$100$  |  |
|  $9\sim 10$| $5\times 10^4$ | $10^9$ |  |


---

---
title: "【模板】后缀排序"
layout: "post"
diff: 省选/NOI-
pid: P3809
tag: ['字符串', 'O2优化', '排序', '后缀数组 SA']
---
# 【模板】后缀排序
## 题目背景

这是一道模板题。

## 题目描述

读入一个长度为 $ n $ 的由大小写英文字母或数字组成的字符串，请把这个字符串的所有非空后缀按字典序（用 ASCII 数值比较）从小到大排序，然后按顺序输出后缀的第一个字符在原串中的位置。位置编号为 $ 1 $ 到 $ n $。

## 输入格式

一行一个长度为 $ n $ 的仅包含大小写英文字母或数字的字符串。

## 输出格式

一行，共 $n$ 个整数，表示答案。

## 样例

### 样例输入 #1
```
ababa
```
### 样例输出 #1
```
5 3 1 4 2
```
## 提示

$1\le n \le 10^6$。



---

---
title: "【模板】三维偏序（陌上花开）"
layout: "post"
diff: 省选/NOI-
pid: P3810
tag: ['树状数组', 'cdq 分治', 'O2优化', '分治', '排序', '整体二分', 'K-D Tree']
---
# 【模板】三维偏序（陌上花开）
## 题目背景

这是一道模板题，可以使用 bitset，CDQ 分治，KD-Tree 等方式解决。
## 题目描述

有 $ n $ 个元素，第 $ i $ 个元素有 $ a_i,b_i,c_i $ 三个属性，设 $ f(i) $ 表示满足 $ a_j \leq a_i $ 且 $ b_j \leq b_i $ 且 $ c_j \leq c_i $ 且 $ j \ne i $ 的 $j$ 的数量。

对于 $ d \in [0, n) $，求 $ f(i) = d $ 的数量。
## 输入格式

第一行两个整数 $ n,k $，表示元素数量和最大属性值。

接下来 $ n $ 行，每行三个整数 $ a_i ,b_i,c_i $，分别表示三个属性值。
## 输出格式

$ n $ 行，第 $ d + 1 $ 行表示 $ f(i) = d $ 的 $ i $ 的数量。
## 样例

### 样例输入 #1
```
10 3
3 3 3
2 3 3
2 3 1
3 1 1
3 1 2
1 3 1
1 1 2
1 2 2
1 3 2
1 2 1

```
### 样例输出 #1
```
3
1
3
0
1
0
1
0
0
1

```
## 提示

$ 1 \leq n \leq 10^5$，$1 \leq a_i, b_i, c_i \le k \leq 2 \times 10^5 $。



---

---
title: "[NOI2017] 游戏"
layout: "post"
diff: 省选/NOI-
pid: P3825
tag: ['2017', 'NOI', 'Special Judge', 'O2优化', '拓扑排序', '2-SAT', '强连通分量']
---
# [NOI2017] 游戏
## 题目背景

【本题原题时限 1s】

狂野飙车是小 L 最喜欢的游戏。与其他业余玩家不同的是，小 L 在玩游戏之余，还精于研究游戏的设计，因此他有着与众不同的游戏策略。

## 题目描述

小 L 计划进行 $n$ 场游戏，每场游戏使用一张地图，小 L 会选择一辆车在该地图上完成游戏。

小 L 的赛车有三辆，分别用大写字母 $A$、$B$、$C$ 表示。地图一共有四种，分别用小写字母 $x$、$a$、$b$、$c$ 表示。

其中，赛车 $A$ 不适合在地图 $a$ 上使用，赛车 $B$ 不适合在地图 $b$ 上使用，赛车 $C$ 不适合在地图 $c$ 上使用，而地图 $x$ 则适合所有赛车参加。

适合所有赛车参加的地图并不多见，最多只会有 $d$ 张。

$n$ 场游戏的地图可以用一个小写字母组成的字符串描述。例如：$S=\texttt{xaabxcbc}$ 表示小 L 计划进行 $8$ 场游戏，其中第 $1$ 场和第 $5$ 场的地图类型是 $x$，适合所有赛车，第 $2$ 场和第 $3$ 场的地图是 $a$，不适合赛车 $A$，第 $4$ 场和第 $7$ 场的地图是 $b$，不适合赛车 $B$，第 $6$ 场和第 $8$ 场的地图是 $c$，不适合赛车 $C$。

小 L 对游戏有一些特殊的要求，这些要求可以用四元组 $ (i, h_i, j, h_j) $ 来描述，表示若在第 $i$ 场使用型号为 $h_i$ 的车子，则第 $j$ 场游戏要使用型号为 $h_j$ 的车子。

你能帮小 L 选择每场游戏使用的赛车吗？如果有多种方案，输出任意一种方案。

如果无解，输出 `-1`。
## 输入格式

输入第一行包含两个非负整数 $n$, $d$。

输入第二行为一个字符串 $S$。

$n$, $d$, $S$ 的含义见题目描述，其中 $S$ 包含 $n$ 个字符，且其中恰好 $d$ 个为小写字母 $x$。

输入第三行为一个正整数 $m$ ，表示有 $m$ 条用车规则。

接下来 $m$ 行，每行包含一个四元组 $i,h_i,j,h_j$ ，其中 $i,j$ 为整数，$h_i,h_j$ 为字符 $A$ 、$B$ 或 $C$，含义见题目描述。
## 输出格式

输出一行。

若无解输出 `-1`。

若有解，则包含一个长度为 $n$ 的仅包含大写字母 A、B、C 的字符串，表示小 L 在这 $n$ 场游戏中如何安排赛车的使用。如果存在多组解，输出其中任意一组即可。
## 样例

### 样例输入 #1
```
3 1
xcc
1
1 A 2 B
```
### 样例输出 #1
```
ABA
```
## 提示

### 样例 1 解释

小 $L$ 计划进行 $3$ 场游戏，其中第 $1$ 场的地图类型是 $x$，适合所有赛车，第 $2$ 场和第 $3$ 场的地图是 $c$，不适合赛车 $C$。

小 $L$ 希望：若第 $1$ 场游戏使用赛车 $A$，则第 $2$ 场游戏使用赛车 $B$。

那么为这 $3$ 场游戏分别安排赛车 $A$、$B$、$A$ 可以满足所有条件。

若依次为 $3$ 场游戏安排赛车为 $BBB$ 或 $BAA$ 时，也可以满足所有条件，也被视为正确答案。

但依次安排赛车为 $AAB$ 或 $ABC$ 时，因为不能满足所有条件，所以不被视为正确答案。

### 样例 2

详见附加文件。

### 数据范围

| 测试点编号 |        $n$         |   $d$   |    $m$     |        其他性质         |
| :--------: | :----------------: | :-----: | :--------: | :---------------------: |
|    $1$     |      $\le 2$       |   $0$   |  $\le 4$   |           无            |
|    $2$     |      $\le 2$       | $\le n$ |  $\le 4$   |           无            |
|    $3$     |      $\le 5$       |   $0$   |  $\le 10$  |           无            |
|    $4$     |      $\le 5$       | $\le n$ |  $\le 10$  |           无            |
|    $5$     |      $\le 10$      |   $0$   |  $\le 20$  |           无            |
|    $6$     |      $\le 10$      | $\le 8$ |  $\le 20$  |           无            |
|    $7$     |      $\le 20$      |   $0$   |  $\le 40$  |    $S$ 中只包含 $c$     |
|    $8$     |      $\le 20$      |   $0$   |  $\le 40$  |           无            |
|    $9$     |      $\le 20$      | $\le 8$ |  $\le 40$  | $S$ 中只包含 $x$ 或 $c$ |
|    $10$    |      $\le 20$      | $\le 8$ |  $\le 40$  |           无            |
|    $11$    |     $\le 100$      |   $0$   | $\le 200$  |    $S$ 中只包含 $c$     |
|    $12$    |     $\le 100$      |   $0$   | $\le 200$  |           无            |
|    $13$    |     $\le 100$      | $\le 8$ | $\le 200$  | $S$ 中只包含 $x$ 或 $c$ |
|    $14$    |     $\le 100$      | $\le 8$ | $\le 200$  |           无            |
|    $15$    | $\le 5\times 10^3$ |   $0$   | $\le 10^4$ |           无            |
|    $16$    | $\le 5\times 10^3$ | $\le 8$ | $\le 10^4$ | $S$ 中只包含 $x$ 或 $c$ |
|    $17$    | $\le 5\times 10^3$ | $\le 8$ | $\le 10^4$ |           无            |
|    $18$    | $\le 5\times 10^4$ |   $0$   | $\le 10^5$ |           无            |
|    $19$    | $\le 5\times 10^4$ | $\le 8$ | $\le 10^5$ | $S$ 中只包含 $x$ 或 $c$ |
|    $20$    | $\le 5\times 10^4$ | $\le 8$ | $\le 10^5$ |           无            |


---

---
title: "序列"
layout: "post"
diff: 省选/NOI-
pid: P3863
tag: ['洛谷原创', 'O2优化', '排序', '分块', '洛谷月赛']
---
# 序列
## 题目描述

给定一个长度为 $n$ 的序列，给出 $q$ 个操作，形如：

$1~l~r~x$ 表示将序列下标介于 $[l,r]$ 的元素加上 $x$ （请注意，$x$ 可能为负）

$2~p~y$ 表示查询 $a_p$ 在过去的多少秒时间内不小于 $y$ （不包括这一秒，细节请参照样例）

开始时为第 $0$ 秒，第 $i$ 个操作发生在第 $i$ 秒。

## 输入格式

第一行两个整数 $n,q$，意义如描述所述。

接下来一行 $n$ 个整数 $a_i$，表示序列的每个元素的初始值。

接下来 $q$ 行，每行第一个数为 $\text{opt}$，表示这次操作的类型。如果 $\text{opt} = 1$，后面紧跟三个整数 $l, r, x$，意义如描述所述；如果 $\text{opt} = 2$，后面紧跟两个整数 $p, y$，意义如描述所述。

## 输出格式

对于每个操作 $2$，在一行内输出一个数表示答案。

## 样例

### 样例输入 #1
```
3 3
1 3 5
2 1 2
1 1 2 -3
2 1 1
```
### 样例输出 #1
```
0
2
```
## 提示

样例一说明：位置 $1$ 在第 $0$ 秒到第 $3$ 秒的值为 $1,1,-2,-2$。对于第一个查询，第 $0$ 到 $1-1=0$ 秒中时间不小于 $2$；对于第二个查询，第 $0$ 到第 $3-1=2$ 秒时间不小于 $1$，分别为第 $0$ 秒，第 $1$ 秒。


对于 $30\%$ 的数据，保证 $n,q \leq 1000$

对于 $70\%$ 的数据，保证 $n,q \leq 50000$

对于 $100\%$ 的数据，保证 $2 \leq n,q \leq 100000$， $1 \leq l \leq r \leq n$， $1 \leq p \leq n$，$-10^9 \leq x,y,a_i \leq 10^9$



---

---
title: "[湖南集训] Hungry Rabbit"
layout: "post"
diff: 省选/NOI-
pid: P3895
tag: ['贪心', '湖南', 'Special Judge', '排序']
---
# [湖南集训] Hungry Rabbit
## 题目描述

可怕的洪水在夏天不期而至，兔子王国遭遇了前所未有的饥荒，它们不得不去外面的森林里寻找食物。

为了简化起见，我们假设兔子王国中有 $n$ 只兔子，编号为 $1$ 到 $n$。在救济粮到来之前的 $m$ 天中，每天恰好有 $k$ 只兔子需要去森林里寻找粮食。森林里居住着可怕的大灰狼，所幸兔子已经摸清了大灰狼捕食习惯，即狼们在每一天只会捕食特定编号的兔子。为了安全起见，兔子们需要保证每次出去觅食的 $k$ 只兔子都不会被狼捕食。

由于每天出去捕食的兔子都不尽相同，它们为每一天定义了一个生疏度 $p_i$ ，即第 $i$ 天出来寻找食物，但是第 $i−1$ 天却没有出来觅食的兔子个数。规定第 $1$ 天的生疏度为 $0$。

现在兔子们希望在保证安全的前提下，每天的生疏度不能超过 $l$，请为兔子们构造一个合法的方案。
## 输入格式


第一行包括四个整数 $n, m, k, l$。

接下来 $n$ 行，每行一个长度为 $m$ 的 $01$ 串。其中第 $i$ 行第 $j$ 个字符若为 $0$，则表示狼在第 $j$ 天会捕食编号为 $i$ 的兔子，为 $1$ 则表示不捕食。
## 输出格式

共 $m$ 行，每行 $k$ 个 $1$ 到 $n$ 之间互不相同的整数，代表这一天出去寻找食物的兔子编号。

如果没有合法方案，则输出一行 `−1` 即可。
## 样例

### 样例输入 #1
```
5 4 3 1
1001
1101
1111
1110
0111
```
### 样例输出 #1
```
2 3 4
2 3 4
3 4 5
2 3 5
```
## 提示

#### 样例 1 解释

对于样例，在这 $4$ 天中，出去觅食的兔子集合分别为 $\{2, 3, 4\}; \{2, 3, 4\}; \{3, 4, 5\}; \{2, 3, 5\}$。

---

#### 数据规模与约定

- 对于 $20\%$ 的测试数据，保证 $1\leq n,m\leq 10$；
- 对于 $100\%$ 的测试数据，保证 $1\leq n,m\leq 800,$，$1\leq k\leq n$，$1\leq l\leq k$。


---

---
title: "[湖南集训] Crazy Rabbit"
layout: "post"
diff: 省选/NOI-
pid: P3897
tag: ['湖南', '枚举', '排序']
---
# [湖南集训] Crazy Rabbit
## 题目描述

兔子们决定在自己的城堡里安排一些士兵进行防守。

给出 $n$ 个点的坐标，和城堡里一个圆心在原点的圆形的障碍，兔子们希望从中选出 $k$ 个兔子，使得它们两两**所在的直线**都不与圆相交。

兔子们希望知道最多能选出多少兔子。
## 输入格式

第一行两个整数 $n$ 和 $r$，表示兔子的个数和圆的半径。

接下来 $n$ 行，每行两个整数 $x_i$ 和 $y_i$，表示第 $i$ 只兔子的坐标

保证每只兔子都严格在障碍外部，且两两所在的直线不与圆相切。
## 输出格式

输出一行一个整数, 表示最多能选出多少兔子
## 样例

### 样例输入 #1
```
6 3
0 6
-7 -4
-3 -2
7 -5
-2 3
8 -3
```
### 样例输出 #1
```
4
```
## 提示

#### 样例 1 解释

 ![](https://cdn.luogu.com.cn/upload/pic/6853.png) 

选择第 $1, 2, 6, 4$ 只兔子即可。

---

#### 数据规模与约定

- 对于 $10\%$ 的数据，保证 $1\leq n\leq 20$。
- 对于 $30\%$ 的数据，保证 $1\leq n\leq 100$。
- 对于 $100\%$ 的数据，保证 $1\leq n\leq 2000$，$1\leq r,x_i,y_i \leq 5000$。


---

---
title: "[SHOI2013] 扇形面积并"
layout: "post"
diff: 省选/NOI-
pid: P3997
tag: ['2013', '线段树', '各省省选', '递归', '上海', 'O2优化', '排序']
---
# [SHOI2013] 扇形面积并
## 题目描述

 ![](https://cdn.luogu.com.cn/upload/pic/11825.png) 

给定 n 个同心的扇形，求有多少面积，被至少 $k$ 个扇形所覆盖。

## 输入格式

第一行是三个整数 $n$，$m$，$k$。$n$ 代表同心扇形个数，$m$ 代表将 $(−\pi ,\pi]$ 的角度区间平均分成 $2m$ 份。

从第二行开始的 $n$ 行，每行三个整数 $r，a_1，a_2$。描述了一个圆心在原点的扇形，半径为 $r$，圆心角是从弧度 $\pi\times \frac{a_1}{m}$ 到 $\pi\times \frac{a_2}{m}$（$a_1$ 不一定小于 $a_2$）。

## 输出格式

输出一个整数 $ans$ ，$\frac{\pi}{2m}\times ans$ 等于至少 $k$ 个扇形所覆盖的总面积。

数据保证答案在 $2^{63} - 1$ 范围内。

## 样例

### 样例输入 #1
```
3 8 2
1 -8 8
3 -7 3
5 -5 5
```
### 样例输出 #1
```
76
```
### 样例输入 #2
```
2 4 1
4 -4 2
1 -4 4
```
### 样例输出 #2
```
98
```
## 提示

对于 $100\%$ 的数据，$1\leq n\leq 10^5$, $1\leq m\leq 10^6$, $1\leq k\leq 5000$, $1\leq r_i\leq 10^5$,$-m\leq a_1,a_2\leq m$。



---

---
title: "[HEOI2013] SAO"
layout: "post"
diff: 省选/NOI-
pid: P4099
tag: ['动态规划 DP', '2013', '各省省选', '河北', '枚举', '拓扑排序', '前缀和']
---
# [HEOI2013] SAO
## 题目描述

Welcome to SAO ( Strange and Abnormal Online)。这是一个 VR MMORPG， 含有 n 个关卡。但是，挑战不同关卡的顺序是一个很大的问题。

某款游戏有 $n-1$ 个对于挑战关卡的限制，诸如第 $i$ 个关卡必须在第 $j$ 个关卡前挑战，或者完成了第 $k$ 个关卡才能挑战第 $l$ 个关卡。并且，如果不考虑限制的方向性，那么在这 $n-1$ 个限制的情况下，任何两个关卡都存在某种程度的关联性。即，我们不能把所有关卡分成两个非空且不相交的子集，使得这两个子集之间没有任何限制。

## 输入格式

第一行，一个整数 $T$，表示数据组数。

对于每组数据，第一行一个整数 $n$，表示关卡数。接下来 $n - 1$ 行，每行为 $i \text{ sign } j$，其中 $0 \leq i, j \leq n - 1$ 且 $i \neq j$，$\text{sign}$ 为 $\tt{<}$ 或者 $\tt{>}$，表示第 $i$ 个关卡必须在第 $j$ 个关卡前或后完成。

## 输出格式

对于每个数据，输出一行一个整数，为攻克关卡的顺序方案个数，$\bmod (10^9+7)$ 输出。

## 样例

### 样例输入 #1
```
2 
5 
0 < 2 
1 < 2 
2 < 3 
2 < 4 
4 
0 < 1 
0 < 2 
0 < 3
```
### 样例输出 #1
```
4 
6
```
## 提示

对于 $20\%$ 的数据有 $n \le 10$。

对于 $40\%$ 的数据有 $n \le 100$。

对于另外 $20\%$ 的数据有，保证数据中 sign 只会是 <，并且 $i<j$。

对于 $100\%$ 的数据有 $T \le 5$，$1 \le n \le 1000$。


---

---
title: "[SCOI2007] 组队"
layout: "post"
diff: 省选/NOI-
pid: P4165
tag: ['2007', '四川', '各省省选', '枚举', '排序']
---
# [SCOI2007] 组队
## 题目描述

NBA每年都有球员选秀环节。通常用速度和身高两项数据来衡量一个篮球运动员的基本素质。假如一支球队里速度最慢的球员速度为minV，身高最矮的球员高度为minH，那么这支球队的所有队员都应该满足: A × ( height – minH ) + B × ( speed – minV ) <= C 其中A和B，C为给定的经验值。这个式子很容易理解，如果一个球队的球员速度和身高差距太大，会造成配合的不协调。

请问作为球队管理层的你，在N名选秀球员中，最多能有多少名符合条件的候选球员。

## 输入格式

第一行四个数N、A、B、C 下接N行每行两个数描述一个球员的height和speed

## 输出格式

最多候选球员数目。

## 样例

### 样例输入 #1
```
4 1 2 10
5 1
3 2
2 3
2 1
```
### 样例输出 #1
```
4
```
## 提示

数据范围： N <= 5000 ,height和speed不大于10000。A、B、C在长整型以内。




---

---
title: "[CQOI2006] 凸多边形 /【模板】半平面交"
layout: "post"
diff: 省选/NOI-
pid: P4196
tag: ['2006', '重庆', '各省省选', '排序', '向量', '栈', '队列', '半平面交']
---
# [CQOI2006] 凸多边形 /【模板】半平面交
## 题目描述

逆时针给出 $n$ 个凸多边形的顶点坐标，求它们交的面积。例如 $n=2$ 时，两个凸多边形如下图：

![](https://cdn.luogu.com.cn/upload/image_hosting/7ieux7g3.png)

则相交部分的面积为 $5.233$。
## 输入格式

第一行有一个整数 $n$，表示凸多边形的个数，以下依次描述各个多边形。第 $i$ 个多边形的第一行包含一个整数 $m_i$，表示多边形的边数，以下 $m_i$ 行每行两个整数，逆时针给出各个顶点的坐标。
## 输出格式

输出文件仅包含一个实数，表示相交部分的面积，保留三位小数。
## 样例

### 样例输入 #1
```
2
6
-2 0
-1 -2
1 -2
2 0
1 2
-1 2
4
0 -3
1 -1
2 2
-1 0
```
### 样例输出 #1
```
5.233
```
## 提示

对于 $100\%$ 的数据：$2 \leq n \leq 10$，$3 \leq m_i \leq 50$，每维坐标为 $[-1000,1000]$ 内的整数。


---

---
title: "[NOI2006] 神奇口袋"
layout: "post"
diff: 省选/NOI-
pid: P4204
tag: ['高精度', '2006', 'NOI', '排序']
---
# [NOI2006] 神奇口袋
## 题目描述

Pòlya 获得了一个奇妙的口袋，上面写着人类难以理解的符号。Pòlya 看得入了迷，冥思苦想，发现了一个神奇的模型（被后人称为 Pòlya 模型)。为了生动地讲授这个神奇的模型，他带着学生们做了一个虚拟游戏：游戏开始时，袋中装入 $a_1$ 个颜色为 $1$ 的球，$a_2$ 个颜色为 $2$ 的球，……，$a_t$ 个颜色为 $t$ 的球，其中 $a_i \in \mathbb Z^+$（$1 \le i \le t$）。

游戏开始后，每次严格进行如下的操作：

从袋中随机的抽出一个小球（袋中所有小球被抽中的概率相等），Pòlya 独自观察这个小球的颜色后将其放回，然后再把 $d$ 个与其颜色相同的小球放到口袋中。

设 $c_i$ 表示第 $i$ 次抽出的小球的颜色（$1 \le C_i \le t$），一个游戏过程将会产生一个颜色序列（$c_1, c_2, \ldots, c_n, \ldots$）。Pòlya 把游戏开始时 $t$ 种颜色的小球每一种的个数 $a_1, a_2, \ldots, a_t$ 告诉了所有学生。然后他问学生：一次游戏过程产生的颜色序列满足下列条件的概率有多大？ 

$$c_{x_1}=y_1, c_{x_2}=y_2, \ldots, c_{x_n}=y_n$$

其中 $0 < x_1 < x_2 < \cdots < x_n$，$1 \le y_i \le t$。换句话说，已知 $(t, n, d, a_1, a_2, \ldots, a_t, x_1, y_1, x_2, y_2, \ldots, x_n, y_n)$，你要回答有多大的可能性会发生下面的事件：“对所有 $k$（$1 \le k \le n$），第 $x_k$ 次抽出的球的颜色为 $y_k$”。
## 输入格式

第一行有三个正整数 $t, n, d$；

第二行有 $t$ 个正整数 $a_1, a_2, \ldots, a_t$，表示游戏开始时口袋里 $t$ 种颜色的球，每种球的个数。

以下 $n$ 行，每行有两个正整数 $x_i, y_i$，表示第 $x_i$ 次抽出颜色为的 $y_i$ 球。
## 输出格式

要求用分数形式输出（显然此概率为有理数）。输出文件包含一行，格式为：`分子/分母`。同时要求输出最简形式（分子分母互质）。特别的，概率为 $0$ 应输出 `0/1`，概率为 $1$ 应输出 `1/1`。
## 样例

### 样例输入 #1
```
2 3 1
1 1
1 1
2 2
3 1

```
### 样例输出 #1
```
1/12

```
### 样例输入 #2
```
3 1 2
1 1 1
5 1

```
### 样例输出 #2
```
1/3

```
## 提示

**【样例解释 #1】**

初始时，两种颜色球数分别为 $(1, 1)$，取出色号为 $1$ 的球的概率为 $1/2$；第二次取球之前，两种颜色球数分别为 $(2, 1)$，取出色号为 $2$ 的球的概率为 $1/3$；第三次取球之前，两种颜色球数分别为 $(2, 2)$，取出色号为 $1$ 的球的概率为 $1/2$，所以三次取球的总概率为 $1/12$。

**【数据规模和约定】**

对于 $100 \%$ 的数据，$1 \le t, n \le 1000$，$1 \le a_k, d \le 10$，$1 \le x_1 < x_2 < \cdots < x_n \le 10000$，$1 \le y_k \le t$。


---

---
title: "[USACO18OPEN] Out of Sorts P"
layout: "post"
diff: 省选/NOI-
pid: P4372
tag: ['2018', 'USACO', '排序', 'Ad-hoc']
---
# [USACO18OPEN] Out of Sorts P
## 题目描述

留意着农场之外的长期职业生涯的可能性，奶牛 Bessie 开始在不同的在线编程网站上学习算法。她最喜欢的两个算法是“冒泡排序”和“快速排序”，但不幸的是，Bessie 轻易地把它们搞混了，最后实现了一个奇怪的混合算法！

如果数组 $A$ 中 $A[0 \ldots i]$ 的最大值不大于 $A[i+1 \ldots N-1]$ 的最小值，我们就称元素 $i$ 和 $i+1$ 之间的位置为一个“分隔点”。Bessie 还记得快速排序包含对数组的重排，产生一个分隔点，然后递归对两侧的 $A[0 \ldots i]$ 和 $A[i+1 \ldots N-1]$ 排序。然而，尽管她正确地记下了数组中所有的分隔点都可以在线性时间内求出，她却忘记了快速排序应该如何重排来快速构造一个分隔点！在这个可能是排序算法历史上最糟糕的失误之下，她做出了一个不幸的决定：使用冒泡排序来完成这个任务。

以下是 Bessie 最初对数组 $A$ 进行排序的实现的概要。她首先写了一个简单的函数，执行冒泡排序的一轮：

```
bubble_sort_pass(A) {
   for i = 0 to length(A)-2
      if A[i] > A[i+1], swap A[i] and A[i+1]
}
```

她的快速排序（相当快）函数的递归代码如下：

```
quickish_sort(A) {
   if length(A) == 1, return
   do { // Main loop
      work_counter = work_counter + length(A)
      bubble_sort_pass(A)
   } while (no partition points exist in A)
   divide A at all partition points; recursively quickish_sort each piece
}
```

Bessie 好奇于她的代码能够运行得多快。简单起见，她计算出主循环的每一轮都消耗线性时间，因此她通过增加一个全局变量 `work_counter` 的值来跟踪整个算法完成的总工作量。

给定一个输入数组，请预测 `quickish_sort` 函数接收这个数组后，变量 `work_counter` 的最终值。
## 输入格式

输入的第一行包含 $N$（$1 \leq N \leq 100,000$）。接下来的 $N$ 行描述了 $A[0] \ldots A[N-1]$，每个数都是一个范围在 $0 \ldots 10^9$ 的整数。输入数据不保证各不相同。
## 输出格式

输出 `work_counter` 的最终值。
## 样例

### 样例输入 #1
```
7
20
2
3
4
9
8
7
```
### 样例输出 #1
```
12

```
## 提示

在这个例子中，数组初始为 `20 2 3 4 9 8 7`。在一轮冒泡排序之后（增加 $7$ 的工作量），我们得到 `2 | 3 | 4 | 9 8 7 | 20`，其中 `|` 表示一个分隔点。于是问题被分成了递归的子问题，包括对 `2`、`3`、`4`、`20` 排序（每个消耗 $0$ 单元的工作量）和对 `9 8 7` 排序。对于 `9 8 7` 这个子问题，主循环的一轮（$3$ 单元工作量）得到 `8 7 | 9`，在此之后最后一轮处理 `8 7`（$2$ 单元工作量）就有效地完成了排序。

题目来源：Brian Dean


---

---
title: "[BalkanOI 2007] Mokia 摩基亚"
layout: "post"
diff: 省选/NOI-
pid: P4390
tag: ['2007', '树状数组', '分治', '排序', 'BalkanOI（巴尔干半岛）']
---
# [BalkanOI 2007] Mokia 摩基亚
## 题目描述

摩尔瓦多的移动电话公司摩基亚（Mokia）设计出了一种新的用户定位系统。和其他的定位系统一样，它能够迅速回答任何形如 “用户 C 的位置在哪？” 的问题，精确到毫米。但其真正高科技之处在于，它能够回答形如 “给定区域内有多少名用户？” 的问题。

在定位系统中，世界被认为是一个 $w\times w$ 的正方形区域，由 $1\times 1$ 的方格组成。每个方格都有一个坐标 $(x, y)$，$1\leq x,y\leq w$。坐标的编号从 $1$ 开始。对于一个 $4\times 4$ 的正方形，就有 $1\leq x\leq 4$，$1\leq y\leq 4$（如图）：

![](https://cdn.luogu.com.cn/upload/pic/17271.png)

请帮助 Mokia 公司编写一个程序来计算在某个矩形区域内有多少名用户。
## 输入格式

有三种命令，意义如下：

|命令|参数|意义|
|:-:|:-:|:-:|
|$0$|$w$|初始化一个全零矩阵。本命令仅开始时出现一次。|
|$1$|$x\ y\ a$|向方格 $(x, y)$ 中添加 $a$ 个用户。$a$ 是正整数。|
|$2$|$x_1\ y_1\ x_2\ y_2$|查询 $x_1\leq x\leq x_2$，$y_1\leq y\leq y_2$ 所规定的矩形中的用户数量。|
|$3$|无参数|结束程序。本命令仅结束时出现一次。|

输入共若干行，每行有若干个整数，表示一个命令。
## 输出格式

对所有命令 $2$，输出一个一行整数，即当前询问矩形内的用户数量。
## 样例

### 样例输入 #1
```
0 4
1 2 3 3
2 1 1 3 3
1 2 2 2
2 2 2 3 4
3
```
### 样例输出 #1
```
3
5

```
## 提示

#### 数据规模与约定


对于 $100\%$ 的数据，保证：
- $1\leq w\leq 2\times 10 ^ 6$。
- $1\leq x_1\leq x_2\leq w$，$1\leq y_1\leq y_2\leq w$，$1\leq x,y\leq w$，$0<a\leq 10000$。
- 命令 $1$ 不超过 $160000$ 个。
- 命令 $2$ 不超过 $10000$ 个。


---

---
title: "[CQOI2005] 三角形面积并"
layout: "post"
diff: 省选/NOI-
pid: P4406
tag: ['2005', '重庆', '各省省选', '枚举', '排序']
---
# [CQOI2005] 三角形面积并
## 题目描述

给出 $n$ 个三角形，求它们并的面积。
## 输入格式

第一行为 $n(n \leq 100)$， 即三角形的个数。

以下 $n$ 行，每行 $6$ 个实数 $x_1$, $y_1$, $x_2$, $y_2$, $x_3$, $y_3$，代表三角形的顶点坐标。坐标均为不超过 $10^6$ 的实数，输入数据保留 $1$ 位小数。
## 输出格式

输出并的面积 $u$, 保留两位小数。

## 样例

### 样例输入 #1
```
2
0.0 0.0 2.0 0.0 1.0 1.0
1.0 0.0 3.0 0.0 2.0 1.0
```
### 样例输出 #1
```
1.75
```


---

---
title: "[BJWC2011] 最小三角形"
layout: "post"
diff: 省选/NOI-
pid: P4423
tag: ['2011', '递归', '北京', '分治', '排序']
---
# [BJWC2011] 最小三角形
## 题目描述

Xaviera 现在遇到了一个有趣的问题。

平面上有 $N$ 个点，Xaviera 想找出周长最小的三角形。

由于点非常多，分布也非常乱，所以 Xaviera 想请你来解决这个问题。

为了减小问题的难度，这里的三角形也包括共线的三点。
## 输入格式

第一行包含一个整数 $N$ 表示点的个数。

接下来 $N$ 行每行有两个整数，表示这个点的坐标。
## 输出格式

输出只有一行，包含一个 $6$ 位小数，为周长最短的三角形的周长（四舍五入）。
## 样例

### 样例输入 #1
```
4
1 1
2 3
3 3
3 4
```
### 样例输出 #1
```
3.414214

```
## 提示

对于所有数据，$3 \leq N \leq 2\times 10^5$


---

---
title: "[SCOI2007] k短路"
layout: "post"
diff: 省选/NOI-
pid: P4467
tag: ['字符串', '2007', '四川', '各省省选', '排序', '最短路', 'A*  算法']
---
# [SCOI2007] k短路
## 题目描述

有 $n$ 个城市和 $m$ 条单向道路，城市编号为 $1$ 到 $n$。每条道路连接两个不同的城市，且任意两条道路要么起点不同要么终点不同，因此 $n$ 和 $m$ 满足$m \le n(n-1)$。

给定两个城市 $a$ 和 $b$，可以给 $a$ 到 $b$ 的所有简单路（所有城市最多经过一次，包括起点和终点）排序：先按长度从小到大排序，长度相同时按照字典序从小到大排序。你的任务是求出 $a$ 到 $b$ 的第 $k$ 短路。

## 输入格式

输入第一行包含五个正整数 $n,m,k,a,b$。

以下 $m$ 行每行三个整数 $u,v,l$，表示从城市 $u$ 到城市 $v$ 有一条长度为 $l$ 的单向道路。
## 输出格式

如果 $a$ 到 $b$ 的简单路不足 $k$ 条，输出 `No`，否则输出第 $k$ 短路：从城市 $a$ 开始依次输出每个到达的城市，直到城市 $b$，中间用减号 `-` 分割。
## 样例

### 样例输入 #1
```
5 20 10 1 5
1 2 1
1 3 2
1 4 1
1 5 3
2 1 1
2 3 1
2 4 2
2 5 2
3 1 1
3 2 2
3 4 1
3 5 1
4 1 1
4 2 1
4 3 1
4 5 2
5 1 1
5 2 1
5 3 1
5 4 1
```
### 样例输出 #1
```
1-2-4-3-5
```
### 样例输入 #2
```
4 6 1 1 4
2 4 2
1 3 2
1 2 1
1 4 3
2 3 1
3 4 1
```
### 样例输出 #2
```
1-2-3-4
```
### 样例输入 #3
```
3 3 5 1 3
1 2 1
2 3 1
1 3 1
```
### 样例输出 #3
```
No
```
## 提示

第一个例子有 $5$ 个城市，所有可能出现的道路均存在。从城市 $1$ 到城市 $5$ 一共有 $5$ 条简单路，排序如下：

![](https://cdn.luogu.com.cn/upload/pic/17706.png)

- $20\%$ 的数据满足：$n\leq 5$；
- $40\%$ 的数据满足：$n\leq 30$；
- $100\%$ 的数据满足：$2\leq n\leq 50$，$1\leq k\leq 200$，$1\le l\le 10^4$。


---

---
title: "[HNOI2006] 军机调度"
layout: "post"
diff: 省选/NOI-
pid: P4540
tag: ['2006', '各省省选', '湖南', '枚举', '排序', '位运算']
---
# [HNOI2006] 军机调度
## 题目描述

凯萨拥有一支由n个人组成的雇佣军，他们靠在威尼斯商行接任务过活。

这支军队的成份比较复杂，不同的人往往具有不同的技能，有的人还拥有多项技能。

威尼斯商行的任务也参差不齐，有的需要几个人合作完成，有的只需要一个人独立完成：有的很简单，不需要耗多少时间，因此报酬也较低，有的很有难度，需要多个人长期合作完成，因此报酬就高。完成这些任务的时间不会超过一个月。并且，一个人不能同时执行两项任务，也不能中途加入或者退出任务。但可以不执行任何任务。

一项只需要n个人来完成的任务，如果执行该任务的人数p大于n,那么反而会得到更少的报酬，即原报酬的1/(p-n+1)。

凯萨是一位英明的领袖，他往往在每个月的月底召开军事会议，总结上个月的成果，发给大家报酬，并指派下个月的任务。

请问，凯萨应该怎样指派任务，才能使总报酬最高？总报酬为多少？
## 输入格式

一行包含两个正整数n,m。彼此用空格隔开，

其中n〈10表示雇佣军的人数，m〈15表示下个月可选的任务数。

接下来的n行中第i行（对应文件的第i+1行）的第一个整数小于等于表示编号为i的雇佣军可执行的任务数

后面的整数是编号为i的雇佣军可以执行的所有任务的编号，这些整数之间用空格隔开。

最后的m行中，每行有四个整数b、e、p和r，彼此之间用空格隔开，

其中第j行（对应整个文件的第n+j+1行）是编号为j的任务的描述：

0<b<32表示该任务的开始日（这一天会被计入任务所需的时间中），

0<e<32表示该任务的结束日（这一天也会被计入任务所需的时间中），

p<10表示该任务所需人数，0<r<100000表示该任务的报酬。
## 输出格式

第一行只有一个整数t,表示最多可获得的总报酬
## 样例

### 样例输入 #1
```
3 5
2 1 4
2 2 4
3 3 4 5
2 20 1 100 
1 18 1 200 
3 28 1 800 
21 30 3 1500 
19 21 1 400 
```
### 样例输出 #1
```
1800
```


---

---
title: "礼物"
layout: "post"
diff: 省选/NOI-
pid: P4934
tag: ['Special Judge', 'O2优化', '枚举', '排序', '拓扑排序', '洛谷月赛']
---
# 礼物
## 题目背景

由于你出色的完成了前面两道题目，善良的 __stdcall 决定给你一个小礼物，给拼搏在 AK 这套题之路上的你，一个有力的援助。
## 题目描述

__stdcall 决定给你 $n$ 个礼物，每个礼物有一个魔力值 $a_i$。

这些礼物的魔力值都是独一无二的，两两互不相同。这些礼物都有着神奇的魔力，如果两个礼物 $i, j$ 的魔力值满足 $a_i \operatorname{bitand} a_j \ge \min(a_i, a_j)$，那么这两个礼物的魔力将会相互抵消，因此它们不能放在一个箱子里。

这里的 $\operatorname{bitand}$ 表示按位与运算，如果你对这一运算不够了解，请参考：<https://baike.baidu.com/item/%E6%8C%89%E4%BD%8D%E4%B8%8E/9601818>。

作为发礼物苦力的 ljt12138 的箱子并不多，不过幸运的是，每个箱子都足够大。现在他请求你帮助他合理分配，用**尽可能少**的箱子装下所有礼物。换言之，使得每个礼物都被恰好装入一个箱子中，且同一个箱子中的礼物魔力不会相互抵消。如果有多种合法的方案，你只需要给出**任意一种**。

ljt12138 十分善良，如果你只能求出所需要的箱子数，也可以获得该测试点 $60\%$ 的分数，关于这一点，请参考下面的提示与说明。
## 输入格式

- 第一行两个数 $n$ 和 $k$，$n$ 为礼物总数，$k$ 为一个参数，方便你进行计算。
- 第二行 $n$ 个两两不同的数$a_i$，满足 $0\le a_i < 2^k$，表示礼物的魔力值。
## 输出格式

- 第一行输出一个数。如果你不希望输出方案，请输出0；如果你希望输出方案，请输出 $1$。**如果你在这一行输出了不符合要求的信息，将被判为 WA**。
- 第二行一个数 $m$，表示你将礼物装到了 $m$ 个箱子里。
- 如果你在第一行输出了 $1$，接下来 $m$ 行，每行表示一个箱子：首先一个数 $s_i$，表示当前箱子中礼物的个数；接下来 $s_i$ 个数，表示当前子集。
## 样例

### 样例输入 #1
```
5 3
0 4 7 1 6 

```
### 样例输出 #1
```
1
4
1 0
2 1 4
1 6
1 7 
```
## 提示

### 附加样例

你可以在  <https://pan.baidu.com/s/1A8_ZA4yXXi5y6771x9JKUw> 下载附加样例。

### 关于输出方案

- 如果你在第一行输出了 $0$，而正确回答了最小所需的箱子数，将获得测试点 $60\%$ 的分数。
- 如果你在第一行输出了 $1$，正确回答了最小所需的箱子数，但没有给出正确的方案，也将获得该测试点 $60\%$ 的分数。
- 如果你没有正确回答最小所需的箱子数，将不会获得该测试点的分数。
- 请选手注意，如果你未按照上述格式输出答案，将无法获得任何分数。

数据 $n, k$ 的关系由下面的表格给出：

|数据编号| $n$ | $k$ |
|:----:|:----:|:----:|
|$1$|$5$|$3$|
|$2$|$6$|$3$|
|$3$|$7$|$10$|
|$4$|$8$|$10$|
|$5$|$16$|$7$|
|$6$|$17$|$8$|
|$7$|$17$|$9$|
|$8$|$17$|$20$|
|$9$|$2\times 10^3$|$17$|
|$10$|$2.5\times 10^3$|$18$|
|$11$|$3\times 10^3$|$19$|
|$12$|$3\times 10^3$|$20$|
|$13$|$2.5\times 10^4$|$15$|
|$14$|$2.5\times 10^4$|$15$|
|$15$|$5\times 10^4$|$16$|
|$16$|$5\times 10^4$|$16$|
|$17$|$2.5\times 10^5$|$18$|
|$18$|$5\times 10^5$|$19$|
|$19$|$10^6$|$20$|
|$20$|$10^6$|$20$|


---

---
title: "绫小路的特别考试"
layout: "post"
diff: 省选/NOI-
pid: P4964
tag: ['贪心', '枚举', '排序', '深度优先搜索 DFS', '栈']
---
# 绫小路的特别考试
## 题目背景

>  这世界上「胜利」便是一切。无关乎过程。
要付出多少牺牲都无所谓。只要最后我「胜出」那就行了。

![](https://i.loli.net/2018/10/06/5bb879f4ac370.jpg)
## 题目描述

一场新的特别考试来临了，这次的考试内容是（wan e de）文化课，但有所不同的是，考试中允许学生使用对讲机。然而，对讲机的接收范围是有限的（每个对讲机都能发送无限远，但是只能接收到接收范围内的信号），所以不是所有学生都能接收到其他同学的广播。

考试时，共有 $n$ 名学生坐成一排（从左至右依次编号为 $1$ ~ $n$），绫小路自己坐在第 $c$ 号位置。每名学生都有一个能力值 $w_i$。绫小路已经给每名学生安排了一个接收范围为 $d_i$ 的对讲机。

每名学生可以直接做出难度**不超过**自身能力值的**所有**题目，一旦一名学生凭能力做出某道题，他就会把这道题的做法进行广播。一名坐在位置 $i$，有接收范围为 $d_i$ 的对讲机的学生，可以接收到 $[i-d_i,\ i+d_i]$ 范围内所有学生的广播，若这个范围内有人公布了做法，则他将会做这道题，并也会把这道题的做法进行广播。

绫小路会问你一些问题：当一道题目难度为 $x$ 时，有多少学生会做这道题？由于绫小路想隐藏实力，他可能会修改自己的能力值。这两种操作分别用以下两种方式表示：

- $1\ x$，表示询问当一道题目难度为 $x$ 时，有多少学生会做这道题。

- $2\ x$，将绫小路的能力值修改为 $x$，即将 $w_c$ 修改为 $x$。

---

形式化描述（与上文同义）：

> 给你两个长为 $n$ 的数列 $w_{1..n}$ 和 $d_{1..n}$，以及一个 $w_c$ 可修改的位置 $c$。现在有两种操作（共 $m$ 次）：
- $1\ x$ 表示一次询问：设 $f_i=\begin{cases}1\quad(w_i\ge x)\\1\quad(\exists\ j \in [i - d_i,\ i + d_i],\ f_j=1)\\ 0\quad(otherwise)\end{cases}$，这里的 $f_i$ 定义中引用了 $f_j$，$\ \ \ \ $所以 $f_{1..n}$ 是会不断更新的，直到无法继续更新时，计算这次询问的答案为 $\sum\limits_{i=1}^nf_i$。
- $2\ x$ 表示一次修改：把 $w_c$ 修改为 $x$。
## 输入格式

由于数据量太大，为了避免读入耗时过长，使用**伪随机数生成器**的方式输入，并**强制在线**。

**建议你忽略输入格式，直接使用下面提供的数据生成器模板，了解具体的生成过程对你来说是不必要的。**

第一行，三个正整数 $n,\ m,\ c$，分别代表学生的总人数，操作总数和绫小路所在的位置。

第二行，五个整数 $\mathrm{seed},\ \mathrm{mind},\ \mathrm{maxd},\ \mathrm{mfq},\ k$。

> 此处的 $\mathrm{mind},\ \mathrm{maxd}$ 仅用于生成初始的 $d_{1..n}$，下文中调整 $d_p$ 所用的 $t$ 可能不在 $[\mathrm{mind},\ \mathrm{maxd}]$ 范围内。

接下来的 $k$ 行，每行两个整数 $p,\ t$，表示调整第 $p$ 号同学的对讲机接收范围（即 $d_p$）为 $t$。

> 若一名同学的对讲机接收范围被调整多次，以**最后一次**为准。

---

** 数据生成器模板：**

```cpp
#include <cstdio>

unsigned long long seed;
int n, m, c, mfq, mind, maxd, k, w[2000001], d[2000001];

inline int randInt() { seed = 99999989 * seed + 1000000007; return seed >> 33; } 

void generate()
{
	// 在读入种子后生成初始的 w 数组和 d 数组.
    for (int i = 1; i <= n; i++) { w[i] = randInt() % n; }
    for (int i = 1; i <= n; i++) { d[i] = randInt() % (maxd - mind + 1) + mind; }
}

void getOperation(int lastans, int &opt, int &x)
{
    // 生成一次操作的参数 opt 和 x, lastans 表示上一次询问的答案, 初始值为 0.
    if ((0ll + randInt() + lastans) % mfq) { opt = 1; } else { opt = 2; }
    x = (0ll + randInt() + lastans) % n;
}

int main()
{
    scanf("%d %d %d", &n, &m, &c);
    scanf("%llu %d %d %d %d", &seed, &mind, &maxd, &mfq, &k);
    generate();
    for (int i = 1; i <= k; i++)
    {
        int p, t;
        scanf("%d %d", &p, &t);
        d[p] = t;
    }
    // 从这里开始，你可以使用生成的 w 数组和 d 数组.
    int lastans = 0, finalans = 0;
    for (int i = 1; i <= m; i++)
    {
        int opt, x;
        getOperation(lastans, opt, x);
        if (opt == 1)
        {
            // 在这里执行询问操作，并用答案的表达式替代下面的 ___.      
            finalans = (finalans * 233ll + ___) % 998244353;
            lastans = ___;
        }
        else
        {
            // 在这里执行修改操作.
        }
    }
    printf("%d\n", finalans);
    return 0;
}
```
## 输出格式

令 $ans_i$ 表示第 $i$ 次询问（操作 $1$）的答案，$T_i=\begin{cases}(T_{i-1}\times 233+ans_i)\mod 998244353\quad(i\ge 1)\\0\quad(i=0)\end{cases}$

设 $q$ 表示询问（操作 $1$）的个数，你只需要输出一个整数 $T_q$。
## 样例

### 样例输入 #1
```
3 3 2
19720918 0 1 2 0
```
### 样例输出 #1
```
700
```
### 样例输入 #2
```
10 10 8
2102036 0 1 4 1
5 2
```
### 样例输出 #2
```
760521825
```
### 样例输入 #3
```
1000 1000 126
114321251 1 2 2 0
```
### 样例输出 #3
```
91977056
```
## 提示

### 你需要用到的变量：

$1\le c\le n\le 2\times 10^6$，$1\le m\le 2\times 10^6$，$0\le w_i,\ d_i,\ x<n$。

### 其它用于生成数据的变量：

$1\le \mathrm{seed},\ \mathrm{mfq}\le 10^9$，$0\le \mathrm{mind}\le \mathrm{maxd}<n$，$0\le k\le 2\times 10^5$，$1\le p\le n$，$0\le t<n$。

## 样例解释

### 样例一：

生成得到三名同学的能力值 $w_{1..3} = \{0,\ 1,\ 2\}$，对讲机接收范围 $d_{1..3} = \{1,\ 0,\ 1\}$。

第一个操作是 `1 1`，询问有多少同学会做难度为 $1$ 的题。

绫小路（第 $2$ 名同学）和第 $3$ 名同学能够独立做出这道题（$w_2 \ge 1$ ，$w_3 \ge 1$），第 $1$ 名同学虽然能力不足，但通过对讲机能接收到绫小路广播的做法（$2 \in [1 - d_1,\ 1 + d_1]$），所以他也会做。故 $ans_1 = 3$。

第二个操作是 `2 0`，修改绫小路（第 $2$ 名同学）的能力值为 $0$。此时 $w_{1..3} = \{0,\ 0,\ 2\}$。

第三个操作是 `1 1`，再次询问有多少同学会做难度为 $1$ 的题。

只有第 $3$ 名同学能够独立做出（$w_3 \ge 1$），然而第 $1$ 名同学和绫小路（第 $2$ 名同学）都无法接收到他广播的做法（$3 \notin [1 - d_1,\ 1 + d_1]$，$3 \notin [2 - d_2,\ 2 + d_2]$），做不出来。故 $ans_2 = 1$。

综上所述，$T_1 = ans_1 = 3$，$T_2 = 3 \times T_1+ ans_2 = 3 \times 233 + 1 = 700$，仅输出 $700$ 即可。

### 样例二：

生成得到 $w_{1..10} = \{1,\ 6,\ 6,\ 5,\ 3,\ 5,\ 2,\ 7,\ 9,\ 5\}$，$d_{1..10} =\{1,\ 1,\ 1,\ 1,\ 2,\ 0,\ 1,\ 0,\ 1,\ 1\}$。

十次操作及对应结果如下所示：

`1 6`，查询操作，$ans_1 = 9$，$T_1 = 9$。

`2 2`，修改操作，$w_{1..10}$ 变为 $\{1,\ 6,\ 6,\ 5,\ 3,\ 5,\ 2,\ 2,\ 9,\ 5\}$。

`1 7`，查询操作，$ans_2 = 2$，$T_2 = 2099$。

`1 3`，查询操作，$ans_3 = 9$，$T_3 = 489076$。

`2 4`，修改操作，$w_{1..10}$ 变为 $\{1,\ 6,\ 6,\ 5,\ 3,\ 5,\ 2,\ 4,\ 9,\ 5\}$。

`1 3`，查询操作，$ans_4 = 10$，$T_4 = 113954718$。
  
`2 2`，修改操作，$w_{1..10}$ 变为 $\{1,\ 6,\ 6,\ 5,\ 3,\ 5,\ 2,\ 2,\ 9,\ 5\}$。
  
`1 9`，查询操作，$ans_5 = 2$，$T_5 = 597096118$。  

`1 0`，查询操作，$ans_6 = 10$，$T_6 = 367430437$。    

`1 3`，查询操作，$ans_7 = 9$，$T_7 = 760521825$。

仅输出 $760521825$ 即可。

### 样例三：

~~出题人有足够的良心写出这个样例的解释，可惜版面太小，写不下。~~


---

---
title: "HMR的LIS Ⅲ"
layout: "post"
diff: 省选/NOI-
pid: P5010
tag: ['贪心', '线段树', 'O2优化', '排序']
---
# HMR的LIS Ⅲ
## 题目背景

[HMR的LIS Ⅰ](https://www.luogu.org/problemnew/show/T51390)

[HMR的LIS Ⅱ](https://www.luogu.org/problemnew/show/T51391)

在你帮助HMR切掉AKIOI的神仙LSK的两道题后，LSK很不满，决定好好刁难一下你（而不是HMR）
## 题目描述

LSK又给出了一个长度为n的序列，要求你求出它的IBvl序列

IBvl序列满足以下要求：

1.一个IBvl序列满足$ \forall ~ i \in (1,len] , L < a_i - a_{i-1} < R $，其中$len$为IBvl序列的长度

2.IBvl序列中的元素相对顺序应满足在原序列中的相对顺序

3.在所有满足条件的序列中长度最长

我们视位置不同的元素为不同元素，有任一组成元素不同的IBvl序列为不同IBvl序列

现在要求你输出原序列的IBvl序列的长度，并输出字典序第k小（以元素在原序列中的位置为关键字排序）的序列的每个元素在原序列中的位置
## 输入格式

第一行输入4个整数，n，k，L，R

第二行输入n个整数，表示神仙LSK给出的序列
## 输出格式

第一行输出IBvl序列的长度

第二行输出IBvl序列的每个元素的位置
## 样例

### 样例输入 #1
```
5 3 2 4
6 8 0 2 7
```
### 样例输出 #1
```
1
3
```
## 提示

#### 样例解释：

对于给出的数据，一共有$5$种IBvl序列，分别是:$\{6\},\{8\},\{0\},\{2\},\{7\}$。

他们在原序列中位置的编号序列分别是$\{1\},\{2\},\{3\},\{4\},\{5\}$

IBvl序列的长度为1。

要求输出字典序第$3$小的编号序列，于是输出$3$。

#### 数据范围与约定：

对于20%的数据，$ n \le 18$

对于50%的数据，$ n \le 1000 , | l | , | r | \leq 10^9 , r-l>1 , 0 \le a[i] \le 10^9 $

对于另外10%的数据，$ l=0 , r=10^9+1 , k=1 $

对于另外20%的数据，$ l=0 , r=10^9+1 , k \le 3 $

对于100%的数据，$ n \le 5*10^5 , | l | , | r | \le 10^9 , r-l>1 , k \le 10^{13} , 0 \le a[i] \le 10^9 $

对于所有数据，保证合法且有解。

对于前50%的数据，时限为1s，后50%的数据，时限为2s（~~凉~~良心不卡常）


---

---
title: "[USACO18DEC] The Cow Gathering P"
layout: "post"
diff: 省选/NOI-
pid: P5157
tag: ['图论', '2018', 'USACO', '图论建模', '拓扑排序']
---
# [USACO18DEC] The Cow Gathering P
## 题目描述

奶牛们从世界各地聚集起来参加一场大型聚会。总共有 $ N $ 头奶牛， $ N-1 $ 对奶牛互为朋友。每头奶牛都可以通过一些朋友关系认识其他每头奶牛。

她们玩得很开心，但是现在到了她们应当离开的时间了，她们会一个接一个地离开。她们想要以某种顺序离开，使得只要至少还有两头奶牛尚未离开，所有尚未离开的奶牛都还有没有离开的朋友。此外，由于行李寄存的因素，有 $ M $ 对奶牛 $ (a_i,b_i) $ 必须满足奶牛 $ a_i $ 要比奶牛 $ b_i $ 先离开。注意奶牛 $ a_i $ 和奶牛 $ b_i $ 可能是朋友，也可能不是朋友。

帮助奶牛们求出，对于每一头奶牛，她是否可以成为最后一头离开的奶牛。可能会发生不存在满足上述要求的奶牛离开顺序的情况。
## 输入格式

输入的第 $ 1 $ 行包含两个空格分隔的整数 $ N $ 和 $ M $ 。

输入的第 $ 2 \leq i \leq N $ 行，每行包含两个整数 $ x_i $ 和 $ y_i $ ，满足 $ 1 \leq x_i $ ， $ y_i \leq N,xi \neq yi $ ，表示奶牛 $ x_i $ 和奶牛 $ y_i $ 是朋友关系。

输入的第 $ N+1 \leq i \leq N+M $ 行，每行包含两个整数 $ a_i $ 和 $ b_i $ ，满足 $ 1 \leq a_i,b_i \leq N $ ， $ a_i \neq b_i $ ，表示奶牛 $ a_i $ 必须比奶牛 $ b_i $ 先离开聚会。

输入保证 $ 1 \leq N,M \leq 10^5 $ 。对于占总分 $ 20\% $ 的测试数据，保证 $ N,M \leq 3000 $ 。
## 输出格式

输出 $ N $ 行，每行包含一个整数 $ d_i $ ，如果奶牛 $ i $ 可以成为最后一头离开的奶牛，则 $ d_i=1 $ ，否则 $ d_i=0 $ 。
## 样例

### 样例输入 #1
```
5 1
1 2
2 3
3 4
4 5
2 4

```
### 样例输出 #1
```
0
0
1
1
1

```


---

---
title: "水晶"
layout: "post"
diff: 省选/NOI-
pid: P5510
tag: ['O2优化', '排序', '前缀和']
---
# 水晶
## 题目背景

2019/12/27 修改最后一个点的数据范围

Steve带领军队到达了黑暗势力的据点

然而，他发现黑暗势力正在使用水晶保护自己

为了突破防御，Steve开始用武器攻击水晶
## 题目描述

黑暗势力的水晶已经排成了一排，而且数量很多

水晶可分为$n$组，第$i$组内有$a_i$个水晶，并且防御力均为$na_i$

Steve的武器也已经排成了一排，而且数量也很多

武器也可分为$n$组，第$i$组内有$b_i$个武器，并且攻击力均为$nb_i$

每一轮攻击中，黑暗势力会选择一个水晶，Steve会选择一个武器

如果这个武器的攻击力大于水晶的防御力，这次攻击就有效

然而，水晶和武器数量太多了，Steve很难知道具体选择了哪个水晶，哪个武器

现在Steve希望知道：

1.对于所有可能的情况，有多少种选法是一次有效的攻击

2.如果已经知道选用水晶的防御力在第$x$组水晶的防御力和第$y$组水晶的防御力之间，且选用武器的攻击力在第$z$组武器的攻击力和第$u$组武器的攻击力之间，那么，有多少种选法是一次有效的攻击

也就是，选择的水晶防御力不小于第$x$组水晶和第$y$组水晶防御力的较小值，不大于两者的较大值，武器同理

两个选法不同，当且仅当选用的水晶或武器不同（可以在同一组）

由于战事紧迫，你需要迅速回答问题才能让Steve作出下一轮攻击的决策

因此，部分测试点强制在线

为了避免答案过大，答案对$998244353$取模
## 输入格式

由于输入输出规模较大，使用下面的模板完成数据生成，具体格式请看模板和样例

评测时，所有测试点都只会输入5个数，输出1个数，因此你不需要输入输出优化

为便于调试，该模板可以手动指定数据，并输出每一个询问的答案，只需要输入的$k=0$

对于所有测试点，保证调用交互库消耗的时间不超过300ms
```
#include<cstdio>
using namespace std;
#define u32 unsigned int
#define u64 unsigned long long
int cl;
const int N=2500007;
const long long M=998244353LL;
int n,q,k;
int a[N],na[N],b[N],nb[N];
int x,y,z,u;
namespace lib{
    u64 read(){
        u64 n=0;
        char c=getchar();
        while(c<'0'||c>'9')c=getchar();
        while(c>='0'&&c<='9'){
            n=n*10+c-'0';
            c=getchar();
        }
        return n;
    }
    char r[30];
    void write(u64 num){
        if(num==0){
            putchar('0');
            return;
        }
        int t=0;
        while(num){
            r[t++]=num%10+'0';
            num/=10;
        }
        while(t)putchar(r[--t]);
    }
    u64 s;
    u64 rand(u64 l,u64 r){
        s=s*19260817+1;
        return ((s>>8)%(r-l+1)+l);
    }
    int ra,t;
    void init(){
        n=read();k=read();
        if(k<2){
            for(int i=1;i<=n;i++){
                a[i]=read();na[i]=read();
            }
            for(int i=1;i<=n;i++){
                b[i]=read();nb[i]=read();
            }
        }else{
            s=read();ra=read();
            u64 bacs=s;
            for(int i=1;i<=n;i++){
            	s=s*19260817+1;
        		a[i]=((s>>8)%ra+1);
                //a[i]=rand(1,ra);
                s=s*19260817+1;
        		//na[i]=((s>>8)%(M-1)+1);
                //na[i]=rand(1,M-1);
            }
            s=bacs;
            for(int i=1;i<=n;i++){
            	s=s*19260817+1;
        		//a[i]=((s>>8)%ra+1);
                //a[i]=rand(1,ra);
                s=s*19260817+1;
        		na[i]=((s>>8)%(M-1)+1);
                //na[i]=rand(1,M-1);
            }
            bacs=s;
            for(int i=1;i<=n;i++){
                s=s*19260817+1;
        		b[i]=((s>>8)%ra+1);
                //a[i]=rand(1,ra);
                s=s*19260817+1;
        		//nb[i]=((s>>8)%(M-1)+1);
            }
            s=bacs;
            for(int i=1;i<=n;i++){
                s=s*19260817+1;
        		//b[i]=((s>>8)%ra+1);
                //a[i]=rand(1,ra);
                s=s*19260817+1;
        		nb[i]=((s>>8)%(M-1)+1);
            }
        }
        q=read();
    }
    u64 lastans;
    u64 res;
    void reply(u64 num){
        if(k<2){
            write(num);putchar('\n');
        }else{
            res=res*233+num;
        }
        lastans^=num;
    }
    void query(){
        if(k<2){
            x=read();y=read();z=read();u=read();
        }else{
        	s=s*19260817+1;
        	x=((s>>8)%n+1);
        	s=s*19260817+1;
        	y=((s>>8)%n+1);
        	s=s*19260817+1;
        	z=((s>>8)%n+1);
        	s=s*19260817+1;
        	u=((s>>8)%n+1);
            //x=rand(1,n);y=rand(1,n);z=rand(1,n);u=rand(1,n);
        }
        if(k&1){
        	int t=lastans%n+1;
        	if((x+=t)>n)x-=n;
        	if((y+=t)>n)y-=n;
        	if((z+=t)>n)z-=n;
        	if((u+=t)>n)u-=n;
            /*x=(x+lastans)%n+1;
            y=(y+lastans)%n+1;
            z=(z+lastans)%n+1;
            u=(u+lastans)%n+1;*/
        }
    }
    void stop(){
        if(k>=2){write(res);putchar('\n');}
    }
}
int main(){
	lib::init();
	//现在你可以使用生成的a,na,b,nb
	
    //回答第一问
    
	lib::reply(233);
	
	for(int i=1;i<=q;i++){
		lib::query();
		
		//回答第二问 
        
		lib::reply(233);
	}
	lib::stop();
}
```
## 输出格式

如果$k=0$，则会分别输出每一问的答案

否则，只会输出一个整数用于检查结果是否正确
## 样例

### 样例输入 #1
```
2 0
1 1
3 3
2 2
4 4
9
1 1 1 1
1 1 1 2
1 1 2 2
2 1 1 1
1 2 1 2
1 2 2 2
2 2 1 1
2 2 1 2
2 2 2 2

```
### 样例输出 #1
```
18
2
6
4
2
18
16
0
12
12

```
### 样例输入 #2
```
2 0
1 1
2 2
2 2
3 3
9
1 1 1 1
1 1 1 2
1 1 2 2
1 2 1 1
1 2 1 2
1 2 2 2
2 2 1 1
2 2 1 2
2 2 2 2

```
### 样例输出 #2
```
11
2
5
3
2
11
9
0
6
6

```
### 样例输入 #3
```
5 0
1 1
1 1
1 1
2 1
2 1
1 1
1 1
2 1
2 1
3 1
7
2 4 1 1
1 3 3 4
3 4 5 5
2 5 4 4
1 5 5 5
1 3 1 2
1 2 3 4

```
### 样例输出 #3
```
11
0
6
5
6
5
0
6

```
### 样例输入 #4
```
3 0
3 1
2 2
1 3
4 4
5 5
6 6
12
1 3 2 2
1 2 2 3
3 1 1 2
2 1 3 1
1 1 2 3
3 1 3 1
3 2 2 3
1 2 3 3
1 2 1 3
3 2 1 1
2 2 1 3
3 3 1 2

```
### 样例输出 #4
```
90
30
33
54
45
11
90
55
18
45
20
30
27

```
### 样例输入 #5
```
3 2 233 5 10

```
### 样例输出 #5
```
15618218285282996994
```
### 样例输入 #6
```
3 0
3 754517792
1 842082509
4 600944080
2 592435186
5 348652025
5 247250863
10
1 3 3 2
3 2 1 1
2 2 3 2
2 1 2 1
3 3 3 1
2 3 3 2
1 3 3 3
1 3 3 3
2 2 1 3
2 1 2 1

```
### 样例输出 #6
```
988687952
712318441
204869162
71500349
703342331
285345621
783818790
712318441
712318441
276369511
703342331

```
## 提示

样例1解释：

当选择第二组武器时，一定能进行一次有效攻击

当选择第一组武器时，只有选择第一组水晶才能进行一次有效攻击

因而，不难求出每一问的答案

建议根据样例进一步理解题意

样例5与样例6一致

数据范围：

对于所有数据，满足$1\le x,y,z,u \le n$，$1\le a_i,b_i\le 10^9$，$1\le na_i,nb_i\le 998244352$

如未特别说明，$k=3$，即：由模板生成数据，强制在线

如果$k=2$，那么这组数据仍由生成器生成，但不强制在线，也就是你可以在不回答询问的情况下得到下一个询问的真实值，随后按顺序回答即可

测试点| 分值| n | q| 特殊性质
:-: | :-: | :-: | :-: | :-:
1| 4| 100| 100| $k=2$| 
2| 14| 3000| 3000| $k=2$|
3| 11| 100000| 100000| $a_i,b_i\le 100$|
4| 10| 15| 4000000| |
5| 12| 100| 4000000| |
6| 14| 5000| 4000000| |
7| 16| 100000| 100000| |
8| 19| 2500000| 4000000| |


---

---
title: "ygg发神威"
layout: "post"
diff: 省选/NOI-
pid: P5647
tag: ['树形数据结构', '线段树', '二分', '平衡树', 'O2优化', '枚举', '排序']
---
# ygg发神威
## 题目背景

ygg 发神威了，机房的萌新们瑟瑟发抖。
## 题目描述

ygg 的机房内共有 $n$ 台电脑且都被使用，为了节省机房内电脑的开销，第 $i$ 台电脑会同时被 $a_i$ 个萌新使用。每台电脑都装有一个「多人在线交流平台」，一台电脑会直接地或间接地通过这个平台与其他所有电脑连接。由于「多人在线交流平台」仍然处于测试阶段，如果一台电脑有多于一种不同的消息传输方式将消息传输到另外的任意一台电脑，就会有各种稀奇古怪的问题产生。两种消息的传输方式被认为是不同的，当且仅当传输消息所经过的直接连接的线路的集合不同，或者传输所经过的电脑的集合不同。当然，消息的传输肯定不会经过一条线路多次。为了避免这种状况，「多人在线交流平台」的线路被特殊地设计了，以使得任意两台电脑之间的传输线路唯一。同时，为了防止一台电脑负荷过大，一台电脑最多会通过「多人在线交流平台」的线路与 $p$ 台电脑相连。

原本两台通过「多人在线交流平台」的线路相连的电脑之间可以相互传输数据，可是 ygg 发现，这会允许使用两台电脑的萌新们互相发送消息，引起大规模~~考试作弊~~膜拜 ygg 的行为。所以他大发神威，切断了所有连接线路的一半。具体地，他将原本通过「多人在线交流平台」的双向线路连接的两台电脑之间的线路变成了单向线路。即，原本通过一条双向线路连接的两台电脑中，只能有一台电脑向另一台电脑发送消息，而另一台电脑不能将任何消息发送回来。

机房内的萌新们在每个时刻都有若干条消息需要传递。如果一台电脑 $i$ 能够直接或间接地通过「多人在线交流平台」的线路连接到电脑 $j$，那么使用电脑 $i$ 的 $a_i$ 个萌新中的任何一个都可以向使用电脑 $j$ 的 $a_j$ 个萌新发送消息。显然，使用同一台电脑的萌新之间的消息只需要在线下传达，不需要使用「多人在线交流平台」，因此不会计入线上发送的消息。

其实机房中的萌新们早已知道了「多人在线交流平台」的管理员密码，所以能够对其线路的连接方向做出修改。可无论他们怎么尝试，都不能恢复最开始时双向连接的状态了。机房中的萌新们当然希望能够尽可能地发送消息，所以他们想要知道，在机房的电脑仅被单向的线路连接时，每一时刻最多能有多少条消息被通过「多人在线交流平台」发送。

为了简化问题，我们假设机房内的所有萌新均能够在同一时刻发送线上消息，并且每一个萌新可以同时向多个人发送消息。

**简要题面：给一棵结点编号** $1\sim n$**，结点权值** $a_i$**，且结点度数最大为** $p$ **的树。求将树的每条边改为有向边后下式的最大值：**

$$\sum_{i=1}^{n}\sum_{j=1}^{n}a_ia_j\left[i\rightarrow j\right]$$

$\left[i\rightarrow j\right]$ **定义为：若编号为** $i$ **的结点能通过有向边到达编号为** $j$ **的结点，则值为** $1$**；否则值为** $0$**，且** $\left[i\rightarrow i\right]=0$**。**
## 输入格式

输入共 $(n+1)$ 行。

第一行两个正整数 $n$ 和 $p$，分别代表机房内的电脑数与所有电脑的负荷的最大值。  
第二行共 $n$ 个正整数，第 $i$ 个整数 $a_i$ 为使用第 $i$ 台电脑的萌新的数量。  
接下来 $(n-1)$ 行，第 $(i+2)$ 行两个整数 $u_i,v_i$ ，表示第 $u_i$ 和 $v_i$ 台电脑之间原本有一条「多人在线交流平台」的双向线路。
## 输出格式

输出一行一个整数，表示在某一时刻能够发送的消息数的最大值。
## 样例

### 样例输入 #1
```
4 2
1 2 3 4
1 2
3 2
4 1

```
### 样例输出 #1
```
35

```
## 提示

### 样例解释

能够发送的消息最多时的消息传递方向如下：

![](https://i.loli.net/2019/10/30/3AsqcyzdY25E8gP.png)

在该连接方式下发送消息最多的时刻，使用 $1$ 号电脑的 $1$ 个萌新向 $5$ 个萌新各发送了一条消息，共 $1\times5=5$ 条消息；  
使用 $2$ 号电脑的 $2$ 个萌新分别向 $3$ 个萌新各发送了一条消息，共 $2\times3=6$ 条消息；  
使用 $3$ 号电脑的 $3$ 个萌新不能向任何萌新发送线上消息，因此没有消息从该电脑发送；  
使用 $4$ 号电脑的 $4$ 个萌新分别向 $6$ 个萌新各发送了一条消息，共 $4\times6=24$ 条消息。  
因此，在某一时刻，最多可以有 $5+6+24=35$ 条线上消息被发送。   
可以使用枚举法验证，不存在一种单向的连接方式，使得在某一时刻发送的线上消息的数量能够达到 $36$ 条或更多。

### 数据范围及约定

对于 $10\%$ 的数据，$n\le10$；  
对于另外 $10\%$ 的数据，$n=p+1$；  
对于另外 $10\%$ 的数据，$p=2$；  
对于另外 $10\%$ 的数据，$p\le20$；  
对于另外 $10\%$ 的数据，$p\le40$；  

对于所有数据，$2\le n\le10^5$，$2\le p\le50$，$1\le a_i\le100$，$1\le u_i,v_i\le n$。保证给出的双向连接线路能够使任意两台电脑之间的消息传输线路唯一。保证至少有一台电脑原本通过「多人在线交流平台」连接的线路数恰好为 $p$，且没有电脑原本连接的线路数大于 $p$。


---

---
title: "丝之割"
layout: "post"
diff: 省选/NOI-
pid: P6047
tag: ['动态规划 DP', '贪心', '2020', '排序', '斜率优化']
---
# 丝之割
## 题目背景

Pharloom 是一个神秘的王国，[丝线与歌](https://www.bilibili.com/video/av43623335)是那里最强大的力量。多弦琴是 Pharloom 的一种强大武器，正如多项式是 OI 中的强大武器。

因为你很讨厌多项式，你决定摧毁多弦琴。
## 题目描述

下面这部分题面只是为了帮助你理解题意，并没有详细的解释。更为严谨清晰的叙述见形式化题意。

多弦琴由两根支柱和连接两根支柱的 $m$ 条弦组成。每根支柱上都均匀安放着 $n$ 个固定点，第 $i$ 条弦连接上方支柱的第 $u_i$ 个固定点和下方支柱的第 $v_i$ 个固定点。

![](https://cdn.luogu.com.cn/upload/image_hosting/14igq7bn.png)

> 上图是一把多弦琴

为了摧毁多弦琴，你可以进行若干次切割操作。在一次切割操作中，你可以选择上方支柱的某一个固定点 $u$ 和下方支柱的一个固定点 $v$，所有被 $u$ 到 $v$ 的连线**从左到右**穿过的弦都将被破坏。但同时，你需要付出 $a_u \times b_v$ 的代价。

形式化题意：有 $m$ 条弦，一条弦可以抽象为一个二元组 $(u,v)$，你可以进行任意次切割操作，一次切割操作你将选择两个下标 $i$ 和 $j$ 满足 $i,j \in [1,n]$，然后所有满足 $u>i,v<j$ 的弦 $(u,v)$ 都将被破坏，同时你将付出 $a_i \times b_j​$ 的代价。求破坏所有弦的最小代价和。
## 输入格式

第一行两个整数 $n,m$。

第二行 $n$ 个整数 $a_1,a_2,\dots,a_n$。

第三行 $n$ 个整数 $b_1,b_2,\dots,b_n$。

接下来 $m$ 行每行两个整数 $u,v$，表示有一条弦 $(u,v)$。

以上输入的意义见题目描述。
## 输出格式

一行一个整数，答案。
## 样例

### 样例输入 #1
```
5 2
3 9 1 9 9
9 9 1 9 3
2 1
5 4
```
### 样例输出 #1
```
6
```
### 样例输入 #2
```
5 1
9 9 9 9 1
1 9 9 9 9
3 3
```
### 样例输出 #2
```
81
```
## 提示

#### 样例解释

对于第一组样例，使用两次切割，分别为 $(1,3)$，$(3,5)$，花费代价 $3 \times 1 + 1 \times 3 = 6$。

对于第二组样例，注意切割 $(5,1)$ 不能使弦 $(3,3)$ 消失。

---

#### 数据范围

**「本题采用捆绑测试」**

对于所有测试点，保证 $1 \leq n, m \leq 3\times 10^5$，$2 \leq u \leq n$，$1 \leq v \leq n-1$，$1 \leq a_i,b_i \leq 10^6$。

$\text{Subtask 1 (21 pts)}$ $n,m \leq 6$。

$\text{Subtask 2 (3 pts)}$ $m=1$。

$\text{Subtask 3 (1 pts)}$ $a_1=b_n = 1$。

$\text{Subtask 4 (25 pts)}$ $n,m \leq 100$。

$\text{Subtask 5 (29 pts)}$ $n,m \leq 10^3$。

$\text{Subtask 6 (21 pts)}$ 无特殊限制。

---
#### 提示

如果你认真观察了数据范围，你会发现这把多弦琴一定能够被破坏。


---

---
title: "分散层叠算法(Fractional Cascading)"
layout: "post"
diff: 省选/NOI-
pid: P6466
tag: ['二分', 'O2优化', '排序', '分散层叠']
---
# 分散层叠算法(Fractional Cascading)
## 题目背景

`Fractional Cascading` 算法，国内多译为“分散层叠”。

本题仅提供一个简单而经典的方式给算法验证正确性，原则上会尽量卡掉比较暴力的做法，但不保证乱搞一定无法通过。
## 题目描述

给出 $k$ 个长度为 $n$ 的**有序数组**。

现在有 $q$ 个查询 : 给出数 $x$，分别求出每个数组中大于等于 $x$ 的最小的数(非严格后继)。

若后继不存在，则定义为 $0$。

每个查询的答案定义为 $k$ 个后继的**异或和**。

你需要**在线地**回答这些询问。

由于输出太多不好，给出参数 $d$，你只需要输出编号为 $d$ 的倍数的询问的答案。询问从 $1$ 开始编号。


## 输入格式

第一行四个整数 $n,k,q,d$，意义如题面所述。

后 $k$ 行，每行 $n$ 个整数，描述一个数组。**所有数组中出现过的数不重复**，保证每个数组严格递增。

后 $q$ 行，每行一个整数 $x$，描述一个询问。

输入中所得的 $x$ 需要与上一个询问的答案(**无论是否输出**)异或解密，如果这是第一个询问，则无需操作。
## 输出格式

对于编号为 $d$ 的倍数的每个询问，输出一行一个整数，表示  $k$ 个后继的异或和。
## 样例

### 样例输入 #1
```
6 3 8 1
1 4 6 7 10 20 
2 3 8 11 14 18 
5 9 12 13 15 17 
20
6
9
4
29
5
14
9
```
### 样例输出 #1
```
20
6
9
23
13
11
11
3
```
### 样例输入 #2
```
2 4 1 1
64 65
25 26
44 62
35 81
81
```
### 样例输出 #2
```
81
```
### 样例输入 #3
```
20 4 10 1
553 897 1333 1949 2261 2541 2901 3133 3209 3713 4373 4749 5761 7405 8733 10417 13013 15185 16825 16981 
246 750 806 1534 2274 2470 2486 3278 3954 4618 5306 5638 6114 6310 7106 7522 7734 8170 8702 8974 
1047 1275 2347 2711 3607 4719 5911 6051 7099 7519 8087 8435 8499 8687 8835 10151 10491 11159 11915 12483 
548 1392 2188 3260 3404 3768 5076 5668 5732 6612 7284 7492 8900 9008 9536 9768 11160 12096 12300 13100 
3133
3331
4139
2685
2229
1163
3228
2694
3913
7058
```
### 样例输出 #3
```
600
8156
676
1176
600
3800
8
432
8156
320
```
## 提示

#### 样例解释

对于样例 1，解密后的数据为:

```cpp
6 3 8 1
1 4 6 7 10 20
2 3 8 11 14 18
5 9 12 13 15 17
20
18
15
13
10
8
5
2
```
---
#### 数据规模的与约定
- 对于 $20\%$ 的数据，$k\leq 10$，$n\leq 1000$，$q\leq 1000$。
- 对于 $50\%$ 的数据，$k\leq 10$，$q\leq 2\times 10^5$。
- 对于 $100\%$ 的数据，$1 \leq k\leq 100$，$2\leq n\leq 10^4$，$q\leq 5\times 10^5$，$1\leq d\leq 10$，解密后输入中出现的数均在 $[1,5\times 10^8)$ 范围内。


---

---
title: "[USACO20DEC] Square Pasture G"
layout: "post"
diff: 省选/NOI-
pid: P7153
tag: ['数学', '2020', 'USACO', 'O2优化', '排序', '双指针 two-pointer']
---
# [USACO20DEC] Square Pasture G
## 题目描述

Farmer John 最大的牧草地可以被看作是一个由方格组成的巨大的二维方阵（想象一个巨大的棋盘）。现在，有 $N$ 头奶牛正占据某些方格（$1≤N≤200$）。

Farmer John 想要建造一个可以包围一块正方形区域的栅栏；这个正方形必须四边与 $x$ 轴和 $y$ 轴平行，最少包含一个方格。请帮助他求出他可以包围在这样的区域内的不同的奶牛子集的数量。注意空集应当被计算为答案之一。 
## 输入格式

输入的第一行包含一个整数 $N$。以下 $N$ 行每行包含两个空格分隔的整数，表示一头奶牛所在方格的坐标 $(x,y)$。所有 $x$ 坐标各不相同，所有 $y$ 坐标各不相同。所有 $x$ 与 $y$ 的值均在 $0…10^9$ 范围内。

注意尽管所有奶牛所在的方格坐标均非负，但围成的正方形区域可以包含坐标为负的方格。
## 输出格式

输出 FJ 可以包围的奶牛的子集数量。可以证明这个数量可以用 32 位有符号整数型存储。 
## 样例

### 样例输入 #1
```
4
0 2
2 3
3 1
1 0

```
### 样例输出 #1
```
14
```
### 样例输入 #2
```
16
17 4
16 13
0 15
1 19
7 11
3 17
6 16
18 9
15 6
11 7
10 8
2 1
12 0
5 18
14 5
13 2
```
### 样例输出 #2
```
420
```
## 提示

 - 测试点 1-5 中，所有奶牛所在的方格的坐标均小于 20 。
 - 测试点 6-10 中，$N≤20$。
 - 测试点 11-20 没有额外限制。

供题：Benjamin Qi 



---

---
title: "[CCO 2021] Travelling Merchant"
layout: "post"
diff: 省选/NOI-
pid: P7831
tag: ['图论', '贪心', '2021', 'CCO（加拿大）', '拓扑排序']
---
# [CCO 2021] Travelling Merchant
## 题目描述

一个国家有 $n$ 个城市和 $m$ 条单向道路，一个旅行商在这些城市之间旅行。

第 $i$ 条道路从城市 $a_i$ 到城市 $b_i$，只有当他的资产不少于 $r_i$ 元才可以走这条道路，走过这条道路之后他的资产会增加 $p_i$ 元。

他希望自己可以永远不停的游走下去，于是他想知道从任意一个城市出发至少需要多少元初始资产。
## 输入格式

第一行，两个整数 $n, m$；

接下来 $m$ 行，第 $i$ 行有四个整数 $a_i, b_i, r_i, p_i$。
## 输出格式

一行，$n$ 个整数，若第 $i$ 个城市无解，第 $i$ 个整数为 $-1$；否则，为至少需要的初始资产（单位为元）。
## 样例

### 样例输入 #1
```
5 5
3 1 4 0
2 1 3 0
1 3 1 1
3 2 3 1
4 2 0 2
```
### 样例输出 #1
```
2 3 3 1 -1
```
## 提示

#### 样例 #1 解释
以第 $2$ 座城市为例：从第 $2$ 座城市出发，初始资产 $3$ 元，则可以在第 $2, 1, 3$ 三座城市无限绕圈。
#### 数据范围
对于 $\frac{2}{7}$ 的数据，$2 \leq n, m \leq 2 \times 10^3$；

对于另 $\frac{15}{49}$ 的数据，$p_i = 0$；

对于 $100\%$ 的数据，$2 \leq n, m \leq 2 \times 10^5$，$1 \leq a_i, b_i \leq n$，$a_i \neq b_i$，$0 \leq r_i, p_i \leq 10^9$，**保证没有自环但可能有重边**。
#### 题目来源
[CCO2021](https://cemc.math.uwaterloo.ca/contests/computing/2021/index.html) D2T1


---

---
title: "「SWTR-7」Spider Solitaire"
layout: "post"
diff: 省选/NOI-
pid: P7877
tag: ['模拟', 'Special Judge', 'O2优化', '图论建模', '拓扑排序', '洛谷月赛']
---
# 「SWTR-7」Spider Solitaire
## 题目背景

#### 题目描述下方有简化题意。

![](https://cdn.luogu.com.cn/upload/image_hosting/7tdo8cdf.png)

---

小 A 在玩蜘蛛纸牌。  
为了方便你理解蜘蛛纸牌，小 A 给出了简化后的游戏规则：

- 一副牌有 $n$ 张，从小到大分别为 $1,2,\cdots,n$。
- 现有 $m$ 个牌堆，$1$ 副牌。每个牌堆中有 $0$ 张或多张牌。
- 定义「龙」$a_1,a_2,\cdots,a_d$ 为满足 $a_i-1=a_{i+1}\ (1\leq i<d)$ 的任意多张连续的牌。**一张牌也是一个「龙」。**
- 一组连续的牌可以移动，当且仅当这组牌形成了一个「龙」，且「龙」在牌堆的**最右边**。
- 一组连续的牌只能移动到一个**非空**牌堆的最右边，**且必须满足可以与该非空牌堆最右边的「龙」构成一条更大的「龙」**。
- 游戏胜利，当且仅当所有的 $n$ 张牌形成了一个「龙」。

---

例如当 $m=3$，$n=9$，局面为

```plain
9 8 4 3 2 1
7 5
6
```

时，第一个牌堆最右边的 `4 3 2 1` 形成了一个「龙」，所以 `4 3 2 1` 可以移动。将 `4 3 2 1` 移动到第二个牌堆的最右边，此时局面为

```plain
9 8
7 5 4 3 2 1
6
```

接下来将第二个牌堆右边的 `5 4 3 2 1` 移动到第三个牌堆的最右边，此时局面为

```plain
9 8
7
6 5 4 3 2 1
```

接下来将第三个牌堆的 `6 5 4 3 2 1` 移动到第二个牌堆的最右边，此时局面为

```plain
9 8
7 6 5 4 3 2 1
\
```

接下来将第二个牌堆的 `7 6 5 4 3 2 1` 移动到第一个牌堆的最右边，此时牌堆为

```plain
9 8 7 6 5 4 3 2 1
\
\
```

因为所有 $9$ 张牌形成了一个「龙」，所以游戏胜利。
## 题目描述

给定一个蜘蛛纸牌初始局面，小 A 想知道能否获得胜利。若能，请输出 $\texttt{YES}$ 以及**获胜所需的最小步数**。否则输出 $\texttt{NO}$。

小 A 还想知道，对于每张牌 $i$，如果要移动 $i$ 至少需要多少步，**包括移动 $i$ 的这一步**。如果无法移动输出 `-1`。

---

#### 「简化题意」

有 $m$ 个**横向**的数堆，数堆里共有 $n$ 个数，每个数堆里有 $0$ 或多个数。所有数堆里的数组成了 $1\sim n$ 中的所有数。

你可以将一个数堆**最右边递减且公差为 $-1$ 的**连续若干个数 $a_1,a_2,\cdots,a_c$ **按照原来的顺序移到另外一个非空数堆的最右边**，当且仅当该非空数堆最右边的一个数 $b=a_1+1$。

求将所有的 $n$ 个数都移动到同一个数堆且满足从左往右依次递减的最小步数。如果无解输出 $\texttt{NO}$。

**此外，你还需要对于每个数 $i$，输出如果要移动 $i$ 至少需要多少步。**
## 输入格式

第一行一个整数 $T$，表示子任务编号。  
第二行两个整数 $n,m$，分别表示一副牌的张数和牌堆的个数。  
接下来 $m$ 行，每行首先一个整数 $c$ 表示该牌堆中牌的个数，接下来 $c$ 个整数 $b_1,b_2,\cdots,b_c$ **从左到右**描述这个牌堆。
## 输出格式

如果能够获胜，在第一行输出 $\texttt{YES}$，**第二行输出最少步数**。否则输出一行 $\texttt{NO}$。

无论是否能够获胜，你还需输出 $n$ 行，第 $i$ 行一个**介于 $-1$ 与 $n$ 之间的整数**，表示移动 $i$ 至少需要多少步。
## 样例

### 样例输入 #1
```
0
9 3
6 9 8 4 3 2 1
2 7 5
1 6

```
### 样例输出 #1
```
YES
4
1
1
1
1
1
2
3
-1
-1

```
### 样例输入 #2
```
0
13 4
4 13 10 1 7
3 11 4 8
4 6 5 3 2
2 12 9

```
### 样例输出 #2
```
YES
10
2
2
2
3
3
3
1
1
3
6
7
8
-1

```
### 样例输入 #3
```
0
5 1
5 5 4 3 2 1

```
### 样例输出 #3
```
YES
0
-1
-1
-1
-1
-1

```
### 样例输入 #4
```
0
17 10
2 12 14
1 3
3 1 13 15
0
2 9 8
1 5
3 16 7 6
2 11 2
1 4
2 17 10

```
### 样例输出 #4
```
YES
14
4
1
1
1
1
1
1
1
1
2
3
4
3
1
2
4
-1
```
### 样例输入 #5
```
0
13 4
4 10 1 13 7
4 11 12 4 8
4 6 5 3 2
1 9

```
### 样例输出 #5
```
NO
-1
2
2
3
3
3
1
1
-1
-1
6
5
-1

```
## 提示

**「样例 1 说明」**

因为 1,2,3,4,5 可以直接移动，所以至少需要 1 步即可移动。  
因为需要先将 5 移至 6 右侧，6 才能移动，所以至少需要 2 步即可移动。  
因为需要先将 5 移至 6 右侧，再将 4,3,2,1 移至 5 右侧，7 才能移动，所以至少需要 3 步即可移动。  
显然 8,9 无法移动。

**「Special Judge」**

本题使用 Special Judge，请**严格遵守输出格式**：

- 如果你正确输出对能否获胜的判定，且如果能够获胜，你正确输出最小步数，你将获得该测试点**至少** $40\%$ 的分数。
- **在上一部分的基础上**，如果你正确输出移动每张牌的最小步数，你将获得该测试点**剩下** $60\%$ 的分数。也就是说，如果你上一部分输出错误，你在这一部分也不会获得任何分数。
- **如果你的输出格式错误，你将获得该测试点 $0\%$ 的分数**，包括但不限于**只输出对能否获胜的判定**。
- 需要特别注意的是，如果你不能正确求出移动每张牌的最小步数，请**随机输出 $[-1,n]$ 之间的任意整数**，否则你将获得该测试点 $0\%$ 的分数。
- 每行结束后你都需要输出换行符，**包括最后一行**。

checker 将在题目最后给出。

**「数据范围与约定」**

**本题采用捆绑测试。**

- Subtask #0（0 points）：是样例。
- Subtask #1（15 points）：$n\leq 3\times 10^3$，$m=2$。
- Subtask #2（15 points）：$b_i>b_{i+1}\ (1\leq i<c)$，$n\leq 3\times 10^3$。
- Subtask #3（25 points）：$n\leq 14$，$m=3$。
- Subtask #4（30 points）：$n\leq 3\times 10^3$。
- Subtask #5（15 points）：无特殊限制。

对于 $100\%$ 的数据，$1\leq n,m\leq 5\times 10^4$。时间限制 1s，空间限制 512MB。

**「题目来源」**

[Sweet Round 07](https://www.luogu.com.cn/contest/51773) D。  
idea & solution & data：[Alex_Wei](https://www.luogu.com.cn/user/123294)；验题：[chenxia25](https://www.luogu.com.cn/user/138400)。

---

以下是 checker，你需要有 testlib.h 才能成功编译。

```cpp
#include "testlib.h"
#include <bits/stdc++.h>

using namespace std;

#define ll long long
#define pii pair <int,int>
#define fi first
#define se second
#define pb emplace_back
#define mp make_pair 
#define vint vector <int>
#define vpii vector <pii>
#define all(x) x.begin(),x.end()
#define sor(x) sort(all(x))
#define rev(x) reverse(all(x))
#define mem(x,v) memset(x,v,sizeof(x))

#define rint inf.readInt
#define reof inf.readEof()
#define reoln inf.readEoln()
#define rspace inf.readSpace()

// wrong answer : quitf(_wa,"The answer is wrong")
// accepted :  quitf(_ok,"The answer is correct")
// partly correct : quitp(0.5,"The answer is partly correct")

int main(int argc,char* argv[]){
	registerTestlibCmd(argc,argv);
	
	string jans=ans.readToken();
	string pans=ouf.readToken(jans);
	int sub=rint(),n=rint(),diff=0;
	
	if(jans=="YES"){
		int jstep=ans.readInt();
		int pstep=ouf.readInt();
		if(jstep!=pstep)quitf(_wa,"The answer is wrong");
	}
	
	for(int i=1;i<=n;i++){
		int jans=ans.readInt();
		int pans=ouf.readInt();
		if(jans!=pans)diff=1;
	}
	
	while(!ouf.seekEof())ouf.readToken();
	while(!inf.seekEof())inf.readToken();
	while(!ans.seekEof())ans.readToken();
	if(diff)quitp(0.4,"The answer is partially correct");
	else quitf(_ok,"OK, you AK IOI");
	
	return 0;
}
```


---

---
title: "[USACO22JAN] Multiple Choice Test P"
layout: "post"
diff: 省选/NOI-
pid: P8101
tag: ['USACO', '2022', '凸包', '极角排序']
---
# [USACO22JAN] Multiple Choice Test P
## 题目描述

奶牛们正在参加一个选择题测试。在通常的测试中，对每个问题你的选项会被单独评分然后累加，而在此测试中，你的选项在累加之后再评分。

具体地说，你被给定二维平面上的 $N$（$2 \le N \le 10^5$）组整数向量，其中每个向量用一个有序对 $(x,y)$ 表示。从每组中选择一个向量，使向量的总和尽可能远离原点。

输入保证向量的总数不超过 $2 \times 10^5$。每组至少包含 $2$ 个向量，并且一组内所有向量各不相同。输入同时保证每个 $x$ 和 $y$ 坐标的绝对值不超过 $\dfrac{10^9}{N}$。
## 输入格式

输入的第一行包含 $N$，为向量的组数。

每一组的第一行包含 $G$，为组中的向量数。以下 $G$ 行包含组中的向量。相邻组之间用空行分隔。
## 输出格式

输出最大可能的欧几里得距离的平方。
## 样例

### 样例输入 #1
```
3

2
-2 0
1 0

2
0 -2
0 1

3
-5 -5
5 1
10 10
```
### 样例输出 #1
```
242
```
## 提示

【样例解释】

最优方案是从第一组选择 $(1,0)$，从第二组中选择 $(0,1)$，从第三组选择 $(10,10)$。这些向量之和等于 $(11,11)$，与原点的距离平方等于 $11^2+11^2=242$。

【数据范围】

- 测试点 1-5 中，向量的总数不超过 $10^3$。
- 测试点 6-9 中，每一组恰好包含 $2$ 个向量。
- 测试点 10-17 没有额外限制。

供题：Benjamin Qi


---

---
title: "[USACO22OPEN] Hoof and Brain P"
layout: "post"
diff: 省选/NOI-
pid: P8276
tag: ['USACO', '2022', '拓扑排序', '启发式合并']
---
# [USACO22OPEN] Hoof and Brain P
## 题目描述

给定一个包含 $N$ 个结点和 $M$ 条边的有向图（$2 \leq N \leq 10^5$, $1 \leq M \leq 2 \cdot 10^5$），Farmer John 的奶牛们喜欢玩以下的双人游戏。

在图中的不同结点上放置两个指示物（可以用一些与奶牛相关的物品代替指示物）。每一回合，一名玩家，脑，选择一个需要沿某一条出边移动的指示物。另一名玩家，蹄，选择沿着哪条出边移动该指示物。两个指示物在任何时刻不允许处于同一个结点上。如果在某些时刻蹄不能做出合法的行动，则脑获胜。如果游戏可以无限进行下去，则蹄获胜。

给定 $Q$ 个询问（$1 \leq Q \leq 10^5$），包含两个指示物所在的初始结点。对于每个询问，输出哪名玩家获胜。
## 输入格式

输入的第一行包含 $N$ 和 $M$。

以下 $M$ 行每行包含两个整数 $a$ 和 $b$，表示一条从 $a$ 连向 $b$ 的边。

图中不包含自环或重边。

下一行包含 $Q$。

最后 $Q$ 行每行包含两个整数 $x$ 和 $y$，满足 $1\le x,y\le N$ 以及 $x\neq y$，表示指示物所在的初始结点。

## 输出格式

输出一个长为 $Q$ 的字符串，其中字符 B 表示脑获胜，H 表示蹄获胜。

**注意：本题的时间限制为 4 秒，通常限制的两倍。**
## 样例

### 样例输入 #1
```
9 10
1 2
2 3
3 4
4 7
3 5
1 6
6 8
8 9
9 6
7 2
4
1 5
1 2
1 6
2 4
```
### 样例输出 #1
```
BHHB
```
## 提示

【数据范围】

脑可以通过选择结点 $5$ 赢得第一局游戏；此时蹄将没有合法的行动。

脑可以通过选择结点 $4$ 然后选择结点 $7$ 赢得最后一局游戏；此时蹄没有合法的行动。

蹄赢得其他局游戏。

【测试点性质】

- 测试点 2-3 满足 $N\le 100$，$M\le 200$。
- 测试点 4-9 满足 $N\le 5000$。
- 测试点 10-21 没有额外限制。


---

---
title: "「DAOI R1」Fireworks"
layout: "post"
diff: 省选/NOI-
pid: P8288
tag: ['并查集', '树形 DP', '拓扑排序', '基环树']
---
# 「DAOI R1」Fireworks
## 题目背景

> 俯首，满城灯火交辉。
> 
> 回眸，漫天流星逆飞。
## 题目描述

人们以前通常会放烟花，而每个烟花都有它本身的美观度。

$ \texttt{Iratis} $ 想要在户外放烟花，但是有烟花之间有一些关系：

- 关系一：对于烟花 $ x $ ，有一个对应烟花 $ a_x $ ，若烟花 $ x $ 与烟花 $ a_x $ 一起燃放，就会使烟花 $ x $ 的美观度减少 $ b_x $ 。

- 关系二：有一些烟花是一个系列，必须同时燃放，其中有一个是主烟花，**每个烟花只会属于一个系列**。

特别地，若有一系列 $ S_1 $ （主烟花为 $ p_1 $ ） 。 $ p_1 $ 关系一所对应的烟花为系列 $ S_2 $ 中的烟花。而 $ S_1 $ 系列中的其他烟花与非 $ S_1,S_2 $ 系列中的烟花形成关系一。**那么对于这条关系一，它不会降低美观度。**

$ \texttt{Iratis} $ 家里有 $ n $ 个烟花，他希望选择其中的一些烟花燃放，使得这些**烟花的美观度总和**最大。
## 输入格式

第一行包含两个整数 $ n,m $，分别描述烟花的个数和和关系二的个数。

接下来 $ n $ 行，每行三个整数 $ v_i,a_i,b_i $ ，分别是这个烟花的美观度、关系一对应的烟花、关系一降低的美观度。

最后 $ m $ 行，每行先读入两个数 $ p_i,k_i $，然后是 $ k_i $ 个数，表示这 $ k_i $ 个烟花是一个系列，编号为 $ p_i $ 的烟花为主烟花。
## 输出格式

输出一行一个整数，表示烟花的美观度总和。
## 样例

### 样例输入 #1
```
3 0
2 2 1
2 3 1
2 1 1

```
### 样例输出 #1
```
3
```
### 样例输入 #2
```
4 1
3 2 1
3 1 3
3 4 2
3 3 2
1 2 1 3

```
### 样例输出 #2
```
7
```
## 提示

### 样例解释
#### 样例1解释

烟花 $ 1,2,3 $ 一起燃放，最大美观度为 $ 2+2+2-1-1-1=3 $ 。

#### 样例2解释

烟花 $ 1,3,4 $ 一起燃放。

由于 $ 1,3 $ 为同一系列且 $ 1 $ 为主烟花，所以 $ 3 $ 烟花的关系一不会生效。

故总的美观度为 $ 3 \times 3-2=7 $ 。

### 数据规模

**本题采用捆绑测试**

| Subtask | $ m $  | 分值 |
| :----------: | :----------: | :----------: |
| $ 0 $ | $ =0 $ | $ 30 $ |
| $ 1 $ | 无特殊限制 | $ 70 $ |

对于 $ 100\% $ 的数据，满足 $ 0 \leq m \leq n \leq 5 \times 10^5,0 \leq b_i \leq v_i \leq 10^{12},1 \leq a_i \leq n,a_i \neq i $ 。 


---

---
title: "『JROI-4』沈阳大街 2"
layout: "post"
diff: 省选/NOI-
pid: P8321
tag: ['动态规划 DP', '2022', '洛谷原创', 'O2优化', '排序', '洛谷月赛']
---
# 『JROI-4』沈阳大街 2
## 题目描述

给定两个长度为 $n$ 的序列 $A,B$，满足：

* $\forall 1\le i<n,A_i \ge A_{i+1}$ 

* $A_n\ge \min\limits_{i=1}^n(B_i)$

$\pi$ 是一个长度为 $n$ 的排列，定义价值函数 $f(\pi)$：

$$
f(\pi)=\prod_{i=1}^n\min(A_i,B_{\pi(i)})
$$

每种排列出现的概率相等，求 $f(\pi)$ 的期望对 $998244353$ 取模的结果。

即求:

$$
\left(\dfrac{1}{n!}\sum_\pi f(\pi)\right) \bmod 998244353
$$

## 输入格式

第一行输入一个整数 $n$。

第二行 $n$ 个整数表示 $A_i$。

第三行 $n$ 个整数表示 $B_i$。
## 输出格式

输出一行一个整数，为答案。
## 样例

### 样例输入 #1
```
8
15 14 13 10 9 6 3 2 
2 10 8 2 9 1 10 2 
```
### 样例输出 #1
```
114102208
```
## 提示

**本题采用捆绑测试。**

|  子任务编号 | 分值 | 特殊限制 |
| :-----------: | :---:| :-----------: |
| 1 | 5 | $1\le n\le 8$ |
| 2 | 35 | $1\le n\le 50$ |
| 3 | 20 | $A_n\ge \max\limits_{i=1}^n(B_i)$ |
| 4 | 40 | 无 |

对于 $100\%$ 的数据满足 $1\le n\le 5000$，$1\le A_i,B_i\le 10^9$。


---

---
title: "[USACO23FEB] Fertilizing Pastures G"
layout: "post"
diff: 省选/NOI-
pid: P9128
tag: ['数学', '贪心', 'USACO', '2023', '排序']
---
# [USACO23FEB] Fertilizing Pastures G
## 题目描述

There are $N$ pastures $(2 \le N \le 2 \cdot 10^5)$, connected by $N−1$ roads, such that they form a tree. Every road takes $1$ second to cross. Each pasture starts out with $0$ grass, and the ith pasture's grass grows at a rate of $a_i (1 \le a_i \le 10^8)$ units per second. Farmer John is in pasture $1$ at the start, and needs to drive around and fertilize the grass in every pasture. If he visits a pasture with $x$ units of grass, it will need $x$ amount of fertilizer. A pasture only needs to be fertilized the first time it is visited, and fertilizing a pasture takes $0$ time.

The input contains an additional parameter $T \in \{0,1\}$.

 - If $T=0$, Farmer John must end at pasture $1$.
 - If $T=1$, Farmer John may end at any pasture.

Compute the minimum amount of time it will take to fertilize every pasture and the minimum amount of fertilizer needed to finish in that amount of time. 
## 输入格式

The first line contains $N$ and $T$.

Then for each $i$ from $2$ to $N$, there is a line containing $p_i$ and $a_i$, meaning that there is a road connecting pastures $p_i$ and $i$. It is guaranteed that $1 \le p_i<i$. 
## 输出格式

 The minimum amount of time and the minimum amount of fertilizer, separated by spaces. 
## 样例

### 样例输入 #1
```
5 0
1 1
1 2
3 1
3 4
```
### 样例输出 #1
```
8 21
```
### 样例输入 #2
```
5 1
1 1
1 2
3 1
3 4
```
### 样例输出 #2
```
6 29
```
## 提示

### Explanation for Sample 1

The optimal route for Farmer John is as follows: 

 - At time $1$, move to node $3$, which now has $1 \cdot 2=2$ grass and so needs $2$ fertilizer.
 - At time $2$, move to node $5$, which now has $2 \cdot 4=8$ grass and so needs $8$ fertilizer.
 - At time $3$, move back to node $3$, which we already fertilized and so don't need to fertilize again.
 - At time $4$, move to node $4$, which now has $4 \cdot 1=4$ grass and so needs $4$ fertilizer.
 - At time $5$, move back to node $3$, which we already fertilized.
 - At time $6$, move back to node $1$.
 - At time $7$, move to node $2$, which now has $7 \cdot 1=7$ grass and so needs $7$ fertilizer.
 - At time $8$, return to node $1$. 

This route takes $8$ time and uses $2+8+4+7=21$ fertilizer. It can be shown that $8$ is the least possible amount of time for any route that returns to node $1$ at the end and $21$ is the least possible fertilizer used for any route that returns to node $1$ and takes $8$ time.

### Explanation for Sample 2

The optimal route for Farmer John is as follows:

 - At time $1$, move to node $2$, which now has $1 \cdot 1=1$ grass and so needs $1$ fertilizer.
 - At time $2$, move back to node $1$.
 - At time $3$, move to node $3$, which now has $3 \cdot 2=6$ grass and so needs $6$ fertilizer.
 - At time $4$, move to node $5$, which now has $4 \cdot 4=16$ grass and so needs $16$ fertilizer.
 - At time $5$, move back to node $3$, which we already fertilized and so don't need to fertilize again.
 - At time $6$, move to node $4$, which now has $6 \cdot 1=6$ grass and so needs $6$ fertilizer.

This route takes $6$ time and uses $1+6+16+6=29$ fertilizer. It can be shown that $6$ is the least possible amount of time for any route and $29$ is the least possible fertilizer used for any route that takes $6$ time.

### SCORING

 - Inputs $3-10$: $T=0$
 - Inputs $11-22$: $T=1$
 - Inputs $3-6$ and $11-14$: No pasture is adjacent to more than three roads.
## 题目翻译

### 题目描述

有 $N$ 个顶点的树，经过节点之间的每一条边都需要 $1s$。每个顶点一开始的权值均为 $0$，第 $i$ 个点的权值的增长速率为 $a_i/s$。FJ 从 $1$ 号顶点出发遍历整棵树。当 FJ 走到某个节点时，若该节点的权值为 $x$，则需要支出大小为 $x$ 的费用。（当然，只需在第一次经过该节点时需要支出。）

给出一个参数 $T$:

+ **若 $T=0$，FJ 必须回到 $1$ 号节点**。

+ **若 $T=1$，FJ 可以在任意节点结束他的遍历**。

求遍历所有节点的最小时间和此时需要付出的最小的费用。

### 输入格式

第一行包括 $N$ 和 $T$。

第 $2$ 行到第 $N$ 行，包含两个整数 $p_i$ 和 $a_i$,$a_i$ 的含义见上文。$p_i$ 则表示节点 $i$ 和 $p_i$ 之间有一条边相连。

### 输出格式
两个整数：遍历所有节点的最小时间和此时需要付出的最小的费用。

$2 \le N \le 2 \times 10^5,T \in \{0,1\},1 \le a_i \le 10^8, 1 \le p_i < i$。


---

---
title: "[省选联考 2023] 过河卒"
layout: "post"
diff: 省选/NOI-
pid: P9169
tag: ['博弈论', '各省省选', '2023', 'O2优化', '广度优先搜索 BFS', '拓扑排序']
---
# [省选联考 2023] 过河卒
## 题目背景

棋盘上有一个过河卒，需要走到底线。卒行走的规则是可以向左移动一格，向右移动一格或者向前移动一格。同时在棋盘上有两个另一方的棋子，需要拦截这个卒走到底线。这两个棋子的走法和帅一致，可以走到前后左右四个方向上相邻的格子。因此本题可以称为“帅拦过河卒”。
## 题目描述

有一个 $n$ 行 $m$ 列的棋盘。我们用 $(i,j)$ 表示第 $i$ 行第 $j$ 列的位置。棋盘上有一些 障碍，还有一个黑棋子和两个红棋子。

游戏的规则是这样的: 红方先走，黑方后走，双方轮流走棋。红方每次可以选择一个红棋子，向棋盘的相邻一格走一步。具体而言，假设红方选择的这个棋子位置在 $(i,j)$，那么它可以走到 $(i-1,j),(i+1,j),(i,j-1),(i,j+1)$ 中的一个，只要这个目的地在棋盘内且没有障碍且没有红方的另一个棋子。

黑方每次可以将自己的棋子向三个方向之一移动一格。具体地，假设这个黑棋子位置在 $(i,j)$，那么它可以走到 $(i-1,j),(i,j-1),(i,j+1)$ 这三个格子中的一个，只要这个目的地在棋盘内且没有障碍。

在一方行动之前，如果发生以下情况之一，则立即结束游戏，按照如下的规则判断胜负（列在前面的优先）：

- 黑棋子位于第一行。此时黑方胜。

- 黑棋子和其中一个红棋子在同一个位置上。此时进行上一步移动的玩家胜。

- 当前玩家不能进行任何合法操作。此时对方胜。

现在假设双方采用最优策略，不会进行不利于自己的移动。也就是说:

- 若存在必胜策略，则会选择所有必胜策略中，不论对方如何操作，本方后续获胜所需步数最大值最少的操作。
- 若不存在必胜策略，但存在不论对方如何行动，自己都不会落败的策略，则会选择任意一种不败策略。
- 若不存在不败策略，则会选择在所有策略中，不论对方如何操作，对方后续获胜所需步数最小值最大的操作。

如果在 $100^{100^{100}}$ 个回合之后仍不能分出胜负，则认为游戏平局。请求出游戏结束时双方一共移动了多少步，或者判断游戏平局。
## 输入格式

**本题有多组测试数据**。

输入的第一行包含两个整数 $\text{id},T$，分别表示测试点编号和数据组数。特别地，样例的 $\text{id}$ 为 $0$。

接下来包含 $T$ 组数据，每组数据的格式如下：

第一行包含两个正整数 $n,m$，表示棋盘的行数和列数。

接下来 $n$ 行，每行包含一个长度为 $m$ 的字符串，其中第 $i$ 行的第 $j$ 个字符表示棋盘上 $(i,j)$ 这个位置的状态。

在这些字符中：$\texttt{'.'}$ 表示空位；$\texttt{'\#'}$ 表示障碍物；$\texttt{'X'}$ 表示黑棋；$\texttt{'O'}$ 表示红棋。

保证黑棋恰好有一个，红棋恰好有两个，且黑棋不在第一行。
## 输出格式

对于每组数据，输出一行字符串。

如果游戏平局，请输出一行 $\texttt{"Tie"}$。

如果红方胜，请输出一行 $\texttt{"Red t"}$。其中 $\texttt{t}$ 为游戏结束时双方移动的步数之和。显然这应该是一个奇数。

如果黑方胜，请输出一行 $\texttt{"Black t"}$。其中 $\texttt{t}$ 为游戏结束时双方移动的步数之和。显然这应该是一个偶数。

注意，请输出双引号内的字符串，不包含双引号。
## 样例

### 样例输入 #1
```
0 5
4 5
...#O
.#..#
#O#..
.#..X
3 3
#.#
O.O
.X.
3 3
O..
.#X
.O.
5 5
.....
.....
..O..
#..#.
O#.X.
9 9
...######
.#.......
.#######.
.#.#.....
.#O#.####
.#.#.....
.#######.
.#X......
.O.......

```
### 样例输出 #1
```
Black 0
Black 2
Black 2
Tie
Red 75

```
### 样例输入 #2
```
见附件中的 zu/zu2.in
```
### 样例输出 #2
```
见附件中的 zu/zu2.ans
```
## 提示

**【样例 1 解释】**

第一组数据，红方第一步没有可行的移动，所以黑方胜。

第二组数据，无论第一步红方怎么移动，黑方都可以在下一步让黑棋子与红棋子在同一个位置。

第三组数据，无论第一步红方怎么移动，黑方都可以将自己的棋子往上移动一枚来达成胜利。

第四组数据，有一个红棋子不能动。另一个红棋子可以在第三行移动来防止黑棋子进入第一行。黑棋子也可以一直在第五行移动。如果红棋子到达第五行，黑棋子可以选择从另一边逃走。

第五组数据，在最后一行的那个红棋子可以从左边绕一圈抓住黑棋子。注意另一个红棋子可以移动。

**【样例 2 解释】**

这个样例中的每一组数据都满足测试点 $5$ 到 $13$ 中某一个测试点的限制。

**【子任务】**

对于所有的数据，保证：$1 \leq T \leq 10$，$2 \leq n \leq 10$，$1 \leq m \leq 10$，$\text{id}$ 等于测试点编号。

对于每组数据保证：棋盘上的黑棋恰好有一个，红棋恰好有两个，且黑棋不在第一 行。

- 测试点 $1 \sim 4$：保证要么平局，要么红方在开始时无法移动。

- 测试点 $5 \sim 6$：保证 $n \geq 4$ 。保证棋盘上第 $n-1$ 行的每一个格子都是障碍物，且 棋盘上其他行没有障碍物。保证黑棋在前 $n-2$ 行，有一个红棋在前 $n-2$ 行，另一个红棋在第 $n$ 行。

- 测试点 $7 \sim 9$：保证 $m=1$。

- 测试点 $10 \sim 13$：保证要么平局，要么存在策略可以在 $9$ 步之内结束游戏。

- 测试点 $14 \sim 20$：无特殊限制。


---

---
title: "似曾相识燕归来"
layout: "post"
diff: 省选/NOI-
pid: P9347
tag: ['洛谷原创', 'Special Judge', 'O2优化', '排序', '构造', '洛谷月赛', '分类讨论']
---
# 似曾相识燕归来
## 题目背景

春雨将过，忽而燕鸣轻唤，唤起春波荡漾。春波荡漾，漾起去年的回忆。回忆生香，香满檐下。檐下燕巢残旧，不禁落泪，抬头望归来之燕，心中一动，却是旧时相识……
## 题目描述

$n$ 只燕在夕阳中飞过。按从前到后的顺序，第 $i$ 只燕的大小为 $p_i$，且 $p$ 是一个长度为 $n$ 的排列。

现在可以进行**至多 $L$ 次**如下操作：

- 选定三个整数 $i,j,k$ 满足 $1\le i<j<k\le n$，如果 $p_i>p_k$，交换第 $i,j$ 只燕；否则交换第 $j,k$ 只燕。

为了使队形整齐，我们希望燕是从前到后升序排列的，即 $\forall 1\le i\le n$ 都有 $p_i=i$。

问是否可以达成目标。若可以，请构造一组符合要求的操作。
## 输入格式

**本题有多组测试数据。**

第一行一个整数 $T$，表示测试数据组数。

对于每组测试数据：

- 第一行两个整数 $n,L$。
- 第二行 $n$ 个整数 $p_1,p_2,\ldots,p_n$。
## 输出格式

对于每组测试数据：

- 若无法用至多 $L$ 次操作使得 $p$ 升序排列，仅输出一行 `-1`；
- 否则第一行输出一个整数表示操作次数 $x$，后 $x$ 行每行输出三个整数 $i,j,k$ 表示进行的操作。你需要保证 $0\le x\le L$，$1\le i<j<k\le n$。
## 样例

### 样例输入 #1
```
1
4 4
4 2 1 3
```
### 样例输出 #1
```
2
1 3 4
2 3 4
```
## 提示

**【提示】**

一个长度为 $n$ 的排列是一个满足 $1$ 到 $n$ 中的所有正整数恰好出现 $1$ 次的数组。例如，$[3,1,2]$ 是一个长度为 $3$ 的排列，而 $[5,5,1,2,3]$ 不是一个排列。

**【样例 1 解释】**

- 第一次操作中，$i=1,j=3,k=4$，由于 $p_1>p_4$，我们交换 $p_1,p_3$，此时 $p=[1,2,4,3]$；
- 第二次操作中，$i=2,j=3,k=4$，由于 $p_2<p_4$，我们交换 $p_3,p_4$，此时 $p=[1,2,3,4]$。

**【数据规模与约定】**

**本题采用捆绑测试。**

-  Subtask 1（5 points）：$n\le 3$。
-  Subtask 2（5 points）：$n\le 4$。
-  Subtask 3（5 points）：$T\le 50$，$n\le 8$。
-  Subtask 4（10 points）：$n\le 8$。
-  Subtask 5（25 points）：$L=n+2$。
-  Subtask 6（25 points）：$L=n+1$。
-  Subtask 7（25 points）：无特殊限制。

对于 $100\%$ 的数据，$1\le T\le 10^5$，$1\le n,\sum n\le 2\times 10^6$，$n\le L\le n+2$，$p$ 为一个 $1\sim n$ 的排列。


---

