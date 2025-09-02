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

