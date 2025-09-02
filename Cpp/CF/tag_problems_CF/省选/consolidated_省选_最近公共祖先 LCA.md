---
title: "Beautiful Tree"
layout: "post"
diff: 省选/NOI-
pid: CF1904F
tag: ['倍增', '强连通分量', 'Tarjan', '最近公共祖先 LCA']
---

# Beautiful Tree

## 题目描述

Lunchbox has a tree of size $ n $ rooted at node $ 1 $ . Each node is then assigned a value. Lunchbox considers the tree to be beautiful if each value is distinct and ranges from $ 1 $ to $ n $ . In addition, a beautiful tree must also satisfy $ m $ requirements of $ 2 $ types:

- "1 a b c" — The node with the smallest value on the path between nodes $ a $ and $ b $ must be located at $ c $ .
- "2 a b c" — The node with the largest value on the path between nodes $ a $ and $ b $ must be located at $ c $ .

Now, you must assign values to each node such that the resulting tree is beautiful. If it is impossible to do so, output $ -1 $ .

## 输入格式

The first line contains two integers $ n $ and $ m $ ( $ 2 \le n, m \le 2 \cdot 10^5 $ ).

The next $ n - 1 $ lines contain two integers $ u $ and $ v $ ( $ 1 \le u, v \le n, u \ne v $ ) — denoting an edge between nodes $ u $ and $ v $ . It is guaranteed that the given edges form a tree.

The next $ m $ lines each contain four integers $ t $ , $ a $ , $ b $ , and $ c $ ( $ t \in \{1,2\} $ , $ 1 \le a, b, c \le n $ ). It is guaranteed that node $ c $ is on the path between nodes $ a $ and $ b $ .

## 输出格式

If it is impossible to assign values such that the tree is beautiful, output $ -1 $ . Otherwise, output $ n $ integers, the $ i $ -th of which denotes the value of node $ i $ .

## 样例 #1

### 输入

```
7 5
1 2
1 3
1 4
3 5
4 6
3 7
1 6 5 1
2 6 7 3
1 2 7 1
1 7 5 7
2 4 2 2
```

### 输出

```
1 6 7 5 3 4 2
```

## 样例 #2

### 输入

```
2 2
1 2
1 1 2 1
1 1 2 2
```

### 输出

```
-1
```



---

---
title: "Vertex Pairs"
layout: "post"
diff: 省选/NOI-
pid: CF2042E
tag: ['贪心', '最近公共祖先 LCA']
---

# Vertex Pairs

## 题目描述

给定一个由$ 2n $个顶点组成的树。回想一下，树是一个没有环的连通无向图。每个顶点上都写了一个从$ 1 $到$ n $的整数。从$ 1 $到$ n $的每个值都恰好写在两个不同的顶点上。每个顶点也有成本-顶点$ i $成本$ 2^i $。

你需要选择树的一个顶点子集，如下所示：

- 子集是连通的；也就是说，从子集中的每个顶点，只通过子集中的顶点可达子集中的每个其他顶点；
- 从$ 1 $到$ n $的每个值都至少写在子集中的一个顶点上。

在所有这样的子集中，您需要找到其中顶点的总代价最小的子集。注意，您不需要最小化子集中的顶点数量。

## 输入格式

第一行包含一个整数$ n $ （$ 1 \le n \le 2 \cdot 10^5 $）。

第二行包含$ 2n $整数$ a_1, a_2, \dots, a_{2n} $ （$ 1 \le a_i \le n $）。从$ 1 $到$ n $的每个值恰好出现两次。

接下来的$ 2n-1 $行中每行包含两个整数$ v $和$ u $ （$ 1 \le v, u \le 2n $）——树的边。这些边构成了一棵有效的树。

## 输出格式

在第一行中，打印一个整数$ k $——子集中的顶点数。

在第二行中，打印从$ 1 $到$ 2n $的$ k $个不同整数——所选子集中顶点的索引。顶点可以以任意顺序打印。

## 样例 #1

### 输入

```
3
1 1 3 2 3 2
4 2
1 6
6 2
6 3
2 5
```

### 输出

```
3
2 4 5
```

## 样例 #2

### 输入

```
3
2 3 1 3 2 1
6 4
2 4
5 2
3 6
3 1
```

### 输出

```
4
1 3 4 6
```

## 样例 #3

### 输入

```
6
5 2 3 4 6 4 2 5 6 1 1 3
10 8
2 10
12 7
4 10
5 9
6 2
1 9
3 4
12 6
11 5
4 5
```

### 输出

```
6
2 3 4 5 8 10
```



---

---
title: "Sandy and Nuts"
layout: "post"
diff: 省选/NOI-
pid: CF599E
tag: ['动态规划 DP', '枚举', '最近公共祖先 LCA']
---

# Sandy and Nuts

## 题目描述

Rooted tree is a connected graph without any simple cycles with one vertex selected as a root. In this problem the vertex number $ 1 $ will always serve as a root.

Lowest common ancestor of two vertices $ u $ and $ v $ is the farthest from the root vertex that lies on both the path from $ u $ to the root and on path from $ v $ to the root. We will denote it as $ LCA(u,v) $ .

Sandy had a rooted tree consisting of $ n $ vertices that she used to store her nuts. Unfortunately, the underwater storm broke her tree and she doesn't remember all it's edges. She only managed to restore $ m $ edges of the initial tree and $ q $ triples $ a_{i} $ , $ b_{i} $ and $ c_{i} $ , for which she supposes $ LCA(a_{i},b_{i})=c_{i} $ .

Help Sandy count the number of trees of size $ n $ with vertex $ 1 $ as a root, that match all the information she remembered. If she made a mess and there are no such trees then print $ 0 $ . Two rooted trees are considered to be distinct if there exists an edge that occur in one of them and doesn't occur in the other one.

## 输入格式

The first line of the input contains three integers $ n $ , $ m $ and $ q $ ( $ 1<=n<=13,0<=m<n,0<=q<=100 $ ) — the number of vertices, the number of edges and $ LCA $ triples remembered by Sandy respectively.

Each of the next $ m $ lines contains two integers $ u_{i} $ and $ v_{i} $ ( $ 1<=u_{i},v_{i}<=n,u_{i}≠v_{i} $ ) — the numbers of vertices connected by the $ i $ -th edge. It's guaranteed that this set of edges is a subset of edges of some tree.

The last $ q $ lines contain the triplets of numbers $ a_{i} $ , $ b_{i} $ , $ c_{i} $ ( $ 1<=a_{i},b_{i},c_{i}<=n) $ . Each of these triples define $ LCA(a_{i},b_{i})=c_{i} $ . It's not guaranteed that there exists a tree that satisfy all the given $ LCA $ conditions.

## 输出格式

Print a single integer — the number of trees of size $ n $ that satisfy all the conditions.

## 说明/提示

In the second sample correct answer looks like this:

 ![](https://cdn.luogu.com.cn/upload/vjudge_pic/CF599E/3a06f49f1bab15c25fa9029dff674e9bd2958cf5.png)In the third sample there are two possible trees:

 ![](https://cdn.luogu.com.cn/upload/vjudge_pic/CF599E/5bc65707292dd568a0ac7a018a2f94f9303bf3c4.png) ![](https://cdn.luogu.com.cn/upload/vjudge_pic/CF599E/bacea40f00b7ff26956d9e8aa34e3c4499c85dc6.png)In the fourth sample the answer is $ 0 $ because the information about $ LCA $ is inconsistent.

## 样例 #1

### 输入

```
4 0 0

```

### 输出

```
16

```

## 样例 #2

### 输入

```
4 0 1
3 4 2

```

### 输出

```
1

```

## 样例 #3

### 输入

```
3 1 0
1 2

```

### 输出

```
2

```

## 样例 #4

### 输入

```
3 0 2
2 3 2
2 3 1

```

### 输出

```
0

```

## 样例 #5

### 输入

```
4 1 2
1 2
2 2 2
3 4 2

```

### 输出

```
1

```



---

---
title: "Digit Tree"
layout: "post"
diff: 省选/NOI-
pid: CF715C
tag: ['最近公共祖先 LCA', '概率论', '逆元']
---

# Digit Tree

## 题目描述

ZS the Coder has a large tree. It can be represented as an undirected connected graph of $ n $ vertices numbered from $ 0 $ to $ n-1 $ and $ n-1 $ edges between them. There is a single nonzero digit written on each edge.

One day, ZS the Coder was bored and decided to investigate some properties of the tree. He chose a positive integer $ M $ , which is coprime to $ 10 $ , i.e. ![](https://cdn.luogu.com.cn/upload/vjudge_pic/CF715C/9b5bdec4cb6231baa1f3fcb57eb25703ae0eed8f.png).

ZS consider an ordered pair of distinct vertices $ (u,v) $ interesting when if he would follow the shortest path from vertex $ u $ to vertex $ v $ and write down all the digits he encounters on his path in the same order, he will get a decimal representaion of an integer divisible by $ M $ .

Formally, ZS consider an ordered pair of distinct vertices $ (u,v) $ interesting if the following states true:

- Let $ a_{1}=u,a_{2},...,a_{k}=v $ be the sequence of vertices on the shortest path from $ u $ to $ v $ in the order of encountering them;
- Let $ d_{i} $ ( $ 1<=i&lt;k $ ) be the digit written on the edge between vertices $ a_{i} $ and $ a_{i+1} $ ;
- The integer ![](https://cdn.luogu.com.cn/upload/vjudge_pic/CF715C/72be647436ef167ccaba4334e08ad71c22afc6b4.png) is divisible by $ M $ .

Help ZS the Coder find the number of interesting pairs!

## 输入格式

The first line of the input contains two integers, $ n $ and $ M $ ( $ 2<=n<=100000 $ , $ 1<=M<=10^{9} $ , ![](https://cdn.luogu.com.cn/upload/vjudge_pic/CF715C/d9389e45dbbc083daab078bda82851582dd53c47.png)) — the number of vertices and the number ZS has chosen respectively.

The next $ n-1 $ lines contain three integers each. $ i $ -th of them contains $ u_{i},v_{i} $ and $ w_{i} $ , denoting an edge between vertices $ u_{i} $ and $ v_{i} $ with digit $ w_{i} $ written on it ( $ 0<=u_{i},v_{i}&lt;n,1<=w_{i}<=9 $ ).

## 输出格式

Print a single integer — the number of interesting (by ZS the Coder's consideration) pairs.

## 说明/提示

In the first sample case, the interesting pairs are $ (0,4),(1,2),(1,5),(3,2),(2,5),(5,2),(3,5) $ . The numbers that are formed by these pairs are $ 14,21,217,91,7,7,917 $ respectively, which are all multiples of $ 7 $ . Note that $ (2,5) $ and $ (5,2) $ are considered different.

 ![](https://cdn.luogu.com.cn/upload/vjudge_pic/CF715C/08c05395fdf8f9a998abf43b020555e6b5471bd5.png)In the second sample case, the interesting pairs are $ (4,0),(0,4),(3,2),(2,3),(0,1),(1,0),(4,1),(1,4) $ , and $ 6 $ of these pairs give the number $ 33 $ while $ 2 $ of them give the number $ 3333 $ , which are all multiples of $ 11 $ .

 ![](https://cdn.luogu.com.cn/upload/vjudge_pic/CF715C/8a71025758e81b9cf19889885872aec3ca3f5ffc.png)

## 样例 #1

### 输入

```
6 7
0 1 2
4 2 4
2 0 1
3 0 9
2 5 7

```

### 输出

```
7

```

## 样例 #2

### 输入

```
5 11
1 2 3
2 0 3
3 0 3
4 3 3

```

### 输出

```
8

```



---

---
title: "Nikita and game"
layout: "post"
diff: 省选/NOI-
pid: CF842E
tag: ['最近公共祖先 LCA', '树的直径']
---

# Nikita and game

## 题目描述

Nikita plays a new computer game. There are $ m $ levels in this game. In the beginning of each level a new class appears in the game; this class is a child-class of the class $ y_{i} $ (and $ y_{i} $ is called parent-class for this new class). Thus, the classes form a tree. Initially there is only one class with index $ 1 $ .

Changing the class to its neighbour (child-class or parent-class) in the tree costs $ 1 $ coin. You can not change the class back. The cost of changing the class $ a $ to the class $ b $ is equal to the total cost of class changes on the path from $ a $ to $ b $ in the class tree.

Suppose that at $ i $ -th level the maximum cost of changing one class to another is $ x $ . For each level output the number of classes such that for each of these classes there exists some other class $ y $ , and the distance from this class to $ y $ is exactly $ x $ .

## 输入格式

First line contains one integer number $ m $ — number of queries ( $ 1<=m<=3·10^{5} $ ).

Next $ m $ lines contain description of queries. $ i $ -th line ( $ 1<=i<=m $ ) describes the $ i $ -th level and contains an integer $ y_{i} $ — the index of the parent-class of class with index $ i+1 $ ( $ 1<=y_{i}<=i $ ).

## 输出格式

Suppose that at $ i $ -th level the maximum cost of changing one class to another is $ x $ . For each level output the number of classes such that for each of these classes there exists some other class $ y $ , and the distance from this class to $ y $ is exactly $ x $ .

## 样例 #1

### 输入

```
4
1
1
2
1

```

### 输出

```
2
2
2
3

```

## 样例 #2

### 输入

```
4
1
1
2
3

```

### 输出

```
2
2
2
2

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
title: "NN country"
layout: "post"
diff: 省选/NOI-
pid: CF983E
tag: ['倍增', '深度优先搜索 DFS', '最近公共祖先 LCA']
---

# NN country

## 题目描述

In the NN country, there are $ n $ cities, numbered from $ 1 $ to $ n $ , and $ n - 1 $ roads, connecting them. There is a roads path between any two cities.

There are $ m $ bidirectional bus routes between cities. Buses drive between two cities taking the shortest path with stops in every city they drive through. Travelling by bus, you can travel from any stop on the route to any other. You can travel between cities only by bus.

You are interested in $ q $ questions: is it possible to get from one city to another and what is the minimum number of buses you need to use for it?

## 输入格式

The first line contains a single integer $ n $ ( $ 2 \le n \le 2 \cdot 10^5 $ ) — the number of cities.

The second line contains $ n - 1 $ integers $ p_2, p_3, \ldots, p_n $ ( $ 1 \le p_i < i $ ), where $ p_i $ means that cities $ p_i $ and $ i $ are connected by road.

The third line contains a single integer $ m $ ( $ 1 \le m \le 2 \cdot 10^5 $ ) — the number of bus routes.

Each of the next $ m $ lines contains $ 2 $ integers $ a $ and $ b $ ( $ 1 \le a, b \le n $ , $ a \neq b $ ), meaning that there is a bus route between cities $ a $ and $ b $ . It is possible that there is more than one route between two cities.

The next line contains a single integer $ q $ ( $ 1 \le q \le 2 \cdot 10^5 $ ) — the number of questions you are interested in.

Each of the next $ q $ lines contains $ 2 $ integers $ v $ and $ u $ ( $ 1 \le v, u \le n $ , $ v \neq u $ ), meaning that you are interested if it is possible to get from city $ v $ to city $ u $ and what is the minimum number of buses you need to use for it.

## 输出格式

Print the answer for each question on a separate line. If there is no way to get from one city to another, print $ -1 $ . Otherwise print the minimum number of buses you have to use.

## 说明/提示

 ![](https://cdn.luogu.com.cn/upload/vjudge_pic/CF983E/c42b59e68a69956240c890e5363c8c983d1d430c.png) Routes for first sample are marked on the picture.

## 样例 #1

### 输入

```
7
1 1 1 4 5 6
4
4 2
5 4
1 3
6 7
6
4 5
3 5
7 2
4 5
3 2
5 3

```

### 输出

```
1
3
-1
1
2
3

```

## 样例 #2

### 输入

```
7
1 1 2 3 4 1
4
4 7
3 5
7 6
7 6
6
4 6
3 1
3 2
2 7
6 3
5 3

```

### 输出

```
1
-1
-1
1
-1
1

```



---

