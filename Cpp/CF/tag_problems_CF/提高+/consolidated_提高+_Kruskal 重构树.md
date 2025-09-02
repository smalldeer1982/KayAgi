---
title: "Labyrinth"
layout: "post"
diff: 提高+/省选-
pid: CF1578L
tag: ['Kruskal 重构树', '树形 DP']
---

# Labyrinth

## 题目描述

In a dream, Lucy found herself in a labyrinth. This labyrinth consists of $ n $ rooms, connected by $ m $ passages ( $ i $ -th passage is $ w_i $ cm wide). Each passage can be traversed in both directions. It is guaranteed that it is possible to get from any room to any other room. But this is not an ordinary labyrinth — each room in this labyrinth contains a magic candy. When Lucy eats this magic candy, she is getting wider. Specifically, if she eats candy from room $ i $ she becomes wider by $ c_i $ cm. Note that she is not obliged to eat candy the first time she visits a particular room, but she can eat each candy only once.

Unfortunately, passages in this labyrinth are pretty narrow, so after eating some candy, Lucy can get too wide and will not be able to traverse them — her width should not be greater than the width of the corresponding passage.

Lucy starts her journey in a room number $ 1 $ . She wants to eat all the candies. After that, she will just wake up, so she does not have to be able to return to the room $ 1 $ . She realizes that with her current width, she may not be able to do so, so she plans a workout before embarking on her journey. Lucy wants to know if it is possible to start with some positive width and still eat all the candies. If yes, then what is the maximal starting width with which it is possible.

## 输入格式

The first line contains two integers, $ n $ and $ m $ ( $ 2 \le n \le 10^5; n - 1 \le m \le 10^5 $ ) — the number of rooms and the number of passages.

The second line contains $ n $ integers — $ c_i $ ( $ 1 \le c_i \le 10^9 $ ).

Next $ m $ lines contain three integers each — $ a_i $ , $ b_i $ and $ w_i $ ( $ 1 \le a_i, b_i \le n; a_i \ne b_i; 1 \le w_i \le 10^9 $ ) describing passage that connects rooms $ a_i $ and $ b_i $ and is $ w_i $ cm wide. It is guaranteed that the resulting labyrinth is connected and there is at most one passage between any pair of rooms.

## 输出格式

If it is possible to eat all the candies, output the maximal possible starting width, otherwise output $ -1 $ .

## 样例 #1

### 输入

```
3 3
1 2 3
1 2 4
1 3 4
2 3 6
```

### 输出

```
3
```

## 样例 #2

### 输入

```
2 1
1 1
1 2 1
```

### 输出

```
-1
```



---

---
title: "Qpwoeirut and Vertices"
layout: "post"
diff: 提高+/省选-
pid: CF1706E
tag: ['线段树', 'Kruskal 重构树', 'ST 表', '整体二分']
---

# Qpwoeirut and Vertices

## 题目描述

You are given a connected undirected graph with $ n $ vertices and $ m $ edges. Vertices of the graph are numbered by integers from $ 1 $ to $ n $ and edges of the graph are numbered by integers from $ 1 $ to $ m $ .

Your task is to answer $ q $ queries, each consisting of two integers $ l $ and $ r $ . The answer to each query is the smallest non-negative integer $ k $ such that the following condition holds:

- For all pairs of integers $ (a, b) $ such that $ l\le a\le b\le r $ , vertices $ a $ and $ b $ are reachable from one another using only the first $ k $ edges (that is, edges $ 1, 2, \ldots, k $ ).

## 输入格式

The first line contains a single integer $ t $ ( $ 1\le t\le 1000 $ ) — the number of test cases.

The first line of each test case contains three integers $ n $ , $ m $ , and $ q $ ( $ 2\le n\le 10^5 $ , $ 1\le m, q\le 2\cdot 10^5 $ ) — the number of vertices, edges, and queries respectively.

Each of the next $ m $ lines contains two integers $ u_i $ and $ v_i $ ( $ 1\le u_i, v_i\le n $ ) — ends of the $ i $ -th edge.

It is guaranteed that the graph is connected and there are no multiple edges or self-loops.

Each of the next $ q $ lines contains two integers $ l $ and $ r $ ( $ 1\le l\le r\le n $ ) — descriptions of the queries.

It is guaranteed that that the sum of $ n $ over all test cases does not exceed $ 10^5 $ , the sum of $ m $ over all test cases does not exceed $ 2\cdot 10^5 $ , and the sum of $ q $ over all test cases does not exceed $ 2\cdot 10^5 $ .

## 输出格式

For each test case, print $ q $ integers — the answers to the queries.

## 说明/提示

![](https://cdn.luogu.com.cn/upload/vjudge_pic/CF1706E/8251767c792df96adbc7d8ce1ae896aca10bb309.png)Graph from the first test case. The integer near the edge is its number.In the first test case, the graph contains $ 2 $ vertices and a single edge connecting vertices $ 1 $ and $ 2 $ .

In the first query, $ l=1 $ and $ r=1 $ . It is possible to reach any vertex from itself, so the answer to this query is $ 0 $ .

In the second query, $ l=1 $ and $ r=2 $ . Vertices $ 1 $ and $ 2 $ are reachable from one another using only the first edge, through the path $ 1 \longleftrightarrow 2 $ . It is impossible to reach vertex $ 2 $ from vertex $ 1 $ using only the first $ 0 $ edges. So, the answer to this query is $ 1 $ .

 ![](https://cdn.luogu.com.cn/upload/vjudge_pic/CF1706E/af65cd675bd4523d08062174925e59fd8900ee43.png)Graph from the second test case. The integer near the edge is its number.In the second test case, the graph contains $ 5 $ vertices and $ 5 $ edges.

In the first query, $ l=1 $ and $ r=4 $ . It is enough to use the first $ 3 $ edges to satisfy the condition from the statement:

- Vertices $ 1 $ and $ 2 $ are reachable from one another through the path $ 1 \longleftrightarrow 2 $ (edge $ 1 $ ).
- Vertices $ 1 $ and $ 3 $ are reachable from one another through the path $ 1 \longleftrightarrow 3 $ (edge $ 2 $ ).
- Vertices $ 1 $ and $ 4 $ are reachable from one another through the path $ 1 \longleftrightarrow 2 \longleftrightarrow 4 $ (edges $ 1 $ and $ 3 $ ).
- Vertices $ 2 $ and $ 3 $ are reachable from one another through the path $ 2 \longleftrightarrow 1 \longleftrightarrow 3 $ (edges $ 1 $ and $ 2 $ ).
- Vertices $ 2 $ and $ 4 $ are reachable from one another through the path $ 2 \longleftrightarrow 4 $ (edge $ 3 $ ).
- Vertices $ 3 $ and $ 4 $ are reachable from one another through the path $ 3 \longleftrightarrow 1 \longleftrightarrow 2 \longleftrightarrow 4 $ (edges $ 2 $ , $ 1 $ , and $ 3 $ ).

If we use less than $ 3 $ of the first edges, then the condition won't be satisfied. For example, it is impossible to reach vertex $ 4 $ from vertex $ 1 $ using only the first $ 2 $ edges. So, the answer to this query is $ 3 $ .

In the second query, $ l=3 $ and $ r=4 $ . Vertices $ 3 $ and $ 4 $ are reachable from one another through the path $ 3 \longleftrightarrow 1 \longleftrightarrow 2 \longleftrightarrow 4 $ (edges $ 2 $ , $ 1 $ , and $ 3 $ ). If we use any fewer of the first edges, nodes $ 3 $ and $ 4 $ will not be reachable from one another.

## 样例 #1

### 输入

```
3
2 1 2
1 2
1 1
1 2
5 5 5
1 2
1 3
2 4
3 4
3 5
1 4
3 4
2 2
2 5
3 5
3 2 1
1 3
2 3
1 3
```

### 输出

```
0 1 
3 3 0 5 5 
2
```



---

---
title: "Digital Village (Hard Version)"
layout: "post"
diff: 提高+/省选-
pid: CF2021E2
tag: ['动态规划 DP', 'Kruskal 重构树']
---

# Digital Village (Hard Version)

## 题目描述

**这是问题的困难版本。在三个版本中，$n$ 和 $m$ 的约束条件不同。只有所有版本的问题都解决了，你才能进行 hack。**

Pak Chanek 正在为 Khuntien 村设置互联网连接。这个村庄可以表示为一个连通的简单图，其中有 $n$ 栋房屋和 $m$ 条互联网电缆，每条电缆连接房屋 $u_i$ 和房屋 $v_i$，并且具有延迟 $w_i$。

有 $p$ 栋房屋需要互联网。Pak Chanek 最多可以在 $k$ 栋房屋中安装服务器。需要互联网的房屋将连接到其中一个服务器。但是，由于每条电缆都有其延迟，对于需要互联网的房屋 $s_i$，其经历的延迟将是该房屋与其连接的服务器之间电缆的**最大**延迟。

对于每个 $k = 1,2,\ldots,n$，帮助 Pak Chanek 确定所有需要互联网的房屋所能达到的最小**总**延迟。

## 输入格式

每个测试包含多个测试用例。第一行包含测试用例的数量 $t$ ( $1 \le t \le 2000$ )。对每个测试用例说明如下：

每个测试用例的第一行包含三个整数 $n$ , $m$ , $p$ ( $2 \le n \le 5000$ ; $n-1 \le m \le 5000$ ; $1 \le p \le n$ )，表示房屋数量、电缆数量和需要网络的房屋数量。

每个测试用例的第二行包含 $p$ 个整数 $s_1, s_2, \ldots, s_p$ ( $1 \le s_i \le n$ )，表示需要上网的房屋。保证 $s$ 中的所有元素都是不同的。

每个测试用例下 $m$ 行每行包含三个整数 $u_i$、$v_i$ 和 $w_i$（$1 \le u_i , v_i \le n$ ; $1 \le w_i \le 10^9$）表示一条连接房屋 $u_i$ 和房屋 $v_i$ 的网线，延迟为 $w_i$。保证给定的边构成一个连通的简单图。

保证 $n$ 和 $m$ 之和不超过 $5000$。

## 输出格式

对于每个测试用例，输出 $n$ 个整数：对**每个**$k = 1,2,\ldots,n$，计算所有需要上网的房屋所能达到的最小总延迟。

**样例解释**

第一个测试用例中，$k=3$ 的一个的最佳解决方案是在顶点 $2$ 、 $6$ 和 $8$ 安装服务器，并获得以下延迟：

- $\text{latency}(2) = 0$
- $\text{latency}(5) = \max(3, 5) = 5$
- $\text{latency}(6) = 0$
- $\text{latency}(8) = 0$
- $\text{latency}(9) = \max(2, 4) = 4$

因此总延迟为 $0+5+0+0+4=9$ 。

## 样例 #1

### 输入

```
2
9 8 5
2 5 6 8 9
1 2 1
1 3 2
3 4 10
4 5 3
4 6 5
1 7 10
7 8 4
7 9 2
3 3 2
3 1
1 2 1
2 3 3
1 3 2
```

### 输出

```
34 19 9 4 0 0 0 0 0
2 0 0
```



---

