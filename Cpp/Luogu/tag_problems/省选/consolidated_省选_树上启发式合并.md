---
title: "[Opoi 2024] 二十六点"
layout: "post"
diff: 省选/NOI-
pid: P10536
tag: ['线段树', '树上启发式合并', 'O2优化', '树链剖分', '单调栈']
---
# [Opoi 2024] 二十六点
## 题目背景

二十六点：

> 。 。 。 。 。 。 。 。 。 。 。 。 。
>
> 。 。 。 。 。 。 。 。 。 。 。 。 。

凑二十六点真好玩，而为了凑四道题，就有了这道权值只有 $26$ 种的凑数题。
## 题目描述


给你一棵有 $n$ 个结点的以 $1$ 为根的树 $T$，第 $i$ 个结点有一个颜色 $c_i$，${\tt a} \le c_i \le {\tt z}$，和一个值 $P_i$。

对于每一个点 $x$，**从它到它子树中每一个点**（注意顺序是从它本身到子树中的点）都有一条路径，一共有子树的大小条路径。

现在忽略掉这些路径中的第 $2$ 到第 $P_x$ 个的点，特别地，若 $P_x = 1$ 则不忽略任何点。将忽略后的路径当作一个序列，序列中每个点的权值为路径上点的 $c_i$，求**每一个点的所有序列最长不下降子序列长度的最大值**。

注: 若有路径 $j$ 上的节点数 $len_j < P_x$，则相当于忽略这条路径上除第一个点外的所有点。

## 输入格式

第一行一个整数 $n$。

第二行 $n$ 个整数 $P_i$。

第三行 $n$ 个小写字母 $c_i$，**字符与字符间没有空格**。

接下来 $n - 1$ 行，描述树 $T$，每行两个整数 $u,v$，表示 $u,v$ 存在一条边。

行末可能有多余空格（慎用 `getchar()`）。
## 输出格式

输出 $n$ 行，表示每一个点的答案，按照编号从小到大输出。
## 样例

### 样例输入 #1
```
7
2 1 1 9 8 5 1
zzabcad
1 2
2 3
3 4
3 5
5 6
5 7
```
### 样例输出 #1
```
3
3
3
1
1
1
1

```
### 样例输入 #2
```
12
1 2 2 4 1 3 4 3 1 4 3 1 
baabbbbbbbaa
4 6
5 7
1 2
12 10
8 2
10 11
5 9
10 3
2 3
4 3
4 5

```
### 样例输出 #2
```
5
4
3
1
2
1
1
1
1
1
1
1
```
## 提示



### 样例一解释：

样例中树的形态：

![](https://cdn.luogu.com.cn/upload/image_hosting/6vbio7vo.png?x-oss-process=image/resize,h_450,m_lfit)

对于 $1$ 号节点：
$P_1=2$。

|  序列| 权值 | 最长不下降子序列长度 | 最长不下降子序列 |
| :----------: | :----------: | :----------: | :----------: |
| 1 | z | 1 | z |
| 1 3 | za | 1 |  z |
| 1 3 4 |  zab | 2  | ab |
| 1 3 5  |  zac | 2 |  ac   |
| 1 3 5 6 |  zaca | 2  | ac |
| 1 3 5 7 | zacd| 3 | acd  |

长度最长的最长不降子序列：acd。

$2$ 号节点和 $1$ 号节点同理。

对于 $3$ 号节点：
$P_3=1$。

|  序列| 权值 | 最长不下降子序列长度 | 最长不下降子序列 |
| :----------: | :----------: | :----------: | :----------: |
| 3 | a | 1 | a |
| 3 4 | ab | 1 |  ab |
| 3 5  |  ac | 2  | ac |
| 3 5 6  |  aca | 2 |  ac   |
|3 5 7   |  acd | 3  |acd |

长度最长的最长不降子序列：acd。

对于 $4,5,6,7$，它的所有序列中都只有它自己一个点，所以输出 $1$。
### 数据范围

本题采用 Subtask 计分。

| Subtask | Limit | Pts |
| :-----------: | :-----------: | :-----------: |
| 0 | $n \le 100$ | 5 |
| 1 | $n \le 2000$ | 15 |
| 2 | $\forall 1 \le i \le n \quad P_i=1$ | 30 |
| 3 | Empty | 50 |

对于 $100\%$ 的数据：

$1 \le n \le 10^5$。

$\forall 1 \le i \le n$， $c_i$ 为小写字母，$1 \le P_i \le n$。

给出的树连通且合法。


---

---
title: "[JOI Open 2024] 考试 2"
layout: "post"
diff: 省选/NOI-
pid: P10626
tag: ['动态规划 DP', '线段树', '树上启发式合并', '2024', '树链剖分', '动态树 LCT', 'JOI（日本）']
---
# [JOI Open 2024] 考试 2
## 题目描述

JOI 君在 IOI 高中上学，期末考试即将来临。考试的内容是计算 **IOI 函数**。IOI 函数是将 $[1,10^9]$ 之间的整数映射到布尔值（即 $\texttt{True}/\texttt{False}$）的函数。IOI 函数可以从以下六条 IOI 高中规定的规则中构造：

1. 设 $a$ 为 $[1,10^9]$ 之间的整数，则 $\texttt{[a]}$ 是一个 IOI 函数。它将不小于 $a$ 的整数映射成 $\texttt{True}$，将小于 $a$ 的整数映射成 $\texttt{False}$。

2. 记 $\texttt{f}$ 为 IOI 函数，则 $\texttt{(f)}$ 是一个 IOI 函数，它的映射规则与 $\texttt{f}$ 的映射规则相同。

3. 记 $\texttt{f}$ 为 IOI 函数，则 $\texttt{!f}$ 是一个 IOI 函数。设 $x$ 为整数，若 $\texttt{f}$ 将 $x$ 映射为 $\texttt{True}$，则 $\texttt{!f}$ 将 $x$ 映射为 $\texttt{False}$；否则 $\texttt{!f}$ 将 $x$ 映射为 $\texttt{True}$。

4. 记 $\texttt{f},\texttt{g}$ 为 IOI 函数，则 $\texttt{f\&g}$ 也是一个 IOI 函数。设 $x$ 为整数，则 $\texttt{f\&g}$ 将 $x$ 映射为 $\texttt{True}$，当且仅当 $\texttt{f},\texttt{g}$ 都将 $x$ 映射为 $\texttt{True}$。

5. 记 $\texttt{f},\texttt{g}$ 为 IOI 函数，则 $\texttt{f\^ g}$ 也是一个 IOI 函数。设 $x$ 为整数，则 $\texttt{f\^ g}$ 将 $x$ 映射为 $\texttt{True}$，当且仅当 $\texttt{f},\texttt{g}$ 中恰好有一个将 $x$ 映射为 $\texttt{True}$。

6. 记 $\texttt{f},\texttt{g}$ 为 IOI 函数，则 $\texttt{f|g}$ 也是一个 IOI 函数。设 $x$ 为整数，则 $\texttt{f|g}$ 将 $x$ 映射为 $\texttt{True}$，当且仅当 $\texttt{f},\texttt{g}$ 中至少有一个将 $x$ 映射为 $\texttt{True}$。

如果某个 IOI 函数用多条规则构造出，数字更大的规则将决定函数值。例如，对于 $\texttt{[1]\&[2]|[3]}$ 应当应用规则 6，其中 $\texttt{f} = \texttt{[1]\&[2]},\texttt{g} = \texttt{[3]}$（而非应用规则 4，其中 $\texttt{f} = \texttt{[1]},\texttt{g} = \texttt{[2]|[3]}$）。额外地，对于规则 4，5，6，应当最大化 $\texttt{f}$ 的长度。例如，对于 $\texttt{[4]ˆ[5]ˆ[6]}$，应当在 $\texttt{f} = \texttt{[4]ˆ[5]},\texttt{g} = \texttt{[6]}$ 上应用规则 5（而非 $\texttt{f} = \texttt{[4]},\texttt{g} = \texttt{[5]ˆ[6]}$）。

为备战期末考试，JOI 君准备好了一个长度为 $N$ 的 IOI 函数 $S$。他打算用 $Q$ 个整数 $X_1,X_2,\cdots,X_Q$ 来练习他的计算技能。于是他找来了你——能够熟练处理 IOI 函数的人，来解决这个问题。

你需要写一个程序。给定 $N,Q,S$ 以及 $X_1,X_2,\cdots,X_Q$，对于 $i=1,2=\cdots,Q$，回答 IOI 函数 $S$ 会将 $X_i$ 映射成 $\texttt{True}$ 还是 $\texttt{False}$。

## 输入格式

输入格式如下所示：

> $N$ $Q$\
> $S$\
> $X_1$\
> $X_2$\
> $\vdots$\
> $X_Q$
## 输出格式

输出 $Q$ 行，第 $i$ 行为 $\texttt{True}$ 或者 $\texttt{False}$，即 $X_i$ 被 $S$ 映射成的值。
## 样例

### 样例输入 #1
```
15 5
(![2]|[3])&![4]
1
2
3
4
5
```
### 样例输出 #1
```
True
False
True
False
False
```
### 样例输入 #2
```
20 4
(!![23])^((([116])))
54
1
200
89
```
### 样例输出 #2
```
True
False
False
True
```
### 样例输入 #3
```
32 4
[2]|[5]&[1]|(([1000000000])|[7])
4
10
6
1
```
### 样例输出 #3
```
True
True
True
False
```
## 提示


### 样例解释

样例 $1$ 解释如下：

| $X_i$ | $\texttt{![2]}$ | $\texttt{[3]}$ | $\texttt{![2]\|[3]}$ | $\texttt{![4]}$ | $\texttt{(![2]\|[3])\&![4]}$ |
| :--: | :--: | :--: | :--: | :--: | :--: |
| $1$ | $\texttt{True}$ | $\texttt{False}$ | $\texttt{True}$ | $\texttt{True}$ | $\texttt{True}$ |
| $2$ | $\texttt{False}$ | $\texttt{False}$ | $\texttt{False}$ | $\texttt{True}$ | $\texttt{False}$ |
| $3$ |  $\texttt{False}$ | $\texttt{True}$ | $\texttt{True}$ | $\texttt{True}$ | $\texttt{True}$ |
| $4$ | $\texttt{False}$ | $\texttt{True}$ | $\texttt{True}$ | $\texttt{False}$ | $\texttt{False}$ |
| $5$ |  $\texttt{False}$ | $\texttt{True}$ | $\texttt{True}$ | $\texttt{False}$ | $\texttt{False}$ |

样例 $1$ 满足子任务 $3,6,7$ 的条件。

样例 $2$ 满足子任务 $1,3,5\sim 7$ 的条件。

样例 $3$ 满足子任务 $3,4,6,7$ 的条件。	

### 数据范围

- $1 \le N \le 1\,000\,000$；
- $1 \le Q \le 200\,000$；
- $S$ 为长度为 $N$ 的 IOI 函数；
- $1 \le X_i \le 10^9$（$1 \le i \le Q$）；
- $N, Q, X_i$（$1 \le i \le Q$）均为整数。

### 子任务

1. （$5$ points）$S$ 中不含 $\texttt{\&}$ 和 $\texttt{|}$；
2. （$20$ points）$Q = 1$；
3. （$10$ points）$N \le 10\,000$；
4. （$6$ points）$S$ 中不含 $\texttt{!}$ 和 $\texttt{ˆ}$；
5. （$12$ points）当应用规则 4 或 6 来构造 $S$ 时，$\texttt{f}$ 和 $\texttt{g}$ 中至少有一个是用规则 1 得到的；
6. （$20$ points）$N \le 400\, 000$；
7. （$27$ points）无额外约束。

*赛时公告：如果你复制题面中的 LaTeX，可能会得到 `ˆ`，但实际上是 `^`。请特别注意。

由 Starrykiller 根据英文题面翻译。


---

---
title: "【MX-X1-T4】「KDOI-05」简单的字符串问题"
layout: "post"
diff: 省选/NOI-
pid: P10716
tag: ['字符串', '倍增', '树上启发式合并', 'O2优化', 'KMP 算法', '梦熊比赛']
---
# 【MX-X1-T4】「KDOI-05」简单的字符串问题
## 题目背景

原题链接：<https://oier.team/problems/X1D>。
## 题目描述

你有一个字符串 $S$。$q$ 个询问，每次给出 $(i,k)$，求有多少个非空字符串 $A$，使得存在可空字符串 $B_1,B_2,\dots,B_{k-1}$ 满足：

$$S[1,i]=AB_1AB_2A\dots AB_{k-1}A$$

其中 $S[1,i]$ 表示 $S$ 的长度为 $i$ 的前缀。
## 输入格式

第一行一个正整数 $n$ 表示 $S$ 的长度。

接下来一个长度为 $n$ 且仅包含小写字母的字符串表示 $S$。

接下来一行一个正整数表示 $q$。

接下来 $q$ 行，每行两个正整数表示一个询问的 $i,k$。
## 输出格式

输出 $q$ 行，每行一个非负整数表示答案。
## 样例

### 样例输入 #1
```
10
aabaacaaaa
5
5 3
5 2
6 1
10 4
10 5
```
### 样例输出 #1
```
1
2
1
2
1
```
### 样例输入 #2
```
10
bababababa
10
6 1
6 2
6 3
6 4
6 5
10 2
10 3
9 4
5 5
4 2
```
### 样例输出 #2
```
1
1
1
0
0
2
1
1
0
1

```
## 提示

**【样例解释 \#1】**

对于第一次询问 $(5,3)$，可以取 $A=\texttt{a}$，$B_1=\varepsilon$，$B_2=\texttt{ba}$，其中 $\varepsilon$ 表示空串。可以证明有且仅有一个合法的 $A$。

**【数据范围】**

**本题采用捆绑测试。**

| 子任务编号 | 分值 | $n,q\leq$ | 特殊性质 |
|:--:|:--:|:--:|:--:|
| $1$ | $5$ | $500$ | 无 |
| $2$ | $10$ | $5000$ | 无 |
| $3$ | $10$ | $2\times10^5$ | $S$ 中字符从 $\tt a,b$ 中随机生成 |
| $4$ | $20$ | $2\times10^5$ | 每个询问的 $k$ 相同 |
| $5$ | $20$ | $5\times10^4$ | 无 |
| $6$ | $35$ | $2\times10^5$ | 无 |

对于 $100\%$ 的数据：$1\leq k\leq i\leq n\leq 2\times 10^5$，$1\leq q\leq 2\times 10^5$，$s$ 仅包含小写字母。


---

---
title: "『SpOI - R1』Lamborghini (Demo)"
layout: "post"
diff: 省选/NOI-
pid: P10795
tag: ['点分治', '树上启发式合并', 'Kruskal 重构树', 'O2优化', '线段树合并']
---
# 『SpOI - R1』Lamborghini (Demo)
## 题目描述

给你一棵无根树，每个点 $i$ 有两个属性 $t_i,v_i$。

定义有向路径 $i\to j$ 的 $f_{i,j}$ 为：

- 若 $i\to j$ 上 $t_x$ 最小的点为 $x$ 且 $v_j\leq v_x\leq v_i$，则 $f_{i,j}=x$。
- 否则，$f_{i,j}=0$。

求 $\sum\limits_{i=1}^n\sum\limits_{j=1}^n f_{i,j}$。
## 输入格式

第一行一个整数 $n$。

第二行 $n$ 个以空格分隔的整数，第 $i$ 项表示点 $i$ 的 $t_i$。

第三行 $n$ 个以空格分隔的整数，第 $i$ 项表示点 $i$ 的 $v_i$。

接下来 $n-1$ 行，每行两个整数 $a,b$，表示一条树边 $a\leftrightarrow b$。
## 输出格式

输出一行一个整数，表示答案。
## 样例

### 样例输入 #1
```
3
1 2 3
1 3 5
1 2
2 3
```
### 样例输出 #1
```
10
```
### 样例输入 #2
```
5
1 3 5 8 10
1 5 3 2 8
2 1
3 1
4 1
5 3
```
### 样例输出 #2
```
22
```
## 提示

#### 样例 #1 解释

- $f(1,1)=1$。
- $f(1,2)=0$。
- $f(1,3)=0$。
- $f(2,1)=1$。
- $f(2,2)=2$。
- $f(2,3)=0$。
- $f(3,1)=1$。
- $f(3,2)=2$。
- $f(3,3)=3$。

故 $\sum\limits_{i=1}^3\sum\limits_{j=1}^3 f(i,j)=10$。

### 数据范围

**本题开启子任务捆绑与子任务依赖。**

对于 $100\%$ 的数据，$t$ 互不相同，$1\leq n\leq 10^5$，$1\leq t_i,v_i\leq 10^9$。

| Subtask | $n\leq$ | $t_i,v_i\leq$ | 特殊性质 | 得分 | 子任务依赖 |
| :-----------: | :-----------: | :-----------: | :-----------: | :-----------: | :-----------: |
| 1 | $300$ | $10^5$ | 无 | $15$ | 无 |
| 2 | $5000$ | $10^5$ | 无 | $15$ | 1 |
| 3 | $10^5$ | $10^9$ | $A$ | $15$ | 无 |
| 4 | $10^5$ | $10^9$ | $B$ | $15$ | 无 |
| 5 | $10^5$ | $10^9$ | 无 | $40$ | 1,2,3,4 |

特殊性质 $A$：**钦定 $1$ 号节点为树的根**，对于任意点对 $(x,y)$ 且 $x\neq y$，若 $x$ 是 $y$ 的祖先，则 $t_x<t_y$。

特殊性质 $B$：$\forall i\in[1,n),a_i=i,b_i=i+1$。


---

---
title: "[COTS 2023] 题 Zadatak"
layout: "post"
diff: 省选/NOI-
pid: P10834
tag: ['树上启发式合并', '2023', 'O2优化', 'COCI（克罗地亚）', '线段树合并']
---
# [COTS 2023] 题 Zadatak
## 题目背景


译自 [Izborne Pripreme 2023 (Croatian IOI/CEOI Team Selection)](https://hsin.hr/pripreme2023/) D2T3。$\texttt{1s,0.5G}$。

祝 NaCly_Fish 生日快乐！（2024.7.28）
## 题目描述

Jura 有 $N$ 个正方形，标号为 $1\sim N$，第 $i$ 个正方形边长为 $a_i$，且 $2\mid a_i$。起初，这些正方形都是黑色的。

Jura 决定花费他生命中的 $(N-1)$ 秒来玩这些正方形。在第 $i$ 秒时，Jura 将第 $x_i$ 和第 $y_i$ 个正方形合并成第 $(N+i)$ 个正方形（合并后，第 $x_i$ 和第 $y_i$ 个正方形不再存在）。

合并正方形时，将两个正方形的中心对齐，边缘平行对齐地摆在平面中。新的正方形的大小为合并的两个正方形中较大那个的大小；它的颜色是原来两个正方形颜色的「异或和」（黑+黑=白，白+白=白，黑+白=黑，白+黑=黑）。合并正方形的**代价**为，两个正方形合并前（但是已经按照刚才的要求摆好），正方形的交中，满足在两个正方形中均为黑色的区域的面积。

你需要输出每次合并操作的代价。

下图为正方形合并的示例：

![](https://cdn.luogu.com.cn/upload/image_hosting/8uquyi9a.png)

## 输入格式

第一行，一个正整数 $N$，表示正方形数量；

第二行，$N$ 个正整数，描述序列 $a$。

接下来 $(N-1)$ 行，每行两个正整数 $x_i,y_i$，描述一次操作。
## 输出格式

输出 $(N-1)$ 行，每行一个整数，表示操作的代价。
## 样例

### 样例输入 #1
```
6 
8 6 2 4 2 6
1 2
3 4
5 7
6 8
9 10
```
### 样例输出 #1
```
36
4
0
12
4
```
### 样例输入 #2
```
7 
4 2 6 6 2 4 2
1 2
3 8
4 9
5 10
6 11
7 12
```
### 样例输出 #2
```
4
12
24
0
16
0 
```
### 样例输入 #3
```
8
4 10 2 10 6 8 4 12
1 2
3 4
5 6
7 8
9 10
11 12
13 14
```
### 样例输出 #3
```
16
4
36
16
84
28
0
```
## 提示


### 样例解释

样例 $1$ 的最后一个操作如图所示：

![](https://cdn.luogu.com.cn/upload/image_hosting/rvjzj56s.png)

#### 数据范围

对于 $100\%$ 的数据，保证：

- $1\le N\le 10^5$；
- $2\le a_i\le 10^6$。
- $2\mid a_i$。
- $1\le x_i,y_i\le N+i-1$
- 操作前正方形存在，且 $x_i\neq y_i$。

| 子任务编号 | 分值 | 约束  |
|:-----:|:------:|:-------:|
| $1$  | $14$  | $N\le 5\, 000$  |
| $2$  | $25$  | $x_1=1,y_1=2$；$\forall 2\le i\le N-1$，$x_i=i+2,y_i=N+i-1$  |
| $3$  | $17$  | $\exists k\in \mathbb{N}$，使得 $2^k=N$；$x_i=2i-1,y_i=2i$ |
| $4$  | $21$  | $n\le 30\, 000$ |
| $5$  | $23$  | 无额外约束 |






---

---
title: "[ONTAK2015] Bajtocja"
layout: "post"
diff: 省选/NOI-
pid: P8026
tag: ['2015', '并查集', '树上启发式合并', '哈希 hashing']
---
# [ONTAK2015] Bajtocja
## 题目描述

给定 $d$ 张无向图，每张图都有 $n$ 个点。一开始，在任何一张图中都没有任何边。接下来有 $m$ 次操作，每次操作会给出 $a, b, k$，意为在第 $k$ 张图中的点 $a$ 和点 $b$ 之间添加一条无向边。你需要在每次操作之后输出有序数对 $(a, b)$ 的个数，使得 $1 \leq a, b \leq n$，且 $a$ 点和 $b$ 点在 $d$ 张图中都连通。
## 输入格式

第一行，三个整数 $d, n, m$；

接下来 $m$ 行，每行三个整数 $a, b, k$。
## 输出格式

$m$ 行，每行一个整数，表示所求的值。
## 样例

### 样例输入 #1
```
3 4 10
1 2 1
2 1 2
1 2 3
3 4 1
1 3 2
2 3 3
2 4 2
3 4 3
3 4 2
1 3 1
```
### 样例输出 #1
```
4
4
6
6
6
6
6
8
8
16
```
## 提示

对于 $100\%$ 的数据，$1 \leq d \leq 200$，$1 \leq n \leq5 \times 10^3$，$1\leq m \leq 10^6$，$1 \leq a, b \leq n$，$1 \leq k \leq d$。


---

---
title: "『GROI-R2』 Beside You"
layout: "post"
diff: 省选/NOI-
pid: P9655
tag: ['并查集', '树上启发式合并', '洛谷原创', 'O2优化', '树形 DP', '最近公共祖先 LCA', '树论', '虚树', '洛谷月赛']
---
# 『GROI-R2』 Beside You
## 题目背景

記憶の森

始まりの謎 いつか

この未知の果てに告げ知らせて

——江口孝宏《Beside You》
## 题目描述

我相信所有读过这一段剧情的人都不想让别人也经历一样的痛苦，但是坦尼尔还是只能消失，对吗？

坦尼尔最后留下了一棵以 $1$ 为根的有根树，在树的每个结点上，都有一个记忆碎片。有的碎片表示着一个世界记忆的开始，而另外的碎片表示着一个世界记忆的终结。

这时，树上飞来了一只蝴蝶~~モリモリあつし~~。蝴蝶在树上飞舞的过程中，经过了一些结点。爱丽丝能确定蝴蝶经过的结点个数至少有 $2$ 个，但是她忘记了具体的点数。

爱丽丝发现，蝴蝶经过的所有点都是互相连通的。当她把目光朝向每一条经过点数大于 $1$ 的从连通块**深度最小的结点**通往**连通块的任意一个叶子结点**（一个点是连通块的叶子结点，当且仅当它在树上没有子结点，或者它在树上的任意子结点均不在该连通块内）的简单路径时，她发现这些路径上的记忆都是完整的。爱丽丝认为一条路径上的记忆是完整的，当且仅当这条路径上既没有出现一个世界的记忆**没开始就结束**（路径中途在没有未结束的记忆的时候，出现了表示记忆终结的碎片）的情况，也没有出现一个世界的记忆**开始之后没有终结**（路径结束之后还有没结束的记忆）的情况。

可惜她已经遗忘了蝴蝶经过了哪些点，所以你需要告诉她蝴蝶**最多**可能经过多少点。

**形式化题面**

给定一棵以 $1$ 为根的 $n$ 个节点的树 $T=(V,E)$，每个节点上的点权 $c_i$ 为一个**左括号或一个右括号**，节点编号为 $1\sim n$。

我们定义点集 $V'\subseteq V$ 合法，当且仅当 $|V'|>1$（**即 $V'$ 的大小大于 $1$**） 且 $\forall u,v \in V'$，从 $u$ 到 $v$ 的简单路径只经过 $V'$ 中的点。

同时我们定义 $E'\subseteq E$ 为能使得 $\forall u,v \in V'$，从 $u$ 到 $v$ 的简单路径，只经过 $E'$ 中的边的大小最小的边集。

定义一个合法点集 $V'$ 的根为 $V'$ 中深度最小的结点。

定义 $u$ 为合法点集 $V'$ 的叶子节点，当且仅当 $u$ 不是 $V'$ 的根，且满足 $v \in V', (u,v) \in E'$ 的 $v$ 的数量为 $1$。

求一个合法点集 $S$，**满足其根节点到其任意一个叶子的路径上，每个点的点权顺次相接为一个合法的括号序列**，并**最大化** $|S|$。

我们通过如下规则定义一个合法的括号序列：

- 空串（即长度为 $0$ 的串）是一个合法的括号序列。

- 若串 $\text{A,B}$ 都是合法的括号序列，则字符串 $\text{AB}$ （即将字符串 $\text{A}$ 与 $\text{B}$ 按顺序拼接起来）也是合法的括号序列。

- 若串 $\text{A}$ 是合法的括号序列，则字符串 $\text{(A)}$ 是一个合法的括号序列。

你需要输出符合要求的最大 $|S|$。
## 输入格式

第一行输入一个正整数 $n$ 表示树上结点个数。

第二行输入一个长度为 $n$ 的字符串 $c$。$c_i$ 为 ``(`` 表示这个结点上有一个标志着记忆开始的碎片，$c_i$ 为 ``)`` 表示这个结点上有一个标志着记忆终结的碎片。

接下来 $n-1$ 行，每行输入两个正整数 $u,v$，表示结点 $u,v$ 之间有一条边。
## 输出格式

输出一行一个整数，表示答案。
## 样例

### 样例输入 #1
```
3
())
1 2
1 3
```
### 样例输出 #1
```
3
```
### 样例输入 #2
```
8
()))())(
1 2
1 3
3 4
3 5
3 6
5 7
2 8
```
### 样例输出 #2
```
5
```
## 提示

**样例解释**

![](https://s1.ax1x.com/2023/08/07/pPEj56K.png)

蝴蝶经过的最大合法点集 $S$ 为 $\{1,2,3\}$。

![](https://s1.ax1x.com/2023/08/07/pPEv90g.png)

蝴蝶经过的最大合法点集 $S$ 为 $\{1,2,3,5,7\}$。

**数据范围**

**本题采用捆绑测试**。

| $\text{Subtask}$ | $n\le$ | 特殊性质 | 分值 |
| :-----------: | :-----------: | :-----------: | :-----------: |
| $1$ | $20$ |  | $5$ |
| $2$ | $3000$ |  | $20$ |
| $3$ | $5\times10^5$ | $\text{A}$ | $15$  |
| $4$ | $5\times10^5$ | $\text{B}$ |  $10$ |
| $5$ | $2\times10^5$ |  | $15$ |
| $6$ | $5\times10^5$ |  | $35$ |

特殊性质 $\text{A}$：保证树退化成一条链（不保证 $1$ 号节点为其一个端点）。

特殊性质 $\text{B}$：保证原树上任意结点到叶子的路径上右括号数量不少于左括号数量。

对于 $100\%$ 的数据满足 $1\le n\le 5\times 10^5$，$1\le u,v \le n$，$c_i$ 为 ``(`` 或 ``)``。


---

---
title: "[ICPC 2018 Qingdao R] Kawa Exam"
layout: "post"
diff: 省选/NOI-
pid: P9886
tag: ['2018', '树上启发式合并', 'O2优化', 'ICPC', '青岛']
---
# [ICPC 2018 Qingdao R] Kawa Exam
## 题目描述

BaoBao is taking an online exam of the Kawa programming language, which consists of $n$ multiple choice questions. The exam is not easy, as for each question, BaoBao needs to select the one and only one correct answer from $10^5$ available choices! But don't worry, as an active committer of the famous \textit{open-kdk}, BaoBao obviously knows all the correct answers.

Although BaoBao is an expert in Kawa, the developers of the exam system are definitely not experts in software engineering. There are $m$ bugs in the exam system, and the $i$-th bug can be described as $(u_i, v_i)$, which means that BaoBao must select the same choice for question $u_i$ and $v_i$ (even if the choice he selects is incorrect!).

Time is limited, and the exam must go on. The developers only have time to fix one bug. Now the developers are wondering, for all $1 \le i \le m$, what's the maximum possible number of questions BaoBao can correctly answer if they fix the $i$-th bug. Please write a program to solve this problem so that the developers can select a proper bug to fix.
## 输入格式

There are multiple test cases. The first line of the input contains an integer $T$, indicating the number of test cases. For each test case:

The first line contains two integers $n$ and $m$ ($1 \le n \le 10^5$, $1 \le m \le 10^5$), indicating the number of questions and the number of bugs.

The second line contains $n$ integers $a_1, a_2, \dots, a_n$ ($1 \le a_i \le 10^5$), where $a_i$ indicates the correct answer for question $i$.

For the following $m$ lines, the $i$-th line has two integers $u_i$ and $v_i$ ($1 \le u_i, v_i \le n$), indicating the $i$-th bug.

It's guaranteed that neither the sum of $n$ nor the sum of $m$ over all test cases will exceed $10^6$.
## 输出格式

For each test case output one line containing $m$ integers $c_1, c_2, \dots, c_m$ separated by a space, where $c_i$ indicates the maximum possible number of questions BaoBao can correctly answer if the $i$-th bug is fixed.

Please, DO NOT output extra spaces at the end of each line, or your answer may be considered incorrect!
## 样例

### 样例输入 #1
```
3
7 5
1 2 1 2 1 2 1
1 2
1 3
2 4
5 6
5 7
3 3
1 2 3
1 2
1 3
2 3
2 3
12345 54321
1 2
1 2
1 1
```
### 样例输出 #1
```
6 5 5 5 4
1 1 1
1 1 1
```
## 提示

The following table explains the first sample test case.

- The ``possible choices`` column indicates a possible set of choices to each question BaoBao can select, leading to a maximum possible number of correctly answered questions;
- The ``correct`` column indicates the number of correctly answered questions using the set of choices provided in the ``possible choices`` column.

$$\begin{array}{|c|c|c|c|}
\hline
\textbf{Bug No.} & \textbf{Possible Choices} & \textbf{Correct} \\
\hline
1 & (1, 2, 1, 2, 1, 1, 1) & 6 \\
\hline
2 & (2, 2, 1, 2, 1, 1, 1) & 5 \\
\hline
3 & (1, 1, 1, 2, 1, 1, 1) & 5 \\
\hline
4 & (1, 1, 1, 1, 1, 2, 1) & 5 \\
\hline
5 & (1, 1, 1, 1, 1, 1, 1) & 4 \\
\hline
\end{array}$$

For the second sample test case, no matter which bug is fixed, BaoBao has to select the same choice for all the three questions. As the correct answer for each question is different, BaoBao can only correctly answer 1 question.

For the third sample test case, note that even if the developers fix the first bug, the second bug is still taking effect and BaoBao still has to select the same choice for the two problems. It's the same if the second bug is fixed.
## 题目翻译

BaoBao 正在参加 Kawa 编程语言的在线考试，该考试由 $n$ 个多项选择题组成。考试并不容易，对于每一道题，BaoBao 都需要从 $10^5$ 个可用选项中选择唯一一个正确答案！但别担心，作为著名的 $\text{open-kdk}$ 的积极参与者，BaoBao 显然知道所有正确的答案。

虽然 BaoBao 是 Kawa 方面的专家，但考试系统的开发人员绝对不是软件工程方面的专家。考试系统中有 $m$ 个错误，第 $i$ 个错误可以描述为 $(u_i,v_i)$，这意味着 BaoBao 必须为第 $u_i$ 和 $v_i$ 个问题选择相同的选项（即使他选择的选项不正确！）。

但是考试必须继续，这就意味着开发人员只有时间修复一个错误。现在，开发人员想知道，对于所有的 $1\le i\le m$，如果他们修复 $i$，BaoBao 可以正确回答的最大问题数量是多少。

## 输入格式

有多个测试用例。输入的第一行包含一个整数 $T$，表示测试用例的数量。对于每个测试用例：

第一行包含两个整数 $n$ 和 $m$（$1\le n\le 10^5$，$1\le m\le 10^5$），表示问题数量和错误数量。

第二行包含 $n$ 个整数 $a_1,a_2,\dots,a_n$（$1\le a_i\le 10^5$），其中 $a_i$ 表示问题 $i$ 的正确答案。

对于以下 $m$ 行，第 $i$ 行有两个整数 $u_i$ 和 $v_i$（$1\le u_i,v_i\le n$），表示第 $i$ 个错误。

保证所有测试用例的 $n$ 和 $m$ 的总和都不会超过 $10^6$。

## 输出格式

对于每个测试用例的输出，一行包含由空格分隔的 $m$ 个整数 $c_1,c_2,\dots,c_m$，其中 $c_i$ 表示如果修复了第 $i$ 个错误，BaoBao 可以正确回答的最大问题数。

请不要在每行末尾输出多余的空格，否则您的答案可能会被认为是错误的！

## 提示

下表解释了第一个示例测试用例。

- “可能的选择”列表示 BaoBao 可以选择的每个问题的一组可能的选择，从而导致正确回答的问题的最大可能数量；

- “正确”列表示使用“可能的选择”列中提供的一组选择正确回答的问题的数量。

$$\begin{array}{|c|c|c|c|}
\hline
\textbf{Bug 编号} & \textbf{可能的选择} & \textbf{正确} \\
\hline
1 & (1, 2, 1, 2, 1, 1, 1) & 6 \\
\hline
2 & (2, 2, 1, 2, 1, 1, 1) & 5 \\
\hline
3 & (1, 1, 1, 2, 1, 1, 1) & 5 \\
\hline
4 & (1, 1, 1, 1, 1, 2, 1) & 5 \\
\hline
5 & (1, 1, 1, 1, 1, 1, 1) & 4 \\
\hline
\end{array}$$

对于第二个样本测试用例，无论哪个 bug 被修复，BaoBao 都必须为所有三个问题选择相同的选项。由于每个问题的正确答案不同，BaoBao 只能正确回答一个问题。

对于第三个示例测试用例，请注意，即使开发人员修复了第一个错误，第二个错误仍然有效，BaoBao 仍然必须为这两个问题选择相同的选项。如果第二个错误被修复，情况也是一样的。


---

