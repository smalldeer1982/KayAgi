---
title: "[HBCPC2024] Lili Likes Polygons"
layout: "post"
diff: NOI/NOI+/CTSC
pid: P10860
tag: ['2024', '离散化', '网络流', 'O2优化', 'XCPC', '湖北']
---
# [HBCPC2024] Lili Likes Polygons
## 题目描述

Lili and Nana are weeding in the backyard of Lili’s house. They are repeatedly selecting rectangular areas and removing all the grass within them.

The backyard can be visualized as a 2D grid, each square cell representing one unit area. They have performed a total of $n$ operations. During the $i$-th operation, they choose the left, bottom, right, and top sides of a rectangle, denoted as $l_i, b_i, r_i, t_i$, and clear all the cells within this rectangle using a lawnmower. **Note that these rectangles may overlap with each other.**

Let $[l_i, r_i]\times[b_i, t_i]$ denote a rectangle.

Here is an example illustrated in the following figure.  They have selected $2$ rectangles, with the first rectangle being $[1, 5]\times[2, 3]$ and the second rectangle being $[2, 3]\times[1, 4]$.

![](https://cdn.luogu.com.cn/upload/image_hosting/nb9g0n5i.png)

After the $n$ weeding operations, the union of the bare area may not be connected but all the sides are horizontal or vertical. Thus, the union becomes orthogonal polygon(s), some of which contain polygon holes.  Moreover, there can be bare cells inner some holes. Please see the example inputs for more details and illustrations.

Now, they want to restore the land by planting some plants on the bare cells. Lili likes polygons, especially rectangles. Therefore, they want to select several rectangles, and these rectangles do not overlap with each other and exactly cover all the bare cells. Then, they plant different plants in different rectangles they selected.

For example, here is a feasible selection of rectangles for the aforementioned case: choose $[1, 1]\times [2, 3]$, $[2, 3]\times[1, 4]$ and $[4, 5]\times [2, 3]$.

After playing for a while, these two little girls have become tired, so they want to know the minimum number of non-overlapping rectangles that can cover all the bare cells.
## 输入格式

The first line contains a single integer $n$ ($1\leq n\leq 300$) --- the number of rectangles when they weed.

The following $n$ lines each contain $4$ integers, and the $i$-th line contains $l_i, b_i, r_i, t_i$ ($1\leq l_i, b_i, r_i, t_i\leq 10^9, l_i\leq r_i, b_i\leq t_i$) --- the left, bottom, right, and top sides of the $i$-th rectangle.

It is guaranteed the sum of the endpoints of the bare area (polygon(s) with polygonal holes) does not exceed $2000$.
## 输出格式

Output a single integer on a single line denoting the minimum number of rectangles they need to select to plant plants on all the bare cells.
## 样例

### 样例输入 #1
```
8
1 1 1 1
1 2 1 2
1 3 1 3
2 1 2 1
2 3 2 3
3 1 3 1
3 2 3 2
3 3 3 3
```
### 样例输出 #1
```
4
```
### 样例输入 #2
```
2
1 1 100 100
1 501 100 600
```
### 样例输出 #2
```
2
```
### 样例输入 #3
```
4
1 1 4 1
1 4 5 4
1 1 1 4
4 1 4 5
```
### 样例输出 #3
```
5
```
### 样例输入 #4
```
9
1 1 9 1
1 1 1 9
1 9 9 9
9 1 9 9
3 3 7 3
3 3 3 7
3 7 7 7
7 3 7 7
5 5 5 5
```
### 样例输出 #4
```
9
```
## 提示

For the first example, an optimal selection is $[1, 1]\times [1, 3]$, $[2, 1]\times [2, 1]$,  $[2, 3]\times [2, 3]$ and $[3, 1]\times [3, 3]$.

For the second example, an optimal selection is $[1, 1]\times [100, 100]$ and $[1, 501]\times [100, 600]$.

For the third example, an optimal selection is $[1, 1]\times [4, 1]$, $[1, 4]\times [5, 4]$,  $[1, 2]\times [1, 3]$, $[4, 2]\times [4, 3]$ and $[4, 5]\times [4, 5]$.

For the fourth example, the bare area is illustrated in the following figure. 

![](https://cdn.luogu.com.cn/upload/image_hosting/uun9l7e6.png)
## 题目翻译

### 题目描述
莉莉和娜娜正在莉莉家后院除草。她们反复选择矩形区域，并移除其中的所有草坪。

后院可以被视为一个二维网格，每个方格表示一个单位面积。她们共进行了 $n$ 次操作。在第 $i$ 次操作中，她们选择了一个矩形的左、下、右、上的边界，分别表示为 $l_i, b_i, r_i, t_i$，并使用割草机清除该矩形内的所有方格。**注意，这些矩形可能会相互重叠。**

用 $[l_i, r_i] \times [b_i, t_i]$ 表示一个矩形。

以下是一个例子，如图所示。她们选择了 $2$ 个矩形，第一个矩形是 $[1, 5] \times [2, 3]$，第二个矩形是 $[2, 3] \times [1, 4]$。

经过 $n$ 次除草操作后，裸露区域的联合可能不连通，但所有边都是水平或垂直的。因此，联合区域变成了一个或多个直角多边形，其中一些可能包含多边形孔洞。此外，在某些孔洞内部可能会有裸露的方格。更多细节和图示请参见示例输入。

现在，她们想通过在裸露的方格上种植植物来恢复土地。莉莉喜欢多边形，特别是矩形。因此，她们想选择若干个矩形，这些矩形之间不重叠，并且能够完全覆盖所有的裸露方格。然后，她们将在选择的不同矩形中种植不同的植物。

例如，下面是上述情况的一个可行的矩形选择：选择 $[1, 1] \times [2, 3]$、$[2, 3] \times [1, 4]$ 和 $[4, 5] \times [2, 3]$。

玩了一会儿，这两个小女孩已经累了，所以她们想知道覆盖所有裸露方格的最小不重叠矩形数量。


### 输入格式

第一行包含一个整数 $n$ ($1 \leq n \leq 300$) —— 表示除草时使用的矩形数量。

接下来的 $n$ 行每行包含 $4$ 个整数，第 $i$ 行包含 $l_i, b_i, r_i, t_i$ ($1 \leq l_i, b_i, r_i, t_i \leq 10^9, l_i \leq r_i, b_i \leq t_i$) —— 表示第 $i$ 个矩形的左、下、右、上边界。

保证裸露区域的端点总数（多边形及其孔洞）不超过 $2000$。

### 输出格式

在一行上输出一个整数，表示覆盖所有裸露方格所需选择的最小矩形数量。

### 说明/提示

对于第一个例子，最优选择是 $[1, 1] \times [1, 3]$、$[2, 1] \times [2, 1]$、$[2, 3] \times [2, 3]$ 和 $[3, 1] \times [3, 3]$。

对于第二个例子，最优选择是 $[1, 1] \times [100, 100]$ 和 $[1, 501] \times [100, 600]$。

对于第三个例子，最优选择是 $[1, 1] \times [4, 1]$、$[1, 4] \times [5, 4]$、$[1, 2] \times [1, 3]$、$[4, 2] \times [4, 3]$ 和 $[4, 5] \times [4, 5]$。

对于第四个例子，裸露区域如下图所示。

![](https://cdn.luogu.com.cn/upload/image_hosting/uun9l7e6.png)

翻译者：[Immunoglobules](https://www.luogu.com.cn/user/1066251)


---

---
title: "[COTS 2019] 挑战 Izazov"
layout: "post"
diff: NOI/NOI+/CTSC
pid: P11224
tag: ['2019', '网络流', 'Special Judge', '二分图', 'COCI（克罗地亚）']
---
# [COTS 2019] 挑战 Izazov
## 题目背景


译自 [Izborne Pripreme 2019 (Croatian IOI/CEOI Team Selection)](https://hsin.hr/pripreme2019/) D2T1。$\texttt{15s,0.5G}$。
## 题目描述


给定 $N\times M$ 的黑白矩阵。用尽可能少数量的矩形覆盖住所有黑色格子，要求：
- 每个黑色格子**恰好被一个**矩形覆盖；
- 任意两个矩形不重叠；
- 矩形不覆盖白色格子。

并输出方案。
## 输入格式

第一行，两个正整数 $N,M$。

接下来一个 $N\times M$ 的矩阵，每个位置是 $\texttt{C}$ 或者 $\texttt{B}$。其中，$\texttt{C}$ 代表黑色（克罗地亚语「crno」），$\texttt{B}$ 代表白色（克罗地亚语「bijelo」）。

## 输出格式


输出 $N$ 行，每行 $M$ 个数，表示你的方案：
- 未被覆盖的区域，用 $0$ 表示；
- 否则，设使用了 $K$ 个矩形，将矩形用 $1\sim K$ 标号后，对应位置用覆盖它的矩形编号表示。

每一行相邻的数要用空格隔开。
## 样例

### 样例输入 #1
```
4 5
CCBCB
CCBBB
CCCBB
CCCBB
```
### 样例输出 #1
```
1 1 0 2 0
1 1 0 0 0
3 3 3 0 0
3 3 3 0 0
```
### 样例输入 #2
```
7 5
CCCBB
BCBBB
BCCCB
BCCCB
CCCCC
BBBBB
BCCCB
```
### 样例输出 #2
```
1 1 1 0 0
0 2 0 0 0
0 3 3 3 0
0 3 3 3 0
4 4 4 4 4
0 0 0 0 0
0 5 5 5 0
```
### 样例输入 #3
```
5 11
BBCCCBCCCBC
BCCBCBBCCCC
CCCCBCCCCCC
BCBCCCBCCCB
CCCCBCBBCCB
```
### 样例输出 #3
```
0 0 1 1 1 0 2 2 2 0 3
0 4 4 0 5 0 0 6 6 6 3
7 7 7 7 0 8 8 6 6 6 3
0 9 0 10 10 10 0 6 6 6 0
11 11 11 11 0 12 0 0 13 13 0
```
## 提示



对于 $100\%$ 的数据，保证 $1\le N,M\le 500$。


| 测试点编号 | $N,M\le $    | 得分 |  
| :--: | :--: |:--: |  
| $ 1\sim 5 $    | $ 26 $ |   $ 25 $   |  
| $ 6\sim 10 $    | $ 100 $ |  $ 25 $   |  
| $ 11\sim 15 $    | $ 250 $ | $ 25 $   |  
| $ 16\sim 20 $    | $ 500 $ |$ 25 $   |  

【计分方式】

如果你输出的是最优解，得满分。

否则，设最优解用的矩形数量为 $A$，你的解用的矩形数量为 $B$，该测试点得分为 $0.75\cdot (A/B)^{10}\cdot 5$ 分。 


---

---
title: "基础构造练习题 2（P11635 加强版）"
layout: "post"
diff: NOI/NOI+/CTSC
pid: P12081
tag: ['搜索', '网络流', '交互题', 'Special Judge', '剪枝', '通信题']
---
# 基础构造练习题 2（P11635 加强版）
## 题目背景

本题较 P11635（CTS 2025 Day 2 T2）添加了 $K = 8, 9, 10$ 的情形，并提高了 $K = 6, 7$ 时 $N$ 的限制。注意：P11635 的所有 `unsigned int` 需要修改为 `unsigned long long`。
## 题目描述

**这是一道通信题。**

有若干个节点，它们一开始分别存储有一个数字 $a_i \in \{0, 1\}$，它们想要通过 $K$ 轮通信知道其它每个节点存储的数字。

每一轮通信开始的时候，每个节点 $i$ 对每个节点 $j$，都会选择一个数字 $c_{i,j} \in \{0, 1\}$，表示它将会向节点 $j$ 发送数字 $c_{i,j}$，而在这轮通信结束的时候，节点 $j$ 会收到所有节点向它发送的数字的和，具体而言节点 $j$ 会收到一个数字 $s_j = \sum_{i} c_{i,j}$。

现在给定 $K$，你需要找到一个尽量大的 $N$，满足在通过 $K$ 轮通信之后每个节点都可以知道所有节点存储的数字。

### 实现细节

**你不需要，也不应该实现 `main` 函数。**

你需要实现以下函数：

1. `int init(int K);`
   - 该函数传入通信总轮数 $K$ 的值。**保证** $1 \leq K \leq 10$。
   - 该函数需要返回你选择的节点数量 $N$，**你需要保证** $1 \leq N \leq 60$。
   - 对于每次代码运行，**保证在任意 `send` 函数调用前，该函数会被交互库调用恰好一次**。

2. `unsigned long long send(int K, int N, int round, int number, const std::vector<int>& received);`
   - 该函数传入通信总轮数 $K$，你实现的 `init` 函数返回的节点数量 $N$，当前通信的轮数 `round`，当前你需要实现的节点的编号 `number`，当前节点之前通信的轮数中收到的数字 `received`，其中 `received[0]` 表示这个节点一开始存储的数字，而 `received[i] (1 \leq i < \text{round})` 表示这个节点第 $i$ 轮通信结束的时候收到的数字。**保证** $1 \leq K \leq 10$，$1 \leq \text{round} \leq K + 1$，$0 \leq \text{number} < N$，**且 `received` 的长度为 `round`**。
   - 若 $1 \leq \text{round} \leq K$，你需要返回一个无符号 $64$ 位整数 $x$ 表示在这轮通信中节点 `number` 发送给所有节点的数字，其中 $x$ 的第 $i$ 位为节点 `number` 发送给节点 $i$ 的数字，高位用 $0$ 补齐。
   - 若 $\text{round} = K + 1$，你需要返回一个无符号 $64$ 位整数 $x$ 表示节点 `number` 经过 $K$ 轮通信后确定的每个节点存储的数字，其中 $x$ 的第 $i$ 位为编号为 $i$ 的节点存储的数字，高位用 $0$ 补齐。
   - 对于每次代码运行，**保证该函数会被交互库调用不超过 $10^5$ 次**。

注意：你需要保证，对于任意两次传入参数相同的函数调用（包括 `init` 和 `send`），返回值也应当相同，否则你的程序将会直接被判定为错误。

题目保证在规定的限制下，交互库在每次代码运行中的运行时间不会超过 $100\, \mathrm{ms}$；交互库使用的内存大小固定，且不超过 $64\, \mathrm{MiB}$。这意味着在每次代码运行中你的代码可以使用至少 $900\, \mathrm{ms}$ 的时间和 $448\,\mathrm{MiB}$ 的空间。

## 提示

### 测试程序方式

**下发文件中的 `grader.cpp` 是提供的交互库参考实现，最终测试时所用的交互库实现与该参考实现有所不同，因此你的解法不应该依赖交互库实现。**

将你的程序命名为 `message.cpp` 并放置于下发文件目录下后，你可以在下发文件目录下使用如下命令进行测试：

```bash
g++ grader.cpp message.cpp -o grader -std=c++17 -O2
./grader
```

上述脚本将从**标准输入**读入以下格式的数据：

- 输入的第一行一个整数 $0$。
- 输入的第二行两个正整数 $T, K$，其中 $T$ 表示进行通信的次数，$K$ 表示每次通信的轮数。你需要保证 $1 \leq T \leq 101$，$1 \leq K \leq 10$。
- 输入的第 $i + 2 (0 \leq i < T)$ 行一个无符号 $64$ 位整数 $x_i$，表示第 $i$ 次通信时每个节点初始存储的数字，其中 $x_i$ 的第 $j$ 位表示 $j$ 号节点初始存储的数字。你需要保证 $\forall 0 \leq i < T, 0 \leq x_i < 2^{64}$。

上述脚本将输出以下格式的数据到**标准输出**：

- 若通信结果正确，则输出 `Accepted! (N = [N], K = [K])`；
- 若通信结果错误，则输出 `Wrong answer!`。

### 下发文件说明

在下发文件中：

1. `grader.cpp` 是提供的交互库参考实现。
2. `template_message.cpp` 是提供的示例代码，你可以在此代码的基础上实现。

### 子任务

本题共有 $10$ 个子任务，每个子任务分值为 $100$ 分，总分为 $1000$ 分。一个子任务的得分为其中所有测试点的得分最小值。

对于所有测试数据，保证 $1 \leq K \leq 10$，且对于每次代码运行，`send` 会被交互库调用不超过 $10^5$ 次。**对于第 $i$ 个子任务，保证 $K = i$。**

### 评分方式

**注意**：

- 你不应当通过非法方式获取交互库的内部信息，如试图直接读取交互库中存储的值，或直接与标准输入、输出流进行交互。此类行为将被视为作弊；
- **最终的评测交互库与样例交互库的实现有所不同，因此你的解法不应该依赖交互库实现。**

**本题首先会受到和传统题相同的限制**，例如编译错误会导致整道题目得 0 分，运行时错误、超过时间限制、超过空间限制等会导致相应测试点得 0 分等。你只能在程序中访问自己定义的和交互库给出的变量及其对应的内存空间，尝试访问其他空间将可能导致编译错误或运行错误。

在上述条件基础上，在每个测试点中，程序得到的分数将按照以下方式计算：

- 若对于任意两次传入参数相同的该函数调用，返回值不同，则获得 0 分；
- 若 $K$ 轮通信后确定的每个节点存储的数字与每个节点初始存储的数字不同，则获得 0 分；
- 否则设 $N$ 为调用函数 `init()` 得到的结果，则该测试点的得分为 $s \times {0.7}^{\max(C(K) - N, 0)}$，其中 $s$ 为该测试点的分值，$C(K)$ 的计算方式如下表所示：

| 子任务编号 $= K =$ | $C(K) =$ |
| :-: | :-: |
| $1$ | $2$ |
| $2$ | $4$ |
| $3$ | $6$ |
| $4$ | $11$ |
| $5$ | $14$ |
| $6$ | $22$ |
| $7$ | $26$ |
| $8$ | $36$ |
| $9$ | $41$ |
| $10$ | $47$ |



---

---
title: "[NERC 2021] Kingdom Partition"
layout: "post"
diff: NOI/NOI+/CTSC
pid: P12824
tag: ['2021', '网络流', 'Special Judge', 'ICPC', 'NERC/NEERC']
---
# [NERC 2021] Kingdom Partition
## 题目描述

The King is gone. After the King's rule, all the roads in the Kingdom are run down and need repair. Three of the King's children, Adrian, Beatrice and Cecilia, are dividing the Kingdom between themselves.

Adrian and Beatrice do not like each other and do not plan to maintain any relations between themselves in the future. Cecilia is on good terms with both of them. Moreover, most of the Kingdom's workers support Cecilia, so she has better resources and more opportunity to repair the infrastructure and develop the~economy. 

Cecilia proposes to partition the Kingdom into three districts: A (for Adrian), B (for Beatrice), and C (for Cecilia), and let Adrian and Beatrice to negotiate and choose any towns they want to be in their districts, and agree on how they want to partition the Kingdom into three districts.

Adrian's castle is located in town $a$, and Beatrice's one is located in town $b$. So Adrian and Beatrice want their castles to be located in districts A and B, respectively. Cecilia doesn't have a castle, so district C can consist of no towns.

There is an issue for Adrian and Beatrice. When they choose the towns, they will have to pay for the roads' repair.

The cost to repair the road of length $l$ is $2l$ gold. However, Adrian and Beatrice don't have to bear all the repair costs. The repair cost for the road of length $l$ that they bear depends on what towns it connects:

- For a road between two towns inside district A, Adrian has to pay $2l$ gold;
- For a road between two towns inside district B, Beatrice has to pay $2l$ gold;
- For a road between towns from district A and district C, Adrian has to pay $l$ gold, Cecilia bears the remaining cost;
- For a road between towns from district B and district C, Beatrice has to pay $l$ gold, Cecilia bears the remaining cost.

The roads that connect towns from district A and district B won't be repaired, since Adrian and Beatrice are not planning to use them, so no one pays for them. Cecilia herself will repair the roads that connect the towns inside district C, so Adrian and Beatrice won't bear the cost of their repair either.

Adrian and Beatrice want to minimize the total cost they spend on roads' repair. Find the cheapest way for them to partition the Kingdom into three districts.
## 输入格式

The first line contains two integers $n$ and $m$ --- the number of towns and the number of roads in the Kingdom ($2 \le n \le 1000$; $0 \le m \le 2000$).

The second line contains two integers that represent town $a$ and town $b$ --- the towns that have to be located in district A and district B, respectively ($1 \le a, b \le n$; $a \ne b$).

The following $m$ lines describe the Kingdom roads. The $i$-th of them consists of three integers $u_i$, $v_i$, and $l_i$ representing a road of length $l_i$ between towns $u_i$ and $v_i$ ($1 \le u_i, v_i \le n$; $u_i \ne v_i$; $1 \le l_i \le 10^9$).

Each pair of towns is connected with at most one road.
## 输出格式

In the first line output a single integer --- the minimum total cost of roads' repair for Adrian and Beatrice.

In the second line output a string consisting of $n$ characters $\tt{A}$, $\tt{B}$, and $\tt{C}$, $i$-th of the characters representing the district that the $i$-th town should belong to.

If several cheapest ways to partition the Kingdom exist, print any of them.
## 样例

### 样例输入 #1
```
6 7
1 3
1 2 10
2 3 5
1 3 7
4 5 3
3 6 100
4 6 3
5 6 8
```
### 样例输出 #1
```
16
ABBCBA
```
## 提示

The following picture illustrates the example. Adrian and Beatrice don't pay for the dashed roads, they pay $2l$ for the bold roads, and $l$ for the solid roads.

So the total cost is $2 \cdot 5 + 3 + 3 = 16$.

The castles of Adrian and Beatrice are located in bold towns.

![](https://cdn.luogu.com.cn/upload/image_hosting/11ffx3k7.png)


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
title: "[SDOI2011] 保密"
layout: "post"
diff: NOI/NOI+/CTSC
pid: P2494
tag: ['2011', '各省省选', '网络流', '山东', '分数规划']
---
# [SDOI2011] 保密
## 题目描述

现在，保密成为一个很重要也很困难的问题。如果没有做好，后果是严重的。比如，有个人没有自己去修电脑，又没有拆硬盘，后来的事大家都知道了。

当然，对保密最需求的当然是军方，其次才是像那个人。为了应付现在天上飞来飞去的卫星，军事基地一般都会建造在地下。

某 K 国的军事基地是这样子的：地面上两排大天井共 $n_1$ 个作为出入口，内部是许多除可以共享出入口外互不连通的空腔，每个空腔有且只有两个出入口，并且这两个出入口不会在同一排。为了方便起见，两排出入口分别编号为 $1, 3, 5, \dots$ 和 $2, 4, 6, \dots$ 并且最大的编号为 $n_1$。

虽然上面扯了那么多关于保密的东西，但是其实解密也是一件很纠结的事情。但其实最简单直接暴力无脑的解密方法就是找个人去看看…

我们有很牛 X 的特种部队，只需要派出一支特种部队到 K 国基地的某个出入口，那么和这个出入口直接相连的所有空腔都可以被探索，但也只有这些空腔可以被这支部队探索。现在有足够多的特种部队可以供你调遣，你必须使用他们调查完所有的 K 国基地内的空腔。

当然，你的基地离 K 国基地不会太近，周边的地图将会给你，表示为 $n$ 个检查点和 $m$ 条连接这些点的道路，其中点 $1$ 到点 $n_1$ 就是 K 国基地的出入口，点 $n$ 是你的部队的出发点。对每条道路，有不同的通行时间 $t$ 和安全系数 $s$ 。因为情报部门只对单向的道路安全系数进行了评估，所以这些道路只允许单向通行，并且不会存在环。

一支特种部队从你的基地出发，通过某条路径，到达某个 K 国基地出入口，此时这支部队的危险性表示为总时间和这条路径经过的所有道路的安全系数和的比值。整个行动的危险性表示为你派出的所有部队的危险性之和。你需要使这个值最小的情况下探索整个 K 国基地。

快点完成这个任务，在 K 国的叫兽宣布你是 K 国人之前。
## 输入格式

第一行 2 个正整数 $n, m$ 表示整个地区地图上的检查点和道路数。

下面 $m$ 行，每行 4 个正整数 $a, b, t, s$ 表示一条从 $a$ 到 $b$ 的道路需时为 $t$，安全系数为 $s$。

接下来 1 行 2 个正整数 $m_1$ 和 $n_1$, $m_1$ 表示 K 国基地空腔的个数，$n_1$ 表示 K 国基地出入口的个数。

再接下来 $m_1$ 行，每行 2 个正整数 $u, v$，表示每个空腔的 $2$ 个出入口。
## 输出格式

一行，最小的危险性，保留一位小数。或者输出 `-1` 表示此任务不可能完成。
## 样例

### 样例输入 #1
```
5 5

5 1 10 1

5 1 10 1

5 2 9 1

5 3 7 1

5 4 8 1

4 4

1 2

1 4

3 2

3 4
```
### 样例输出 #1
```
17.0
```
## 提示

- 对 $30\%$ 的数据，$n \leq 30$；
- 对 $60\%$ 的数据，$n \leq 300$；
- 另外 $40\%$ 的数据 $n_1 \leq 20$。
- 对于 $100\%$ 的数据，$4 \leq n \leq 700$，$m \leq 100000$，$a, b \leq n$，$1 \leq t, s \leq 10$，$m_1 \leq 40000$，$n_1 < \min(n, 161)$，$u, v \leq n_1$，$u$ 是奇数，$v$ 是偶数。


---

---
title: "[ZJOI2015] 醉熏熏的幻想乡"
layout: "post"
diff: NOI/NOI+/CTSC
pid: P3347
tag: ['2015', '二分', '网络流', '浙江']
---
# [ZJOI2015] 醉熏熏的幻想乡
## 题目描述

傲娇少女幽香是一个很萌很萌的妹子，这些天幻想乡的大家都不知道为何还是拼命喝酒。很快酒就供不应求了，为了满足大家的需求，幽香决定在森林里酿酒。

经过调查，幽香发现森林里面有一些地方非常适合酿酒，有一些地方则非常适合存酒。幽香把这些适合酿酒的地方成为酿酒点，不妨认为有 $n$ 个酿酒点，从 $1$ 到 $n$ 标号。同时也有 $m$ 个适合存酒的地方，幽香将它们成为存酒点，从 $1$ 到 $m$ 标号。在一些酿酒点和存酒点之间存在通道，如果酿酒点 $i$ 到存酒点 $j$ 之间存在通道，那么 $i$ 生产的酒就可以被运输到 $j$。

但是在一个地方酿酒是需要消耗幽香的魔力的，由于存在管理上的因素，在酿酒点 $i$，制造 $x$ 升的酒，需要花费 $a_i\cdot x^2+b_i\cdot x$ 的魔力，注意 $x$ 不一定是一个非负整数，也可以是一个非负实数，同时在这个点最多只能制造 $c_i$ 升的酒。每个存酒点 $j$ 有一个容量 $d_j$，表示这个存酒点最多能存多少升的酒。

幽香打算存尽量多的酒，那么她需要再一些酿酒点生产一些酒并且通过通道将酒运送到存酒点。当然幽香想要节省自己的魔力，所以想让你帮忙算出在满足要求的情况下，最少花费的魔力是多少？
## 输入格式

第一行两个正整数 $n$，$m$，表示酿酒点和存酒点的数量。接下来 $n$ 行，第 $i$ 行三个数 $a_i$，$b_i$，$c_i$，表示在酿酒点 $i$ 制造酒的花费系数和上限。接下来一行 $m$ 个整数，一次为每个存酒点的 $d_i$ 值。接下来 $n$ 行，每行 $m$ 个数，其中第 $i$ 行第 $j$ 个表示酿酒点 $i$ 到存酒点 $j$ 有没有通道（$1$ 表示有，$0$ 表示没有）。
## 输出格式

输出第一行表示幽香最多能存多少升酒（注意这肯定是个整数，直接输出即可）。

输出第二行表示最小花费魔力，注意这肯定是一个有理数，化简后按照 $a/b$ 的形式输出（$0$输出 $0/1$）
## 样例

### 样例输入 #1
```
10 10
0 2 3
2 3 2
3 1 3
1 2 1
1 0 1
1 1 0
3 3 0
1 2 2
3 1 1
3 1 0
3 1 2 2 3 1 1 2 2 0
0 0 0 0 0 0 0 1 0 0
0 0 0 0 0 0 0 0 0 0
0 0 0 0 1 0 0 0 0 0
0 0 0 1 0 0 0 0 0 0
1 0 0 0 1 0 0 0 0 0
1 0 1 0 0 0 0 1 1 0
0 0 0 0 0 0 0 0 0 0
0 0 0 0 0 0 0 0 0 0
0 0 1 0 0 0 1 0 0 0
0 0 0 0 0 1 0 0 1 0
```
### 样例输出 #1
```
8
42/1

```
## 提示

对于 $30\%$ 的数据：所有 $a_i=0$。

对于另 $30\%$ 的数据：最终答案的分母 $\leq 1000$。

对于 $100\%$ 的数据：$1\leq n\leq100$，$1\leq m\leq100$。

对于所有数据，$0\leq a_i,b_i,c_i,d_i\leq3$ 且都是整数。同时对于每个 $i$，$a_i+b_i>0$ 的通道的数量不超过 $1000$ 条。

非常神奇的是，对于所有数据存在一个正整数 $X\leq10^7$，使得存在一个最优解，使得所有路径上运送的酒的体积都是 $1/X$ 的倍数。


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
title: "[CTSC2017] 最长上升子序列"
layout: "post"
diff: NOI/NOI+/CTSC
pid: P3774
tag: ['2017', '网络流', 'O2优化', '杨表', 'CTSC/CTS']
---
# [CTSC2017] 最长上升子序列
## 题目描述

猪小侠最近学习了最长上升子序列的相关知识。对于一个整数序列 $A =(a_1, a_2,\ldots , a_k)$，定义 $A$ 的子序列为：从 $A$ 中删除若干个元素后（允许不删，也允许将所有 $k$ 个元素都删除），剩下的元素按照原来的顺序所组成的序列。如果这个子序列的元素从左到右严格递增，则称它为 $A$ 的一个上升子序列。其中包含元素数量最多的上升子序列称为 $A$ 的最长上升子序列。例如，$(2, 4, 5, 6)$ 和 $(1, 4, 5, 6)$ 都是 $(2, 1, 1, 4, 7, 5, 6)$ 的最长上升子序列，长度都为 $4$。

现在猪小侠遇到了这样一个问题：给定一个序列 $B_m = (b_1, b_2, \ldots, b_m)$，设 $C$ 是 $B_m$ 的子序列，且 $C$ 的最长上升子序列的长度不超过 $k$，则 $C$ 的长度最大能是多少？

猪小侠觉得这个问题太简单了，缺乏挑战，他决定提出一个更难的问题。于是他给了你这样一个序列 $B = (b_1, b_2,\ldots , b_n)$，以及若干次询问。每次询问会给定两个整数 $m$ 和 $k$，你需要对于 $B$ 序列的前 $m$ 个元素构成的序列 $B_m = (b_1, b_2, \ldots, b_m)$ 和 $k$ 回答上述问题。

## 输入格式

第一行两个整数 $n, q$，其中 $n$ 是序列 $B$ 的长度，$q$ 是询问次数。

第二行是空格隔开的 $n$ 个正整数 $b_1, b_2, \ldots, b_n$。

接下来 $q$ 行，其中第 $i$ 行包含两个整数 $m_i, k_i$，表示对 $m = m_i, k = k_i$ 进行询问。

## 输出格式

输出共 $q$ 行，按顺序每行一个整数作为回答。

## 样例

### 样例输入 #1
```
11 6
9 6 3 1 5 12 8 4 2 2 2
5 1
7 2
9 1
9 2
11 1
11 11
```
### 样例输出 #1
```
4 
6 
5 
8 
7
11
```
## 提示

【样例解释】

询问 $1$：对于序列 $(9,6,3,1,5)$，可以选取子序列 $(9,6,3,1)$，它的最长上升子序列长度为 $1$。

询问 $2$：对于序列 $(9,6,3,1,5,12,8)$，可以选取子序列 $(9,6,3,1,12,8)$，它的最长上升子序列长度为 $2$。

询问 $3$：对于序列 $(9,6,3,1,5,12,8,4,2)$，可以选取子序列 $(9,6,5,4,2)$，它的最长上升子序列长度为 $1$。

询问 $4$：对于序列 $(9,6,3,1,5,12,8,4,2)$，可以选取子序列 $(9,6,3,1,12,8,4,2)$，它的最长上升子序列长度为 $2$。

询问 $5$：对于序列 $(9,6,3,1,5,12,8,4,2,2,2)$，可以选取子序列 $(9,6,5,4,2,2,2)$，它的最长上升子序列长度为 $1$。

询问 $6$：对于序列 $(9,6,3,1,5,12,8,4,2,2,2)$，可以选取子序列 $(9,6,3,1,5,12,8,4,2,2,2)$，它的最长上升子序列长度为 $3$。


 ![](https://cdn.luogu.com.cn/upload/pic/5487.png) 

对于 $100\%$ 的数据， $1\leq n\leq 5\times 10^4$，$1\leq b_i\leq 5\times 10^4$，$1\leq q \leq 2\times 10^5$，$1\leq k_i \leq m_i \leq n$。



---

---
title: "无限之环"
layout: "post"
diff: NOI/NOI+/CTSC
pid: P4003
tag: ['2017', '网络流', '费用流', 'CTT（清华集训/北大集训）']
---
# 无限之环
## 题目描述

曾经有一款流行的游戏，叫做 Infinity Loop，先来简单的介绍一下这个游戏：

游戏在一个 $n \times m$ 的网格状棋盘上进行，其中有些小方格中会有水管，水管可能在格某些方向的边界的中点有接口，所有水管的粗细都相同，所以如果两个相邻方格的共边界的中点都有接头，那么可以看作这两个接头互相连接。水管有以下 $15$ 种形状：

 ![](https://cdn.luogu.com.cn/upload/pic/12049.png) 

游戏开始时，棋盘中水管可能存在漏水的地方。

形式化地：如果存在某个接头，没有和其它接头相连接，那么它就是一个漏水的地方。

玩家可以进行一种操作：选定一个含有**非直线型**水管的方格，将其中的水管绕方格中心顺时针或逆时针旋转 $90$ 度。

直线型水管是指左图里中间一行的两种水管。

现给出一个初始局面，请问最少进行多少次操作可以使棋盘上不存在漏水的地方。

## 输入格式

第一行两个正整数 $n$, $m$, 代表网格的大小。

接下来 $n$ 行每行 $m$ 个数，每个数是 $[0,15]$ 中的一个，你可以将其看作一个 $4$ 位的二进制数，从低到高每一位分别代表初始局面中这个格子上、右、下、左方向上是否有水管接头。

特别地，如果这个数是 $0$ ，则意味着这个位置没有水管。

比如 $3(0011_{(2)})$ 代表上和右有接头，也就是一个 $L$ 型，而 $12(1100_{(2)})$ 代表下和左有接头，也就是将 $L$ 型旋转 $180$ 度。

## 输出格式

输出共一行，表示最少操作次数。如果无法达成目标，输出 $-1$。

## 样例

### 样例输入 #1
```
2 3
3 14 12
3 11 12
```
### 样例输出 #1
```
2
```
### 样例输入 #2
```
3 2
1 8
5 10
2 4
```
### 样例输出 #2
```
-1
```
### 样例输入 #3
```
3 3
9 11 3
13 15 7
12 14 6
```
### 样例输出 #3
```
16
```
## 提示

【样例 1 解释】

样例 1 棋盘如下:

旋转方法很显然，先将左上角虚线方格内的水管顺时针转 $90$ 度

 ![](https://cdn.luogu.com.cn/upload/pic/12050.png) 

然后右下角虚线方格内的水管逆时针旋转 $90$ 度，这样就使得水管封闭了

【样例 2 解释】

样例 2 为题目描述中的第一张图片，无法达成目标。

【样例 3 解释】

样例 3 为题目描述中的第二张图片，将除了中心方格以外的每个方格内的水管都转 $180$ 度即可。


 ![](https://cdn.luogu.com.cn/upload/pic/12051.png) 




---

---
title: "[CTSC2008] 祭祀"
layout: "post"
diff: NOI/NOI+/CTSC
pid: P4298
tag: ['2008', '网络流', 'Special Judge', '二分图', '构造', 'CTSC/CTS']
---
# [CTSC2008] 祭祀
## 题目描述

在遥远的东方，有一个神秘的民族，自称 Y 族。他们世代居住在水面上，奉龙王为神。每逢重大庆典，Y 族都会在水面上举办盛大的祭祀活动。我们可以把 Y 族居住地水系看成一个由岔口和河道组成的网络。每条河道连接着两个岔口，并且水在河道内按照一个固定的方向流动。显然，水系中不会有环流（下图描述一个环流的例子）。

 ![](https://cdn.luogu.com.cn/upload/pic/15479.png)

由于人数众多的原因，Y 族的祭祀活动会在多个岔口上同时举行。出于对龙王的尊重，这些祭祀地点的选择必须非常慎重。准确地说，Y 族人认为，如果水流可以从一个祭祀点流到另外一个祭祀点，那么祭祀就会失去它神圣的意义。族长希望在保持祭祀神圣性的基础上，选择尽可能多的祭祀的地点。
## 输入格式

第一行包含两个用空格隔开的整数 $N$、$M$，分别表示岔口和河道的数目，岔口从 $1$ 到 $N$ 编号。

接下来 $M$ 行，每行包含两个用空格隔开的整数 $u$、$v$，描述一条连接岔口 $u$ 和岔口 $v$ 的河道，水流方向为自 $u$ 向 $v$。
## 输出格式

第一行包含一个整数 $K$，表示最多能选取的祭祀点的个数。

接下来一行输出一种可行的选取方案。对于每个岔口依次输出一个整数，如果在该岔口设置了祭祀点，那么输出一个 `1`，否则输出一个 `0`。应确保你输出的 `1` 的个数最多，且中间没有空格。

接下来一行输出，在选择最多祭祀点的前提下，每个岔口是否能够设置祭祀点。对于每个岔口依次输出一个整数，如果在该岔口能够设置祭祀点，那么输出一个 `1`，否则输出一个 `0`。

注意：多余的空格和换行可能会导致你的答案被判断为错误答案。
## 样例

### 样例输入 #1
```
4 4
1 2
3 4
3 2
4 2
```
### 样例输出 #1
```
2
1010
1011
```
## 提示

$N \le 100, M \le 1000$

在样例给出的水系中，不存在一种方法能够选择三个或者三个以上的祭祀点。包含两个祭祀点的测试点的方案有两种：

选择岔口 $1$ 与岔口 $3$（如样例输出第二行），选择岔口 $1$ 与岔口 $4$。

水流可以从任意岔口流至岔口 $2$。如果在岔口 $2$ 建立祭祀点，那么任意其他岔口都不能建立祭祀点但是在最优的一种祭祀点的选取方案中我们可以建立两个祭祀点，所以岔口 $2$ 不能建立祭祀点。对于其他岔口至少存在一个最优方案选择该岔口为祭祀点，所以输出为 `1011`。

感谢@ACdreamer 提供SPJ


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
title: "[BJWC2018] 餐巾计划问题"
layout: "post"
diff: NOI/NOI+/CTSC
pid: P4480
tag: ['2018', '网络流', '北京', '最短路', '队列']
---
# [BJWC2018] 餐巾计划问题
## 题目背景

**本题和网络流24题中的餐巾计划不为重题**
## 题目描述

一个餐厅在相继的 $n$ 天里，每天需用的餐巾数不尽相同。假设第 $i$ 天 $(i=1, 2, ..., n)$ 需要 $r_i$ 块餐巾。餐厅可以在任意时刻购买新的餐巾，每块餐巾的费用为 $p$ 。使用过的旧餐巾，则需要经过清洗才能重新使用。把一块旧餐巾送到清洗店A，需要等待 $m_1$ 天后才能拿到新餐巾，其费用为 $c_1$ ；把一块旧餐巾送到清洗店B，需要等待 $m_2$ 天后才能拿到新餐巾，其费用为 $c_2$ 。例如，将一块第 $k$ 天使用过的餐巾送到清洗店A清洗，则可以在第 $k+m_1$ 天使用。

请为餐厅合理地安排好 $n$ 天中餐巾使用计划，使总的花费最小。
## 输入格式

第一行，包含六个个正整数  $n, m_1, m_2, c_1, c_2, p$ 。

接下来输入 $n$ 行，每行包含一个正整数 $r_i$ 。
## 输出格式

输出一行，包含一个正整数，表示最小的总花费。
## 样例

### 样例输入 #1
```
4 1 2 2 1 3
8
2
1
6
```
### 样例输出 #1
```
35
```
## 提示

**【样例说明】**

第 1 天：买8块餐巾，花费24。送2块餐巾去清洗店A，6块餐巾去清洗店B。

第 2 天：取回2块清洗店A的餐巾，花费4。送1块餐巾去清洗店B。

第 3 天：取回6块清洗店B的餐巾，花费6。

第 4 天：取回1块清洗店B的餐巾，花费1。这样就用了最少的钱。


**【数据规模和约定】**

对于30%的数据，$1 \leq n \leq 5$ ，$1 \leq c_1, c_2, p \leq 5$ ， $1 \leq r_i \leq 5$ 。

对于50%的数据，$1 \leq n \leq 100$ ，$1 \leq r_i \leq 50$ 。

对于70%的数据，$1 \leq n \leq 5000$ 。

对于100%的数据，$1 \leq n \leq 200000$ ， $1 \leq m_1, m_2 \leq n$ ， $1 \leq c_1, c_2, p \leq 100$ ， $1 \leq r_i \leq 100$ 。


---

---
title: "[BJWC2018] Kakuro"
layout: "post"
diff: NOI/NOI+/CTSC
pid: P4486
tag: ['2018', '网络流', '北京', '上下界网络流']
---
# [BJWC2018] Kakuro
## 题目背景

首先介绍一下Kakuro(カックロ) 这个游戏。

游戏规则为：

• 方形空格中填入1 ~ 9 的整数。

• 被斜线分开的方格中，右上角的数字等于其右侧邻接之连续方格中数字之和，左下角的数字等于其下方邻接之连续方格中数字之和。

• 无论是横向还是纵向，连续方格中的数字不能重复。

![](https://cdn.luogu.com.cn/upload/pic/17946.png)
![](https://cdn.luogu.com.cn/upload/pic/17947.png)

左边为一个Kakuro 游戏，右边为这个游戏的唯一解。

我们称一开始给出的数字为线索，称需要填入数字的地方为空格。如果一个格子包含线索那么就不需要填入数字。我们约定所有的谜题都非空，即至少有一个空格需要被填入。

**注意：在以下题目中的游戏规则可能会有所不同，请认真阅读在每个
题目下的规则。**
## 题目描述

游戏规则：

• 空格中填入正整数。

• 被斜线分开的方格中，右上角的数字等于其右侧邻接之连续方格中数字之和，左下角的数字等于其下方邻接之连续方格中数字之和。

Apia 给了Rimbaud 一个Kakuro 谜题。心不灵手不巧的Rimbaud 根本不会做Kakuro，所以只在空格里面填上了一些随机的数字，称这个为一个局面，即包含了谜题一开始给出的线索和后面填入的数字。

现在Rimbaud 希望能修改这个局面使得她的答案是一个合法解。这个局面中有些数字(**包括一开始的给出线索和后面填入的数字**) 是可以修改的。每个数字都有个特定的代价，将这个数字加1 或者减1 都得付出这个数字对应的代价。注意对于一组合法解，必须满足游戏规则，也就是**空格中填的数字必须是正整数并且满足和的条件，但是不要求不重复**。

Rimbaud 希望用最少的代价让这个局面变得合法，如果不可能那么输出-1。
## 输入格式

第一行，两个正整数表示n,m 表示这个游戏的行和列。

接下来n 行，每行包含m 个0 到4 的数字，第i 行第j 列表示第i 行第j 列格子的种类。

• 0 表示这个格子既不是空格也不是线索。

• 1 表示这个格子左下角包含线索，右上角没有线索。

• 2 表示这个格子右上角包含线索，左下角没有线索。

• 3 表示这个格子左下角右上角都包含线索。

• 4 表示这个格子为空格。

输入保证这个从格式上来说一定是个合法的Kakuro 谜题，即每一段连续的空格的左边或者上面的格子包含线索。

接下来n 行，每行包含若干个正整数，按从左往右的顺序给出初始局面中的每个数字。特别地如果这个格子的种类为3，那么先给出左下角的线索，再给出右上角的线索。

接下来n 行，每行包含若干个整数，按从左往右的顺序给出初始局面中的每个数字对应的代价。如果代价为-1 表示这个格子不能修改，否则代价为非负整数。注意3 号格子的两个线索有着两个不同的代价。

**样例1 给出了上面的谜题的输入，请在做题前阅读样例1 确保你理解了输入格式。**
## 输出格式

一个整数表示最小的代价，如果不可能输出-1。
## 样例

### 样例输入 #1
```
8 8
0 1 1 0 0 1 1 1
2 4 4 0 3 4 4 4
2 4 4 3 4 4 4 4
2 4 4 4 4 4 1 0
0 2 4 4 3 4 4 1
0 1 3 4 4 4 4 4
2 4 4 4 4 2 4 4
2 4 4 4 0 2 4 4
23 30 27 12 16
16 9 7 17 24 8 7 9
17 8 9 15 29 8 9 5 7
35 6 8 5 9 7 12
7 6 1 7 8 2 6 7
11 10 16 4 6 1 3 2
21 8 9 3 1 5 1 4
6 3 1 2 3 2 1
-1 -1 -1 -1 -1
-1 -1 -1 -1 -1 -1 -1 -1
-1 -1 -1 -1 -1 -1 -1 -1 -1
-1 -1 -1 -1 -1 -1 -1
-1 -1 -1 -1 -1 -1 -1 -1
-1 -1 -1 -1 -1 -1 -1 -1
-1 -1 -1 -1 -1 -1 -1 -1
-1 -1 -1 -1 -1 -1 -1
```
### 样例输出 #1
```
0
```
### 样例输入 #2
```
5 5
0 1 1 1 1
2 4 4 4 4
2 4 4 3 4
2 4 4 4 4
2 4 4 4 4
16 8 6 8
4 4 9 5 4
12 8 4 19 10 4
14 2 3 3 6
1 7 9 4 5
17 5 10 13
11 15 16 4 14
20 20 15 5 16 3
4 3 19 2 4
19 19 13 15 20
```
### 样例输出 #2
```
822
```
## 提示

对于5% 的数据，保证所有的代价都为-1。

对于20% 的数据，保证所有空格中的数字代价都为-1。

对于另外30% 的数据，保证所有代表线索的数字的代价都为-1。

对于另外20% 的数据，保证只有第一行第一列包含线索，剩下的地方全都是空格。

对于100% 的数据，保证3 ≤ n,m ≤ 30，保证初始局面中的每个数字不超过$10^6$，保证每个数字的代价不超过$10^6$。


---

---
title: "[北京省选集训2019] 图的难题"
layout: "post"
diff: NOI/NOI+/CTSC
pid: P5295
tag: ['图论', '2019', '网络流', '北京', 'O2优化']
---
# [北京省选集训2019] 图的难题
## 题目背景

标题是假的。
## 题目描述

小D 在图论习题书上遇到了一个问题：  
书上画出了一张无向图，要求把边染成黑白两色，要求所有白色边构成的子图没有环，且所有黑色边构成的子图没有环。  
小D 无论怎样尝试都觉得书上的问题没有解，她想请你帮她确认一下。  
由于这道题有很多小问，小D 每次会给你图的点数 $n$、边数 $m$ 与所有边集，你只需要告诉小D 有没有解即可。
## 输入格式

第一行一个正整数 $T$，表示数据组数。  
对于每组数据，第一行两个正整数 $n,m$，意义如题目描述。  
接下来 $m$ 行，每行两个正整数 $u,v$ ,表示一条 $u$ 到 $v$ 的无向边
## 输出格式

输出$T$行，对于每组数据，若有解输出`Yes`，否则输出`No`。
## 样例

### 样例输入 #1
```
3
3 3
1 2
1 3
2 3
2 3
1 2
1 2
1 2
4 6
1 2
1 3
2 4
1 3
2 3
3 4
```
### 样例输出 #1
```
Yes
No
Yes
```
## 提示

### 数据范围：  
对于 $20\%$ 的数据：$1\le m \le 10$  
对于 $40\%$ 的数据：$1\le n \le 15$  
对于 $70\%$ 的数据： $1\le n \le 50$  
对于 $100\%$ 的数据：$1\le n \le 501$，$1\le m \le 2n$，$1\le T \le 10$


---

---
title: "封锁"
layout: "post"
diff: NOI/NOI+/CTSC
pid: P6158
tag: ['2020', '网络流', 'O2优化', '最短路', '最小割', '凸包', '叉积']
---
# 封锁
## 题目背景

震惊！zbw 竟从 B 城监狱逃出！

作为 B 城的警察局长，你必须在 zbw 逃出你的管辖范围之前抓住他。
## 题目描述

B 城可视为一个 $n \times n$ 的方阵，其中监狱在 $(1,1)$，B 城唯一出城的出口在 $(n,n)$。每两个相邻的点（横坐标之差的绝对值 $+$ 纵坐标之间的绝对值 $=1$）之间都有一条**无向的**道路（没有斜着的道路）。你需要在一些道路上部下防守，使得无论 zbw 怎么走，都至少会经过其中的一条道路。

在一条 $(i,j)$ 到 $(i,j+1)$ 的道路上部下防守的花费是 $r_{i,j}$，在一条 $(i,j)$ 到 $(i+1,j)$ 的道路上部下防守的花费是 $d_{i,j}$，同时，在道路上部下防守会对人民的生活造成影响，在一条 $(i,j)$ 到 $(i,j+1)$ 的道路上部下防守对人民的生活造成的影响是 $x_{i,j}$，在一条 $(i,j)$ 到 $(i+1,j)$ 的道路上部下防守对人民的生活造成的影响是 $y_{i,j}$。

定义总花费为 $w$ ，总影响为 $e$ ，作为一名优秀的警察局长，你需要最小化 $w \times e$。 
## 输入格式

第一行一个整数 $n$。

之后的 $n \times (n-1)$ 行，第 $i$ 行两个整数 $r_{i/n+1,(i-1)\bmod n+1}$， $x_{i/n+1,(i-1)\bmod n+1}$。

之后的 $n \times (n-1)$ 行，第 $i$ 行两个整数 $d_{i/n+1,(i-1)\bmod n+1}$ ，$y_{i/n+1,(i-1)\bmod n+1}$。

也就是说，先从上往下给从左往右给出竖边的信息，再从上往下给从左往右给出横边的信息。

如果不理解请见样例解释。

## 输出格式

一行一个整数，表示 $w \times e$ 的最小值。
## 样例

### 样例输入 #1
```
3
8 3
5 2
1 1
4 2
1 2
7 5
7 2
6 1
5 4
2 3
1 4 
4 3
```
### 样例输出 #1
```
49
```
## 提示

![](https://cdn.luogu.com.cn/upload/image_hosting/bjd62iba.png)

如图，左上角为 $(1,1)$，右下角为 $(n,n)$，
其中蓝色数字表示 $r$,
红色数字表示 $x$,
黄色数字表示 $d$,
绿色数字表示 $y$。

最优方案为防守三条边，分别为：

$(2,2)-(2,3),(3,1)-(3,2),(3,2)-(3,3)$

三条边的边权分别是 $2,3$---$1,1$ ---$4,3$

答案为 $(1+2+4)\times (1+3+3)=49$


可以发现没有更优的做法。

**本题采用捆绑测试。**

|  Subtasks| $n$ |特殊性质  |分数
| :----------: | :----------: | :----------: |:----------: |
|  Subtask1| $n=2$ |无  |$5$
|  Subtask2| $n\leq400$ |数据随机  |$15$
|  Subtask3| $n\leq10$ |  无|$15$
|  Subtask4| $n\leq50$ | 无 |$30$
|  Subtask5| $n\leq400$ | 无 |$35$

对于所有数据 $1 \leq n \leq 400$，$0 \leq r_{i,j}, d_{i,j},x_{i,j} ,y_{i,j}  \leq 10^3$。

数据于2020/3/4加强，卡掉部分复杂度错误的做法。


---

---
title: "[ICPC 2017 WF] Son of Pipe Stream"
layout: "post"
diff: NOI/NOI+/CTSC
pid: P6938
tag: ['2017', '网络流', 'Special Judge', '导数', 'ICPC']
---
# [ICPC 2017 WF] Son of Pipe Stream
## 题目描述



Two years ago, you helped install the nation's very first Flubber pipe network in your hometown, to great success. Polls show that everyone loves having their own Flubber dispenser in their kitchen, and now a few enterprising citizens have discovered a use for it. Apparently Flubber, when mixed with water, can help extinguish fires! This is a very timely discovery, as out-of-control fires have lately been surprisingly common.

Your hometown's city council would like to make use of this property of Flubber by creating the $Flubber/water$ mixture at a centrally located station. This station, which is called the Flubber Department (FD) will also have specialized employees trained to travel to the locations of fires and make use of their processed Flubber to control the blazes.

The pipes are already in place all around the city. You are given a layout of the pipes, and must determine how to route Flubber from the Flubber factory and water from a local source through the pipes to the FD.

Note that both Flubber and water will be flowing through the same network of pipes, perhaps even the same pipe. All pipes are bidirectional, but Flubber and water cannot move in opposite directions through the same pipe. Furthermore, if both liquids are sent in the same direction through the same pipe, they will inevitably mix. Therefore the nodes in the network have been equipped with special membranes and filters that enable you to separate and reorganize all incoming mixtures as you see fit. The network is a closed system, so the total rate of each fluid going into a node must equal the total rate of that fluid going out, except at the source of that fluid and the destination (the FD).

Each pipe has a certain capacity. Flubber, being somewhat sluggish, has a viscosity value $v$ , so a pipe that can transport $v liters/second$ of water can transport only $1 liter/second$ of Flubber. The pipe's capacity scales linearly for mixtures of the two. To be precise, if $c$ denotes the water capacity of the pipe and $f$ and $w$ are the rates of Flubber and water moving through the pipe (all measured in $liters/second),$ then the capacity constraint is given by the inequality $v · f + w \le c$ .

Your main concern is balancing the mixture that reaches the FD. You would like as much total liquid as possible, but you also need a sufficient amount of water $-$ because undiluted Flubber is highly flammable $-$ and a sufficient amount of Flubber $-$ because it would not be much of a `Flubber Department` without Flubber! You have come up with a formula to measure the `value` of the final mixture: $F^{a} · W^{1−a},$ where $F$ is the rate of incoming Flubber in $liters/second, W$ is the rate of incoming water in $liters/second,$ and a is a given constant between $0$ and $1$ .

Determine the maximum value of $F^{a} · W^{1−a}$ that can be achieved and how to route the Flubber and water to achieve it.


## 输入格式



The input starts with a line containing the number of locations $n (3 \le n \le 200)$ , the number of pipes $p (n − 1 \le p \le $ n(n $− 1)/2)$ , and the real values $v (1 \le v \le 10)$ and a ($0$ . $01 \le $ a $ \le 0$ . $99$) . Locations are numbered from $1$ to $n$ ; $1$ is the Flubber factory, $2$ is the water source, and $3$ is the FD. The real values have at most $10$ digits after the decimal point.

The following $p$ lines each describe one pipe. Each line contains two integers $j$ and $k (1 \le j < k \le n)$ , giving the locations connected by the pipe, and an integer $c (1 \le c \le 10)$ , giving the water capacity of the pipe in $liters/second.$

No two pipes connect the same pair of locations. Furthermore, it is guaranteed that the network is connected.


## 输出格式



First, for each pipe (in the order given in the input), display two values: the rate of Flubber moving through it, and the rate of water moving through it (negative if the liquid is moving from $k$ to $j)$ , such that $F^{a} ·W^{1−a}$ is maximized. Then display that maximum value accurate to within an absolute error of $10^{−4}.$

If there are multiple solutions, any one will be accepted. All constraints (not sending Flubber and water in opposite directions along the same pipe, flow conservation, pipe capacities, and consistency between the constructed solution and its claimed value) must be satisfied within an absolute error of $10^{−4}.$


## 样例

### 样例输入 #1
```
6 6 3.0 0.66
2 4 8
4 6 1
3 6 1
4 5 5
1 5 7
3 5 3

```
### 样例输出 #1
```
0.000000000 1.360000000
0.000000000 1.000000000
0.000000000 -1.000000000
0.000000000 0.360000000
0.880000000 0.000000000
-0.880000000 -0.360000000
1.02037965897

```
### 样例输入 #2
```
5 5 1.0 0.5
1 2 10
2 3 10
3 4 10
4 5 10
3 5 10

```
### 样例输出 #2
```
5 0
5 5
4.2 3.14159
4.2 3.14159
-4.2 -3.14159
5

```
## 提示

Time limit: 5 s, Memory limit: 512 MB. 


## 题目翻译

### 题目描述
两年以前，你帮助你的家乡安装了国内的第一个 Flubber 管道网络，获得了巨大成功。投票表明每个人都喜欢在自己家的厨房里装上 Flubber 分配器，而现在一些有进取心的市民发现了一种新的用途——Flubber 和水混合后似乎可以帮助灭火！这是一个很及时的发现，因为最近无法控制的大火出奇地常见。

你家乡的市议会想在一个位于中央的地方制造 Flubber 和水的混合物以利用 Flubber 的这个属性。这个被称为 Flubber 部门的地方拥有专门训练的员工去往着火的地点并且利用经过处理的 Flubber 来控制火势。

管道已经在城市中铺设好。你会得到管道布局，而你需要决定如何将 Flubber 从 Flubber 工厂、将水从一个本地水源通过管道运送至 Flubber 部门。

注意 Flubber 和水会在同一管道网络中，甚至可能在同一条管道中流动。所有管道是双向的，但是 Flubber 和水不能在同一条管道中异向流动。此外，如果两种液体同向流过一条管道，它们会不可避免地混合，因此网络中的所有节点配备了特殊的膜和筛，如你所见，可以分离和重新组织所有流入的混合物。管道网络是个封闭系统，因此在每个节点处每种液体的总流入速率必须等于总流出速率，除了每种液体各自的源头和目的地（Flubber 部门）。

每条管道有某个容量，有些粘稠的 Flubber 有一个粘度值 v，所以能运输 v 升每秒的水的管道只能运输 1 升每秒的 Flubber。管道对于混合物的容量是线性变化的。更精确地，假设 c 表示管道对于水的容量，f 和 w 分别表示 Flubber 和水流过管道的速率（单位均为升每秒），则容量的限制用不等式 v⋅f+w≤c 表示。

你主要关心的是平衡流到 Flubber 部门的混合物。你想要尽可能多的混合液体，但是也需要足够的水——因为未经稀释的 Flubber 是高度易燃的——也需要足够的 Flubber——因为 Flubber 部门可不能没了 Flubber！你想出了一个公式来衡量最终混合物的价值：$F^a⋅W^{1−a}$，其中 F 是以升每秒为单位的 Flubber 的流入速率，W 是以升每秒为单位的水的流入速率，a 是一个给定的介于 0 和 1 之间的常数。

求出 $F^a⋅W^{1−a}$ 能达到的最大值以及如何安排 Flubber 和水的路径来达到它。

### 输入格式
输入的第一行包含地点的数量 n (3≤n≤300)，管道的数量 $p (n−1≤p≤\frac12n(n−1))$，和实数 v (1≤v≤10) 和 a (0.01≤a≤0.99)。地点从 1 到 n 标号；1 是 Flubber 工厂，2 是水源，3 是 Flutter 部门。实数的小数点后最多有十位。

接下来的 p 行每行描述了一条管道。每行有两个整数 j 和 k (1≤j<k≤n)，表示管道连接的地点，和一个整数 c (1≤c≤10)，表示这条管道的水容量，以升每秒为单位。

没有两条管道连接相同的两个地点，此外，还保证网络是连通的。

### 输出格式
首先，对于每条管道（按照输入的顺序），输出两个值：其中 Flubber 流过的速率和其中水流过的速率 （如果从 k 流到 j 则为负数），使得 $F^a⋅W^{1−a}$ 最大化。然后输出其最大值，在 $10^{−4}$ 的绝对误差以内。

如果有多解，输出任意一种均可。所有限制（Flubber 和水没有在同一条管道内异向流动、流量守恒、管道容量以及构造的解和其声称的值的一致性）需要在 $10^{−4}$ 的绝对误差内满足。


---

---
title: "[省选联考 2022] 学术社区"
layout: "post"
diff: NOI/NOI+/CTSC
pid: P8291
tag: ['各省省选', '2022', '网络流', 'Special Judge', 'O2优化']
---
# [省选联考 2022] 学术社区
## 题目背景

**小 I 的温馨提示：在题目描述中有形式化的题面，你可以选择跳过题目背景。同时请仔细将本题的除题目背景以外的所有内容进行完整阅读后再进行做题。**

小 I 是一个喜欢 OI 的选手，不过，与其说小 I 喜欢 OI，不如说小 I 喜欢的是他最经常使用的 OJ——FCCOJ——上的趣味功能：学术社区。虽说名字叫学术社区，但小 I 和网友们能够谈论的东西远不止学术。每天学术社区里总会出现不少吸引小 I 注意的帖子。今天小 I 在学术社区冲浪时发现了一个这样的帖子：

> `builtin_clz`：萌新求助，学术社区这题，本机 AC 提交 RE
> 
> `builtin_ctz`：`builtin_clz` 楼下
> 
> `jinkela`：`builtin_ctz` 楼下
> 
> `builtin_ctz`：`builtin_clz` 楼上
> 
> `builtin_clz`：能不能别魔怔了，大家正经回答问题
> 
> `OrzTourist`：`builtin_clz` 楼下
> 
> `OrzTourist`：`OrzTourist` 楼下
> 
> `builtin_clz`：怎么没有人回答问题，我生气了！
> 
> `builtin_clz`：`builtin_clz` 楼上
> 
> `builtin_clz`：`builtin_clz` 楼下
> 
> `builtin_clz`：`builtin_clz` 楼上
> 
> `builtin_clz`：`builtin_clz` 楼下
> 
> ……

虽然这个名叫 `builtin_clz` 的网友因为没有人回答他的学术问题被激怒了，但这个有趣的发言方式让小 I 乐呵了许久，这说明人类的悲欢并不相通。不过当小 I 刷新界面想要往下浏览大家的回复时，却发现学术社区的管理员因为这个帖子过于灌水把它删除了。

为了恢复这个有趣的帖子，小 I 对着网页缓存倒腾了许久，还原出了这个帖子的每条消息。然而因为神秘原因，消息的顺序被打乱了，且缓存中没有每条消息发送的时间，因而小 I 没有办法还原原始帖子中消息的顺序。

秉承 “遇到困难睡大觉” 精神的小 I 决定随便给帖子里的消息排个顺序，不过深受 “`XXX` 楼上” “`XXX` 楼下” 这种发言形式吸引的小 I 还是希望重排之后有尽可能多的这种形式的消息的表达是符合帖子的实际情况的。然而小 I 是一个只会水社区不会做题的 OI 选手，所以小 I 求助于你。

当然了，小 I 知道直接将帖子中的原始信息丢给你对你来说是不方便的，所以他对信息进行了一些规范化处理，详见题目描述中的形式化题意。**同时由于学术社区的特殊规定，帖子中的消息满足一定特殊限制，详见题目描述最后。**
## 题目描述

**以下涉及的所有字符串判等操作都对大小写敏感，例如 `1oushang`、`Loushang`、`LOUSHANG` 是互不相同的字符串。**

小 I 正在整理学术社区中的一个帖子。帖子中一共有 $N$ 个网友发过消息，他们的网名分别为 $n_1, n_2, \ldots, n_N$。帖子中总共有 $M$ 条消息，对于第 $i$ 条消息，我们用三个字符串 $s_{i,1}, s_{i,2}, s_{i,3}$ 构成的三元组描述它，其中 $s_{i,1}$ 表示这条消息发出者的网名，而 $s_{i,2}$ 和 $s_{i,3}$ 描述这条消息的内容。

对于第 $i$ 条消息，我们通过如下方式定义其属于**楼下型消息**、**楼上型消息**、**学术型消息**中的哪一种：

- 若字符串 $s_{i, 3}$ 为 `louxia`，且 $s_{i, 2}$ 恰好与给出的某个网名相同（注意 $s_{i,2} = s_{i,1}$ 是允许的），则称这条消息是**楼下型消息**，$s_{i,2}$ 对应这条消息提到的网友；
- 若字符串 $s_{i,3}$ 为 `loushang`，且 $s_{i,2}$ 恰好与给出的某个网名相同（注意 $s_{i,2} = s_{i,1}$ 是允许的），则称这条消息是**楼上型消息**，$s_{i,2}$ 对应这条消息提到的网友；
- 若以上两个条件都不满足，则称这条消息是**学术消息**。

定义一个对所有消息的重排方案为一个 $1$ 到 $M$ 的排列 $a_1, a_2, a_3, \ldots, a_M$，表示第一条消息是 $(s_{a_1,1}, s_{a_1,2}, s_{a_1,3})$，第二条消息是 $(s_{a_2,1}, s_{a_2,2}, s_{a_2,3})$，依此类推。

对于一个重排方案 $a_1, a_2, a_3, \ldots, a_M$ 中的第 $i$（$1 \le i \le M$）条消息 $(s_{a_i,1}, s_{a_i,2}, s_{a_i,3})$，如下定义其是否是**符合实际情况的**：

- 若这条消息是**楼下型消息**，则这条消息是**符合实际情况的**当且仅当 $i \ne 1$ 且 $s_{a_{i - 1}, 1} = s_{a_i, 2}$，即上一条消息存在且它的发出者与这条消息提到的网友一致。
- 若这条消息是**楼上型消息**，则这条消息是**符合实际情况的**当且仅当 $i \ne M$ 且 $s_{a_{i + 1}, 1} = s_{a_i, 2}$，即下一条消息存在且它的发出者与这条消息提到的网友一致。
- 若这条消息是**学术消息**，则无论如何这条消息一定不是符合实际情况的，这是因为小 I 只想灌水不想学术。

在以上定义下，小 I 希望找到一个重排方案，使得该重排方案中符合实际情况的消息数量最多。你需要帮他找到这个方案以及这个方案中符合实际情况的消息数量。

**为了方便你的解题，小 I 还告诉了你帖子中消息的一个特殊限制：因为学术社区会禁言在社区中只灌水不学术的人，所以在小 I 给出的帖子里，每一个在帖子中发过言的人都一定会在帖子中发出至少一条学术消息。**
## 输入格式

**本题有多组测试数据**。第一行一个整数 $T$ 表示测试数据组数，接下来分别输入 $T$ 组数据。

对于每组测试数据，第一行两个整数 $N, M$ 分别表示帖子中发过消息的网友数量以及帖子的消息数量。

接下来 $N$ 行每行一个字符串 $n$ 表示在帖子中发过消息的一个网友的网名。保证每个测试数据中输入的 $N$ 个网友的网名两两不同。

接下来 $M$ 行每行三个字符串 $s_1, s_2, s_3$ 描述一条消息，相邻的字符串之间用一个空格分隔，其中 $s_1$ 一定与输入中某个网友的网名相等。

输入的所有字符串仅由大小写英文字母、下划线（`_`）、英文问号（`?`）、英文感叹号（`!`）和英文句号（`.`）构成，且长度不超过 $12$。

对于每组测试数据，保证输入的 $N$ 个网名都发出过至少一条消息，**且至少发出过一条学术消息**。

同一组测试数据中可能存在多条消息内容完全一致，此时应将他们视为**多条**消息。
## 输出格式

对于每组测试数据输出两行。

第一行输出一个非负整数表示所有重排方案中最大的符合实际情况的消息数量。

第二行输出 $M$ 个整数 $a_1, a_2, \ldots, a_m$，表示符合实际情况的消息最多的重排方案。

若有多种合法的重排方案，**输出任意一个即可**。
## 样例

### 样例输入 #1
```
2
4 15
builtin_clz
builtin_ctz
jinkela
OrzTourist
builtin_clz MengXin QiuZhu
builtin_ctz builtin_clz louxia
jinkela builtin_ctz louxia
builtin_ctz builtin_clz loushang
builtin_clz BieMoZheng YaoXueShu
OrzTourist builtin_clz louxia
OrzTourist OrzTourist louxia
builtin_clz Iam Angry!
builtin_clz builtin_clz loushang
builtin_clz builtin_clz louxia
builtin_clz builtin_clz loushang
builtin_clz builtin_clz louxia
builtin_ctz Xue Shu
jinkela Xue Shu
OrzTourist Xue Shu
1 9
builtin_clz
builtin_clz builtin_clz loushang
builtin_clz builtin_clz loushang
builtin_clz builtin_clz louxia
builtin_clz builtin_clz Loushang
builtin_clz builtin_clz LOUSHANG
builtin_clz Builtin_clz loushang
builtin_clz loushang louxia
builtin_clz builtin_clz builtin_clz
builtin_clz loushang builtin_clz

```
### 样例输出 #1
```
9
1 2 3 4 5 6 7 8 9 10 11 12 13 14 15
3
8 1 2 7 9 3 6 4 5

```
### 样例输入 #2
```
见附件中的 community/community2.in
```
### 样例输出 #2
```
见附件中的 community/community2.ans
```
## 提示

**【样例解释 #1】**

第一个测试数据与题目背景中给出的例子基本一致，而不同的点在于：为了满足每个人至少发出一条学术消息的要求，在该组数据输入的最后有几条额外的学术消息。

第二个测试数据中，输入的前两条消息是楼上型消息，第三条消息是楼下型消息，其他消息是学术消息。

**【样例 #3】**

见附件中的 `community/community3.in` 与 `community/community3.ans`。

该组样例满足数据范围中的特殊性质 A、特殊性质 B、特殊性质 C。

**【样例 #4】**

见附件中的 `community/community4.in` 与 `community/community4.ans`。

该组样例满足数据范围中的特殊性质 C。

**【数据范围】**

设 $\sum M$ 为单个测试点中所有测试数据的 $M$ 的和。

对于所有测试点，$1 \le T \le 100$，$1 \le N \le M \le 77777$，$1 \le \sum M \le 2.5 \times {10}^5$。

| $T \le$ | $M \le$ | $\sum M \le$ | 测试点编号 | 特殊性质 A | 特殊性质 B | 特殊性质 C |
|:-:|:-:|:-:|:-:|:-:|:-:|:-:|
| $5$ | $10$ | $50$ | $1$ | 无 | 无 | 无 |
| $10$ | $16$ | $160$ | $2$ | 无 | 无 | 无 |
| $30$ | $2222$ | $15000$ | $3 \sim 4$ | 有 | 有 | 有 |
| $30$ | $2222$ | $15000$ | $5 \sim 6$ | 有 | 无 | 有 |
| $30$ | $2222$ | $15000$ | $7 \sim 9$ | 无 | 有 | 有 |
| $30$ | $2222$ | $15000$ | $10 \sim 11$ | 无 | 无 | 有 |
| $30$ | $2222$ | $15000$ | $12 \sim 13$ | 无 | 无 | 无 |
| $100$ | $77777$ | $2.5 \times {10}^5$ | $14 \sim 15$ | 有 | 有 | 有 |
| $100$ | $77777$ | $2.5 \times {10}^5$ | $16$ | 有 | 无 | 有 |
| $100$ | $77777$ | $2.5 \times {10}^5$ | $17 \sim 19$ | 无 | 有 | 有 |
| $100$ | $77777$ | $2.5 \times {10}^5$ | $20 \sim 22$ | 无 | 无 | 有 |
| $100$ | $77777$ | $2.5 \times {10}^5$ | $23 \sim 25$ | 无 | 无 | 无 |

**注意：为了阅读方便，测试点编号在表格中的第四列。**

特殊性质 A：没有楼上型消息。**注意：这不意味着 $\bm{s_3}$ 不等于 `loushang`。**

特殊性质 B：对于每组测试数据，存在一个重排方案，使得每一条楼上型消息和楼下型消息都是符合实际情况的。

特殊性质 C：对于每组测试数据，若存在一条消息是 $s_1$ $s_2$ `loushang`，其中 $s_1, s_2$ 为任意字符串，则该组数据中一定不存在一条消息是 $s_2$ $s_1$ `louxia`。

**【评分方式】**

若一个测试点内所有测试数据的符合实际情况的消息数量都正确，你将获得该测试点 $50 \%$ 的分数；在此基础上，若一个测试点内所有测试数据的重排方案都正确，你将获得该测试点的所有分数。需要注意的是，**如果你只希望获得 $\bm{50 \%}$ 的分数，你也要保证在每组测试数据的第二行输出一个 $\bm{1}$ 到 $\bm{M}$ 的排列，否则实际分数与期望分数可能出现偏差**。

**【提示】**

因为这对你可能很重要，所以小 I 再一次强调：**因为学术社区会禁言在社区中只灌水不学术的人，所以在小 I 给出的帖子里，每一个在帖子中发过言的人都一定会在帖子中发出至少一条学术消息**。

本题输入规模较大，请使用较为快速的输入方式。


---

---
title: "[EC Final 2022] Magic"
layout: "post"
diff: NOI/NOI+/CTSC
pid: P9726
tag: ['2022', '网络流', 'O2优化', 'ICPC']
---
# [EC Final 2022] Magic
## 题目描述

**Warning: Unusual memory limit!**

You are given a sequence $a_0,\ldots,a_{2n}$. Initially, all numbers are zero. 

There are $n$ operations. The $i$-th operation is represented by two integers $l_i, r_i$ ($1\le l_i < r_i\le 2n, 1\le i\le n$), which assigns $i$ to $a_{l_i},\ldots,a_{r_i-1}$.  It is guaranteed that all the $2n$ integers, $l_1,l_2,\ldots, l_n, r_1, r_2, \ldots, r_n$, are distinct.

You need to perform each operation exactly once, in arbitrary order.

You want to maximize the number of $i$ $(0\leq i< 2n)$ such that $a_i\neq a_{i+1}$ after all $n$ operations. Output the maximum number.
## 输入格式

The first line contains an integer $n$ ($1\le n\le 5\times 10^3$).

The $i$-th line of the next $n$ lines contains a pair of integers $l_i, r_i$ ($1\le l_i < r_i\le 2n$). It is guaranteed that all the $2n$ integers, $l_1,l_2,\ldots, l_n, r_1, r_2, \ldots, r_n$, are distinct.
## 输出格式

Output one integer representing the answer in one line.
## 样例

### 样例输入 #1
```
5
2 3
6 7
1 9
5 10
4 8

```
### 样例输出 #1
```
9

```
## 题目翻译

- 你有一个序列 $a_0,a_1,a_2\dots a_{2n}$，初始全为 $0$。
- 给定 $n$ 个区间赋值操作，第 $i$ 个操作 $(l_i,r_i)(1\le l_i,r_i\le 2n)$ 表示把区间 $[l_i,r_i)$ 全部赋值为 $i$，**保证所有 $l_i,r_i$ 互不相同**。
- 你可以指定一个执行操作的顺序，最大化 $\sum_{i=0}^{2n-1}[a_i\ne a_{i+1}]$，输出这个最大值。
- $1\le n\le 5\times 10^3$，**注意空间限制**。


---

