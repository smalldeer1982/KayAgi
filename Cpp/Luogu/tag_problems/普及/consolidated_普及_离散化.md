---
title: "逆序对"
layout: "post"
diff: 普及/提高-
pid: P1908
tag: ['树状数组', '递归', '离散化', '排序']
---
# 逆序对
## 题目描述

猫猫 TOM 和小老鼠 JERRY 最近又较量上了，但是毕竟都是成年人，他们已经不喜欢再玩那种你追我赶的游戏，现在他们喜欢玩统计。

最近，TOM 老猫查阅到一个人类称之为“逆序对”的东西，这东西是这样定义的：对于给定的一段正整数序列，逆序对就是序列中 $a_i>a_j$ 且 $i<j$ 的有序对。知道这概念后，他们就比赛谁先算出给定的一段正整数序列中逆序对的数目。注意序列中可能有重复数字。

**Update：数据已加强。**
## 输入格式

第一行，一个数 $n$，表示序列中有 $n$ 个数。

第二行 $n$ 个数，表示给定的序列。序列中每个数字不超过 $10^9$。

## 输出格式

输出序列中逆序对的数目。

## 样例

### 样例输入 #1
```
6
5 4 2 6 3 1

```
### 样例输出 #1
```
11
```
## 提示

对于 $25\%$ 的数据，$n \leq 2500$。

对于 $50\%$ 的数据，$n \leq 4 \times 10^4$。

对于所有数据，$1 \leq n \leq 5 \times 10^5$。

请使用较快的输入输出。

应该不会有人 $O(n^2)$ 过 50 万吧 —— 2018.8 chen_zhe。


---

---
title: "二进制"
layout: "post"
diff: 普及/提高-
pid: P2104
tag: ['模拟', '字符串', '离散化']
---
# 二进制
## 题目描述

小 Z 最近学会了二进制数，他觉得太小的二进制数太没意思，于是他想对一个巨大二进制数做以下 $4$ 种基础运算：

运算 $1$：将整个二进制数加 $1$。

运算 $2$：将整个二进制数减 $1$。

运算 $3$：将整个二进制数乘 $2$。

运算 $4$：将整个二进制数整除 $2$。

小 Z 很想知道运算后的结果，他只好向你求助。

（Ps：为了简化问题，数据保证 `+`，`-` 操作不会导致最高位的进位与退位）
## 输入格式

第一行两个正整数 $n,m$，表示原二进制数的长度以及运算数。

接下来一行 $n$ 个字符，分别为 `0` 或 `1` 表示这个二进制数。

第三行 $m$ 个字符，分别为 `+`，`-`，`*`，`/`，对应运算 $1,2,3,4$。
## 输出格式

一行若干个字符，表示经过运算后的二进制数。

## 样例

### 样例输入 #1
```
4 10
1101
*/-*-*-/*/
```
### 样例输出 #1
```
10110
```
## 提示


对于 $30\%$ 的数据，$1 \leq n,m \leq 1000$。

对于 $60\%$ 的数据，$1 \leq n,m \leq 10^5$。

对于 $100\%$ 的数据，$1 \leq n,m \leq 5 \times 10^6$。


---

---
title: "[HAOI2012] 容易题"
layout: "post"
diff: 普及/提高-
pid: P2220
tag: ['数学', '2012', '河南', '各省省选', '离散化']
---
# [HAOI2012] 容易题
## 题目描述

有一个长度为 $m$ 的正整数数列 $A$，满足 $\forall i \in A, i \in [1, n]$。

现在给定一些限制（$A_x$ 不能为 $y$）。设数列 $A$ 的积为 $\prod A$，求所有可能数列的积相加起来的和。

换言之，令 $S$ 为所有可能的数列情况 $\{A, A', \ldots\}$，求

$$ \sum_{T \in S} \prod T $$

答案对 $10 ^ 9 + 7$ 取模。
## 输入格式

第一行三个正整数 $n, m, k$。$n, m$ 如题目所示，$k$ 表示限制的条数。

接下来 $k$ 行，每行两个正整数 $x, y$ 表示限制 $A_x \neq y$。

## 输出格式

一行一个正整数表示答案。

如果没有任何合法数列，输出 $0$。

## 样例

### 样例输入 #1
```
3 4 5

1 1

1 1

2 2

2 3

4 3


```
### 样例输出 #1
```
90
```
## 提示

### 样例解释 #1

$A_1$ 不能取 $1$，$A_2$ 不能取 $2, 3$，$A_4$ 不能取 $3$，所以可能的数列有以下 $12$ 种：

| 数列 | 积 |
| :-: | :-: |
| $\{2,   1,   1,   1\}$           | $2$ |
| $\{2,   1,   1,   2\}$           | $4$ |
| $\{2,   1,   2,   1\}$           | $4$ |
| $\{2,   1,   2,   2\}$           | $8$ |
| $\{2,   1,   3,   1\}$           | $6$ |
| $\{2,   1,   3,   2\}$           | $12$ |
| $\{3,   1,   1,   1\}$           | $3$ |
| $\{3,   1,   1,   2\}$           | $6$ |
| $\{3,   1,   2,   1\}$           | $6$ |
| $\{3,   1,   2,   2\}$           | $12$ |
| $\{3,   1,   3,   1\}$           | $9$ |
| $\{3,   1,   3,   2\}$           | $18$ |


### 数据范围

对于 $30\%$ 的数据，$n \leq 4$，$m \leq 10$，$k \leq 10$。

对于另外 $20\%$ 的数据，$k = 0$。

对于 $70\%$ 的数据，$n, m, k \leq 1000$。

对于 $100\%$ 的数据，$1\leq n, m \leq 10^9$，$0\leq k \leq 10^5$，$1 \leq x \leq m$，$1 \leq y \leq n$。


---

---
title: "[USACO11NOV] Cow Lineup S"
layout: "post"
diff: 普及/提高-
pid: P3029
tag: ['2011', 'USACO', '单调队列', '离散化', '队列', '双指针 two-pointer']
---
# [USACO11NOV] Cow Lineup S
## 题目描述

Farmer John has hired a professional photographer to take a picture of some of his cows.  Since FJ's cows represent a variety of different breeds, he would like the photo to contain at least one cow from each distinct breed present in his herd.

FJ's N cows are all standing at various positions along a line, each described by an integer position (i.e., its x coordinate) as well as an integer breed ID.  FJ plans to take a photograph of a contiguous range of cows along the line.  The cost of this photograph is equal its size -- that is, the difference between the maximum and minimum x coordinates of the cows in the range of the photograph.

Please help FJ by computing the minimum cost of a photograph in which there is at least one cow of each distinct breed appearing in FJ's herd.

## 输入格式

\* Line 1: The number of cows, N (1 <= N <= 50,000). 

\* Lines 2..1+N: Each line contains two space-separated positive integers specifying the x coordinate and breed ID of a single cow.  Both numbers are at most 1 billion.

## 输出格式

\* Line 1: The smallest cost of a photograph containing each distinct breed ID.

## 样例

### 样例输入 #1
```
6 
25 7 
26 1 
15 1 
22 3 
20 1 
30 1 

```
### 样例输出 #1
```
4 

```
## 提示

There are 6 cows, at positions 25,26,15,22,20,30, with respective breed IDs 7,1,1,3,1,1.


The range from x=22 up through x=26 (of total size 4) contains each of the distinct breed IDs 1, 3, and 7 represented in FJ's herd.

## 题目翻译

### 问题描述

农民约翰雇一个专业摄影师给他的部分牛拍照。由于约翰的牛有好多品种，他喜欢他的照片包含每个品种的至少一头牛。

约翰的牛都站在一条沿线的不同地方， 每一头牛由一个整数位置 $X_i$ 以及整数品种编号 $ID_i$ 表示。

约翰想拍一张照片，这照片由沿线的奶牛的连续范围组成。照片的成本与规模相当，这就意味着，在一系列照片中的最大和最小 $X$ 坐标的差距决定了照片的成本。

请帮助约翰计算最小的照片成本，这些照片中有每个不同的品种的至少一头牛，没有两头牛愿意站在同一个地点的。


### 输入格式 


第 $1$ 行：牛的数量 $N$；


第 $2..1+N$ 行：每行包含 2 个以空格分隔的正整数 $X_i$ 和 $ID_i$；意义如题目描述；


### 输出格式 


输出共一行，包含每个不同品种 $\rm ID$ 的照片的最低成本。


---

---
title: "[USACO17OPEN] Bovine Genomics S"
layout: "post"
diff: 普及/提高-
pid: P3670
tag: ['2017', 'USACO', '离散化', '枚举']
---
# [USACO17OPEN] Bovine Genomics S
## 题目描述

Farmer John owns $N$ cows with spots and $N$ cows without spots. Having just completed a course in bovine genetics, he is convinced that the spots on his cows are caused by mutations in the bovine genome.


At great expense, Farmer John sequences the genomes of his cows. Each genome is a string of length $M$ built from the four characters A, C, G, and T. When he lines up the genomes of his cows, he gets a table like the following, shown here


for $N=3$:


```cpp
Positions: 1 2 3 4 5 6 7 ... M

Spotty Cow 1: A A T C C C A ... T
Spotty Cow 2: G A T T G C A ... A
Spotty Cow 3: G G T C G C A ... A

Plain Cow 1: A C T C C C A ... G
Plain Cow 2: A G T T G C A ... T
Plain Cow 3: A G T T C C A ... T
```

Looking carefully at this table, he surmises that positions 2 and 4 are sufficient to explain spottiness. That is, by looking at the characters in just these two positions, Farmer John can predict which of his cows are spotty and which are not (for example, if he sees G and C, the cow must be spotty).


Farmer John is convinced that spottiness can be explained not by just one or two positions in the genome, but by looking at a set of three distinct positions.  Please help him count the number of sets of three distinct positions that can each explain spottiness.
## 输入格式

The first line of input contains $N$ ($1 \leq N \leq 500$) and $M$ ($3 \leq M \leq 50$). The next $N$ lines each contain a string of $M$ characters; these describe the genomes of the spotty cows. The final $N$ lines describe the genomes of the plain cows.

## 输出格式

Please count the number of sets of three distinct positions that can explain spottiness. A set of three positions explains spottiness if the spottiness trait can be predicted with perfect accuracy among Farmer John's population of cows by looking at just those three locations in the genome.

## 样例

### 样例输入 #1
```
3 8
AATCCCAT
GATTGCAA
GGTCGCAA
ACTCCCAG
ACTCGCAT
ACTTCCAT
```
### 样例输出 #1
```
22
```
## 题目翻译

### 题目描述

Farmer John 拥有 $N$ 头有斑点的牛和 $N$ 头没有斑点的牛。他刚刚完成了一门关于牛遗传学的课程，并确信他牛身上的斑点是由牛基因组中的突变引起的。

Farmer John 花费巨资对他的牛进行了基因组测序。每个基因组是一个由字符 A、C、G 和 T 组成的长度为 $M$ 的字符串。当他将牛的基因组排列起来时，会得到如下表格，这里展示的是 $N=3$ 的情况：

```
位置：1 2 3 4 5 6 7 ... M

斑点牛 1：A A T C C C A ... T  
斑点牛 2：G A T T G C A ... A  
斑点牛 3：G G T C G C A ... A  

普通牛 1：A C T C C C A ... G  
普通牛 2：A G T T G C A ... T  
普通牛 3：A G T T C C A ... T 
```

仔细观察这个表格后，他推测位置 2 和 4 足以解释斑点现象。也就是说，通过仅查看这两个位置的字符，Farmer John 可以预测哪些牛是有斑点的，哪些是没有斑点的（例如，如果他看到 G 和 C，这头牛一定是有斑点的）。

Farmer John 确信，斑点现象不仅仅可以通过基因组中的一个或两个位置来解释，而是可以通过查看三个不同的位置来解释。请帮助他计算能够解释斑点现象的三个不同位置集合的数量。

### 输入格式

输入的第一行包含 $N$（$1 \leq N \leq 500$）和 $M$（$3 \leq M \leq 50$）。接下来的 $N$ 行每行包含一个长度为 $M$ 的字符串，这些字符串描述了斑点牛的基因组。最后的 $N$ 行描述了普通牛的基因组。

### 输出格式

请计算能够解释斑点现象的三个不同位置集合的数量。如果通过查看基因组中这三个位置的字符，可以在 Farmer John 的牛群中完美准确地预测斑点性状，那么这个三个位置的集合就解释了斑点现象。


---

---
title: "递增"
layout: "post"
diff: 普及/提高-
pid: P3902
tag: ['动态规划 DP', '二分', '树状数组', '离散化']
---
# 递增
## 题目描述

现有数 $A_1,A_2,\cdots,A_n$，修改最少的数字为**实数**，使得数列严格单调递增。

注：原题误表述为修改为整数，现已纠正为实数。本题数据确保按照修改为整数的做法也可以 AC（只是不能过样例）
## 输入格式

第一行，一个整数 $n$。

第二行，$n$ 个整数$A_1,A_2,\cdots,A_n$

## 输出格式

1 个整数，表示最少修改多少个数字

## 样例

### 样例输入 #1
```
3
1 3 2
```
### 样例输出 #1
```
1
```
### 样例输入 #2
```
8
1 2 3 4 4 5 6 7
```
### 样例输出 #2
```
1
```
## 提示

• 对于50% 的数据，$N \le 10^3$

• 对于100% 的数据，$1 \le N \le 10^5 , 1 \le A_i \le 10^9$



---

---
title: "[CCC 2021 S3] Lunch Concert"
layout: "post"
diff: 普及/提高-
pid: P9025
tag: ['数学', '2021', '离散化', 'CCC（加拿大）']
---
# [CCC 2021 S3] Lunch Concert
## 题目描述

有 $N$ 个人，第 $i$ 个人的速度为 $W_i$ **秒每米**，听力为 $D_i$，即能听见距离他不超过 $D_i$ 米处的音乐，初始在 $P_i$ 位置。

你要在 $c$ 位置处开音乐会，这个 $c$ 由你决定且为整数。这 $N$ 个人都会靠近你直到能听到你。你要最小化每个人移动的时间之和。
## 输入格式

第一行：$N$。

接下来的 $N$ 行，每行依次包含 $P_i,W_i,D_i$。
## 输出格式

一个整数：每个人移动的时间之和的最小值。（注意：答案可能超过 $2^{32}$）
## 样例

### 样例输入 #1
```
1
0 1000 0

```
### 样例输出 #1
```
0
```
### 样例输入 #2
```
2
10 4 3
20 4 2

```
### 样例输出 #2
```
20
```
### 样例输入 #3
```
3
6 8 3
1 4 1
14 5 2

```
### 样例输出 #3
```
43
```
## 提示

$$1\leq N\leq 200000,0\leq P_i\leq 10^9,1\leq W_i\leq 1000,0\leq D_i\leq 10^9$$

译自 [CCC2021 S3](https://cemc.math.uwaterloo.ca/contests/computing/past_ccc_contests/2021/ccc/seniorEF.pdf)。

###### 2023.8.10 新增一组 hack 数据。


---

