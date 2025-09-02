---
title: "Mobile Phone Network"
layout: "post"
diff: 省选/NOI-
pid: CF1023F
tag: ['生成树', '树链剖分']
---

# Mobile Phone Network

## 题目描述

You are managing a mobile phone network, and want to offer competitive prices to connect a network.

The network has $ n $ nodes.

Your competitor has already offered some connections between some nodes, with some fixed prices. These connections are bidirectional. There are initially $ m $ connections the competitor is offering. The $ i $ -th connection your competitor is offering will connect nodes $ fa_i $ and $ fb_i $ and costs $ fw_i $ .

You have a list of $ k $ connections that you want to offer. It is guaranteed that this set of connection does not form any cycle. The $ j $ -th of these connections will connect nodes $ ga_j $ and $ gb_j $ . These connections are also bidirectional. The cost of these connections have not been decided yet.

You can set the prices of these connections to any arbitrary integer value. These prices are set independently for each connection. After setting the prices, the customer will choose such $ n - 1 $ connections that all nodes are connected in a single network and the total cost of chosen connections is minimum possible. If there are multiple ways to choose such networks, the customer will choose an arbitrary one that also maximizes the number of your connections in it.

You want to set prices in such a way such that all your $ k $ connections are chosen by the customer, and the sum of prices of your connections is maximized.

Print the maximum profit you can achieve, or $ -1 $ if it is unbounded.

## 输入格式

The first line of input will contain three integers $ n $ , $ k $ and $ m $ ( $ 1 \leq n, k, m \leq 5 \cdot 10^5, k \leq n-1 $ ), the number of nodes, the number of your connections, and the number of competitor connections, respectively.

The next $ k $ lines contain two integers $ ga_i $ and $ gb_i $ ( $ 1 \leq ga_i, gb_i \leq n $ , $ ga_i \not= gb_i $ ), representing one of your connections between nodes $ ga_i $ and $ gb_i $ . Your set of connections is guaranteed to be acyclic.

The next $ m $ lines contain three integers each, $ fa_i $ , $ fb_i $ and $ fw_i $ ( $ 1 \leq fa_i, fb_i \leq n $ , $ fa_i \not= fb_i $ , $ 1 \leq fw_i \leq 10^9 $ ), denoting one of your competitor's connections between nodes $ fa_i $ and $ fb_i $ with cost $ fw_i $ . None of these connections connects a node to itself, and no pair of these connections connect the same pair of nodes. In addition, these connections are given by non-decreasing order of cost (that is, $ fw_{i-1} \leq fw_i $ for all valid $ i $ ).

Note that there may be some connections that appear in both your set and your competitor's set (though no connection will appear twice in one of this sets).

It is guaranteed that the union of all of your connections and your competitor's connections form a connected network.

## 输出格式

Print a single integer, the maximum possible profit you can achieve if you set the prices on your connections appropriately. If the profit is unbounded, print $ -1 $ .

## 说明/提示

In the first sample, it's optimal to give connection $ 1-3 $ cost $ 3 $ , connection $ 1-2 $ cost $ 3 $ , and connection $ 3-4 $ cost $ 8 $ . In this case, the cheapest connected network has cost $ 14 $ , and the customer will choose one that chooses all of your connections.

In the second sample, as long as your first connection costs $ 30 $ or less, the customer chooses both your connections no matter what is the cost of the second connection, so you can get unbounded profit in this case.

## 样例 #1

### 输入

```
4 3 6
1 2
3 4
1 3
2 3 3
3 1 4
1 2 4
4 2 8
4 3 8
4 1 10

```

### 输出

```
14

```

## 样例 #2

### 输入

```
3 2 1
1 2
2 3
1 2 30

```

### 输出

```
-1

```

## 样例 #3

### 输入

```
4 3 3
1 2
1 3
1 4
4 1 1000000000
4 2 1000000000
4 3 1000000000

```

### 输出

```
3000000000

```



---

---
title: "Power Tree"
layout: "post"
diff: 省选/NOI-
pid: CF1120D
tag: ['生成树']
---

# Power Tree

## 题目描述

You are given a rooted tree with $ n $ vertices, the root of the tree is the vertex $ 1 $ . Each vertex has some non-negative price. A leaf of the tree is a non-root vertex that has degree $ 1 $ .

Arkady and Vasily play a strange game on the tree. The game consists of three stages. On the first stage Arkady buys some non-empty set of vertices of the tree. On the second stage Vasily puts some integers into all leaves of the tree. On the third stage Arkady can perform several (possibly none) operations of the following kind: choose some vertex $ v $ he bought on the first stage and some integer $ x $ , and then add $ x $ to all integers in the leaves in the subtree of $ v $ . The integer $ x $ can be positive, negative of zero.

A leaf $ a $ is in the subtree of a vertex $ b $ if and only if the simple path between $ a $ and the root goes through $ b $ .

Arkady's task is to make all integers in the leaves equal to zero. What is the minimum total cost $ s $ he has to pay on the first stage to guarantee his own win independently of the integers Vasily puts on the second stage? Also, we ask you to find all such vertices that there is an optimal (i.e. with cost $ s $ ) set of vertices containing this one such that Arkady can guarantee his own win buying this set on the first stage.

## 输入格式

The first line contains a single integer $ n $ ( $ 2 \le n \le 200\,000 $ ) — the number of vertices in the tree.

The second line contains $ n $ integers $ c_1, c_2, \ldots, c_n $ ( $ 0 \le c_i \le 10^9 $ ), where $ c_i $ is the price of the $ i $ -th vertex.

Each of the next $ n - 1 $ lines contains two integers $ a $ and $ b $ ( $ 1 \le a, b \le n $ ), denoting an edge of the tree.

## 输出格式

In the first line print two integers: the minimum possible cost $ s $ Arkady has to pay to guarantee his own win, and the number of vertices $ k $ that belong to at least one optimal set.

In the second line print $ k $ distinct integers in increasing order the indices of the vertices that belong to at least one optimal set.

## 说明/提示

In the second example all sets of two vertices are optimal. So, each vertex is in at least one optimal set.

## 样例 #1

### 输入

```
5
5 1 3 2 1
1 2
2 3
2 4
1 5

```

### 输出

```
4 3
2 4 5 

```

## 样例 #2

### 输入

```
3
1 1 1
1 2
1 3

```

### 输出

```
2 3
1 2 3 

```



---

---
title: "Clearing Up"
layout: "post"
diff: 省选/NOI-
pid: CF141E
tag: ['并查集', '生成树']
---

# Clearing Up

## 题目描述

After Santa Claus and his assistant Elf delivered all the presents and made all the wishes come true, they returned to the North Pole and found out that it is all covered with snow. Both of them were quite tired and they decided only to remove the snow from the roads connecting huts. The North Pole has $ n $ huts connected with $ m $ roads. One can go along the roads in both directions.

The Elf offered to split: Santa Claus will clear up the wide roads and the Elf will tread out the narrow roads. For each road they decided who will clear it: Santa Claus or the Elf. To minimize the efforts they decided to clear the road so as to fulfill both those conditions:

- between any two huts should exist exactly one simple path along the cleared roads;
- Santa Claus and the Elf should clear the same number of roads.

At this point Santa Claus and his assistant Elf wondered which roads should they clear up?

## 输入格式

The first input line contains two positive integers $ n $ and $ m $ ( $ 1<=n<=10^{3} $ , $ 1<=m<=10^{5} $ ) — the number of huts and the number of roads. Then follow $ m $ lines, each of them contains a road description: the numbers of huts it connects — $ x $ and $ y $ ( $ 1<=x,y<=n $ ) and the person responsible for clearing out this road ("S" — for the Elf or "M" for Santa Claus). It is possible to go on each road in both directions. Note that there can be more than one road between two huts and a road can begin and end in the same hut.

## 输出格式

Print "-1" without the quotes if it is impossible to choose the roads that will be cleared by the given rule. Otherwise print in the first line how many roads should be cleared and in the second line print the numbers of those roads (the roads are numbered from $ 1 $ in the order of occurrence in the input). It is allowed to print the numbers of the roads in any order. Each number should be printed exactly once. As you print the numbers, separate them with spaces.

## 说明/提示

A path is called simple if all huts on it are pairwise different.

## 样例 #1

### 输入

```
1 2
1 1 S
1 1 M

```

### 输出

```
0


```

## 样例 #2

### 输入

```
3 3
1 2 S
1 3 M
2 3 S

```

### 输出

```
2
2 1 

```

## 样例 #3

### 输入

```
5 6
1 1 S
1 2 M
1 3 S
1 4 M
1 5 M
2 2 S

```

### 输出

```
-1

```



---

---
title: "Edges in MST"
layout: "post"
diff: 省选/NOI-
pid: CF160D
tag: ['线段树', '并查集', '生成树', '连通块']
---

# Edges in MST

## 题目描述

You are given a connected weighted undirected graph without any loops and multiple edges.

Let us remind you that a graph's spanning tree is defined as an acyclic connected subgraph of the given graph that includes all of the graph's vertexes. The weight of a tree is defined as the sum of weights of the edges that the given tree contains. The minimum spanning tree (MST) of a graph is defined as the graph's spanning tree having the minimum possible weight. For any connected graph obviously exists the minimum spanning tree, but in the general case, a graph's minimum spanning tree is not unique.

Your task is to determine the following for each edge of the given graph: whether it is either included in any MST, or included at least in one MST, or not included in any MST.

## 输入格式

The first line contains two integers $ n $ and $ m $ ( $ 2<=n<=10^{5} $ , ![](https://cdn.luogu.com.cn/upload/vjudge_pic/CF160D/1841eb9adb257200301ec3daad18abd00c456982.png)) — the number of the graph's vertexes and edges, correspondingly. Then follow $ m $ lines, each of them contains three integers — the description of the graph's edges as " $ a_{i} $ $ b_{i} $ $ w_{i} $ " ( $ 1<=a_{i},b_{i}<=n,1<=w_{i}<=10^{6},a_{i}≠b_{i} $ ), where $ a_{i} $ and $ b_{i} $ are the numbers of vertexes connected by the $ i $ -th edge, $ w_{i} $ is the edge's weight. It is guaranteed that the graph is connected and doesn't contain loops or multiple edges.

## 输出格式

Print $ m $ lines — the answers for all edges. If the $ i $ -th edge is included in any MST, print "any"; if the $ i $ -th edge is included at least in one MST, print "at least one"; if the $ i $ -th edge isn't included in any MST, print "none". Print the answers for the edges in the order in which the edges are specified in the input.

## 说明/提示

In the second sample the MST is unique for the given graph: it contains two first edges.

In the third sample any two edges form the MST for the given graph. That means that each edge is included at least in one MST.

## 样例 #1

### 输入

```
4 5
1 2 101
1 3 100
2 3 2
2 4 2
3 4 1

```

### 输出

```
none
any
at least one
at least one
any

```

## 样例 #2

### 输入

```
3 3
1 2 1
2 3 1
1 3 2

```

### 输出

```
any
any
none

```

## 样例 #3

### 输入

```
3 3
1 2 1
2 3 1
1 3 1

```

### 输出

```
at least one
at least one
at least one

```



---

---
title: "MST with Matching"
layout: "post"
diff: 省选/NOI-
pid: CF1948G
tag: ['生成树']
---

# MST with Matching

## 题目描述

给定一个 $n$ 个点的无向连通图，令 $i, j$ 之间的边权为 $w_{i, j}$，若无边则 $w_{i, j} = 0$。

再给定一个常数 $c$。

你需要找到这个图的一个生成树，使得这个生成树的权值最小。定义一个生成树的权值为以下两者的和：

- 生成树中所有边权的和；
- 生成树上**最大匹配**的大小乘 $c$。

一个无向图 $G = (V, E)$ 的匹配为：一个边集 $E$ 的子集 $E'$，满足对于任意一个点 $i \in V$，不存在两条与 $i$ 相连的边 $(i, a), (i, b)$，使得 $(i, a), (i, b) \in E'$。

## 输入格式

第一行，两个正整数 $n, c$​，表示图的点数与给定常数。

接下来 $n$ 行，第 $i$ 行 $n$ 个非负整数 $w_{i, j}$，表示 $(i, j)$ 的边权 。

## 输出格式

输出一行一个整数，表示最小的生成树权值。

## 说明/提示

对于 $100 \%$ 的数据，保证 $2 \leq n \leq 20, 1 \leq c \leq 10^6, 0 \leq w_{i, j} \leq 10^6$。

保证 $w_{i, j} = w_{j, i}, w_{i, i} = 0$。

Translated by ShiRoZeTsu.

## 样例 #1

### 输入

```
4 10
0 1 8 0
1 0 1 0
8 1 0 2
0 0 2 0
```

### 输出

```
21
```

## 样例 #2

### 输入

```
4 5
0 1 8 0
1 0 1 0
8 1 0 2
0 0 2 0
```

### 输出

```
14
```



---

---
title: "Turtle and Intersected Segments"
layout: "post"
diff: 省选/NOI-
pid: CF1981E
tag: ['生成树']
---

# Turtle and Intersected Segments

## 题目描述

Turtle 给你 $n$ 条线段和一个序列 $a_1,a_2,\cdots,a_n$，第 $i$ 条线段是 $[l_i,r_i]$。

Turtle 将按如下方式建图：对于任意的 $i,j$，若 $a_i,a_j$ 相交，则 $i,j$ 之间连一条边权为 $|a_i-a_j|$ 的边。相交的定义为 $\max(l_1,l_2)\le\min(r_1,r_2)$。

Turtle 想知道最小生成树的边权和是多少。


保证所有子数据 $n$ 的和不超过 $5\cdot10^5$。

## 输入格式

一组输入数据有 $t(1\le t\le10^5)$ 组子数据。第一行输入 $t$，每组子数据格式如下：

## 输出格式

对于每组子数据输出一行一个整数，表示最小生成树的边权和，若没有生成树输出 $-1$。

## 样例 #1

### 输入

```
4
5
1 7 3
2 4 6
3 5 5
6 7 9
3 4 4
5
2 7 3
1 3 6
4 5 5
6 7 9
1 1 4
4
1 4 3
1 2 1
3 4 5
1 4 4
3
1 3 1
2 3 3
4 5 8
```

### 输出

```
9
13
4
-1
```



---

---
title: "Gift"
layout: "post"
diff: 省选/NOI-
pid: CF76A
tag: ['排序', '生成树', '栈']
---

# Gift

## 题目描述

The kingdom of Olympia consists of $ N $ cities and $ M $ bidirectional roads. Each road connects exactly two cities and two cities can be connected with more than one road. Also it possible that some roads connect city with itself making a loop.

All roads are constantly plundered with bandits. After a while bandits became bored of wasting time in road robberies, so they suggested the king of Olympia to pay off. According to the offer, bandits want to get a gift consisted of gold and silver coins. Offer also contains a list of restrictions: for each road it is known $ g_{i} $ — the smallest amount of gold and $ s_{i} $ — the smallest amount of silver coins that should be in the gift to stop robberies on the road. That is, if the gift contains $ a $ gold and $ b $ silver coins, then bandits will stop robberies on all the roads that $ g_{i}<=a $ and $ s_{i}<=b $ .

Unfortunately kingdom treasury doesn't contain neither gold nor silver coins, but there are Olympian tugriks in it. The cost of one gold coin in tugriks is $ G $ , and the cost of one silver coin in tugriks is $ S $ . King really wants to send bandits such gift that for any two cities there will exist a safe path between them. Your task is to find the minimal cost in Olympian tugriks of the required gift.

## 输入格式

The first line of the input contains two integers $ N $ and $ M $ ( $ 2<=N<=200 $ , $ 1<=M<=50000 $ ) — the number of cities and the number of roads, respectively. The second line contains two integers $ G $ and $ S $ ( $ 1<=G,S<=10^{9} $ ) — the prices of gold and silver coins in tugriks. The following $ M $ lines contain information about the offer. Each of the records in list is given as four integers $ x_{i},y_{i},g_{i},s_{i} $ , where $ x_{i} $ and $ y_{i} $ are the numbers of cities that the road connects and $ g_{i} $ , $ s_{i} $ are minimal gold and silver coins requirements for the $ i $ -th road ( $ 1<=x_{i},y_{i}<=N $ , $ 1<=g_{i},s_{i}<=10^{9} $ ). Cities are numbered from $ 1 $ to $ N $ . It is possible that there are more than one road between a pair of cities. It is possible that a road connects the city with itself.

## 输出格式

The output should contain the minimal cost of the gift in Olympian tugriks. If there is no gift that satisfies the given requirements output ![](https://cdn.luogu.com.cn/upload/vjudge_pic/CF76A/843ffcb025f9d699cf4e412e21508ca44c9ae26c.png).

## 样例 #1

### 输入

```
3 3
2 1
1 2 10 15
1 2 4 20
1 3 5 1

```

### 输出

```
30

```



---

---
title: "Best Edge Weight"
layout: "post"
diff: 省选/NOI-
pid: CF827D
tag: ['深度优先搜索 DFS', '生成树', '动态树 LCT']
---

# Best Edge Weight

## 题目描述

You are given a connected weighted graph with $ n $ vertices and $ m $ edges. The graph doesn't contain loops nor multiple edges. Consider some edge with id $ i $ . Let's determine for this edge the maximum integer weight we can give to it so that it is contained in all minimum spanning trees of the graph if we don't change the other weights.

You are to determine this maximum weight described above for each edge. You should calculate the answer for each edge independently, it means there can't be two edges with changed weights at the same time.

## 输入格式

The first line contains two integers $ n $ and $ m $ ( $ 2<=n<=2·10^{5} $ , $ n-1<=m<=2·10^{5} $ ), where $ n $ and $ m $ are the number of vertices and the number of edges in the graph, respectively.

Each of the next $ m $ lines contains three integers $ u $ , $ v $ and $ c $ ( $ 1<=v,u<=n $ , $ v≠u $ , $ 1<=c<=10^{9} $ ) meaning that there is an edge between vertices $ u $ and $ v $ with weight $ c $ .

## 输出格式

Print the answer for each edge in the order the edges are given in the input. If an edge is contained in every minimum spanning tree with any weight, print -1 as the answer.

## 样例 #1

### 输入

```
4 4
1 2 2
2 3 2
3 4 2
4 1 3

```

### 输出

```
2 2 2 1 
```

## 样例 #2

### 输入

```
4 3
1 2 2
2 3 2
3 4 2

```

### 输出

```
-1 -1 -1 
```



---

---
title: "Xor-MST"
layout: "post"
diff: 省选/NOI-
pid: CF888G
tag: ['深度优先搜索 DFS', '生成树', '进制']
---

# Xor-MST

## 题目描述

You are given a complete undirected graph with $ n $ vertices. A number $ a_{i} $ is assigned to each vertex, and the weight of an edge between vertices $ i $ and $ j $ is equal to $ a_{i}xora_{j} $ .

Calculate the weight of the minimum spanning tree in this graph.

## 输入格式

The first line contains $ n $ ( $ 1<=n<=200000 $ ) — the number of vertices in the graph.

The second line contains $ n $ integers $ a_{1} $ , $ a_{2} $ , ..., $ a_{n} $ ( $ 0<=a_{i}<2^{30} $ ) — the numbers assigned to the vertices.

## 输出格式

Print one number — the weight of the minimum spanning tree in the graph.

## 样例 #1

### 输入

```
5
1 2 3 4 5

```

### 输出

```
8

```

## 样例 #2

### 输入

```
4
1 2 3 4

```

### 输出

```
8

```



---

---
title: "Envy"
layout: "post"
diff: 省选/NOI-
pid: CF891C
tag: ['生成树', '连通块', '虚树']
---

# Envy

## 题目描述

For a connected undirected weighted graph $ G $ , MST (minimum spanning tree) is a subgraph of $ G $ that contains all of $ G $ 's vertices, is a tree, and sum of its edges is minimum possible.

You are given a graph $ G $ . If you run a MST algorithm on graph it would give you only one MST and it causes other edges to become jealous. You are given some queries, each query contains a set of edges of graph $ G $ , and you should determine whether there is a MST containing all these edges or not.

## 输入格式

The first line contains two integers $ n $ , $ m $ ( $ 2<=n,m<=5·10^{5} $ , $ n-1<=m $ ) — the number of vertices and edges in the graph and the number of queries.

The $ i $ -th of the next $ m $ lines contains three integers $ u_{i} $ , $ v_{i} $ , $ w_{i} $ ( $ u_{i}≠v_{i} $ , $ 1<=w_{i}<=5·10^{5} $ ) — the endpoints and weight of the $ i $ -th edge. There can be more than one edges between two vertices. It's guaranteed that the given graph is connected.

The next line contains a single integer $ q $ ( $ 1<=q<=5·10^{5} $ ) — the number of queries.

 $ q $ lines follow, the $ i $ -th of them contains the $ i $ -th query. It starts with an integer $ k_{i} $ ( $ 1<=k_{i}<=n-1 $ ) — the size of edges subset and continues with $ k_{i} $ distinct space-separated integers from $ 1 $ to $ m $ — the indices of the edges. It is guaranteed that the sum of $ k_{i} $ for $ 1<=i<=q $ does not exceed $ 5·10^{5} $ .

## 输出格式

For each query you should print "YES" (without quotes) if there's a MST containing these edges and "NO" (of course without quotes again) otherwise.

## 说明/提示

This is the graph of sample:

 ![](https://cdn.luogu.com.cn/upload/vjudge_pic/CF891C/d7f37868e211da76f9c523f75a033c3f4d56f21c.png)Weight of minimum spanning tree on this graph is $ 6 $ .

MST with edges $ (1,3,4,6) $ , contains all of edges from the first query, so answer on the first query is "YES".

Edges from the second query form a cycle of length $ 3 $ , so there is no spanning tree including these three edges. Thus, answer is "NO".

## 样例 #1

### 输入

```
5 7
1 2 2
1 3 2
2 3 1
2 4 1
3 4 1
3 5 2
4 5 2
4
2 3 4
3 3 4 5
2 1 7
2 1 2

```

### 输出

```
YES
NO
YES
NO

```



---

---
title: "Weighting a Tree"
layout: "post"
diff: 省选/NOI-
pid: CF901D
tag: ['生成树', '最近公共祖先 LCA', '构造']
---

# Weighting a Tree

## 题目描述

给你一个有 $n$ 个顶点与 $m$ 条边的无向图，那些顶点的编号依次为 $1$ 到 $n$。

再给你 $n$ 个整数 $C[1],c[2],…,C[n]$，每一个数都在区间 $[-n,n]$ 之间。保证 $C[v]$ 的奇偶性与顶点 $v$ 的度的奇偶性相同。一个顶点的的度是指连接到它的边数。

你需要按照下列的要求为所有边写上一个在 $-2\cdot n^2$ 与 $2\cdot n^2$ 之间的一个重量：对于任何一个顶点 $v$，所有连接到这个顶点的边的重量和等于 $C[v]$。或者，确定这是不可能达到的。

## 输入格式

第一行是两个整数 $n$ 和 $m$ $\ (2\le n\le 10^5$,$n-1\le m\le 10^5)$，为边与顶点的个数。

第二行有 $n$ 个整数 $C[1],C[2]……C[n]\ (-n\le C[i]\le n$)，$C[i]$ 是连接到 $i$ 的边的权值之和。保证 $C[v]$ 的奇偶性与顶点 $v$ 的度的奇偶性相同。

之后的 $m$ 行是用来描述无向图的边的。对于第 $i$ 行，有 $a[i]$ 和 $b[i]$ 两个整数$\ (1\le a[i],b[i]\le n,a[i]≠b[i])$，表示第 $i$ 条边连接点 $a[i]$ 和 $b[i]$ 。

保证给出的无向图是联通的且不含有重边与自环。

## 输出格式

如果无解，输出"NO"。

否则输出"YES"和$m$行，每一行表示对应编号的边的权值。

Translated by @Microelectronics

## 样例 #1

### 输入

```
3 3
2 2 2
1 2
2 3
1 3

```

### 输出

```
YES
1
1
1

```

## 样例 #2

### 输入

```
4 3
-1 0 2 1
1 2
2 3
3 4

```

### 输出

```
YES
-1
1
1

```

## 样例 #3

### 输入

```
6 6
3 5 5 5 1 5
1 4
3 2
4 3
4 5
3 5
5 6

```

### 输出

```
YES
3
5
3
-1
-3
5

```

## 样例 #4

### 输入

```
4 4
4 4 2 4
1 2
2 3
3 4
4 1

```

### 输出

```
NO
```



---

