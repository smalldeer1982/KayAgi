---
title: "Cycle"
layout: "post"
diff: 提高+/省选-
pid: CF117C
tag: ['模拟', '图论']
---

# Cycle

## 题目描述

一个 $\texttt{tournament}$ 是一个没有自环的有向图，同时，每两个点之间有一条边连接。这就是说，对于两个点 $u,v (u\neq v)$，有一条从 $u$ 到 $v$ 的边或一条从 $v$ 到 $u$ 的边。

给你一个 $\texttt{tournament}$，请找出一个长度为 $3$ 的环。

## 输入格式

第一行一个正整数 $n$。

接下来 $n$ 行：一个 $n \times n$ 的邻接矩阵 $a$，由 `0` 和 `1` 组成。

若 $a_{i,j}=1$，表示有一条路从 $i$ 通往 $j$。

数据保证 $a_{i,i}=0$ 并且 $a_{i,j} \neq a_{j,i}$。

## 输出格式

仅一行：任意一种解决方案；若没有，输出 `-1`。

## 样例 #1

### 输入

```
5
00100
10000
01001
11101
11000

```

### 输出

```
1 3 2 
```

## 样例 #2

### 输入

```
5
01111
00000
01000
01100
01110

```

### 输出

```
-1

```



---

---
title: "Wires"
layout: "post"
diff: 提高+/省选-
pid: CF1250N
tag: ['图论']
---

# Wires

## 题目描述

Polycarpus has a complex electronic device. The core of this device is a circuit board. The board has $ 10^9 $ contact points which are numbered from $ 1 $ to $ 10^9 $ . Also there are $ n $ wires numbered from $ 1 $ to $ n $ , each connecting two distinct contact points on the board. An electric signal can pass between wires $ A $ and $ B $ if:

- either both wires share the same contact point;
- or there is a sequence of wires starting with $ A $ and ending with $ B $ , and each pair of adjacent wires in the sequence share a contact point.

 ![](https://cdn.luogu.com.cn/upload/vjudge_pic/CF1250N/6e2b2c43d3bbdc24d7f958ca966b6424ae4f2ebd.png)The picture shows a circuit board with $ 5 $ wires. Contact points with numbers $ 2, 5, 7, 8, 10, 13 $ are used. Here an electrical signal can pass from wire $ 2 $ to wire $ 3 $ , but not to wire $ 1 $ .Currently the circuit board is broken. Polycarpus thinks that the board could be fixed if the wires were re-soldered so that a signal could pass between any pair of wires.

It takes $ 1 $ minute for Polycarpus to re-solder an end of a wire. I.e. it takes one minute to change one of the two contact points for a wire. Any contact point from range $ [1, 10^9] $ can be used as a new contact point. A wire's ends must always be soldered to distinct contact points. Both wire's ends can be re-solded, but that will require two actions and will take $ 2 $ minutes in total.

Find the minimum amount of time Polycarpus needs to re-solder wires so that a signal can pass between any pair of wires. Also output an optimal sequence of wire re-soldering.

## 输入格式

The input contains one or several test cases. The first input line contains a single integer $ t $ — number of test cases. Then, $ t $ test cases follow.

The first line of each test case contains a single integer $ n $ ( $ 1 \le n \le 10^5 $ ) — the number of wires. The following $ n $ lines describe wires, each line containing two space-separated integers $ x_i, y_i $ ( $ 1 \le x_i, y_i \le 10^9 $ , $ x_i \neq y_i $ ) — contact points connected by the $ i $ -th wire. A couple of contact points can be connected with more than one wire.

Sum of values of $ n $ across all test cases does not exceed $ 10^5 $ .

## 输出格式

For each test case first print one line with a single integer $ k $ — the minimum number of minutes needed to re-solder wires so that a signal can pass between any pair of wires. In the following $ k $ lines print the description of re-solderings. Each re-soldering should be described by three integers $ w_j, a_j, b_j $ ( $ 1 \le w_j \le n $ , $ 1 \le a_j, b_j \le 10^9 $ ). Such triple means that during the $ j $ -th re-soldering an end of the $ w_j $ -th wire, which was soldered to contact point $ a_j $ , becomes soldered to contact point $ b_j $ instead. After each re-soldering of a wire it must connect two distinct contact points. If there are multiple optimal re-solderings, print any of them.

## 样例 #1

### 输入

```
2
1
4 7
4
1 2
2 3
4 5
5 6

```

### 输出

```
0
1
2 3 5

```



---

---
title: "AND-MEX Walk"
layout: "post"
diff: 提高+/省选-
pid: CF1659E
tag: ['图论', '并查集', '位运算']
---

# AND-MEX Walk

## 题目描述

There is an undirected, connected graph with $ n $ vertices and $ m $ weighted edges. A walk from vertex $ u $ to vertex $ v $ is defined as a sequence of vertices $ p_1,p_2,\ldots,p_k $ (which are not necessarily distinct) starting with $ u $ and ending with $ v $ , such that $ p_i $ and $ p_{i+1} $ are connected by an edge for $ 1 \leq i < k $ .

We define the length of a walk as follows: take the ordered sequence of edges and write down the weights on each of them in an array. Now, write down the bitwise AND of every nonempty prefix of this array. The length of the walk is the MEX of all these values.

More formally, let us have $ [w_1,w_2,\ldots,w_{k-1}] $ where $ w_i $ is the weight of the edge between $ p_i $ and $ p_{i+1} $ . Then the length of the walk is given by $ \mathrm{MEX}(\{w_1,\,w_1\& w_2,\,\ldots,\,w_1\& w_2\& \ldots\& w_{k-1}\}) $ , where $ \& $ denotes the [bitwise AND operation](https://en.wikipedia.org/wiki/Bitwise_operation#AND).

Now you must process $ q $ queries of the form u v. For each query, find the minimum possible length of a walk from $ u $ to $ v $ .

The MEX (minimum excluded) of a set is the smallest non-negative integer that does not belong to the set. For instance:

- The MEX of $ \{2,1\} $ is $ 0 $ , because $ 0 $ does not belong to the set.
- The MEX of $ \{3,1,0\} $ is $ 2 $ , because $ 0 $ and $ 1 $ belong to the set, but $ 2 $ does not.
- The MEX of $ \{0,3,1,2\} $ is $ 4 $ because $ 0 $ , $ 1 $ , $ 2 $ and $ 3 $ belong to the set, but $ 4 $ does not.

## 输入格式

The first line contains two integers $ n $ and $ m $ ( $ 2 \leq n \leq 10^5 $ ; $ n-1 \leq m \leq \min{\left(\frac{n(n-1)}{2},10^5\right)} $ ).

Each of the next $ m $ lines contains three integers $ a $ , $ b $ , and $ w $ ( $ 1 \leq a, b \leq n $ , $ a \neq b $ ; $ 0 \leq w < 2^{30} $ ) indicating an undirected edge between vertex $ a $ and vertex $ b $ with weight $ w $ . The input will not contain self-loops or duplicate edges, and the provided graph will be connected.

The next line contains a single integer $ q $ ( $ 1 \leq q \leq 10^5 $ ).

Each of the next $ q $ lines contains two integers $ u $ and $ v $ ( $ 1 \leq u, v \leq n $ , $ u \neq v $ ), the description of each query.

## 输出格式

For each query, print one line containing a single integer — the answer to the query.

## 说明/提示

The following is an explanation of the first example.

 ![](https://cdn.luogu.com.cn/upload/vjudge_pic/CF1659E/e80c1510937e2e4c165cad1b2b45b357811161d4.png)The graph in the first example.Here is one possible walk for the first query:

 $ $$$1 \overset{5}{\rightarrow} 3 \overset{3}{\rightarrow} 2 \overset{1}{\rightarrow} 1 \overset{5}{\rightarrow} 3 \overset{1}{\rightarrow} 4 \overset{2}{\rightarrow} 5. $ $ </p><p>The array of weights is  $ w=\[5,3,1,5,1,2\] $ . Now if we take the bitwise AND of every prefix of this array, we get the set  $ \\{5,1,0\\} $ . The MEX of this set is  $ 2$$$. We cannot get a walk with a smaller length (as defined in the statement).

## 样例 #1

### 输入

```
6 7
1 2 1
2 3 3
3 1 5
4 5 2
5 6 4
6 4 6
3 4 1
3
1 5
1 2
5 3
```

### 输出

```
2
0
1
```

## 样例 #2

### 输入

```
9 8
1 2 5
2 3 11
3 4 10
3 5 10
5 6 2
5 7 1
7 8 5
7 9 5
10
5 7
2 5
7 1
6 4
5 2
7 6
4 1
6 2
4 7
2 8
```

### 输出

```
0
0
2
0
0
2
1
0
1
1
```



---

---
title: "Doremy's Experimental Tree"
layout: "post"
diff: 提高+/省选-
pid: CF1764F
tag: ['图论', '并查集', '构造']
---

# Doremy's Experimental Tree

## 题目描述

Doremy has an edge-weighted tree with $ n $ vertices whose weights are integers between $ 1 $ and $ 10^9 $ . She does $ \frac{n(n+1)}{2} $ experiments on it.

In each experiment, Doremy chooses vertices $ i $ and $ j $ such that $ j \leq i $ and connects them directly with an edge with weight $ 1 $ . Then, there is exactly one cycle (or self-loop when $ i=j $ ) in the graph. Doremy defines $ f(i,j) $ as the sum of lengths of shortest paths from every vertex to the cycle.

Formally, let $ \mathrm{dis}_{i,j}(x,y) $ be the length of the shortest path between vertex $ x $ and $ y $ when the edge $ (i,j) $ of weight $ 1 $ is added, and $ S_{i,j} $ be the set of vertices that are on the cycle when edge $ (i,j) $ is added. Then,
 $$ f(i,j)=\sum_{x=1}^{n}\left(\min_{y\in S_{i,j}}\mathrm{dis}_{i,j}(x,y)\right).  $$
 
 Doremy writes down all values of  $ f(i,j) $  such that  $ 1 \leq j \leq i \leq n $ , then goes to sleep. However, after waking up, she finds that the tree has gone missing. Fortunately, the values of  $ f(i,j) $  are still in her notebook, and she knows which  $ i $  and  $ j $  they belong to. Given the values of  $ f(i,j)$, can you help her restore the tree?

It is guaranteed that at least one suitable tree exists.

## 输入格式

The first line of input contains a single integer $ n $ ($ 2 \le n \le 2000 $) — the number of vertices in the tree.

The following $ n $ lines contain a lower-triangular matrix with $ i $ integers on the $ i $ -th line; the $ j $ -th integer on the $ i $ -th line is $ f(i,j) $ ( $ 0 \le f(i,j) \le 2\cdot 10^{15} $ ).

It is guaranteed that there exists a tree whose weights are integers between $ 1 $ and $ 10^9 $ such that the values of $ f(i,j) $ of the tree match those given in the input.

## 输出格式

Print $ n-1 $ lines describing the tree. In the $ i $ -th line of the output, output three integers $ u_i $ , $ v_i $ , $ w_i $ ( $ 1 \le u_i,v_i \le n $ , $ 1 \le w_i \le 10^9 $ ), representing an edge $ (u_i,v_i) $ whose weight is $ w_i $ .

If there are multiple answers, you may output any.

All edges must form a tree and all values of $ f(i,j) $ must match those given in the input.

## 说明/提示

In the first test case, the picture below, from left to right, from top to bottom, shows the graph when pairs $ (1,1) $ , $ (1,2) $ , $ (1,3) $ , $ (2,2) $ , $ (2,3) $ , $ (3,3) $ are connected with an edge, respectively. The nodes colored yellow are on the cycle.

![](https://cdn.luogu.com.cn/upload/vjudge_pic/CF1764F/65b459471236cb3c4f73ac2ff04b74120b42f624.png)

## 样例 #1

### 输入

```
3
7
3 5
0 2 8
```

### 输出

```
2 3 3
1 2 2
```

## 样例 #2

### 输入

```
9
8081910646
8081902766 8081903751
8081902555 8081903540 8081905228
3090681001 3090681986 3090681775 7083659398
7083657913 7083658898 7083658687 2092437133 15069617722
1748216295 1748217280 1748217069 5741194692 749972427 10439821163
2377558289 2377559274 2377559063 6370536686 1379314421 5028071980 8866466178
1746983932 1746984917 1746984706 5739962329 748740064 10438588800 5026839617 10448447704
2341942133 2341943118 2341942907 6334920530 1343698265 4992455824 8830850022 4991223461 9115779270
```

### 输出

```
1 2 985
2 3 211
2 4 998244353
2 5 998244853
4 6 671232353
6 8 1232363
4 7 356561356
7 9 35616156
```



---

---
title: "C+K+S"
layout: "post"
diff: 提高+/省选-
pid: CF2023C
tag: ['图论', '哈希 hashing']
---

# C+K+S

## 题目描述

# 题面
给您两个强连接 $^{1}$ 有向图，每个图都有恰好 $n$ 个顶点，但可能有不同数量的边。仔细观察后，您发现了一个重要特征--这两个图中任何一个循环的长度都能被 $k$ 整除。

每个 $2n$ 顶点都属于两种类型中的一种：传入或传出。每个顶点的类型都是已知的。

您需要确定是否有可能在源图之间绘制恰好 $n$ 条有向边，从而满足以下四个条件：

- 任何添加的边的两端都位于不同的图中。
- 从每个传出顶点，正好有一条新增边产生。
- 在每个进入的顶点中，正好有一条添加边进入。
- 在生成的图中，任何循环的长度都能被 $k$ 整除。

$^{1}$强连接图是指从每个顶点到其他顶点都有一条路径的图。

## 输入格式

**输入**

每个测试由多个测试用例组成。第一行包含一个整数 $t$ ( $1 \le t \le 10^4$ )--测试用例数。测试用例说明如下。

每个测试用例的第一行包含两个整数 $n$ 和 $k$ （ $2 \le k \le n \le 2 \cdot 10^5$ ）--每个图形的顶点数和每个循环的长度可整除的值。

每个测试用例的第二行包含 $n$ 个整数 $a_1, a_2, \ldots, a_n$ ( $a_i \in \{0, 1\}$ )。如果 $a_i = 0$ ，则第一个图形的顶点 $i$ 进入。如果是 $a_i = 1$ ，那么第一个图形的顶点 $i$ 是传出的。

每个测试用例的第三行包含一个整数 $m_1$ ( $1 \le m_1 \le 5 \cdot 10^5$ ) - 第一个图中的边数。

接下来的 $m_1$ 行包含对第一个图的边的描述。其中 $i$ 行包含两个整数 $v_i$ 和 $u_i$ （ $1 \le v_i, u_i \le n$ ）--第一个图形中从顶点 $v_i$ 到顶点 $u_i$ 的一条边。

接下来以同样的格式描述第二个图形。

下一行包含 $n$ 个整数 $b_1, b_2, \ldots, b_n$ ( $b_i \in \{0, 1\}$ )。如果是 $b_i = 0$ ，那么第二个图形的顶点 $i$ 是进入的。如果是 $b_i = 1$ ，那么第二个图形的顶点 $i$ 是传出的。

下一行包含一个整数 $m_2$ ( $1 \le m_2 \le 5 \cdot 10^5$ )--第二个图形中的边数。

接下来的 $m_2$ 行包含对第二个图的边的描述。其中 $i$ 行包含两个整数 $v_i$ 和 $u_i$ （ $1 \le v_i, u_i \le n$ ）--第二个图中从顶点 $v_i$ 到顶点 $u_i$ 的一条边。

可以保证这两个图都是强连接的，并且所有循环的长度都能被 $k$ 整除。

保证所有测试案例中 $n$ 的总和不超过 $2 \cdot 10^5$ 。保证所有测试用例中 $m_1$ 与 $m_2$ 之和不超过 $5 \cdot 10^5$ 。

## 输出格式

**输出**

对于每个测试用例，如果可以绘制 $n$ 条新边且满足所有条件，则输出 "YES"（不带引号），否则输出 "NO"（不带引号）。

您可以输出任何情况下的答案（例如，字符串 "yEs"、"yes"、"Yes "和 "YES "将被视为肯定答案）。

# 样例解释
**注**

在第一个测试用例中，从第一个图到第二个图的边可以绘制为 $(1, 3)$ 和 $(4, 2)$ （这对边中的第一个数字是第一个图中的顶点编号，这对边中的第二个数字是第二个图中的顶点编号），从第二个图到第一个图的边可以绘制为 $(1, 2)$ 和 $(4, 3)$ （这对边中的第一个数字是第二个图中的顶点编号，这对边中的第二个数字是第一个图中的顶点编号）。

在第二个测试案例中，共有 $4$ 个进入顶点和 $2$ 个离开顶点，因此无法绘制 $3$ 条边。

## 样例 #1

### 输入

```
3
4 2
1 0 0 1
4
1 2
2 3
3 4
4 1
1 0 0 1
4
1 3
3 2
2 4
4 1
3 3
0 0 0
3
1 2
2 3
3 1
1 1 0
3
1 2
2 3
3 1
4 2
1 1 1 1
4
1 2
2 3
3 4
4 1
0 0 0 0
6
1 2
2 1
1 3
3 1
1 4
4 1
```

### 输出

```
YES
NO
YES
```



---

---
title: "Choose Your Queries"
layout: "post"
diff: 提高+/省选-
pid: CF2025F
tag: ['图论', '构造']
---

# Choose Your Queries

## 题目描述

You are given an array $ a $ , consisting of $ n $ integers (numbered from $ 1 $ to $ n $ ). Initially, they are all zeroes.

You have to process $ q $ queries. The $ i $ -th query consists of two different integers $ x_i $ and $ y_i $ . During the $ i $ -th query, you have to choose an integer $ p $ (which is either $ x_i $ or $ y_i $ ) and an integer $ d $ (which is either $ 1 $ or $ -1 $ ), and assign $ a_p = a_p + d $ .

After each query, every element of $ a $ should be a non-negative integer.

Process all queries in such a way that the sum of all elements of $ a $ after the last query is the minimum possible.

## 输入格式

The first line contains two integers $ n $ and $ q $ ( $ 2 \le n \le 3 \cdot 10^5 $ ; $ 1 \le q \le 3 \cdot 10^5 $ ) — the number of elements in $ a $ and the number of queries, respectively.

Then $ q $ lines follow. The $ i $ -th of these lines contains two integers $ x_i $ and $ y_i $ ( $ 1 \le x_i, y_i \le n $ ; $ x_i \ne y_i $ ) — the description of the $ i $ -th query.

## 输出格式

For each query, print a line containing two characters:

- the first character should be x if you choose $ p=x_i $ , or y if you choose $ p=y_i $ ;
- the second character should be + if you choose $ d=1 $ , or - if you choose $ d=-1 $ .

If there are multiple answers, print any of them.

## 样例 #1

### 输入

```
3 4
1 2
3 2
3 1
1 2
```

### 输出

```
y+
x+
x-
y-
```

## 样例 #2

### 输入

```
4 4
1 2
2 3
3 4
3 2
```

### 输出

```
y+
y+
x-
y-
```

## 样例 #3

### 输入

```
4 2
2 1
4 3
```

### 输出

```
y+
x+
```



---

---
title: "Matrix Transformation"
layout: "post"
diff: 提高+/省选-
pid: CF2043E
tag: ['图论', '贪心', '位运算']
---

# Matrix Transformation

## 题目描述

给定两个大小为 $n \times m$ 的矩阵 $A$ 和 $B$，其中元素是 $0$ 到 $10^9$ 之间的整数。你可以对矩阵 $A$ 执行以下任意次数的操作，且操作顺序不受限制：

- **按位与操作**：选择某一行 $i$ 和一个非负整数 $x$，将这一行的每个元素用 $x$ 进行按位与运算。具体来说，对于行 $i$ 的每个元素 $A_{i,j}$，都替换为 $A_{i,j} \text{ & } x$。
- **按位或操作**：选择某一列 $j$ 和一个非负整数 $x$，将这一列的每个元素用 $x$ 进行按位或运算。具体来说，对于列 $j$ 的每个元素 $A_{i,j}$，都替换为 $A_{i,j} \text{ | } x$。

可以在每次操作中选择不同的 $x$ 值。

你的任务是判断是否可以通过上述操作，将矩阵 $A$ 转变为矩阵 $B$。

## 输入格式

第一行包含一个整数 $t$（$1 \le t \le 100$），表示测试用例的数量。接下来是 $t$ 组测试用例。

每个测试用例如下：

- 第一行包含两个整数 $n$ 和 $m$（$1 \le n, m \le 10^3$ 且 $n \cdot m \le 10^3$），表示矩阵 $A$ 和 $B$ 的行数和列数。
- 接下来的 $n$ 行描述矩阵 $A$，每行包含 $m$ 个整数 $A_{i,1}, A_{i,2}, \dots, A_{i,m}$，表示该行的所有元素（$0 \le A_{i,j} \le 10^9$）。
- 再接下来的 $n$ 行描述矩阵 $B$，每行包含 $m$ 个整数 $B_{i,1}, B_{i,2}, \dots, B_{i,m}$，表示该行的所有元素（$0 \le B_{i,j} \le 10^9$）。

## 输出格式

对于每个测试用例，如果可以将矩阵 $A$ 转换为矩阵 $B$，请输出 `Yes`；否则输出 `No`。输出中的字母大小写不作要求。

## 说明/提示

以第二组输入数据为例，展示如何通过操作将矩阵 $A$ 转换为矩阵 $B$：

初始状态下，矩阵 $A$ 如下：

$$
\begin{bmatrix}
10 & 10 \\
42 & 42 \\
\end{bmatrix}
$$

1. 对第一行：应用按位与操作，选择 $x = 0$，矩阵变为：

$$
\begin{bmatrix}
0 & 0 \\
42 & 42 \\
\end{bmatrix}
$$

2. 对第二行：再次应用按位与操作，选择 $x = 0$，矩阵变为：

$$
\begin{bmatrix}
0 & 0 \\
0 & 0 \\
\end{bmatrix}
$$

3. 对第一列：应用按位或操作，选择 $x = 21$，矩阵变为：

$$
\begin{bmatrix}
21 & 0 \\
21 & 0 \\
\end{bmatrix}
$$

4. 对第二列：再次应用按位或操作，选择 $x = 21$，最终矩阵为：

$$
\begin{bmatrix}
21 & 21 \\
21 & 21 \\
\end{bmatrix}
$$

通过这一系列操作，我们成功将矩阵 $A$ 转换为矩阵 $B$。

 **本翻译由 AI 自动生成**

## 样例 #1

### 输入

```
4
1 1
12
13
2 2
10 10
42 42
21 21
21 21
2 2
74 10
42 106
21 85
85 21
2 4
1 2 3 4
5 6 7 8
3 2 3 4
1 0 1 0
```

### 输出

```
Yes
Yes
No
Yes
```



---

---
title: "X Aura"
layout: "post"
diff: 提高+/省选-
pid: CF2045G
tag: ['图论', '最短路']
---

# X Aura

## 题目描述

Mount ICPC 可以被表示为一个网格，共有 $R$ 行（编号从 $1$ 到 $R$）和 $C$ 列（编号从 $1$ 到 $C$）。位于第 $r$ 行和第 $c$ 列的单元格被表示为 $(r, c)$，其高度为 $H_{r, c}$。两个单元格是相邻的，如果它们共享一条边。正式来说，$(r, c)$ 相邻于 $(r-1, c)$、$(r+1, c)$、$(r, c-1)$ 和 $(r, c+1)$，如果这些单元格存在。

你只能在相邻的单元格之间移动，每次移动都会产生一个惩罚。具有一个奇数正整数 $X$ 的气场，从高度为 $h_1$ 的单元格移动到高度为 $h_2$ 的单元格会产生 $(h_1 - h_2)^X$ 的惩罚。注意，惩罚可以是负数。

你想回答 $Q$ 个独立的场景。在每个场景中，你从起始单元格 $(R_s, C_s)$ 开始，想要移动到目标单元格 $(R_f, C_f)$，以最小的总惩罚。有些场景可能会使总惩罚变得任意小，这样的场景被称为无效的。找到从起始单元格到目标单元格的最小总惩罚，或者确定场景是否无效。

## 输入格式

第一行包含三个整数 $R$、$C$ 和 $X$（$1 \leq R, C \leq 1000$；$1 \leq X \leq 9$；$X$ 是一个奇数整数）。

接下来的 $R$ 行每行包含一个长度为 $C$ 的字符串 $H_r$。每个字符在 $H_r$ 中都是一个数字，从 $0$ 到 $9$。$H_r$ 中的第 $c$ 个字符表示单元格 $(r, c)$ 的高度，即 $H_{r, c}$。

下一行包含一个整数 $Q$（$1 \leq Q \leq 100,000$）。

接下来的 $Q$ 行每行包含四个整数 $R_s$、$C_s$、$R_f$ 和 $C_f$（$1 \leq R_s, R_f \leq R$；$1 \leq C_s, C_f \leq C$）。

## 输出格式

对于每个场景，输出以下内容在一行中。如果场景是无效的，输出“INVALID”。否则，输出一个整数，表示从起始单元格到目标单元格的最小总惩罚。

## 样例 #1

### 输入

```
3 4 1
3359
4294
3681
5
1 1 3 4
3 3 2 1
2 2 1 4
1 3 3 2
1 1 1 1
```

### 输出

```
2
4
-7
-1
0
```

## 样例 #2

### 输入

```
2 4 5
1908
2023
2
1 1 2 4
1 1 1 1
```

### 输出

```
INVALID
INVALID
```

## 样例 #3

### 输入

```
3 3 9
135
357
579
2
3 3 1 1
2 2 2 2
```

### 输出

```
2048
0
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
title: "Melody"
layout: "post"
diff: 提高+/省选-
pid: CF2110E
tag: ['图论', '欧拉回路']
---

# Melody

## 题目描述

在 2077 年，统治世界的机器人意识到人类的音乐并不那么出色，于是它们开始创作自己的音乐。

为了创作音乐，机器人拥有一种特殊的乐器，能够产生 $n$ 种不同的声音。每种声音由其音量和音高来表征。一系列声音被称为音乐。如果任意两个连续的声音仅在音量或仅在音高上有所不同，则该音乐被认为是优美的。如果任意三个连续的声音在音量或音高上相同，则该音乐被认为是单调的。

你需要创作一段优美且不单调的音乐，其中包含乐器产生的每个声音恰好一次。

## 输入格式

每个测试包含多个测试用例。第一行包含测试用例的数量 $t$（$1 \le t \le 10^4$）。接下来是测试用例的描述。

每个测试用例的第一行包含一个数字 $n$（$1 \le n \le 2 \cdot 10^5$）——乐器能够产生的声音数量。

接下来是 $n$ 行，其中第 $i$ 行包含一对数字 $v_i, p_i$（$1 \le v_i, \space p_i \le 10^9$）——第 $i$ 个声音的音量和音高。保证在所有 $n$ 个声音中不存在重复，即对于任意 $i \neq j$，至少满足 $v_i \neq v_j$ 或 $p_i \neq p_j$ 中的一个条件。

所有测试用例的 $n$ 之和不超过 $2 \cdot 10^5$。

## 输出格式

对于每个测试用例，如果能够创作出这样的音乐，输出 "YES"，并在下一行输出 $n$ 个数字——构成优美且不单调音乐的声音索引顺序。否则，输出 "NO"。

你可以以任意大小写形式输出每个字母（例如，"yEs"、"yes"、"Yes" 和 "YES" 都会被接受为肯定答案）。

## 说明/提示

在第一个测试用例中，音乐 $(239,239)-(239,179)-(179,179)-(179,239)$ 是合适的，包含了所有声音，且所有连续的声音仅在音量或音高上有所不同。

在第二个测试用例中，可以证明无法用给定的声音创作出合适的音乐。

翻译由 DeepSeek V3 完成

## 样例 #1

### 输入

```
5
4
179 239
179 179
239 179
239 239
3
1 1
2 1
3 1
1
5 7
5
1 1
1 2
2 1
2 2
99 99
7
1 1
1 3
2 1
2 2
3 1
3 2
3 3
```

### 输出

```
YES
4 3 2 1 
NO
YES
1 
NO
YES
3 4 6 7 2 1 5
```



---

---
title: "Two Arrays"
layout: "post"
diff: 提高+/省选-
pid: CF2113F
tag: ['图论', '图论建模', '欧拉回路']
---

# Two Arrays

## 题目描述

You are given two arrays $ a $ and $ b $ of length $ n $ . You can perform the following operation an unlimited number of times:

- Choose an integer $ i $ from $ 1 $ to $ n $ and swap $ a_i $ and $ b_i $ .

Let $ f(c) $ be the number of distinct numbers in array $ c $ . Find the maximum value of $ f(a) + f(b) $ . Also, output the arrays $ a $ and $ b $ after performing all operations.

## 输入格式

Each test contains multiple test cases. The first line contains the number of test cases $ t $ ( $ 1 \le t \le 10^4 $ ). The description of the test cases follows.

The first line of each test case contains a single integer $ n $ ( $ 1 \le n \le 10^5 $ ) — the length of the arrays.

The second line of each test case contains $ n $ integers $ a_1, a_2, \ldots, a_n $ ( $ 1 \le a_i \le 2n $ ) — the elements of array $ a $ .

The third line of each test case contains $ n $ integers $ b_1, b_2, \ldots, b_n $ ( $ 1 \le b_i \le 2n $ ) — the elements of array $ b $ .

It is guaranteed that the sum of $ n $ over all test cases does not exceed $ 10^5 $ .

## 输出格式

For each test case, print a single integer in the first line — the maximum value of $ f(a) + f(b) $ .

In the second line, print $ n $ integers — the elements of array $ a $ after performing the operations.

In the third line, print $ n $ integers — the elements of array $ b $ after performing the operations.

## 说明/提示

In the first test case, after applying three operations with $ i=2 $ , $ i=4 $ , and $ i=5 $ , we obtain $ a = [1, 3, 4, 5, 2] $ and $ b = [1, 2, 3, 4, 4] $ . After that, $ f(a) + f(b) = 5 + 4 = 9 $ . It can be shown that it is not possible to achieve a greater answer.

In the second test case, after applying the operations: $f([2, 3, 4, 2, 1, 5, 6]) + f([1, 2, 3, 4, 5, 6, 5]) = 6 + 6 = 12 $.

## 样例 #1

### 输入

```
3
5
1 2 4 4 4
1 3 3 5 2
7
2 2 4 4 5 5 5
1 3 3 2 1 6 6
7
12 3 3 4 5 6 4
1 2 13 8 10 13 7
```

### 输出

```
9
1 3 4 5 2 
1 2 3 4 4 
12
2 3 4 2 1 5 6 
1 2 3 4 5 6 5 
14
12 3 13 8 10 6 4 
1 2 3 4 5 13 7
```



---

---
title: "Gellyfish and Camellia Japonica"
layout: "post"
diff: 提高+/省选-
pid: CF2115B
tag: ['图论', '拓扑排序']
---

# Gellyfish and Camellia Japonica

## 题目描述

Gellyfish 有一个长度为 $n$ 的整数数组 $c$，初始状态为 $c = [a_1, a_2, \ldots, a_n]$。接下来，Gellyfish 对数组进行 $q$ 次修改。每次修改由三个整数 $x_i, y_i, z_i$ 描述，表示将 $c_{z_i}$ 的值设置为 $\min(c_{x_i}, c_{y_i})$。经过 $q$ 次修改后，数组变为 $c = [b_1, b_2, \ldots, b_n]$。  
Flower 知道最终数组 $b$ 和所有修改操作 $(x_i, y_i, z_i)$，但不知道初始数组 $a$。她希望找到任意一个满足条件的初始数组 $a$，或者判断不存在这样的 $a$。如果存在多个解，输出任意一个即可。

## 输入格式

第一行包含一个整数 $t$（$1 \le t \le 10^4$），表示测试用例的数量。  
对于每个测试用例:  
第一行包含两个整数 $n$ 和 $q$（$1 \leq n, q \leq 3 \cdot 10^5$），分别表示数组大小和修改次数。  
第二行包含 $n$ 个整数 $b_1, b_2, \ldots, b_n$（$1 \leq b_i \leq 10^9$），表示修改后的数组。  
接下来的 $q$ 行，每行包含三个整数 $x_i, y_i, z_i$（$1 \leq x_i, y_i, z_i \leq n$），描述一次修改操作。  
所有测试用例的 $n$ 之和与 $q$ 之和均不超过 $3 \cdot 10^5$。

## 输出格式

对于每个测试用例：  
如果存在初始数组 $a$，输出一行 $n$ 个整数 $a_1, a_2, \ldots, a_n$（$0 \leq a_i \leq 10^9$）。  
否则，输出一行 `-1` 。

## 说明/提示

**第一个测试用例：** 修改操作要求 $b_2 = \min(a_1, a_2)$，且 $b_1 = a_1$。但 $b_1 = 1 < b_2 = 2$，矛盾，无解。  
**第二个测试用例：** 初始数组 $a = [1, 2, 3]$ 经过两次修改后得到 $b = [1, 2, 3]$。  
**第三个测试用例：** 输出 $a = [1, 2, 3, 4, 5, 5]$ 是一个可行解。  

---  

由 DeepSeek 翻译

## 样例 #1

### 输入

```
3
2 1
1 2
2 1 2
3 2
1 2 3
2 3 2
1 2 1
6 4
1 2 2 3 4 5
5 6 6
4 5 5
3 4 4
2 3 3
```

### 输出

```
-1
1 2 3 
1 2 3 4 5 5
```



---

---
title: "Red Light, Green Light (Hard version)"
layout: "post"
diff: 提高+/省选-
pid: CF2118D2
tag: ['数学', '图论']
---

# Red Light, Green Light (Hard version)

## 题目描述

**这是问题的困难版本。不同版本的区别在于对 $k$ 和单个测试点中的 $n,q$ 总和的限制不同。**

给你一个长度为 $10^{15}$ 的长条和一个常数 $k$。在长条上有 $n$ 个格子上有一个信号灯，第 $i$ 个信号灯在格子 $p_i$ 处，同时具有一个初相 $d_i<k$。第 $i$ 个信号灯将在时刻 $z\times k+d_i,z$ 为整数时亮红灯，其他时刻亮绿灯。

时刻 $0$ 时你在某个格子处，面向正方向。每个时刻你将执行如下操作：
- 如果你所在的格子上有一个红色的信号灯，转向；
- 向你所面向的方向走一格。

你要处理 $q$ 个询问，询问给出时刻 $0$ 时你在格子 $a_i$，问时刻 $10^{100}$ 你是否已经走出长条的范围。

## 输入格式

多组数据。第一行一个整数 $t(1\le t\le 2\times 10^5)$，表示数据组数。

对于每组数据：第一行两个整数 $n,k(1\le n\le 2\times 10^5,1\le k\le 10^{15})$。\
第二行 $n$ 个整数 $p_1,p_2,\cdots,p_n(1\le p_1<p_2\cdots<p_n\le 10^{15})$。\
第三行 $n$ 个整数 $d_1,d_2,\cdots,d_n(0\le d_i<k)$。\
第四行一个整数 $q(1\le q\le 2\times 10^5)$。\
第五行 $q$ 个整数 $a_1,a_2,\cdots,a_q(1\le a_i\le 10
^{15})$。

保证单个测试点中 $\sum n,\sum q\le 2\times 10^5$。

## 输出格式

对于每组数据，输出 $q$ 行，第 $i$ 个询问结果为是则在第 $i$ 行输出 `YES`，否则输出 `NO`。你可以以任意形式输出答案（大写或小写）。例如，`yEs`，`yes`，`Yes` 和 `YES` 均是符合条件的输出。

## 说明/提示

对于第一组数据，从 $1,2,3$ 出发的情况如下：

![](https://cdn.luogu.com.cn/upload/vjudge_pic/CF2118D2/ce9b61d8441ec2687644e4fcb1ecf9c698d0d9de.png)

对于第二组数据，从 $2$ 出发的情况如下：

![](https://cdn.luogu.com.cn/upload/vjudge_pic/CF2118D2/b6fc75687c6b2b664c445b1824b01121fde0aaa1.png)

## 样例 #1

### 输入

```
4
2 2
1 4
1 0
3
1 2 3
9 4
1 2 3 4 5 6 7 8 9
3 2 1 0 1 3 3 1 1
5
2 5 6 7 8
4 2
1 2 3 4
0 0 0 0
4
1 2 3 4
3 4
1 2 3
3 1 1
3
1 2 3
```

### 输出

```
YES
NO
YES
YES
YES
YES
NO
NO
YES
YES
NO
NO
YES
NO
YES
```



---

---
title: "Book of Evil"
layout: "post"
diff: 提高+/省选-
pid: CF337D
tag: ['动态规划 DP', '图论']
---

# Book of Evil

## 题目描述

Paladin Manao caught the trail of the ancient Book of Evil in a swampy area. This area contains $ n $ settlements numbered from 1 to $ n $ . Moving through the swamp is very difficult, so people tramped exactly $ n-1 $ paths. Each of these paths connects some pair of settlements and is bidirectional. Moreover, it is possible to reach any settlement from any other one by traversing one or several paths.

The distance between two settlements is the minimum number of paths that have to be crossed to get from one settlement to the other one. Manao knows that the Book of Evil has got a damage range $ d $ . This means that if the Book of Evil is located in some settlement, its damage (for example, emergence of ghosts and werewolves) affects other settlements at distance $ d $ or less from the settlement where the Book resides.

Manao has heard of $ m $ settlements affected by the Book of Evil. Their numbers are $ p_{1},p_{2},...,p_{m} $ . Note that the Book may be affecting other settlements as well, but this has not been detected yet. Manao wants to determine which settlements may contain the Book. Help him with this difficult task.

## 输入格式

The first line contains three space-separated integers $ n $ , $ m $ and $ d $ ( $ 1<=m<=n<=100000; 0<=d<=n-1 $ ). The second line contains $ m $ distinct space-separated integers $ p_{1},p_{2},...,p_{m} $ ( $ 1<=p_{i}<=n $ ). Then $ n-1 $ lines follow, each line describes a path made in the area. A path is described by a pair of space-separated integers $ a_{i} $ and $ b_{i} $ representing the ends of this path.

## 输出格式

Print a single number — the number of settlements that may contain the Book of Evil. It is possible that Manao received some controversial information and there is no settlement that may contain the Book. In such case, print 0.

## 说明/提示

Sample 1. The damage range of the Book of Evil equals 3 and its effects have been noticed in settlements 1 and 2. Thus, it can be in settlements 3, 4 or 5.

 ![](https://cdn.luogu.com.cn/upload/vjudge_pic/CF337D/bb5982168a46056c0b6c7bf34dd6accd73b10df3.png)

## 样例 #1

### 输入

```
6 2 3
1 2
1 5
2 3
3 4
4 5
5 6

```

### 输出

```
3

```



---

---
title: "Information Graph"
layout: "post"
diff: 提高+/省选-
pid: CF466E
tag: ['图论', '并查集']
---

# Information Graph

## 题目描述

在某公司中有n名员工（编号为1至n），开始时员工之间没有任何关系，在接下来的m天会发生以下事：

1.y成为了x的上司（x在那之前不会有上司）

2.员工x得到了一份文件，然后x把文件传给了他的上司，然后上司又传给了他的上司，以此类推，直到某人没有上司，将文件销毁

3.询问x是否看过某份文件。



1.	如果t=1，然后读入两个整数x,y（1<=x,y<=n）表示员工编号，y成为了x的上司，保证这时x不会有上司。


3.	如果t=3，然后读入两个整数x，i，表示查询员工x是否阅读过文件i，保证i已经被输入。(就是不会出现这份文件还没被任何人读过的情况)。

 保证输入至少有一个第三种类型的操作。

## 输出格式

对于每一个操作3，如果这个员工阅读过这份文件则输出“YES”（不加引号），否则输出“NO”（不加引号）。（注意换行）。

## 样例 #1

### 输入

```
4 9
1 4 3
2 4
3 3 1
1 2 3
2 2
3 1 2
1 3 1
2 2
3 1 3

```

### 输出

```
YES
NO
YES

```



---

---
title: "Mr. Kitayuta's Colorful Graph"
layout: "post"
diff: 提高+/省选-
pid: CF506D
tag: ['图论', '并查集', '分块']
---

# Mr. Kitayuta's Colorful Graph

## 题目描述

给出一个 $n$ 个点，$m$ 条边的无向图，每条边上是有颜色的。有 $q$ 组询问

对于第 $i$ 组询问，给出点对 $u_i,v_i$， 求有多少种颜色 $c$，满足存在至少一条从 $u_i$ 到 $v_i$ 的路径，使得该路径上的所有边的颜色均为 $c$。

## 输入格式

第一行两个整数 $n,m$ 分别表示点的个数和边的个数  
接下来 $m$ 行，每行三个整数 $x_i,y_i,c_i$，表示有一条连接点 $x_i,y_i$ 的边，且该边的颜色为 $c_i$

接下来一行一个整数 $q$，表示询问的个数

接下来 $q$ 行，每行两个整数 $u_i,v_i$，表示一组询问

## 输出格式

对于每一组询问，在单独的一行输出对应的答案

## 说明/提示

$2 \le n \le 10^5$  
$1 \le m,q \le 10^5$  
$1\le x_i,y_i,u_i,v_i \le n$  
$1 \le c_i \le m$

## 样例 #1

### 输入

```
4 5
1 2 1
1 2 2
2 3 1
2 3 3
2 4 3
3
1 2
3 4
1 4

```

### 输出

```
2
1
0

```

## 样例 #2

### 输入

```
5 7
1 5 1
2 5 1
3 5 1
4 5 1
1 2 2
2 3 2
3 4 2
5
1 5
5 1
2 5
1 5
1 4

```

### 输出

```
1
1
1
1
2

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
title: "Buy a Ticket"
layout: "post"
diff: 提高+/省选-
pid: CF938D
tag: ['图论建模', '最短路']
---

# Buy a Ticket

## 题目描述

Musicians of a popular band "Flayer" have announced that they are going to "make their exit" with a world tour. Of course, they will visit Berland as well.

There are $ n $ cities in Berland. People can travel between cities using two-directional train routes; there are exactly $ m $ routes, $ i $ -th route can be used to go from city $ v_{i} $ to city $ u_{i} $ (and from $ u_{i} $ to $ v_{i} $ ), and it costs $ w_{i} $ coins to use this route.

Each city will be visited by "Flayer", and the cost of the concert ticket in $ i $ -th city is $ a_{i} $ coins.

You have friends in every city of Berland, and they, knowing about your programming skills, asked you to calculate the minimum possible number of coins they have to pay to visit the concert. For every city $ i $ you have to compute the minimum number of coins a person from city $ i $ has to spend to travel to some city $ j $ (or possibly stay in city $ i $ ), attend a concert there, and return to city $ i $ (if $ j≠i $ ).

Formally, for every ![](https://cdn.luogu.com.cn/upload/vjudge_pic/CF938D/035d166bda223ecd5c31eb614a76bdcc9b8fe8c4.png) you have to calculate ![](https://cdn.luogu.com.cn/upload/vjudge_pic/CF938D/f2e29a8bb6e05026242d6e3afeeabb7241997635.png), where $ d(i,j) $ is the minimum number of coins you have to spend to travel from city $ i $ to city $ j $ . If there is no way to reach city $ j $ from city $ i $ , then we consider $ d(i,j) $ to be infinitely large.

## 输入格式

The first line contains two integers $ n $ and $ m $ ( $ 2<=n<=2·10^{5} $ , $ 1<=m<=2·10^{5} $ ).

Then $ m $ lines follow, $ i $ -th contains three integers $ v_{i} $ , $ u_{i} $ and $ w_{i} $ ( $ 1<=v_{i},u_{i}<=n,v_{i}≠u_{i} $ , $ 1<=w_{i}<=10^{12} $ ) denoting $ i $ -th train route. There are no multiple train routes connecting the same pair of cities, that is, for each $ (v,u) $ neither extra $ (v,u) $ nor $ (u,v) $ present in input.

The next line contains $ n $ integers $ a_{1},a_{2},...\ a_{k} $ ( $ 1<=a_{i}<=10^{12} $ ) — price to attend the concert in $ i $ -th city.

## 输出格式

Print $ n $ integers. $ i $ -th of them must be equal to the minimum number of coins a person from city $ i $ has to spend to travel to some city $ j $ (or possibly stay in city $ i $ ), attend a concert there, and return to city $ i $ (if $ j≠i $ ).

## 样例 #1

### 输入

```
4 2
1 2 4
2 3 7
6 20 1 25

```

### 输出

```
6 14 1 25 

```

## 样例 #2

### 输入

```
3 3
1 2 1
2 3 1
1 3 1
30 10 20

```

### 输出

```
12 10 12 

```



---

