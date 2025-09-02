---
title: "Sergey and Subway"
layout: "post"
diff: 提高+/省选-
pid: CF1060E
tag: ['分治', '深度优先搜索 DFS', '概率论']
---

# Sergey and Subway

## 题目描述

Sergey Semyonovich is a mayor of a county city N and he used to spend his days and nights in thoughts of further improvements of Nkers' lives. Unfortunately for him, anything and everything has been done already, and there are no more possible improvements he can think of during the day (he now prefers to sleep at night). However, his assistants have found a solution and they now draw an imaginary city on a paper sheet and suggest the mayor can propose its improvements.

Right now he has a map of some imaginary city with $ n $ subway stations. Some stations are directly connected with tunnels in such a way that the whole map is a tree (assistants were short on time and enthusiasm). It means that there exists exactly one simple path between each pair of station. We call a path simple if it uses each tunnel no more than once.

One of Sergey Semyonovich's favorite quality objectives is the sum of all pairwise distances between every pair of stations. The distance between two stations is the minimum possible number of tunnels on a path between them.

Sergey Semyonovich decided to add new tunnels to the subway map. In particular, he connected any two stations $ u $ and $ v $ that were not connected with a direct tunnel but share a common neighbor, i.e. there exists such a station $ w $ that the original map has a tunnel between $ u $ and $ w $ and a tunnel between $ w $ and $ v $ . You are given a task to compute the sum of pairwise distances between all pairs of stations in the new map.

## 输入格式

The first line of the input contains a single integer $ n $ ( $ 2 \leq n \leq 200\,000 $ ) — the number of subway stations in the imaginary city drawn by mayor's assistants. Each of the following $ n - 1 $ lines contains two integers $ u_i $ and $ v_i $ ( $ 1 \leq u_i, v_i \leq n $ , $ u_i \ne v_i $ ), meaning the station with these indices are connected with a direct tunnel.

It is guaranteed that these $ n $ stations and $ n - 1 $ tunnels form a tree.

## 输出格式

Print one integer that is equal to the sum of distances between all pairs of stations after Sergey Semyonovich draws new tunnels between all pairs of stations that share a common neighbor in the original map.

## 说明/提示

In the first sample, in the new map all pairs of stations share a direct connection, so the sum of distances is $ 6 $ .

In the second sample, the new map has a direct tunnel between all pairs of stations except for the pair $ (1, 4) $ . For these two stations the distance is $ 2 $ .

## 样例 #1

### 输入

```
4
1 2
1 3
1 4

```

### 输出

```
6

```

## 样例 #2

### 输入

```
4
1 2
2 3
3 4

```

### 输出

```
7

```



---

---
title: "Permutation Graph"
layout: "post"
diff: 提高+/省选-
pid: CF1696D
tag: ['贪心', '线段树', '分治']
---

# Permutation Graph

## 题目描述

给出一个 $1$ 到 $n$ 的排列 $ [a_1,a_2,\dots,a_n] $ 。对于 $1\le i < j\le n$ ，记 $ \operatorname{mn}(i,j) $ 为 $\min\limits_{k=i}^j a_k$ ，记  $ \operatorname{mx}(i,j) $ 为 $ \max\limits_{k=i}^j a_k $ 。

有一张 $n$ 个点的无向图，点的编号为 $1$ 到 $n$ 。对于每一对整数 $ 1\le i<j\le n $ ，如果同时满足 $ \operatorname{mn}(i,j)=a_i $ 且 $ \operatorname{mx}(i,j)=a_j $ ，或同时满足 $ \operatorname{mn}(i,j)=a_j $ 和 $ \operatorname{mx}(i,j)=a_i $ ，那么就在 $i$ 和 $j$ 之间连一条长度为 $1$ 的边。

询问这张图中从 $1$ 到 $n$ 的最短路的长度。可以证明 $1$ 和 $n$ 总是连通，所以最短路总是存在。

## 输入格式

每个数据点包含多组数据。第一行一个整数 $t$ ( $ 1 \le t \le 5\cdot 10^4 $ ) 表示测试组数

对于每组数据，第一行一个整数 $n$ ( $ 1\le n\le 2.5\cdot 10^5 $ ) 。

第二行包含 $n$ 个整数 $ a_1 $ , $ a_2 $ , $ \ldots $ , $ a_n $ ( $ 1\le a_i\le n $ ) 。保证 $a$ 是 $ 1 $ , $ 2 $ , $ \dots $ , $ n $ 的一个排列。

保证所有数据的 $n$ 之和不超过 $ 5\cdot 10^5 $

## 输出格式

对于每组数据，输出一个整数表示从 $1$ 到 $n$ 的最短路长度

## 样例 #1

### 输入

```
5
1
1
2
1 2
5
1 4 2 3 5
5
2 1 5 3 4
10
7 4 8 1 6 10 3 5 2 9
```

### 输出

```
0
1
1
4
6
```



---

---
title: "Tree Master"
layout: "post"
diff: 提高+/省选-
pid: CF1806E
tag: ['剪枝', '分块', '根号分治']
---

# Tree Master

## 题目描述

You are given a tree with $ n $ weighted vertices labeled from $ 1 $ to $ n $ rooted at vertex $ 1 $ . The parent of vertex $ i $ is $ p_i $ and the weight of vertex $ i $ is $ a_i $ . For convenience, define $ p_1=0 $ .

For two vertices $ x $ and $ y $ of the same depth $ ^\dagger $ , define $ f(x,y) $ as follows:

- Initialize $ \mathrm{ans}=0 $ .
- While both $ x $ and $ y $ are not $ 0 $ : 
  - $ \mathrm{ans}\leftarrow \mathrm{ans}+a_x\cdot a_y $ ;
  - $ x\leftarrow p_x $ ;
  - $ y\leftarrow p_y $ .
- $ f(x,y) $ is the value of $ \mathrm{ans} $ .

You will process $ q $ queries. In the $ i $ -th query, you are given two integers $ x_i $ and $ y_i $ and you need to calculate $ f(x_i,y_i) $ .

 $ ^\dagger $ The depth of vertex $ v $ is the number of edges on the unique simple path from the root of the tree to vertex $ v $ .

## 输入格式

The first line contains two integers $ n $ and $ q $ ( $ 2 \le n \le 10^5 $ ; $ 1 \le q \le 10^5 $ ).

The second line contains $ n $ integers $ a_1, a_2, \ldots, a_n $ ( $ 1 \le a_i \le 10^5 $ ).

The third line contains $ n-1 $ integers $ p_2, \ldots, p_n $ ( $ 1 \le p_i < i $ ).

Each of the next $ q $ lines contains two integers $ x_i $ and $ y_i $ ( $ 1\le x_i,y_i\le n $ ). It is guaranteed that $ x_i $ and $ y_i $ are of the same depth.

## 输出格式

Output $ q $ lines, the $ i $ -th line contains a single integer, the value of $ f(x_i,y_i) $ .

## 说明/提示

Consider the first example:

In the first query, the answer is $ a_4\cdot a_5+a_3\cdot a_3+a_2\cdot a_2+a_1\cdot a_1=3+4+25+1=33 $ .

In the second query, the answer is $ a_6\cdot a_6+a_2\cdot a_2+a_1\cdot a_1=1+25+1=27 $ .

## 样例 #1

### 输入

```
6 2
1 5 2 3 1 1
1 2 3 3 2
4 5
6 6
```

### 输出

```
33
27
```

## 样例 #2

### 输入

```
14 8
3 2 5 3 1 4 2 2 2 5 5 5 2 4
1 2 3 1 1 4 7 3 3 1 5 3 8
4 4
4 10
13 10
3 12
13 9
3 12
9 10
11 5
```

### 输出

```
47
53
48
36
42
36
48
14
```



---

---
title: "Sum of Progression"
layout: "post"
diff: 提高+/省选-
pid: CF1921F
tag: ['根号分治']
---

# Sum of Progression

## 题目描述

You are given an array $ a $ of $ n $ numbers. There are also $ q $ queries of the form $ s, d, k $ .

For each query $ q $ , find the sum of elements $ a_s + a_{s+d} \cdot 2 + \dots + a_{s + d \cdot (k - 1)} \cdot k $ . In other words, for each query, it is necessary to find the sum of $ k $ elements of the array with indices starting from the $ s $ -th, taking steps of size $ d $ , multiplying it by the serial number of the element in the resulting sequence.

## 输入格式

Each test consists of several testcases. The first line contains one integer $ t $ ( $ 1 \le t \le 10^4 $ ) — the number of testcases. Next lines contain descriptions of testcases.

The first line of each testcase contains two numbers $ n, q $ ( $ 1 \le n \le 10^5, 1 \le q \le 2 \cdot 10^5 $ ) — the number of elements in the array $ a $ and the number of queries.

The second line contains $ n $ integers $ a_1, ... a_n $ ( $ -10^8 \le a_1, ..., a_n \le 10^8 $ ) — elements of the array $ a $ .

The next $ q $ lines each contain three integers $ s $ , $ d $ , and $ k $ ( $ 1 \le s, d, k \le n $ , $ s + d\cdot (k - 1) \le n $ ).

It is guaranteed that the sum of $ n $ over all testcases does not exceed $ 10^5 $ , and that the sum of $ q $ over all testcases does not exceed $ 2 \cdot 10^5  $ .

## 输出格式

For each testcase, print $ q $ numbers in a separate line — the desired sums, separated with space.

## 样例 #1

### 输入

```
5
3 3
1 1 2
1 2 2
2 2 1
1 1 2
3 1
-100000000 -100000000 -100000000
1 1 3
5 3
1 2 3 4 5
1 2 3
2 3 2
1 1 5
3 1
100000000 100000000 100000000
1 1 3
7 7
34 87 5 42 -44 66 -32
2 2 2
4 3 1
1 3 2
6 2 1
5 2 2
2 5 2
6 1 2
```

### 输出

```
5 1 3 
-600000000 
22 12 55 
600000000 
171 42 118 66 -108 23 2
```



---

---
title: "Count Paths"
layout: "post"
diff: 提高+/省选-
pid: CF1923E
tag: ['点分治', '递归']
---

# Count Paths

## 题目描述

You are given a tree, consisting of $ n $ vertices, numbered from $ 1 $ to $ n $ . Every vertex is colored in some color, denoted by an integer from $ 1 $ to $ n $ .

A simple path of the tree is called beautiful if:

- it consists of at least $ 2 $ vertices;
- the first and the last vertices of the path have the same color;
- no other vertex on the path has the same color as the first vertex.

Count the number of the beautiful simple paths of the tree. Note that paths are considered undirected (i. e. the path from $ x $ to $ y $ is the same as the path from $ y $ to $ x $ ).

## 输入格式

The first line contains a single integer $ t $ ( $ 1 \le t \le 10^4 $ ) — the number of testcases.

The first line of each testcase contains a single integer $ n $ ( $ 2 \le n \le 2 \cdot 10^5 $ ) — the number of vertices in the tree.

The second line contains $ n $ integers $ c_1, c_2, \dots, c_n $ ( $ 1 \le c_i \le n $ ) — the color of each vertex.

The $ i $ -th of the next $ n - 1 $ lines contains two integers $ v_i $ and $ u_i $ ( $ 1 \le v_i, u_i \le n $ ; $ v_i \neq u_i $ ) — the $ i $ -th edge of the tree.

The given edges form a valid tree. The sum of $ n $ over all testcases doesn't exceed $ 2 \cdot 10^5 $ .

## 输出格式

For each testcase, print a single integer — the number of the beautiful simple paths of the tree.

## 样例 #1

### 输入

```
4
3
1 2 1
1 2
2 3
5
2 1 2 1 2
1 2
1 3
3 4
4 5
5
1 2 3 4 5
1 2
1 3
3 4
4 5
4
2 2 2 2
3 1
3 2
3 4
```

### 输出

```
1
3
0
3
```



---

---
title: "Number of k-good subarrays"
layout: "post"
diff: 提高+/省选-
pid: CF1982E
tag: ['分治']
---

# Number of k-good subarrays

## 题目描述

Let $ bit(x) $ denote the number of ones in the binary representation of a non-negative integer $ x $ .

A subarray of an array is called  $ k $ -good if it consists only of numbers with no more than $ k $ ones in their binary representation, i.e., a subarray $ (l, r) $ of array $ a $ is good if for any $ i $ such that $ l \le i \le r $ condition $ bit(a_{i}) \le k $ is satisfied.

You are given an array $ a $ of length $ n $ , consisting of consecutive non-negative integers starting from $ 0 $ , i.e., $ a_{i} = i $ for $ 0 \le i \le n - 1 $ (in $ 0 $ -based indexing). You need to count the number of  $ k $ -good subarrays in this array.

As the answer can be very large, output it modulo $ 10^{9} + 7 $ .

## 输入格式

Each test consists of multiple test cases. The first line contains an integer $ t $ ( $ 1 \le t \le 10^{4} $ ) — the number of test cases. The following lines describe the test cases.

The single line of each test case contains two integers $ n $ , $ k $ ( $ 1 \le n \le 10^{18}, 1 \le k \le 60 $ ).

## 输出格式

For each test case, output a single integer — the number of  $ k $ -good subarrays modulo $ 10^{9} + 7 $ .

## 说明/提示

For the first test case $ a = [0, 1, 2, 3, 4, 5] $ , $ k = 1 $ .

To find the answer, let's write all the numbers in binary representation:

 $ $$$a = [\color{green}{000}, \color{green}{001}, \color{green}{010}, \color{red}{011}, \color{green}{100}, \color{red}{101}] $ $ </p><p>From this, it can be seen that the numbers  $ 3 $  and  $ 5 $  have  $ 2 \\ge (k = 1) $  ones in their binary representation, so the answer should include all subarrays that do not contain either  $ 3 $  or  $ 5 $ , which are the subarrays (in  $ 0 $ -based indexing): ( $ 0 $ ,  $ 0 $ ), ( $ 0 $ ,  $ 1 $ ), ( $ 0 $ ,  $ 2 $ ), ( $ 1 $ ,  $ 1 $ ), ( $ 1 $ ,  $ 2 $ ), ( $ 2 $ ,  $ 2 $ ), ( $ 4 $ ,  $ 4$$$).

## 样例 #1

### 输入

```
10
6 1
16 2
1 1
3 1
31 3
14 1
1337 5
100000 20
795569939321040850 56
576460752303423268 59
```

### 输出

```
7
35
1
6
155
8
7323
49965
741136395
66679884
```



---

---
title: "Eliminating Balls With Merging (Easy Version)"
layout: "post"
diff: 提高+/省选-
pid: CF1998E1
tag: ['线段树', '分治', 'ST 表', '单调栈']
---

# Eliminating Balls With Merging (Easy Version)

## 题目描述

_喝水_ 

—— 孙武，程序员健康指南

**这是问题的简单版本。本题中 $x=n$ 。你必须同时解决这两个版本的问题，才能  hack**。

给你两个整数 $n$ 和 $x$ ( $x=n$ )。有 $n$ 个球排成一排，从左到右编号为 $1$ 到 $n$ 。最初，在第 $i$ 个球上写着一个值 $a_i$。

对于从 $1$ 到 $n$ 的每个整数 $i$ ，我们定义一个函数 $f(i)$ 如下：

- 假设有一个集合 $S = \{1, 2, \ldots, i\}$ 。
    
- 在每次运算中，必须从 $S$ 中选择一个整数 $l$ ( $1 \leq l < i$ )，使得 $l$ 不是 $S$ 的最大元素。假设 $r$ 是 $S$ 中大于 $l$ 的最小元素。
    
    - 如果是 $a_l > a_r$ ，则令 $a_l = a_l + a_r$ 并从 $S$ 中删除 $r$ 。
    - 如果是 $a_l < a_r$ ，则令 $a_r = a_l + a_r$ ，并从 $S$ 删除 $l$ 。
    - 如果是 $a_l = a_r$ ，则从 $S$ 中选择删除整数 $l$ 或 $r$ ：
        - 如果选择从 $S$ 中删除 $l$ ，则设置 $a_r = a_l + a_r$ 并从 $S$ 中删除 $l$ 。
        - 如果您选择从 $S$ 中删除 $r$ ，则需要设置 $a_l = a_l + a_r$ ，并从 $S$ 中删除 $r$ 。
    
- $f(i)$ 表示这样的整数 $j$ ( $1 \le j \le i$ )的个数，即执行上述操作恰好 $i - 1$ 次后可以得到 $S = \{j\}$ 。

对 $x$ 到 $n$ 的每个整数 $i$ 都需要求出 $f(i)$ 。

## 输入格式

第一行包含 $t$ ( $1 \leq t \leq 10^4$ ) ，表示测试用例数。

每个测试用例的第一行包含两个整数 $n$ 和 $x$ ( $1 \leq n \leq 2 \cdot 10^5; x = n$ )--球的个数和最小索引 $i$ ，您需要找到该索引的 $f(i)$ 。

每个测试用例的第二行包含 $a_1, a_2, \ldots, a_n$ ( $1 \leq a_i \leq 10^9$ ) - 写在每个球上的初始数字。

保证所有测试用例中 $n$ 的总和不超过 $2 \cdot 10^5$ 。

## 输出格式

对于每个测试用例，在一行中输出 $n-x+1$ 个空格分隔的整数，其中第 $j$ 个整数表示 $f(x+j-1)$ 。

**样例解释**

在第一个测试用例中，要计算 $f(5)$ 。可以看出，经过 $4$ 次运算后， $S$ 可以包含 $2$ 、 $3$ 或 $4$ 。下面是生成 $S = \{4\}$ 所需的运算。

- 最初是 $S = \{1, 2, 3, 4, 5\}$ 和 $a = [1, 2, 3, 2, 1]$ 。
- 选择 $l = 1$ 。自然是 $r = 2$ 。由于 $a_1< a_2$ ，我们设置 $a_2 = 1 + 2$ ，并从 $S$ 中删除 $1$ 。现在， $S = \{2, 3, 4, 5\}$ 和 $a = [1, 3, 3, 2, 1]$ 。
- 选择 $l = 4$ 。自然是 $r = 5$ 。由于 $a_4> a_5$ ，我们设置 $a_4 = 2 + 1$ ，并从 $S$ 中删除 $5$ 。现在， $S = \{2, 3, 4\}$ 和 $a = [1, 3, 3, 3, 1]$ 。
- 选择 $l = 3$ 。自然是 $r = 4$ 。由于 $a_3 = a_4$ ，我们可以选择删除 $3$ 或 $4$ 。既然要保留 $4$ ，那么就删除 $3$ 。因此，设置 $a_4 = 3 + 3$ 并从 $S$ 中删除 $3$ 。现在， $S = \{2, 4\}$ 和 $a = [1, 3, 3, 6, 1]$ 。
- 选择 $l = 2$ 。自然是 $r = 4$ 。由于 $a_2< a_4$ ，我们设置 $a_4 = 3 + 6$ ，并从 $S$ 中删除 $2$ 。最后是 $S = \{4\}$ 和 $a = [1, 3, 3, 9, 1]$ 。

在第二个测试案例中，要求计算 $f(7)$ 。可以证明，经过 $6$ 次运算后， $S$ 可以包含 $2$ 、 $4$ 、 $6$ 或 $7$ 。

## 样例 #1

### 输入

```
3
5 5
1 2 3 2 1
7 7
4 5 1 2 1 4 5
11 11
1 2 3 1 1 9 3 2 4 1 3
```

### 输出

```
3
4
4
```



---

---
title: "Eliminating Balls With Merging (Hard Version)"
layout: "post"
diff: 提高+/省选-
pid: CF1998E2
tag: ['分治', '笛卡尔树']
---

# Eliminating Balls With Merging (Hard Version)

## 题目描述

喝水。     
—— 孙武，《成为一名健康程序员的艺术》

这是这个问题的更难的版本。唯一的区别是在这个版本中 $x = 1$。你必须破解这两个版本才能破解。

你被给定了两个整数 $n$ 和 $x$ ( $x = 1$ )，有 $n$ 个球排成一排，从左到右从 $1$ 到 $n$ 编号。最初，在第 $i$ 个球上写了一个值 $a_i$。

对于从 $1$ 到 $n$ 的每一个整数 $i$，我们定义函数 $f(i)$ 如下：

+ 假设你有一个集合 $S = \{1, 2, \ldots, i\}$。
+ 对于每一次操作，你需要从 $S$ 中选择出一个整数 $l$ $(1 \le l < i)$，使得 $l$ 不是 $S$ 中的最大元素。假设 $r$ 是 $S$ 中比 $l$ 大的最小元素。    
	+ 如果 $a_l > a_r$，你把 $a_l$ 赋值为 $a_l + a_r$，然后将 $r$ 从 $S$ 中移除
    + 如果 $a_l < a_r$，你把 $a_r$ 赋值为 $a_l + a_r$，然后将 $l$ 从 $S$ 中移除
    + 如果 $a_l = a_r$，你可以在 $l$ 和 $r$ 任意选一个移出 $S$：
    	+ 如果 你选择把 $l$ 从 $S$ 中移除，你需要 $a_r$ 赋值为 $a_l + a_r$，然后将 $l$ 从 $S$ 中移除。
        + 如果 你选择把 $r$ 从 $S$ 中移除，你需要 $a_l$ 赋值为 $a_l + a_r$，然后将 $r$ 从 $S$ 中移除。
+ $f(i)$ 表示整数 $j$ $(1 \le j \le i)$ 的个数，使得在执行上述运算 $i − 1$ 次后可以得到 $S = \{ j \}$。

对于每一个整数 $i$ 从 $x$ 到 $n$，你需要找到 $f(i)$。

## 输入格式

第一行包含一个整数 $t$ $(1 ≤ t ≤ 10^4)$，也就是测试组数。

每一组测试数据的第一行包含两个整数 $n$ 和 $x$ $(1 ≤ n ≤ 2 \cdot 10^5;x = 1)$，也就是球的数量和最小的索引 $i$ 你需要找到 $f(i)$。

每一组测试数据的第二行包含 $n$ 个整数 $a_1,a_2,...,a_n$ $(1 ≤ a_i ≤ 10^9)$，也就是每个球上写的数字。

保证所有测试数据中的 $n$ 之和小于等于 $2 \cdot 10^5$。

## 输出格式

对于每一组测试数据，在新的一行中输出 $n - x + 1$ 个用一个空格隔开的整数，其中第 $j$ 个数应当表示 $f(x + j - 1)$。

## 说明/提示

对于第一组数据，下面是对于每个 $1$ 到 $n$ 的 $i$，$j$ 可以取到的所有数值：

+ 对于 $f(1)$，$j$ 只能取 $1$。
+ 对于 $f(2)$，$j$ 只能取 $2$。
+ 对于 $f(3)$，$j$ 能取 $2$ 和 $3$。
+ 对于 $f(4)$，$j$ 能取 $2$ 和 $3$。
+ 对于 $f(5)$，$j$ 能取 $2$，$3$ 和 $4$。

## 样例 #1

### 输入

```
3
5 1
1 2 3 2 1
7 1
4 5 1 2 1 4 5
11 1
1 2 3 1 1 9 3 2 4 1 3
```

### 输出

```
1 1 2 2 3
1 1 1 1 1 3 4
1 1 2 2 2 1 1 1 3 3 4
```



---

---
title: "Alter the GCD"
layout: "post"
diff: 提高+/省选-
pid: CF2005D
tag: ['数论', '根号分治']
---

# Alter the GCD

## 题目描述

You are given two arrays $ a_1, a_2, \ldots, a_n $ and $ b_1, b_2, \ldots, b_n $ .

You must perform the following operation exactly once:

- choose any indices $ l $ and $ r $ such that $ 1 \le l \le r \le n $ ;
- swap $ a_i $ and $ b_i $ for all $ i $ such that $ l \leq i \leq r $ .

Find the maximum possible value of $ \text{gcd}(a_1, a_2, \ldots, a_n) + \text{gcd}(b_1, b_2, \ldots, b_n) $ after performing the operation exactly once. Also find the number of distinct pairs $ (l, r) $ which achieve the maximum value.

## 输入格式

In the first line of the input, you are given a single integer $ t $ ( $ 1 \le t \le 10^5 $ ), the number of test cases. Then the description of each test case follows.

In the first line of each test case, you are given a single integer $ n $ ( $ 1 \le n \le 2 \cdot 10^5 $ ), representing the number of integers in each array.

In the next line, you are given $ n $ integers $ a_1, a_2, \ldots, a_n $ ( $ 1 \le a_i \le 10^9 $ ) — the elements of the array $ a $ .

In the last line, you are given $ n $ integers $ b_1, b_2, \ldots, b_n $ ( $ 1 \le b_i \le 10^9 $ ) — the elements of the array $ b $ .

The sum of values of $ n $ over all test cases does not exceed $ 5 \cdot 10^5 $ .

## 输出格式

For each test case, output a line with two integers: the maximum value of $ \text{gcd}(a_1, a_2, \ldots, a_n) + \text{gcd}(b_1, b_2, \ldots, b_n) $ after performing the operation exactly once, and the number of ways.

## 说明/提示

In the first, third, and fourth test cases, there's no way to achieve a higher GCD than $ 1 $ in any of the arrays, so the answer is $ 1 + 1 = 2 $ . Any pair $ (l, r) $ achieves the same result; for example, in the first test case there are $ 36 $ such pairs.

In the last test case, you must choose $ l = 1 $ , $ r = 2 $ to maximize the answer. In this case, the GCD of the first array is $ 5 $ , and the GCD of the second array is $ 1 $ , so the answer is $ 5 + 1 = 6 $ , and the number of ways is $ 1 $ .

## 样例 #1

### 输入

```
5
8
11 4 16 17 3 24 25 8
8 10 4 21 17 18 25 21
4
6 4 24 13
15 3 1 14
2
13 14
5 8
8
20 17 15 11 21 10 3 7
9 9 4 20 14 9 13 1
2
18 13
15 20
```

### 输出

```
2 36
3 2
2 3
2 36
6 1
```



---

---
title: "Monster"
layout: "post"
diff: 提高+/省选-
pid: CF2035E
tag: ['动态规划 DP', '模拟退火', '根号分治']
---

# Monster

## 题目描述

Man, this Genshin boss is so hard. Good thing they have a top-up of $ 6 $ coins for only $  \$4.99 $ . I should be careful and spend no more than I need to, lest my mom catches me...



You are fighting a monster with $ z $ health using a weapon with $ d $ damage. Initially, $ d=0 $ . You can perform the following operations.

- Increase $ d $ — the damage of your weapon by $ 1 $ , costing $ x $ coins.
- Attack the monster, dealing $ d $ damage and costing $ y $ coins.

You cannot perform the first operation for more than $ k $ times in a row.

Find the minimum number of coins needed to defeat the monster by dealing at least $ z $ damage.

## 输入格式

The first line contains a single integer $ t $ ( $ 1\le t\le 100 $ ) — the number of test cases.

The only line of each test case contains 4 integers $ x $ , $ y $ , $ z $ , and $ k $ ( $ 1\leq x, y, z, k\leq 10^8 $ ) — the first operation's cost, the second operation's cost, the monster's health, and the limitation on the first operation.

## 输出格式

For each test case, output the minimum number of coins needed to defeat the monster.

## 说明/提示

In the first test case, $ x = 2 $ , $ y = 3 $ , $ z = 5 $ , and $ k = 5 $ . Here's a strategy that achieves the lowest possible cost of $ 12 $ coins:

- Increase damage by $ 1 $ , costing $ 2 $ coins.
- Increase damage by $ 1 $ , costing $ 2 $ coins.
- Increase damage by $ 1 $ , costing $ 2 $ coins.
- Attack the monster, dealing $ 3 $ damage, costing $ 3 $ coins.
- Attack the monster, dealing $ 3 $ damage, costing $ 3 $ coins.

You deal a total of $ 3 + 3 = 6 $ damage, defeating the monster who has $ 5 $ health. The total number of coins you use is $ 2 + 2 + 2 + 3 + 3 = 12 $ coins.

In the second test case, $ x = 10 $ , $ y = 20 $ , $ z = 40 $ , and $ k = 5 $ . Here's a strategy that achieves the lowest possible cost of $ 190 $ coins:

- Increase damage by $ 5 $ , costing $ 5\cdot x $ = $ 50 $ coins.
- Attack the monster once, dealing $ 5 $ damage, costing $ 20 $ coins.
- Increase damage by $ 2 $ , costing $ 2\cdot x $ = $ 20 $ coins.
- Attack the monster $ 5 $ times, dealing $ 5\cdot 7 = 35 $ damage, costing $ 5\cdot y $ = $ 100 $ coins.

You deal a total of $ 5 + 35 = 40 $ damage, defeating the monster who has exactly $ 40 $ health. The total number of coins you use is $ 50 + 20 + 20 + 100 = 190 $ coins.

## 样例 #1

### 输入

```
4
2 3 5 5
10 20 40 5
1 60 100 10
60 1 100 10
```

### 输出

```
12
190
280
160
```



---

---
title: "I've Been Flipping Numbers for 300 Years and Calculated the Sum"
layout: "post"
diff: 提高+/省选-
pid: CF2072G
tag: ['根号分治']
---

# I've Been Flipping Numbers for 300 Years and Calculated the Sum

## 题目描述

经过三百年的史莱姆养殖，Akito 终于获得了魔法数字 $n$。当他找到商人准备兑换黄金时，商人却给了他一个任务。

商人表示，完成这个任务需要用到技能 $\text{rev}(n, p)$，而 Akito 恰好最近学会了这个技能。$\text{rev}(n, p)$ 表示以下操作流程：

1. 将数字 $n$ 以 $p$ 进制表示，记作 $n = \overline{n_{\ell - 1} \ldots n_1 n_0}$，其中 $\ell$ 是 $n$ 的 $p$ 进制表示的位数长度。
2. 反转这个 $p$ 进制表示，得到 $m = \overline{n_0 n_1 \ldots n_{\ell - 1}}$。
3. 将 $m$ 转换回十进制并作为结果返回。

商人的任务是计算总和 $x = \sum\limits_{p = 2}^{k} \text{rev}(n, p)$。由于这个数字可能非常大，只需要输出 $x$ 对 $10^9 + 7$ 取模后的余数。商人还提到，上一个旅行者计算这个和已经用了三百年仍未完成。但你一定会帮助 Akito 更快完成，对吗？

## 输入格式

第一行包含一个数 $t$（$1 \le t \le 5000$）——测试用例的数量。

每个测试用例的唯一一行包含两个数 $n$ 和 $k$（$1 \le n \le 3 \cdot 10^5$，$2 \le k \le 10^{18}$）——魔法数字和求和的进制上限。

请注意，所有测试用例的 $n$ 之和没有限制。

## 输出格式

对于每个测试用例，输出一个数字——$x = \sum\limits_{p = 2}^{k} \text{rev}(n, p)$ 对 $10^9 + 7$ 取模后的结果。

## 说明/提示

在第三个测试用例中，$n = 1$。数字 1 在任何进制下都表示为单个数字，这意味着对于任意 $p \ge 2$ 都有 $\text{rev}(1, p) = 1$。因此，$x = \sum\limits_{p = 2}^{k} 1 = \sum\limits_{p = 2}^{10} 1 = 10 - 2 + 1 = 9$。

在第四个测试用例中，$x = \text{rev}(4, 2) + \text{rev}(4, 3) + \text{rev}(4, 4)$。计算各项：
- $4 = 100_2 \rightarrow \text{rev}(4, 2) = 001_2 = 1$
- $4 = 11_3 \rightarrow \text{rev}(4, 3) = 11_3 = 4$
- $4 = 10_4 \rightarrow \text{rev}(4, 4) = 01_4 = 1$
因此，$x = 1 + 4 + 1 = 6$。

在第七个测试用例中，$x = \text{rev}(9, 2) + \text{rev}(9, 3)$。计算各项：
- $9 = 1001_2 \rightarrow \text{rev}(9, 2) = 1001_2 = 9$
- $9 = 100_3 \rightarrow \text{rev}(9, 3) = 001_3 = 1$
因此，$x = 9 + 1 = 10$。

翻译由 DeepSeek R1 完成

## 样例 #1

### 输入

```
12
3 2
42 52
1 10
4 4
16 2
69 69
9 3
19 84
9982 44353
100000 1000000007
17 30
777 1000000000000000000
```

### 输出

```
3
7594
9
6
1
33471
10
2006
120792461
584502117
775
46058362
```



---

---
title: "La Vaca Saturno Saturnita"
layout: "post"
diff: 提高+/省选-
pid: CF2094H
tag: ['二分', '数论', '根号分治']
---

# La Vaca Saturno Saturnita

## 题目描述

Saturnita 的情绪取决于一个长度为 $n$ 的数组 $a$（只有他知道其含义）以及一个函数 $f(k, a, l, r)$（只有他知道如何计算）。以下是该函数的伪代码实现：

```
function f(k, a, l, r):
   ans := 0
   for i from l to r (inclusive):
      while k is divisible by a[i]:
         k := k/a[i]
      ans := ans + k
   return ans
```

给定 $q$ 个查询，每个查询包含整数 $k$、$l$ 和 $r$。对于每个查询，请输出 $f(k,a,l,r)$ 的值。

## 输入格式

第一行包含一个整数 $t$（$1 \leq t \leq 10^4$）——测试用例的数量。

每个测试用例的第一行包含两个整数 $n$ 和 $q$（$1 \leq n \leq 10^5$，$1 \leq q \leq 5 \cdot 10^4$）。

第二行包含 $n$ 个整数 $a_1, a_2, \ldots, a_n$（$2 \leq a_i \leq 10^5$）。

接下来的 $q$ 行，每行包含三个整数 $k$、$l$ 和 $r$（$1 \leq k \leq 10^5$，$1 \leq l \leq r \leq n$）。

保证所有测试用例的 $n$ 之和不超过 $10^5$，且所有测试用例的 $q$ 之和不超过 $5 \cdot 10^4$。

## 输出格式

对于每个查询，在新的一行输出答案。


## 说明/提示

翻译由 DeepSeek V3 完成

## 样例 #1

### 输入

```
2
5 3
2 3 5 7 11
2 1 5
2 2 4
2310 1 5
4 3
18 12 8 9
216 1 2
48 2 4
82944 1 4
```

### 输出

```
5
6
1629
13
12
520
```



---

---
title: "Baudelaire (hard version)"
layout: "post"
diff: 提高+/省选-
pid: CF2106G2
tag: ['二分', '点分治', '分治']
---

# Baudelaire (hard version)

## 题目描述

这是该问题的困难版本。两个版本之间的唯一区别在于，在困难版本中树的形态可以是任意的。

本题是交互题。

波德莱尔非常富有，因此他购买了一棵大小为 $n$ 的树，这棵树以某个任意节点为根。此外，每个节点的值为 $1$ 或 $-1$。

书呆子牛看到了这棵树并爱上了它。然而计算机科学的收入不足以让他买下这棵树。波德莱尔决定和书呆子牛玩一个游戏，如果他赢了，就把这棵树送给他。

书呆子牛不知道哪个节点是根，也不知道节点的值。但他可以向波德莱尔提出两种类型的查询：

1. `1 k u₁ u₂ ... uₖ`：设 $f(u)$ 为从树的根到节点 $u$ 的路径上所有节点的值之和。书呆子牛可以选择一个整数 $k$（$1 \le k \le n$）和 $k$ 个节点 $u_1, u_2, ..., u_k$，然后他会收到值 $f(u_1) + f(u_2) + ... + f(u_k)$。
2. `2 u`：波德莱尔将切换节点 $u$ 的值。具体来说，如果 $u$ 的值为 $1$，则变为 $-1$，反之亦然。

如果书呆子牛在总共 $n + 200$ 次查询内正确猜出每个节点的值（即执行查询后树的最终值），他就获胜。你能帮助他获胜吗？

## 输入格式

输入的第一行包含一个整数 $t$（$1 \le t \le 100$），表示测试用例的数量。

每个测试用例的第一行包含一个整数 $n$（$2 \le n \le 10^3$），表示树的大小。

接下来的 $n-1$ 行每行包含两个整数 $u$ 和 $v$（$1 \le u, v \le n$，$u \neq v$），表示树中节点 $u$ 和 $v$ 之间有一条边。

保证所有测试用例的 $n$ 之和不超过 $10^3$，并且每个输入的图都是合法的树。

## 输出格式

要提出类型 $1$ 的查询，请按以下格式输出一行（不带引号）：
- `? 1 k u₁ u₂ ... uₖ`（$1 \le k, u_i \le n$）

评测机将返回一个整数，即 $f(u_1) + f(u_2) + ... + f(u_k)$。

要提出类型 $2$ 的查询，请按以下格式输出一行：
- `? 2 u`（$1 \le u \le n$）

评测机会切换节点 $u$ 的值：如果其值为 $1$，则变为 $-1$，反之亦然。

当你找到答案时，请按以下格式输出一行：
- `! v₁ v₂ ... vₙ`（$v_i = 1$ 或 $v_i = -1$，$v_i$ 是执行查询后节点 $i$ 的值）

之后，继续处理下一个测试用例，或者如果是最后一个测试用例则终止程序。输出答案不计入查询次数。

交互器不是自适应的，这意味着树的值在参与者提出查询之前就已经确定。

如果你的程序进行了超过 $n + 200$ 次查询，它应立即终止并收到 Wrong Answer 的判定。否则，你可能会得到任意判定，因为你的解决方案将继续从已关闭的流中读取数据。

在打印查询后，不要忘记输出换行符并刷新输出缓冲区。否则，你可能会得到 Idleness Limit Exceeded 的判定。可以使用以下方法刷新输出：
- C++：`fflush(stdout)` 或 `cout.flush()`
- Java：`System.out.flush()`
- Pascal：`flush(output)`
- Python：`stdout.flush()`
- 其他语言请参考相关文档。

## Hack 格式

对于 Hack 攻击，请使用以下格式：

第一行应包含一个整数 $t$（$1 \le t \le 100$）——测试用例的数量。

每个测试用例的第一行必须包含两个整数 $n$ 和 $root$（$2 \le n \le 10^3$，$1 \le root \le n$）——树的大小和树的根节点。

每个测试用例的第二行必须包含 $n$ 个整数 $a_1, a_2, ..., a_n$（$|a_i| = 1$）——其中 $a_i$ 是节点 $i$ 的值。

接下来的 $n-1$ 行每行必须包含两个整数 $u$ 和 $v$（$1 \le u, v \le n$）——表示节点 $u$ 和 $v$ 之间有一条边。

所有测试用例的 $n$ 之和不得超过 $10^3$，并且每个输入的图必须是合法的树。

## 说明/提示

在第一个示例中，树的根是节点 $4$，初始值为 $[-1, -1, -1, 1]$（第 $i$ 个值是节点 $i$ 的值）。

初始时，$f(1) = 0$，$f(2) = 0$，$f(3) = -1$，$f(4) = 1$。因此，第一个查询的答案是 $f(1) + f(2) + f(4) = 1$，第二个查询的答案是 $f(3) + f(1) = -1$。

在切换节点 $4$ 的值后，值变为 $[-1, -1, -1, -1]$。此时 $f(1) = -2$，$f(2) = -2$，$f(3) = -3$，$f(4) = -1$。因此 $f(1) + f(2) + f(4) = -5$，$f(3) + f(1) = -5$。

我们最终回答节点的值为 $[-1, -1, -1, -1]$，这是正确的。注意我们报告的是节点在变化后的值，而不是之前的值。

在第二个示例中，树的根是 $2$，初始值为 $[1, 1]$。

在最后一个示例中，树的根是 $1$，初始值为 $[-1, 1, 1, 1, 1, 1, -1]$。

注意这只是一个解释查询如何工作的示例，并不涉及具体的解题策略。

翻译由 DeepSeek V3 完成

## 样例 #1

### 输入

```
3
4
1 4
4 2
2 3

1

-1


-5

-5

2
1 2

2

7
1 2
2 7
7 3
7 4
7 5
7 6

-1
```

### 输出

```
? 1 3 1 2 4

? 1 2 3 1

? 2 4
? 1 3 1 2 4

? 1 2 3 1

! -1 -1 -1 -1


? 1 1 1

! 1 1






? 1 1 1

! -1 1 1 1 1 1 -1
```



---

---
title: "Painting Fence"
layout: "post"
diff: 提高+/省选-
pid: CF448C
tag: ['贪心', '递归', '分治']
---

# Painting Fence

## 题目描述

Bizon the Champion isn't just attentive, he also is very hardworking.

Bizon the Champion decided to paint his old fence his favorite color, orange. The fence is represented as $ n $ vertical planks, put in a row. Adjacent planks have no gap between them. The planks are numbered from the left to the right starting from one, the $ i $ -th plank has the width of $ 1 $ meter and the height of $ a_{i} $ meters.

Bizon the Champion bought a brush in the shop, the brush's width is $ 1 $ meter. He can make vertical and horizontal strokes with the brush. During a stroke the brush's full surface must touch the fence at all the time (see the samples for the better understanding). What minimum number of strokes should Bizon the Champion do to fully paint the fence? Note that you are allowed to paint the same area of the fence multiple times.

## 输入格式

The first line contains integer $ n $ $ (1<=n<=5000) $ — the number of fence planks. The second line contains $ n $ space-separated integers $ a_{1},a_{2},...,a_{n} $ $ (1<=a_{i}<=10^{9}) $ .

## 输出格式

Print a single integer — the minimum number of strokes needed to paint the whole fence.

## 说明/提示

In the first sample you need to paint the fence in three strokes with the brush: the first stroke goes on height 1 horizontally along all the planks. The second stroke goes on height 2 horizontally and paints the first and second planks and the third stroke (it can be horizontal and vertical) finishes painting the fourth plank.

In the second sample you can paint the fence with two strokes, either two horizontal or two vertical strokes.

In the third sample there is only one plank that can be painted using a single vertical stroke.

## 样例 #1

### 输入

```
5
2 2 1 2 1

```

### 输出

```
3

```

## 样例 #2

### 输入

```
2
2 2

```

### 输出

```
2

```

## 样例 #3

### 输入

```
1
5

```

### 输出

```
1

```



---

---
title: "Addition on Segments"
layout: "post"
diff: 提高+/省选-
pid: CF981E
tag: ['线段树', '分治', '背包 DP']
---

# Addition on Segments

## 题目描述

Grisha come to a contest and faced the following problem.

You are given an array of size $ n $ , initially consisting of zeros. The elements of the array are enumerated from $ 1 $ to $ n $ . You perform $ q $ operations on the array. The $ i $ -th operation is described with three integers $ l_i $ , $ r_i $ and $ x_i $ ( $ 1 \leq l_i \leq r_i \leq n $ , $ 1 \leq x_i \leq n $ ) and means that you should add $ x_i $ to each of the elements with indices $ l_i, l_i + 1, \ldots, r_i $ . After all operations you should find the maximum in the array.

Grisha is clever, so he solved the problem quickly.

However something went wrong inside his head and now he thinks of the following question: "consider we applied some subset of the operations to the array. What are the possible values of the maximum in the array?"

Help Grisha, find all integers $ y $ between $ 1 $ and $ n $ such that if you apply some subset (possibly empty) of the operations, then the maximum in the array becomes equal to $ y $ .

## 输入格式

The first line contains two integers $ n $ and $ q $ ( $ 1 \leq n, q \leq 10^{4} $ ) — the length of the array and the number of queries in the initial problem.

The following $ q $ lines contain queries, one per line. The $ i $ -th of these lines contains three integers $ l_i $ , $ r_i $ and $ x_i $ ( $ 1 \leq l_i \leq r_i \leq n $ , $ 1 \leq x_i \leq n $ ), denoting a query of adding $ x_i $ to the segment from $ l_i $ -th to $ r_i $ -th elements of the array, inclusive.

## 输出格式

In the first line print the only integer $ k $ , denoting the number of integers from $ 1 $ to $ n $ , inclusive, that can be equal to the maximum in the array after applying some subset (possibly empty) of the given operations.

In the next line print these $ k $ integers from $ 1 $ to $ n $ — the possible values of the maximum. Print these integers in increasing order.

## 说明/提示

Consider the first example. If you consider the subset only of the first query, the maximum is equal to $ 1 $ . If you take only the second query, the maximum equals to $ 2 $ . If you take the first two queries, the maximum becomes $ 3 $ . If you take only the fourth query, the maximum becomes $ 4 $ . If you take the fourth query and something more, the maximum becomes greater that $ n $ , so you shouldn't print it.

In the second example you can take the first query to obtain $ 1 $ . You can take only the second query to obtain $ 2 $ . You can take all queries to obtain $ 3 $ .

In the third example you can obtain the following maximums:

- You can achieve the maximim of $ 2 $ by using queries: $ (1) $ .
- You can achieve the maximim of $ 3 $ by using queries: $ (2) $ .
- You can achieve the maximim of $ 5 $ by using queries: $ (1, 2) $ .
- You can achieve the maximim of $ 6 $ by using queries: $ (3) $ .
- You can achieve the maximim of $ 8 $ by using queries: $ (1, 3) $ .
- You can achieve the maximim of $ 9 $ by using queries: $ (2, 3) $ .

## 样例 #1

### 输入

```
4 3
1 3 1
2 4 2
3 4 4

```

### 输出

```
4
1 2 3 4 

```

## 样例 #2

### 输入

```
7 2
1 5 1
3 7 2

```

### 输出

```
3
1 2 3 

```

## 样例 #3

### 输入

```
10 3
1 1 2
1 1 3
1 1 6

```

### 输出

```
6
2 3 5 6 8 9 

```



---

