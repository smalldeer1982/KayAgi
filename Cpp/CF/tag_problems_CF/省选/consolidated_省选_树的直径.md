---
title: "Iris's Full Binary Tree"
layout: "post"
diff: 省选/NOI-
pid: CF2006E
tag: ['线段树', '树的遍历', '树的直径']
---

# Iris's Full Binary Tree

## 题目描述

Iris likes full binary trees.

Let's define the depth of a rooted tree as the maximum number of vertices on the simple paths from some vertex to the root. A full binary tree of depth $ d $ is a binary tree of depth $ d $ with exactly $ 2^d - 1 $ vertices.

Iris calls a tree a  $ d $ -binary tree if some vertices and edges can be added to it to make it a full binary tree of depth $ d $ . Note that any vertex can be chosen as the root of a full binary tree.

Since performing operations on large trees is difficult, she defines the binary depth of a tree as the minimum $ d $ satisfying that the tree is $ d $ -binary. Specifically, if there is no integer $ d \ge 1 $ such that the tree is $ d $ -binary, the binary depth of the tree is $ -1 $ .

Iris now has a tree consisting of only vertex $ 1 $ . She wants to add $ n - 1 $ more vertices to form a larger tree. She will add the vertices one by one. When she adds vertex $ i $ ( $ 2 \leq i \leq n $ ), she'll give you an integer $ p_i $ ( $ 1 \leq p_i < i $ ), and add a new edge connecting vertices $ i $ and $ p_i $ .

Iris wants to ask you the binary depth of the tree formed by the first $ i $ vertices for each $ 1 \le i \le n $ . Can you tell her the answer?

## 输入格式

Each test consists of multiple test cases. The first line contains a single integer $ t $ ( $ 1 \leq t \leq 10^4 $ ) — the number of test cases. The description of the test cases follows.

The first line of each test case contains a single integer $ n $ ( $ 2 \leq n \leq 5 \cdot 10^5 $ ) — the final size of the tree.

The second line of each test case contains $ n - 1 $ integers $ p_2, p_3, \ldots, p_n $ ( $ 1 \leq p_i < i $ ) — descriptions of all edges of the tree.

It is guaranteed that the sum of $ n $ over all test cases does not exceed $ 5 \cdot 10^5 $ .

## 输出格式

For each test case output $ n $ integers, $ i $ -th of them representing the binary depth of the tree formed by the first $ i $ vertices.

## 说明/提示

In the first test case, the final tree is shown below:

 ![](https://cdn.luogu.com.cn/upload/vjudge_pic/CF2006E/7f900739a2145e9bd80715ede4260b35ba51b9fd.png)- The tree consisting of the vertex $ 1 $ has the binary depth $ 1 $ (the tree itself is a full binary tree of depth $ 1 $ ).
- The tree consisting of the vertices $ 1 $ and $ 2 $ has the binary depth $ 2 $ (we can add the vertex $ 3 $ to make it a full binary tree of depth $ 2 $ ).
- The tree consisting of the vertices $ 1 $ , $ 2 $ and $ 3 $ has the binary depth $ 2 $ (the tree itself is a full binary tree of depth $ 2 $ ).

In the second test case, the formed full binary tree after adding some vertices to the tree consisting of $ n $ vertices is shown below (bolded vertices are added):

 ![](https://cdn.luogu.com.cn/upload/vjudge_pic/CF2006E/90faca99e1781d73f69b5b60a32aa2a2da38a68c.png)The depth of the formed full binary tree is $ 4 $ .

In the fifth test case, the final tree is shown below:

 ![](https://cdn.luogu.com.cn/upload/vjudge_pic/CF2006E/2c0d039efae462812828b42368688f46ffc8b41e.png)It can be proved that Iris can't form any full binary tree by adding vertices and edges, so the binary depth is $ -1 $ .

## 样例 #1

### 输入

```
7
3
1 1
6
1 2 3 4 5
7
1 1 3 2 5 1
10
1 1 2 1 4 2 4 5 8
10
1 1 3 1 3 2 2 2 6
20
1 1 2 2 4 4 5 5 7 6 8 6 11 14 11 8 13 13 12
25
1 1 3 3 1 5 4 4 6 8 11 12 8 7 11 13 7 13 15 6 19 14 10 23
```

### 输出

```
1 2 2 
1 2 2 3 3 4 
1 2 2 3 3 4 4 
1 2 2 3 3 3 4 4 5 5 
1 2 2 3 3 4 4 4 -1 -1 
1 2 2 3 3 4 4 4 4 5 5 5 5 6 6 6 6 6 6 7 
1 2 2 3 3 4 4 4 4 5 5 6 6 6 6 6 7 7 7 7 7 8 8 8 8
```



---

---
title: "Expected diameter of a tree"
layout: "post"
diff: 省选/NOI-
pid: CF804D
tag: ['树的直径', '前缀和', '期望']
---

# Expected diameter of a tree

## 题目描述

Pasha is a good student and one of MoJaK's best friends. He always have a problem to think about. Today they had a talk about the following problem.

We have a forest (acyclic undirected graph) with $ n $ vertices and $ m $ edges. There are $ q $ queries we should answer. In each query two vertices $ v $ and $ u $ are given. Let $ V $ be the set of vertices in the connected component of the graph that contains $ v $ , and $ U $ be the set of vertices in the connected component of the graph that contains $ u $ . Let's add an edge between some vertex ![](https://cdn.luogu.com.cn/upload/vjudge_pic/CF804D/8ef01bdc02f37e886781700f62479c92154da008.png) and some vertex in ![](https://cdn.luogu.com.cn/upload/vjudge_pic/CF804D/0479fe8afb5e9211cdac4c2d711ca0b8e2ad6e82.png) and compute the value $ d $ of the resulting component. If the resulting component is a tree, the value $ d $ is the diameter of the component, and it is equal to -1 otherwise. What is the expected value of $ d $ , if we choose vertices $ a $ and $ b $ from the sets uniformly at random?

Can you help Pasha to solve this problem?

The diameter of the component is the maximum distance among some pair of vertices in the component. The distance between two vertices is the minimum number of edges on some path between the two vertices.

Note that queries don't add edges to the initial forest.

## 输入格式

The first line contains three integers $ n $ , $ m $ and $ q $ ( $ 1<=n,m,q<=10^{5} $ ) — the number of vertices, the number of edges in the graph and the number of queries.

Each of the next $ m $ lines contains two integers $ u_{i} $ and $ v_{i} $ ( $ 1<=u_{i},v_{i}<=n $ ), that means there is an edge between vertices $ u_{i} $ and $ v_{i} $ .

It is guaranteed that the given graph is a forest.

Each of the next $ q $ lines contains two integers $ u_{i} $ and $ v_{i} $ ( $ 1<=u_{i},v_{i}<=n $ ) — the vertices given in the $ i $ -th query.

## 输出格式

For each query print the expected value of $ d $ as described in the problem statement.

Your answer will be considered correct if its absolute or relative error does not exceed $ 10^{-6} $ . Let's assume that your answer is $ a $ , and the jury's answer is $ b $ . The checker program will consider your answer correct, if ![](https://cdn.luogu.com.cn/upload/vjudge_pic/CF804D/259203790d90e969d73ec841bd0673c1e8e7d69a.png).

## 说明/提示

In the first example the vertices $ 1 $ and $ 3 $ are in the same component, so the answer for the first query is -1. For the second query there are two options to add the edge: one option is to add the edge $ 1-2 $ , the other one is $ 2-3 $ . In both ways the resulting diameter is $ 2 $ , so the answer is $ 2 $ .

In the second example the answer for the first query is obviously -1. The answer for the second query is the average of three cases: for added edges $ 1-2 $ or $ 1-3 $ the diameter is $ 3 $ , and for added edge $ 1-4 $ the diameter is $ 2 $ . Thus, the answer is ![](https://cdn.luogu.com.cn/upload/vjudge_pic/CF804D/80f05d9f9a5abbad800eeb11e2f309500aaccabe.png).

## 样例 #1

### 输入

```
3 1 2
1 3
3 1
2 3

```

### 输出

```
-1
2.0000000000

```

## 样例 #2

### 输入

```
5 2 3
2 4
4 3
4 2
4 1
2 5

```

### 输出

```
-1
2.6666666667
2.6666666667

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

