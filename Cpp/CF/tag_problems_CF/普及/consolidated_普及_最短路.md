---
title: "Dijkstra?"
layout: "post"
diff: 普及/提高-
pid: CF20C
tag: ['最短路']
---

# Dijkstra?

## 题目描述

给定一张无向有权图，请输出任意一条从 $1$ 到 $n$ 的最短路径。

## 输入格式

第一行两个整数 $n, m$（$2 \le n \le 10 ^ 5, 0 \le m \le 10 ^ 5$），表示图的点数和边数。

接下来 $m$ 行每行三个整数 $u, v, w$，表示图中有一条从 $u$ 到 $v$ 的边权为 $w$ 的无向边。

## 输出格式

一个可行的路径，如果不存在这种路径输出 `-1`。

## 样例 #1

### 输入

```
5 6
1 2 2
2 5 5
2 3 4
1 4 1
4 3 3
3 5 1

```

### 输出

```
1 4 3 5 
```

## 样例 #2

### 输入

```
5 6
1 2 2
2 5 5
2 3 4
1 4 1
4 3 3
3 5 1

```

### 输出

```
1 4 3 5 
```



---

---
title: "Planets"
layout: "post"
diff: 普及/提高-
pid: CF229B
tag: ['最短路']
---

# Planets

## 题目描述

## 题面
在宇宙里有 $n$  个星球，分别编号为 $1,2,...,n$  。Jack现在在 $1$  号星球上，他要去 $n$  号星球。已知一些星球之间有双向的传送通道，Jack可以通过这些传送通道移动。每次传送需要一些时间，在不同的星球之间传送也可能需要不同时间。

当有其他人在使用这个星球的传送通道时，Jack无法离开这个星球。比如，如果有人在 $t$  时刻使用通道，那Jack只能在 $t+1$  时刻离开（如果t+1时刻没有人在使用通道）。

现在，Jack想请你计算他最早可以在哪个时刻到达 $n$  号星球。Jack在0时刻出发。

## 输入格式

输入的第一行包括两个由空格分割的整数，星球数 $n$  ( $2≤n≤10^5$  )和传送通道数 $m$  ( $0≤m≤10^5$  )。

接下来的 $m$  行，每行包括了3个整数 $a$  , $b$  和 $c$  ( $1≤a,b≤n, a≠b, 1≤c≤10^4$  )，表示星球 $a$  与星球 $b$  之间有一条耗时为 $c$  的传送通道。

接下来的 $n$  行，第 $i$  行表示第 $i$  个星球的传送通道的使用情况。每行首先是一个整数 $k_i$  ，表示一共有 $k_i$  个时刻这个星球的传送通道在被使用，接下来 $k_i$  个整数 $t_{ij}$  ( $0≤t_{ij}≤10^9$  )表示在 $t_{ij}$  时刻 $i$  星球的传送通道正被他人使用。所有 $k_i$  的和不超过 $10^5$  。 $t_{ij}$ 按照升序排列

## 输出格式

输出一行，一个整数，表示Jack可以最早在哪个时刻到达 $n$  号星球。如果他无法通过这些传送通道到达，输出 -1 。

## 输入输出样例
略

## 样例解释
对于样例1，Jack有3种方案：
1. 直接从1->4，在时刻8到达星球4。
2. 先从1->3，在时刻3到达，但是此时（时刻3和时刻4）有其他人在使用通道，他只能在时刻5出发，在时刻8到达星球4。
3. 先从1->2，在时刻2到达，再从2->4，在时刻7到达。
所以他最早可以在时刻7到达。

对于样例2，Jack不能通过传送从星球1前往星球3。

感谢@星烁晶熠辉 提供的翻译和@Styx 提供的建议

## 样例 #1

### 输入

```
4 6
1 2 2
1 3 3
1 4 8
2 3 4
2 4 5
3 4 3
0
1 3
2 3 4
0

```

### 输出

```
7

```

## 样例 #2

### 输入

```
3 1
1 2 3
0
1 3
0

```

### 输出

```
-1

```



---

---
title: "The Two Routes"
layout: "post"
diff: 普及/提高-
pid: CF601A
tag: ['最短路']
---

# The Two Routes

## 题目描述

有个地方有一些城镇，城镇与城镇间有铁路或公路相连，如果有铁路相连，就不会有公路相连，没有铁路连接的城镇就会有公路相连。给你 $n$ 个城镇， $m$ 条铁路线，问同时从城镇1出发，分别坐火车和坐汽车到达城镇n，求两者都到达的时候最少的用时。其中火车和汽车不能同时到达中间点。

## 输入格式

第一行两个整数 $n$ 和 $m$   $(0<=m<=n×(n-1)/2$ 
表示城镇的数量和铁路的数量。
接下来 $m$ 行每行两个整数 $u$ 和 $v$ ，表示城镇 $u$ 到 $v$ 有铁路相连。

## 输出格式

一个整数，表示两种交通工具都到达终点的最少用时，如果**其中有一种交通工具不能到达或都不能到达终点**，输出 $-1$ 。

相邻两地乘火车或汽车的用时都是1

感谢@_UKE自动机_ 提供的翻译

## 样例 #1

### 输入

```
4 2
1 3
3 4

```

### 输出

```
2

```

## 样例 #2

### 输入

```
4 6
1 2
1 3
1 4
2 3
2 4
3 4

```

### 输出

```
-1

```

## 样例 #3

### 输入

```
5 5
4 2
3 5
4 5
5 1
1 2

```

### 输出

```
3

```



---

---
title: "Jamie and Interesting Graph"
layout: "post"
diff: 普及/提高-
pid: CF916C
tag: ['最短路', '生成树', '素数判断,质数,筛法']
---

# Jamie and Interesting Graph

## 题目描述

Jamie has recently found undirected weighted graphs with the following properties very interesting:

- The graph is connected and contains exactly $ n $ vertices and $ m $ edges.
- All edge weights are integers and are in range $ [1,10^{9}] $ inclusive.
- The length of shortest path from $ 1 $ to $ n $ is a prime number.
- The sum of edges' weights in the minimum spanning tree (MST) of the graph is a prime number.
- The graph contains no loops or multi-edges.

If you are not familiar with some terms from the statement you can find definitions of them in notes section.

Help Jamie construct any graph with given number of vertices and edges that is interesting!



## 输入格式

First line of input contains 2 integers $ n $ , $ m $ ![](https://cdn.luogu.com.cn/upload/vjudge_pic/CF916C/2d5925c368d31be87894bfaeb81a5671f57414c2.png) — the required number of vertices and edges.

## 输出格式

In the first line output 2 integers $ sp $ , $ mstw $ $ (1<=sp,mstw<=10^{14}) $ — the length of the shortest path and the sum of edges' weights in the minimum spanning tree.

In the next $ m $ lines output the edges of the graph. In each line output 3 integers $ u $ , $ v $ , $ w $ $ (1<=u,v<=n,1<=w<=10^{9}) $ describing the edge connecting $ u $ and $ v $ and having weight $ w $ .

## 说明/提示

The graph of sample 1: ![](https://cdn.luogu.com.cn/upload/vjudge_pic/CF916C/03021596e10dc8211f3fe958e7629dc3a97d37e7.png) Shortest path sequence: $ {1,2,3,4} $ . MST edges are marked with an asterisk (\*).

Definition of terms used in the problem statement:

A shortest path in an undirected graph is a sequence of vertices $ (v_{1},v_{2},...\ ,v_{k}) $ such that $ v_{i} $ is adjacent to $ v_{i+1} $ $ 1<=i<k $ and the sum of weight ![](https://cdn.luogu.com.cn/upload/vjudge_pic/CF916C/df0334815830e4f0c8788e37a58a6247ba52744b.png) is minimized where $ w(i,j) $ is the edge weight between $ i $ and $ j $ . ([https://en.wikipedia.org/wiki/Shortest\_path\_problem](https://en.wikipedia.org/wiki/Shortest_path_problem))

A prime number is a natural number greater than 1 that has no positive divisors other than 1 and itself. ([https://en.wikipedia.org/wiki/Prime\_number](https://en.wikipedia.org/wiki/Prime_number))

A minimum spanning tree (MST) is a subset of the edges of a connected, edge-weighted undirected graph that connects all the vertices together, without any cycles and with the minimum possible total edge weight. ([https://en.wikipedia.org/wiki/Minimum\_spanning\_tree](https://en.wikipedia.org/wiki/Minimum_spanning_tree))

[https://en.wikipedia.org/wiki/Multiple\_edges](https://en.wikipedia.org/wiki/Multiple_edges)

## 样例 #1

### 输入

```
4 4

```

### 输出

```
7 7
1 2 3
2 3 2
3 4 2
2 4 4

```

## 样例 #2

### 输入

```
5 4

```

### 输出

```
7 13
1 2 2
1 3 4
1 4 3
4 5 4

```



---

---
title: "Fair"
layout: "post"
diff: 普及/提高-
pid: CF986A
tag: ['广度优先搜索 BFS', '最短路', '队列']
---

# Fair

## 题目描述

一些公司将在Byteland举办商品交易会（or博览会？）。在Byteland有 $n$ 个城市，城市间有 $m$ 条双向道路。当然，城镇之间两两连通。
Byteland生产的货物有 $k$ 种类型，每个城镇只生产一种。
为了举办商品交易会，你必须至少带来 $s$ 种不同类型的商品。将货物从 $u$ 镇带到城镇 $v$ 将花费 $d(u,v)$ 的费用，其中 $d(u,v)$ 是从 $u$ 到 $v$ 的最短路径的长度。
路径的长度是这个路径中的道路的数量。              
组织者将支付所有的运输费用，但他们可以选择从哪些城镇带来货物。现在他们想计算每个城镇举办商品交易会的最小费用。

## 输入格式

第一行 $4$ 个整数$n$ , $m$ , $k$ , $s$ ($1\le n\le 10^5 $,$1\le m\le 10^5 $,$1\le s\le k\le min(n,100)$ )——分别表示 城镇数，道路数，生产的货物数，举办商品交易会所需的货物数。

接下来一行$n$个整数$a_1,a_2,...,a_n(1\le a_i \le k)$ , $a_i$是第$i$个城镇生产的商品种类.保证$1$和$k$之间的所有整数在整数$a_i$中至少出现一次。 

接下来$m$行表示道路。每行两个整数 $u$ $v$ $(1 \le u$,$v \le n, u\ne v)$ 表示  $u$ $v$ 之间有一条双向道路。保证每两个城镇之间只有一条路。并且城镇之间两两连通。

## 输出格式

输出$n$个数。第$i$个数表示在第$i$个城镇举办商品交易会所需花在运输上的最小费用。数与数之间用空格分开。

## 样例 #1

### 输入

```
5 5 4 3
1 2 4 3 2
1 2
2 3
3 4
4 1
4 5

```

### 输出

```
2 2 2 2 3 

```

## 样例 #2

### 输入

```
7 6 3 2
1 2 3 3 2 2 1
1 2
2 3
3 4
2 5
5 6
6 7

```

### 输出

```
1 1 1 2 2 1 1 

```



---

