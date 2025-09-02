---
title: "Chemical table"
layout: "post"
diff: 提高+/省选-
pid: CF1012B
tag: ['并查集', '概率论', '构造']
---

# Chemical table

## 题目描述

Innopolis University scientists continue to investigate the periodic table. There are $ n·m $ known elements and they form a periodic table: a rectangle with $ n $ rows and $ m $ columns. Each element can be described by its coordinates $ (r,c) $ ( $ 1<=r<=n $ , $ 1<=c<=m $ ) in the table.

Recently scientists discovered that for every four different elements in this table that form a rectangle with sides parallel to the sides of the table, if they have samples of three of the four elements, they can produce a sample of the fourth element using nuclear fusion. So if we have elements in positions $ (r_{1},c_{1}) $ , $ (r_{1},c_{2}) $ , $ (r_{2},c_{1}) $ , where $ r_{1}≠r_{2} $ and $ c_{1}≠c_{2} $ , then we can produce element $ (r_{2},c_{2}) $ .

 ![](https://cdn.luogu.com.cn/upload/vjudge_pic/CF1012B/a1ec2b34980f17dea8ef9d5c32f5d591ae712bba.png)Samples used in fusion are not wasted and can be used again in future fusions. Newly crafted elements also can be used in future fusions.

Innopolis University scientists already have samples of $ q $ elements. They want to obtain samples of all $ n·m $ elements. To achieve that, they will purchase some samples from other laboratories and then produce all remaining elements using an arbitrary number of nuclear fusions in some order. Help them to find the minimal number of elements they need to purchase.

## 输入格式

The first line contains three integers $ n $ , $ m $ , $ q $ ( $ 1<=n,m<=200000 $ ; $ 0<=q<=min(n·m,200000) $ ), the chemical table dimensions and the number of elements scientists already have.

The following $ q $ lines contain two integers $ r_{i} $ , $ c_{i} $ ( $ 1<=r_{i}<=n $ , $ 1<=c_{i}<=m $ ), each describes an element that scientists already have. All elements in the input are different.

## 输出格式

Print the minimal number of elements to be purchased.

## 说明/提示

For each example you have a picture which illustrates it.

The first picture for each example describes the initial set of element samples available. Black crosses represent elements available in the lab initially.

The second picture describes how remaining samples can be obtained. Red dashed circles denote elements that should be purchased from other labs (the optimal solution should minimize the number of red circles). Blue dashed circles are elements that can be produced with nuclear fusion. They are numbered in order in which they can be produced.

Test 1

We can use nuclear fusion and get the element from three other samples, so we don't need to purchase anything.

 ![](https://cdn.luogu.com.cn/upload/vjudge_pic/CF1012B/d0188b7b484eed4ec50dd63bc64a04ce06b65611.png)Test 2

We cannot use any nuclear fusion at all as there is only one row, so we have to purchase all missing elements.

 ![](https://cdn.luogu.com.cn/upload/vjudge_pic/CF1012B/ba8b5c94cc17a4604dd0e58fb6a66f6e2487526e.png)Test 3

There are several possible solutions. One of them is illustrated below.

Note that after purchasing one element marked as red it's still not possible to immidiately produce the middle element in the bottom row (marked as 4). So we produce the element in the left-top corner first (marked as 1), and then use it in future fusions.

 ![](https://cdn.luogu.com.cn/upload/vjudge_pic/CF1012B/5273513fe4bf0485a76591391c8b08a7edf8e9af.png)

## 样例 #1

### 输入

```
2 2 3
1 2
2 2
2 1

```

### 输出

```
0

```

## 样例 #2

### 输入

```
1 5 3
1 3
1 1
1 5

```

### 输出

```
2

```

## 样例 #3

### 输入

```
4 3 6
1 2
1 3
2 2
2 3
3 1
3 3

```

### 输出

```
1

```



---

---
title: "Trader Problem"
layout: "post"
diff: 提高+/省选-
pid: CF1618G
tag: ['并查集']
---

# Trader Problem

## 题目描述

Monocarp plays a computer game (yet again!). This game has a unique trading mechanics.

To trade with a character, Monocarp has to choose one of the items he possesses and trade it for some item the other character possesses. Each item has an integer price. If Monocarp's chosen item has price $ x $ , then he can trade it for any item (exactly one item) with price not greater than $ x+k $ .

Monocarp initially has $ n $ items, the price of the $ i $ -th item he has is $ a_i $ . The character Monocarp is trading with has $ m $ items, the price of the $ i $ -th item they have is $ b_i $ . Monocarp can trade with this character as many times as he wants (possibly even zero times), each time exchanging one of his items with one of the other character's items according to the aforementioned constraints. Note that if Monocarp gets some item during an exchange, he can trade it for another item (since now the item belongs to him), and vice versa: if Monocarp trades one of his items for another item, he can get his item back by trading something for it.

You have to answer $ q $ queries. Each query consists of one integer, which is the value of $ k $ , and asks you to calculate the maximum possible total cost of items Monocarp can have after some sequence of trades, assuming that he can trade an item of cost $ x $ for an item of cost not greater than $ x+k $ during each trade. Note that the queries are independent: the trades do not actually occur, Monocarp only wants to calculate the maximum total cost he can get.

## 输入格式

The first line contains three integers $ n $ , $ m $ and $ q $ ( $ 1 \le n, m, q \le 2 \cdot 10^5 $ ).

The second line contains $ n $ integers $ a_1, a_2, \dots, a_n $ ( $ 1 \le a_i \le 10^9 $ ) — the prices of the items Monocarp has.

The third line contains $ m $ integers $ b_1, b_2, \dots, b_m $ ( $ 1 \le b_i \le 10^9 $ ) — the prices of the items the other character has.

The fourth line contains $ q $ integers, where the $ i $ -th integer is the value of $ k $ for the $ i $ -th query ( $ 0 \le k \le 10^9 $ ).

## 输出格式

For each query, print one integer — the maximum possible total cost of items Monocarp can have after some sequence of trades, given the value of $ k $ from the query.

## 样例 #1

### 输入

```
3 4 5
10 30 15
12 31 14 18
0 1 2 3 4
```

### 输出

```
55
56
60
64
64
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
title: "Cross Swapping"
layout: "post"
diff: 提高+/省选-
pid: CF1713E
tag: ['并查集']
---

# Cross Swapping

## 题目描述

You are given a square matrix $ A $ of size $ n \times n $ whose elements are integers. We will denote the element on the intersection of the $ i $ -th row and the $ j $ -th column as $ A_{i,j} $ .

You can perform operations on the matrix. In each operation, you can choose an integer $ k $ , then for each index $ i $ ( $ 1 \leq i \leq n $ ), swap $ A_{i, k} $ with $ A_{k, i} $ . Note that cell $ A_{k, k} $ remains unchanged.

For example, for $ n = 4 $ and $ k = 3 $ , this matrix will be transformed like this:

 ![](https://cdn.luogu.com.cn/upload/vjudge_pic/CF1713E/d1b19f5b512e1f5ff57fc09bc0db3a4a06f7217c.png)The operation $ k = 3 $ swaps the blue row with the green column.You can perform this operation any number of times. Find the lexicographically smallest matrix $ ^\dagger $ you can obtain after performing arbitrary number of operations.

 $ {}^\dagger $ For two matrices $ A $ and $ B $ of size $ n \times n $ , let $ a_{(i-1) \cdot n + j} = A_{i,j} $ and $ b_{(i-1) \cdot n + j} = B_{i,j} $ . Then, the matrix $ A $ is lexicographically smaller than the matrix $ B $ when there exists an index $ i $ ( $ 1 \leq i \leq n^2 $ ) such that $ a_i < b_i $ and for all indices $ j $ such that $ 1 \leq j < i $ , $ a_j = b_j $ .

## 输入格式

The first line contains a single integer $ t $ ( $ 1 \leq t \leq 10^5 $ ) — the number of test cases.

The first line of each test case contains a single integer $ n $ ( $ 1 \leq n \leq 1000 $ ) — the size of the matrix.

The $ i $ -th line of the next $ n $ lines contains $ n $ integers $ A_{i, 1}, A_{i, 2}, \dots, A_{i, n} $ ( $ 1 \le A_{i, j} \le 10^9 $ ) — description of the matrix $ A $ .

It is guaranteed that the sum of $ n^2 $ over all test cases does not exceed $ 10^6 $ .

## 输出格式

For each test case, print $ n $ lines with $ n $ integers each — the lexicographically smallest matrix.

## 说明/提示

Note that in every picture below the matrix is transformed in such a way that the blue rows are swapped with the green columns.

In the first test case, we can perform $ 1 $ operation for $ k = 3 $ . The matrix will be transformed as below:

 ![](https://cdn.luogu.com.cn/upload/vjudge_pic/CF1713E/88f476fc46013e92b5ee2e2b1dd8db92737cd1fe.png) In the second test case, we can perform $ 2 $ operations for $ k = 1 $ and $ k = 3 $ :  ![](https://cdn.luogu.com.cn/upload/vjudge_pic/CF1713E/7dca46c6a1cae82c4c4f4ef39e7a9d0c69d58c39.png)  ![](https://cdn.luogu.com.cn/upload/vjudge_pic/CF1713E/64667956c5c35ceed44d4424defaf36a557d6e58.png)

## 样例 #1

### 输入

```
2
3
2 1 2
2 1 2
1 1 2
4
3 3 1 2
1 1 3 1
3 2 3 2
2 3 3 1
```

### 输出

```
2 1 1
2 1 1
2 2 2
3 1 1 2
3 1 2 1
3 3 3 3
2 3 2 1
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
title: "City Union"
layout: "post"
diff: 提高+/省选-
pid: CF1799E
tag: ['贪心', '并查集', '构造']
---

# City Union

## 题目描述

You are given $ n \times m $ grid. Some cells are filled and some are empty.

A city is a maximal (by inclusion) set of filled cells such that it is possible to get from any cell in the set to any other cell in the set by moving to adjacent (by side) cells, without moving into any cells not in the set. In other words, a city is a connected component of filled cells with edges between adjacent (by side) cells.

Initially, there are two cities on the grid. You want to change some empty cells into filled cells so that both of the following are satisfied:

- There is one city on the resulting grid.
- The shortest path between any two filled cells, achievable only by moving onto filled cells, is equal to the Manhattan distance between them.

The Manhattan distance between two cells $ (a, b) $ and $ (c, d) $ is equal to $ |a - c| + |b - d| $ .

Find a way to add filled cells that satisfies these conditions and minimizes the total number of filled cells.

## 输入格式

Input consists of multiple test cases. The first line contains a single integer $ t $ , the number of test cases ( $ 1 \le t \le 5000 $ ).

The first line of each test case contains two integers $ n $ and $ m $ ( $ 1 \le n, m \le 50 $ , $ nm \geq 3 $ ).

The next $ n $ lines describe the grid. The $ i $ -th line contains a string $ s_i $ of length $ m $ . $ s_{i,j} $ is '\#' if the cell in position $ (i, j) $ is filled, and '.' if it is empty.

It is guaranteed that there are exactly two cities in the initial grid.

It is guaranteed that the sum of $ n\cdot m $ over all test cases does not exceed $ 25\,000 $ .

## 输出格式

For each test case, output $ n $ lines, each containing a string of length $ m $ , describing the grid you create in the same format as the input.

If there are multiple possible answers with the minimum number of filled cells print any.

## 说明/提示

In the first test case, we can add a single filled cell between the two cities to connect them. We can verify that the second condition is satisfied.

In the second test case, we can also connect the cities with a single filled cell, while satisfying the second condition.

In the third test case, note that if we filled the 3 cells in the top left, the cities would be connected, but the second condition would not be satisfied for cells $ (4, 2) $ and $ (2, 4) $ .

## 样例 #1

### 输入

```
11
1 3
#.#
2 2
.#
#.
4 4
..##
...#
#...
##..
6 6
.##...
##....
......
....##
.....#
...###
6 5
.#..#
.#..#
.#..#
.#.##
.#...
##...
5 5
#####
#...#
#.#.#
#...#
#####
4 4
.##.
##.#
#.##
.##.
5 5
..###
....#
.....
#....
#....
5 6
.##...
##....
#....#
....##
...##.
6 5
..##.
...##
....#
#....
##...
.##..
5 4
..##
..#.
..#.
#...
#...
```

### 输出

```
###

.#
##

..##
..##
###.
##..

.##...
###...
..#...
..####
...###
...###

.####
.####
.####
.####
.#...
##...

#####
#####
#####
#####
#####

.##.
####
####
.##.

..###
..###
..#..
###..
#....

.##...
###...
######
...###
...##.

..##.
..###
..###
###..
###..
.##..

..##
..#.
..#.
###.
#...
```



---

---
title: "Large Graph"
layout: "post"
diff: 提高+/省选-
pid: CF1978F
tag: ['并查集', '数论']
---

# Large Graph

## 题目描述

Given an array $ a $ of length $ n $ . Let's construct a square matrix $ b $ of size $ n \times n $ , in which the $ i $ -th row contains the array $ a $ cyclically shifted to the right by $ (i - 1) $ . For example, for the array $ a = [3, 4, 5] $ , the obtained matrix is

 $ $$$b = \begin{bmatrix} 3 & 4 & 5 \\ 5 & 3 & 4 \\ 4 & 5 & 3 \end{bmatrix} $ $ </p><p>Let's construct the following graph:</p><ul> <li> The graph contains  $ n^2 $  vertices, each of which corresponds to one of the elements of the matrix. Let's denote the vertex corresponding to the element  $ b\_{i, j} $  as  $ (i, j) $ .</li><li> We will draw an edge between vertices  $ (i\_1, j\_1) $  and  $ (i\_2, j\_2) $  if  $ |i\_1 - i\_2| + |j\_1 - j\_2| \\le k $  and  $ \\gcd(b\_{i\_1, j\_1}, b\_{i\_2, j\_2}) &gt; 1 $ , where  $ \\gcd(x, y) $  denotes the <a href="https://en.wikipedia.org/wiki/Greatest_common_divisor">greatest common divisor</a> of integers  $ x $  and  $ y $ . </li></ul><p>Your task is to calculate the number of connected components $ ^{\\dagger} $  in the obtained graph.</p><p> $ ^{\\dagger}$$$A connected component of a graph is a set of vertices in which any vertex is reachable from any other via edges, and adding any other vertex to the set violates this rule.

## 输入格式

Each test consists of multiple test cases. The first line contains a single integer $ t $ ( $ 1 \leq t \leq 10^5 $ ) — the number of test cases. The description of the test cases follows.

The first line of each test case contains two integers $ n $ and $ k $ ( $ 2 \le n \le 10^6 $ , $ 2 \le k \le 2 \cdot 10^6 $ ) — the length of the array and the parameter $ k $ .

The second line of each test case contains $ n $ integers $ a_1, a_2, \ldots, a_n $ ( $ 1 \le a_i \le 10^6 $ ) — the elements of the array $ a $ .

It is guaranteed that the sum of $ n $ over all test cases does not exceed $ 10^6 $ .

## 输出格式

For each test case, output a single integer — the number of connected components in the obtained graph.

## 说明/提示

In the first test case, the matrix $ b $ is given in the statement. The first connected component contains the vertices $ (1, 1) $ , $ (2, 2) $ , and $ (3, 3) $ . The second connected component contains the vertices $ (1, 2) $ , $ (2, 3) $ , and $ (3, 1) $ . The third connected component contains the vertices $ (1, 3) $ , $ (2, 1) $ , and $ (3, 2) $ . Thus, the graph has $ 3 $ connected components.

In the second test case, the following matrix is obtained:

 $ $$$b = \begin{bmatrix} 3 & 4 & 9 \\ 9 & 3 & 4 \\ 4 & 9 & 3 \end{bmatrix} $ $ </p><p>The first connected component contains all vertices corresponding to elements with values  $ 3 $  and  $ 9 $ . The second connected component contains all vertices corresponding to elements with the value  $ 4$$$.

In the fourth test case, all vertices are in one connected component.

## 样例 #1

### 输入

```
6
3 3
3 4 5
3 3
3 4 9
3 2
3 4 9
2 2
2 8
5 3
8 27 5 4 3
4 10
2 2 2 2
```

### 输出

```
3
2
3
1
4
1
```



---

---
title: "Max Plus Min Plus Size"
layout: "post"
diff: 提高+/省选-
pid: CF2018D
tag: ['动态规划 DP', '线段树', '并查集']
---

# Max Plus Min Plus Size

## 题目描述

[EnV - 尘龙酒馆](https://soundcloud.com/envyofficial/env-the-dusty-dragon-tavern)

----------------
给定一个由正整数组成的数组 $a_1, a_2, \ldots, a_n$ 。

你可以将数组中的一些元素涂成红色，但不能有两个相邻的红色元素（即对于 $1 \leq i \leq n-1$ 来说， $a_i$ 和 $a_{i+1}$ 中至少有一个元素不能是红色的）。

您的得分是红色元素的最大值加上红色元素的最小值，再加上红色元素的数量。请找出您能得到的最高分。

## 输入格式

每个测试包含多个测试用例。第一行包含测试用例的数量 $t$ ( $1 \le t \le 10^4$ )。对每个测试用例输入如下：

每个测试用例的第一行都包含一个整数 $n$ ( $1 \le n \le 2 \cdot 10^5$ ) ，表示数组的长度。

每个测试用例的第二行包含 $n$ 个整数 $a_1, a_2, \ldots, a_n$ ( $1 \le a_i \le 10^9$ ) 表示给定的数组。

保证所有测试用例中 $n$ 的总和不超过 $2 \cdot 10^5$ 。

## 输出格式

对于每个测试用例，输出一个整数：根据题意将某些元素染成红色后可能得到的最大分数。

**样例解释**

在第一个测试用例中，可以对数组着色如下： $[\color{red}{5}\color{black}, 4, \color{red}{5} \color{black}]$ .您的得分是 $\max([5, 5]) + \min([5, 5]) + \text{size}([5, 5]) = 5+5+2 = 12$ 。这是你能得到的最高分。

在第二个测试案例中，您可以对数组着色如下： $[4, \color{red}{5},\color{black} 4]$ .您的得分是 $\max([5]) + \min([5]) + \text{size}([5]) = 5+5+1 = 11$ 。这是你能得到的最高分。

在第三个测试案例中，您可以对数组着色如下： $[\color{red}{3}\color{black}, 3, \color{red}{3} \color{black},3, \color{red}{4}\color{black}, 1, 2, \color{red}{3}, \color{black}5, \color{red}{4} \color{black}]$ .您的得分是 $\max([3, 3, 4, 3, 4]) + \min([3, 3, 4, 3, 4]) + \text{size}([3, 3, 4, 3, 4]) = 4+3+5 = 12$ 。这是你能得到的最高分。

## 样例 #1

### 输入

```
4
3
5 4 5
3
4 5 4
10
3 3 3 3 4 1 2 3 5 4
10
17 89 92 42 29 41 92 14 70 45
```

### 输出

```
12
11
12
186
```



---

---
title: "Billetes MX (Easy Version)"
layout: "post"
diff: 提高+/省选-
pid: CF2022E1
tag: ['并查集', '位运算']
---

# Billetes MX (Easy Version)

## 题目描述

This is the easy version of the problem. In this version, it is guaranteed that $ q = 0 $ . You can make hacks only if both versions of the problem are solved.

An integer grid $ A $ with $ p $ rows and $ q $ columns is called beautiful if:

- All elements of the grid are integers between $ 0 $ and $ 2^{30}-1 $ , and
- For any subgrid, the XOR of the values at the corners is equal to $ 0 $ . Formally, for any four integers $ i_1 $ , $ i_2 $ , $ j_1 $ , $ j_2 $ ( $ 1 \le i_1 < i_2 \le p $ ; $ 1 \le j_1 < j_2 \le q $ ), $ A_{i_1, j_1} \oplus A_{i_1, j_2} \oplus A_{i_2, j_1} \oplus A_{i_2, j_2} = 0 $ , where $ \oplus $ denotes the [bitwise XOR operation](https://en.wikipedia.org/wiki/Bitwise_operation#XOR).

There is a partially filled integer grid $ G $ with $ n $ rows and $ m $ columns where only $ k $ cells are filled. Polycarp wants to know how many ways he can assign integers to the unfilled cells so that the grid is beautiful.

However, Monocarp thinks that this problem is too easy. Therefore, he will perform $ q $ updates on the grid. In each update, he will choose an unfilled cell and assign an integer to it. Note that these updates are persistent. That is, changes made to the grid will apply when processing future updates.

For each of the $ q + 1 $ states of the grid, the initial state and after each of the $ q $ queries, determine the number of ways Polycarp can assign integers to the unfilled cells so that the grid is beautiful. Since this number can be very large, you are only required to output their values modulo $ 10^9+7 $ .

## 输入格式

The first line contains $ t $ ( $ 1 \le t \le 10^4 $ ) — the number of test cases.

The first line of each test case contains four integers $ n $ , $ m $ , $ k $ and $ q $ ( $ 2 \le n, m \le 10^5 $ ; $ 0 \le k \le 10^5 $ ; $ q = 0 $ ) — the number of rows, the number of columns, the number of fixed cells, and the number of updates.

The following $ k $ lines contain three integers $ r $ , $ c $ and $ v $ ( $ 1 \le r \le n, 1 \le c \le m $ ; $ 0 \le v < 2^{30} $ ) — indicating that $ G_{r, c} $ is assigned the integer $ v $ .

The following $ q $ lines contain three integers $ r $ , $ c $ and $ v $ ( $ 1 \le r \le n, 1 \le c \le m $ ; $ 0 \le v < 2^{30} $ ) — indicating that $ G_{r, c} $ is assigned the integer $ v $ .

It is guaranteed that the pairs $ (r,c) $ over all assignments are distinct.

It is guaranteed that the sum of $ n $ , $ m $ , $ k $ and $ q $ over all test cases does not exceed $ 10^5 $ respectively.

## 输出格式

For each test case, output $ q + 1 $ lines. The $ i $ -th line of output should contain the answer of the $ i $ -th state of the grid modulo $ 10^9 + 7 $ .

## 说明/提示

In the first test case of the example, we have the following grid:

  $ 0 $  $ 6 $  $ 10 $  $ 6 $  $ 0 $  $ 12 $  $ 10 $  $ 12 $  $ ? $ It can be proven that the only valid value for tile $ (3, 3) $ is $ 0 $ .

## 样例 #1

### 输入

```
2
3 3 8 0
2 1 6
3 2 12
1 2 6
2 2 0
1 3 10
1 1 0
2 3 12
3 1 10
2 5 2 0
1 1 10
1 2 30
```

### 输出

```
1
489373567
```



---

---
title: "Billetes MX (Hard Version)"
layout: "post"
diff: 提高+/省选-
pid: CF2022E2
tag: ['并查集', '位运算']
---

# Billetes MX (Hard Version)

## 题目描述

This is the hard version of the problem. In this version, it is guaranteed that $ q \leq 10^5 $ . You can make hacks only if both versions of the problem are solved.

An integer grid $ A $ with $ p $ rows and $ q $ columns is called beautiful if:

- All elements of the grid are integers between $ 0 $ and $ 2^{30}-1 $ , and
- For any subgrid, the XOR of the values at the corners is equal to $ 0 $ . Formally, for any four integers $ i_1 $ , $ i_2 $ , $ j_1 $ , $ j_2 $ ( $ 1 \le i_1 < i_2 \le p $ ; $ 1 \le j_1 < j_2 \le q $ ), $ A_{i_1, j_1} \oplus A_{i_1, j_2} \oplus A_{i_2, j_1} \oplus A_{i_2, j_2} = 0 $ , where $ \oplus $ denotes the [bitwise XOR operation](https://en.wikipedia.org/wiki/Bitwise_operation#XOR).

There is a partially filled integer grid $ G $ with $ n $ rows and $ m $ columns where only $ k $ cells are filled. Polycarp wants to know how many ways he can assign integers to the unfilled cells so that the grid is beautiful.

However, Monocarp thinks that this problem is too easy. Therefore, he will perform $ q $ updates on the grid. In each update, he will choose an unfilled cell and assign an integer to it. Note that these updates are persistent. That is, changes made to the grid will apply when processing future updates.

For each of the $ q + 1 $ states of the grid, the initial state and after each of the $ q $ queries, determine the number of ways Polycarp can assign integers to the unfilled cells so that the grid is beautiful. Since this number can be very large, you are only required to output their values modulo $ 10^9+7 $ .

## 输入格式

The first line contains $ t $ ( $ 1 \le t \le 10^4 $ ) — the number of test cases.

The first line of each test case contains four integers $ n $ , $ m $ , $ k $ and $ q $ ( $ 2 \le n, m \le 10^5 $ ; $ 0 \le k, q \leq 10^5 $ ) — the number of rows, the number of columns, the number of fixed cells, and the number of updates.

The following $ k $ lines contain three integers $ r $ , $ c $ and $ v $ ( $ 1 \le r \le n, 1 \le c \le m $ ; $ 0 \le v < 2^{30} $ ) indicating that $ G_{r, c} $ is assigned the integer $ v $ .

The following $ q $ lines contain three integers $ r $ , $ c $ and $ v $ ( $ 1 \le r \le n, 1 \le c \le m $ ; $ 0 \le v < 2^{30} $ ) indicating that $ G_{r, c} $ is assigned the integer $ v $ .

It is guaranteed that the pairs $ (r,c) $ over all assignments are distinct.

It is guaranteed that the sum of $ n $ , $ m $ , $ k $ and $ q $ over all test cases does not exceed $ 10^5 $ respectively.

## 输出格式

For each test case, output $ q + 1 $ lines. The $ i $ -th line of output should contain the answer of the $ i $ -th state of the grid modulo $ 10^9 + 7 $ .

## 说明/提示

In the first test case of the example, we initially have the following grid:

  $ 0 $  $ 6 $  $ 10 $  $ 6 $  $ 0 $  $ 12 $  $ 10 $  $ 12 $  $ ? $ It can be proven that the only valid value for tile $ (3, 3) $ is $ 0 $ , so the first answer is $ 1 $ . For the second query, the grid does not satisfy the condition, and thus the answer is $ 0 $ .

## 样例 #1

### 输入

```
3
3 3 8 1
2 1 6
3 2 12
1 2 6
2 2 0
1 3 10
1 1 0
2 3 12
3 1 10
3 3 1
2 5 2 0
1 1 10
1 2 30
2 5 0 2
1 1 10
1 2 30
```

### 输出

```
1
0
489373567
651321892
769740174
489373567
```



---

---
title: "Connected Components"
layout: "post"
diff: 提高+/省选-
pid: CF292D
tag: ['并查集']
---

# Connected Components

## 题目描述

We already know of the large corporation where Polycarpus works as a system administrator. The computer network there consists of $ n $ computers and $ m $ cables that connect some pairs of computers. In other words, the computer network can be represented as some non-directed graph with $ n $ nodes and $ m $ edges. Let's index the computers with integers from 1 to $ n $ , let's index the cables with integers from 1 to $ m $ .

Polycarpus was given an important task — check the reliability of his company's network. For that Polycarpus decided to carry out a series of $ k $ experiments on the computer network, where the $ i $ -th experiment goes as follows:

1. Temporarily disconnect the cables with indexes from $ l_{i} $ to $ r_{i} $ , inclusive (the other cables remain connected).
2. Count the number of connected components in the graph that is defining the computer network at that moment.
3. Re-connect the disconnected cables with indexes from $ l_{i} $ to $ r_{i} $ (that is, restore the initial network).

Help Polycarpus carry out all experiments and for each print the number of connected components in the graph that defines the computer network through the given experiment. Isolated vertex should be counted as single component.

## 输入格式

The first line contains two space-separated integers $ n $ , $ m $ $ (2<=n<=500; 1<=m<=10^{4}) $ — the number of computers and the number of cables, correspondingly.

The following $ m $ lines contain the cables' description. The $ i $ -th line contains space-separated pair of integers $ x_{i} $ , $ y_{i} $ $ (1<=x_{i},y_{i}<=n; x_{i}≠y_{i}) $ — the numbers of the computers that are connected by the $ i $ -th cable. Note that a pair of computers can be connected by multiple cables.

The next line contains integer $ k $ $ (1<=k<=2·10^{4}) $ — the number of experiments. Next $ k $ lines contain the experiments' descriptions. The $ i $ -th line contains space-separated integers $ l_{i} $ , $ r_{i} $ $ (1<=l_{i}<=r_{i}<=m) $ — the numbers of the cables that Polycarpus disconnects during the $ i $ -th experiment.

## 输出格式

Print $ k $ numbers, the $ i $ -th number represents the number of connected components of the graph that defines the computer network during the $ i $ -th experiment.

## 样例 #1

### 输入

```
6 5
1 2
5 4
2 3
3 1
3 6
6
1 3
2 5
1 5
5 5
2 4
3 3

```

### 输出

```
4
5
6
3
4
2

```



---

---
title: "Reclamation"
layout: "post"
diff: 提高+/省选-
pid: CF325D
tag: ['并查集']
---

# Reclamation

## 题目描述

### 题意简述

给定一个大小为 $r \times c$ 的二维环形网格图，每一行的第 $1$ 格和第 $c$ 格同样相邻。  
现在按照给定的顺序将 $n$ 个格子变成障碍物。一个格子可以变成障碍的条件为该格子变成障碍后仍然存在一条从第 $1$ 行到第 $r$ 行的路径。如果一个格子不可以变成障碍，就跳过该操作并且继续处理接下来的格子。路径为四相邻规则。
您需要求出最多可以有多少个格子变成障碍物。

## 输入格式

第一行有三个整数 $r,c,n(1 \le r,c \le 3000, 1 \le n \le 3 \cdot 10^5)$。  
接下来 $n$ 行，每行两个正整数 $r_i , c_i$，表示将位于 $r_i $ 行，$c_i$ 列的格子变成障碍物。

## 输出格式

输出一个整数表示答案。

## 样例 #1

### 输入

```
3 4 9
2 2
3 2
2 3
3 4
3 1
1 3
2 1
1 1
1 4

```

### 输出

```
6

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
title: "Imbalance Value of a Tree"
layout: "post"
diff: 提高+/省选-
pid: CF915F
tag: ['并查集', '枚举']
---

# Imbalance Value of a Tree

## 题目描述

给定一棵树，每个顶点都被写上了一个数，第 $i$ 个顶点写上的数是 $a_i$。定义一个函数 $I(x,y)$ 表示从顶点 $x$ 到 $y$ 的简单路径上 $a_i$ 的最大值和最小值的差。

你要求出 $\sum_{i=1}^{n}\sum_{j=i}^{n}I(i,j)$。

## 输入格式

第一行一个正整数 $n(1\le n\le 10^6)$，表示树上节点个数。

第二行 $n$ 个正整数 $a_1,a_2,\cdots,a_n$，表示树上每个节点写的数值。

接下来 $n-1$ 行，每行两个正整数 $x,y$，表示一条边连接节点 $x$ 和 $y$（$1\le x,y\le n$，$x\ne y$）。保证图是一棵树。

## 输出格式

输出一个数，表示 $\sum_{i=1}^n\sum_{j=i}^nI(i,j)$。

## 样例 #1

### 输入

```
4
2 2 3 1
1 2
1 3
1 4

```

### 输出

```
6

```



---

