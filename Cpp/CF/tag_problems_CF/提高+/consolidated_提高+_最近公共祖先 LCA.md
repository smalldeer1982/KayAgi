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
title: "XOR Tree"
layout: "post"
diff: 提高+/省选-
pid: CF1709E
tag: ['树上启发式合并', '最近公共祖先 LCA']
---

# XOR Tree

## 题目描述

You are given a tree consisting of $ n $ vertices. A number is written on each vertex; the number on vertex $ i $ is equal to $ a_i $ .

Recall that a simple path is a path that visits each vertex at most once. Let the weight of the path be the bitwise XOR of the values written on vertices it consists of. Let's say that a tree is good if no simple path has weight $ 0 $ .

You can apply the following operation any number of times (possibly, zero): select a vertex of the tree and replace the value written on it with an arbitrary positive integer. What is the minimum number of times you have to apply this operation in order to make the tree good?

## 输入格式

The first line contains one integer $ n $ ( $ 1 \le n \le 2 \cdot 10^5 $ ) — the number of vertices.

The second line contains $ n $ integers $ a_1 $ , $ a_2 $ , ..., $ a_n $ ( $ 1 \le a_i < 2^{30} $ ) — the numbers written on vertices.

Then $ n - 1 $ lines follow, each containing two integers $ x $ and $ y $ ( $ 1 \le x, y \le n; x \ne y $ ) denoting an edge connecting vertex $ x $ with vertex $ y $ . It is guaranteed that these edges form a tree.

## 输出格式

Print a single integer — the minimum number of times you have to apply the operation in order to make the tree good.

## 说明/提示

In the first example, it is enough to replace the value on the vertex $ 1 $ with $ 13 $ , and the value on the vertex $ 4 $ with $ 42 $ .

## 样例 #1

### 输入

```
6
3 2 1 3 2 1
4 5
3 4
1 4
2 1
6 1
```

### 输出

```
2
```

## 样例 #2

### 输入

```
4
2 1 1 1
1 2
1 3
1 4
```

### 输出

```
0
```

## 样例 #3

### 输入

```
5
2 2 2 2 2
1 2
2 3
3 4
4 5
```

### 输出

```
2
```



---

---
title: "Fairy"
layout: "post"
diff: 提高+/省选-
pid: CF19E
tag: ['二分图', '最近公共祖先 LCA', '差分']
---

# Fairy

## 题目描述

Once upon a time there lived a good fairy A. One day a fine young man B came to her and asked to predict his future. The fairy looked into her magic ball and said that soon the fine young man will meet the most beautiful princess ever and will marry her. Then she drew on a sheet of paper $ n $ points and joined some of them with segments, each of the segments starts in some point and ends in some other point. Having drawn that picture, she asked the young man to erase one of the segments from the sheet. Then she tries to colour each point red or blue so, that there is no segment having points of the same colour as its ends. If she manages to do so, the prediction will come true. B wants to meet the most beautiful princess, that's why he asks you to help him. Find all the segments that will help him to meet the princess.

## 输入格式

The first input line contains two integer numbers: $ n $ — amount of the drawn points and $ m $ — amount of the drawn segments ( $ 1<=n<=10^{4},0<=m<=10^{4} $ ). The following $ m $ lines contain the descriptions of the segments. Each description contains two different space-separated integer numbers $ v $ , $ u $ ( $ 1<=v<=n,1<=u<=n $ ) — indexes of the points, joined by this segment. No segment is met in the description twice.

## 输出格式

In the first line output number $ k $ — amount of the segments in the answer. In the second line output $ k $ space-separated numbers — indexes of these segments in ascending order. Each index should be output only once. Segments are numbered from 1 in the input order.

## 样例 #1

### 输入

```
4 4
1 2
1 3
2 4
3 4

```

### 输出

```
4
1 2 3 4 
```

## 样例 #2

### 输入

```
4 5
1 2
2 3
3 4
4 1
1 3

```

### 输出

```
1
5 
```



---

---
title: "DFS Checker (Hard Version)"
layout: "post"
diff: 提高+/省选-
pid: CF2002D2
tag: ['最近公共祖先 LCA']
---

# DFS Checker (Hard Version)

## 题目描述

This is the hard version of the problem. In this version, you are given a generic tree and the constraints on $ n $ and $ q $ are higher. You can make hacks only if both versions of the problem are solved.

You are given a rooted tree consisting of $ n $ vertices. The vertices are numbered from $ 1 $ to $ n $ , and the root is the vertex $ 1 $ . You are also given a permutation $ p_1, p_2, \ldots, p_n $ of $ [1,2,\ldots,n] $ .

You need to answer $ q $ queries. For each query, you are given two integers $ x $ , $ y $ ; you need to swap $ p_x $ and $ p_y $ and determine if $ p_1, p_2, \ldots, p_n $ is a valid DFS order $ ^\dagger $ of the given tree.

Please note that the swaps are persistent through queries.

 $ ^\dagger $ A DFS order is found by calling the following $ \texttt{dfs} $ function on the given tree.

```
<pre class="lstlisting">```
dfs_order = []<br></br><br></br>function dfs(v):<br></br>    append v to the back of dfs_order<br></br>    pick an arbitrary permutation s of children of v<br></br>    for child in s:<br></br>        dfs(child)<br></br>dfs(1)<br></br>
```
```

Note that the DFS order is not unique.

## 输入格式

Each test contains multiple test cases. The first line contains the number of test cases $ t $ ( $ 1\le t\le10^4 $ ). The description of the test cases follows.

The first line of each test case contains two integers $ n $ , $ q $ ( $ 2\le n\le 3\cdot 10^5 $ , $ 2\le q\le 10^5 $ ) — the number of vertices in the tree and the number of queries.

The next line contains $ n-1 $ integers $ a_2,a_3,\ldots,a_n $ ( $ 1\le a_i<i $ ) — the parent of each vertex in the given tree.

The next line contains $ n $ integers $ p_1,p_2,\ldots,p_n $ ( $ 1\le p_i\le n $ , all $ p_i $ are distinct) — the initial permutation $ p $ .

The next $ q $ lines each contain two integers $ x $ , $ y $ ( $ 1\le x,y\le n,x\neq y $ ) — the positions of the elements to swap in the permutation.

It is guaranteed that the sum of all $ n $ does not exceed $ 3\cdot 10^5 $ , and the sum of all $ q $ does not exceed $ 10^5 $ .

## 输出格式

For each test case, print $ q $ lines corresponding to the $ q $ queries. For each query, output $ \texttt{YES} $ if there is a DFS order that exactly equals the current permutation, and output $ \texttt{NO} $ otherwise.

You can output $ \texttt{Yes} $ and $ \texttt{No} $ in any case (for example, strings $ \texttt{yEs} $ , $ \texttt{yes} $ , $ \texttt{Yes} $ , and $ \texttt{YES} $ will be recognized as a positive response).

## 说明/提示

In the first test case, the permutation $ p_1, p_2, \ldots, p_n $ after each modification is $ [1,3,2],[1,2,3],[3,2,1] $ , respectively. The first two permutations are valid DFS orders; the third is not a DFS order.

In the second test case, the permutation $ p_1, p_2, \ldots, p_n $ after each modification is $ [1,2,5,4,3,6,7],[1,3,5,4,2,6,7],[1,3,7,4,2,6,5],[1,3,7,6,2,4,5] $ , respectively.

## 样例 #1

### 输入

```
3
3 3
1 1
1 2 3
2 3
3 2
1 3
7 4
1 1 2 2 3 3
1 2 3 4 5 6 7
3 5
2 5
3 7
4 6
5 4
1 1 3 4
2 3 4 5 1
5 1
4 5
3 4
2 3
```

### 输出

```
YES
YES
NO
YES
NO
NO
YES
YES
NO
NO
YES
```



---

---
title: "Ain and Apple Tree"
layout: "post"
diff: 提高+/省选-
pid: CF2107E
tag: ['数学', '贪心', '最近公共祖先 LCA']
---

# Ain and Apple Tree

## 题目描述

如果我也被从苹果树上掉下的苹果砸中，我能变得像牛顿一样擅长物理吗？

为了更擅长物理，Ain 想建造一棵苹果树，这样她就能被树上的苹果砸中。她的苹果树有 $n$ 个节点，根节点为 $1$。她将苹果树的权重定义为 $\sum \limits_{i=1}^n \sum \limits_{j=i+1}^n \text{dep}(\operatorname{lca}(i,j))$。

这里，$\text{dep}(x)$ 定义为从节点 $1$ 到节点 $x$ 的唯一最短路径上的边数。$\operatorname{lca}(i, j)$ 定义为在路径 $(1, i)$ 和 $(1, j)$ 上同时出现且 $\text{dep}(x)$ 值最大的唯一节点 $x$。

Ain 从一些旧书中得知，牛顿的苹果树的权重大约是 $k$，但具体的值已经丢失了。

作为 Ain 的朋友，你想为她建造一棵有 $n$ 个节点的苹果树，且树的权重与 $k$ 的绝对差不超过 $1$，即 $|\text{权重} - k| \le 1$。如果无法满足这一条件，请报告这一情况。

## 输入格式

每个测试包含多个测试用例。第一行包含测试用例的数量 $t$（$1 \le t \le 10^4$）。接下来是测试用例的描述。

每个测试用例的第一行包含两个数字 $n, k$（$2 \le n \le 10^5$，$0 \le k \le 10^{15}$）。

保证所有测试用例的 $n$ 之和不超过 $2 \cdot 10^5$。

## 输出格式

对于每个测试用例，如果存在解，首先输出 `Yes`，否则输出 `No`。你可以使用任意大小写，例如 `YES` 和 `yEs` 也会被接受。

如果至少存在一个解，则输出 $n-1$ 行，每行包含两个数字 $u, v$（$1 \le u, v \le n$），表示苹果树的边。


## 说明/提示

在第一个测试用例中，我们可以验证权重为 $0$。这满足条件，因为 $k = 1$，所以绝对差仅为 $1$。

在第二个测试用例中，不存在解，因为没有 $2$ 个节点的树的权重为 $1$、$2$ 或 $3$。

翻译由 DeepSeek V3 完成

## 样例 #1

### 输入

```
5
2 1
2 2
4 0
5 7
5 5
```

### 输出

```
Yes
1 2
No
Yes
1 2
1 3
1 4
Yes
1 3
3 5
4 5
3 2
Yes
1 2
2 3
2 4
2 5
```



---

---
title: "New Year Tree"
layout: "post"
diff: 提高+/省选-
pid: CF379F
tag: ['广度优先搜索 BFS', '最近公共祖先 LCA', '树的直径']
---

# New Year Tree

## 题目描述

You are a programmer and you have a New Year Tree (not the traditional fur tree, though) — a tree of four vertices: one vertex of degree three (has number 1), connected with three leaves (their numbers are from 2 to 4).

On the New Year, programmers usually have fun. You decided to have fun as well by adding vertices to the tree. One adding operation looks as follows:

- First we choose some leaf of the tree with number $ v $ .
- Let's mark the number of vertices on the tree at this moment by variable $ n $ , then two vertexes are added to the tree, their numbers are $ n+1 $ and $ n+2 $ , also you get new edges, one between vertices $ v $ and $ n+1 $ and one between vertices $ v $ and $ n+2 $ .

Your task is not just to model the process of adding vertices to the tree, but after each adding operation print the diameter of the current tree. Come on, let's solve the New Year problem!

## 输入格式

The first line contains integer $ q $ $ (1<=q<=5·10^{5}) $ — the number of operations. Each of the next $ q $ lines contains integer $ v_{i} $ $ (1<=v_{i}<=n) $ — the operation of adding leaves to vertex $ v_{i} $ . Variable $ n $ represents the number of vertices in the current tree.

It is guaranteed that all given operations are correct.

## 输出格式

Print $ q $ integers — the diameter of the current tree after each operation.

## 样例 #1

### 输入

```
5
2
3
4
8
5

```

### 输出

```
3
4
4
5
6

```



---

---
title: "A and B and Lecture Rooms"
layout: "post"
diff: 提高+/省选-
pid: CF519E
tag: ['倍增', '最近公共祖先 LCA']
---

# A and B and Lecture Rooms

## 题目描述

A和B在准备参加编程比赛。

A和B学习的大学的房间由走廊连接。大学一共有$n$ 个房间，由$n-1$ 条走廊连接，房间的编号是从$1$ 到$n$ 的数字编号。

A和B在大学的某些房间里进行比赛。在每场比赛之后，他们会一起在一个房间里讨论问题。A和B希望这个讨论问题的房间到分别他们两个人比赛房间的距离相等。两个房间之间的距离指他们之间最短路的边数。

因为A和B每天都在不一样的房间里比赛，所以他们请求你告诉他们在接下来比赛的$m$ 天里可以用来讨论问题的房间有多少个？

## 输入格式

第一行包括整数$n$ ，其中$(1<=n<=10^5)$ ，表示房间数量。

接下来的$n-1$ 行描述所有的走廊。这$n-1$ 行中的第$i$ 行包括两个整数$a_i$ 和$b_i$ ，表示第$i$ 条走廊连接了房间$a_i$ 和$b_i$ 。

接下来的一行输入比赛的天数$m(1<=m<=10^5)$ 。

再接下来的$m$ 行，第$j$ 行包含两个整数$x_j$ 和$y_j(1<=x_j,y_j<=n)$ ，表示比赛的第$j$ 天A将在$x_j$ 房间比赛，B将在$y_j$ 房间比赛。

## 输出格式

在第$i(1<=i<=m)$ 行输出当天分别到A、B比赛的房间距离相等的房间数量。

感谢@lonelysir 提供的翻译

## 样例 #1

### 输入

```
4
1 2
1 3
2 4
1
2 3

```

### 输出

```
1

```

## 样例 #2

### 输入

```
4
1 2
2 3
2 4
2
1 2
1 3

```

### 输出

```
0
2

```



---

