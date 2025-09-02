---
title: "[LSOT-2] Tree and Xor"
layout: "post"
diff: 省选/NOI-
pid: P10157
tag: ['数学', '贪心', '二分', '位运算', 'Ad-hoc', '分类讨论']
---
# [LSOT-2] Tree and Xor
## 题目描述

给定 $n$，你需要构造一棵 $n$ 个点的以 $1$ 为根的有根树，满足 $\bigoplus\limits_{i=1}^ndegree(i)=0$ 且 $fa_2 \sim fa_n$ 的字典序最小。其中，$\oplus$ 表示异或运算。

其中 $degree(i)$ 表示与点 $i$ 相连的点数，$fa_i$ 表示点 $i$ 的父节点且 $fa_i < i$。

你需要输出 $\sum\limits_{i=2}^ni \times fa_i$，若无解则输出 $-1$。
## 输入格式

第一行，一个正整数 $T$，表示询问数量。

接下来每 $T$ 行每行一个正整数 $n$ 表示一次询问。
## 输出格式

一共 $T$ 行，每行一个整数表示答案除 $998244353$ 的余数。
## 样例

### 样例输入 #1
```
2
2
3
```
### 样例输出 #1
```
2
-1
```
## 提示

**「本题采用捆绑测试」**

- $\texttt{Subtask 1(5 pts)：}n \leq 7$。
- $\texttt{Subtask 2(10 pts)：} n \leq 20$。
- $\texttt{Subtask 3(20 pts)：}\sum n \leq 2000$。
- $\texttt{Subtask 4(15 pts)：}n = 2^k-1$，其中 $k$ 是自然数。
- $\texttt{Subtask 5(50 pts)：}$无特殊限制。

对于所有数据，$1\le T\le 10^6$，$2 \leq n \leq 10^{9}$。


---

---
title: "「HOI R1」杂造选构"
layout: "post"
diff: 省选/NOI-
pid: P10382
tag: ['2024', 'Special Judge', 'O2优化', '构造', 'Ad-hoc', '分类讨论', '洛谷比赛']
---
# 「HOI R1」杂造选构
## 题目背景

小 $\iiint$ 跟这个烦人的构造没有任何关系。
## 题目描述

若一个序列 $a$ 满足以下要求：

- $a_i=-1$ 或 $a_i\in [1,n]$。
- 对于每个 $a_i\not=-1$，将 $a_i\to i$ 连边而形成的图不存在环。

则称这个序列是合法的。

现给定整数 $x$ 与序列 $a$，满足序列 $a$ 所有元素是 $[-1,n]$ 范围内的整数。请你将所有 $a_i=0$ 的位置替换成其他整数，使得 $\sum\limits ^{n} _{i=1} a_i = x$ 且 $a$ 是合法的。若不存在这样一种方案，则报告无解。
## 输入格式

第一行两个整数 $n$ 和 $x$。

第二行 $n$ 个整数，表示 $a$ 序列。保证 $\forall a_i \in [-1,n]$。
## 输出格式

若无解，则说明你被骗了，因此输出一个字符串 `Rick`。否则输出 $n$ 个整数，表示替换完所有为 $0$ 的元素后的 $a$ 序列。
## 样例

### 样例输入 #1
```
6 -6
-1 -1 -1 0 0 0
```
### 样例输出 #1
```
-1 -1 -1 -1 -1 -1
```
### 样例输入 #2
```
6 14
0 1 4 0 1 4
```
### 样例输出 #2
```
-1 1 4 5 1 4
```
### 样例输入 #3
```
6 10
0 0 0 0 0 0
```
### 样例输出 #3
```
-1 -1 4 5 -1 4
```
### 样例输入 #4
```
6 6
1 1 0 0 0 0
```
### 样例输出 #4
```
Rick
```
### 样例输入 #5
```
6 40
0 0 0 0 0 0
```
### 样例输出 #5
```
Rick
```
## 提示

**本题开启捆绑测试。**

| Subtask | 分值 | $n \le$ | $x \le$ |特殊性质 |
| :----------: | :----------: | :----------: | :----------: | :----------: |
| #0 | $13$ | $15$ | $225$|无|
| #1 | $24$ | $10^3$ | $10^9$|无|
| #2 | $27$ | $10^5$ | $10^{18}$|有|
| #3 | $36$ | $10^5$ | $10^{18}$|无|

*特殊性质：保证 $\forall a_i =0$。

对于所有数据，满足 $1 \le n \le 10^5,-10^{18} \le x \le 10^{18}$。

***

**Special Judge 返回值对应表**

- `Accepted.` 答案正确。
- `Oops, your answer is wrong. 1` 答案为无解，选手代码输出有解。
- `Oops, your answer is wrong. 2` 选手输出的 $\sum a_i \not = x$。
- `Oops, your answer is wrong. 3` 选手输出中含有 $0$。
- `Oops, your answer is wrong. 4` 选手输出中含有环。
- `Oops, your answer is wrong. 5` 选手输出在填空的同时将输入的 $a_i \not=0$ 的位置改动了。


---

---
title: "【MX-X7-T6】[LSOT-3] 棋盘"
layout: "post"
diff: 省选/NOI-
pid: P11565
tag: ['动态规划 DP', '博弈论', 'O2优化', 'Ad-hoc', '分类讨论', '梦熊比赛']
---
# 【MX-X7-T6】[LSOT-3] 棋盘
## 题目背景

原题链接：<https://oier.team/problems/X7G>。

现在有一个序列。

这个序列第 $1$ 项为 $0$，第 $2$ 项为 $1$，第 $3$ 项为 $1$，第 $4$ 项为 $3$。

现在 [@lxwtr](https://www.luogu.com.cn/discuss/875194) 问你第 $n$ 项的值为多少。
## 题目描述

Alice 和 Bob 找到了一个棋盘。棋盘可以看成一个数轴，初始时在原点处有 $n$ 个棋子。令 $a_i$ 表示数轴下标为 $i$ 的位置的棋子数量（原点 $i=0$），操作者每次会找到最小的满足 $a_i\ge 2$ 的 $i$，令 $a_i$ 减去 $2$ 并选择令 $a_{i+1}$ 加上 $1$ 或令 $a_{i+2}$ 加上 $1$。由 Alice 先手，二人轮流操作。操作者必须操作，如果无法找到这样的 $i$ 则立即结束游戏。

Alice 希望二人的总操作次数最少，Bob 希望二人的总操作次数最多，二人都是绝对聪明的。二人一共进行了 $T$ 次游戏，你希望知道每次游戏最终二人一共会进行多少次操作。
## 输入格式

第一行，一个正整数 $T$，表示进行的游戏次数。

接下来 $T$ 行，每行一个正整数 $n$，表示每次游戏开始时，原点的棋子个数。
## 输出格式

共 $T$ 行，第 $i$ 行一个非负整数，表示第 $i$ 次游戏最终二人一共会进行多少次操作。
## 样例

### 样例输入 #1
```
6
1
2
3
4
100
100000

```
### 样例输出 #1
```
0
1
1
3
95
99989

```
## 提示

**【样例解释】**

对于第一次游戏，原点棋子数为 $1$，无法进行操作。

对于第二次游戏，可以恰好进行一次操作之后使得 $a_1=1$ 或 $a_2=1$。无论哪一种都无法继续操作。

对于第三次游戏，类似第二次游戏，额外在原点留下了一个棋子。

对于第四次游戏，第一次操作无论 Alice 操作后将棋子放在哪个位置，Bob 都可以放在那个位置，这样 Alice 会再进行一次操作。总共 $3$ 次操作。

**【数据范围】**

**本题采用捆绑测试。**

- 子任务 1（5 分）：$n\le16$。
- 子任务 2（6 分）：$n\le 50$。
- 子任务 3（14 分）：$n\le 200$。
- 子任务 4（20 分）：$n\le 5000$。
- 子任务 5（21 分）：$n\le 10^5$。
- 子任务 6（34 分）：无特殊性质。

对于全部的数据，$1\le T\le 500$，$1\le n\le 10^{18}$。


---

---
title: "[USACO25FEB] Min Max Subarrays P"
layout: "post"
diff: 省选/NOI-
pid: P11845
tag: ['二分', 'USACO', '2025', '分类讨论', '单调栈']
---
# [USACO25FEB] Min Max Subarrays P
## 题目描述

**注意：本题的时间限制为 3 秒，通常限制的 1.5 倍。**

给定一个长为 $N$ 的整数数组 $a_1,a_2,\dots,a_N$（$2\le N \le 10^6$，$1\le a_i\le N$)。输出所有 $N(N+1)/2$ 个 $a$ 的连续子数组的以下子问题的答案之和。

给定一个非空整数列表，交替执行以下操作（从第一个操作开始）直到列表大小恰好为一。

1. 将列表内的两个相邻整数替换为它们的较小值。
1. 将列表内的两个相邻整数替换为它们的较大值。

求最终余下的整数的最大可能值。

例如，

$[4, 10, 3] \to [4, 3] \to [4]$

$[3, 4, 10] \to [3, 10] \to [10]$

在第一个数组中，$(10, 3)$ 被替换为 $\min(10, 3)=3$，随后 $(4, 3)$ 被替换为 $\max(4, 3)=4$。

## 输入格式

输入的第一行包含 $N$。

第二行包含 $a_1,a_2,\dots,a_N$。
## 输出格式

输出所有连续子数组的子问题的答案之和。

## 样例

### 样例输入 #1
```
2
2 1
```
### 样例输出 #1
```
4
```
### 样例输入 #2
```
3
3 1 3
```
### 样例输出 #2
```
12
```
### 样例输入 #3
```
4
2 4 1 3
```
### 样例输出 #3
```
22
```
## 提示

样例 1 解释：

对于 $[2]$ 答案为 $2$，对于 $[1]$ 答案为 $1$，对于 $[2, 1]$ 答案为 $1$。

因此，我们的输出应当为 $2+1+1 = 4$。

样例 3 解释：

考虑子数组 $[2, 4, 1, 3]$。


1. 在 $(1, 3)$ 上应用第一次操作，我们的新数组是 $[2, 4, 1]$。
1. 在 $(4, 1)$ 上应用第二次操作，我们的新数组是 $[2, 4]$。
1. 在 $(2, 4)$ 上应用第三次操作，我们最终的数是 $2$。

可以证明 $2$ 是最终的数的最大可能值。

- 测试点 $4\sim 5$：$N\le 100$。
- 测试点 $6\sim 7$：$N\le 5000$。
- 测试点 $8\sim 9$：$\max(a)\le 10$。
- 测试点 $10\sim 13$：没有额外限制。


---

---
title: "[GCJ 2014 #3] Crime House"
layout: "post"
diff: 省选/NOI-
pid: P13262
tag: ['贪心', '2014', '二分', '分类讨论', 'Google Code Jam']
---
# [GCJ 2014 #3] Crime House
## 题目描述

While working for the police, you've identified a house where people go to commit crimes, called Crime House. One day, you set up a camera over the door of the house and record a video.

You don't know how many people were in Crime House at the start of the day, but you can see people enter and leave through the front door. Unfortunately, because the people entering and leaving Crime House are criminals, sometimes they wear masks; and you aren't quite sure if the front door is the only way in or out.

Sometimes you can guess who was wearing a mask. If criminal #5 entered the house, then someone wearing a mask left, then criminal #5 entered the house again, then either the person wearing the mask was criminal #5, or there is another way out of Crime House.

At the end of the day, when Crime House has closed its doors for the night, you watch your video. Because you're an optimist, you want to figure out if it's possible that there are no other entrances or exits from crime house; and if so, you want to figure out the minimum number of people who could be in Crime House at the end of the day.
## 输入格式

The first line of the input gives the number of test cases, $\mathbf{T}$. $\mathbf{T}$ test cases follow. Each test case starts with a line containing a single integer $\mathbf{N}$, the number of times people pass through the front door of Crime House in the day. Next follows $\mathbf{N}$ lines, each of which contains information about one person entering or leaving Crime House through the front door.

That information consists of a single character, $\mathbf{E}$ or $\mathbf{L}$, followed by a space and then an integer $\mathbf{i d}$. If the first character is $\mathbf{E}$, that indicates someone entered Crime House through the front door; if it's $\mathbf{L}$, someone left through the front door. If $\mathbf{i d}$ is greater than zero, the person with that identifier entered or left Crime House. If $\mathbf{i d}$ is zero, then the person who entered or left Crime House was wearing a mask, and we don't know who he or she was.

## 输出格式

For each test case, output one line containing "Case #x: $y$", where $\mathrm{x}$ is the test case number (starting from 1). If it's possible that there are no other entrances or exits from Crime House, then $y$ should be the minimum number of people who could be in Crime House at the end of the day. If that's impossible, $y$ should be "CRIME TIME".
## 样例

### 样例输入 #1
```
5
3
E 5
L 0
E 5
2
L 1
L 1
4
L 1
E 0
E 0
L 1
7
L 2
E 0
E 1
E 2
E 0
E 3
L 4
13
L 4
L 1
L 2
E 0
L 1
E 0
L 2
E 0
L 2
E 0
E 0
L 1
L 4
```
### 样例输出 #1
```
Case #1: 1
Case #2: CRIME TIME
Case #3: 1
Case #4: 4
Case #5: 0
```
## 提示

**Limits**

- $1 \leq \mathbf{T} \leq 100 .$
- $0 \leq \text {id} \leq 2000 .$

**Small dataset(12 Pts)**

- Time limit: ~~60~~ 3 seconds.
- $1 \leq \mathbf{N} \leq 15 .$

**Large dataset(22 Pts)**

- Time limit: ~~120~~ 10 seconds.
- $1 \leq \mathbf{N} \leq 1000$


---

---
title: "[GCJ 2012 Finals] Xeno-archaeology"
layout: "post"
diff: 省选/NOI-
pid: P13334
tag: ['数学', '2012', '扫描线', '分类讨论', 'Google Code Jam']
---
# [GCJ 2012 Finals] Xeno-archaeology
## 题目描述

Long ago, an alien civilization built a giant monument. The floor of the monument looked like this:

```
###############
#.............#
#.###########.#
#.#.........#.#
#.#.#######.#.#
#.#.#.....#.#.#
#.#.#.###.#.#.#
#.#.#.#.#.#.#.#
#.#.#.###.#.#.#
#.#.#.....#.#.#
#.#.#######.#.#
#.#.........#.#
#.###########.#
#.............#
###############
```

Each '#' represents a red tile, and each '.' represents a blue tile. The pattern went on for miles and miles (you may, for the purposes of the problem, assume it was infinite). Today, only a few of the tiles remain. The rest have been damaged by methane rain and dust storms. Given the locations and colours of the remaining tiles, can you find the center of the pattern?
## 输入格式

The first line of the input gives the number of test cases, $T$. $T$ test cases follow. Each one starts with a line containing $N$, the number of remaining tiles. The next $N$ lines each contain $X_i$, $Y_i$, and the tile colour (either '#' or '.').

## 输出格式

For each test case, output one line containing "Case #$c$: $X$ $Y$", where $c$ is the case number (starting from 1) and ($X$, $Y$) is the location of the center of the pattern. If there is more than one possible answer, output the ($X$, $Y$) closest to (0, 0) in Manhattan distance (the distance in $x$, plus the distance in $y$). If there are still ties, output the one with the largest $X$. If there are still ties after that, output the one with the largest $Y$. If there is no possible answer, output "Case #$c$: Too damaged".
## 样例

### 样例输入 #1
```
6
1
0 0 .
1
0 0 #
3
0 0 #
0 1 #
1 0 #
5
50 30 #
49 30 #
49 31 #
49 32 #
50 32 #
2
-98 0 #
99 50 .
4
88 88 .
88 89 .
89 88 .
89 89 .
```
### 样例输出 #1
```
Case #1: 0 0
Case #2: 1 0
Case #3: 1 1
Case #4: 50 31
Case #5: 1 0
Case #6: Too damaged
```
## 提示

**Limits**

- $1 \leq T \leq 50.$
- The list of coordinates in each test case will not contain duplicates.

**Test set 1 (12 Pts, Visible Verdict)**

- $1 \leq N \leq 100.$
- $-100 \leq X_i \leq 100.$
- $-100 \leq Y_i \leq 100.$

**Test set 2 (33 Pts, Hidden Verdict)**

- $1 \leq N \leq 1000.$
- $-10^{15} \leq X_i \leq 10^{15}.$
- $-10^{15} \leq Y_i \leq 10^{15}.$


---

---
title: "[USACO16DEC] Lots of Triangles P"
layout: "post"
diff: 省选/NOI-
pid: P1715
tag: ['计算几何', '2016', 'USACO', '容斥原理', '分类讨论']
---
# [USACO16DEC] Lots of Triangles P
## 题目描述

Farmer John is thinking of selling some of his land to earn a bit of extra income. His property contains $N$ trees ($3 \leq N \leq 300$), each described by a point in the 2D plane, no three of which are collinear. FJ is thinking about selling triangular lots of land defined by having trees at their vertices; there are of course $L = \binom{N}{3}$ such lots he can consider, based on all possible triples of trees on his property.

A triangular lot has value $v$ if it contains exactly $v$ trees in its interior (the trees on the corners do not count, and note that there are no trees on the boundaries since no three trees are collinear). For every $v = 0 \ldots N-3$, please help FJ determine how many of his $L$ potential lots have value $v$.
## 输入格式

The first line of input contains $N$.

The following $N$ lines contain the $x$ and $y$ coordinates of a single tree; these are both integers in the range $0 \ldots 1,000,000$.
## 输出格式

Output $N-2$ lines, where output line $i$ contains a count of the number of lots having value $i-1$.
## 样例

### 样例输入 #1
```
7
3 6
17 15
13 15
6 12
9 1
2 7
10 19
```
### 样例输出 #1
```
28
6
1
0
0
```
## 题目翻译

### 题目描述

Farmer John 正在考虑出售他的一部分土地以赚取一些额外收入。他的财产包含 $N$ 棵树（$3 \leq N \leq 300$），每棵树由二维平面中的一个点描述，且任意三棵树不共线。FJ 正在考虑出售由三棵树作为顶点定义的三角形地块；显然，他可以考虑的此类地块数量为 $L = \binom{N}{3}$，基于他财产中所有可能的三棵树组合。

一个三角形地块的价值为 $v$，如果它的内部恰好包含 $v$ 棵树（顶点上的树不计入，且由于没有三棵树共线，边界上也没有树）。对于每个 $v = 0 \ldots N-3$，请帮助 FJ 确定他的 $L$ 个潜在地块中有多少个地块的价值为 $v$。

### 输入格式

输入的第一行包含 $N$。

接下来的 $N$ 行每行包含一棵树的 $x$ 和 $y$ 坐标；这些坐标都是 $0 \ldots 1,000,000$ 范围内的整数。

### 输出格式

输出 $N-2$ 行，其中第 $i$ 行输出价值为 $i-1$ 的地块数量。


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

---
title: "[ICPC 2022 Xi'an R] Power of Two"
layout: "post"
diff: 省选/NOI-
pid: P9365
tag: ['2022', 'Special Judge', 'O2优化', '构造', 'ICPC', '分类讨论']
---
# [ICPC 2022 Xi'an R] Power of Two
## 题目描述

$$
2 ^ {2 ^ {2 ^ {2 ^ {2 ^ {2 ^ {2 ^ {2 ^ {2 ^ {2}}}}}}}}}
$$

SolarPea likes blowing up PolarSea's blog by sending power tower of $2$. As the tower is too high, the stack of the web page overflows. So the blog no longer works.

Now SolarPea has $n$ powers of two $a_1, a_2, \ldots, a_n$, $x$ bitwise AND operators, $y$ bitwise OR operators and $z$ bitwise XOR operators. It is guaranteed that $n = x + y + z$.

Solarpea wants to construct an arithmetic expression with these numbers and operators. Formally, define $x_0 = 0$ and $x_i = x_{i - 1}\ \mathrm{op}_i\ b_i$, where $b$ is a permutation of $a$, which means we can rearrange $a$ to get $b$, and $\mathrm{op}_i$ is one of the three types of bitwise operators above. Then $x_n$ is the result of the expresstion.

The larger the expression, the more likely it is to make PolarSea's blog unable to work. SolarPea wants you to help him to find the largest $x_n$ and construct such an expression. If there are multiple solutions, output any of them.

You need to process $T$ test cases independently.
## 输入格式

The first line contains a single integer $T$ ($1\leq T \leq 10 ^ 5$), denoting the number of test cases.

For each test case, the first line contains four integers $n$, $x$, $y$ and $z$ ($0\leq x, y, z\leq n \leq 65\,536, n = x + y + z$). The next line contains $n$ integers $c_1, c_2, \ldots, c_n$ ($0\leq c_i < n$), where $a_i = 2 ^ {c_i}$.

It is guaranteed that the sum of $n$ over all test cases is no more than $1\,048\,576$.
## 输出格式

For each test case, output three lines.

The first line contains a $01$-string of length $n$, representing the binary form of the largest $x_n$.

The next line contains a single $1$-indexed string $\mathrm{op}$ of length $n$, where $\mathrm{op}_i$ represents the $i$-th operator. Here, we denote AND as `&` (ASCII 38), OR as `|` (ASCII 124), and XOR as `^` (ASCII 94). You should guarantee that there is exactly $x$ AND operators, $y$ OR operators and $z$ XOR operators.

The third line contains $n$ integers $d_1, d_2, \ldots, d_n$, the $i$-th of which representing the logarithm of $b_i$ with base $2$. That is, $d$ is a permutaion of $c$.

If there are multiple solutions, output any of them.
## 样例

### 样例输入 #1
```
4
4 3 0 1
1 0 1 0
4 1 0 3
1 0 1 0
8 0 2 6
1 5 5 7 1 5 5 7
8 0 0 8
1 5 5 7 1 5 5 7

```
### 样例输出 #1
```
0010
&&^&
0 0 1 1
0011
^^&^
0 1 0 1
10100000
^^|^^^^|
1 5 5 7 1 5 5 7
00000000
^^^^^^^^
1 5 5 7 1 5 5 7

```
## 提示

**Source**: The 2022 ICPC Asia Xi'an Regional Contest Problem H.

**Author**: Alex_Wei.

![](https://cdn.luogu.com.cn/upload/image_hosting/g2frgx9s.png)
## 题目翻译

## 题目描述
SolarPea 喜欢通过发送电力塔来炸毁 PolarSea 的博客 $2$。由于塔太高，网页的堆栈溢出。所以博客已经不能用了。  

现在 SolarPea 拥有两个 $a_1、a_2、ldots、a_n$、$x$ 位 AND 运算符、$y$ 位 OR 运算符和 $z$ 位 XOR 运算符的 $n$ 次方。保证 $n = x + y + z$。  

Solarpea 希望使用这些数字和运算符构造一个算术表达式。正式地定义 $x_0 = 0$ 和 $x_i = x_{i - 1}\ \mathrm{op}_i\ b_i$，其中 $b$ 是 $a$ 的排列，这意味着我们可以重新排列 $a$ 来得到 $b$，而 $\mathrm{op}_i$ 是上述三种类型的按位运算符之一。那么 $x_n$ 就是表达式的结果。

表达式越大，就越有可能使 PolarSea 的博客无法工作。SolarPea 希望你帮他找到最大的 $x_n$ 并构造这样的表达式。如果有多个解决方案，则输出其中任何一个。

您需要独立处理 $T$ 个测试用例。
## 输入格式
第一行包含一个整数 $T $ （$1\leq T \leq 10 ^ 5$），表示测试用例的数量。  

对于每个测试用例，第一行包含四个整数 $n$， $x$， $y$ 和 $z$ （$0\leq x, y, z\leq n \leq 65\,536, n = x + y + z$）。下一行包含 $n$ 个整数 $c_1, c_2, \ldots, c_n$ ($0\leq c_i < n$)，其中 $a_i = 2 ^ {c_i}$。

保证所有测试用例的 $n $ 之和不超过 $1\,048\,576$。  
## 输出格式
对于每个测试用例，输出 3 行。  

第一行包含一个长度为 $n$ 的 $01$ 字符串，表示最大 $x_n$ 的二进制形式。  

下一行包含一个长度为 $n$ 的 $1$ 索引字符串 $\mathrm{op}$，其中 $\mathrm{op}_i$表示第 $i$ 个运算符。在这里，我们将 AND 表示为 `&` （ASCII 38），OR 表示为 `|` （ASCII 124），将 XOR 表示为 `^` （ASCII 94）。您应该保证正好有 $x $ AND 运算符、$y$ OR 运算符和 $z$ XOR 运算符。

第三行包含 $n$ 个整数 $d_1, d_2, \ldots, d_n$，其中第 $i$ 个代表 $b_i$ 的对数，以 $2$ 为底。也就是说，$d$ 是 $c$ 的排列。

如果有多个解决方案，则输出其中任何一个。

## 输入输出样例
无
## 提示
**来源**：2022 ICPC 亚洲习安区域赛问题 H.  
**作者**： Alex_Wei.


---

---
title: "ZHY 的矩阵"
layout: "post"
diff: 省选/NOI-
pid: P9490
tag: ['动态规划 DP', '递推', 'O2优化', '分类讨论']
---
# ZHY 的矩阵
## 题目描述

ZHY 的记忆中有一个 $k$ 行 $n$ 列的 01 矩阵 $A$，满足下列条件：

- 每一列都至多有一个 $1$。
- 每行相邻的两个 $1$ 所在的两列夹出的 $k$ 行的矩形（包括这两列）内至少有三个 $1$。

突然，ZHY 想起来了矩阵中 $x$ 个位置的值。请你计算有多少种填充 $A$ 的剩余位置的方案，使得 $A$ 满足条件。

----

形式化的讲，设 $A$ 第 $i$ 行第 $j$ 列的数为 $A_{i,j}$，则 $A$ 满足下列条件：

- 对于 $\forall i \in [1,k],\kern{2pt}j \in [1,n]$，$A_{i,j} \in \{0,1\}$。

- 对于 $\forall i \in [1,n]$，$\displaystyle\sum_{j=1}^{k} A_{j,i}\le 1$。

- 对于 $\forall i,j \in [1,n],\kern{2pt}p \in [1,k]$ 且 $j>i$，若有 $A_{p,i}=A_{p,j}=1,\displaystyle \sum_{x=i}^{j}A_{p,x}=2$，则有 $\Big(\displaystyle \sum_{x=1}^{k} \sum_{y=i}^{j} A_{x,y}\Big) \ge 3$。

- 对于 $\forall i\in[1,x]$，有 $A_{a_{i},b_{i}}=c_{i}$。

由于答案可能很大，你只需告诉 ZHY 答案对 $10^{9}+7$ 取模的结果。定义两个矩阵 $A,A'$ 不同，当且仅当存在 $i\in[1,k]$，$j\in[1,n]$ 满足 $A_{i,j}\ne A'_{i,j}$。
## 输入格式

第一行三个整数，表示 $n,k,x$。

接下来 $x$ 行，每行三个整数 $a_{i},b_{i},c_{i}$。
## 输出格式

一行一个整数，表示答案。
## 样例

### 样例输入 #1
```
3 2 2
1 1 1
2 2 0

```
### 样例输出 #1
```
2

```
## 提示

**样例解释**

满足条件的矩阵只有以下 $2$ 种：

$$
\begin{Bmatrix}
1&0&0\\
0&0&0
\end{Bmatrix}
$$

$$
\begin{Bmatrix}
1&0&0\\
0&0&1
\end{Bmatrix}
$$

----


**本题采用捆绑测试。**

| $\mathrm{Subtask} \kern{2pt} \mathrm{id}$ | $n$ | $x$ | 特殊性质 | 分值 |
| :-----: | :-----: | :-----: | :-----: | :-----: |
| $0$ | $\le 8$ | $\le 8$ | $k=2$ | $12$ |
| $1$ | $\le 2 \times 10^{5}$ | $\le 2\times 10^{5}$ | 无 | $26$ |
| $2$ | $\le 10^{9}$ | $=0$ | 无 | $23$ |
| $3$ | $\le 10^{9}$ | $\le 2\times 10^{5}$ | $c_{i}=1$ | $15$ |
| $4$ | $\le 10^{9}$ | $\le 2\times 10^{5}$ | 无 | $24$ |

对于所有数据，$1 \le n \le 10^{9}$，$0 \le x \le 2\times 10^{5}$，$2\le k \le 100$。$1 \le a_{i} \le k$，$1 \le b_{i} \le n$，$c_{i} \in \{0,1\}$。保证不存在一对 $i,j \in [1,x],\kern{2pt}i\neq j$，满足 $a_{i}=a_{j},\kern{2pt}b_{i}=b_{j}$。


---

---
title: "「PFLOI R1」PFL 变换"
layout: "post"
diff: 省选/NOI-
pid: P9591
tag: ['洛谷原创', 'Special Judge', 'O2优化', '模拟退火', '构造', 'Ad-hoc', '分类讨论']
---
# 「PFLOI R1」PFL 变换
## 题目背景

五大高手云集于此，思想的火花激烈碰撞。很快，PFLOI Round 1 准备完毕。

开始了……
## 题目描述

新的征途已经开始：智力踏上了寻香蕉之旅。道路上共有 $n$ 个香蕉，编号从 $1$ 到 $n$。

智力看到如此美食，非常激动。但是智力不想吃得太饱或太少，所以它会吃**刚好** $m$ 个香蕉。

智力是一个挑剔的人，只有当它吃的 $m$ 个香蕉的编号的异或和**恰好为** $2^{\lfloor\log_2 n\rfloor+1}-1$ 时他才会满意。请你帮忙找出他应该吃哪些香蕉，好让他满意。

如果怎样都不能满足智力的需求，就请输出 `-1` 吧。

------------

**形式化题面**：

请你从 $1$ 到 $n$ 中选出 $m$ 个数，使得它们的异或和恰好为 $2^{\lfloor\log_2 n\rfloor+1}-1$。若无解输出 `-1`。
## 输入格式

**本题有多组数据**。

第一行一个整数 $T$，表示一共有 $T$ 组测试数据。

对于每组测试数据，每行两个整数 $n$ 和 $m$，含义见题面。
## 输出格式

对于每组测试数据，若有解，输出一行共 $m$ 个整数，表示你选择的 $m$ 个数；若无解，输出 `-1`。

**本题采用 Special Judge**。若有多种可能的解，任意输出一个即可。
## 样例

### 样例输入 #1
```
7
5 2
6 6
7 6
8 3
9 3
10 1
7 4
```
### 样例输出 #1
```
3 4
1 6 2 4 3 5 
1 2 3 4 5 6
8 6 1
8 1 6
-1
3 5 6 7
```
## 提示

**本题不采用捆绑测试**。

| 测试点编号 | 特殊性质 | 分值 |
| :----------: | :----------: | :-----:| 
| $1,2$ | $n\le15$ | $2\times4=8$ |
| $3\sim11 $ | $n\le128$ | $9\times3=27$ |
| $12\sim24 $ | $\sum n\le10^5$ | $13\times3=39$ |
| $25\sim29$ | 无特殊限制 | $5\times4=20$ |
| $30$ | 无特殊限制 | $1\times6=6$ |

对于所有数据，$1\le m\le n\le10^6$，$1\le\sum n,T\le10^6$。


---

---
title: "[ICPC 2022 Jinan R] Set of Intervals"
layout: "post"
diff: 省选/NOI-
pid: P9674
tag: ['2022', 'O2优化', 'ICPC', 'Ad-hoc', '分类讨论', '济南']
---
# [ICPC 2022 Jinan R] Set of Intervals
## 题目描述

Prof. Pang has a multi-set of intervals $S=\{[l_i,r_i]\}$($l_i<r_i$).

Prof. Pang will perform the following operation for $|S|-1$ times:

- Select two intervals $[a,b]$ and $[c,d]$ from $S$, and then choose two integers $x,y$ satisfying $x\in [a,b], y\in [c,d], x<y$. After that, delete $[a,b]$ and $[c,d]$ from $S$, and add $[x,y]$ to $S$.

It's easy to find that $S$ contains exactly one interval after the operations, and Prof. Pang will get the interval as a gift.

Now Prof. Pang wants you to calculate how many different intervals he can get.
## 输入格式

The first line contains one integer $T~$($1\le T \le 10^4$), the number of test cases.

For each test case, the first line contains one integer $n~$($1\le n\le 10^5$) --- the size of $S$. Each of the following $n$ lines contains two integers $l_i$ and $r_i~$($1\le l_i<r_i\le 10^9$), describing the $i$-th interval in $S$.

It is guaranteed that the sum of $n$ over all test cases is no more than $10^5$.
## 输出格式

For each test case, output one line containing the answer to Prof. Pang's question.
## 样例

### 样例输入 #1
```
4
1
1 1000000000
2
1 1000000000
1 1000000000
4
1 2
3 4
5 6
7 8
4
1 3
2 4
5 8
6 7
```
### 样例输出 #1
```
1
499999999500000000
26
28
```
## 题目翻译

蓝蓝有一个元素全为闭区间的可重集 $S=\{[l_i,r_i]\}$($l_i<r_i$)。

蓝蓝将会执行以下操作 $n-1$ 次：
- 从 $S$ 内选择两个闭区间 $[a,b]$ 和 $[c,d]$，再选择两个整数 $x,y$ 满足 $x\in [a,b], y\in [c,d], x<y$，然后从 $S$ 中删去 $[a,b]$ 和 $[c,d]$，并把 $[x,y]$ 添加进 $S$。

显然最终 $S$ 中有且仅有一个区间。现在蓝蓝想知道她可以获得多少不同的区间。


---

---
title: "[ICPC 2021 Nanjing R] Puzzle in Inazuma"
layout: "post"
diff: 省选/NOI-
pid: P9841
tag: ['2021', 'Special Judge', 'O2优化', '构造', 'ICPC', '分类讨论', '南京']
---
# [ICPC 2021 Nanjing R] Puzzle in Inazuma
## 题目描述

Every traveler knows that they'll be rewarded with a treasure box after solving the puzzles in Inazuma, but few know that these puzzles are designed by Yae Miko, the Guuji of the Grand Narukami Shrine, to test whether the traveler is strong enough to save her friend Raiden Shogun and people of Inazuma.

![](https://cdn.luogu.com.cn/upload/image_hosting/p50zu2m6.png)

After a traveler passes the test Yae will have to reset the puzzles to the initial state. But this time she has some troubles and even doubts that whether some of them are already broken.

Yae's puzzle can be considered as a weighted undirected complete graph $G$ before resetting. We also denote the initial state as another weighted undirected complete graph $H$. Both $G$ and $H$ have exactly $n$ vertices, and these vertices are labeled from $1$ to $n$.

To reset graph $G$ to $H$ Yae can perform the following operation any number of times:
- First select four distinct vertices $a$, $b$, $c$, $d$ and an integer $x$. Note that she can select a different set of $a$, $b$, $c$, $d$ and $x$ each time.
- Let $(i, j)$ be the edge between vertices $i$ and $j$. Increase the weight of $(a, b)$, $(a, c)$ and $(a, d)$ by $x$ and also decrease the weight of $(b, c)$, $(b, d)$ and $(c, d)$ by $x$.

Please help Yae determine whether she can change graph $G$ to graph $H$. If yes you also shall tell her the detailed steps.
## 输入格式

There is only one test case in each test file.

The first line of the input contains an integer $n$ ($4 \leq n \leq 100$) indicating the number of vertices in graph $G$ and $H$.

For the following $(n - 1)$ lines, the $i$-th line contains $(n - i)$ integers $w_{i, i + 1}, w_{i, i + 2}, \cdots, w_{i, n}$ ($-100 \le w_{i, j} \le 100$) where $w_{i, j}$ indicates the weight of the edge connecting vertices $i$ and $j$ in graph $G$.

For the following $(n - 1)$ lines, the $i$-th line contains $(n - i)$ integers $v_{i, i + 1}, v_{i, i + 2}, \cdots, v_{i, n}$ ($-100 \le v_{i, j} \le 100$) where $v_{i, j}$ indicates the weight of the edge connecting vertices $i$ and $j$ in graph $H$.
## 输出格式

If Yae cannot change $G$ to $H$, output `-1`.

Otherwise first output an integer $m$ ($0 \le m \le 10^5$) in one line indicating the number of operations Yae needs.

For the following $m$ lines, output five integers $a_i$, $b_i$, $c_i$, $d_i$ and $x_i$ in the $i$-th line separated by a space, indicating that for the $i$-th operation Yae choose vertices $a_i$, $b_i$, $c_i$, $d_i$ and integer $x_i$. Note that $a_i$, $b_i$, $c_i$, $d_i$ must be distinct and $-10^9 \le x_i \le 10^9$.

It can be proved that if graph $G$ can be changed to graph $H$ there exists a solution with no more than $10^5$ operations.

Note that you don't have to minimize $m$. If there are multiple solutions, output any of them.
## 样例

### 样例输入 #1
```
4
0 1 1
0 0
1
1 0 0
1 1
0

```
### 样例输出 #1
```
1
2 1 3 4 1

```
### 样例输入 #2
```
4
3 3 3
0 0
0
0 0 0
3 3
3

```
### 样例输出 #2
```
1
1 2 3 4 -3

```
### 样例输入 #3
```
5
-12 15 -12 1
37 14 7
7 9
-11
12 5 1 13
-1 -4 -7
-5 -9
18

```
### 样例输出 #3
```
-1

```
## 题目翻译

给定一个 $n$ 个点的带权完全图 $G$，现在你可以对这个图做至多 $10^5$ 次如下操作，使其变成另一张带权完全图 $H$：
- 选取四个点 $a,b,c,d$ 与权值 $x$，使得边 $(a,b),(a,c),(a,d)$ 加上 $x$，边 $(b,c),(b,d),(c,d)$ 减去 $x$。

构造一组方案或判断无解。  
$4\le n\le 100$，边权在 $-100\sim 100$ 之间。


---

---
title: "「RiOI-03」网格"
layout: "post"
diff: 省选/NOI-
pid: P9917
tag: ['树状数组', '洛谷原创', 'O2优化', '洛谷月赛', '分类讨论']
---
# 「RiOI-03」网格
## 题目背景

2022 年某次集训讲课，课件中出现了一道以 MLE 真名首字母严格顺序作为输入变量的题目。MLE 就想在自己的题目里用 [vectorwyx](https://www.luogu.com.cn/user/238408) 的首字母当输入变量，于是就有了这道题。

可惜如今 [vectorwyx](https://www.luogu.com.cn/user/238408) 已经退役了，人生有梦，各自精彩。

## 题目描述

**请仔细阅读本题数据范围。**

给定一个 $n\times n$ 的正方形网格，一共有 $n$ 行，$n$ 列，初始时所有网格均为红色。有 $n$ 组询问，每次询问会把一整行或一整列的颜色全部染成红色或白色，每次询问后输出所有红色网格的周长，而且询问之间不独立。
## 输入格式

第一行为一个正整数 $n$；

接下来的 $n$ 行，每行三个正整数 $w,y,x$。$w$ 表示颜色，$w=1$ 表示染成红色，$w=0$ 表示染成白色。$y$ 表示行或列，$y=1$ 表示把第 $x$ 行全部染色，$y=0$ 表示把第 $x$ 列全部染色。
## 输出格式

一共有 $n$ 行，每行一个整数，表示每次修改后的红色部分周长。
## 样例

### 样例输入 #1
```
5
0 0 3
0 1 2
0 1 4
1 0 2
1 1 4
```
### 样例输出 #1
```
28
32
36
36
32

```
## 提示

### 样例解释

[样例图片解释](https://www.luogu.com.cn/paste/rvrhouei)

### 数据范围

对于 $100\%$ 的数据，$3\leq n \leq 10^6 $，$1<x<n$。

$$
\def\arraystretch{1.5}
\begin{array}{|c|c|c|c|c|c|} \hline
\textbf{\textsf{\#}}  & \bm{{n\le}} & \textbf{\textsf{特殊性质}} & \textbf{\textsf{\#}}  & \bm{{n\le}} & \textbf{\textsf{特殊性质}}\cr\hline
1  & 5 & - & 
11  & 10^5 & - \cr\hline
2  & 100 & - & 
12  & 10^5 & - \cr\hline
3  & 100 & - & 
13  & 10^5 & - \cr\hline
4  & 2000 & \textbf{A} & 
14  & 10^5 & - \cr\hline
5  & 2000 & \textbf{B} & 
15  & 10^6 & - \cr\hline
6  & 2000 & - & 
16  & 10^6 & - \cr\hline
7  & 10^5 & \textbf{AB} & 
17  & 10^6 & - \cr\hline
8  & 10^5 & \textbf{B} & 
18  & 10^6 & - \cr\hline
9  & 10^5 & \textbf{A} & 
19  & 10^6 & - \cr\hline
10  & 10^5 & - & 
20  & 10^6 & - \cr\hline
\end{array}
$$

- 特殊性质 $\bf A$：保证 $w=0$。
- 特殊性质 $\bf B$：保证 $y=0$。


---

