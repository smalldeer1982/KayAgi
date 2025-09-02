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
title: "Tree or not Tree"
layout: "post"
diff: 省选/NOI-
pid: CF117E
tag: ['线段树', '树链剖分']
---

# Tree or not Tree

## 题目描述

You are given an undirected connected graph $ G $ consisting of $ n $ vertexes and $ n $ edges. $ G $ contains no self-loops or multiple edges. Let each edge has two states: on and off. Initially all edges are switched off.

You are also given $ m $ queries represented as $ (v,u) $ — change the state of all edges on the shortest path from vertex $ v $ to vertex $ u $ in graph $ G $ . If there are several such paths, the lexicographically minimal one is chosen. More formally, let us consider all shortest paths from vertex $ v $ to vertex $ u $ as the sequences of vertexes $ v,v_{1},v_{2},...,u $ . Among such sequences we choose the lexicographically minimal one.

After each query you should tell how many connected components has the graph whose vertexes coincide with the vertexes of graph $ G $ and edges coincide with the switched on edges of graph $ G $ .

## 输入格式

The first line contains two integers $ n $ and $ m $ ( $ 3<=n<=10^{5} $ , $ 1<=m<=10^{5} $ ). Then $ n $ lines describe the graph edges as $ a $ $ b $ ( $ 1<=a,b<=n $ ). Next $ m $ lines contain the queries as $ v $ $ u $ ( $ 1<=v,u<=n $ ).

It is guaranteed that the graph is connected, does not have any self-loops or multiple edges.

## 输出格式

Print $ m $ lines, each containing one integer — the query results.

## 说明/提示

Let's consider the first sample. We'll highlight the switched on edges blue on the image.

- The graph before applying any operations. No graph edges are switched on, that's why there initially are 5 connected components.
  
   ![](https://cdn.luogu.com.cn/upload/vjudge_pic/CF117E/6d848190f5d9993cf6ddd5c1e2cd0e57d9ae6288.png)
- The graph after query $ v=5,u=4 $ . We can see that the graph has three components if we only consider the switched on edges.
  
   ![](https://cdn.luogu.com.cn/upload/vjudge_pic/CF117E/2f3ad3d35eecb878e654ed5cd572ed4f02ecf9ff.png)
- The graph after query $ v=1,u=5 $ . We can see that the graph has three components if we only consider the switched on edges.
  
   ![](https://cdn.luogu.com.cn/upload/vjudge_pic/CF117E/31e75e1c5e9c21b4cec0bc2e71e38cbba47e290d.png)

Lexicographical comparison of two sequences of equal length of $ k $ numbers should be done as follows. Sequence $ x $ is lexicographically less than sequence $ y $ if exists such $ i $ ( $ 1<=i<=k $ ), so that $ x_{i}<y_{i} $ , and for any $ j $ ( $ 1<=j<i $ ) $ x_{j}=y_{j} $ .

## 样例 #1

### 输入

```
5 2
2 1
4 3
2 4
2 5
4 1
5 4
1 5

```

### 输出

```
3
3

```

## 样例 #2

### 输入

```
6 2
4 6
4 3
1 2
6 5
1 5
1 4
2 5
2 6

```

### 输出

```
4
3

```



---

---
title: "Tourists"
layout: "post"
diff: 省选/NOI-
pid: CF487E
tag: ['线段树', '强连通分量', '树链剖分', '圆方树']
---

# Tourists

## 题目描述

Cyberland 有 $n$ 座城市，编号从 $1$ 到 $n$，有 $m$ 条双向道路连接这些城市。第 $j$ 条路连接城市 $a_j$ 和 $b_j$。每天，都有成千上万的游客来到 Cyberland 游玩。

在每一个城市，都有纪念品售卖，第 $i$ 个城市售价为 $w_i$。这个售价有时会变动。

每一个游客的游览路径都有固定起始城市和终止城市，且不会经过重复的城市。

他们会在路径上的城市中，售价最低的那个城市购买纪念品。

你能求出每一个游客在所有合法的路径中能购买的最低售价是多少吗？

你要处理 $q$ 个操作：

`C a w`： 表示 $a$ 城市的纪念品售价变成 $w$。

`A a b`： 表示有一个游客要从 $a$ 城市到 $b$ 城市，你要回答在所有他的旅行路径中最低售价的最低可能值。

## 输入格式

第一行包含用一个空格隔开的三个数 $n, m, q$。

接下来 $n$ 行，每行包含一个数 $w_i$。

接下来 $m$ 行，每行包含用一个空格隔开的两个数 $a_j$,$b_j$。（$1 \le a _ j, b _ j \le n,a _ j \neq b _ j$）

数据保证没有两条道路连接同样一对城市，也没有一条道路两端是相同的城市。并且任意两个城市都可以相互到达。

接下来 $q$ 行，每行是 `C a w` 或 `A a b` ，描述了一个操作。

## 输出格式

对于每一个 A 类操作，输出一行表示对应的答案。

## 样例 #1

### 输入

```
3 3 3
1
2
3
1 2
2 3
1 3
A 2 3
C 1 5
A 2 3

```

### 输出

```
1
2

```

## 样例 #2

### 输入

```
7 9 4
1
2
3
4
5
6
7
1 2
2 5
1 5
2 3
3 4
2 4
5 6
6 7
5 7
A 2 3
A 6 4
A 6 7
A 3 3

```

### 输出

```
2
1
5
3

```



---

---
title: "Duff in the Army"
layout: "post"
diff: 省选/NOI-
pid: CF587C
tag: ['线段树', '倍增', '树链剖分']
---

# Duff in the Army

## 题目描述

Duff是一个军队中的一名士兵。Malek是**她**的上司。

他们在一个名为Andarz Gu的国家里，这个国家有 $n$  个城市，分别编号 $1-n$  。有 $n-1$  条双向通行的道路联通整个国家。

一共有 $m$  个人居住在这个国家中的一些城市里，每一个人有他的身份号（第 $i$  个人的身份号是 $i$  ）。注意，有可能有多个人居住在同一个城市，也有可能有些城市无人居住。

Malek喜欢对别人下命令，所以他让Duff回答他的q个提问，每一个提问包含三个数 $v$  , $u$  和 $a$  。

为了回答一个提问：  
设想一共有 $x$  个人居住在从城市 $u$  到城市 $v$  （包含）的路径上，他们的身份号从小到大排序后分别是 $p_1,p_2,...,p_x$  。如果设 $k=min(x,a)$  ，那么Duff应该按顺序告诉Malek $k,p_1,p_2,...,p_k$  。从另一种说法来说，Malek想要知道在路径上身份编号前 $a$  小的人（或者更少，如果这条路上总共居住的人少于 $a$  个）。

Duff现在非常忙碌，所以她让你来帮助她回答Malek的提问。

## 输入格式

输入的第一行包括3个整数， $n$  , $m$  和 $q$  。($1<=n,m,q<=10^5$ ）

接下来的 $n-1$  行描述了连通城市的道路。每一行包括两个整数 $u$  和 $v$  ，表示从城市 $u$  到城市 $v$  有一条双向道路。（$1<=u,v<=n , u≠v$ ）

接下来的一行包括 $m$  个正整数 $c_1,c_2,...,c_m$  ， $c_i$  表示编号为 $i$  的人居住在城市 $c_i$  里。（$1<=c_i<=n$ ，对于每一个 $i$  有 $1<=i<=m$ ）

接下来的 $q$  行描述了Malek的提问。每一行包括三个正整数 $u$  , $v$  和 $a$  （$1<=v,u<=n$ ，$1<=a<=10$ ，含义见题面）

## 输出格式

对于每一次提问，输出一行，包括 $k,p_1,p_2,...,p_k$  （含义见题面）。

感谢@星烁晶熠辉  提供的翻译

## 样例 #1

### 输入

```
5 4 5
1 3
1 2
1 4
4 5
2 1 4 3
4 5 6
1 5 2
5 5 10
2 3 3
5 3 1

```

### 输出

```
1 3
2 2 3
0
3 1 2 4
1 2

```



---

---
title: "Jamie and Tree"
layout: "post"
diff: 省选/NOI-
pid: CF916E
tag: ['线段树', '最近公共祖先 LCA', '树链剖分']
---

# Jamie and Tree

## 题目描述

To your surprise, Jamie is the final boss! Ehehehe.

Jamie has given you a tree with $ n $ vertices, numbered from $ 1 $ to $ n $ . Initially, the root of the tree is the vertex with number $ 1 $ . Also, each vertex has a value on it.

Jamie also gives you three types of queries on the tree:

 $ 1\ v $ — Change the tree's root to vertex with number $ v $ .

 $ 2\ u\ v\ x $ — For each vertex in the subtree of smallest size that contains $ u $ and $ v $ , add $ x $ to its value.

 $ 3\ v $ — Find sum of values of vertices in the subtree of vertex with number $ v $ .

A subtree of vertex $ v $ is a set of vertices such that $ v $ lies on shortest path from this vertex to root of the tree. Pay attention that subtree of a vertex can change after changing the tree's root.

Show your strength in programming to Jamie by performing the queries accurately!

## 输入格式

The first line of input contains two space-separated integers $ n $ and $ q $ ( $ 1<=n<=10^{5},1<=q<=10^{5} $ ) — the number of vertices in the tree and the number of queries to process respectively.

The second line contains $ n $ space-separated integers $ a_{1},a_{2},...,a_{n} $ ( $ -10^{8}<=a_{i}<=10^{8} $ ) — initial values of the vertices.

Next $ n-1 $ lines contains two space-separated integers $ u_{i},v_{i} $ ( $ 1<=u_{i},v_{i}<=n $ ) describing edge between vertices $ u_{i} $ and $ v_{i} $ in the tree.

The following $ q $ lines describe the queries.

Each query has one of following formats depending on its type:

 $ 1\ v $ ( $ 1<=v<=n $ ) for queries of the first type.

 $ 2\ u\ v\ x $ ( $ 1<=u,v<=n,-10^{8}<=x<=10^{8} $ ) for queries of the second type.

 $ 3\ v $ ( $ 1<=v<=n $ ) for queries of the third type.

All numbers in queries' descriptions are integers.

The queries must be carried out in the given order. It is guaranteed that the tree is valid.

## 输出格式

For each query of the third type, output the required answer. It is guaranteed that at least one query of the third type is given by Jamie.

## 说明/提示

The following picture shows how the tree varies after the queries in the first sample.

 ![](https://cdn.luogu.com.cn/upload/vjudge_pic/CF916E/9b296178af98e90dbbac00c785fb2ed88745e7bd.png)

## 样例 #1

### 输入

```
6 7
1 4 2 8 5 7
1 2
3 1
4 3
4 5
3 6
3 1
2 4 6 3
3 4
1 6
2 2 4 -5
1 4
3 3

```

### 输出

```
27
19
5

```

## 样例 #2

### 输入

```
4 6
4 3 5 6
1 2
2 3
3 4
3 1
1 3
2 2 4 3
1 1
2 2 4 -3
3 1

```

### 输出

```
18
21

```



---

---
title: "Santa's Gift"
layout: "post"
diff: 省选/NOI-
pid: CF960H
tag: ['线段树', '树链剖分', '期望']
---

# Santa's Gift

## 题目描述

Santa has an infinite number of candies for each of $ m $ flavours. You are given a rooted tree with $ n $ vertices. The root of the tree is the vertex $ 1 $ . Each vertex contains exactly one candy. The $ i $ -th vertex has a candy of flavour $ f_i $ .

Sometimes Santa fears that candies of flavour $ k $ have melted. He chooses any vertex $ x $ randomly and sends the subtree of $ x $ to the Bakers for a replacement. In a replacement, all the candies with flavour $ k $ are replaced with a new candy of the same flavour. The candies which are not of flavour $ k $ are left unchanged. After the replacement, the tree is restored.

The actual cost of replacing one candy of flavour $ k $ is $ c_k $ (given for each $ k $ ). The Baker keeps the price fixed in order to make calculation simple. Every time when a subtree comes for a replacement, the Baker charges $ C $ , no matter which subtree it is and which flavour it is.

Suppose that for a given flavour $ k $ the probability that Santa chooses a vertex for replacement is same for all the vertices. You need to find out the expected value of error in calculating the cost of replacement of flavour $ k $ . The error in calculating the cost is defined as follows.

 $ $$$ Error\ E(k) =\ (Actual Cost\ –\ Price\ charged\ by\ the\ Bakers) ^ 2. $ $ </p><p>Note that the actual cost is the cost of replacement of one candy of the flavour  $ k $  multiplied by the number of candies in the subtree.</p><p>Also, sometimes Santa may wish to replace a candy at vertex  $ x $  with a candy of some flavour from his pocket.</p><p>You need to handle two types of operations: </p><ul> <li> Change the flavour of the candy at vertex  $ x $  to  $ w $ . </li><li> Calculate the expected value of error in calculating the cost of replacement for a given flavour  $ k$$$.

## 输入格式

The first line of the input contains four integers $ n $ ( $ 2 \leqslant n \leqslant 5 \cdot 10^4 $ ), $ m $ , $ q $ , $ C $ ( $ 1 \leqslant m, q \leqslant 5 \cdot 10^4 $ , $ 0 \leqslant C \leqslant 10^6 $ ) — the number of nodes, total number of different flavours of candies, the number of queries and the price charged by the Bakers for replacement, respectively.

The second line contains $ n $ integers $ f_1, f_2, \dots, f_n $ ( $ 1 \leqslant f_i \leqslant m $ ), where $ f_i $ is the initial flavour of the candy in the $ i $ -th node.

The third line contains $ n - 1 $ integers $ p_2, p_3, \dots, p_n $ ( $ 1 \leqslant p_i \leqslant n $ ), where $ p_i $ is the parent of the $ i $ -th node.

The next line contains $ m $ integers $ c_1, c_2, \dots c_m $ ( $ 1 \leqslant c_i \leqslant 10^2 $ ), where $ c_i $ is the cost of replacing one candy of flavour $ i $ .

The next $ q $ lines describe the queries. Each line starts with an integer $ t $ ( $ 1 \leqslant t \leqslant 2 $ ) — the type of the query.

If $ t = 1 $ , then the line describes a query of the first type. Two integers $ x $ and $ w $ follow ( $ 1 \leqslant  x \leqslant  n $ , $ 1 \leqslant  w \leqslant m $ ), it means that Santa replaces the candy at vertex $ x $ with flavour $ w $ .

Otherwise, if $ t = 2 $ , the line describes a query of the second type and an integer $ k $ ( $ 1 \leqslant k \leqslant m $ ) follows, it means that you should print the expected value of the error in calculating the cost of replacement for a given flavour $ k $ .

The vertices are indexed from $ 1 $ to $ n $ . Vertex $ 1 $ is the root.

## 输出格式

Output the answer to each query of the second type in a separate line.

Your answer is considered correct if its absolute or relative error does not exceed $ 10^{-6} $ .

Formally, let your answer be $ a $ , and the jury's answer be $ b $ . The checker program considers your answer correct if and only if $ \frac{|a-b|}{max(1,b)}\leqslant 10^{-6} $ .

## 说明/提示

For $ 1 $ -st query, the error in calculating the cost of replacement for flavour $ 1 $ if vertex $ 1 $ , $ 2 $ or $ 3 $ is chosen are $ 66^2 $ , $ 66^2 $ and $ (-7)^2 $ respectively. Since the probability of choosing any vertex is same, therefore the expected value of error is $ \frac{66^2+66^2+(-7)^2}{3} $ .

Similarly, for $ 2 $ -nd query the expected value of error is $ \frac{41^2+(-7)^2+(-7)^2}{3} $ .

After $ 3 $ -rd query, the flavour at vertex $ 2 $ changes from $ 1 $ to $ 3 $ .

For $ 4 $ -th query, the expected value of error is $ \frac{(-7)^2+(-7)^2+(-7)^2}{3} $ .

Similarly, for $ 5 $ -th query, the expected value of error is $ \frac{89^2+41^2+(-7)^2}{3} $ .

## 样例 #1

### 输入

```
3 5 5 7
3 1 4
1 1
73 1 48 85 89
2 1
2 3
1 2 3
2 1
2 3

```

### 输出

```
2920.333333333333
593.000000000000
49.000000000000
3217.000000000000

```



---

