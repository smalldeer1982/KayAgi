---
title: "[GCJ 2010 #2] Bacteria"
layout: "post"
diff: 提高+/省选-
pid: P13401
tag: ['图论', '2010', '广度优先搜索 BFS', '连通块', 'Google Code Jam']
---
# [GCJ 2010 #2] Bacteria
## 题目描述

A number of bacteria lie on an infinite grid of cells, each bacterium in its own cell.

Each second, the following transformations occur (all simultaneously):

1. If a bacterium has no neighbor to its north and no neighbor to its west, then it will die.
2. If a cell has no bacterium in it, but there are bacteria in the neighboring cells to the north and to the west, then a new bacterium will be born in that cell.

Upon examining the grid, you note that there are a positive, finite number of bacteria in one or more rectangular regions of cells.

Determine how many seconds will pass before all the bacteria die.

Here is an example of a grid that starts with 6 cells containing bacteria, and takes 6 seconds for all the bacteria to die. '1's represent cells with bacteria, and '0's represent cells without bacteria.

```
000010
011100
010000
010000
000000

000000
001110
011000
010000
000000

000000
000110
001100
011000
000000

000000
000010
000110
001100
000000

000000
000000
000010
000110
000000

000000
000000
000000
000010
000000

000000
000000
000000
000000
000000
```
## 输入格式

The input consists of:

- One line containing $C$, the number of test cases.

Then for each test case:

- One line containing $R$, the number of rectangles of cells that initially contain bacteria.
- $R$ lines containing four space-separated integers $X_1$ $Y_1$ $X_2$ $Y_2$. This indicates that all the cells with X coordinate between $X_1$ and $X_2$, inclusive, and Y coordinate between $Y_1$ and $Y_2$, inclusive, contain bacteria.

The rectangles may overlap.

North is in the direction of decreasing Y coordinate.

West is in the direction of decreasing X coordinate.
## 输出格式

For each test case, output one line containing "Case #$N$: $T$", where $N$ is the case number (starting from 1), and $T$ is the number of seconds until the bacteria all die.
## 样例

### 样例输入 #1
```
1
3
5 1 5 1
2 2 4 2
2 3 2 4
```
### 样例输出 #1
```
Case #1: 6
```
## 提示

**Limits**

- $1 \leq C \leq 100.$

**Small dataset (6 Pts, Test set 1 - Visible)**

- $1 \leq R \leq 10$
- $1 \leq X_1 \leq X_2 \leq 100$
- $1 \leq Y_1 \leq Y_2 \leq 100$

**Large dataset (25 Pts, Test set 2 - Hidden)**

- $1 \leq R \leq 1000$
- $1 \leq X_1 \leq X_2 \leq 1000000$
- $1 \leq Y_1 \leq Y_2 \leq 1000000$
- The number of cells initially containing bacteria will be at most $1000000$.



---

---
title: "[USACO2.1] 城堡 The Castle"
layout: "post"
diff: 提高+/省选-
pid: P1457
tag: ['搜索', 'USACO', '枚举', '连通块']
---
# [USACO2.1] 城堡 The Castle
## 题目背景

我们憨厚的 USACO 主人公农夫约翰（Farmer John）以无法想象的运气,在他生日那天收到了一份特别的礼物：一张“幸运爱尔兰”（一种彩票）。结果这张彩票让他获得了这次比赛唯一的奖品——坐落于爱尔兰郊外的一座梦幻般的城堡！
## 题目描述

喜欢吹嘘的农夫约翰立刻回到有着吹嘘传统的威斯康辛老家开始吹嘘了, 农夫约翰想要告诉他的奶牛们关于他城堡的一切。他需要做一些吹嘘前的准备工作：比如说知道城堡有多少个房间，每个房间有多大。  

另外，农夫约翰想要把一面单独的墙（指两个单位间的墙）拆掉以形成一个更大的房间。 你的工作就是帮农夫约翰做以上的准备，算出房间数与房间的大小。

城堡的平面图被划分成 $n \times m$ 个正方形的单位，一个这样的单位可以有 $0 \sim 4 $ 面墙环绕。城堡周围一定有外墙环绕以遮风挡雨。（就是说平面图的四周一定是墙。）

请仔细研究下面这个有注解的城堡平面图：

```plain
     1   2   3   4   5   6   7
   #############################
 1 #   |   #   |   #   |   |   #
   #####---#####---#---#####---#
 2 #   #   |   #   #   #   #   #
   #---#####---#####---#####---#
 3 #   |   |   #   #   #   #   #
   #---#########---#####---#---#
 4 # ->#   |   |   |   |   #   #
   #############################
```

- $\verb!#!$ 表示墙壁；
- $\verb!|!$ 和 $\verb!-!$ 表示没有墙壁；
- $\verb!->!$ 指向了一面墙，移除了这面墙我们就有一间最大的新房间。

友情提示，这个城堡的平面图是 $4 \times 7$ 个单位的。一个“房间”的是平面图中一个由 `#`、`-`、`|` 围成的格子（就是图里面的那一个个的格子）。比如说这个样例就有 $5$ 个房间。（大小分别为 $9,7,3,1,8$ 个单位（排名不分先后））

移去箭头所指的那面墙，可以使 $2$ 个房间合为一个新房间，且比移去其他墙所形成的房间都大。

城堡保证至少有 $2$ 个房间，而且一定有一面墙可以被移走。

## 输入格式

第一行两个正整数 $m,n$，表示城堡有 $n$ 行 $m$ 列。 

每一个单位的数字告诉我们这个单位的东西南北是否有墙存在。每个数字是由以下四个整数中的任意个加起来的。

$1$: 在西面有墙

$2$: 在北面有墙

$4$: 在东面有墙

$8$: 在南面有墙

城堡内部的墙会被规定两次。比如说 $(1,1)$ 南面的墙，亦会被标记为 $(2,1)$ 北面的墙。

## 输出格式

输出包含如下四行:

第一行：城堡的房间数目。

第二行：最大的房间的大小

第三行：移除一面墙能得到的最大的房间的大小

第四行：移除哪面墙可以得到面积最大的新房间。

选择最佳的墙来推倒。有多解时选最靠西的，仍然有多解时选最靠南的。同一格子北边的墙比东边的墙更优先。

用该墙的南邻单位的北墙或西邻单位的东墙来表示这面墙，方法是输出邻近单位的行数、列数和墙的方位（ `N`（北）或者 `E`（东））。

## 样例

### 样例输入 #1
```
7 4
11 6 11 6 3 10 6
7 9 6 13 5 15 5
1 10 12 7 13 7 5
13 11 10 8 10 12 13
```
### 样例输出 #1
```
5
9
16
4 1 E
```
## 提示

【数据范围】  
对于 $100\%$ 的数据，$1\le n,m \le 50$。

USACO 2.1

翻译来自NOCOW



---

---
title: "[USACO12JAN] Bovine Alliance G"
layout: "post"
diff: 提高+/省选-
pid: P3043
tag: ['2012', 'USACO', '连通块']
---
# [USACO12JAN] Bovine Alliance G
## 题目描述

Bessie and her bovine pals from nearby farms have finally decided that they are going to start connecting their farms together by trails in an effort to form an alliance against the farmers.  The cows in each of the N (1 <= N <= 100,000) farms were initially instructed to build a trail to exactly one other farm, for a total of N trails.  However months into the project only M (1 <= M < N) of these trails had actually been built.

Arguments between the farms over which farms already built a trail now threaten to split apart the cow alliance.  To ease tension, Bessie wishes to calculate how many ways the M trails that exist so far could have been built.  For example, if there is a trail connecting farms 3 and 4, then one possibility is that farm 3 built the trail, and the other possibility is that farm 4 built the trail.  Help Bessie by calculating the number of different assignments of trails to the farms that built them, modulo 1,000,000,007.  Two assignments are considered different if there is at least one trail built by a different farm in each assignment.

给出 n 个点 m 条边的无向图，现把点和边分组，每条边只能和相邻两点之一分在一组，点也可以单独一组。每个点只能被选择一次，求总方案数。

答案对 1e9+7 取模。
## 输入格式

\* Line 1: Two space-separated integers N and M

\* Lines 2..1+M: Line i+1 describes the ith trail.  Each line contains two space-separated integers u\_i and v\_i (1 <= u\_i, v\_i <= N, u\_i != v\_i) describing the pair of farms connected by the trail.

## 输出格式

\* Line 1: A single line containing the number of assignments of trails to farms, taken modulo 1,000,000,007.  If no assignment satisfies the above conditions output 0.

## 样例

### 样例输入 #1
```
5 4 
1 2 
3 2 
4 5 
4 5 

```
### 样例输出 #1
```
6 

```
### 样例输入 #2
```
6 5
1 2
2 3
3 4
1 4
2 4
```
### 样例输出 #2
```
0
```
## 提示

Note that there can be two trails between the same pair of farms.


There are 6 possible assignments.  Letting {a,b,c,d} mean that farm 1 builds trail a, farm 2 builds trail b, farm 3 builds trail c, and farm 4 builds trail d, the assignments are:

```cpp
{2, 3, 4, 5} 
{2, 3, 5, 4} 
{1, 3, 4, 5} 
{1, 3, 5, 4} 
{1, 2, 4, 5} 
{1, 2, 5, 4} 

```


---

---
title: "[CQOI2017] 小Q的棋盘"
layout: "post"
diff: 提高+/省选-
pid: P3698
tag: ['动态规划 DP', '贪心', '2017', '重庆', '各省省选', '枚举', '背包 DP', '连通块']
---
# [CQOI2017] 小Q的棋盘
## 题目描述

小 Q 正在设计一种棋类游戏。

在小 Q 设计的游戏中，棋子可以放在棋盘上的格点中。某些格点之间有连线，棋子只能在有连线的格点之间移动。整个棋盘上共有 $V$ 个格点，编号为 $0,1,2,\cdots, V- 1$，它们是连通的，也就是说棋子从任意格点出发，总能到达所有的格点。小 Q 在设计棋盘时，还保证棋子从一个格点移动到另外任一格点的路径是唯一的。

小 Q 现在想知道，当棋子从格点 $0$ 出发，移动 $N$ 步最多能经过多少格点。格点可以重复经过多次，但不重复计数。

## 输入格式

第一行包含2个正整数 $V, N$，其中 $V$ 表示格点总数，$N$ 表示移动步数。

接下来 $V-1$ 行，每行两个数 $a_i,b_i$，表示编号为$a_i,b_i$ 的两个格点之间有连线。

## 输出格式

输出一行一个整数，表示最多经过的格点数量。

## 样例

### 样例输入 #1
```
5 2
1 0
2 1
3 2
4 3
```
### 样例输出 #1
```
3
```
### 样例输入 #2
```
9 5
0 1
0 2
2 6
4 2
8 1
1 3
3 7
3 5
```
### 样例输出 #2
```
5
```
## 提示

【输入输出样例 1 说明】

从格点 $0$ 出发移动 $2$ 步。经过 $0, 1, 2$ 这 $3$ 个格点。

【输入输出样例 2 说明】

一种可行的移动路径为 $0 \to 1 \to 3 \to 5 \to 3 \to 7$，经过 $0, 1, 3, 5, 7$ 这 $5$ 个格点。

【数据规模与约定】

对于 $100\%$ 的测试点，$1\le N,V ≤ 100$，$0 ≤a_i,b_i< V$。



---

---
title: "小D的地下温泉"
layout: "post"
diff: 提高+/省选-
pid: P3820
tag: ['并查集', '洛谷原创', '广度优先搜索 BFS', '连通块', '洛谷月赛']
---
# 小D的地下温泉
## 题目背景

小D最喜欢泡温泉了。小D找某奸商租下了一块$N$行$M$列的地，左上角为$(1,1)$，右下角为$(N,M)$。小D本以为这块地里全是温泉，结果这块地极不稳定，曾经发生过一些地形变动，所以其中一些地方全是土。

## 题目描述

一开始他会告诉你当前这块地的情况，但是小D有一些假操作，希望你操作给他看：

1. 由小D指定$w$个位置，他希望知道其中哪个位置下水泡温泉的范围最大。泡温泉的范围定义为指定位置通过向上下左右四个方向能到达的位置的个数。若询问的位置为土，则范围为0。如果如果有多个位置均为最大，输出给出顺序较前的那个。位置编号为$1,2,...,w$。

2. 由小D指定$w$个位置，他会使用膜法按顺序翻转这$w$个地方的地形。即若原位置是土，则该位置变为温泉；若原位置是温泉，则该位置变为土。因为小D不希望活动范围减少得太快，所以他在将温泉变为土时不会将一个区域分割。

## 输入格式

第一行输入两个整数，$N,M$，为土地大小。

接下来的$N$行每行输入$M$个字符，为'.'（代表温泉）或'\*'（代表土）（不包括引号）

第$N+2$行输入一个整数，$Q$，为操作数量。

接下来的$Q$行，每行先读入两个整数$opt$和$w$，表示操作类型和指定点的数量，在同一行还有$2\times w$个数$x_{1},y_{1},x_{2},y_{2},...,x_{w},y_{w}$，分别表示$w$个操作的位置为$(x_{1},y_{1}),(x_{2},y_{2}),...,(x_{w},y_{w})$。

## 输出格式

对于每个操作1，输出询问的答案并换行

## 样例

### 样例输入 #1
```
5 5
.*...
.****
*....
*****
.....
3
1 2 1 1 1 3
2 1 3 1
1 2 1 1 1 3
```
### 样例输出 #1
```
2
1

```
## 提示

对于30%的数据，$N,M\le 100,\sum w\le 100$

对于70%的数据，$N,M\le 1000$

对于100%的数据，$1\le N\times M,Q\le 10^{6},\sum w\le 10^{6},w\geq 1$

数据在windows下制作



---

---
title: "[USACO18JAN] MooTube G"
layout: "post"
diff: 提高+/省选-
pid: P4185
tag: ['2018', 'USACO', '并查集', '连通块']
---
# [USACO18JAN] MooTube G
## 题目背景

*本题与 [银组同名题目](/problem/P6111) 在题意上一致，唯一的差别是数据范围。*
## 题目描述

在业余时间，Farmer John 创建了一个新的视频共享服务，他将其命名为 MooTube。在 MooTube 上，Farmer John 的奶牛可以录制，分享和发现许多有趣的视频。他的奶牛已经发布了 $N$ 个视频（$1 \leq N \leq 10^5$），为了方便将其编号为  $1 \ldots N$ 。然而，FJ 无法弄清楚如何帮助他的奶牛找到他们可能喜欢的新视频。

FJ 希望为每个 MooTube 视频创建一个“推荐视频”列表。这样，奶牛将被推荐与他们已经观看过的视频最相关的视频。

FJ 设计了一个“相关性”度量标准，顾名思义，它确定了两个视频相互之间的相关性。他选择 $N-1$ 对视频并手动计算其之间的相关性。然后，FJ 将他的视频建成一棵树，其中每个视频是节点，并且他手动将 $N-1$ 对视频连接。为了方便，FJ 选择了 $N-1$ 对，这样任意视频都可以通过一条连通路径到达任意其他视频。 FJ 决定将任意一对视频的相关性定义为沿此路径的任何连接的最小相关性。

Farmer John 想要选择一个 $K$ 值，以便在任何给定的 MooTube 视频旁边，推荐所有其他与该视频至少有 $K$ 相关的视频。然而，FJ 担心会向他的奶牛推荐太多的视频，这可能会分散他们对产奶的注意力！因此，他想设定适当的 $K$ 值。 Farmer John希望得到您的帮助，回答有关 $K$ 值的推荐视频的一些问题。
## 输入格式

第一行输入包含 $N$ 和 $Q$（$1 \leq Q \leq 10^5$）。

接下来的 $N-1$ 行描述了 FJ 手动比较的一对视频。 每行包括三个整数  $p_i$，$q_i$ 和 $r_i$（$1 \leq p_i, q_i \leq N$，$1 \leq r_i \leq 10^9$），表示视频 $p_i$ 和 $q_i$ 已连接并且相关性为 $r_i$。

接下来的 $Q$ 行描述了 Farmer John 的 $Q$ 个问题。每行包含两个整数，$k_i$ 和 $v_i$（$1 \leq k_i \leq 10^9$，$1 \leq v_i \leq N$），表示 FJ 的第 $i$ 个问题询问中当 $K = k_i$ 时，第 $v_i$ 个视频推荐列表中将推荐的视频数。
## 输出格式

输出 $Q$ 行。在第 $i$ 行，输出 FJ 的第 $i$ 个问题的答案。
## 样例

### 样例输入 #1
```
4 3
1 2 3
2 3 2
2 4 4
1 2
4 1
3 1
```
### 样例输出 #1
```
3
0
2

```


---

---
title: "[JSOI2010] 连通数"
layout: "post"
diff: 提高+/省选-
pid: P4306
tag: ['2010', '各省省选', '江苏', '枚举', '图论建模', '连通块', '强连通分量']
---
# [JSOI2010] 连通数
## 题目背景

本题数据过水，可前往 https://www.luogu.com.cn/problem/U143178 提交

$\text{upd 2022.8.4}$：已作为 Hack 数据合并进来。
## 题目描述

度量一个有向图连通情况的一个指标是连通数，指图中可达顶点对个的个数。

如图

![](https://cdn.luogu.com.cn/upload/image_hosting/8jviim6w.png)

顶点 $1$ 可达 $1, 2, 3, 4, 5$

顶点 $2$ 可达 $2, 3, 4, 5$

顶点 $3$ 可达 $3, 4, 5$

顶点 $4, 5$ 都只能到达自身。

所以这张图的连通数为 $14$。

给定一张图，请你求出它的连通数
## 输入格式

输入数据第一行是图顶点的数量，一个正整数 $N$。  
接下来 $N$ 行，每行 $N$ 个字符。第 $i$ 行第 $j$ 列的 `1` 表示顶点 $i$ 到 $j$ 有边，`0` 则表示无边。
## 输出格式

输出一行一个整数，表示该图的连通数。
## 样例

### 样例输入 #1
```
3
010
001
100
```
### 样例输出 #1
```
9
```
## 提示

对于 $100 \%$ 的数据，$1 \le N \le 2000$。


---

---
title: "[USACO22DEC] Strongest Friendship Group G"
layout: "post"
diff: 提高+/省选-
pid: P8905
tag: ['USACO', '并查集', '2022', '枚举', '连通块']
---
# [USACO22DEC] Strongest Friendship Group G
## 题目描述

Farmer John 有 $N$ 头奶牛（$2 \le N \le 10^5$），编号为 $1\cdots N$。这些奶牛中有 $M(1 \le M \le 2\times 10^5)$ 对朋友。

一组奶牛被称为是「小团体」，如果该组中的每头奶牛都可以从该组中的每头其他奶牛出发通过完全位于该组内的一系列朋友关系到达（连接到组外奶牛的朋友关系无效）。小团体的「强度」是组内奶牛的最小组内朋友数乘以组内奶牛的数量（同样，注意连接到组外奶牛的朋友关系不计入此定义）。

求所有小团体的最大强度。 
## 输入格式

输入的第一行包含 $N$ 和 $M$。

以下 $M$ 行每行包含两个整数 $u_i$ 和 $v_i$，表示奶牛 $u_i$ 和 $v_i$ 是朋友（$1 \le u_i,v_i \le N,u_i\neq v_i$）。每个奶牛无序对至多出现一次。 
## 输出格式

 输出一行，包含所有小团体的最大强度。 
## 样例

### 样例输入 #1
```
8 10
1 2
1 3
1 4
2 3
2 4
3 4
1 5
2 6
3 7
4 8
```
### 样例输出 #1
```
12
```
## 提示

### 样例 1 解释

可以观察到最大强度来自编号为 $1,2,3,4$ 的奶牛组。该组内奶牛的最小朋友数为 $3$，故答案为 $4 \times 3=12$。

### 测试点性质

 - 对于 $1 \le T \le 3$，测试点 $T$ 满足 $N \le 16$。
 - 对于 $4 \le T \le 9$，测试点 $T$ 满足 $N \le 1000$。
- 对于 $10 \le T \le 20$，测试点 $T$ 没有额外限制。 


---

