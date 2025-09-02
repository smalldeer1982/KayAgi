---
title: "Lucky Array"
layout: "post"
diff: 省选/NOI-
pid: CF121E
tag: ['树状数组', '枚举', '进制']
---

# Lucky Array

## 题目描述

Petya 喜欢幸运数，幸运数只包含 $4$ 和 $7$ 这两个数字。例如 $47$，$744$，$4$ 都是幸运数字，但 $5,16,467$ 不是。

Petya 有一个 $N$ 个数的数组，他想给这个数组执行 $M$ 个操作，可以分为两种操作：

1. `add l r d` 把第 $l$ 到第 $r$ 个数都加上 $d$；
2. `count l r` 统计第 $l$ 到第 $r$ 个数有多少个幸运数字。

保证所有数操作前后都不超过 $10^4$。

请你编一个程序来执行这些操作。

$1\leq N,M\leq 10^5$，$1\leq l\leq r\leq N$，$1\leq d \leq 10^4$。

## 输入格式

第一行，两个数 $N$ 和 $M$；

第二行，$N$ 个数，表示原数组；

## 输出格式

对于每个询问幸运数个数的问题，输出答案，每个占一行。

_输入输出样例在下面_

## 说明/提示

对于第一个样例：

1. 执行了 `add 1 3 2` 操作之后变成：$[4, 5, 6]$；
2. 执行了 `add 2 3 3` 操作之后变成：$[4, 8, 9]$。

对于第二个样例：

1. 执行了 `add 1 4 3` 之后变成：$[7,7,7,7]$；
2. 执行了 `add 2 3 40` 之后变成：$[7,47,47,7]$。

## 样例 #1

### 输入

```
3 6
2 3 4
count 1 3
count 1 2
add 1 3 2
count 1 3
add 2 3 3
count 1 3

```

### 输出

```
1
0
1
1

```

## 样例 #2

### 输入

```
4 5
4 4 4 4
count 1 4
add 1 4 3
count 1 4
add 2 3 40
count 1 4

```

### 输出

```
4
4
4

```



---

---
title: "Closest Pair"
layout: "post"
diff: 省选/NOI-
pid: CF1635F
tag: ['树状数组', '单调队列']
---

# Closest Pair

## 题目描述

There are $ n $ weighted points on the $ OX $ -axis. The coordinate and the weight of the $ i $ -th point is $ x_i $ and $ w_i $ , respectively. All points have distinct coordinates and positive weights. Also, $ x_i < x_{i + 1} $ holds for any $ 1 \leq i < n $ .

The weighted distance between $ i $ -th point and $ j $ -th point is defined as $ |x_i - x_j| \cdot (w_i + w_j) $ , where $ |val| $ denotes the absolute value of $ val $ .

You should answer $ q $ queries, where the $ i $ -th query asks the following: Find the minimum weighted distance among all pairs of distinct points among the points in subarray $ [l_i,r_i] $ .

## 输入格式

The first line contains 2 integers $ n $ and $ q $ $ (2 \leq n \leq 3 \cdot 10^5; 1 \leq q \leq 3 \cdot 10^5) $ — the number of points and the number of queries.

Then, $ n $ lines follows, the $ i $ -th of them contains two integers $ x_i $ and $ w_i $ $ (-10^9 \leq x_i \leq 10^9; 1 \leq w_i \leq 10^9) $ — the coordinate and the weight of the $ i $ -th point.

It is guaranteed that the points are given in the increasing order of $ x $ .

Then, $ q $ lines follows, the $ i $ -th of them contains two integers $ l_i $ and $ r_i $ $ (1 \leq l_i < r_i \leq n) $ — the given subarray of the $ i $ -th query.

## 输出格式

For each query output one integer, the minimum weighted distance among all pair of distinct points in the given subarray.

## 说明/提示

For the first query, the minimum weighted distance is between points $ 1 $ and $ 3 $ , which is equal to $ |x_1 - x_3| \cdot (w_1 + w_3) = |-2 - 1| \cdot (2 + 1) = 9 $ .

For the second query, the minimum weighted distance is between points $ 2 $ and $ 3 $ , which is equal to $ |x_2 - x_3| \cdot (w_2 + w_3) = |0 - 1| \cdot (10 + 1) = 11 $ .

For the fourth query, the minimum weighted distance is between points $ 3 $ and $ 4 $ , which is equal to $ |x_3 - x_4| \cdot (w_3 + w_4) = |1 - 9| \cdot (1 + 2) = 24 $ .

## 样例 #1

### 输入

```
5 5
-2 2
0 10
1 1
9 2
12 7
1 3
2 3
1 5
3 5
2 4
```

### 输出

```
9
11
9
24
11
```



---

---
title: "MCMF?"
layout: "post"
diff: 省选/NOI-
pid: CF1682F
tag: ['树状数组']
---

# MCMF?

## 题目描述

You are given two integer arrays $ a $ and $ b $ ( $ b_i \neq 0 $ and $ |b_i| \leq 10^9 $ ). Array $ a $ is sorted in non-decreasing order.

The cost of a subarray $ a[l:r] $ is defined as follows:

- If $  \sum\limits_{j = l}^{r} b_j \neq 0 $ , then the cost is not defined.
- Otherwise:
  
  
  - Construct a bipartite flow graph with $ r-l+1 $ vertices, labeled from $ l $ to $ r $ , with all vertices having $ b_i \lt 0 $ on the left and those with $ b_i \gt 0 $ on right. For each $ i, j $ such that $ l \le i, j \le r $ , $ b_i<0 $ and $ b_j>0 $ , draw an edge from $ i $ to $ j $ with infinite capacity and cost of unit flow as $ |a_i-a_j| $ .
  - Add two more vertices: source $ S $ and sink $ T $ .
  - For each $ i $ such that $ l \le i \le r $ and $ b_i<0 $ , add an edge from $ S $ to $ i $ with cost $ 0 $ and capacity $ |b_i| $ .
  - For each $ i $ such that $ l \le i \le r $ and $ b_i>0 $ , add an edge from $ i $ to $ T $ with cost $ 0 $ and capacity $ |b_i| $ .
  - The cost of the subarray is then defined as the minimum cost of maximum flow from $ S $ to $ T $ .

You are given $ q $ queries in the form of two integers $ l $ and $ r $ . You have to compute the cost of subarray $ a[l:r] $ for each query, modulo $ 10^9 + 7 $ .

If you don't know what the minimum cost of maximum flow means, read [here](https://en.wikipedia.org/wiki/Minimum-cost_flow_problem).

## 输入格式

The first line of input contains two integers $ n $ and $ q $ $ (2 \leq n \leq 2\cdot 10^5, 1 \leq q \leq 2\cdot10^5) $ — length of arrays $ a $ , $ b $ and the number of queries.

The next line contains $ n $ integers $ a_1,a_2 \ldots a_n $ ( $ 0 \leq a_1 \le a_2 \ldots \le a_n \leq 10^9) $ — the array $ a $ . It is guaranteed that $ a $ is sorted in non-decreasing order.

The next line contains $ n $ integers $ b_1,b_2 \ldots b_n $ $ (-10^9\leq b_i \leq 10^9, b_i \neq 0) $ — the array $ b $ .

The $ i $ -th of the next $ q $ lines contains two integers $ l_i,r_i $ $ (1\leq l_i \leq r_i \leq n) $ . It is guaranteed that $  \sum\limits_{j = l_i}^{r_i} b_j = 0 $ .

## 输出格式

For each query $ l_i $ , $ r_i $ — print the cost of subarray $ a[l_i:r_i] $ modulo $ 10^9 + 7 $ .

## 说明/提示

In the first query, the maximum possible flow is $ 1 $ i.e one unit from source to $ 2 $ , then one unit from $ 2 $ to $ 3 $ , then one unit from $ 3 $ to sink. The cost of the flow is $ 0 \cdot 1 + |2 - 4| \cdot 1 + 0 \cdot 1 = 2 $ .

In the second query, the maximum possible flow is again $ 1 $ i.e from source to $ 7 $ , $ 7 $ to $ 6 $ , and $ 6 $ to sink with a cost of $ 0 \cdot |10 - 10| \cdot 1 + 0 \cdot 1 = 0 $ .

In the third query, the flow network is shown on the left with capacity written over the edge and the cost written in bracket. The image on the right shows the flow through each edge in an optimal configuration.

 ![](https://cdn.luogu.com.cn/upload/vjudge_pic/CF1682F/b6040909c6a89f65b5b7d87c18e4b15cd451816a.png) Maximum flow is $ 3 $ with a cost of $ 0 \cdot 3 + 1 \cdot 1 + 4 \cdot 2 + 0 \cdot 1 + 0 \cdot 2 = 9 $ .In the fourth query, the flow network looks as –

 ![](https://cdn.luogu.com.cn/upload/vjudge_pic/CF1682F/785b5422d5947aa6cf07e9905d5c183db07a5c80.png)The minimum cost maximum flow is achieved in the configuration –

 ![](https://cdn.luogu.com.cn/upload/vjudge_pic/CF1682F/58ed2fd428ae0881741713ff33b82d81dd69edde.png)The maximum flow in the above network is 4 and the minimum cost of such flow is 15.

## 样例 #1

### 输入

```
8 4
1 2 4 5 9 10 10 13
6 -1 1 -3 2 1 -1 1
2 3
6 7
3 5
2 6
```

### 输出

```
2
0
9
15
```



---

---
title: "Diverse Segments"
layout: "post"
diff: 省选/NOI-
pid: CF1684F
tag: ['线段树', '树状数组']
---

# Diverse Segments

## 题目描述

给定长度为 $n$ 的序列 $a$，以及 $m$ 个数对 $(l_i,r_i)$。  
你可以进行下列操作至多一次：

- 选择序列 $a$ 的一个子段，并将其中的每个元素的值都改成任意整数。

你需要保证执行完操作之后，对于每个整数 $i(1\leq i\leq m)$，都有 $a[l_i,r_i]$ 中所有元素互不相同。  
你需要最小化操作时选择的子段的长度，并求出这个长度的最小值。  
特别的如果没有必要进行操作，答案为 $0$。

## 输入格式

第一行输入一个整数 $t(1\leq t\leq100)$ 表示数据组数，接下来对于每组数据：  
第一行输入两个整数 $n,m(1\leq n,m,\sum n,\sum m\leq2\times10^5)$ 表示序列长度和给定的数对数。  
接下来一行输入 $n$ 个整数表示 $a_1,a_2,\cdots,a_n(1\leq a_i\leq10^9)$。  
接下来输入 $m$ 行，其中第 $i$ 行输入两个整数表示 $l_i,r_i(1\leq l_i\leq r_i\leq n)$。

## 输出格式

对于每组数据：  
输出进行操作的子段的长度的最小值。

### 样例解释

对于第一组数据，我们可以选择子段 $[1,2]$ 并将序列改成 $[114,514,2,1,3,3,5]$，此时：

- 对于第一个数对 $(1,4)$，我们有 $a[1,4]=[114,514,2,1]$。
- 对于第二个数对 $(4,5)$，我们有 $a[4,5]=[1,3]$。  
- 对于第三个数对 $(2,4)$，我们有 $a[2,4]=[514,2,1]$。

显然每个数对都满足要求，且我们可以证明没有更优的答案，因此答案为 $2$。  
对于第二组数据，我们没有必要进行操作。  
对于第三组数据，我们可以选择子段 $[1,1]$ 并将序列改成 $[1,7,5,6]$。

## 样例 #1

### 输入

```
5
7 3
1 1 2 1 3 3 5
1 4
4 5
2 4
5 2
10 1 6 14 1
4 5
2 4
4 5
5 7 5 6
2 2
1 3
2 4
3 3
3 4
7 3
2 2 2 7 8 2 2
4 4
4 4
5 5
1 1
123
1 1
```

### 输出

```
2
0
1
0
0
```



---

---
title: "LCM Sum (hard version)"
layout: "post"
diff: 省选/NOI-
pid: CF1712E2
tag: ['线段树', '树状数组', '数论']
---

# LCM Sum (hard version)

## 题目描述

We are sum for we are many

Some Number



This version of the problem differs from the previous one only in the constraint on $ t $ . You can make hacks only if both versions of the problem are solved.

You are given two positive integers $ l $ and $ r $ .

Count the number of distinct triplets of integers $ (i, j, k) $ such that $ l \le i < j < k \le r $ and $ \operatorname{lcm}(i,j,k) \ge i + j + k $ .

Here $ \operatorname{lcm}(i, j, k) $ denotes the [least common multiple (LCM)](https://en.wikipedia.org/wiki/Least_common_multiple) of integers $ i $ , $ j $ , and $ k $ .

## 输入格式

Each test contains multiple test cases. The first line contains the number of test cases $ t $ ( $ \bf{1 \le t \le 10^5} $ ). Description of the test cases follows.

The only line for each test case contains two integers $ l $ and $ r $ ( $ 1 \le l \le r \le 2 \cdot 10^5 $ , $ l + 2 \le r $ ).

## 输出格式

For each test case print one integer — the number of suitable triplets.

## 说明/提示

In the first test case, there are $ 3 $ suitable triplets:

- $ (1,2,3) $ ,
- $ (1,3,4) $ ,
- $ (2,3,4) $ .

In the second test case, there is $ 1 $ suitable triplet:

- $ (3,4,5) $ .

## 样例 #1

### 输入

```
5
1 4
3 5
8 86
68 86
6 86868
```

### 输出

```
3
1
78975
969
109229059713337
```



---

---
title: "Kazaee"
layout: "post"
diff: 省选/NOI-
pid: CF1746F
tag: ['树状数组', '哈希 hashing']
---

# Kazaee

## 题目描述

给出一个长度为 $n$ 的数组 $a$ 和以下两种操作：

- $1\ i\ x$：将 $a_i$ 修改为 $x$。
- $2\ l\ r\ k$：询问在数组区间 $[l, r]$ 内是否每个出现过的正整数的出现次数都是 $k$ 的倍数。（建议参照样例理解）若是则输出 `YES`，若否则输出 `NO`。

## 输入格式

第一行两个整数 $n$、$q$，表示数组长度和操作数。

第二行 $n$ 个整数，为数组 $a$ 中的元素。（下标从1开始）

之后 $q$ 行，每行一个询问。

## 输出格式

对于每个操作2，给出相应答案（YES 或 NO）。

## 样例 #1

### 输入

```
10 8
1234 2 3 3 2 1 1 2 3 4
2 1 6 2
1 1 1
2 1 6 2
2 1 9 2
1 10 5
2 1 9 3
1 3 5
2 3 10 2
```

### 输出

```
NO
YES
NO
YES
YES
```



---

---
title: "Nobody is needed"
layout: "post"
diff: 省选/NOI-
pid: CF1946F
tag: ['动态规划 DP', '树状数组']
---

# Nobody is needed

## 题目描述

Oleg received a permutation $ a $ of length $ n $ as a birthday present.

Oleg's friend Nechipor asks Oleg $ q $ questions, each question is characterized by two numbers $ l $ and $ r $ , in response to the question Oleg must say the number of sets of indices $ (t_1, t_2, \ldots, t_k) $ of any length $ k \ge 1 $ such that:

- $ l \le t_i \le r $ for each $ i $ from $ 1 $ to $ k $ .
- $ t_i < t_{i+1} $ for each $ i $ from $ 1 $ to $ k-1 $ .
- $ a_{t_{i+1}} $ is divisible by $ a_{t_i} $ for each $ i $ from $ 1 $ to $ k-1 $ .

Help Oleg and answer all of Nechipor's questions.

## 输入格式

Each test consists of several sets of input data. The first line contains a single integer $ t $ ( $ 1 \le t \le 10^4 $ ) — the number of sets of input data. The description of the sets of input data follows.

The first line of each set of input data contains two integers $ n $ and $ q $ ( $ 1 \le n, q \le 10^6 $ ) — the length of the permutation and the number of Nechipor's questions.

The second line of each set of input data contains $ n $ integers $ a_1, a_2, \ldots, a_n $ ( $ 1 \le a_i \le n $ ) — the permutation $ a $ itself.

In each of the next $ q $ lines of each set of input data, there are two integers $ l $ and $ r $ ( $ 1 \le l \le r \le n $ ) — the next question of Nechipor.

It is guaranteed that the sum of the values of $ n $ and the sum of the values of $ q $ over all test cases does not exceed $ 10^6 $ .

## 输出格式

For each set of input data, output the answers to all of Nechipor's questions.

## 说明/提示

All suitable arrays in the first set of input data: ( $ 1 $ ), ( $ 2 $ ), ( $ 3 $ ), ( $ 4 $ ), ( $ 5 $ ), ( $ 6 $ ), ( $ 7 $ ), ( $ 8 $ ), ( $ 1, 3 $ ), ( $ 1, 6 $ ), ( $ 1, 7 $ ), ( $ 1, 6, 7 $ ), ( $ 2, 3 $ ), ( $ 2, 4 $ ), ( $ 2, 5 $ ), ( $ 2, 6 $ ), ( $ 2, 7 $ ), ( $ 2, 8 $ ), ( $ 2, 6, 7 $ ), ( $ 6, 7 $ ).

All suitable arrays in the fourth set of input data: ( $ 1 $ ), ( $ 2 $ ), ( $ 3 $ ), ( $ 4 $ ), ( $ 5 $ ), ( $ 6 $ ), ( $ 7 $ ), ( $ 8 $ ), ( $ 1, 2 $ ), ( $ 1, 3 $ ), ( $ 1, 4 $ ), ( $ 1, 5 $ ), ( $ 1, 6 $ ), ( $ 1, 7 $ ), ( $ 1, 8 $ ), ( $ 1, 2, 4 $ ), ( $ 1, 2, 6 $ ), ( $ 1, 2, 8 $ ), ( $ 1, 2, 4, 8 $ ), ( $ 1, 3, 6 $ ), ( $ 1, 4, 8 $ ), ( $ 2, 4 $ ), ( $ 2, 6 $ ), ( $ 2, 8 $ ), ( $ 2, 4, 8 $ ), ( $ 3, 6 $ ), ( $ 4, 8 $ ).

## 样例 #1

### 输入

```
4
8 8
2 1 6 3 5 4 8 7
1 8
2 8
1 7
1 6
1 3
5 8
4 4
2 3
1 1
1
1 1
3 3
3 2 1
1 2
1 3
2 3
8 1
1 2 3 4 5 6 7 8
1 8
```

### 输出

```
20 15 18 12 5 5 1 3
1
2 3 2
27
```



---

---
title: "Balanced Problem"
layout: "post"
diff: 省选/NOI-
pid: CF2029G
tag: ['动态规划 DP', '树状数组']
---

# Balanced Problem

## 题目描述

There is an array $ a $ consisting of $ n $ integers. Initially, all elements of $ a $ are equal to $ 0 $ .

Kevin can perform several operations on the array. Each operation is one of the following two types:

- Prefix addition — Kevin first selects an index $ x $ ( $ 1\le x\le n $ ), and then for each $ 1\le j\le x $ , increases $ a_j $ by $ 1 $ ;
- Suffix addition — Kevin first selects an index $ x $ ( $ 1\le x\le n $ ), and then for each $ x\le j\le n $ , increases $ a_j $ by $ 1 $ .

In the country of KDOI, people think that the integer $ v $ is balanced. Thus, Iris gives Kevin an array $ c $ consisting of $ n $ integers and defines the beauty of the array $ a $ as follows:

- Initially, set $ b=0 $ ;
- For each $ 1\le i\le n $ , if $ a_i=v $ , add $ c_i $ to $ b $ ;
- The beauty of $ a $ is the final value of $ b $ .

Kevin wants to maximize the beauty of $ a $ after all the operations. However, he had already performed $ m $ operations when he was sleepy. Now, he can perform an arbitrary number (possibly zero) of new operations.

You have to help Kevin find the maximum possible beauty if he optimally performs the new operations.

However, to make sure that you are not just rolling the dice, Kevin gives you an integer $ V $ , and you need to solve the problem for each $ 1\le v\le V $ .

## 输入格式

Each test contains multiple test cases. The first line of the input contains a single integer $ t $ ( $ 1\le t\le 1000 $ ) — the number of test cases. The description of test cases follows.

The first line of each test case contains three integers $ n $ , $ m $ , and $ V $ ( $ 1\le n, m\le 2\cdot 10^5 $ , $ 1\le V\le 2000 $ ) — the length of the array $ a $ , the number of initial operations, and the number that Kevin gives you.

The second line contains $ n $ integers $ c_1, c_2, \ldots, c_n $ ( $ 1\le c_i\le 10^9 $ ) — the elements in the array $ c $ .

Then $ m $ lines follow, the $ i $ -th line containing a character $ op $ and an integer $ x $ ( $ op=\mathtt{L} $ or $ \mathtt{R} $ , $ 1\le x\le n $ ) — the type of the $ i $ -th operation and the selected index.

- If $ op=\mathtt{L} $ , this operation is a prefix addition on index $ x $ ;
- If $ op=\mathtt{R} $ , this operation is a suffix addition on index $ x $ .

It is guaranteed that:

- the sum of $ n $ over all test cases does not exceed $ 2\cdot 10^5 $ ;
- the sum of $ m $ over all test cases does not exceed $ 2\cdot 10^5 $ ;
- the sum of $ V^2 $ over all test cases does not exceed $ 4\cdot 10^6 $ .

## 输出格式

For each test case, output $ V $ integers in a single line, the $ i $ -th integer denoting the maximum possible beauty after Kevin performs some new operations when $ v=i $ .

## 说明/提示

In the first test case, the array $ a $ changes as follows for the initial operations: $ [0, 0, 0] \xrightarrow{\mathtt{L}\ 3} [1, 1, 1] \xrightarrow{\mathtt{R}\ 3} [1, 1, 2] \xrightarrow{\mathtt{L}\ 1} [2, 1, 2] $ .

- For $ v=1 $ , it is optimal to not perform any new operations, and the beauty is $ b=c_2=2 $ ;
- For $ v=2 $ , it is optimal to perform a prefix addition operation on index $ 2 $ . After that, $ a $ becomes $ [3,2,2] $ , and the beauty is $ b=c_2+c_3=6 $ .

In the second test case, for both $ v=1 $ and $ v=2 $ , it is optimal to not perform any new operations.

## 样例 #1

### 输入

```
5
3 3 2
1 2 4
L 3
R 3
L 1
3 3 2
5 1 4
L 3
R 3
L 1
5 4 5
1 1 1 1 1
L 3
R 2
L 5
L 4
10 12 9
10 9 8 7 6 5 4 3 2 1
L 2
L 4
R 4
R 4
L 6
R 8
L 3
L 2
R 1
R 10
L 8
L 1
1 1 4
1000000000
L 1
```

### 输出

```
2 6
1 9
0 1 3 5 5
0 0 0 6 25 32 35 44 51
1000000000 1000000000 1000000000 1000000000
```



---

---
title: "Divide OR Conquer"
layout: "post"
diff: 省选/NOI-
pid: CF2038D
tag: ['动态规划 DP', '树状数组', '动态规划优化']
---

# Divide OR Conquer

## 题目描述

You are given an array $ [a_1, a_2, \ldots a_n] $ consisting of integers between $ 0 $ and $ 10^9 $ . You have to split this array into several segments (possibly one) in such a way that each element belongs to exactly one segment.

Let the first segment be the array $ [a_{l_1}, a_{l_1 + 1}, \ldots, a_{r_1}] $ , the second segment be $ [a_{l_2}, a_{l_2+ 1}, \ldots, a_{r_2}] $ , ..., the last segment be $ [a_{l_k}, a_{l_k+ 1}, \ldots, a_{r_k}] $ . Since every element should belong to exactly one array, $ l_1 = 1 $ , $ r_k = n $ , and $ r_i + 1 = l_{i+1} $ for each $ i $ from $ 1 $ to $ k-1 $ . The split should meet the following condition: $ f([a_{l_1}, a_{l_1 + 1}, \ldots, a_{r_1}]) \le f([a_{l_2}, a_{l_2+ 1}, \ldots, a_{r_2}]) \le \dots \le f([a_{l_k}, a_{l_k+1}, \ldots, a_{r_k}]) $ , where $ f(a) $ is the bitwise OR of all elements of the array $ a $ .

Calculate the number of ways to split the array, and print it modulo $ 998\,244\,353 $ . Two ways are considered different if the sequences $ [l_1, r_1, l_2, r_2, \ldots, l_k, r_k] $ denoting the splits are different.

## 输入格式

The first line contains an integer $ n $ ( $ 1 \le n \le 2 \cdot 10^5 $ ) — the length of the array $ a $ .

The second line contains $ n $ integers $ a_1, a_2, \ldots, a_n $ ( $ 0 \le a_i \le 10 ^9 $ ) — the elements of the given array.

## 输出格式

Print one integer — the number of ways to split the array, taken modulo $ 998\,244\,353 $ .

## 说明/提示

In the first two examples, every way to split the array is valid.

In the third example, there are three valid ways to split the array:

- $ k = 3 $ ; $ l_1 = 1, r_1 = 1, l_2 = 2, r_2 = 2, l_3 = 3, r_3 = 3 $ ; the resulting arrays are $ [3] $ , $ [4] $ , $ [6] $ , and $ 3 \le 4 \le 6 $ ;
- $ k = 2 $ ; $ l_1 = 1, r_1 = 1, l_2 = 2, r_2 = 3 $ ; the resulting arrays are $ [3] $ and $ [4, 6] $ , and $ 3 \le 6 $ ;
- $ k = 1 $ ; $ l_1 = 1, r_1 = 3 $ ; there will be only one array: $ [3, 4, 6] $ .

If you split the array into two arrays $ [3, 4] $ and $ [6] $ , the bitwise OR of the first array is $ 7 $ , and the bitwise OR of the second array is $ 6 $ ; $ 7 > 6 $ , so this way to split the array is invalid.

## 样例 #1

### 输入

```
3
1 2 3
```

### 输出

```
4
```

## 样例 #2

### 输入

```
5
1000 1000 1000 1000 1000
```

### 输出

```
16
```

## 样例 #3

### 输入

```
3
3 4 6
```

### 输出

```
3
```



---

---
title: "Skyscape"
layout: "post"
diff: 省选/NOI-
pid: CF2084F
tag: ['贪心', '线段树', '树状数组']
---

# Skyscape

## 题目描述

给定一个长度为 $n$ 的排列 $a$ $^{\text{∗}}$。

我们称一个长度为 $n$ 的排列 $b$ 是好的，如果在最多进行 $n$ 次（可以是零次）以下操作后，排列 $a$ 和 $b$ 可以变得相同：

- 选择两个整数 $l, r$，满足 $1 \le l < r \le n$ 且 $a_r = \min(a_l, a_{l + 1}, \ldots, a_r)$。
- 将子段 $[a_l, a_{l + 1}, \ldots, a_r]$ 循环右移一位。换句话说，将 $a$ 替换为：
  $$
  [a_1, \ldots, a_{l - 1}, \; a_r, a_l, a_{l + 1}, \ldots, a_{r - 1}, \; a_{r + 1}, \ldots, a_n]
  $$

同时给定一个长度为 $n$ 的排列 $c$，其中部分元素缺失（用 $0$ 表示）。

你需要找到一个好的排列 $b_1, b_2, \ldots, b_n$，使得 $b$ 可以通过填充 $c$ 中缺失的元素得到（即对于所有 $1 \le i \le n$，如果 $c_i \ne 0$，则 $b_i = c_i$）。如果不存在这样的排列，输出 $-1$。

$^{\text{∗}}$ 长度为 $n$ 的排列是指由 $1$ 到 $n$ 的 $n$ 个不同整数按任意顺序组成的数组。例如，$[2,3,1,5,4]$ 是一个排列，但 $[1,2,2]$ 不是排列（因为 $2$ 在数组中出现了两次），$[1,3,4]$ 也不是排列（因为 $n=3$ 但数组中包含 $4$）。

## 输入格式

每个测试包含多个测试用例。第一行包含测试用例的数量 $t$（$1 \le t \le 10^4$）。接下来是每个测试用例的描述。

每个测试用例的第一行包含一个整数 $n$（$2 \le n \le 5 \cdot 10^5$）。  
第二行包含 $n$ 个整数 $a_1, a_2, \ldots, a_n$（$1 \le a_i \le n$）。保证 $a$ 是一个长度为 $n$ 的排列。  
第三行包含 $n$ 个整数 $c_1, c_2, \ldots, c_n$（$0 \le c_i \le n$）。保证 $c$ 中非 $0$ 的元素互不相同。  

保证所有测试用例的 $n$ 之和不超过 $5 \cdot 10^5$。

## 输出格式

对于每个测试用例：

- 如果无法找到满足条件的好排列 $b$，输出一个整数 $-1$。
- 否则，输出 $n$ 个整数 $b_1, b_2, \ldots, b_n$——你找到的好排列 $b$。需要确保对于所有 $1 \le i \le n$，如果 $c_i \ne 0$，则 $b_i = c_i$。如果有多个解，输出任意一个即可。


## 说明/提示

- 在第一个测试用例中，$b = [1, 2]$ 是一个有效解，因为进行以下操作后 $a$ 和 $b$ 会变得相同：
  - 选择 $l = 1, r = 2$ 并循环右移子段 $[a_1, a_2]$。此时 $a$ 变为 $[1, 2]$。

- 在第二个测试用例中，$b = [2, 3, 4, 1]$ 是一个有效解，因为进行以下操作后 $a$ 和 $b$ 会变得相同：
  - 选择 $l = 1, r = 2$ 并循环右移子段 $[a_1, a_2]$。此时 $a$ 变为 $[2, 3, 4, 1]$。

- 在第三个测试用例中，$b = [1, 3, 2, 4, 5]$ 是一个有效解，因为进行以下操作后 $a$ 和 $b$ 会变得相同：
  - 选择 $l = 1, r = 3$ 并循环右移子段 $[a_1, a_2, a_3]$。此时 $a$ 变为 $[1, 3, 2, 5, 4]$。
  - 选择 $l = 4, r = 5$ 并循环右移子段 $[a_4, a_5]$。此时 $a$ 变为 $[1, 3, 2, 4, 5]$。

- 在第四个测试用例中，$b = [3, 2, 1, 5, 4]$ 是一个有效解，因为 $a$ 和 $b$ 已经相同。

- 在第五个测试用例中，不存在满足条件的好排列 $b$，因此输出 $-1$。

- 在第六个测试用例中，$b = [3, 2, 1, 5, 4, 6]$ 是一个有效解，因为进行以下操作后 $a$ 和 $b$ 会变得相同：
  - 选择 $l = 2, r = 4$ 并循环右移子段 $[a_2, a_3, a_4]$。此时 $a$ 变为 $[3, 2, 5, 6, 1, 4]$。
  - 选择 $l = 3, r = 5$ 并循环右移子段 $[a_3, a_4, a_5]$。此时 $a$ 变为 $[3, 2, 1, 5, 6, 4]$。
  - 选择 $l = 5, r = 6$ 并循环右移子段 $[a_5, a_6]$。此时 $a$ 变为 $[3, 2, 1, 5, 4, 6]$。

翻译由 DeepSeek V3 完成

## 样例 #1

### 输入

```
9
2
2 1
1 2
4
3 2 4 1
2 0 0 1
5
3 2 1 5 4
1 3 0 0 0
5
3 2 1 5 4
3 2 1 5 4
5
3 2 1 5 4
3 2 5 1 4
6
3 5 6 2 1 4
0 2 0 5 0 0
6
3 5 6 2 1 4
0 2 0 6 4 0
9
6 9 2 4 1 7 8 3 5
0 2 5 9 0 0 0 8 0
9
8 5 3 9 1 7 4 6 2
0 0 8 0 7 0 4 0 2
```

### 输出

```
1 2
2 3 4 1
1 3 2 4 5
3 2 1 5 4
-1
3 2 1 5 4 6
-1
-1
1 3 8 5 7 9 4 6 2
```



---

---
title: "Maxim and Increasing Subsequence"
layout: "post"
diff: 省选/NOI-
pid: CF261D
tag: ['线段树', '树状数组', '枚举']
---

# Maxim and Increasing Subsequence

## 题目描述

Maxim loves sequences, especially those that strictly increase. He is wondering, what is the length of the longest increasing subsequence of the given sequence $ a $ ?

Sequence $ a $ is given as follows:

- the length of the sequence equals $ n×t $ ;
- ![](https://cdn.luogu.com.cn/upload/vjudge_pic/CF261D/62550b81a494c59fe3493af08329ebf8f9d7bb9b.png) $ (1<=i<=n×t) $ , where operation ![](https://cdn.luogu.com.cn/upload/vjudge_pic/CF261D/946bcc44e053027f1f6b5dfc3143583e661988f5.png) means taking the remainder after dividing number $ x $ by number $ y $ .

Sequence $ s_{1},s_{2},...,s_{r} $ of length $ r $ is a subsequence of sequence $ a_{1},a_{2},...,a_{n} $ , if there is such increasing sequence of indexes $ i_{1},i_{2},...,i_{r} $ $ (1<=i_{1}&lt;i_{2}&lt;...\ &lt;i_{r}<=n) $ , that $ a_{ij}=s_{j} $ . In other words, the subsequence can be obtained from the sequence by crossing out some elements.

Sequence $ s_{1},s_{2},...,s_{r} $ is increasing, if the following inequality holds: $ s_{1}&lt;s_{2}&lt;...&lt;s_{r} $ .

Maxim have $ k $ variants of the sequence $ a $ . Help Maxim to determine for each sequence the length of the longest increasing subsequence.

## 输入格式

The first line contains four integers $ k $ , $ n $ , $ maxb $ and $ t $ $ (1<=k<=10; 1<=n,maxb<=10^{5}; 1<=t<=10^{9}; n×maxb<=2·10^{7}) $ . Each of the next $ k $ lines contain $ n $ integers $ b_{1},b_{2},...,b_{n} $ $ (1<=b_{i}<=maxb) $ .

Note that for each variant of the sequence $ a $ the values $ n $ , $ maxb $ and $ t $ coincide, the only arrays $ b $ s differ.

The numbers in the lines are separated by single spaces.

## 输出格式

Print $ k $ integers — the answers for the variants of the sequence $ a $ . Print the answers in the order the variants follow in the input.

## 样例 #1

### 输入

```
3 3 5 2
3 2 1
1 2 3
2 3 1

```

### 输出

```
2
3
3

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
title: "Mystic Carvings"
layout: "post"
diff: 省选/NOI-
pid: CF297E
tag: ['线段树', '树状数组', '容斥原理']
---

# Mystic Carvings

## 题目描述

The polar bears have discovered a gigantic circular piece of floating ice with some mystic carvings on it. There are $ n $ lines carved on the ice. Each line connects two points on the boundary of the ice (we call these points endpoints). The endpoints are numbered $ 1,2,...,2n $ counter-clockwise along the circumference. No two lines share an endpoint.

Now a group of 6 polar bears (Alice, Bob, Carol, Dave, Eve, Frank) are going to build caves on the endpoints. Each polar bear would build a cave and live in it. No two polar bears can build a cave on the same endpoints. Alice and Bob is a pair of superstitious lovers. They believe the lines are carved by aliens (or humans, which are pretty much the same thing to polar bears), and have certain spiritual power. Therefore they want to build their caves on two endpoints which are connected by a line. The same for Carol and Dave, Eve and Frank.

The distance between two caves X and Y is defined as one plus minimum number of other caves one need to pass through in order to travel from X to Y along the boundary of the ice (endpoints without caves are not counted).

To ensure fairness, the distances between the three pairs of lovers have to be the same (that is, the distance between Alice and Bob, the distance between Carol and Dave, and the distance between Eve and Frank are the same).

The figures below show two different configurations, where the dots on the circle are the endpoints. The configuration on the left is not valid. Although each pair of lovers (A and B, C and D, E and F) is connected a line, the distance requirement is not satisfied. The distance between A and B is 2 (one can go from A to B in the clockwise direction passing through F). The distance between E and F is also 2. However, the distance between C and D is 1 (one can go from C to D in the counter-clockwise direction without passing through any other caves). The configuration on the right is valid. All three pairs have the same distance 1.

 ![](https://cdn.luogu.com.cn/upload/vjudge_pic/CF297E/d4294009e1edf87a8acd5f07b8b6190c53a3334c.png)Count the number of ways to build the caves under the requirements. Two configurations are considered the same if the same set of 6 endpoints are used.

## 输入格式

The first line contains integer $ n $ ( $ 3<=n<=10^{5} $ ) — the number of lines.

Each of the following $ n $ lines contains two integers $ a_{i},b_{i} $ ( $ 1<=a_{i},b_{i}<=2n $ ), which means that there is a line carved on the ice connecting the $ a_{i} $ –th and $ b_{i} $ –th endpoint.

It's guaranteed that each endpoints touches exactly one line.

## 输出格式

Print the number of ways to build the caves.

Please, do not write the %lld specifier to read or write 64-bit integers in С++. It is preferred to use the cin, cout streams or the %I64d specifier.

## 说明/提示

The second sample corresponds to the figure in the problem statement.

## 样例 #1

### 输入

```
4
5 4
1 2
6 7
8 3

```

### 输出

```
2

```

## 样例 #2

### 输入

```
8
1 7
2 4
3 9
5 11
6 8
10 16
13 15
14 12

```

### 输出

```
6

```



---

---
title: "Iahub and Xors"
layout: "post"
diff: 省选/NOI-
pid: CF341D
tag: ['线段树', '树状数组', '树套树']
---

# Iahub and Xors

## 题目描述

Iahub does not like background stories, so he'll tell you exactly what this problem asks you for.

You are given a matrix $ a $ with $ n $ rows and $ n $ columns. Initially, all values of the matrix are zeros. Both rows and columns are 1-based, that is rows are numbered 1, 2, ..., $ n $ and columns are numbered 1, 2, ..., $ n $ . Let's denote an element on the $ i $ -th row and $ j $ -th column as $ a_{i,j} $ .

We will call a submatrix $ (x_{0},y_{0},x_{1},y_{1}) $ such elements $ a_{i,j} $ for which two inequalities hold: $ x_{0}<=i<=x_{1} $ , $ y_{0}<=j<=y_{1} $ .

Write a program to perform two following operations:

1. Query( $ x_{0} $ , $ y_{0} $ , $ x_{1} $ , $ y_{1} $ ): print the xor sum of the elements of the submatrix $ (x_{0},y_{0},x_{1},y_{1}) $ .
2. Update( $ x_{0} $ , $ y_{0} $ , $ x_{1} $ , $ y_{1} $ , $ v $ ): each element from submatrix $ (x_{0},y_{0},x_{1},y_{1}) $ gets xor-ed by value $ v $ .

## 输入格式

The first line contains two integers: $ n $ ( $ 1<=n<=1000 $ ) and $ m $ ( $ 1<=m<=10^{5} $ ). The number $ m $ represents the number of operations you need to perform. Each of the next $ m $ lines contains five or six integers, depending on operation type.

If the $ i $ -th operation from the input is a query, the first number from $ i $ -th line will be 1. It will be followed by four integers $ x_{0} $ , $ y_{0} $ , $ x_{1} $ , $ y_{1} $ . If the $ i $ -th operation is an update, the first number from the $ i $ -th line will be 2. It will be followed by five integers $ x_{0} $ , $ y_{0} $ , $ x_{1} $ , $ y_{1} $ , $ v $ .

It is guaranteed that for each update operation, the following inequality holds: $ 0<=v<2^{62} $ . It is guaranteed that for each operation, the following inequalities hold: $ 1<=x_{0}<=x_{1}<=n $ , $ 1<=y_{0}<=y_{1}<=n $ .

## 输出格式

For each query operation, output on a new line the result.

## 说明/提示

After the first $ 3 $ operations, the matrix will look like this:

```
1 1 2
1 1 2
3 3 3
```
The fourth operation asks us to compute 1 xor 2 xor 3 xor 3 = 3.

The fifth operation asks us to compute 1 xor 3 = 2.

## 样例 #1

### 输入

```
3 5
2 1 1 2 2 1
2 1 3 2 3 2
2 3 1 3 3 3
1 2 2 3 3
1 2 2 3 2

```

### 输出

```
3
2

```



---

---
title: "On Changing Tree"
layout: "post"
diff: 省选/NOI-
pid: CF396C
tag: ['树状数组', '前缀和', '栈']
---

# On Changing Tree

## 题目描述

You are given a rooted tree consisting of $ n $ vertices numbered from $ 1 $ to $ n $ . The root of the tree is a vertex number $ 1 $ .

Initially all vertices contain number $ 0 $ . Then come $ q $ queries, each query has one of the two types:

- The format of the query: $ 1 $ $ v $ $ x $ $ k $ . In response to the query, you need to add to the number at vertex $ v $ number $ x $ ; to the numbers at the descendants of vertex $ v $ at distance $ 1 $ , add $ x-k $ ; and so on, to the numbers written in the descendants of vertex $ v $ at distance $ i $ , you need to add $ x-(i·k) $ . The distance between two vertices is the number of edges in the shortest path between these vertices.
- The format of the query: $ 2 $ $ v $ . In reply to the query you should print the number written in vertex $ v $ modulo $ 1000000007 $ $ (10^{9}+7) $ .

Process the queries given in the input.

## 输入格式

The first line contains integer $ n $ ( $ 1<=n<=3·10^{5} $ ) — the number of vertices in the tree. The second line contains $ n-1 $ integers $ p_{2},p_{3},...\ p_{n} $ ( $ 1<=p_{i}&lt;i $ ), where $ p_{i} $ is the number of the vertex that is the parent of vertex $ i $ in the tree.

The third line contains integer $ q $ ( $ 1<=q<=3·10^{5} $ ) — the number of queries. Next $ q $ lines contain the queries, one per line. The first number in the line is $ type $ . It represents the type of the query. If $ type=1 $ , then next follow space-separated integers $ v,x,k $ ( $ 1<=v<=n $ ; $ 0<=x&lt;10^{9}+7 $ ; $ 0<=k&lt;10^{9}+7 $ ). If $ type=2 $ , then next follows integer $ v $ ( $ 1<=v<=n $ ) — the vertex where you need to find the value of the number.

## 输出格式

For each query of the second type print on a single line the number written in the vertex from the query. Print the number modulo $ 1000000007 $ $ (10^{9}+7) $ .

## 说明/提示

You can read about a rooted tree here: http://en.wikipedia.org/wiki/Tree\_(graph\_theory).

## 样例 #1

### 输入

```
3
1 1
3
1 1 2 1
2 1
2 2

```

### 输出

```
2
1

```



---

---
title: "Inversions After Shuffle"
layout: "post"
diff: 省选/NOI-
pid: CF749E
tag: ['树状数组', '枚举', '期望']
---

# Inversions After Shuffle

## 题目描述

You are given a permutation of integers from $ 1 $ to $ n $ . Exactly once you apply the following operation to this permutation: pick a random segment and shuffle its elements. Formally:

1. Pick a random segment (continuous subsequence) from $ l $ to $ r $ . All ![](https://cdn.luogu.com.cn/upload/vjudge_pic/CF749E/150441d31156a32e0b2da63844d600138a543898.png) segments are equiprobable.
2. Let $ k=r-l+1 $ , i.e. the length of the chosen segment. Pick a random permutation of integers from $ 1 $ to $ k $ , $ p_{1},p_{2},...,p_{k} $ . All $ k! $ permutation are equiprobable.
3. This permutation is applied to elements of the chosen segment, i.e. permutation $ a_{1},a_{2},...,a_{l-1},a_{l},a_{l+1},...,a_{r-1},a_{r},a_{r+1},...,a_{n} $ is transformed to $ a_{1},a_{2},...,a_{l-1},a_{l-1+p1},a_{l-1+p2},...,a_{l-1+pk-1},a_{l-1+pk},a_{r+1},...,a_{n} $ .

Inversion if a pair of elements (not necessary neighbouring) with the wrong relative order. In other words, the number of inversion is equal to the number of pairs $ (i,j) $ such that $ i&lt;j $ and $ a_{i}&gt;a_{j} $ . Find the expected number of inversions after we apply exactly one operation mentioned above.

## 输入格式

The first line contains a single integer $ n $ ( $ 1<=n<=100000 $ ) — the length of the permutation.

The second line contains $ n $ distinct integers from $ 1 $ to $ n $ — elements of the permutation.

## 输出格式

Print one real value — the expected number of inversions. Your answer will be considered correct if its absolute or relative error does not exceed $ 10^{-9} $ .

Namely: let's assume that your answer is $ a $ , and the answer of the jury is $ b $ . The checker program will consider your answer correct, if ![](https://cdn.luogu.com.cn/upload/vjudge_pic/CF749E/d8d110e69d298146d951837cc2710d1c4cc74a7d.png).

## 样例 #1

### 输入

```
3
2 3 1

```

### 输出

```
1.916666666666666666666666666667

```



---

---
title: "Anton and Permutation"
layout: "post"
diff: 省选/NOI-
pid: CF785E
tag: ['线段树', '树状数组']
---

# Anton and Permutation

## 题目描述

Anton likes permutations, especially he likes to permute their elements. Note that a permutation of $ n $ elements is a sequence of numbers $ {a_{1},a_{2},...,a_{n}} $ , in which every number from $ 1 $ to $ n $ appears exactly once.

One day Anton got a new permutation and started to play with it. He does the following operation $ q $ times: he takes two elements of the permutation and swaps these elements. After each operation he asks his friend Vanya, how many inversions there are in the new permutation. The number of inversions in a permutation is the number of distinct pairs $ (i,j) $ such that $ 1<=i<j<=n $ and $ a_{i}>a_{j} $ .

Vanya is tired of answering Anton's silly questions. So he asked you to write a program that would answer these questions instead of him.

Initially Anton's permutation was $ {1,2,...,n} $ , that is $ a_{i}=i $ for all $ i $ such that $ 1<=i<=n $ .

## 输入格式

The first line of the input contains two integers $ n $ and $ q $ $ (1<=n<=200000,1<=q<=50000) $ — the length of the permutation and the number of operations that Anton does.

Each of the following $ q $ lines of the input contains two integers $ l_{i} $ and $ r_{i} $ $ (1<=l_{i},r_{i}<=n) $ — the indices of elements that Anton swaps during the $ i $ -th operation. Note that indices of elements that Anton swaps during the $ i $ -th operation can coincide. Elements in the permutation are numbered starting with one.

## 输出格式

Output $ q $ lines. The $ i $ -th line of the output is the number of inversions in the Anton's permutation after the $ i $ -th operation.

## 说明/提示

Consider the first sample.

After the first Anton's operation the permutation will be $ {1,2,3,5,4} $ . There is only one inversion in it: $ (4,5) $ .

After the second Anton's operation the permutation will be $ {1,5,3,2,4} $ . There are four inversions: $ (2,3) $ , $ (2,4) $ , $ (2,5) $ and $ (3,4) $ .

After the third Anton's operation the permutation will be $ {1,4,3,2,5} $ . There are three inversions: $ (2,3) $ , $ (2,4) $ and $ (3,4) $ .

After the fourth Anton's operation the permutation doesn't change, so there are still three inversions.

## 样例 #1

### 输入

```
5 4
4 5
2 4
2 5
2 2

```

### 输出

```
1
4
3
3

```

## 样例 #2

### 输入

```
2 1
2 1

```

### 输出

```
1

```

## 样例 #3

### 输入

```
6 7
1 4
3 5
2 3
3 3
3 6
2 1
5 1

```

### 输出

```
5
6
7
7
10
11
8

```



---

