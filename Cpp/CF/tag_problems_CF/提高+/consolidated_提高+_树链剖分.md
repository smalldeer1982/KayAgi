---
title: "Ehab and the Big Finale"
layout: "post"
diff: 提高+/省选-
pid: CF1174F
tag: ['树链剖分']
---

# Ehab and the Big Finale

## 题目描述

This is an interactive problem.

You're given a tree consisting of $ n $ nodes, rooted at node $ 1 $ . A tree is a connected graph with no cycles.

We chose a hidden node $ x $ . In order to find this node, you can ask queries of two types:

- d $ u $ ( $ 1 \le u \le n $ ). We will answer with the distance between nodes $ u $ and $ x $ . The distance between two nodes is the number of edges in the shortest path between them.
- s $ u $ ( $ 1 \le u \le n $ ). We will answer with the second node on the path from $ u $ to $ x $ . However, there's a plot twist. If $ u $ is not an ancestor of $ x $ , you'll receive "Wrong answer" verdict!

Node $ a $ is called an ancestor of node $ b $ if $ a \ne b $ and the shortest path from node $ 1 $ to node $ b $ passes through node $ a $ . Note that in this problem a node is not an ancestor of itself.

Can you find $ x $ in no more than $ 36 $ queries? The hidden node is fixed in each test beforehand and does not depend on your queries.

## 输入格式

The first line contains the integer $ n $ ( $ 2 \le n \le 2 \cdot 10^5 $ ) — the number of nodes in the tree.

Each of the next $ n-1 $ lines contains two space-separated integers $ u $ and $ v $ ( $ 1 \le u,v \le n $ ) that mean there's an edge between nodes $ u $ and $ v $ . It's guaranteed that the given graph is a tree.

## 输出格式

To print the answer, print "! x" (without quotes).

Interaction

To ask a question, print it in one of the formats above:

- d $ u $ ( $ 1 \le u \le n $ ), or
- s $ u $ ( $ 1 \le u \le n $ ).

After each question, you should read the answer: either the distance or the second vertex on the path, as mentioned in the legend.

If we answer with $ -1 $ instead of a valid answer, that means you exceeded the number of queries, made an invalid query, or violated the condition in the second type of queries. Exit immediately after receiving $ -1 $ and you will see Wrong answer verdict. Otherwise, you can get an arbitrary verdict because your solution will continue to read from a closed stream.

After printing a query, do not forget to output end of line and flush the output. Otherwise, you will get Idleness limit exceeded. To do this, use:

- fflush(stdout) or cout.flush() in C++;
- System.out.flush() in Java;
- flush(output) in Pascal;
- stdout.flush() in Python;
- See the documentation for other languages.

Hacks:

The first line should contain two integers $ n $ and $ x $ ( $ 2 \le n \le 2 \cdot 10^5 $ , $ 1 \le x \le n $ ).

Each of the next $ n-1 $ lines should contain two integers $ u $ and $ v $ ( $ 1 \le u,v \le n $ ) that mean there is an edge between nodes $ u $ and $ v $ . The edges must form a tree.

## 说明/提示

In the first example, the hidden node is node $ 5 $ .

 ![](https://cdn.luogu.com.cn/upload/vjudge_pic/CF1174F/2fc09cdc0e97e7f39493296632ab302b06fdb975.png)We first ask about the distance between node $ x $ and node $ 2 $ . The answer is $ 3 $ , so node $ x $ is either $ 4 $ or $ 5 $ . We then ask about the second node in the path from node $ 3 $ to node $ x $ . Note here that node $ 3 $ is an ancestor of node $ 5 $ . We receive node $ 5 $ as the answer. Finally, we report that the hidden node is node $ 5 $ .

## 样例 #1

### 输入

```
5
1 2
1 3
3 4
3 5
3
5
```

### 输出

```
d 2
s 3
! 5
```



---

---
title: "Beard Graph"
layout: "post"
diff: 提高+/省选-
pid: CF165D
tag: ['线段树', '最近公共祖先 LCA', '树链剖分']
---

# Beard Graph

## 题目描述

Let's define a non-oriented connected graph of $ n $ vertices and $ n-1 $ edges as a beard, if all of its vertices except, perhaps, one, have the degree of 2 or 1 (that is, there exists no more than one vertex, whose degree is more than two). Let us remind you that the degree of a vertex is the number of edges that connect to it.

Let each edge be either black or white. Initially all edges are black.

You are given the description of the beard graph. Your task is to analyze requests of the following types:

- paint the edge number $ i $ black. The edge number $ i $ is the edge that has this number in the description. It is guaranteed that by the moment of this request the $ i $ -th edge is white
- paint the edge number $ i $ white. It is guaranteed that by the moment of this request the $ i $ -th edge is black
- find the length of the shortest path going only along the black edges between vertices $ a $ and $ b $ or indicate that no such path exists between them (a path's length is the number of edges in it)

The vertices are numbered with integers from $ 1 $ to $ n $ , and the edges are numbered with integers from $ 1 $ to $ n-1 $ .

## 输入格式

The first line of the input contains an integer $ n $ ( $ 2<=n<=10^{5} $ ) — the number of vertices in the graph. Next $ n-1 $ lines contain edges described as the numbers of vertices $ v_{i} $ , $ u_{i} $ ( $ 1<=v_{i},u_{i}<=n $ , $ v_{i}≠u_{i} $ ) connected by this edge. It is guaranteed that the given graph is connected and forms a beard graph, and has no self-loops or multiple edges.

The next line contains an integer $ m $ ( $ 1<=m<=3·10^{5} $ ) — the number of requests. Next $ m $ lines contain requests in the following form: first a line contains an integer $ type $ , which takes values ​​from $ 1 $ to $ 3 $ , and represents the request type.

If $ type=1 $ , then the current request is a request to paint the edge black. In this case, in addition to number $ type $ the line should contain integer $ id $ ( $ 1<=id<=n-1 $ ), which represents the number of the edge to paint.

If $ type=2 $ , then the current request is a request to paint the edge white, its form is similar to the previous request.

If $ type=3 $ , then the current request is a request to find the distance. In this case, in addition to $ type $ , the line should contain two integers $ a $ , $ b $ ( $ 1<=a,b<=n $ , $ a $ can be equal to $ b $ ) — the numbers of vertices, the distance between which must be found.

The numbers in all lines are separated by exactly one space. The edges are numbered in the order in which they are given in the input.

## 输出格式

For each request to "find the distance between vertices $ a $ and $ b $ " print the result. If there is no path going only along the black edges between vertices $ a $ and $ b $ , then print "-1" (without the quotes). Print the results in the order of receiving the requests, separate the numbers with spaces or line breaks.

## 说明/提示

In the first sample vertices $ 1 $ and $ 2 $ are connected with edge number $ 1 $ , and vertices $ 2 $ and $ 3 $ are connected with edge number $ 2 $ . Before the repainting edge number $ 2 $ each vertex is reachable from each one along the black edges. Specifically, the shortest path between $ 1 $ and $ 3 $ goes along both edges.

If we paint edge number $ 2 $ white, vertex $ 3 $ will end up cut off from other vertices, that is, no path exists from it to any other vertex along the black edges.

## 样例 #1

### 输入

```
3
1 2
2 3
7
3 1 2
3 1 3
3 2 3
2 2
3 1 2
3 1 3
3 2 3

```

### 输出

```
1
2
1
1
-1
-1

```

## 样例 #2

### 输入

```
6
1 5
6 4
2 3
3 5
5 6
6
3 3 4
2 5
3 2 6
3 1 2
2 3
3 3 1

```

### 输出

```
3
-1
3
2

```



---

---
title: "Chain Queries"
layout: "post"
diff: 提高+/省选-
pid: CF1975E
tag: ['线段树', '树链剖分']
---

# Chain Queries

## 题目描述

You are given a tree of $ n $ vertices numbered from $ 1 $ to $ n $ . Initially, all vertices are colored white or black.

You are asked to perform $ q $ queries:

- "u" — toggle the color of vertex $ u $ (if it was white, change it to black and vice versa).

After each query, you should answer whether all the black vertices form a chain. That is, there exist two black vertices such that the simple path between them passes through all the black vertices and only the black vertices. Specifically, if there is only one black vertex, they form a chain. If there are no black vertices, they do not form a chain.

## 输入格式

Each test contains multiple test cases. The first line contains the number of test cases $ t $ ( $ 1\leq t\leq 10^4 $ ). The description of the test cases follows.

The first line of each test case contains two integers $ n $ and $ q $ ( $ 1\leq n,q\leq 2\cdot 10^5 $ ).

The second line of each test case contains $ n $ integers $ c_1,c_2,\ldots,c_n $ ( $ c_i \in \{ \mathtt{0}, \mathtt{1} \} $ ) — the initial color of the vertices. $ c_i $ denotes the color of vertex $ i $ where $ \mathtt{0} $ denotes the color white, and $ \mathtt{1} $ denotes the color black.

Then $ n - 1 $ lines follow, each line contains two integers $ x_i $ and $ y_i $ ( $ 1 \le x_i,y_i \le n $ ), indicating an edge between vertices $ x_i $ and $ y_i $ . It is guaranteed that these edges form a tree.

The following $ q $ lines each contain an integer $ u_i $ ( $ 1 \le u_i \le n $ ), indicating the color of vertex $ u_i $ needs to be toggled.

It is guaranteed that the sum of $ n $ and $ q $ over all test cases respectively does not exceed $ 2\cdot 10^5 $ .

## 输出格式

For each query, output "Yes" if the black vertices form a chain, and output "No" otherwise.

You can output "Yes" and "No" in any case (for example, strings "yEs", "yes", "Yes" and "YES" will be recognized as a positive response).

## 说明/提示

In the second test case, the color of the vertices are as follows:

The initial tree:

 ![](https://cdn.luogu.com.cn/upload/vjudge_pic/CF1975E/d67482a066522c11f266b4eca3d7a1ef0055849d.png)The first query toggles the color of vertex $ 4 $ :

 ![](https://cdn.luogu.com.cn/upload/vjudge_pic/CF1975E/4a07e30139deb2cb81867b3706db8e9ec51e4318.png)The second query toggles the color of vertex $ 3 $ :

 ![](https://cdn.luogu.com.cn/upload/vjudge_pic/CF1975E/fd56e11f35468c4b51183822460fd341cde05e88.png)The third query toggles the color of vertex $ 2 $ :

 ![](https://cdn.luogu.com.cn/upload/vjudge_pic/CF1975E/f1f02d1c42e642ef8cfd2174f0e71d8955cb85ac.png)The fourth query toggles the color of vertex $ 5 $ :

 ![](https://cdn.luogu.com.cn/upload/vjudge_pic/CF1975E/72ebf27a994a252cc8de91446a4beacafa646ddb.png)

## 样例 #1

### 输入

```
2
2 1
1 0
1 2
1
5 4
1 0 0 0 0
1 2
1 3
1 5
3 4
4
3
2
5
```

### 输出

```
No
No
Yes
Yes
No
```

## 样例 #2

### 输入

```
4
5 3
1 1 1 1 1
3 5
2 5
3 4
1 5
1
1
1
4 4
0 0 0 0
1 2
2 3
1 4
1
2
3
2
1 1
1
1
1 1
0
1
```

### 输出

```
Yes
No
Yes
Yes
Yes
Yes
No
No
Yes
```



---

---
title: "Water Tree"
layout: "post"
diff: 提高+/省选-
pid: CF343D
tag: ['线段树', '树链剖分']
---

# Water Tree

## 题目描述

Mad scientist Mike has constructed a rooted tree, which consists of $ n $ vertices. Each vertex is a reservoir which can be either empty or filled with water.

The vertices of the tree are numbered from 1 to $ n $ with the root at vertex 1. For each vertex, the reservoirs of its children are located below the reservoir of this vertex, and the vertex is connected with each of the children by a pipe through which water can flow downwards.

Mike wants to do the following operations with the tree:

1. Fill vertex $ v $ with water. Then $ v $ and all its children are filled with water.
2. Empty vertex $ v $ . Then $ v $ and all its ancestors are emptied.
3. Determine whether vertex $ v $ is filled with water at the moment.

 Initially all vertices of the tree are empty.Mike has already compiled a full list of operations that he wants to perform in order. Before experimenting with the tree Mike decided to run the list through a simulation. Help Mike determine what results will he get after performing all the operations.

## 输入格式

The first line of the input contains an integer $ n $ ( $ 1<=n<=500000 $ ) — the number of vertices in the tree. Each of the following $ n-1 $ lines contains two space-separated numbers $ a_{i} $ , $ b_{i} $ ( $ 1<=a_{i},b_{i}<=n $ , $ a_{i}≠b_{i} $ ) — the edges of the tree.

The next line contains a number $ q $ ( $ 1<=q<=500000 $ ) — the number of operations to perform. Each of the following $ q $ lines contains two space-separated numbers $ c_{i} $ ( $ 1<=c_{i}<=3 $ ), $ v_{i} $ ( $ 1<=v_{i}<=n $ ), where $ c_{i} $ is the operation type (according to the numbering given in the statement), and $ v_{i} $ is the vertex on which the operation is performed.

It is guaranteed that the given graph is a tree.

## 输出格式

For each type 3 operation print 1 on a separate line if the vertex is full, and 0 if the vertex is empty. Print the answers to queries in the order in which the queries are given in the input.

## 样例 #1

### 输入

```
5
1 2
5 1
2 3
4 2
12
1 1
2 3
3 1
3 2
3 3
3 4
1 2
2 4
3 1
3 3
3 4
3 5

```

### 输出

```
0
0
0
1
0
1
0
1

```



---

---
title: "Minimum spanning tree for each edge"
layout: "post"
diff: 提高+/省选-
pid: CF609E
tag: ['生成树', '树链剖分']
---

# Minimum spanning tree for each edge

## 题目描述

# Minimum spanning tree for each edge

## 题面翻译


给你 $n$ 个点，$m$ 条边，如果对于一个最小生成树中要求必须包括第 $i(1 \le i \le m)$ 条边，那么最小生成树的权值总和最小是多少。


Connected undirected weighted graph without self-loops and multiple edges is given. Graph contains $ n $ vertices and $ m $ edges.

For each edge $ (u,v) $ find the minimal possible weight of the spanning tree that contains the edge $ (u,v) $ .

The weight of the spanning tree is the sum of weights of all edges included in spanning tree.

## 输入格式

第一行有两个整数 $n$ 和 $m$。

接下来 $m$ 行，每行有三个整数 $u$，$v$ 和 $w$ 表示一条权值为 $w$ 的边连接 $u$ 和 $v$。


First line contains two integers $ n $ and $ m $ ( $ 1<=n<=2·10^{5},n-1<=m<=2·10^{5} $ ) — the number of vertices and edges in graph.

Each of the next $ m $ lines contains three integers $ u_{i},v_{i},w_{i} $ ( $ 1<=u_{i},v_{i}<=n,u_{i}≠v_{i},1<=w_{i}<=10^{9} $ ) — the endpoints of the $ i $ -th edge and its weight.

## 输出格式

总共 $m$ 行，第 $i$ 行一个整数代表包括第 $i$ 条边时的最小权值和。


Print $ m $ lines. $ i $ -th line should contain the minimal possible weight of the spanning tree that contains $ i $ -th edge.

The edges are numbered from $ 1 $ to $ m $ in order of their appearing in input.

## 说明/提示

$1 \le n \le 2 \times 10^5,n-1 \le m\le 2 \times 10^5$

$1 \le u_i,v_i \le n,u_i \neq v_i,1 \le w_i \le 10^9$

## 样例 #1

### 输入

```
5 7
1 2 3
1 3 1
1 4 5
2 3 2
2 5 3
3 4 2
4 5 4

```

### 输出

```
9
8
11
8
8
8
9

```



---

