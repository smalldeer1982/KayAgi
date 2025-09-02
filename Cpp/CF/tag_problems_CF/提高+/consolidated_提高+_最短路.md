---
title: "The Shortest Statement"
layout: "post"
diff: 提高+/省选-
pid: CF1051F
tag: ['最短路', '生成树', '最近公共祖先 LCA']
---

# The Shortest Statement

## 题目描述

给你一个有 $n$ 个点，$m$ 条边的无向连通图。有 $q$ 次询问，第 $i$ 次询问回答从 $u_i$ 到 $v_i$ 的最短路的长度。

## 输入格式

第一行有两个数 $n$ 和 $m$（$1 \leq n,m \leq 10^5,m-n\leq 20$）。 接下来 $m$ 行包含一条边，输入三个正整数 $u_i,v_i,d_i(1 \leq u_i,v_i \leq n,1 \leq d_i \leq 10^9)$，意思是 $u_i$ 到 $v_i$ 之间有一条长度为 $d_i$ 的边。数据保证不存在自环和重边。下一行再输入一个数 $q$，接下来的 $q$ 行每行输入两个正整数 $u_i,v_i(1 \leq u_i,v_i \leq n)$。

## 输出格式

输出 $q$ 行，第 $i$ 行的输出的应为第 $i$ 次询问的答案。

## 样例 #1

### 输入

```
3 3
1 2 3
2 3 1
3 1 5
3
1 2
1 3
2 3

```

### 输出

```
3
4
1

```

## 样例 #2

### 输入

```
8 13
1 2 4
2 3 6
3 4 1
4 5 12
5 6 3
6 7 8
7 8 7
1 4 1
1 8 3
2 6 9
2 7 1
4 6 3
6 8 2
8
1 5
1 7
2 3
2 8
3 7
3 4
6 8
7 8

```

### 输出

```
7
5
6
7
7
1
2
7

```



---

---
title: "Three Pieces"
layout: "post"
diff: 提高+/省选-
pid: CF1065D
tag: ['搜索', '状态合并', '最短路']
---

# Three Pieces

## 题目描述

You stumbled upon a new kind of chess puzzles. The chessboard you are given is not necesserily $ 8 \times 8 $ , but it still is $ N \times N $ . Each square has some number written on it, all the numbers are from $ 1 $ to $ N^2 $ and all the numbers are pairwise distinct. The $ j $ -th square in the $ i $ -th row has a number $ A_{ij} $ written on it.

In your chess set you have only three pieces: a knight, a bishop and a rook. At first, you put one of them on the square with the number $ 1 $ (you can choose which one). Then you want to reach square $ 2 $ (possibly passing through some other squares in process), then square $ 3 $ and so on until you reach square $ N^2 $ . In one step you are allowed to either make a valid move with the current piece or replace it with some other piece. Each square can be visited arbitrary number of times.

A knight can move to a square that is two squares away horizontally and one square vertically, or two squares vertically and one square horizontally. A bishop moves diagonally. A rook moves horizontally or vertically. The move should be performed to a different square from the one a piece is currently standing on.

You want to minimize the number of steps of the whole traversal. Among all the paths to have the same number of steps you want to choose the one with the lowest number of piece replacements.

What is the path you should take to satisfy all conditions?

## 输入格式

The first line contains a single integer $ N $ ( $ 3 \le N \le 10 $ ) — the size of the chessboard.

Each of the next $ N $ lines contains $ N $ integers $ A_{i1}, A_{i2}, \dots, A_{iN} $ ( $ 1 \le A_{ij} \le N^2 $ ) — the numbers written on the squares of the $ i $ -th row of the board.

It is guaranteed that all $ A_{ij} $ are pairwise distinct.

## 输出格式

The only line should contain two integers — the number of steps in the best answer and the number of replacement moves in it.

## 说明/提示

Here are the steps for the first example (the starting piece is a knight):

1. Move to $ (3, 2) $
2. Move to $ (1, 3) $
3. Move to $ (3, 2) $
4. Replace the knight with a rook
5. Move to $ (3, 1) $
6. Move to $ (3, 3) $
7. Move to $ (3, 2) $
8. Move to $ (2, 2) $
9. Move to $ (2, 3) $
10. Move to $ (2, 1) $
11. Move to $ (1, 1) $
12. Move to $ (1, 2) $

## 样例 #1

### 输入

```
3
1 9 3
8 6 7
4 2 5

```

### 输出

```
12 1

```



---

---
title: "Moving Platforms"
layout: "post"
diff: 提高+/省选-
pid: CF1932G
tag: ['最短路', '扩展欧几里德算法']
---

# Moving Platforms

## 题目描述

有一个迷宫，迷宫由 $n$ 个平台组成，所有平台间由 $m$ 条通道相连。

每个平台都在某个高度 $l_i$ 上， $l_i$ 是一个 $0$ 到 $H - 1$ 的整数。对于每一步移动，如果你当前在平台 $i$ 上，你可以选择停留在原地或者移动到另一个平台 $j$ 上。如果要移动到平台 $j$ ，那么它们必须由通道连接，并且它们的高度必须相同，即 $l_i = l_j$。

在每一步移动之后，所有平台的高度都会改变。对于所有 $i$，平台 $i$ 的新高度计算为 $l'_i = (l_i + s_i) \bmod H$。

你的起点是平台 $1$ 。请找到到达平台 $n$ 所需的最少步骤数。

## 输入格式

第一行输入一个整数 $t$（$1 \le t \le 10^4$），表示测试数据的组数。

对于每组测试数据，第一行包含三个整数 $n$、$m$ 和 $H$（$2 \le n \le 10^5$，$1 \le m \le 10^5$，$1 \le H \le 10^9$）。

第二行包含 $n$ 个整数 $l_i$，表示每个平台的初始高度（$0 \le l_i \le H-1$）。

第三行包含 $n$ 个整数 $s_i$，表示每个平台的高度变化值（$0 \le s_i \le H-1$）。

接下来的 $m$ 行，每行输入一对整数，表示相连的平台。保证每对平台之间最多有一条通道，并且没有将平台连接到其本身的通道。

保证所有测试点中 $n$ 的总和不超过 $10^5$，$m$ 的总和不超过 $10^5$。

## 输出格式

对于每组测试数据，每行输出一个整数，表示从平台 $1$ 到平台 $n$ 所需的最少步骤数。

如果无法到达平台 $n$，请输出 $-1$。

## 样例 #1

### 输入

```
3
3 3 10
1 9 4
2 3 0
1 2
3 2
1 3
2 1 10
1 2
4 6
1 2
8 7 25
22 14 5 3 10 14 11 1
9 5 4 10 7 16 18 18
2 8
6 3
3 5
7 5
2 6
1 4
4 7
```

### 输出

```
6
-1
52
```



---

---
title: "Call During the Journey"
layout: "post"
diff: 提高+/省选-
pid: CF2000G
tag: ['二分', '最短路']
---

# Call During the Journey

## 题目描述

你所居住的城市由 $n$ 个交叉路口和连接几对交叉路口的 $m$ 条街道组成。您可以在每条街道上向任一方向前进。没有两条街道连接同一对交叉路口，也没有一条街道只连接一个交叉路口。您可以从任何一个交叉路口到达另一个交叉路口，但可能会经过其他一些交叉路口。

每分钟，你可以在路口 $u_i$ 登上一辆公交车，然后行驶 $l_{i1}$ 分钟到达路口 $v_i$ 。相反，您可以在 $l_{i1}$ 分钟内从路口 $v_i$ 到达路口 $u_i$ 。您只能在交叉路口上下车。只有当您正在某交叉路口时，才能在该交叉路口登上公共汽车。

您也可以沿着每条街道步行，这需要 $l_{i2} \gt l_{i1}$ 分钟。

您可以在十字路口停车。

您住在十字路口编号 $1$ 处。今天您在 $0$ 点起床，在路口编号 $n$ 处有一个重要活动安排，您必须在 $t_0$ 点之前到达。你还计划打一个电话，通话时间为 $t_1$ 至 $t_2$ 分钟（ $t_1 \lt t_2 \lt t_0$ ）。

通话期间，您不能乘坐公共汽车，但可以在任何街道上行走、停靠在站点处或待在家里。您可以在 $t_1$ 分钟下车，在 $t_2$ 分钟再次上车。

由于您希望获得充足的睡眠，您开始好奇您可以多晚离开家，以便有时间讲电话，同时还不会在活动中迟到？

## 输入格式

第一行包含一个整数 $t$ ( $1 \le t \le 10^4$ ) - 测试用例数。下面是测试用例的说明。

每个测试用例的第一行包含两个整数 $n$ , $m$ ( $2 \le n \le 10^5, 1 \le m \le 10^5$ ) - 城市中十字路口和街道的数量。

每个测试用例的第二行分别包含三个整数 $t_0$ , $t_1$ , $t_2$ ( $1 \lt t_1 \lt t_2 \lt t_0 \le 10^9$ ) - 事件开始时间、电话开始时间和结束时间。

每个测试用例接下来的 $m$ 行包含对街道的描述。

第 $i$ 行包含四个整数 $u_i$ 、 $v_i$ 、 $l_{i1}$ 、 $l_{i2}$ （ $1 \le u_i, v_i \le n$ 、 $u_i \neq v_i$ 、 $1 \le l_{i1} \lt l_{i2} \le 10^9$ ）--即由第 $i$ 条街道连接的十字路口的编号，以及沿街乘坐公交车和步行所需的时间。保证没有两条街道连接同一对交叉路口，并且可以从任何一个交叉路口到达另一个交叉路口。

保证所有测试用例中 $n$ 的值之和不超过 $10^5$ 。同时保证所有测试用例中 $m$ 的值之和不超过 $10^5$ 。

## 输出格式

对于每个测试用例，输出一个整数--您离开家的最晚时间，以便有时间讲电话而不会迟到。如果您不能按时到达活动地点，则输出 `-1`。

## 样例 #1

### 输入

```
7
5 5
100 20 80
1 5 30 100
1 2 20 50
2 3 20 50
3 4 20 50
4 5 20 50
2 1
100 50 60
1 2 55 110
4 4
100 40 60
1 2 30 100
2 4 30 100
1 3 20 50
3 4 20 50
3 3
100 80 90
1 2 1 10
2 3 10 50
1 3 20 21
3 2
58 55 57
2 1 1 3
2 3 3 4
2 1
12 9 10
2 1 6 10
5 5
8 5 6
2 1 1 8
2 3 4 8
4 2 2 4
5 3 3 4
4 5 2 6
```

### 输出

```
0
-1
60
80
53
3
2
```



---

---
title: "X Aura"
layout: "post"
diff: 提高+/省选-
pid: CF2045G
tag: ['图论', '最短路']
---

# X Aura

## 题目描述

Mount ICPC 可以被表示为一个网格，共有 $R$ 行（编号从 $1$ 到 $R$）和 $C$ 列（编号从 $1$ 到 $C$）。位于第 $r$ 行和第 $c$ 列的单元格被表示为 $(r, c)$，其高度为 $H_{r, c}$。两个单元格是相邻的，如果它们共享一条边。正式来说，$(r, c)$ 相邻于 $(r-1, c)$、$(r+1, c)$、$(r, c-1)$ 和 $(r, c+1)$，如果这些单元格存在。

你只能在相邻的单元格之间移动，每次移动都会产生一个惩罚。具有一个奇数正整数 $X$ 的气场，从高度为 $h_1$ 的单元格移动到高度为 $h_2$ 的单元格会产生 $(h_1 - h_2)^X$ 的惩罚。注意，惩罚可以是负数。

你想回答 $Q$ 个独立的场景。在每个场景中，你从起始单元格 $(R_s, C_s)$ 开始，想要移动到目标单元格 $(R_f, C_f)$，以最小的总惩罚。有些场景可能会使总惩罚变得任意小，这样的场景被称为无效的。找到从起始单元格到目标单元格的最小总惩罚，或者确定场景是否无效。

## 输入格式

第一行包含三个整数 $R$、$C$ 和 $X$（$1 \leq R, C \leq 1000$；$1 \leq X \leq 9$；$X$ 是一个奇数整数）。

接下来的 $R$ 行每行包含一个长度为 $C$ 的字符串 $H_r$。每个字符在 $H_r$ 中都是一个数字，从 $0$ 到 $9$。$H_r$ 中的第 $c$ 个字符表示单元格 $(r, c)$ 的高度，即 $H_{r, c}$。

下一行包含一个整数 $Q$（$1 \leq Q \leq 100,000$）。

接下来的 $Q$ 行每行包含四个整数 $R_s$、$C_s$、$R_f$ 和 $C_f$（$1 \leq R_s, R_f \leq R$；$1 \leq C_s, C_f \leq C$）。

## 输出格式

对于每个场景，输出以下内容在一行中。如果场景是无效的，输出“INVALID”。否则，输出一个整数，表示从起始单元格到目标单元格的最小总惩罚。

## 样例 #1

### 输入

```
3 4 1
3359
4294
3681
5
1 1 3 4
3 3 2 1
2 2 1 4
1 3 3 2
1 1 1 1
```

### 输出

```
2
4
-7
-1
0
```

## 样例 #2

### 输入

```
2 4 5
1908
2023
2
1 1 2 4
1 1 1 1
```

### 输出

```
INVALID
INVALID
```

## 样例 #3

### 输入

```
3 3 9
135
357
579
2
3 3 1 1
2 2 2 2
```

### 输出

```
2048
0
```



---

---
title: "Another Exercise on Graphs (hard version)"
layout: "post"
diff: 提高+/省选-
pid: CF2057E2
tag: ['图论', '最短路', '生成树']
---

# Another Exercise on Graphs (hard version)

## 题目描述

这是该问题的简单版本。不同版本间的区别在于此版本对 $m$ 有额外约束。只有在你解决了该问题的所有版本后，才能进行 hack。

最近，"T-generation" 的导师需要筹备一场训练赛。他们发现缺少一道题目，且整场比赛中没有图论相关的问题，于是设计了如下题目。

给定一个包含 $n$ 个顶点和 $m$ 条边的连通带权无向图，图中无自环和重边。

处理 $q$ 次形如 $(a, b, k)$ 的查询：在从顶点 $a$ 到顶点 $b$ 的所有路径中，找出路径上边权的第 $k$ 小最大值$^{\dagger}$。

导师们认为这个问题非常有趣，但存在一个问题：他们不知道如何解决它。请帮助他们解决这个问题，因为距离比赛开始仅剩几小时。

$^{\dagger}$ 设 $w_1 \ge w_2 \ge \ldots \ge w_{h}$ 为某条路径中所有边权按非递增顺序排列后的结果。该路径边权的第 $k$ 大值即为 $w_{k}$。


## 输入格式

输入包含多组测试数据。第一行是一个整数 $ t $（$ 1 \le t \le 100 $），表示测试数据的组数。接下来是每组测试数据的详细描述。

每组测试数据的第一行包含三个整数 $ n, m $ 和 $ q $（$ 2 \le n \le 400 $，$ n - 1 \le m \le \frac{n \cdot (n - 1)}{2} $，$ 1 \le q \le 3 \cdot 10^5 $），分别表示图的顶点数、边数和查询数。

接下来的 $ m $ 行中，每行包含三个整数 $ v, u $ 和 $ w $（$ 1 \le v, u \le n $，$ 1 \le w \le 10^9 $），表示图中的一条边及其权重。确保图中没有自环和重边。

接下来的 $ q $ 行中，每行包含三个整数 $ a, b $ 和 $ k $（$ 1 \le a, b \le n $，$ k \ge 1 $），代表一个查询。确保从顶点 $ a $ 到顶点 $ b $ 的所有路径至少有 $ k $ 条边。

确保所有测试数据的 $ n $ 总和不超过 $ 400 $。

确保所有测试数据的 $ q $ 总和不超过 $ 3 \cdot 10^5 $。

## 输出格式

对于每组测试数据，输出所有查询的答案。

## 说明/提示

在第一组测试数据中，第一个查询的一个最优路径为 $ 1 \rightarrow 3 \rightarrow 4 $，这条路径上第二大的边权值为 $ 1 $。在第二个查询中，一个最优路径为 $ 2 \rightarrow 4 \rightarrow 3 $，该路径上最大的边权值为 $ 2 $。

在第二组测试数据中，第一个查询的一个最优路径为 $ 1 \rightarrow 2 \rightarrow 4 \rightarrow 5 \rightarrow 6 $，这条路径上第三大的边权值为 $ 2 $。

 **本翻译由 AI 自动生成**

## 样例 #1

### 输入

```
3
4 4 2
1 2 2
2 4 2
1 3 4
3 4 1
1 4 2
2 3 1
6 7 3
1 2 10
2 3 3
3 4 9
4 5 2
5 6 1
2 4 10
4 6 10
1 6 3
1 6 2
2 4 1
11 17 10
1 4 5
1 3 19
1 2 10
3 2 13
4 5 1
4 6 11
3 5 9
3 6 18
2 7 17
5 8 15
5 10 8
6 9 4
7 10 20
7 8 16
8 11 3
9 11 6
10 11 14
3 11 1
3 11 3
1 11 1
1 11 4
1 11 3
8 2 2
10 4 1
3 9 2
3 9 1
6 7 3
```

### 输出

```
1 2
2 9 9
11 3 11 1 3 10 8 4 11 4
```



---

---
title: "Robot Control"
layout: "post"
diff: 提高+/省选-
pid: CF346D
tag: ['动态规划 DP', '最短路']
---

# Robot Control

## 题目描述

The boss of the Company of Robot is a cruel man. His motto is "Move forward Or Die!". And that is exactly what his company's product do. Look at the behavior of the company's robot when it is walking in the directed graph. This behavior has been called "Three Laws of Robotics":

- Law 1. The Robot will destroy itself when it visits a vertex of the graph which it has already visited.
- Law 2. The Robot will destroy itself when it has no way to go (that is when it reaches a vertex whose out-degree is zero).
- Law 3. The Robot will move randomly when it has multiple ways to move (that is when it reach a vertex whose out-degree is more than one). Of course, the robot can move only along the directed edges of the graph.

Can you imagine a robot behaving like that? That's why they are sold at a very low price, just for those who are short of money, including mzry1992, of course. mzry1992 has such a robot, and she wants to move it from vertex $ s $ to vertex $ t $ in a directed graph safely without self-destruction. Luckily, she can send her robot special orders at each vertex. A special order shows the robot which way to move, if it has multiple ways to move (to prevent random moving of the robot according to Law 3). When the robot reaches vertex $ t $ , mzry1992 takes it off the graph immediately. So you can see that, as long as there exists a path from $ s $ to $ t $ , she can always find a way to reach the goal (whatever the vertex $ t $ has the outdegree of zero or not).

 ![](https://cdn.luogu.com.cn/upload/vjudge_pic/CF346D/70cbc1b898581d5fe7e403c459e5024fa4aa2e72.png) Sample 2 However, sending orders is expensive, so your task is to find the minimum number of orders mzry1992 needs to send in the worst case. Please note that mzry1992 can give orders to the robot while it is walking on the graph. Look at the first sample to clarify that part of the problem.

## 输入格式

The first line contains two integers $ n $ ( $ 1<=n<=10^{6} $ ) — the number of vertices of the graph, and $ m $ ( $ 1<=m<=10^{6} $ ) — the number of edges. Then $ m $ lines follow, each with two integers $ u_{i} $ and $ v_{i} $ ( $ 1<=u_{i},v_{i}<=n $ ; $ v_{i}≠u_{i} $ ), these integers denote that there is a directed edge from vertex $ u_{i} $ to vertex $ v_{i} $ . The last line contains two integers $ s $ and $ t $ ( $ 1<=s,t<=n $ ).

It is guaranteed that there are no multiple edges and self-loops.

## 输出格式

If there is a way to reach a goal, print the required minimum number of orders in the worst case. Otherwise, print -1.

## 说明/提示

Consider the first test sample. Initially the robot is on vertex 1. So, on the first step the robot can go to vertex 2 or 3. No matter what vertex the robot chooses, mzry1992 must give an order to the robot. This order is to go to vertex 4. If mzry1992 doesn't give an order to the robot at vertex 2 or 3, the robot can choose the "bad" outgoing edge (return to vertex 1) according Law 3. So, the answer is one.

## 样例 #1

### 输入

```
4 6
1 2
2 1
1 3
3 1
2 4
3 4
1 4

```

### 输出

```
1

```

## 样例 #2

### 输入

```
4 5
1 2
2 1
1 3
2 4
3 4
1 4

```

### 输出

```
1

```



---

---
title: "Breaking Good"
layout: "post"
diff: 提高+/省选-
pid: CF507E
tag: ['最短路']
---

# Breaking Good

## 题目描述

Breaking Good is a new video game which a lot of gamers want to have. There is a certain level in the game that is really difficult even for experienced gamers.

Walter William, the main character of the game, wants to join a gang called Los Hermanos (The Brothers). The gang controls the whole country which consists of $ n $ cities with $ m $ bidirectional roads connecting them. There is no road is connecting a city to itself and for any two cities there is at most one road between them. The country is connected, in the other words, it is possible to reach any city from any other city using the given roads.

The roads aren't all working. There are some roads which need some more work to be performed to be completely functioning.

The gang is going to rob a bank! The bank is located in city $ 1 $ . As usual, the hardest part is to escape to their headquarters where the police can't get them. The gang's headquarters is in city $ n $ . To gain the gang's trust, Walter is in charge of this operation, so he came up with a smart plan.

First of all the path which they are going to use on their way back from city $ 1 $ to their headquarters $ n $ must be as short as possible, since it is important to finish operation as fast as possible.

Then, gang has to blow up all other roads in country that don't lay on this path, in order to prevent any police reinforcements. In case of non-working road, they don't have to blow up it as it is already malfunctional.

If the chosen path has some roads that doesn't work they'll have to repair those roads before the operation.

Walter discovered that there was a lot of paths that satisfied the condition of being shortest possible so he decided to choose among them a path that minimizes the total number of affected roads (both roads that have to be blown up and roads to be repaired).

Can you help Walter complete his task and gain the gang's trust?

## 输入格式

The first line of input contains two integers $ n,m $ ( $ 2<=n<=10^{5} $ , ![](https://cdn.luogu.com.cn/upload/vjudge_pic/CF507E/7412e0c24161431dea3b8fc7986fb97f2e01ac9d.png)), the number of cities and number of roads respectively.

In following $ m $ lines there are descriptions of roads. Each description consists of three integers $ x,y,z $ ( $ 1<=x,y<=n $ , ![](https://cdn.luogu.com.cn/upload/vjudge_pic/CF507E/1e51689966dea809d53fe0a67f2ab14a233e8803.png)) meaning that there is a road connecting cities number $ x $ and $ y $ . If $ z=1 $ , this road is working, otherwise it is not.

## 输出格式

In the first line output one integer $ k $ , the minimum possible number of roads affected by gang.

In the following $ k $ lines output three integers describing roads that should be affected. Each line should contain three integers $ x,y,z $ ( $ 1<=x,y<=n $ , ![](https://cdn.luogu.com.cn/upload/vjudge_pic/CF507E/1e51689966dea809d53fe0a67f2ab14a233e8803.png)), cities connected by a road and the new state of a road. $ z=1 $ indicates that the road between cities $ x $ and $ y $ should be repaired and $ z=0 $ means that road should be blown up.

You may output roads in any order. Each affected road should appear exactly once. You may output cities connected by a single road in any order. If you output a road, it's original state should be different from $ z $ .

After performing all operations accroding to your plan, there should remain working only roads lying on some certain shortest past between city $ 1 $ and $ n $ .

If there are multiple optimal answers output any.

## 说明/提示

In the first test the only path is $ 1-2 $

In the second test the only shortest path is $ 1-3-4 $

In the third test there are multiple shortest paths but the optimal is $ 1-4-6-8 $

## 样例 #1

### 输入

```
2 1
1 2 0

```

### 输出

```
1
1 2 1

```

## 样例 #2

### 输入

```
4 4
1 2 1
1 3 0
2 3 1
3 4 1

```

### 输出

```
3
1 2 0
1 3 1
2 3 0

```

## 样例 #3

### 输入

```
8 9
1 2 0
8 3 0
2 3 1
1 4 1
8 7 0
1 5 1
4 6 1
5 7 0
6 8 0

```

### 输出

```
3
2 3 0
1 5 0
6 8 1

```



---

---
title: "Journey"
layout: "post"
diff: 提高+/省选-
pid: CF57D
tag: ['枚举', '最短路', '前缀和']
---

# Journey

## 题目描述

兔子Stewie发现了一个新的平行宇宙。这个宇宙是二维的且是矩形网格，包含n行，m列。它是非常小的：网格的一个格子只能包含一个粒子。这个宇宙中的每一个粒子要么是静态的，要么是动态的。每个静态粒子总是保持在同一位置。由于莫名其妙的引力定律，平行宇宙中没有两个静态粒子存在于一行或一列中，也不可能存在于其它静态粒子的左上，左下，右上，右下的4个格子中。一个动态粒子出现在一个随机的空格子中，随机地选择目的格子（目的格子可能与起始格子重合，请看样例），并沿着最短的路径移动到没有被静态粒子占据的目标格子中。所有空格子被选择为路径的开始或结束的概率是相同的。到达目标格子后，粒子消失。在同一个时刻只允许有一个动态粒子存在。每个移动过程中，这个粒子必须从一个格子移动到相邻的一个格子，这个过程需要一个银河秒。Stewie对宇宙中一个粒子的平均寿命感兴趣。


------------

## 输入格式

第一行包含两个用空格分开的整数：n，m（2＜n，m <＝1000），表示宇宙的大小。后面有n行，每行m个符号，每一个符号描述了没有动态粒子的宇宙——如果第i行第 j个符号等于‘X’，表示有一个静态粒子，如果它是空的，则等于“.”。保证所描述的宇宙满足上述静态粒子排布规则

## 输出格式

输出有一行，一个数，表示粒子的平均寿命。
结果如与正确答案有10的-6次方以内误差，即为正确。

## 样例 #1

### 输入

```
2 2
..
.X

```

### 输出

```
0.888888888889

```

## 样例 #2

### 输入

```
3 3
...
.X.
...

```

### 输出

```
2.000000000000

```



---

---
title: "Complete The Graph"
layout: "post"
diff: 提高+/省选-
pid: CF715B
tag: ['枚举', '最短路']
---

# Complete The Graph

## 题目描述

ZS the Coder has drawn an undirected graph of $ n $ vertices numbered from $ 0 $ to $ n-1 $ and $ m $ edges between them. Each edge of the graph is weighted, each weight is a positive integer.

The next day, ZS the Coder realized that some of the weights were erased! So he wants to reassign positive integer weight to each of the edges which weights were erased, so that the length of the shortest path between vertices $ s $ and $ t $ in the resulting graph is exactly $ L $ . Can you help him?

## 输入格式

The first line contains five integers $ n,m,L,s,t $ ( $ 2<=n<=1000,1<=m<=10000,1<=L<=10^{9},0<=s,t<=n-1,s≠t $ ) — the number of vertices, number of edges, the desired length of shortest path, starting vertex and ending vertex respectively.

Then, $ m $ lines describing the edges of the graph follow. $ i $ -th of them contains three integers, $ u_{i},v_{i},w_{i} $ ( $ 0<=u_{i},v_{i}<=n-1,u_{i}≠v_{i},0<=w_{i}<=10^{9} $ ). $ u_{i} $ and $ v_{i} $ denote the endpoints of the edge and $ w_{i} $ denotes its weight. If $ w_{i} $ is equal to $ 0 $ then the weight of the corresponding edge was erased.

It is guaranteed that there is at most one edge between any pair of vertices.

## 输出格式

Print "NO" (without quotes) in the only line if it's not possible to assign the weights in a required way.

Otherwise, print "YES" in the first line. Next $ m $ lines should contain the edges of the resulting graph, with weights assigned to edges which weights were erased. $ i $ -th of them should contain three integers $ u_{i} $ , $ v_{i} $ and $ w_{i} $ , denoting an edge between vertices $ u_{i} $ and $ v_{i} $ of weight $ w_{i} $ . The edges of the new graph must coincide with the ones in the graph from the input. The weights that were not erased must remain unchanged whereas the new weights can be any positive integer not exceeding $ 10^{18} $ .

The order of the edges in the output doesn't matter. The length of the shortest path between $ s $ and $ t $ must be equal to $ L $ .

If there are multiple solutions, print any of them.

## 说明/提示

Here's how the graph in the first sample case looks like :

 ![](https://cdn.luogu.com.cn/upload/vjudge_pic/CF715B/c442fd279761bfa74ef367b518cede1e1fa97983.png)In the first sample case, there is only one missing edge weight. Placing the weight of $ 8 $ gives a shortest path from $ 0 $ to $ 4 $ of length $ 13 $ .

In the second sample case, there is only a single edge. Clearly, the only way is to replace the missing weight with $ 123456789 $ .

In the last sample case, there is no weights to assign but the length of the shortest path doesn't match the required value, so the answer is "NO".

## 样例 #1

### 输入

```
5 5 13 0 4
0 1 5
2 1 2
3 2 3
1 4 0
4 3 4

```

### 输出

```
YES
0 1 5
2 1 2
3 2 3
1 4 8
4 3 4

```

## 样例 #2

### 输入

```
2 1 123456789 0 1
0 1 0

```

### 输出

```
YES
0 1 123456789

```

## 样例 #3

### 输入

```
2 1 999999999 1 0
0 1 1000000000

```

### 输出

```
NO

```



---

---
title: "Buy a Ticket"
layout: "post"
diff: 提高+/省选-
pid: CF938D
tag: ['图论建模', '最短路']
---

# Buy a Ticket

## 题目描述

Musicians of a popular band "Flayer" have announced that they are going to "make their exit" with a world tour. Of course, they will visit Berland as well.

There are $ n $ cities in Berland. People can travel between cities using two-directional train routes; there are exactly $ m $ routes, $ i $ -th route can be used to go from city $ v_{i} $ to city $ u_{i} $ (and from $ u_{i} $ to $ v_{i} $ ), and it costs $ w_{i} $ coins to use this route.

Each city will be visited by "Flayer", and the cost of the concert ticket in $ i $ -th city is $ a_{i} $ coins.

You have friends in every city of Berland, and they, knowing about your programming skills, asked you to calculate the minimum possible number of coins they have to pay to visit the concert. For every city $ i $ you have to compute the minimum number of coins a person from city $ i $ has to spend to travel to some city $ j $ (or possibly stay in city $ i $ ), attend a concert there, and return to city $ i $ (if $ j≠i $ ).

Formally, for every ![](https://cdn.luogu.com.cn/upload/vjudge_pic/CF938D/035d166bda223ecd5c31eb614a76bdcc9b8fe8c4.png) you have to calculate ![](https://cdn.luogu.com.cn/upload/vjudge_pic/CF938D/f2e29a8bb6e05026242d6e3afeeabb7241997635.png), where $ d(i,j) $ is the minimum number of coins you have to spend to travel from city $ i $ to city $ j $ . If there is no way to reach city $ j $ from city $ i $ , then we consider $ d(i,j) $ to be infinitely large.

## 输入格式

The first line contains two integers $ n $ and $ m $ ( $ 2<=n<=2·10^{5} $ , $ 1<=m<=2·10^{5} $ ).

Then $ m $ lines follow, $ i $ -th contains three integers $ v_{i} $ , $ u_{i} $ and $ w_{i} $ ( $ 1<=v_{i},u_{i}<=n,v_{i}≠u_{i} $ , $ 1<=w_{i}<=10^{12} $ ) denoting $ i $ -th train route. There are no multiple train routes connecting the same pair of cities, that is, for each $ (v,u) $ neither extra $ (v,u) $ nor $ (u,v) $ present in input.

The next line contains $ n $ integers $ a_{1},a_{2},...\ a_{k} $ ( $ 1<=a_{i}<=10^{12} $ ) — price to attend the concert in $ i $ -th city.

## 输出格式

Print $ n $ integers. $ i $ -th of them must be equal to the minimum number of coins a person from city $ i $ has to spend to travel to some city $ j $ (or possibly stay in city $ i $ ), attend a concert there, and return to city $ i $ (if $ j≠i $ ).

## 样例 #1

### 输入

```
4 2
1 2 4
2 3 7
6 20 1 25

```

### 输出

```
6 14 1 25 

```

## 样例 #2

### 输入

```
3 3
1 2 1
2 3 1
1 3 1
30 10 20

```

### 输出

```
12 10 12 

```



---

---
title: "Volleyball"
layout: "post"
diff: 提高+/省选-
pid: CF95C
tag: ['优先队列', '最短路', '队列']
---

# Volleyball

## 题目描述

Petya loves volleyball very much. One day he was running late for a volleyball match. Petya hasn't bought his own car yet, that's why he had to take a taxi. The city has $ n $ junctions, some of which are connected by two-way roads. The length of each road is defined by some positive integer number of meters; the roads can have different lengths.

Initially each junction has exactly one taxi standing there. The taxi driver from the $ i $ -th junction agrees to drive Petya (perhaps through several intermediate junctions) to some other junction if the travel distance is not more than $ t_{i} $ meters. Also, the cost of the ride doesn't depend on the distance and is equal to $ c_{i} $ bourles. Taxis can't stop in the middle of a road. Each taxi can be used no more than once. Petya can catch taxi only in the junction, where it stands initially.

At the moment Petya is located on the junction $ x $ and the volleyball stadium is on the junction $ y $ . Determine the minimum amount of money Petya will need to drive to the stadium.

## 输入格式

The first line contains two integers $ n $ and $ m $ ( $ 1<=n<=1000,0<=m<=1000) $ . They are the number of junctions and roads in the city correspondingly. The junctions are numbered from $ 1 $ to $ n $ , inclusive. The next line contains two integers $ x $ and $ y $ ( $ 1<=x,y<=n $ ). They are the numbers of the initial and final junctions correspondingly. Next $ m $ lines contain the roads' description. Each road is described by a group of three integers $ u_{i} $ , $ v_{i} $ , $ w_{i} $ ( $ 1<=u_{i},v_{i}<=n,1<=w_{i}<=10^{9} $ ) — they are the numbers of the junctions connected by the road and the length of the road, correspondingly. The next $ n $ lines contain $ n $ pairs of integers $ t_{i} $ and $ c_{i} $ ( $ 1<=t_{i},c_{i}<=10^{9} $ ), which describe the taxi driver that waits at the $ i $ -th junction — the maximum distance he can drive and the drive's cost. The road can't connect the junction with itself, but between a pair of junctions there can be more than one road. All consecutive numbers in each line are separated by exactly one space character.

## 输出格式

If taxis can't drive Petya to the destination point, print "-1" (without the quotes). Otherwise, print the drive's minimum cost.

Please do not use the %lld specificator to read or write 64-bit integers in С++. It is preferred to use cin, cout streams or the %I64d specificator.

## 说明/提示

An optimal way — ride from the junction 1 to 2 (via junction 4), then from 2 to 3. It costs 7+2=9 bourles.

## 样例 #1

### 输入

```
4 4
1 3
1 2 3
1 4 1
2 4 1
2 3 5
2 7
7 2
1 2
7 7

```

### 输出

```
9

```



---

