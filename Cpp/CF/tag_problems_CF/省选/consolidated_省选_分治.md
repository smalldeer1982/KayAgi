---
title: "Omkar and Modes"
layout: "post"
diff: 省选/NOI-
pid: CF1372F
tag: ['分治']
---

# Omkar and Modes

## 题目描述

Ray lost his array and needs to find it by asking Omkar. Omkar is willing to disclose that the array has the following qualities:

1. The array has $ n $ ( $ 1 \le n \le 2 \cdot 10^5 $ ) elements.
2. Every element in the array $ a_i $ is an integer in the range $ 1 \le a_i \le 10^9. $
3. The array is sorted in nondecreasing order.

Ray is allowed to send Omkar a series of queries. A query consists of two integers, $ l $ and $ r $ such that $ 1 \le l       \le r \le n $ . Omkar will respond with two integers, $ x $ and $ f $ . $ x $ is the mode of the subarray from index $ l $ to index $ r $ inclusive. The mode of an array is defined by the number that appears the most frequently. If there are multiple numbers that appear the most number of times, the smallest such number is considered to be the mode. $ f $ is the amount of times that $ x $ appears in the queried subarray.

The array has $ k $ ( $ 1 \le k \le \min(25000,n) $ ) distinct elements. However, due to Ray's sins, Omkar will not tell Ray what $ k $ is. Ray is allowed to send at most $ 4k $ queries.

Help Ray find his lost array.

## 输入格式

The only line of the input contains a single integer $ n $ ( $ 1 \le n \le 2 \cdot 10^5 $ ), which equals to the length of the array that you are trying to find.

## 输出格式

The interaction starts with reading $ n $ .

Then you can make one type of query:

- " $ ? \enspace l \enspace r $ " ( $ 1 \le l \le         r \le n $ ) where $ l $ and $ r $ are the bounds of the subarray that you wish to query.

The answer to each query will be in the form " $ x \enspace       f $ " where $ x $ is the mode of the subarray and $ f $ is the number of times $ x $ appears in the subarray.

- $ x $ satisfies ( $ 1 \leq x \leq 10^9 $ ).
- $ f $ satisfies ( $ 1 \leq f \leq r-l+1 $ ).
- If you make more than $ 4k $ queries or violate the number range in the query, you will get an output "-1."
- If you terminate after receiving the response " $ -1 $ ", you will get the "Wrong answer" verdict. Otherwise you can get an arbitrary verdict because your solution will continue to read from a closed stream.

To output your answer, print:

- " $ ! \enspace a_1 \enspace a_2 \enspace \ldots         \enspace a_{n-1} \enspace a_n $ " which is an exclamation point followed by the array with a space between every element.

And quit after that. This query is not counted towards the $ 4k $ queries limit.

After printing a query do not forget to output end of line and flush the output. Otherwise, you will get Idleness limit exceeded. To do this, use:

- fflush(stdout) or cout.flush() in C++;
- System.out.flush() in Java;
- flush(output) in Pascal;
- stdout.flush() in Python;
- see documentation for other languages.

 Hack Format

To hack, output $ 1 $ integer on the first line, $ n $ ( $ 1       \le n \le 2 \cdot 10^5 $ ). On the second line output $ n $ integers $ a_1, a_2, \ldots, a_{n-1}, a_n $ separated by a space such that there are at most $ 25000 $ distinct numbers and $ a_j \le a_{j+1} $ for all $ j $ from $ 1 $ to $ n-1 $ .

## 说明/提示

The first query is $ l=1 $ and $ r=6 $ . The mode is $ 2 $ , and $ 2 $ appears $ 2 $ times, so $ x=2 $ and $ f=2 $ . Note that $ 3 $ also appears two times, but $ 2 $ is outputted because $ 2 $ is smaller.

The second query is $ l=1 $ and $ r=3 $ . The mode is $ 2 $ and $ 2 $ appears twice in the subarray with indices $ [1,3] $ .

The third query is $ l=4 $ and $ r=6 $ . The mode is $ 3 $ and $ 3 $ appears twice in the subarray with indices $ [4,6] $ .

The fourth query is $ l=3 $ and $ r=4 $ . The mode is $ 2 $ , which appears once in the subarray with indices $ [3,4] $ . Note that $ 3 $ also appears once in that range, but $ 2 $ is smaller than $ 3 $ .

## 样例 #1

### 输入

```
6

2 2

2 2

3 2

2 1
```

### 输出

```
? 1 6

? 1 3

? 4 6

? 3 4

! 1 2 2 3 3 4
```



---

---
title: "Set"
layout: "post"
diff: 省选/NOI-
pid: CF1975F
tag: ['分治']
---

# Set

## 题目描述

Define the binary encoding of a finite set of natural numbers $ T \subseteq \{0,1,2,\ldots\} $ as $ f(T) = \sum\limits_{i \in T} 2^i $ . For example, $ f(\{0,2\}) = 2^0 + 2^2 = 5 $ and $ f(\{\}) = 0 $ . Notice that $ f $ is a bijection from all such sets to all non-negative integers. As such, $ f^{-1} $ is also defined.

You are given an integer $ n $ along with $ 2^n-1 $ sets $ V_1,V_2,\ldots,V_{2^n-1} $ .

Find all sets $ S $ that satisfy the following constraint:

- $ S \subseteq \{0,1,\ldots,n-1\} $ . Note that $ S $ can be empty.
- For all non-empty subsets $ T \subseteq \{0,1,\ldots,n-1\} $ , $ |S \cap T| \in V_{f(T)} $ .

Due to the large input and output, both input and output will be given in terms of binary encodings of the sets.

## 输入格式

The first line of input contains a single integer $ n $ ( $ 1 \leq n \leq 20 $ ).

The second line of input contains $ 2^n-1 $ integers $ v_1,v_2,\ldots,v_{2^n-1} $ ( $ 0 \leq v_i < 2^{n+1} $ ) — the sets $ V_i $ given in their binary encoding where $ V_i = f^{-1}(v_i) $ .

## 输出格式

The first line of output should contain an integer $ k $ indicating the number of possible $ S $ .

In the following $ k $ lines, you should output $ f(S) $ for all possible $ S $ in increasing order.

## 说明/提示

In the first test case, one possible $ S $ is $ f^{-1}(3) = \{0,1\} $ . All the non-empty subsets $ T \subseteq \{0,1,2\} $ and the corresponding $ |S \cap T| $ , $ f(T) $ and $ V_f(T) $ are as follows:

  $ T $  $ |S\cap T| $  $ f(T) $  $ V_{f(T)} $  $ \{0\} $  $ 1 $  $ 1 $  $ \{0,1,2,3\} $  $ \{1\} $  $ 1 $  $ 2 $  $ \{0,1,2,3\} $  $ \{2\} $  $ 0 $  $ 4 $  $ \{0,1,2,3\} $  $ \{0,1\} $  $ 2 $  $ 3 $  $ \{0,1,2,3\} $  $ \{0,2\} $  $ 1 $  $ 5 $  $ \{0,1,2,3\} $  $ \{1,2\} $  $ 1 $  $ 6 $  $ \{0,1,2,3\} $  $ \{0,1,2\} $  $ 2 $  $ 7 $  $ \{2,3\} $

## 样例 #1

### 输入

```
3
15 15 15 15 15 15 12
```

### 输出

```
4
3
5
6
7
```

## 样例 #2

### 输入

```
5
63 63 63 63 6 63 63 63 63 63 63 5 63 63 63 63 63 63 8 63 63 63 63 2 63 63 63 63 63 63 63
```

### 输出

```
1
19
```



---

---
title: "Spinning Round (Easy Version)"
layout: "post"
diff: 省选/NOI-
pid: CF1987G1
tag: ['分治']
---

# Spinning Round (Easy Version)

## 题目描述

This is the easy version of the problem. The only difference between the two versions are the allowed characters in $ s $ . In the easy version, $ s $ only contains the character ?. You can make hacks only if both versions of the problem are solved.

You are given a permutation $ p $ of length $ n $ . You are also given a string $ s $ of length $ n $ , consisting only of the character ?.

For each $ i $ from $ 1 $ to $ n $ :

- Define $ l_i $ as the largest index $ j < i $ such that $ p_j > p_i $ . If there is no such index, $ l_i := i $ .
- Define $ r_i $ as the smallest index $ j > i $ such that $ p_j > p_i $ . If there is no such index, $ r_i := i $ .

Initially, you have an undirected graph with $ n $ vertices (numbered from $ 1 $ to $ n $ ) and no edges. Then, for each $ i $ from $ 1 $ to $ n $ , add one edge to the graph:

- If $ s_i = $ L, add the edge $ (i, l_i) $ to the graph.
- If $ s_i = $ R, add the edge $ (i, r_i) $ to the graph.
- If $ s_i = $ ?, either add the edge $ (i, l_i) $ or the edge $ (i, r_i) $ to the graph at your choice.

Find the maximum possible diameter $ ^{\text{∗}} $ over all connected graphs that you can form. Output $ -1 $ if it is not possible to form any connected graphs.

 $ ^{\text{∗}} $ Let $ d(s, t) $ denote the smallest number of edges on any path between $ s $ and $ t $ .

The diameter of the graph is defined as the maximum value of $ d(s, t) $ over all pairs of vertices $ s $ and $ t $ .

## 输入格式

Each test contains multiple test cases. The first line of input contains a single integer $ t $ ( $ 1 \le t \le 2 \cdot 10^4 $ ) — the number of test cases. The description of the test cases follows.

The first line of each test case contains a single integer $ n $ ( $ 2 \le n \le 4 \cdot 10^5 $ ) — the length of the permutation $ p $ .

The second line of each test case contains $ n $ integers $ p_1,p_2,\ldots, p_n $ ( $ 1 \le p_i \le n $ ) — the elements of $ p $ , which are guaranteed to form a permutation.

The third line of each test case contains a string $ s $ of length $ n $ . It is guaranteed that it consists only of the character ?.

It is guaranteed that the sum of $ n $ over all test cases does not exceed $ 4 \cdot 10^5 $ .

## 输出格式

For each test case, output the maximum possible diameter over all connected graphs that you form, or $ -1 $ if it is not possible to form any connected graphs.

## 说明/提示

In the first test case, here are some possible connected graphs that you can form (the labels are indices):

 ![](https://cdn.luogu.com.cn/upload/vjudge_pic/CF1987G1/b9e604b93005a6fc948b7a3b538eda48ad94326a.png)![](https://cdn.luogu.com.cn/upload/vjudge_pic/CF1987G1/1015454202f1913e51db8d5cb7f5b2c4acb62524.png)![](https://cdn.luogu.com.cn/upload/vjudge_pic/CF1987G1/910cf619de9f1bf38bbce8c5e1df95915cc19272.png)In the second test case, the only connected graph has a diameter of $ 1 $ .

## 样例 #1

### 输入

```
8
5
2 1 4 3 5
?????
2
1 2
??
3
3 1 2
???
7
5 3 1 6 4 2 7
???????
5
5 2 1 3 4
?????
6
6 2 3 4 5 1
??????
8
1 7 5 6 2 8 4 3
????????
12
6 10 7 1 8 5 12 2 11 3 4 9
????????????
```

### 输出

```
4
1
2
6
4
5
5
8
```



---

---
title: "Bottle Arrangement"
layout: "post"
diff: 省选/NOI-
pid: CF2041J
tag: ['动态规划 DP', '分治', '扫描线', '差分']
---

# Bottle Arrangement

## 题目描述

![](https://cdn.luogu.com.cn/upload/vjudge_pic/CF2041J/a93240ff9d94fb996cc13c493b1008f9c0801598.png) Image generated by ChatGPT 4o.Mayaw works in a renowned Epah (aboriginal Taiwanese millet wine; Epah is the Pangcah term for aboriginal Taiwanese millet wine, named in the language of the Pangcah people, the largest Indigenous group in Taiwan) bar in the Fata'an Village. To showcase the depth of its collections, the bar has a two-row wine rack where each row can fit exactly $ n $ bottles. There are already $ n $ bottles placed on the back row of the rack, where the $ i $ -th bottle from left has height $ a_i $ . The owner of the bar has another $ n $ bottles with distinct heights $ b_1, \ldots, b_n $ that he would like Mayaw to put on the first row. To ensure that all bottles on the rack are visible, the owner requires that each bottle on the back row should not be blocked by the one put in front of it. That is, if a bottle of height $ h $ is put on the $ i $ -th spot (from left) in the first row, then $ h $ must be less than $ a_i $ . However, not all such arrangements are good for the owner. To pay tributes to the Maxi Mountain nearby, he additionally demands that the bottles in the front row should display a mountain-like shape. In particular, the heights of the bottles, when listing from left to right, should form a sequence that is first (non-strictly) increasing and then (non-strictly) decreasing.

Unfortunately, sometimes it is impossible to achieve owner's requirements. That is why Mayaw is also allowed to slightly reduce a bottle's height by removing its cap that has a height of $ 1 $ . In other words, after the removal of the cap, the height of the bottle decreases by exactly $ 1 $ . Of course, exposing the Epah inside the bottle to the open air is detrimental to its quality, and therefore it is desirable to remove as few bottle caps as possible.

Can you help Mayaw determine the minimum number of caps needed to be removed so that he can arrange the bottles in a way that satisfies the owner's requirements? Note that the positions of the bottles in the back row are fixed and Mayaw is not allowed to modify them.

## 输入格式

The first line contains an integer $ n $ which represents the number of bottles in each row. The second line contains $ n $ integers $ a_1, \ldots, a_n $ , the height of the bottles in the back row. The third line contains $ n $ distinct integers $ b_1, \ldots, b_n $ , the height of the bottles in the front row.

- $ 1 \leq n \leq 5 \times 10^5 $
- $ 1 \leq a_i, b_i \leq 10^9 $
- All $ b_i $ 's are distinct.

## 输出格式

Output the minimum number of bottle caps needed to be removed so that Mayaw can arrange the bottles in the desired way. If it is impossible to achieve that (regardless of the number of caps removed), output -1 instead.

## 样例 #1

### 输入

```
5
2 4 6 5 4
1 2 3 4 5
```

### 输出

```
0
```

## 样例 #2

### 输入

```
5
2 3 6 5 4
1 2 3 4 5
```

### 输出

```
0
```

## 样例 #3

### 输入

```
5
6 2 6 6 6
1 2 3 4 5
```

### 输出

```
1
```

## 样例 #4

### 输入

```
5
7 2 7 7 7
1 3 4 5 6
```

### 输出

```
-1
```

## 样例 #5

### 输入

```
10
18 20 16 18 16 10 13 6 4 10
19 10 9 15 4 16 6 12 3 17
```

### 输出

```
4
```



---

---
title: "Graph Inclusion"
layout: "post"
diff: 省选/NOI-
pid: CF2069F
tag: ['线段树', '线段树分治']
---

# Graph Inclusion

## 题目描述

在无向图中，连通分量（connected component）定义为满足以下条件的顶点集合 $S$：
- 对于 $S$ 中的任意顶点对 $(u, v)$，存在从 $u$ 到 $v$ 的路径；
- 不存在属于 $S$ 外部的顶点与 $S$ 内部的顶点之间存在路径。

例如，下图中的图有三个连通分量：$\{1, 3, 7, 8\}$、$\{2\}$、$\{4, 5, 6\}$。

![](https://cdn.luogu.com.cn/upload/vjudge_pic/CF2069F/c7da17be18c82b1f53abfd338e215a533856c956.png)

我们称图 $A$ 包含（include）图 $B$，当且仅当图 $B$ 的每个连通分量都是图 $A$ 某个连通分量的子集。

给定两个图 $A$ 和 $B$，它们均包含 $n$ 个顶点（编号为 $1$ 到 $n$）。初始时两个图都没有边。你需要处理以下两种类型的查询：
- 向其中一个图添加一条边；
- 从其中一个图中删除一条边。

在每次查询后，你需要计算为了使图 $A$ 包含图 $B$ 所需要向图 $A$ 添加的最小边数，并输出该数值。注意这些边不会被实际添加，仅需计算数量。

## 输入格式

第一行包含两个整数 $n$ 和 $q$（$2 \le n \le 4 \cdot 10^5$；$1 \le q \le 4 \cdot 10^5$）——分别表示顶点数和查询数。

接下来 $q$ 行描述查询，其中第 $i$ 行描述第 $i$ 个查询。查询描述以一个字符 $c_i$（A 或 B）开头，表示该查询作用的图。接着是两个整数 $x_i$ 和 $y_i$（$1 \le x_i, y_i \le n$；$x_i \ne y_i$）。如果对应图中存在边 $(x_i, y_i)$，则删除该边；否则添加该边。

## 输出格式

对于每个查询，输出一个整数——为使图 $A$ 包含图 $B$ 所需向图 $A$ 添加的最小边数。

翻译由 DeepSeek R1 完成

## 样例 #1

### 输入

```
6 9
A 2 3
B 1 3
A 2 1
A 3 2
B 5 6
A 6 5
A 3 4
A 4 2
A 4 3
```

### 输出

```
0
1
0
1
2
1
1
0
1
```



---

---
title: "Modulo 3"
layout: "post"
diff: 省选/NOI-
pid: CF2104G
tag: ['并查集', '数论', '线段树分治']
---

# Modulo 3

## 题目描述

给定基环内向森林，每个点有且仅有一条出边 $g_i$，可能有自环。

所有点的初始颜色均为 $1$，你可以执行如下操作**任意次**（可以为零次）：

- 选择一个顶点 $u \in [1,n]$，再选择一种颜色 $c \in [1,k]$，将 $u$ 能到达的所有点（包括 $u$ 本身）染成颜色 $c$。

你需要求出，最终能形成的不同的图的数量，**答案对 $3$ 取模**。

两个图不同，当且仅当存在一个编号为 $i$ 的节点，它的颜色在两图中不同。

现在有 $q$ 次修改操作，每次给定 $x,y,k$：

- 将 $g_x$ 修改为 $y$。
- 对于本次输入的 $k$，输出答案，对 $3$ 取模。

对 $g_x$ 的修改操作是永久的，对后面有影响。但是在每次询问答案时，所有顶点的初始颜色都是 $1$。

## 输入格式

第一行包含两个整数 $n$ 和 $q$。

第二行包含 $n$ 个整数 $g_1, g_2, \dots, g_n$。

接下来是 $q$ 行，第 $i$ 行包含三个整数 $x_i$ 、 $y_i$ 和 $k_i$ （$1 \le k_i \le 10^9$ ）。

## 输出格式

共 $q$ 行，每行一个在 $[0,3)$ 的整数。

## 说明/提示

$1 \le n, q \le 2 \times 10^5$。

## 样例 #1

### 输入

```
4 5
2 3 1 4
4 3 1
2 1 2
3 4 3
4 1 5
2 4 4
```

### 输出

```
1
2
0
2
1
```

## 样例 #2

### 输入

```
8 10
7 4 6 8 7 7 1 4
1 7 5
2 3 3
8 6 1
3 1 3
7 2 5
5 2 4
2 7 4
4 6 5
5 2 3
4 5 1
```

### 输出

```
1
0
1
0
2
1
1
2
0
1
```



---

---
title: "Close Vertices"
layout: "post"
diff: 省选/NOI-
pid: CF293E
tag: ['点分治', '树状数组', '概率论']
---

# Close Vertices

## 题目描述

You've got a weighted tree, consisting of $ n $ vertices. Each edge has a non-negative weight. The length of the path between any two vertices of the tree is the number of edges in the path. The weight of the path is the total weight of all edges it contains.

Two vertices are close if there exists a path of length at most $ l $ between them and a path of weight at most $ w $ between them. Count the number of pairs of vertices $ v,u $ $ (v&lt;u) $ , such that vertices $ v $ and $ u $ are close.

## 输入格式

The first line contains three integers $ n $ , $ l $ and $ w $ $ (1<=n<=10^{5},1<=l<=n,0<=w<=10^{9}) $ . The next $ n-1 $ lines contain the descriptions of the tree edges. The $ i $ -th line contains two integers $ p_{i},w_{i} $ $ (1<=p_{i}&lt;(i+1),0<=w_{i}<=10^{4}) $ , that mean that the $ i $ -th edge connects vertex $ (i+1) $ and $ p_{i} $ and has weight $ w_{i} $ .

Consider the tree vertices indexed from 1 to $ n $ in some way.

## 输出格式

Print a single integer — the number of close pairs.

Please, do not use the %lld specifier to read or write 64-bit integers in С++. It is preferred to use the cin, cout streams or the %I64d specifier.

## 样例 #1

### 输入

```
4 4 6
1 3
1 4
1 3

```

### 输出

```
4

```

## 样例 #2

### 输入

```
6 2 17
1 3
2 5
2 13
1 6
5 9

```

### 输出

```
9

```



---

---
title: "Tricky Function"
layout: "post"
diff: 省选/NOI-
pid: CF429D
tag: ['枚举', '分治', '未知标签296']
---

# Tricky Function

## 题目描述

Iahub and Sorin are the best competitive programmers in their town. However, they can't both qualify to an important contest. The selection will be made with the help of a single problem. Blatnatalag, a friend of Iahub, managed to get hold of the problem before the contest. Because he wants to make sure Iahub will be the one qualified, he tells Iahub the following task.

You're given an (1-based) array $ a $ with $ n $ elements. Let's define function $ f(i,j) $ $ (1<=i,j<=n) $ as $ (i-j)^{2}+g(i,j)^{2} $ . Function g is calculated by the following pseudo-code:

```
int g(int i, int j) {
    int sum = 0;
    for (int k = min(i, j) + 1; k <= max(i, j); k = k + 1)
        sum = sum + a[k];
    return sum;
}
```
Find a value $ min_{i≠j}  f(i,j) $ .

Probably by now Iahub already figured out the solution to this problem. Can you?

## 输入格式

The first line of input contains a single integer $ n $ ( $ 2<=n<=100000 $ ). Next line contains $ n $ integers $ a[1] $ , $ a[2] $ , ..., $ a[n] $ ( $ -10^{4}<=a[i]<=10^{4} $ ).

## 输出格式

Output a single integer — the value of $ min_{i≠j}  f(i,j) $ .

## 样例 #1

### 输入

```
4
1 0 0 -1

```

### 输出

```
1

```

## 样例 #2

### 输入

```
2
1 -1

```

### 输出

```
2

```



---

---
title: "Painting Edges"
layout: "post"
diff: 省选/NOI-
pid: CF576E
tag: ['线段树', '分治', '栈']
---

# Painting Edges

## 题目描述

Note the unusual memory limit for this problem.

You are given an undirected graph consisting of $ n $ vertices and $ m $ edges. The vertices are numbered with integers from $ 1 $ to $ n $ , the edges are numbered with integers from $ 1 $ to $ m $ . Each edge can be unpainted or be painted in one of the $ k $ colors, which are numbered with integers from $ 1 $ to $ k $ . Initially, none of the edges is painted in any of the colors.

You get queries of the form "Repaint edge $ e_{i} $ to color $ c_{i} $ ". At any time the graph formed by the edges of the same color must be bipartite. If after the repaint this condition is violated, then the query is considered to be invalid and edge $ e_{i} $ keeps its color. Otherwise, edge $ e_{i} $ is repainted in color $ c_{i} $ , and the query is considered to valid.

Recall that the graph is called bipartite if the set of its vertices can be divided into two parts so that no edge connected vertices of the same parts.

For example, suppose you are given a triangle graph, that is a graph with three vertices and edges $ (1,2) $ , $ (2,3) $ and $ (3,1) $ . Suppose that the first two edges are painted color $ 1 $ , and the third one is painted color $ 2 $ . Then the query of "repaint the third edge in color $ 1 $ " will be incorrect because after its execution the graph formed by the edges of color $ 1 $ will not be bipartite. On the other hand, it is possible to repaint the second edge in color $ 2 $ .

You receive $ q $ queries. For each query, you should either apply it, and report that the query is valid, or report that the query is invalid.

## 输入格式

The first line contains integers $ n $ , $ m $ , $ k $ , $ q $ ( $ 2<=n<=5·10^{5} $ , $ 1<=m,q<=5·10^{5} $ , $ 1<=k<=50 $ ) — the number of vertices, the number of edges, the number of colors and the number of queries.

Then follow $ m $ edges of the graph in the form $ a_{i} $ , $ b_{i} $ ( $ 1<=a_{i},b_{i}<=n $ ).

Then follow $ q $ queries of the form $ e_{i} $ , $ c_{i} $ ( $ 1<=e_{i}<=m $ , $ 1<=c_{i}<=k $ ).

It is guaranteed that the graph doesn't contain multiple edges and loops.

## 输出格式

For each query print "YES" (without the quotes), if it is valid, or "NO" (without the quotes), if this query destroys the bipartivity of the graph formed by the edges of some color.

## 样例 #1

### 输入

```
3 3 2 5
1 2
2 3
1 3
1 1
2 1
3 2
3 1
2 2

```

### 输出

```
YES
YES
YES
NO
YES

```



---

---
title: "String Set Queries"
layout: "post"
diff: 省选/NOI-
pid: CF710F
tag: ['分治', '哈希 hashing', '分块', '字典树 Trie', 'AC 自动机', 'KMP 算法']
---

# String Set Queries

## 题目描述

You should process $ m $ queries over a set $ D $ of strings. Each query is one of three kinds:

1. Add a string $ s $ to the set $ D $ . It is guaranteed that the string $ s $ was not added before.
2. Delete a string $ s $ from the set $ D $ . It is guaranteed that the string $ s $ is in the set $ D $ .
3. For the given string $ s $ find the number of occurrences of the strings from the set $ D $ . If some string $ p $ from $ D $ has several occurrences in $ s $ you should count all of them.

Note that you should solve the problem in online mode. It means that you can't read the whole input at once. You can read each query only after writing the answer for the last query of the third type. Use functions fflush in C++ and BufferedWriter.flush in Java languages after each writing in your program.

## 输入格式

The first line contains integer $ m $ ( $ 1<=m<=3·10^{5} $ ) — the number of queries.

Each of the next $ m $ lines contains integer $ t $ ( $ 1<=t<=3 $ ) and nonempty string $ s $ — the kind of the query and the string to process. All strings consist of only lowercase English letters.

The sum of lengths of all strings in the input will not exceed $ 3·10^{5} $ .

## 输出格式

For each query of the third kind print the only integer $ c $ — the desired number of occurrences in the string $ s $ .

## 样例 #1

### 输入

```
5
1 abc
3 abcabc
2 abc
1 aba
3 abababc

```

### 输出

```
2
2

```

## 样例 #2

### 输入

```
10
1 abc
1 bcd
1 abcd
3 abcd
2 abcd
3 abcd
2 bcd
3 abcd
2 abc
3 abcd

```

### 输出

```
3
2
1
0

```



---

---
title: "Till I Collapse"
layout: "post"
diff: 省选/NOI-
pid: CF786C
tag: ['二分', '根号分治']
---

# Till I Collapse

## 题目描述

Rick and Morty want to find MR. PBH and they can't do it alone. So they need of Mr. Meeseeks. They Have generated $ n $ Mr. Meeseeks, standing in a line numbered from $ 1 $ to $ n $ . Each of them has his own color. $ i $ -th Mr. Meeseeks' color is $ a_{i} $ .

Rick and Morty are gathering their army and they want to divide Mr. Meeseeks into some squads. They don't want their squads to be too colorful, so each squad should have Mr. Meeseeks of at most $ k $ different colors. Also each squad should be a continuous subarray of Mr. Meeseeks in the line. Meaning that for each $ 1<=i<=e<=j<=n $ , if Mr. Meeseeks number $ i $ and Mr. Meeseeks number $ j $ are in the same squad then Mr. Meeseeks number $ e $ should be in that same squad.

 ![](https://cdn.luogu.com.cn/upload/vjudge_pic/CF786C/f2b873f46d1ce1d5117f05fee6c23499da101533.png)Also, each squad needs its own presidio, and building a presidio needs money, so they want the total number of squads to be minimized.

Rick and Morty haven't finalized the exact value of $ k $ , so in order to choose it, for each $ k $ between $ 1 $ and $ n $ (inclusive) need to know the minimum number of presidios needed.

## 输入格式

The first line of input contains a single integer $ n $ ( $ 1<=n<=10^{5} $ ) — number of Mr. Meeseeks.

The second line contains $ n $ integers $ a_{1},a_{2},...,a_{n} $ separated by spaces ( $ 1<=a_{i}<=n $ ) — colors of Mr. Meeseeks in order they standing in a line.

## 输出格式

In the first and only line of input print $ n $ integers separated by spaces. $ i $ -th integer should be the minimum number of presidios needed if the value of $ k $ is $ i $ .

## 说明/提示

For the first sample testcase, some optimal ways of dividing army into squads for each $ k $ are:

1. $ [1],[3],[4],[3,3] $
2. $ [1],[3,4,3,3] $
3. $ [1,3,4,3,3] $
4. $ [1,3,4,3,3] $
5. $ [1,3,4,3,3] $

For the second testcase, some optimal ways of dividing army into squads for each $ k $ are:

1. $ [1],[5],[7],[8],[1],[7],[6],[1] $
2. $ [1,5],[7,8],[1,7],[6,1] $
3. $ [1,5,7],[8],[1,7,6,1] $
4. $ [1,5,7,8],[1,7,6,1] $
5. $ [1,5,7,8,1,7,6,1] $
6. $ [1,5,7,8,1,7,6,1] $
7. $ [1,5,7,8,1,7,6,1] $
8. $ [1,5,7,8,1,7,6,1] $

## 样例 #1

### 输入

```
5
1 3 4 3 3

```

### 输出

```
4 2 1 1 1 

```

## 样例 #2

### 输入

```
8
1 5 7 8 1 7 6 1

```

### 输出

```
8 4 3 2 1 1 1 1 

```



---

---
title: "Yet Another Minimization Problem"
layout: "post"
diff: 省选/NOI-
pid: CF868F
tag: ['动态规划 DP', '分治']
---

# Yet Another Minimization Problem

## 输出格式

$2 \leq n \leq 10^5$，$2 \leq k \leq \min(n,20)$，$1 \leq a_i \leq n$ 。

## 样例 #1

### 输入

```
7 3
1 1 3 3 3 2 1

```

### 输出

```
1

```

## 样例 #2

### 输入

```
10 2
1 2 1 2 1 2 1 2 1 2

```

### 输出

```
8

```

## 样例 #3

### 输入

```
13 3
1 2 2 2 1 2 1 1 1 2 2 1 1

```

### 输出

```
9

```



---

---
title: "Palindromes in a Tree"
layout: "post"
diff: 省选/NOI-
pid: CF914E
tag: ['点分治', '分治', '状态合并']
---

# Palindromes in a Tree

## 题目描述

#### 题意

给你一颗 $n$ 个顶点的树（连通无环图）。顶点从 $1$ 到 $n$ 编号，并且每个顶点对应一个在 `a` 到 `t` 的字母。
树上的一条路径是回文是指至少有一个对应字母的排列为回文。

对于每个顶点，输出通过它的回文路径的数量。

注意：从 $u$ 到 $v$ 的路径与从 $v$ 到 $u$ 的路径视为相同，只计数一次。

## 输入格式

第一行包含一个整数 $n$（$2\leq n\leq 2\times 10^5$）。

接下来的 $n-1$ 行，每行包含两个整数 $u$ 和 $v$（$1\leq u,v\leq n,u\neq v$）表示一条连接 $u$ 和 $v$ 的边。保证给出的图是一棵树。
再下一行包含一个 $n$ 个字符的字符串，第 $i$ 个字符对应第 $i$ 个顶点。

## 输出格式

输出一行，包含 $n$ 个整数，第 $i$ 个数表示经过顶点 $i$ 的回文路径数量。

## 样例 #1

### 输入

```
5
1 2
2 3
3 4
3 5
abcbb

```

### 输出

```
1 3 4 3 3 

```

## 样例 #2

### 输入

```
7
6 2
4 3
3 7
5 2
7 2
1 4
afefdfs

```

### 输出

```
1 4 1 1 2 4 2 

```



---

---
title: "Shortest Path Queries"
layout: "post"
diff: 省选/NOI-
pid: CF938G
tag: ['线段树分治']
---

# Shortest Path Queries

## 题目描述

You are given an undirected connected graph with weighted edges. The length of some path between two vertices is the bitwise xor of weights of all edges belonging to this path (if some edge is traversed more than once, then it is included in bitwise xor the same number of times).

There are three types of queries you have to process:

- $ 1 $ $ x $ $ y $ $ d $ — add an edge connecting vertex $ x $ to vertex $ y $ with weight $ d $ . It is guaranteed that there is no edge connecting $ x $ to $ y $ before this query;
- $ 2 $ $ x $ $ y $ — remove an edge connecting vertex $ x $ to vertex $ y $ . It is guaranteed that there was such edge in the graph, and the graph stays connected after this query;
- $ 3 $ $ x $ $ y $ — calculate the length of the shortest path (possibly non-simple) from vertex $ x $ to vertex $ y $ .

Print the answers for all queries of type $ 3 $ .

## 输入格式

The first line contains two numbers $ n $ and $ m $ ( $ 1<=n,m<=200000 $ ) — the number of vertices and the number of edges in the graph, respectively.

Then $ m $ lines follow denoting the edges of the graph. Each line contains three integers $ x $ , $ y $ and $ d $ ( $ 1<=x<y<=n $ , $ 0<=d<=2^{30}-1 $ ). Each pair $ (x,y) $ is listed at most once. The initial graph is connected.

Then one line follows, containing an integer $ q $ ( $ 1<=q<=200000 $ ) — the number of queries you have to process.

Then $ q $ lines follow, denoting queries in the following form:

- $ 1 $ $ x $ $ y $ $ d $ ( $ 1<=x<y<=n $ , $ 0<=d<=2^{30}-1 $ ) — add an edge connecting vertex $ x $ to vertex $ y $ with weight $ d $ . It is guaranteed that there is no edge connecting $ x $ to $ y $ before this query;
- $ 2 $ $ x $ $ y $ ( $ 1<=x<y<=n $ ) — remove an edge connecting vertex $ x $ to vertex $ y $ . It is guaranteed that there was such edge in the graph, and the graph stays connected after this query;
- $ 3 $ $ x $ $ y $ ( $ 1<=x<y<=n $ ) — calculate the length of the shortest path (possibly non-simple) from vertex $ x $ to vertex $ y $ .

It is guaranteed that at least one query has type $ 3 $ .

## 输出格式

Print the answers for all queries of type $ 3 $ in the order they appear in input.

## 样例 #1

### 输入

```
5 5
1 2 3
2 3 4
3 4 5
4 5 6
1 5 1
5
3 1 5
1 1 3 1
3 1 5
2 1 5
3 1 5

```

### 输出

```
1
1
2

```



---

---
title: "GCD Counting"
layout: "post"
diff: 省选/NOI-
pid: CF990G
tag: ['点分治', '容斥原理']
---

# GCD Counting

## 题目描述

You are given a tree consisting of $ n $ vertices. A number is written on each vertex; the number on vertex $ i $ is equal to $ a_i $ .

Let's denote the function $ g(x, y) $ as the greatest common divisor of the numbers written on the vertices belonging to the simple path from vertex $ x $ to vertex $ y $ (including these two vertices).

For every integer from $ 1 $ to $ 2 \cdot 10^5 $ you have to count the number of pairs $ (x, y) $ $ (1 \le x \le y \le n) $ such that $ g(x, y) $ is equal to this number.

## 输入格式

The first line contains one integer $ n $ — the number of vertices $ (1 \le n \le 2 \cdot 10^5) $ .

The second line contains $ n $ integers $ a_1 $ , $ a_2 $ , ..., $ a_n $ $ (1 \le a_i \le 2 \cdot 10^5) $ — the numbers written on vertices.

Then $ n - 1 $ lines follow, each containing two integers $ x $ and $ y $ $ (1 \le x, y \le n, x \ne y) $ denoting an edge connecting vertex $ x $ with vertex $ y $ . It is guaranteed that these edges form a tree.

## 输出格式

For every integer $ i $ from $ 1 $ to $ 2 \cdot 10^5 $ do the following: if there is no pair $ (x, y) $ such that $ x \le y $ and $ g(x, y) = i $ , don't output anything. Otherwise output two integers: $ i $ and the number of aforementioned pairs. You have to consider the values of $ i $ in ascending order.

See the examples for better understanding.

## 样例 #1

### 输入

```
3
1 2 3
1 2
2 3

```

### 输出

```
1 4
2 1
3 1

```

## 样例 #2

### 输入

```
6
1 2 4 8 16 32
1 6
6 3
3 4
4 2
6 5

```

### 输出

```
1 6
2 5
4 6
8 1
16 2
32 1

```

## 样例 #3

### 输入

```
4
9 16 144 6
1 3
2 3
4 3

```

### 输出

```
1 1
2 1
3 1
6 2
9 2
16 2
144 1

```



---

