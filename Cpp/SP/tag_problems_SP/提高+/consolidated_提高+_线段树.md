---
title: "GSS1 - Can you answer these queries I"
layout: "post"
diff: 提高+/省选-
pid: SP1043
tag: ['线段树', '分治', '前缀和']
---

# GSS1 - Can you answer these queries I

## 题目描述

You are given a sequence A\[1\], A\[2\], ..., A\[N\] . ( |A\[i\]| ≤ 15007 , 1 ≤ N ≤ 50000 ). A query is defined as follows:   
 Query(x,y) = Max { a\[i\]+a\[i+1\]+...+a\[j\] ; x ≤ i ≤ j ≤ y }.   
 Given M queries, your program must output the results of these queries.

## 输入格式

- The first line of the input file contains the integer N.
- In the second line, N numbers follow.
- The third line contains the integer M.
- M lines follow, where line i contains 2 numbers xi and yi.

## 输出格式

 Your program should output the results of the M queries, one query per line.

## 样例 #1

### 输入

```
3 
-1 2 3
1
1 2
```

### 输出

```
2
```



---

---
title: "GSS3 - Can you answer these queries III"
layout: "post"
diff: 提高+/省选-
pid: SP1716
tag: ['线段树', '矩阵乘法', '动态 DP']
---

# GSS3 - Can you answer these queries III

## 题目描述

You are given a sequence A of N (N <= 50000) integers between -10000 and 10000. On this sequence you have to apply M (M <= 50000) operations:   
 modify the i-th element in the sequence or for given x y print max{Ai + Ai+1 + .. + Aj | x<=i<=j<=y }.

## 输入格式

The first line of input contains an integer N. The following line contains N integers, representing the sequence A1..AN.   
 The third line contains an integer M. The next M lines contain the operations in following form:  
 0 x y: modify Ax into y (|y|<=10000).  
 1 x y: print max{Ai + Ai+1 + .. + Aj | x<=i<=j<=y }.

## 输出格式

For each query, print an integer as the problem required.

## 样例 #1

### 输入

```
4
1 2 3 4
4
1 1 3
0 3 -3
1 2 4
1 3 3
```

### 输出

```
6
4
-3
```



---

---
title: "GSS4 - Can you answer these queries IV"
layout: "post"
diff: 提高+/省选-
pid: SP2713
tag: ['线段树']
---

# GSS4 - Can you answer these queries IV

## 题目描述

You are given a sequence A of N(N <= 100,000) positive integers. There sum will be less than 10 $ ^{18} $ . On this sequence you have to apply M (M <= 100,000) operations:

(A) For given x,y, for each elements between the x-th and the y-th ones (inclusively, counting from 1), modify it to its positive square root (rounded down to the nearest integer).

(B) For given x,y, query the sum of all the elements between the x-th and the y-th ones (inclusively, counting from 1) in the sequence.

## 输入格式

Multiple test cases, please proceed them one by one. Input terminates by EOF.

For each test case:

The first line contains an integer N. The following line contains N integers, representing the sequence A $ _{1} $ ..A $ _{N} $ .   
 The third line contains an integer M. The next M lines contain the operations in the form "i x y".i=0 denotes the modify operation, i=1 denotes the query operation.

## 输出格式

For each test case:

Output the case number (counting from 1) in the first line of output. Then for each query, print an integer as the problem required.

Print an blank line after each test case.

See the sample output for more details.

## 样例 #1

### 输入

```
5
1 2 3 4 5
5
1 2 4
0 2 4
1 2 4
0 4 5
1 1 5
4
10 10 10 10
3
1 1 4
0 2 3
1 1 4
```

### 输出

```
Case #1:
9
4
6

Case #2:
40
26
```



---

---
title: "ADAAPPLE - Ada and Apple"
layout: "post"
diff: 提高+/省选-
pid: SP30785
tag: ['线段树', '树链剖分']
---

# ADAAPPLE - Ada and Apple

## 题目描述

Ada the Ladybug is currently on a trip on apple [tree](https://en.wikipedia.org/wiki/Tree_(data_structure)). There are many apples on the tree connected with branches. Each apple is inhabited by either Psylloideas or by Woolly Apple Aphids. Psylloideas and Aphids doesn't like each other, so it is strictly prohibited to walk from apple of Psylloideas to apple of aphids (and vice versa). Ada has some questions, whether it is possible to go from node **I** to node **J**.

Anyway note, that as Aphids and Psyllodeas doesn't like each other, they sometime conquer an apple of the others. Also note, that it is a real apple tree (not some bush) so no apple is connected with more than 50 other apples.

## 输入格式

The first line contains **1 , number apples on tree and number for queries.**

The next line contains **N** characters (either 0 or 1), indicating whether **i** $ ^{th} $ apple belongs to Psyllodeas or to Aphids.

Next **N-1** lines contains two numbers, the branches (edges) of apple tree (**0 , **I ≠ J**).**

Each of following **Q** lines contains one of following types of queries:

 **0 I**, **0 , meaning that ownership of **I** $ ^{th} $ apple has changed.**

 **1 I J**, **0 , question, whether it is possible to go from **I** $ ^{th} $ to **J** $ ^{th} $ apple.**

## 输出格式

For each query of second kind (1) print "YES", if it is possible or "NO" if it is impossible!



---

---
title: "DQUERY - D-query"
layout: "post"
diff: 提高+/省选-
pid: SP3267
tag: ['莫队', '线段树', '树状数组', '可持久化线段树']
---

# DQUERY - D-query

## 题目描述

[English](/problems/DQUERY/en/) [Vietnamese](/problems/DQUERY/vn/)Given a sequence of n numbers a $ _{1} $ , a $ _{2} $ , ..., a $ _{n} $ and a number of d-queries. A d-query is a pair (i, j) (1 ≤ i ≤ j ≤ n). For each d-query (i, j), you have to return the number of distinct elements in the subsequence a $ _{i} $ , a $ _{i+1} $ , ..., a $ _{j} $ .

## 输入格式

- Line 1: n (1 ≤ n ≤ 30000).
- Line 2: n numbers a $ _{1} $ , a $ _{2} $ , ..., a $ _{n} $ (1 ≤ a $ _{i} $ ≤ 10 $ ^{6} $ ).
- Line 3: q (1 ≤ q ≤ 200000), the number of d-queries.
- In the next q lines, each line contains 2 numbers i, j representing a d-query (1 ≤ i ≤ j ≤ n).

## 输出格式

- For each d-query (i, j), print the number of distinct elements in the subsequence a $ _{i} $ , a $ _{i+1} $ , ..., a $ _{j} $ in a single line.

## 样例 #1

### 输入

```
5
1 1 2 1 3
3
1 5
2 4
3 5
```

### 输出

```
3
2
3
```



---

---
title: "INTDSET - Chiaki With Intervals"
layout: "post"
diff: 提高+/省选-
pid: SP34032
tag: ['动态规划 DP', '线段树']
---

# INTDSET - Chiaki With Intervals

## 题目描述

给你一个有 $n$ 个区间的集合 $A$，求有多少个子集 $S$ 满足条件：任意区间 $a \in A$ 且 $a \notin S$ 均与 $S$ 的至少一个子集有交集。

答案对 $10^9+7$ 取模。

注意 $A$ 本身是一个合法的答案。

## 输入格式

第一行输入整数 $T$ ，代表数据组数。

对于每组数据，先输入整数 $n$，代表区间的个数，接下来是 $n$ 行，每行2个整数 $l_i,r_i$，代表一个区间。

## 输出格式

对于每组数据，输出一个整数。

## 样例 #1

### 输入

```
2
3
1 2
3 4
5 6
3
1 4
2 4
3 4
```

### 输出

```
1
7
```



---

---
title: "QTREE - Query on a tree"
layout: "post"
diff: 提高+/省选-
pid: SP375
tag: ['线段树', '最近公共祖先 LCA', '树链剖分']
---

# QTREE - Query on a tree

## 题目描述

You are given a tree (an acyclic undirected connected graph) with **N** nodes, and edges numbered 1, 2, 3...**N**-1.

We will ask you to perfrom some instructions of the following form:

- **CHANGE i ti** : change the cost of the i-th edge to ti  
   or
- **QUERY a b** : ask for the maximum edge cost on the path from node a to node b

## 输入格式

The first line of input contains an integer **t**, the number of test cases (**t** <= 20). t test cases follow.

For each test case:

- In the first line there is an integer **N** (**N** <= 10000),
- In the next **N**-1 lines, the i-th line describes the i-th edge: a line with three integers **a b c** denotes an edge between **a**, **b** of cost **c** (**c** <= 1000000),
- The next lines contain instructions **"CHANGE i ti"** or **"QUERY a b"**,
- The end of each test case is signified by the string "**DONE**".

There is one blank line between successive tests.

## 输出格式

For each "**QUERY**" operation, write one integer representing its result.

## 样例 #1

### 输入

```
1

3
1 2 1
2 3 2
QUERY 1 2
CHANGE 1 3
QUERY 1 2
DONE
```

### 输出

```
1
3
```



---

---
title: "MKTHNUM - K-th Number"
layout: "post"
diff: 提高+/省选-
pid: SP3946
tag: ['线段树', '可持久化线段树', '可持久化']
---

# MKTHNUM - K-th Number

## 题目描述

题目大意：

给你 $n$ 个数，多次询问某段区间中第 $k$ 小的数。

## 输入格式

第一行有两个整数 $n,m$，分别为整数个数、询问次数。

第二行有 $n$ 个整数，其中第 $i$ 个为 $a_i$。

接下来 $m$ 行，每行三个整数 $i,j,k$，询问第 $i$ 个数到第 $j$ 个数中第 $k$ 小的数。

## 输出格式

输出共 $m$ 行，为对每次询问的回答。

## 说明/提示

$1\le n \le 100000$ , $1 \le m \le 5000$ , $-10^9 \le a_i \le 10^9$。

~~注意：简单的做法可是过不了的。~~

 感谢 @gjc1124646822  提供的翻译。
 
 Fixed by @AnEasySong



---

---
title: "CPAIR - Counting pairs"
layout: "post"
diff: 提高+/省选-
pid: SP5542
tag: ['线段树']
---

# CPAIR - Counting pairs

## 题目描述

给出一个长度为 $N$ 的非负整数序列 $A$，回答 $Q$ 个询问。每个询问包含 $3$ 个数：$v,a,b$，回答序列 $A$ 中有多少个区间的最小值 $\ge v$，且区间的长度在 $[a,b]$ 范围内。

## 输入格式

第一行输入两个整数，包含 $N$ 和 $Q$

第二行输入 $N$ 个整数，表示序列 $A$

接下来 $Q$ 行，每行输入三个整数 $v,a,b$，含义同上

## 输出格式

输出共 $Q$ 行，每行一个整数，为每个询问的答案

## 说明/提示

- $1 \le N,Q \le 10^5$
- $1 \le a \le b \le N$
- $0 \le v,A_i \le 10^9$

## 样例 #1

### 输入

```
5 3

5 3 2 7 4

3 2 3

2 2 5

4 1 1
```

### 输出

```
2

10

3
```



---

