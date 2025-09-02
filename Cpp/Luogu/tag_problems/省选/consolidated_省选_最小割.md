---
title: "「Daily OI Round 3」City Planning"
layout: "post"
diff: 省选/NOI-
pid: P10129
tag: ['网络流', '洛谷原创', 'O2优化', '最小割', '线性规划']
---
# 「Daily OI Round 3」City Planning
## 题目背景

只要不失去你的崇高，整个世界都会为你敞开。
## 题目描述

Provence-Alpes-Côte d'Azur 的管理者们遇上大麻烦了！他们邀请你来解决城市规划的问题。

这群管理者一共有 $t$ 人，并且这个地区一共有 $n$ 个城镇，第 $i$ 个城镇内部又有 $k_i$ 个村庄，通过 $p_i$ 条道路连接，第 $j$ 条道路双向连接第 $i$ 个城镇中的第 $u_{i,j}$ 和 $v_{i,j}$ 两个村庄，管理道路的人是第 $w_{i,j}$ 个，客流量是 $z_{i,j}$。

为了管理组内部的团结，保证每个人在同一个城镇最多管理 $1$ 条道路。

现在这些城镇中的村庄和村庄之间的道路都遭到了损坏，管理者们急于恢复这些城镇内的交通。这些城镇互相之间有 $m$ 条高铁，每条高铁连接了 $u,v$ 两个城镇，并且当初为了设计的优美，这 $n$ 个城镇和 $m$ 条高铁构成了一个**二分图**。

对于每个城镇 $i$，你都需要帮助管理组选择一个参数 $c_i(1 \le c_i \le k_i)$，修复一些村庄，编号在 $1 \sim c_i$ 之间的村庄都会被修复，如果道路的两端的村庄都修复了，那么这条道路就会自动修复。因此第 $i$ 个城镇中会产生 $b_{i,c_i}$ 的花费。

对于管理者 $i$ 来说，如果存在两条他在不同城镇管理的道路都没有被修复，并且这两条道路所属的城镇有高铁**直接连接**，你需要支付这两条道路的人流量的乘积来弥补损失，这样管理者 $i$ 才会高兴。（对于**任意**两条满足上述条件的道路你都需要弥补损失，而不是对于每个管理者只需要弥补一对道路的损失）

为了让管理组的成员都高兴并且给出的方案符合题目的要求（即 $1 \le c_i \le k_i$），你需要提前计算好自己至少需要支付多少钱以应对这一群管理者们的刁难。


## 输入格式

第一行三个整数 $n,m,t$ 表示城镇的数量，城镇间的高铁的数量和管理组人员的数量。

接下来 $m$ 行每行两个整数 $x,y$ 表示这条高铁连接的两个城镇的编号。

接下来 $n$ 组输入，对于第 $i$ 组输入，格式如下：

第一行两个整数 $k_i,p_i$ 表示第 $i$ 个城镇有 $k_i$ 个村庄，$p_i$ 条道路。

第二行 $k_i$ 个整数，第 $j$ 个整数表示当 $c=j$ 时的花费 $b_{i,j}$。

接下来 $p_i$ 行，每行四个整数 $u_{i,j},v_{i,j},w_{i,j},z_{i,j}$，表示有一条边连接 $i$ 号城镇的第 $u_{i,j}$ 个村庄和第 $v_{i,j}$ 个村庄，并且管理道路的人是第 $w_{i,j}$ 个，客流量为 $z_{i,j}$。
## 输出格式

一行一个整数表示让所有管理者都高兴的最小花费是多少。
## 样例

### 样例输入 #1
```
2 2 3
2 1
2 1
1 3
3
1 1 2 3
1 1 1 1
1 1 3 3
2 0
7 6
```
### 样例输出 #1
```
9
```
### 样例输入 #2
```
3 1 3
1 2
3 2
1 2 3
1 2 1 3
2 3 2 2
2 2
1 100
1 1 1 3
1 2 2 1
5 1
5 0 5 5 5
4 5 1 3
```
### 样例输出 #2
```
4
```
### 样例输入 #3
```
5 6 5
4 3
3 5
1 2
2 1
3 4
3 5
2 0
37 44
4 2
33 2 43 49
3 1 3 6
3 4 4 6
6 4
4 23 0 9 35 22
3 4 2 7
3 4 5 3
2 1 3 2
4 4 4 10
3 2
14 41 35
2 2 4 1
3 3 2 5
3 5
27 39 9
3 3 2 1
3 2 3 3
2 1 1 5
2 1 5 3
1 2 4 8
```
### 样例输出 #3
```
71
```
## 提示

#### 【样例解释 #1】

我们可以选择 $c_1=1,c_2=2$，那么花费就是 $b_{1,c_1}+b_{2,c_2}=3+6=9$，而没有一个管理员你需要讨好。

#### 【样例解释 #2】

我们可以选择 $c_1=1,c_2=1,c_3=2$，那么花费就是 $b_{1,c_1}+b_{2,c_2}+b_{3,c_3}=1+1=2$，但是管理员 $2$ 在城镇 $1$ 中管理的道路 $2 \to 3$ 不可能被修复，在城镇 $2$ 中管理的道路 $1 \to 2$ 不可能被修复，你就需要花费 $2 \times 1 = 2$ 的代价讨好管理员 $2$，总的代价就是 $4$。

你并不需要讨好管理员 $1$，哪怕他在城镇 $1$ 和 $3$ 中分别有一条道路不可能被修复，因为城镇 $1$ 和 $3$ 没有高铁相连，所以你不需要为此支付额外的资金。

#### 【数据范围】

对于全部数据保证：$1 \le n \le 50$，$1 \le k_i \le 100$，$0 \le p_i \le t$，$0 \le m \le 500$，$1 \le t \le 50$，$1 \le x,y \le n$，$x \ne y$，$0 \le b_{i,j} \le 10^9$，$1 \le u_{i,j},v_{i,j} \le k_i$，$1 \le w_{i,j} \le t$，$1 \le z_{i,j} \le 10^4$。

$n$ 个城镇和 $m$ 条高铁构成的图是一个二分图，每个管理员在同一个村庄管理的道路数量不超过 $1$。

**可能有连接同一对城镇的不同的高铁，不会出现自己连向自己的高铁。但城镇中的村庄可能会有自己连向自己的道路，也可能出现连接同一对村庄的不同的道路。**


---

---
title: "[PA 2019 Final] 摆棋 / Pionki"
layout: "post"
diff: 省选/NOI-
pid: P11816
tag: ['动态规划 DP', '2019', '图论建模', 'PA（波兰）', '最大流最小割定理']
---
# [PA 2019 Final] 摆棋 / Pionki
## 题目背景

译自 PA 2019 Final。


本题数据为自造。

std：zimpha，validator：Starrykiller，generator：Wuyanru & Starrykiller。
## 题目描述

给定一个 $A\times B\times C$ 的立体棋盘。每个格子可以用三元组 $(i,j,k)$ 描述，其中 $1\le i\le A$，$1\le j\le B$，$1\le k\le C$。

起初，$(i,j,k)$ 上有 $a_{i,j,k}$ 个棋子。

每次操作，可以选择一个格子 $(i,j,k)$，满足 $(i,j,k)$ 上至少有一个棋子，然后将这枚棋子移动到 $(i+1,j,k)$ 或 $(i,j+1,k)$ 或 $(i,j,k+1)$ 中的一个。棋子不能移出棋盘边界。

目标是让 $(i,j,k)$ 上有 $b_{i,j,k}$ 个棋子。判断是否能够达成目标。



## 输入格式

**本题单个测试点内有多组测试数据。**

第一行，一个正整数 $T$，表示测试数据组数。接下来依次描述 $T$ 组数据。

每组数据第一行，三个正整数 $A,B,C$。

接下来 $A$ 块，每块包含 $B$ 行，每行 $C$ 个非负整数。第 $i$ 块第 $j$ 行第 $k$ 个数即为 $a_{i,j,k}$。


接下来 $A$ 块，每块包含 $B$ 行，每行 $C$ 个非负整数。第 $i$ 块第 $j$ 行第 $k$ 个数即为 $b_{i,j,k}$。

对于这 $2A$ 块，每两个块之间由一个空行隔开（所以每组测试数据有 $(2A-1)$ 行空行）。
## 输出格式

对于每组测试数据输出一行：

如果可以达成目标，输出 $\texttt{TAK}$；否则输出 $\texttt{NIE}$。
## 样例

### 样例输入 #1
```
2
2 3 4
2 0 0 1
0 0 1 0
1 0 0 0

0 1 0 0
1 0 0 0
0 0 0 0

0 0 1 0
0 1 0 0
0 0 0 0

1 0 0 0
0 0 0 0
0 0 0 4
2 2 2
2 2
2 1

2 1
1 1

1 1
1 2

1 2
2 2
```
### 样例输出 #1
```
NIE
TAK
```
## 提示

- $1\le T\le 10^4$；
- $1\le A,\sum A\le 10^4$；
- $1\le B,C\le 6$；
- $0\le a_{i,j,k},b_{i,j,k}\le 10^{12}$；
- $\sum a_{i,j,k}=\sum b_{i,j,k}$。




---

---
title: "[GCJ 2018 Finals] Jurisdiction Restrictions"
layout: "post"
diff: 省选/NOI-
pid: P13153
tag: ['2018', '二分', '网络流', '最大流最小割定理', 'Google Code Jam']
---
# [GCJ 2018 Finals] Jurisdiction Restrictions
## 题目描述

The city of Gridtopia is a matrix of square cells ("blocks") with $R$ rows and $C$ columns; rows are numbered (starting from 1) from top to bottom, and columns are numbered (starting from 1) from left to right. The city is served by $S$ different police stations; the i-th station is in the block located in the $R_i$th row and the $C_i$th column, and no block contains more than one station.

Each station is only able to patrol blocks that are no more than $D_i$ blocks away from that station, either horizontally or vertically. That is, the i-th station can only patrol the block in row $R'$ and column $C'$ if $\max(|R' - R_i|, |C' - C_i|) \leq D_i$. Put another way, the i-th station can patrol only blocks within the square of side length $2D_i + 1$ centered on that station.

As the new police commissioner, you need to assign some blocks within the city to exactly one station that is able to patrol it. Blocks that contain stations and blocks that no station is able to patrol should not be assigned. All other blocks have to be assigned. Moreover, you must distribute this assignment load as evenly as possible among stations. Let $A_i$ denote the number of blocks assigned to the i-th station; then your goal is to minimize the difference between the maximum of all the $A_i$ values and the minimum of all of the $A_i$ values. If you make optimal assignments, what is the smallest possible difference?

## 输入格式

The first line of the input gives the number of test cases, $T$. $T$ test cases follow. Each case begins with one line with three integers $R$, $C$, and $S$: respectively, the numbers of rows and columns in the grid of cells, and the number of stations. Then, there are $S$ more lines. The i-th of these has three integers $R_i$, $C_i$, and $D_i$: respectively, the row and column in which the i-th station is located, and the parameter that determines which blocks that station is able to patrol, as described above.

## 输出格式

For each test case, output one line containing `Case #x: y`, where $x$ is the test case number (starting from 1) and $y$ is the difference described above.
## 样例

### 样例输入 #1
```
2
3 4 2
1 1 1
3 3 2
5 5 2
4 1 2
3 2 2
```
### 样例输出 #1
```
Case #1: 4
Case #2: 0
```
## 提示

In Sample Case #1, the city consists of a grid with 3 rows and 4 columns, with one station in the upper left block and one station in the block to the left of the lower right block. The first station can only patrol the three blocks that touch the edge or corner of its block; every other block is at a horizontal or vertical distance of more than 1 away. The second station can patrol any block in the grid (except for the blocks containing the stations). The difference in number of blocks assigned is minimized if you assign station 1 all three of the blocks it can patrol, and then assign the remaining seven blocks to station 2.

In Sample Case #2, one optimal strategy is to assign the blocks as follows. In this picture, $1$ represents station 1, $2$ represents station 2, $!$ represents a block assigned to station 1, $@$ represents a block assigned to station 2, and $.$ represents a block assigned to neither station (because neither station can patrol it). Notice that a station's assigned blocks do not need to form a single continuous area.

```
@@@@.
!!!@.
!2!@.
1!!@.
!@!@.
```

**Limits**

- $1 \leq T \leq 100.$
- $2 \leq S \leq 15.$
- $1 \leq R_i \leq R,$ for all $i.$
- $1 \leq C_i \leq C,$ for all $i.$
- For all $i \neq j,$ $R_i \neq R_j$ and/or $C_i \neq C_j.$ (No two stations are in the same block.)
- $1 \leq D_i < \max(R, C),$ for all $i.$

**Test set 1 (5 Pts, Visible)**

- $1 \leq R \leq 20.$
- $1 \leq C \leq 20.$

**Test set 2 (23 Pts, Hidden)**

- $1 \leq R \leq 10^9.$
- $1 \leq C \leq 10^9.$


---

---
title: "[GCJ 2015 #2] Bilingual"
layout: "post"
diff: 省选/NOI-
pid: P13226
tag: ['2015', '网络流', '最大流最小割定理', 'Google Code Jam']
---
# [GCJ 2015 #2] Bilingual
## 题目描述

Elliot's parents speak French and English to him at home. He has heard a lot of words, but it isn't always clear to him which word comes from which language! Elliot knows one sentence that he's sure is English and one sentence that he's sure is French, and some other sentences that could be either English or French. If a word appears in an English sentence, it must be a word in English. If a word appears in a French sentence, it must be a word in French.

Considering all the sentences that Elliot has heard, what is the minimum possible number of words that he's heard that must be words in both English and French?
## 输入格式

The first line of the input gives the number of test cases, $\mathbf{T}$. $\mathbf{T}$ test cases follow. Each starts with a single line containing an integer $\mathbf{N}$. $\mathbf{N}$ lines follow, each of which contains a series of space-separated "words". Each "word" is made up only of lowercase characters a-z. The first of those $\mathbf{N}$ lines is a "sentence" in English, and the second is a "sentence" in French. The rest could be "sentences" in either English or French. (Note that the "words" and "sentences" are not guaranteed to be valid in any real language.)
## 输出格式

For each test case, output one line containing "Case #$x$: $y$", where $\mathrm{x}$ is the test case number (starting from 1) and $\mathrm{y}$ is the minimum number of words that Elliot has heard that must be words in both English and French.
## 样例

### 样例输入 #1
```
4
2
he loves to eat baguettes
il aime manger des baguettes
4
a b c d e
f g h i j
a b c i j
f g h d e
4
he drove into a cul de sac
elle a conduit sa voiture
il a conduit dans un cul de sac
il mange pendant que il conduit sa voiture
6
adieu joie de vivre je ne regrette rien
adieu joie de vivre je ne regrette rien
a b c d e
f g h i j
a b c i j
f g h d e
```
### 样例输出 #1
```
Case #1: 1
Case #2: 4
Case #3: 3
Case #4: 8
```
## 提示

**Sample Explanation**

In Case #1, Elliot knows for sure that the first sentence is in English and the second is in French, so there is no ambiguity; the only word that must be in both English and French is "baguettes".

In Case #2, the last two sentences could either be: English English, English French, French English, or French French. The second of those possibilities is the one that minimizes the number of words common to both languages; that set turns out to be d, e, i, and j.

**Limits**

- $1 \leq \mathbf{T} \leq 25$.
- Each word will contain no more than 10 characters.
- The two "known" sentences will contain no more than 1000 words each.
- The "unknown" sentences will contain no more than 10 words each.

**Small dataset**

- Time limit: ~~240~~ 5 seconds.
- $2 \leq \mathbf{N} \leq 20$.

**Large dataset**

- Time limit: ~~480~~ 10 seconds.
- $2 \leq \mathbf{N} \leq 200$.


---

---
title: "[GCJ 2014 #2] Don't Break The Nile"
layout: "post"
diff: 省选/NOI-
pid: P13258
tag: ['2014', '最短路', '最大流最小割定理', 'Google Code Jam']
---
# [GCJ 2014 #2] Don't Break The Nile
## 题目描述

Aliens have landed. These aliens find our Earth's rivers intriguing because their home planet has no flowing water at all, and now they want to construct their alien buildings in some of Earth's rivers. You have been tasked with making sure their buildings do not obstruct the flow of these rivers too much, which would cause serious problems. In particular, you need to determine what the maximum flow that the river can sustain is, given the placement of buildings.

The aliens prefer to construct their buildings on stretches of river that are straight and have uniform width. Thus you decide to model the river as a rectangular grid, where each cell has integer coordinates $(X, Y; 0 \leq X < W$ and $0 \leq Y < H)$. Each cell can sustain a flow of 1 unit through it, and the water can flow between edge-adjacent cells. All the cells on the south side of the river (that is with y-coordinate equal to 0) have an implicit incoming flow of 1. All buildings are rectangular and are grid-aligned. The cells that lie under a building cannot sustain any flow. Given these constraints, determine the maximum amount of flow that can reach the cells on the north side of the river (that is with y-coordinate equal to $H-1$).
## 输入格式

The first line of the input gives the number of test cases, $T$. $T$ test cases follow. Each test case will begin with a single line containing three integers, $W$, the width of the river, $H$, the height of the river, and $B$, the number of buildings being placed in the river. The next $B$ lines will each contain four integers, $X_0$, $Y_0$, $X_1$, and $Y_1$. $X_0$, $Y_0$ are the coordinates of the lower-left corner of the building, and $X_1$, $Y_1$ are the coordinates of the upper-right corner of the building. Buildings will not overlap, although two buildings can share an edge.

## 输出格式

For each test case, output one line containing "Case #$x$: $m$", where $x$ is the test case number (starting from 1) and $m$ is the maximum flow that can pass through the river.
## 样例

### 样例输入 #1
```
2
3 3 2
2 0 2 0
0 2 0 2
5 6 4
1 0 1 0
3 1 3 3
0 2 1 3
1 5 2 5
```
### 样例输出 #1
```
Case #1: 1
Case #2: 2
```
## 提示

**Sample Explanation**

Here are visual representations of the two test cases in the sample input:

![](https://cdn.luogu.com.cn/upload/image_hosting/hwtuxcp6.png)

![](https://cdn.luogu.com.cn/upload/image_hosting/uogniqfm.png)

**Limits**

- $1 \leq T \leq 100$.
- $0 \leq X_0 \leq X_1 < W$.
- $0 \leq Y_0 \leq Y_1 < H$.

**Small dataset(10 Pts)**

- Time limit: ~~60~~ 3 seconds.
- $3 \leq W \leq 100$.
- $3 \leq H \leq 500$.
- $0 \leq B \leq 10$.

**Large dataset(20 Pts)**

- Time limit: ~~120~~ 5 seconds.
- $3 \leq W \leq 1000$.
- $3 \leq H \leq 10^8$.
- $0 \leq B \leq 1000$.



---

---
title: "[GCJ 2009 Finals] Wi-fi Towers"
layout: "post"
diff: 省选/NOI-
pid: P13451
tag: ['2009', '网络流', '最小割', 'Google Code Jam']
---
# [GCJ 2009 Finals] Wi-fi Towers
## 题目描述

You are given a network of wireless towers. Each tower has a range and can send data to neighboring towers as long as the distance is less than or equal to the sending tower's range.

The towers are using an old communication protocol $A$, but there is a new, better protocol $B$ available. We are thinking about upgrading some towers to send data using protocol $B$ to achieve better bandwidth.

There is one important restriction: if a tower $T$ is using the new protocol $B$, every tower within $T$'s range must also be running protocol $B$, so that they can understand the data sent from $T$. The reverse is not necessary — towers running the new protocol $B$ can be sent data from towers using the old protocol $A$.

Your task is to select the best set of towers to upgrade from protocol $A$ to protocol $B$. There is some benefit to upgrading a tower, but there are also installation costs. So each tower will have a score, which can be positive or negative, which is the value of upgrading the tower. Choose the set of towers to upgrade in such a way that the total score of the upgraded towers is maximized.
## 输入格式

The first line contains the number of test cases, $T$. Each test case starts with the number of towers, $n$. The following $n$ lines each contain 4 integers: $x$, $y$, $r$, $s$. They describe a tower at coordinates $x$, $y$ having a range of $r$ and a score (value of updating to the new protocol) of $s$.

## 输出格式

For each test case, output:

Case #$X$: score

where $X$ is the test case number, starting from 1, and score is the total score for the best choice of towers.
## 样例

### 样例输入 #1
```
1
5
0 1 7 10
0 -1 7 10
5 0 1 -15
10 0 6 10
15 1 2 -20
```
### 样例输出 #1
```
Case #1: 5
```
## 提示

**Limits**

- $1 \leq T \leq 55$
- $-10000 \leq x, y \leq 10000$
- $1 \leq r \leq 20000$
- $-1000 \leq s \leq 1000$
- No two towers will have the same coordinates.

**Small dataset(3 Pts)**

- $1 \leq n \leq 15$

**Large dataset(25 Pts)**

- $1 \leq n \leq 500$



---

---
title: "小M的作物"
layout: "post"
diff: 省选/NOI-
pid: P1361
tag: ['图论', '网络流', '最小割']
---
# 小M的作物
## 题目描述

小 M 在 MC 里开辟了两块巨大的耕地 $A$ 和 $B$（你可以认为容量是无穷），现在，小 P 有 $n$ 种作物的种子，每种作物的种子有 $1$ 个（就是可以种一棵作物），编号为 $1$ 到 $n$。

现在，第 $i$ 种作物种植在 $A$ 中种植可以获得 $a_i$ 的收益，在 $B$ 中种植可以获得 $b_i$ 的收益，而且，现在还有这么一种神奇的现象，就是某些作物共同种在一块耕地中可以获得额外的收益，小 M 找到了规则中共有 $m$ 种作物组合，第 $i$ 个组合中的作物共同种在 $A$ 中可以获得 $c_{1,i}$ 的额外收益，共同种在 $B$ 中可以获得 $c_{2,i}$ 的额外收益。

小 M 很快的算出了种植的最大收益，但是他想要考考你，你能回答他这个问题么？
## 输入格式

第一行一个整数 $n$，表示作物种数。

第二行 $n$ 个整数，表示 $a_i$。

第三行 $n$ 个整数，表示 $b_i$。

第四行一个整数 $m$，表示组合种数。

接下来 $m$ 行中，第 $i$ 行第一个整数 $k_i$，表示第 $i$ 个作物组合中的作物种数，接下来两个整数 $c_{1,i},c_{2,i}$，然后 $k_i$ 个整数，表示该组合中的作物编号。
## 输出格式

只有一行，包括一个整数，表示最大收益。
## 样例

### 样例输入 #1
```
3
4 2 1
2 3 2
1
2 3 2 1 2
```
### 样例输出 #1
```
11
```
## 提示

### 样例解释

 $A$ 耕地种作物 $1,2$，$B$ 耕地种作物 $3$，收益： $4+2+3+2=11$。

### 数据范围

对于 $100\%$ 的数据，$1 \le k < n \le 10^3$，$1 \le m \le 10^3$。题目当中出现的所有权值均为不大于 $1000$ 的非负整数。


---

---
title: "[国家集训队] happiness"
layout: "post"
diff: 省选/NOI-
pid: P1646
tag: ['集训队互测', '最小割']
---
# [国家集训队] happiness
## 题目描述

高一一班的座位表是个 $n\times m$ 的矩阵，经过一个学期的相处，每个同学和前后左右相邻的同学互相成为了好朋友。这学期要分文理科了，每个同学对于选择文科与理科有着自己的喜悦值，而一对好朋友如果能同时选文科或者理科，那么他们又将收获一些喜悦值。

作为计算机竞赛教练的 scp 大老板，想知道如何分配可以使得全班的喜悦值总和最大。
## 输入格式

第一行两个正整数 $n$，$m$。

接下来是六个矩阵。

- 第一个矩阵为 $n$ 行 $m$ 列。此矩阵的第 $i$ 行第 $j$ 列的数字表示座位在第 $i$ 行第 $j$ 列的同学选择文科获得的喜悦值。
- 第二个矩阵为 $n$ 行 $m$ 列。此矩阵的第 $i$ 行第 $j$ 列的数字表示座位在第 $i$ 行第 $j$ 列的同学选择理科获得的喜悦值。
- 第三个矩阵为 $n-1$ 行 $m$ 列。此矩阵的第 $i$ 行第 $j$ 列的数字表示座位在第 $i$ 行第 $j$ 列的同学与第 $i+1$ 行第 $j$ 列的同学同时选择文科获得的额外喜悦值。
- 第四个矩阵为 $n-1$ 行 $m$ 列。此矩阵的第 $i$ 行第 $j$ 列的数字表示座位在第 $i$ 行第 $j$ 列的同学与第 $i+1$ 行第 $j$ 列的同学同时选择理科获得的额外喜悦值。
- 第五个矩阵为 $n$ 行 $m-1$ 列。此矩阵的第 $i$ 行第 $j$ 列的数字表示座位在第 $i$ 行第 $j$ 列的同学与第 $i$ 行第 $j+1$ 列的同学同时选择文科获得的额外喜悦值。
- 第六个矩阵为 $n$ 行 $m-1$ 列。此矩阵的第 $i$ 行第 $j$ 列的数字表示座位在第 $i$ 行第 $j$ 列的同学与第 $i$ 行第 $j+1$ 列的同学同时选择理科获得的额外喜悦值。
## 输出格式

输出一个整数，表示喜悦值总和的最大值。

## 样例

### 样例输入 #1
```
1 2
1 1
100 110
1
1000
```
### 样例输出 #1
```
1210

```
## 提示

### 样例解释

两人都选理，则获得 $100+110+1000$ 的喜悦值。

对于 $100\%$ 的数据，$1\le n,m \le 100$，且所有喜悦值均为小于等于 $5000$ 的非负整数。


---

---
title: "[国家集训队] 圈地计划"
layout: "post"
diff: 省选/NOI-
pid: P1935
tag: ['集训队互测', '最小割']
---
# [国家集训队] 圈地计划
## 题目描述

最近房地产商 GDOI(Group of Dumbbells Or Idiots) 从 NOI(Nuts Old Idiots) 手中得到了一块开发土地。据了解，这块土地是一块矩形的区域，可以纵横划分为 $N\times M$ 块小区域。GDOI 要求将这些区域分为商业区和工业区来开发。根据不同的地形环境，每块小区域建造商业区和工业区能取得不同的经济价值。更具体点，对于第 $i$ 行第 $j$ 列的区域，建造商业区将得到 $A_{i,j}$ 收益，建造工业区将得到 $B_{i,j}$ 收益。另外不同的区域连在一起可以得到额外的收益，即如果区域 $(i,j)$ 相邻（相邻是指两个格子有公共边）有 $k$ 块（显然 $k$ 不超过 $4$）类型不同于 $(i,j)$ 的区域，则这块区域能增加 $k\times C_{i,j}$ 收益。经过 Tiger.S 教授的勘察，收益矩阵 $A,B,C$ 都已经知道了。你能帮 GDOI 求出一个收益最大的方案么？

## 输入格式

输入第一行为两个整数，分别为正整数 $N$ 和 $M$，分别表示区域的行数和列数；

第 $2$ 到 $N+1$ 行，每行 $M$ 个整数，表示商业区收益矩阵 $A$；

第 $N+2$ 到 $2N+1$ 行，每行 $M$ 个整数，表示工业区收益矩阵 $B$；

第 $2N+2$ 到 $3N+1$ 行，每行 $M$ 个整数，表示相邻额外收益矩阵 $C$。

## 输出格式

输出只有一行，包含一个整数，为最大收益值。

## 样例

### 样例输入 #1
```
3 3
1 2 3
4 5 6
7 8 9
9 8 7
6 5 4
3 2 1
1 1 1
1 3 1
1 1 1
```
### 样例输出 #1
```
81
```
## 提示

$N,M\leq 100$，$0\leq A_{i,j},B_{i,j},C_{i,j}\leq 10^3$。

对于 $30\%$ 的数据有 $N, M\leq 6$；

对于 $50\%$ 的数据有 $N, M \leq 20$；

对于 $100\%$ 的数据有 $N,M\leq 100$。


---

---
title: "[NOI2010] 海拔"
layout: "post"
diff: 省选/NOI-
pid: P2046
tag: ['图论', '2010', 'NOI', '最短路', '最小割']
---
# [NOI2010] 海拔
## 题目描述

YT 市是一个规划良好的城市，城市被东西向和南北向的主干道划分为 $n \times n$ 个区域。简单起见，可以将 YT 市看作 一个正方形，每一个区域也可看作一个正方形。从而，YT 城市中包括 $(n+1) \times (n+1)$ 个交叉路口和 $2n \times (n+1)$ 条双向道路（简称道路），每条双向道路连接主干道上两个相邻的交叉路口。下图为一张 YT 市的地图（$n = 2$），城市被划分为 $2 \times 2$ 个区域，包括 $3 \times 3$ 个交叉路口和 $12$ 条双向道路。

 ![](https://cdn.luogu.com.cn/upload/pic/1133.png) 

小 Z 作为该市的市长，他根据统计信息得到了每天上班高峰期间 YT 市每条道路两个方向的人流量，即在高峰期间沿着该方向通过这条道路的人数。每一个交叉路口都有不同的海拔高度值，YT 市市民认为爬坡是一件非常累的事情，每向上爬 $h$ 的高度，就需要消耗 $h$ 的体力。如果是下坡的话，则不需要耗费体力。因此如果一段道路的终点海拔减去起点海拔的值为 $h$（注意 $h$ 可能是负数），那么一个人经过这段路所消耗的体力是 $\max\{0, h\}$。

小 Z 还测量得到这个城市西北角的交叉路口海拔为 $0$，东南角的交叉路口海拔为 $1$（如上图所示），但其它交叉路口的海拔高度都无法得知。小 Z 想知道在最理想的情况下（即你可以任意假设其他路口的海拔高度），每天上班高峰期间所有人爬坡消耗的总体力和的最小值。
## 输入格式

第一行包含一个整数 $n$。

接下来 $4n(n + 1)$ 行，每行包含一个非负整数分别表示每一条道路每一个方向的人流量信息。

输入顺序：$n(n + 1)$个数表示所有从西到东方向的人流量，然后 $n(n + 1)$ 个数表示所有从北到南方向的人流量，$n(n + 1)$ 个数表示所有从东到西方向的人流量，最后是 $n(n + 1)$ 个数表示所有从南到北方向的人流量。对于每一个方向，输入顺序按照起点由北向南，若南北方向相同时由西到东的顺序给出（参见样例输入）。
## 输出格式

仅包含一个数，表示在最理想情况下每天上班高峰期间所有人爬坡所消耗的总体力和（即总体力和的最小值），结果四舍五入到整数。

## 样例

### 样例输入 #1
```
1
1
2
3
4
5
6
7
8
```
### 样例输出 #1
```
3
```
## 提示

![](https://cdn.luogu.com.cn/upload/pic/1134.png) 

### 数据范围

- 对于 $20\%$ 的数据：$n \leq 3$；
- 对于 $50\%$ 的数据：$n \leq 15$；
- 对于 $80\%$ 的数据：$n \leq 40$；
- 对于 $100\%$ 的数据：$1 \leq n \leq 500$，$0 \leq \text{流量} \leq 10^6$ 且所有流量均为整数。


---

---
title: "方格取数问题"
layout: "post"
diff: 省选/NOI-
pid: P2774
tag: ['网络流', 'O2优化', '深度优先搜索 DFS', '最小割', '网络流与线性规划 24 题']
---
# 方格取数问题
## 题目描述

有一个 $m$ 行 $n$ 列的方格图，每个方格中都有一个正整数。现要从方格中取数，使任意两个数所在方格没有公共边，且取出的数的总和最大，请求出最大的和。

## 输入格式

第一行是两个用空格隔开的整数，分别代表方格图的行数 $m$ 和列数 $n$。

第 $2$ 到第 $(m + 1)$ 行，每行 $n$ 个整数，第 $(i + 1)$ 行的第 $j$ 个整数代表方格图第 $i$ 行第 $j$ 列的的方格中的数字 $a_{i, j}$。
## 输出格式

输出一行一个整数，代表和最大是多少。
## 样例

### 样例输入 #1
```
3 3
1 2 3
3 2 3
2 3 1 
```
### 样例输出 #1
```
11
```
## 提示

**数据规模与约定**

对于 $100\%$ 的数据，保证 $1 \leq n, m \leq 100$，$1 \leq a_{i, j} \leq 10^5$。

**提示**

请注意输入的第一行先读入 $m$ 再读入 $n$。


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
title: "[USACO09MAR] Earthquake Damage 2 G"
layout: "post"
diff: 省选/NOI-
pid: P2944
tag: ['2009', 'USACO', '网络流', '图论建模', '最小割']
---
# [USACO09MAR] Earthquake Damage 2 G
## 题目描述

Wisconsin has had an earthquake that has struck Farmer John's farm! The earthquake has damaged some of the pastures so that they are unpassable. Remarkably, none of the cowpaths was damaged.

As usual, the farm is modeled as a set of P (1 <= P <= 3,000) pastures conveniently numbered 1..P which are connected by a set of C (1 <= C <= 20,000) non-directional cowpaths conveniently numbered 1..C. Cowpath i connects pastures a\_i and b\_i (1 <= a\_i <= P; 1 <= b\_i <= P). Cowpaths might connect a\_i to itself or perhaps might connect two pastures more than once.  The barn is located in pasture 1.

A total of N (1 <= N <= P) cows (in different pastures) sequentially contacts Farmer John via moobile phone with an integer message report\_j (2 <= report\_j <= P) that indicates that pasture report\_j is undamaged but that the calling cow is unable to return to the barn from pasture report\_j because she could not find a path that does not go through damaged pastures.

After all the cows report in, determine the minimum number of pastures that are damaged.

地震袭击了威斯康星州，一些牧场被摧毁了。

一共有 $P$ 个牧场。由 $C$ 条双向路连接。两个牧场间可能有多条路。一条路也可能连接相同的牧场。牛棚坐落在牧场 $1$。

$N\ (1 \le N \le P)$ 只奶牛打来了求救电话，说她们的农场没有被摧毁，但是已经无法到达牛棚。求出最少可能有多少牧场被摧毁。

## 输入格式

\* Line 1: Three space-separated integers: P, C, and N

\* Lines 2..C+1: Line i+1 describes cowpath i with two integers: a\_i and b\_i

\* Lines C+2..C+N+1: Line C+1+j contains a single integer: report\_j

## 输出格式

\* Line 1: One number, the minimum number of damaged pastures.

## 样例

### 样例输入 #1
```
5 5 2 
1 2 
2 3 
3 5 
2 4 
4 5 
4 
5 

```
### 样例输出 #1
```
1 

```
## 提示

Only pasture 2 being damaged gives such a scenario.



---

---
title: "[HNOI2013] 切糕"
layout: "post"
diff: 省选/NOI-
pid: P3227
tag: ['2013', '网络流', '湖南', '最小割']
---
# [HNOI2013] 切糕
## 题目描述

经过千辛万苦小 A 得到了一块切糕，切糕的形状是长方体，小 A 打算拦腰将切糕切成两半分给小 B。出于美观考虑，小 A 希望切面能尽量光滑且和谐。于是她找到你，希望你能帮她找出最好的切割方案。

出于简便考虑，我们将切糕视作一个长 $P$、宽 $Q$、高 $R$ 的长方体点阵。我们将位于第 $z$ 层中第 $x$ 行、第 $y$ 列上的点称 $(x,y,z)$，它有一个非负的不和谐值 $v(x,y,z)$。一个合法的切面满足以下两个条件：

 - 与每个纵轴（一共有 $P\times Q$ 个纵轴）有且仅有一个交点。即切面是一个函数 $f(x,y)$，对于所有 $(x,y)(x\in [1,P],y\in[1,Q])$，我们需指定一个切割点 $f(x,y)$，且 $1\le f(x,y)\le R$。

 - 切面需要满足一定的光滑性要求，即相邻纵轴上的切割点不能相距太远。对于所有的 $1\le x,x'\le P$ 和 $1\le y,y'\le Q$，若 $|x-x'|+|y-y'|=1$，则 $|f(x,y)-f(x',y')| \le D$，其中 $D$ 是给定的一个非负整数。

可能有许多切面 $f$ 满足上面的条件，小 A 希望找出总的切割点上的不和谐值最小的那个。
## 输入格式

第一行是三个正整数 $P,Q,R$，表示切糕的长宽高。

第二行有一个非负整数 $D$，表示光滑性要求。

接下来是 $R$ 个 $P$ 行 $Q$ 列的矩阵，第 $z$ 个矩阵的第 $x$ 行第 $y$ 列是 $v(x,y,z)(1\le x\le P,1\le y\le Q,1\le z\le R)$。
## 输出格式

仅包含一个整数，表示在合法基础上最小的总不和谐值。
## 样例

### 样例输入 #1
```
2 2 2
1
6 1
6 1
2 6
2 6
```
### 样例输出 #1
```
6
```
## 提示

#### 输入输出样例 1 解释

最佳切面的 $f$ 为 $f(1,1)=f(2,1)=2,f(1,2)=f(2,2)=1$。

---
#### 数据规模与约定

对于 $100\%$ 的数据，$1 \leq P,Q,R\leq 40,0\le D\le R$，且给出的所有的不和谐值不超过 $1000$。


---

---
title: "[SDOI2014] LIS"
layout: "post"
diff: 省选/NOI-
pid: P3308
tag: ['2014', '网络流', '山东', '最小割']
---
# [SDOI2014] LIS
## 题目描述

给定序列 $A$，序列中的每一项 $A_i$ 有删除代价 $B_i$ 和附加属性 $C_i$。请删除若干项，使得 $A$ 的最长上升子序列长度减少至少 $1$，且付出的代价之和最小，并输出方案。

如果有多种方案，请输出将删去项的附加属性排序之后，字典序最小的一种。

## 输入格式

输入包含多组数据。    

输入的第一行包含整数 $T$，表示数据组数。接下来 $4T$ 行描述每组数据。    

每组数据的第一行包含一个整数 $N$，表示 $A$ 的项数。

接下来三行，每行 $N$ 个整数 $A_1\sim A_n$，$B_1\sim B_n$，$C_1\sim C_n$，满足 $1\le A_i,B_i,C_i \le 10^9$，且 $C_i$ 两两不同。

## 输出格式

对每组数据，输出两行。第一行包含两个整数 $S,M$，依次表示删去项的代价和与数量；接下来一行 $M$ 个整数，表示删去项在 $A$ 中的的位置，按升序输出。

## 样例

### 样例输入 #1
```
1
6
3 4 4 2 2 3
2 1 1 1 1 2
6 5 4 3 2 1
```
### 样例输出 #1
```
4 3
2 3 6

```
## 提示

【样例说明】

删去 $(A_2,A_3,A_6),(A_1,A_6),(A_2,A_3,A_4,A_5)$ 等都是合法的方案，但$(A_2,A_3,A_6)$ 对应的 $C$ 值的字典序最小。

对于 $100\%$ 的数据，$1\le N\le 700$，$1\le T\le 5$。



---

---
title: "[ZJOI2011] 最小割"
layout: "post"
diff: 省选/NOI-
pid: P3329
tag: ['2011', '网络流', '浙江', '分治', '最小割']
---
# [ZJOI2011] 最小割
## 题目描述

小白在图论课上学到了一个新的概念——最小割，下课后小白在笔记本上写下了如下这段话： 

对于一个图，某个对图中结点的划分将图中所有结点分成两个部分，如果结点 $s$ 和 $t$ 不在同一个部分中，则称这个划分是关于 $s,t$ 的割。对于带权图来说，将所有顶点处在不同部分的边的权值相加所得到的值定义为这个割的容量，而 $s,t$ 的最小割指的是在关于 $s,t$ 的割中容量最小的割。

现给定一张无向图，小白有若干个形如“图中有多少个无序点对的最小割的容量不超过 $x$ ”的疑问，小蓝虽然很想回答这些问题，但小蓝最近忙着挖木块，于是作为小蓝的好友，你又有任务了。
## 输入格式

**本题有多组测试数据。**

第一行一个整数 $T$，表示测试数据组数。

对于每组测试数据，第一行两个整数 $n,m$，表示图的点数和边数。

接下来 $m$ 行，每行三个整数 $u,v,c$ 表示有一条权为 $c$ 的无向边 $(u,v)$。不保证图中无重边。

接下来一行一个整数 $q$ 表示询问的个数，下面 $q$ 行每行一个整数 $x$ 描述一组询问。
## 输出格式

对于每一组测试数据输出 $q$ 行，每行一个整数表示对应询问的答案。对于满足条件的点对 $(p,q)$ 和点对 $(q,p)$ 只应该在答案中统计一次。

**在两组测试数据之间需要输出一行空行。**
## 样例

### 样例输入 #1
```
1
5 0
1
0
```
### 样例输出 #1
```
10
```
## 提示

对于 $100 \%$ 的数据，$1 \leq T \leq 10$，$1 \leq n \leq 150$，$0 \leq m \leq 3000$，$0 \leq x \leq 2^{31}-1$，$0 \leq q \leq 30$。


---

---
title: "[POI 2005] KOS-Dicing"
layout: "post"
diff: 省选/NOI-
pid: P3425
tag: ['2005', 'POI（波兰）', '网络流', 'Special Judge', '生成树', '最小割']
---
# [POI 2005] KOS-Dicing
## 题目描述

Dicing is a two-player game and its outcome is fully random. Lately its popularity increases all over Byteotia. There is even a special club for dicing amateurs in the capital city of Byteotia. The club patrons take their time talking to each other and playing their favourite game with a randomly chosen opponent every once in a while. Everyone who wins the most games one day gains the title of the lucky chap. Sometimes it happens that the night at the club is a quiet one and only few games are played. It is a time when even one win can make you a lucky chap.

Once upon a time a most unlucky fellow, Byteasar, won the glorious title. He was so deeply shocked that he completely forgot how many games he had won. Now he is wondering how good his luck was and whether fortune finally smiled upon him - perhaps his luck changed for good? He knows exactly how many games and between whom were played that lucky night. However, he does not know the results. Byteasar desires to find out what is the smallest number of wins that could provide the title of the lucky chap. Be a good fellow and help him satisfy his curiosity!

TaskWrite a programme that:

for each game played reads from the standard input the pair of players who competed in it.

finds the smallest number $k$, such that a set of games' outcomes exists in which each player wins $k$ games at the most,writes the number $k$ and the results of games in the found set to the standard output.

Dicing 是一个两人玩的游戏,这个游戏在Byteotia非常流行. 甚至人们专门成立了这个游戏的一个俱乐部. 俱乐部的人时常在一起玩这个游戏然后评选出玩得最好的人.现在有一个非常不走运的家伙,他想成为那个玩的最好的人,他现在知道了所有比赛的安排,他想知道,在最好的情况下,他最少只需要赢几场就可以赢得冠军,即他想知道比赛以后赢的最多的那个家伙最少会赢多少场.

## 输入格式

In the first line of the standard input there is a pair of integers $n$ and $m$ separated by a single space, $1\le n\le 10000$, $0\le m\le 10000$; $n$ denotes the number of players, while $m$ is the number of games. The players are numbered from $1$ to $n$. In the following $m$ lines there are pairs of players' numbers depicting the sequence of games, separated by single spaces. One pair may occur many times in the sequence.

## 输出格式

The first line of the standard output should contain the determined number $k$. For each pair of players' numbers $a$, $b$ specified in the $i$'th line of the input, in the $i$'th line of the output the number $1$ should be written if the player no. $a$ wins against player no. $b$ in the found set of outcomes, or $0$ otherwise.

## 样例

### 样例输入 #1
```
4 4
1 2
1 3
1 4
1 2
```
### 样例输出 #1
```
1
0
0
0
1
```
## 题目翻译

描述

掷骰子是一种双人游戏，它的结果是完全随机的。最近它在整个Byteotia变得非常流行。在Byteotia的首都甚至有一个特别的掷骰子业余爱好者俱乐部。俱乐部的老主顾们花时间互相聊天并每隔一阵子就和一个随机选择的对手玩这他们最喜欢的游戏。一天中赢得最多游戏的人会得到“幸运者”头衔。有时晚上俱乐部很安静，只有很少的比赛。这是哪怕赢一场也能获得“幸运者”头衔的时间。

很久很久以前有一个很不走运的人，叫Byteasar，赢得了这个光荣的头衔。他被深深地震惊了以至于完全忘了他已经赢了多少场。现在他想知道他有多幸运，以及幸运之神是否最终会向他微笑——也许他的运气会变好？他确切地知道在那个幸运的晚上有多少场游戏以及是谁玩的。然而，他不知道结果。Byteasar希望查明至少要赢几场才能获得“幸运者”头衔。做个好人，帮他满足他的好奇心吧！

任务：写一个程序：

对于每场游戏从stdin读入这场游戏的一对玩家 找到最小的数k，使得存在一个游戏结果的集合，其中赢最多的玩家赢了k场。向stdout输出数k和找到的集合中游戏的结果

输入

stdin的第一行有一个一对由一个空格分开整数n和m (1 <= n, m <= 10000) 。n表示玩家数，m表示游戏数。玩家从1到n编号。在接下来的m行中有每场游戏的一对玩家的编号，由一个空格分开，描述了游戏的序列。一对玩家可能会在这个序列中多次出现。

输出

stdout的第一行应该包含一个确定的数k。对于在输入的第i行指定的一对玩家a, b，如果在找到的结果集合中a胜过b，则在输出的第i行输出1, 否则输出0.

感谢 @zyt1253679098  提供的翻译。


---

---
title: "[POI 2006] SZK-Schools"
layout: "post"
diff: 省选/NOI-
pid: P3440
tag: ['2006', 'POI（波兰）', '深度优先搜索 DFS', '最小割']
---
# [POI 2006] SZK-Schools
## 题目描述

B 国境内有 $n$ 所学校，每所学校都有一个 $1 \sim n$ 的编号。

由于管理过于宽松，可能存在两个学校同时用一个编号的情况，当然也存在一个编号没有学校用的情况。

现在国王决定重新给所有学校编号，使得任意两个学校的编号不同。

当然，改变编号是一个很繁重的工作，学校不希望自己的编号改变太多。每个学校都有一个可以接受的新编号区间 $[a,b]$，以及改变编号的单位成本 $k$。如果一个学校的旧编号为 $m$，新编号为 $m'$，那么给这个学校改变编号的成本即为 $k \times |m'-m|$。

现在你需要告诉国王完成编号更新的最低成本是多少，或者说明这是不可能的。
## 输入格式

第一行一个整数 $n$。

接下来 $n$ 行，每行四个整数 $m_i,a_i,b_i,k_i$，代表 $i$ 号学校的旧编号为 $m_i$，新编号的范围为 $[a_i,b_i]$，改变编号的单位成本为 $k_i$。
## 输出格式

如果不存在一种方案，使得任意两个学校的编号不同，输出 `NIE`。

否则输出一个整数，代表最小成本。
## 样例

### 样例输入 #1
```
5
1 1 2 3
1 1 5 1
3 2 5 5
4 1 5 10
3 3 3 1
```
### 样例输出 #1
```
9
```
## 提示

【数据范围】  
对于 $100\%$ 的数据，$1\le a_i \le m_i \le b_i \le n \le 200$，$1\le k_i \le 1000$。


---

---
title: "[六省联考 2017] 寿司餐厅"
layout: "post"
diff: 省选/NOI-
pid: P3749
tag: ['2017', '各省省选', '广度优先搜索 BFS', '深度优先搜索 DFS', '最小割']
---
# [六省联考 2017] 寿司餐厅
## 题目描述

Kiana 最近喜欢到一家非常美味的寿司餐厅用餐。

每天晚上，这家餐厅都会按顺序提供 $n$ 种寿司，第 $i$ 种寿司有一个代号 $a_i$ 和美味度 $d_{i, i}$，不同种类的寿司有可能使用相同的代号。每种寿司的份数都是无限的，Kiana 也可以无限次取寿司来吃，但每种寿司每次只能取一份，且每次取走的寿司必须是按餐厅提供寿司的顺序连续的一段，即 Kiana 可以一次取走第 $1, 2$ 种寿司各一份，也可以一次取走第 $2, 3$ 种寿司各一份，但不可以一次取走第 $1, 3$ 种寿司。

由于餐厅提供的寿司种类繁多，而不同种类的寿司之间相互会有影响：三文鱼寿司和鱿鱼寿司一起吃或许会很棒，但和水果寿司一起吃就可能会肚子痛。因此，Kiana 定义了一个综合美味度 $d_{i, j} \ (i < j)$，表示在一次取的寿司中，如果包含了餐厅提供的从第 $i$ 份到第 $j$ 份的所有寿司，吃掉这次取的所有寿司后将获得的额外美味度。由于取寿司需要花费一些时间，所以我们认为分两次取来的寿司之间相互不会影响。注意在吃一次取的寿司时，不止一个综合美味度会被累加，比如若 Kiana 一次取走了第 $1, 2, 3$ 种寿司各一份，除了 $d_{1, 3}$ 以外，$d_{1, 2}, d_{2, 3}$ 也会被累加进总美味度中。

神奇的是，Kiana 的美食评判标准是有记忆性的，无论是单种寿司的美味度，还是多种寿司组合起来的综合美味度，在计入 Kiana 的总美味度时都只会被累加一次。比如，若 Kiana 某一次取走了第 $1, 2$ 种寿司各一份，另一次取走了第 $2, 3$ 种寿司各一份，那么这两次取寿司的总美味度为 $d_{1, 1} + d_{2, 2} + d_{3, 3} + d_{1, 2} + d_{2, 3}$，其中 $d_{2, 2}$ 只会计算一次。

奇怪的是，这家寿司餐厅的收费标准很不同寻常。具体来说，如果 Kiana 一共吃过了 $c \ (c > 0)$ **种**代号为 $x$ 的寿司，则她需要为这些寿司付出 $mx^2 + cx$ 元钱，其中 $m$ 是餐厅给出的一个常数。

现在 Kiana 想知道，在这家餐厅吃寿司，自己能获得的总美味度（包括所有吃掉的单种寿司的美味度和所有被累加的综合美味度）减去花费的总钱数的最大值是多少。由于她不会算，所以希望由你告诉她。
## 输入格式

第一行包含两个正整数 $n, m$，分别表示这家餐厅提供的寿司总数和计算寿司价格中使用的常数。  
第二行包含 $n$ 个正整数，其中第 $k$ 个数 $a_k$ 表示第 $k$ 份寿司的代号。  
接下来 $n$ 行，第 $i$ 行包含 $n - i + 1$ 个整数，其中第 $j$ 个数 $d_{i, i+j-1}$ 表示吃掉寿司能获得的相应的美味度，具体含义见问题描述。
## 输出格式

输出共一行包含一个正整数，表示 Kiana 能获得的总美味度减去花费的总钱数的最大值。
## 样例

### 样例输入 #1
```
3 1
2 3 2
5 -10 15
-10 15
15
```
### 样例输出 #1
```
12
```
### 样例输入 #2
```
5 0
1 4 1 3 4
50 99 8 -39 30
68 27 -75 -32
70 24 72
-10 81
-95
```
### 样例输出 #2
```
381
```
### 样例输入 #3
```
10 1
5 5 4 4 1 2 5 1 5 3
83 91 72 29 22 -5 57 -14 -36 -3
-11 34 45 96 32 73 -1 0 29
-48 68 44 -5 96 66 17 74
88 47 69 -9 2 25 -49
86 -9 -77 62 -10 -30
2 40 95 -74 46
49 -52 2 -51
-55 50 -44
72 22
-68
```
### 样例输出 #3
```
1223
```
## 提示

### 样例解释 1

在这组样例中，餐厅一共提供了 $3$ 份寿司，它们的代号依次为 $a_1 = 2, a_2 = 3, a_3 = 2$，计算价格时的常数 $m = 1$。

在保证每次取寿司都能获得新的美味度的前提下，Kiana 一共有 $14$ 种不同的吃寿司方案。以下列出其中几种：
1. Kiana 一个寿司也不吃，这样她获得的总美味度和花费的总钱数都是 $0$，两者相减也是 $0$；
2. Kiana 只取 $1$ 次寿司，且只取第 $1$ 个寿司，即她取寿司的情况为 $\{[1, 1]\}$，这样获得的总美味度为 $5$，花费的总钱数为 $1 \times 2^2 + 1 \times 2 = 6$，两者相减为 $-1$；
3. Kiana 取 $2$ 次寿司，第一次取第 $1, 2$ 个寿司，第二次取第 $2, 3$ 个寿司，即她取寿司的情况为 $\{[1, 2], [2, 3]\}$，这样获得的总美味度为 $5 + (-10) + 15 + (-10) + 15 = 15$，花费的总钱数为 $(1 \times 2^2 + 2 \times 2) + (1 \times 3^2 + 1 \times 3) = 20$，两者相减为 $-5$；
4. Kiana 取 $2$ 次寿司，第一次取第 $1$ 个寿司，第二次取第 $3$ 个寿司，即她取寿司的情况为 $\{[1, 1], [3, 3]\}$，这样获得的总美味度为 $5 + 15 = 20$，花费的总钱数为 $1 \times 2^2 + 2 \times 2 = 8$，两者相减为 $12$。

在 $14$ 种方案中，惟一的最优方案是列出的最后一种方案，这时她获得的总美味度减去花费的总钱数的值最大为 $12$。

### 数据范围

对于所有数据，保证 $-500 \leq d_{i, j} \leq 500$。

数据的一些特殊约定如下表：

| Case # | $n$ | $a_i$ | $m$ | 附加限制 |
|:-:|:-:|:-:|:-:|:-:|
| 1 | $\leq 2$ | $\leq 30$ | $= 0$ | - |
| 2 | $\leq 2$ | $\leq 30$ | $= 1$ | - |
| 3 | $\leq 3$ | $\leq 30$ | $= 0$ | - |
| 4 | $\leq 3$ | $\leq 30$ | $= 1$ | - |
| 5 | $\leq 5$ | $\leq 30$ | $= 0$ | - |
| 6 | $\leq 5$ | $\leq 30$ | $= 1$ | - |
| 7 | $\leq 10$ | $\leq 30$ | $= 0$ | 所有的 $a_i$ 相同 |
| 8 | $\leq 10$ | $\leq 30$ | $= 1$ | - |
| 9 | $\leq 15$ | $\leq 30$ | $= 0$ | 所有的 $a_i$ 相同 |
| 10 | $\leq 15$ | $\leq 30$ | $= 1$ | - |
| 11 | $\leq 30$ | $\leq 1000$ | $= 0$ | 所有的 $a_i$ 相同 |
| 12 | $\leq 30$ | $\leq 30$ | $= 0$ | 所有的 $a_i$ 相同 |
| 13 | $\leq 30$ | $\leq 1000$ | $= 0$ | - |
| 14 | $\leq 30$ | $\leq 1000$ | $= 1$ | - |
| 15 | $\leq 50$ | $\leq 1000$ | $= 0$ | 所有的 $a_i$ 相同 |
| 16 | $\leq 50$ | $\leq 30$ | $= 0$ | 所有的 $a_i$ 相同 |
| 17 | $\leq 50$ | $\leq 1000$ | $= 0$ | - |
| 18 | $\leq 50$ | $\leq 1000$ | $= 1$ | - |
| 19 | $\leq 100$ | $\leq 1000$ | $= 0$ | - |
| 20 | $\leq 100$ | $\leq 1000$ | $= 1$ | - |


---

---
title: "[TJOI2009] 战争游戏"
layout: "post"
diff: 省选/NOI-
pid: P3866
tag: ['2009', '各省省选', '最小割', '天津']
---
# [TJOI2009] 战争游戏
## 题目背景

小R正在玩一个战争游戏。游戏地图是一个M行N列的矩阵，每个格子可能是障碍物，也可能是空地，在游戏开始时有若干支敌军分散在不同的空地格子中。每支敌军都可以从当前所在的格子移动到四个相邻的格子之一，但是不能移动到包含障碍物的格子。如果敌军移动出了地图的边界，那么战争就失败了。

## 题目描述

现在你的任务是，在敌军开始移动前，通过飞机轰炸使得某些原本是空地的格子变得不可通行，这样就有可能阻止敌军移出地图边界（出于某种特殊的考虑，你不能直接轰炸敌军所在的格子）。由于地形不同的原因，把每个空地格子轰炸成不可通行所需的炸药数目可能是不同的，你需要计算出要阻止敌军所需的最少的炸药数。

## 输入格式

输入文件的第一行包含两个数M和N，分别表示矩阵的长和宽。接下来M行，每行包含用空格隔开的N个数字，每个数字表示一个格子的情况：若数字为-1，表示这个格子是障碍物；若数字为0，表示这个格子里有一支敌军；若数字为一个正数x，表示这个格子是空地，且把它轰炸成不可通行所需的炸药数为x。

地图上的敌军数量不为1，即地图上有多个0。
## 输出格式

输出一个数字，表示所需的最少炸药数。数据保证有解存在。

## 样例

### 样例输入 #1
```
4 3
1 2 1
1 10 1
1 0 -1
1 1 1
```
### 样例输出 #1
```
6
```
## 提示

对50%的数据，1 ≤ M,N ≤ 10

对100%的数据，1 ≤ M,N ≤ 30

矩阵里的每个数不超过100



---

---
title: "[TJOI2010] 电影迷"
layout: "post"
diff: 省选/NOI-
pid: P3872
tag: ['2010', '各省省选', '图论建模', '最小割', '天津']
---
# [TJOI2010] 电影迷
## 题目描述

小A是一个电影迷，他收集了上百部的电影，打算从中挑出若干部在假期看完。他根据自己的口味和网上的介绍，对每部电影X都打了一个分数vX，表示自己喜欢的程度。这个分数的范围在-1000至1000之间，越大表示越喜欢。小A每看一部电影X，他的体验值就会加上vX。

另外，因为某些电影是组成一个系列的，比如著名的《终结者》系列、《黑客帝国》系列等等，如果小A只看了前一部而没有看后一部的话，他就会觉得不是很爽。准确来讲，对于任意两部不同的电影X,Y，他们可能存在一个依赖值dXY，表示如果小A看了X但是没看Y，他的体验值就会减少dXY。（注意与观看的顺序无关，只要两部都看过，就不会减少体验值）

现在他要选出若干电影来看，使得得到的总的体验值最大。如果他无法得到正的体验值，就输出0。

## 输入格式

输入的第一行是两个整数：电影总数N和依赖关系数目M。第二行包含用空格隔开的N个数，表示对每部电影的打分。接下来M行，每行包含三个整数X, Y, dXY，表示一个依赖关系。每个有序对(X,Y)最多出现一次。(1 ≤ X,Y ≤ N)

## 输出格式

输出一个整数，表示小A能得到的最大体验值。

## 样例

### 样例输入 #1
```
2 2
100 -50
1 2 49
2 1 10

```
### 样例输出 #1
```
51
```
## 提示

如果小A只看电影1，体验值为100-49 = 51。如果只看电影2，体验值为-50-10 = -60。如果两部都看，体验值为100+(-50) = 50。所以应该只看电影1。

数据规模与约定

对于20%的数据，1 ≤ N ≤ 15

对于100%的数据，1 ≤ N ≤ 100, -1000 ≤ vX ≤ 1000, 0 < dXY ≤ 1000

每个测试点时限1秒



---

---
title: "[TJOI2015] 线性代数"
layout: "post"
diff: 省选/NOI-
pid: P3973
tag: ['2015', '各省省选', '图论建模', '最小割', '天津']
---
# [TJOI2015] 线性代数
## 题目描述

为了提高智商，ZJY 开始学习线性代数。

她的小伙伴菠萝给她出了这样一个问题：给定一个 $n \times n$ 的矩阵 $B$ 和一个 $1 \times n$ 的矩阵 $C$。求出一个 $1×n$ 的 01 矩阵 $A$，使得 $D=(A×B-C)×A^{\sf T}$ 最大，其中$A^{\sf T}$为$A$的转置，输出$D$。
## 输入格式

第一行输入一个整数 $n$。接下来 $n$ 行输入 $B$ 矩阵，第 $i$ 行第 $j$ 个数代表 $B$ 接下来一行输入 $n$ 个整数，代表矩阵 $C$。矩阵 $B$ 和矩阵 $C$ 中每个数字都是不过 $1000$ 的非负整数。

## 输出格式

输出一个整数，表示最大的 $D$。
## 样例

### 样例输入 #1
```
3
1 2 1
3 1 0
1 2 3
2 3 7
```
### 样例输出 #1
```
2
```
## 提示

- 对于 $30\%$ 的数据，$n \leq 15$；
- 对于 $100\%$ 的数据，$1 \leq n \leq 500$；
- 另外还有两组不计分的 hack 数据，放在 subtask 2 中，数据范围与上面一致。



---

---
title: "[ICPC-Beijing 2006] 狼抓兔子"
layout: "post"
diff: 省选/NOI-
pid: P4001
tag: ['2006', '网络流', '北京', '最小割', 'ICPC']
---
# [ICPC-Beijing 2006] 狼抓兔子
## 题目描述

现在小朋友们最喜欢的"喜羊羊与灰太狼"。话说灰太狼抓羊不到，但抓兔子还是比较在行的，而且现在的兔子还比较笨，它们只有两个窝，现在你做为狼王，面对下面这样一个网格的地形：

 ![](https://cdn.luogu.com.cn/upload/pic/11942.png) 

左上角点为 $(1,1)$，右下角点为 $(N,M)$（上图中 $N=3$，$M=4$）。有以下三种类型的道路：

1. $(x,y)\rightleftharpoons(x+1,y)$

2. $(x,y)\rightleftharpoons(x,y+1)$

3. $(x,y)\rightleftharpoons(x+1,y+1)$

道路上的权值表示这条路上最多能够通过的兔子数，道路是无向的。左上角和右下角为兔子的两个窝，开始时所有的兔子都聚集在左上角 $(1,1)$ 的窝里，现在它们要跑到右下角 $(N,M)$ 的窝中去，狼王开始伏击这些兔子。当然为了保险起见，如果一条道路上最多通过的兔子数为 $K$，狼王需要安排同样数量的 $K$ 只狼，才能完全封锁这条道路，你需要帮助狼王安排一个伏击方案，使得在将兔子一网打尽的前提下，参与的狼的数量要最小。因为狼还要去找喜羊羊麻烦。

## 输入格式

第一行两个整数 $N,M$，表示网格的大小。

接下来分三部分。

第一部分共 $N$ 行，每行 $M-1$ 个数，表示横向道路的权值。

第二部分共 $N-1$ 行，每行 $M$ 个数，表示纵向道路的权值。

第三部分共 $N-1$ 行，每行 $M-1$ 个数，表示斜向道路的权值。
## 输出格式

输出一个整数，表示参与伏击的狼的最小数量。

## 样例

### 样例输入 #1
```
3 4
5 6 4
4 3 1
7 5 3
5 6 7 8
8 7 6 5
5 5 5
6 6 6
```
### 样例输出 #1
```
14
```
## 提示

### 数据规模与约定

对于全部的测试点，保证 $3 \leq N,M \leq 1000$，所有道路的权值均为不超过 $10^6$ 的正整数。


---

---
title: "[CQOI2016] 不同的最小割"
layout: "post"
diff: 省选/NOI-
pid: P4123
tag: ['2016', '重庆', '各省省选', '网络流', '分治', '最小割']
---
# [CQOI2016] 不同的最小割
## 题目描述

学过图论的同学都知道最小割的概念：对于一个图，某个对图中结点的划分将图中所有结点分成两个部分，如果结点 $s,t$ 不在同一个部分中，则称这个划分是关于 $s,t$ 的割。对于带权图来说，将所有顶点处在不同部分的边的权值相加所得到的值定义为这个割的容量，而 $s,t$ 的最小割指的是在关于 $s,t$ 的割中容量最小的割。

而对冲刺 NOI 竞赛的选手而言，求带权图中两点的最小割已经不是什么难事了。我们可以把视野放宽，考虑有 $N$ 个点的无向连通图中所有点对的最小割的容量，共能得到 $N(N-1)/2$ 个数值。这些数值中互不相同的有多少个呢？这似乎是个有趣的问题。
## 输入格式

第一行包含两个数 $N,M$，表示点数和边数。

接下来 $M$ 行，每行三个数 $u,v,w$，表示点 $u$ 和点 $v$ (从 $1$ 开始标号) 之间有一条权值是 $w$ 的边。
## 输出格式

第一行为一个整数，表示不同的最小割容量的个数。
## 样例

### 样例输入 #1
```
4 4
1 2 3
1 3 6
2 4 5
3 4 4
```
### 样例输出 #1
```
3
```
## 提示

$1\leq N\leq 850,1\leq M\leq 8500,1\leq w\leq 100000$。


---

---
title: "[AHOI2009] 最小割"
layout: "post"
diff: 省选/NOI-
pid: P4126
tag: ['2009', '并查集', '各省省选', '安徽', '强连通分量', '最小割']
---
# [AHOI2009] 最小割
## 题目描述

A,B两个国家正在交战，其中A国的物资运输网中有$N$个中转站，$M$条单向道路。设其中第$i (1≤i≤M)$条道路连接了$v_i,u_i$两个中转站，那么中转站$v_i$可以通过该道路到达$u_i$中转站，如果切断这条道路，需要代价$c_i$。

现在B国想找出一个路径切断方案，使中转站$s$不能到达中转站$t$，并且切断路径的代价之和最小。

小可可一眼就看出，这是一个求最小割的问题。但爱思考的小可可并不局限于此。现在他对每条单向道路提出两个问题：

- 问题一：是否存在一个最小代价路径切断方案，其中该道路被切断？
- 问题二：是否对任何一个最小代价路径切断方案，都有该道路被切断？

现在请你回答这两个问题。

## 输入格式

第一行有$4$个正整数，依次为$N,M,s,t$。

第$2$行到第$(M+1)$行每行$3$个正整数$v,u,c$，表示$v$中转站到$u$中转站之间有单向道路相连，单向道路的起点是$v$， 终点是$u$,切断它的代价是$c(1≤c≤100000)$。

注意:两个中转站之间可能有多条道路直接相连。 同一行相邻两数之间可能有一个或多个空格。

## 输出格式

对每条单向边，按输入顺序，依次输出一行，包含两个非$0$即$1$的整数，分别表示对问题一和问题二的回答(其中输出$1$表示是，输出$0$表示否)。 同一行相邻两数之间用一个空格隔开，每行开头和末尾没有多余空格。

## 样例

### 样例输入 #1
```
6 7 1 6
1 2 3
1 3 2
2 4 4
2 5 1
3 5 5
4 6 2
5 6 3
```
### 样例输出 #1
```
1 0
1 0
0 0
1 0
0 0
1 0
1 0
```
## 提示

设第$(i+1)$行输入的边为$i$号边，那么$\{1,2\},\{6,7\},\{2,4,6\}$是仅有的三个最小代价切割方案。它们的并是$\{1,2,4,6,7\}$，交是 $\{\varnothing \}$ 。

测试数据规模如下表所示

数据编号|N|M|数据编号|N|M
-|-|-|-|-|-
1|10|50|6|1000|20000
2|20|200|7|1000|40000
3|200|2000|8|2000|50000
4|200|2000|9|3000|60000
5|1000|20000|10|4000|60000



---

---
title: "[CEOI 2008] order"
layout: "post"
diff: 省选/NOI-
pid: P4177
tag: ['2008', 'CEOI（中欧）', '最小割']
---
# [CEOI 2008] order
## 题目描述

有 $N$ 个工作，$M$ 种机器，每种机器可以租或者买。每个工作包括若干道工序，每道工序需要某种机器来完成。

你需要最大化利益。
## 输入格式

第一行给出 $N,M$。

接下来若干行描述一个工作，对于每个工作，第一行给定 $x_i$ 和 $t_i$，分别表示此工作的收入和工序数。

后面 $t_i$ 行，每行两个整数 $a_{ij}$ 和 $b_{ij}$，分别表示此工序需要的机器和此工作租用此机器的费用。

最后 $M$ 行，每行一个正整数表示购买机器的费用 $y_i$。
## 输出格式

最大利润

## 样例

### 样例输入 #1
```
2 3
100 2
1 30
2 20
100 2
1 40
3 80
50
80
110
```
### 样例输出 #1
```
50
```
## 提示

对于 $100\%$ 的数据满足 $1\le N,M\le 1200，1\le x_i\le 5000，b_{ij},y_i\le 20000$。


---

---
title: "[CERC2015] Juice Junctions"
layout: "post"
diff: 省选/NOI-
pid: P4214
tag: ['2015', '最小割']
---
# [CERC2015] Juice Junctions
## 题目描述

你被雇佣升级一个旧果汁加工厂的橙汁运输系统。系统有管道和节点构成。每条管道都是双向的，且每条管道的流量都是 $1$ 升每秒。管道可能连接节点，每个节点最多可以连接 $3$ 条管道。节点的流量是无限的。节点用整数 $1$ 到 $n$ 来表示。在升级系统之前，你需要对现有系统进行分析。对于两个不同节点 $s$ 和 $t$，$s-t$ 的流量被定义为：当 $s$ 为源点，$t$ 为汇点，从 $s$ 能流向 $t$ 的最大流量。

以下面的第一组样例数据为例，$1-6$ 的流量为 $3$，$1-2$ 的流量为 $2$。

计算每一对满足 $a<b$ 的节点 $a-b$ 的流量的和。
## 输入格式

第一行包括 $2$ 个整数 $n$ 和 $m$（$2\leq n\leq 3\times 10^3$，$0\leq m\leq 4500$），表示节点数和管道数。

接下来 $m$ 行，每行包括两个相异整数 $a,b$（$1\leq a,b\leq n$），表示一条管道连接节点 $a,b$。

每个节点最多连接 $3$ 条管道，每对节点最多被一条管道连接。
## 输出格式

输出一个整数——每对满足 $a<b$ 的节点 $a-b$ 的流量之和。
## 样例

### 样例输入 #1
```
6 8
1 3
2 3
4 1
5 6
2 6
5 1
6 4
5 3
```
### 样例输出 #1
```
36
```


---

---
title: "文理分科"
layout: "post"
diff: 省选/NOI-
pid: P4313
tag: ['网络流', '图论建模', '最小割']
---
# 文理分科
## 题目描述

文理分科是一件很纠结的事情！（虽然看到这个题目的人肯定都没有纠结过）

小 P 所在的班级要进行文理分科。他的班级可以用一个 $n\times m$ 的矩阵进行描述，每个格子代表一个同学的座位。每位同学必须从文科和理科中选择一科。同学们在选择科目的时候会获得一个满意值。满意值按如下的方式得到：

- 如果第 $i$ 行第 $j$ 列的同学选择了文科，则他将获得 $art_{i,j}$ 的满意值，如果选择理科，将得到 $science_{i,j}$ 的满意值。

- 如果第 $i$ 行第 $j$ 列的同学选择了文科，并且他相邻（两个格子相邻当且仅当它们拥有一条相同的边）的同学全部选择了文科，则他会更开心，所以会增加 $same\text{\underline{ }}art_{i,j}$ 的满意值。

- 如果第 $i$ 行第 $j$ 列的同学选择了理科，并且他相邻的同学全部选择了理科，则增加 $same\text{\underline{ }}science_{i,j}$ 的满意值。

小 P 想知道，大家应该如何选择，才能使所有人的满意值之和最大。请告诉他这个最大值。
## 输入格式

输入第一行为两个正整数 $n,m$。  
接下来 $n$ 行 $m$ 个整数，第 $i$ 行第 $j$ 个整数表示 $art_{i,j}$；  
接下来 $n$ 行 $m$ 个整数，第 $i$ 行第 $j$ 个整数表示 $science_{i,j}$；  
接下来 $n$ 行 $m$ 个整数，第 $i$ 行第 $j$ 个整数表示 $same\text{\underline{ }}art_{i,j}$；  
接下来 $n$ 行 $m$ 个整数，第 $i$ 行第 $j$ 个整数表示 $same\text{\underline{ }}science_{i,j}$。
## 输出格式

输出为一个整数，表示最大的满意值之和。
## 样例

### 样例输入 #1
```
3 4
13 2 4 13
7 13 8 12
18 17 0 5
8 13 15 4
11 3 8 11
11 18 6 5
1 2 3 4 
4 2 3 2
3 1 0 4
3 2 3 2
0 2 2 1
0 2 4 4 
```
### 样例输出 #1
```
152
```
## 提示

### 样例说明

1 表示选择文科，0 表示选择理科，方案如下：

1  0  0  1

0  1  0  0

1  0  0  0

### 数据范围

$n,m\leq 100$，读入数据均 $\leq 500$。                                                                                                                                                              


---

---
title: "王者之剑"
layout: "post"
diff: 省选/NOI-
pid: P4474
tag: ['网络流', '二分图', '最小割']
---
# 王者之剑
## 题目描述

![https://cdn.luogu.com.cn/upload/pic/17920.png](https://cdn.luogu.com.cn/upload/pic/17920.png)  

这是在阿尔托利亚·潘德拉贡成为英灵前的事情，她正要去拔出石中剑成为亚瑟王，在这之前她要去收集一些宝石。

宝石排列在一个 $n \times m$ 的网格中，每个网格中有一块价值为 $v_{i,j}$ 的宝石，阿尔托利亚·潘德拉贡可以选择自己的起点。

开始时刻为 $0$ 秒。以下操作，每秒按顺序执行。

1. 在第 $i$ 秒开始的时候，阿尔托利亚·潘德拉贡在方格 $(x,y)$ 上，她可以拿走 $(x, y)$ 中的宝石。
2. 在偶数秒，阿尔托利亚·潘德拉贡周围四格的宝石会消失。
3. 若阿尔托利亚·潘德拉贡第 $i$ 秒开始时在方格 $(x,y)$ 上，则在第 $i+1$ 秒可以立即移动到 $(x+1,y),(x,y+1),(x-1,y)$ 或 $(x, y- 1)$ 上，也可以停留在（$x,y)$ 上。


求阿尔托利亚·潘德拉贡最多可以获得多少价值的宝石
## 输入格式

第一行给出数字 $N,M$ 代表行列数 $N,M$ 均小于等于 $100$，宝石的价值不会超过 $10000$。下面 $N$ 行 $M$ 列用于描述数字矩阵。
## 输出格式

输出最多可以拿到多少价值宝石。
## 样例

### 样例输入 #1
```
2 2
1 2
2 1
```
### 样例输出 #1
```
4
```
## 提示

姚金宇的原创题。


---

---
title: "[BalticOI 2008] 黑手党"
layout: "post"
diff: 省选/NOI-
pid: P4662
tag: ['2008', 'Special Judge', '最小割', 'BalticOI（波罗的海）']
---
# [BalticOI 2008] 黑手党
## 题目描述

Byteland 国警方收到了一条匿名举报，其中说当地黑帮老大正计划一次从港口到郊区仓库的运输。警方知道运输的时间并且知道运输需要用到国家的高速公路网。

高速公路网包含双向的高速公路段，每个路段直接连着两个不同的收费站。一个收费站可能与很多其他的收费站相连。汽车只能通过收费站进入或离开高速公路网。据所知，黑帮会距港口边最近的收费站进入高速公路，从距仓库最近的收费站离开（不会在出高速后重新进入）。特警组位于选定的收费站处。当运输车辆进入被监控的收费站时，它就会被警察抓住。

从这个角度看，最简单的办法就是在每个收费站处都安排特警班。然而，控制一个收费站需要特定的费用，每个收费站费用不同。警方想要让花费最小，所以他们需要制定一个收费站的最小控制集，这个集合满足两个条件：

-    所有从港口到仓库的交通必须至少经过集合中的一个收费站
-    监控这些收费站的费用（即监控每一个收费站费用之和）最小

你可以假设使用高速公路可以从港口到仓库。

#任务

写一个程序能够：

-    从标准输入中读取高速公路网，监控代价和运输的起点和终点
-    找到收费站的最小控制集
-    输出这个集合到标准输出

## 输入格式

标准输入的第一行包含两个整数 $n$ 和 $m$，表示收费站的总数和公路段的总数。收费站按 $1$ 到 $n$ 标号；

第二行包含两个整数 $a$ 和 $b$，分别表示距港口和仓库最近的两个收费站编号；

接下来 $n$ 行表示控制费用，第 $i$ 行包含一个整数，表示第 $i$ 个收费站的控制费用 $c$；

接下来 $m$ 行表示高速公路网，第 $j$ 行包含两个整数 $x$ 和 $y$，表示在 $x$ 和 $y$ 收费站之间有一条公路段相连。每一条高速公路段只出现一次。 
## 输出格式

唯一的一行输出应包含最小控制集中收费站的编号，以递增顺序输出，用一个空格分隔。

如果有多于一个最小控制集，你的程序可以输出任意一个。 
## 样例

### 样例输入 #1
```
5 6
5 3
2
4
8
3
10
1 5
1 2
2 4
4 5
2 3
3 4
```
### 样例输出 #1
```
1 4
```
## 提示

**样例解释**

![0](https://i.loli.net/2018/02/19/5a8af2c2ef8d7.gif)

这张图片显示了高速公路网中收费站的编号（在左上角）和控制费用。$1$ 号和 $4$ 号收费站组成了最小控制集，总控制费用为 $5$。

**数据范围**

对于 $40\%$ 的测试数据，$n\le 20$；

对于全部数据，$1\le n\le 200,1\le m \le 2\times 10^4$​​，$1 \le a,b \le n,a≠b$，$1\le c\le 10^7$​​，$1\le x<y\le n$。


---

---
title: "【模板】最小割树（Gomory-Hu Tree）"
layout: "post"
diff: 省选/NOI-
pid: P4897
tag: ['网络流', '深度优先搜索 DFS', '最小割']
---
# 【模板】最小割树（Gomory-Hu Tree）
## 题目背景

模板题。做本题之前请确保你会 Dinic 或 ISAP。如果你乱搞过了我请你抽烟。

根据惯例，网络流题不允许卡 Dinic/ISAP，但可以卡 EK，本题数据严格遵循上述条约。
## 题目描述

给定一个 $n$ 个点 $m$ 条边的无向连通图，多次询问两点之间的最小割。

两点间的最小割是这样定义的：原图的每条边有一个割断它的代价，你需要用最小的代价使得这两个点不连通。
## 输入格式

第一行两个数 $n,m$。

接下来 $m$ 行，每行 $3$ 个数 $u,v,w$，表示有一条连接 $u$ 与 $v$ 的无向边，割断它的代价为 $w$。

接下来这一行有一个整数$Q$，表示询问次数

接下来 $Q$ 行，每行两个数 $u,v$，你需要求出 $u$ 与 $v$ 之间的最小割

**注意：因为数据有误，给定图的真实点数应该是 $n+1$ 个，编号为 $0$ 到 $n$。**
## 输出格式

输出共 $Q$ 行，每行一个整数对应询问的答案
## 样例

### 样例输入 #1
```
4 5
1 2 2
2 3 2
4 2 3
4 3 1
1 3 1
3
1 4
2 4
2 3
```
### 样例输出 #1
```
3
4
4
```
## 提示

$1\le n\leq 500,\quad 0\le m\leq 1500,\quad 0\le Q\leq 10^5,\quad 0\leq w\leq 10^4,\quad u\neq v$


---

---
title: "[清华集训 2012] 最小生成树"
layout: "post"
diff: 省选/NOI-
pid: P5934
tag: ['2012', '网络流', '最小割', 'CTT（清华集训/北大集训）']
---
# [清华集训 2012] 最小生成树
## 题目描述

给定一个边带正权的连通无向图 $G=(V,E)$，其中 $N=|V|,M=|E|$，$N$ 个点从 $1$ 到 $N$ 依次编号，给定三个正整数 $u,v$ 和 $L(u\ne v)$，假设现在加入一条边权为 $L$ 的边 $(u,v)$，那么需要删掉最少多少条边，才能够使得这条边既可能出现在最小生成树上，也可能出现在最大生成树上？
## 输入格式

第一行包含用空格隔开的两个整数，分别为 $N$ 和 $M$；

接下来 $M$ 行，每行包含三个正整数 $u,v$ 和 $w$ 表示图 $G$ 存在一条边权为 $w$ 的边 $u,v$。

最后一行包含用空格隔开的三个整数，分别为 $u,v$ 和 $L$；

数据保证图中没有自环。
## 输出格式

输出一行一个整数表示最少需要删掉的边的数量。
## 样例

### 样例输入 #1
```
3 2
3 2 1
1 2 3
1 2 2

```
### 样例输出 #1
```
1
```
## 提示

#### 样例解释
我们只需把边 $(1,2)$ 删除即可，删除并加入新边之后，图中的生成树唯一。

#### 数据规模与约定
对于 $20\%$ 的数据满足 $N\leqslant10,M\leqslant20,L\leqslant20$；

对于 $50\%$ 的数据满足 $N\leqslant300,M\leqslant3000,L\leqslant200$；

对于 $100\%$ 的数据满足 $N\leqslant20000,M\leqslant200000,L\leqslant20000$。


---

---
title: "[RC-02] 开门大吉"
layout: "post"
diff: 省选/NOI-
pid: P6054
tag: ['网络流', 'Special Judge', 'O2优化', '最小割', '期望']
---
# [RC-02] 开门大吉
## 题目描述

$n$ 位选手去参加节目“开门大吉”。共有 $m$ 套题，每套题包含 $p$ 个题目，第 $i$ 位选手答对第 $j$ 套题中第 $k$ 道的概率为 $f_{i,j,k}$。

若一位选手答对第 $i$ 题，会在已得到奖励的基础上，再得到 $c_i$ 元奖励。选手总是从第一道开始，按顺序答题的。

同时，为了防止过多的选手做同一套题，还有 $y$ 条形如“第 $i$ 位选手的套题编号必须至少比第 $j$ 位的大 $k$”的限制。

你需要给每一位选手分配一套题（不同选手可以相同），使得所有人的期望奖励和最小。
## 输入格式

输入包含多组数据。第一行是一个整数 $T$，为数据组数。

对于每组数据，第一行四个整数 $n,m,p,y$。

接下来一行 $p$ 个整数，第 $i$ 个为 $c_i$。 

接下来 $m$ 个 $n\times p$ 的矩阵，第 $j$ 个矩阵中第 $i$ 行第 $k$ 个实数为 $f_{i,j,k}$。

接下来 $y$ 行，每行三个整数 $i,j,k$（$1\le i,j\le n$，$-m<k<m$），描述一条限制。
## 输出格式

对于每组数据，输出一个实数，为答案。无解输出 `-1`。

本题有 Special Judge，答案误差在 $5\times 10^{-4}$ 以内都算对。

由于 SPJ 敏感，请在每组数据末尾都输出一个换行符，并不要再输出其它字符。
## 样例

### 样例输入 #1
```
4
3 2 4 0
10 10 10 20
0.3 0.5 0.7 0.4
0.2 0.6 0.2 0.2
0.7 0.1 0.8 0.2
0.5 0.5 0.5 0.5
0.2 0.5 0.3 0.6
0.3 0.5 0.4 0.1
3 2 4 1
10 10 10 20
0.3 0.5 0.7 0.4
0.2 0.6 0.2 0.2
0.7 0.1 0.8 0.2
0.5 0.5 0.5 0.5
0.2 0.5 0.3 0.6
0.3 0.5 0.4 0.1
2 3 1
3 2 4 1
10 10 10 20
0.3 0.5 0.7 0.4
0.2 0.6 0.2 0.2
0.7 0.1 0.8 0.2
0.5 0.5 0.5 0.5
0.2 0.5 0.3 0.6
0.3 0.5 0.4 0.1
1 2 1
3 2 4 2
10 10 10 20
0.3 0.5 0.7 0.4
0.2 0.6 0.2 0.2
0.7 0.1 0.8 0.2
0.5 0.5 0.5 0.5
0.2 0.5 0.3 0.6
0.3 0.5 0.4 0.1
1 2 1
2 3 1
```
### 样例输出 #1
```
15.1460
18.5340
18.7560
-1
```
## 提示

【样例解释】

这里只解释第二组数据。

一共只有两套题，而第二个人的套题编号大于第三个人，因此第二个人一定是选第二套，第三个人选第一套。

第二个人选第二套，期望支出：$0.2\times (1-0.5)\times 10+0.2\times 0.5 \times (1-0.3) \times 20+0.2\times 0.5 \times 0.3\times (1-0.6)  \times 30+0.2\times 0.5 \times 0.3\times 0.6  \times 50=3.66$。

其他人的计算方法类似。

【数据范围】

**本题捆绑测试。**

对于所有数据，$1\le n,m,p\le 80$，$0\le y\le 10^3$，$0\le f_{i,j,k} \le 1$，$0\le c_i\le 10^5$，$1 \le T\le 50$。保证每个测试点的输入数据大小小于 $10\text{MB}$。

Subtask 1（20 pts）：$n,m,p,y\le 7$；

Subtask 2（20 pts）：$T\le 6$，$y=0$；

Subtask 3（20 pts）：$n,m,p\le 30$，$y\le 200$；

Subtask 4（20 pts）：$T=1$；

Subtask 5（20 pts）：$T\le 5$。


---

---
title: "[THUPC 2022 初赛] 分组作业"
layout: "post"
diff: 省选/NOI-
pid: P8215
tag: ['2022', 'O2优化', '最小割', 'THUPC']
---
# [THUPC 2022 初赛] 分组作业
## 题目描述

老师布置了分组作业。在此之前，老师将班上 $2n$ 个学生分成了 $n$ 组，每组两个人。其中 $1$ 号和 $2$ 号为一组，$3$ 号和 $4$ 号为一组，……，$2n-1$ 号和 $2n$ 号为一组。

老师让每个队伍自行安排分工。这样是否合作就成了一个大问题。大家决定用表决的方式来确定。首先每个人决定是否愿意和队友合作。不同的人因为自己的原因和分配的队友的原因，对合作的意愿不一样，对于第 $i$ 个学生，选择“愿意”会产生 $c_i$ 的不满，选择“不愿意”会产生 $d_i$ 的不满。

如果两名队友都选择“愿意”，那么根据实际情况他们可以合作或者不合作。但是如果有一名队友选择“不愿意”，那么他们只能不合作。

学生中还有 $m$ 个单向的喜欢关系，一个关系形如“$A$ 喜欢 $B$”。在这样一个关系中，如果 $A$ 没有和队友合作，且 $B$ 选择了“愿意”，$A$ 会有略微沮丧，产生 $a_i$ 的不满；如果 $A$ 表决了“不愿意”，但 $B$ 成功与队友合作，那么 $A$ 会羡慕嫉妒恨并产生 $b_i$ 的不满。（由于当 $A$ 和 $B$ 在同一组时这种设定会变得很奇怪，所以题目保证不会有这种情况）其中 $i$ 表示第 $i$ 个关系。

如果一个学生 $i$ 选择了“愿意”但是他的队友选择了“不愿意”，那么他会因为队友产生 $e_i$ 的不满。

问所有情况下最小的不满之和是多少。
## 输入格式

第一行两个整数 $n,m$。

接下来 $2n$ 行，每行三个整数 $c_i,d_i,e_i$。

接下来 $m$ 行，每行四个正整数 $A,B,a_i,b_i$ 。
## 输出格式

一行一个整数表示答案。
## 样例

### 样例输入 #1
```
2 1
8 6 7
5 2 8
7 1 5
6 5 8
1 4 4 3
```
### 样例输出 #1
```
14
```
## 提示

【数据范围】

保证 $1\le n \le 5000$，$0\le m \le 10000$，$1\le a_i,b_i,c_i,d_i,e_i\le 10^9$。


---

