---
title: "[信息与未来 2023] 电路布线"
layout: "post"
diff: 提高+/省选-
pid: B3791
tag: ['动态规划 DP', '搜索', '2023', '江苏', 'Special Judge', '剪枝', '折半搜索 meet in the middle', '信息与未来']
---
# [信息与未来 2023] 电路布线
## 题目描述

电路布局布线（Circuit Layout and Routing）是电子设计自动化（EDA）领域的一个重要概念，它涉及到在电路板或集成电路上安排和连接电子元件的过程。这个过程的目标是在满足电气性能、信号完整性、电磁兼容性等要求的同时，实现对空间、成本和生产工艺的优化。

![](https://cdn.luogu.com.cn/upload/image_hosting/vcbssp42.png)

小小现在需要解决一个简化的电路布线问题，在一个 $n × m$ 的方格中进行电路布线。其中：
- 井号 `#` 标记的格子已经被占用，不能布线。
- 加号 `+` 标记的格子会连接到电路的其他部分，必须被布线。在给定的电路布线问题中，至少有一个格子必须被布线。
- 点号 `.` 标记的格子小小有权选择是否布线：布线即将该格标记为加号，不布线即保持为点号。

小小的任务是选择尽可能多的格子进行布线 (将 `.` 的格子标记为 `+`)，满足：
1. 布线电路连通。即从任意一个已布线的格子，都能通过上、下、左、右移动到相邻已布线格子的方式，到达任意另一个布线的格子。
2. 布线不存在短路 (回路)，即不存在某个布线的格子能通过 $> 2$ 步的上、下、左、右移动到相邻布线格子的方式回到自身，且经过的格子各不相同。

例如，以下是一个电路布线问题，已有三个格子被标记为必须布线 (加号)：
```plain
#....#
....+#
.+####
.+...#
```
以下展示了一种合法和两种不合法的布线方案：
```plain
#+.+.# #.+..# #++..#
+++++# ..+++# .++++#
.+#### .+#### .+####
.++++# .+...# .+...#
合法 不连通 有回路
```
## 输入格式

输入第一行是两个空格分隔的整数 $n$ 和 $m$，代表布线问题格子的行数和列数。

接下来 $n$ 行，每行 $m$ 个字符（`#`、`+`、`.` 中的一个），描述了具体的布线问题。

输入数据保证至少存在一种合法的布线方案。输入数据中至少有一个 `+`。
## 输出格式

输出 $n$ 行，每行 $m$ 个字符，代表最优的布线方案，其中被布线的格子尽可能多。如有多种可能的方案，输出任意一种即可。
## 样例

### 样例输入 #1
```
2 2
+.
..
```
### 样例输出 #1
```
+.
++
```
### 样例输入 #2
```
3 5
...+#
..###
....+
```
### 样例输出 #2
```
++++#
.+###
+++++
```
### 样例输入 #3
```
5 6
..++..
.#..#.
.#..#.
.#..#.
......
```
### 样例输出 #3
```
++++++
+#.+#+
+#+.#+
+#++#+
++.+++
```
## 提示

### 数据规模

对于 $40\%$ 的数据，满足 $n × m \le 16$。

对于 $100\%$ 的数据，满足 $1\le n, m \le 6$。

### 评分标准

在你的布线方案合法（连通且无回路）的前提下：

- 如果你的方案是最优布线方案，即布线的格子最多，该测试点得满分。
- 否则，该测试点得一半分数。

>本题原始满分为 $20\text{pts}$。

---

SPJ Provider：@[scp020](https://www.luogu.com.cn/user/553625)


---

---
title: "[ROIR 2024] 表格游戏 (Day 1)"
layout: "post"
diff: 提高+/省选-
pid: P11122
tag: ['2024', 'Special Judge', '折半搜索 meet in the middle', '状压 DP', 'ROIR（俄罗斯）']
---
# [ROIR 2024] 表格游戏 (Day 1)
## 题目背景

翻译自 [ROIR 2024 D1T3](https://neerc.ifmo.ru/school/archive/2023-2024/ru-olymp-regional-2024-day1.pdf)。

给定一个有 $h$ 行和 $w$ 列的表格 $A$，每个单元格内含有一个整数。行从上到下编号为 $1$ 到 $h$，列从左到右编号为 $1$ 到 $w$。允许对这个表格进行以下操作：

- 选择一列并删除它（删除的列左边和右边的列变为相邻的列）；
- 选择一行并删除它（删除的行上边和下边的行变为相邻的行）。

这些操作可以按任意顺序执行任意多次。
## 题目描述

你需要确定是否可以通过这些操作将表格变为一个数字之和为 $s$ 的表格。如果可以，请给出具体的操作。
## 输入格式

第一行包含两个数字 $h$ 和 $w$，表示表格的大小（$1 \leq h, w \leq 15$）。

接下来 $h$ 行，每行包含 $w$ 个整数，其中第 $i$ 行第 $j$ 列为 $A_{i,j}$（$0 \leq A_{i,j} \leq 10^9$）。

最后一行输入数字 $s$，即需要通过操作达到的和（$1 \leq s \leq 10^{18}$）。
## 输出格式

如果从原始表格中无法得到一个数字之和为 $s$ 的表格，输出 `NO`。

否则：
- 第一行输出 `YES`。
- 第二行输出一个数字 $k$ ，表示需要进行的操作次数。
- 接下来的 $k$ 行，每行输出两个整数 $t_j$，$i_j$，其中 $t_j = 1$ 表示操作是对行进行的，$t_j = 2$ 表示操作是对列进行的。数字 $i_j$ 应为操作所针对的行或列的初始编号。
## 样例

### 样例输入 #1
```
3 3
1 2 3
2 3 1
3 1 2
8
```
### 样例输出 #1
```
YES
2
1 3
2 3
```
### 样例输入 #2
```
2 3
2 2 2
2 2 2
5
```
### 样例输出 #2
```
NO
```
### 样例输入 #3
```
5 5
1 2 1 4 5
2 5 4 1 2
4 2 4 3 1
5 5 3 2 4
1 2 4 5 2
34
```
### 样例输出 #3
```
YES
3
1 4
1 5
2 1
```
## 提示

在样例 $1$ 中，最初给定的表格是：

$$
\begin{matrix}
1 & 2 & 3 \\
2 & 3 & 1 \\
3 & 1 & 2 \\
\end{matrix}
$$

删除第三行和第三列后，我们得到以下表格，其元素总和为 $8$：

$$
\begin{matrix}
1 & 2 & 3 \\
2 & 3 & 1 \\
3 & 1 & 2 \\
\end{matrix}
\rightarrow
\begin{matrix}
1 & 2 & 3 \\
2 & 3 & 1 \\
\end{matrix}
\rightarrow
\begin{matrix}
1 & 2 \\
2 & 3 \\
\end{matrix}
$$

在样例 $2$ 中，显然无法通过操作从初始表格中得到元素总和为 $5$ 的表格，因为初始表格全部都是 $2$，而 $5$ 是一个奇数。

在样例 $3$ 中，最初给定的表格是：

$$
\begin{matrix}
1 & 2 & 1 & 4 & 5 \\
2 & 5 & 4 & 1 & 2 \\
4 & 2 & 4 & 3 & 1 \\
5 & 5 & 3 & 2 & 4 \\
1 & 2 & 4 & 5 & 2 \\
\end{matrix}
$$

删除最后两行和第一列后，我们得到以下表格，其元素总和为 $34$：

$$
\begin{matrix}
1 & 2 & 1 & 4 & 5 \\
2 & 5 & 4 & 1 & 2 \\
4 & 2 & 4 & 3 & 1 \\
5 & 5 & 3 & 2 & 4 \\
1 & 2 & 4 & 5 & 2 \\
\end{matrix}
\rightarrow
\begin{matrix}
1 & 2 & 1 & 4 & 5 \\
2 & 5 & 4 & 1 & 2 \\
4 & 2 & 4 & 3 & 1 \\
1 & 2 & 4 & 5 & 2 \\
\end{matrix}
\rightarrow
\begin{matrix}
1 & 2 & 1 & 4 & 5 \\
2 & 5 & 4 & 1 & 2 \\
4 & 2 & 4 & 3 & 1 \\
\end{matrix}
\rightarrow
\begin{matrix}
2 & 1 & 4 & 5 \\
5 & 4 & 1 & 2 \\
2 & 4 & 3 & 1 \\
\end{matrix}
$$

| 子任务 | 分值 | 特殊性质 |
| :----------: | :----------: | :----------: |
| $0$ | $0$ | 同样例 |
| $1$ | $17$ | $h=1$ |
| $2$ | $6$ | 第 $i$ 行中的数字和不超过 $i$ |
| $3$ | $10$ | $h\le3$ |
| $4$ | $13$ | $h,w\le10$ |
| $5$ | $13$ | $h,w\le12$ |
| $6$ | $12$ | $A_{i,j}\le6$ |
| $7$ | $29$ | 无 |

对于 $100\%$ 的数据，$1 \leq h, w \leq 15$，$0 \leq A_{i,j} \leq 10^9$，$1 \leq s \leq 10^{18}$。


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
title: "[USACO12OPEN] Balanced Cow Subsets G"
layout: "post"
diff: 提高+/省选-
pid: P3067
tag: ['搜索', '2012', 'USACO', '折半搜索 meet in the middle']
---
# [USACO12OPEN] Balanced Cow Subsets G
## 题目描述

Farmer John's owns N cows (2 <= N <= 20), where cow i produces M(i) units of milk each day (1 <= M(i) <= 100,000,000).  FJ wants to streamline the process of milking his cows every day, so he installs a brand new milking machine in his barn.  Unfortunately, the machine turns out to be far too sensitive: it only works properly if the cows on the left side of the barn have the exact same total milk output as the cows on the right side of the barn!

Let us call a subset of cows "balanced" if it can be partitioned into two groups having equal milk output.  Since only a balanced subset of cows can make the milking machine work, FJ wonders how many subsets of his N cows are balanced.  Please help him compute this quantity.

## 输入格式

\* Line 1: The integer N.

\* Lines 2..1+N: Line i+1 contains M(i). 


## 输出格式

\* Line 1: The number of balanced subsets of cows.

## 样例

### 样例输入 #1
```
4 
1 
2 
3 
4 

```
### 样例输出 #1
```
3 

```
## 提示

There are 4 cows, with milk outputs 1, 2, 3, and 4.


There are three balanced subsets: the subset {1,2,3}, which can be partitioned into {1,2} and {3}, the subset {1,3,4}, which can be partitioned into {1,3} and {4}, and the subset {1,2,3,4} which can be partitioned into {1,4} and {2,3}.

## 题目翻译

我们定义一个奶牛集合 $S$ 是平衡的，当且仅当满足以下两个条件：

- $S$ 非空。
- $S$ 可以被**划分**成两个集合 $A,B$，满足 $A$ 里的奶牛产奶量之和等于 $B$ 里的奶牛产奶量之和。划分的含义是，$A\cup B=S$ 且 $A\cap B=\varnothing$。

现在给定大小为 $n$ 的奶牛集合 $S$，询问它有多少个子集是平衡的。请注意，奶牛之间是互不相同的，但是它们的产奶量可能出现相同。

### 输入格式

第一行一个整数 $n$，表示奶牛的数目。

第 $2$ 至 $n+1$ 行，每行一个数 $a_i$，表示每头奶牛的产奶量。

### 输出格式

输出一个数表示方案总数。

### 样例解释

共存在三种方案。集合 $\{1,2,3\}$ 可以划分为 $\{1,2\}$ 与 $\{3\}$；集合 $\{1,3,4\}$ 可以划分为 $\{1,3\}$ 与 $\{4\}$；集合 $\{1,2,3,4\}$ 可以划分为 $\{1,4\}$ 与 $\{2,3\}$，共 $3$ 种子集。

### 数据范围及约定

对于全部数据，保证 $1\le n\le 20$，$1\le a_i\le 10^8$。


---

---
title: "[USACO22FEB]  Robot Instructions S"
layout: "post"
diff: 提高+/省选-
pid: P8187
tag: ['USACO', '2022', '折半搜索 meet in the middle']
---
# [USACO22FEB]  Robot Instructions S
## 题目描述

Bessie is learning how to control a robot she has recently received as a gift.
The robot begins at point $(0,0)$ on the coordinate plane and Bessie wants the robot to end at point $(x_g,y_g)$. Bessie initially has a list of $N$ $(1\le N\le 40)$ instructions to give to the robot, the $i$-th of which will move the robot $x_i$ units right and $y_i$ units up (or left or down when $x_i$ and $y_i$ are negative, respectively).

For each $K$ from $1$ to $N$, help Bessie count the number of ways she can select $K$ instructions from the original $N$ such that after the $K$ instructions are executed, the robot will end at point $(x_g,y_g)$.

**Note: the time and memory limits for this problem are 4s and 512MB, twice the defaults.**
## 输入格式

The first line contains $N$. The next line contains $x_g$ and $y_g$, each in the range $−10^9\cdots 10^9$. The final $N$ lines describe the instructions. Each line has two integers $x_i$ and $y_i$, also in the range $−10^9\cdots 10^9$.

It is guaranteed that $(x_g,y_g)\neq (0,0)$ and $(x_i,y_i)\neq (0,0)$ for all $i$.
## 输出格式

Print $N$ lines, the number of ways Bessie can select $K$ instructions from the original $N$ for each $K$ from $1$ to $N$.
## 样例

### 样例输入 #1
```
7
5 10
-2 0
3 0
4 0
5 0
0 10
0 -10
0 10
```
### 样例输出 #1
```
0
2
0
3
0
1
0
```
## 提示

【样例解释】

In this example, there are six ways Bessie can select the instructions:
```
(-2,0) (3,0) (4,0) (0,10) (0,-10) (0,10) (1 2 3 5 6 7)
(-2,0) (3,0) (4,0) (0,10) (1 2 3 5)
(-2,0) (3,0) (4,0) (0,10) (1 2 3 7)
(5,0) (0,10) (0,-10) (0,10) (4 5 6 7)
(5,0) (0,10) (4 5)
(5,0) (0,10) (4 7)
```
For the first way, the robot's path looks as follows:
```
(0,0) -> (-2,0) -> (1,0) -> (5,0) -> (5,10) -> (5,0) -> (5,10)
```

【数据范围】

- Test cases 2-4 satisfy $N\le 20$.
- Test cases 5-16 satisfy no additional constraints.
## 题目翻译

## 题目描述
贝西正在学习如何控制她最近作为礼物收到的机器人。

机器人初始在坐标平面上的点 $(0,0)$，Bessie 希望机器人在点 $(x_g,y_g)$ 停止。 Bessie 最初有一个包含 $N(1\leq N \leq 40)$ 条指令的指令列表给机器人，其中第 $i$ 个指令将向右移动机器人 $x_i$
  单位和向上移动 $y_i$
  单位（或者当 $x_i$ 和 $y_i$ 为负数时分别向左或向下移动）。

对于从 $1$ 到 $N$ 的每个 $K$，帮助 Bessie 计算她可以从原始 $N$ 中选择 $K$ 条指令的方案数，使得在执行 $K$ 条指令后，机器人将在点 $(x_g,y_g)$ 处停止。

## 输入格式
第一行包含 $N$ 。下一行包含 $x_g$ 和 $y_g$，每个数都在 $-10^9\dots 10^9$ 的范围内。最后的 $N$ 行描述了指令。每行有两个整数 $x_i$ 和 $y_i$，也在 $-10^9\dots 10^9$ 范围内。

保证 $(x_g,y_g)\neq (0,0)$ 和对于所有的 $i，(x_i,y_i)\neq (0,0)$。

## 数据范围
数据 $2\sim 4$ 满足 $N\leq 20$。

数据 $5\sim 16$ 无额外约束。

### 样例解释
在此示例中，Bessie 可以通过六种方式选择指令：
```
(-2,0) (3,0) (4,0) (0,10) (0,-10) (0,10) (1 2 3 5 6 7)

(-2,0) (3,0) (4,0) (0,10) (1 2 3 5)

(-2,0) (3,0) (4,0) (0,10) (1 2 3 7)

(5,0) (0,10) (0,-10) (0,10) (4 5 6 7)

(5,0) (0,10) (4 5)

(5,0) (0,10) (4 7)
```
对于第一种方式，机器人的路径如下所示：

$(0,0) \to (-2,0) \to (1,0) \to (5,0) \to (5,10) \to (5,0) \to (5,10)$


---

---
title: "[蓝桥杯 2023 省 A] 买瓜"
layout: "post"
diff: 提高+/省选-
pid: P9234
tag: ['2023', 'O2优化', '蓝桥杯省赛', '折半搜索 meet in the middle']
---
# [蓝桥杯 2023 省 A] 买瓜
## 题目描述

小蓝正在一个瓜摊上买瓜。瓜摊上共有 $n$ 个瓜，每个瓜的重量为 $A_i$。小蓝刀功了得，他可以把任何瓜劈成完全等重的两份，不过每个瓜只能劈一刀。

小蓝希望买到的瓜的重量的和恰好为 $m$。

请问小蓝至少要劈多少个瓜才能买到重量恰好为 $m$ 的瓜。如果无论怎样小蓝都无法得到总重恰好为 $m$ 的瓜，请输出 $-1$。
## 输入格式

输入的第一行包含两个整数 $n,m$，用一个空格分隔，分别表示瓜的个数和小蓝想买到的瓜的总重量。

第二行包含 $n$ 个整数 $A_i$，相邻整数之间使用一个空格分隔，分别表示每个瓜的重量。
## 输出格式

输出一行包含一个整数表示答案。
## 样例

### 样例输入 #1
```
3 10
1 3 13
```
### 样例输出 #1
```
2
```
## 提示

#### 【评测用例规模与约定】

对于 $20 \%$ 的评测用例，$n \leq 10$;

对于 $60 \%$ 的评测用例，$n \leq 20$;

对于所有评测用例，$1 \leq n \leq 30$，$1 \leq A_i \leq 10^9$，$1 \leq m \leq 10^9$。


---

