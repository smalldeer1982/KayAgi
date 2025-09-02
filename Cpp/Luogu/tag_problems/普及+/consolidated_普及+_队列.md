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
title: "『FLA - I』云音泛"
layout: "post"
diff: 普及+/提高
pid: P10837
tag: ['模拟', '离散化', '洛谷原创', 'O2优化', '排序', '前缀和', '队列', '差分', '洛谷月赛']
---
# 『FLA - I』云音泛
## 题目背景

**[English statement.](/problem/U458238) You must submit your code at the Chinese version of the statement.**

“……这些年来，过得可好？”

“……无所谓好或不好，人生一场空虚大梦，韶华白首，不过转瞬。惟有天道恒在，往复循环，不曾更改...”
## 题目描述

在梦中，秋种下了 $n$ 朵凋零玫瑰。他记得，第 $i$ 朵玫瑰是在时刻 $t_i$ 种植的。

凋零玫瑰在被种下的那个时刻就立即开放，但每一株玫瑰只会开放 $m$ 个时刻（在时刻 $T$ 种植的玫瑰会且仅会在从时刻 $T$ 到时刻 $T+m-1$ 的 $m$ 个时刻开放），在 $m$ 个时刻后便化作再也无法挽留的灰尘，飘散在凛冽的寒风中。

他问你，假如他可以改变不超过一朵玫瑰的种植时间（选定一个 $t_i$ 并将其修改为任意正整数），那么最多有多少个时刻有且仅有一株凋零玫瑰开放？
## 输入格式

第一行输入两个正整数 $n,m$。

第二行输入 $n$ 个正整数，第 $i$ 个正整数为 $t_i$。
## 输出格式

输出一行一个正整数表示答案。
## 样例

### 样例输入 #1
```
5 4
11 9 1 3 12

```
### 样例输出 #1
```
14

```
### 样例输入 #2
```
13 7
6 42 58 41 20 60 2 61 45 28 45 28 12

```
### 样例输出 #2
```
38

```
## 提示

**「样例解释 #1」**

如图，使用金色标记有且仅有一株凋零玫瑰开放的时刻，使用黑色和红色标记每朵凋零玫瑰开放的时刻。

![example1](https://cdn.luogu.com.cn/upload/image_hosting/1u42cn1k.png)

将使用红色标记的玫瑰的种植时刻改为 $17$（将 $t_1$ 的值修改为 $17$，如下图）后有 $14$ 个时刻有且仅有一株凋零玫瑰开放。可以证明不存在能够使有且仅有一株凋零玫瑰开放的时刻数量大于 $14$ 的修改方案。

![example2](https://cdn.luogu.com.cn/upload/image_hosting/ig0pgy5w.png)

**「数据范围」**

|测试点编号|$n \leq$|$m \leq$|$t_i \leq$|
|:-:|:-:|:-:|:-:|
|$1 \sim 6$|$5000$|$5000$|$5000$|
|$7 \sim 12$|$2 \times 10^5$|$2 \times 10^5$|$2 \times 10^5$|
|$13 \sim 14$|$2 \times 10^5$|$1$|$10^9$|
|$15 \sim 20$|$2 \times10^5$|$10^9$|$10^9$|

对于所有测试数据，$1 \leq n \leq 2 \times 10^5$，$1 \leq m,t_i \leq 10^9$。


---

---
title: "【MX-J8-T3】水星湖"
layout: "post"
diff: 普及+/提高
pid: P11215
tag: ['模拟', '搜索', 'O2优化', '队列', '梦熊比赛']
---
# 【MX-J8-T3】水星湖
## 题目背景

原题链接：<https://oier.team/problems/J8C>。
## 题目描述

有一个 $n\times m$ 的矩形网格。用数对 $(x, y)$ 表示第 $x$ 行、第 $y$ 列的位置。

网格内有 $q$ 片湖泊（$q$ 可能为 $0$），第 $i$ 片湖泊覆盖了左上角为 $(a_{i, 1}, b_{i, 1})$、右下角为 $(a_{i, 2}, b_{i, 2})$ 的矩形区域，这片区域里的所有位置都被称为湖泊。如果一个位置不属于任何一片湖泊，它就是陆地。湖泊两两不会重叠，但可能相邻。

小 Y 会进行 $r$ 次种树。第 $i$ 次，他在第 $t_i$ 秒向 $(x_i, y_i)$ 里种下一棵树，保证该位置不为湖泊，且要么没有种下或生长过树，要么曾经种下或生长的树已经死亡。保证种树是按照时间顺序进行的，即 $t_1, t_2, \dots, t_r$ 单调不降。

每一秒，对于每个位置 $(x, y)$，若它同时满足如下所有条件，则会在 $(x, y)$ 处生长出一棵树：
- 它是一块无树存活的陆地；
- 它与一块湖泊**相邻**；
- 它**在前一秒**与一棵存活的树**相邻**。

（上述所说的**相邻**是在四连通意义下的，即位置 $(x_1, y_1)$ 和 $(x_2, y_2)$ 相邻当且仅当 $\lvert x_1 - x_2 \rvert + \lvert y_1 - y_2 \rvert = 1$。）

如果一棵树在存活**大于 $\bm k$ 秒**后（以其被种下或生长出来时开始计算），与其相邻的所有位置**均为无树存活的陆地**，则它会死亡。

小 Y 想要知道：经过充分多时间后（也即，经过足够多的时间，使得网格内不会有新的位置长出树，也不会有旧的树死去的状态下），网格内最终会有多少棵树。
## 输入格式

第一行，五个整数 $n, m, q, r, k$。

接下来 $q$ 行，每行四个正整数 $a_{i, 1}, b_{i, 1}, a_{i, 2}, b_{i, 2}$，描述第 $i$ 片湖泊的位置。保证湖泊两两不会重叠。

接下来 $r$ 行，每行三个正整数 $t_i, x_i, y_i$，分别表示第 $i$ 棵树被种下的秒数和行列位置。保证 $t_1, t_2, \dots, t_r$ 单调不降。
## 输出格式

仅一行一个整数，表示经过充分多时间后，网格内最终会有多少棵树。
## 样例

### 样例输入 #1
```
5 6 2 1 1
2 1 3 3
3 5 5 6
1 1 5
```
### 样例输出 #1
```
10
```
### 样例输入 #2
```
3 3 0 3 1
1 3 1
2 1 1
3 2 1

```
### 样例输出 #2
```
2
```
## 提示

**【样例解释 \#1】**

如图所示，为经过充分多时间后网格中的情况。

![](https://cdn.luogu.com.cn/upload/image_hosting/kdlmoo7p.png)

网格内不会有新的位置长出树，也不会有旧的树死去，所以经过充分多时间后，网格内有 $10$ 棵树。

**【样例解释 \#2】**

在这一组数据中，所有位置都是陆地，没有湖泊。

第 $1$ 秒时，第一棵树在 $(3, 1)$ 被种下。

第 $2$ 秒时，第二棵树在 $(1, 1)$ 被种下。紧接着，第一棵树已存活 $> 1$ 秒，且与其相邻的所有位置均为没有存活的树的陆地，因此死亡。

第 $3$ 秒时，第三棵树在 $(2, 1)$ 被种下。紧接着，第二棵树已存活 $> 1$ 秒，而此时第三棵树与其相邻，因此不死亡。

随后，网格内不会有新的位置长出树，也不会有旧的树死去。所以经过充分多时间后，网格内有 $2$ 棵树。

**【样例 \#3】**

见附件中的 `lake/lake3.in` 与 `lake/lake3.ans`。

该组样例满足测试点 $4 \sim 7$ 的约束条件。

**【样例 \#4】**

见附件中的 `lake/lake4.in` 与 `lake/lake4.ans`。

该组样例满足测试点 $8 \sim 10$ 的约束条件。

**【样例 \#5】**

见附件中的 `lake/lake5.in` 与 `lake/lake5.ans`。

该组样例满足测试点 $13 \sim 15$ 的约束条件。

**【样例 \#6】**

见附件中的 `lake/lake6.in` 与 `lake/lake6.ans`。

该组样例满足测试点 $16 \sim 20$ 的约束条件。

**【数据范围】**

本题共 $20$ 个测试点，每个 $5$ 分。

|测试点编号|$n,m\le$|$q\le$|$r\le$|$t_i,k\le$|
| :-----------: | :-------------:|:-----------: |:-----------: |:-----------: |
|$1\sim3$|$10$|$10$|$10$|$10$|
|$4\sim7$|$50$|$100$|$1000$|$1000$|
|$8\sim 10$|$3000$|$0$|$10^5$|$10^9$|
|$11\sim12$|$3000$|$10^5$|$1$|$10^9$|
|$13\sim15$|$1000$|$10^5$|$10^5$|$12$|
|$16\sim20$|$3000$|$10^5$|$10^5$|$10^9$|

对于全部数据，保证：
- $1 \leq n, m \leq 3000$；
- $0 \leq q \leq 10^5$；
- $1 \leq a_{i, 1} \le a_{i, 2} \leq n$，$1 \leq b_{i, 1} \le b_{i, 2} \leq m$；
- 湖泊两两不会重叠；
- $1 \leq r \leq 10^5$；
- $1 \leq t_1 \leq t_2 \leq \dots \leq t_r \leq 10^9$；
- $1 \leq x_i \leq n$，$1 \leq y_i \leq m$；
- 位置 $(x_i, y_i)$ 不是湖泊且无树存活；
- $1 \leq k \leq 10^9$。



---

---
title: "机器人搬重物"
layout: "post"
diff: 普及+/提高
pid: P1126
tag: ['搜索', '广度优先搜索 BFS', '队列']
---
# 机器人搬重物
## 题目描述

机器人移动学会（RMI）现在正尝试用机器人搬运物品。机器人的形状是一个直径 $1.6$ 米的球。在试验阶段，机器人被用于在一个储藏室中搬运货物。储藏室是一个 $N\times M$ 的网格，有些格子为不可移动的障碍。机器人的中心总是在格点上，当然，机器人必须在最短的时间内把物品搬运到指定的地方。机器人接受的指令有：

- 向前移动 $1$ 步（`Creep`）；
- 向前移动 $2$ 步（`Walk`）；
- 向前移动 $3$ 步（`Run`）；
- 向左转（`Left`）；
- 向右转（`Right`）。

每个指令所需要的时间为 $1$ 秒。请你计算一下机器人完成任务所需的最少时间。
## 输入格式

第一行为两个正整数 $N,M\ (1\le N,M\le50)$，下面 $N$ 行是储藏室的构造，$0$ 表示无障碍，$1$ 表示有障碍，数字之间用一个空格隔开。接着一行有 $4$ 个整数和 $1$ 个大写字母，分别为起始点和目标点左上角网格的行与列，起始时的面对方向（东 $\tt  E$，南 $\tt  S$，西 $\tt W$，北 $\tt N$），数与数，数与字母之间均用一个空格隔开。终点的面向方向是任意的。
## 输出格式

一个整数，表示机器人完成任务所需的最少时间。如果无法到达，输出 $-1$。

 
![](https://cdn.luogu.com.cn/upload/image_hosting/mma661em.png)

## 样例

### 样例输入 #1
```
9 10
0 0 0 0 0 0 1 0 0 0
0 0 0 0 0 0 0 0 1 0
0 0 0 1 0 0 0 0 0 0
0 0 1 0 0 0 0 0 0 0
0 0 0 0 0 0 1 0 0 0
0 0 0 0 0 1 0 0 0 0
0 0 0 1 1 0 0 0 0 0
0 0 0 0 0 0 0 0 0 0
1 0 0 0 0 0 0 0 1 0
7 2 2 7 S
```
### 样例输出 #1
```
12
```


---

---
title: "【MX-S6-T1】「KDOI-11」打印"
layout: "post"
diff: 普及+/提高
pid: P11289
tag: ['贪心', 'O2优化', '排序', '优先队列', '梦熊比赛']
---
# 【MX-S6-T1】「KDOI-11」打印
## 题目背景

原题链接：<https://oier.team/problems/S6A>。
## 题目描述

巡的家有 $m$ 台打印机，编号从 $1$ 到 $m$。她有 $n$ 个文件想要打印。其中第 $i$ 个文件会在第 $t_i$ 时刻下发打印命令，打印这个文件需要 $s_i$ 的时间。

每次发送一个文件打印会选择等待时间最短的打印机，如有多个，选择编号最小的。

你需要告诉巡每台打印机打印了哪些文件。

**保证同一时刻不会下发多个打印命令。**
## 输入格式

第一行，两个正整数 $n,m$，表示文件的数量和打印机的数量。

接下来 $n$ 行，每行两个正整数 $s_i,t_i$，表示第 $i$ 个文件需要的打印时间以及下发命令的时刻。保证所有 $t_i$ 互不相同。
## 输出格式

$m$ 行，第 $i$ 行 $k_i + 1$ 个整数：
- 第一个非负整数 $k_i$，表示第 $i$ 台打印机打印的文件数量；
- 接下来 $k_i$ 个正整数，从小到大排序，表示其打印的文件编号。
## 样例

### 样例输入 #1
```
3 3
2 3
2 1
5 2
```
### 样例输出 #1
```
2 1 2
1 3
0
```
## 提示

**【样例解释 #1】**

共有 $3$ 台打印机。按时间顺序，打印命令如下：
- 文件 $2$ 在第 $1$ 秒被下发。此时所有打印机等待时间都是 $0$。因此选择编号最小的 $1$ 号打印机。
- 文件 $3$ 在第 $2$ 秒被下发。此时 $1$ 号打印机正在打印文件 $2$，其余打印机等待时间都是 $0$。因此选择编号最小的 $2$ 号打印机。
- 文件 $1$ 在第 $3$ 秒被下发。此时 $1$ 号打印机已经完成文件 $2$ 的打印，等待时间为 $0$。因此选择 $1$ 号打印机。

故三台打印机分别打印了编号为 $[1,2],[3],[]$ 的文件。

**【样例 #2】**

见附件中的 `print/print2.in` 与 `print/print2.ans`。

该组样例满足测试点 $1\sim 3$ 的约束条件。

**【样例 #3】**

见附件中的 `print/print3.in` 与 `print/print3.ans`。

该组样例满足测试点 $4\sim 9$ 的约束条件。

**【样例 #4】**

见附件中的 `print/print4.in` 与 `print/print4.ans`。

该组样例满足测试点 $18\sim 20$ 的约束条件。

**【数据范围】**

对于所有测试数据，保证：$1\leq n,m\leq 2\times 10^5$，$1\leq s_i,t_i\leq 10^9$，所有 $t_i$ 互不相同。

| 测试点编号  |   $n,m\leq$    | $s_i\leq $ |   $t_i\leq $   |
| :---------: | :------------: | :--------: | :------------: |
|  $1\sim 3$  |      $10$      |   $10^9$   |     $10^9$     |
|  $4\sim 9$  |     $5000$     |   $10^9$   |     $10^9$     |
| $10\sim 13$ | $2\times 10^5$ |    $1$     |     $2\times 10^5$     |
| $14\sim 17$ | $2\times 10^5$ |   $10^9$   | $2\times 10^5$ |
| $18\sim 20$ | $2\times 10^5$ |   $10^9$   |     $10^9$     |




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
title: "[NOI2015] 荷马史诗"
layout: "post"
diff: 普及+/提高
pid: P2168
tag: ['贪心', '2015', '堆', 'NOI', '优先队列', '霍夫曼树']
---
# [NOI2015] 荷马史诗
## 题目背景

> 追逐影子的人，自己就是影子 —— 荷马
## 题目描述

Allison 最近迷上了文学。她喜欢在一个慵懒的午后，细细地品上一杯卡布奇诺，静静地阅读她爱不释手的《荷马史诗》。但是由《奥德赛》和《伊利亚特》 组成的鸿篇巨制《荷马史诗》实在是太长了，Allison 想通过一种编码方式使得它变得短一些。

一部《荷马史诗》中有 $n$ 种不同的单词，从 $1$ 到 $n$ 进行编号。其中第 $i$ 种单词出现的总次数为 $w_i$。Allison 想要用 $k$ 进制串 $s_i$ 来替换第 $i$ 种单词，使得其满足如下要求：

对于任意的 $1\leq i, j\leq n$ ，$i\ne j$ ，都有：$s_i$ 不是 $s_j$ 的前缀。

现在 Allison 想要知道，如何选择 $s_i$，才能使替换以后得到的新的《荷马史诗》长度最小。在确保总长度最小的情况下，Allison 还想知道最长的 $s_i$ 的最短长度是多少？

一个字符串被称为 $k$ 进制字符串，当且仅当它的每个字符是 $0$ 到 $k-1$ 之间（包括 $0$ 和 $k-1$ ）的整数。

字符串 $str1$ 被称为字符串 $str2$ 的前缀，当且仅当：存在 $1 \leq t\leq m$ ，使得 $str1 = str2[1..t]$。其中，$m$ 是字符串 $str2$ 的长度，$str2[1..t]$ 表示 $str2$ 的前 $t$ 个字符组成的字符串。
## 输入格式

输入的第 $1$ 行包含 $2$ 个正整数 $n, k$ ，中间用单个空格隔开，表示共有 $n$ 种单词，需要使用 $k$ 进制字符串进行替换。

接下来 $n$ 行，第 $i + 1$ 行包含 $1$ 个非负整数 $w_i$，表示第 $i$ 种单词的出现次数。
## 输出格式

输出包括 $2$ 行。

第 $1$ 行输出 $1$ 个整数，为《荷马史诗》经过重新编码以后的最短长度。

第 $2$ 行输出 $1$ 个整数，为保证最短总长度的情况下，最长字符串 $s_i$ 的最短长度。
## 样例

### 样例输入 #1
```
4 2
1
1
2
2

```
### 样例输出 #1
```
12
2
```
### 样例输入 #2
```
6 3
1
1
3
3
9
9

```
### 样例输出 #2
```
36
3

```
## 提示

#### 【样例解释】

#### 样例 1 解释

用 $X(k)$ 表示 $X$ 是以 $k$ 进制表示的字符串。

一种最优方案：令 $00(2)$ 替换第 $1$ 种单词， $01(2)$ 替换第 2 种单词， $10(2)$ 替换第 $3$ 种单词，$11(2)$ 替换第 $4$ 种单词。在这种方案下，编码以后的最短长度为：

$1 × 2 + 1 × 2 + 2 × 2 + 2 × 2 = 12$

最长字符串 $s_i$ 的长度为 $2$ 。

一种非最优方案：令 $000(2)$ 替换第 $1$ 种单词，$001(2)$ 替换第 $2$ 种单词，$01(2)$ 替换第 $3$ 种单词，$1(2)$ 替换第 $4$ 种单词。在这种方案下，编码以后的最短长度为：

$1 × 3 + 1 × 3 + 2 × 2 + 2 × 1 = 12$

最长字符串 $s_i$ 的长度为 $3$ 。与最优方案相比，文章的长度相同，但是最长字符串的长度更长一些。

#### 样例 2 解释

一种最优方案：令 $000(3)$ 替换第 $1$ 种单词，$001(3)$ 替换第 $2$ 种单词，$01(3)$ 替换第 $3$ 种单词， $02(3)$ 替换第 $4$ 种单词， $1(3)$ 替换第 5 种单词， $2(3)$ 替换第 $6$ 种单词。

#### 【数据规模与约定】

所有测试数据的范围和特点如下表所示（所有数据均满足 $0 < w_i \leq 10^{11}$）：

| 测试点编号 |  $n$ 的规模  | $k$ 的规模 |            备注            |
| :--------: | :----------: | :--------: | :------------------------: |
|    $1$     |    $n=3$     |   $k=2$    |                            |
|    $2$     |    $n=5$     |   $k=2$    |                            |
|    $3$     |    $n=16$    |   $k=2$    |     所有 $w_i$ 均相等      |
|    $4$     |  $n=1\,000$  |   $k=2$    | $w_i$ 在取值范围内均匀随机 |
|    $5$     |  $n=1\,000$  |   $k=2$    |                            |
|    $6$     | $n=100\,000$ |   $k=2$    |                            |
|    $7$     | $n=100\,000$ |   $k=2$    |     所有 $w_i$ 均相等      |
|    $8$     | $n=100\,000$ |   $k=2$    |                            |
|    $9$     |    $n=7$     |   $k=3$    |                            |
|    $10$    |    $n=16$    |   $k=3$    |     所有 $w_i$ 均相等      |
|    $11$    |  $n=1\,001$  |   $k=3$    |     所有 $w_i$ 均相等      |
|    $12$    | $n=99\,999$  |   $k=4$    |     所有 $w_i$ 均相等      |
|    $13$    | $n=100\,000$ |   $k=4$    |                            |
|    $14$    | $n=100\,000$ |   $k=4$    |                            |
|    $15$    |  $n=1\,000$  |   $k=5$    |                            |
|    $16$    | $n=100\,000$ |   $k=7$    | $w_i$ 在取值范围内均匀随机 |
|    $17$    | $n=100\,000$ |   $k=7$    |                            |
|    $18$    | $n=100\,000$ |   $k=8$    | $w_i$ 在取值范围内均匀随机 |
|    $19$    | $n=100\,000$ |   $k=9$    |                            |
|    $20$    | $n=100\,000$ |   $k=9$    |                            |

#### 【提示】

选手请注意使用 64 位整数进行输入输出、存储和计算。

#### 【评分方式】

对于每个测试点：

- 若输出文件的第 $1$ 行正确，得到该测试点 $40\%$ 的分数；
- 若输出文件完全正确，得到该测试点 $100\%$ 的分数。


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
title: "[USACO09OPEN] Work Scheduling G"
layout: "post"
diff: 普及+/提高
pid: P2949
tag: ['贪心', '递推', '2009', 'USACO', '优先队列']
---
# [USACO09OPEN] Work Scheduling G
## 题目描述

Farmer John has so very many jobs to do! In order to run the farm efficiently, he must make money on the jobs he does, each one of which takes just one time unit.

His work day starts at time 0 and has 1,000,000,000 time units (!).  He currently can choose from any of N (1 <= N <= 100,000) jobs

conveniently numbered 1..N for work to do. It is possible but

extremely unlikely that he has time for all N jobs since he can only work on one job during any time unit and the deadlines tend to fall so that he can not perform all the tasks.

Job i has deadline D\_i (1 <= D\_i <= 1,000,000,000). If he finishes job i by then, he makes a profit of P\_i (1 <= P\_i <= 1,000,000,000).

What is the maximum total profit that FJ can earn from a given list of jobs and deadlines?  The answer might not fit into a 32-bit integer.



## 输入格式

\* Line 1: A single integer: N

\* Lines 2..N+1: Line i+1 contains two space-separated integers: D\_i and P\_i

## 输出格式

\* Line 1: A single number on a line by itself that is the maximum possible profit FJ can earn.

## 样例

### 样例输入 #1
```
3 
2 10 
1 5 
1 7 

```
### 样例输出 #1
```
17 

```
## 提示

Complete job 3 (1,7) at time 1 and complete job 1 (2,10) at time 2 to maximize the earnings (7 + 10 -> 17).

## 题目翻译

约翰有太多的工作要做。为了让农场高效运转，他必须靠他的工作赚钱，每项工作花一个单位时间。 他的工作日从 $0$ 时刻开始，有 $10^9$ 个单位时间。在任一时刻，他都可以选择编号 $1$ 到 $N$ 的 $N(1 \leq N \leq 10^5)$ 项工作中的任意一项工作来完成。 因为他在每个单位时间里只能做一个工作，而每项工作又有一个截止日期，所以他很难有时间完成所有N个工作，虽然还是有可能。 对于第 $i$ 个工作，有一个截止时间 $D_i(1 \leq D_i \leq 10^9)$，如果他可以完成这个工作，那么他可以获利 $P_i( 1\leq P_i\leq 10^9 )$. 在给定的工作利润和截止时间下，约翰能够获得的利润最大为多少.


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
title: "[USACO17JAN] Cow Dance Show S"
layout: "post"
diff: 普及+/提高
pid: P3611
tag: ['模拟', '2017', '线段树', '二分', 'USACO', '优先队列', '队列']
---
# [USACO17JAN] Cow Dance Show S
## 题目描述

After several months of rehearsal, the cows are just about ready to put on their annual dance performance; this year they are performing the famous bovine ballet "Cowpelia".

The only aspect of the show that remains to be determined is the size of the stage. A stage of size $K$ can support $K$ cows dancing simultaneously. The $N$ cows in the herd ($1 \leq N \leq 10,000$) are conveniently numbered $1 \ldots N$ in the order in which they must appear in the dance. Each cow $i$ plans to dance for a specific duration of time $d(i)$. Initially, cows $1 \ldots K$ appear on stage and start dancing. When the first of these cows completes her part, she leaves the stage and cow $K+1$ immediately starts dancing, and so on, so there are always $K$ cows dancing (until the end of the show, when we start to run out of cows). The show ends when the last cow completes her dancing part, at time $T$.

Clearly, the larger the value of $K$, the smaller the value of $T$. Since the show cannot last too long, you are given as input an upper bound $T_{max}$ specifying the largest possible value of $T$. Subject to this constraint, please determine the smallest possible value of $K$.


## 输入格式

The first line of input contains $N$ and $T_{max}$, where $T_{max}$ is an integer of value at most 1 million.

The next $N$ lines give the durations $d(1) \ldots d(N)$ of the dancing parts for cows $1 \ldots N$. Each $d(i)$ value is an integer in the range $1 \ldots 100,000$.

It is guaranteed that if $K=N$, the show will finish in time.


## 输出格式

Print out the smallest possible value of $K$ such that the dance performance will take no more than $T_{max}$ units of time.


## 样例

### 样例输入 #1
```
5 8
4
7
8
6
4
```
### 样例输出 #1
```
4

```
## 题目翻译

### 题目描述

经过几个月的排练，奶牛们基本准备好展出她们的年度舞蹈表演。今年她们要表演的是著名的奶牛芭蕾——“cowpelia”。

表演唯一有待决定的是舞台的尺寸。一个大小为 $K$ 的舞台可以支持 $K$ 头牛同时在舞台上跳舞。在牛群中的 $N$ 头牛按照她们必须出现在舞蹈中的顺序方便地编号为 $1,2,\dots,N$。第 $i$ 头牛计划跳 $d_i$ 的特定持续时间。
一开始，第 $1,2,\dots,K$ 头牛出现在舞台上并开始跳舞。当这些牛中的某一头牛首先完成了她的部分，她会马上离开舞台并且第 $K+1$ 头牛会出现在舞台上并开始跳舞。所以，舞台上总有 $K$ 头奶牛在跳舞（直到表演的尾声，奶牛不够的时候）。当最后一头奶牛完成了她的舞蹈部分，表演结束，共花了 $T$ 个单位时间。

显然，$K$ 的值越大，$T$ 就越小。由于表演不能拖太长，你得知了指定 $T$ 的最大可能值的上限 $T_{max}$。请根据这个约束，确定 $K$ 的最小值。

### 输入格式

第一行包括 $N$ 和 $T_{max}$ 两个整数。

接下来的 $N$ 行，第 $i$ 行给出了第 $i$ 头牛跳舞的持续时间 $d_i$。第 $i$ 行包括一个整数 $d_i$。

保证 $K=N$ 时表演会按时完成。

### 输出格式

输出在表演时间不大于 $T_{max}$ 时的 $K$ 的最小可能值。

### 提示说明

对于 $100\%$ 的数据，$1 \le N \le 10^4$，$T_{max} \le 10^6$，$1 \le d_i \le 10^5$。


---

---
title: "[AHOI2017初中组] alter"
layout: "post"
diff: 普及+/提高
pid: P3718
tag: ['字符串', '贪心', '2017', '二分', '安徽', '枚举', '队列']
---
# [AHOI2017初中组] alter
## 题目描述

有 $n$ 盏灯排成一列，其中有些灯开着，有些灯关着。小可可希望灯是错落有致的，他定义一列灯的状态的不优美度为这些灯中最长的连续的开着或关着的灯的个数。小可可最多可以按开关 $k$ 次，每次操作可以使该盏灯的状态取反：原来开着的就关着，反之开着。现在给出这些灯的状态，求操作后最小的不优美度。
## 输入格式

第一行两个整数 $n,k$。

第二行是一个长度为 $n$ 的字符串，其中有两种字符：`N` 和 `F`。其中 `N` 表示该灯开着，`F` 表示该灯关着。
## 输出格式

最小的不优美度。
## 样例

### 样例输入 #1
```
8 1
NNNFFNNN
```
### 样例输出 #1
```
3
```
## 提示

$30\%$ 的数据：$1\le k \le n\le20$；

$50\%$ 的数据：$1\le k \le n\le300$；

另有 $15\%$ 的数据：$1\le k \le n\le 10^5$，字符串为全 `N` 或全 `F`；

$100\%$ 的数据：$1\le k \le n\le 10^5$。

本题已经加入 hack 数据。


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
title: "[JSOI2007] 建筑抢修"
layout: "post"
diff: 普及+/提高
pid: P4053
tag: ['贪心', '2007', '各省省选', '江苏', '优先队列']
---
# [JSOI2007] 建筑抢修
## 题目描述

小刚在玩 JSOI 提供的一个称之为“建筑抢修”的电脑游戏：经过了一场激烈的战斗，T 部落消灭了所有 Z 部落的入侵者。但是 T 部落的基地里已经有 $N$ 个建筑设施受到了严重的损伤，如果不尽快修复的话，这些建筑设施将会完全毁坏。现在的情况是：T 部落基地里只有一个修理工人，虽然他能瞬间到达任何一个建筑，但是修复每个建筑都需要一定的时间。同时，修理工人修理完一个建筑才能修理下一个建筑，不能同时修理多个建筑。如果某个建筑在一段时间之内没有完全修理完毕，这个建筑就报废了。你的任务是帮小刚合理的制订一个修理顺序，以抢修尽可能多的建筑。

## 输入格式

第一行，一个整数 $N$。

接下来 $N$ 行，每行两个整数 $T_1,T_2$ 描述一个建筑：修理这个建筑需要 $T_1$ 秒，如果在 $T_2$ 秒之内还没有修理完成，这个建筑就报废了。

## 输出格式

输出一个整数 $S$，表示最多可以抢修 $S$ 个建筑。

## 样例

### 样例输入 #1
```
4
100 200
200 1300
1000 1250
2000 3200
```
### 样例输出 #1
```
3
```
## 提示

对于 $100 \%$ 的数据，$1 \le N < 150000$，$1 \le T_1 < T_2 < 2^{31}$。


---

---
title: "[AHOI2018初中组] 分组"
layout: "post"
diff: 普及+/提高
pid: P4447
tag: ['贪心', '2018', '二分', '安徽', '队列']
---
# [AHOI2018初中组] 分组
## 题目描述

小可可的学校信息组总共有 $n$ 个队员，每个人都有一个实力值 $a_i$。现在，一年一度的编程大赛就要到了，小可可的学校获得了若干个参赛名额，教练决定把学校信息组的 $n$ 个队员分成若干个小组去参加这场比赛。

但是每个队员都不会愿意与实力跟自己过于悬殊的队员组队，于是要求分成的每个小组的队员实力值连续，同时，一个队不需要两个实力相同的选手。举个例子：$[1, 2, 3, 4, 5]$ 是合法的分组方案，因为实力值连续；$[1, 2, 3, 5]$ 不是合法的分组方案，因为实力值不连续；$[0, 1, 1, 2]$ 同样不是合法的分组方案，因为出现了两个实力值为 $1$ 的选手。

如果有小组内人数太少，就会因为时间不够而无法获得高分，于是小可可想让你给出一个合法的分组方案，满足所有人都恰好分到一个小组，使得人数最少的组人数最多，输出人数最少的组人数的最大值。

注意：实力值可能是负数，分组的数量没有限制。
## 输入格式

输入有两行：

第一行一个正整数 $n$，表示队员数量。  
第二行有 $n$ 个整数，第 $i$ 个整数 $a_i$ 表示第 $i$ 个队员的实力。
## 输出格式

输出一行，包括一个正整数，表示人数最少的组的人数最大值。
## 样例

### 样例输入 #1
```
7
4 5 2 3 -4 -3 -5
```
### 样例输出 #1
```
3

```
## 提示

【样例解释】
分为 $2$ 组，一组的队员实力值是 $\{4, 5, 2, 3\}$，一组是 $\{-4, -3, -5\}$，其中最小的组人数为 $3$，可以发现没有比 $3$ 更优的分法了。

【数据范围】

对于 $100\%$ 的数据满足：$1\leq n\leq 100000$，$|a_i|\leq10^9$。

本题共 $10$ 个测试点，编号为 $1\sim10$，每个测试点额外保证如下：
| 测试点编号 | 数据限制 |
| :-----------: | :-----------: |
| $1\sim2$ | $n\leq 6, 1\leq a_i \leq 100$ |
| $3\sim4$ | $n\leq 1000, 1\leq a_i\leq 10^5$ 且 $a_i$ 互不相同 |
| $5\sim6$ | $n\leq 100000, a_i$ 互不相同 |
| $7\sim8$ | $n\leq 100000, 1\leq a_i \leq10^5$ |
| $9\sim 10$ | $n\leq 100000, -10^9 \leq a_i \leq 10^9$ |


---

---
title: "[BalticOI 2011] Switch the Lamp On 电路维修 (Day1)"
layout: "post"
diff: 普及+/提高
pid: P4667
tag: ['2011', '线段树', '优先队列', '最短路', 'BalticOI（波罗的海）']
---
# [BalticOI 2011] Switch the Lamp On 电路维修 (Day1)
## 题目描述

Casper is designing an electronic circuit on a $N \times M$ rectangular grid plate. There are $N \times M$ square tiles that are aligned to the grid on the plate. Two (out of four) opposite corners of each tile are connected by a wire.

A power source is connected to the top left corner of the plate. A lamp is connected to the bottom right corner of the plate. The lamp is on only if there is a path of wires connecting power source to lamp. In order to switch the lamp on, any number of tiles can be turned by 90° (in both directions).

![0](http://ruanx.pw/bzojch/file/2346_0.jpg)

In the picture above the lamp is off. If any one of the tiles in the second column from the right is turned by 90° , power source and lamp get connected, and the lamp is on.

Write a program to find out the minimal number of tiles that have to be turned by 90° to switch the lamp on.
## 输入格式

The first line of input contains two integer numbers $N$ and $M$, the dimensions of the plate. In each of the following $N$ lines there are $M$ symbols – either \ or / – which indicate the direction of the wire connecting the opposite vertices of the corresponding tile.
## 输出格式

There must be exactly one line of output. If it is possible to switch the lamp on, this line must contain only one integer number: the minimal number of tiles that have to be turned to switch on the lamp. If it is not possible, output the string: ``NO SOLUTION``
## 样例

### 样例输入 #1
```
3 5
\\/\\
\\///
/\\\\
```
### 样例输出 #1
```
1
```
## 提示

对于 $40\%$ 的数据，$1 \le N \le 4$，$1 \le M \le 5$。

对于所有数据，$1 \le N,M \le 500$。
## 题目翻译

### 题目描述
Casper 正在设计电路。有一种正方形的电路元件，在它的两组相对顶点中，有一组会用导线连接起来，另一组则不会。有 $N\times M$ 个这样的元件，你想将其排列成 $N$ 行，每行 $M$ 个。 电源连接到板的左上角。灯连接到板的右下角。只有在电源和灯之间有一条电线连接的情况下，灯才会亮着。为了打开灯，任何数量的电路元件都可以转动 90°（两个方向）。

![](https://cdn.luogu.com.cn/upload/pic/1286.png)

![](https://cdn.luogu.com.cn/upload/pic/1285.png)

在上面的图片中，灯是关着的。如果右边的第二列的任何一个电路元件被旋转 90°，电源和灯都会连接，灯被打开。现在请你编写一个程序，求出最小需要多少旋转多少电路元件。

### 输入输出格式

#### 输入格式
输入的第一行包含两个整数 $N$ 和 $M$，表示盘子的尺寸。 在以下 $N$ 行中，每一行有 $M$ 个符号 `\` 或 `/`，表示连接对应电路元件对角线的导线的方向。
#### 输出格式：
如果可以打开灯，那么输出只包含一个整数，表示最少转动电路元件的数量。

如果不可能打开灯，输出 `NO SOLUTION`。


---

---
title: "[USACO19JAN] Redistricting P"
layout: "post"
diff: 普及+/提高
pid: P5202
tag: ['动态规划 DP', '2019', 'USACO', '优先队列']
---
# [USACO19JAN] Redistricting P
## 题目背景

USACO 19 年一月月赛铂金组第一题。
## 题目描述

奶牛们的特大城市，牛都，要进行重新分区了！——这总是一个在居住在这里的两大主要种族（荷斯坦牛和更赛牛）之间富有争议的政治事件，因为两大种族都想要在牛都政府中保持足够的影响力。

牛都的大都市圈由一列 $n$ 块牧草地组成，每块里有一头奶牛，均为荷斯坦牛 (Holstein) 和更赛牛 (Guernsey) 之一。

牛都政府想要将大都市圈划分为若干个连续的区，使得每个区至少包含一块牧草地且至多包含 $k$ 块牧草地，并且每块牧草地恰好属于一个区。由于政府当前由荷斯坦牛控制，她们想要找到一种分区方式能够最小化更赛牛较多或者均势的区的数量（如果更赛牛的数量与荷斯坦牛的数量相等那么这个区就是均势的）。

有一个关心政治的更赛牛团体想要知道政府的分区计划可能会对她们造成多少损害。帮助她们求出最坏情况，也就是更赛牛较多或是均势的区的最小可能的数量。
## 输入格式

输入的第一行是用空格隔开的两个整数，分别代表牧草地的个数 $n$ 和每个区包含草地的上限 $k$。

输入的第二行是一个长度为 $n$ 的字符串 $s$，$s$ 中只含字符 `H` 和 `G`。若 $s$ 的第 $i$ 个字符是 `H`，则代表第 $i$ 块草地上的奶牛是荷斯坦牛，否则是更赛牛。
## 输出格式

输出一行一个整数，代表更赛牛较多或者优势区的最小可能数量。
## 样例

### 样例输入 #1
```
7 2
HGHGGHG
```
### 样例输出 #1
```
3
```
## 提示

### 样例解释

一种可能的划分方式是 $[1],~[2, 3],~[4, 5],~[6, 7]$。第二、四个区是均势的区，第三个区是更赛牛优势的区。

### 数据范围

对于 $100\%$ 的数据，保证 $1 \leq k \leq n \leq 3 \times 10^5$，$s$ 的长度为 $n$，且只含字符 `H` 和 `G`。


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
title: "[NOIP 2004 提高组] 合并果子 加强版"
layout: "post"
diff: 普及+/提高
pid: P6033
tag: ['贪心', '2004', 'NOIP 提高组', 'O2优化', '排序', '队列']
---
# [NOIP 2004 提高组] 合并果子 加强版
## 题目背景

本题除【数据范围与约定】外与 [P1090](https://www.luogu.com.cn/problem/P1090) **完  全  一  致**。
## 题目描述

在一个果园里，多多已经将所有的果子打了下来，而且按果子的不同种类分成了不同的堆。多多决定把所有的果子合成一堆。

每一次合并，多多可以把两堆果子合并到一起，消耗的体力等于两堆果子的重量之和。可以看出，所有的果子经过 $(n - 1)$ 次合并之后， 就只剩下一堆了。多多在合并果子时总共消耗的体力等于每次合并所耗体力之和。

因为还要花大力气把这些果子搬回家，所以多多在合并果子时要尽可能地节省体力。假定每个果子重量都为 $1$，并且已知果子的种类数和每种果子的数目，你的任务是设计出合并的次序方案，使多多耗费的体力最少，并输出这个最小的体力耗费值。

例如有 $3$ 堆果子，数目依次为 $1,~2,~9$。可以先将 $1$、$2$ 堆合并，新堆数目为 $3$，耗费体力为 $3$。接着，将新堆与原先的第三堆合并，又得到新的堆，数目为 $12$，耗费体力为 $12$。所以多多总共耗费体力为 $3+12=15$。可以证明 $15$ 为最小的体力耗费值。

## 输入格式

输入的第一行是一个整数 $n$，代表果子的堆数。\
输入的第二行有 $n$ 个用空格隔开的整数，第 $i$ 个整数代表第 $i$ 堆果子的个数 $a_i$。
## 输出格式

输出一行一个整数，表示最小耗费的体力值。
## 样例

### 样例输入 #1
```
3 
1 2 9 

```
### 样例输出 #1
```
15

```
## 提示

**【数据规模与约定】**

**本题采用多测试点捆绑测试，共有四个子任务**。

- Subtask 1（10 points）：$1 \leq n \leq 8$。
- Subtask 2（20 points）：$1 \leq n \leq 10^3$。
- Subtask 3（30 points）：$1 \leq n \leq 10^5$。
- Subtask 4（40 points）：$1 \leq n \leq 10^7$。

对于全部的测试点，保证 $1 \leq a_i \leq 10^5$。

**【提示】**

- 请注意常数因子对程序效率造成的影响。
- 请使用类型合适的变量来存储本题的结果。
- 本题输入规模较大，请注意数据读入对程序效率造成的影响。




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
title: "「DPOI-1」道路规划"
layout: "post"
diff: 普及+/提高
pid: P8896
tag: ['贪心', '2022', '洛谷原创', 'O2优化', '优先队列', '构造']
---
# 「DPOI-1」道路规划
## 题目背景

不可以，总司令。
## 题目描述

战场上有 $n$ 个据点，从 $1\sim n$ 编号。**每两个据点**之间**都**有一条双向道路。

一天，总司令来战区巡视，走着走着迷路了，于是愤怒地下达命令，让你把每一条双向道路变成单向的，使得这些道路**不包含环**（否则总司令会迷路）。但由于每个据点的规模互不相同，总司令从第 $i$ 个据点出发沿着单向道路能**直接到达**的据点数量需要在 $[l_i,r_i]$ 之间。换言之，第 $i$ 个点的出度需要在 $[l_i,r_i]$ 之间。你需要告诉总司令有没有可能满足他的需求。
## 输入格式

**本题有多组测试数据。**

第一行，一个整数 $T$，表示数据组数。

对于每组数据：

第一行，一个整数 $n$，表示据点数量；

第二行，$n$ 个整数 $l_1, l_2, \dots, l_n$；

第三行，$n$ 个整数 $r_1, r_2, \dots, r_n$。
## 输出格式

对于每组数据：

一行，一个字符串。若可以满足总司令的需求，一行 `YES`；否则，一行 `NO`。
## 样例

### 样例输入 #1
```
2
5
0 1 4 0 0
3 4 4 1 3
3
1 2 2
2 2 2
```
### 样例输出 #1
```
YES
NO
```
### 样例输入 #2
```
见下发文件 road2.in
```
### 样例输出 #2
```
见下发文件 road2.out
```
## 提示

#### 样例 #1 解释
下面是第 $1$ 组数据中一种可行的方案：

![](https://cdn.luogu.com.cn/upload/image_hosting/2uvwlydw.png)

#### 样例 #2 解释
该样例满足测试点 $3 \sim 6$ 的限制。
#### 数据范围
**本题测试点分数不等分。**

|  测试点编号  | $n \le$ | 特殊条件 |每个测试点分数|
| :----------: | :-----------: | :------: | :----: |
|     $1\sim 2$      |     $10$     |   无   |$5$|
|     $3\sim 6$      |     $1000$     |    无     |$5$|
|     $7\sim 8$      |     $10^5$     |    所有 $l_i = i-1$ 或所有 $l_i \geq \min (i, n - 1)$    |$5$|
| $9 \sim 10$  | $10^5$ | $l_i=0$ 或 $r_i=n-1$ |$5$|
| $11 \sim 15$ | $10^5$ | 无 |$10$|

对于 $100\%$ 的数据，$1 \leq n \leq 10^5$，$0 \leq l_i \leq r_i < n$，$1 \leq T \leq 10$。


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

