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

