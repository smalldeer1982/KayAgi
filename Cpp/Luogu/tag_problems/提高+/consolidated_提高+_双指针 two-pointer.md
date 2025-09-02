---
title: "[USACO24OPEN] Smaller Averages G"
layout: "post"
diff: 提高+/省选-
pid: P10282
tag: ['动态规划 DP', 'USACO', '2024', '前缀和', '双指针 two-pointer']
---
# [USACO24OPEN] Smaller Averages G
## 题目描述

Bessie 有两个长度为 $N$ 的数组（$1\le N\le 500$）。第一个数组的第 $i$ 个元素为 $a_i$（$1\le a_i\le 10^6$），第二个数组的第 $i$ 个元素为 $b_i$（$1\le b_i\le 10^6$）。

Bessie 希望将两个数组均划分为若干**非空**子数组，使得以下条件成立。

1. 每个元素恰属于 $1$ 个子数组。
2. 两个数组划分为相同数量的子数组。令第一个和第二个数组被划分为的子数组数量为 $k$（即，第一个数组被划分为恰好 $k$ 个子数组，第二个数组被划分为恰好 $k$ 个子数组）。
3. 对于所有 $1\le i\le k$，第一个数组左数第 $i$ 个子数组的平均值**小于或等于**第二个数组左数第 $i$ 个子数组的平均值。 

计算她有多少种方式在满足限制的情况下将两个数组划分为非空子数组，对 $10^9+7$ 取模。两种划分方式被认为是不同的，如果子数组的数量不同或是某个元素属于不同的子数组。 
## 输入格式

输入的第一行包含 $N$。

第二行包含 $a_1,a_2,\ldots,a_N$。

第三行包含 $b_1,b_2,\ldots,b_N$。 
## 输出格式

输出在满足限制的情况下将两个数组划分为非空子数组的方法数模 $10^9+7$ 的余数。
## 样例

### 样例输入 #1
```
2
1 2
2 2
```
### 样例输出 #1
```
2
```
### 样例输入 #2
```
3
1 3 2
2 2 2
```
### 样例输出 #2
```
3
```
### 样例输入 #3
```
5
2 5 1 3 2
2 1 5 2 2
```
### 样例输出 #3
```
1
```
### 样例输入 #4
```
7
3 5 2 3 4 4 1
5 3 5 3 3 4 1
```
### 样例输出 #4
```
140
```
## 提示

### 样例解释 1

两种合法的方法为：

1. 将第一个数组划分为 $[1],[2]$，第二个数组划分为 $[2],[2]$。
2. 将第一个数组划分为 $[1,2]$，第二个数组划分为 $[2,2]$。

### 样例解释 2

三种合法的方法为：

1. 将第一个数组划分为 $[1,3],[2]$，第二个数组划分为 $[2,2],[2]$。
2. 将第一个数组划分为 $[1,3],[2]$，第二个数组划分为 $[2],[2,2]$。
3. 将第一个数组划分为 $[1,3,2]$，第二个数组划分为 $[2,2,2]$。

### 样例解释 3

唯一合法的方法是将第一个数组划分为 $[2],[5,1,3],[2]$，第二个数组划分为 $[2],[1,5],[2,2]$。

### 测试点性质

- 测试点 $5-6$：$N\le 10$。
- 测试点 $7-9$：$N\le 80$。
- 测试点 $10-17$：$N\le 300$。
- 测试点 $18-20$：$N\le 500$。


---

---
title: "Necklace"
layout: "post"
diff: 提高+/省选-
pid: P10476
tag: ['双指针 two-pointer']
---
# Necklace
## 题目描述

有一天，袁同学绵了一条价值连城宝石项链，但是，一个严重的问题是，他竟然忘记了项链的主人是谁！在得知此事后，很多人向同学发来了很多邮件，都说项链是自己的，要求他归还（显然其中最多只有一个人说了真话）。袁同学要求每个人都写了一段关于自己项链的描述：

项链上的宝石用数字 $0$ 至 $9$ 来表示。一个对于项链的表示就是从项链的某个宝石开始：顺指针绕一圈，沿途记下经过的宝石，比如如下项链：

![](https://cdn.luogu.com.cn/upload/image_hosting/57501u19.png)

它的可能的四种表示是 $0123$、$1230$、$2301$、$3012$。

袁同学现在心急如焚，于是他找到了你，希望你能够编一个程序，判断两个给定的描述是否代表同一个项链（注意，项链是不会翻转的）。
## 输入格式

输入文件只有两行，每行一个由 $0$ 至 $9$ 组成的字符串，描述一个项链的表示（保证项链的长度是相等的）。
## 输出格式

如果两条项链不可能同构，那么输出 `No`，否则的话，第一行输出一个 `Yes` 第二行输出该项链的字典序最小的表示。
## 样例

### 样例输入 #1
```
2234342423 
2423223434
```
### 样例输出 #1
```
Yes
2234342423
```
## 提示

设 $L =$ 项链长度，则 $1\leq L \leq 1000000$。


---

---
title: "【MX-J2-T4】Turtle and Cycles"
layout: "post"
diff: 提高+/省选-
pid: P10843
tag: ['二分', 'O2优化', '前缀和', '差分', '双指针 two-pointer', '梦熊比赛']
---
# 【MX-J2-T4】Turtle and Cycles
## 题目背景

原题链接：<https://oier.team/problems/J2E>。
## 题目描述

给你一个环形的 $0 \sim n - 1$ 的**排列** $a_0, a_1, \ldots, a_{n - 1}$。

一次操作你可以选择一个整数 $i \in [0, n - 1]$，把 $a_i$ 赋值成 $a_{(i - 1) \bmod n} + a_{(i + 1) \bmod n} - a_i$。

一个位置 $i \in [0, n - 1]$ 是好的当且仅当 $a_{(i - 1) \bmod n} < a_i$ 且 $a_{(i + 1) \bmod n} < a_i$。

环形序列 $a$ 是好的当且仅当存在**恰好**一个位置 $i \in [0, n - 1]$ 使得位置 $i$ 是好的。

求至少要进行多少次操作能让 $a$ 变成好的。可以证明一定有解。
## 输入格式

**本题有多组测试数据。**

第一行输入一个正整数 $T$，表示测试数据组数。

对于每组测试数据：

第一行包含一个正整数 $n$。

第二行包含 $n$ 个非负整数 $a_0, a_1, \ldots, a_{n - 1}$。
## 输出格式

对于每组数据，输出一行一个整数，表示最少要进行的操作次数。
## 样例

### 样例输入 #1
```
3
2
1 0
5
2 3 0 4 1
10
0 5 9 7 3 1 6 4 8 2

```
### 样例输出 #1
```
0
1
5

```
## 提示

#### 【样例解释】

在第一组数据中，初始序列恰好存在一个好的位置 $i = 0$，所以答案为 $0$。

在第二组数据中，可以选择 $i = 2$ 操作，操作后序列变为 $a = [2, 3, 7, 4, 1]$。此时序列恰好存在一个好的位置 $i = 2$，所以答案为 $1$。

#### 【数据范围】

**本题采用捆绑测试且开启子任务依赖。**

| 子任务编号 | 分值 | $n \le$ | $\sum n \le$ | 特殊性质 | 子任务依赖 |
| :-: | :-: | :-: | :-: | :-: | :-: |
| $1$ | $19$ | $6$ | $10^4$ | 无 | 无 |
| $2$ | $14$ | $12$ | $10^4$ | 无 | $1$ |
| $3$ | $27$ | $2 \cdot 10^3$ | $10^4$ | 无 | $1, 2$ |
| $4$ | $2$ | $2 \cdot 10^5$ | $2 \cdot 10^5$ | $a_i = i$ | 无 |
| $5$ | $38$ | $2 \cdot 10^5$ | $2 \cdot 10^5$ | 无 | $1, 2, 3, 4$ |

对于所有数据，满足 $1 \le T \le 10^4$，$2 \le n, \sum n \le 2 \cdot 10^5$，$0 \le a_i \le n - 1$，$a$ 是一个 $0 \sim n - 1$ 的排列。


---

---
title: "【MX-X10-T4】[LSOT-4] Fragment of Memories"
layout: "post"
diff: 提高+/省选-
pid: P12008
tag: ['倍增', '双指针 two-pointer', '梦熊比赛']
---
# 【MX-X10-T4】[LSOT-4] Fragment of Memories
## 题目背景

甜与苦的一体两面。
## 题目描述

苏珊在昏迷前度过了 $m$ 天。从第一天起，苏珊会有一个基准记忆 $x$，第 $i$（$1\le i\le m$）天的记忆为 $x+i-1$。这 $m$ 天的记忆按顺序依次拼接，得到了一串长为 $m$ 的记忆。

在梦境中，这段记忆被按顺序重复了 $k$ 遍。在这之后，为了唤醒苏珊，露薇娅进入了梦境，记忆被插入了一些不属于苏珊的记忆，最终变为了一个长度为 $n$ 的序列 $a_1, \ldots, a_n$。

现在给你这个序列和 $k$。露薇娅不知道一开始的基准记忆 $x$ 是多少，所以他想知道对于所有的 $1\le x\le V$，$m$ 的值最大可能是多少。若对于一个 $x$ 不存在合法的记忆，输出 $0$。
## 输入格式

第一行，三个整数 $n,k,V$，意义如题面所示。

第二行，$n$ 个整数 $a_1, \ldots, a_n$，表示最终的序列。
## 输出格式

仅一行，$V$ 个整数，第 $i$ 个整数表示当 $x=i$ 时最大的可能的 $m$。
## 样例

### 样例输入 #1
```
9 2 5
2 1 3 4 5 2 3 2 4
```
### 样例输出 #1
```
0 3 2 1 0
```
### 样例输入 #2
```
30 3 8
3 4 5 5 1 2 8 4 5 3 6 4 5 7 5 6 6 7 6 8 7 1 8 2 3 2 7 3 7 8
```
### 样例输出 #2
```
0 2 1 2 1 2 2 1
```
## 提示

**【样例解释 #1】**

当 $x=2$、$m=3$ 时，苏珊的记忆是 `2 3 4`。重复了 $k=2$ 次变成了 `2 3 4 2 3 4`。在位置 $1$ 和位置 $2$ 中间、位置 $3$ 和位置 $4$ 中间、位置 $5$ 和位置 $6$ 中间分别插入了一个数后变成了原序列。

类似地，`2`、`3`、`4`、`2 3`、`3 4` 都是符合要求的记忆。

**【数据范围】**

**本题采用捆绑测试。**

- 子任务 1（13 分）：$n\le 100$。
- 子任务 2（21 分）：$n\le 3000$。
- 子任务 3（23 分）：$n\le 3\times10^4$。
- 子任务 4（25 分）：$n\le 5\times10^5$。
- 子任务 5（18 分）：无特殊性质。

对于全部的数据，$1\le k\le n\le 2\times 10^6$，$1\le a_i\le V\le n$。


---

---
title: "[NordicOI 2025] 垃圾收集 / Garbage Collection"
layout: "post"
diff: 提高+/省选-
pid: P12119
tag: ['线段树', '双指针 two-pointer']
---
# [NordicOI 2025] 垃圾收集 / Garbage Collection
## 题目描述

北海上漂浮着 $N$ 块垃圾，编号从 $1$ 到 $N$。第 $i$ 块垃圾位于坐标 $\left(x_{i}, y_{i}\right)$，重量为 $w_{i}$。作为一项清理行动的一部分，你需要在某个矩形区域内收集所有垃圾。这个矩形区域的宽度为 $W$，高度为 $H$，但具体位置尚未确定。

你的任务是确定在最佳位置放置清理区域时，能够收集到的垃圾总重量的最大值。

译者注：「北海（North Sea）」指的是是北大西洋的一部分，不是广西壮族自治区北海市。
## 输入格式

第一行包含三个整数 $N,W$ 和 $H$。

接下来的 $N$ 行中，第 $i$ 行包含三个整数 $x_{i}, y_{i}$ 和 $w_{i}$，分别表示第 $i$ 块垃圾的坐标和重量。
## 输出格式

一行一个非负整数表示答案。
## 样例

### 样例输入 #1
```
5 3 2
3 1 10
2 1 5
1 0 5
0 2 10
1 3 5

```
### 样例输出 #1
```
20
```
## 提示

【样例解释】

最佳的清理区域应覆盖坐标为 $(3,1)$、$(2,1)$ 和 $(1,0)$ 的垃圾，总重量为 $10+5+5=20$。

![](https://cdn.luogu.com.cn/upload/image_hosting/9ln6vecp.png)

【数据规模与约定】

对于所有数据，满足：

$1 \leq N \leq 10^{5},1 \leq W, H \leq 10^{9},0 \leq x_{i}, y_{i} < 10^{9}(1 \leq i \leq N),1 \leq w_{i} \leq 10^{9}(1 \leq i \leq N)$。

详细子任务附加限制及分值如下表所示：

|  子任务编号| 分值 | 特殊限制 |
| :-----------: | :-----------: |:-----------: |
| $1$ | $10$ | $N \le 400$ |
| $2$ | $12$ | $W,H,x_i,y_i \le 2000$ |
| $3$ | $15$ | $N \le 2000$ |
| $4$ | $22$ | $H=10^9$ |
| $5$ | $23$ | $W,H,x_i,y_i \le 10^5$ |
| $6$ | $18$ |无特殊限制  |


---

---
title: "[NAC 2025] Geometry Rush"
layout: "post"
diff: 提高+/省选-
pid: P12623
tag: ['2025', 'ICPC', '双指针 two-pointer', 'NAC']
---
# [NAC 2025] Geometry Rush
## 题目描述

You are playing the summer's hottest rhythm-based action platformer---Geometry Rush! The game is played on a 2D plane. Your character begins at $(0,0)$ and every second must move at a $45$-degree angle either up-right or down-right, which takes your character from position $(x,y)$ to $(x+1,y+1)$ or $(x+1, y-1)$ respectively. You can change which direction you move every second, but not in between moves. There are obstacles protruding from the floor and ceiling that you must dodge. You win the game if, after $w$ seconds, you reach the line $x=w$ without having touched any obstacles on the way.

The play area extends vertically from $y=-h$ to $y=h$. Obstacles are two polygonal curves: one curve starts at $(0,h)$ and ends at $(w,h)$ and represents a ceiling of varying height. The $x$ values of the vertices of this curve are non-decreasing, and the $y$ values lie between $-h$ and $h$ inclusive. A second polygonal curve starts at $(0,-h)$ and ends at $(w,-h)$ and represents the floor. Its vertices satisfy similar constraints.

Your character is a point of negligible extent: you can move from position $(x,y)$ to $(x+1,y\pm 1)$ so long as the line segment between your start and end position does not intersect either obstacle. (Exactly touching either polygonal curve counts as intersecting an obstacle, and loses the game.)

You have played *a lot* of games of Geometry Rush. To keep the game interesting, you have started to set challenges for yourself. For example: you win the game no matter where you cross the $x=w$ goal line. But for what maximum value of $y$ can you win the game by crossing at $(w,y)$ without touching any obstacles on the way? For what minimum value? Compute these numbers.
## 输入格式

The first line of the input contains four space-separated integers $n$, $m$, $w$, and $h$. The first two integers ($3 \leq n, m \leq 10^{5}$) are the number of vertices in the ceiling and floor polygonal curves, respectively. The second two integers ($3 \leq w, h \leq 10^{5}$) are the width and height of the play area, as described above.

The next $n$ lines each contain two space-separated integers $x$ and $y$ ($0 \leq x \leq w$; $-h \leq y \leq h$): the coordinates of the vertices of the ceiling polygonal curve, in order from left to right. It is guaranteed that the first vertex is at $(0,h)$ and the last vertex is at $(w,h)$.

The next $m$ lines each contain two space-separated integers $x$ and $y$ ($0 \leq x \leq w$; $-h \leq y \leq h$): the coordinates of the vertices of the floor polygonal curve, in order from left to right. It is guaranteed that the first vertex is at $(0,-h)$ and the last vertex is at $(w,-h)$.

For both polygonal curves: the $x$ coordinates are non-decreasing, all vertices are distinct, and the curve does not self-intersect. Neither curve intersects $(0,0)$. (The floor and ceiling curves might intersect each other, in which case the game is unwinnable.)
## 输出格式

If it is impossible to win the game, print $\texttt{impossible}$. Otherwise, print two space-separated integers: the minimum and maximum $y$ values that the player could reach at $x=w$ without losing the game by touching an obstacle along the way.
## 样例

### 样例输入 #1
```
4 4 5 5
0 5
0 2
5 2
5 5
0 -5
0 -2
5 -2
5 -5
```
### 样例输出 #1
```
-1 1
```
### 样例输入 #2
```
4 4 6 5
0 5
0 2
6 2
6 5
0 -5
0 -2
6 -2
6 -5
```
### 样例输出 #2
```
0 0
```
### 样例输入 #3
```
3 3 7 5
0 5
5 -1
7 5
0 -5
2 1
7 -5
```
### 样例输出 #3
```
impossible
```
### 样例输入 #4
```
4 3 5 5
0 5
0 2
5 2
5 5
0 -5
3 -1
5 -5
```
### 样例输出 #4
```
-1 1
```


---

---
title: "[GCJ 2018 #1B] Mysterious Road Signs"
layout: "post"
diff: 提高+/省选-
pid: P13140
tag: ['动态规划 DP', '2018', '双指针 two-pointer', 'Google Code Jam']
---
# [GCJ 2018 #1B] Mysterious Road Signs
## 题目描述

The town of Signfield is on a perfectly straight and infinitely long road running from west to east. Along that road, there is a sequence of $\mathbf{S}$ mysterious road signs with numbers on both sides. The $i$-th sign (numbered in order from west to east) is at a point $\mathbf{D}_{\mathbf{i}}$ kilometers east of Signfield, and has a number $\mathbf{A}_{\mathbf{i}}$ on the west-facing side and a number $\mathbf{B}_{\mathbf{i}}$ on the east-facing side.

Nobody in Signfield knows what these signs are trying to say. You think that the numbers on the west sides of the signs are intended for drivers traveling east, and that they represent distances to some particular destination. Similarly, you think that the numbers on the east sides of the signs are for drivers traveling west, and that they represent distances to some particular destination. You suspect that not all of the signs may be consistent with this theory, though.

To start testing your theory, you are interested in finding valid sets of signs that obey the following rules:

* The set is a contiguous subsequence of the sequence of all road signs. (The entire sequence also counts as a contiguous subsequence.)
* There exist locations $\mathrm{M}$ and $\mathrm{N}$ kilometers east of Signfield, where $\mathrm{M}$ and $\mathrm{N}$ are (not necessarily positive and not necessarily distinct) numbers, such that for every sign in that set, at least one of the following is true:
    * $\mathbf{D}_{\mathbf{i}}+\mathbf{A}_{\mathbf{i}}=\mathbf{M}$.
    * $\mathbf{D}_{\mathbf{i}}-\mathbf{B}_{\mathbf{i}}=\mathbf{N}$.

What is the largest possible number of signs in a valid set as described above, and how many different valid sets of that size are there?
## 输入格式

The first line of the input gives the number of test cases, $\mathbf{T}$. $\mathbf{T}$ test cases follow. Each begins with one line containing one integer $\mathbf{S}$ : the number of road signs. Then, $\mathbf{S}$ more lines follow. The $i$-th of these lines represents the $i$-th sign (in west-to-east order), and contains three integers $\mathbf{D}_{\mathbf{i}}, \mathbf{A}_{\mathbf{i}}$, and $\mathbf{B}_{\mathbf{i}}$ : the sign's distance (in kilometers) east of Signfield, the number on its west side, and the number on its east side.

## 输出格式

For each test case, output one line containing `Case #x: y z`, where $x$ is the test case number (starting from 1), and $y$ and $z$ are the largest possible number of signs in a valid set and the number of valid sets of that size, as described in the problem statement.
## 样例

### 样例输入 #1
```
3
1
1 1 1
5
2 7 12
6 3 11
8 10 1
11 11 12
13 9 14
5
1 3 3
2 2 2
3 1 1
4 2 2
5 3 3
```
### 样例输出 #1
```
Case #1: 1 1
Case #2: 3 2
Case #3: 5 1
```
## 提示

**Sample Explanation**

In Sample Case #1, there is only one sign. If we choose just that sign as our set, there are many possible values of $\mathrm{M}$ and $\mathrm{N}$ that work - for example:

* $\mathrm{M}=2$ and $\mathrm{N}=0$
* $\mathrm{M}=1$ and $\mathrm{N}=0$ (remember that each sign only needs to be correct for one of its values; also, $\mathrm{M}$ and $\mathrm{N}$ might be in the same place as one or more signs, or Signfield itself)
* $\mathrm{M}=2$ and $\mathrm{N}=-12345$ ( $\mathrm{N}$ might be west of Signfield)
* $\mathrm{M}=0$ and $\mathrm{N}=0$ ( $\mathrm{M}$ and $\mathrm{N}$ are not necessarily distinct)
* $\mathrm{M}=2$ and $\mathrm{N}=3$ ( $\mathrm{N}$ might be east of $\mathrm{M}$)

So, the set consisting of just that one sign is valid. That is the only set of that length, so the answer is 11 .

In Sample Case #2, note that the first, second, fourth, and fifth signs would be consistent with $\mathrm{M}=9$ and $\mathrm{N}=-1$, but they do not form a contiguous subsequence. (The 1 on the back of the third sign cannot be used as if it were on the front.) As it turns out, there is no valid set of four signs. There are two different valid sets of three signs. Note that although there are two different $\mathrm{M} / \mathrm{N}$ pairs that make the second set of three signs valid, that set counts only once:

* the first, second, and third signs, with $\mathrm{M}=9$ and $\mathrm{N}=7$
* the third, fourth, and fifth signs, with $\mathrm{M}=18$ and $\mathrm{N}=-1$ or with $\mathrm{M}=22$ and $\mathrm{N}=7$

In Sample Case #3, the entire sequence is a valid set, with $\mathrm{M}=4$ and $\mathrm{N}=2$.

**Limits**

- $1 \leqslant \mathbf{T} \leqslant 60$.
- $1 \leqslant \mathbf{D}_{\mathbf{i}} \leqslant 10^{6}$, for all $i$.
- $\mathbf{D}_{\mathbf{i}}<\mathbf{D}_{\mathbf{j}}$, for all $i<j$.
- $1 \leqslant \mathbf{A}_{\mathbf{i}} \leqslant 10^{6}$, for all $i$.
- $1 \leqslant \mathbf{B}_{\mathbf{i}} \leqslant 10^{6}$, for all $i$.

**Test set 1 (10 Pts, Visible)**

- $1 \leqslant \mathbf{S} \leqslant 100$ for all test cases.

**Test set 2 (20 Pts, Hidden)**

- $1 \leqslant \mathbf{S} \leqslant 100$ for all but 3 test cases.
- $\mathbf{S}=10^{5}$ for 3 test cases.


---

---
title: "[GCJ 2010 Finals] Travel Plan"
layout: "post"
diff: 提高+/省选-
pid: P13410
tag: ['动态规划 DP', '2010', '双指针 two-pointer', '折半搜索 meet in the middle', 'Google Code Jam']
---
# [GCJ 2010 Finals] Travel Plan
## 题目描述

In a yet-to-be-announced and rechecked discovery by Antarctic astronomers, it is written that there are $N$ inhabited planets in space, all lying along the same straight line, with the $i$-th planet lying at coordinate $X_i$ along the line ($i = 1, 2, ..., N$). Earth is the first planet, lying at coordinate zero, so $X_1$ will always be equal to $0$.

Being very excited about this fact, you start planning a trip to visit all the planets. Since unknown planets can be dangerous, you want to visit each planet exactly once before returning to Earth. You have $F$ units of fuel, and you want to spend as much of it on this trip as possible so that your final landing on Earth is safer. Your spaceship is pretty basic and can only fly along a straight line from any planet $i$ to any other planet $j$, consuming $|X_i - X_j|$ units of fuel along the way. It can't turn without landing.

So you need to create a travel plan that requires at most $F$ units of fuel, starts from Earth, visits each of the other planets exactly once, and then returns to Earth. If there are several such plans, you should find the one that consumes most fuel. Output the amount of fuel consumed.

## 输入格式

The first line of the input gives the number of test cases, $T$. $T$ test cases follow. Each test case description starts with a line containing the number of planets $N$. The next line contains $N$ numbers $X_i$, the coordinates of the planets. The next line contains the amount of fuel $F$ that you have.

## 输出格式

For each test case, output one line containing either "Case #$x$: NO SOLUTION", when there's no such travel plan, or "Case #$x$: $y$", where $x$ is the case number (starting from $1$) and $y$ is the maximum amount of fuel consumed.
## 样例

### 样例输入 #1
```
3
3
0 10 -10
40
5
0 1 2 3 4
13
5
0 1 2 3 4
7
```
### 样例输出 #1
```
Case #1: 40
Case #2: 12
Case #3: NO SOLUTION
```
## 提示

**Limits**

- $1 \leq F \leq 10^{17}.$
- $-10^{15} \leq X_i \leq 10^{15}.$
- $X_1 = 0.$
- All $X_i$ are different.

**Small dataset (3 Pts, Test set 1 - Visible)**

- $1 \leq T \leq 100.$
- $2 \leq N \leq 10.$

**Large dataset (30 Pts, Test set 2 - Hidden)**

- $1 \leq T \leq 20.$
- $2 \leq N \leq 30.$


---

---
title: "[OOI 2024] More Gifts"
layout: "post"
diff: 提高+/省选-
pid: P13504
tag: ['贪心', '2024', '双指针 two-pointer', 'Moscow Olympiad']
---
# [OOI 2024] More Gifts
## 题目描述

The organizers of the Closed Olympiad in Informatics decided to prepare gifts for the participants of the Olympiad. A total of $k$ same gift boxes were prepared, each box contains a stack of $n$ gifts. At the top of each stack there is a gift of type $a_1$, below it there is a gift of type $a_2$, and so on, at the bottom of the stack there is a gift of type $a_n$.

The distribution of gifts will be as follows: at the beginning, gifts from the first stack will be given out from top to bottom. After there are no more gifts left in the first stack, gifts from the second stack will be given from top to bottom, and so on, in the end gifts from the $k$-th stack will be given.

A participant can receive several gifts at once, so at the beginning gifts will be given to the first participant, then to the second, and so on. It is known that if a participant receives more than $t$ different types of gifts, the participant will be too happy and will write the Olympiad poorly. In order for the participants to write the Olympiad well, it was decided to give each participant no more than $t$ different types of gifts (note that a participant may receive several gifts of the same type).

The organizers of the Closed Olympiad in Informatics decided to make the Olympiad exclusive and invite as few participants as possible. Help the organizers find out the minimum number of participants they can invite so that all the gifts are distributed to the participants, and each participant receives no more than $t$ different types of gifts.
## 输入格式

The first line of the input contains three integers $n$, $k$, and $t$ ($1 \le n \le 300\,000$, $1 \le k, t \le 10^9$) --- the number of gifts in one stack, the number of stacks of gifts, and the maximum number of different types of gifts that can be received by one participant.

The second line contains $n$ integers $a_1,\ a_2,\ \ldots,\ a_n$ ($1 \le a_i \le 10^9$) --- the types of gifts, in the order from top to bottom of the stack.
## 输出格式

Output a single number --- the minimum number of participants, such that all the gifts will be distributed to them, and each participant receives no more than $t$ different types of gifts.
## 样例

### 样例输入 #1
```
2 4 1
1 2
```
### 样例输出 #1
```
8
```
### 样例输入 #2
```
4 3 1
1 1 2 1
```
### 样例输出 #2
```
7
```
### 样例输入 #3
```
7 2 3
1 2 3 4 5 6 7
```
### 样例输出 #3
```
5
```
## 提示

### Note

In the first example, the stack contains the following types of gifts (in order from top to bottom). Different colors denote different positions in the stack.

:::align{center}
![](https://cdn.luogu.com.cn/upload/image_hosting/7a0npd0f.png)
:::

There are a total of 4 stacks of gifts, so the gifts will be given out in the following order:

:::aligned{center}
![](https://cdn.luogu.com.cn/upload/image_hosting/anlvf2nr.png)
:::

Since $t = 1$, each participant in this case can only receive gifts of one type:

:::aligned{center}
![](https://cdn.luogu.com.cn/upload/image_hosting/sxu9l82y.png)
:::

In the second example, the order of gift distribution and the final sets of gifts are following:

:::aligned{center}
![](https://cdn.luogu.com.cn/upload/image_hosting/cezyhq06.png)
![](https://cdn.luogu.com.cn/upload/image_hosting/ic7s6njx.png)
:::

In the third example, the order of gift distribution is as follows:

:::aligned{center}
![](https://cdn.luogu.com.cn/upload/image_hosting/14b4v2bt.png)
:::

In this case, one of the possible optimal distribution of gifts into sets is the following:

:::aligned{center}
![](https://cdn.luogu.com.cn/upload/image_hosting/a31c7071.png)
:::

### Scoring

The tests for this problem consist of six groups. Points for each group are given only if all tests of the group and all tests of the required groups are passed. Note that passing the example tests is not required for some groups.

| Group | Points | Additional constraints | < | < | Required groups | Comment |
|:------:|:------:|:----------------------:|:--:|:--:|:---------------:|:-------:|
|       |        | $n$ | $k$ | $t$ | | |
| 0 | 0 | -- | -- | -- | -- | Examples. |
| 1 | 14 | $n \le 100$ | $k \le 10$ | -- | 0 | -- |
| 2 | 12 | -- | -- | $t = 1$ | -- | -- |
| 3 | 16 | $n \le 1000$ | $k \le 1000$ | -- | 0, 1 | -- |
| 4 | 21 | $n \le 1500$ | $k \le 10^6$ | -- | 0, 1, 3 | -- |
| 5 | 18 | -- | $k \le 10^6$ | -- | 0, 1, 3, 4 | -- |
| 6 | 19 | -- | -- | -- | 0 -- 5 | -- |



---

---
title: "[SWERC 2023] Break a leg!"
layout: "post"
diff: 提高+/省选-
pid: P13799
tag: ['计算几何', '2023', 'ICPC', '双指针 two-pointer']
---
# [SWERC 2023] Break a leg!
## 题目描述

:::align{center}

![](https://espresso.codeforces.com/a2628cf785edc53f8245d1203533bdfe5a5f491a.png)

:::

For the first time, breakdance will be featured in the Olympics. And you get to participate! Well, you get to participate to the jury... More precisely, you get to build the table in front of which the jury will be seated: still, that is an impressive feat, congratulations!


Actually, the top of the table is already built: it is plane, has constant width and constant density, and its shape consists in the interior of an $N$-sided non-crossing polygon $P_1 P_2 \dots P_N$ in which no three vertices are collinear (i.e., no line goes through three vertices or more). You have three table legs of same length and negligible width. Your task is to place them at distinct corners of the table so that the table remains stable when standing on these legs. In other words, you must choose three vertices $P_i$, $P_j$ and $P_k$ of the polygon such that the centre of gravity of the polygon lies in the interior of the triangle $P_i P_j P_k$ (and not on its boundary).


In how many different ways can you do this? If two ways of placing legs differ only by a permutation
of the legs, they are not counted as different ways.
## 输入格式

The first line contains the number $N$. Then follow $N$ lines: the $i^\text{th}$ of these lines contains two space-separated integers $x_i$ and $y_i$, which are the $x$-coordinate and the $y$-coordinate of the vertex $P_i$.

**Limits**
	
- $3 \leq N \leq 100~000$;
- $-1~000~000 \leq x_i \leq 1~000~000$ and $-1~000~000 \leq y_i \leq 1~000~000$ for all $i \leq N$;
- whenever $1 \leq i < j < k \leq N$, the vertices $P_i$, $P_j$ and $P_k$ are not collinear;
- the polygonal shape $P_1 P_2 \dots P_N$ is non-crossing.


## 输出格式

The output should contain a single line, consisting of a single integer: the number of ways of placing legs such that the table remains stable.
## 样例

### 样例输入 #1
```
4
0 0
1 0
1 1
0 1
```
### 样例输出 #1
```
0
```
### 样例输入 #2
```
4
0 0
5 0
6 6
0 5
```
### 样例输出 #2
```
1
```
### 样例输入 #3
```
5
0 0
2 0
2 20
1 1
0 20
```
### 样例输出 #3
```
5
```


---

---
title: "[NOI2016] 区间"
layout: "post"
diff: 提高+/省选-
pid: P1712
tag: ['2016', '线段树', 'NOI', '离散化', 'O2优化', '排序', '双指针 two-pointer']
---
# [NOI2016] 区间
## 题目描述

在数轴上有 $n$ 个闭区间从 $1$ 至 $n$ 编号，第 $i$ 个闭区间为 $[l_i,r_i]$ 。

现在要从中选出 $m$ 个区间，使得这 $m$ 个区间共同包含至少一个位置。换句话说，就是使得存在一个 $x$ ，使得对于每一个被选中的区间 $[l_i,r_i]$，都有 $l_i \leq x \leq r_i$ 。

对于一个合法的选取方案，它的花费为被选中的最长区间长度减去被选中的最短区间长度。

区间 $[l_i,r_i]$ 的长度定义为 $(r_i-l_i)$ ，即等于它的右端点的值减去左端点的值。

求所有合法方案中最小的花费。如果不存在合法的方案，输出 $-1$。
## 输入格式

第一行包含两个整数，分别代表 $n$ 和 $m$。

第 $2$ 到第 $(n + 1)$ 行，每行两个整数表示一个区间，第 $(i + 1)$ 行的整数 $l_i, r_i$ 分别代表第 $i$ 个区间的左右端点。
## 输出格式

输出一行一个整数表示答案。

## 样例

### 样例输入 #1
```
6 3
3 5
1 2
3 4
2 2
1 5
1 4
```
### 样例输出 #1
```
2
```
## 提示

#### 样例输入输出 1 解释

![](https://cdn.luogu.com.cn/upload/image_hosting/qoddox9k.png)
 
 如图，当 $n=6$，$m=3$ 时，花费最小的方案是选取 $[3,5],[3,4],[1,4]$ 这三个区间，它们共同包含了 $4$ 这个位置，所以是合法的。其中最长的区间是 $[1, 4]$，最短的区间是 $[3, 4]$，所以它的花费是 $(4 - 1) - (4 - 3) = 2$。

#### 数据规模与约定

本题共 20 个测试点，各测试点信息如下表。
| 测试点编号 | $ n= $ | $ m= $ | $ l_i,r_i $ |
|:-:|:-:|:-:|:-:|
| 1 | $ 20 $ | $ 9 $ | $ 0 \le l_i \le r_i \le 100 $ |
| 2 | $ 20 $ | $ 10 $ | $ 0 \le l_i \le r_i \le 100 $ |
| 3 | $ 199 $ | $ 3 $ | $ 0 \le l_i \le r_i \le 100000 $ |
| 4 | $ 200 $ | $ 3 $ | $ 0 \le l_i \le r_i \le 100000 $ |
| 5 | $ 1000 $ | $ 2 $ | $ 0 \le l_i \le r_i \le 100000 $ |
| 6 | $ 2000 $ | $ 2 $ | $ 0 \le l_i \le r_i \le 100000 $ |
| 7 | $ 199 $ | $ 60 $ | $ 0 \le l_i \le r_i \le 5000 $ |
| 8 | $ 200 $ | $ 50 $ | $ 0 \le l_i \le r_i \le 5000 $ |
| 9 | $ 200 $ | $ 50 $ | $ 0 \le l_i \le r_i \le 10^9 $ |
| 10 | $ 1999 $ | $ 500 $ | $ 0 \le l_i \le r_i \le 5000 $ |
| 11 | $ 2000 $ | $ 400 $ | $ 0 \le l_i \le r_i \le 5000 $ |
| 12 | $ 2000 $ | $ 500 $ | $ 0 \le l_i \le r_i \le 10^9 $ |
| 13 | $ 30000 $ | $ 2000 $ | $ 0 \le l_i \le r_i \le 100000 $ |
| 14 | $ 40000 $ | $ 1000 $ | $ 0 \le l_i \le r_i \le 100000 $ |
| 15 | $ 50000 $ | $ 15000 $ | $ 0 \le l_i \le r_i \le 100000 $ |
| 16 | $ 100000 $ | $ 20000 $ | $ 0 \le l_i \le r_i \le 100000 $ |
| 17 | $ 200000 $ | $ 20000 $ | $ 0 \le l_i \le r_i \le 10^9 $ |
| 18 | $ 300000 $ | $ 50000 $ | $ 0 \le l_i \le r_i \le 10^9 $ |
| 19 | $ 400000 $ | $ 90000 $ | $ 0 \le l_i \le r_i \le 10^9 $ |
| 20 | $ 500000 $ | $ 200000 $ | $ 0 \le l_i \le r_i \le 10^9 $ |

对于全部的测试点，保证 $1 \leq m \leq n$，$1 \leq n \leq 5 \times 10^5$，$1 \leq m \leq 2 \times 10^5$，$0 \leq l_i \leq r_i \leq 10^9$。


---

---
title: "[CCC 2016] 合并饭团"
layout: "post"
diff: 提高+/省选-
pid: P4805
tag: ['动态规划 DP', '2016', 'CCC（加拿大）', '区间 DP', '双指针 two-pointer']
---
# [CCC 2016] 合并饭团
## 题目描述

**译自 [CCC2016](https://cemc.math.uwaterloo.ca/contests/computing/2016/index.html) Senior T4「[Combining Riceballs](https://cemc.math.uwaterloo.ca/contests/computing/2016/stage%201/seniorEn.pdf)」**

Alphonse 有 $N$ 个美味的饭团，它们大小不一，摆放成一行。他想把最大的饭团让给自己的基友。他可以执行以下操作：

 - 如果两个**相邻的**饭团大小相同，Alphonse 可以把它们合并成一个新的饭团。新饭团的大小是两个原饭团大小之和。它将占据两个原饭团先前占据的位置。

 - 如果两个饭团大小相同，且它们之间只有一个饭团，Alphonse 也可以把它们合并成一个新的饭团。（中间的饭团大小没有规定。）新饭团的大小是三个原饭团大小之和，并占据三个原饭团先前的位置。

Alphonse 可以按照他的意愿执行任意次操作。

在执行 0 或更多次操作后，确定他应该把哪个饭团让给基友。
## 输入格式

第一行，一个整数 $N(1 \le N \le 400)$。

第二行，$N$ 个以空格分隔的整数，表示每个饭团的大小，按照从左到右的顺序给出。每个整数的上界为 $1\ 000\ 000$。
## 输出格式

输出 Alphonse 可以得到的最大的饭团大小。
## 样例

### 样例输入 #1
```
7
47 12 12 3 9 9 3
```
### 样例输出 #1
```
48
```
### 样例输入 #2
```
4
1 2 3 1
```
### 样例输出 #2
```
3
```
## 提示

#### 样例解释 1
有一种可能的合并方案为：合并大小同为 $12$ 的两个饭团，得到一个大小为 $24$ 的饭团。然后合并大小同为 $9$ 的两个饭团，得到一个大小为 $18$。接着合并大小为 $3,18$ 和 $3$ 的三个饭团，得到一个大小为 $24$ 的饭团。最后合并大小同为 $24$ 的两个饭团，得到一个大小为 $48$ 的饭团。

#### 样例解释 2
我们无法进行操作，所以答案为 $3$。

对于 $\frac1{15}$ 的数据，$N = 4$。

对于另外 $\frac2{15}$ 的数据，$N \le 10$。

对于另外 $\frac5{15}$ 的数据，$N \le 50$。


---

---
title: "[USACO21JAN] Dance Mooves G"
layout: "post"
diff: 提高+/省选-
pid: P7298
tag: ['USACO', '2021', 'O2优化', '双指针 two-pointer']
---
# [USACO21JAN] Dance Mooves G
## 题目描述

Farmer John 的奶牛们正在炫耀她们的最新舞步！

最初，所有的 $N$ 头奶牛（$2≤N≤10^5$）站成一行，奶牛 $i$ 排在其中第 $i$ 位。舞步序列给定为 $K$ （$1≤K≤2\times10^5$）个位置对 $(a_1,b_1),(a_2,b_2),…,(a_K,b_K)$。在舞蹈的第 $i=1…K$ 分钟，位置 $a_i$ 与 $b_i$ 上的奶牛交换位置。同样的 $K$ 次交换在第 $K+1…2K$ 分钟发生，在第 $2K+1…3K$ 分钟再次发生，以此类推，周期性地持续共 $M$ 分钟（$1≤M≤10^{18}$）。换言之， 

 - 在第 $1$ 分钟，位置 $a_1$ 与 $b_1$ 上的奶牛交换位置。
 - 在第 $2$ 分钟，位置 $a_2$ 与 $b_2$ 上的奶牛交换位置。
 - ……
 - 在第 $K$ 分钟，位置 $a_K$ 与 $b_K$ 上的奶牛交换位置。
 - 在第 $K+1$ 分钟，位置 $a_1$ 与 $b_1$ 上的奶牛交换位置。
 - 在第 $K+2$ 分钟，位置 $a_2$ 与 $b_2$ 上的奶牛交换位置。
 - 以此类推……

对于每头奶牛，求她在队伍中会占据的不同的位置数量。

注意：本题每个测试点的时间限制为默认限制的两倍。 
## 输入格式

输入的第一行包含 $N$、$K$ 和 $M$。以下 $K$ 行分别包含 $(a_1,b_1)…(a_K,b_K)$（$1≤a_i<b_i≤N$）。 
## 输出格式

输出 $N$ 行，第 $i$ 行包含奶牛 $i$ 可以到达的不同的位置数量。 
## 样例

### 样例输入 #1
```
6 4 7
1 2
2 3
3 4
4 5
```
### 样例输出 #1
```
5
4
3
3
3
1
```
## 提示

$7$ 分钟之后，各个位置上的奶牛为 $[3,4,5,2,1,6]$。

 - 奶牛 $1$ 可以到达位置 $\{1,2,3,4,5\}$。
 - 奶牛 $2$ 可以到达位置 $\{1,2,3,4\}$。
 - 奶牛 $3$ 可以到达位置 $\{1,2,3\}$。
 - 奶牛 $4$ 可以到达位置 $\{2,3,4\}$。
 - 奶牛 $5$ 可以到达位置 $\{3,4,5\}$。
 - 奶牛 $6$ 从未移动，所以她没有离开过位置 $6$。
 
#### 测试点性质：

 - 测试点 1-5 满足 $N≤100,K≤200$。
 - 测试点 6-10 满足 $M=10^{18}$。
 - 测试点 11-20 没有额外限制。

Problem credits: Chris Zhang 


---

---
title: "[POI 2020/2021 R3] Les Bitérables"
layout: "post"
diff: 提高+/省选-
pid: P9403
tag: ['2020', 'POI（波兰）', '差分', '双指针 two-pointer']
---
# [POI 2020/2021 R3] Les Bitérables
## 题目背景

译自 [XXVIII Olimpiada Informatyczna - III etap](https://sio2.mimuw.edu.pl/c/oi28-3/dashboard/) [Les Bitérables](https://szkopul.edu.pl/problemset/problem/Lpz563_ATiESIrNZxiT5bwIx/statement/)。

d1t2。
## 题目描述

有 $t$ 个时刻，第 $i$ 个时刻给出了局面 $p_1,p_2,\dots,p_{s_i}$，表示在数轴的 $(0,d)$ 范围内，有且仅有 $p_1,p_2,\dots,p_{s_i}$ 这些位置上有物品。

在 $0$ 位置和 $d$ 位置有无穷多个物品。

你可以花费一个代价，将一个物品向左移动一个位置或向右移动一个位置。

问你在相邻两个时刻之间，把前一个局面转化为后一个局面，最少需要多少代价。
## 输入格式

第一行两个正整数 $n,d$。

接下来 $n$ 行，每行描述一个时刻的局面，首先是一个非负整数 $s_i$，接下来是 $s_i$ 个正整数，分别为 $p_1,p_2,\dots,p_{s_i}$。保证 $0<p_1<p_2<\dots<p_{s_i}<d$。
## 输出格式

$n-1$ 行，每行一个整数，你的答案。
## 样例

### 样例输入 #1
```
3 10
2 4 7
3 3 6 8
1 5

```
### 样例输出 #1
```
4
6
```
### 样例输入 #2
```
见附件
```
### 样例输出 #2
```
6252500
6252500

```
### 样例输入 #3
```
见附件
```
### 样例输出 #3
```
999990000
999990000
999990000
999990000

```
### 样例输入 #4
```
生成器：/paste/3igmip11
```
### 样例输出 #4
```
生成器：/paste/fusadpm0
```
## 提示

对于所有数据，$2\leq n\leq 500000$，$2\leq d\leq 10^{12}$，$\sum s_i\leq 500000$。

| 子任务编号 | 附加限制 | 分数 |
| :----------: | :----------: | :----------: |
| 1 | $s_i\leq 1$ | 5 |
| 2 | $s_i\leq 3$ | 10 |
| 3 | $d\leq 7$ | 12 |
| 4 | $\sum s_i\leq 5000$ | 27 |
| 5 | 如果 $s_i>0$，那么 $p_{s_i}=p_1+s_i-1$ | 11 |
| 6 |  | 35 |



---

---
title: "[ICPC 2021 Macao R] Laser Trap"
layout: "post"
diff: 提高+/省选-
pid: P9658
tag: ['计算几何', '2021', 'O2优化', '叉积', 'ICPC', '双指针 two-pointer', '澳门']
---
# [ICPC 2021 Macao R] Laser Trap
## 题目描述

BaoBao is playing the famous game $\textit{Elden Ring}$ these days. It's an open-world game in which you can control your character to travel from places to places. However, your character could also enter a trap and you need to figure out how to escape. Right now, BaoBao's character is stuck in a 2-dimensional plane with deadly lasers. There are $n$ laser generators (each can be regarded as a point) shooting laser beams between every pair of them (so there are $\frac{n(n-1)}{2}$ laser beams in total). The beams start and end at generator points and do not stretch to infinity.

Starting at point $(0,0)$, BaoBao wants to escape to point $(10^{10^{10^{10^{10}}}}, 10^{10^{10^{10^{10}}}})$ without touching any laser beam or generator. In order to do so, BaoBao can ask her friend DreamGrid to remove any number of laser generators, together with any laser beam that starts or ends at these generators. Output the minimum number of laser generators that need to be erased for the escape.

Note that BaoBao does not need to move in a specific direction to escape. Her escaping route can even be a curve if necessary.
## 输入格式

There are multiple test cases. The first line of the input contains an integer $T$ indicating the number of test cases. For each test case:

The first line contains an integer $n$ ($1 \le n \le 10^6$) indicating the number of laser generators.

For the following $n$ lines, the $i$-th line contains two integers $x_i$ and $y_i$ ($-10^9 \le x_i, y_i \le 10^9$) indicating the location of the $i$-th laser generator.

It is guaranteed that no two generators coincide, and no laser beam or generator will touch $(0,0)$.

It is also guaranteed that the sum of $n$ of all test cases will not exceed $10^6$.
## 输出格式

For each test case output one line containing one integer indicating the minimum number of generators that need to be removed.
## 样例

### 样例输入 #1
```
3
2
1 0
2 0
3
1 0
0 1
-1 -1
5
2 -1
1 2
-1 2
-2 -1
0 -2
```
### 样例输出 #1
```
0
1
2
```
## 提示

The second and the third sample test cases are shown below. Solid dots and lines represent the remaining laser generators and beams, while hollow dots and dashed lines represent the removed laser generators and beams. The arrow is the escaping route.

![](https://cdn.luogu.com.cn/upload/image_hosting/b0sz7cm0.png)

![](https://cdn.luogu.com.cn/upload/image_hosting/dwcsdmj6.png)
## 题目翻译

一直角坐标系中，BaoBao 在原点位置，平面上有 $n$ 个发射装置，任意两个发射器之间都有激光束，共 $(n-1) \times n / 2$ 条激光，BaoBao 的朋友可以去除任何发射器，问最少去除多少发射器，能使 BaoBao不会被激光所伤还能从 $(0,0)$ 逃逸到 $\left(10^{10^{10^{10^{10}}}}, 10^{10^{10^{10^{10}}}}\right)$。

tip.发射器不会重合，也不会存在激光束穿过 $(0,0)$。


---

