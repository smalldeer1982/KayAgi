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
title: "MST Company"
layout: "post"
diff: 提高+/省选-
pid: CF125E
tag: ['贪心', '排序', '生成树']
---

# MST Company

## 题目描述

The MST (Meaningless State Team) company won another tender for an important state reform in Berland.

There are $ n $ cities in Berland, some pairs of the cities are connected by roads. Each road has its price. One can move along any road in any direction. The MST team should carry out the repair works on some set of roads such that one can get from any city to any other one moving only along the repaired roads. Moreover, this set should contain exactly $ k $ capital roads (that is, the roads that start or finish in the capital). The number of the capital is 1.

As the budget has already been approved, the MST Company will profit by finding the set with minimum lengths of roads.

## 输入格式

The first input line contains three integers $ n,m,k $ ( $ 1<=n<=5000;0<=m<=10^{5};0<=k&lt;5000 $ ), where $ n $ is the number of cities in the country, $ m $ is the number of roads in the country, $ k $ is the number of capital roads in the required set. Then $ m $ lines enumerate the roads in question. Each road is specified by three numbers $ a_{i},b_{i},w_{i} $ ( $ 1<=a_{i},b_{i}<=n $ ; $ 1<=w<=10^{5} $ ), where $ a_{i},b_{i} $ are the numbers of cities linked by a road and $ w_{i} $ is its length.

Between each pair of cities no more than one road exists. There are no roads that start and finish in one city. The capital's number is 1.

## 输出格式

In the first line print the number of roads in the required set. The second line should contain the numbers of roads included in the sought set. If the sought set does not exist, print -1.

## 样例 #1

### 输入

```
4 5 2
1 2 1
2 3 1
3 4 1
1 3 3
1 4 2

```

### 输出

```
3
1 5 2 
```



---

---
title: "Railway System"
layout: "post"
diff: 提高+/省选-
pid: CF1687B
tag: ['生成树']
---

# Railway System

## 题目描述

As for the technology in the outside world, it is really too advanced for Gensokyo to even look up to.

—Yasaka Kanako, Symposium of Post-mysticism



This is an interactive problem.

Under the direct supervision of Kanako and the Moriya Shrine, the railway system of Gensokyo is finally finished. GSKR (Gensokyo Railways) consists of $ n $ stations with $ m $ bidirectional tracks connecting them. The $ i $ -th track has length $ l_i $ ( $ 1\le l_i\le 10^6 $ ). Due to budget limits, the railway system may not be connected, though there may be more than one track between two stations.

The value of a railway system is defined as the total length of its all tracks. The maximum (or minimum) capacity of a railway system is defined as the maximum (or minimum) value among all of the currently functional system's [full spanning forest](https://en.wikipedia.org/wiki/Spanning_tree#Spanning_forests).

In brief, full spanning forest of a graph is a spanning forest with the same connectivity as the given graph.

Kanako has a simulator only able to process no more than $ 2m $ queries. The input of the simulator is a string $ s $ of length $ m $ , consisting of characters 0 and/or 1. The simulator will assume the $ i $ -th track functional if $ s_i= $ 1. The device will then tell Kanako the maximum capacity of the system in the simulated state.

Kanako wants to know the the minimum capacity of the system with all tracks functional with the help of the simulator.

The structure of the railway system is fixed in advance. In other words, the interactor is not adaptive.

## 输入格式

The first and only line of input contains two integers $ n,m $ ( $ 2 \leq n \leq 200 $ , $ 1\le m \le 500 $ ) — the number of stations and tracks.

## 输出格式

Begin the interaction by reading $ n,m $ .

To make a query, print "? $ s $ " (without quotes, $ s $ is a string of length $ m $ , consisting of characters 0 and/or 1). Then you should read our response from standard input — the maximum capacity of the system in the simulated state.

If your program has made an invalid query or has run out of tries, the interactor will terminate immediately and your program will get a verdict Wrong answer.

To give the final answer, print "! $ L $ " (without the quotes, $ L $ is the minimum capacity of the system with all tracks functional). Note that giving this answer is not counted towards the limit of $ 2m $ queries.

After printing a query do not forget to output end of line and flush the output. Otherwise, you will get Idleness limit exceeded. To do this, use:

- fflush(stdout) or cout.flush() in C++;
- System.out.flush() in Java;
- flush(output) in Pascal;
- stdout.flush() in Python;
- see documentation for other languages.

Hacks

The first line of input must contain two integers $ n,m $ ( $ 2 \leq n \leq 200 $ , $ 1\le m \le 500 $ ) — the number of stations and tracks.

The next $ m $ lines of input must contain exactly $ 3 $ space-separated integers $ u_i $ , $ v_i $ , $ l_i $ ( $ 1\le u_i,v_i \le n $ , $ u_i\ne v_i $ , $ 1 \leq l_i \leq 10^6 $ ) — the endpoints and the length of the $ i $ -th track.

## 说明/提示

Here is the graph of the example, satisfying $ l_i=i $ .

 ![](https://cdn.luogu.com.cn/upload/vjudge_pic/CF1687B/91ed2595ccd5b28c792f8d64dc85c03cf1c73365.png)

## 样例 #1

### 输入

```
5 4

0

5

9

7
```

### 输出

```
? 0000

? 1110

? 1111

? 1101

! 7
```



---

---
title: "DFS Trees"
layout: "post"
diff: 提高+/省选-
pid: CF1707C
tag: ['生成树', '最近公共祖先 LCA', '差分']
---

# DFS Trees

## 题目描述

You are given a connected undirected graph consisting of $ n $ vertices and $ m $ edges. The weight of the $ i $ -th edge is $ i $ .

Here is a wrong algorithm of finding a [minimum spanning tree](https://en.wikipedia.org/wiki/Minimum_spanning_tree) (MST) of a graph:

```
<pre class="verbatim"><br></br>vis := an array of length n<br></br>s := a set of edges<br></br><br></br>function dfs(u):<br></br>    vis[u] := true<br></br>    iterate through each edge (u, v) in the order from smallest to largest edge weight<br></br>        if vis[v] = false<br></br>            add edge (u, v) into the set (s)<br></br>            dfs(v)<br></br><br></br>function findMST(u):<br></br>    reset all elements of (vis) to false<br></br>    reset the edge set (s) to empty<br></br>    dfs(u)<br></br>    return the edge set (s)<br></br>
```

Each of the calls findMST(1), findMST(2), ..., findMST(n) gives you a spanning tree of the graph. Determine which of these trees are minimum spanning trees.

## 输入格式

The first line of the input contains two integers $ n $ , $ m $ ( $ 2\le n\le 10^5 $ , $ n-1\le m\le 2\cdot 10^5 $ ) — the number of vertices and the number of edges in the graph.

Each of the following $ m $ lines contains two integers $ u_i $ and $ v_i $ ( $ 1\le u_i, v_i\le n $ , $ u_i\ne v_i $ ), describing an undirected edge $ (u_i,v_i) $ in the graph. The $ i $ -th edge in the input has weight $ i $ .

It is guaranteed that the graph is connected and there is at most one edge between any pair of vertices.

## 输出格式

You need to output a binary string $ s $ , where $ s_i=1 $ if findMST(i) creates an MST, and $ s_i = 0 $ otherwise.

## 说明/提示

Here is the graph given in the first example.

 ![](https://cdn.luogu.com.cn/upload/vjudge_pic/CF1707C/6866eea697370f9ef4baf895c7023c2ffb357c36.png)There is only one minimum spanning tree in this graph. A minimum spanning tree is $ (1,2),(3,5),(1,3),(2,4) $ which has weight $ 1+2+3+5=11 $ .

Here is a part of the process of calling findMST(1):

- reset the array vis and the edge set s;
- calling dfs(1);
- vis\[1\] := true;
- iterate through each edge $ (1,2),(1,3) $ ;
- add edge $ (1,2) $ into the edge set s, calling dfs(2): 
  - vis\[2\] := true
  - iterate through each edge $ (2,1),(2,3),(2,4) $ ;
  - because vis\[1\] = true, ignore the edge $ (2,1) $ ;
  - add edge $ (2,3) $ into the edge set s, calling dfs(3): 
      - ...

In the end, it will select edges $ (1,2),(2,3),(3,5),(2,4) $ with total weight $ 1+4+2+5=12>11 $ , so findMST(1) does not find a minimum spanning tree.

It can be shown that the other trees are all MSTs, so the answer is 01111.

## 样例 #1

### 输入

```
5 5
1 2
3 5
1 3
3 2
4 2
```

### 输出

```
01111
```

## 样例 #2

### 输入

```
10 11
1 2
2 5
3 4
4 2
8 1
4 5
10 5
9 5
8 2
5 7
4 6
```

### 输出

```
0011111011
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
title: "MST in Modulo Graph"
layout: "post"
diff: 提高+/省选-
pid: CF2081D
tag: ['生成树']
---

# MST in Modulo Graph

## 题目描述

给定一个包含 $n$ 个顶点的完全图，其中第 $i$ 个顶点的权值为 $p_i$。连接顶点 $x$ 和顶点 $y$ 的边的权重等于 $\operatorname{max}(p_x, p_y) \bmod \operatorname{min}(p_x, p_y)$。

请找出连接图中所有 $n$ 个顶点的 $n - 1$ 条边组成的集合的最小总权重。

## 输入格式

每个测试包含多个测试用例。第一行输入测试用例数量 $t$（$1 \le t \le 10^4$）。接下来描述每个测试用例。

每个测试用例的第一行包含一个整数 $n$（$1 \le n \le 5 \cdot 10^5$）。

每个测试用例的第二行包含 $n$ 个整数 $p_1, p_2, \ldots, p_n$（$1 \le p_i \le 5 \cdot 10^5$）。

保证所有测试用例的 $n$ 总和不超过 $5 \cdot 10^5$。
保证所有测试用例的 $\max(p_1,p_2,\ldots,p_n)$ 总和不超过 $5 \cdot 10^5$。

## 输出格式

对于每个测试用例，输出一个整数表示最小生成树的总权重。

## 说明/提示

第一个测试用例中，一种可能的连接方式是选择边 $(1, 2)$、$(1, 4)$、$(1, 5)$、$(2, 3)$。第一条边的权重为 $\operatorname{max}(p_1, p_2) \bmod \operatorname{min}(p_1, p_2)=4 \bmod 3 = 1$，其他所有边的权重均为 $0$。

翻译由 DeepSeek R1 完成

## 样例 #1

### 输入

```
4
5
4 3 3 4 4
10
2 10 3 2 9 9 4 6 4 6
12
33 56 48 41 89 73 99 150 55 100 111 130
7
11 45 14 19 19 8 10
```

### 输出

```
1
0
44
10
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

---
title: "Magic Matrix"
layout: "post"
diff: 提高+/省选-
pid: CF632F
tag: ['图论', '生成树']
---

# Magic Matrix

## 题目描述

You're given a matrix $ A $ of size $ n×n $ .

Let's call the matrix with nonnegative elements magic if it is symmetric (so $ a_{ij}=a_{ji} $ ), $ a_{ii}=0 $ and $ a_{ij}<=max(a_{ik},a_{jk}) $ for all triples $ i,j,k $ . Note that $ i,j,k $ do not need to be distinct.

Determine if the matrix is magic.

As the input/output can reach very huge size it is recommended to use fast input/output methods: for example, prefer to use scanf/printf instead of cin/cout in C++, prefer to use BufferedReader/PrintWriter instead of Scanner/System.out in Java.

## 输入格式

The first line contains integer $ n $ ( $ 1<=n<=2500 $ ) — the size of the matrix $ A $ .

Each of the next $ n $ lines contains $ n $ integers $ a_{ij} $ ( $ 0<=a_{ij}&lt;10^{9} $ ) — the elements of the matrix $ A $ .

Note that the given matrix not necessarily is symmetric and can be arbitrary.

## 输出格式

Print ''MAGIC" (without quotes) if the given matrix $ A $ is magic. Otherwise print ''NOT MAGIC".

## 样例 #1

### 输入

```
3
0 1 2
1 0 2
2 2 0

```

### 输出

```
MAGIC

```

## 样例 #2

### 输入

```
2
0 1
2 3

```

### 输出

```
NOT MAGIC

```

## 样例 #3

### 输入

```
4
0 1 2 3
1 0 3 4
2 3 0 5
3 4 5 0

```

### 输出

```
NOT MAGIC

```



---

---
title: "Mahmoud and Ehab and the xor-MST"
layout: "post"
diff: 提高+/省选-
pid: CF959E
tag: ['生成树', '进制', '前缀和']
---

# Mahmoud and Ehab and the xor-MST

## 题目描述

Ehab is interested in the bitwise-xor operation and the special graphs. Mahmoud gave him a problem that combines both. He has a complete graph consisting of $ n $ vertices numbered from $ 0 $ to $ n-1 $ . For all $ 0<=u<v<n $ , vertex $ u $ and vertex $ v $ are connected with an undirected edge that has weight ![](https://cdn.luogu.com.cn/upload/vjudge_pic/CF959E/31294aedffbec70e119efb89ca1f6d2afecc694a.png) (where ![](https://cdn.luogu.com.cn/upload/vjudge_pic/CF959E/bc47da33894a98df53134f30108d8405a90ea418.png) is the [bitwise-xor operation](https://en.wikipedia.org/wiki/Bitwise_operation#XOR)). Can you find the weight of the minimum spanning tree of that graph?

You can read about complete graphs in [https://en.wikipedia.org/wiki/Complete\_graph](https://en.wikipedia.org/wiki/Complete_graph)

You can read about the minimum spanning tree in [https://en.wikipedia.org/wiki/Minimum\_spanning\_tree](https://en.wikipedia.org/wiki/Minimum_spanning_tree)

The weight of the minimum spanning tree is the sum of the weights on the edges included in it.

## 输入格式

The only line contains an integer $ n $ $ (2<=n<=10^{12}) $ , the number of vertices in the graph.

## 输出格式

The only line contains an integer $ x $ , the weight of the graph's minimum spanning tree.

## 说明/提示

In the first sample: ![](https://cdn.luogu.com.cn/upload/vjudge_pic/CF959E/da1dd366c44de9a7fa58c6a7748f6a57cd6a4b83.png) The weight of the minimum spanning tree is 1+2+1=4.

## 样例 #1

### 输入

```
4

```

### 输出

```
4
```



---

