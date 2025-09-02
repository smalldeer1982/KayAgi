---
title: "[GCJ 2017 Finals] Stack Management"
layout: "post"
diff: NOI/NOI+/CTSC
pid: P13183
tag: ['图论', '2017', '深度优先搜索 DFS', '图论建模', 'Google Code Jam']
---
# [GCJ 2017 Finals] Stack Management
## 题目描述

You are playing a solitaire game in which there are $\mathbf{N}$ stacks of face-up cards, each of which initially has $\mathbf{C}$ cards. Each card has a value and a suit, and no two cards in the game have the same value/suit combination.

In one move, you can do one of the following things:

1. If there are two or more cards with the same suit that are on top of different stacks, you may remove the one of those cards with the smallest value from the game. (Whenever you remove the last card from a stack, the stack is still there — it just becomes empty.)
2. If there is an empty stack, you may take a card from the top of any one of the non-empty stacks and place it on top of (i.e., as the only card in) that empty stack.

You win the game if you can make a sequence of moves such that eventually, each stack contains at most one card. Given a starting arrangement, determine whether it is possible to win the game.
## 输入格式

The first line of the input gives the number $\mathbf{P}$ of premade stacks that will be used in the test cases. Then, $\mathbf{P}$ lines follow. The i-th of those lines begins with an integer $\mathbf{C}_{\mathbf{i}}$, the number of cards in the i-th of those premade stacks, and continues with $\mathbf{C}_{\mathbf{i}}$ ordered pairs of integers. The j-th of these ordered pairs has two integers $\mathbf{V}_{\mathbf{i j}}$ and $\mathbf{S}_{\mathbf{i j}}$, representing the value and suit of the j-th card from the top in the i-th premade stack.

Then, there is another line with one integer $\mathbf{T}$, the number of test cases. $\mathbf{T}$ test cases follow. Each case begins with one line with two integers $\mathbf{N}$ and $\mathbf{C}$: the number of stacks, and the number of cards in each of those stacks. Then, there is one line with $\mathbf{N}$ integers $\mathbf{P}_{\mathbf{i}}$, representing the indexes (starting from 0) of the test case's set of premade stacks.

## 输出格式

For each test case, output one line containing Case #x: y, where $x$ is the test case number (starting from 1) and $y$ is POSSIBLE if it is possible to win the game, or IMPOSSIBLE otherwise.
## 样例

### 样例输入 #1
```
5
2 7 2 7 1
2 6 4 7 4
2 3 2 6 2
2 4 2 10 2
2 5 4 7 3
2
2 2
0 2
3 2
4 1 3
```
### 样例输出 #1
```
Case #1: POSSIBLE
Case #2: IMPOSSIBLE
```
## 提示

**Sample Explanation**

In sample case #1, there are two stacks, each of which has two cards. The first stack has a 7 of suit 2 on top and a 7 of suit 1 below that. The second stack has a 3 of suit 2 on top and a 6 of suit 2 below that.

It is possible to win the game as follows:

* Remove the 3 of suit 2 from the second stack.
* Remove the 6 of suit 2 from the second stack. This makes the second stack empty.
* Move the 7 of suit 2 to the second stack. Then the win condition is satisfied: all stacks have at most one card.

In sample case #2, there are three stacks, each of which has two cards. It is not possible to win the game in this case; the only possible move is to remove the 5 of suit 4 on top of the third stack, and this does not open up any new moves.

**Limits**

- $1 \leq T \leq 100$.
- $2 \leq P \leq 60000$.
- $0 \leq P_i < P$, for all $i$.
- The $P_i$-th premade stack has exactly $C$ cards.
- No two cards in a test case have the same value/suit combination.

**Small dataset (10 Pts, Test Set 1 - Visible)**

- $2 \leq N \leq 4$.
- $2 \leq C_i \leq 13$, for all $i$.
- $2 \leq C \leq 13$.
- $1 \leq V_{ij} \leq 13$, for all $i$ and $j$.
- $1 \leq S_{ij} \leq 4$, for all $i$ and $j$.

**Large dataset (30 Pts, Test Set 2 - Hidden)**

- $2 \leq N \leq 50000$.
- $2 \leq C_i \leq 50000$, for all $i$.
- $2 \leq C \leq 50000$.
- $4 \leq N \times C \leq 10^5$.
- $1 \leq V_{ij} \leq 50000$, for all $i$ and $j$.
- $1 \leq S_{ij} \leq 50000$, for all $i$ and $j$.


---

---
title: "[GCJ 2015 Finals] Taking Over The World"
layout: "post"
diff: NOI/NOI+/CTSC
pid: P13236
tag: ['图论', '2015', '二分', '网络流', '图论建模', 'Google Code Jam']
---
# [GCJ 2015 Finals] Taking Over The World
## 题目描述

You and your friend Pinky have a plan to take over the world. But first you need to disable a certain secret weapon.

It is hidden inside a twisted maze of passages (a graph) with one entrance. Pinky is going to be at the vertex with the secret weapon, disabling it. Meanwhile, a security team at the graph entrance will be alerted, and will run through the graph to try to get to Pinky in time to stop him. You are going to be slowing down the security team to give Pinky as much time as possible. It takes one unit of time to traverse any edge of the graph, but you can additionally "obstruct" up to $\mathbf{K}$ vertices. It takes one additional unit of time to traverse an obstructed vertex. You will choose to obstruct a set of vertices that slows down the security team by as much as possible.

If the security team will be starting at the graph entrance and is trying to get to the secret weapon vertex, how much time will it take them to get there? Note that you have to commit all your obstructions before the security guards start their journey, and the security guards will know which vertices you have obstructed and will choose an optimal path based on that information.

Obstructing the secret weapon vertex is not useful because that will not delay the guards any further after they have already caught Pinky. Obstructing the entrance, on the other hand, is obviously a good idea.
## 输入格式

The first line of the input gives the number of test cases, $\mathbf{T}$. $\mathbf{T}$ test cases follow. Each one starts with a line containing $\mathbf{N}, \mathbf{M}$, and $\mathbf{K}$. The next $\mathbf{M}$ lines each contain a pair of vertices connected by an edge. Vertices are numbered from 0 (the entrance) to $\mathbf{N}-1$ (the secret weapon room). The first vertex will always be smaller than the second vertex, and no pair of vertices will appear more than once in the same test case. Edges are bi-directional -- the guards can travel along any edge in either direction.

## 输出格式

For each test case, output one line containing "Case #x: y", where $\mathrm{x}$ is the test case number (starting from 1) and $\mathrm{y}$ is the time it will take the security guards to get from the entrance to the secret weapon room.
## 样例

### 样例输入 #1
```
5
3 2 1
0 1
1 2
3 2 2
0 1
1 2
3 2 3
0 1
1 2
4 4 2
0 1
0 2
1 3
2 3
7 11 3
0 1
0 2
0 3
1 4
1 5
2 4
2 5
3 4
3 5
4 6
5 6
```
### 样例输出 #1
```
Case #1: 3
Case #2: 4
Case #3: 4
Case #4: 3
Case #5: 5
```
## 提示

**Limits**

- $1 \leq \mathbf{T} \leq 100$.
- $2 \leq \mathbf{N} \leq 100$.
- $1 \leq \mathbf{M} \leq \mathbf{N} \times (\mathbf{N} - 1) / 2$.
- $1 \leq \mathbf{K} \leq \mathbf{N}$.
- There will always be a path from room 0 to room $\mathbf{N} - 1$.

**Small dataset(7 Pts)**

- Time limit: ~~240~~ 5 seconds.
- It will not be possible to delay the guards by more than 2 time units, compared to the shortest unobstructed path length (using the given $\mathbf{K}$).

**Large dataset(29 Pts)**

- Time limit: ~~480~~ 10 seconds.
- No extra restrictions.


---

---
title: "矩阵链排序问题"
layout: "post"
diff: NOI/NOI+/CTSC
pid: P1753
tag: ['动态规划 DP', '图论', '区间 DP', '图论建模', '可并堆', 'Ad-hoc']
---
# 矩阵链排序问题
## 题目描述

给定 $n$ 个矩阵，已知第 $i$ 个矩阵 $M_i$ 的大小为 $w_i$ 行 $w_{i+1}$ 列，而我们并不关心其内容。我们考虑将其按照顺序相乘（称其为链乘积）：

$$ M = M_1 \times M_2 \times \cdots \times M_n $$

矩阵乘法并不满足交换律，但是其满足结合律，因此我们可以通过合理安排结合顺序，尽可能减少需要的运算次数。在此题中，我们定义将一个大小为 $a \times b$ 的矩阵乘以一个大小为 $b \times c$ 的矩阵需要 $abc$ 次运算。

请你算出将题目所给的 $n$ 个矩阵进行链乘积所需的最少运算数。为了方便起见，你不需要构造方案。
## 输入格式

输入的第一行为一个正整数 $n$，代表矩阵的数量。

接下来的一行包含 $n+1$ 个正整数，其中第 $i$ 个整数为 $w_i$，含义参考题目描述。
## 输出格式

输出包含一个整数，代表最小运算次数。
## 样例

### 样例输入 #1
```
3
5 3 2 6
```
### 样例输出 #1
```
90
```
## 提示

样例解释：样例告诉我们有 $n = 3$ 个矩阵，其大小分别是 $5 \times 3$，$3 \times 2$ 和 $2 \times 6$。分别考虑两种乘法顺序：

- 先将 $M_1$ 和 $M_2$ 相乘得到一个 $5 \times 2$ 的矩阵，然后和 $M_3$ 相乘，此时运算次数为 $5 \times 3 \times 2 + 5 \times 2 \times 6 = 90$；
- 先将 $M_2$ 和 $M_3$ 相乘得到一个 $3 \times 6$ 的矩阵，然后和 $M_1$ 相乘，此时运算次数为 $3 \times 2 \times 6 + 5 \times 3 \times 6 = 126$。

本题要求运算次数最少，因此答案为 $90$。

---

对所有的数据，$1 \leq n \leq 2 \times 10^6$，$1 \leq w \leq 10^4$。其中：

- 对 $30\%$ 的数据，满足 $n \leq 500$；
- 对另外 $30\%$ 的数据，满足 $n \leq 2 \times 10^5$。


---

---
title: "[NOI2015] 小园丁与老司机"
layout: "post"
diff: NOI/NOI+/CTSC
pid: P2304
tag: ['动态规划 DP', '2015', 'NOI', '网络流', 'Special Judge', '图论建模']
---
# [NOI2015] 小园丁与老司机
## 题目描述

小园丁 Mr. S 负责看管一片田野，田野可以看作一个二维平面。田野上有 $n$ 棵 许愿树，编号 $1,2,3,\dots,n$ ，每棵树可以看作平面上的一个点，其中第 $i$ 棵树 $(1 \leq i \leq n)$ 位于坐标 $(x_i, y_i)$ 。任意两棵树的坐标均不相同。

老司机 Mr. P 从原点 $(0,0)$ 驾车出发，进行若干轮行动。每一轮，Mr. P 首先选择任意一个满足以下条件的方向：

1.为左、右、上、左上 $45\degree$、右上 $45\degree$ 五个方向之一。

2.沿此方向前进可以到达一棵他尚未许愿过的树。

完成选择后，Mr.P 沿该方向直线前进，必须到达该方向上距离最近的尚未许愿的树，在树下许愿并继续下一轮行动。如果没有满足条件的方向可供选择，则停止行动。他会采取最优策略，在尽可能多的树下许愿。若最优策略不唯一，可以选择任意一种。

不幸的是，小园丁 Mr.S 发现由于田野土质松软，老司机 Mr.P 的小汽车在每轮行进过程中，都会在田野上留下一条车辙印，一条车辙印可看作以两棵树（或原点和一棵树）为端点的一条线段。

在 Mr.P 之后，还有很多许愿者计划驾车来田野许愿，这些许愿者都会像 Mr.P 一样任选一种最优策略行动。Mr.S 认为非左右方向（即上、左上  $45\degree$、右 上 $45\degree$ 三个方向）的车辙印很不美观，为了维护田野的形象，他打算租用一些轧路机，在这群许愿者到来之前夯实所有“可能留下非左右方向车辙印”的地面。“可能留下非左右方向车辙印”的地面应当是田野上的若干条线段，其中每条线段都包含在某一种最优策略的行进路线中。每台轧路机都采取满足以下三个条件的工作模式：

1.从原点或任意一棵树出发。

2.只能向上、左上 $45\degree$、右上 $45\degree$ 三个方向之一移动，并且只能在树下改变方向或停止。

3.只能经过“可能留下非左右方向车辙印”的地面，但是同一块地面可以 被多台轧路机经过。

现在 Mr. P 和 Mr. S 分别向你提出了一个问题：

1.请给 Mr.P 指出任意一条最优路线。

2.请告诉 Mr.S 最少需要租用多少台轧路机。
## 输入格式

第 $1$ 行包含 $1$ 个正整数 $n$，表示许愿树的数量。

接下来 $n$ 行，第 $i+1$ 行包含 $2$ 个整数 $x_i,y_i$，中间用单个空格隔开，表示第 $i$ 棵许愿树的坐标。
## 输出格式

包括 $3$ 行。

第 $1$ 行输出 $1$ 个整数 $m$，表示 Mr. P 最多能在多少棵树下许愿。

输出文件的第 $2$ 行输出 $m$ 个整数，相邻整数之间用单个空格隔开，表示 Mr.P 应该依次在哪些树下许愿。

输出文件的第 $3$ 行输出 $1$ 个整数，表示 Mr. S 最少需要租用多少台轧路机。

## 样例

### 样例输入 #1
```
6
-1 1
1 1
-2 2
0 8
0 9
0 10

```
### 样例输出 #1
```
3
2 1 3
3

```
### 样例输入 #2
```
4
0 1
-2 1
2 1
3 2

```
### 样例输出 #2
```
4
1 2 3 4
2
```
## 提示

#### 样例 1 解释

最优路线共 $2$ 条，可许愿 $3$ 次：$(0,0) \rightarrow (1,1) \rightarrow (-1,1) \rightarrow (-2,2)$ 或 $(0,0) \rightarrow (0,8) \rightarrow (0,9) \rightarrow (0,10)$。

至少 $3$ 台轧路机，路线是 $(0,0) \rightarrow (1,1)$，$(-1,1) \rightarrow (-2,2)$ 和 $(0,0) \rightarrow (0,8) \rightarrow (0,9) \rightarrow (0,10)$。

#### 样例 2 解释

最优路线唯一：$(0,0) \rightarrow (0,1) \rightarrow (-2,1) \rightarrow (2,1) \rightarrow (3,2)$，可许愿 $4$ 次。其中在 $(0,1)$ 许愿后，从 $(-2,1)$ 出发沿着向右的方向能够到达的最近的未许愿过的树是 $(2,1)$，所以可以到达 $(2,1)$。

而如果沿着 $(0,0) \rightarrow (0,1) \rightarrow (2,1) \rightarrow (-2,1)$ 的方向前进，此时 $(-2,1)$ 右边所有树都是许愿过的，根据题目条件规定，停止前进。故无法获得最优解。

$(0,0) \rightarrow (0,1)$ 与 $(2,1) \rightarrow (3,2)$ 会留下非左右方向车辙印，需 $2$ 台轧路机。

![](https://cdn.luogu.com.cn/upload/pic/1509.png)


---

---
title: "[CQOI2017] 老C的方块"
layout: "post"
diff: NOI/NOI+/CTSC
pid: P3756
tag: ['2017', '重庆', '各省省选', '网络流', '图论建模', '最小割']
---
# [CQOI2017] 老C的方块
## 题目描述

老 C 是个程序员。

作为一个懒惰的程序员，老 C 经常在电脑上玩方块游戏消磨时间。游戏被限定在一个由小方格排成的 $R$ 行 $C$ 列网格上，如果两个小方格有公共的边，就称它们是相邻的，而且有些相邻的小方格之间的公共边比较特殊。特殊的公共边排列得有很强的规律。首先规定，第 $1$ 行的前两个小方格之间的边是特殊边。然后，特殊边在水平方向上每 $4$ 个小方格为一个周期，在竖直方向上每 $2$ 个小方格为一个周期。所有的奇数列与下一列之间都有特殊边，且所在行的编号从左到右奇偶交替。

下图所示是一个 $R=C=8$ 的网格，蓝色标注的边是特殊边。首先，在第 $1$ 行，第 $1$ 列和第 $2$ 列之间有一条特殊边。因为竖直方向周期为 $2$，所以所有的奇数行，第 $1$ 列和第 $2$ 列之间都有特殊边。因为水平方向周期为 $4$，所以所有奇数行的第 $5$ 列和第 $6$ 列之间也有特殊边，如果网格足够大，所有奇数行的第 $9$ 列和第 $10$ 列、第 $13$ 列和第 $14$ 列之间都有特殊边。因为所有的奇数列和下一列之间都有特殊边，所以第 $3$ 列和第 $4$ 列、第 $7$ 列和第 $8$ 列之间也有特殊边，而所在行的编号从左到右奇偶交替，所以它们的特殊边在偶数行。如果网格的规模更大，我们可以用同样的方法找出所有的特殊边。

 ![](https://cdn.luogu.com.cn/upload/pic/5092.png) 

网格的每个小方格刚好可以放入一个小方块，在游戏的一开始，有些小方格已经放上了小方块，另外的小方格没有放。老 C 很讨厌下图所示的图形，如果他发现有一些小方块排列成了它讨厌的形状（特殊边的位置也要如图中所示），就很容易弃疗，即使是经过任意次旋转、翻转后排列成讨厌的形状，老 C 也同样容易弃疗。

 ![](https://cdn.luogu.com.cn/upload/pic/5093.png) 

为了防止弃疗，老 C 决定趁自己还没有弃疗，赶紧移除一些格子里小方块，使得剩下的小方块不能构成它讨厌的形状。但是游戏里每移除一个方块都是要花费一些金币的，每个方块需要花费的金币有多有少参差不齐。老 C 当然希望尽可能少的使用游戏里的金币，但是最少要花费多少金币呢？老 C 懒得思考，就把这个问题交给你了。

## 输入格式

第一行有 $3$ 个正整数 $C,R,n$，表示 $C$ 列 $R$ 行的网格中，有 $n$ 个小方格放了小方块。

接下来 $n$ 行，每行 $3$ 个正整数 $x,y,w$，表示在第 $x$ 列第 $y$ 行的小方格里放了小方块，移除它需要花费 $w$ 个金币。保证不会重复，且都在网格范围内。

## 输出格式

输出一行，包含一个整数，表示最少花费的金币数量。

## 样例

### 样例输入 #1
```
2 2 4
1 1 5 
1 2 6 
2 1 7 
2 2 8 
```
### 样例输出 #1
```
5
```
### 样例输入 #2
```
3 3 7 
1 1 10 
1 2 15 
1 3 10 
2 1 10 
2 2 10 
2 3 10 
3 1 10 
```
### 样例输出 #2
```
15
```
## 提示

【输入输出样例 2 说明】 如图所示。容易发现，如果不移除第 $1$ 列第 $2$ 行的小方块，则至少要移除两个小方块，才能不包含老 C 讨厌的图形，花费至少 $20$ 个金币；而删除第 $1$ 列第 $2$ 行的小方块后，原有的讨厌图形全都不存在了，只需要花费 $15$ 个金币。


 ![](https://cdn.luogu.com.cn/upload/pic/5094.png) 

【数据规模与约定】

对于第 $1\sim 2$ 个测试点，$1\le C, R \le 100$，$1\leq n \leq 20$。

对于第 $3\sim 6$ 个测试点，$1 \leq C, R\leq 10^5$，$2000\le n\leq 5000$，数据有梯度。

对于第 $7\sim 10$ 个测试点，$1\leq C, R\leq 10^5$，$30000 \leq n\leq 10^5$，数据有梯度。

对于所有测试点，$1 \leq C, R, n \leq 10^5$，$ 1 \leq w \leq 10^4$。



---

---
title: "[WC2007] 剪刀石头布"
layout: "post"
diff: NOI/NOI+/CTSC
pid: P4249
tag: ['图论', '2007', 'Special Judge', 'O2优化', '图论建模', '费用流', '差分', 'WC']
---
# [WC2007] 剪刀石头布
## 题目描述

在一些一对一游戏的比赛（如下棋、乒乓球和羽毛球的单打）中，我们经常会遇到 $A$ 胜过 $B$，$B$ 胜过 $C$ 而 $C$ 又胜过 $A$ 的有趣情况，不妨形象的称之为剪刀石头布情况。有的时候，无聊的人们会津津乐道于统计有多少这样的剪刀石头布情况发生，即有多少对无序三元组 $(A,B,C)$，满足其中的一个人在比赛中赢了另一个人，另一个人赢了第三个人而第三个人又胜过了第一个人。注意这里无序的意思是说三元组中元素的顺序并不重要，将 $(A, B, C)$、$(A, C, B)$、$(B, A, C)$、$(B, C, A)$、$(C, A, B)$ 和 $(C, B, A)$ 视为相同的情况。

有 $N$ 个人参加一场这样的游戏的比赛，赛程规定任意两个人之间都要进行一场比赛：这样总共有 $\frac{N*(N-1)}{2}$ 场比赛。比赛已经进行了一部分，我们想知道在极端情况下，比赛结束后最多会发生多少剪刀石头布情况。即给出已经发生的比赛结果，而你可以任意安排剩下的比赛的结果，以得到尽量多的剪刀石头布情况。

## 输入格式

输入文件的第 $1$ 行是一个整数 $N$，表示参加比赛的人数。

之后是一个 $N$ 行 $N$ 列的数字矩阵：一共 $N$ 行，每行 $N$ 列，数字间用空格隔开。

在第 $(i+1)$ 行的第 $j$ 列的数字如果是 $1$，则表示 $i$ 在已经发生的比赛中赢了 $j$；该数字若是 $0$，则表示在已经发生的比赛中 $i$ 败于 $j$；该数字是
 $2$，表示 $i$ 和 $j$ 之间的比赛尚未发生。数字矩阵对角线上的数字，即第 $(i+1)$ 行第 $i$ 列的数字都是 $0$，它们仅仅是占位符号，没有任何意义。

输入文件保证合法，不会发生矛盾，当 $i \neq j$ 时，第 $(i+1)$ 行第 $j$ 列和第 $(j+1)$ 行第 $i$ 列的两个数字要么都是 $2$，要么一个是 $0$ 一个是 $1$。

## 输出格式

输出文件的第 $1$ 行是一个整数，表示在你安排的比赛结果中，出现了多少剪刀石头布情况。

输出文件的第 $2$  行开始有一个和输入文件中格式相同的 $N$ 行 $N$ 列的数字矩阵。第 $(i+1)$ 行第 $j$ 个数字描述了 $i$ 和 $j$ 之间的比赛结果，$1$ 表示 $i$ 赢了 $j$，$0$ 表示 $i$ 负于 $j$，与输入矩阵不同的是，在这个矩阵中没有表示比赛尚未进行的数字 $2$；对角线上的数字都是 $0$。输出矩阵要保证合法，不能发生矛盾。

## 样例

### 样例输入 #1
```
3
0 1 2
0 0 2
2 2 0

```
### 样例输出 #1
```
1
0 1 0
0 0 1
1 0 0

```
## 提示

### 【评分标准】
对于每个测试点，仅当你的程序的输出第一行的数字和标准答案一致，且给出了一个与之一致的合法方案，你才能得到该测试点的满分，否则该测试点得 $0$ 分。
### 【数据范围】
$30\%$ 的数据中，$N \leq 6$；

$100\%$ 的数据中，$N \leq 100$。



---

---
title: "[八省联考 2018] 劈配"
layout: "post"
diff: NOI/NOI+/CTSC
pid: P4382
tag: ['2018', '各省省选', '网络流', 'O2优化', '枚举', '图论建模']
---
# [八省联考 2018] 劈配
## 题目背景

一年一度的综艺节目《中国新代码》又开始了。Zayid 从小就梦想成为一名程序员，他觉得这是一个展示自己的舞台，于是他毫不犹豫地报名了。
## 题目描述

轻车熟路的 Zayid 顺利地通过了海选，接下来的环节是导师盲选，这一阶段的规则是这样的：

总共 $n$ 名参赛选手（编号从 $1$ 至 $n$ ）每人写出一份代码并介绍自己的梦想。接着 由所有导师对这些选手进行排名。为了避免后续的麻烦，规定**不存在排名并列的情况**。

同时，每名选手都将独立地填写一份志愿表，来对总共 $m$ 位导师（编号从 $1$ 至 $m$ ）作出评价。志愿表上包含了共 $m$ 档志愿。对于每一档志愿，选手被允许填写最多 $C$ 位导师，每位导师最多被每位选手填写**一次**（**放弃某些导师也是被允许的**）。

在双方的工作都完成后，进行录取工作。每位导师都有自己战队的人数上限，这意味着可能有部分选手的较高志愿、甚至是全部志愿无法得到满足。节目组对“前 $i$ 名的录取结果最优”作出如下定义：

- 前 $1$ 名的录取结果最优，**当且仅当**第 $1$ 名被其最高非空志愿录取（**特别地**，如果第 $1$ 名没有填写志愿表，那么该选手出局）。

- 前 $i$ 名的录取结果最优，当且仅当在前 $i - 1$ 名的录取结果最优的情况下，第 $i$ 名 被其理论可能的最高志愿录取（特别地，如果第 $i$ 名没有填写志愿表，或其所有志愿中的导师战队均已满员，那么该选手出局）。

如果一种方案满足“前 $n$ 名的录取结果最优”，那么我们可以简称这种方案是**最优的**。

举例而言，$2$ 位导师 $\rm T$ 老师、 $\rm F$ 老师的战队人数上限分别都是 $1$ 人；$2$ 位选手 Zayid 、DuckD 分列第 $1$ 、 $2$ 名。那么下面 $3$ 种志愿表及其对应的最优录取结果如表中所示：

![](https://cdn.luogu.com.cn/upload/pic/17003.png)

![](https://cdn.luogu.com.cn/upload/pic/17004.png)

可以证明，对于上面的志愿表，对应的方案都是唯一的最优录取结果。

每个人都有一个自己的理想值 $s_i$ ，表示第 $i$ 位同学希望自己被第 $s_i$ 或更高的志愿录取，如果没有，那么他就会非常沮丧。

现在，所有选手的志愿表和排名都已公示。巧合的是，每位选手的排名都恰好与它们的编号相同。

对于每一位选手，Zayid 都想知道下面两个问题的答案：

- 在最优的录取方案中，他会被第几志愿录取。

- 在其他选手相对排名不变的情况下，至少上升多少名才能使得他不沮丧。

作为《中国新代码》的实力派代码手，Zayid 当然轻松地解决了这个问题。不过他还是想请你再算一遍，来检验自己计算的正确性。
## 输入格式

每个测试点包含多组测试数据，第一行 $2$ 个用空格隔开的非负整数 $T,C$ ，分别表示数据组数、每档志愿最多允许填写的导师数目。

接下来依次描述每组数据，对于每组数据：

- 第 $1$ 行两个用空格隔开的正整数 $n,m$ 。

> $n,m$ 分别表示选手的数量、导师的数量。

- 第 $2$ 行 $m$ 个用空格隔开的正整数：其中第 $i$ 个整数为 $b_i$ 。

> $b_i$ 表示编号为 $i$ 的导师战队人数的上限。

第 $3$ 行至第 $n + 2$ 行，每行 $m$ 个用空格隔开的非负整数：其中第 $i + 2$ 行左起第 $j$ 个数为 $a_{i,j}$ 。

> $a_{i,j}$ 表示编号为 $i$ 的选手将编号为 $j$ 的导师编排在了第 $a_{i,j}$ 志愿。特别地，如果 $a_{i,j}= 0$ ，则表示该选手没有将该导师填入志愿表。

> 在这一部分，保证每行中不存在某一个正数出现超过 $C$ 次（ **$0$ 可能出现超过 $C$ 次**），同时保证所有  $a_{i,j} \leqslant m$ 。

- 第 $n + 3$ 行 $n$ 个用空格隔开的正整数，其中第 $i$ 个整数为 $s_i$ 。

> $s_i$ 表示编号为 $i$ 的选手的理想值。

> 在这一部分，保证 $s_i \leqslant m$ 。
## 输出格式

按顺序输出每组数据的答案。对于每组数据，输出 $2$ 行：

- 第 $1$ 行输出 $n$ 个用空格隔开的正整数，其中第 $i$ 个整数的意义为：

	在最优的录取方案中，编号为 $i$ 的选手会被该档志愿录取。

> **特别地，如果该选手出局，则这个数为 $m + 1$** 。

- 第 $2$ 行输出 $n$ 个用空格隔开的非负整数，其中第 $i$ 个整数的意义为：

	使编号为 $i$ 的选手不沮丧，最少需要让他上升的排名数。
    
> **特别地，如果该选手一定会沮丧，则这个数为 $i$ 。**
## 样例

### 样例输入 #1
```
3 5
2 2
1 1
2 2
1 2
1 1
2 2
1 1
1 2
1 2
2 1
2 2
1 1
0 1
0 1
2 2
```
### 样例输出 #1
```
2 1
1 0
1 2
0 1
1 3
0 1
```
### 样例输入 #2
```
1 5
4 3
2 1 1
3 1 3
0 0 1
3 1 2
2 3 1
2 3 3 3
```
### 样例输出 #2
```
1 1 3 2
0 0 0 0
```
## 提示

- 样例 $1$ 解释

三组数据分别与【题目描述】中的三个表格对应。

对于第 $1$ 组数据：由于选手 $1$ 没有填写第一志愿，所以他一定无法被第一志愿录取，也就一定会沮丧。选手 $2$ 按原排名就不沮丧，因此他不需要提升排名。

对于第 $2$ 组和第 $3$ 组数据： $1$ 号选手都不需要提升排名。而希望被第一志愿录取的 $2$ 号选手都必须升到第 $1$ 名才能如愿。

- 样例 $2$ 解释

$1$ 号选手的第一志愿只填写了 $2$ 号导师，因此 $1$ 号选手必定被 $2$ 号导师录取。

$2$ 号选手的第一志愿只填写了 $3$ 号导师，因此 $2$ 号选手必定被 $3$ 号导师录取。

由于 $2,3$ 号导师均满员，且 $3,4$ 号选手均填写了 $1$ 号导师，因此他们都会被 $1$ 号导师录取。

所以 $1,2$ 号选手均被第 $1$ 志愿录取，$3$ 号选手被第 $3$ 志愿录取， $4$ 号选手被第 $2$ 志愿录取。

由于他们都如愿以偿了，所以他们都不需要提升名次。


|测试点编号|$n \leqslant$|$m \leqslant$|$C$|其他约定|
|:----:|:---:|:----:|:----:|:----:|
|1| $10$|$1$|$=1$|无|
|2|$10$|$2$|$=2$|$s_i=m$|
|3|$10$|$3$|$=3$|无|
|4|$100$|$100$|$=1$|$b_i=1$|
|5|$100$|$100$|$=1$|无|
|6|$200$|$200$|$=1$|$b_i=1$|
|7|$200$|$200$|$=1$|无|
|8|$100$|$100$|$=10$|无|
|9|$200$|$200$|$=10$|$b_i=1$|
|10|$200$|$200$|$=10$|无|

- 对于所有测试点，保证 $ T \leqslant 5$ 。

- 对于所有测试点钟的所有数据，保证 $ m \leqslant n \leqslant 200, b_i \leqslant n$


---

---
title: "[ZJOI2011] 营救皮卡丘"
layout: "post"
diff: NOI/NOI+/CTSC
pid: P4542
tag: ['2011', '各省省选', '浙江', '图论建模', '最短路', '费用流']
---
# [ZJOI2011] 营救皮卡丘
## 题目描述

皮卡丘被火箭队用邪恶的计谋抢走了！这三个坏家伙还给小智留下了赤果果的挑衅！为了皮卡丘，也为了正义，小智和他的朋友们义不容辞的踏上了营救皮卡丘的道路。

火箭队一共有$N$个据点，据点之间存在$M$条双向道路。据点分别从$1$到$N$标号。小智一行$K$人从真新镇出发，营救被困在$N$号据点的皮卡丘。为了方便起见，我们将真新镇视为$0$号据点，一开始$K$个人都在$0$号点。

由于火箭队的重重布防，要想摧毁$K$号据点，必须按照顺序先摧毁$1$到$K-1$号据点，并且，如果$K-1$号据点没有被摧毁，由于防御的连锁性，小智一行任何一个人进入据点$K$，都会被发现，并产生严重后果。因此，在$K-1$号据点被摧毁之前，任何人是不能够经过$K$号据点的。

为了简化问题，我们忽略战斗环节，小智一行任何一个人经过$K$号据点即认为$K$号据点被摧毁。被摧毁的据点依然是可以被经过的。

$K$个人是可以分头行动的，只要有任何一个人在$K-1$号据点被摧毁之后，经过$K$号据点，$K$号据点就被摧毁了。显然的，只要$N$号据点被摧毁，皮卡丘就得救了。

野外的道路是不安全的，因此小智一行希望在摧毁$N$号据点救出皮卡丘的同时，使得$K$个人所经过的道路的长度总和最少。

请你帮助小智设计一个最佳的营救方案吧！
## 输入格式

第一行包含三个正整数$N,M,K$。表示一共有$N+1$个据点，分别从$0$到$N$编号，以及$M$条无向边。一开始小智一行共$K$个人均位于$0$号点。 

接下来$M$行，每行三个非负整数，第i行的整数为$A_i$，$B_i$，$L_i$。表示存在一条从$A_i$号据点到$B_i$号据点的长度为$L_i$的道路。
## 输出格式

仅包含一个整数$S$，为营救皮卡丘所需要经过的最小的道路总和。
## 样例

### 样例输入 #1
```
3 4 2
0 1 1
1 2 1
2 3 100
0 3 1
```
### 样例输出 #1
```
3
```
## 提示

【样例说明】

小智和小霞一起前去营救皮卡丘。在最优方案中，小智先从真新镇前往1号点，接着前往2号据点。当小智成功摧毁2号据点之后，小霞从真新镇出发直接前往3号据点，救出皮卡丘。

对于100%的数据满足$N ≤ 150, M ≤ 20 000, 1 ≤ K ≤ 10, L_i ≤ 10 000$, 保证小智一行一定能够救出皮卡丘。

至于为什么$K ≤ 10$，你可以认为最终在小智的号召下，小智，小霞，小刚，小建，小遥，小胜，小光，艾莉丝，天桐，还有去日本旅游的黑猫警长，一同前去大战火箭队。


---

---
title: "[NEERC 2016] Binary Code"
layout: "post"
diff: NOI/NOI+/CTSC
pid: P6965
tag: ['2016', 'Special Judge', '图论建模', '2-SAT', '字典树 Trie', 'ICPC']
---
# [NEERC 2016] Binary Code
## 题目描述



Ben has recently learned about binary prefix codes. A binary code is a set of $n$ distinct nonempty code words $s_{i}$ , each consisting of 0s and $1s.$ A code is called a prefix code if for every $i ≠ j$ neither $s_{i}$ is a prefix of $s_{j}$ nor $s_{j}$ is a prefix of $s_{i}$ . A word $x$ is called a prefix of a word $w$ if there exists a possibly empty word $y$ , such that xy $= w$ . For example, $x = 11$ is a prefix of $w = 110$ and $x = 0100$ is a prefix of $w = 0100$ .

Ben found a paper with $n$ lines of binary code in it. However, this paper is pretty old and there are some unreadable characters. Fortunately, each word contains at most one unreadable character.

Ben wants to know whether these $n$ lines could represent a binary prefix code. In other words, can he replace every unreadable character with $0$ or $1$ , so that the code becomes a prefix code?


## 输入格式



The first line contains integer $n$ -- the number of code words $(1 \le n \le 5 · 10^{5}).$

Next $n$ lines contain nonempty code word records, one per line. Each code word record consists of `0`, `1` and `?` characters. Every code word record contains at most one `?` character that represents unreadable character.

The total length of words does not exceed $5 · 10^{5}$ .


## 输出格式



Output `NO` in the first line if the code cannot be a prefix code.

Otherwise, output `YES` in the first line. Next $n$ lines shall contain code words in the same order as the corresponding code word records in the input.

If there are several prefix codes, that could have been written on the paper, output any one.


## 样例

### 样例输入 #1
```
4
00?
0?00
?1
1?0

```
### 样例输出 #1
```
YES
000
0100
11
100

```
### 样例输入 #2
```
3
0100
01?0
01?0

```
### 样例输出 #2
```
NO

```
## 提示

Time limit: 2 s, Memory limit: 2048 MB. 


## 题目翻译

### 题目描述

给定 `n` 个01串，每个字符串至多有一位是未知的，可以填 `0` 或 `1` ，求是否存在一种方案，使得任意一个字符串不是其它任意一个字符串的前缀

### 输入格式

第一行是一个正整数 `n` ，代表字符串的数量。 $(1 \leq n \leq 5 \cdot 10^5)$

接下来 `n` 行每行一个字符串，只可能由 `0` 、 `1` 或 `?` 组成。 `?` 代表未知的位置，每个字符串最多一个。

保证字符串总长度不超过 $5 \cdot 10^5$ 。

### 输出格式

如果无解，只需要输出 `NO` 。

如果有解，在第一行输出 `YES` ，接下来 `n` 行输出方案。

如果有多组解，只需要输出任意一组。


---

