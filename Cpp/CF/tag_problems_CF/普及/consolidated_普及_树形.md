---
title: "Vertical Paths"
layout: "post"
diff: 普及/提高-
pid: CF1675D
tag: ['树形数据结构', '树链剖分']
---

# Vertical Paths

## 题目描述

You are given a rooted tree consisting of $ n $ vertices. Vertices are numbered from $ 1 $ to $ n $ . Any vertex can be the root of a tree.

A tree is a connected undirected graph without cycles. A rooted tree is a tree with a selected vertex, which is called the root.

The tree is specified by an array of parents $ p $ containing $ n $ numbers: $ p_i $ is a parent of the vertex with the index $ i $ . The parent of a vertex $ u $ is a vertex that is the next vertex on the shortest path from $ u $ to the root. For example, on the simple path from $ 5 $ to $ 3 $ (the root), the next vertex would be $ 1 $ , so the parent of $ 5 $ is $ 1 $ .

The root has no parent, so for it, the value of $ p_i $ is $ i $ (the root is the only vertex for which $ p_i=i $ ).

Find such a set of paths that:

- each vertex belongs to exactly one path, each path can contain one or more vertices;
- in each path each next vertex — is a son of the current vertex (that is, paths always lead down — from parent to son);
- number of paths is minimal.

For example, if $ n=5 $ and $ p=[3, 1, 3, 3, 1] $ , then the tree can be divided into three paths:

1. $ 3 \rightarrow 1 \rightarrow 5 $ (path of $ 3 $ vertices),
2. $ 4 $ (path of $ 1 $ vertices).
3. $ 2 $ (path of $ 1 $ vertices).

 ![](https://cdn.luogu.com.cn/upload/vjudge_pic/CF1675D/b196ebd17b672e4b5d378bdd713910bded65862b.png)Example of splitting a root tree into three paths for $ n=5 $ , the root of the tree — node $ 3 $ .

## 输入格式

The first line of input data contains an integer $ t $ ( $ 1 \le t \le 10^4 $ ) — the number of test cases in the test.

Each test case consists of two lines.

The first of them contains an integer $ n $ ( $ 1 \le n \le 2 \cdot 10^5 $ ). It is the number of vertices in the tree.

The second line contains $ n $ integers $ p_1, p_2, \dots, p_n $ ( $ 1 \le p_i \le n $ ). It is guaranteed that the $ p $ array encodes some rooted tree.

It is guaranteed that the sum of the values $ n $ over all test cases in the test does not exceed $ 2 \cdot 10^5 $ .

## 输出格式

For each test case on the first line, output an integer $ m $ — the minimum number of non-intersecting leading down paths that can cover all vertices of the tree.

Then print $ m $ pairs of lines containing path descriptions. In the first of them print the length of the path, in the second — the sequence of vertices specifying that path in the order from top to bottom. You can output the paths in any order.

If there are several answers, output any of them.

## 样例 #1

### 输入

```
6
5
3 1 3 3 1
4
1 1 4 1
7
1 1 2 3 4 5 6
1
1
6
4 4 4 4 1 2
4
2 2 2 2
```

### 输出

```
3
3
3 1 5
1
2
1
4

2
2
1 2
2
4 3

1
7
1 2 3 4 5 6 7

1
1
1

3
3
4 1 5
2
2 6
1
3

3
2
2 1
1
3
1
4
```



---

---
title: "White-Black Balanced Subtrees"
layout: "post"
diff: 普及/提高-
pid: CF1676G
tag: ['深度优先搜索 DFS', '树形 DP']
---

# White-Black Balanced Subtrees

## 题目描述

You are given a rooted tree consisting of $ n $ vertices numbered from $ 1 $ to $ n $ . The root is vertex $ 1 $ . There is also a string $ s $ denoting the color of each vertex: if $ s_i = \texttt{B} $ , then vertex $ i $ is black, and if $ s_i = \texttt{W} $ , then vertex $ i $ is white.

A subtree of the tree is called balanced if the number of white vertices equals the number of black vertices. Count the number of balanced subtrees.

A tree is a connected undirected graph without cycles. A rooted tree is a tree with a selected vertex, which is called the root. In this problem, all trees have root $ 1 $ .

The tree is specified by an array of parents $ a_2, \dots, a_n $ containing $ n-1 $ numbers: $ a_i $ is the parent of the vertex with the number $ i $ for all $ i = 2, \dots, n $ . The parent of a vertex $ u $ is a vertex that is the next vertex on a simple path from $ u $ to the root.

The subtree of a vertex $ u $ is the set of all vertices that pass through $ u $ on a simple path to the root. For example, in the picture below, $ 7 $ is in the subtree of $ 3 $ because the simple path $ 7 \to 5 \to 3 \to 1 $ passes through $ 3 $ . Note that a vertex is included in its subtree, and the subtree of the root is the entire tree.

 ![](https://cdn.luogu.com.cn/upload/vjudge_pic/CF1676G/70fb6ac8a70942903450f21b07ea9969f086df2c.png) The picture shows the tree for $ n=7 $ , $ a=[1,1,2,3,3,5] $ , and $ s=\texttt{WBBWWBW} $ . The subtree at the vertex $ 3 $ is balanced.

## 输入格式

The first line of input contains an integer $ t $ ( $ 1 \le t \le 10^4 $ ) — the number of test cases.

The first line of each test case contains an integer $ n $ ( $ 2 \le n \le 4000 $ ) — the number of vertices in the tree.

The second line of each test case contains $ n-1 $ integers $ a_2, \dots, a_n $ ( $ 1 \le a_i < i $ ) — the parents of the vertices $ 2, \dots, n $ .

The third line of each test case contains a string $ s $ of length $ n $ consisting of the characters $ \texttt{B} $ and $ \texttt{W} $ — the coloring of the tree.

It is guaranteed that the sum of the values $ n $ over all test cases does not exceed $ 2 \cdot 10^5 $ .

## 输出格式

For each test case, output a single integer — the number of balanced subtrees.

## 说明/提示

The first test case is pictured in the statement. Only the subtrees at vertices $ 2 $ and $ 3 $ are balanced.

In the second test case, only the subtree at vertex $ 1 $ is balanced.

In the third test case, only the subtrees at vertices $ 1 $ , $ 3 $ , $ 5 $ , and $ 7 $ are balanced.

## 样例 #1

### 输入

```
3
7
1 1 2 3 3 5
WBBWWBW
2
1
BW
8
1 2 3 4 5 6 7
BWBWBWBW
```

### 输出

```
2
1
4
```



---

---
title: "Min-Fund Prison (Easy)"
layout: "post"
diff: 普及/提高-
pid: CF1970G1
tag: ['树形 DP']
---

# Min-Fund Prison (Easy)

## 题目描述

现给出一张由 $n$ 个点 $m=n-1$ 条边构成的树，其 $m$ 条边为 $(u_i, v_i)$ ( $1\leq i\leq m$ )，表示 $u_i,v_i$ 相连。

你可以以 $c$ 的成本在任意两个点 $x, y$ 之间连一条边。这个操作可以进行任意次，设你操作了 $k$ 次。

在连边操作之后，你必须删去一条割边，使得剩下的图恰由 $2$ 个连通块组成。设两个连通块的大小为 $x,y$ ，请问 $x^2+y^2+kc$ 的最小值为何？

## 输入格式

第一行输入样例个数 $t$ ( $1\leq t\leq 10^5$ ) 。接下来输入 $t$ 个样例，每个样例形式如下——

每个样例的第一行包含三个整数 $n, m, c$ ( $2\leq n\leq 10^5, m=n-1, 1\leq c\leq 10^9$ )，表示点数，边数和加边操作的成本。

接下来 $m$ 行，每一行输入两个整数 $u, v$ ( $1\leq u,v\leq n,u\neq v$ )，表示 $u,v$ 之间有一条边。

保证对于所有输入的样例，满足 $\sum n\leq 10^5,\sum m\leq 5\times 10^5$ 。

## 输出格式

如果能够使得最后结果为两个连通块，输出 $x^2+y^2+kc$ 的最小值；否则，输出 $-1$ 。

## 样例 #1

### 输入

```
2
2 1 3
1 2
8 7 76
3 1
3 2
2 4
2 5
4 6
4 7
7 8
```

### 输出

```
2
32
```



---

---
title: "Guess The Tree"
layout: "post"
diff: 普及/提高-
pid: CF2001C
tag: ['树形数据结构', '二分']
---

# Guess The Tree

## 题目描述

这是一道交互题。

Misuki 有一棵结构未知，具有 $n$ 个节点的树，节点编号从 $ 1 $ 到 $ n $ ，并要求你写一份代码来猜测它。

你可以询问以下问题：

`? a b`

其中 $a,b$ 为两个节点的编号。

对于一次询问，Misuki 会告诉你哪个节点 $x$ 能最小化 $|d(a,x)-d(b,x)|$ 的值，其中 $d(x,y)$ 是节点 $x$ 和 $y$ 之间的距离。如果存在多个这样的节点，Misuki 会告诉你最小化 $d(a,x)$ 的节点。

现要求你使用不超过 $15n$ 次的询问，来确定这棵树的结构。

## 输入格式

**本题有多组测试数据。** 第一行一个正整数 $t$ ，代表测试样例的个数，$1 \le t \le 200 $。

对于每组测试数据，一行一个正整数 $n$（$2 \le n \le 1000$），代表树中的节点数。

保证所有测试数据中 $n$ 的总和不超过 $1000$。

## 输出格式

交互从读取整数 $n$ 开始，
然后你最多可以进行 $15n$ 次查询。在每个查询后，读取一个整数作为查询的答案。

要输出答案，请按如下格式输出：

！$a_1$ $b_1$ $a_2$ $b_2$ ... $a_{n-1}$ $b_{n-1}$ 

这意味着对于 $1 \le i \le n-1$，节点 $ a_i $ 和 $ b_i $ 之间有一条边。你可以按任意顺序输出边。

在进行 $15n$ 次查询后，若再进行查询，将读取到 $-1$ 。收到 $-1$ 后，请终止程序以接收 Wrong Answer 判定。

## 说明/提示

打印每一行后（即进行一次询问或输出一次答案后），请输出回车并刷新输出缓冲区。可刷新输出缓冲区的有：

- C++ 中的 `fflush(stdout)` 或 `cout.flush()`;
- Java 中的 `System.out.flush()`;
- Pascal 中的 `flush(output)`;
- Python 中的 `stdout.flush()`;
- 对于其他语言，请参阅其他语言的文档。

Translated by @[ARIS2_0](https://www.luogu.com.cn/user/1340759)

## 样例 #1

### 输入

```
1
4
1
1
3
```

### 输出

```
? 1 2

? 1 3

? 1 4

! 1 2 1 3 3 4
```



---

