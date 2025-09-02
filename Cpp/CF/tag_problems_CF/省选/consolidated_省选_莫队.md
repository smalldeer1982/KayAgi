---
title: "Complicated Computations"
layout: "post"
diff: 省选/NOI-
pid: CF1436E
tag: ['莫队', '线段树']
---

# Complicated Computations

## 题目描述

In this problem MEX of a certain array is the smallest positive integer not contained in this array.

Everyone knows this definition, including Lesha. But Lesha loves MEX, so he comes up with a new problem involving MEX every day, including today.

You are given an array $ a $ of length $ n $ . Lesha considers all the non-empty subarrays of the initial array and computes MEX for each of them. Then Lesha computes MEX of the obtained numbers.

An array $ b $ is a subarray of an array $ a $ , if $ b $ can be obtained from $ a $ by deletion of several (possible none or all) elements from the beginning and several (possibly none or all) elements from the end. In particular, an array is a subarray of itself.

Lesha understands that the problem is very interesting this time, but he doesn't know how to solve it. Help him and find the MEX of MEXes of all the subarrays!

## 输入格式

The first line contains a single integer $ n $ ( $ 1 \le n \le 10^5 $ ) — the length of the array.

The next line contains $ n $ integers $ a_1, a_2, \ldots, a_n $ ( $ 1 \le a_i \le n $ ) — the elements of the array.

## 输出格式

Print a single integer — the MEX of MEXes of all subarrays.

## 样例 #1

### 输入

```
3
1 3 2
```

### 输出

```
3
```

## 样例 #2

### 输入

```
5
1 4 3 1 2
```

### 输出

```
6
```



---

---
title: "Yunli's Subarray Queries (extreme version)"
layout: "post"
diff: 省选/NOI-
pid: CF2009G3
tag: ['莫队', '线段树']
---

# Yunli's Subarray Queries (extreme version)

## 题目描述

这是问题的极限版本。在这个版本中，每个查询的输出与简单版和困难版不同。保证对于所有的查询都有 $ r \geq l+k-1 $。

对于一个任意数组 $ b $，云莉可以无数次进行以下操作：

- 选择一个下标 $ i $，将 $ b_i $ 设置为任意她想要的整数 $ x $（$ x $ 不限制在 $ [1, n] $ 区间内）。

定义 $ f(b) $ 为所需的最小操作次数，以使得 $ b $ 中存在一个长度至少为 $ k $ 的连续子数组。

云莉给出一个大小为 $ n $ 的数组 $ a $ 并询问你 $ q $ 次，你需要在每次查询中计算并输出 $\sum_{i=l}^{r-k+1} \sum_{j=i+k-1}^{r} f([a_i, a_{i+1}, \ldots, a_j])$。

如果数组中存在从下标 $ i $ 开始的长度为 $ k $ 的连续子数组（$ 1 \leq i \leq |b|-k+1 $），那么在该子数组中，对于 $ i < j \leq i+k-1 $，必须满足 $ b_j = b_{j-1} + 1 $。

## 输入格式

第一行输入 $ t $（$ 1 \leq t \leq 10^4 $）—— 表示测试用例的数量。

接下来的每个测试用例的第一行包含三个整数 $ n $、$ k $ 和 $ q $（$ 1 \leq k \leq n \leq 2 \cdot 10^5 $，$ 1 \leq q \leq 2 \cdot 10^5 $），分别表示数组的长度、连续子数组的长度和查询的次数。

接下来是一行，包含 $ n $ 个整数 $ a_1, a_2, \ldots, a_n $（$ 1 \leq a_i \leq n $）。

接下来的 $ q $ 行中，每行包含两个整数 $ l $ 和 $ r $（$ 1 \leq l \leq r \leq n $，$ r \geq l+k-1 $），表示查询的区间。

保证所有测试用例中 $ n $ 的总和不超过 $ 2 \cdot 10^5 $，所有测试用例中 $ q $ 的总和不超过 $ 2 \cdot 10^5 $。

## 输出格式

对于每个查询，输出一行结果，即 $\sum_{i=l}^{r-k+1} \sum_{j=i+k-1}^{r} f([a_i, a_{i+1}, \ldots, a_j])$。

## 说明/提示

在第一个测试用例的第一个查询中，我们可以通过如下方法来计算结果：

- 当 $ i = 4 $ 且 $ j = 5 $ 时，$ f([2, 1])=1 $，因为云莉可以将 $ b_2 $ 设为 3，从而一步操作后形成长度为 2 的连续子数组。
- 当 $ i = 4 $ 且 $ j = 6 $ 时，$ f([2, 1, 2])=0 $，因为已经存在长度为 2 的连续子数组。
- 当 $ i = 5 $ 且 $ j = 6 $ 时，$ f([1, 2])=0 $，因为已经存在长度为 2 的连续子数组。

此查询的答案为 $ 1+0+0=1 $。

 **本翻译由 AI 自动生成**

## 样例 #1

### 输入

```
5
7 2 4
1 2 3 2 1 2 3
4 6
1 7
2 7
3 7
8 4 2
4 3 1 1 2 4 3 2
3 6
1 5
5 4 2
4 5 1 2 3
1 4
1 5
10 4 8
2 3 6 5 8 9 8 10 10 1
2 7
6 10
1 9
1 6
3 9
4 10
2 10
1 8
10 7 4
3 4 5 3 4 5 9 10 8 9
1 9
2 10
1 10
2 9
```

### 输出

```
1
3
3
3
2
7
2
4
8
6
28
7
16
20
32
19
18
15
26
9
```



---

---
title: "Tree and Queries"
layout: "post"
diff: 省选/NOI-
pid: CF375D
tag: ['莫队', '树上启发式合并']
---

# Tree and Queries

## 题目描述

You have a rooted tree consisting of $ n $ vertices. Each vertex of the tree has some color. We will assume that the tree vertices are numbered by integers from 1 to $ n $ . Then we represent the color of vertex $ v $ as $ c_{v} $ . The tree root is a vertex with number 1.

In this problem you need to answer to $ m $ queries. Each query is described by two integers $ v_{j},k_{j} $ . The answer to query $ v_{j},k_{j} $ is the number of such colors of vertices $ x $ , that the subtree of vertex $ v_{j} $ contains at least $ k_{j} $ vertices of color $ x $ .

You can find the definition of a rooted tree by the following link: http://en.wikipedia.org/wiki/Tree\_(graph\_theory).

## 输入格式

The first line contains two integers $ n $ and $ m $ $ (2<=n<=10^{5}; 1<=m<=10^{5}) $ . The next line contains a sequence of integers $ c_{1},c_{2},...,c_{n} $ $ (1<=c_{i}<=10^{5}) $ . The next $ n-1 $ lines contain the edges of the tree. The $ i $ -th line contains the numbers $ a_{i},b_{i} $ $ (1<=a_{i},b_{i}<=n; a_{i}≠b_{i}) $ — the vertices connected by an edge of the tree.

Next $ m $ lines contain the queries. The $ j $ -th line contains two integers $ v_{j},k_{j} $ $ (1<=v_{j}<=n; 1<=k_{j}<=10^{5}) $ .

## 输出格式

Print $ m $ integers — the answers to the queries in the order the queries appear in the input.

## 说明/提示

A subtree of vertex $ v $ in a rooted tree with root $ r $ is a set of vertices $ {u :dist(r,v)+dist(v,u)=dist(r,u)} $ . Where $ dist(x,y) $ is the length (in edges) of the shortest path between vertices $ x $ and $ y $ .

## 样例 #1

### 输入

```
8 5
1 2 2 3 3 2 3 3
1 2
1 5
2 3
2 4
5 6
5 7
5 8
1 2
1 3
1 4
2 3
5 3

```

### 输出

```
2
2
1
0
1

```

## 样例 #2

### 输入

```
4 1
1 2 3 4
1 2
2 3
3 4
1 1

```

### 输出

```
4

```



---

---
title: "Machine Learning"
layout: "post"
diff: 省选/NOI-
pid: CF940F
tag: ['莫队', '枚举', '分块']
---

# Machine Learning

## 题目描述

You come home and fell some unpleasant smell. Where is it coming from?

You are given an array $ a $ . You have to answer the following queries:

1. You are given two integers $ l $ and $ r $ . Let $ c_{i} $ be the number of occurrences of $ i $ in $ a_{l:r} $ , where $ a_{l:r} $ is the subarray of $ a $ from $ l $ -th element to $ r $ -th inclusive. Find the Mex of $ {c_{0},c_{1},...,c_{10^{9}}} $
2. You are given two integers $ p $ to $ x $ . Change $ a_{p} $ to $ x $ .

The Mex of a multiset of numbers is the smallest non-negative integer not in the set.

Note that in this problem all elements of $ a $ are positive, which means that $ c_{0} $ = 0 and $ 0 $ is never the answer for the query of the second type.

## 输入格式

The first line of input contains two integers $ n $ and $ q $ ( $ 1<=n,q<=100000 $ ) — the length of the array and the number of queries respectively.

The second line of input contains $ n $ integers — $ a_{1} $ , $ a_{2} $ , $ ... $ , $ a_{n} $ ( $ 1<=a_{i}<=10^{9} $ ).

Each of the next $ q $ lines describes a single query.

The first type of query is described by three integers $ t_{i}=1 $ , $ l_{i} $ , $ r_{i} $ , where $ 1<=l_{i}<=r_{i}<=n $ — the bounds of the subarray.

The second type of query is described by three integers $ t_{i}=2 $ , $ p_{i} $ , $ x_{i} $ , where $ 1<=p_{i}<=n $ is the index of the element, which must be changed and $ 1<=x_{i}<=10^{9} $ is the new value.

## 输出格式

For each query of the first type output a single integer — the Mex of $ {c_{0},c_{1},...,c_{10^{9}}} $ .

## 说明/提示

The subarray of the first query consists of the single element — $ 1 $ .

The subarray of the second query consists of four $ 2 $ s, one $ 3 $ and two $ 1 $ s.

The subarray of the fourth query consists of three $ 1 $ s, three $ 2 $ s and one $ 3 $ .

## 样例 #1

### 输入

```
10 4
1 2 3 1 1 2 2 2 9 9
1 1 1
1 2 8
2 7 1
1 2 8

```

### 输出

```
2
3
2

```



---

