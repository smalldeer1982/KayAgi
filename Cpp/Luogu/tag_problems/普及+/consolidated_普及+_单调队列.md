---
title: "Choose"
layout: "post"
diff: 普及+/提高
pid: P10059
tag: ['贪心', '二分', '单调队列', '洛谷原创', 'O2优化', '前缀和', 'ST 表', '洛谷月赛']
---
# Choose
## 题目背景

[加强版](https://www.luogu.com.cn/problem/U397746)

对于一个长度为 $n$ 的序列 $a$ ，定义 $a$ 的极差表示 $a$ 中最大值与最小值之差；定义 $C(a,l,r)$ 表示 $a$ 的**连续**子序列 $[a_l,a_{l+1},\dots,a_r]$，其中 $1\le l\le r\le n$。
## 题目描述

给定一个长度为 $n$ 的序列 $a$。

你需要选出 $a$ 的 $k$ 个长度均为 $L$ $(1\le L\le n-k+1)$ 的不同**连续**子序列 
$C(a,l_1,l_1+L-1),C(a,l_2,l_2+L-1),\dots,C(a,l_k,l_k+L-1)$，其中 $1\le l_1<l_2< \dots< l_k\le n-L+1$。

记这 $k$ 个子序列中极差的最小值为 $X$，你需要求出 $X$ 的最大值。同时，你还需要求出，在满足 $X$ 最大的情况下  $L$ 的最小值。
## 输入格式

**本题有多组测试数据。**

第一行一个整数 $T$，表示测试数据组数。

对于每组测试数据：

- 第一行两个整数 $n,k$。
- 第二行 $n$ 个整数 $a_1,a_2,...,a_n$。
## 输出格式

对于每组测试数据：

- 一行两个整数 $X,L$，表示所求极差和子序列长度。
## 样例

### 样例输入 #1
```
3
5 1
1 2 3 4 5
5 2
1 2 3 4 5
5 3
1 2 3 4 5
```
### 样例输出 #1
```
4 5
3 4
2 3
```
### 样例输入 #2
```
2
5 1
1 2 2 2 3
5 2
1 2 2 2 3
```
### 样例输出 #2
```
2 5
1 2
```
## 提示

**【样例 1 解释】**

- $k=1$ 时，极差最大不超过 $4$，此时满足长度最短的一种方案为 $[1,2,3,4,5]$。
- $k=2$ 时，极差最大不超过 $3$，此时满足长度最短的一种方案为 $[1,2,3,4],[2,3,4,5]$。
- $k=3$ 时，极差最大不超过 $2$，此时满足长度最短的一种方案为 $[1,2,3],[2,3,4],[3,4,5]$。

**【数据规模与约定】**

**本题采用捆绑测试。**

| 子任务 | 分值 | $n\le$ | $k\le$ | 特殊性质 |
| :----------: | :----------: | :----------: | :----------: | :----------: |
| $1$ | $5$ | $10^5$ | $n$ | $a_i$ 均相等 |
| $2$ | $5$ | $10^5$ | $1$ | 数据随机生成 |
| $3$ | $10$ | $100$ | $n$ | 所求的 $X$ 不超过 $10^3$ |
| $4$ | $20$ | $100$ | $n$ | 无 |
| $5$ | $20$ | $10^4$ | $n$ | 无 |
| $6$ | $40$ | $10^5$ | $n$ | 无 |

对于 $100\%$ 的数据，$1\le T\le 10$，$1\le n\le 10^5$，$1\le k\le n$，$-10^9\le a_i\le 10^9$。


---

---
title: "[ROIR 2022] 跳跃机器人 (Day 1)"
layout: "post"
diff: 普及+/提高
pid: P10087
tag: ['动态规划 DP', '数学', '树形数据结构', '线段树', '线性数据结构', '树状数组', '单调队列', '2022', 'Special Judge', '\ufeff基础算法', '动态规划优化', '队列', '其它技巧', 'ROIR（俄罗斯）']
---
# [ROIR 2022] 跳跃机器人 (Day 1)
## 题目背景

翻译自 [ROIR 2022 D1T2](https://neerc.ifmo.ru/school/archive/2021-2022/ru-olymp-regional-2022-day1.pdf)。

某公司正在开发一种跳跃机器人。为了测试机器人，他们在一个多边形平台上设置了一个由 $n$ 个特殊平台组成的环形路线，平台从 $1$ 到 $n$ 编号。第 $i$ 个平台与 $i+1$ 个平台之间的距离为 $d_i$，最后一个平台与第一个平台之间的距离为 $d_n$（假设长度分别为 $d_1,d_2,\dots,d_n$ 的边可以组成一个 $n$ 边形）。

机器人配备了人工智能，在测试过程中学习跳得更远。在任何时刻，机器人通过一个整数 $a$ 来表示它的灵敏度。如果 $a$ 大于等于 $d_i$，机器人可以从平台 $i$ 跳到平台 $i+1$；同样地，如果 $a$ 大于等于 $d_n$，机器人可以从最后一个平台跳到第一个平台。每次跳跃后，机器人的灵敏度增加 $1$。
## 题目描述

机器人的开发人员选择一个平台作为起始平台。如果机器人可以完成 $n$ 次跳跃，回到原来的平台，他们认为实验是成功的。开发人员需要确定机器人的最小起始灵敏度是多少，并选择哪个平台作为起始平台。
## 输入格式

第一行包含一个整数 $n$。

第二行包含一个整数 $f$。

- 如果 $f = 1$，则第三行包含 $n$ 个整数 $d_1, d_2, \dots , d_n$，意义见题目背景。
- 如果 $f = 2$，则第三行包含一个整数 $m$，以及三个整数 $x,y,z$。第四行包含 $m$ 个整数 $c_1, c_2, \dots , c_m$。此时距离值 $d_i$ 根据以下公式计算：
   - 如果 $1 \le i \le m$，则 $d_i = c_i$。
   - 如果 $m + 1 \le i \le n$，则 $d_i = ((x \times d_{i−2} + y \times d_{i−1} + z) \bmod 10^9) + 1$。
## 输出格式

输出两个整数，即最小允许的起始灵敏度 $a$ 和可用于放置机器人的起始平台编号。如果有多个最小起始灵敏度对应的起始平台，可以输出任意一个。
## 样例

### 样例输入 #1
```
5
1
3 7 4 2 5
```
### 样例输出 #1
```
4 3
```
### 样例输入 #2
```
10
2
5 1 2 3
1 2 3 4 5
```
### 样例输出 #2
```
653 1
```
## 提示

样例说明：

在第二个示例中，距离数组为 $[1, 2, 3, 4, 5, 18, 45, 112, 273, 662]$。

根据公式计算 $d_6$ 到 $d_{10}$ 的值：

- $d_6 = ((1 \cdot d_4 + 2 \cdot d_5 + 3) \bmod 10^9) + 1 = ((1 \cdot 4 + 2 \cdot 5 + 3) \bmod 10^9) + 1 = 18$；
- $d_7 = ((1 \cdot d_5 + 2 \cdot d_6 + 3) \bmod 10^9) + 1 = ((1 \cdot 5 + 2 \cdot 18 + 3) \bmod 10^9) + 1 = 45$；
- $d_8 = ((1 \cdot d_6 + 2 \cdot d_7 + 3) \bmod 10^9) + 1 = ((1 \cdot 18 + 2 \cdot 45 + 3) \bmod 10^9) + 1 = 112$；
- $d_9 = ((1 \cdot d_7 + 2 \cdot d_8 + 3) \bmod 10^9) + 1 = ((1 \cdot 45 + 2 \cdot 112 + 3) \bmod 10^9) + 1 = 273$；
- $d_{10} = ((1 \cdot d_8 + 2 \cdot d_9 + 3) \bmod 10^9) + 1 = ((1 \cdot 112 + 2 \cdot 273 + 3) \bmod 10^9) + 1 = 662$。

本题使用捆绑测试。

| 子任务 | 分值 | 特殊性质 |
| :----------: | :----------: | :----------: |
| $0$ | $15$ | $n\le300,f=1,d\le300$ |
| $1$ | $17$ | $n\le5000,f=2$ |
| $2$ | $10$ | $n\le100000,f=1$ 且保证从第一个平台开始跳是最佳选择 |
| $3$ | $20$ | $n\le100000,f=1$ |
| $4$ | $5$ | $f=2$ 且保证从第一个平台开始跳是最佳选择 |
| $5$ | $33$ | $f=2$ |

对于 $100\%$ 的数据，$3 \le n \le 10^7$。当 $f=1$ 时 $1 \le d_i \le 10^9$，当 $f=2$ 时 $2 \le m \le \min(n, 10^5)$，$0 \le x, y, z \le 10^9$，$1 \le c_i \le 10^9$。

注：本题的算法标签部分参考了官方题解中用到的解法。


---

---
title: "『SpOI - R1』Double Champions"
layout: "post"
diff: 普及+/提高
pid: P10793
tag: ['动态规划 DP', '贪心', '单调队列', 'O2优化', '排序']
---
# 『SpOI - R1』Double Champions
## 题目描述

**本题包含多组数据。**

现在有若干个格子排在一行上。

再给出 $n$ 个区间，每个区间 $i$ 可以覆盖 $[l_i,r_i]$ 这个区间中的每一个格子（例如，区间 $[1,2]$ 可以覆盖格子 $1,2$）。

现在需要把这些区间分组，每个组带来的贡献为所有其旗下的区间的交的总长度。

你需要求出最少把这些区间分成多少组，才能使得每一组的贡献都 $\geq w$。如果不存在任何方案满足条件，输出 `No`。
## 输入格式

第一行一个整数 $T$，表示数据组数。

对于每组数据，第一行两个整数 $n,w$。

接下来 $n$ 行，每一行两个整数 $l_i,r_i$，描述一个区间。
## 输出格式

对于每组数据，输出一行一个答案，表示最少要分的组数，或者字符串 `No`，表示无解。
## 样例

### 样例输入 #1
```
2
5 3 
6 10
6 8 
3 5 
7 9 
1 9
5 5
5 10
3 8
6 10
4 10
5 9
```
### 样例输出 #1
```
3
3
```
## 提示

#### 样例 #1 解释

按照输入顺序将输入的区间依次编号为 $①,②,③,④,⑤$。

可以将 $5$ 个区间分为以下 $3$ 组：$\{①,④\},\{②\},\{③⑤\}$。这样每一组的贡献即交集大小分别为 $3,3,3$，符合对每组贡献 $\geq 3$ 的要求。可以证明，$3$ 组是所有符合条件的区间划分方案中组数最少的。

### 数据范围

**请注意常数因子对程序效率的影响。**

**本题开启捆绑测试和子任务依赖。**

对于 $100\%$ 的数据，$1\leq T\leq 20$，$1\leq n\leq 2\times 10^5$，$0\leq w\leq 10^6$，$1\leq l_i\leq r_i\leq 10^6$。

| Subtask | $n\leq$ | $w,l_i,r_i\leq$ | 得分 | 子任务依赖 |
| :----------: | :----------: | :----------: | :----------: | :----------: |
| 1 | $8$ | $15$ | $10$ | 无 |
| 2 | $11$ | $20$ | $10$ | 1 |
| 3 | $1.5\times 10^3$ | $10^4$ | $25$ | 1,2 |
| 4 | $2\times 10^5$ | $10^6$ | $55$ | 1,2,3 |


---

---
title: "扶苏出勤日记"
layout: "post"
diff: 普及+/提高
pid: P12000
tag: ['二分', '单调队列', '洛谷原创', 'O2优化', 'ST 表', '洛谷月赛']
---
# 扶苏出勤日记
## 题目描述

扶苏是一个舞萌吃。在接下来的 $n$ 天里，她每天都要去玩舞萌，并且她希望每天**游玩的局数相同**。

游玩一局舞萌固定花费 $1$ 个游戏币。然而，游戏币每天的价格都有可能变化。具体来说，在第 $i$ 天，一元可以购买 $a_i$ 个游戏币。

靠着给洛谷打~~黑~~工，扶苏每天都会有一些收入。她会在第 $i$ 天收入 $b_i$ 元。

每天，扶苏会**先**得到当天的收入 $b_i$ 元，再去购买游戏币，再游玩舞萌。

扶苏每天可以使用自己拥有的钱的任意金额按照当天的币价购买游戏币。也就是说，她不必一次性换光所有的钱，可以在当天只使用一部分钱购买游戏币，存下一些剩余的钱留在今后的若干天购买游戏币。同时，她一天不必花光所有的游戏币，可以只在当天花费一部分游戏币，存下一些剩余的游戏币在之后的若干天玩。

扶苏知道今后 $n$ 天的币价和她每天的收入，她想在接下来 $n$ 天里每天游玩相同局数的舞萌。因此她想知道，在她使用最优策略购买游戏币的情况下，她每天最多可以游玩多少局舞萌？
## 输入格式

**本题单个测试点内有多组测试数据**。第一行是一个正整数 $T$，表示数据组数。对每组数据：

第一行是一个整数 $n$，表示总天数。  
第二行是 $n$ 个整数 $a_1, a_2, \dots ,a_n$，表示每天一元钱购买的币数。  
第三行是 $n$ 个整数 $b_1, b_2, \dots ,b_n$，表示扶苏每天的收入。  
## 输出格式

对每组测试数据，输出一行一个整数表示答案。
## 样例

### 样例输入 #1
```
3
5
1 2 3 4 5
5 4 3 2 1
5
1 1 1 1 1
2 3 4 5 6
9
9 9 8 2 4 4 3 5 3
10 10 10 10 10 10 10 10 10
```
### 样例输出 #1
```
5
2
55
```
## 提示

### 数据规模与约定

用 $N$ 表示单个测试点内 $n$ 的和。
- 对 $20\%$ 的数据，保证 $1 \leq n \leq 3$，$N \leq 1000$；
- 对 $40\%$ 的数据，保证 $1\le n \le 2000$，$N \leq 10000$；
- 对 $60\%$ 的数据，满足 $1\le n \le 10^5$，$N \leq 2 \times 10^5$；
- 另有 $10\%$ 的数据，满足 $a_i \geq a_{i + 1}$（对 $1 \leq i \leq n-1$）。
- 另有 $10\%$ 的数据，满足 $a_i \leq a_{i + 1}$（对 $1 \leq i \leq n-1$）。
- 对于 $100\%$ 的数据，满足 $1\le n\le 10^6$，$1\le a_i \le 1000$，$1\le b_i \le 10^9$，$n \leq N \leq 2 \times 10^6$，$1 \leq T \leq 2 \times 10^6$。



---

---
title: "[蓝桥杯 2023 国 Java B] 游戏"
layout: "post"
diff: 普及+/提高
pid: P12225
tag: ['单调队列', '2023', '期望', '蓝桥杯国赛']
---
# [蓝桥杯 2023 国 Java B] 游戏
## 题目描述

熊大和熊二在玩游戏。他们将 $n$ 个正整数 $a_1, a_2, \dots, a_n$ 排成一行，然后各用一个长度为 $k$ 的框在这个数组中各自随机框选出一段长度为 $k$ 的连续子序列（随机框选指在合法的 $n - k + 1$ 个连续子序列中均匀随机）。熊大记录了他框出的 $k$ 个数中的最大值 $P$，熊二记录了他框出的 $k$ 个数的最小值 $Q$，他们突然有个疑问：$P - Q$ 的期望是多少？
## 输入格式

输入共 $2$ 行。

第一行为两个正整数 $n, k$。

第二行为 $n$ 个由空格隔开的正整数 $a_1, a_2, \dots, a_n$。
## 输出格式

输出共 $1$ 行，一个浮点数（请保留两位小数）。
## 样例

### 样例输入 #1
```
3 2
1 2 3
```
### 样例输出 #1
```
1.00
```
## 提示

### 样例说明

一共有四种情况：

- 熊大框出 $[1, 2]$，$P = 2$；熊二框出 $[1, 2]$，$Q = 1$，$P - Q = 1$。
- 熊大框出 $[1, 2]$，$P = 2$；熊二框出 $[2, 3]$，$Q = 2$，$P - Q = 0$。
- 熊大框出 $[2, 3]$，$P = 3$；熊二框出 $[1, 2]$，$Q = 1$，$P - Q = 2$。
- 熊大框出 $[2, 3]$，$P = 3$；熊二框出 $[2, 3]$，$Q = 2$，$P - Q = 1$。

所以 $P - Q$ 的期望为 $(1 + 0 + 2 + 1) / 4 = 1.00$。

### 评测用例规模与约定

- 对于 $20\%$ 的数据，保证 $n \leq 10^2$。
- 对于 $40\%$ 的数据，保证 $n \leq 10^3$。
- 对于 $100\%$ 的数据，保证 $n \leq 10^5$，$0 < a_i \leq 10^9$，$0 < k \leq n$。


---

---
title: "[蓝桥杯 2025 国 C] 数列染色"
layout: "post"
diff: 普及+/提高
pid: P12882
tag: ['动态规划 DP', '单调队列', '2025', '动态规划优化', '蓝桥杯国赛']
---
# [蓝桥杯 2025 国 C] 数列染色
## 题目描述

有一个长度为 $n$ 的数列 $(a_1, a_2, \cdots, a_n)$，初始时只有 $a_1$ 和 $a_n$ 是黑色的，其它数都是白色的。小蓝可以选择若干白色的数将其染黑，但是必须满足相邻的两个黑色的数之间最多包含 $k$ 个白色的数，他想让所有黑色的数的和尽可能小，请问他最少可以让所有黑色的数的和为多少。
## 输入格式

输入的第一行包含两个整数 $n, k$，用一个空格分隔。

第二行包含 $n$ 个正整数 $a_1, a_2, \cdots, a_n$，相邻整数之间使用一个空格分隔。

## 输出格式

输出一行包含一个整数表示答案。
## 样例

### 样例输入 #1
```
8 2
5 2 7 5 5 9 3 7
```
### 样例输出 #1
```
19
```
## 提示

**【样例说明】**

选择染黑 $a_2, a_5$，黑色的数的和为 $5 + 2 + 5 + 7 = 19$。

**【评测用例规模与约定】**

对于 $20\%$ 的评测用例，$1 \leq n \leq 10$；

对于 $50\%$ 的评测用例，$1 \leq n \leq 5000$；

对于所有评测用例，$0 \leq k < n \leq 10^5$，$1 \leq a_i \leq 10^6$。



---

---
title: "[GCJ 2010 #1A] Make it Smooth"
layout: "post"
diff: 普及+/提高
pid: P13391
tag: ['动态规划 DP', '2010', '单调队列', 'Google Code Jam']
---
# [GCJ 2010 #1A] Make it Smooth
## 题目描述

You have a one-dimensional array of $N$ pixels. Each pixel has a value, represented by a number between 0 and 255, inclusive. The distance between two pixels is the absolute difference of their numbers.

You can perform each of the following operations zero or more times:

1. With cost $D$, delete any pixel, so its original neighbors become neighboring pixels.
2. With cost $I$, insert one pixel of any value into any position -- either between two existing pixels, or before the first pixel, or after the last pixel.
3. You can change the value of any pixel. The cost is the absolute difference of the old value of the pixel and the new value of the pixel.

The array is smooth if any neighboring pixels have distance at most $M$. Find the minimum possible cost of a sequence of operations that makes the array smooth.

Note: The empty array -- the array containing no pixels -- is considered to be smooth.
## 输入格式

The first line of the input gives the number of test cases, $T$. $T$ test cases follow, each with two lines. The first line is in the form "D I M N", the next line contains $N$ numbers $a_i$: the values of the pixels from left to the right.

## 输出格式

For each test case, output one line containing "Case #x: y", where $x$ is the case number (starting from 1), and $y$ is the minimum cost to make the input array smooth.
## 样例

### 样例输入 #1
```
2
6 6 2 3
1 7 5
100 1 5 3
1 50 7
```
### 样例输出 #1
```
Case #1: 4
Case #2: 17
```
## 提示

**Sample Explanation**

In Case #1, decreasing the $7$ to $3$ costs $4$ and is the cheapest solution. In Case #2, deleting is extremely expensive; it's cheaper to insert elements so your final array looks like $[1, 6, 11, 16, 21, 26, 31, 36, 41, 46, 50, 45, 40, 35, 30, 25, 20, 15, 10, 7]$.

**Limits**

- All the numbers in the input are integers.
- $1 \leqslant T \leqslant 100$
- $0 \leqslant D, I, M, a_i \leqslant 255$

**Small dataset (12 Pts, Test set 1 - Visible)**

- $1 \leqslant N \leqslant 3$.

**Large dataset (24 Pts, Test set 2 - Hidden)**

- $1 \leqslant N \leqslant 100$.



---

---
title: "寻找段落"
layout: "post"
diff: 普及+/提高
pid: P1419
tag: ['二分', '单调队列']
---
# 寻找段落
## 题目描述

给定一个长度为 $n$ 的序列 $a$，定义 $a_i$ 为第 $i$ 个元素的价值。现在需要找出序列中最有价值的“段落”。段落的定义是长度在 $[S, T]$ 之间的连续序列。最有价值段落是指平均值最大的段落。

**段落的平均值** 等于 **段落总价值** 除以 **段落长度**。
## 输入格式

第一行一个整数 $n$，表示序列长度。

第二行两个整数 $S$ 和 $T$，表示段落长度的范围，在 $[S, T]$ 之间。

第三行到第 $n+2$ 行，每行一个整数表示每个元素的价值指数。
## 输出格式

一个实数，保留 $3$ 位小数，表示最优段落的平均值。
## 样例

### 样例输入 #1
```
3

2 2

3

-1

2


```
### 样例输出 #1
```
1.000
```
## 提示

【数据范围】

对于 $30\%$ 的数据有 $n \le 1000$。

对于 $100\%$ 的数据有 $1 \le n \le 100000$，$1 \le S \le T \le n$，$-{10}^4 \le a_i \le {10}^4$。

【题目来源】

tinylic 改编



---

---
title: "琪露诺"
layout: "post"
diff: 普及+/提高
pid: P1725
tag: ['动态规划 DP', '单调队列', '优先队列']
---
# 琪露诺
## 题目描述

在幻想乡，琪露诺是以笨蛋闻名的冰之妖精。

某一天，琪露诺又在玩速冻青蛙，就是用冰把青蛙瞬间冻起来。但是这只青蛙比以往的要聪明许多，在琪露诺来之前就已经跑到了河的对岸。于是琪露诺决定到河岸去追青蛙。

小河可以看作一列格子依次编号为 $0$ 到 $N$，琪露诺只能从编号小的格子移动到编号大的格子。而且琪露诺按照一种特殊的方式进行移动，当她在格子 $i$ 时，她只移动到区间 $[i+L,i+R]$ 中的任意一格。你问为什么她这么移动，这还不简单，因为她是笨蛋啊。

每一个格子都有一个冰冻指数 $A_i$，编号为 $0$ 的格子冰冻指数为 $0$。当琪露诺停留在那一格时就可以得到那一格的冰冻指数 $A_i$。琪露诺希望能够在到达对岸时，获取最大的冰冻指数，这样她才能狠狠地教训那只青蛙。

但是由于她实在是太笨了，所以她决定拜托你帮它决定怎样前进。

开始时，琪露诺在编号 $0$ 的格子上，只要她下一步的位置编号大于 $N$ 就算到达对岸。

## 输入格式

第一行三个正整数 $N, L, R$。

第二行共 $N+1$ 个整数，第 $i$ 个数表示编号为 $i-1$ 的格子的冰冻指数 $A_{i-1}$。

## 输出格式

一个整数，表示最大冰冻指数。

## 样例

### 样例输入 #1
```
5 2 3
0 12 3 11 7 -2

```
### 样例输出 #1
```
11


```
## 提示

对于 $60\%$ 的数据，$N \le 10^4$。

对于 $100\%$ 的数据，$N \le 2\times 10^5$，$-10^3 \le  A_i\le 10^3 $，$1 \le L \le R \le N $。数据保证最终答案不超过 $2^{31}-1$。



---

---
title: "宝物筛选"
layout: "post"
diff: 普及+/提高
pid: P1776
tag: ['动态规划 DP', '单调队列', 'NOI 导刊', '背包 DP', '进制']
---
# 宝物筛选
## 题目描述

终于，破解了千年的难题。小 FF 找到了王室的宝物室，里面堆满了无数价值连城的宝物。

这下小 FF 可发财了，嘎嘎。但是这里的宝物实在是太多了，小 FF 的采集车似乎装不下那么多宝物。看来小 FF 只能含泪舍弃其中的一部分宝物了。

小 FF 对洞穴里的宝物进行了整理，他发现每样宝物都有一件或者多件。他粗略估算了下每样宝物的价值，之后开始了宝物筛选工作：小 FF 有一个最大载重为 $W$ 的采集车，洞穴里总共有 $n$ 种宝物，每种宝物的价值为 $v_i$，重量为 $w_i$，每种宝物有 $m_i$ 件。小 FF 希望在采集车不超载的前提下，选择一些宝物装进采集车，使得它们的价值和最大。
## 输入格式

第一行为一个整数 $n$ 和 $W$，分别表示宝物种数和采集车的最大载重。

接下来 $n$ 行每行三个整数 $v_i,w_i,m_i$。
## 输出格式

输出仅一个整数，表示在采集车不超载的情况下收集的宝物的最大价值。
## 样例

### 样例输入 #1
```
4 20
3 9 3
5 9 1
9 4 2
8 1 3
```
### 样例输出 #1
```
47
```
## 提示

对于 $30\%$ 的数据，$n\leq \sum m_i\leq 10^4$，$0\le W\leq 10^3$。

对于 $100\%$ 的数据，$n\leq \sum m_i \leq 10^5$，$0\le W\leq 4\times 10^4$，$1\leq n\le 100$。


---

---
title: "选择数字"
layout: "post"
diff: 普及+/提高
pid: P2034
tag: ['动态规划 DP', '单调队列']
---
# 选择数字
## 题目描述

给定一行 $n$ 个非负整数 $a_1 \cdots a_n$。现在你可以选择其中若干个数，但不能有超过 $k$ 个连续的数字被选择。你的任务是使得选出的数字的和最大。
## 输入格式

第一行两个整数 $n$，$k$。

以下 $n$ 行，每行一个整数表示 $a_i$。
## 输出格式

输出一个值表示答案。

## 样例

### 样例输入 #1
```
5 2
1
2
3
4
5 

```
### 样例输出 #1
```
12
```
## 提示

对于 $20\%$ 的数据，$n \le 10$。

对于另外 $20\%$ 的数据，$k=1$。

对于 $60\%$ 的数据，$n \le 1000$。

对于 $100\%$ 的数据，$1 \le n \le 100000$，$1 \le k \le n$，$0 \le $ 数字大小 $ \le 1,000,000,000$。

时间限制 $500$ ms。


---

---
title: "[HAOI2007] 理想的正方形"
layout: "post"
diff: 普及+/提高
pid: P2216
tag: ['2007', '河南', '各省省选', '单调队列', '队列']
---
# [HAOI2007] 理想的正方形
## 题目描述

有一个 $a \times b$ 的整数组成的矩阵，现请你从中找出一个 $n \times n$ 的正方形区域，使得该区域所有数中的最大值和最小值的差最小。
## 输入格式

第一行为 $3$ 个整数，分别表示 $a,b,n$ 的值。

第二行至第 $a+1$ 行每行为 $b$ 个非负整数，表示矩阵中相应位置上的数。每行相邻两数之间用一空格分隔。
## 输出格式

仅一个整数，为 $a \times b$ 矩阵中所有“ $n \times n$ 正方形区域中的最大整数和最小整数的差值”的最小值。
## 样例

### 样例输入 #1
```
5 4 2
1 2 5 6
0 17 16 0
16 17 2 1
2 10 2 1
1 2 2 2

```
### 样例输出 #1
```
1
```
## 提示

矩阵中的所有数都不超过 $1,000,000,000$。

$20\%$ 的数据 $2 \le a,b \le 100,n \le a,n \le b,n \le 10$。

$100\%$ 的数据 $2 \le a,b \le 1000,n \le a,n \le b,n \le 100$。


---

---
title: "良好的感觉"
layout: "post"
diff: 普及+/提高
pid: P2422
tag: ['动态规划 DP', '单调队列']
---
# 良好的感觉
## 题目描述

kkk 做了一个人体感觉分析器。每一天，人都有一个感受值 $A_i$，$A_i$ 越大，表示人感觉越舒适。在一段时间 $\left[i, j\right]$ 内，人的舒适程度定义为 $\left[i, j\right]$ 中最不舒服的那一天的感受值 $\times$ $\left[i, j\right]$中每一天感受值的和。现在给出 kkk 在连续 $N$ 天中的感受值，请问，在哪一段时间，kkk 感觉最舒适？

## 输入格式

第一行为 $N$，代表数据记录的天数。

第二行 $N$ 个整数，代表每一天的感受值。
## 输出格式

一行，表示在最舒适的一段时间中的感受值。

## 样例

### 样例输入 #1
```
6
3 1 6 4 5 2
```
### 样例输出 #1
```
60
```
## 提示

kkk 最开心的一段时间是第 $3$ 天到第 $5$ 天，开心值：$(6+4+5)\times4=60$。

对于 $30\%$ 的数据，$1\le N\le 100$。

对于 $70\%$ 的数据，$1\le N\le 2000$。

对于 $100\%$ 的数据，$1\le N\le 100000$，$1\le \texttt{感受值}\le 1000000$。


---

---
title: "[SCOI2009] 生日礼物"
layout: "post"
diff: 普及+/提高
pid: P2564
tag: ['2009', '四川', '各省省选', '单调队列', '队列']
---
# [SCOI2009] 生日礼物
## 题目背景

四川2009NOI省选

## 题目描述


小西有一条很长的彩带，彩带上挂着各式各样的彩珠。已知彩珠有 $N$ 个，分为 $K$ 种。简单的说，可以将彩带抽象为一个 x 轴，每一个彩珠有一个对应的坐标（即位置）。某些坐标上可以没有彩珠，但多个彩珠也可以出现在同一个位置上。

小布的生日快到了，于是小西打算剪一段彩带送给小布。为了让礼物彩带足够漂亮，小西希望这一段彩带中能包含所有种类的彩珠。同时，为了方便，小西希望这段彩带尽可能短，你能帮助小西计算这个最短的长度么？

彩带的长度即为彩带开始位置到结束位置的位置差。

## 输入格式

第一行包含两个整数 $N, K$，分别表示彩珠的总数以及种类数。

接下来 $K$ 行，每行第一个数为 $T_i$，表示第 $i$ 种彩珠的数目。

接下来按升序给出 $T_i$ 个非负整数，为这 $T_i$ 个彩珠分别出现的位置。
## 输出格式

输出应包含一行，为最短彩带长度。

## 样例

### 样例输入 #1
```
6 3
1 5
2 1 7
3 1 3 8

```
### 样例输出 #1
```
3
```
## 提示


### 样例说明

有多种方案可选，其中比较短的是 $1 \sim 5$ 和 $5 \sim 8$。后者长度为 $3$，更短，故答案为 $3$。

### 数据范围

对于 $50\%$ 的数据，$N \le 10^4$；

对于 $80\%$ 的数据，$N \le 8 \times 10^5$；

对于 $100\%$ 的数据，$1 \le N \le 10^6, 1 \le K \le 60$，$0 \le$ 珠子位置 $< 2^{31}$，且 $\sum T_i = N$。


---

---
title: "[USACO11OPEN] Mowing the Lawn G"
layout: "post"
diff: 普及+/提高
pid: P2627
tag: ['动态规划 DP', '2011', 'USACO', '单调队列']
---
# [USACO11OPEN] Mowing the Lawn G
## 题目描述

在一年前赢得了小镇的最佳草坪比赛后，Farmer John 变得很懒，再也没有修剪过草坪。现在，新一轮的最佳草坪比赛又开始了，Farmer John 希望能够再次夺冠。

然而，Farmer John 的草坪非常脏乱，因此，Farmer John 只能够让他的奶牛来完成这项工作。Farmer John 有 $N$（$1\le N\le 10^5$）只排成一排的奶牛，编号为 $1\ldots N$。每只奶牛的效率是不同的，奶牛 $i$ 的效率为 $E_i$（$0\le E_i\le 10^9$）。

靠近的奶牛们很熟悉，因此，如果 Farmer John安排超过 $K$ 只连续的奶牛，那么，这些奶牛就会罢工去开派对 :)。因此，现在 Farmer John 需要你的帮助，计算 FJ 可以得到的最大效率，并且该方案中没有连续的超过 $K$ 只奶牛。
## 输入格式

第一行：空格隔开的两个整数 $N$ 和 $K$。

第二到 $N+1$ 行：第 $i+1$ 行有一个整数 $E_i$。
## 输出格式

第一行：一个值，表示 Farmer John 可以得到的最大的效率值。
## 样例

### 样例输入 #1
```
5 2
1
2
3
4
5

```
### 样例输出 #1
```
12

```


---

---
title: "好消息，坏消息"
layout: "post"
diff: 普及+/提高
pid: P2629
tag: ['线性数据结构', '单调队列', '前缀和', '队列']
---
# 好消息，坏消息
## 题目描述

Uim 在公司里面当秘书，现在有 $n$ 条消息要告知老板。每条消息有一个好坏度，这会影响老板的心情。告知完一条消息后，老板的心情等于老板之前的心情加上这条消息的好坏度。最开始老板的心情是 $0$，一旦老板心情到了 $0$ 以下就会勃然大怒，炒了 Uim 的鱿鱼。

Uim 为了不被炒，提前知道了这些消息（已经按时间的发生顺序进行了排列）的好坏度，希望知道如何才能不让老板发怒。

Uim 必须按照事件的发生顺序逐条将消息告知给老板。不过 Uim 可以使用一种叫 “倒叙” 的手法，例如有 $n$ 条消息，Uim 可以按 $k,k+1,k+2,\ldots,n,1,2,\ldots,k-1$（事件编号）这种顺序通报。

他希望知道，有多少个 $k$，可以使从 $k$ 号事件开始通报到 $n$ 号事件然后再从 $1$ 号事件通报到 $k-1$ 号事件可以让老板不发怒。
## 输入格式

第一行一个整数 $n$（$1 \le n \le10^6$），表示有 $n$ 个消息。

第二行 $n$ 个整数，按时间顺序给出第 $i$ 条消息的好坏度 $A_i$（$-10^3\le A_i \le 10^3$）。
## 输出格式

一行一个整数，表示可行的方案个数。
## 样例

### 样例输入 #1
```
4
-3 5 1 2

```
### 样例输出 #1
```
2


```
## 提示

**【样例解释】**

通报事件的可行顺序（用编号表示）为 $2\rightarrow3\rightarrow4\rightarrow1$ 或 $3\rightarrow4\rightarrow1\rightarrow2$（分别对应 $k=2$ 和 $k=3$）

通报事件的可行顺序（用好坏度表示）为 $5\rightarrow1\rightarrow2\rightarrow(-3)$ 或 $1\rightarrow2\rightarrow(-3)\rightarrow5$

**【数据范围】**

对于 $25\%$ 的数据，$n\le10^3$；  
对于 $75\%$ 的数据，$n\le10^4$；  
对于 $100\%$ 的数据，$1 \le n\le 10^6$。


---

---
title: "[USACO09OPEN] Grazing2 S"
layout: "post"
diff: 普及+/提高
pid: P2954
tag: ['动态规划 DP', '递推', '2009', 'USACO', '单调队列']
---
# [USACO09OPEN] Grazing2 S
## 题目描述

Farmer John has N (2 <= N <= 1,500) prize milk cows conveniently numbered 1..N. His newly-painted barn has S (N <= S <= 1,000,000) stalls (conveniently numbered 1..S) in a single long line; each stall is a unit distance from its neighboring stall(s).

The cows have made their way to the stalls for a rest; cow i is in stall P\_i. Antisocial as they are, the cows get grumpy if they are situated in stalls very close to each other, so Farmer John wants to move the cows to be as spread out as possible.

FJ wants to make sure that the N - 1 distances between adjacent cows are as large as possible, and he would also like them to be similar to each other (i.e., close to equi-distant spacing).

In particular, FJ would like all distances between adjacent cows to be at most 1 different from (S - 1) / (N - 1), where integer division is used. Moreover, he would like as many of these distances as possible to be exactly equal to (S - 1) / (N - 1) [integer

division]. Thus, with four cows and eight stalls, one can place the cows at positions 1, 3, 5, 8 or 1, 3, 6, 8 but not at 1, 2, 4, 7 or 1, 2, 4, 8.

Help FJ spread the cows as efficiently as possible by calculating and reporting the minimum total distance that the cows have to move in order to achieve proper spacing. Ignore the distance it takes for a cow to enter or exit a stall.

约翰有N(2≤N≤1500)头奶牛，S(N≤S≤1,000,000)个一字排开的牛棚．相邻牛棚间的距离恰好为1．

奶牛们已经回棚休息，第i只奶牛现在待在牛棚Pi．如果两只奶牛离得太近，会让奶牛们变得很暴躁．所以约翰想给一些奶牛换一个棚，让她们之间的距离变得尽量大，并且尽管接近．令d=Trunc((s-1)/(n-1))

所以约翰希望最终的奶牛的状态是：两只相邻奶牛间的距离与d之差不超过1，而且让尽量多的间距等于d．因此，对于4只奶牛8个棚的情况，1，3，5，8或1，3，6，8这样的安置情况是允许的，而1，2，4，7或1，2，4，8这样的情况是不允许的．    帮助约翰移动奶牛，让所有奶牛的移动距离之和最小，同时让最终的安置情况符合约翰心意．

## 输入格式

\* Line 1: Two space-separated integers: N and S

\* Lines 2..N+1: Line i+1 contains the single integer: P\_i

## 输出格式

\* Line 1: A single integer: the minimum total distance the cows have to travel. This number is guaranteed to be under 1,000,000,000 (thus fitting easily into a signed 32-bit integer).

## 样例

### 样例输入 #1
```
5 10 
2 
8 
1 
3 
9 

```
### 样例输出 #1
```
4 

```
## 提示

1   2   3   4   5   6   7   8   9  10

Cow Locs     | A | B | C | . | . | . | . | D | E | . | 

Cows move from stall 2 to 3, 3 to 5, and 9 to 10. The total distance moved is 1 + 2 + 1 = 4. The final positions of the cows are in stalls 1, 3, 5, 8, and 10.

1   2   3   4   5   6   7   8   9  10

Init Stall     | A | B | C | . | . | . | . | D | E | . | 
Final Stall    | A | . | B | . | C | . | . | D | . | E | 
Distance moved | 0 | . | 1 | . | 2 | . | . | 0 | . | 1 | 


---

---
title: "[USACO13NOV] Crowded Cows S"
layout: "post"
diff: 普及+/提高
pid: P3088
tag: ['2013', 'USACO', '单调队列', '队列']
---
# [USACO13NOV] Crowded Cows S
## 题目描述

Farmer John's N cows (1 <= N <= 50,000) are grazing along a one-dimensional fence.  Cow i is standing at location x(i) and has height h(i) (1 <= x(i),h(i) <= 1,000,000,000).

A cow feels "crowded" if there is another cow at least twice her height within distance D on her left, and also another cow at least twice her height within distance D on her right (1 <= D <= 1,000,000,000).  Since crowded cows produce less milk, Farmer John would like to count the number of such cows.  Please help him.

FJ有 $N(1\le N\le50000)$ 头奶牛沿着一维的栅栏吃草，第 $i$ 头奶牛在目标点 $x_i$ ，它的身高是 $h_i (1 \le x_i,h_i\le10^9)$。

当一头奶牛左边 $D(1\le D\le10^9)$ 距离内且右边 $D$ 距离内有身高至少是它的两倍的奶牛，它就会觉得拥挤。

请计算觉得拥挤的奶牛的数量。

## 输入格式

\* Line 1: Two integers, N and D.

\* Lines 2..1+N: Line i+1 contains the integers x(i) and h(i).  The locations of all N cows are distinct.

第一行两个整数 $N,D$。

接下来 $N$ ，每行两个整数 $x_i,h_i$。保证 $x_i$ 互不相同。
## 输出格式

\* Line 1: The number of crowded cows.

一行一个整数，表示觉得拥挤的奶牛的数量。
## 样例

### 样例输入 #1
```
6 4 
10 3 
6 2 
5 3 
9 7 
3 6 
11 2 

```
### 样例输出 #1
```
2 

```
## 提示

There are 6 cows, with a distance threshold of 4 for feeling crowded.  Cow #1 lives at position x=10 and has height h=3, and so on.


The cows at positions x=5 and x=6 are both crowded. 




---

---
title: "[POI 2011] TEM-Temperature"
layout: "post"
diff: 普及+/提高
pid: P3522
tag: ['2011', '单调队列', 'POI（波兰）', '队列']
---
# [POI 2011] TEM-Temperature
## 题目描述

The Byteotian Institute of Meteorology (BIM) measures the air temperature  daily.

The measurement is done automatically, and its result immediately printed.

Unfortunately, the ink in the printer has long dried out...

The employees of BIM however realised the fact only recently, when the    Byteotian Organisation for Meteorology (BOM) requested access to that data.

An eager intern by the name of Byteasar saved the day, as he systematically    noted down the temperatures reported by two domestic alcohol thermometers    placed on the north and south outside wall of the BIM building.

It was established decades ago by various BIM employees that the temperature    reported by the thermometer on the south wall of the building is never lower    than the actual temperature, while that reported by the thermometer on the    north wall of the building is never higher than the actual temperature.

Thus even though the exact temperatures for each day remain somewhat of    a mystery, the range they were in is known at least.

Fortunately for everyone involved (except Byteasar and you, perhaps),    BOM does not require exact temperatures. They only want to know the longest    period in which the temperature was not dropping (i.e. on each successive    day it was no smaller than on the day before).

In fact, the veteran head of BIM knows very well that BOM would like this    period as long as possible.

To whitewash the negligence he insists that Byteasar determines, based on    his valuable notes, the longest period in which the temperature    could have been not dropping.

Now this is a task that Byteasar did not quite expect on his BIM internship,    and he honestly has no idea how to tackle it.

He asks you for help in writing a program that determines the longest such    period.

某国进行了连续 $ n $ ( $ 1 \le n \le 1,000,000 $）天的温度测量，测量存在误差，测量结果是第 $i$ 天温度在 $[l_i,r_i]$ 范围内。

求最长的连续的一段，满足该段内可能温度不降。

## 输入格式

In the first line of the standard input there is one integer  $ n $ ( $ 1 \le n \le 1,000,000 $) that denotes the number of days for which Byteasar took notes on the temperature. The measurements from day are given in the  $ {(i + 1)}$-th line . Each of those lines holds two integers,  $ x $ and  $ y $ ( $ -10^9 \le x \le y \le 10^9 $). These denote, respectively, the minimum and maximum possible temperature on that particular day, as reported by the two thermometers.

In some of the tests, worth 50 points in total, the temperatures never drop below  $ -50 $ degrees (Celsius, in case you wonder!) and never exceeds  $ 50 $ degrees ( $ -50 \le x \le y \le 50 $).
## 输出格式

In the first and only line of the standard output your program should print a single integer, namely the maximum number of days for which the temperature in Byteotia could have been not dropping.

## 样例

### 样例输入 #1
```
6
6 10
1 5
4 8
2 5
6 8
3 5
```
### 样例输出 #1
```
4
```


---

---
title: "Power收集"
layout: "post"
diff: 普及+/提高
pid: P3800
tag: ['动态规划 DP', '单调队列', '洛谷原创', 'O2优化']
---
# Power收集
## 题目背景

据说在红雾异变时，博丽灵梦单身前往红魔馆，用十分强硬的手段将事件解决了。

然而当时灵梦在 Power 达到 MAX 之前，不具有“上线收点”的能力，所以她想要知道她能收集多少 P 点，然而这个问题她答不上来，于是她找到了学 OI 的你。
## 题目描述

可以把游戏界面理解成一个 $N$ 行 $M$ 列的棋盘，有 $K$ 个格子上有 $P$ 点，其价值为 $\operatorname{val}(i,j)$。

初始灵梦可以选择在第一行的任意一个格子出发，每秒她必须下移一格。

灵梦具有一个左右移动的速度 $T$，可以使她每秒向左或右移动至多 $T$ 格，也可以不移动，并且不能折返。移动可视为瞬间完成，不经过路途上的点，只能获得目标格子的 P 点。

求最终她能获得的 POWER 值最大是多少？
## 输入格式

第一行四个数字，$N,M,K,T$。

接下来 $K$ 行每行 $3$ 个数字 $x,y,v$，代表第 $x$ 行第 $y$ 列有一个 $val$ 为 $v$ 的 P 点，数据保证一个格子上最多只有 $1$ 个 P 点。
## 输出格式

一个数字

## 样例

### 样例输入 #1
```
3 3 4 1
1 1 3
1 2 1
2 2 3
3 3 3

```
### 样例输出 #1
```
9
```
## 提示

对于 $40\%$ 的测试点，$1 \le N,M,T,K \le 200$。

对于 $100\%$ 的测试点，$1 \le N,M,T,K \le 4000$。

$v \le 100$，$N,M,K,T$ 均为整数。

by-szc


---

---
title: "「SWTR-3」Golden Sword"
layout: "post"
diff: 普及+/提高
pid: P5858
tag: ['动态规划 DP', '单调队列', 'O2优化']
---
# 「SWTR-3」Golden Sword
## 题目背景

小 E 不幸在一场战斗中失去了他的金宝剑。
## 题目描述

制造一把金宝剑需要 $n$ 种原料，编号为 $1$ 到 $n$，编号为 $i$ 的原料的坚固值为 $a_i$。

炼金是很讲究放入原料的顺序的，因此小 E 必须**按照 $1$ 到 $n$ 的顺序**依次将这些原料放入炼金锅。

但是，炼金锅的容量非常有限，它**最多只能容纳 $w$ 个原料**。

所幸的是，**每放入一个原料之前**，小 E 可以从中取出一些原料，数量不能超过 $s$ 个。

- 我们定义第 $i$ 种原料的耐久度为：放入第 $i$ 种原料时锅内的原料总数（包括正在放入的原料） $\times\ a_i$，则宝剑的耐久度为**所有原料**的耐久度之和。

小 E 当然想让他的宝剑的耐久度尽可能得大，这样他就可以带着它进行更多的战斗，请求出耐久度的最大值。

注：这里的“放入第 $i$ 种原料时锅内的原料总数**包括正在放入锅中的原料**，详细信息请见样例。
## 输入格式

第一行，三个整数 $n,w,s$。

第二行，$n$ 个整数 $a_1,a_2,\dots,a_n$。
## 输出格式

一行一个整数，表示耐久度的最大值。
## 样例

### 样例输入 #1
```
5 3 3
1 3 2 4 5

```
### 样例输出 #1
```
40
```
### 样例输入 #2
```
5 3 3
1 -3 -2 4 5

```
### 样例输出 #2
```
21
```
### 样例输入 #3
```
7 4 2
-5 3 -1 -4 7 -6 5

```
### 样例输出 #3
```
17
```
### 样例输入 #4
```
5 3 1
-1 -3 -2 -4 -5

```
### 样例输出 #4
```
-15
```
## 提示

#### 「样例说明」

- **对于样例 1**，一种可行的**最优**方案为：
首先放进原料 1，此时锅内有 $1$ 种原料，耐久度为 $1\times a_1=1\times 1=1$。  
再放进原料 2，此时锅内有 $2$ 种原料，耐久度为 $2\times a_2=2\times 3=6$。  
再放进原料 3，此时锅内有 $3$ 种原料，耐久度为 $3\times a_3=3\times 2=6$。  
取出原料 1，再放进原料 4，此时锅内有 $3$ 种原料，耐久度为 $3\times a_4=3\times 4=12$。  
取出原料 4，再放进原料 5，此时锅内有 $3$ 种原料，耐久度为 $3\times a_5=3\times 5=15$。  
最终答案为 $1+6+6+12+15=40$。  
- **对于样例 2**，一种可行的**最优**方案为：  
放进原料 1，耐久度为 $1\times 1=1$。  
取出原料 1，放进原料 2，耐久度为 $1\times (-3)=-3$。  
放进原料 3，耐久度为 $2\times (-2)=-4$。  
放进原料 4，耐久度为 $3\times 4=12$。  
取出原料 2，放进原料 5，耐久度为 $3\times 5=15$。  
最终答案为 $1+(-3)+(-4)+12+15=21$。  
- **对于样例 3**，一种可行的**最优**方案为：  
  $a_1+2a_2+2a_3+3a_4+4a_5+3a_6+4a_7=17$。 
- **对于样例 4**，一种可行的**最优**方案为：  
$a_1+a_2+a_3+a_4+a_5=-15$。

#### 「数据范围与约定」

**本题使用捆绑测试。**

- Subtask #1（15 points）：$n\leq 10$。
- Subtask #2（5 points）：$n\leq 100$，$a_i\geq0$。
- Subtask #3（15 points）：$n\leq 300$。
- Subtask #4（15 points）：$s=w=n$。
- Subtask #5（5 points）：$a_i\geq 0$。
- Subtask #6（10 points）：$n\leq 2\times 10^3$。
- Subtask #7（10 points）：$s=1$。
- Subtask #8（25 points）：无特殊限制。

对于 $100\%$ 的数据，$1 \leq s \leq w \leq n \leq 5\times 10^3$，$|a_i| \leq 10^9$。对于 Subtask $i$ 有 $|a_i|\leq 10^{i+1}$。

#### 「帮助/说明」

本题下发大样例，具体输入输出见 [**Big Sample**](https://pan.baidu.com/s/1erVDllDlvNlEShxh3U42gA) 中的 gold01-08.in/gold01-08.out。提取码：757d。  
**文件名与 Subtask 编号一一对应。**

#### 「来源」

[Sweet Round 03 D](https://www.luogu.com.cn/contest/24755)。  
idea & solution：ET2006。


---

---
title: "「ACOI2020」课后期末考试滑溜滑溜补习班"
layout: "post"
diff: 普及+/提高
pid: P6040
tag: ['动态规划 DP', '2020', '单调队列', 'O2优化', '动态规划优化']
---
# 「ACOI2020」课后期末考试滑溜滑溜补习班
## 题目背景

![T2](https://s2.ax1x.com/2020/01/12/lopS6f.png)

潮田 渚（Shiota Nagisa）因为理科不大好，自然会被仔细观察学生的杀老师发现，于是渚同学只得加入杀老师举办的课后期末考试滑溜滑溜补习班。至于为什么叫这个名字，额，你不能问我啊。
## 题目描述

在补习班上，因为多个学生会同时有需求，所以杀老师会制造分身用音速移动来回回答问题。

补习班上有 $n$ 个同学，他们每一个人都有一个问题。杀老师为了有序回答学生的问题，把所有学生排成了一列。第 $i$ 个学生的问题有一个困难值 $a_i$，杀老师回答第 $i$ 个学生的问题需要花费 $a_i$ 的精力。杀老师到了哪里，它就要解决那个学生的问题。杀老师最开始会解决序列中第一个同学的问题，他最后会去解决最后一个同学的问题。

杀老师每次解决完一个同学的问题到下一个同学的座位上就要花费 $k$ 点精力值。特殊的，如果杀老师想让自己轻松一点，可以不移动到下一个，可以直接到下两个，下三个，就不用解决跳过的同学的问题了。对应的，它会被学生调侃。受到打击的杀老师自然会花费格外的精力，花费的精力为 $k+(q-p-1) \times d$（当前位置为 $p$，跳到的位置为 $q$）。

当然的，杀老师也是有速度的啊，并且它想解决学生的一些问题，所以说杀老师最多只会跳过 $x-1$ 个学生，去解决下 $x$ 个学生的问题。
## 输入格式

第一行五个整数 $n,k,d,x,tp$，表示有 $n$ 个学生，只按顺序去到下一个学生的座位需要花费 $k$ 点精力，每多跳过一个学生就要多花费 $d$ 点精力值，每一次最多只能跳过 $x-1$ 个学生，是否是特殊数据。

- $tp=0$，第二行 $n$ 个整数 $a_{1\dots n}$，$a_i$ 表示第 $i$ 个学生的问题的困难值为 $a_i$。

- $tp=1$，第二行一个整数 $Seed$，作为种子，然后调用 $rnd$ 函数**依次**生成 $n$ 个整数，作为 $a$ 数组，$a_i$ 表示第 $i$ 个学生的问题的困难值为 $a_i$。

```cpp
inline int rnd () {
	static const int MOD = 1e9;
	return Seed = ( 1LL * Seed * 0x66CCFF % MOD + 20120712 ) % MOD;
}
```
## 输出格式

一行一个整数，表示杀老师解决完最后一个同学的问题最少需要花费多少精力。
## 样例

### 样例输入 #1
```
5 3 4 1 0
1 2 3 4 5

```
### 样例输出 #1
```
27
```
### 样例输入 #2
```
10 30630 56910 2 0
7484 99194 86969 17540 29184 68691 91892 81564 93999 74280 

```
### 样例输出 #2
```
717318
```
### 样例输入 #3
```
10000000 899999999 923456655 213111 1
1314520
```
### 样例输出 #3
```
9231813656566921
```
## 提示

#### 样例解释 #1

杀老师每次不能跳过学生，因此他必须依次移动并解决所有问题，故答案为解决问题所需的精力 $1+2+3+4+5=15$ 与移动所需的精力 $4 \times 3=12$，所以花费精力之和为 $27$。

------------
#### 数据范围

**本题采用捆绑测试**。

- Subtask 1（20 points），学生们学习认真听话，留下来的同学也会更少：$tp=0$，$n \leq 10^3$。     
- Subtask 2（30 points），杀老师的速度快极了，并且学生们没时间吐槽它：$tp=0$，$n \leq 10^6$。     
- Subtask 3（50 points），$tp=1$，其余无特殊限制。

对于 $100\%$ 的数据，$1 \leq n \leq 10^7$，$0 \leq k,d,a_i \leq 10^9$，$1 \leq x \leq n-1$。

------------
#### 提示

对于 $tp=1$ 的数据，$rnd$ 函数只用于减小输入量，标准算法不依赖该数据生成方式。


---

---
title: "[COCI 2010/2011 #3] DIFERENCIJA"
layout: "post"
diff: 普及+/提高
pid: P6503
tag: ['2010', '单调队列', 'O2优化', '栈', 'COCI（克罗地亚）']
---
# [COCI 2010/2011 #3] DIFERENCIJA
## 题目描述

给出一个长度为 $n$ 的序列 $a_i$，求出下列式子的值：

$$\sum_{i=1}^{n} \sum_{j=i}^{n} (\max_{i\le k\le j} a_k-\min_{i\le k\le j} a_k)$$



即定义一个子序列的权值为序列内最大值与最小值的差。求出所有连续子序列的权值和。


## 输入格式

输入第一行一个整数 $n$，表示序列的长度。

接下来的 $n$ 行，每行一个整数 $a_i$，描述这个序列。
## 输出格式

输出一行一个整数，表示式子的答案。
## 样例

### 样例输入 #1
```
3
1
2
3
```
### 样例输出 #1
```
4
```
### 样例输入 #2
```
4
7
5
7
5
```
### 样例输出 #2
```
12
```
### 样例输入 #3
```
4
3
1
7
2
```
### 样例输出 #3
```
31
```
## 提示

#### 数据规模与约定

对于 $100\%$ 的数据，保证 $2\le n\le 3\times 10^5$，$1\le a_i\le 10^8$。

#### 说明

**题目译自 [COCI2010-2011](https://hsin.hr/coci/archive/2010_2011/) [CONTEST #3](https://hsin.hr/coci/archive/2010_2011/contest3_tasks.pdf) *T5 DIFERENCIJA***。


---

---
title: "奶牛排队"
layout: "post"
diff: 普及+/提高
pid: P6510
tag: ['单调队列', 'NOI 导刊', 'O2优化', '分治', '栈']
---
# 奶牛排队
## 题目描述

奶牛在熊大妈的带领下排成了一条直队。

显然，不同的奶牛身高不一定相同……

现在，奶牛们想知道，如果找出一些连续的奶牛，要求最左边的奶牛 $A$ 是最矮的，最右边的 $B$ 是最高的，且 $B$ 高于 $A$ 奶牛。中间如果存在奶牛，则身高不能和 $A,B$ 奶牛相同。问这样的奶牛最多会有多少头？

从左到右给出奶牛的身高，请告诉它们符合条件的最多的奶牛数（答案可能是 $0,2$，但不会是 $1$）。
## 输入格式

第一行一个正整数 $N$，表示奶牛的头数。

接下来 $N$ 行，每行一个正整数，从上到下表示从左到右奶牛的身高 $h_i$。

## 输出格式

一行一个整数，表示最多奶牛数。
## 样例

### 样例输入 #1
```
5
1
2
3
4
1
```
### 样例输出 #1
```
4
```
## 提示

#### 样例解释

取第 $1$ 头到第 $4$ 头奶牛，满足条件且为最多。

#### 数据范围

对于全部的数据，满足 $2 \le N \le 10^5$，$1 \le h_i <2^{31}$。


---

---
title: "[yLOI2020] 不离"
layout: "post"
diff: 普及+/提高
pid: P7095
tag: ['贪心', '2020', '二分', '堆', '单调队列', 'O2优化']
---
# [yLOI2020] 不离
## 题目背景

> 乱玄黄时序，探风林实虚。  
> 我要你共我奇谈怪趣。  
> 任日月斑斓，待春秋兴残。  
> 我要我们有聚无散。  

——银临《不离》
## 题目描述

这道题目来自 zxy 哔哔，咕咕让哔哔选一首歌作为题目名，但是哔哔说没有想好，于是咕咕就帮他选了这首歌。

哔哔在玩一款叫做《暗黑破坏神》的游戏，某天哔哔灵光乍现，以游戏为背景出了一道神仙题并告诉了咕咕。咕咕并不会做，于是对题目进行了一定的简化。因此，经过简化后，这道题已经和《暗黑破坏神》没什么关系了。

游戏中人物有两个属性，我们分别称之为「力量」和「精神」，同时哔哔有 $n$ 件装备，穿戴第 $i$ 件装备需要人物在穿戴前的力量值不低于 $a_i$，精神值不低于 $b_i$。在穿戴第 $i$ 件装备后，人物的力量值会增加 $c_i$，精神值会增加 $d_i$。

哔哔可以自由选择穿装备的顺序，只要满足力量和精神不低于对应值，就可以穿戴该装备。

现在，咕咕想知道，如果想让哔哔穿戴上所有的装备，那么人物的初始力量值（即没有穿任何装备之前的力量值）最小应该是多少？在初始力量值最小的前提下，初始精神值（即没有穿任何装备之前的精神值）最小应该是多少？

显然，初始力量和初始精神都应该是非负整数。
## 输入格式

第一行有一个整数，表示该测试点所在的子任务编号 $T$。  
第二行有一个整数，表示哔哔的装备件数 $n$。  
第 $3$ 到第 $(n+2)$ 行，每行四个整数，第 $(i+2)$ 行的整数依次表示 $a_i,b_i,c_i,d_i$。
## 输出格式

输出一行两个用空格隔开的整数，分别表示最小的初始力量值以及在初始力量值最小的前提下最小的初始精神值。
## 样例

### 样例输入 #1
```
0
2
1 5 0 2
1 2 3 4
```
### 样例输出 #1
```
1 2
```
## 提示

### 样例 1 解释

当初始力量值为 $1$，精神值为 $2$ 时，可以穿戴第 $2$ 件装备。在穿戴该装备后，增加 $3$ 点力量和 $4$ 点精神，人物的属性变为 $4$ 点力量和 $6$ 点精神，此时可以穿戴第 $1$ 件装备。

### 数据规模与约定

**本题采用多测试点捆绑测试**。

- 子任务 $1$（$5$ 分）：保证 $n=0$。
- 子任务 $2$（$5$ 分）：保证 $n=1$。
- 子任务 $3$（$20$ 分）：保证 $a_i,b_i \le 100$，$n \le 6$。
- 子任务 $4$（$10$ 分）：保证 $a_i,b_i \le 10^5$，$n \le 6$。
- 子任务 $5$（$10$ 分）：保证 $a_i,b_i \le 10$。
- 子任务 $6$（$10$ 分）：保证 $a_i,b_i \le 100$。
- 子任务 $7$（$10$ 分）：保证 $b_i=0$，$n \le 6$。
- 子任务 $8$（$10$ 分）：保证 $b_i=0$。
- 子任务 $9$（$10$ 分）：保证 $n \le 6$。
- 子任务 $10$（$10$ 分）：无特殊约定。

对于全部的测试点，保证 $0 \le n \le 10^5$，$0 \le a_i,b_i,c_i,d_i \le 10^9$。

### 提示
有 $4$ 个样例文件，请见附加文件中的 forever.zip。

对于第三个样例，满足 $b_i = 0$。


---

---
title: "回旋加速器（2021 CoE-II C）"
layout: "post"
diff: 普及+/提高
pid: P7590
tag: ['单调队列', '2021', '其它技巧']
---
# 回旋加速器（2021 CoE-II C）
## 题目描述

回旋加速器（$\text{Cyclotron}$）是利用磁场和电场使带电粒子作回旋运动并经高频电场反复加速的装置，是高能物理中的重要仪器。

我们来研究回旋加速器的一个简化模型。将回旋加速器视为一个环形的轨道，轨道上设置了 $n$ 个加速腔，依次编号为 $1$ 至 $n$。将一束质子从某个加速腔导入，在导入时，质子束的动能为零。第 $i$ 个加速腔能够为质子束提供 $e_i$ 的动能 ，质子束从第 $i$ 个加速腔运行到第 $i + 1$ 个加速腔会损失 $d_i$ 的动能（由于是环形轨道，编号为 $n$ 的加速腔后面是编号为 $1$ 的加速腔）。

给定每个加速腔能够提供的动能值以及质子束在各个加速腔之间运行所损失的动能值，试确定质子束能否绕环形轨道运行一周。如果能够成功，应该选择从哪个加速腔导入质子束。质子束在两个加速腔之间运行时，动能不能为零，但质子束刚到达加速腔时，动能可以为零，因为可以立即获得加速腔所提供的动能。
## 输入格式

**输入包含多组测试数据。**

输入第一行包含一个整数 $T$，表示测试数据的组数。接着是一个空行。

接下来是 $T$ 组数据，每组数据由三行构成。两组数据之间有一个空行。

每组数据的第一行是一个整数 $n$，表示加速腔的个数。第二行一共 $n$ 个整数，依次表示编号为 $i$ 的加速腔能够提供的动能 $e_i$。第三行一共 $n$ 个整数，依次表示质子束从第 $i$ 个加速腔运行到第 $i + 1$ 个加速腔所损失的动能 $d_i$。由于是环形轨道，第三行的第 $n$ 个整数表示的是从第 $n$ 个加速腔运行到第 $1$ 个加速腔时损失的动能。
## 输出格式

每组数据输出一行。如果质子束无法环绕加速器运行一周，输出 `Failed!`，否则输出导入质子束的加速腔编号，如果有多个加速腔可供选择，选择具有最小编号的加速腔。
## 样例

### 样例输入 #1
```
1

3
1 2 3
2 3 4
```
### 样例输出 #1
```
Failed!
```
### 样例输入 #2
```
1

10
1 2 3 4 5 6 7 8 9 10
3 2 1 2 3 4 5 6 7 8
```
### 样例输出 #2
```
2
```
## 提示

**样例说明**

输入 #1

该组输入共有 $3$ 个加速腔，依次能够提供的动能为 $1$、$2$、$3$。从第 $1$ 个加速腔运行到第 $2$ 个加速腔损失 $2$ 动能，从第 $2$ 个加速腔运行到第 $3$ 个加速腔损失 $3$ 动能，从第 $3$ 个加速腔运行到第 $1$ 个加速腔损失 $4$ 动能。不管从哪个加速腔导入质子束，都会使得质子束在两个加速腔运行过程中动能变为零，无法环绕轨道一周。

输入 #2

该组输入共有 $10$ 个加速腔，如果从第 $1$ 个加速腔导入质子束，将获得动能 $1$，但是在从第 $1$ 个加速腔运行到第 $2$ 个加速腔的过程中会损失 $3$ 动能，因此会使得质子束无法环绕轨道一周。而从第 $2$ 个到第 $10$ 个加速腔中的任意一个导入质子束，均能保证质子束在加速腔之间运行时动能不为零，因此都可作为导入质子束的加速腔，但编号为 $2$ 的加速腔具有最小的编号。需要注意，从第 $2$ 个加速腔导入质子束，当运行到第 $3$ 个加速腔时，动能恰为零，根据题意，这种情形是允许的。

------------


**数据范围**

- Subtask $1$：$2 \le n \le 10$，$10$ 分。
- Subtask $2$：$2 \le n \le 10^3$，$30$ 分。
- Subtask $3$：$2 \le n \le 10^5$，$30$ 分。
- Subtask $4$：$2 \le n \le 10^6$，$30$ 分。

对于 $100\%$ 的数据，$1 \le T \le 20$，$0 \lt e_i \le 100$，$0 \lt d_i \le 100$。



------------

**约定**

质子束的运行方向规定为：从第 $1$ 个加速腔到第 $2$ 个加速腔，从第 $2$ 个加速腔到第 $3$ 个加速腔$\cdots$从第 $n$ 个加速腔到第 $1$ 个加速腔。


---

---
title: "「LCOI2022」 Cow Insertion"
layout: "post"
diff: 普及+/提高
pid: P8102
tag: ['单调队列', '2022', 'O2优化']
---
# 「LCOI2022」 Cow Insertion
## 题目背景

Farmer John 迎来了新奶牛——Bessie。每个奶牛都会有一定的开心值，Farmer John 希望 Bessie 能更幸福的生活在这里。
## 题目描述

牛棚里原来有 $n$ 头奶牛，开心值的感染距离 $m$，并且 $a_i$ 表示原来牛棚中第 $i(1\le i\le n)$ 头牛的开心值。并且，Bessie 同样拥有一个开心值 $A$。

整个牛棚的开心值是 $\sum\limits_{i=1}^{n-m+1}\ \max\limits_{i\le j\le i+m-1}\ a_j$，Bessie 可以住在任意两头牛的中间或起始以及最后。Farmer John 想知道：Bessie 来这里之后，整个牛棚的开心值最大为多少。
## 输入格式

第一行包含三个整数 $n,m,A$。分别表示为奶牛个数，开心值的感染距离，以及 Bessie 的开心值。

接下来一行，包含 $n$ 个数 $a_i$，表示原来牛棚中第 $i(1\le i\le n)$ 头牛的开心值。
## 输出格式

仅一行，表示 Bessie 来这里之后，整个牛棚的开心值的最大值。
## 样例

### 样例输入 #1
```
3 2 50
60 100 70
```
### 样例输出 #1
```
270
```
## 提示

【样例解释】
- 当 Bessie 在第一个位置时（$50,60,100,70$），整个牛棚的开心值的最大值为 $\newcommand{\cases}[1]{\{#1\}}\max\cases{60,50}+\max\cases{60,100}+\max\cases{100,70}$，即 $60+100+100=260$。
- 当 Bessie 在第二个位置时（$60,50,100,70$），整个牛棚的开心值的最大值为 $\newcommand{\cases}[1]{\{#1\}}\max\cases{60,50}+\max\cases{50,100}+\max\cases{100,70}$，即 $60+100+100=260$。
- 当 Bessie 在第三个位置时（$60,100,50,70$），整个牛棚的开心值的最大值为 $\newcommand{\cases}[1]{\{#1\}}\max\cases{60,100}+\max\cases{100,50}+\max\cases{50,70}$，即 $100+100+70=270$。
- 当 Bessie 在第四个位置时（$60,100,70,50$），整个牛棚的开心值的最大值为 $\newcommand{\cases}[1]{\{#1\}}\max\cases{60,100}+\max\cases{100,70}+\max\cases{70,50}$，即 $70+100+100=270$。

显然，整个牛棚的开心值的最大值为 $\newcommand{\cases}[1]{\{#1\}}\max\cases{260,260,270,270}=270$。

【数据范围与约定】

|subtask|$n\le$|分值|
|:-:|:-:|:-:|
|$1$|$5\times10^2$|$10$|
|$2$|$5\times10^3$|$20$|
|$3$|$5\times10^6$|$70$|

对于 $100\%$ 的数据，$1\le m\le n$，$0\le a_i, A\le100$。


---

---
title: "「MXOI Round 2」队列"
layout: "post"
diff: 普及+/提高
pid: P9588
tag: ['线段树', '倍增', '二分', '平衡树', '树状数组', '单调队列', '洛谷原创', 'O2优化', '优先队列', '前缀和', '队列', '洛谷月赛']
---
# 「MXOI Round 2」队列
## 题目描述

小 C 有一个队列，他要对这个队列进行 $q$ 次操作。操作共四种，参数分别如下：

$1\ x$：这是第一种操作，表示从队尾依次插入 $1,2,3,\cdots,x$；

$2\ y$：这是第二种操作，表示弹出队头的前 $y$ 个元素；

$3\ z$：这是第三种操作，表示查询队列中的第 $z$ 个元素；

$4$：这是第四种操作，表示查询队列中所有元素的最大值。

你需要帮助他维护这个队列，并对于每个第三种操作和第四种操作，输出查询的答案。
## 输入格式

第一行两个整数 $c,q$，其中 $c$ 表示测试点编号。$c=0$ 表示该测试点为样例。

接下来 $q$ 行，每行 $1 \sim 2$ 个整数，表示一个操作，格式见【**题目描述**】。
## 输出格式

对于每个第三种操作和第四种操作，输出一行一个整数，表示查询的答案。
## 样例

### 样例输入 #1
```
0 9
1 5
1 3
2 2
1 4
3 6
3 8
2 4
4
3 3
```
### 样例输出 #1
```
3
2
4
1
```
## 提示

#### 【样例解释 #1】

在进行第四次操作后，队列中的元素依次为 $3,4,5,1,2,3,1,2,3,4$。

在进行第七次操作后，队列中的元素依次为 $2,3,1,2,3,4$。

#### 【样例 #2】

见附加文件中的 `queue/queue2.in` 与 `queue/queue2.ans`。

该样例满足测试点 $1$ 的限制。

#### 【样例 #3】

见附加文件中的 `queue/queue3.in` 与 `queue/queue3.ans`。

该样例满足测试点 $4$ 的限制。

#### 【样例 #4】

见附加文件中的 `queue/queue4.in` 与 `queue/queue4.ans`。

该样例满足测试点 $11$ 的限制。

#### 【样例 #5】

见附加文件中的 `queue/queue5.in` 与 `queue/queue5.ans`。

该样例满足测试点 $15$ 的限制。

#### 【样例 #6】

见附加文件中的 `queue/queue6.in` 与 `queue/queue6.ans`。

该样例满足测试点 $20$ 的限制。

#### 【数据范围】

设 $\sum x$ 表示单个测试点内 $x$ 之和。

对于 $100\%$ 的数据，$1 \le q \le 2\times 10^5$，$1 \le x,y,z \le 10^9$，$0 \le \sum x \le 2\times10^{14}$，保证在进行第二种操作前队列内元素个数不小于 $y$，在进行第三种操作前队列内元素个数不小于 $z$，在进行第四种操作前队列内元素个数大于 $0$。

|测试点编号|$q \le$|$x \le$|$\sum x \le$|特殊性质|
|:---:|:---:|:---:|:---:|:---:|
|$1\sim3$|$500$|$500$|$2\times10^5$|C|
|$4\sim8$|$5000$|$5000$|$2\times10^7$|无|
|$9\sim10$|$2\times10^5$|$10^9$|$2\times10^{14}$|AB|
|$11\sim12$|$2\times10^5$|$10^9$|$2\times10^{14}$|B|
|$13\sim14$|$2\times10^5$|$10^9$|$2\times10^9$|AC|
|$15\sim16$|$2\times10^5$|$10^9$|$2\times10^9$|C|
|$17\sim18$|$2\times10^5$|$500$|$2\times10^7$|无|
|$19$|$2\times10^5$|$10^9$|$2\times10^9$|无|
|$20$|$2\times10^5$|$10^9$|$2\times10^{14}$|无|

特殊性质 A：没有第二种操作。

特殊性质 B：没有第三种操作。

特殊性质 C：没有第四种操作。


---

---
title: "[GDCPC 2023] Base Station Construction"
layout: "post"
diff: 普及+/提高
pid: P9691
tag: ['动态规划 DP', '单调队列', '2023', '广东', 'O2优化', 'XCPC']
---
# [GDCPC 2023] Base Station Construction
## 题目描述

China Mobile Shenzhen Branch was registered in $1999$. Four years later, Guangdong Collegiate Programming Contest was held for the first time. China Mobile Shenzhen Branch, along with Guangdong Collegiate Programming Contest, witnesses the prosperity and development of the computer industry in Guangdong.

![](https://cdn.luogu.com.cn/upload/image_hosting/md6qj7fz.png)

During the construction of a communication line, it is critical to carefully choose the locations for base stations. The distance from west to east of a city is $n$ kilometers. The engineers have investigated the cost to build a base station at $1, 2, \cdots, n$ kilometers from west to east, which are $a_1, a_2, \cdots, a_n$ respectively.

To ensure communication quality for the residents, the locations of base stations also need to meet $m$ requirements. The $i$-th requirement can be represented as a pair of integers $l_i$ and $r_i$ ($1 \le l_i \le r_i \le n$), indicating that there must be at least $1$ base station between $l_i$ kilometers and $r_i$ kilometers (both inclusive) from west to east.

As the chief engineer, you need to decide the number of base stations to build and their locations, and finally calculate the minimum total cost to satisfy all requirements.
## 输入格式

There are multiple test cases. The first line of the input contains an integer $T$ indicating the number of test cases. For each test case:

The first line contains an integer $n$ ($1 \le n \le 5 \times 10^5$) indicating the distance from west to east of the city.

The second line contains $n$ integers $a_1, a_2, \cdots, a_n$ ($1 \le a_i \le 10^9$) where $a_i$ indicates the cost to build a base station at $i$ kilometers from west to east.

The third line contains an integer $m$ ($1 \le m \le 5 \times 10^5$) indicating the number of requirements.

For the following $m$ lines, the $i$-th line contains two integers $l_i$ and $r_i$ ($1 \le l_i \le r_i \le n$) indicating that there must be at least $1$ base station between $l_i$ kilometers and $r_i$ kilometers (both inclusive) from west to east.

It's guaranteed that neither the sum of $n$ nor the sum of $m$ of all test cases will exceed $5 \times 10^5$.
## 输出格式

For each test case output one line containing one integer indicating the minimum total cost to satisfy all requirements.
## 样例

### 样例输入 #1
```
2
5
3 2 4 1 100
3
1 3
2 4
5 5
5
7 3 4 2 2
3
1 4
2 3
4 5
```
### 样例输出 #1
```
102
5
```
## 提示

For the first sample test case the optimal solution is to build base stations at $2$ kilometers and $5$ kilometers from west to east. The total cost is $2 + 100 = 102$.

For the second sample test case the optimal solution is to build base stations at $2$ kilometers and $4$ kilometers from west to east. The total cost is $3 + 2 = 5$.
## 题目翻译

**【题目描述】**

中国移动通信集团广东有限公司深圳分公司（以下简称``深圳移动``）于 $1999$ 年正式注册。四年后，广东省大学生程序设计竞赛第一次举办。深圳移动与广东省大学生程序设计竞赛一起见证了广东省计算机行业的兴旺与发展。

在建设通信线路的过程中，信号基站的选址是一个非常关键的问题。某城市从西到东的距离为 $n$ 千米，工程师们已经考察了在从西往东 $1, 2, \cdots, n$ 千米的位置建设基站的成本，分别是 $a_1, a_2, \cdots, a_n$。

为了保证居民的通信质量，基站的选址还需要满足 $m$ 条需求。第 $i$ 条需求可以用一对整数 $l_i$ 和 $r_i$ 表示（$1 \le l_i \le r_i \le n$），代表从西往东 $l_i$ 千米到 $r_i$ 千米的位置之间（含两端）至少需要建设 $1$ 座基站。

作为总工程师，您需要决定基站的数量与位置，并计算满足所有需求的最小总成本。

**【输入格式】**

有多组测试数据。第一行输入一个整数 $T$ 表示测试数据组数，对于每组测试数据：

第一行输入一个整数 $n$（$1 \le n \le 5 \times 10^5$）表示城市从西到东的距离。

第二行输入 $n$ 个整数 $a_1, a_2, \cdots, a_n$（$1 \le a_i \le 10^9$），其中 $a_i$ 表示在从西往东 $i$ 千米的位置建设基站的成本。

第三行输入一个整数 $m$（$1 \le m \le 5 \times 10^5$）表示需求的数量。

对于接下来 $m$ 行，第 $i$ 行输入两个整数 $l_i$ 和 $r_i$（$1 \le l_i \le r_i \le n$）表示从西往东 $l_i$ 千米到 $r_i$ 千米的位置之间（含两端）至少需要建设 $1$ 座基站。

保证所有数据 $n$ 之和与 $m$ 之和均不超过 $5 \times 10^5$。

**【输出格式】**

每组数据输出一行一个整数，表示满足所有需求的最小总成本。

**【样例解释】**

对于第一组样例数据，最优方案是在从西往东 $2$ 千米和 $5$ 千米的位置建设基站。总成本为 $2 + 100 = 102$。

对于第二组样例数据，最优方案是在从西往东 $2$ 千米和 $4$ 千米的位置建设基站。总成本为 $3 + 2 = 5$。


---

