---
title: "【MX-J8-T4】 2048"
layout: "post"
diff: 省选/NOI-
pid: P11216
tag: ['动态规划 DP', 'O2优化', '区间 DP', '动态规划优化', '前缀和', '梦熊比赛']
---
# 【MX-J8-T4】 2048
## 题目背景

原题链接：<https://oier.team/problems/J8D>。

---

[《2048》](https://2048game.com/)是一款非常好玩，火爆全球的小游戏。
## 题目描述

现在，小 Y 把《2048》稍做修改，得到如下的一维变种（其中部分规则可能与你对《2048》的印象相悖，请以下文为准）：

- 游戏在一行 $n$ 个格子组成的网格中进行。每个格子要么为空，要么包含一个带有正整数权值的方块。
- 游戏开始时，会在一个任意的格子上生成一个权值为 $2$ 的方块，其他格子为空。
- 玩家通过向左（或右，下同）滑动进行操作。每次操作：
  1. 所有方块将全部靠左（或右）堆叠放置，彼此紧贴，不留空位。
  2. 如果堆叠完毕后，存在相邻的两个方块权值相等，设其权值均为 $k$，则消除这两个方块，并在原先其中一个方块的位置生成一个权值为 $2k$ 的方块（这称作一次合并）（**可以证明，在该游戏过程中不会存在连续 $\bm 3$ 个相邻方块权值相等，因此不需要考虑合并顺序的问题**），随后所有方块继续向左（或右）堆叠，直到不存在能合并的情况为止。
  3. 最后，在最右（或左）端，即滑动方向的相反方向，生成一个权值为 $2$ 的新方块。

下图展示了一次向左滑动操作的示例。

![](https://cdn.luogu.com.cn/upload/image_hosting/d7qp6f1i.png)

- 如下定义一个方块的**出现时间**：
  - 设它被生成时，游戏进行的轮数（即玩家进行滑动操作的次数）为 $i$（包括当前操作）。
  - 如果该方块是被合并生成的，令它的出现时间为 $2 i$；
  - 否则该方块是新生成的，令它的出现时间为 $2 i + 1$；
  - 如果该方块是游戏最开始时生成的权值为 $2$ 的方块，令它的出现时间为 $1$。
  - 可以证明，按如上定义的出现时间满足：在游戏进行的任意时刻下，任意两个不同方块的出现时间均不同。
- 游戏的目标是生成 $2^x$，因此在游戏的任何过程中，一旦出现了 $2^x$，游戏立刻结束，且游戏胜利。
- 如果一次滑动操作的步骤 2 结束时，所有 $n$ 个格子全都包含方块（事实上，这次滑动操作是滑不动的，但仍然认为是一次滑动操作），则步骤 3 中无法正常生成新方块，不会进行步骤 3，且游戏失败。

小 Y 正在研究这个新 2048 游戏的所有失败状态的个数。具体地，在游戏失败时，两个失败状态 A 和 
B 被认为**本质相同**，当且仅当以下条件同时成立：

- 对每个 $1 \leq i \leq n$，A 中方块 $i$ 和 B 中方块 $i$ 的权值均相同；
- 对每对 $1 \le i < j \le n$，A 中的方块 $i$ 与方块 $j$ 的出现时间的大小关系，与 B 中的方块 $i$ 与方块 $j$ 的出现时间的大小关系相同。

小 Y 想要知道，总共有多少种**本质不同**的失败状态。答案对给定模数 $p$ 取模（$p$ 未必为素数）。
## 输入格式

**本题有多组测试数据。**

第一行，两个正整数 $T, p$，分别表示数据组数和模数。对于每组数据：

- 仅一行，两个整数 $n, x$。
## 输出格式

对于每组数据：

- 仅一行一个正整数，表示本质不同的失败状态数，答案对 $p$ 取模。
## 样例

### 样例输入 #1
```
5 71
3 4
4 3
4 4
4 5
5 6

```
### 样例输出 #1
```
8
0
12
34
20

```
## 提示

**【样例解释 \#1】**

对于第一组数据，$n = 3$，$x = 4$：
- 仅从网格状态上看，共有 $6$ 种失败的可能性：$[8, 4, 2], [2, 4, 8], [2, 8, 4], [4, 8, 2], [2, 8, 2],[2, 4, 2]$。
  - 但考虑 $[2, 8, 2]$，其可以对应两种本质不同的失败状态：
    - 中间的 $8$ 先被生成，随后左边的 $2$ 生成，随后右边的 $2$ 生成；
    - 中间的 $8$ 先被生成，随后右边的 $2$ 生成，随后左边的 $2$ 生成。
  - 对于 $[2, 4, 2]$ 也是同理。
- 对于其它的可能性，可以证明其只能对应一种本质不同的失败状态。
- 所以，答案为 $1 + 1 + 1 + 1 + 2 + 2 = 8$，在模 $71$ 意义下为 $8$。

对于第二组数据，$n = 4$，$x = 3$：
- 可以证明，无论如何，游戏都将胜利，因此不存在任何失败状态，答案为 $0$。

对于第三组数据，$n = 4$，$x = 4$：
- 仅从网格状态上看，共有 $4$ 种失败的可能性：$[2, 8, 4, 2], [2, 4, 8, 2], [4, 8, 4, 2],[2, 4, 8, 4]$。
- 其中，$[2, 8, 4, 2]$ 和 $[2, 4, 8, 2]$ 分别对应 $4$ 种本质不同的失败情况，$[4, 8, 4, 2]$ 和 $[2, 4, 8, 4]$ 分别对应 $2$ 种本质不同的失败情况。
  - 以 $[2, 8, 4, 2]$ 为例，下面列举该局面对应的 $4$ 种本质不同的失败情况（操作方式不唯一，数字上面的小数字表示出现时间）：
  $$
  \begin{aligned}
  & [\overset{\hspace{15.385mu}}{}, \overset{\hspace{3.84625mu}1\hspace{3.84625mu}}{2}, \overset{\hspace{15.385mu}}{}, \overset{\hspace{15.385mu}}{}] & & [\overset{\hspace{15.385mu}}{}, \overset{\hspace{3.84625mu}1\hspace{3.84625mu}}{2}, \overset{\hspace{15.385mu}}{}, \overset{\hspace{15.385mu}}{}] & & [\overset{\hspace{15.385mu}}{}, \overset{\hspace{3.84625mu}1\hspace{3.84625mu}}{2}, \overset{\hspace{15.385mu}}{}, \overset{\hspace{15.385mu}}{}] & & [\overset{\hspace{15.385mu}}{}, \overset{\hspace{3.84625mu}1\hspace{3.84625mu}}{2}, \overset{\hspace{15.385mu}}{}, \overset{\hspace{15.385mu}}{}] \\
  \stackrel{\text{L}}\to& [\overset{\hspace{3.84625mu}1\hspace{3.84625mu}}{2}, \overset{\hspace{15.385mu}}{}, \overset{\hspace{15.385mu}}{}, \overset{\hspace{3.84625mu}3\hspace{3.84625mu}}{2}] & \stackrel{\text{L}}\to& [\overset{\hspace{3.84625mu}1\hspace{3.84625mu}}{2}, \overset{\hspace{15.385mu}}{}, \overset{\hspace{15.385mu}}{}, \overset{\hspace{3.84625mu}3\hspace{3.84625mu}}{2}] & \stackrel{\text{L}}\to& [\overset{\hspace{3.84625mu}1\hspace{3.84625mu}}{2}, \overset{\hspace{15.385mu}}{}, \overset{\hspace{15.385mu}}{}, \overset{\hspace{3.84625mu}3\hspace{3.84625mu}}{2}] & \stackrel{\text{L}}\to& [\overset{\hspace{3.84625mu}1\hspace{3.84625mu}}{2}, \overset{\hspace{15.385mu}}{}, \overset{\hspace{15.385mu}}{}, \overset{\hspace{3.84625mu}3\hspace{3.84625mu}}{2}] \\
  \stackrel{\text{L}}\to& [\overset{\hspace{3.84625mu}4\hspace{3.84625mu}}{4}, \overset{\hspace{15.385mu}}{}, \overset{\hspace{15.385mu}}{}, \overset{\hspace{3.84625mu}5\hspace{3.84625mu}}{2}] & \stackrel{\text{L}}\to& [\overset{\hspace{3.84625mu}4\hspace{3.84625mu}}{4}, \overset{\hspace{15.385mu}}{}, \overset{\hspace{15.385mu}}{}, \overset{\hspace{3.84625mu}5\hspace{3.84625mu}}{2}] & \stackrel{\text{L}}\to& [\overset{\hspace{3.84625mu}4\hspace{3.84625mu}}{4}, \overset{\hspace{15.385mu}}{}, \overset{\hspace{15.385mu}}{}, \overset{\hspace{3.84625mu}5\hspace{3.84625mu}}{2}] & \stackrel{\text{R}}\to& [\overset{\hspace{3.84625mu}5\hspace{3.84625mu}}{2}, \overset{\hspace{15.385mu}}{}, \overset{\hspace{15.385mu}}{}, \overset{\hspace{3.84625mu}4\hspace{3.84625mu}}{4}] \\
  \stackrel{\text{L}}\to& [\overset{\hspace{3.84625mu}4\hspace{3.84625mu}}{4}, \overset{\hspace{3.84625mu}5\hspace{3.84625mu}}{2}, \overset{\hspace{15.385mu}}{}, \overset{\hspace{3.84625mu}7\hspace{3.84625mu}}{2}] & \stackrel{\text{L}}\to& [\overset{\hspace{3.84625mu}4\hspace{3.84625mu}}{4}, \overset{\hspace{3.84625mu}5\hspace{3.84625mu}}{2}, \overset{\hspace{15.385mu}}{}, \overset{\hspace{3.84625mu}7\hspace{3.84625mu}}{2}] & \stackrel{\text{L}}\to& [\overset{\hspace{3.84625mu}4\hspace{3.84625mu}}{4}, \overset{\hspace{3.84625mu}5\hspace{3.84625mu}}{2}, \overset{\hspace{15.385mu}}{}, \overset{\hspace{3.84625mu}7\hspace{3.84625mu}}{2}] & \stackrel{\text{L}}\to& [\overset{\hspace{3.84625mu}5\hspace{3.84625mu}}{2}, \overset{\hspace{3.84625mu}4\hspace{3.84625mu}}{4}, \overset{\hspace{15.385mu}}{}, \overset{\hspace{3.84625mu}7\hspace{3.84625mu}}{2}] \\
  \stackrel{\text{L}}\to& [\overset{\hspace{3.84625mu}8\hspace{3.84625mu}}{8}, \overset{\hspace{15.385mu}}{}, \overset{\hspace{15.385mu}}{}, \overset{\hspace{3.84625mu}9\hspace{3.84625mu}}{2}] & \stackrel{\text{L}}\to& [\overset{\hspace{3.84625mu}8\hspace{3.84625mu}}{8}, \overset{\hspace{15.385mu}}{}, \overset{\hspace{15.385mu}}{}, \overset{\hspace{3.84625mu}9\hspace{3.84625mu}}{2}] & \stackrel{\text{R}}\to& [\overset{\hspace{3.84625mu}9\hspace{3.84625mu}}{2}, \overset{\hspace{15.385mu}}{}, \overset{\hspace{15.385mu}}{}, \overset{\hspace{3.84625mu}8\hspace{3.84625mu}}{8}] & \stackrel{\text{L}}\to& [\overset{\hspace{3.84625mu}5\hspace{3.84625mu}}{2}, \overset{\hspace{3.84625mu}4\hspace{3.84625mu}}{4}, \overset{\hspace{3.84625mu}7\hspace{3.84625mu}}{2}, \overset{\hspace{3.84625mu}9\hspace{3.84625mu}}{2}] \\
  \stackrel{\text{L}}\to& [\overset{\hspace{3.84625mu}8\hspace{3.84625mu}}{8}, \overset{\hspace{3.84625mu}9\hspace{3.84625mu}}{2}, \overset{\hspace{15.385mu}}{}, \overset{11}{2}] & \stackrel{\text{L}}\to& [\overset{\hspace{3.84625mu}8\hspace{3.84625mu}}{8}, \overset{\hspace{3.84625mu}9\hspace{3.84625mu}}{2}, \overset{\hspace{15.385mu}}{}, \overset{11}{2}] & \stackrel{\text{L}}\to& [\overset{\hspace{3.84625mu}9\hspace{3.84625mu}}{2}, \overset{\hspace{3.84625mu}8\hspace{3.84625mu}}{8}, \overset{\hspace{15.385mu}}{}, \overset{11}{2}] & \stackrel{\text{L}}\to& [\overset{\hspace{3.84625mu}5\hspace{3.84625mu}}{2}, \overset{10}{8}, \overset{\hspace{15.385mu}}{}, \overset{11}{2}] \\
  \stackrel{\text{L}}\to& [\overset{\hspace{3.84625mu}8\hspace{3.84625mu}}{8}, \overset{12}{4}, \overset{\hspace{15.385mu}}{}, \overset{13}{2}] & \stackrel{\text{R}}\to& [\overset{13}{2}, \overset{\hspace{15.385mu}}{}, \overset{\hspace{3.84625mu}8\hspace{3.84625mu}}{8}, \overset{12}{4}] & \stackrel{\text{L}}\to& [\overset{\hspace{3.84625mu}9\hspace{3.84625mu}}{2}, \overset{\hspace{3.84625mu}8\hspace{3.84625mu}}{8}, \overset{11}{2}, \overset{13}{2}] & \stackrel{\text{L}}\to& [\overset{\hspace{3.84625mu}5\hspace{3.84625mu}}{2}, \overset{10}{8}, \overset{11}{2}, \overset{13}{2}] \\
  \stackrel{\text{R}}\to& [\overset{15}{2}, \overset{\hspace{3.84625mu}8\hspace{3.84625mu}}{8}, \overset{12}{4}, \overset{13}{2}] & \stackrel{\text{L}}\to& [\overset{13}{2}, \overset{\hspace{3.84625mu}8\hspace{3.84625mu}}{8}, \overset{12}{4}, \overset{15}{2}] & \stackrel{\text{L}}\to& [\overset{\hspace{3.84625mu}9\hspace{3.84625mu}}{2}, \overset{\hspace{3.84625mu}8\hspace{3.84625mu}}{8}, \overset{14}{4}, \overset{15}{2}] & \stackrel{\text{L}}\to& [\overset{\hspace{3.84625mu}5\hspace{3.84625mu}}{2}, \overset{10}{8}, \overset{14}{4}, \overset{15}{2}]
  \end{aligned}
  $$
  对这 $4$ 种情况，出现时间的大小关系（离散化后）分别为 $[4, 1, 2, 3]$、$[3, 1, 2, 4]$、$[2, 1, 3, 4]$、$[1, 2, 3, 4]$。
- 所以，答案为 $4 + 4 + 2 + 2 = 12$，在模 $71$ 意义下为 $12$。

对于第四组数据，$n = 4$，$x = 5$：
- 可以证明答案为 $34$，在模 $71$ 意义下为 $34$。

对于第五组数据，$n = 5$，$x = 6$：
- 可以证明答案为 $162$，在模 $71$ 意义下为 $20$。

**【样例 \#2】**

见附件中的 `game/game2.in` 与 `game/game2.ans`。

该组样例满足测试点 $3 \sim 5$ 的约束条件。

**【样例 \#3】**

见附件中的 `game/game3.in` 与 `game/game3.ans`。

该组样例满足测试点 $6 \sim 10$ 的约束条件。

**【样例 \#4】**

见附件中的 `game/game4.in` 与 `game/game4.ans`。

该组样例满足测试点 $14 \sim 17$ 的约束条件。

**【样例 \#5】**

见附件中的 `game/game5.in` 与 `game/game5.ans`。

该组样例满足测试点 $22 \sim 25$ 的约束条件。

**【数据范围】**

本题共 $25$ 个测试点，每个 $4$ 分。

|测试点编号|$T \le$|$n,x \le$|特殊性质|
| :-----------: | :-------------:|:-----------:|:-----------: |
|$1\sim2$|$10$|$4$|无
|$3\sim5$|$10$|$10$|无
|$6\sim10$|$10$|$22$|无
|$11\sim13$|$1$|$80$|无
|$14\sim17$|$1000$|$80$|无
|$18\sim20$|$1$|$300$|无
|$21$|$10^5$|$300$| $p = 2$ |
|$22\sim25$|$10^5$|$300$|无


对于全部数据，保证：$1\le T\le 10^5$，$1\le n,x\le 300$，$2\le p\le10^9$。


---

---
title: "[GCJ 2013 #3] Observation Wheel"
layout: "post"
diff: 省选/NOI-
pid: P13301
tag: ['动态规划 DP', '2013', 'Special Judge', '区间 DP', '概率论', '期望', 'Google Code Jam']
---
# [GCJ 2013 #3] Observation Wheel
## 题目描述

An observation wheel consists of $N$ passenger gondolas arranged in a circle, which is slowly rotating. Gondolas pass the entrance one by one, and when a gondola passes the entrance, a person may enter that gondola.

In this problem, the gondolas are so small that they can take just one person each, so if the gondola passing by the entrance is already occupied, the person waiting at the entrance will have to wait for the next one to arrive. If that gondola is also occupied, the person will have to wait for the next one after that, and so on, until a free gondola arrives. For simplicity, we will not consider people exiting the gondolas in this problem — let's assume that all people do is enter the gondolas, and then rotate with the wheel for an arbitrarily long time.

We want to make sure people are not disappointed because of long waiting times, and so we have introduced a flexible pricing scheme: when a person approaches the wheel, and the first gondola passing by the entrance is free, she pays $N$ dollars for the ride. If the first gondola is occupied and she has to wait for the second one, she pays $N-1$ dollars for the ride. If the first two gondolas are occupied and she has to wait for the third one, she pays $N-2$ dollars for the ride. Generally, if she has to wait for $K$ occupied gondolas to pass by, she pays $N-K$ dollars. In the worst case, when she has to wait for all but one gondola to pass, she will pay just 1 dollar.

Let's assume that people approach our wheel at random moments in time, so for each person approaching the wheel, the first gondola to pass the entrance is picked uniformly and independently. Let's also assume that nobody will come to the wheel while there's already at least one person waiting to enter, so that we don't have to deal with queueing. A person will always take the first free gondola that passes the entrance.

You are given the number of gondolas and which gondolas are already occupied. How much money are we going to make, on average, until all gondolas become occupied?
## 输入格式

The first line of the input gives the number of test cases, $T$. $T$ lines follow. Each line describes one test case and contains only '.' (dot) or 'X' (capital letter X) characters. The number of characters in this line gives you $N$. The $i$-th character is 'X' when the $i$-th gondola is already occupied, and '.' when it's still free. The gondolas are numbered in the order they pass the entrance, so the 1st gondola is followed by the 2nd gondola, and so on, starting over from the beginning after the last gondola passes.

## 输出格式

For each test case, output one line containing "Case #x: y", where $x$ is the case number (starting from 1) and $y$ is the average amount of money we will get, in dollars. Answers with absolute or relative error no larger than $10^{-9}$ will be accepted. See the FAQ for an explanation of what that means, and what formats of floating-point numbers we accept.
## 样例

### 样例输入 #1
```
5
.X.
X.X.
.XX.
X..XX.
.XX..X
```
### 样例输出 #1
```
Case #1: 4.66666666666667
Case #2: 6.00000000000000
Case #3: 5.75000000000000
Case #4: 13.4722222222222
Case #5: 13.5277777777778
```
## 提示

**Sample Explanation**

Here's how the first example works. There are nine possibilities, each with probability $1/9$:

The first person comes. If the next gondola to pass the entrance is:

* The 1st gondola, which is free, the first person enters it and pays 3 dollars. Then, some time later, the second person comes. If the next gondola to pass the entrance is:
    * The 1st gondola, which is occupied, and so is the 2nd gondola, the second person has to wait until the 3rd gondola, and thus she pays just 1 dollar before entering it. In total, we've earned 4 dollars.
    * The 2nd gondola, which is occupied, the second person has to skip it and enter the 3rd gondola and thus pays 2 dollars. In total, we've earned 5 dollars.
    * The 3rd gondola, which is free, so the second person pays 3 dollars. In total, we've earned 6 dollars.
* The 2nd gondola, which is occupied, the first person has to skip it and enter the 3rd gondola, paying 2 dollars. Then, some time later, the second person comes. If the next gondola to pass the entrance is:
    * The 1st gondola, which is free, the second person pays 3 dollars. In total, we've earned 5 dollars.
    * The 2nd gondola, which is occupied (as is the 3rd gondola), the second person has to wait until the 1st gondola, and thus she pays just 1 dollar before entering it. In total, we've earned 3 dollars.
    * The 3rd gondola, which is occupied, the second person has to skip it and enter the 1st gondola and thus pays 2 dollars. In total, we've earned 4 dollars.
* The 3rd gondola, which is free, the first person enters it and pays 3 dollars. Then, some time later, the second person comes. If the next gondola to pass the entrance is:
    * The 1st gondola, which is free, the second person pays 3 dollars. In total, we've earned 6 dollars.
    * The 2nd gondola, which is occupied (as is the 3rd gondola), the second person has to wait until the 1st gondola, and thus she pays just 1 dollar before entering it. In total, we've earned 4 dollars.
    * The 3rd gondola, which is occupied, the second person has to skip it and enter the 1st gondola and thus pays 2 dollars. In total, we've earned 5 dollars.

We have nine possibilities, earning 3 dollars in one of them, 4 dollars in three of them, 5 dollars in three of them, and 6 dollars in two of them. On average, we earn $(1\times 3+3\times 4+3\times 5+2\times 6)/9=42/9=4.6666666666\dots$ dollars.

**Limits**

- $1 \leq T \leq 50$. 

**Small dataset (8 Pts, Test set 1 - Visible)**

- Time limit: ~~30~~ 3 seconds.
- $1 \leq N \leq 20$.

**Large dataset (23 Pts, Test set 2 - Hidden)**

- Time limit: ~~60~~ 6 seconds.
- $1 \leq N \leq 200$.


---

---
title: "[OOI 2024] Big Persimmon"
layout: "post"
diff: 省选/NOI-
pid: P13505
tag: ['动态规划 DP', '2024', '区间 DP', '动态规划优化', 'Moscow Olympiad']
---
# [OOI 2024] Big Persimmon
## 题目描述

Alice and Bob bought a big persimmon, cut it into $n$ pieces with sizes $w_1, \dots, w_n$, and immediately started eating it. The kids will eat the pieces simultaneously, and for each of them, the eating process is as follows:

As soon as someone finishes eating their previous piece (and at the beginning of the meal), they choose the next piece and start eating it. If a piece of size $w$ is taken, it will take exactly $w$ seconds to eat it, and then it will be time to choose a new piece. If both finish eating their previous piece at the same time (or if the eating just started), Alice will choose the first piece, but they will start eating at the same time. Choosing a new piece does not take time.

Since both Alice and Bob are perfectionists, when they choose a piece, they will take either the smallest (with the smallest $w_i$) or the largest (with the largest $w_i$) from all the remaining pieces.

The eating process ends when the last person finishes eating and there are no more pieces left.

Both Alice and Bob are interested in eating as much as possible. Find the total size of the pieces that Alice will eat and the total size of the pieces that Bob will eat, if they both choose the pieces optimally.
## 输入格式

The first line contains a single integer $n$ $(1 \le n \le 2000)$ --- the number of persimmon pieces.

The second line contains $n$ integers $w_1,\ w_2,\ \dots,\ w_n$ ($1 \le w_i \le 20\,000$, $w_i \le w_{i + 1}$) --- the sizes of the persimmon pieces.

Let $W$ denote the sum of the sizes of all the pieces. It is guaranteed that $W \le 20\,000$.
## 输出格式

In a single line, output two numbers --- the total size of the pieces that Alice will eat and the total size of the pieces that Bob will eat, if they both choose the pieces optimally.
## 样例

### 样例输入 #1
```
5
1 1 3 4 6
```
### 样例输出 #1
```
8 7
```
### 样例输入 #2
```
4
1 1 2 2
```
### 样例输出 #2
```
3 3
```
### 样例输入 #3
```
4
1 7 7 9
```
### 样例输出 #3
```
10 14

```
## 提示

### Note

In the first example, Alice should first take a piece of size $1$. Immediately after that, Bob should also take a piece of size $1$. After a second, Alice will take a piece of size $3$, and then Bob will take a piece of size $6$. $3$ seconds later, Alice will take a piece of size $4$. $3$ seconds later, Bob will finish eating, and a second later the process will finish. At this point, Alice will eat pieces of sizes $1 + 3 + 4 = 8$, and Bob: $1 + 6 = 7$.

In the third example, Alice should take a piece of size $1$, and Bob should take a piece of size $7$. After a second, Alice will take a piece of size $9$, and $6$ seconds later, Bob will take a piece of size $7$.

### Scoring

The tests for this problem consist of four groups. Points for each group are given only if all tests of the group and all tests of the required groups are passed.. Note that passing the example tests is not required for some groups. $\textbf{Offline-evaluation}$ means that the results of testing your solution on this group will only be available after the competition.

| Group | Points | Additional constraints | <|Required Groups | Comment |
|:-----:|:------:|:----------------------:|:--:|:---------------:|:-------:|
|       |        | $n$ | $w_i$ | | |
| 0 | 0 | -- | -- | -- | Examples. |
| 1 | 10 | $n = 3$ | -- | -- | -- |
| 2 | 12 | -- | $w_i \le 2$ | -- | -- |
| 3 | 19 | $n \le 200$ | $w_i \le 500$ | 0 | -- |
| 4 | 15 | $n \le 500$ | $W \le 5000$ | -- | $w_{i+1} \le 2 \cdot w_i$ for all $1 \le i \le n - 1$ |
| 5 | 13 | -- | -- | 2, 4 | $w_{i+1} \le 2 \cdot w_i$ for all $1 \le i \le n - 1$ |
| 6 | 31 | -- | -- | 0 -- 5 | **Offline-evaluation.** |


---

---
title: "[NWRRC 2023] First Solved, Last Coded"
layout: "post"
diff: 省选/NOI-
pid: P13586
tag: ['模拟', '动态规划 DP', '2023', 'Special Judge', '区间 DP', 'ICPC', 'NWRRC']
---
# [NWRRC 2023] First Solved, Last Coded
## 题目描述

In ICPC, teamwork is everything. That's why everyone on your team has a well-defined role: Sol the Solver can solve any problem in the problem set, Codie the Coder can implement any solution that Sol comes up with, and you... are the glue that holds everything together. Sol and Codie are very picky about the order of problems they would solve/code, and your job is to satisfy their preferences.

There will be $n$ problems in the upcoming contest, and you know the general topic of each problem: greedy, geometry, graphs, etc. For simplicity, we will represent each topic with an integer from $1$ to $n$. These integers don't have to be distinct, that is, multiple problems in the contest can have the same topic.

Sol wants to solve problems in a specific order of topics: first, the problem with the topic $a_1$, after that, the problem with the topic $a_2$, $\ldots$, and finally, the problem with the topic $a_n$. Codie also has a preference list: $b_1, b_2, \ldots, b_n$, only willing to code problems in that order of topics.

Your job during the contest will be to take solution sheets from Sol and hand them to Codie in the correct order. As your team only has one table to work with, you don't have enough space to arrange all the solutions neatly. Thus, you came up with the following workflow: you will ask Sol for solutions (who will hand them to you in order $a_1, a_2, \ldots, a_n$), store them in a stack on your part of the table, and hand them to Codie to code (in order $b_1, b_2, \ldots, b_n$).

More formally, at any moment during the contest, you have (at most) two actions you can make:

- If there are still any unsolved problems remaining, ask Sol for another solution and put it on top of your stack of solution sheets. This action is denoted by the character $\tt{S}$.
- If your stack is not empty, take the solution sheet from the top of your stack and give it to Codie to implement. This action is denoted by the character $\tt{C}$.

For the given lists of Sol's and Codie's preferences, find a sequence of actions that ensures that all problems are solved and coded in the correct order. Consider all solving and coding times insignificant --- managing solution sheets is a much harder and more important job anyway.
## 输入格式

The first line contains a single integer $n$, denoting the number of problems in the contest ($1 \le n \le 100$).

The second line contains $n$ integers $a_1, a_2, \ldots, a_n$, denoting Sol's preferred order of topics ($1 \le a_i \le n$).

The third line contains $n$ integers $b_1, b_2, \ldots, b_n$, denoting Codie's preferred order of topics ($1 \le b_i \le n$).

The given lists are equal as multisets: every integer occurs the same number of times in $A$ and in $B$.
## 输出格式

If your task is impossible, print $\tt{NO}$. Otherwise, print $\texttt{YES}$ on the first line, followed by the sequence of actions on the second line: a string consisting of $2n$ characters $\tt{S}$ or $\tt{C}$ ($n$ of each), describing your actions in order.

You are not allowed to ask Sol for more solutions if all $n$ problems have already been solved, or give Codie a solution with the wrong topic. If there are multiple answers, print any of them.
## 样例

### 样例输入 #1
```
4
4 1 2 2
1 2 4 2
```
### 样例输出 #1
```
YES
SSCSCCSC
```
### 样例输入 #2
```
3
2 3 1
1 2 3
```
### 样例输出 #2
```
NO
```


---

---
title: "[NOI2009] 二叉查找树"
layout: "post"
diff: 省选/NOI-
pid: P1864
tag: ['动态规划 DP', '2009', 'NOI', '区间 DP']
---
# [NOI2009] 二叉查找树
## 题目描述

已知一棵特殊的二叉查找树。根据定义，该二叉查找树中每个结点的数据值都比它左儿子结点的数据值大，而比它右儿子结点的数据值小。

另一方面，这棵查找树中每个结点都有一个权值，每个结点的权值都比它的儿子结点的权值要小。

已知树中所有结点的数据值各不相同；所有结点的权值也各不相同。这时可得出这样一个有趣的结论：如果能够确定树中每个结点的数据值和权值，那么树的形态便可以唯一确定。因为这样的一棵树可以看成是按照权值从小到大顺序插入结点所得到的、按照数据值排序的二叉查找树。

一个结点在树中的深度定义为它到树根的距离加 $1$。因此树的根结点的深度为 $1$。

每个结点除了数据值和权值以外，还有一个访问频度。我们定义一个结点在树中的访问代价为它的访问频度乘以它在树中的深度。整棵树的访问代价定义为所有结点在树中的访问代价之和。

现在给定每个结点的数据值、权值和访问频度，你可以根据需要修改某些结点的权值，但每次修改你会付出 $K$ 的额外修改代价。你可以把结点的权值改为任何实数，但是修改后所有结点的权值必须仍保持互不相同。现在你要解决的问题是，整棵树的访问代价与额外修改代价的和最小是多少？
## 输入格式

输入文件中的第一行为两个正整数 $N,K$。其中 $N$ 表示结点的个数，$K$ 表示每次修改所需的额外修改代价。

接下来的一行为 $N$ 个非负整数，表示每个结点的数据值。

再接下来的一行为 $N$ 个非负整数，表示每个结点的权值。

再接下来的一行为 $N$ 个非负整数，表示每个结点的访问频度。

其中：所有的数据值、权值、访问频度均不超过 $4 \times 10^5$。
## 输出格式

输出文件中仅一行为一个数，即你所能得到的整棵树的访问代价与额外修改代价之和的最小值。

## 样例

### 样例输入 #1
```
4 10
1 2 3 4
1 2 3 4
1 2 3 4

```
### 样例输出 #1
```
29
```
## 提示

### 样例解释

![](https://cdn.luogu.com.cn/upload/image_hosting/10bjubxe.png)

输入的原图是左图，它的访问代价是 $1 \times 1+2 \times 2+3 \times 3+4 \times 4=30$。

最佳的修改方案是把输入中的第 $3$ 个结点的权值改成 $0$，得到右图，访问代价是：$1 \times 2+2 \times 3+3 \times 1+4 \times 2=19$，加上额外修改代价 $10$，一共是 $29$。

### 数据范围

- 对于 $40\%$ 的数据，满足 $N \leq 30$；
- 对于 $70\%$ 的数据，满足 $N \leq 50$；
- 对于 $100\%$ 的数据，满足：$1 \leq N \leq 70$，$1 \leq K \leq 3 \times 10^7$。



---

---
title: "[SCOI2007] 压缩"
layout: "post"
diff: 省选/NOI-
pid: P2470
tag: ['字符串', '动态规划 DP', '2007', '四川', '各省省选', '区间 DP']
---
# [SCOI2007] 压缩
## 题目描述

给一个由小写字母组成的字符串，我们可以用一种简单的方法来压缩其中的重复信息。压缩后的字符串除了小写字母外还可以（但不必）包含大写字母R与M，其中M标记重复串的开始，R重复从上一个M（如果当前位置左边没有M，则从串的开始算起）开始的解压结果（称为缓冲串）。


`bcdcdcdcd` 可以压缩为 `bMcdRR`，下面是解压缩的过程：


已经解压的部分|解压结果|缓冲串
---|---|---
b|b|b
bM|b|.
bMc|bc|c
bMcd|bcd|cd
bMcdR|bcdcd|cdcd
bMcdRR|bcdcdcdcd|cdcdcdcd


## 输入格式

输入仅一行，包含待压缩字符串，仅包含小写字母，长度为n。

## 输出格式

输出仅一行，即压缩后字符串的最短长度。

## 样例

### 样例输入 #1
```
aaaaaaa
```
### 样例输出 #1
```
5
```
### 样例输入 #2
```
bcdcdcdcdxcdcdcdcd
```
### 样例输出 #2
```
12
```
## 提示

在第一个例子中，解为aaaRa，在第二个例子中，解为bMcdRRxMcdRR。


【限制】

50%的数据满足：1<=n<=20

 
100%的数据满足：1<=n<=50




---

---
title: "[SHOI2008] 仙人掌图 II"
layout: "post"
diff: 省选/NOI-
pid: P4244
tag: ['动态规划 DP', '2008', '各省省选', '上海', '深度优先搜索 DFS', '区间 DP', '仙人掌']
---
# [SHOI2008] 仙人掌图 II
## 题目背景

题目这个II是和[SHOI2006的仙人掌图](https://www.luogu.org/problemnew/show/P4129)区分的，bzoj没有。
**但是实际上还是和bzoj1023是一个题目的**。
## 题目描述

如果某个无向连通图的任意一条边至多只出现在一条简单回路（simple cycle）里，我们就称这张图为仙人掌图（cactus）。所谓简单回路就是指在图上不重复经过任何一个顶点的回路。

![](https://cdn.luogu.com.cn/upload/pic/13241.png)

举例来说，上面的第一个例子是一张仙人图，而第二个不是——注意到它有三条简单回路：（4，3，2，1，6，5，4）、（7，8，9，10，2，3，7）以及（4，3，7，8，9，10，2，1，6，5，4），而（2，3）同时出现在前两个的简单回路里。另外，第三张图也不是仙人图，因为它并不是连通图。显然，仙人图上的每条边，或者是这张仙人图的桥（bridge），或者在且仅在一个简单回路里，两者必居其一。定义在图上两点之间的距离为这两点之间最短路径的距离。定义一个图的直径为这张图相距最远的两个点的距离。**现在我们假定仙人图的每条边的权值都是1，你的任务是求出给定的仙人图的直径**。
## 输入格式

输入的第一行包括两个整数n和m（1≤n≤50000以及0≤m≤10000）。其中n代表顶点个数，我们约定图中的顶点将从1到n编号。接下来一共有m行。代表m条路径。每行的开始有一个整数k（2≤k≤1000），代表在这条路径上的顶点个数。接下来是k个1到n之间的整数，分别对应了一个顶点，相邻的顶点表示存在一条连接这两个顶点的边。一条路径上可能通过一个顶点好几次，比如对于第一个样例，第一条路径从3经过8，又从8返回到了3，但是我们保证所有的边都会出现在某条路径上，而且不会重复出现在两条路径上，或者在一条路径上出现两次。
## 输出格式

只需输出一个数，这个数表示仙人图的直径长度。
## 样例

### 样例输入 #1
```
15 3
9 1 2 3 4 5 6 7 8 3
7 2 9 10 11 12 13 10
5 2 14 9 15 10
```
### 样例输出 #1
```
8
```
### 样例输入 #2
```
10 1
10 1 2 3 4 5 6 7 8 9 10
```
### 样例输出 #2
```
9
```
## 提示


对第一个样例的说明：6号点和12号点的最短路径长度为8，所以这张图的直径为8。

【注意】使用Pascal语言的选手请注意：你的程序在处理大数据的时候可能会出现栈溢出。
如果需要调整栈空间的大小，可以在程序的开头填加一句：{\$M 5000000}，其中5000000即指代栈空间的大小，请根据自己的程序选择适当的数值。


---

---
title: "[IOI 2000] 邮局 加强版"
layout: "post"
diff: 省选/NOI-
pid: P4767
tag: ['数学', '2000', 'IOI', '枚举', '区间 DP', '四边形不等式']
---
# [IOI 2000] 邮局 加强版
## 题目描述

高速公路旁边有一些村庄。高速公路表示为整数轴，每个村庄的位置用单个整数坐标标识。没有两个在同样地方的村庄。两个位置之间的距离是其整数坐标差的绝对值。

邮局将建在一些，但不一定是所有的村庄中。为了建立邮局，应选择他们建造的位置，使每个村庄与其最近的邮局之间的距离总和最小。

你要编写一个程序，已知村庄的位置和邮局的数量，计算每个村庄和最近的邮局之间所有距离的最小可能的总和。
## 输入格式

第一行包含两个整数：第一个是村庄 $V$ 的数量，第二个是邮局的数量 $P$。

第二行包含 $V$ 个整数。这些整数是村庄的位置。
## 输出格式

第一行包含一个整数 $S$，它是每个村庄与其最近的邮局之间的所有距离的总和。
## 样例

### 样例输入 #1
```
10 5 
1 2 3 6 7 9 11 22 44 50
```
### 样例输出 #1
```
9
```
## 提示

对于 $40\%$ 的数据，$V \leq 300$。

对于 $100\%$ 的数据，$1 \leq P \leq 300$，$P \leq V  \leq 3000$，$1 \leq $ 村庄位置 $\leq 10000$。


---

---
title: "「Wdsr-2」环"
layout: "post"
diff: 省选/NOI-
pid: P6735
tag: ['动态规划 DP', '2020', '区间 DP', '组合数学']
---
# 「Wdsr-2」环
## 题目描述

Kagamine Rin 有一个圆环，上面均匀分布着 $n$ 个点，这些点之间连接着 $m$ 条线段。

突然有一天，这些线段全都不见了。

Rin 想要找回这些线段，但是她不记得线段的分布。她只记得，这些线段中任意两条都不相交。

**注意：只在端点处相交不算相交；重合不算相交。** 下面的样例解释有助于理解本题中的定义。

Rin 有时还会记得一些额外的信息，她可能还会告诉你每个点上连接的线段数。

现在 Rin 想要知道，符合她的记忆的方案数有多少种。由于结果可能很大，你只需要输出答案对 $1000000007$ 取模的结果（模数是一个质数）。

## 输入格式

第一行输入三个整数 $n,m,type$。

如果 $type=1$，接下来一行输入 $n$ 个整数，第 $i$ 个整数 $a_i$ 表示第 $i$ 个点上连接的线段数。数据保证 $\sum_{i=1}^na_i=2m$。

## 输出格式

输出只有一个整数，表示合法的方案数对 $1000000007$ 取模的结果。

## 样例

### 样例输入 #1
```
4 2 0

```
### 样例输出 #1
```
20

```
### 样例输入 #2
```
4 2 1
1 1 1 1

```
### 样例输出 #2
```
2

```
## 提示

样例解释：

![](https://cdn.luogu.com.cn/upload/image_hosting/82pgikk2.png)

**Update：上图第二行第三个画错了，它的竖应该在右边**


如上图，有 $20$ 种方案满足样例 $1$ 的要求，而只有最后两种方案满足样例 $2$ 的要求。

------

**本题采用捆绑测试**，数据范围遵守如下约定：

subtask | $n\le$ | $m\le$ | $type$ | 分数
:-:|:-:|:-:|:-:|:-:
$0$ | $8$ | $8$ | $0$ | $10$
$1$ | $50$ | $50$ | $0$ | $10$
$2$ | $4000$ | $4000$ | $0$ | $15$
$3$ | $8$ | $8$ | $1$ | $10$
$4$ | $50$ | $50$ | $1$ | $15$
$5$ | $600$ | $600$ | $1$ | $20$
$6$ | $4000$ | $4000$ | $1$ | $20$

对于所有数据，有 $2\le n\le 4000,1\le m\le 4000,type\in \{0,1\}, a_i \ge 0$。若 $type=1$ 则保证 $\sum_{i=1}^na_i=2m$。


---

---
title: "[THUPC 2021] 小 E 爱消除"
layout: "post"
diff: 省选/NOI-
pid: P7605
tag: ['2021', 'O2优化', '区间 DP', 'THUPC']
---
# [THUPC 2021] 小 E 爱消除
## 题目描述

管道中塞着 $n$ 个彩色的球。这些球的直径相同。从一端到另一端它们的颜色分别为 $c_1,c_2,\ldots,c_n$。

小 E 有一个空的杯子。杯口的直径恰好比球的直径大一些，所以小 E 可以把球放入杯子中，但一次只能放入一个，并且球在杯子中只能竖直叠放。杯子中两个相邻的同色球会一起消失。

由于管道的特殊性，小 E 每次只能选择管道的一端，将最靠外的球取出，然后马上放进杯子里。

问当管道中的球全部取出后，杯子里最少会剩下几个球，以及在此前提下至少需要多大的杯子。
## 输入格式

第一行一个正整数 $n$。

第二行 $n$ 个正整数，第 $i$ 个表示 $c_i$。
## 输出格式

输出一行，包含两个非负整数。第一个数表示杯子里剩下球数的最小值。第二个数表示在此前提下杯子需要至少能装下多少个球。
## 样例

### 样例输入 #1
```
12
3 5 1 4 9 3 3 5 1 4 9 3

```
### 样例输出 #1
```
0 5

```
## 提示

**【样例解释】**

一种最优的方案如下：

先将两端的 $3$ 放入杯子中消去。

然后把左端的 $5,1,4,9$ 依次放入杯子，这时杯子中有 $4$ 个球。

再把右端的 $9,4$ 依次放入杯子，每放入一个球就会和杯子里的另一个球消去。在放入 $9$ 后消去前杯子中有 $5,1,4,9,9$，所以杯子需要能够容纳 $5$ 个球。

接着把左端的 $3,3$ 放入杯子，这时被杯子中有 $2$ 个球。

最后把右端的 $1,5$ 依次放入杯子。这时杯子是空的。

图片可见下发文件中的 `Sampledescription.pptx`。

**【数据范围】**

保证 $1 \le n \le 50$，$1 \le c_i \le n$。

**【题目来源】**

来自 2021 清华大学学生程序设计竞赛暨高校邀请赛（THUPC2021）。

题解等资源可在 [https://github.com/yylidiw/thupc_1/tree/master](https://github.com/yylidiw/thupc_1/tree/master) 查看。


---

---
title: "[USACO23FEB] Piling Papers G"
layout: "post"
diff: 省选/NOI-
pid: P9129
tag: ['USACO', '2023', '数位 DP', '区间 DP']
---
# [USACO23FEB] Piling Papers G
## 题目描述

Farmer John wrote down $N (1 \le N \le 300)$ digits on pieces of paper. For each $i \in [1,N]$, the ith piece of paper contains digit $a_i (1 \le a_i \le 9)$.

The cows have two favorite integers $A$ and $B(1 \le A \le B<10^{18})$, and would like you to answer $Q (1 \le Q \le 5⋅10^4)$ queries. For the $i$-th query, the cows will move left to right across papers $l_i \cdots r_i (1 \le l_i \le r_i \le N)$, maintaining an initially empty pile of papers. For each paper, they will either add it to the top of the pile, to the bottom of the pile, or neither. In the end, they will read the papers in the pile from top to bottom, forming an integer. Over all $3 ^ {r_i−l_i+1}$ ways for the cows to make choices during this process, count the number of ways that result in the cows reading an integer in $[A,B]$ inclusive, and output this number modulo $10^9+7$. 
## 输入格式

The first line contains three space-separated integers $N, A$, and $B$.

The second line contains $N$ space-separated digits $a_1,a_2, \cdots ,a_N$.

The third line contains an integer $Q$, the number of queries.

The next $Q$ lines each contain two space-separated integers $l_i$ and $r_i$. 
## 输出格式

For each query, a single line containing the answer. 
## 样例

### 样例输入 #1
```
5 13 327
1 2 3 4 5
3
1 2
1 3
2 5
```
### 样例输出 #1
```
2
18
34
```
## 提示

### Explanation for Sample 1

For the first query, there are nine ways Bessie can stack papers when reading the interval $[1,2]$:

 - Bessie can ignore $1$ then ignore $2$, getting $0$.
 - Bessie can ignore $1$ then add $2$ to the top of the stack, getting $2$.
 - Bessie can ignore $1$ then add $2$ to the bottom of the stack, getting $2$.
 - Bessie can add $1$ to the top of the stack then ignore $2$, getting $1$.
 - Bessie can add $1$ to the top of the stack then add $2$ to the top of the stack, getting $21$.
 - Bessie can add $1$ to the top of the stack then add $2$ to the bottom of the stack, getting $12$.
 - Bessie can add $1$ to the bottom of the stack then ignore $2$, getting $1$.
 - Bessie can add $1$ to the bottom of the stack then add $2$ to the top of the stack, getting $21$.
 - Bessie can add $1$ to the bottom of the stack then add $2$ to the bottom of the stack, getting $12$. 

Only the $2$ ways that give $21$ yield a number between $13$ and $327$, so the answer is $2$.

### SCORING

 - Inputs $2-3$: $B<100$
 - Inputs $4-5$: $A=B$
 - Inputs $6-13$: No additional constraints.
## 题目翻译

给定长度为 $n(1\leq n\leq 300)$ 的整数序列 $a(1\leq a_i\leq 9)$，和整数区间 $[A,B](1\leq A\leq B\leq 10^{18})$，有 $q$ 次询问，每次询问给出 $l,r$。每次询问开始，你有一个空串 $x$，你可以正序对 $a_{l\sim r}$ 进行操作，操作有三种：$x\rightarrow\overline{x+a_i}$，$x\rightarrow\overline{a_i+x}$，或者什么也不做，求 $\overline{x}$ 的取值在 $[A,B]$ 的不同的操作方案数，对 $10^9+7$ 取模。


---

---
title: "「KDOI-06-S」合并序列"
layout: "post"
diff: 省选/NOI-
pid: P9746
tag: ['动态规划 DP', '2023', '洛谷原创', 'Special Judge', 'O2优化', '区间 DP', '位运算', '洛谷月赛']
---
# 「KDOI-06-S」合并序列
## 题目描述

给定一个长度为 $n$ 的序列 $a_1,a_2,\ldots a_n$。

你可以对这个序列进行若干（可能为 $0$）次操作。在每次操作中，你将会：

* 选择三个正整数 $i<j<k$，满足 $a_i\oplus a_j\oplus a_k=0$ 且 $k$ 的值不超过此时序列的长度。记 $s=a_i\oplus a_{i+1}\oplus \cdots\oplus a_k$。
* 然后，删除 $a_i\sim a_k$，并在原来这 $k-i+1$ 个数所在的位置插入 $s$。注意，此时序列 $a$ 的长度将会减少 $(k-i)$。

请你判断是否能够使得序列 $a$ 仅剩一个数，也就是说，在所有操作结束后 $a$ 的长度为 $1$。若可以，你还需要给出一种操作方案。
## 输入格式

从标准输入读入数据。

**本题含有多组测试数据。**

输入的第一行包含一个正整数 $T$，表示数据组数。

对于每组测试数据，第一行一个正整数 $n$，表示初始序列长度。

第二行 $n$ 个整数 $a_1,a_2,\ldots,a_n$，表示初始序列中每个元素的值。
## 输出格式

对于每组测试数据：

+ 若存在一种方案使得序列 $a$ 仅剩一个数，请在输出的第一行输出 `Huoyu`。
  + 接下来，在第二行你应该输出一个非负整数 $t$，表示你的操作次数。你需要保证 $0\le t\le n$。
  + 接下来 $t$ 行，每行输出三个正整数 $i,j,k$，表示你在这次操作中选择的三个数的值。你需要保证 $i<j<k$ 且 $k$ 的值不超过此时序列的长度。
+ 否则，请输出一行一个字符串 `Shuiniao`。
## 样例

### 样例输入 #1
```
2
5
3 3 1 4 5
9
3 4 6 5 4 5 1 2 4
```
### 样例输出 #1
```
Huoyu
2
3 4 5
1 2 3
Huoyu
3
1 3 4
2 3 4
1 2 4
```
## 提示

**【样例解释 #1】**

对于第一组测试数据：

* 第一次操作中，$a_3\oplus a_4\oplus a_5=1\oplus4\oplus5=0$，操作后的序列为 $[3,3,0]$；
* 第二次操作中，$a_1\oplus a_2\oplus a_3=3\oplus3\oplus0=0$，操作后的序列为 $[0]$。

于是，序列 $a$ 在两次操作后仅剩一个数。

对于第二组测试数据：

* 第一次操作，$a_1\oplus a_3\oplus a_4=3\oplus6\oplus5=0$，$s=4$，操作后的序列为 $[4,4,5,1,2,4]$。
* 第二次操作，$a_2\oplus a_3\oplus a_4=4\oplus5\oplus1=0$，操作后的序列为 $[4,0,2,4]$。
* 第三次操作，$a_1\oplus a_2\oplus a_4=4\oplus0\oplus4=0$，$s=2$，操作后的序列为 $[2]$。

于是，序列 $a$ 在三次操作后仅剩一个数。

**【样例 #2】**

见选手目录下的 `merge/merge2.in` 与 `merge/merge2.ans`。

这个样例满足测试点 $6\sim7$ 的条件限制。

**【样例 #3】**

见选手目录下的 `merge/merge3.in` 与 `merge/merge3.ans`。

这个样例满足测试点 $12\sim13$ 的条件限制。

**【数据范围】**

对于所有数据保证：$1\leq T\leq20$，$1\leq n\leq500$，$0\leq a_i<512$。

| 测试点编号 | $n$ | $\sum n\leq$ | $a_i<$ |
|:--:|:--:|:--:|:--:|
| $1$ | $=1$ | $20$ | $512$ |
| $2$ | $=2$ | $40$ | $512$ |
| $3$ | $=3$ | $60$ | $512$ |
| $4$ | $=4$ | $80$ | $512$ |
| $5$ | $=5$ | $100$ | $512$ |
| $6\sim7$ | $\leq40$ | $800$ | $512$ |
| $8\sim9$ | $\leq70$ | $1~400$ | $512$ |
| $10\sim11$ | $\leq130$ | $2~600$ | $512$ |
| $12\sim13$ | $\leq300$ | $6~000$ | $128$ |
| $14\sim15$ | $\leq500$ | $3~000$ | $64$ |
| $16\sim17$ | $\leq500$ | $3~000$ | $128$ |
| $18\sim20$ | $\leq500$ | $10~000$ | $512$ |

**【提示】**

$\oplus$ 表示按位异或运算。

**请对程序的常数以及效率给予充分的信任。**


---

