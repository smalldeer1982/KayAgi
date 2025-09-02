---
title: "Session in BSU"
layout: "post"
diff: 省选/NOI-
pid: CF1027F
tag: ['网络流', '连通块', '二分图']
---

# Session in BSU

## 题目描述

Polycarp studies in Berland State University. Soon he will have to take his exam. He has to pass exactly $ n $ exams.

For the each exam $ i $ there are known two days: $ a_i $ — day of the first opportunity to pass the exam, $ b_i $ — day of the second opportunity to pass the exam ( $ a_i < b_i $ ). Polycarp can pass at most one exam during each day. For each exam Polycarp chooses by himself which day he will pass this exam. He has to pass all the $ n $ exams.

Polycarp wants to pass all the exams as soon as possible. Print the minimum index of day by which Polycarp can pass all the $ n $ exams, or print -1 if he cannot pass all the exams at all.

## 输入格式

The first line of the input contains one integer $ n $ ( $ 1 \le n \le 10^6 $ ) — the number of exams.

The next $ n $ lines contain two integers each: $ a_i $ and $ b_i $ ( $ 1 \le a_i < b_i \le 10^9 $ ), where $ a_i $ is the number of day of the first passing the $ i $ -th exam and $ b_i $ is the number of day of the second passing the $ i $ -th exam.

## 输出格式

If Polycarp cannot pass all the $ n $ exams, print -1. Otherwise print the minimum index of day by which Polycarp can do that.

## 样例 #1

### 输入

```
2
1 5
1 7

```

### 输出

```
5

```

## 样例 #2

### 输入

```
3
5 13
1 5
1 7

```

### 输出

```
7

```

## 样例 #3

### 输入

```
3
10 40
40 80
10 80

```

### 输出

```
80

```

## 样例 #4

### 输入

```
3
99 100
99 100
99 100

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
title: "Two Paths"
layout: "post"
diff: 省选/NOI-
pid: CF36E
tag: ['图论', '连通块', '欧拉回路']
---

# Two Paths

## 题目背景

注意这题要加上这个：

```
freopen("input.txt","r",stdin);
freopen("output.txt","w",stdout);
```

## 题目描述

Once archaeologists found $ m $ mysterious papers, each of which had a pair of integers written on them. Ancient people were known to like writing down the indexes of the roads they walked along, as « $ a $ $ b $ » or « $ b $ $ a $ », where $ a,b $ are the indexes of two different cities joint by the road . It is also known that the mysterious papers are pages of two travel journals (those days a new journal was written for every new journey).

During one journey the traveler could walk along one and the same road several times in one or several directions but in that case he wrote a new entry for each time in his journal. Besides, the archaeologists think that the direction the traveler took on a road had no effect upon the entry: the entry that looks like « $ a $ $ b $ » could refer to the road from $ a $ to $ b $ as well as to the road from $ b $ to $ a $ .

The archaeologists want to put the pages in the right order and reconstruct the two travel paths but unfortunately, they are bad at programming. That’s where you come in. Go help them!

## 输入格式

The first input line contains integer $ m $ ( $ 1<=m<=10000 $ ). Each of the following $ m $ lines describes one paper. Each description consists of two integers $ a,b $ ( $ 1<=a,b<=10000 $ , $ a≠b $ ).

## 输出格式

In the first line output the number $ L_{1} $ . That is the length of the first path, i.e. the amount of papers in its description. In the following line output $ L_{1} $ space-separated numbers — the indexes of the papers that describe the first path. In the third and fourth lines output similarly the length of the second path $ L_{2} $ and the path itself. Both paths must contain at least one road, i.e. condition $ L_{1}&gt;0 $ and $ L_{2}&gt;0 $ must be met. The papers are numbered from $ 1 $ to $ m $ according to the order of their appearance in the input file. The numbers should be output in the order in which the traveler passed the corresponding roads. If the answer is not unique, output any.

If it’s impossible to find such two paths, output «-1».

Don’t forget that each paper should be used exactly once, i.e $ L_{1}+L_{2}=m $ .

## 样例 #1

### 输入

```
2
4 5
4 3

```

### 输出

```
1
2 
1
1

```

## 样例 #2

### 输入

```
1
1 2

```

### 输出

```
-1

```



---

---
title: "Mr. Kitayuta's Technology"
layout: "post"
diff: 省选/NOI-
pid: CF505D
tag: ['排序', '拓扑排序', '连通块']
---

# Mr. Kitayuta's Technology

## 题目描述

Shuseki Kingdom在创新和技术方面是世界领先的国家。在Shuseki Kingdom中有编号1到n的n个城市。

Kitayuta先生的研究使Shuseki Kingdom会在两个城市之间建造传送管道。连接两个城市的传送管道是单向的，即从城市x到城市y的传送管道不能用来从城市y前往城市x。由于每个城市内的交通极为发达，因此如果从城市x到城市y的传送管道和从城市y到城市z的传送管道都已建造好，人们就可以直接从城市x前往城市z。

Kitayuta先生同时也是一个政客。他认为有m对“重要城市对”(ai,bi) ( 1<=i<=m )之间的交通很重要。他计划建造传送管道时，要使得对于每对“重要城市对”(ai,bi)，都可以通过使用一个或多个传送管道，从城市ai前往城市bi。请你计算出，最少需要建造几条传送管道，才能满足Kitayuta先生的需求。到目前为止，还没有建造任何传送管道，城市之间也没有任何其他有效的交通工具。

## 输入格式

输入共m+1行

第一行，两个以空格分隔的整数n和m（2 <= n<= 10 ^ 5，1 <= m<= 10 ^ 5），分别表示Shuseki王国的城市数量和重要城市对的数量。

接下来的m行中，每行有两个数字ai和bi，( 1<=ai,bi<=n,ai≠bi )，表示从城市ai必须能通过一个或多个传送管道到达城市bi（但不必保证能从城市bi前往城市ai）。保证每对重要城市对都是不同的。

## 输出格式

输出共1行，一个整数，表示能使得Kitayuta先生的需求满足的传送管道的数量的最小值。

## 说明/提示

对于第一个样例，构建管道的最佳方法之一如下图所示：

![](https://cdn.luogu.org/upload/vjudge_pic/CF505D/41d1e53a1057dea3b2f50b9af3dc7c7c17995877.png)

对于第二个样例，构建管道的最佳方法之一如下图所示：

![](https://cdn.luogu.org/upload/vjudge_pic/CF505D/3fd4624f001628b234de5055b8104860cf1c833c.png)

## 样例 #1

### 输入

```
4 5
1 2
1 3
1 4
2 3
2 4

```

### 输出

```
3

```

## 样例 #2

### 输入

```
4 6
1 2
1 4
2 3
2 4
3 2
3 4

```

### 输出

```
4

```



---

---
title: "Bear and Square Grid"
layout: "post"
diff: 省选/NOI-
pid: CF679C
tag: ['字符串', '搜索', '连通块']
---

# Bear and Square Grid

## 题目描述

You have a grid with $ n $ rows and $ n $ columns. Each cell is either empty (denoted by '.') or blocked (denoted by 'X').

Two empty cells are directly connected if they share a side. Two cells $ (r_{1},c_{1}) $ (located in the row $ r_{1} $ and column $ c_{1} $ ) and $ (r_{2},c_{2}) $ are connected if there exists a sequence of empty cells that starts with $ (r_{1},c_{1}) $ , finishes with $ (r_{2},c_{2}) $ , and any two consecutive cells in this sequence are directly connected. A connected component is a set of empty cells such that any two cells in the component are connected, and there is no cell in this set that is connected to some cell not in this set.

Your friend Limak is a big grizzly bear. He is able to destroy any obstacles in some range. More precisely, you can choose a square of size $ k×k $ in the grid and Limak will transform all blocked cells there to empty ones. However, you can ask Limak to help only once.

The chosen square must be completely inside the grid. It's possible that Limak won't change anything because all cells are empty anyway.

You like big connected components. After Limak helps you, what is the maximum possible size of the biggest connected component in the grid?

## 输入格式

The first line of the input contains two integers $ n $ and $ k $ ( $ 1<=k<=n<=500 $ ) — the size of the grid and Limak's range, respectively.

Each of the next $ n $ lines contains a string with $ n $ characters, denoting the $ i $ -th row of the grid. Each character is '.' or 'X', denoting an empty cell or a blocked one, respectively.

## 输出格式

Print the maximum possible size (the number of cells) of the biggest connected component, after using Limak's help.

## 说明/提示

In the first sample, you can choose a square of size $ 2×2 $ . It's optimal to choose a square in the red frame on the left drawing below. Then, you will get a connected component with $ 10 $ cells, marked blue in the right drawing.

 ![](https://cdn.luogu.com.cn/upload/vjudge_pic/CF679C/73f9f2e0fd56d2fb7f7f3062a32953f02d9af103.png)

## 样例 #1

### 输入

```
5 2
..XXX
XX.XX
X.XXX
X...X
XXXX.

```

### 输出

```
10

```

## 样例 #2

### 输入

```
5 3
.....
.XXX.
.XXX.
.XXX.
.....

```

### 输出

```
25

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

