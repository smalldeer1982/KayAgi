---
title: "漫长的小纸带"
layout: "post"
diff: 提高+/省选-
pid: P11311
tag: ['动态规划 DP', '洛谷原创', '排序', '洛谷月赛']
---
# 漫长的小纸带
## 题目背景

[The English statement for T4](https://www.luogu.com.cn/problem/U508235)

You can also see the pdf at the bottom of the chinese problem statement.

小 $ \zeta $ 是一个喜欢打暴力的 OIer。在每次模拟赛中，他秉持着“10 分钟想不出来正解那就把暴力糊上去”的理念，每次都稳定地拿到很高的分数；平时训练时，他会关注题目的部分分，针对部分分任务进行求解，有时在部分分求解上使用的时间比这个题正解的思考都长。
## 题目描述

小 $ \zeta $ 经过了几年的暴力训练，暴力水平更是炉火纯青。在 S-PSC 2077 的比赛中，他惊喜的发现第二题《漫长的小纸带》是一道很困难的题目，正适合他这种暴力选手发挥。

这道题目是多测题目，在某个测试点内有 $ n $ 组数据，第 $ i $ 组数据的规模为 $ a_i $。他写出了一个暴力程序，对于一段连续的数据，程序解决这段数据需要消耗的时间为这段数据中出现的不同的 $ a_i $ 的种类数平方。形式化地讲，对于一个从第 $ l $ 组到第 $ r $ 组的连续的数据段，记 $ S=\{a_i|l \le i \le r\} $，程序需要消耗 $ |S|^2 $ 的时间来一起解决它们。

现在，他给你 $ n $ 和 $ n $ 组数据的规模，请找到一种将这些数据划分成若干个数据段的方案，使得程序消耗的总时间最短。
## 输入格式

第一行一个整数 $ n $。

接下来一行 $ n $ 个整数 $ a_i $，代表每一组测试数据的规模。
## 输出格式

输出一个数代表总时间消耗。
## 样例

### 样例输入 #1
```
5
1 2 3 4 5
```
### 样例输出 #1
```
5
```
### 样例输入 #2
```
6
1 2 2 1 2 3
```
### 样例输出 #2
```
5
```
### 样例输入 #3
```
9
1 2 1 4 1 2 1 1 2
```
### 样例输出 #3
```
8
```
### 样例输入 #4
```
21
1 2 1 2 1 2 1 2 1 2 3 4 5 6 7 1 2 1 2 1 2
```
### 样例输出 #4
```
13
```
## 提示

**【样例 3 解释】**

分段方式为：

* 第一段 $ \{1\} $，消耗为 $ 1 $。
* 第二段 $ \{2\} $，消耗为 $ 1 $。
* 第三段 $ \{1\} $，消耗为 $ 1 $。
* 第四段 $ \{4\} $，消耗为 $ 1 $。
* 第五段 $ \{1,2,1,1,2\} $，消耗为 $ 4 $。

故程序总共消耗的时间为 $ 8 $。

**【数据范围】**

对于 $ 100\% $ 的数据，$ 1 \le n \le 2 \times 10^5 $，$ 1 \le a_i \le 10^9 $。

**提示：本题开启捆绑测试。**

| 子任务编号 | $ n \le $ | 特殊性质 | 分数 |
|:-:|:-:|:-:|:-:|
| $ 1 $ | $ 10 $ | - | $ 8 $ |
| $ 2 $ | $ 300 $ | - | $ 8 $ |
| $ 3 $ | $ 2000 $ | - | $ 16 $ |
| $ 4 $ | - | A | $ 16 $ |
| $ 5 $ | - | B | $ 24 $ |
| $ 6 $ | - | - | $ 28 $ |

特殊性质 A：所有的 $ a_i $ 在 $ [1,10^9] $ 内等概率随机生成，且本子任务只有 $ 1 $ 个测试点。

特殊性质 B：$ 1 \le a_i \le 1000 $。



---

---
title: "[GCJ 2022 #3] Mascot Maze"
layout: "post"
diff: 提高+/省选-
pid: P12999
tag: ['贪心', '2022', 'Special Judge', '拓扑排序', 'Google Code Jam']
---
# [GCJ 2022 #3] Mascot Maze
## 题目描述

The Google Coding Competitions team is setting up a new theme park. As in any good theme park, we want to have actors dressed up as mascots to interact with visitors. Because we are in a rush to open, we decided to use the letters from CODE JAM, KICK START, and HASH CODE as mascots, for a total of 13 different mascots (the letters `ACDEHIJKMORST`).

The park's only attraction is a maze that has a set of $\mathbf{N}$ rooms numbered from 1 to $\mathbf{N}$. Each room has a left exit and a right exit. Each exit takes the visitor to another room. Exits cannot be used in reverse; for example, if room 2 has an exit to room 3, you cannot go back from room 3 to room 2 unless room 3 also happens to have an exit to room 2.

![](https://cdn.luogu.com.cn/upload/image_hosting/8fuhdtgj.png)

We want to place exactly one of our 13 mascots in each room. Each letter may be present in zero, one, or more rooms of the maze. To increase variety, we want to place mascots so that any three (not necessarily distinct) rooms that a visitor can visit consecutively have three different mascots.

Can you help us choose a mascot for each room such that this goal is met, or let us know that it cannot be done?

## 输入格式

The first line of the input gives the number of test cases, $\mathbf{T}$. $\mathbf{T}$ test cases follow. Each test case consists of 3 lines. The first line contains a single integer $\mathbf{N}$, representing the number of rooms in the maze. The second line contains $\mathbf{N}$ integers $\mathbf{L}_1, \mathbf{L}_2, \ldots, \mathbf{L}_\mathbf{N}$, representing that the left exit from room $i$ leads to room $\mathbf{L}_i$. The third and last line contains $\mathbf{N}$ integers $\mathbf{R}_1, \mathbf{R}_2, \ldots, \mathbf{R}_\mathbf{N}$, representing that the right exit from room $i$ leads to room $\mathbf{R}_i$.

## 输出格式

For each test case, output one line containing `Case #x: y`, where $x$ is the test case number (starting from 1) and $y$ is `IMPOSSIBLE` if there is no way to assign mascots while obeying the rules explained above. Otherwise, $y$ is an $\mathbf{N}$ character long string. The $i$-th character of $y$ should be an uppercase letter from the set `ACDEHIJKMORST`, representing that you wish to assign that mascot to the $i$-th room.
## 样例

### 样例输入 #1
```
4
3
2 1 1
3 3 2
6
3 1 4 1 2 3
5 3 5 2 4 5
20
2 3 4 5 6 7 8 9 10 11 12 13 14 15 16 17 18 19 1 1
3 4 5 6 7 8 9 10 11 12 13 14 15 16 17 18 19 20 20 2
19
2 3 4 5 6 7 8 9 10 11 12 13 14 15 16 17 18 1 1
3 4 5 6 7 8 9 10 11 12 13 14 15 16 17 18 19 19 3
```
### 样例输出 #1
```
Case #1: IMPOSSIBLE
Case #2: TSHIRT
Case #3: HCJKSHCJKSHCJKSHCJKS
Case #4: CODEJAMROCKSTHEMOST
```
## 提示

**Sample Explanation**

Sample Case #1 is the image in the problem statement. It is possible to visit rooms 1, 2, and 1 consecutively (which visits room 1 twice), so the case is impossible.

Sample Case #2 has the following layout (blue arrows represent the left exits and red arrows represent the right exits):

![](https://cdn.luogu.com.cn/upload/image_hosting/ykiviiry.png)

One of many valid answers is to assign mascots as indicated. Notice that although we do not need to assign two $\tau$ mascots in this case, we have done so in a way that does not break the rules.

Sample Cases #3 and #4 are possible, but require the use of multiple copies of some mascots.

**Limits**

- $1 \leq \mathbf{T} \leq 100$.
- $\mathbf{L}_i \neq i$, for all $i$. $\mathbf{R}_i \neq i$, for all $i$. $1 \leq \mathbf{L}_i < \mathbf{R}_i \leq \mathbf{N}$, for all $i$.

**Test Set 1 (12 Pts, Visible Verdict)**

- Time limit: 20 seconds.
- $3 \leq \mathbf{N} \leq 100$.

**Test Set 2 (13 Pts, Hidden Verdict)**

- Time limit: 45 seconds.
- $3 \leq \mathbf{N} \leq 10^5$.


---

---
title: "[GCJ 2019 #2] Contransmutation"
layout: "post"
diff: 提高+/省选-
pid: P13118
tag: ['动态规划 DP', '图论', '2019', '拓扑排序', '强连通分量', 'Google Code Jam']
---
# [GCJ 2019 #2] Contransmutation
## 题目描述

Last year, we asked you to help us convert expensive metals into lead. (You do not need to know anything about the previous problem to solve this one.) But your country's leader is still greedy for more lead!

There are $\mathbf{M}$ metals known in the world; lead is metal number 1 on your periodic table. Your country's leader has asked you to use the metals in the treasury to make as much lead as possible.

For each metal (including lead), you know exactly one formula that lets you destroy one gram of that metal and create one gram each of two metals. (It is best not to think too much about the principle of mass conservation!) Note that it is possible that the formula for the i-th metal might produce the i-th metal as one of the products. The formulas do not work with partial grams. However, you can use each formula as often as you would like (or not at all), as long as you have a gram of the required ingredient.

If you make optimal choices, what is the largest number of grams of lead you can end up with, or is it unbounded? If it is not unbounded: since the output can be a really big number, we only ask you to output the remainder of dividing the result by the prime $10^9+7$ (that is, $1000000007$).
## 输入格式

The first line of the input gives the number of test cases, $\mathbf{T}$. $\mathbf{T}$ test cases follow. Each begins with one line with an integer $\mathbf{M}$: the number of metals known in the world. Then there are $\mathbf{M}$ more lines with two integers $\mathbf{R_{i1}}$ and $\mathbf{R_{i2}}$ each; the i-th of these lines, counting starting from 1, indicates that you can destroy one gram of metal i to create one gram of metal $\mathbf{R_{i1}}$ and one gram of metal $\mathbf{R_{i2}}$. Finally, there is one line with $\mathbf{M}$ integers $\mathbf{G_1}$, $\mathbf{G_2}$, ..., $\mathbf{G_M}$; $\mathbf{G_i}$ is the number of grams of metal i in the treasury. Lead is metal 1.

## 输出格式

For each test case, output one line containing `Case #x: y` where $x$ is the test case number (starting from 1). If there is no bound on the maximum amount of lead that can be produced, $y$ must be UNBOUNDED. Otherwise, $y$ must be the largest amount of lead, in grams, that you can end up with, modulo the prime $10^9+7$ (that is, $1000000007$).
## 样例

### 样例输入 #1
```
3
2
1 2
1 2
1 0
2
1 2
1 2
0 0
4
2 4
3 4
2 4
2 3
10 10 10 10
```
### 样例输出 #1
```
Case #1: UNBOUNDED
Case #2: 0
Case #3: 10
```
## 提示

**Sample Explanation**

In Sample Case #1, you have one formula that turns 1 gram of lead into 1 gram of lead and 1 gram of the second metal, and another formula that turns 1 gram of the second metal into 1 gram of lead and 1 gram of the second metal. You can alternate between these formulas to produce as much of both metals as you want.

Sample Case #2 has the same formulas as Sample Case #1, but you have no metals to start with!

In Sample Case #3, none of the formulas help you produce more lead, so you cannot end up with more lead than you started with.

**Limits**

- $1 \leq \mathbf{R_{i1}} < \mathbf{R_{i2}} \leq \mathbf{M}$, for all $i$.

**Test set 1 (7 Pts, Visible)**

- $1 \leq \mathbf{T} \leq 100$.
- $2 \leq \mathbf{M} \leq 10$.
- $0 \leq \mathbf{G_i} \leq 10$, for all $i$.

**Test set 2 (16 Pts, Hidden)**

- $1 \leq \mathbf{T} \leq 100$.
- $2 \leq \mathbf{M} \leq 100$.
- $0 \leq \mathbf{G_i} \leq 10^9$, for all $i$.

**Test set 3 (6 Pts, Hidden)**

- $1 \leq \mathbf{T} \leq 5$.
- $2 \leq \mathbf{M} \leq 10^5$.
- $0 \leq \mathbf{G_i} \leq 10^9$, for all $i$.


---

---
title: "[GCJ 2015 #1A] Logging"
layout: "post"
diff: 提高+/省选-
pid: P13217
tag: ['计算几何', '2015', '凸包', '极角排序', 'Google Code Jam']
---
# [GCJ 2015 #1A] Logging
## 题目描述

A certain forest consists of $N$ trees, each of which is inhabited by a squirrel.

The **boundary** of the forest is the convex polygon of smallest area which contains every tree, as if a giant rubber band had been stretched around the outside of the forest.

Formally, every tree is a single point in two-dimensional space with unique coordinates $(X_i, Y_i)$, and the boundary is the convex hull of those points.

Some trees are **on the boundary** of the forest, which means they are on an edge or a corner of the polygon. The squirrels wonder how close their trees are to being on the boundary of the forest.

One at a time, each squirrel climbs down from its tree, examines the forest, and determines the minimum number of trees that would need to be cut down for its own tree to be on the boundary. It then writes that number down on a log.

Determine the list of numbers written on the log.
## 输入格式

The first line of the input gives the number of test cases, $T$. $T$ test cases follow; each consists of a single line with an integer $N$, the number of trees, followed by $N$ lines with two space-separated integers $X_i$ and $Y_i$, the coordinates of each tree. No two trees will have the same coordinates.

## 输出格式

For each test case, output one line containing "Case #$x$:", followed by $N$ lines with one integer each, where line $i$ contains the number of trees that the squirrel living in tree $i$ would need to cut down.
## 样例

### 样例输入 #1
```
2
5
0 0
10 0
10 10
0 10
5 5
9
0 0
5 0
10 0
0 5
5 5
10 5
0 10
5 10
10 10
```
### 样例输出 #1
```
Case #1:
0
0
0
0
1
Case #2:
0
0
0
0
3
0
0
0
0
```
## 提示

**Sample Explanation**

In the first sample case, there are four trees forming a square, and a fifth tree inside the square. Since the first four trees are already on the boundary, the squirrels for those trees each write down $0$. Since one tree needs to be cut down for the fifth tree to be on the boundary, the fifth squirrel writes down $1$.

**Limits**

- $-10^6 \leq X_i, Y_i \leq 10^6$.

**Small dataset**

- Time limit: ~~240~~ 5 seconds.
- $1 \leq T \leq 100$.
- $1 \leq N \leq 15$.

**Large dataset**

- Time limit: ~~480~~ 20 seconds.
- $1 \leq T \leq 14$.
- $1 \leq N \leq 3000$.


---

---
title: "可怜的狗狗"
layout: "post"
diff: 提高+/省选-
pid: P1533
tag: ['线段树', '平衡树', '洛谷原创', '排序']
---
# 可怜的狗狗
## 题目描述

小卡家有  $n$ 只狗，由于品种、年龄不同，每一只狗都有一个不同的漂亮值。漂亮值与漂亮的程度成反比（漂亮值越低越漂亮），吃饭时，狗狗们会按顺序站成一排等着主人给食物。

可是嘉嘉真的很懒，他才不肯喂这么多狗呢，这多浪费时间啊，于是他每次就只给第  $i$ 只到第  $j$ 只狗中第  $k$ 漂亮的狗狗喂食（好狠心的人啊）。而且为了保证某一只狗狗不会被喂太多次，他喂的每个区间  $[i,j]$ 不互相包含。
## 输入格式

第一行输入两个数  $n,m$， $m$ 表示嘉嘉喂食的次数

第二行  $n$ 个整数，表示第  $i$ 只狗的漂亮值为  $a_i$。

接下来  $m$ 行，每行  $3$ 个整数  $i,j,k$，表示询问这次喂食喂第  $i$ 到第  $j$ 只狗中第  $k$ 漂亮的狗的漂亮值。
## 输出格式

$m$ 行，每行一个整数，表示每一次喂的那只狗漂亮值为多少。
## 样例

### 样例输入 #1
```
7 2
1 5 2 6 3 7 4
1 5 3
2 7 1

```
### 样例输出 #1
```
3
2

```
## 提示

$1\le n \le 3\times 10^5 ,1\le m \le5\times10^4,0\le a_i<2^{31}$，且 $a_i$ 互不相同。


---

---
title: "[USACO09FEB] Fair Shuttle G"
layout: "post"
diff: 提高+/省选-
pid: P1607
tag: ['贪心', '2009', '线段树', 'USACO', '排序']
---
# [USACO09FEB] Fair Shuttle G
## 题目描述

Although Farmer John has no problems walking around the fair to collect prizes or see the shows, his cows are not in such good shape; a full day of walking around the fair leaves them exhausted. To help them enjoy the fair, FJ has arranged for a shuttle truck to take the cows from place to place in the fairgrounds.

FJ couldn't afford a really great shuttle, so the shuttle he rented traverses its route only once (!) and makes N (1 <= N <= 20,000) stops (conveniently numbered 1..N) along its path. A total of K (1 <= K <= 50,000) groups of cows conveniently numbered 1..K wish to use the shuttle, each of the M\_i (1 <= M\_i <= N) cows in group i wanting to ride from one stop S\_i (1 <= S\_i < E\_i) to another stop E\_i (S\_i < E\_i <= N) farther along the route.

The shuttle might not be able to pick up an entire group of cows (since it has limited capacity) but can pick up partial groups as appropriate.

Given the capacity C (1 <= C <= 100) of the shuttle truck and the descriptions of the groups of cows that want to visit various sites at the fair, determine the maximum number of cows that can ride the shuttle during the fair.

## 输入格式

第一行：包括三个整数：$K,N$ 和 $C$，彼此用空格隔开。

第二行到 $K+1$ 行：在第 $i+1$ 行，将会告诉你第 $i$ 组奶牛的信息：$S_i,E_i$ 和 $M_i$，彼此用空格隔开。

## 输出格式

第一行：可以坐班车的奶牛的最大头数。

## 样例

### 样例输入 #1
```
8 15 3
1 5 2
13 14 1
5 8 3
8 14 2
14 15 1
9 12 1
12 15 2
4 6 1

```
### 样例输出 #1
```
10

```
## 提示

【样例说明】

班车可以把 $2$ 头奶牛从 $1$ 送到 $5$，$3$ 头奶牛从 $5$ 送到 $8$，$2$ 头奶牛从 $8$ 送到 $14$，$1$ 头奶牛从 $9$ 送到 $12$，$1$ 头奶牛从 $13$ 送到 $14$，$1$ 头奶牛从 $14$ 送到 $15$。

## 题目翻译


逛逛集市，兑兑奖品，看看节目对农夫约翰来说不算什么，可是他的奶牛们非常缺乏锻炼——如果要逛完一整天的集市，他们一定会筋疲力尽的。所以为了让奶牛们也能愉快地逛集市，约翰准备让奶牛们在集市上以车代步。但是，约翰木有钱，他租来的班车只能在集市上沿直线跑一次，而且只能停靠 $N(1 \leq N\leq 20000)$ 个地点（所有地点都以 $1$ 到 $N$ 之间的一个数字来表示）。现在奶牛们分成 $K(1\leq K\leq 50000)$ 个小组，第i 组有 $M_i(1\leq M_i\leq N)$ 头奶牛，他们希望从 $S_i$ 跑到 $E_i(1\leq S_i< E_i\leq N)$。

由于班车容量有限，可能载不下所有想乘车的奶牛们，此时也允许小组里的一部分奶牛分开乘坐班车。约翰经过调查得知班车的容量是 $C(1\leq C\leq 100)$，请你帮助约翰计划一个尽可能满足更多奶牛愿望的方案。



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
title: "[USACO10MAR] Barn Allocation G"
layout: "post"
diff: 提高+/省选-
pid: P1937
tag: ['贪心', '2010', '线段树', 'USACO', '排序']
---
# [USACO10MAR] Barn Allocation G
## 题目描述

Farmer John recently opened up a new barn and is now accepting stall allocation requests from the cows since some of the stalls have a better view of the pastures.

The barn comprises N (1 <= N <= 100,000) stalls conveniently numbered 1..N; stall i has capacity C\_i cows (1 <= C\_i <= 100,000). Cow i may request a contiguous interval of stalls (A\_i, B\_i) in which to roam (1 <= A\_i <= N; A\_i <= B\_i <= N), i.e., the cow would like to wander among all the stalls in the range A\_i..B\_i (and the stalls must always have the capacity for her to wander).

Given M (1 <= M <= 100,000) stall requests, determine the maximum number of them that can be satisfied without exceeding stall

capacities.

 
农夫约翰最近开了一个新的牲口棚屋，并且现在接受来自奶牛的分配畜栏请求因为其中的一些畜栏有更好风景。

畜栏包括N个畜栏(1 ≤ N ≤ 100,000)，方便起见，我们把它们编号为1..N，畜栏i能容纳Ci只牛(1 ≤ Ci ≤ 100,000)，第i只牛需要连续编号畜栏（从Ai到Bi）来漫步其中，

(1 ≤ Ai ≤ N; Ai ≤ Bi ≤ N)，换言之，这只牛想要在编号范围为Ai..Bi的畜栏漫步（所有它想要畜栏必须实施为它空出位置来供它散步）

给出M个畜栏分配请求（1 ≤ M ≤ 100,000），回答最多能满足多少只牛的要求（不增加另外畜栏）

考虑以下例子：

```cpp
畜栏号:    1   2   3   4   5
           +---+---+---+---+---+
容纳空间:  | 1 | 3 | 2 | 1 | 3 |  
           +---+---+---+---+---+
Cow 1       XXXXXXXXXXX             (1, 3)
Cow 2           XXXXXXXXXXXXXXX     (2, 5)
Cow 3           XXXXXXX             (2, 3)
Cow 4                   XXXXXXX     (4, 5)
```
约翰显然不能满足所有的牛，因为畜栏3，4请求太多了

经过试验，我们发现，我们能满足牛1，3，4需要，所以这组数据答案为3

## 输入格式

第一行包括两个以空格隔开的正整数：N,M

第二行到第N+1行：第i+1行包括一个整数：Ci

第N+2到第N+M+1行：第i+N+1 包括两个整数Ai、Bi

## 输出格式

仅一行：能满足的最大需要

## 样例

### 样例输入 #1
```
5 4
1
3
2
1
3
1 3
2 5
2 3
4 5
```
### 样例输出 #1
```
3
```
## 提示

Source: USACO 2010 March Gold

Translator: @chrome01



---

---
title: "[NOIP 2013 提高组] 火柴排队"
layout: "post"
diff: 提高+/省选-
pid: P1966
tag: ['2013', '树状数组', 'NOIP 提高组', '排序']
---
# [NOIP 2013 提高组] 火柴排队
## 题目背景

NOIP2013 提高组 D1T2
## 题目描述

涵涵有两盒火柴，每盒装有 $n$ 根火柴，每根火柴都有一个高度。 现在将每盒中的火柴各自排成一列， 同一列火柴的高度互不相同， 两列火柴之间的距离定义为：$ \sum (a_i-b_i)^2$。

其中 $a_i$ 表示第一列火柴中第 $i$ 个火柴的高度，$b_i$ 表示第二列火柴中第  $i$ 个火柴的高度。

每列火柴中相邻两根火柴的位置都可以交换，请你通过交换使得两列火柴之间的距离最小。请问得到这个最小的距离，最少需要交换多少次？如果这个数字太大，请输出这个最小交换次数对 $10^8-3$ 取模的结果。

## 输入格式

共三行，第一行包含一个整数 $n$，表示每盒中火柴的数目。

第二行有 $n$ 个整数，每两个整数之间用一个空格隔开，表示第一列火柴的高度。

第三行有 $n$ 个整数，每两个整数之间用一个空格隔开，表示第二列火柴的高度。

## 输出格式

一个整数，表示最少交换次数对 $10^8-3$ 取模的结果。

## 样例

### 样例输入 #1
```
4
2 3 1 4
3 2 1 4

```
### 样例输出 #1
```
1
```
### 样例输入 #2
```
4
1 3 4 2
1 7 2 4
```
### 样例输出 #2
```
2
```
## 提示

**输入输出样例说明一**

最小距离是 $ 0$，最少需要交换 $1$ 次，比如：交换第 $1 $ 列的前 $ 2$ 根火柴或者交换第 $2$ 列的前 $2 $ 根火柴。

**输入输出样例说明二**

最小距离是 $10$，最少需要交换 $2$ 次，比如：交换第 $1$ 列的中间 $2$ 根火柴的位置，再交换第 $2$ 列中后 $2$ 根火柴的位置。

**数据范围**

对于 $10\%$ 的数据， $1 \leq n \leq 10$；

对于 $30\%$ 的数据，$1 \leq n \leq 100$；

对于 $60\%$ 的数据，$1 \leq n \leq 10^3$；

对于 $100\%$ 的数据，$1 \leq n \leq 10^5$，$0 \leq$ 火柴高度 $< 2^{31}$。


---

---
title: "[SDOI2009] Elaxia的路线"
layout: "post"
diff: 提高+/省选-
pid: P2149
tag: ['2009', '各省省选', '山东', '拓扑排序', '最短路']
---
# [SDOI2009] Elaxia的路线
## 题目描述

最近，Elaxia 和 w** 的关系特别好，他们很想整天在一起，但是大学的学习太紧张了，他们必须合理地安排两个人在一起的时间。

Elaxia 和 w** 每天都要奔波于宿舍和实验室之间，他们 希望在节约时间的前提下，一起走的时间尽可能的长。

现在已知的是 Elaxia 和 w** 所在的宿舍和实验室的编号以及学校的地图：  
地图上有 $n$ 个路口，$m$ 条路，经过每条路都需要一定的时间。 具体地说，就是要求无向图中，两对点间最短路的最长公共路径。

## 输入格式

第一行两个正整数 $n,m$，表示点数和边数。
  
第二行四个正整数 $x_1,y_1,x_2,y_2$，分别表示 Elaxia 的宿舍和实验室及 w** 的宿舍和实验室的标号。

接下来 $m$ 行，每行三个整数 $u,v,w$，表示 $u,v$之间有一条边，需要 $w$ 的时间经过。
## 输出格式

一行一个整数表示答案。（即最长公共路径的长度）

## 样例

### 样例输入 #1
```
9 10
1 6 7 8
1 2 1
2 5 2
2 3 3
3 4 2
3 9 5
4 5 3
4 6 4
4 7 2
5 8 1
7 9 1
```
### 样例输出 #1
```
3
```
## 提示

【数据范围】    
对于 $30\%$ 的数据，$1\le n \le 100$；   
对于 $60\%$ 的数据，$1\le n \le 1000$；   
对于 $100\%$ 的数据，$1\le n \le 1500$，$1 \leq m \leq 3 \times 10^5$，$1\le w \le 10^4$，输入数据保证没有重边和自环。



---

---
title: "[HNOI2003] 多项式的加法和乘法"
layout: "post"
diff: 提高+/省选-
pid: P2281
tag: ['2003', '线性数据结构', '各省省选', '平衡树', '湖南', '排序']
---
# [HNOI2003] 多项式的加法和乘法
## 题目描述

今天的数学课上，老师讲了多项式的加法和乘法。然后布置了很多计算题，小明不想花太多时间来做数学作业，于是想编写一个程序来完成这个任务。

比如计算下面两个多项式的和与积：

$xy^2z+31wx^3y^3z^{50}+s^3$  
$v^2+s^3+3wx^3y^3$

假定所有变量都是单个大写字符，所有的系数和指数都是常数，且都是整数。

我们用 `X^3` 表示 $X$ 的三次方，在系数和不同的项之间用空格分隔，例如 `X Y^2` 中，$X$ 和 $Y$ 之间有空格。下面是两个多项式的例子，除此之外没有别的空格。

`X Y^2 Z + 31 W X^3 Y^3 Z^50 + S^3`  
`V^2 + S^3 + 3 W X^3 Y^3`

现在，按照上面的格式给定两个多项式，请你求出这两个多项式的和与积。
## 输入格式

输入包括两行，每一行是一个多项式。每个多项式不超过 $250$ 个字符。计算过程中保证任何中间结果系数和指数均不超过长整数范围。
## 输出格式

输出也是两行，第一行是两个多项式的和，第二行是两个多项式的积。输出中要求合并同类项。输出多项式的格式和输入的格式类似，但输出时请把所有空格都去掉，并保证每一项都是 ASCII 码排在前面的变量放在前面，即输出 `X^3Y^2` 而不是 `Y^2X^3`。另外，输出的项请按变量 `A` 的指数从小到大排列，变量 `A` 指数相同的，按变量 `B` 的指数从小到大排列，依此类推。并注意输出要符合我们平常书写的习惯。
## 样例

### 样例输入 #1
```
A + B
3 A + 4 A B^3 + C

```
### 样例输出 #1
```
C+B+4A+4AB^3

BC+AC+3AB+4AB^4+3A^2+4A^2B^3


```


---

---
title: "[SDOI2010] 所驼门王的宝藏"
layout: "post"
diff: 提高+/省选-
pid: P2403
tag: ['2010', '各省省选', '山东', '拓扑排序', '强连通分量', 'Tarjan']
---
# [SDOI2010] 所驼门王的宝藏
## 题目描述

在宽广的非洲荒漠中，生活着一群勤劳勇敢的羊驼家族。被族人恭称为“先知”的 AlpacaL.Sotomon 是这个家族的领袖，外人也称其为“所驼门王”。所驼门王毕生致力于维护家族的安定与和谐，他曾亲自率军粉碎河蟹帝国主义的野蛮侵略，为族人立下赫赫战功。所驼门王一生财宝无数，但因其生性节俭低调，他将财宝埋藏在自己设计的地下宫殿里，这也是今天 Henry Curtis 故事的起点。Henry 是一个爱财如命的贪婪家伙，而又非常聪明，他费尽心机谋划了这次盗窃行动，破解重重机关后来到这座地下宫殿前。

整座宫殿呈矩阵状，由 $R \times C$ 间矩形宫室组成，其中有 $N$ 间宫室里埋藏着宝藏，称作藏宝宫室。宫殿里外、相邻宫室间都由坚硬的实体墙阻隔，由一间宫室到达另一间只能通过所驼门王独创的移动方式——传送门。所驼门王为这 $N$ 间藏宝宫室每间都架设了一扇传送门，没有宝藏的宫室不设传送门，所有的宫室传送门分为三种：

1. “横天门”：由该门可以传送到同行的任一宫室；
2. “纵寰门”：由该门可以传送到同列的任一宫室；
3. “任意门”：由该门可以传送到以该门所在宫室为中心周围 $8$ 格中任一宫室（如果目标宫室存在的话）。

深谋远虑的 Henry 当然事先就搞到了所驼门王当年的宫殿招标册，书册上详细记录了每扇传送门所属宫室及类型。而且，虽然宫殿内外相隔，但他自行准备了一种便携式传送门，可将自己传送到殿内任意一间宫室开始寻宝，并在任意一间宫室结束后传送出宫。整座宫殿只许进出一次，且便携门无法进行宫室之间的传送。不过好在宫室内传送门的使用没有次数限制，每间宫室也可以多次出入。

现在 Henry 已经打开了便携门，即将选择一间宫室进入。为得到尽多宝藏，他希望安排一条路线，使走过的不同藏宝宫室尽可能多。请你告诉 Henry 这条路线最多行经不同藏宝宫室的数目。
## 输入格式

第一行给出三个正整数 $N,R,C$。

以下 $N$ 行，每行给出一扇传送门的信息，包含三个正整数 $x_i,y_i,T_i$，表示该传送门设在位于第 $x_i$ 行第 $y_i$ 列的藏宝宫室，类型为 $T_i$。$T_i$ 是一个 $1 \sim 3$ 间的整数，$1$ 表示可以传送到第 $x_i$ 行任意一列的“横天门”，$2$ 表示可以传送到任意一行第 $y_i$ 列的“纵寰门”，$3$ 表示可以传送到周围 $8$ 格宫室的“任意门”。

保证 $1 \le x_i \le R$，$1 \le y_i \le C$，所有的传送门位置互不相同。
## 输出格式

输出只有一个正整数，表示你确定的路线所经过不同藏宝宫室的最大数目。

## 样例

### 样例输入 #1
```
10 7 7
2 2 1
2 4 2
1 7 2
2 7 3
4 2 2
4 4 1
6 7 3
7 7 1
7 5 2
5 2 1
```
### 样例输出 #1
```
9
```
## 提示

数据规模和约定：

![](https://cdn.luogu.com.cn/upload/pic/1594.png)



---

---
title: "[HAOI2006] 旅行"
layout: "post"
diff: 提高+/省选-
pid: P2502
tag: ['2006', '河南', '并查集', '各省省选', '枚举', '排序']
---
# [HAOI2006] 旅行
## 题目描述

Z 小镇是一个景色宜人的地方，吸引来自各地的观光客来此旅游观光。Z 小镇附近共有 $n$ 个景点（编号为 $1,2,3,\ldots,n$），这些景点被 $m$ 条道路连接着，所有道路都是双向的，两个景点之间可能有多条道路。

也许是为了保护该地的旅游资源，Z 小镇有个奇怪的规定，就是对于一条给定的公路 $r_i$，任何在该公路上行驶的车辆速度必须为 $v_i$。

速度变化太快使得游客们很不舒服，因此从一个景点前往另一个景点的时候，大家都希望选择行驶过程中最大速度和最小速度的比尽可能小的路线，也就是所谓最舒适的路线。
## 输入格式

第一行包含两个正整数 $n,m$。

接下来的 $m$ 行每行包含三个正整数 $x,y,v$。表示景点 $x$ 到景点 $y$ 之间有一条双向公路，车辆必须以速度 $v$ 在该公路上行驶。

最后一行包含两个正整数 $s,t$，表示想知道从景点 $s$ 到景点 $t$ 最大最小速度比最小的路径。$s$ 和 $t$ 不可能相同。
## 输出格式

如果景点 $s$ 到景点 $t$ 没有路径，输出` IMPOSSIBLE`。否则输出一个数，表示最小的速度比。如果需要，输出一个既约分数。

## 样例

### 样例输入 #1
```
4 2
1 2 1
3 4 2
1 4
```
### 样例输出 #1
```
IMPOSSIBLE
```
### 样例输入 #2
```
3 3
1 2 10
1 2 5
2 3 8
1 3
```
### 样例输出 #2
```
5/4
```
### 样例输入 #3
```
3 2
1 2 2
2 3 4
1 3
```
### 样例输出 #3
```
2
```
## 提示

对于 $100\%$ 的数据，$1 \le x,y \le n \le 500$，$1 \le v < 3 \times 10^4$，$1 \le m \le 5 \times 10^3$，$x \ne y$。


---

---
title: "[AHOI2012] 铁盘整理"
layout: "post"
diff: 提高+/省选-
pid: P2534
tag: ['搜索', '2012', '各省省选', '安徽', '排序', '剪枝', '启发式迭代加深搜索 IDA*', 'A*  算法']
---
# [AHOI2012] 铁盘整理
## 题目描述

在训练中，一些臂力训练器材是少不了的，小龙在练习的时候发现举重器械上的铁盘放置的非常混乱，并没有按照从轻到重的顺序摆放，这样非常不利于循序渐进的锻炼。他打算利用一个非常省力气的办法来整理这些铁盘，即每次都拿起最上面的若干个圆盘并利用器械的力量上下翻转，这样翻转若干次以后，铁盘将会按照从小到大的顺序排列好。那么你能不能帮小龙确定，最少翻转几次就可以使铁盘按从小到大排序呢？

例如：下面的铁盘经过如图所示的以下几个步骤的翻转后变为从小到大排列。

![](https://cdn.luogu.com.cn/upload/image_hosting/xtpst1lw.png)
## 输入格式

共两行。第一行为铁盘个数 $N$（$1 \leq N \leq 16$），第二行为 $N$ 个不同的正整数，分别为从上到下的铁盘的半径 $R$（$1 \leq R \leq 100$）。

## 输出格式

一个正整数，表示使铁盘从小到大有序需要的最少翻转次数。
## 样例

### 样例输入 #1
```
5
2 4 3 5 1
```
### 样例输出 #1
```
5
```


---

---
title: "[SCOI2012] 滑雪"
layout: "post"
diff: 提高+/省选-
pid: P2573
tag: ['图论', '2012', '四川', '各省省选', '排序', '生成树']
---
# [SCOI2012] 滑雪
## 题目描述

a180285 非常喜欢滑雪。他来到一座雪山，这里分布着 $m$ 条供滑行的轨道和 $n$ 个轨道之间的交点（同时也是景点），而且每个景点都有一编号 $i\space (1 \le i \le n)$ 和一高度 $h_i$。  

a180285 能从景点 $i$ 滑到景点 $j$ 当且仅当存在一条 $i$ 和 $j$ 之间的边，且 $i$ 的高度**不小于** $j$。与其他滑雪爱好者不同，a180285 喜欢用最短的滑行路径去访问尽量多的景点。如果仅仅访问一条路径上的景点，他会觉得数量太少。

于是 a18028 5拿出了他随身携带的时间胶囊。这是一种很神奇的药物，吃下之后可以立即回到上个经过的景点（不用移动也不被认为是 a180285 滑行的距离）。  

请注意，这种神奇的药物是可以连续食用的，即能够回到较长时间之前到过的景点（比如上上个经过的景点和上上上个经过的景点）。 现在，a180285站在 $1$ 号景点望着山下的目标，心潮澎湃。他十分想知道在不考虑时间胶囊消耗的情况下，以最短滑行距离滑到尽量多的景点的方案（即满足经过景点数最大的前提下使得滑行总距离最小）。你能帮他求出最短距离和景点数吗？

## 输入格式

输入的第一行是两个整数 $n,m$。
接下来一行有 $n$ 个整数 $h_i$，分别表示每个景点的高度。

接下来 $m$ 行，表示各个景点之间轨道分布的情况。每行三个整数 $u,v,k$，表示编号为 $u$ 的景点和编号为 $v$ 的景点之间有一条长度为 $k$ 的轨道。

## 输出格式

输出一行，表示 a180285 最多能到达多少个景点，以及此时最短的滑行距离总和。

## 样例

### 样例输入 #1
```
3 3 
3 2 1 
1 2 1 
2 3 1 
1 3 10 
```
### 样例输出 #1
```
3 2
```
## 提示

【数据范围】   
对于 $ 30\% $ 的数据，$ 1 \le n \le 2000 $；   
对于 $ 100\% $ 的数据，$ 1 \le n \le 10^5 $。


对于所有的数据，保证 $ 1 \le m \le 10^6 $ , $ 1 \le h_i \le 10^9 $ ，$ 1 \le k_i \le 10^9 $。



---

---
title: "[USACO3.1] 联系 Contact"
layout: "post"
diff: 提高+/省选-
pid: P2724
tag: ['USACO', '枚举', '排序']
---
# [USACO3.1] 联系 Contact
## 题目背景

奶牛们开始对用射电望远镜扫描牧场外的宇宙感兴趣。最近，他们注意到了一种非常奇怪的脉冲调制微波从星系的中央发射出来。他们希望知道电波是否是被某些地外生命发射出来的，还是仅仅是普通的的星星发出的。

## 题目描述

帮助奶牛们用一个能够分析他们在文件中记下的记录的工具来找到真相。他们在寻找长度在 $A$ 到 $B$ 之间（包含 $A$ 和 $B$ 本身）在每天的数据文件中重复次数前 $n$ 多的比特序列。

符合的序列可能会重叠，并且至少出现一次的序列会被计数。
## 输入格式

输入的第一行是三个整数 $A, B, n$，其含义见【题目描述】。

第二行是及以后一个字符串 $s$，每行的字符数不超过 $80$。所有行的字符串依次连接即为 $s$。
## 输出格式

输出 $n$ 个频率最高的序列（按照频率由高到低的次序）。由短到长排列频率相同的这些序列，如果长短相同，按二进制大小排列。如果出现的序列个数小于 $n$，输出存在的序列。

对于每个存在的频率，先输出单独包含该频率的一行，再输出以空格分隔的这些序列。每行六个（除非剩下的少于六个）。
## 样例

### 样例输入 #1
```
2 4 10
01010010010001000111101100001010011001111000010010011110010000000
```
### 样例输出 #1
```
23
00
15
01 10
12
100
11
11 000 001
10
010
8
0100
7
0010 1001
6
111 0000
5
011 110 1000
4
0001 0011 1100
```
## 提示

#### 输入输出样例 1 解释

在样例里，序列 $100$ 出现了 $12$ 次，而序列 $1000$ 出现了 $5$ 次。次数最多的序列是 $00$，出现了 $23$ 次。

---

#### 数据规模与约定

对于 $100\%$ 的数据，保证 $1 \leq n \leq 50$，$1 \leq A \leq B \leq 12$，$s$ 中只含字符 `0` 和字符 `1`，且长度不超过 $2 \times 10^5$。

---
#### 说明

题目翻译来自 NOCOW。


---

---
title: "[USACO09DEC] Cow Toll Paths G"
layout: "post"
diff: 提高+/省选-
pid: P2966
tag: ['2009', 'USACO', '排序', '最短路']
---
# [USACO09DEC] Cow Toll Paths G
## 题目描述

Like everyone else, FJ is always thinking up ways to increase his revenue. To this end, he has set up a series of tolls that the cows will pay when they traverse the cowpaths throughout the farm.

The cows move from any of the $N (1 \leq N \leq 250)$ pastures conveniently numbered $1...N$ to any other pasture over a set of $M (1 \leq M \leq 10,000) $bidirectional cowpaths that connect pairs of different pastures $A_j$ and $B_j (1 \leq A_j \leq N; 1 \leq B_j \leq N)$. FJ has assigned a toll $L_j (1 \leq L_j \leq 100,000)$ to the path connecting pastures $A_j$ and $B_j$.

While there may be multiple cowpaths connecting the same pair of pastures, a cowpath will never connect a pasture to itself. Best of all, a cow can always move from any one pasture to any other pasture by following some sequence of cowpaths.

In an act that can only be described as greedy, FJ has also assigned a toll $C_i (1 \leq C_i \leq 100,000)$ to every pasture. The cost of moving from one pasture to some different pasture is the sum of the tolls for each of the cowpaths that were traversed plus a **single additional toll** that is the maximum of all the pasture tolls encountered along the way, including the initial and destination pastures.

The patient cows wish to investigate their options. They want you to write a program that accepts $K (1 \leq K \leq 10,000)$ queries and outputs the minimum cost of trip specified by each query. Query $i$ is a pair of numbers $s_i$ and $t_i (1 \leq s_i \leq N; 1 \leq t_i \leq N; s_i \neq t_i)$ specifying a starting and ending pasture.

Consider this example diagram with five pastures:

The 'edge toll' for the path from pasture $1$ to pasture $2$ is $3$. Pasture $2$'s 'node toll' is $5$.

To travel from pasture $1$ to pasture $4$, traverse pastures $1$ to $3$ to $5$ to $4$. This incurs an edge toll of $2+1+1=4$ and a node toll of $4$ (since pasture $5$'s toll is greatest), for a total cost of $4+4=8$.

The best way to travel from pasture $2$ to pasture $3$ is to traverse pastures $2$ to $5$ to $3$. This incurs an edge toll of $3+1=4$ and a node toll of $5$, for a total cost of $4+5=9$.

给定一个 $n$ 点 $m$ 边的双向图，第 $i$ 条道路连接了 $u_i$ 与 $v_i$，边权为 $w_i$，第 $i$ 个点的点权为 $c_i$。

给定 $q$ 组询问，第 $i$ 组询问求从 $s_i$ 到 $t_i$ 的路径的边权之和与点权的最大值的和的最小值。

**可能有重边，但保证无自环。**
## 输入格式

-  Line $1$: Three space separated integers: $N$, $M$, and $K$

- Lines $2..N+1$: Line $i+1$ contains a single integer: $C_i$

- Lines $N+2..N+M+1$: Line $j+N+1$ contains three space separated integers: $A_j$, $B_j$, and $L_j$

- Lines $N+M+2..N+M+K+1$: Line $i+N+M+1$ specifies query $i$ using two space-separated integers: $s_i$ and $t_i$

第一行三个整数 $n,m,q$ 代表点数，边数与询问数。   
接下来 $n$ 行每行一个整数 $c_i$ 代表第 $i$ 个点的点权。    
接下来 $m$ 行每行三个整数 $u_i,v_i,w_i$ 代表第 $i$ 条边从 $u_i$ 连到 $v_i$ 边权为 $w_i$。   
接下来 $q$ 行每行两个整数 $s_i,t_i$ 代表第 $i$ 组询问求从 $s_i$ 到 $t_i$ 的边权之和与点权的最大值的和的最小值。

## 输出格式

- Lines $1..K$: Line $i$ contains a single integer which is the lowest cost of any route from $s_i$ to $t_i$

$q$ 行每行一个整数，代表第 $i$ 组询问的结果。
## 样例

### 样例输入 #1
```
5 7 2 
2 
5 
3 
3 
4 
1 2 3 
1 3 2 
2 5 3 
5 3 1 
5 4 1 
2 4 3 
3 4 4 
1 4 
2 3 

```
### 样例输出 #1
```
8 
9 

```
## 提示

对于 $100\%$ 的数据，$1 \le n \le 250$，$1 \le m \le 10^4$，$1 \le q \le 10^4$。


---

---
title: "[USACO10JAN] Cow Telephones G"
layout: "post"
diff: 提高+/省选-
pid: P2977
tag: ['贪心', '递推', '2010', 'USACO', '排序']
---
# [USACO10JAN] Cow Telephones G
## 题目描述

The cows have set up a telephone network, which for the purposes of this problem can be considered to be an unrooted tree of unspecified degree with N (1 <= N <= 100,000) vertices conveniently numbered 1..N. Each vertex represents a telephone switchboard, and each edge represents a telephone wire between two switchboards. Edge i is specified by two integers A\_i and B\_i the are the two vertices joined by edge i (1 <= A\_i <= N; 1 <= B\_i <= N; A\_i != B\_i).

Some switchboards have only one telephone wire connecting them to another switchboard; these are the leaves of the tree, each of which is a telephone booth located in a cow field.

For two cows to communicate, their conversation passes along the unique shortest path between the two vertices where the cows are located. A switchboard can accomodate only up to K (1 <= K <= 10) simultaneous conversations, and there can be at most one conversation going through a given wire at any one time.

Given that there is a cow at each leaf of the tree, what is the maximum number of pairs of cows that can simultaneously hold

conversations? A cow can, of course, participate in at most one conversation.

```cpp
1   5          C1   C5 
|   |          ||   || 
2---4   -->    |2---4| 
|   |          ||   || 
3   6          C3   C6 
```
Consider this six-node telephone tree with K=1: 

There are four cows, located at vertices 1, 3, 5 and 6. If cow 1 talks to cow 3, and cow 5 talks to cow 6, then they do not exceed the maximum number of conversations per switchboard, so for this example the answer is 2 (for two pairs of cows talking simultaneously). 

奶牛们要建立一个电话网络，它们可以被认为是一个无根树（大概是个图吧。。。），里面N (1 <= N <= 100,000)个结点可以简便的编号为1...N。每一个结点代表一个电话交换机（类似开关），每条边代表一个连接两个电话交换机的电话线。边i是用两个整数A\_i和B\_i表示的，也就是该边连接着A\_i和B\_i两个电话交换机(1 <= A\_i <= N; 1 <= B\_i <= N; A\_i != B\_i).

一些电话交换机只有一根电话线；它们是这棵树的叶子结点，每个叶子结点只有一只牛。当两头牛在通话时，它们的对话沿着唯一的在两头牛所在结点的最短路径。

一个电话交换机只能忙于K(1 <= K <= 10)个同时的对话，而且每个电话线同一时间只能传送一个对话。

给出一个每个叶子结点都有一头牛的树， 问最多有多少对奶牛能在同一时间进行它们的对话？

## 输入格式

\* Line 1: Two space separated integers: N and K

\* Lines 2..N: Line i+1 contains two space-separated integers: A\_i and B\_i

## 输出格式

\* Line 1: The number of pairs of cows that can simultaneously hold conversations

## 样例

### 样例输入 #1
```
6 1 
1 2 
2 3 
2 4 
4 5 
4 6 

```
### 样例输出 #1
```
2 

```


---

---
title: "[USACO11OPEN] Cow Checkers S"
layout: "post"
diff: 提高+/省选-
pid: P3024
tag: ['贪心', '2011', 'USACO', '排序']
---
# [USACO11OPEN] Cow Checkers S
## 题目描述

One day, Bessie decides to challenge Farmer John to a game of 'Cow Checkers'. The game is played on an M\*N (1 <= M <= 1,000,000; 1 <= N <= 1,000,000) checkerboard that initially contains a single checker piece on the checkboard square coordinates (X, Y) (0 <= X < M; 0 <= Y < N). The bottom leftmost square of the checkerboard has

coordinates (0, 0), and the top rightmost square has coordinates (M-1, N-1). Bessie always moves first, and then the two players alternate turns.  Each turn comprises one of three types of moves:

1) Move the checker piece to any square on the same row to the left of its current position.

2) Move the checker piece to any square on the same column below its current position.

3) Move the checker piece to any spot k squares below and k squares to the left of the current square (where k is any positive integer such that this new spot is still on the checkerboard).

The first player unable to make a move (i.e., because the checker is at (0, 0)) loses. Given that Bessie always goes first, determine who will win the game if both play optimally.

Play and report the winner for T games (1 <= T <= 1,000) reading in a new X,Y starting value for each new game.

有一天，Bessie准备玩一个叫做奶牛跳棋的游戏，来挑战Farmer John。


这个游戏的棋盘大小为 M\*N (1 <= M <= 1,000,000; 1 <= N <= 1,000,000) 。最初棋盘上只有一个棋子在（x,y），棋盘的左下角坐标是（0,0），右上角的坐标是（M-1，N-1）。


每次游戏Bessie都是第一个开始，之后两个人轮流。


每次下棋的时候都有三种走法：


1.向左走任意步


2.向下走任意步


3.向左走k步然后向下走k步（k可随便取值，只要不走出棋盘）


首先走到（0,0）的人为胜利者。


游戏共有T次，每次都会给出一个新的坐标（x,y），请输出每一轮赢家的名字。

## 输入格式

\* Line 1: Two space-separated integers: M and N

\* Line 2: A single integer: T

\* Lines 3..T+2: Two space-separated integers: X and Y

第一行：M N


第二行：T


第三行到第T+2行:这一轮的X Y

## 输出格式

\* Lines 1..T: Should contain either 'Farmer John' or 'Bessie' depending on who wins each  game.

共T行，每一行输出那一轮的赢家

## 样例

### 样例输入 #1
```
3 3 
1 
1 1 

```
### 样例输出 #1
```
Bessie 

```
## 提示

Farmer John and Bessie are playing one game on a 3\*3 checkerboard with the checker piece initially at (1, 1) (i.e. at the center of the board).


Bessie initially can only move the checker piece to either (1, 0) or (0, 1), or (0, 0). Bessie can immediately win by moving the piece to (0, 0).


起点在（1,1），一开始有三种选择（1,0）,（0,1），（0,0）只要Bessie在开始时将棋子移到（1,0）或（0,1），就必胜无疑。


感谢@ 2014nhc  提供的翻译



---

---
title: "[USACO11DEC] Cow Photography G/S"
layout: "post"
diff: 提高+/省选-
pid: P3034
tag: ['2011', 'USACO', '排序']
---
# [USACO11DEC] Cow Photography G/S
## 题目描述

The cows are in a particularly mischievous mood today!  All Farmer John wants to do is take a photograph of the cows standing in a line, but they keep moving right before he has a chance to snap the picture.

Specifically, each of FJ's N (1 <= N <= 20,000) cows has a unique integer ID number.  FJ wants to take a picture of the cows standing in a line in a very specific ordering, represented by the contents of an array A[1...N], where A[j] gives the ID number of the jth cow in the ordering.  He arranges the cows in this order, but just before he can press the button on his camera to snap the picture, a group of zero or more cows (not necessarily a contiguous group) moves to a set of new positions in the lineup.  More precisely, a group of zero or more cows steps away from the line, with the remaining cows shifting over to close the resulting gaps in the lineup.  The cows who stepped away then re-insert themselves at different positions in the lineup (not necessarily at the locations they originally occupied).  Frustrated but not deterred, FJ again arranges his cows according to the ordering in A, but again, right before he can snap a picture, a different group of zero or more cows moves to a set of new positions in the lineup.

The process above repeats for a total of five photographs before FJ gives up.  Given the contents of each photograph, see if you can reconstruct the original intended ordering A.  Each photograph shows an ordering of the cows that differs from A in that some group of zero or more cows has moved. However, a cow only moves in at most one photograph: if a cow is part of the group that moves in one photograph, she will not actively move in any of the other four photographs (although she could end up at a different index as a consequence of other cows around her moving, of course).

Farmer John居然拍了五张照片，每张表示初始化牛位置的移动后的状态。然后求出FJ这五头牛初始化的样子。

## 输入格式

\* Line 1: The number of cows, N (1 <= N <= 20,000). 

\* Lines 2..5N+1: The next 5N lines describe five orderings, each one a block of N contiguous lines.  Each line contains the ID of a cow, an integer in the range 0...1,000,000,000.

## 输出格式

\* Lines 1..N: The intended ordering A, one ID per line. 


## 样例

### 样例输入 #1
```
5 
10 
20 
30 
40 
50 
20 
10 
30 
40 
50 
30 
10 
20 
40 
50 
40 
10 
20 
30 
50 
50 
10 
20 
30 
40 

```
### 样例输出 #1
```
10 
20 
30 
40 
50 

```
## 提示

There are 5 cows, with IDs 10, 20, 30, 40, and 50.  In each of the 5 photos, a different cow moves to the front of the line (at most one cow moves in each photo here, but it is possible in other inputs that multiple cows could move in a particular photo).


The correct original ordering A[1..5] is 10, 20, 30, 40, 50.


## 题目翻译

## 题目描述

今天的奶牛们特别调皮！Farmer John 想做的只是给排成一排的奶牛拍照，但是在他拍下照片之前，奶牛们一直在移动。

具体地说，FJ 有 $N$ 头奶牛（$1 \leq N \leq 20\,000$），每头奶牛都有一个唯一确定的编号。FJ 想要以一个特定的顺序拍下一张奶牛排成一排的照片，这个顺序用数组 $A[1 \ldots N]$ 表示，其中 $A[i]$ 代表排在 $i$ 位置的奶牛的编号。

他按照这样的顺序将奶牛们排列好，但在他按下快门之前，有些奶牛（可能是零头或任意多头奶牛，位置也不一定连续）将移到一个新的位置。更准确地说，一些奶牛离开队列，剩下的奶牛靠拢，这些离开的奶牛再将自己重新插入到队列中的任意位置（不一定是他们之前的位置）。FJ 感到非常沮丧，他再次按照 $A$ 数组的顺序重新安排了队列。但在他再次按下快门之前，又有一些奶牛移动到了新的位置。

就这样，FJ 拍了五张照片。给出每张照片拍摄的内容（即 FJ 按下快门时奶牛的顺序），请你尝试推算出 FJ 最初为奶牛们排的顺序（即 $A$ 数组）。由于可能有奶牛移动，照片显示的顺序与原来的顺序可能有所不同。但是，一头奶牛最多只会移动一次：即如果一头奶牛在拍其中一张照片时移动了，它在拍其他四张照片的时候都不会移动。当然，由于其他奶牛也在移动，它在不同照片中的顺序并不一定相同。

## 输入格式

第一行包含一个整数 $N$。

接下来 $5N$ 行，每 $N$ 行描述了一张照片中各奶牛的顺序。每行包含一个奶牛的编号，保证所有编号都是不超过 $1\,000\,000\,000$ 的非负整数。

## 输出格式

输出 $N$ 行，每行一个整数 $A[i]$，即 FJ 最初为奶牛排好的顺序。

## 样例解释

FJ 拍的五张照片分别为：

- `10 20 30 40 50`
- `20 10 30 40 50`
- `30 10 20 40 50`
- `40 10 20 30 50`
- `50 10 20 30 40`


---

---
title: "[USACO14JAN] Cow Curling G"
layout: "post"
diff: 提高+/省选-
pid: P3099
tag: ['贪心', '2014', 'USACO', '排序']
---
# [USACO14JAN] Cow Curling G
## 题目描述

Cow curling is a popular cold-weather sport played in the Moolympics.

Like regular curling, the sport involves two teams, each of which slides N heavy stones (3 <= N <= 50,000) across a sheet of ice.  At the end of the game, there are 2N stones on the ice, each located at a distinct 2D point.

Scoring in the cow version of curling is a bit curious, however.  A stone is said to be "captured" if it is contained inside a triangle whose corners are stones owned by the opponent (a stone on the boundary of such a triangle also counts as being captured).  The score for a team is the number of opponent stones that are captured.

Please help compute the final score of a cow curling match, given the locations of all 2N stones.

有两支队伍在比赛，一队可以一次取出3个点来，所围成的三角形覆盖的区域可以“捕获”对方的点，问两支队伍各能够捕获对方多少个点。

## 输入格式

\* Line 1: The integer N.

\* Lines 2..1+N: Each line contains 2 integers specifying the x and y coordinates of a stone for team A (each coordinate lies in the range -40,000 .. +40,000).

\* Lines 2+N..1+2N: Each line contains 2 integers specifying the x and y coordinates of a stone for team B (each coordinate lies in the range -40,000 .. +40,000).

## 输出格式

\* Line 1: Two space-separated integers, giving the scores for teams A and B.

## 样例

### 样例输入 #1
```
4 
0 0 
0 2 
2 0 
2 2 
1 1 
1 10 
-10 3 
10 3 

```
### 样例输出 #1
```
1 2 

```
## 提示

Each team owns 4 stones.  Team A has stones at (0,0), (0,2), (2,0), and (2,2), and team B has stones at (1,1), (1,10), (-10,3), and (10,3).


Team A captures their opponent's stone at (1,1).  Team B captures their opponent's stones at (0,2) and (2,2).



---

---
title: "[USACO15JAN] Grass Cownoisseur G"
layout: "post"
diff: 提高+/省选-
pid: P3119
tag: ['2015', 'USACO', '拓扑排序', '强连通分量', 'Tarjan']
---
# [USACO15JAN] Grass Cownoisseur G
## 题目描述

In an effort to better manage the grazing patterns of his cows, Farmer John has installed one-way cow paths all over his farm. The farm consists of N fields, conveniently numbered 1..N, with each one-way cow path connecting a pair of fields. For example, if a path connects from field X to field Y, then cows are allowed to travel from X to Y but not from Y to X.

Bessie the cow, as we all know, enjoys eating grass from as many fields as possible. She always starts in field 1 at the beginning of the day and visits a sequence of fields, returning to field 1 at the end of the day. She tries to maximize the number of distinct fields along her route, since she gets to eat the grass in each one (if she visits a field multiple times, she only eats the grass there once).

As one might imagine, Bessie is not particularly happy about the one-way restriction on FJ's paths, since this will likely reduce the number of distinct fields she can possibly visit along her daily route.  She wonders how much grass she will be able to eat if she breaks the rules and follows up to one path in the wrong direction. Please compute the maximum number of distinct fields she can visit along a route starting and ending at field 1, where she can follow up to one path along the route in the wrong direction.  Bessie can only travel backwards at most once in her journey.  In particular, she cannot even take the same path backwards twice.
## 输入格式

The first line of input contains N and M, giving the number of fields and the number of one-way paths (1 <= N, M <= 100,000). 

The following M lines each describe a one-way cow path.  Each line contains two distinct field numbers X and Y, corresponding to a cow path from X to Y.  The same cow path will never appear more than once.
## 输出格式

A single line indicating the maximum number of distinct fields Bessie can visit along a route starting and ending at field 1, given that she can follow at most one path along this route in the wrong direction.
## 样例

### 样例输入 #1
```
7 10 
1 2 
3 1 
2 5 
2 4 
3 7 
3 5 
3 6 
6 5 
7 2 
4 7 


```
### 样例输出 #1
```
6 

```
## 提示

SOLUTION NOTES:

Here is an ASCII drawing of the sample input:

```cpp
v---3-->6
7   | \ |
^\  v  \|
| \ 1   |
|   |   v
|   v   5
4<--2---^
```

Bessie can visit pastures 1, 2, 4, 7, 2, 5, 3, 1 by traveling backwards on the path between 5 and 3.  When she arrives at 3 she cannot reach 6 without following another backwards path.
## 题目翻译

### 题目描述

为了更好地管理牛群的放牧路线，Farmer John 在他的农场中安装了若干单向牛道。农场由 $N$ 块草场组成，编号为 $1$ 到 $N$，每条单向牛道连接一对草场。例如，若存在一条从草场 $X$ 到 $Y$ 的路径，则牛可以从 $X$ 前往 $Y$，但不能从 $Y$ 返回 $X$。

众所周知，Bessie 喜欢尽可能多地品尝不同草场的牧草。她每天从草场 $1$ 出发，访问一系列草场后返回草场 $1$。她试图最大化沿途经过的不同草场数量（重复访问的草场只算一次）。

由于单向路径的限制，Bessie 担心这会减少她每日路线中可以访问的草场数量。她想知道如果她违反规则，在路线中最多逆向通过某条道路一次，最多能品尝多少草场的牧草。请计算她从草场 $1$ 出发并返回的情况下，最多能访问的不同草场数量。注意 Bessie 在整个旅程中最多只能逆向通过一条道路，且同一条路径不能逆向两次。

### 输入格式

第一行包含两个整数 $N$ 和 $M$，表示草场数量和单向牛道数量（$1 \leq N, M \leq 100,000$）。

接下来 $M$ 行每行描述一条单向牛道，包含两个不同的整数 $X$ 和 $Y$，表示从 $X$ 到 $Y$ 的单向路径。保证每条路径不会重复出现。

### 输出格式

输出一行，表示 Bessie 在最多逆向通过一条道路的情况下，从草场 $1$ 出发并返回时能访问的最大不同草场数量。

### 说明/提示

**样例解析：**

以下是样例输入的 ASCII 图示：

```
v---3-->6
7   | \ |
^\  v  \|
| \ 1   |
|   |   v
|   v   5
4<--2---^
```

Bessie 可以通过逆向路径 $5\to 3$ 访问草场 $1, 2, 4, 7, 2, 5, 3, 1$。到达草场 $3$ 后，若不再次逆向其他路径则无法前往 $6$。


---

---
title: "[USACO15OPEN] Trapped in the Haybales S"
layout: "post"
diff: 提高+/省选-
pid: P3124
tag: ['贪心', '2015', 'USACO', '排序']
---
# [USACO15OPEN] Trapped in the Haybales S
## 题目描述

Farmer John has received a shipment of $N$ large hay bales ($1 \le N \le 100,000$), and placed them at various locations along the road connecting the barn with his house.  Each bale $j$ has a size $S_j$ and a distinct position $P_j$ giving its location along the one-dimensional road. Bessie the cow is currently located at position $B$, where there is no hay bale.

Bessie the cow can move around freely along the road, even up to the position at which a bale is located, but she cannot cross through this position.  As an exception, if she runs in the same direction for $D$ units of distance, she builds up enough speed to break through and permanently eliminate any hay bale of size strictly less than $D$. Of course, after doing this, she might open up more space to allow her to make a run at other hay bales, eliminating them as well.

FJ is currently re-painting his house and his barn, and wants to make sure Bessie cannot reach either one (cows and fresh paint do not make a good combination!)  Accordingly, FJ wants to make sure Bessie never breaks through the leftmost or rightmost hay bale, so she stays effectively trapped within the hay bales.  FJ has the ability to add hay to a single bale of his choosing to help keep Bessie trapped.  Please help him determine the minimum amount of extra size he needs to add to some bale to ensure Bessie stays trapped.
## 输入格式

The first line of input contains $N$ as well as Bessie's initial position $B$. Each of the next $N$ lines describes a bale, and contains two integers giving its size and position.  All sizes and positions are in the range $1\ldots 10^9$.

## 输出格式

Print a single integer, giving the minimum amount of hay FJ needs to add to prevent Bessie from escaping.  Print -1 if it is impossible to prevent Bessie's escape.

## 样例

### 样例输入 #1
```
5 7
8 1
1 4
3 8
12 15
20 20
```
### 样例输出 #1
```
4
```
## 题目翻译

### 题目描述

FJ 收到了 $N$ 捆干草，并将它们放置在连接房屋与谷仓的道路上。第 $j$ 捆干草的大小为 $S_j$，位置为 $P_j$。Bessie 一开始在 $B$ 处，不与任何一捆干草的位置重合。

Bessie 可以在干草捆之间任意移动（也可以到达干草捆所在的位置），但不能越过干草捆。但凡事总有例外：当 Bessie 进行了长度为 $D$ 的冲刺后，她就可以击碎一捆大小严格小于 $D$ 的干草，这意味着这捆干草不复存在。

由于某些原因，FJ 希望把 Bessie 困在最左边与最右边的干草捆之间。为此，他希望将某一捆干草的大小增加一些。如果可能把 Bessie 困住，请输出他最少需要增加多少干草；否则输出 `-1`。

$1 \leqslant N \leqslant 10^5$，$1 \leqslant S_i, P_i, B \leqslant 10^9$。

### 输入格式

第一行，两个整数 $N, B$，分别表示干草捆数量与 Bessie 所在位置。

接下来 $N$ 行，第 $i$ 行为两个整数 $S_i, P_i$，分别表示第 $i$ 捆干草的大小与位置。

### 输出格式

如果可能把 Bessie 困住，输出一行一个整数，表示最少需要增加多少干草；否则输出 `-1`。

Translated by [KHIN](/user/236807).


---

---
title: "[HNOI2015] 菜肴制作"
layout: "post"
diff: 提高+/省选-
pid: P3243
tag: ['贪心', '2015', '湖南', '排序', '拓扑排序']
---
# [HNOI2015] 菜肴制作
## 题目描述

知名美食家小 A 被邀请至 ATM 大酒店，为其品评菜肴。ATM 酒店为小 A 准备了 $n$ 道菜肴，酒店按照为菜肴预估的质量从高到低给予 $1$ 到 $n$ 的顺序编号，预估质量最高的菜肴编号为 $1$。

由于菜肴之间口味搭配的问题，某些菜肴必须在另一些菜肴之前制作，具体的，一共有 $m$ 条形如 $i$ 号菜肴必须先于 $j$ 号菜肴制作的限制，我们将这样的限制简写为 $(i,j)$。

现在，酒店希望能求出一个最优的菜肴的制作顺序，使得小 A 能尽量先吃到质量高的菜肴：

也就是说，

1. 在满足所有限制的前提下，$1$ 号菜肴尽量优先制作。

2. 在满足所有限制，$1$ 号菜肴尽量优先制作的前提下，$2$ 号菜肴尽量优先制作。

3. 在满足所有限制，$1$ 号和 $2$ 号菜肴尽量优先的前提下，$3$ 号菜肴尽量优先制作。

4. 在满足所有限制，$1$ 号和 $2$ 号和 $3$ 号菜肴尽量优先的前提下，$4$ 号菜肴尽量优先制作。

5. 以此类推。

例 1：共 $4$ 道菜肴，两条限制 $(3,1)$、$(4,1)$，那么制作顺序是 $3,4,1,2$。

例 2：共 $5$ 道菜肴，两条限制 $(5,2)$、$(4,3)$，那么制作顺序是 $1,5,2,4,3$。

例 1 里，首先考虑 $1$，因为有限制 $(3,1)$ 和 $(4,1)$，所以只有制作完 $3$ 和 $4$ 后才能制作 $1$，而根据 3，$3$ 号又应尽量比 $4$ 号优先，所以当前可确定前三道菜的制作顺序是 $3,4,1$；接下来考虑 $2$，确定最终的制作顺序是 $3,4,1,2$。

例 $2$ 里，首先制作 $1$ 是不违背限制的；接下来考虑 $2$ 时有 $(5,2)$ 的限制，所以接下来先制作 $5$ 再制作 $2$；接下来考虑 $3$ 时有 $(4,3)$ 的限制，所以接下来先制作 $4$ 再制作 $3$，从而最终的顺序是 $1,5,2,4,3$。现在你需要求出这个最优的菜肴制作顺序。无解输出 `Impossible!`（首字母大写，其余字母小写）
## 输入格式

第一行是一个正整数 $t$，表示数据组数。接下来是 $t$ 组数据。对于每组数据：第一行两个用空格分开的正整数 $n$ 和 $m$，分别表示菜肴数目和制作顺序限制的条目数。接下来 $m$ 行，每行两个正整数 $x,y$，表示 $x$ 号菜肴必须先于 $y$ 号菜肴制作的限制。
## 输出格式

输出文件仅包含 $t$ 行，每行 $n$ 个整数，表示最优的菜肴制作顺序，或者 `Impossible!` 表示无解。

## 样例

### 样例输入 #1
```
3
5 4
5 4
5 3
4 2
3 2
3 3
1 2
2 3
3 1
5 2
5 2
4 3
```
### 样例输出 #1
```
1 5 3 4 2 

Impossible! 

1 5 2 4 3
```
## 提示

**【样例解释】**

第二组数据同时要求菜肴 $1$ 先于菜肴 $2$ 制作，菜肴 $2$ 先于菜肴 $3$ 制作，菜肴 $3$ 先于菜肴 $1$ 制作，而这是无论如何也不可能满足的，从而导致无解。

**【数据范围】**

$100\%$ 的数据满足 $n,m\le 10^5$，$1\le t\le 3$。

$m$ 条限制中可能存在完全相同的限制。


---

---
title: "[SDOI2015] 排序"
layout: "post"
diff: 提高+/省选-
pid: P3322
tag: ['搜索', '2015', '山东', '排序', '深度优先搜索 DFS']
---
# [SDOI2015] 排序
## 题目描述

小 A 有一个 $1\sim 2^N$ 的排列 $A_1\sim A_{2^N}$，他希望将 $A$ 数组从小到大排序,小 $A$ 可以执行的操作有 $N$ 种，每种操作最多可以执行一次，对于所有的 $i(1\le i\le N)$，第 $i$ 种操作为将序列从左到右划分为 $2^{N-i+1}$ 段，每段恰好包括 $2^{i-1}$ 个数,然后整体交换其中两段。

小 A 想知道可以将数组 $A$ 从小到大排序的不同的操作序列有多少个。小 A 认为两个操作序列不同，当且仅当操作个数不同，或者至少一个操作不同（种类不同或者操作位置不同）。

下面是一个操作事例: $N=3,A=[3,6,1,2,7,8,5,4]$。
- 第一次操作，执行第 $3$ 种操作，交换 $A[1..4]$ 和 $A[5..8]$，交换后的 $A$ 为$[7,8,5,4,3,6,1,2]$。
- 第二次操作，执行第 $1$ 种操作，交换 $A[3]$ 和 $A[5]$，交换后的 $A$ 为$[7,8,3,4,5,6,1,2]$。
- 第三次操作，执行第 $2$ 种操作，交换 $A[1..2]$ 和 $A[7..8]$，交换后的 $A[1..8]$ 为$[1,2,3,4,5,6,7,8]$。
## 输入格式

第一行，一个整数 $N$。

第二行，$2^N$ 个整数，$A_1\sim A_{2^N}$。
## 输出格式

一个整数表示答案。

## 样例

### 样例输入 #1
```
3
7 8 5 6 1 2 4 3
```
### 样例输出 #1
```
6
```
## 提示

$100\%$ 的数据, $1\le N\le 12$。



---

---
title: "[APIO2009] 会议中心"
layout: "post"
diff: 提高+/省选-
pid: P3626
tag: ['贪心', '2009', '线段树', '倍增', 'APIO', '排序', '前缀和']
---
# [APIO2009] 会议中心
## 题目描述

Siruseri 政府建造了一座新的会议中心。许多公司对租借会议中心的会堂很 感兴趣，他们希望能够在里面举行会议。

对于一个客户而言，仅当在开会时能够独自占用整个会堂，他才会租借会堂。 会议中心的销售主管认为：最好的策略应该是将会堂租借给尽可能多的客户。

显 然，有可能存在不止一种满足要求的策略。 例如下面的例子。总共有 4 个公司。他们对租借会堂发出了请求，并提出了 他们所需占用会堂的起止日期（如下表所示）。

```cpp
       开始日期 结束日期 
 公司1    4        9 
 公司2    9        11 
 公司3    13       19 
 公司4    10       17 
```
上例中，最多将会堂租借给两家公司。租借策略分别是租给公司 1 和公司 3， 或是公司 2 和公司 3，也可以是公司 1 和公司 4。注意会议中心一天最多租借给 一个公司，所以公司 1 和公司 2 不能同时租借会议中心，因为他们在第九天重合 了。

销售主管为了公平起见，决定按照如下的程序来确定选择何种租借策略：首 先，将租借给客户数量最多的策略作为候选，将所有的公司按照他们发出请求的 顺序编号。对于候选策略，将策略中的每家公司的编号按升序排列。最后，选出 其中字典序最小1的候选策略作为最终的策略。

例中，会堂最终将被租借给公司 1 和公司 3：3 个候选策略是 {(1,3),(2,3),(1,4)}。而在字典序中(1,3)<(1,4)<(2,3)。 你的任务是帮助销售主管确定应该将会堂租借给哪些公司。

## 输入格式

输入的第一行有一个整数 N，表示发出租借会堂申请的公司的个数。第 2 到 第 N+1 行每行有 2 个整数。第 i+1 行的整数表示第 i 家公司申请租借的起始和终 止日期。对于每个公司的申请，起始日期为不小于 1 的整数，终止日期为不大于 10^9 的整数。

## 输出格式

输出的第一行应有一个整数 M，表示最多可以租借给多少家公司。第二行应列出 M 个数，表示最终将会堂租借给哪些公司。

## 样例

### 样例输入 #1
```
4 
4 9
9 11 
13 19 
10 17
```
### 样例输出 #1
```
2
1 3
```
## 提示

对于 50%的输入，N≤3000。

在所有输入中，N≤200000。



---

---
title: "[USACO17FEB] Why Did the Cow Cross the Road III G"
layout: "post"
diff: 提高+/省选-
pid: P3660
tag: ['2017', 'USACO', '树状数组', '枚举', '排序', '前缀和']
---
# [USACO17FEB] Why Did the Cow Cross the Road III G
## 题目描述

The layout of Farmer John's farm is quite peculiar, with a large circular road running around the perimeter of the main field on which his cows graze during the day. Every morning, the cows cross this road on their way towards the field, and every evening they all cross again as they leave the field and return to the barn.

As we know, cows are creatures of habit, and they each cross the road the same way every day. Each cow crosses into the field at a different point from where she crosses out of the field, and all of these crossing points are distinct from each-other. Farmer John owns $N$ cows, conveniently identified with the integer IDs $1 \ldots N$, so there are precisely $2N$ crossing points around the road. Farmer John records these crossing points concisely by scanning around the circle clockwise, writing down the ID of the cow for each crossing point, ultimately forming a sequence with $2N$ numbers in which each number appears exactly twice. He does not record which crossing points are entry points and which are exit points.

Looking at his map of crossing points, Farmer John is curious how many times various pairs of cows might cross paths during the day. He calls a pair of cows $(a,b)$ a "crossing" pair if cow $a$'s path from entry to exit must cross cow $b$'s path from entry to exit. Please help Farmer John count the total number of crossing pairs.
## 输入格式

The first line of input contains $N$ ($1 \leq N \leq 50,000$), and the next $2N$ lines describe the cow IDs for the sequence of entry and exit points around the field.

## 输出格式

Please print the total number of crossing pairs.

## 样例

### 样例输入 #1
```
4
3
2
4
4
1
3
2
1
```
### 样例输出 #1
```
3
```
## 题目翻译

### 题目描述

Farmer John 的农场布局非常独特，主田地的外围有一条环形道路，他的奶牛白天在这里吃草。每天早上，奶牛们都会穿过这条道路进入田地，每天晚上它们又会再次穿过这条道路离开田地返回牛棚。

众所周知，奶牛是习惯性动物，它们每天都会以相同的方式穿过道路。每头奶牛进入田地的点和离开田地的点不同，并且所有这些穿过点都彼此不同。Farmer John 拥有 $N$ 头奶牛，方便地用整数 ID $1 \ldots N$ 标识，因此道路周围恰好有 $2N$ 个穿过点。Farmer John 通过顺时针扫描环形道路，记录每个穿过点的奶牛 ID，最终形成一个包含 $2N$ 个数字的序列，其中每个数字恰好出现两次。他并未记录哪些穿过点是进入点，哪些是离开点。

看着他的穿过点地图，Farmer John 好奇一天中不同奶牛对之间可能会交叉多少次。如果奶牛 $a$ 从进入点到离开点的路径必须与奶牛 $b$ 从进入点到离开点的路径交叉，那么他称奶牛对 $(a,b)$ 为“交叉”对。请帮助 Farmer John 计算交叉对的总数。

### 输入格式

输入的第一行包含 $N$ ($1 \leq N \leq 50,000$)，接下来的 $2N$ 行描述了田地周围进入和离开点的奶牛 ID 序列。

### 输出格式

请输出交叉对的总数。


---

---
title: "将军令"
layout: "post"
diff: 提高+/省选-
pid: P3942
tag: ['动态规划 DP', '贪心', 'O2优化', '排序', '栈']
---
# 将军令
## 题目背景


> 历史/落在/赢家/之手  
> 至少/我们/拥有/传说  
> 谁说/败者/无法/不朽  
> 拳头/只能/让人/低头  
> 念头/却能/让人/抬头  
> 抬头/去看/去爱/去追  
> 你心中的梦
## 题目描述

又想起了四月。

如果不是省选，大家大概不会这么轻易地分道扬镳吧？  只见一个又一个昔日的队友离开了机房。

凭君莫话封侯事，一将功成万骨枯。


 
梦里，小 F 成了一个给将军送密信的信使。

现在，有两封关乎国家生死的密信需要送到前线大将军帐下，路途凶险，时间紧迫。小 F 不因为自己的祸福而避趋之，勇敢地承担了这个任务。

不过，小 F 实在是太粗心了，他一不小心把两封密信中的一封给弄掉了。

小 F 偷偷打开了剩下的那封密信。他 发现一副十分详细的地图，以及几句批文——原来 这是战场周围的情报地图。他仔细看后发现，在这张地图上标记了 n 个从 1 到 n 标号的 驿站，n − 1 条长度为 1 里的小道，每条小道双向连接两个不同的驿站，并且驿站之间可以 通过小道两两可达。

小 F 仔细辨认着上面的批注，突然明白了丢失的信的内容了。原来，每个驿站都可以驻 扎一个小队，每个小队可以控制距离不超过 k 里的驿站。如果有驿站没被控制，就容易产 生危险——因此这种情况应该完全避免。而那封丢失的密信里，就装着朝廷数学重臣留下的 精妙的排布方案，也就是用了最少的小队来控制所有驿站。

小 F 知道，如果能计算出最优方案的话，也许他就能够将功赎过，免于死罪。他找到了 你，你能帮帮他吗？  当然，小 F 在等待你的支援的过程中，也许已经从图上观察出了一些可能会比较有用的 性质，他会通过一种特殊的方式告诉你。

## 输入格式

从标准输入中读入数据。

输入第 1 行一个正整数 n,k,t，代表驿站数，一支小队能够控制的最远距离，以及特 殊性质所代表的编号。关于特殊性质请参照数据范围。

输入第 2 行至第 n 行，每行两个正整数 $u_i$,$v_i$，表示在 $u_i$ 和 $v_i$ 间，有一条长度为 一里的小道。

## 输出格式

输出到标准输出中。

输出一行，为最优方案下需要的小队数。

## 样例

### 样例输入 #1
```
4 1 0 
1 2 
1 3 
1 4
```
### 样例输出 #1
```
1 
 
```
### 样例输入 #2
```
6 1 0 
1 2 
1 3 
1 4 
4 5 
4 6
```
### 样例输出 #2
```
2 

```
## 提示

【样例 1 说明】

如图。由于一号节点到周围的点距离均是 1，因此可以控制所有驿站。

【样例 2 说明】

如图，和样例 1 类似。



 ![](https://cdn.luogu.com.cn/upload/pic/9813.png) 

子任务会给出部分测试数据的特点。如果你在解决题目中遇到了困难，可以尝试只解 决一部分测试数据。

关于 t 的含义如下： t = 0：该测试点没有额外的特殊性质；  t = 1：保证最多 8 个点的所连接的小道超过 1 条； t = 2：保证所有点到 1 号点的距离不超过 2。


每个测试点的数据规模及特点如下表

![](https://cdn.luogu.com.cn/upload/pic/9812.png)



---

---
title: "[TJOI2013] 黄金矿工"
layout: "post"
diff: 提高+/省选-
pid: P3961
tag: ['2013', '各省省选', '排序', '背包 DP', '图论建模', '天津']
---
# [TJOI2013] 黄金矿工
## 题目描述

小 A 最近迷上了在上课时玩《黄金矿工》这款游戏。为了避免被老师发现，他必须小心翼翼，因此他总是输。

在输掉自己所有的金币后，他向你求助。每个黄金可以看做一个点（没有体积）。现在给出你 $N$ 个黄金的坐标，挖到它们所需要的时间以及它们的价值。有些黄金在同一条直线上，这时候你必须按顺序挖。你可以瞬间把钩子转到任意角度。

小 A 一开始在坐标 $(0,0)$，请你帮助小 A 算出在时间 $T$ 内他最多可以得到多少价值的金子。
## 输入格式

第一行两个整数 $N$ 和 $T$，表示黄金的个数和总时间。

接下来 $N$ 行，每行四个整数 $x$、$y$、$t$、$v$，分别表示黄金的坐标，挖到这个黄金的时间，以及这个黄金的价值。
## 输出格式

一个整数,表示你可以在 $T$ 时间内得到的最大价值。
## 样例

### 样例输入 #1
```
3 10
1 1 1 1
2 2 2 2
1 3 15 9
```
### 样例输出 #1
```
3
```
### 样例输入 #2
```
3 10
1 1 13 1
2 2 2 2
1 3 4 7
```
### 样例输出 #2
```
7
```
## 提示

- 对于 $30\%$ 的数据，$0<T\le 4\times 10^3$；
- 对于 $100\%$ 的数据，$1\le N\le 200$，$0<T\le 4\times 10^4$。

保证 $0\le|x|\le 200$，$0<y≤200$，$0<t\le 200$，$0\le v\le 200$。


---

---
title: "[TJOI2014] 上升子序列"
layout: "post"
diff: 提高+/省选-
pid: P3970
tag: ['2014', '线段树', '各省省选', '树状数组', '排序', '天津']
---
# [TJOI2014] 上升子序列
## 题目描述

给定一个只包含整数的序列(序列元素的绝对值大小不超过10^9),你需要计算上升子序列的个数,满足如下条件的称之为一个上升子序列:

1. 是原序列的一个子序列

2. 长度至少为2

3. 所有元素都严格递增

如果两个上升子序列相同,那么只需要计算一次。例如:序列{1,2,3,3}有4个上升子序列,分别为{1,2}{1,3},{1,2,3},{2,3}

## 输入格式

输入的第一行是一个整数n,表示序列长度。接下来一行是n个整数,表示序列。

## 输出格式

输出仅包含一行,即原序列有多少个上升子序列。由于答案可能非常大,你只需要输出答案模10^9+7的余数。

## 样例

### 样例输入 #1
```
4
1 2 3 3
```
### 样例输出 #1
```
4
```
## 提示

### 数据范围

对于 30% 的数据，N ≤ 5000

对于 100% 的数据，N ≤ 10^5



---

---
title: "[HEOI2012] 采花"
layout: "post"
diff: 提高+/省选-
pid: P4113
tag: ['2012', '各省省选', '树状数组', '河北', '排序', '可持久化线段树', '前缀和']
---
# [HEOI2012] 采花
## 题目描述

萧薰儿是古国的公主，平时的一大爱好是采花。

今天天气晴朗，阳光明媚，公主清晨便去了皇宫中新建的花园采花。

花园足够大，容纳了 $n$ 朵花，共有 $c$ 种颜色，用整数 $1 \sim c$ 表示。且花是排成一排的，以便于公主采花。公主每次采花后会统计采到的花的颜色数，颜色数越多她会越高兴。同时，她有一癖好，她不允许最后自己采到的花中，某一颜色的花只有一朵。为此，公主每采一朵花，要么此前已采到此颜色的花，要么有相当正确的直觉告诉她，她必能再次采到此颜色的花。

由于时间关系，公主只能走过花园连续的一段进行采花，便让女仆福涵洁安排行程。福涵洁综合各种因素拟定了 $m$ 个行程，然后一一向你询问公主能采到的花共有几种不同的颜色。
## 输入格式

输入的第一行是三个用空格隔开的整数，分别代表花的个数 $n$，花的颜色数 $c$，以及行程数 $m$。

输入的第二行是 $n$ 个用空格隔开的整数，第 $i$ 个整数代表第 $i$ 朵花的颜色 $x_i$。

第 $3$ 行到第 $(m + 2)$ 行，每行两个整数 $l, r$，第 $(i + 2)$ 行的数字代表第 $i$ 次行程为第 $l$ 到第 $r$ 朵花。
## 输出格式

共输出 $m$ 行，每行一个整数。第 $i$ 行的整数代表第 $i$ 次行程公主能采到的花共有几种不同的颜色。
## 样例

### 样例输入 #1
```
5 3 5
1 2 2 3 1
1 5
1 2
2 2
2 3
3 5
```
### 样例输出 #1
```
2
0
0
1
0

```
## 提示

#### 输入输出样例 $1$ 解释

共有五朵花，颜色分别为 $1,~2,~2,~3,~1$。

对于第一次行程，公主采花的区间为 $[1, 5]$，可以采位置 $1,~2,~3,~5$ 处的花，共有 $1$ 和 $2$ 两种不同的颜色。

对于第二次行程，公主采花的区间为 $[1, 2]$，但是颜色为 $1$ 和 $2$ 的花都只出现了一次，因此公主无花可采。

对于第三次行程，公主采花的区间为 $[2, 2]$，但是颜色为 $2$ 的花只出现了一次，公主无花可采。

对于第四次行程，公主采花的区间为 $[2, 3]$，可以采 $2,~3$ 位置的花，只有 $2$ 这一种颜色。

对于第五次行程，公主采花的区间为 $[3,5]$，但是颜色为 $1, 2, 3$ 的花都只出现了一次，因此公主无花可采。

#### 数据范围与约定

**本题采用多测试点捆绑测试，共有两个子任务**。

对于子任务 $1$，分值为 $100$ 分，保证 $1 \leq n, c, m \leq 3 \times 10^5$。

对于子任务 $2$，分值为 $100$ 分，保证 $1 \leq n, c, m \leq 2 \times 10^6$。

对于全部的测试点，保证 $1 \leq x_i \leq c$，$1 \leq l \leq r \leq n$。


---

---
title: "[SCOI2015] 国旗计划"
layout: "post"
diff: 提高+/省选-
pid: P4155
tag: ['贪心', '2015', '四川', '倍增', '二分', '排序']
---
# [SCOI2015] 国旗计划
## 题目描述

A 国正在开展一项伟大的计划 —— 国旗计划。这项计划的内容是边防战士手举国旗环绕边境线奔袭一圈。这项计划需要多名边防战士以接力的形式共同完成，为此，国土安全局已经挑选了 $N$ 名优秀的边防战士作为这项计划的候选人。


A 国幅员辽阔，边境线上设有 $M$ 个边防站，顺时针编号 $1$ 至 $M$。每名边防战士常驻两个边防站，并且善于在这两个边防站之间长途奔袭，我们称这两个边防站之间的路程是这个边防战士的奔袭区间。$N$ 名边防战士都是精心挑选的，身体素质极佳，所以每名边防战士的奔袭区间都不会被其他边防战士的奔袭区间所包含。


现在，国土安全局局长希望知道，至少需要多少名边防战士，才能使得他们的奔袭区间覆盖全部的边境线，从而顺利地完成国旗计划。不仅如此，安全局局长还希望知道更详细的信息：对于每一名边防战士，在他必须参加国旗计划的前提下，至少需要多少名边防战士才能覆盖全部边境线，从而顺利地完成国旗计划。

## 输入格式

第一行，包含两个正整数 $N,M$，分别表示边防战士数量和边防站数量。


随后 $N$ 行，每行包含两个正整数。其中第 $i$ 行包含的两个正整数 $C_i$、$D_i$ 分别表示 $i$ 号边防战士常驻的两个边防站编号，$C_i$ 号边防站沿顺时针方向至 $D_i$ 号边防站力他的奔袭区间。数据保证整个边境线都是可被覆盖的。

## 输出格式

输出数据仅 $1$ 行，需要包含 $N$ 个正整数。其中，第 $j$ 个正整数表示 $j$ 号边防战士必须参加的前提下至少需要多少名边防战士才能顺利地完成国旗计划。

## 样例

### 样例输入 #1
```
4 8
2 5
4 7
6 1
7 3
```
### 样例输出 #1
```
3 3 4 3
```
## 提示

$N\leqslant 2×10^5,M<10^9,1\leqslant C_i,D_i\leqslant M$。



---

---
title: "可爱の#10数字划分"
layout: "post"
diff: 提高+/省选-
pid: P4257
tag: ['O2优化', '排序', '素数判断,质数,筛法', '概率论']
---
# 可爱の#10数字划分
## 题目背景

可可可可可可爱的付公主 qwq 有 $n$ 个数，$1\sim n$，每个数都有价值 $V_i$，你要将它们划分成若干个集合，每个数属于一个集合。
## 题目描述

我们这里规定:

1. 质数只能和质数分在同一个集合。  
2. 合数只能和合数分在同一个集合（$1$ 也算在合数内）。   
3. 我们假设目前所有质数集合的并集为 $U$（也就是之前所有质数集合以及 $S$ 的并集），每个质数集合 $S$ 的价值定义如下：  
$$V_S=\frac {(\sum_{i\in S}V_i)^p} {\prod_{i\in U}V_i}$$

4. 我们定义每个合数集合 $S$ 的价值如下:

令 $k=|S|$，我们用这 $k$ 个数分别作为 $k$ 条边的权值，连接 $k+1$ 个点，构成一棵树。对于一个排列 $P(1\sim k+1)$，价值为：

$$V_P=\sum_{i=1}^{n-1} f(P_i,P_{i+1})$$

其中 $f(u,v)$ 为路径 $(u,v)$ 上最大的边权。

集合 $S$ 的价值为：

$$V_S=E(\min\{V_P\})\times|S|$$

其中 $E(X)$ 代表 $X$ 的数学期望，期望是针对所有可能的有标号无根树，$\min$ 是针对所有可能的 $P$。这时集合内所有元素都不同，也就是所有边不同。

5. 一个划分方案的价值定义为所有集合的价值的乘积。
6. 两个划分方案相同当且仅当它们中所有集合对应相同，且质数集合的相对顺序相同。

现在给定 $n,p$ 和 $V_i$，请你求出所有合法的不同划分方案的价值之和。

结果对 $10^9+7$ 取模，除法请使用乘法逆元。
## 输入格式

第一行输入两个正整数 $n,p$。

第二行输入 $n$ 个正整数 $V_i$。
## 输出格式

共一行一个非负整数，代表答案对 $10^9+7$ 取模的结果。
## 样例

### 样例输入 #1
```
4 1
1 2 3 4

```
### 样例输出 #1
```
333333359
```
## 提示

### 样例解释

有以下 $6$ 种划分方案:

1. $(2,3)$ 和 $(1,4)$。$(2,3)$ 的价值为 ${\dfrac 5 6}$，$(1,4)$ 的价值为 $10$，总价值为 ${\dfrac {25} 3}$。
2. $(2),(3)$ 和 $(1,4)$。$(2)$ 的价值为 $1$，$(3)$ 的价值为 ${\dfrac 1 2}$，$(1,4)$ 的价值为 $10$，总价值为 $5$。
3. $(3),(2)$ 和 $(1,4)$。$(3)$ 的价值为 $1$，$(2)$ 的价值为 ${\dfrac 1 3}$，$(1,4)$ 的价值为 $10$，总价值为 ${\dfrac {10} 3}$。
4. $(2,3)$ 和 $(1),(4)$。$(2,3)$ 的价值为 ${\dfrac 5 6}$，$(1)$ 的价值为 $1$，$(4)$ 的价值为 $4$，总价值为 ${\dfrac {10} 3}$。
5. $(2),(3)$ 和 $(1),(4)$。$(2)$ 的价值为 $1$，$(3)$ 的价值为 ${\dfrac 1 2}$，$(1)$ 的价值为 $1$，$(4)$ 的价值为 $4$，总价值为 $2$。
6. $(3),(2)$ 和 $(1),(4)$。$(3)$ 的价值为 $1$，$(2)$ 的价值为 ${\dfrac 1 3}$，$(1)$ 的价值为 $1$，$(4)$ 的价值为 $4$，总价值为 ${\dfrac 4 3}$。

因此所有划分方案的价值和为${\dfrac {70} 3}$。对 $10^9+7$ 取模后结果为 $333333359$。

### 数据范围

对于 $100\%$ 的数据，满足 $1\le n\le 70$，$1\le V_i\le 10^{12}$。

下表中给出了每个测试点具体的数据范围，都表示小于等于。为了防止卡 OJ，所以本题数据组数进行压缩，分值改变，具体参照表格。

| 数据编号 |  n   |  p   |  Vi   | 测试点分值 | 时限 |
| :------: | :--: | :--: | :---: | :--------: | :--: |
|    1     |  10  |  1   |  100  |     10     |  1s  |
|    2     |  20  |  1   | 1000  |     10     |  1s  |
|    3     |  30  |  1   | 10000 |     10     |  1s  |
|    4     |  40  | 1e9  | 1e12  |     10     |  1s  |
|    5     |  50  |  1   | 1e12  |     5      |  1s  |
|    6     |  50  | 1e9  | 1e12  |     5      |  1s  |
|    7     |  60  |  1   | 1e12  |     5      |  2s  |
|    8     |  60  | 1e9  | 1e12  |     5      |  2s  |
|    9     |  70  | 1e9  | 1e12  |     20     |  10s  |
|    10    |  70  | 1e9  | 1e12  |     20     |  5s  |

提示：大家不要太过相信自己的常数，尽量做好常数优化。


---

---
title: "[USACO18OPEN] Out of Sorts G"
layout: "post"
diff: 提高+/省选-
pid: P4375
tag: ['2018', 'USACO', '树状数组', '离散化', '排序']
---
# [USACO18OPEN] Out of Sorts G
## 题目描述

留意着农场之外的长期职业生涯的可能性，奶牛 Bessie 开始在不同的在线编程网站上学习算法。

她到目前为止最喜欢的算法是“冒泡排序”。以下是 Bessie 最初的对长度为 $N$ 的数组 $A$ 进行排序的代码实现：

```
sorted = false
while (not sorted):
   sorted = true
   moo
   for i = 0 to N-2:
      if A[i+1] < A[i]:
         swap A[i], A[i+1]
         sorted = false
```

显然，代码中的 `moo` 指令的作用只是输出“moo”。奇怪的是，Bessie 似乎执着于在她的代码中的不同位置使用这个语句。

在用若干个数组测试了她的代码之后，Bessie 观察到一个有趣的现象：大的元素很快就会被拉到数组末尾，而小的元素需要很长时间“冒泡”到数组的开头（她怀疑这就是这个算法得名的原因）。为了实验和缓解这一问题，Bessie 修改了她的代码，使代码在每次循环中向前再向后各扫描一次，从而无论是大的元素还是小的元素在每一次循环中都有机会被拉较长的一段距离。她的代码现在是这样的：

```
sorted = false
while (not sorted):
   sorted = true
   moo
   for i = 0 to N-2:
      if A[i+1] < A[i]:
         swap A[i], A[i+1]
   for i = N-2 downto 0:
      if A[i+1] < A[i]:
         swap A[i], A[i+1]
   for i = 0 to N-2:
      if A[i+1] < A[i]:
         sorted = false
```

给定一个输入数组，请预测 Bessie 修改后的代码会输出多少次“moo”。

## 输入格式

输入的第一行包含 $N$（$1 \leq N \leq 100,000$）。接下来的 $N$ 行描述了 $A[0] \ldots A[N-1]$，每个数都是一个范围在 $0 \ldots 10^9$ 的整数。输入数据不保证各不相同。
## 输出格式

输出“moo”被输出的次数。
## 样例

### 样例输入 #1
```
5
1
8
5
3
2
```
### 样例输出 #1
```
2
```
## 提示

供题：Brian Dean


---

---
title: "[USACO18OPEN] Milking Order G"
layout: "post"
diff: 提高+/省选-
pid: P4376
tag: ['2018', '二分', 'USACO', '图论建模', '拓扑排序']
---
# [USACO18OPEN] Milking Order G
## 题目描述

Farmer John 的 $N$ 头奶牛（$1 \leq N \leq 10^5$），编号为 $1 \ldots N$，最近闲得发慌。因此，她们发展了一个与 Farmer John 每天早上为她们挤牛奶时的排队顺序相关的复杂社会阶层。

经过若干周的研究，Farmer John 对他的奶牛的社会结构总计进行了 $M$ 次观察（$1 \leq M \leq 50,000$）。每个观察结果都是某些奶牛的一个有序序列，表示这些奶牛应该按照序列中的顺序进行挤奶。例如，如果 Farmer John 的一次观察结果是序列 $2$、$5$、$1$，那么 Farmer John 应该在给奶牛 $5$ 挤奶之前的某个时刻给奶牛 $2$ 挤奶，并在给奶牛 $1$ 挤奶之前的某个时刻给奶牛 $5$ 挤奶。

Farmer John 的观察结果是按优先级排列的，因此他的目标是最大化 $X$ 的值，使得他的挤奶顺序能够符合前 $X$ 个观察结果描述的状态。当多种挤奶顺序都能符合前 $X$ 个状态时，Farmer John 遵循一个长期以来的传统——编号较小的奶牛的地位高于编号较大的奶牛，因此他会最先给编号最小的奶牛挤奶。更正式地说，如果有多个挤奶顺序符合这些状态，Farmer John 会采用字典序最小的那一个。挤奶顺序 $x$ 的字典序比挤奶顺序 $y$ 小，如果对于某个 $j$，$x_i = y_i$ 对所有 $i < j$ 成立，并且 $x_j < y_j$（即这两个挤奶顺序到某个位置之前完全相同，而在该位置上 $x$ 比 $y$ 小）。

请帮助 Farmer John 确定给奶牛挤奶的最佳顺序。
## 输入格式

第一行包含 $N$ 和 $M$。接下来的 $M$ 行，每行描述了一个观察结果。第 $i+1$ 行描述了观察结果 $i$，第一个数是观察结果中的奶牛数量 $m_i$，后面是一列 $m_i$ 个整数，给出这次观察中奶牛的顺序。所有 $m_i$ 的总和至多为 $200,000$。
## 输出格式

输出 $N$ 个空格分隔的整数，表示一个 $1 \ldots N$ 的排列，为 Farmer John 给他的奶牛们挤奶应该采用的顺序。
## 样例

### 样例输入 #1
```
4 3
3 1 2 3
2 4 2
3 3 4 1
```
### 样例输出 #1
```
1 4 2 3

```
## 提示

在这个例子中，Farmer John 有四头奶牛，他的挤奶顺序应该满足以下规则：奶牛 $1$ 在奶牛 $2$ 之前、奶牛 $2$ 在奶牛 $3$ 之前（第一个观察结果），奶牛 $4$ 在奶牛 $2$ 之前（第二个观察结果），奶牛 $3$ 在奶牛 $4$ 之前、奶牛 $4$ 在奶牛 $1$ 之前（第三个观察结果）。前两个观察结果可以同时被满足，但 Farmer John 不能同时满足所有规则，因为这会要求奶牛 $1$ 在奶牛 $3$ 之前，同时奶牛 $3$ 在奶牛 $1$ 之前。

这意味着总共有两种可能的挤奶顺序：$1\ 4\ 2\ 3$ 和 $4\ 1\ 2\ 3$，第一种是字典序较小的。

题目来源：Jay Leeds


---

---
title: "选举"
layout: "post"
diff: 提高+/省选-
pid: P4394
tag: ['贪心', '排序', '背包 DP']
---
# 选举
## 题目描述

Byteland 国的居民最近一直为议会选举投票。现在，当结果公布的时候，党派不得不决定联合组建政府。 

每个党派都会获得议会中的一定席位。联合政府由这些党派中的一部分组成，他们在议会中的席位数之和**严格大于**总席位数的一半。对于联合政府来说，席位越多越好。

一个**过剩**的联合政府是指联合政府中的一个党派被移出后，剩余的联合政府在国会中仍有过半数的席位。

请写一个程序能够找到一个在议会中有着**最大可能席位数**且**不过剩**的联合政府。
## 输入格式

标准输出的第一行包含一个整数 $n$，表示参加选举的党派数。党派被从 $1$ 到 $n$ 编号。

第二行包含 $n$ 个非负整数 $a_1,\dots ,a_n$，被一个空格隔开，$a_i$ 是第 $i$ 个党派获得的席位数。你可以假设国会中的中的总席位数为小于等于 $10^5$ 的正整数。
## 输出格式

包含一个整数，表示最大可能席位数。
## 样例

### 样例输入 #1
```
4
1 3 2 4
```
### 样例输出 #1
```
7
```
## 提示

样例解释：选择第二个政党和第四个。

对于全部数据，$1\le n\le 300$。


---

---
title: "[USACO05DEC] Cleaning Shifts S"
layout: "post"
diff: 提高+/省选-
pid: P4644
tag: ['动态规划 DP', '递推', '2005', '线段树', 'USACO', '排序', '队列']
---
# [USACO05DEC] Cleaning Shifts S
## 题目描述

约翰的奶牛们从小娇生惯养，她们无法容忍牛棚里的任何脏东西。约翰发现，如果要使这群有洁癖的奶牛满意，他不得不雇佣她们中的一些来清扫牛棚，约翰的奶牛中有 $ N(1 \leq N \leq 10000) $ 头愿意通过清扫牛棚来挣一些零花钱。

由于在某个时段中奶牛们会在牛棚里随时随地地乱扔垃圾，自然地，她们要求在这段时间里，无论什么时候至少要有一头奶牛正在打扫。需要打扫的时段从某一天的第 $ M $ 秒开始，到第 $ E $ 秒结束 $ (0 \leq M \leq E \leq 86399) $。注意这里的秒是指时间段而不是时间点，也就是说，每天需要打扫的总时间是 $ E-M+1 $ 秒。

约翰已经从每头牛那里得到了她们愿意接受的工作计划：对于某一头牛，她每天都愿意在笫 $ T_1 \ldots T_2 $ 秒的时间段内工作 $ (M \leq T_1 \leq T_2 \leq E) $ ，所要求的报酬是 $ S $ 美元 $ (0 \leq S \leq 500000) $。与需打扫时段的描述一样，如果一头奶牛愿意工作的时段是每天的第 $ 10 \ldots 20 $ 秒，那她总共工作的时间是 $ 11 $ 秒，而不是 $ 10 $ 秒。

约翰一旦决定雇佣某一头奶牛，就必须付给她全额的工资，而不能只让她工作一段时间，然后再按这段时间在她愿意工作的总时间中所占的百分比来决定她的工资。现在请你帮约翰决定该雇佣哪些奶牛以保持牛棚的清洁，当然，在能让奶牛们满意的前提下，约翰希望使总花费尽量小。
## 输入格式

第 $ 1 $ 行： $ 3 $ 个正整数 $ N,M,E $ 。

第 $ 2 $ 到 $ N+1 $ 行：第 $ i+1 $ 行给出了编号为 $ i $ 的奶牛的工作计划，即 $ 3 $ 个正整数 $ T_1,T_2,S $ 。
## 输出格式

输出一个整数，表示约翰需要为牛棚清理工作支付的最少费用。如果清理工作不可能完成，那么输出 $ -1 $ 。
## 样例

### 样例输入 #1
```
3 0 4
0 2 3
3 4 2
0 0 1
```
### 样例输出 #1
```
5
```
## 提示

约翰有 $ 3 $ 头牛，牛棚在第 $ 0 $ 秒到第 $ 4 $ 秒之间需要打扫。 约翰雇佣前两头牛清扫牛棚，可以只花 $ 5 $ 美元就完成一整天的清扫。



---

---
title: "[Wind Festival] Running In The Sky"
layout: "post"
diff: 提高+/省选-
pid: P4742
tag: ['图论建模', '拓扑排序', '强连通分量']
---
# [Wind Festival] Running In The Sky
## 题目背景

$[Night - 20:02$ $P.M.]$

夜空真美啊……但是……快要结束了呢……
## 题目描述

一天的活动过后，所有学生都停下来欣赏夜空下点亮的风筝。$Curtis$ $Nishikino$想要以更近的视角感受一下，所以她跑到空中的风筝上去了(这对于一个妹子来说有点匪夷所思)! 每只风筝上的灯光都有一个亮度 $k_i$. 由于风的作用，一些风筝缠在了一起。但是这并不会破坏美妙的气氛，缠在一起的风筝会将灯光汇聚起来，形成更亮的光源！

$Curtis$ $Nishikino$已经知道了一些风筝间的关系，比如给出一对风筝$(a,b)$, 这意味着她可以从 $a$ 跑到 $b$ 上去，但是不能返回。

现在，请帮她找到一条路径(她可以到达一只风筝多次，但只在第一次到达时她会去感受上面的灯光), 使得她可以感受到最多的光亮。同时请告诉她这条路径上单只风筝的最大亮度，如果有多条符合条件的路径，输出能产生最大单只风筝亮度的答案。
## 输入格式

第一行两个整数 $n$ 和 $m$. $n$ 是风筝的数量, $m$ 是风筝间关系对的数量. 

接下来一行 $n$ 个整数 $k_i$.

接下来 $m$ 行, 每行两个整数 $a$ 和 $b$, 即$Curtis$可以从 $a$ 跑到 $b$.
## 输出格式

一行两个整数。$Curtis$在计算出的路径上感受到的亮度和，这条路径上的单只风筝最大亮度.
## 样例

### 样例输入 #1
```
5 5
8 9 11 6 7
1 2
2 3
2 4
4 5
5 2
```
### 样例输出 #1
```
41 11
```
## 提示

对于 $20\%$ 的数据, $0<n \le 5\times10^3, \ 0 < m \le 10^4$.

对于 $80\%$ 的数据, $0 < n \le 10^5, \ 0 < m \le 3\times10^5$.

对于 $100\%$ 的数据, $0<n\le2\times10^5,\ 0<m\le5\times10^5,\ 0<k\le200$.



---

---
title: "[CCO 2015] 饥饿的狐狸"
layout: "post"
diff: 提高+/省选-
pid: P4801
tag: ['贪心', '2015', '枚举', '排序', 'CCO（加拿大）']
---
# [CCO 2015] 饥饿的狐狸
## 题目描述

**本题译自 [CCO 2015](https://cemc.math.uwaterloo.ca/contests/computing/past_ccc_contests/2015/index.html) Day1 T1「[Hungry Fox](https://cemc.math.uwaterloo.ca/contests/computing/past_ccc_contests/2015/stage%202/day1.pdf)」**

到你的宠物狐狸的晚餐时间啦！他的晚餐包含 $N$ 块饼干，第 $i$ 块饼干的温度是 $T_i$ 摄氏度。同时，在晚餐中还包含了一大盘 $W$ 摄氏度的水。

在喝了一口水之后，你的狐狸开始吃饭了。每当他吃一块饼干时，这块饼干的美味度为当前饼干与吃/喝的前一样食物（包括饼干和水）的温度的差的绝对值。它可以在任意时间喝水（保证水喝不完），或按任意顺序吃饼干。

最后狐狸获得的美味值为它吃下的每块饼干的美味度之和。请求出狐狸获得的最小和最大的美味值。
## 输入格式

第一行两个整数 $N,W$，表示饼干总数和水的温度。  

接下来 $N$ 行，每行一个整数 $T_i(1\le i\le N)$ 表示第 $i$ 块饼干的温度。
## 输出格式

输出两个整数，分别为狐狸获得的最小和最大的美味值。
## 样例

### 样例输入 #1
```
3 20
18
25
18
```
### 样例输出 #1
```
7 16
```
## 提示

要得到最小美味值，一种可行的方案是，狐狸先喝水，然后吃第一块饼干，再吃第三块饼干，接着喝水，最后吃下第二块饼干，这样做，它所感受到的温度分别为 $20,18,18,20,25$ 摄氏度，总的美味度为 $2+0+5=7$。

要得到最大美味值，一种可行的方案是，狐狸先喝水，然后按顺序吃饼干，它所感受到的温度分别为 $20,18,25,18$ 摄氏度，总的美味度为 $2+7+7=16$。

对于 $30\%$ 及以上的数据， $W=0$；  

对于 $100\%$ 的数据， $1\le N \le 100000, 0\le W \le 10^9, 0 \le T _ i \le 10 ^ 9$。


---

---
title: "[TJOI2013] 拯救小矮人"
layout: "post"
diff: 提高+/省选-
pid: P4823
tag: ['贪心', '2013', '排序', '背包 DP', '天津']
---
# [TJOI2013] 拯救小矮人
## 题目描述

一群小矮人掉进了一个很深的陷阱里，由于太矮爬不上来，于是他们决定搭一个人梯。即：一个小矮人站在另一小矮人的 肩膀上，直到最顶端的小矮人伸直胳膊可以碰到陷阱口。

对于每一个小矮人，我们知道他从脚到肩膀的高度 $A_i$，并且他的胳膊长度为 $B_i$。陷阱深度为 $H$。

如果我们利用矮人 $1$，矮人 $2$，矮人 $3$，……，矮人 $k$ 搭一个梯子，满足 $A_1+A_2+A_3+\dots+A_k+B_k \geq H$，那么矮人 $k$ 就可以离开陷阱逃跑了，一旦一个矮人逃跑了，他就不能再搭人梯了。  

我们希望尽可能多的小矮人逃跑，问最多可以使多少个小矮人逃跑。
## 输入格式

第一行一个整数 $N$，表示矮人的个数，接下来 $N$ 行每一行两个整数 $A_i$ 和 $B_i$，最后一行是 $H$。
## 输出格式

一个整数表示最多可以逃跑多少小矮人。
## 样例

### 样例输入 #1
```
2
20 10
5 5
30
```
### 样例输出 #1
```
2
```
### 样例输入 #2
```
2
20 10
5 5
35
```
### 样例输出 #2
```
1
```
## 提示

对于 $30\%$ 的数据，$N\leq 200$；  

对于 $100\%$ 的数据，$1 \leq N\leq 2000$，$1 \leq A_i,B_i,H\leq10^5$。


---

---
title: "kry loves 2048"
layout: "post"
diff: 提高+/省选-
pid: P4829
tag: ['排序', '队列', '洛谷月赛']
---
# kry loves 2048
## 题目背景

kls是一个人赢。
## 题目描述

kls最近在玩一款类似2048的游戏，规则是这样的：

一开始，有$n$个方块，每个方块上有一个$1$到$m$的整数。

kls可以进行两种操作：

1. 选择两个数字相同的方块（不一定要相邻），将它们合并成一个数字为原来的两倍的方块；

2. 减小一个方块上的数字。

操作的次数没有限制，最终的得分为所有方块上的最大的数字。

因为kls要去陪妹子了，没有时间继续玩，他想让你帮忙计算一下，最多能得到多少分。
## 输入格式

因为数据可能很大，读入容易超时，所以kls给你们提供了一个c++的随机数生成器。

```cpp
void generate_array(int a[], int n, int m, int seed) {
    unsigned x = seed;
    for (int i = 0; i < n; ++i) {
        x ^= x << 13;
        x ^= x >> 17;
        x ^= x << 5;
        a[i] = x % m + 1;
    }
}
```

把这个函数复制到你的程序里。用一个足够大的数组，以及输入数据给出的$n$，$m$和$seed$作为参数，调用这个函数。然后这个数组里就是一开始的方块上的数字（下标从0开始）。

输入一行三个数$n,m,seed$，含义如上。
## 输出格式

一行一个数，表示最大得分。
## 样例

### 样例输入 #1
```
5 10 233
```
### 样例输出 #1
```
24
```
### 样例输入 #2
```
5 50 3
```
### 样例输出 #2
```
48
```
### 样例输入 #3
```
1000 1000 666
```
### 样例输出 #3
```
374784
```
## 提示

### 样例解释

样例1生成出来的数是 6 10 7 5 4。

样例2生成出来的数是 8 12 48 4 4。

### 数据范围

对于30%的数据，$n, m \le 10$；

对于60%的数据，$n, m \le 10^5$；

对于100%的数据，$n, m \le 10^7$，$1 \le seed \le 10^9$。


---

---
title: "最后的战役"
layout: "post"
diff: 提高+/省选-
pid: P4945
tag: ['动态规划 DP', '贪心', '离散化', '排序']
---
# 最后的战役
## 题目背景

NOIP2018原创模拟题T5

NOIP2018原创模拟赛DAY2 T1

NOIP T1+ or T2-  难度

题目背景改编自小说《哈利波特与死亡圣器》
## 题目描述

**最后的战役打响了。**

哈利被宣告“死亡”，伏地魔带着他的部下准备进攻霍格沃茨。但是霍格沃茨有古老的魔法保护，他们必须先摧毁这些保护。魔法保护一共有$n$层，每一层保护有两个参数：$k,p$。其中k表示魔法的类型，p表示能量的大小。

伏地魔每秒都会穿过一层保护，他在第 $i$ 秒（到达了第 $i$ 层）他有以下选择：  


1.收集 $[1,i]$ 层魔法中魔法类型为 $x_i$ 的魔法能量

2.收集 $[1,i]$ 层中魔法能量最大那层的魔法能量

3.使用加倍魔法

对于上面三个选择，他每秒可以可以选择一个，并可能获得能量，对于不同的选择，获得的能量也不同：

对于1.获得$[1,i]$层中**所有魔法类型为$x_i$的**魔法能量（请结合样例1理解）

对于2.获得$[1,i]$中魔法能量最大的那一层的魔法能量

对于3.这一秒总共收集的能量不变（也就是这一秒不收集新的能量），但是下一秒获得的能量翻倍。**但是他不能连续使用加倍魔法**，而且他最多只能使用$m$次，**对于每一层的能量他都可以重复获取**

只有他通过了这$n$层保护，并获得了最大的魔法能量才有可能彻底摧毁霍格沃茨的魔法防御，可是巫师又是不擅长计算的。

于是，伏地魔找到了你，而你，作为精通计算机技术的麻瓜程序员，现在需要做的就是设计一个程序帮助伏地魔计算出他可以获得的最大的魔法能量的值。

最终的决战已经展开，魔法界的历史又翻过了一页……
## 输入格式

第一行：两个数：$n,m$，意义见题目描述

接下来$n$行，第$i+1$行表示$k_i,p_i$，意义见题目描述

最后一行，共$n$个数，第$i$个数表示$x_i$，意义见题目描述
## 输出格式

一个数，表示伏地魔可以获得的最大能量值
## 样例

### 样例输入 #1
```
4 1
1 2
2 3
1 2
3 8
3 2 1 3
```
### 样例输出 #1
```
21
```
### 样例输入 #2
```
8 3
1 2
2 5
3 2
2 3
1 4
1 6
2 2
3 3
1 3 2 1 4 5 2 1
```
### 样例输出 #2
```
57
```
### 样例输入 #3
```
10 3
9 9
8 8
5 7
6 6
5 5
5 5
3 3
2 2
1 1
9 9
1 2 3 5 5 5 6 7 8 9
```
### 样例输出 #3
```
124
```
## 提示

**样例一解释：**

第一秒最多可以获得2经验值，第二秒最多可以获得3经验值，**因为第三秒可以收集魔法类型为1的能量，所以最多可以获得4能量值**，第四秒最多可以获得8经验值，所以选择在第三秒使用加倍魔法，共可以获得：$2+3+0+2*8=21$能量值

**数据范围：**

30%数据满足：$n<=100,m<=10$

50%数据满足：$n<=5,000,m<=20$

70%数据满足：$n,m<=2\times 10^4,m<=200$

100%数据满足：$n<=5\times 10^4,m<=500,0<p_i<=10^4,0<k_i<=10^9,0<x_i<=10^9$

**特殊约定：**

30%数据满足$m=0$


---

---
title: "[yLOI2019] 梅深不见冬"
layout: "post"
diff: 提高+/省选-
pid: P5521
tag: ['贪心', '2019', 'O2优化', '排序', '深度优先搜索 DFS']
---
# [yLOI2019] 梅深不见冬
## 题目背景

> 风，吹起梅岭的深冬；霜，如惊涛一样汹涌；  
> 雪，飘落后把所有烧成空，像这场，捕捉不到的梦。   
> 醒来时已是多年之久，宫门铜环才长了铁锈，也开始生出离愁。

——银临《梅深不见冬》
## 题目描述

扶苏从深冬的梅岭走出，来到了一棵有 $n$ 个节点的有根树上。

如果你不知道什么是树，可以认为树是一个边数恰好比节点个数少一的简单无向连通图。

如果我们规定 $x$ 是树 $T$ 的根，那么定义任意一个节点 $y$ 到根的路径就是从 $y$ 出发不重复经过节点到达 $x$ 所经过的所经过的点构成的点集。可以证明这样的点集有且仅有一个。

定义一个节点 $u$ 是节点 $v$ 的孩子，当且仅当 $u$ 与 $v$ 相连且 $u$ 不在 $v$ 到根的路径中。如果 $u$ 是 $v$ 的孩子，那么定义 $v$ 是 $u$ 的家长节点。

如果我是 @[\_rqy](https://www.luogu.org/space/show?uid=7868) 那种~~毒瘤~~神仙的话，可能会问你每个节点的孩子数不超过 $k$ 的 $n$ 个节点的带标号无根树一共有多少个，可惜这个问题我也不会，所以我不会问你这么毒瘤的问题。

扶苏从这棵 $n$ 个节点的树的 $1$ 号节点出发，沿着树上的边行走。当然我们规定 $1$ 号节点是这棵树的根。他所行走的规定是：当扶苏在节点 $u$ 时，扶苏要么在 $u$ 的孩子中选择一个**没有到达过**的节点 $v$ 并行走到 $v$，要么选择回到 $u$ 的家长节点。

现在给每个节点一个权值 $w$，其中 $i$ 号节点的权值为 $w_i$。他想给这棵树的某个节点放上从梅岭带出的梅花。我们规定扶苏能在节点 $u$ 放上梅花当且仅当满足如下条件：

> 扶苏当前在节点 $u$。
>
> 对于 $u$ 的所有孩子 $v$，节点 $v$ 被放上了 $w_v$ 朵梅花。

同时，扶苏可以在**任意时刻**收回**任意节点**上的梅花，在收回梅花时不需要走到对应节点。

现在扶苏想问问你，对于每个节点，如果他想在 $i$ 号节点上放 $w_i$ 朵梅花，那么他最少要从梅岭带出多少朵梅花。
## 输入格式

每个输入文件中都有且仅有一组测试数据。

数据的第一行是一个整数 $n$ 代表树的节点个数。

第二行有 $n-1$ 个用空格隔开的整数，第 $i$ 个整数 $p_i$ 代表第 $i+1$ 号节点的家长节点编号。

第三行有 $n$ 个用空格隔开的整数，第 $i$ 个整数代表 $w_i$。
## 输出格式

输出一行 $n$ 个用空格隔开的整数，第 $i$ 个整数代表想在 $i$ 号节点上放 $w_i$ 朵梅花需要准备的梅花个数。
## 样例

### 样例输入 #1
```
3 
1 2 
1 1 1
```
### 样例输出 #1
```
2 2 1
```
### 样例输入 #2
```
3
1 1
1 1 1
```
### 样例输出 #2
```
3 1 1
```
### 样例输入 #3
```
6
1 1 2 3 4
3 14 1 5 12 15
```
### 样例输出 #3
```
21 20 13 20 12 15
```
## 提示

#### 输入输出样例 1 解释

![qwq](https://cdn.luogu.com.cn/upload/pic/72286.png)

样例 1 的输入如上图，每个节点都需要放 $1$ 一朵梅花。

如果在 1 号节点放梅花，则从一号点运动到 2 号点，然后运动到 3 号点，在 3 号点上放一朵梅花，返回 2 号点，在 2 号点上放一朵梅花，同时收回三号点的梅花，然后返回 1 号点，将从 3 号点收回的梅花放到 1 号点即可。一共需要两朵梅花。

在 2、3 号节点放梅花的方案类似。

#### 输入输出样例 3 解释

![qwq](https://cdn.luogu.com.cn/upload/pic/72287.png)

样例 3 的输入如左图。

先从 1 号节点运动至 3 号节点，再运动至 5 号节点，在 5 号节点上放置 $12$ 朵梅花，然后返回 3 号节点，在 3 号节点上放置 $1$ 朵梅花，收回五号节点的 $12$ 朵梅花，返回 1 号节点。

然后运动到 2 号节点，通过 4 号节点运动到 6 号节点，放下 $15$ 朵梅花，返回 4 号节点放下 $5$ 朵梅花，此时树上有的梅花数为 $5 + 15 + 1 = 21$，分别在 4 号、6 号和 3 号节点上。然后收回 6 号节点的梅花，返回 2 号节点，放下 $14$ 朵梅花，收回 4 号节点的，返回 1 号节点，在 1 号节点上放置 $3$ 朵梅花，即可达到在 1 号节点上放梅花的目的。

可以验证最大花费为 $21$。其他节点的答案同理。

请注意，其他节点的答案不一定是按照该节点的运动路径行走得到的。

---

#### 数据规模与约定

| 测试点编号 |  $n = $  | 测试点编号 |  $n = $  |
| :--------: | :------: | :--------: | :------: |
|     1      |   $1$    |     11     | $100003$ |
|     2      |   $8$    |     12     | $100003$ |
|     3      |   $8$    |     13     | $100003$ |
|     4      |   $8$    |     14     | $100003$ |
|     5      |   $8$    |     15     | $100004$ |
|     6      | $100000$ |     16     | $100004$ |
|     7      | $100000$ |     17     | $100004$ |
|     8      | $100002$ |     18     | $100004$ |
|     9      | $100002$ |     19     | $100004$ |
|     10     | $100002$ |     20     | $100004$ |

- 对于测试点 5、6，满足特殊性质：每个节点的孩子结点个数不超过 $2$。
- 对于测试点 8 到测试点 10，满足特殊性质：每个节点的孩子节点个数不超过 $5$。
- 对于测试点 11 到测试点 14，满足特殊性质：任意一个节点到根的路径上的点数不超过 $3$，也即树高不超过 $3$。
- 对于 $100\%$ 的数据，保证 $1 \leq n \leq 10^5 + 4,~1 \leq p_i \leq i,~1 \leq w_i \leq 1000$。

---

#### 提示

- $n$ 的末位数字可以帮助你快速的判断测试点所具有的的特殊性质。


---

---
title: "[GZOI2017] 配对统计"
layout: "post"
diff: 提高+/省选-
pid: P5677
tag: ['2017', '各省省选', '树状数组', 'O2优化', '排序', '贵州']
---
# [GZOI2017] 配对统计
## 题目背景

GZOI2017 D1T3
## 题目描述

给定 $n$ 个数 $a_1,\cdots,a_n$。

对于一组配对 $(x,y)$，若对于所有的 $i=1,2,\cdots,n$，满足 $|a_x-a_y|\le|a_x-a_i|(i\not=x)$，则称 $(x,y)$ 为一组好的配对（$|x|$ 表示 $x$ 的绝对值）。

给出若干询问，每次询问区间 $[l,r]$ 中含有多少组好的配对。

即，取 $x,y$（$l\le x,y\le r$ 且 $x\not=y$），问有多少组 $(x,y)$ 是好的配对。
## 输入格式

第一行两个正整数 $n,m$。

第二行 $n$ 个数 $a_1,\cdots,a_n$。

接下来 $m$ 行，每行给出两个数 $l,r$。
## 输出格式

$Ans_i$ 表示第 $i$ 次询问的答案，输出 $\sum_{i=1}^m\limits Ans_i\times i$ 即可。
## 样例

### 样例输入 #1
```
3 2
2 1 3
1 2
1 3
```
### 样例输出 #1
```
10
```
## 提示

**【样例解释】**

第一次询问好的配对有：$(1,2)(2,1)$；

第二次询问好的配对有：$(1,2)(2,1),(1,3)(3,1)$；

答案 $=2\times 1+4\times 2=10$。

**【数据约束】**

![](https://cdn.luogu.com.cn/upload/image_hosting/32ms79n8.png)


---

---
title: "[USACO19DEC] Meetings S"
layout: "post"
diff: 提高+/省选-
pid: P5835
tag: ['2019', '二分', 'USACO', '排序', '队列']
---
# [USACO19DEC] Meetings S
## 题目描述

有两个牛棚位于一维数轴上的点 $0$ 和 $L$ 处（$1 \leq L \leq 10^9$）。同时有 $N$ 头奶牛（$1 \leq N \leq 5 \times 10^4$）位于数轴上不同的位置（将牛棚和奶牛看作点）。每头奶牛 $i$ 初始时位于某个位置 $x_i$，并朝着正向或负向以一个单位每秒的速度移动，用一个等于 $1$ 或 $-1$ 的整数 $d_i$ 表示。每头奶牛还拥有一个在范围 $[1,10^3]$ 内的重量。所有奶牛始终以恒定的速度移动，直到以下事件之一发生：
- 如果奶牛 $i$ 移动到了一个牛棚，则奶牛 $i$ 停止移动。
- 当奶牛 $i$ 和 $j$ 占据了相同的点的时候，并且这一点不是一个牛棚，则发生了相遇。此时，奶牛 $i$ 被赋予奶牛 $j$ 先前的速度，反之亦然。注意奶牛可能在一个非整数点相遇。

令 $T$ 等于停止移动的奶牛（由于到达两个牛棚之一）的重量之和至少等于所有奶牛的重量之和的一半的最早时刻。请求出在时刻 $0 \ldots T$（包括时刻 $T$）之间发生的奶牛对相遇的总数。

## 输入格式

输入的第一行包含两个空格分隔的整数 $N$ 和 $L$。

以下 $N$ 行，每行包含三个空格分隔的整数 $w_i$，$x_i$ 以及 $d_i$。所有的位置 $x_i$ 各不相同，并且满足 $0<x_i<L$。
## 输出格式

输出一行，包含答案。
## 样例

### 样例输入 #1
```
3 5
1 1 1
2 2 -1
3 3 -1
```
### 样例输出 #1
```
2
```
## 提示

### 样例解释

在这个例子中，奶牛们按如下方式移动：

1. 第一和第二头奶牛于时刻 0.5 在位置 1.5 相遇。此时第一头奶牛拥有速度 -1，第二头奶牛拥有速度 1。
2. 第二和第三头奶牛于时刻 1 在位置 2 相遇。此时第二头奶牛拥有速度 −1，第三头奶牛拥有速度 1。
3. 第一头奶牛于时刻 2 到达左边的牛棚。
4. 第二头奶牛于时刻 3 到达左边的牛棚。
5. 由于到达牛棚的奶牛的总重量已经至少是所有奶牛的总重量的一半，这个过程此时终止。如果继续进行下去，第三头奶牛将会在时刻 4 到达右边的牛棚。

发生了恰好两次相遇。 

### 子任务

测试点 $2\sim 4$ 满足 $N\le 10^2$，并且对所有 $i$，$w_i=1$。

测试点 $5\sim 7$ 满足 $N\le 10^2$。

供题：Benjamin Qi


---

---
title: "[USACO20OPEN] The Moo Particle S"
layout: "post"
diff: 提高+/省选-
pid: P6283
tag: ['2020', 'USACO', '并查集', '排序']
---
# [USACO20OPEN] The Moo Particle S
## 题目描述

FJ 的奶牛们最近很无聊，她们想到了一种全新的方式缓解无聊：研究高等物理！事实上，她们甚至成功发现了一种新的亚原子粒子，她们将其命名为“哞粒子”。

奶牛们正在进行一项有关 $N$ 个哞粒子的实验（$1\le N\le 10^5$）。粒子 $i$ 的“自旋”可以用范围在 $−10^9\ldots 10^9$ 之间的两个整数 $x_i$ 和 $y_i$ 来描述。有时两个哞粒子会发生相互作用。自旋为 ($x_i,y_i$) 和 ($x_j,y_j$) 的两个粒子之间仅当 $x_i\le x_j$ 并且 $y_i\le y_j$ 时会发生相互作用。在这些条件下，有可能这两个粒子中的一个会消失（另一个粒子不会发生任何变化）。在任意给定的时刻，至多只有一次相互作用会发生。

奶牛们想要知道在经过一些任意的相互作用之后剩余的哞粒子的最小数量。
## 输入格式

输入的第一行包含一个整数 $N$，为哞粒子的初始数量。以下 $N$ 行每行包含两个空格分隔的整数，为一个粒子的自旋。每个粒子的自旋各不相同。
## 输出格式

输出一个整数，为经过一些任意的相互作用之后剩余的哞粒子的最小数量。
## 样例

### 样例输入 #1
```
4
1 0
0 1
-1 0
0 -1
```
### 样例输出 #1
```
1
```
### 样例输入 #2
```
3
0 0
1 1
-1 3
```
### 样例输出 #2
```
2
```
## 提示

### 样例输入输出 1 解释

一个可能的相互作用顺序：

- 粒子 $1$ 和 $4$ 相互作用，粒子 $1$ 消失。
- 粒子 $2$ 和 $4$ 相互作用，粒子 $4$ 消失。
- 粒子 $2$ 和 $3$ 相互作用，粒子 $3$ 消失。
仅留下粒子 $2$。

### 样例输入输出 2 解释

粒子 $3$ 不能与任何其他两个粒子相互作用，所以它必然会留下。粒子 $1$ 和 $2$ 中必然留下至少一个。

### 子任务
- 测试点 $3$-$6$ 满足 $N\le 10^3$。
- 测试点 $7$-$12$ 没有额外限制。


---

---
title: "[COCI 2016/2017 #1] Cezar"
layout: "post"
diff: 提高+/省选-
pid: P6286
tag: ['字符串', '2016', 'Special Judge', '拓扑排序', '字典树 Trie', 'COCI（克罗地亚）']
---
# [COCI 2016/2017 #1] Cezar
## 题目描述

Mirko 想对 $n$ 个单词进行加密。加密过程是这样的：

1.  选择一个英文字母表的排列作为密钥。
2.  将单词中的 `a` 替换为密钥中的第一个字母，`b` 替换为密钥中的第二个字母……以此类推。

例如，以 `qwertyuiopasdfghjklzxcvbnm` 作为密钥对 `cezar` 加密后，将得到 `etmqk`。

他希望，将所有单词加密并按字典序升序排列后，最初的第 $a_i$ 个单词位于第 $i$ 位。请你判断，这能否实现。如果能，请给出任意一种可行的密钥。
## 输入格式

第一行一个整数 $n$。

接下来 $n$ 行，每行一个字符串，表示待加密的单词。

最后一行 $n$ 个整数，表示 $a_i$。
## 输出格式

**本题使用 Special Judge**。

如果 Mirko 的要求不能实现，输出 `NE`。

否则，输出 `DA`。接下来一行输出任意一种可行的密钥。
## 样例

### 样例输入 #1
```
2
ab
bc
2 1 
```
### 样例输出 #1
```
DA
bacdefghijklmnopqrstuvwxyz 
```
### 样例输入 #2
```
3
abc
bcd
add
1 2 3 
```
### 样例输出 #2
```
NE 
```
### 样例输入 #3
```
3
bbb
ccc
ddd
2 3 1 
```
### 样例输出 #3
```
DA
adbcefghijklmnopqrstuvwxyz 
```
## 提示

#### 【样例解释】

**样例 1 解释**

以 `bacdefghijklmnopqrstuvwxyz` 为密钥加密后，得到：

- `ba`
- `ac`

字典序升序排列后，得到：

- `ac`
- `ba`

原先的第一个单词在第二位，第二个单词在第一位。符合要求。

**样例 3 解释**

以 `adbcefghijklmnopqrstuvwxyz`  为密钥加密后，得到：

- `ddd`
- `bbb`
- `ccc`

字典序升序排列后，得到：

- `bbb`
- `ddd`
- `ccc`

原先的第一个单词在第二位，第二个单词在第三位，第三个单词在第一位。符合要求。

---

#### 数据规模与约定

对于 $100\%$ 的数据，$2\le n\le 100$，$1 \leq a_i \leq n$。

所有单词的长度不超过 $100$，且只包含小写字母。

------------

#### 说明

**题目译自 [COCI2016-2017](https://hsin.hr/coci/archive/2016_2017/) [CONTEST #1](https://hsin.hr/coci/archive/2016_2017/contest1_tasks.pdf) _T3 Cezar_**。


---

---
title: "『MdOI R2』Odyssey"
layout: "post"
diff: 提高+/省选-
pid: P6381
tag: ['动态规划 DP', '数学', '图论', '拓扑排序', '素数判断,质数,筛法', '洛谷月赛']
---
# 『MdOI R2』Odyssey
## 题目背景

超越音速的极限，不及瑰丽多变的极光；

微弱的脉冲，开拓原本一片混沌的天地；

沉郁的蓝缓缓闪动，史诗的红迎接巅峰；

血色的夕阳尽头，是将夜的星辰；

夜半的满天星空，也会被来自地狱的硝烟掩盖；

炽红炼狱消逝，只金色遗迹永存。

在这里等待着每一位的，都是一段艰苦而璀璨的旅程。
## 题目描述

若正整数 $a$ 与 $b$ 满足：

- $a$ 与 $b$ 的积是一个正整数的 $k$ 次方，即存在正整数 $c$ 使得 $ab=c^k$。

那么我们称 $(a,b)$ 为一组**完美数对**。

---

有一个包含 $n$ 个结点和 $m$ 条边的**有向无环图**，这张图中的每条边都有权值和长度两个属性。

如果一条路径 $P$ 满足**以下条件之一**，则称其为一条**完美路径**：

- $P$ 中仅包含一条边。

- $P$ 从其起点开始依次为 $e_1, e_2, e_3, \ldots e_p$ 这 $p\ (p\ge 2)$ 条边，对于任意的 $1\leq i\leq p-1$，$e_i$ 的权值和 $e_{i+1}$ 的权值组成完美数对。

你需要求出图中最长完美路径的长度，一条路径的长度定义为这条路径上所有边的长度之和。
## 输入格式

第一行：三个整数 $n,m,k$，分别表示有向无环图的结点数、边数和完美数对的参数。

接下来 $m$ 行：每行四个整数 $u,v,w,l$，表示有一条权值为 $w$，长度为 $l$ 的有向边从 $u$ 连向 $v$。
## 输出格式

第一行：一个整数 $ans$，表示最长完美路径的长度。
## 样例

### 样例输入 #1
```
5 7 2
2 5 2 5
5 3 18 9
2 4 6 7
4 3 6 3
2 1 24 2
1 4 6 8
1 5 8 4
```
### 样例输出 #1
```
14
```
## 提示

【帮助与提示】  

为方便选手测试代码，本题额外提供两组附加样例供选手使用。  

[样例输入1](https://www.luogu.com.cn/paste/wx1lz6m2) [样例输出1](https://www.luogu.com.cn/paste/28xe7f0x)      

[样例输入2](https://www.luogu.com.cn/paste/efgwngs5) [样例输出2](https://www.luogu.com.cn/paste/5hcpoayt)   

----

【样例解释】

样例中给出的有向无环图如图所示，其中边上的红色数字为边的权值，黑色数字为边的长度：

![](https://cdn.luogu.com.cn/upload/image_hosting/w6x03ksd.png)

最长完美路径为 $2\to 5\to 3$，因为这两条边的权值 $2$ 和 $18$ 满足 $2\times 18=6^2$，是完美数对，此路径长度为 $5+9=14$。

此外，$2\to 1\to 4\to 3,\ \ 2\to 4\to 3,\ \ 1\to 5\to 3$ 等也是完美路径，但不是最长的。

图中，$2\to 1\to 5\to 3$ 长度为 $15$，是一条更长的路径，但它并不是完美路径，因为前两个边权 $24$ 和 $8$ 的乘积为 $192$，不是正整数的平方，即 $(24,8)$ 不是完美数对。

---

【数据范围】

**本题采用捆绑测试。**

对于 $100\%$ 的数据：$1\leq n\leq 10^5,\ \ 1\leq m\leq 2\times 10^5,\ \ 1\leq k\leq 10,\ \ 1\leq u,v\leq n,\ \ 1\leq w\leq 10^5,\ \ 1\leq l\leq 10^4$。

给出的图**不保证弱连通**，图中从一个点到另一个点**可能**存在多条边，但保证给出的图是有向无环图。

| 子任务编号 | $n\leq$ |     $m\leq$      | $w\leq$ | $k\leq$ |  特殊性质  | 分值 |
| :--------: | :-----: | :--------------: | :-----: | :-----: | :--------: | :--: |
| Subtask 1  | $10^5$  |  $2\times 10^5$  | $10^5$  |   $1$   |     无     | $18$ |
| Subtask 2  |  $10$   |       $10$       |  $100$  |  $2$   |     无     | $12$ |
| Subtask 3  |  $600$  | $1.5\times 10^3$ | $10^3$  |   $2$   |     无     | $10$ |
| Subtask 4  | $10^5$  |  $2\times 10^5$  | $10^5$  |   $2$   | $w$ 为素数 | $15$ |
| Subtask 5  | $10^5$  |  $2\times 10^5$  | $10^5$  |   $2$   |     无     | $15$ |
| Subtask 6  |  $600$  | $1.5\times 10^3$ | $10^3$  |  $5$   |     无     | $10$ |
| Subtask 7  | $10^5$  |  $2\times 10^5$  | $10^5$  |  $10$   |     无     | $20$ |




---

---
title: "「SWTR-5」Chain"
layout: "post"
diff: 提高+/省选-
pid: P6651
tag: ['动态规划 DP', 'O2优化', '拓扑排序', '容斥原理']
---
# 「SWTR-5」Chain
## 题目描述

给定 $n$ 个点，$m$ 条边的有向无环图。不保证图连通。

$q$ 次询问，每次给出 $k$ 和 $k$ 个互不相同的数 $c_i$，求出如果去掉这 $k$ 个点，整个有向无环图将剩余多少条链。答案对 $10^9+7$ 取模。**每次询问独立。**

- “链”的定义是：我们设一条长度为 $p$ 的链的路径为 $w_0\to w_1\to\cdots\to w_{p-1}\to w_p$，则应满足 $w_0$ 入度为 $0$，$w_p$ 出度为 $0$。你可以将其理解为一条食物链。

- 两条链是“不同的”，当且仅当它们的长度不同，或者经过的点集不同。

- **需要特别注意的是，删去某些点后新产生的链不计入答案。** 例如 $1\to 2\to 3\to 4$ 一图中，有 $1$ 条链 $1\to 2\to 3\to 4$。如果去掉 $2$ 号点，则剩余 $0$ 条链。
## 输入格式

第一行两个整数 $n,m$，分别表示点的个数和边的条数。

接下来 $m$ 行，每行两个整数 $u,v(u\neq v)$，表示 $u\to v$ 有一条有向边。

第 $m+2$ 行一个整数 $q$，表示询问个数。

接下来 $q$ 行：  
- 每行先是一个整数 $k$，表示去掉的点的个数。
- 接下来 $k$ 个整数 $c_i$，表示去掉的点的编号。
## 输出格式

共 $q$ 行，每行表示该次询问答案对 $10^9+7$ 取模后的值。
## 样例

### 样例输入 #1
```
7 14
3 2
4 5
2 5
2 6
3 1
3 5
3 7
3 6
6 4
1 4
6 5
1 6
7 2
7 4
7
3 2 4 6
2 4 6
2 2 5
2 1 4
0
1 4
1 6
```
### 样例输出 #1
```
1
3
0
6
13
7
5
```
### 样例输入 #2
```
233 1
1 2
6
0
1 10
2 10 40
1 1
1 2
2 1 2
```
### 样例输出 #2
```
232
231
230
231
231
231
```
## 提示

「样例 $1$ 说明」

DAG 如图：

![](https://cdn.luogu.com.cn/upload/image_hosting/2gbdoemh.png)

询问 $1$：如果去掉 $2,4,6$，则剩余 $1$ 条链：$3\to 5$。

询问 $2$：如果去掉 $4,6$，则剩余 $3$ 条链：$3\to 5$，$3\to 2\to 5$，$3\to 7\to 2\to 5$。

询问 $7$：如果去掉 $6$，则剩余 $5$ 条链：$3\to 5$，$3\to 2\to 5$，$3\to 7\to 2\to 5$，$3\to 1\to 4\to 5$，$3\to 7\to 4\to 5$。

「数据范围与约定」

**本题采用捆绑测试。**

- Subtask 1（1 point）：给定的图是一条链。
- Subtask 2（14 points）：$n,q\leq 10$。
- Subtask 3（20 points）：$q\leq 10^3$。
- Subtask 4（17 points）：$k=1$。
- Subtask 5（18 points）：$k=2$。
- Subtask 6（30 points）：无特殊限制。

对于 $100\%$ 的数据：$2\leq n\leq 2\times 10^3$，$1\leq m\leq \min(\frac{n\times(n-1)}{2},2\times 10^4)$，$1\leq q\leq 5\times 10^5$。  
所有询问满足：$1\leq \sum k\leq 2\times 10^6$，$0\leq k\leq \min(n,15)$，$1\leq c_i\leq n$。保证 $c_i$ 互不相同。

**本题轻微卡常，请注意 IO 优化。**

---

「题目来源」

[Sweet Round 05](https://www.luogu.com.cn/contest/28195) D。  
idea & solution：[Alex_Wei](https://www.luogu.com.cn/user/123294)。


---

---
title: "[CSP-S2020] 函数调用"
layout: "post"
diff: 提高+/省选-
pid: P7077
tag: ['动态规划 DP', '数学', '2020', '拓扑排序', 'CSP-S 提高级']
---
# [CSP-S2020] 函数调用
## 题目描述

函数是各种编程语言中一项重要的概念，借助函数，我们总可以将复杂的任务分解成一个个相对简单的子任务，直到细化为十分简单的基础操作，从而使代码的组织更加严密、更加有条理。然而，过多的函数调用也会导致额外的开销，影响程序的运行效率。

某数据库应用程序提供了若干函数用以维护数据。已知这些函数的功能可分为三类：

1. 将数据中的指定元素加上一个值；
2. 将数据中的每一个元素乘以一个相同值；
3. **依次**执行若干次函数调用，保证不会出现递归（即不会直接或间接地调用本身）。

在使用该数据库应用时，用户可一次性输入要调用的函数序列（一个函数可能被调用多次），在**依次**执行完序列中的函数后，系统中的数据被加以更新。某一天，小 A 在应用该数据库程序处理数据时遇到了困难：由于频繁而低效的函数调用，系统在执行操作时进入了无响应的状态，他只好强制结束了数据库程序。为了计算出正确数据，小 A 查阅了软件的文档，了解到每个函数的具体功能信息，现在他想请你根据这些信息帮他计算出更新后的数据应该是多少。
## 输入格式

第一行一个正整数 $n$，表示数据的个数。  
第二行 $n$ 个整数，第 $i$ 个整数表示下标为 $i$ 的数据的初始值为 $a_i$。  
第三行一个正整数 $m$，表示数据库应用程序提供的函数个数。函数从 $1 \sim m$ 编号。  
接下来 $m$ 行中，第 $j$（$1 \le j \le m$）行的第一个整数为 $T_j$，表示 $j$ 号函数的类型：

1. 若 $T_j = 1$，接下来两个整数 $P_j, V_j$ 分别表示要执行加法的元素的下标及其增加的值；
2. 若 $T_j = 2$，接下来一个整数 $V_j$ 表示所有元素所乘的值；
3. 若 $T_j = 3$，接下来一个正整数 $C_j$ 表示 $j$ 号函数要调用的函数个数，  
  随后 $C_j$ 个整数 $g^{(j)}_1, g^{(j)}_2, \ldots , g^{(j)}_{C_j}$ 依次表示其所调用的函数的编号。

第 $m + 4$ 行一个正整数 $Q$，表示输入的函数操作序列长度。  
第 $m + 5$ 行 $Q$ 个整数 $f_i$，第 $i$ 个整数表示第 $i$ 个执行的函数的编号。
## 输出格式

一行 $n$ 个用空格隔开的整数，按照下标 $1 \sim n$ 的顺序，分别输出在执行完输入的函数序列后，数据库中每一个元素的值。**答案对** $\boldsymbol{998244353}$ **取模。**
## 样例

### 样例输入 #1
```
3
1 2 3
3
1 1 1
2 2
3 2 1 2
2
2 3

```
### 样例输出 #1
```
6 8 12
```
### 样例输入 #2
```
10
1 2 3 4 5 6 7 8 9 10
8
3 2 2 3
3 2 4 5
3 2 5 8
2 2
3 2 6 7
1 2 5
1 7 6
2 3
3
1 2 3
```
### 样例输出 #2
```
36 282 108 144 180 216 504 288 324 360

```
### 样例输入 #3
```
见附件中的 call/call3.in
```
### 样例输出 #3
```
见附件中的 call/call3.ans
```
## 提示

**【样例 #1 解释】**

$1$ 号函数功能为将 $a_1$ 的值加一。$2$ 号函数功能为所有元素乘 $2$。$3$ 号函数将先调用 $1$ 号函数，再调用 $2$ 号函数。

最终的函数序列先执行 $2$ 号函数，所有元素的值变为 $2, 4, 6$。

再执行 $3$ 号函数时，先调用 $1$ 号函数，所有元素的值变为 $3, 4, 6$。再调用 $2$ 号函数，所有元素的值变为 $6, 8, 12$。

**【数据范围】**

| 测试点编号 | $n, m, Q \le$ | $\sum C_j$ | 其他特殊限制 |
| :----------: | :----------: | :----------: | :----------: |
| $1 \sim 2$ | $1000$ | $= m - 1$ | 函数调用关系构成一棵树 |
| $3 \sim 4$ | $1000$ | $\le 100$ | 无 |
| $5 \sim 6$ | $20000$ | $\le 40000$ | 不含第 $2$ 类函数或不含第 $1$ 类函数 |
| $7$ | $20000$ | $= 0$ | 无 |
| $8 \sim 9$ | $20000$ | $= m - 1$ | 函数调用关系构成一棵树 |
| $10 \sim 11$ | $20000$ | $\le 2 \times 10^5$ | 无 |
| $12 \sim 13$ | $10^5$ | $\le 2 \times 10^5$ | 不含第 $2$ 类函数或不含第 $1$ 类函数 |
| $14$ | $10^5$ | $= 0$ | 无 |
| $15 \sim 16$ | $10^5$ | $= m - 1$ | 函数调用关系构成一棵树 |
| $17 \sim 18$ | $10^5$ | $\le 5 \times 10^5$ | 无 |
| $19 \sim 20$ | $10^5$ | $\le 10^6$ | 无 |

对于所有数据：$0 \le a_i \le 10^4$，$T_j \in \{1,2,3\}$，$1 \le P_j \le n$，$0 \le V_j \le 10^4$，$1 \le g^{(j)}_k \le m$，$1 \le f_i \le m$。


---

---
title: "「dWoi R2」Change / 改造"
layout: "post"
diff: 提高+/省选-
pid: P7845
tag: ['图论', '拓扑排序']
---
# 「dWoi R2」Change / 改造
## 题目背景

入间改造对人类生存繁殖有帮助的工具（~~就是性能工具，具体可以去看看弹丸论破 V3 自由时间与入间美兔的交谈，在这里不方便说吧，毕竟是 青 少 年 编 程 网 站~~）玩腻了，她发现了有一个很 符 合 她 胃 口 的东西，叫做 Galgame，于是她开始打一款叫做 Little Busters 的 Galgame，然后沉迷上了沙耶线最后的场景。

---

![](https://cdn.luogu.com.cn/upload/image_hosting/vxy5rh6c.png)

## 题目描述

在经过 $99$ 次的 Replay 后，沙耶终于发现迷宫是一个有向无环图。为了保证最后一次 Replay 的趣味性，时风瞬给沙耶和理树安排了一个小游戏。

这张有向无环图 $G$ 有 $n$ 个点，$m$ 条边，每条边的长度为 $1$。设 $l_i$ 为初始点 $s$ 到第 $i$ 条边所指向的点 $u$ 的最短路，定义第 $i$ 条边的边权为 $p-l_i$。游戏步骤是这样的（所有选择都是按如下顺序进行，并且每个人的选择都是公开的）。

1. 理树站在点 $s$ 上。  
2. 时风瞬会随机选取一个点作为 $t$（$t$ 可以等于 $s$）。
3. 如果无法从 $s$ 到达 $t$，游戏直接结束。
3. 沙耶需要选择一条边。
4. 理树需要找到一条从 $s$ 到 $t$ 的路径。
5. 若沙耶选择的边在理树所选择的路径上，则理树就会将这条边的边权的钱给沙耶。

理树希望能少输钱，沙耶希望能多拿钱。若两方都采取最优策略，请问沙耶期望能得到多少钱。
## 输入格式

第一行四个整数 $n,m,s,p$，分别代表有向图点数，边数与理树站在的位置，以及题目中出现的 $p$。

接下来 $m$ 行每行两个整数 $u_i,v_i$ 描述一条边。
## 输出格式

一行一个整数代表答案。

请对 $998244353$ 取模。
## 样例

### 样例输入 #1
```
8 8 1 10
1 2
1 3
1 4
2 5
3 5
5 6
6 7
6 8
```
### 样例输出 #1
```
6
```
### 样例输入 #2
```
3 2 1 3
1 2
1 3
```
### 样例输出 #2
```
332748119
```
## 提示

#### 样例 1 解释

比如 $t=6$ 时，沙耶应该选择连接 $5,6$ 的那条边；$t=8$ 时，沙耶仍然应该选择连接 $5,6$ 的那条边；$t=4$ 时，应该选择连接 $1,4$ 的那条边；$t=5$ 时，沙耶无论选择什么边都不会得到钱。

设 $res_u$ 表示 $t=u$ 时沙耶能获得的最大收益，我们有 $res=\{0,9,9,9,0,7,7,7\}$。

#### 样例 2 解释

设 $res_u$ 表示 $t=u$ 时沙耶能获得的最大收益，我们有 $res=\{0,2,2\}$。

---

#### 数据规模与约定

**本题采用捆绑测试。**

- Subtask 1（10 pts）：$n,m \le 5$；
- Subtask 2（20 pts）：$m=n-1$，$u_i<v_i$，$s=1$；
- Subtask 3（30 pts）：$n,m \le 10^3$；
- Subtask 4（40 pts）：无特殊限制。

对于 $100\%$ 的数据，$1 \le n,m \le 5 \times 10^6$，$1 \le s \le n$，$1 \le u_i,v_i \le n$，$u_i \ne v_i$，$n\le p \le 10^9$。


---

---
title: "[USACO22JAN] Minimizing Haybales P"
layout: "post"
diff: 提高+/省选-
pid: P8099
tag: ['线段树', '二分', 'USACO', '2022', '拓扑排序']
---
# [USACO22JAN] Minimizing Haybales P
## 题目描述

Bessie 感到无聊，于是又在 Farmer John 的牛棚里制造麻烦。FJ 有 $N$（$1 \le N \le 10^5$）堆草堆。对于每个 $i \in [1,N]$，第 $i$ 堆草堆有 $h_i$（$1 \le h_i \le 10^9$）的草。Bessie 不想让任何的草倒下来，所以她唯一可以执行的操作为：

- 如果两个相邻的草堆的高度相差不超过 $K$（$1 \le K \le 10^9$），她可以交换这两堆草堆。

Bessie 在一系列这样的操作之后可以得到的的字典序最小的高度序列是什么？
## 输入格式

输入的第一行包含 $N$ 和 $K$。第 $i+1$ 行包含第 $i$ 堆草堆的高度。
## 输出格式

输出 $N$ 行，第 $i$ 行包含答案中第 $i$ 堆草堆的高度。
## 样例

### 样例输入 #1
```
5 3
7
7
3
6
2
```
### 样例输出 #1
```
6
7
7
2
3
```
## 提示

【样例解释】

一种 Bessie 可以交换草堆的方式如下：

```plain
   7 7 3 6 2
-> 7 7 6 3 2
-> 7 7 6 2 3
-> 7 6 7 2 3
-> 6 7 7 2 3
```

【数据范围】

- 所有测试点的 $10\%$ 满足 $N \le 100$。
- 所有测试点的另外 $20\%$ 满足 $N \le 5000$。
- 其余 $70\%$ 的测试点没有额外限制。

供题：Daniel Zhang，Benjamin Qi


---

---
title: "[USACO22OPEN] Apple Catching G"
layout: "post"
diff: 提高+/省选-
pid: P8272
tag: ['贪心', 'USACO', '2022', '排序']
---
# [USACO22OPEN] Apple Catching G
## 题目描述

天上下苹果了！在某些时刻，一定数量的苹果会落到数轴上。在某些时刻，Farmer John 的一些奶牛将到达数轴并开始接苹果。

如果一个苹果在没有奶牛接住的情况下落到数轴上，它就会永远消失。如果一头奶牛和一个苹果同时到达，奶牛就会接住苹果。每头奶牛每秒可以移动一单位距离。一旦一头奶牛接住了一个苹果，她就会离开数轴。

如果 FJ 的奶牛以最优方式合作，她们总共能接住多少个苹果？
## 输入格式

输入的第一行包含 $N$（$1\le N\le 2\cdot 10^5$），为苹果落到数轴上的次数或 FJ 的奶牛出现的次数。

以下 $N$ 行每行包含四个整数 $q_i$，$t_i$，$x_i$ 和 $n_i$（$q_i\in \{1,2\}, 0\le t_i\le 10^9, 0\le x_i\le 10^9, 1\le n_i\le 10^3$）。

- 如果 $q_i=1$，意味着 FJ 的 $n_i$ 头奶牛在 $t_i$ 时刻来到数轴上的 $x_i$ 位置。
- 如果 $q_i=2$，意味着 $n_i$ 个苹果在 $t_i$ 时刻落到了数轴上的 $x_i$ 位置。

输入保证所有有序对 $(t_i,x_i)$ 各不相同。
## 输出格式

输出 FJ 的奶牛总计能接住的苹果的最大数量。
## 样例

### 样例输入 #1
```
5
2 5 10 100
2 6 0 3
2 8 10 7
1 2 4 5
1 4 7 6
```
### 样例输出 #1
```
10
```
### 样例输入 #2
```
5
2 5 10 100
2 6 0 3
2 8 11 7
1 2 4 5
1 4 7 6
```
### 样例输出 #2
```
9
```
## 提示

【样例解释 1】

在这个例子中，在 $t=5$ 时刻落地的 $100$ 个苹果均不能被接住。以下是一种接住 $10$ 个苹果的方式：

- FJ 的所有六头 $t=4$ 时刻到达的奶牛各接一个 $t=8$ 时刻落地的苹果。
- FJ 的一头 $t=2$ 时刻到达的奶牛接一个 $t=8$ 时刻落地的苹果。
- 余下三头 $t=2$ 时刻到达的奶牛各接一个 $t=6$ 时刻落地的苹果。

【样例解释 2】

再一次地，在 $t=5$ 时刻落地的苹果均不能被接住。除此之外，在 $t=2$ 时刻到达的奶牛均不能接住 $t=8$ 时刻落地的苹果。以下是一种接住 $9$ 个苹果的方式：

- FJ 的所有六头 $t=4$ 时刻到达的奶牛各接一个 $t=8$ 时刻落地的苹果。
- 余下三头 $t=2$ 时刻到达的奶牛各接一个 $t=6$ 时刻落地的苹果。


---

---
title: "「DAOI R1」Magic"
layout: "post"
diff: 提高+/省选-
pid: P8285
tag: ['数学', '排序']
---
# 「DAOI R1」Magic
## 题目背景

> $ \text{-1,-1,+2} $
## 题目描述

乔木 来到了大魔王的面前，他决定使用魔法击败魔王。

给定一个整数 $n$，表示有 $n$ 个魔法阵，在每个魔法阵上都存在着一定的魔力值 $a_i$。

你每次可以选择三个魔法阵 $i,j,k\;(i,j,k$ 互不相同且 $a_i>0$，$a_j>0)$，然后 乔木 将会让第 $i$ 个魔法阵和第 $j$ 个魔法阵上的魔力值 $a_i,a_j$ 分别减 $1$，并让第 $k$ 个魔法阵上的魔力值 $a_k$ 加 $2$，我们将这称之为一次操作。

乔木 想要将所有的魔力汇聚到一起以发挥最大的威力。他想知道在经过若干次操作后，能否让其中 $n-1$ 个魔法阵上的魔力值为 $0$，并使汇聚的那一个魔法阵的魔力值为原魔法阵的所有魔力值之和。
## 输入格式

**本题包含多组数据。**

一行输入一个数 $T$，表示数据组数。

接下来对于每组数据，先输入一个正整数 $n$，然后依次输入 $n$ 个整数，第 $i$ 个整数代表 $a_i$。
## 输出格式

对于每组数据输出一行，若可以实现，则输出 `YES`，否则输出 `NO`。
## 样例

### 样例输入 #1
```
2
4
2 0 2 2
3
5 0 7
```
### 样例输出 #1
```
YES
NO
```
## 提示

### 样例解释
- 对于第一组数据，可以将 $a_1$ 和 $a_3$ 对 $a_4$ 进行两次操作。
- 对于第二组数据，可以证明不行。

### 数据范围
- 对于 $5\%$ 的数据：$1\le n\le2$，$0\le a_i\le10^3$。
- 对于 $20\%$ 的数据：$1\le n\le10$，$0\le a_i\le10^3$。
- 对于 $100\%$ 的数据：$1\le \sum{n}\le2\times10^{6}$，$0\le a_i\le10^{9}$。

对于所有数据，保证 $1\le T\le100$ 且 $\sum\limits_{i=1}^{n} a_i \ge1$。


---

---
title: "[蓝桥杯 2017 国 A] 区间移位"
layout: "post"
diff: 提高+/省选-
pid: P8660
tag: ['贪心', '2017', '二分', '排序', '蓝桥杯国赛']
---
# [蓝桥杯 2017 国 A] 区间移位
## 题目描述

数轴上有 $n$ 个闭区间：$D_1, \cdots ,D_n$。

其中区间 $D_i$ 用一对整数 $[a_i,b_i]$ 来描述，满足 $a_i<b_i$。

已知这些区间的长度之和至少有 $10000$。

所以，通过适当的移动这些区间，你总可以使得他们的“并”覆盖 $[0,10000]$ ——也就是说 $[0,10000]$ 这个区间内的每一个点都落于至少一个区间内。

你希望找一个移动方法，使得位移差最大的那个区间的位移量最小。

具体来说，假设你将 $D_i$ 移动到 $[a_i+c_i,b_i+c_i]$ 这个位置。你希望使得 $\max\limits_{i=1}^n\{|c_i|\}$ 最小。
## 输入格式

输入的第一行包含一个整数 $n$，表示区间的数量。

接下来有 $n$ 行，每行 $2$ 个整数 $a_i,b_i$，以一个空格分开，表示区间 $[a_i,b_i]$。

保证区间的长度之和至少是 $10000$。

## 输出格式

输出一个数字，表示答案。如果答案是整数，只输出整数部分。如果答案不是整数，输出时四舍五入保留一位小数。
## 样例

### 样例输入 #1
```
2
10 5010
4980 9980
```
### 样例输出 #1
```
20
```
### 样例输入 #2
```
4
0 4000
3000 5000
5001 8000
7000 10000
```
### 样例输出 #2
```
0.5
```
## 提示

**【样例解释】**

样例 1：第一个区间往左移动 $10$；第二个区间往右移动 $20$。

样例 2：第 $2$ 个区间往右移 $0.5$；第 $3$ 个区间往左移 $0.5$ 即可。

**【数据范围】**

对于 $30\%$ 的评测用例，$1 \le n \le 10$；

对于 $100\%$ 的评测用例，$1 \le n \le 10000$，$0 \le a_i<b_i \le 10000$。


---

---
title: "[蓝桥杯 2022 省 A] 扫描游戏"
layout: "post"
diff: 提高+/省选-
pid: P8777
tag: ['模拟', '计算几何', '2022', '排序', '蓝桥杯省赛']
---
# [蓝桥杯 2022 省 A] 扫描游戏
## 题目描述

有一根围绕原点 $O$ 顺时针旋转的棒 $OA$，初始时指向正上方（Y 轴正向）。平面中有若干物件，第 $i$ 个物件的坐标为 $\left(x_{i}, y_{i}\right)$，价值为 $z_{i}$。当棒扫到某个物件时，棒的长度会瞬间增长 $z_{i}$，且物件瞬间消失（棒的顶端恰好碰到物件也视为扫到)，如果此时增长完的棒又额外碰到了其他物件，也按上述方式消去（它和上述那个点视为同时消失）。

如果将物件按照消失的时间排序，则每个物件有一个排名，同时消失的物件排名相同，请输出每个物件的排名，如果物件永远不会消失则输出 $-1$。
## 输入格式

输入第一行包含两个整数 $n$、$L$，用一个空格分隔，分别表示物件数量和棒的初始长度。

接下来 $n$ 行每行包含第三个整数 $x_{i}, y_{i}, z_{i}$。

注意存在 $(x_{i}, y_{i})=(0,0)$ 的情况，这些点视为一开始就立刻被碰到。
## 输出格式

输出一行包含 $n$ 整数，相邻两个整数间用一个空格分隔，依次表示每个物件的排名。
## 样例

### 样例输入 #1
```
5 2
0 1 1
0 3 2
4 3 5
6 8 1
-51 -33 2
```
### 样例输出 #1
```
1 1 3 4 -1
```
## 提示

对于 $30 \%$ 的评测用例，$1 \leq n \leq 500$ ；

对于 $60 \%$ 的评测用例，$1 \leq n \leq 5000$;

对于所有评测用例，$1 \leq n \leq 2\times10^5,-10^{9} \leq x_{i}, y_{i} \leq 10^{9}, 1 \leq L, z_{i} \leq 10^{9}$ 。 

样蓝桥杯 2022 省赛 A 组 H 题。


---

---
title: "「TAOI-1」椎名真昼"
layout: "post"
diff: 提高+/省选-
pid: P9220
tag: ['博弈论', 'O2优化', '拓扑排序', '强连通分量', 'Tarjan']
---
# 「TAOI-1」椎名真昼
## 题目背景

**请注意赛后题目添加了多测。因此请将您的赛时代码进行修改后再提交。**
## 题目描述

你正在看轻小说，突然你的家长走了进来，于是你假装在写 OI 题目。

Alice 和 Bob 正在玩一款游戏，给定一个有向图，每个点初始有一个颜色（黑或白）。

双方轮流进行操作，Alice 先手，每次操作选定一个节点，将所有从该点开始，能到达的点（包括自身）颜色翻转。如果某次操作后所有节点都变为白色，则进行该次操作的人胜利。

假如双方都采用最优策略使得自己胜利，或者如果自己无法胜利，使得对方无法胜利。

给你节点的初始状态，请你求出最终的胜者，亦或者，没有胜者。

---

定义点 $u$ 能到达点 $v$，当且仅当存在数列 $(a_1,a_2,a_3,\cdots,a_k)$，其中 $k \ge 1$，使得 $\forall i \in [1,k)$，存在有向边 $a_i \to a_{i+1}$，且 $a_1=u$，$a_k=v$。
## 输入格式

**本题有多组测试数据。**

第一行一个正整数 $T$，代表数据组数。

对于每组测试数据：

第一行两个整数 $n, m$，代表图的点数，边数。

第二行 $n$ 个整数，代表每个点开始时的颜色。$1$ 代表黑色，$0$ 代表白色。

接下来 $m$ 行，每行两个整数 $u, v$ 代表一条从 $u \to v$ 的边。
## 输出格式

对于每组测试数据：

如果最后 Alice 胜利，输出 `A`。

如果最后 Bob 胜利，输出 `B`。

如果双方（在对方的阻止下）都无法胜利，输出 `N`。

您无需输出空格或换行符。
## 样例

### 样例输入 #1
```
2
2 1
1 0
2 1
3 2
1 0 1
1 2
2 3
```
### 样例输出 #1
```
AN
```
## 提示

### 数据范围

**本题采用捆绑测试**。

- Subtask 1（5 points）：$n \leq 2$，$m \leq 1$，$T=1$。
- Subtask 2（15 points）：$n \leq 5$，$m \leq 8$，$T=1$。
- Subtask 3（25 points）：保证所有点的初始颜色相同。
- Subtask 4（55 points）：无特殊限制。

对于所有测试数据，$1 \leq n \leq 10^5$，$1 \leq m \leq 2 \times 10^5$，$1 \le T \le 15$。

### 样例解释

在第一组数据中，Alice 可以先手对节点 $1$ 进行操作。操作后所有节点变为白色。

在第二组数据中，双方都没有必胜的方法，因此双方会互相拖延对方阻止对方获胜。

---

「据说如果无论如何都输出 `N` 的话，有 $45\%$ 的几率能够得到正确答案？」

「怎么可能，不会真的有人造出这么蠢的数据吧……」


---

---
title: "[YsOI2023] 广度优先遍历"
layout: "post"
diff: 提高+/省选-
pid: P9534
tag: ['洛谷原创', 'Special Judge', 'O2优化', '广度优先搜索 BFS', '拓扑排序', '最近公共祖先 LCA', '洛谷月赛']
---
# [YsOI2023] 广度优先遍历
## 题目背景

Ysuperman 模板测试的图论题。

【数据删除】
## 题目描述

今天的模板测试是无向图上的广度优先遍历，【数据删除】马上写好了代码：

```cpp
#include <cstdio>
#include <cstring>
#include <iostream>
#include <algorithm>
#include <vector>
#include <queue>
using namespace std;
const int maxn = 100005;
vector<int> G[maxn];
queue<int> q;
int pa[maxn];
int main()
{
    int n, m;
    cin >> n >> m;
    for (int i = 1; i <= m; ++i)
    {
        int u, v;
        cin >> u >> v;
        G[u].push_back(v);
        G[v].push_back(u);
    }
    memset(pa, -1, sizeof pa);
    q.push(1);
    pa[1] = 0;
    while (!q.empty())
    {
        int u = q.front();
        q.pop();
        for (auto v : G[u])
        {
            if (pa[v] != -1)
                continue;
            pa[v] = u;
            q.push(v);
        }
    }
    for (int i = 1; i <= n; ++i)
    {
        cout << pa[i];
        if (i != n)
            cout << " ";
    }
    cout << endl;
    return 0;
}
```

如你所见，这份代码会输入一个 $n$ 个点 $m$ 条边的无向图，并且求出这张图以 $1$ 为根的一棵“广度优先遍历树”，最后输出所有点的父亲节点编号。

不过值得注意的是，这棵“广度优先遍历树”的具体形态和“边的输入顺序”有关，也就是说，不同的输入顺序可能会得到不同的父亲节点编号。

现在【数据删除】告诉了你 $n,m$、这 $m$ 条边以及在某个“边输入顺序”情况下他的代码的输出，你需要还原出这个“边输入顺序”。如果有多种边输入顺序对应的都是这样的输出，你**只需要输出其中任意一种**即可。

特别的，保证有解，且无向图连通，无自环（但是有可能有重边）。
## 输入格式

第一行两个正整数 $n,m$ 分别表示无向图的点数和边数。

接下来 $m$ 行每行两个整数 $u,v$ 表示存在 $u$ 与 $v$ 之间存在一条无向边。

最后一行 $n$ 个整数表示【数据删除】代码的输出。（由题意可知他输出的是某个“边输入顺序”情况下他得到的“广度优先遍历树”中 $1\sim n$ 这些节点的父亲节点编号）
## 输出格式

输出包含 $m$ 行，每行两个整数 $u,v$ 表示 $u$ 和 $v$ 之间存在一条无向边，你的输出顺序表示你给出的“边输入顺序”。

请注意，你需要保证如果输入给出的图中 $u,v$ 间连了 $k$ 条边，那么你给出的图中 $u,v$ 间也要连有 $k$ 条边。

如果有多种“边输入顺序”合法，**输出其中任意一种都会被判断为正确**。另外，由于是无向边，所以你输出的**一条边两个点的排列顺序对答案判定没有影响**。
## 样例

### 样例输入 #1
```
4 4
2 1
1 3
2 4
4 3
0 1 1 3
```
### 样例输出 #1
```
1 3
3 4
1 2
2 4

```
### 样例输入 #2
```
8 9
7 8
6 1
5 4
7 1
4 1
3 7
2 6
7 5
2 4
0 6 7 1 4 1 1 7
```
### 样例输出 #2
```
6 2
7 3
4 5
1 6
7 8
1 4
1 7
2 4
5 7
```
## 提示

#### 样例 1 解释

直接运行【数据删除】的代码即可。

如果不改变边输入顺序，将下面数据输入【数据删除】的代码：

```
4 4
2 1
1 3
2 4
4 3
```

他的代码跑出来结果如下：

```
0 1 1 2
```

如果按照样例 1 输出给出的顺序，即，将下面数据输入他的代码：

```
4 4
1 3
3 4
1 2
2 4
```

输出为：

```
0 1 1 3
```

#### 数据范围

对于前 $10\%$ 的数据，满足 $n\le 8$，$m\le 10$。

对于前 $40\%$ 的数据，满足 $n\le 1000$，$m\le 2000$。

另有 $10\%$ 的数据，满足 $m=n-1$。

对于 $100\%$ 的数据，满足 $1\le n\le 10^5$，$1\le m\le 2\times 10^5$。

#### 提示

为什么有可能会有重边，因为懒得去重了，这个家伙出图论题就是懒得判重边的（）

附件下发了本题 checker。


---

---
title: "[EC Final 2022] Inversion"
layout: "post"
diff: 提高+/省选-
pid: P9721
tag: ['2022', '交互题', 'Special Judge', 'O2优化', '排序', 'ICPC']
---
# [EC Final 2022] Inversion
## 题目描述

$\textbf{This is an interactive problem.}$

There is a hidden permutation $p_1, p_2, \dots, p_n$ of $\{1, 2, \dots, n\}$. You want to find it by asking the parity of the number of inversions of $p_l,\ldots, p_r$.

You can query in the format ${?~l~r}$, and the interactor will respond you $\left( \sum_{l\leq i < j\leq r} [p_i > p_j]\right) \bmod 2$. $[p_i>p_j]$ is $1$ when $p_i>p_j$ and $0$ when $p_i\le p_j$.
## 输入格式

Firstly, you should read the integer $n$ ($1\le n\le 2000$).

After that, you can make no more than $4 \times 10^4$ queries. To make a query, output ``${?~l~r}$'' ($1 \leq l \leq r \leq n$) on a separate line, then you should read the response from standard input. 

To give your answer, print ``${!~p_1~p_2~\dots~p_n}$'' on a separate line. The output of the answer is \textbf{not} counted towards the limit of $4 \times 10^4$ queries. 

After that, your program should terminate. 

After printing a query, do not forget to output end of line and flush the output. To do this, use $\texttt{fflush(stdout)}$ or $\texttt{cout.flush()}$ in C++, $\texttt{System.out.flush()}$ in Java, $\texttt{flush(output)}$ in Pascal, or $\texttt{stdout.flush()}$ in Python. 

It is guaranteed that the permutation is fixed in advance. 
## 样例

### 样例输入 #1
```
3

0

0

1

```
### 样例输出 #1
```

? 1 2

? 1 3

? 2 3

! 2 3 1
```
## 题目翻译

**【题目描述】**

这是一个交互式问题。

有一个隐藏的排列 $p_1, p_2, \dots, p_n$，其中包含 $\{1, 2, \dots, n\}$ 的排列。你想通过询问 $p_l,\ldots, p_r$ 的逆序对数量的奇偶性来找到它。

你可以以 ${?~l~r}$ 的格式进行查询，交互器会回答你 $\left( \sum_{l\leq i < j\leq r} [p_i > p_j]\right) \bmod 2$。其中 $[p_i>p_j]$ 在 $p_i>p_j$ 时为 $1$，在 $p_i\le p_j$ 时为 $0$。

首先，你需要读入整数 $n$（$1\le n\le 2000$）。

之后，你可以进行不超过 $4 \times 10^4$ 次查询。要进行查询，输出 ${?~l~r}$（$1 \leq l \leq r \leq n$）在单独的一行上，然后你应该从标准输入中读取响应。

要给出你的答案，将 ${!~p_1~p_2~\dots~p_n}$ 打印在单独的一行上。答案的输出 $\textbf{不}$ 计入 $4 \times 10^4$ 次查询的限制。

之后，你的程序应该终止。

在打印查询后，不要忘记输出换行并刷新输出。要做到这一点，在 C++ 中使用 $\texttt{fflush(stdout)}$ 或 $\texttt{cout.flush()}$，在 Java 中使用 $\texttt{System.out.flush()}$，在 Pascal 中使用 $\texttt{flush(output)}$，或者在 Python 中使用 $\texttt{stdout.flush()}$。

保证排列提前固定。

翻译来自于：[ChatGPT](https://chatgpt.com/)


---

