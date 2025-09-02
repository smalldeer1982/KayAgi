---
title: "Tree with Small Distances"
layout: "post"
diff: 普及+/提高
pid: CF1029E
tag: ['动态规划 DP', '贪心']
---

# Tree with Small Distances

## 题目描述

给定一颗有根树（根节点为 $1$）。要求往树中加入一些边使得从根节点到其他节点的距离至多是 $2$。 求加入边的最小数量。(边全部都是无向的)

## 输入格式

第一行一个整数 $n$，表示树中的节点个数。 接下来 $n−1$ 行，每行两个整数 $x,y$，表示 $x,y$ 之间有一条连边。

## 输出格式

一个整数，表示加入边的最小数量。

## 说明/提示

$2 \le n \le 2\times 10^5$

## 样例 #1

### 输入

```
7
1 2
2 3
2 4
4 5
4 6
5 7

```

### 输出

```
2

```

## 样例 #2

### 输入

```
7
1 2
1 3
2 4
2 5
3 6
1 7

```

### 输出

```
0

```

## 样例 #3

### 输入

```
7
1 2
2 3
3 4
3 5
3 6
3 7

```

### 输出

```
1

```



---

---
title: "Vasya and Good Sequences"
layout: "post"
diff: 普及+/提高
pid: CF1030E
tag: ['动态规划 DP', '枚举', '进制']
---

# Vasya and Good Sequences

## 题目描述

Vasya has a sequence $ a $ consisting of $ n $ integers $ a_1, a_2, \dots, a_n $ . Vasya may pefrom the following operation: choose some number from the sequence and swap any pair of bits in its binary representation. For example, Vasya can transform number $ 6 $ $ (\dots 00000000110_2) $ into $ 3 $ $ (\dots 00000000011_2) $ , $ 12 $ $ (\dots 000000001100_2) $ , $ 1026 $ $ (\dots 10000000010_2) $ and many others. Vasya can use this operation any (possibly zero) number of times on any number from the sequence.

Vasya names a sequence as good one, if, using operation mentioned above, he can obtain the sequence with [bitwise exclusive or](https://en.wikipedia.org/wiki/Exclusive_or) of all elements equal to $ 0 $ .

For the given sequence $ a_1, a_2, \ldots, a_n $ Vasya'd like to calculate number of integer pairs $ (l, r) $ such that $ 1 \le l \le r \le n $ and sequence $ a_l, a_{l + 1}, \dots, a_r $ is good.

## 输入格式

The first line contains a single integer $ n $ ( $ 1 \le n \le 3 \cdot 10^5 $ ) — length of the sequence.

The second line contains $ n $ integers $ a_1, a_2, \dots, a_n $ ( $ 1 \le a_i \le 10^{18} $ ) — the sequence $ a $ .

## 输出格式

Print one integer — the number of pairs $ (l, r) $ such that $ 1 \le l \le r \le n $ and the sequence $ a_l, a_{l + 1}, \dots, a_r $ is good.

## 说明/提示

In the first example pairs $ (2, 3) $ and $ (1, 3) $ are valid. Pair $ (2, 3) $ is valid since $ a_2 = 7 \rightarrow 11 $ , $ a_3 = 14 \rightarrow 11 $ and $ 11 \oplus 11 = 0 $ , where $ \oplus $ — bitwise exclusive or. Pair $ (1, 3) $ is valid since $ a_1 = 6 \rightarrow 3 $ , $ a_2 = 7 \rightarrow 13 $ , $ a_3 = 14 \rightarrow 14 $ and $ 3 \oplus 13 \oplus 14 = 0 $ .

In the second example pairs $ (1, 2) $ , $ (2, 3) $ , $ (3, 4) $ and $ (1, 4) $ are valid.

## 样例 #1

### 输入

```
3
6 7 14

```

### 输出

```
2

```

## 样例 #2

### 输入

```
4
1 2 1 16

```

### 输出

```
4

```



---

---
title: "Bicolorings"
layout: "post"
diff: 普及+/提高
pid: CF1051D
tag: ['动态规划 DP', '状态合并', '连通块']
---

# Bicolorings

## 题目描述

**题目大意：**

给定一个$2\times n$的棋盘，可以对上面的格子黑白染色，求染色后棋盘上的联通块的个数正好为$k$的染色方案数

## 输入格式

一行两个整数$n,k$

## 输出格式

一个整数，表示方案数

## 样例 #1

### 输入

```
3 4

```

### 输出

```
12

```

## 样例 #2

### 输入

```
4 1

```

### 输出

```
2

```

## 样例 #3

### 输入

```
1 2

```

### 输出

```
2

```



---

---
title: "Array Without Local Maximums"
layout: "post"
diff: 普及+/提高
pid: CF1067A
tag: ['动态规划 DP']
---

# Array Without Local Maximums

## 题目描述

$Ivan$偶然发现一个旧的生日礼物。礼物是一个含有$n$个元素的数组，每个元素都介于$1$和$200$之间。但是现在数组已经很旧了，有的数字难以看清。他记得对于所有元素，它的相邻元素中至少有一个不小于它。也就是说：

$a_1\le a_2,a_n\le a_{n-1}$且$a_i\le \max \left( a_{i-1},a_{i+1} \right) $对于任意$i\in \left[ 2,n-1 \right] $都成立。

$Ivan$想知道有多少种方案能够还原这个数组。当然，还原后要保证每个元素仍然介于$1$和$200$之间。输出方案数对$998244353$取模的结果。

## 输入格式

第一行一个整数$n\left( 2\le n\le 10^5 \right)$，表示数组大小。

第二行$n$个整数，表示数组中的元素（保证每个元素都介于$1$和$200$之间）。若$a_i=-1$表示这个数已经看不清了。

## 输出格式

方案数对$998244353$取模的结果。

## 说明/提示

第一个样例，$a_2$只能为$2$。

第二个样例，$a_1=a_2$，所以有$200$中可能。

## 样例 #1

### 输入

```
3
1 -1 2

```

### 输出

```
1

```

## 样例 #2

### 输入

```
2
-1 -1

```

### 输出

```
200

```



---

---
title: "LCIS"
layout: "post"
diff: 普及+/提高
pid: CF10D
tag: ['动态规划 DP', '树状数组', '前缀和']
---

# LCIS

## 题目描述

This problem differs from one which was on the online contest.

The sequence $ a_{1},a_{2},...,a_{n} $ is called increasing, if $ a_{i}<a_{i+1} $ for $ i<n $ .

The sequence $ s_{1},s_{2},...,s_{k} $ is called the subsequence of the sequence $ a_{1},a_{2},...,a_{n} $ , if there exist such a set of indexes $ 1<=i_{1}<i_{2}<...<i_{k}<=n $ that $ a_{ij}=s_{j} $ . In other words, the sequence $ s $ can be derived from the sequence $ a $ by crossing out some elements.

You are given two sequences of integer numbers. You are to find their longest common increasing subsequence, i.e. an increasing sequence of maximum length that is the subsequence of both sequences.

## 输入格式

The first line contains an integer $ n $ ( $ 1<=n<=500 $ ) — the length of the first sequence. The second line contains $ n $ space-separated integers from the range $ [0,10^{9}] $ — elements of the first sequence. The third line contains an integer $ m $ ( $ 1<=m<=500 $ ) — the length of the second sequence. The fourth line contains $ m $ space-separated integers from the range $ [0,10^{9}] $ — elements of the second sequence.

## 输出格式

In the first line output $ k $ — the length of the longest common increasing subsequence. In the second line output the subsequence itself. Separate the elements with a space. If there are several solutions, output any.

## 样例 #1

### 输入

```
7
2 3 1 6 5 4 6
4
1 3 5 6

```

### 输出

```
3
3 5 6 

```

## 样例 #2

### 输入

```
5
1 2 0 2 1
3
1 0 1

```

### 输出

```
2
0 1 

```



---

---
title: "Xor Tree"
layout: "post"
diff: 普及+/提高
pid: CF1446C
tag: ['动态规划 DP', '字典树 Trie']
---

# Xor Tree

## 题目描述

For a given sequence of distinct non-negative integers $ (b_1, b_2, \dots, b_k) $ we determine if it is good in the following way:

- Consider a graph on $ k $ nodes, with numbers from $ b_1 $ to $ b_k $ written on them.
- For every $ i $ from $ 1 $ to $ k $ : find such $ j $ ( $ 1 \le j \le k $ , $ j\neq i $ ), for which $ (b_i \oplus b_j) $ is the smallest among all such $ j $ , where $ \oplus $ denotes the operation of bitwise XOR ([https://en.wikipedia.org/wiki/Bitwise\_operation#XOR](https://en.wikipedia.org/wiki/Bitwise_operation#XOR)). Next, draw an undirected edge between vertices with numbers $ b_i $ and $ b_j $ in this graph.
- We say that the sequence is good if and only if the resulting graph forms a tree (is connected and doesn't have any simple cycles).

It is possible that for some numbers $ b_i $ and $ b_j $ , you will try to add the edge between them twice. Nevertheless, you will add this edge only once.

You can find an example below (the picture corresponding to the first test case).

Sequence $ (0, 1, 5, 2, 6) $ is not good as we cannot reach $ 1 $ from $ 5 $ .

However, sequence $ (0, 1, 5, 2) $ is good.

 ![](https://cdn.luogu.com.cn/upload/vjudge_pic/CF1446C/787661480e10ca394e5bb0097a1db13aac775e6e.png)You are given a sequence $ (a_1, a_2, \dots, a_n) $ of distinct non-negative integers. You would like to remove some of the elements (possibly none) to make the remaining sequence good. What is the minimum possible number of removals required to achieve this goal?

It can be shown that for any sequence, we can remove some number of elements, leaving at least $ 2 $ , so that the remaining sequence is good.

## 输入格式

The first line contains a single integer $ n $ ( $ 2 \le n \le 200,000 $ ) — length of the sequence.

The second line contains $ n $ distinct non-negative integers $ a_1, a_2, \ldots, a_n $ ( $ 0 \le a_i \le 10^9 $ ) — the elements of the sequence.

## 输出格式

You should output exactly one integer — the minimum possible number of elements to remove in order to make the remaining sequence good.

## 说明/提示

Note that numbers which you remove don't impact the procedure of telling whether the resulting sequence is good.

It is possible that for some numbers $ b_i $ and $ b_j $ , you will try to add the edge between them twice. Nevertheless, you will add this edge only once.

## 样例 #1

### 输入

```
5
0 1 5 2 6
```

### 输出

```
1
```

## 样例 #2

### 输入

```
7
6 9 8 7 3 5 2
```

### 输出

```
2
```



---

---
title: "Not Adding"
layout: "post"
diff: 普及+/提高
pid: CF1627D
tag: ['动态规划 DP']
---

# Not Adding

## 题目描述

You have an array $ a_1, a_2, \dots, a_n $ consisting of $ n $ distinct integers. You are allowed to perform the following operation on it: 

- Choose two elements from the array $ a_i $ and $ a_j $ ( $ i \ne j $ ) such that $ \gcd(a_i, a_j) $ is not present in the array, and add $ \gcd(a_i, a_j) $ to the end of the array. Here $ \gcd(x, y) $ denotes [greatest common divisor (GCD)](https://en.wikipedia.org/wiki/Greatest_common_divisor) of integers $ x $ and $ y $ .

Note that the array changes after each operation, and the subsequent operations are performed on the new array.

What is the maximum number of times you can perform the operation on the array?

## 输入格式

The first line consists of a single integer $ n $ ( $ 2 \le n \le 10^6 $ ).

The second line consists of $ n $ integers $ a_1, a_2, \dots, a_n $ ( $ 1 \leq a_i \leq 10^6 $ ). All $ a_i $ are distinct.

## 输出格式

Output a single line containing one integer — the maximum number of times the operation can be performed on the given array.

## 说明/提示

In the first example, one of the ways to perform maximum number of operations on the array is:

- Pick $ i = 1, j= 5 $ and add $ \gcd(a_1, a_5) = \gcd(4, 30) = 2 $ to the array.
- Pick $ i = 2, j= 4 $ and add $ \gcd(a_2, a_4) = \gcd(20, 25) = 5 $ to the array.
- Pick $ i = 2, j= 5 $ and add $ \gcd(a_2, a_5) = \gcd(20, 30) = 10 $ to the array.

It can be proved that there is no way to perform more than $ 3 $ operations on the original array.

In the second example one can add $ 3 $ , then $ 1 $ , then $ 5 $ , and $ 2 $ .

## 样例 #1

### 输入

```
5
4 20 1 25 30
```

### 输出

```
3
```

## 样例 #2

### 输入

```
3
6 10 15
```

### 输出

```
4
```



---

---
title: "Infinite Set"
layout: "post"
diff: 普及+/提高
pid: CF1635D
tag: ['动态规划 DP']
---

# Infinite Set

## 题目描述

You are given an array $ a $ consisting of $ n $ distinct positive integers.

Let's consider an infinite integer set $ S $ which contains all integers $ x $ that satisfy at least one of the following conditions:

1. $ x = a_i $ for some $ 1 \leq i \leq n $ .
2. $ x = 2y + 1 $ and $ y $ is in $ S $ .
3. $ x = 4y $ and $ y $ is in $ S $ .

For example, if $ a = [1,2] $ then the $ 10 $ smallest elements in $ S $ will be $ \{1,2,3,4,5,7,8,9,11,12\} $ .

Find the number of elements in $ S $ that are strictly smaller than $ 2^p $ . Since this number may be too large, print it modulo $ 10^9 + 7 $ .

## 输入格式

The first line contains two integers $ n $ and $ p $ $ (1 \leq n, p \leq 2 \cdot 10^5) $ .

The second line contains $ n $ integers $ a_1,a_2,\ldots,a_n $ $ (1 \leq a_i \leq 10^9) $ .

It is guaranteed that all the numbers in $ a $ are distinct.

## 输出格式

Print a single integer, the number of elements in $ S $ that are strictly smaller than $ 2^p $ . Remember to print it modulo $ 10^9 + 7 $ .

## 说明/提示

In the first example, the elements smaller than $ 2^4 $ are $ \{1, 3, 4, 6, 7, 9, 12, 13, 15\} $ .

In the second example, the elements smaller than $ 2^7 $ are $ \{5,11,20,23,39,41,44,47,79,80,83,89,92,95\} $ .

## 样例 #1

### 输入

```
2 4
6 1
```

### 输出

```
9
```

## 样例 #2

### 输入

```
4 7
20 39 5 200
```

### 输出

```
14
```

## 样例 #3

### 输入

```
2 200000
48763 1000000000
```

### 输出

```
448201910
```



---

---
title: "Yet Another Minimization Problem"
layout: "post"
diff: 普及+/提高
pid: CF1637D
tag: ['动态规划 DP', '背包 DP']
---

# Yet Another Minimization Problem

## 题目描述

You are given two arrays $ a $ and $ b $ , both of length $ n $ .

You can perform the following operation any number of times (possibly zero): select an index $ i $ ( $ 1 \leq i \leq n $ ) and swap $ a_i $ and $ b_i $ .

Let's define the cost of the array $ a $ as $ \sum_{i=1}^{n} \sum_{j=i + 1}^{n} (a_i + a_j)^2 $ . Similarly, the cost of the array $ b $ is $ \sum_{i=1}^{n} \sum_{j=i + 1}^{n} (b_i + b_j)^2 $ .

Your task is to minimize the total cost of two arrays.

## 输入格式

Each test case consists of several test cases. The first line contains a single integer $ t $ ( $ 1 \leq t \leq 40 $ ) — the number of test cases. The following is a description of the input data sets.

The first line of each test case contains an integer $ n $ ( $ 1 \leq n \leq 100 $ ) — the length of both arrays.

The second line of each test case contains $ n $ integers $ a_1, a_2, \ldots, a_n $ ( $ 1 \leq a_i \leq 100 $ ) — elements of the first array.

The third line of each test case contains $ n $ integers $ b_1, b_2, \ldots, b_n $ ( $ 1 \leq b_i \leq 100 $ ) — elements of the second array.

It is guaranteed that the sum of $ n $ over all test cases does not exceed $ 100 $ .

## 输出格式

For each test case, print the minimum possible total cost.

## 说明/提示

In the second test case, in one of the optimal answers after all operations $ a = [2, 6, 4, 6] $ , $ b = [3, 7, 6, 1] $ .

The cost of the array $ a $ equals to $ (2 + 6)^2 + (2 + 4)^2 + (2 + 6)^2 + (6 + 4)^2 + (6 + 6)^2 + (4 + 6)^2 = 508 $ .

The cost of the array $ b $ equals to $ (3 + 7)^2 + (3 + 6)^2 + (3 + 1)^2 + (7 + 6)^2 + (7 + 1)^2 + (6 + 1)^2 = 479 $ .

The total cost of two arrays equals to $ 508 + 479 = 987 $ .

## 样例 #1

### 输入

```
3
1
3
6
4
3 6 6 6
2 7 4 1
4
6 7 2 4
2 5 3 5
```

### 输出

```
0
987
914
```



---

---
title: "Vitaly and Advanced Useless Algorithms"
layout: "post"
diff: 普及+/提高
pid: CF1650F
tag: ['动态规划 DP', '背包 DP']
---

# Vitaly and Advanced Useless Algorithms

## 题目描述

Vitaly enrolled in the course Advanced Useless Algorithms. The course consists of $ n $ tasks. Vitaly calculated that he has $ a_i $ hours to do the task $ i $ from the day he enrolled in the course. That is, the deadline before the $ i $ -th task is $ a_i $ hours. The array $ a $ is sorted in ascending order, in other words, the job numbers correspond to the order in which the assignments are turned in.

Vitaly does everything conscientiously, so he wants to complete each task by $ 100 $ percent, or more. Initially, his completion rate for each task is $ 0 $ percent.

Vitaly has $ m $ training options, each option can be used not more than once. The $ i $ th option is characterized by three integers: $ e_i, t_i $ and $ p_i $ . If Vitaly uses the $ i $ th option, then after $ t_i $ hours (from the current moment) he will increase the progress of the task $ e_i $ by $ p_i $ percent.

For example, let Vitaly have $ 3 $ of tasks to complete. Let the array $ a $ have the form: $ a = [5, 7, 8] $ . Suppose Vitaly has $ 5 $ of options: $ [e_1=1, t_1=1, p_1=30] $ , $ [e_2=2, t_2=3, p_2=50] $ , $ [e_3=2, t_3=3, p_3=100] $ , $ [e_4=1, t_4=1, p_4=80] $ , $ [e_5=3, t_5=3, p_5=100] $ .

Then, if Vitaly prepares in the following way, he will be able to complete everything in time:

- Vitaly chooses the $ 4 $ -th option. Then in $ 1 $ hour, he will complete the $ 1 $ -st task at $ 80 $ percent. He still has $ 4 $ hours left before the deadline for the $ 1 $ -st task.
- Vitaly chooses the $ 3 $ -rd option. Then in $ 3 $ hours, he will complete the $ 2 $ -nd task in its entirety. He has another $ 1 $ hour left before the deadline for the $ 1 $ -st task and $ 4 $ hours left before the deadline for the $ 3 $ -rd task.
- Vitaly chooses the $ 1 $ -st option. Then after $ 1 $ hour, he will complete the $ 1 $ -st task for $ 110 $ percent, which means that he will complete the $ 1 $ -st task just in time for the deadline.
- Vitaly chooses the $ 5 $ -th option. He will complete the $ 3 $ -rd task for $ 2 $ hours, and after another $ 1 $ hour, Vitaly will complete the $ 3 $ -rd task in its entirety.

Thus, Vitaly has managed to complete the course completely and on time, using the $ 4 $ options.

Help Vitaly — print the options for Vitaly to complete the tasks in the correct order. Please note: each option can be used not more than once. If there are several possible answers, it is allowed to output any of them.

## 输入格式

The first line of input data contains an integer $ T $ ( $ 1 \le T \le 10^4 $ ) —the number of input test cases in the test.

The descriptions of the input test case follow.

The first line of each test case description contains two integers $ n $ and $ m $ ( $ 1 \le n,m \le 10^5 $ ) —the number of jobs and the number of training options, respectively.

The next line contains $ n $ numbers $ a_1, a_2, \dots, a_n $ ( $ 1 \le a_i \le 10^9 $ ) — the time before the deadline of job $ i $ . The array values — are non-decreasing, that is $ a_1 \le a_2 \le \dots \le a_n $ .

The following $ m $ lines contain triples of numbers $ e_i, t_i, p_i $ ( $ 1 \le e_i \le n $ , $ 1 \le t_i \le 10^9 $ , $ 1 \le p_i \le 100 $ ) — if Vitaly chooses this option, then after $ t_i $ hours he will increase the progress of the task $ e_i $ by $ p_i $ percent. The options are numbered from $ 1 $ to $ m $ in order in the input data.

It is guaranteed that the sum of $ n+m $ on all test cases does not exceed $ 2 \cdot 10^5 $ .

## 输出格式

For each test case, print on the first line the number $ k $ , meaning that for $ k $ of options, Vitaly will be able to complete each task by $ 100 $ percent or more on time. The options should not be repeated. Or print -1 if Vitaly is unable to complete all tasks in time.

If there is an answer, on the next line print $ k $ of different integers from $ 1 $ to $ m $ — the numbers of the options in the order you want. If there is more than one answer, it is allowed to print any of them.

## 样例 #1

### 输入

```
5
3 5
5 7 8
1 1 30
2 3 50
2 3 100
1 1 80
3 3 100
1 5
51
1 36 91
1 8 40
1 42 83
1 3 45
1 13 40
2 9
9 20
2 8 64
2 7 64
1 20 56
2 8 76
2 20 48
1 2 89
1 3 38
2 18 66
1 7 51
3 2
7 18 33
1 5 80
3 4 37
2 5
569452312 703565975
1 928391659 66
1 915310 82
2 87017081 92
1 415310 54
2 567745964 82
```

### 输出

```
4
1 4 3 5 
3
2 4 5 
4
6 7 1 2 
-1
4
2 4 3 5
```

## 样例 #2

### 输入

```
3
3 9
20 31 40
1 9 64
3 17 100
3 9 59
3 18 57
3 20 49
2 20 82
2 14 95
1 8 75
2 16 67
2 6
20 36
2 2 66
2 20 93
1 3 46
1 10 64
2 8 49
2 18 40
1 1
1000000000
1 1000000000 100
```

### 输出

```
-1
4
3 4 1 5 
1
1
```



---

---
title: "Counting Shortcuts"
layout: "post"
diff: 普及+/提高
pid: CF1650G
tag: ['动态规划 DP', '图论']
---

# Counting Shortcuts

## 题目描述

Given an undirected connected graph with $ n $ vertices and $ m $ edges. The graph contains no loops (edges from a vertex to itself) and multiple edges (i.e. no more than one edge between each pair of vertices). The vertices of the graph are numbered from $ 1 $ to $ n $ .

Find the number of paths from a vertex $ s $ to $ t $ whose length differs from the shortest path from $ s $ to $ t $ by no more than $ 1 $ . It is necessary to consider all suitable paths, even if they pass through the same vertex or edge more than once (i.e. they are not simple).

 ![](https://cdn.luogu.com.cn/upload/vjudge_pic/CF1650G/3360dade3a147f98c6dd4b25980520a2ae6123a6.png)Graph consisting of $ 6 $ of vertices and $ 8 $ of edgesFor example, let $ n = 6 $ , $ m = 8 $ , $ s = 6 $ and $ t = 1 $ , and let the graph look like the figure above. Then the length of the shortest path from $ s $ to $ t $ is $ 1 $ . Consider all paths whose length is at most $ 1 + 1 = 2 $ .

- $ 6 \rightarrow 1 $ . The length of the path is $ 1 $ .
- $ 6 \rightarrow 4 \rightarrow 1 $ . Path length is $ 2 $ .
- $ 6 \rightarrow 2 \rightarrow 1 $ . Path length is $ 2 $ .
- $ 6 \rightarrow 5 \rightarrow 1 $ . Path length is $ 2 $ .

There is a total of $ 4 $ of matching paths.

## 输入格式

The first line of test contains the number $ t $ ( $ 1 \le t \le 10^4 $ ) —the number of test cases in the test.

Before each test case, there is a blank line.

The first line of test case contains two numbers $ n, m $ ( $ 2 \le n \le 2 \cdot 10^5 $ , $ 1 \le m \le 2 \cdot 10^5 $ ) —the number of vertices and edges in the graph.

The second line contains two numbers $ s $ and $ t $ ( $ 1 \le s, t \le n $ , $ s \neq t $ ) —the numbers of the start and end vertices of the path.

The following $ m $ lines contain descriptions of edges: the $ i $ th line contains two integers $ u_i $ , $ v_i $ ( $ 1 \le u_i,v_i \le n $ ) — the numbers of vertices that connect the $ i $ th edge. It is guaranteed that the graph is connected and does not contain loops and multiple edges.

It is guaranteed that the sum of values $ n $ on all test cases of input data does not exceed $ 2 \cdot 10^5 $ . Similarly, it is guaranteed that the sum of values $ m $ on all test cases of input data does not exceed $ 2 \cdot 10^5 $ .

## 输出格式

For each test case, output a single number — the number of paths from $ s $ to $ t $ such that their length differs from the length of the shortest path by no more than $ 1 $ .

Since this number may be too large, output it modulo $ 10^9 + 7 $ .

## 样例 #1

### 输入

```
4

4 4
1 4
1 2
3 4
2 3
2 4

6 8
6 1
1 4
1 6
1 5
1 2
5 6
4 6
6 3
2 6

5 6
1 3
3 5
5 4
3 1
4 2
2 1
1 4

8 18
5 1
2 1
3 1
4 2
5 2
6 5
7 3
8 4
6 4
8 7
1 4
4 7
1 6
6 7
3 8
8 5
4 5
4 3
8 2
```

### 输出

```
2
4
1
11
```



---

---
title: "Tokitsukaze and Good 01-String (hard version)"
layout: "post"
diff: 普及+/提高
pid: CF1678B2
tag: ['动态规划 DP', '贪心']
---

# Tokitsukaze and Good 01-String (hard version)

## 题目描述

This is the hard version of the problem. The only difference between the two versions is that the harder version asks additionally for a minimum number of subsegments.

Tokitsukaze has a binary string $ s $ of length $ n $ , consisting only of zeros and ones, $ n $ is even.

Now Tokitsukaze divides $ s $ into the minimum number of contiguous subsegments, and for each subsegment, all bits in each subsegment are the same. After that, $ s $ is considered good if the lengths of all subsegments are even.

For example, if $ s $ is "11001111", it will be divided into "11", "00" and "1111". Their lengths are $ 2 $ , $ 2 $ , $ 4 $ respectively, which are all even numbers, so "11001111" is good. Another example, if $ s $ is "1110011000", it will be divided into "111", "00", "11" and "000", and their lengths are $ 3 $ , $ 2 $ , $ 2 $ , $ 3 $ . Obviously, "1110011000" is not good.

Tokitsukaze wants to make $ s $ good by changing the values of some positions in $ s $ . Specifically, she can perform the operation any number of times: change the value of $ s_i $ to '0' or '1' ( $ 1 \leq i \leq n $ ). Can you tell her the minimum number of operations to make $ s $ good? Meanwhile, she also wants to know the minimum number of subsegments that $ s $ can be divided into among all solutions with the minimum number of operations.

## 输入格式

The first contains a single positive integer $ t $ ( $ 1 \leq t \leq 10\,000 $ ) — the number of test cases.

For each test case, the first line contains a single integer $ n $ ( $ 2 \leq n \leq 2 \cdot 10^5 $ ) — the length of $ s $ , it is guaranteed that $ n $ is even.

The second line contains a binary string $ s $ of length $ n $ , consisting only of zeros and ones.

It is guaranteed that the sum of $ n $ over all test cases does not exceed $ 2 \cdot 10^5 $ .

## 输出格式

For each test case, print a single line with two integers — the minimum number of operations to make $ s $ good, and the minimum number of subsegments that $ s $ can be divided into among all solutions with the minimum number of operations.

## 说明/提示

In the first test case, one of the ways to make $ s $ good is the following.

Change $ s_3 $ , $ s_6 $ and $ s_7 $ to '0', after that $ s $ becomes "1100000000", it can be divided into "11" and "00000000", which lengths are $ 2 $ and $ 8 $ respectively, the number of subsegments of it is $ 2 $ . There are other ways to operate $ 3 $ times to make $ s $ good, such as "1111110000", "1100001100", "1111001100", the number of subsegments of them are $ 2 $ , $ 4 $ , $ 4 $ respectively. It's easy to find that the minimum number of subsegments among all solutions with the minimum number of operations is $ 2 $ .

In the second, third and fourth test cases, $ s $ is good initially, so no operation is required.

## 样例 #1

### 输入

```
5
10
1110011000
8
11001111
2
00
2
11
6
100110
```

### 输出

```
3 2
0 3
0 1
0 1
3 1
```



---

---
title: "Moving Chips"
layout: "post"
diff: 普及+/提高
pid: CF1680E
tag: ['动态规划 DP', '贪心']
---

# Moving Chips

## 题目描述

## 题意翻译  
### 题意简述
给你一个大小为$2$×$n$的棋盘，
棋子用'*'表示，空位用'.'表示。  
在一次移动中，你可以选择任何棋子并将其移动到棋盘的任何相邻的格子，如果目的格子中有棋子则把他们合并为一个。

## 输入格式

第一行一个正整数$t$表示数据组数。  
对于每组数据，第一行一个正整数$n$表示棋盘列数，接下来两行每行输入一个字符串$s$，
表示棋盘初始状态。

## 输出格式

对于每组数据输出一个正整数表示在棋盘上正好留下一个棋子所需的最小移动数。  
### 数据规模  
$1$<=$t$<=$10^{4}$，$1$<=$n$<=$2\cdot$$10^{5}$  
所有测试案例的$n$之和不超过$2$$\cdot$$10^{5}$
($\sum_{}^{}$$n$<=$2$$\cdot$$10^{5}$)

## 样例 #1

### 输入

```
5
1
*
.
2
.*
**
3
*.*
.*.
4
**.*
**..
5
**...
...**
```

### 输出

```
0
2
3
5
5
```



---

---
title: "Color with Occurrences"
layout: "post"
diff: 普及+/提高
pid: CF1714D
tag: ['动态规划 DP', '贪心']
---

# Color with Occurrences

## 题目描述

You are given some text $ t $ and a set of $ n $ strings $ s_1, s_2, \dots, s_n $ .

In one step, you can choose any occurrence of any string $ s_i $ in the text $ t $ and color the corresponding characters of the text in red. For example, if $ t=\texttt{bababa} $ and $ s_1=\texttt{ba} $ , $ s_2=\texttt{aba} $ , you can get $ t=\color{red}{\texttt{ba}}\texttt{baba} $ , $ t=\texttt{b}\color{red}{\texttt{aba}}\texttt{ba} $ or $ t=\texttt{bab}\color{red}{\texttt{aba}} $ in one step.

You want to color all the letters of the text $ t $ in red. When you color a letter in red again, it stays red.

In the example above, three steps are enough:

- Let's color $ t[2 \dots 4]=s_2=\texttt{aba} $ in red, we get $ t=\texttt{b}\color{red}{\texttt{aba}}\texttt{ba} $ ;
- Let's color $ t[1 \dots 2]=s_1=\texttt{ba} $ in red, we get $ t=\color{red}{\texttt{baba}}\texttt{ba} $ ;
- Let's color $ t[4 \dots 6]=s_2=\texttt{aba} $ in red, we get $ t=\color{red}{\texttt{bababa}} $ .

Each string $ s_i $ can be applied any number of times (or not at all). Occurrences for coloring can intersect arbitrarily.

Determine the minimum number of steps needed to color all letters $ t $ in red and how to do it. If it is impossible to color all letters of the text $ t $ in red, output -1.

## 输入格式

The first line of the input contains an integer $ q $ ( $ 1 \le q \le 100 $ ) —the number of test cases in the test.

The descriptions of the test cases follow.

The first line of each test case contains the text $ t $ ( $ 1 \le |t| \le 100 $ ), consisting only of lowercase Latin letters, where $ |t| $ is the length of the text $ t $ .

The second line of each test case contains a single integer $ n $ ( $ 1 \le n \le 10 $ ) — the number of strings in the set.

This is followed by $ n $ lines, each containing a string $ s_i $ ( $ 1 \le |s_i| \le 10 $ ) consisting only of lowercase Latin letters, where $ |s_i| $ — the length of string $ s_i $ .

## 输出格式

For each test case, print the answer on a separate line.

If it is impossible to color all the letters of the text in red, print a single line containing the number -1.

Otherwise, on the first line, print the number $ m $ — the minimum number of steps it will take to turn all the letters $ t $ red.

Then in the next $ m $ lines print pairs of indices: $ w_j $ and $ p_j $ ( $ 1 \le j \le m $ ), which denote that the string with index $ w_j $ was used as a substring to cover the occurrences starting in the text $ t $ from position $ p_j $ . The pairs can be output in any order.

If there are several answers, output any of them.

## 说明/提示

The first test case is explained in the problem statement.

In the second test case, it is impossible to color all the letters of the text in red.

## 样例 #1

### 输入

```
6
bababa
2
ba
aba
caba
2
bac
acab
abacabaca
3
aba
bac
aca
baca
3
a
c
b
codeforces
4
def
code
efo
forces
aaaabbbbcccceeee
4
eeee
cccc
aaaa
bbbb
```

### 输出

```
3
2 2
1 1
2 4
-1
4
1 1
2 6
3 3
3 7
4
3 1
1 2
2 3
1 4
2
4 5
2 1
4
3 1
4 5
2 9
1 13
```



---

---
title: "Robot in a Hallway"
layout: "post"
diff: 普及+/提高
pid: CF1716C
tag: ['动态规划 DP']
---

# Robot in a Hallway

## 题目描述

有一 $2$ 行 $m$ 列的网格，从上到下编号为 $1$ 至 $2$，从左往右编号为 $1$ 至 $m$。

机器人开始时在网格 $(1,1)$ 内。一秒内，它可以进行如下任意一个动作：

- 走到上、下、左、右任意相邻的网格
- 待在网格内不动

开始时，除了网格 $(1,1)$ 其他格子都是锁着的。每个网格 $(i,j)$ 有一个值 $a_{i,j}$，表示该网格解锁的时间。只有经过至少 $a_{i,j}$ 秒后，机器人才可以进入网格 $(i,j)$。

机器人要走遍所有网格，且每个网格只能被访问一次（网格 $(1,1)$ 在一开始就被访问过）。访问可以在任意网格内结束。

实现如上操作的最快时间是什么？

## 输入格式

第一行是一个整数 $t$（$ 1 \le t \le 10^4$），表示测试用例的个数。

每个样例的第一行是一个整数 $m$（$ 2 \le m \le 2 \cdot 10^5 $），表示网格的列数。

下面两行中的第 $i$ 行有 $m$ 个整数 $ a_{i,1}, a_{i,2}, \dots, a_{i,m} $（$ 0 \le a_{i,j} \le 10^9 $），表示每个格子解锁的时间，其中 $a_{1,1}=0$。如果 $a_{i,j}=0$，表示网格 $(i,j)$ 一开始就是解锁的。

所有测试用例中 $m$ 的和不超过 $2 \times 10^5$。

## 输出格式

对于每个测试样例，输出一个整数：机器人走遍每一个网格且每个网格只被访问一次的最小时间。

## 样例 #1

### 输入

```
4
3
0 0 1
4 3 2
5
0 4 8 12 16
2 6 10 14 18
4
0 10 10 10
10 10 10 10
2
0 0
0 0
```

### 输出

```
5
19
17
3
```



---

---
title: "Chip Move"
layout: "post"
diff: 普及+/提高
pid: CF1716D
tag: ['动态规划 DP']
---

# Chip Move

## 题目描述

There is a chip on the coordinate line. Initially, the chip is located at the point $ 0 $ . You can perform any number of moves; each move increases the coordinate of the chip by some positive integer (which is called the length of the move). The length of the first move you make should be divisible by $ k $ , the length of the second move — by $ k+1 $ , the third — by $ k+2 $ , and so on.

For example, if $ k=2 $ , then the sequence of moves may look like this: $ 0 \rightarrow 4 \rightarrow 7 \rightarrow 19 \rightarrow 44 $ , because $ 4 - 0 = 4 $ is divisible by $ 2 = k $ , $ 7 - 4 = 3 $ is divisible by $ 3 = k + 1 $ , $ 19 - 7 = 12 $ is divisible by $ 4 = k + 2 $ , $ 44 - 19 = 25 $ is divisible by $ 5 = k + 3 $ .

You are given two positive integers $ n $ and $ k $ . Your task is to count the number of ways to reach the point $ x $ , starting from $ 0 $ , for every $ x \in [1, n] $ . The number of ways can be very large, so print it modulo $ 998244353 $ . Two ways are considered different if they differ as sets of visited positions.

## 输入格式

The first (and only) line of the input contains two integers $ n $ and $ k $ ( $ 1 \le k \le n \le 2 \cdot 10^5 $ ).

## 输出格式

Print $ n $ integers — the number of ways to reach the point $ x $ , starting from $ 0 $ , for every $ x \in [1, n] $ , taken modulo $ 998244353 $ .

## 说明/提示

Let's look at the first example:

Ways to reach the point $ 1 $ : $ [0, 1] $ ;

Ways to reach the point $ 2 $ : $ [0, 2] $ ;

Ways to reach the point $ 3 $ : $ [0, 1, 3] $ , $ [0, 3] $ ;

Ways to reach the point $ 4 $ : $ [0, 2, 4] $ , $ [0, 4] $ ;

Ways to reach the point $ 5 $ : $ [0, 1, 5] $ , $ [0, 3, 5] $ , $ [0, 5] $ ;

Ways to reach the point $ 6 $ : $ [0, 1, 3, 6] $ , $ [0, 2, 6] $ , $ [0, 4, 6] $ , $ [0, 6] $ ;

Ways to reach the point $ 7 $ : $ [0, 2, 4, 7] $ , $ [0, 1, 7] $ , $ [0, 3, 7] $ , $ [0, 5, 7] $ , $ [0, 7] $ ;

Ways to reach the point $ 8 $ : $ [0, 3, 5, 8] $ , $ [0, 1, 5, 8] $ , $ [0, 2, 8] $ , $ [0, 4, 8] $ , $ [0, 6, 8] $ , $ [0, 8] $ .

## 样例 #1

### 输入

```
8 1
```

### 输出

```
1 1 2 2 3 4 5 6
```

## 样例 #2

### 输入

```
10 2
```

### 输出

```
0 1 0 1 1 1 1 2 2 2
```



---

---
title: "Letter Picking"
layout: "post"
diff: 普及+/提高
pid: CF1728D
tag: ['动态规划 DP', '贪心', '区间 DP']
---

# Letter Picking

## 题目描述

Alice and Bob are playing a game. Initially, they are given a non-empty string $ s $ , consisting of lowercase Latin letters. The length of the string is even. Each player also has a string of their own, initially empty.

Alice starts, then they alternate moves. In one move, a player takes either the first or the last letter of the string $ s $ , removes it from $ s $ and prepends (adds to the beginning) it to their own string.

The game ends when the string $ s $ becomes empty. The winner is the player with a lexicographically smaller string. If the players' strings are equal, then it's a draw.

A string $ a $ is lexicographically smaller than a string $ b $ if there exists such position $ i $ that $ a_j = b_j $ for all $ j < i $ and $ a_i < b_i $ .

What is the result of the game if both players play optimally (e. g. both players try to win; if they can't, then try to draw)?

## 输入格式

The first line contains a single integer $ t $ ( $ 1 \le t \le 1000 $ ) — the number of testcases.

Each testcase consists of a single line — a non-empty string $ s $ , consisting of lowercase Latin letters. The length of the string $ s $ is even.

The total length of the strings over all testcases doesn't exceed $ 2000 $ .

## 输出格式

For each testcase, print the result of the game if both players play optimally. If Alice wins, print "Alice". If Bob wins, print "Bob". If it's a draw, print "Draw".

## 说明/提示

One of the possible games Alice and Bob can play in the first testcase:

1. Alice picks the first letter in $ s $ : $ s= $ "orces", $ a= $ "f", $ b= $ "";
2. Bob picks the last letter in $ s $ : $ s= $ "orce", $ a= $ "f", $ b= $ "s";
3. Alice picks the last letter in $ s $ : $ s= $ "orc", $ a= $ "ef", $ b= $ "s";
4. Bob picks the first letter in $ s $ : $ s= $ "rc", $ a= $ "ef", $ b= $ "os";
5. Alice picks the last letter in $ s $ : $ s= $ "r", $ a= $ "cef", $ b= $ "os";
6. Bob picks the remaining letter in $ s $ : $ s= $ "", $ a= $ "cef", $ b= $ "ros".

Alice wins because "cef" &lt; "ros". Neither of the players follows any strategy in this particular example game, so it doesn't show that Alice wins if both play optimally.

## 样例 #1

### 输入

```
2
forces
abba
```

### 输出

```
Alice
Draw
```



---

---
title: "Even Subarrays"
layout: "post"
diff: 普及+/提高
pid: CF1731C
tag: ['动态规划 DP', '数学', '前缀和']
---

# Even Subarrays

## 题目描述

You are given an integer array $ a_1, a_2, \dots, a_n $ ( $ 1 \le a_i \le n $ ).

Find the number of subarrays of $ a $ whose $ \operatorname{XOR} $ has an even number of divisors. In other words, find all pairs of indices $ (i, j) $ ( $ i \le j $ ) such that $ a_i \oplus a_{i + 1} \oplus \dots \oplus a_j $ has an even number of divisors.

For example, numbers $ 2 $ , $ 3 $ , $ 5 $ or $ 6 $ have an even number of divisors, while $ 1 $ and $ 4 $ — odd. Consider that $ 0 $ has an odd number of divisors in this task.

Here $ \operatorname{XOR} $ (or $ \oplus $ ) denotes the [bitwise XOR operation](https://en.wikipedia.org/wiki/Bitwise_operation#XOR).

Print the number of subarrays but multiplied by 2022... Okay, let's stop. Just print the actual answer.

## 输入格式

Each test contains multiple test cases. The first line contains the number of test cases $ t $ ( $ 1 \leq t \leq 10^4 $ ). Description of the test cases follows.

The first line of each test case contains a single integer $ n $ ( $ 2 \leq n \leq 2 \cdot 10^5 $ ) — the length of the array $ a $ .

The second line contains $ n $ integers $ a_1, a_2, \dots, a_n $ ( $ 1 \leq a_i \leq n $ ).

It is guaranteed that the sum of $ n $ over all test cases does not exceed $ 2 \cdot 10^5 $ .

## 输出格式

For each test case, print the number of subarrays, whose $ \operatorname{XOR} $ has an even number of divisors.

## 说明/提示

In the first test case, there are $ 4 $ subarrays whose $ \operatorname{XOR} $ has an even number of divisors: $ [3] $ , $ [3,1] $ , $ [1,2] $ , $ [2] $ .

In the second test case, there are $ 11 $ subarrays whose $ \operatorname{XOR} $ has an even number of divisors: $ [4,2] $ , $ [4,2,1] $ , $ [4,2,1,5] $ , $ [2] $ , $ [2,1] $ , $ [2,1,5] $ , $ [2,1,5,3] $ , $ [1,5,3] $ , $ [5] $ , $ [5,3] $ , $ [3] $ .

In the third test case, there is no subarray whose $ \operatorname{XOR} $ has an even number of divisors since $ \operatorname{XOR} $ of any subarray is either $ 4 $ or $ 0 $ .

## 样例 #1

### 输入

```
4
3
3 1 2
5
4 2 1 5 3
4
4 4 4 4
7
5 7 3 7 1 7 3
```

### 输出

```
4
11
0
20
```



---

---
title: "Sorting By Multiplication"
layout: "post"
diff: 普及+/提高
pid: CF1861D
tag: ['动态规划 DP']
---

# Sorting By Multiplication

## 题目描述

You are given an array $ a $ of length $ n $ , consisting of positive integers.

You can perform the following operation on this array any number of times (possibly zero):

- choose three integers $ l $ , $ r $ and $ x $ such that $ 1 \le l \le r \le n $ , and multiply every $ a_i $ such that $ l \le i \le r $ by $ x $ .

Note that you can choose any integer as $ x $ , it doesn't have to be positive.

You have to calculate the minimum number of operations to make the array $ a $ sorted in strictly ascending order (i. e. the condition $ a_1 < a_2 < \dots < a_n $ must be satisfied).

## 输入格式

The first line contains a single integer $ t $ ( $ 1 \le t \le 10^4 $ ) — the number of test cases.

The first line of each test case contains one integer $ n $ ( $ 1 \le n \le 2 \cdot 10^5 $ ) — the length of the array $ a $ .

The second line of each test case contains $ n $ integers $ a_1, a_2, \dots, a_n $ ( $ 1 \le a_i \le 10^9 $ ) — the array $ a $ .

Additional constraint on the input: the sum of $ n $ over all test cases does not exceed $ 2 \cdot 10^5 $ .

## 输出格式

For each test case, print one integer — the minimum number of operations required to make $ a $ sorted in strictly ascending order.

## 说明/提示

In the first test case, we can perform the operations as follows:

- $ l = 2 $ , $ r = 4 $ , $ x = 3 $ ;
- $ l = 4 $ , $ r = 4 $ , $ x = 2 $ ;
- $ l = 5 $ , $ r = 5 $ , $ x = 10 $ .

 After these operations, the array $ a $ becomes $ [1, 3, 6, 12, 20] $ .In the second test case, we can perform one operation as follows:

- $ l = 1 $ , $ r = 4 $ , $ x = -2 $ ;
- $ l = 6 $ , $ r = 6 $ , $ x = 1337 $ .

 After these operations, the array $ a $ becomes $ [-10, -8, -6, -4, 5, 1337] $ .In the third test case, the array $ a $ is already sorted.

## 样例 #1

### 输入

```
3
5
1 1 2 2 2
6
5 4 3 2 5 1
3
1 2 3
```

### 输出

```
3
2
0
```



---

---
title: "Flag 2"
layout: "post"
diff: 普及+/提高
pid: CF18E
tag: ['动态规划 DP', '枚举']
---

# Flag 2

## 题目描述

According to a new ISO standard, a flag of every country should have, strangely enough, a chequered field $ n×m $ , each square should be wholly painted one of 26 colours. The following restrictions are set:

- In each row at most two different colours can be used.
- No two adjacent squares can be painted the same colour.

Pay attention, please, that in one column more than two different colours can be used.

Berland's government took a decision to introduce changes into their country's flag in accordance with the new standard, at the same time they want these changes to be minimal. By the given description of Berland's flag you should find out the minimum amount of squares that need to be painted different colour to make the flag meet the new ISO standard. You are as well to build one of the possible variants of the new Berland's flag.

## 输入格式

The first input line contains 2 integers $ n $ and $ m $ ( $ 1<=n,m<=500 $ ) — amount of rows and columns in Berland's flag respectively. Then there follows the flag's description: each of the following $ n $ lines contains $ m $ characters. Each character is a letter from a to z, and it stands for the colour of the corresponding square.

## 输出格式

In the first line output the minimum amount of squares that need to be repainted to make the flag meet the new ISO standard. The following $ n $ lines should contain one of the possible variants of the new flag. Don't forget that the variant of the flag, proposed by you, should be derived from the old flag with the minimum amount of repainted squares. If the answer isn't unique, output any.

## 样例 #1

### 输入

```
3 4
aaaa
bbbb
cccc

```

### 输出

```
6
abab
baba
acac

```

## 样例 #2

### 输入

```
3 3
aba
aba
zzz

```

### 输出

```
4
aba
bab
zbz

```



---

---
title: "Feed Cats"
layout: "post"
diff: 普及+/提高
pid: CF1932F
tag: ['动态规划 DP']
---

# Feed Cats

## 题目描述

你在玩一个游戏，这个游戏有 $n$ 步。你有 $m$ 只猫，每只猫有特定的饲养时间 $[l_i,r_i]$。如果你在第 $x$ 步决定饲养，那么所有满足 $l_i\le x\le r_i$ 的猫都会被饲养；或者你不决定饲养，那么无事发生。但是如果一只猫被饲养了两次及以上，它就会死亡。请问在没有猫死亡的情况下，最多有多少只猫被饲养了至少一次？

## 输入格式

第一行一个整数 $t$，表示数据组数。每组数据格式如下：

第一行两个整数 $n,m$，含义如上。

接下来 $m$ 行每行两个整数 $l_i,r_i$，含义如上。

$1\le t\le10^4,1\le n,\sum n\le10^6,1\le m,\sum m\le2\times10^5,1\le l_i\le r_i\le n$。

## 输出格式

每组数据一行一个整数表示在满足条件的情况下最多有多少只猫被饲养了至少一次。

翻译 @\_Sunmoon\_

## 样例 #1

### 输入

```
3
15 6
2 10
3 5
2 4
7 7
8 12
11 11
1000 1
1 1000
5 10
1 2
3 4
3 4
3 4
3 4
1 1
1 2
3 3
3 4
3 4
```

### 输出

```
5
1
10
```



---

---
title: "Rudolf and k Bridges"
layout: "post"
diff: 普及+/提高
pid: CF1941E
tag: ['动态规划 DP', '单调队列']
---

# Rudolf and k Bridges

## 题目描述

Bernard loves visiting Rudolf, but he is always running late. The problem is that Bernard has to cross the river on a ferry. Rudolf decided to help his friend solve this problem.

The river is a grid of $ n $ rows and $ m $ columns. The intersection of the $ i $ -th row and the $ j $ -th column contains the number $ a_{i,j} $ — the depth in the corresponding cell. All cells in the first and last columns correspond to the river banks, so the depth for them is $ 0 $ .

 ![](https://cdn.luogu.com.cn/upload/vjudge_pic/CF1941E/2420e4ab48e7eae57737cc3a1dbfde24de284901.png) The river may look like this.Rudolf can choose the row $ (i,1), (i,2), \ldots, (i,m) $ and build a bridge over it. In each cell of the row, he can install a support for the bridge. The cost of installing a support in the cell $ (i,j) $ is $ a_{i,j}+1 $ . Supports must be installed so that the following conditions are met:

1. A support must be installed in cell $ (i,1) $ ;
2. A support must be installed in cell $ (i,m) $ ;
3. The distance between any pair of adjacent supports must be no more than $ d $ . The distance between supports $ (i, j_1) $ and $ (i, j_2) $ is $ |j_1 - j_2| - 1 $ .

Building just one bridge is boring. Therefore, Rudolf decided to build $ k $ bridges on consecutive rows of the river, that is, to choose some $ i $ ( $ 1 \le i \le n - k + 1 $ ) and independently build a bridge on each of the rows $ i, i + 1, \ldots, i + k - 1 $ . Help Rudolf minimize the total cost of installing supports.

## 输入格式

The first line contains a single integer $ t $ $ (1 \le t \le 10^3) $ — the number of test cases. The descriptions of the test cases follow.

The first line of each test case contains four integers $ n $ , $ m $ , $ k $ , and $ d $ ( $ 1 \le k \le n \le 100 $ , $ 3 \le m \le 2 \cdot 10^5 $ , $ 1 \le d \le m $ ) — the number of rows and columns of the field, the number of bridges, and the maximum distance between supports.

Then follow $ n $ lines, $ i $ -th line contains $ m $ positive integers $ a_{i, j} $ ( $ 0 \le a_{i, j} \le 10^6 $ , $ a_{i, 1} = a_{i, m} = 0 $ ) — the depths of the river cells.

It is guaranteed that the sum of $ n \cdot m $ for all sets of input data does not exceed $ 2 \cdot 10^5 $ .

## 输出格式

For each test case, output a single number — the minimum total cost of supports installation.

## 说明/提示

In the first test case, it is most profitable to build a bridge on the second row.

 ![](https://cdn.luogu.com.cn/upload/vjudge_pic/CF1941E/7ad474029f5a4a6573b004238d770f23ae9fe42a.png) It is not a top view, but side view: gray cells — bridge itself, white cells are empty, black cells — supports, blue cells — water, brown cells — river bottom.In the second test case, it is most profitable to build bridges on the second and third rows. The supports will be placed in cells $ (2, 3) $ , $ (3, 2) $ , and on the river banks.

In the third test case the supports can be placed along the river banks.

## 样例 #1

### 输入

```
5
3 11 1 4
0 1 2 3 4 5 4 3 2 1 0
0 1 2 3 2 1 2 3 3 2 0
0 1 2 3 5 5 5 5 5 2 0
4 4 2 1
0 3 3 0
0 2 1 0
0 1 2 0
0 3 3 0
4 5 2 5
0 1 1 1 0
0 2 2 2 0
0 2 1 1 0
0 3 2 1 0
1 8 1 1
0 10 4 8 4 4 2 0
4 5 3 2
0 8 4 4 0
0 3 4 8 0
0 8 1 10 0
0 10 1 5 0
```

### 输出

```
4
8
4
15
14
```



---

---
title: "Tandem Repeats?"
layout: "post"
diff: 普及+/提高
pid: CF1948D
tag: ['动态规划 DP', '枚举']
---

# Tandem Repeats?

## 题目描述

给定一个由**小写字母**和**问号** `?` 组成的字符串 $s$，你可以将问号 `?` 替换为任何小写字母。

替换后，你需要找到 $s$ 中最长的**重复**子串。

一个长度为 $2n$ 的字符串 $t$ 是**重复**串，当且仅当对于所有 $1 \leq i \leq n$，有 $t_i = t_{i+n}$。

## 输入格式

**本题目含多组数据。**

第一行，一个正整数 $t$，表示数据组数。

接下来每组数据仅包含一行，一个字符串 $s$。

## 输出格式

对于每组数据，输出一行一个非负整数，表示你得到的最长重复子串的长度。

如果这样的子串不存在，输出 `0`。

## 说明/提示

对于 $100 \%$ 的数据，保证 $1 \leq t \leq 10^3, 1 \leq |s| \leq 5 \times 10^3$​。

保证 $\sum |s| \leq 5 \times 10^3$。

Translated by ShiRoZeTsu.

## 样例 #1

### 输入

```
4
zaabaabz
?????
code?????s
codeforces
```

### 输出

```
6
4
10
0
```



---

---
title: "Shuffling Songs"
layout: "post"
diff: 普及+/提高
pid: CF1950G
tag: ['动态规划 DP', '状态合并']
---

# Shuffling Songs

## 题目描述

Vladislav 有一个由 $n$ 首歌组成的播放列表，编号从 $1$ 到 $n$。歌曲 $i$ 属于流派 $g_i$ 并由作者 $w_i$ 创作。他希望以这样一种方式制作播放列表：每对相邻的歌曲要么有相同的作者，要么属于相同的流派（或两者兼有）。他称这样的播放列表为激动人心的。 $g_i$ 和 $w_i$ 都是长度不超过 $10^4$ 的字符串。

但是有可能不总是能使用所有歌曲制作出激动人心的播放列表，因此洗牌过程分为两步。首先，移除一些数量（可能为零）的歌曲，然后重新排列剩余的歌曲使播放列表激动人心。

由于 Vladislav 不喜欢从他的播放列表中移除歌曲，他希望尽可能少地进行移除。帮助他找出为了能重新排列剩余歌曲使播放列表激动人心而需要进行的最少移除数量。

## 输入格式

输入的第一行包含一个整数 $t$（$1 \le t \le 1000$） ——表示多少组数据。

每个测试用例的第一行包含一个单独的整数 $n（1 \le n \le 16）$表示原始播放列表中的歌曲数量。

接着是 $n$ 行，第 $i$ 行包含两个由小写字母组成的字符串 $g_i$ 和 $w_i （1 \leq |g_i|, |w_i| \leq 10^4）$  ——第 $i$ 首歌的流派和作者。其中 $|g_i|$ 和 $|w_i|$ 是字符串的长度。

所有测试用例中 $2^n$ 的总和不超过 $2^{16}$。

所有测试用例中 $|g_i| + |w_i|$ 的总和不超过 $4 \times 10^5$。

## 输出格式

对于每个测试用例，输出一个整数，为使得结果的播放列表可以激动人心所必需的最少移除数量。

## 样例 #1

### 输入

```
4
1
pop taylorswift
4
electronic themotans
electronic carlasdreams
pop themotans
pop irinarimes
7
rap eminem
rap drdre
rap kanyewest
pop taylorswift
indierock arcticmonkeys
indierock arcticmonkeys
punkrock theoffspring
4
a b
c d
e f
g h
```

### 输出

```
0
0
4
3
```



---

---
title: "Colored Balls"
layout: "post"
diff: 普及+/提高
pid: CF1954D
tag: ['动态规划 DP']
---

# Colored Balls

## 题目描述

There are balls of $ n $ different colors; the number of balls of the $ i $ -th color is $ a_i $ .

The balls can be combined into groups. Each group should contain at most $ 2 $ balls, and no more than $ 1 $ ball of each color.

Consider all $ 2^n $ sets of colors. For a set of colors, let's denote its value as the minimum number of groups the balls of those colors can be distributed into. For example, if there are three colors with $ 3 $ , $ 1 $ and $ 7 $ balls respectively, they can be combined into $ 7 $ groups (and not less than $ 7 $ ), so the value of that set of colors is $ 7 $ .

Your task is to calculate the sum of values over all $ 2^n $ possible sets of colors. Since the answer may be too large, print it modulo $ 998\,244\,353 $ .

## 输入格式

The first line contains a single integer $ n $ ( $ 1 \le n \le 5000 $ ) — the number of colors.

The second line contains $ n $ integers $ a_1, a_2, \dots, a_n $ ( $ 1 \le a_i \le 5000 $ ) — the number of balls of the $ i $ -th color.

Additional constraint on input: the total number of balls doesn't exceed $ 5000 $ .

## 输出格式

Print a single integer — the sum of values of all $ 2^n $ sets of colors, taken modulo $ 998\,244\,353 $ .

## 说明/提示

Consider the first example. There are $ 8 $ sets of colors:

- for the empty set, its value is $ 0 $ ;
- for the set $ \{1\} $ , its value is $ 1 $ ;
- for the set $ \{2\} $ , its value is $ 1 $ ;
- for the set $ \{3\} $ , its value is $ 2 $ ;
- for the set $ \{1,2\} $ , its value is $ 1 $ ;
- for the set $ \{1,3\} $ , its value is $ 2 $ ;
- for the set $ \{2,3\} $ , its value is $ 2 $ ;
- for the set $ \{1,2,3\} $ , its value is $ 2 $ .

So, the sum of values over all $ 2^n $ sets of colors is $ 11 $ .

## 样例 #1

### 输入

```
3
1 1 2
```

### 输出

```
11
```

## 样例 #2

### 输入

```
1
5
```

### 输出

```
5
```

## 样例 #3

### 输入

```
4
1 3 3 7
```

### 输出

```
76
```



---

---
title: "Unfair Game"
layout: "post"
diff: 普及+/提高
pid: CF1955F
tag: ['动态规划 DP', '数学']
---

# Unfair Game

## 题目描述

Alice and Bob gathered in the evening to play an exciting game on a sequence of $ n $ integers, each integer of the sequence doesn't exceed $ 4 $ . The rules of the game are too complex to describe, so let's just describe the winning condition — Alice wins if the [bitwise XOR](http://tiny.cc/xor_wiki_eng) of all the numbers in the sequence is non-zero; otherwise, Bob wins.

The guys invited Eve to act as a judge. Initially, Alice and Bob play with $ n $ numbers. After one game, Eve removes one of the numbers from the sequence, then Alice and Bob play with $ n-1 $ numbers. Eve removes one number again, after which Alice and Bob play with $ n - 2 $ numbers. This continues until the sequence of numbers is empty.

Eve seems to think that in such a game, Alice almost always wins, so she wants Bob to win as many times as possible. Determine the maximum number of times Bob can win against Alice if Eve removes the numbers optimally.

## 输入格式

The first line contains an integer $ t $ ( $ 1 \le t \le 10^4 $ ) — the number of test cases.

The first and only line of each test case contains four integers $ p_i $ ( $ 0 \le p_i \le 200 $ ) — the number of ones, twos, threes, and fours in the sequence at the beginning of the game.

## 输出格式

For each test case, print the maximum number of times Bob will win in a separate line, if Eve removes the numbers optimally.

## 说明/提示

In the first example, Bob wins when Eve has not removed any numbers yet.

In the second example, Bob wins if Eve removes one one and one three.

## 样例 #1

### 输入

```
5
1 1 1 0
1 0 1 2
2 2 2 0
3 3 2 0
0 9 9 9
```

### 输出

```
1
1
3
3
12
```



---

---
title: "GCD on a grid"
layout: "post"
diff: 普及+/提高
pid: CF1955G
tag: ['动态规划 DP', '搜索', '数论']
---

# GCD on a grid

## 题目描述

Not long ago, Egor learned about the Euclidean algorithm for finding the greatest common divisor of two numbers. The greatest common divisor of two numbers $ a $ and $ b $ is the largest number that divides both $ a $ and $ b $ without leaving a remainder. With this knowledge, Egor can solve a problem that he once couldn't.

Vasily has a grid with $ n $ rows and $ m $ columns, and the integer $ {a_i}_j $ is located at the intersection of the $ i $ -th row and the $ j $ -th column. Egor wants to go from the top left corner (at the intersection of the first row and the first column) to the bottom right corner (at the intersection of the last row and the last column) and find the greatest common divisor of all the numbers along the path. He is only allowed to move down and to the right. Egor has written down several paths and obtained different GCD values. He became interested in finding the maximum possible GCD.

Unfortunately, Egor is tired of calculating GCDs, so he asks for your help in finding the maximum GCD of the integers along the path from the top left corner to the bottom right corner of the grid.

## 输入格式

The first line contains an integer $ t $ ( $ 1 \le t \le {10}^{4} $ ) — the number of test cases.

The first line of each test case contains two integers $ n $ and $ m $ ( $ 1 \le n, m \le 100 $ ) — the number of rows and columns of the grid.

Then, there are $ n $ lines, where the $ i $ -th line contains $ m $ integers $ (1 \le a_{i,j} \le {10}^{6} $ ) — the integers written in the $ i $ -th row and the $ j $ -th column of the grid.

It is guaranteed that the sum of $ n \cdot m $ does not exceed $ 2 \cdot {10}^{5} $ over all test cases.

## 输出格式

For each test case, output the maximum possible GCD along the path from the top left cell to the bottom right cell in a separate line.

## 样例 #1

### 输入

```
3
2 3
30 20 30
15 25 40
3 3
12 4 9
3 12 2
8 3 12
2 4
2 4 6 8
1 3 6 9
```

### 输出

```
10
3
1
```



---

---
title: "How Does the Rook Move?"
layout: "post"
diff: 普及+/提高
pid: CF1957C
tag: ['动态规划 DP', '组合数学', '排列组合']
---

# How Does the Rook Move?

## 题目描述

你在一个 $n\times n$ 的棋盘上玩一个游戏。

你每次可以选择在 $(r,c)$ 的位置放置一个**白色的车**，使得放置后所有车无法通过水平或垂直的方向攻击到其它车（无论颜色）。如果 $r\not=c$ 则电脑在 $(c,r)$ 处放一个**黑色的车**，可以证明，如果你的操作合法，电脑操作必定合法。

现在你已经放置了 $k$ 个白色的车（显然电脑也已经进行了对应操作），如果你继续放车直到没有合法的位置放车，则游戏结束。

你希望知道游戏结束时形成的局面的可能性。

答案对 $10^9+7$ 取模。

两个局面不同当且仅当某个位置上的车颜色不同或其中一个局面放了车而另一个没有。

## 输入格式

第一行一个整数 $t$，表示数据组数。

接下来对于每组数据，第一行两个整数 $n,k$。

接下来 $k$ 行，每行两个整数 $r_i,c_i$，表示已经放置的白车的位置。

## 输出格式

共 $t$ 行，每行一个整数，表示答案。

## 说明/提示

对于全部数据，满足 $ 1 \leq t \leq 10^4 $，$ 1 \leq n \leq 3 \times 10^5 $ , $ 0 \leq k \leq n $，$\sum n\le3\times10^5$。

## 样例 #1

### 输入

```
3
4 1
1 2
8 1
7 6
1000 4
4 4
952 343
222 333
90 91
```

### 输出

```
3
331
671968183
```



---

---
title: "Minimizing the Sum"
layout: "post"
diff: 普及+/提高
pid: CF1969C
tag: ['动态规划 DP', '区间 DP']
---

# Minimizing the Sum

## 题目描述

You are given an integer array $ a $ of length $ n $ .

You can perform the following operation: choose an element of the array and replace it with any of its neighbor's value.

For example, if $ a=[3, 1, 2] $ , you can get one of the arrays $ [3, 3, 2] $ , $ [3, 2, 2] $ and $ [1, 1, 2] $ using one operation, but not $ [2, 1, 2 $ \] or $ [3, 4, 2] $ .

Your task is to calculate the minimum possible total sum of the array if you can perform the aforementioned operation at most $ k $ times.

## 输入格式

The first line contains a single integer $ t $ ( $ 1 \le t \le 10^4 $ ) — the number of test cases.

The first line of each test case contains two integers $ n $ and $ k $ ( $ 1 \le n \le 3 \cdot 10^5 $ ; $ 0 \le k \le 10 $ ).

The second line contains $ n $ integers $ a_1, a_2, \dots, a_n $ ( $ 1 \le a_i \le 10^9 $ ).

Additional constraint on the input: the sum of $ n $ over all test cases doesn't exceed $ 3 \cdot 10^5 $ .

## 输出格式

For each test case, print a single integer — the minimum possible total sum of the array if you can perform the aforementioned operation at most $ k $ times.

## 说明/提示

In the first example, one of the possible sequences of operations is the following: $ [3, 1, 2] \rightarrow [1, 1, 2 $ \].

In the second example, you do not need to apply the operation.

In the third example, one of the possible sequences of operations is the following: $ [2, 2, 1, 3] \rightarrow [2, 1, 1, 3] \rightarrow [2, 1, 1, 1] $ .

In the fourth example, one of the possible sequences of operations is the following: $ [4, 1, 2, 2, 4, 3] \rightarrow [1, 1, 2, 2, 4, 3] \rightarrow [1, 1, 1, 2, 4, 3] \rightarrow [1, 1, 1, 2, 2, 3] $ .

## 样例 #1

### 输入

```
4
3 1
3 1 2
1 3
5
4 2
2 2 1 3
6 3
4 1 2 2 4 3
```

### 输出

```
4
5
5
10
```



---

---
title: "Trails (Medium)"
layout: "post"
diff: 普及+/提高
pid: CF1970E2
tag: ['动态规划 DP', '矩阵加速']
---

# Trails (Medium)

## 题目描述

Harry Potter is hiking in the Alps surrounding Lake Geneva. In this area there are $ m $ cabins, numbered 1 to $ m $ . Each cabin is connected, with one or more trails, to a central meeting point next to the lake. Each trail is either short or long. Cabin $ i $ is connected with $ s_i $ short trails and $ l_i $ long trails to the lake.

Each day, Harry walks a trail from the cabin where he currently is to Lake Geneva, and then from there he walks a trail to any of the $ m $ cabins (including the one he started in). However, as he has to finish the hike in a day, at least one of the two trails has to be short.

How many possible combinations of trails can Harry take if he starts in cabin 1 and walks for $ n $ days?

Give the answer modulo $ 10^9 + 7 $ .

## 输入格式

The first line contains the integers $ m $ and $ n $ .

The second line contains $ m $ integers, $ s_1, \dots, s_m $ , where $ s_i $ is the number of short trails between cabin $ i $ and Lake Geneva.

The third and last line contains $ m $ integers, $ l_1, \dots, l_m $ , where $ l_i $ is the number of long trails between cabin $ i $ and Lake Geneva.

We have the following constraints:

 $ 0 \le s_i, l_i \le 10^3 $ .

 $ 1 \le m \le 10^2 $ .

 $ 1 \le n \le 10^9 $ .

## 输出格式

The number of possible combinations of trails, modulo $ 10^9 + 7 $ .

## 样例 #1

### 输入

```
3 2
1 0 1
0 1 1
```

### 输出

```
18
```



---

---
title: "Job Interview"
layout: "post"
diff: 普及+/提高
pid: CF1976C
tag: ['动态规划 DP', '贪心']
---

# Job Interview

## 题目描述

### 题意翻译
Monocarp 要开设一家 IT 公司。他想招聘 $n$ 名程序员和 $m$ 名测试员。

共有 $n+m+1$ 名候选人，第 $i$ 个人的到达时间为 $i$。

第 $i$ 名候选人的编程技能为 $a_i$ ，测试技能为 $b_i$ （保证 $a_i\not=b_i$）。

公司的能力定义为所有程序员的编程能力与所有测试员的测试能力之和。

形式化的讲，若招聘的程序员集合为 $s$，测试员集合为 $t$，则公司的能力为 $\sum\limits_{i\in s}a_i+\sum\limits_{j\in t}b_j$。

Monocarp 会按照候选人到达的时间顺序为他们分配工作。

对于第 $i$ 个人，招聘规则为：
1. 尝试将 $i$ 分配到最适合 $i$ 的职位，也就是若 $a_i>b_i$，则让他成为程序员，反之同理。
2. 如果该职位已经招满了，就把 $i$ 分配到另一职位上。

你的任务是，对于每个 $i$，输出若这个人不来的情况下，公司的能力值。

## 输入格式

先是一个数字 $t$ 表示数据组数。

对于每组数据：

先输入两个数字 $n,m$ 表示要招聘的程序员/测试员数量。

接着 $n+m+1$ 个数表示每个人的编程能力。

再是 $n+m+1$ 个数表示每个人的测试能力。

## 输出格式

对于每组数据：输出 $n+m+1$ 个数，第 $i$ 个数表示去掉第 $i$ 个人时公司的能力值。

translate by Hoks。

## 样例 #1

### 输入

```
4
1 0
2 1
1 2
0 2
4 5 5
5 4 1
1 2
2 1 5 4
5 2 3 1
3 1
4 3 3 4 1
5 5 4 5 2
```

### 输出

```
1 2 
5 6 9 
8 11 11 12 
13 13 13 12 15
```



---

---
title: "Nikita and LCM"
layout: "post"
diff: 普及+/提高
pid: CF1977C
tag: ['动态规划 DP', '数论']
---

# Nikita and LCM

## 题目描述

Nikita is a student passionate about number theory and algorithms. He faces an interesting problem related to an array of numbers.

Suppose Nikita has an array of integers $ a $ of length $ n $ . He will call a subsequence $ ^\dagger $ of the array special if its [least common multiple (LCM)](https://en.wikipedia.org/wiki/Least_common_multiple) is not contained in $ a $ . The LCM of an empty subsequence is equal to $ 0 $ .

Nikita wonders: what is the length of the longest special subsequence of $ a $ ? Help him answer this question!

 $ ^\dagger $ A sequence $ b $ is a subsequence of $ a $ if $ b $ can be obtained from $ a $ by the deletion of several (possibly, zero or all) elements, without changing the order of the remaining elements. For example, $ [5,2,3] $ is a subsequence of $ [1,5,7,8,2,4,3] $ .

## 输入格式

Each test contains multiple test cases. The first line of input contains a single integer $ t $ ( $ 1 \le t \le 2000 $ ) — the number of test cases. The description of the test cases follows.

The first line of each test case contains a single integer $ n $ ( $ 1 \le n \le 2000 $ ) — the length of the array $ a $ .

The second line of each test case contains $ n $ integers $ a_1, a_2, \ldots, a_n $ ( $ 1 \le a_i \le 10^9 $ ) — the elements of the array $ a $ .

It is guaranteed that the sum of $ n $ over all test cases does not exceed $ 2000 $ .

## 输出格式

For each test case, output a single integer — the length of the longest special subsequence of $ a $ .

## 说明/提示

In the first test case, the LCM of any non-empty subsequence is contained in $ a $ , so the answer is $ 0 $ .

In the second test case, we can take the subsequence $ [3, 2, 10, 1] $ , its LCM is equal to $ 30 $ , which is not contained in $ a $ .

In the third test case, we can take the subsequence $ [2, 3, 6, 100\,003] $ , its LCM is equal to $ 600\,018 $ , which is not contained in $ a $ .

## 样例 #1

### 输入

```
6
5
1 2 4 8 16
6
3 2 10 20 60 1
7
2 3 4 6 12 100003 1200036
9
2 42 7 3 6 7 7 1 6
8
4 99 57 179 10203 2 11 40812
1
1
```

### 输出

```
0
4
4
5
8
0
```



---

---
title: "Magnitude (Hard Version)"
layout: "post"
diff: 普及+/提高
pid: CF1984C2
tag: ['动态规划 DP', '贪心']
---

# Magnitude (Hard Version)

## 题目描述

**注意：** 本题的两个版本题意是有不同的，你可能需要同时阅读两个版本的题意。

给定一个长度为 $n$ 的数组 $a$。初始有 $c=0$；接下来，对每个在 $1$ 到 $n$ 范围内的 $i$（按递增的顺序） ，要执行以下两种操作中的恰好一种：

- 操作 $1$：将 $c$ 修改为 $c+a_i$。

- 操作 $2$：将 $c$ 修改为 $|c+a_i|$，这里 $|x|$ 表示 $x$ 的绝对值。

令所有操作后 $c$ 能取得的最大值为 $k$，你需要求出有多少种本质不同的方案使得 $c=k$。这里两个方案被视为不同，当且仅当存在一个 $i$ 使得其中一个方案选了操作 $1$ 而另一个选了操作 $2$，即便这步操作后两个方案对应的 $c$ 相等。

由于答案可能很大，请输出答案对 $998244353$ 取模后的结果。

## 输入格式

第一行为一个正整数 $t\;(1\leq t\leq 10^4)$，表示测试数据的组数。

接下来的每组测试数据，第一行为一个正整数 $n\;(1\leq n\leq 2\cdot10^5)$，

第二行为 $n$ 个整数 $a_1,a_2,\cdots,a_n\;(-10^9\leq a_i\leq 10^9)$。

## 输出格式

对每组测试数据，输出一个整数，表示本质不同的方案数对 $998244353$ 取模的结果。

保证所有测试数据的 $n$ 之和不超过 $3\cdot10^5$。

## 样例 #1

### 输入

```
5
4
2 -5 3 -3
8
1 4 3 4 1 4 3 4
3
-1 -2 -3
4
-1000000000 1000000000 1000000000 1000000000
4
1 9 8 4
```

### 输出

```
12
256
1
8
16
```



---

---
title: "World is Mine"
layout: "post"
diff: 普及+/提高
pid: CF1987D
tag: ['动态规划 DP', '背包 DP']
---

# World is Mine

## 题目描述

Alice and Bob are playing a game. Initially, there are $ n $ cakes, with the $ i $ -th cake having a tastiness value of $ a_i $ .

Alice and Bob take turns eating them, with Alice starting first:

- In her turn, Alice chooses and eats any remaining cake whose tastiness is strictly greater than the maximum tastiness of any of the cakes she's eaten before that. Note that on the first turn, she can choose any cake.
- In his turn, Bob chooses any remaining cake and eats it.

The game ends when the current player can't eat a suitable cake. Let $ x $ be the number of cakes that Alice ate. Then, Alice wants to maximize $ x $ , while Bob wants to minimize $ x $ .

Find out how many cakes Alice will eat if both players play optimally.

## 输入格式

Each test contains multiple test cases. The first line of input contains a single integer $ t $ ( $ 1 \le t \le 500 $ ) — the number of test cases. The description of the test cases follows.

The first line of each test case contains a single integer $ n $ ( $ 1 \le n \le 5000 $ ) — the number of cakes.

The second line of each test case contains $ n $ integers $ a_1, a_2, \ldots, a_n $ ( $ 1 \le a_i \le n $ ) — the tastiness values of the cakes.

It is guaranteed that the sum of $ n $ over all test cases does not exceed $ 5000 $ .

## 输出格式

For each test case, output a single integer — the number of cakes Alice will eat if both players play optimally.

## 说明/提示

In the first test case, one possible sequence of turns is:

1. Alice eats a cake with a tastiness value of $ 1 $ . The remaining cakes are $ [4, 2, 3] $ .
2. Bob eats a cake with a tastiness value of $ 2 $ . The remaining cakes are $ [4, 3] $ .
3. Alice eats a cake with a tastiness of $ 3 $ . The remaining cakes are $ [4] $ .
4. Bob eats a cake with a tastiness value of $ 4 $ . The remaining cakes are $ [] $ .
5. Since there are no more cakes left, the game ends.

In the second test case, one possible sequence of turns is:

1. Alice eats a cake with a tastiness value of $ 1 $ . The remaining cakes are $ [1, 1] $ .
2. Bob eats a cake with a tastiness value of $ 1 $ . The remaining cakes are $ [1] $ .
3. Since Alice has already eaten a cake with a tastiness value of $ 1 $ , she cannot make a turn, so the game ends.

## 样例 #1

### 输入

```
9
4
1 4 2 3
3
1 1 1
5
1 4 2 3 4
4
3 4 1 4
1
1
8
4 3 2 5 6 8 3 4
7
6 1 1 3 5 3 1
11
6 11 6 8 7 5 3 11 2 3 5
17
2 6 5 3 9 1 6 2 5 6 3 2 3 9 6 1 6
```

### 输出

```
2
1
3
2
1
3
2
4
4
```



---

---
title: "Smithing Skill"
layout: "post"
diff: 普及+/提高
pid: CF1989D
tag: ['动态规划 DP']
---

# Smithing Skill

## 题目描述

你在玩一款可以运行的著名电脑游戏，游戏中，你有许多能升级的技能。今天，你着重于铸造这个技能。你的策略是显然的：用材料锻造武器，并将其熔毁以返还部分材料。具体地，每次锻造和熔毁都可以提供 $1$ 点经验值。

有 $n$ 种可供锻造的武器，$m$ 种材料。

若要锻造第 $i$ 种武器，需耗费 $a_i$ 个 **同种** 材料，熔毁这把武器则返还 $b_i$ 个 **制作所用的** 材料。

初始你每种材料有 $c_i$ 个，你可以无限次的锻造和熔毁，每把武器均可以用任一种材料。

求你能获得的最大经验值。

## 输入格式

第一行输入整数 $n,m$（$1\le n,m \le 10^6$），为武器种数和材料种数。

第二行输入 $n$ 个数 $a_i$（$1 \le a_i \le 10^6$），为第 $i$ 种武器消耗材料数。

第三行输入 $n$ 个数 $b_i$（$1 \le b_i < a_i$）,为熔毁第 $i$ 种武器返回材料数。

第四行输入 $m$ 个数 $c_i$（$1\le c_i \le 10^9$），表示你最开始拥有 $c_i$ 个材料 $i$。

## 输出格式

一行，为你获得的最大经验值。

### 样例解释

第一个样例中可以按下列方式操作：

1. 用材料 $1$ 锻造武器 $1$。

2. 熔毁武器 $1$.

3. 重复操作 $1,2$ 一次。

4. 用材料 $1$ 锻造并熔毁武器 $3$。

5. 用材料 $3$ 锻造并熔毁武器 $3$。

6. 用材料 $1$ 锻造并熔毁武器 $4$。

7. 用材料 $3$ 锻造并熔毁武器 $5$。

最终 $c = [2,4,2]$，经验值为最大值 $12$。

Translated by uid $408071$.

## 样例 #1

### 输入

```
5 3
9 6 7 5 5
8 4 5 1 2
10 4 7
```

### 输出

```
12
```

## 样例 #2

### 输入

```
3 4
10 20 20
0 0 0
9 10 19 20
```

### 输出

```
8
```

## 样例 #3

### 输入

```
1 5
3
1
1000000000 1000000000 1000000000 1000000000 1000000000
```

### 输出

```
4999999990
```



---

---
title: "Determine Winning Islands in Race"
layout: "post"
diff: 普及+/提高
pid: CF1998D
tag: ['动态规划 DP', '最短路']
---

# Determine Winning Islands in Race

## 题目描述

MOOOOOOOOOOOOOOOOO

— Bessie the Cow, The Art of Racing on Islands



Two of Farmer John's cows, Bessie and Elsie, are planning to race on $ n $ islands. There are $ n - 1 $ main bridges, connecting island $ i $ to island $ i + 1 $ for all $ 1 \leq i \leq n - 1 $ . Additionally, there are $ m $ alternative bridges. Elsie can use both main and alternative bridges, while Bessie can only use main bridges. All bridges are one way and can only be used to travel from an island with a lower index to an island with a higher index.

Initially, Elsie starts on island $ 1 $ , and Bessie starts on island $ s $ . The cows alternate turns, with Bessie making the first turn. Suppose the cow is on island $ i $ . During a cow's turn, if there are any bridges connecting island $ i $ to island $ j $ , then the cow can move to island $ j $ . Then, island $ i $ collapses, and all bridges connecting to island $ i $ also collapse. Also, note the following:

- If there are no bridges connecting island $ i $ to another island, then island $ i $ collapses, and this cow is eliminated from the race.
- If the other cow is also on island $ i $ , then after this cow moves to another island, the island collapses, and the other cow is eliminated from the race.
- After an island or bridge collapses, no cows may use them.
- If a cow is eliminated, their turn is skipped for the rest of the race.

The race ends once either cow reaches island $ n $ . It can be shown that regardless of the cows' strategies, at least one cow reaches island $ n $ . Bessie wins if and only if she reaches island $ n $ first.

For each $ 1 \leq s \leq n - 1 $ , determine whether Bessie wins if she starts the race on island $ s $ . Assume both cows follow optimal strategies to ensure their own respective victories.

## 输入格式

The first line contains $ t $ ( $ 1 \leq t \leq 10^4 $ ) – the number of test cases.

The first line of each test case contains $ n $ and $ m $ ( $ 2 \leq n \leq 2 \cdot 10^5 $ , $ 0 \leq m \leq 2 \cdot 10^5 $ ) – the number of islands and the number of alternative bridges.

The next $ m $ lines of each test case contain $ u $ and $ v $ ( $ 1 \leq u < v \leq n $ ) – the islands that the alternative bridge connects. It is guaranteed all alternative bridges are distinct, and they do not coincide with the main bridges.

It is guaranteed that neither the sum of $ n $ nor the sum of $ m $ over all test cases exceeds $ 2 \cdot 10^5 $ .

## 输出格式

For each test case, output a binary string of length $ n - 1 $ on a new line. The $ i $ 'th character is $ 1 $ if it is possible for Bessie to win if she starts on island $ i $ . Otherwise, it is $ 0 $ .

## 说明/提示

In the first test case, there are no alternative bridges for Elsie to overtake Bessie and reach island $ n $ first, so Bessie will win on all islands because she always moves first.

In the second case, Bessie will lose if she starts on island $ 3 $ because:

- Bessie's Turn: Take a main bridge from island $ 3 $ to island $ 4 $ .
- Elsie's Turn: Take a main bridge from island $ 1 $ to island $ 2 $ .
- Bessie's Turn: Take a main bridge from island $ 4 $ to island $ 5 $ .
- Elsie's Turn: Take an alternative bridge from island $ 2 $ to island $ 6 $ . Elsie reaches island $ n $ first.

## 样例 #1

### 输入

```
5
6 0
6 1
2 6
6 1
1 5
10 4
1 3
1 6
2 7
3 8
15 3
2 8
4 9
8 15
```

### 输出

```
11111
11011
10011
100001111
11000111000111
```



---

---
title: "Color Rows and Columns"
layout: "post"
diff: 普及+/提高
pid: CF2000F
tag: ['动态规划 DP']
---

# Color Rows and Columns

## 题目描述

你有 $n$ 个矩形，第 $i$ 个矩形的宽度为 $a_i$，高度为 $b_i$。

你可以无限次地执行这个操作：

选择其中的一个矩形并为其矩形内的一个单元格着色。

当每次有任意一个矩形内的一行或一列被完全着色，你都可以获得 $1$ 分。你的任务是去用尽量少的操作次数来获得至少 $k$ 的得分

假设有一个宽度为 $6$，高度为 $3$ 的矩形，你可以对矩形中的任意四列着色，从而使用 $12$ 次操作，获得 $4$ 分

## 输入格式

第一行是一个整数 $t$，表示一共有 $t$ 组数据。

每个测试用例的第一行是两个整数 $n$ 和 $k$，表示共有 $n$ 个矩形，$k$ 的意思同上文所说。

接下来的 $n$ 行包含对矩形的描述，第 $i$ 行是两个整数 $a_i$ 和 $b_i$，表示一个矩形的宽和高。

对于 $100\%$ 的数据，保证 $\sum n \le 1000$。

## 输出格式

对于每个测试用例，输出一个整数表示要获得至少 $k$ 分所需要的最小操作次数。如果无论如何都无法获得 $k$ 分，请输出 $-1$。

## 样例 #1

### 输入

```
7
1 4
6 3
1 5
4 4
5 10
1 1
1 1
1 1
1 1
1 1
2 100
1 2
5 6
3 11
2 2
3 3
4 4
3 25
9 2
4 3
8 10
4 18
5 4
8 5
8 3
6 2
```

### 输出

```
12
14
5
-1
17
80
35
```



---

---
title: "Turtle and a MEX Problem (Hard Version)"
layout: "post"
diff: 普及+/提高
pid: CF2003D2
tag: ['动态规划 DP', '贪心']
---

# Turtle and a MEX Problem (Hard Version)

## 题目描述

两个版本的问题是不同的。在这个版本的问题中，你不能选择同一个整数两次或更多次。只有当两个版本都解决时，才能进行 hack。

有一天，乌龟正在玩 $n$ 个序列。设第 $i$ 个序列的长度为 $l_i$，则第 $i$ 个序列为 $a_{i, 1}, a_{i, 2}, \ldots, a_{i, l_i}$。

当乌龟在玩耍时，小猪给了他一个问题来解决。问题的陈述如下：

- 最初有一个非负整数 $x$。乌龟可以对这个整数执行任意次数（可能为零）的操作。
- 在每次操作中，乌龟可以选择一个之前未被选择过的整数 $i$（满足 $1 \le i \le n$），并将 $x$ 设为 $\text{mex}^{\dagger}(x, a_{i, 1}, a_{i, 2}, \ldots, a_{i, l_i})$。
- 乌龟被要求找到答案，即在执行任意次数操作后 $x$ 的最大值。

乌龟轻松解决了上述问题。他定义 $f(k)$ 为初始值 $x$ 为 $k$ 时上述问题的答案。

然后小猪给了乌龟一个非负整数 $m$，并要求乌龟找出 $\sum\limits_{i = 0}^m f(i)$ 的值（即 $f(0) + f(1) + \ldots + f(m)$ 的值）。不幸的是，他无法解决这个问题。请帮助他！

$\text{mex}(c_1, c_2, \ldots, c_k)$ 定义为不在序列 $c$ 中出现的最小非负整数 $x$。例如，$\text{mex}(2, 2, 0, 3)$ 是 $1$，$\text{mex}(1, 2)$ 是 $0$。

## 输入格式

每个测试包含多个测试用例。第一行包含测试用例的数量 $t$（$1 \le t \le 10^4$）。接下来是测试用例的描述。

每个测试用例的第一行包含两个整数 $n, m$（$1 \le n \le 2 \cdot 10^5, 0 \le m \le 10^9$）。

接下来的 $n$ 行每行包含若干个整数。第一个整数 $l_i$（$1 \le l_i \le 2 \cdot 10^5$）表示第 $i$ 个序列的长度，后面跟着 $l_i$ 个整数 $a_{i, 1}, a_{i, 2}, \ldots, a_{i, l_i}$（$0 \le a_{i, j} \le 10^9$）表示第 $i$ 个序列的元素。

保证所有测试用例中的 $n$ 之和不超过 $2 \cdot 10^5$，并且所有测试用例中的 $\sum l_i$ 之和不超过 $2 \cdot 10^5$。

## 输出格式

对于每个测试用例，输出一个整数 —— $\sum\limits_{i = 0}^m f(i)$ 的值。

## 说明/提示

在第一个测试用例中，当 $x$ 初始值为 $2$ 时，乌龟可以选择 $i = 3$ 并将 $x$ 设为 $\text{mex}(x, a_{3, 1}, a_{3, 2}, a_{3, 3}, a_{3, 4}) = \text{mex}(2, 7, 0, 1, 5) = 3$。可以证明乌龟无法使 $x$ 的值大于 $3$，因此 $f(2) = 3$。

可以看出 $f(0) = 3$，$f(1) = 3$，$f(2) = 3$，$f(3) = 3$，$f(4) = 4$。所以 $f(0) + f(1) + f(2) + f(3) + f(4) = 3 + 3 + 3 + 3 + 4 = 16$。

在第二个测试用例中，当 $x$ 初始值为 $1$ 时，乌龟可以选择 $i = 1$ 并将 $x$ 设为 $\text{mex}(x, a_{1, 1}, a_{1, 2}, a_{1, 3}, a_{1, 4}, a_{1, 5}) = \text{mex}(1, 0, 2, 0, 4, 11) = 3$。可以证明乌龟无法使 $x$ 的值大于 $3$，因此 $f(1) = 3$。

可以看出 $f(0) = 4$，$f(1) = 3$，$f(2) = 4$，$f(3) = 3$，$f(4) = 4$。所以 $f(0) + f(1) + f(2) + f(3) + f(4) = 4 + 3 + 4 + 3 + 4 = 18$。

在第四个测试用例中，可以看出 $f(0) = 3$ 和 $f(1) = 1$。所以 $f(0) + f(1) = 3 + 1 = 4$。

## 样例 #1

### 输入

```
6
3 4
2 0 2
3 2 3 3
4 7 0 1 5
3 4
5 0 2 0 4 11
1 1
5 1 3 0 3 3
2 50
2 1 2
2 1 2
1 1
7 1 2 4 1 4 9 5
4 114514
2 2 2
5 7 3 6 0 3
3 0 1 1
5 0 9 2 1 5
5 1919810
1 2
2 324003 0
3 1416324 2 1460728
4 1312631 2 0 1415195
5 1223554 192248 2 1492515 725556
```

### 输出

```
16
18
1281
4
6556785365
1842836177961
```



---

---
title: "Lazy Narek"
layout: "post"
diff: 普及+/提高
pid: CF2005C
tag: ['动态规划 DP']
---

# Lazy Narek

## 题目描述

$\text{Alice}$ 有 $n$ 个字符串，每个字符串长度为 $m$。

$\text{Alice}$ 会选择 $n$ 个字符串的一个子集，可以为空，将子集中的字符串首尾按原本的相对顺序拼接，然后她会在拼接的字符串中依次查找字符 "n","a","r","e","k"。当这五个字符全被找到后，$\text{Alice}$ 会将自己的分数 $+5$ 然后继续从当前位置向后查找。

之后 $\text{Bob}$ 会扫描整个字符串并查找，如果 $\text{Alice}$ 的查找中有未被访问的 "n","a","r","e" 或 "k"，$\text{Bob}$ 会将自己的分数 $+1$。

请你帮 $\text{Alice}$ 和 $\text{Bob}$ 求出 $\max\{score_{Alice} - score_{Bob}\}$。

## 输入格式

多组测试数据，第一行一个正整数 $T(1 \leq T \leq 10^5)$，表示数据组数。

接下来每个测试数据的第一行两个正整数 $n,m(1 \leq n,m \leq 10^3)$，表示字符串的数量以及每个字符串的长度。

接下来 $n$ 行，每行一个长度为 $m$ 的字符串，意义如题意所述，仅包含小写字母。

$\sum{n \cdot m} \leq 10^6$

## 输出格式

对于每个测试数据，输出一个整数：$score_{Alice} - score_{Bob}$ 的最大值

## 样例 #1

### 输入

```
4
5 2
nn
aa
rr
ee
kk
1 5
narek
1 4
nare
5 7
nrrarek
nrnekan
uuuuuuu
ppppppp
nkarekz
```

### 输出

```
0
5
0
7
```



---

---
title: "Subtangle Game (Easy Version)"
layout: "post"
diff: 普及+/提高
pid: CF2005E1
tag: ['动态规划 DP']
---

# Subtangle Game (Easy Version)

## 题目描述

这是问题的简单版本。两个版本的区别在于所有变量的约束。只有当两个版本的问题都解决时，才能进行 Hack。

Tsovak 和 Narek 正在玩一个游戏。他们有一个整数数组 $a$ 和一个整数矩阵 $b$，矩阵有 $n$ 行 $m$ 列，行列编号从 1 开始。矩阵中第 $i$ 行第 $j$ 列的单元格为 $ (i, j) $。

他们轮流在矩阵中寻找数组 $a$ 的元素；Tsovak 先开始。每次轮到玩家时，玩家需要在矩阵中寻找当前数组 $a$ 中的元素（Tsovak 寻找第一个，Narek 寻找第二个，依此类推）。假设某个玩家选择了单元格 $ (r, c) $。下一个玩家必须在从 $ (r + 1, c + 1) $ 开始、以 $ (n, m) $ 结束的子矩阵中选择他的单元格（如果 $r = n$ 或 $c = m$，子矩阵可能为空）。如果某个玩家无法在这样的子矩阵中找到相应的单元格（或者剩余的子矩阵为空），或者数组已经结束（前一个玩家已经找到了最后一个元素），那么他就输了。

你的任务是确定如果两位玩家都进行最优策略时，谁会获胜。

## 输入格式

输入的第一行包含一个整数 $ t $ ( $ 1 \le t \le 300 $ ) —— 测试用例的数量。

每个测试用例的第一行包含三个整数 $ l $ 、$ n $ 和 $ m $ ( $ 1 \le l, n, m \le 300 $ ) —— 数组的大小以及矩阵的行数和列数。

第二行包含 $ l $ 个整数 $ a_1, a_2, a_3, \ldots a_l $ ( $ 1 \le a_i \le \min(7, n \cdot m) $ ) —— 数组 $ a $ 的元素。

接下来的 $ n $ 行中，每一行包含 $ m $ 个整数 $ b_{i,1}, b_{i,2}, b_{i,3}, \ldots b_{i,m} $ ( $ 1 \le b_{i,j} \le \min(7, n \cdot m) $ ) —— 表示矩阵的第 $ i $ 行。

保证所有测试用例中 $ n \cdot m $ 的总和不超过 $ 10^5 $ 。

保证所有测试用例中 $ l $ 的总和不超过 $ 300 $ 。

## 输出格式

输出 $ t $ 行，每行对应一个测试用例的答案，若 Tsovak 获胜则输出 "T"，否则输出 "N"（不带引号）。

## 说明/提示

在第一个例子中，Tsovak 首先寻找 $ 1 $ 。矩阵中 $ 1 $ 只出现在 $ (1,1) $，所以他选择该位置。接着，Narek 需要在子矩阵 $ (2, 2) $ 中寻找 $ 2 $，该子矩阵只包含最后两个元素：$ 5 $ 和 $ 2 $。他选择 $ 2 $，随后 Tsovak 输了，因为数组已经结束。

在第二个例子中，Tsovak 需要选择 $ 1 $ 。$ 1 $ 出现在矩阵的最后一个单元格 $ (n,m) $，他选择了该单元格。由于子矩阵 $ (n+1, m+1) $ 为空，Narek 无法找到 $ 2 $，所以他输了。

Translate by 宋怡芃

## 样例 #1

### 输入

```
3
2 2 3
1 2
1 3 5
4 5 2
2 2 4
1 2
1 1 3 2
4 2 5 1
2 4 2
1 2
3 4
5 5
5 5
5 5
```

### 输出

```
N
T
N
```



---

---
title: "Fragile Bridges"
layout: "post"
diff: 普及+/提高
pid: CF201C
tag: ['动态规划 DP', '枚举', '前缀和']
---

# Fragile Bridges

## 题目描述

You are playing a video game and you have just reached the bonus level, where the only possible goal is to score as many points as possible. Being a perfectionist, you've decided that you won't leave this level until you've gained the maximum possible number of points there.

The bonus level consists of $ n $ small platforms placed in a line and numbered from $ 1 $ to $ n $ from left to right and ( $ n-1 $ ) bridges connecting adjacent platforms. The bridges between the platforms are very fragile, and for each bridge the number of times one can pass this bridge from one of its ends to the other before it collapses forever is known in advance.

The player's actions are as follows. First, he selects one of the platforms to be the starting position for his hero. After that the player can freely move the hero across the platforms moving by the undestroyed bridges. As soon as the hero finds himself on a platform with no undestroyed bridge attached to it, the level is automatically ended. The number of points scored by the player at the end of the level is calculated as the number of transitions made by the hero between the platforms. Note that if the hero started moving by a certain bridge, he has to continue moving in the same direction until he is on a platform.

Find how many points you need to score to be sure that nobody will beat your record, and move to the next level with a quiet heart.

## 输入格式

The first line contains a single integer $ n $ ( $ 2<=n<=10^{5} $ ) — the number of platforms on the bonus level. The second line contains ( $ n-1 $ ) integers $ a_{i} $ ( $ 1<=a_{i}<=10^{9} $ , $ 1<=i&lt;n $ ) — the number of transitions from one end to the other that the bridge between platforms $ i $ and $ i+1 $ can bear.

## 输出格式

Print a single integer — the maximum number of points a player can get on the bonus level.

Please, do not use the %lld specifier to read or write 64-bit integers in С++. It is preferred to use the cin, cout streams or the %I64d specifier.

## 说明/提示

One possibility of getting $ 5 $ points in the sample is starting from platform $ 3 $ and consequently moving to platforms $ 4 $ , $ 3 $ , $ 2 $ , $ 1 $ and $ 2 $ . After that the only undestroyed bridge is the bridge between platforms $ 4 $ and $ 5 $ , but this bridge is too far from platform $ 2 $ where the hero is located now.

## 样例 #1

### 输入

```
5
2 1 2 1

```

### 输出

```
5

```



---

---
title: "Expected Power"
layout: "post"
diff: 普及+/提高
pid: CF2020E
tag: ['动态规划 DP', '期望']
---

# Expected Power

## 题目描述

You are given an array of $ n $ integers $ a_1,a_2,\ldots,a_n $ . You are also given an array $ p_1, p_2, \ldots, p_n $ .

Let $ S $ denote the random multiset (i. e., it may contain equal elements) constructed as follows:

- Initially, $ S $ is empty.
- For each $ i $ from $ 1 $ to $ n $ , insert $ a_i $ into $ S $ with probability $ \frac{p_i}{10^4} $ . Note that each element is inserted independently.

Denote $ f(S) $ as the [bitwise XOR](https://en.wikipedia.org/wiki/Bitwise_operation#XOR) of all elements of $ S $ . Please calculate the expected value of $ (f(S))^2 $ . Output the answer modulo $ 10^9 + 7 $ .

Formally, let $ M = 10^9 + 7 $ . It can be shown that the answer can be expressed as an irreducible fraction $ \frac{p}{q} $ , where $ p $ and $ q $ are integers and $ q \not \equiv 0 \pmod{M} $ . Output the integer equal to $ p \cdot q^{-1} \bmod M $ . In other words, output such an integer $ x $ that $ 0 \le x < M $ and $ x \cdot q \equiv p \pmod{M} $ .

## 输入格式

Each test contains multiple test cases. The first line contains the number of test cases $ t $ ( $ 1 \le t \le 10^4 $ ). The description of the test cases follows.

The first line of each test case contains a single integer $ n $ ( $ 1 \le n \le 2 \cdot 10^5 $ ).

The second line of each test case contains $ n $ integers $ a_1,a_2,\ldots,a_n $ ( $ 1 \le a_i \le 1023 $ ).

The third line of each test case contains $ n $ integers $ p_1,p_2,\ldots,p_n $ ( $ 1 \le p_i \le 10^4 $ ).

It is guaranteed that the sum of $ n $ over all test cases does not exceed $ 2 \cdot 10^5 $ .

## 输出格式

For each test case, output the expected value of $ (f(S))^2 $ , modulo $ 10^9 + 7 $ .

## 说明/提示

In the first test case, $ a = [1, 2] $ and each element is inserted into $ S $ with probability $ \frac{1}{2} $ , since $ p_1 = p_2 = 5000 $ and $ \frac{p_i}{10^4} = \frac{1}{2} $ . Thus, there are $ 4 $ outcomes for $ S $ , each happening with the same probability of $ \frac{1}{4} $ :

- $ S = \varnothing $ . In this case, $ f(S) = 0 $ , $ (f(S))^2 = 0 $ .
- $ S = \{1\} $ . In this case, $ f(S) = 1 $ , $ (f(S))^2 = 1 $ .
- $ S = \{2\} $ . In this case, $ f(S) = 2 $ , $ (f(S))^2 = 4 $ .
- $ S = \{1,2\} $ . In this case, $ f(S) = 1 \oplus 2 = 3 $ , $ (f(S))^2 = 9 $ .

Hence, the answer is $ 0 \cdot \frac{1}{4} + 1 \cdot \frac{1}{4} + 4\cdot \frac{1}{4} + 9 \cdot \frac{1}{4} = \frac{14}{4} = \frac{7}{2} \equiv 500\,000\,007 \pmod{10^9 + 7} $ .

In the second test case, $ a = [1, 1] $ , $ a_1 $ is inserted into $ S $ with probability $ 0.1 $ , while $ a_2 $ is inserted into $ S $ with probability $ 0.2 $ . There are $ 3 $ outcomes for $ S $ :

- $ S = \varnothing $ . In this case, $ f(S) = 0 $ , $ (f(S))^2 = 0 $ . This happens with probability $ (1-0.1) \cdot (1-0.2) = 0.72 $ .
- $ S = \{1\} $ . In this case, $ f(S) = 1 $ , $ (f(S))^2 = 1 $ . This happens with probability $ (1-0.1) \cdot 0.2 + 0.1 \cdot (1-0.2) = 0.26 $ .
- $ S = \{1, 1\} $ . In this case, $ f(S) = 0 $ , $ (f(S))^2 = 0 $ . This happens with probability $ 0.1 \cdot 0.2 = 0.02 $ .

Hence, the answer is $ 0 \cdot 0.72 + 1 \cdot 0.26 + 0 \cdot 0.02 = 0.26 = \frac{26}{100} \equiv 820\,000\,006 \pmod{10^9 + 7} $ .

## 样例 #1

### 输入

```
4
2
1 2
5000 5000
2
1 1
1000 2000
6
343 624 675 451 902 820
6536 5326 7648 2165 9430 5428
1
1
10000
```

### 输出

```
500000007
820000006
280120536
1
```



---

---
title: "Gerrymandering"
layout: "post"
diff: 普及+/提高
pid: CF2022C
tag: ['动态规划 DP', '分类讨论']
---

# Gerrymandering

## 题目描述

We all steal a little bit. But I have only one hand, while my adversaries have two.

Álvaro Obregón



Álvaro and José are the only candidates running for the presidency of Tepito, a rectangular grid of $ 2 $ rows and $ n $ columns, where each cell represents a house. It is guaranteed that $ n $ is a multiple of $ 3 $ .

Under the voting system of Tepito, the grid will be split into districts, which consist of any $ 3 $ houses that are connected $ ^{\text{∗}} $ . Each house will belong to exactly one district.

Each district will cast a single vote. The district will vote for Álvaro or José respectively if at least $ 2 $ houses in that district select them. Therefore, a total of $ \frac{2n}{3} $ votes will be cast.

As Álvaro is the current president, he knows exactly which candidate each house will select. If Álvaro divides the houses into districts optimally, determine the maximum number of votes he can get.

 $ ^{\text{∗}} $ A set of cells is connected if there is a path between any $ 2 $ cells that requires moving only up, down, left and right through cells in the set.

## 输入格式

Each test contains multiple test cases. The first line contains the number of test cases $ t $ ( $ 1 \le t \le 10^4 $ ). The description of the test cases follows.

The first line of each test case contains one integer $ n $ ( $ 3 \le n \le 10^5 $ ; $ n $ is a multiple of $ 3 $ ) — the number of columns of Tepito.

The following two lines each contain a string of length $ n $ . The $ i $ -th line contains the string $ s_i $ , consisting of the characters $ \texttt{A} $ and $ \texttt{J} $ . If $ s_{i,j}=\texttt{A} $ , the house in the $ i $ -th row and $ j $ -th column will select Álvaro. Otherwise if $ s_{i,j}=\texttt{J} $ , the house will select José.

It is guaranteed that the sum of $ n $ over all test cases does not exceed $ 10^5 $ .

## 输出格式

For each test case, output a single integer — the maximum number of districts Álvaro can win by optimally dividing the houses into districts.

## 说明/提示

The image below showcases the optimal arrangement of districts Álvaro can use for each test case in the example.

 ![](https://cdn.luogu.com.cn/upload/vjudge_pic/CF2022C/df820ffc2e1ad6e016254b57c0ce9fb7f735735d.png)

## 样例 #1

### 输入

```
4
3
AAA
AJJ
6
JAJAJJ
JJAJAJ
6
AJJJAJ
AJJAAA
9
AJJJJAJAJ
JAAJJJJJA
```

### 输出

```
2
2
3
2
```



---

---
title: "Skipping"
layout: "post"
diff: 普及+/提高
pid: CF2023B
tag: ['动态规划 DP', '图论', '线段树', '最短路']
---

# Skipping

## 题目描述

现在已经是3024年了，出题的想法早就枯竭。现今的OI以一种修改后的个人参赛形式进行。比赛有$n$道题，编号从$1$到$n$，一道题有一个分数$a_i$和一个参数$b_i$。最开始，评测系统会把第$1$道题丢给选手。当一个选手拿到第$i$道题，他有两个选择：

- 提交，获得$a_i$分
- 跳过，但他再不能去交这道题了。

接下来，评测系统会把编号最大的符合下述条件的题目$j$丢给选手：

- 如果选手提交了$i$题，那么$j<i$
- 如果选手选择跳过，那么$j\leq b_i$

系统不能给选手一道之前给过的题目。如果系统找不到这样的题，那么比赛结束。特别的，如果选手提交第一题，比赛结束。

请你帮助小p拿到最高的可能得分。

## 输入格式

此题**多测**，第一行一个整数$t(1\leq t\leq 10^5$，为测试数据组数。每组数据如下：

第一行一个整数$n(1\leq n\leq 4\cdot10^5)$，表示题目数量

第二行一行$n$个整数$a_1,a_2……a_n(1\leq a_i\leq 10^9)$表示题目分数。

第三行一行$n$个整数$b_1,b_2……b_n(1\leq b_i\leq n)$表示题目参数。

保证所有测试数据的$\sum n$不超过$4\cdot 10^5$。

## 输出格式

每行输出一个整数，为小p最大的可能得分。

## 样例 #1

### 输入

```
4
2
15 16
2 1
5
10 10 100 100 1000
3 4 1 1 1
3
100 49 50
3 2 2
4
100 200 300 1000
2 3 4 1
```

### 输出

```
16
200
100
1000
```



---

---
title: "Attribute Checks"
layout: "post"
diff: 普及+/提高
pid: CF2025D
tag: ['动态规划 DP']
---

# Attribute Checks

## 题目描述

Imagine a game where you play as a character that has two attributes: "Strength" and "Intelligence", that are at zero level initially.

During the game, you'll acquire $ m $ attribute points that allow you to increase your attribute levels — one point will increase one of the attributes by one level. But sometimes, you'll encounter a so-called "Attribute Checks": if your corresponding attribute is high enough, you'll pass it; otherwise, you'll fail it.

Spending some time, you finally prepared a list which contains records of all points you got and all checks you've met. And now you're wondering: what is the maximum number of attribute checks you can pass in a single run if you'd spend points wisely?

Note that you can't change the order of records.

## 输入格式

The first line contains two integers $ n $ and $ m $ ( $ 1 \le m \le 5000 $ ; $ m < n \le 2 \cdot 10^6 $ ) — the number of records in the list and the total number of points you'll get during the game.

The second line contains $ n $ integers $ r_1, r_2, \dots, r_n $ ( $ -m \le r_i \le m $ ), where $ r_i $ encodes the $ i $ -th record:

- If $ r_i = 0 $ , then the $ i $ -th record is an acquiring one attribute point. You can spend to level up either Strength or Intelligence;
- If $ r_i > 0 $ , then it's an Intelligence check: if your Intelligence level is greater than or equal to $ |r_i| $ , you pass.
- If $ r_i < 0 $ , then it's a Strength check: if your Strength level is greater than or equal to $ |r_i| $ , you pass.

Additional constraint on the input: the sequence $ r_1, r_2, \dots, r_n $ contains exactly $ m $ elements equal to $ 0 $ .

## 输出格式

Print one integer — the maximum number of checks you can pass.

## 说明/提示

In the first test, it's optimal to spend each point in Strength, so you'll fail $ 2 $ Intelligence checks but pass $ 3 $ Strength checks.

In the second test, you'll fail both checks, since the first point you get comes after the checks.

In the third test, one of the optimal strategies is:

1. spend the first point on Intelligence;
2. spend the second point on Strength;
3. spend the third point on Strength;

 As a result, you'll pass $ 2 $ Intelligence checks $ r_3 $ and $ r_9 $ and $ 2 $ Strength checks $ r_7 $ and $ r_8 $ .

## 样例 #1

### 输入

```
10 5
0 1 0 2 0 -3 0 -4 0 -5
```

### 输出

```
3
```

## 样例 #2

### 输入

```
3 1
1 -1 0
```

### 输出

```
0
```

## 样例 #3

### 输入

```
9 3
0 0 1 0 2 -3 -2 -2 1
```

### 输出

```
4
```



---

---
title: "The Endspeaker (Easy Version)"
layout: "post"
diff: 普及+/提高
pid: CF2027D1
tag: ['动态规划 DP', '二分']
---

# The Endspeaker (Easy Version)

## 题目描述

This is the easy version of this problem. The only difference is that you only need to output the minimum total cost of operations in this version. You must solve both versions to be able to hack.

You're given an array $ a $ of length $ n $ , and an array $ b $ of length $ m $ ( $ b_i > b_{i+1} $ for all $ 1 \le i < m $ ). Initially, the value of $ k $ is $ 1 $ . Your aim is to make the array $ a $ empty by performing one of these two operations repeatedly:

- Type $ 1 $ — If the value of $ k $ is less than $ m $ and the array $ a $ is not empty, you can increase the value of $ k $ by $ 1 $ . This does not incur any cost.
- Type $ 2 $ — You remove a non-empty prefix of array $ a $ , such that its sum does not exceed $ b_k $ . This incurs a cost of $ m - k $ .

You need to minimize the total cost of the operations to make array $ a $ empty. If it's impossible to do this through any sequence of operations, output $ -1 $ . Otherwise, output the minimum total cost of the operations.

## 输入格式

Each test contains multiple test cases. The first line contains the number of test cases $ t $ ( $ 1 \le t \le 1000 $ ). The description of the test cases follows.

The first line of each test case contains two integers $ n $ and $ m $ ( $ 1 \le n, m \le 3 \cdot 10^5 $ , $ \boldsymbol{1 \le n \cdot m \le 3 \cdot 10^5} $ ).

The second line of each test case contains $ n $ integers $ a_1, a_2, \ldots, a_n $ ( $ 1 \le a_i \le 10^9 $ ).

The third line of each test case contains $ m $ integers $ b_1, b_2, \ldots, b_m $ ( $ 1 \le b_i \le 10^9 $ ).

It is also guaranteed that $ b_i > b_{i+1} $ for all $ 1 \le i < m $ .

It is guaranteed that the sum of $ \boldsymbol{n \cdot m} $ over all test cases does not exceed $ 3 \cdot 10^5 $ .

## 输出格式

For each test case, if it's possible to make $ a $ empty, then output the minimum total cost of the operations.

If there is no possible sequence of operations which makes $ a $ empty, then output a single integer $ -1 $ .

## 说明/提示

In the first test case, one optimal sequence of operations which yields a total cost of $ 1 $ is as follows:

- Perform an operation of type $ 2 $ . Choose the prefix to be $ [9] $ . This incurs a cost of $ 1 $ .
- Perform an operation of type $ 1 $ . The value of $ k $ is now $ 2 $ . This incurs no cost.
- Perform an operation of type $ 2 $ . Choose the prefix to be $ [3, 4] $ . This incurs a cost of $ 0 $ .
- Perform an operation of type $ 2 $ . Choose the prefix to be $ [3] $ . This incurs a cost of $ 0 $ .
- The array $ a $ is now empty, and the total cost of all operations is $ 1 $ .

In the second test case, it's impossible to remove any prefix of the array since $ a_1 > b_1 $ , so array $ a $ cannot be made empty by any sequence of operations.

## 样例 #1

### 输入

```
5
4 2
9 3 4 3
11 7
1 2
20
19 18
10 2
2 5 2 1 10 3 2 9 9 6
17 9
10 11
2 2 2 2 2 2 2 2 2 2
20 18 16 14 12 10 8 6 4 2 1
1 6
10
32 16 8 4 2 1
```

### 输出

```
1
-1
2
10
4
```



---

---
title: "Alice's Adventures in Cards"
layout: "post"
diff: 普及+/提高
pid: CF2028D
tag: ['动态规划 DP', '树状数组', '最短路']
---

# Alice's Adventures in Cards

## 题目描述

Alice 正在和红心皇后、红心国王以及红心杰克玩纸牌游戏。这个游戏中有 $ n $ 种不同的纸牌类型。Alice 手上现在有一张类型为 $ 1 $ 的纸牌，她需要通过一系列的交换，得到类型为 $ n $ 的纸牌，才能逃出仙境。而其他三名玩家手上各自持有每种类型的纸牌一张。

在这个游戏中，Alice 可以与这些玩家进行纸牌交换。每位玩家对不同类型纸牌的偏好用排列 $ q $、$ k $ 和 $ j $ 来表示，分别对应红心皇后、红心国王和红心杰克。

对于任意玩家，如果在他们的排列 $ p $ 中，满足 $ p_a > p_b $ ，那么该玩家就认为类型为 $ a $ 的纸牌比类型为 $ b $ 的更有价值。于是，他们愿意用类型为 $ b $ 的纸牌换取类型为 $ a $ 的纸牌。而 Alice 的偏好简单直观：纸牌类型 $ a $ 比类型 $ b $ 更有价值，当且仅当 $ a > b $ ，并且她只会按照这种偏好进行交换。

请判断 Alice 能否通过与其他玩家的交换，从类型为 $ 1 $ 的纸牌升级到类型为 $ n $ 的纸牌。如果可以，请给出可能的交换方案。

$ ^{\text{∗}} $ 长度为 $ n $ 的排列是一个包含 $ n $ 个不同整数（从 $ 1 $ 到 $ n $）的数组。例如，$ [2,3,1,5,4] $ 是一个排列，但 $ [1,2,2] $ 和 $ [1,3,4] $ 则不是。

## 输入格式

输入包含多个测试用例。第一行给出测试用例的数量 $ t $ （$ 1 \le t \le 10^4 $）。随后是每个测试用例的详细描述。

对于每个测试用例，首先提供一个整数 $ n $ （$ 2 \le n \le 2 \cdot 10^5 $），代表纸牌类型的数量。

接下来的三行分别是红心皇后、红心国王和红心杰克对纸牌的偏好排列。每行包括 $ n $ 个整数 $ p_1, p_2, \ldots, p_n $ （$ 1 \le p_i \le n $），表示每个玩家对纸牌的偏好顺序。

所有测试用例中 $ n $ 的总和不超过 $ 2 \cdot 10^5 $。

## 输出格式

对于每个测试用例，输出一行，写上 "YES" 或 "NO" 来表示 Alice 是否能通过交换得到类型为 $ n $ 的纸牌。

如果可以输出 "YES"，接下来一行输出一个整数 $ k $ ，表示 Alice 将进行的交换次数。随后的 $ k $ 行，每行描述一次交换，以一个字符 $ c \in \{\texttt{q}, \texttt{k}, \texttt{j}\} $ 和一个整数 $ x $ 的形式出现，表示 Alice 与玩家 $ c $ 进行交换，以获得类型为 $ x $ 的纸牌。最终必须确保在第 $ k $ 次交换后，得到的纸牌为类型 $ n $。如果存在多种解决方案，输出任意一个即可。

输出中的字母大小写不固定。例如，"yEs"、"yes"、"Yes" 和 "YES" 都被视为肯定回答。同样，代表玩家的字符 $ c $ 也可以使用大写形式（$\texttt{Q}$、$\texttt{K}$、$\texttt{J}$）。

## 说明/提示

在第一个测试用例中，Alice 可以与红心国王交换以获得类型为 $ 2 $ 的纸牌，接着再与红心皇后交换以得到类型为 $ 3 $ 的纸牌。

在第二个测试用例中，尽管 Alice 能与红心皇后交换得到类型为 $ 3 $ 的纸牌，再接着与红心国王交换得到类型为 $ 2 $，最后与红心杰克交换得到类型为 $ 4 $ 的纸牌，但这种方案不符合 Alice 的偏好原则，因此无效。我们可以证明在这种情况下 Alice 无法获得类型为 $ 4 $ 的纸牌。

 **本翻译由 AI 自动生成**

## 样例 #1

### 输入

```
2
3
1 3 2
2 1 3
1 2 3
4
2 3 1 4
1 2 3 4
1 4 2 3
```

### 输出

```
YES
2
k 2
q 3
NO
```



---

---
title: "Natlan Exploring"
layout: "post"
diff: 普及+/提高
pid: CF2037G
tag: ['动态规划 DP', '数论', '莫比乌斯反演', '容斥原理']
---

# Natlan Exploring

## 题目描述

You are exploring the stunning region of Natlan! This region consists of $ n $ cities, and each city is rated with an attractiveness $ a_i $ . A directed edge exists from City $ i $ to City $ j $ if and only if $ i < j $ and $ \gcd(a_i,a_j)\neq 1 $ , where $ \gcd(x, y) $ denotes the [greatest common divisor (GCD)](https://en.wikipedia.org/wiki/Greatest_common_divisor) of integers $ x $ and $ y $ .

Starting from City $ 1 $ , your task is to determine the total number of distinct paths you can take to reach City $ n $ , modulo $ 998\,244\,353 $ . Two paths are different if and only if the set of cities visited is different.

## 输入格式

The first line contains an integer $ n $ ( $ 2 \leq n \leq 2 \cdot 10^5 $ ) — the number of cities.

The second line contains $ n $ integers $ a_1, a_2, \ldots, a_n $ ( $ 2 \leq a_i \leq 10^6 $ ) — the attractiveness of each city.

## 输出格式

Output the total number of distinct paths you can take to reach City $ n $ , modulo $ 998\,244\,353 $ .

## 说明/提示

In the first example, the five paths are the following:

- City $ 1\rightarrow $ City $ 5 $
- City $ 1\rightarrow $ City $ 2\rightarrow $ City $ 5 $
- City $ 1\rightarrow $ City $ 2\rightarrow $ City $ 3\rightarrow $ City $ 5 $
- City $ 1\rightarrow $ City $ 2\rightarrow $ City $ 4\rightarrow $ City $ 5 $
- City $ 1\rightarrow $ City $ 4\rightarrow $ City $ 5 $

In the second example, the two paths are the following:

- City $ 1\rightarrow $ City $ 3\rightarrow $ City $ 5 $
- City $ 1\rightarrow $ City $ 2\rightarrow $ City $ 3\rightarrow $ City $ 5 $

## 样例 #1

### 输入

```
5
2 6 3 4 6
```

### 输出

```
5
```

## 样例 #2

### 输入

```
5
4 196 2662 2197 121
```

### 输出

```
2
```

## 样例 #3

### 输入

```
7
3 6 8 9 11 12 20
```

### 输出

```
7
```

## 样例 #4

### 输入

```
2
2 3
```

### 输出

```
0
```



---

---
title: "Sums on Segments"
layout: "post"
diff: 普及+/提高
pid: CF2043C
tag: ['动态规划 DP', '贪心']
---

# Sums on Segments

## 题目描述

### 题目内容
给定一个长度为 $n$ 的数组 $a$，其中除了至多一个 $i \in [0,n)$ 满足 $|a_i| \neq 1$ 以外，其余全部项均满足 $|a_i|=1$。

求该数组中全部可能的子数组和，以升序输出。子数组是原数组中一段连续的数组。

## 输入格式

第一行一个整数 $t$（$ 1 \le t \le 10^4$ ），表示测试用例数。

每个测试用例包含 $2$ 行，其中：
- 第一行一个正整数 $n$（ $1 \le n \le 2 \cdot 10^5$ ），表示数组长度
- 第二行 $n$ 个整数，表示 $a$ 中元素。

保证全部测试用例中 $n$ 的总和不超过 $2 \cdot 10^5$。

## 输出格式

对于每个测试点，输出两行：
- 第一行一个整数，表示可能的子数组和个数。
- 第二行以升序输出所有可能的子数组和。

即便多个子数组均可求出这个和，每一个值也只需要输出一次。

## 样例 #1

### 输入

```
5
5
1 -1 10 1 1
5
-1 -1 -1 -1 -1
2
-1 2
2
7 1
3
1 4 -1
```

### 输出

```
8
-1 0 1 2 9 10 11 12 
6
-5 -4 -3 -2 -1 0 
4
-1 0 1 2 
4
0 1 7 8 
6
-1 0 1 3 4 5
```



---

---
title: "Shift + Esc"
layout: "post"
diff: 普及+/提高
pid: CF2049D
tag: ['动态规划 DP']
---

# Shift + Esc

## 题目描述

对于被某个装置捉弄之后，龙 Evirir 决定利用他的魔法技能来改变现实以迅速逃脱。

你得到一个 $n$ 行 $m$ 列的非负整数网格，以及一个整数 $k$。我们用 $(i, j)$ 表示从上到下第 $i$ 行、从左到右第 $j$ 列的单元格（$1 \le i \le n$，$1 \le j \le m$）。在每个单元格 $(i, j)$ 上都有一个整数 $a_{i, j}$。

你起始位于 $(1, 1)$，目标是走到 $(n, m)$。在移动过程中，你只能向下或向右移动——也就是说，如果你在 $(i, j)$，只能移动到 $(i+1, j)$ 或 $(i, j+1)$，当然，前提是这些目标单元格必须存在。

在开始移动之前，你可以进行以下操作任意多次：

- 从 $1$ 到 $n$ 中选择一个整数 $i$，然后将第 $i$ 行的元素循环左移一位。这个操作的效果是，将每个 $a_{i,j}$ 更新为 $a_{i,(j \bmod m) + 1}$。

请注意，一旦你开始移动，就不能再进行行移操作。从 $(1, 1)$ 到 $(n, m)$ 之后，令 $x$ 是你在开始移动之前进行的操作次数，而 $y$ 是你经过的所有单元格上的整数之和（包括起始和目标位置）。最终成本被定义为 $kx + y$。

你的任务是计算出以最小成本从 $(1, 1)$ 移动到 $(n, m)$ 所需的操作次数。

## 输入格式

输入包括多个测试用例。第一行为测试用例数量 $t$（$1 \le t \le 10^4$）。接下来每个测试用例包含：

- 一行三个用空格分隔的整数 $n$、$m$ 和 $k$（$1 \leq n, m \leq 200$，$0 \leq k \leq 10^9$）。
- 随后的 $n$ 行，每行包含 $m$ 个用空格分隔的整数，分别表示这一行上的 $a_{i,1},\,a_{i,2},\,\ldots,\,a_{i,m}$（$0 \leq a_{i,j} \leq 10^9$）。

所有测试用例中 $n \cdot m$ 的总和不超过 $5 \cdot 10^4$。

## 输出格式

对于每个测试用例，输出从起点 $(1, 1)$ 到终点 $(n, m)$ 的最小成本。

## 说明/提示

在第一个测试用例中，最低成本是 $113$，可以通过以下步骤实现：

1. 将第 3 行循环左移一次。网格变成：
   $$
   \begin{bmatrix}
   3 & 4 & 9 \\
   5 & 2 & 4 \\
   101 & 101 & 0
   \end{bmatrix}.
   $$
2. 按以下路径行进：$(1, 1) \to (1, 2) \to (2, 2) \to (2, 3) \to (3, 3)$。

进行了一次操作，访问的路径上整数之和为 $y = 3 + 4 + 2 + 4 + 0 = 13$。因此，总成本为 $kx + y = 100 \cdot 1 + 13 = 113$。

在第二个测试用例中，你可以将第 1 行左移一次，第 2 行左移两次，第 3 行左移三次。最终网格变成：
$$
\begin{bmatrix}
0 & 0 & 10 & 10 \\
10 & 0 & 0 & 0 \\
10 & 10 & 10 & 0
\end{bmatrix}.
$$

共进行了 $x = 6$ 次操作，并且经过的路径上整数之和为 $y = 0$。因此，总成本为 $6 \cdot 1 + 0 = 6$。

 **本翻译由 AI 自动生成**

## 样例 #1

### 输入

```
5
3 3 100
3 4 9
5 2 4
0 101 101
3 4 1
10 0 0 10
0 0 10 0
10 10 0 10
1 1 3
4
3 2 3
1 2
3 6
5 4
10 10 14
58 49 25 12 89 69 8 49 71 23
45 27 65 59 36 100 73 23 5 84
82 91 54 92 53 15 43 46 11 65
61 69 71 87 67 72 51 42 55 80
1 64 8 54 61 70 47 100 84 50
86 93 43 51 47 35 56 20 33 61
100 59 5 68 15 55 69 8 8 60
33 61 20 79 69 51 23 24 56 28
67 76 3 69 58 79 75 10 65 63
6 64 73 79 17 62 55 53 61 58
```

### 输出

```
113
6
4
13
618
```



---

---
title: "Resourceful Caterpillar Sequence"
layout: "post"
diff: 普及+/提高
pid: CF2053E
tag: ['动态规划 DP', '博弈论', '树形 DP']
---

# Resourceful Caterpillar Sequence

## 题目描述

无尽的七日轮回

— r-906, [Panopticon](https://www.youtube.com/watch?v=_-Vd0ZGB-lo)

在一个由 $n$ 个顶点组成的树中，定义了一种“毛毛虫”。一个毛毛虫用整数对 $(p, q)$（$1 \leq p, q \leq n$，且 $p \neq q$）表示，它的头在顶点 $p$，尾在顶点 $q$，并且该毛毛虫支配从 $p$ 到 $q$ 的简单路径上的所有顶点（包括 $p$ 和 $q$）。$(p, q)$ 的毛毛虫序列是按到 $p$ 的距离递增排序后的路径上的顶点序列。

Nora 和 Aron 轮流移动这条毛毛虫，Nora 先手。两个人都采用各自的最优策略来进行游戏：

- 他们会尽全力争取胜利；
- 如果无法赢得胜利，他们将努力阻止对方获胜（这样，游戏就会以平局收场）。

在 Nora 的回合中，她需要从与顶点 $p$ 相邻且未被毛毛虫支配的顶点中选择一个 $u$，然后将毛毛虫向顶点 $u$ 移动一个边。同样，在 Aron 的回合中，他需要从与顶点 $q$ 相邻且未被毛毛虫支配的顶点中选择一个 $v$，并将毛毛虫向顶点 $v$ 移动一个边。注意，两位玩家的移动方式是不同的。

若 $p$ 是叶子节点时，Nora 赢得胜利。而当 $q$ 是叶子节点时，Aron 赢得胜利。如果初始时 $p$ 和 $q$ 都是叶子，或经过 $10^{100}$ 回合游戏仍未结束，最终结果为平局。

请统计能让 Aron 赢得游戏的整数对 $(p, q)$ 的数量：$1 \leq p, q \leq n$ 且 $p \neq q$。

*用简单的话来说：当前的毛毛虫序列是 $c_1, c_2, \ldots, c_k$，移动后，新序列变为 $d(u, c_1), d(u, c_2), \ldots, d(u, c_k)$。这里，$d(x, y)$ 表示从 $y$ 到 $x$ 的简单路径上的下一个顶点。

*在树中，一个顶点的度数为1时，该顶点称为叶子节点。

*因此，只要游戏未结束，Nora 总能找到一个顶点 $u$ 来进行移动。Aron 也是一样。

## 输入格式

每个测试组包含多个测试用例。第一行给出一个整数 $t$（$1 \leq t \leq 2 \cdot 10^4$），表示测试用例的数量。接下来是各个测试用例的具体描述。

每个测试用例的第一行包含一个整数 $n$（$2 \leq n \leq 2 \cdot 10^5$），表示树中的顶点数。

接下来的 $n - 1$ 行，每行有两个整数 $u$ 和 $v$（$1 \leq u, v \leq n$），表示顶点 $u$ 和 $v$ 之间存在一条边。保证这些边构成了一棵树。

保证所有测试用例中 $n$ 的总和不超过 $4 \cdot 10^5$。

## 输出格式

对于每个测试用例，输出一个整数，表示能够让 Aron 得胜的整数对 $(p, q)$ 的数量。

## 说明/提示

在第一个测试例中，所有可能的毛毛虫是 $(1, 2)$ 和 $(2, 1)$。由于初始时 $p$ 和 $q$ 都是叶子，因此结果为平局。

在第二个测试例中，满足 Aron 赢得游戏的毛毛虫包括：$(1, 3)$、$(1, 4)$、$(1, 5)$、$(2, 3)$、$(2, 4)$、$(2, 5)$。下面我们来具体分析一些毛毛虫的情况：

- 对于毛毛虫 $(1, 5)$：顶点 $p = 1$ 不是叶子，而 $q = 5$ 是叶子，因此 Aron 在一开始就胜利。
- 对于毛毛虫 $(2, 1)$：顶点 $p = 2$ 不是叶子，$q = 1$ 也不是叶子。在 Nora 的第一次移动中，她可以选择将毛毛虫移向顶点 $5$，此时毛毛虫变为 $(5, 2)$，顶点 $p = 5$ 是叶子，因此 Nora 在下一步中胜利。

 **本翻译由 AI 自动生成**

## 样例 #1

### 输入

```
5
2
1 2
5
1 2
1 3
2 4
2 5
12
1 6
11 2
4 8
12 3
2 7
6 12
8 1
2 3
5 12
9 2
10 3
10
1 2
2 3
3 4
4 5
5 6
4 7
6 8
4 9
4 10
25
1 16
11 22
6 14
3 1
20 14
23 17
25 19
10 11
3 18
10 6
2 21
4 5
11 12
4 9
9 13
8 6
6 1
3 7
8 19
10 24
15 13
1 2
3 4
17 8
```

### 输出

```
0
6
40
27
171
```



---

---
title: "Tree Jumps"
layout: "post"
diff: 普及+/提高
pid: CF2070D
tag: ['动态规划 DP', '广度优先搜索 BFS', '树的遍历']
---

# Tree Jumps

## 题目描述

给定一棵包含 $n$ 个顶点的有根树。树中顶点编号为 $1$ 到 $n$，根为顶点 $1$。定义 $d_x$ 为根到顶点 $x$ 的距离（最短路径上的边数）。

初始时，一个棋子被放置在根节点。你可以执行以下操作任意次（包括零次）：

- 将棋子从当前顶点 $v$ 移动到顶点 $u$，满足 $d_u = d_v + 1$。如果 $v$ 是根节点，可以选择任意满足此约束的顶点 $u$；但如果 $v$ 不是根节点，则 $u$ 不能是 $v$ 的邻居（即 $v$ 和 $u$ 之间不能有直接边相连）。

例如在上图的树结构中，允许的移动包括：$1 \rightarrow 2$，$1 \rightarrow 5$，$2 \rightarrow 7$，$5 \rightarrow 3$，$5 \rightarrow 4$，$3 \rightarrow 6$，$7 \rightarrow 6$。

如果一个顶点序列满足：存在一种棋子移动方式，使得棋子按顺序恰好访问序列中的所有顶点（且仅这些顶点），则该序列被称为有效的。

你的任务是计算有效顶点序列的数量。由于答案可能很大，请输出其对 $998244353$ 取模的结果。

## 输入格式

第一行包含一个整数 $t$（$1 \le t \le 10^4$）——测试用例的数量。

每个测试用例的第一行包含一个整数 $n$（$2 \le n \le 3 \cdot 10^5$）。

第二行包含 $n-1$ 个整数 $p_2, p_3, \dots, p_n$（$1 \le p_i < i$），其中 $p_i$ 表示第 $i$ 个顶点的父节点。顶点 $1$ 是根节点。

输入额外约束：所有测试用例的 $n$ 之和不超过 $3 \cdot 10^5$。

## 输出格式

对于每个测试用例，输出一个整数——有效顶点序列的数量模 $998244353$ 的结果。

## 说明/提示

第一个示例中，有效序列为：$[1]$，$[1, 2]$，$[1, 4]$，$[1, 4, 3]$。

第二个示例中，有效序列为：$[1]$，$[1, 2]$。

第三个示例中，有效序列为：$[1]$，$[1, 2]$，$[1, 2, 7]$，$[1, 2, 7, 6]$，$[1, 5]$，$[1, 5, 3]$，$[1, 5, 3, 6]$，$[1, 5, 4]$。

翻译由 DeepSeek R1 完成

## 样例 #1

### 输入

```
3
4
1 2 1
3
1 2
7
1 2 2 1 4 5
```

### 输出

```
4
2
8
```



---

---
title: "Equalization"
layout: "post"
diff: 普及+/提高
pid: CF2075D
tag: ['动态规划 DP', '背包 DP']
---

# Equalization

## 题目描述

给定两个非负整数 $x$ 和 $y$。

你可以执行以下操作任意次数（包括零次）：选择一个正整数 $k$，并将 $x$ 或 $y$ 除以 $2^k$（向下取整）。此操作的代价为 $2^k$。但存在额外约束：每个 $k$ 值最多只能选择一次。

你的任务是计算使 $x$ 和 $y$ 相等所需的最小可能代价。

## 输入格式

第一行包含一个整数 $t$（$1 \le t \le 10^5$）——测试用例的数量。

每个测试用例的唯一一行包含两个整数 $x$ 和 $y$（$0 \le x, y \le 10^{17}$）。

## 输出格式

对于每个测试用例，输出一个整数——使 $x$ 和 $y$ 相等所需的最小可能代价。

## 说明/提示

第一个示例中，可以按如下步骤操作：选择 $k=1$ 并将 $y$ 除以 $2$。之后，$x$ 和 $y$ 均等于 $0$。

第二个示例中，可以按如下步骤操作：选择 $k=2$ 并将 $x$ 除以 $4$；选择 $k=1$ 并将 $y$ 除以 $2$。之后，$x$ 和 $y$ 均等于 $1$。

第三个示例中，两数已经相等，无需操作。

翻译由 DeepSeek R1 完成

## 样例 #1

### 输入

```
5
0 1
6 2
3 3
13 37
4238659325782394 12983091057341925
```

### 输出

```
2
6
0
26
32764
```



---

---
title: "Scammy Game Ad"
layout: "post"
diff: 普及+/提高
pid: CF2078D
tag: ['动态规划 DP', '贪心']
---

# Scammy Game Ad

## 题目描述

考虑以下游戏。

![](https://cdn.luogu.com.cn/upload/vjudge_pic/CF2078D/08bde909876902ee9b6ced6653b4847e8c05fa58.png)

游戏中每个关卡包含 $n$ 对门。每对门包含一个左门和一个右门。每个门执行以下两种操作之一：
- **加法操作 (+ $a$)**：将该通道的人数增加固定值 $a$。
- **乘法操作 (× $a$)**：将该通道当前人数乘以整数 $a$。这意味着该通道人数将增加 $(a - 1)$ 倍当前值。

每个操作产生的新增人员可以分配到任意通道。但已存在于某个通道的人员不可转移到另一个通道。

初始时，每个通道各有 $1$ 人。你的任务是确定关卡结束时可达到的最大总人数。

## 输入格式

第一行输入整数 $t$（$1 \leq t \leq 10^4$）——测试用例数量。

每个测试用例的第一行包含一个整数 $n$（$1 \leq n \le 30$）——门对的数量。

接下来每个测试用例的 $n$ 行依次描述每对门的左门和右门信息。每个门的信息以 + $a$（$1 \le a \le 1000$）或 × $a$（$2 \le a \le 3$）形式给出，其中 $a$ 为整数。

## 输出格式

对于每个测试用例，输出一个整数——关卡结束时的最大总人数。

## 说明/提示

第一个测试用例的最优操作方式如下：

初始时，左通道人数 $l=1$，右通道人数 $r=1$。

通过第一对门后：
- 左门产生 $4$ 人（加法操作），右门产生 $1 \cdot (2-1) = 1$ 人（乘法操作）
- 总新增 $4+1=5$ 人，分配 $2$ 人到左通道，$3$ 人到右通道
- 结果：$l=1+2=3$，$r=1+3=4$

通过第二对门后：
- 左门产生 $3 \cdot (3-1) = 6$ 人（乘法操作），右门产生 $4 \cdot (3-1) = 8$ 人（乘法操作）
- 总新增 $6+8=14$ 人，均分 $7$ 人到两个通道
- 结果：$l=3+7=10$，$r=4+7=11$

通过最后一对门后：
- 左门产生 $7$ 人（加法操作），右门产生 $4$ 人（加法操作）
- 总新增 $7+4=11$ 人，分配 $6$ 人到左通道，$5$ 人到右通道
- 结果：$l=10+6=16$，$r=11+5=16$

最终总人数为 $16+16=32$。

翻译由 DeepSeek R1 完成

## 样例 #1

### 输入

```
4
3
+ 4 x 2
x 3 x 3
+ 7 + 4
4
+ 9 x 2
x 2 x 3
+ 9 + 10
x 2 + 1
4
x 2 + 1
+ 9 + 10
x 2 x 3
+ 9 x 2
5
x 3 x 3
x 2 x 2
+ 21 + 2
x 2 x 3
+ 41 x 3
```

### 输出

```
32
98
144
351
```



---

---
title: "Math Division"
layout: "post"
diff: 普及+/提高
pid: CF2081A
tag: ['动态规划 DP', '概率论']
---

# Math Division

## 题目描述

Ecrade 有一个整数 $x$。他将以长度为 $n$ 的二进制数的形式向你展示这个数。

存在两种操作：
1. 将 $x$ 替换为 $\left\lfloor \frac{x}{2}\right\rfloor$，其中 $\left\lfloor \frac{x}{2}\right\rfloor$ 是小于等于 $\frac{x}{2}$ 的最大整数。
2. 将 $x$ 替换为 $\left\lceil \frac{x}{2}\right\rceil$，其中 $\left\lceil \frac{x}{2}\right\rceil$ 是大于等于 $\frac{x}{2}$ 的最小整数。

Ecrade 将执行若干次操作直到 $x$ 变为 $1$。每次操作时，他会独立地以 $\frac{1}{2}$ 的概率选择执行第一种操作或第二种操作。

Ecrade 想知道他将执行的操作次数的期望值（模 $10^9 + 7$）。由于问题有一定难度，请你帮助他！

## 输入格式

第一行输入一个整数 $t$（$1 \le t \le 10^5$）——测试用例数量。接下来描述每个测试用例。

每个测试用例的第一行包含一个整数 $n$（$1 \le n \le 10^5$）——$x$ 的二进制表示长度。

每个测试用例的第二行包含一个长度为 $n$ 的二进制字符串：表示 $x$ 的二进制形式，从最高有效位到最低有效位给出。保证 $x$ 的最高有效位为 $1$。

保证所有测试用例的 $n$ 总和不超过 $10^5$。

## 输出格式

对于每个测试用例，输出一个整数表示 Ecrade 将执行的操作次数的期望值（模 $10^9 + 7$）。

形式化地，令 $M = 10^9 + 7$。可以证明精确答案可以表示为不可约分数 $\dfrac{p}{q}$，其中 $p$ 和 $q$ 为整数且 $q \not \equiv 0 \pmod{M}$。请输出 $p \cdot q^{-1} \bmod M$。换句话说，输出满足 $0 \le x < M$ 且 $x \cdot q \equiv p \pmod{M}$ 的整数 $x$。

## 说明/提示

为简化描述，我们将第一种操作称为 $\text{OPER 1}$，第二种操作称为 $\text{OPER 2}$。

第一个测试用例中，$x=6$，存在六种可能的操作序列：
- $6 \xrightarrow{\text{OPER 1}} 3 \xrightarrow{\text{OPER 1}} 1$，概率为 $\dfrac{1}{4}$。
- $6 \xrightarrow{\text{OPER 1}} 3 \xrightarrow{\text{OPER 2}} 2 \xrightarrow{\text{OPER 1}} 1$，概率为 $\dfrac{1}{8}$。
- $6 \xrightarrow{\text{OPER 1}} 3 \xrightarrow{\text{OPER 2}} 2 \xrightarrow{\text{OPER 2}} 1$，概率为 $\dfrac{1}{8}$。
- $6 \xrightarrow{\text{OPER 2}} 3 \xrightarrow{\text{OPER 1}} 1$，概率为 $\dfrac{1}{4}$。
- $6 \xrightarrow{\text{OPER 2}} 3 \xrightarrow{\text{OPER 2}} 2 \xrightarrow{\text{OPER 1}} 1$，概率为 $\dfrac{1}{8}$。
- $6 \xrightarrow{\text{OPER 2}} 3 \xrightarrow{\text{OPER 2}} 2 \xrightarrow{\text{OPER 2}} 1$，概率为 $\dfrac{1}{8}$。

因此，操作次数的期望为 $2 \cdot \dfrac{1}{4} + 3 \cdot \dfrac{1}{8} + 3 \cdot \dfrac{1}{8} + 2 \cdot \dfrac{1}{4} + 3 \cdot \dfrac{1}{8} + 3 \cdot \dfrac{1}{8} = \dfrac{5}{2} \equiv 500\,000\,006 \pmod{10^9 + 7}$。

翻译由 DeepSeek R1 完成

## 样例 #1

### 输入

```
3
3
110
3
100
10
1101001011
```

### 输出

```
500000006
2
193359386
```



---

---
title: "Igor and Mountain"
layout: "post"
diff: 普及+/提高
pid: CF2091F
tag: ['动态规划 DP', '前缀和']
---

# Igor and Mountain

## 题目描述

IT Campus "NEIMARK" 的访客不仅是优秀的程序员，更是体魄强健的运动爱好者！有人练习游泳，有人划船，还有人进行攀岩！

Igor 大师是当地攀岩界的知名人物。某天，他前往山区攀登一座山峰。作为经验丰富的攀岩者，Igor 决定不沿既有路线，而是利用自己的技巧严格垂直攀登。

Igor 找到了一块垂直的矩形山体区域，并将其在脑海中划分为 $n$ 个水平层。随后他将每层用垂直隔板分割为 $m$ 个区段。观察这些区段时，Igor 发现了可供抓握的凸起（以下称为支点）。因此，所选山体区域可表示为 $n \times m$ 的矩形，其中某些单元格包含支点。

作为资深程序员，Igor 决定计算有效路线的数量。路线被定义为由不同支点组成的序列。当满足以下条件时，路线被视为有效：

- 路线中第一个支点位于最底层（第 $n$ 行）；
- 路线中最后一个支点位于最顶层（第 $1$ 行）；
- 每个后续支点不低于前一个支点；
- 每层（即矩形的每一行）至少使用一个支点；
- 每层最多使用两个支点（因 Igor 只有双手）；
- 当相邻支点对应区段中心点的欧氏距离不超过 Igor 的臂展时，才能从当前支点移动到下一个支点。

Igor 的臂展为 $d$，这意味着当两个支点对应区段中心点的欧氏距离不超过 $d$ 时可进行移动。区段 $(i_1, j_1)$ 与 $(i_2, j_2)$ 之间的距离计算公式为 $\sqrt{(i_1 - i_2)^2 + (j_1 - j_2)^2}$。

请计算不同有效路线的数量。若两条路线使用的支点列表或访问顺序不同，则视为不同的路线。

## 输入格式

每个测试包含多个测试用例。第一行包含测试用例数量 $t$ ($1 \leq t \leq 10^3$)。接下来是测试用例描述。

每个测试用例的第一行包含三个整数 $n$、$m$、$d$ ($2 \leq n \leq 2000$, $1 \leq m, d \leq 2000$)。

接下来的 $n$ 行每行包含 $m$ 个字符 —— 描述山体各层情况。字符 '#' 表示空区段，'X' 表示含支点的区段。层数描述顺序为从上到下。

保证所有测试用例的 $n \cdot m$ 之和不超过 $4 \cdot 10^6$。

## 输出格式

对于每个测试用例，输出不同路线数量对 $998244353$ 取模后的结果。


## 说明/提示

第一个样例中的可能路线：

![](https://cdn.luogu.com.cn/upload/vjudge_pic/CF2091F/e87023b4f4a219144271b82b78cb035704abe051.png)  
第二个样例中 Igor 的臂展增大，因此新路线可用，例如：

![](https://cdn.luogu.com.cn/upload/vjudge_pic/CF2091F/af93e08d9fa412dbf0403f4084f2c8743d449017.png)  
第三个样例中底层没有支点，因此不存在有效路线。

翻译由 DeepSeek R1 完成

## 样例 #1

### 输入

```
3
3 4 1
XX#X
#XX#
#X#X
3 4 2
XX#X
#XX#
#X#X
3 1 3
X
X
#
```

### 输出

```
2
60
0
```



---

---
title: "Wonderful City"
layout: "post"
diff: 普及+/提高
pid: CF2096C
tag: ['动态规划 DP']
---

# Wonderful City

## 题目描述

你是古伯兰王国一座城市的骄傲领导者。这座城市有 $n^2$ 栋建筑，排列成 $n$ 行 $n$ 列的网格。位于第 $i$ 行第 $j$ 列的建筑高度为 $h_{i,j}$。

当城市中任意两个相邻建筑的高度都不相同时，这座城市才是美丽的。换句话说，必须满足以下条件：
- 不存在位置 $(i,j)$（$1 \leq i \leq n$，$1 \leq j \leq n-1$）使得 $h_{i,j} = h_{i,j+1}$；
- 不存在位置 $(i,j)$（$1 \leq i \leq n-1$，$1 \leq j \leq n$）使得 $h_{i,j} = h_{i+1,j}$。

A 公司有 $n$ 名工人，B 公司也有 $n$ 名工人。每名工人最多只能被雇佣一次。

雇佣 A 公司的第 $i$ 名工人需要花费 $a_i$ 枚金币。雇佣后，该工人会：
- 将第 $i$ 行所有建筑的高度增加 $1$。即，将 $h_{i,1}, h_{i,2}, \ldots, h_{i,n}$ 都增加 $1$。

雇佣 B 公司的第 $j$ 名工人需要花费 $b_j$ 枚金币。雇佣后，该工人会：
- 将第 $j$ 列所有建筑的高度增加 $1$。即，将 $h_{1,j}, h_{2,j}, \ldots, h_{n,j}$ 都增加 $1$。

请计算使城市变得美丽所需的最少金币数，如果不可能实现则返回 $-1$。

## 输入格式

每个测试包含多个测试用例。第一行包含测试用例的数量 $t$（$1 \le t \le 100$）。接下来是各个测试用例的描述。

每个测试用例的第一行包含一个整数 $n$（$2 \le n \le 1000$）——网格的大小。

接下来每个测试用例的 $n$ 行中，第 $i$ 行包含 $n$ 个整数 $h_{i,1}, h_{i,2}, \ldots, h_{i,n}$（$1 \le h_{i,j} \le 10^9$）——第 $i$ 行建筑的高度。

每个测试用例的下一行包含 $n$ 个整数 $a_1, a_2, \ldots, a_n$（$1 \le a_i \le 10^9$）——雇佣 A 公司工人的费用。

每个测试用例的下一行包含 $n$ 个整数 $b_1, b_2, \ldots, b_n$（$1 \le b_j \le 10^9$）——雇佣 B 公司工人的费用。

保证所有测试用例的 $n$ 之和不超过 $1000$。

## 输出格式

对于每个测试用例，输出一个整数——所需的最少金币数，如果不可能则输出 $-1$。


## 说明/提示

对于第一个测试用例，可以看到城市已经是美丽的，因此答案为 $0$。

对于第二个测试用例，我们可以雇佣 A 公司的第 $2$ 名工人、A 公司的第 $4$ 名工人和 B 公司的第 $4$ 名工人：
- 初始状态：
```
1 2 1 2
3 2 1 2
1 2 1 1
1 3 1 2
```
- 雇佣 A 公司第 $2$ 名工人后：
```
1 2 1 2
4 3 2 3
1 2 1 1
1 3 1 2
```
- 雇佣 A 公司第 $4$ 名工人后：
```
1 2 1 2
4 3 2 3
1 2 1 1
2 4 2 3
```
- 雇佣 B 公司第 $4$ 名工人后：
```
1 2 1 3
4 3 2 4
1 2 1 2
2 4 2 4
```

此时城市变得美丽，雇佣工人的总费用为 $2 + 4 + 8 = 14$，这是可能的最小费用。

对于第三个测试用例，无论如何操作都无法使城市变得美丽，因此答案为 $-1$。

翻译由 DeepSeek V3 完成

## 样例 #1

### 输入

```
4
2
1 2
2 1
100 100
100 100
4
1 2 1 2
3 2 1 2
1 2 1 1
1 3 1 2
1 2 3 4
5 6 7 8
3
1 2 2
2 2 1
2 1 1
100 100 100
100 100 100
6
8 7 2 8 4 8
7 7 9 7 1 1
8 3 1 1 8 5
6 8 3 1 1 4
1 4 5 1 9 6
7 1 1 6 8 2
11 23 20 79 30 15
15 83 73 57 34 63
```

### 输出

```
0
14
-1
183
```



---

---
title: "Fewer Batteries"
layout: "post"
diff: 普及+/提高
pid: CF2110D
tag: ['动态规划 DP', '图论', '二分']
---

# Fewer Batteries

## 题目描述

在 2077 年机器人统治世界后，它们决定进行以下比赛。

有 $n$ 个检查点，第 $i$ 个检查点包含 $b_i$ 块电池。机器人最初从第 $1$ 个检查点出发，不带任何电池，必须到达第 $n$ 个检查点。

检查点之间共有 $m$ 条单向通道。第 $i$ 条通道允许从点 $s_i$ 移动到点 $t_i$（$s_i < t_i$），但不能反向移动。此外，只有当机器人拥有至少 $w_i$ 块充满电的电池时，才能使用第 $i$ 条通道；否则它会在途中耗尽电量。

当机器人到达点 $v$ 时，可以额外获取 $0$ 到 $b_v$（含）之间的任意数量电池。而且，它会携带之前收集的所有电池，并在每个检查点为所有已收集的电池充电。

求机器人旅程结束时能够拥有的最少电池数量，如果无法从第一个检查点到达最后一个检查点，则报告不可能。

## 输入格式

每个测试包含多个测试用例。第一行包含测试用例数量 $t$（$1 \le t \le 10^4$）。接下来是测试用例描述。

每个测试用例的第一行包含两个整数 $n, m$（$2 \leq n \leq 2 \cdot 10^5$，$0 \leq m \leq 3 \cdot 10^5$）——分别表示检查点数量和通道数量。

第二行包含 $n$ 个数字 $b_i$（$0 \leq b_i \leq 10^9$）——第 $i$ 个检查点的电池数量。

接下来的 $m$ 行每行包含三个整数 $s_i, t_i, w_i$（$1 \leq s_i < t_i \leq n$，$1 \leq w_i \leq 10^9$）——通道的起点、终点和通过所需的最低电池数量。

保证所有测试用例的 $n$ 之和不超过 $2 \cdot 10^5$。
保证所有测试用例的 $m$ 之和不超过 $3 \cdot 10^5$。

## 输出格式

对于每个测试用例，输出旅程结束时能够拥有的最少电池数量，如果无法到达点 $n$，则输出 $-1$。


## 说明/提示

在第一个测试用例中，需要在起点获取 $1$ 块电池，然后移动到点 $2$，再移动到点 $3$。

在第二个测试用例中，需要在起点获取 $2$ 块电池，移动到点 $2$ 再获取 $2$ 块电池，移动到点 $4$，最后移动到点 $5$。

在第三个测试用例中，没有从点 $1$ 到点 $n$ 的路径。

在第四个测试用例中，需要在起点获取 $1$ 块电池，移动到点 $2$ 再获取 $9$ 块电池，移动到点 $3$，最后移动到点 $4$。

翻译由 DeepSeek V3 完成

## 样例 #1

### 输入

```
4
3 3
2 0 0
1 2 1
2 3 1
1 3 2
5 6
2 2 5 0 1
1 2 2
1 3 1
1 4 3
3 5 5
2 4 4
4 5 3
2 0
1 1
4 4
3 10 0 0
1 2 1
1 3 3
2 3 10
3 4 5
```

### 输出

```
1
4
-1
10
```



---

---
title: "Small Operations"
layout: "post"
diff: 普及+/提高
pid: CF2114F
tag: ['动态规划 DP', '搜索', '数学', '记忆化搜索', '最大公约数 gcd']
---

# Small Operations

## 题目描述

给你两个正整数 $x,k$。进行以下两种变换之一称为一次操作：
- 选择一个满足 $1 \le a \le k$ 的正整数 $a$，使 $x$ 变为 $x\cdot a$；
- 选择一个满足 $1 \le a \le k$ 的正整数 $a$，使 $x$ 变为 $\frac{x}{a}$，要求操作完后 $x$ 值是整数。

你需要找出使 $x$ 变为给定正整数 $y$ 的最小操作次数，或判断无解。

## 输入格式

第一行，一个正整数 $t\ (1 \le t \le {10}^4)$，表示测试数据组数。

对于每组测试数据，一行三个正整数 $x,y,k\ (1 \le x,y,k \le {10}^6)$。

保证所有测试数据中 $x$ 的总和与 $y$ 的总和均不超过 ${10}^8$。

## 输出格式

对于每组测试数据，如果无解输出 $-1$，否则输出使 $x$ 变为 $y$ 的最小操作次数。

## 说明/提示

对于第一组测试数据，我们可以选择 $a=2$，将 $x$ 除以 $2$，然后选择 $a=3$，将 $x$ 乘上 $3$，此时 $x$ 将变为 $6$，等于 $y$。

对于第二组测试数据，可以证明其不可能。

对于第七组测试数据，我们可以分别选择 $a=7,9,10,10,12,13$，连续做 $6$ 次乘法。可以证明没有比这更少的操作次数了。

## 样例 #1

### 输入

```
8
4 6 3
4 5 3
4 6 2
10 45 3
780 23 42
11 270 23
1 982800 13
1 6 2
```

### 输出

```
2
-1
-1
3
3
3
6
-1
```



---

---
title: "Numbers"
layout: "post"
diff: 普及+/提高
pid: CF213B
tag: ['动态规划 DP', '枚举', '组合数学']
---

# Numbers

## 题目描述

Furik loves writing all sorts of problems, especially such that he can't solve himself. You've got one of his problems, the one Furik gave to Rubik. And Rubik asks you to solve it.

There is integer $ n $ and array $ a $ , consisting of ten integers, indexed by numbers from 0 to 9. Your task is to count the number of positive integers with the following properties:

- the number's length does not exceed $ n $ ;
- the number doesn't have leading zeroes;
- digit $ i $ $ (0<=i<=9) $ occurs in the number at least $ a[i] $ times.

## 输入格式

The first line contains integer $ n $ $ (1<=n<=100) $ . The next line contains 10 integers $ a[0] $ , $ a[1] $ , $ ... $ , $ a[9] $ $ (0<=a[i]<=100) $ — elements of array $ a $ . The numbers are separated by spaces.

## 输出格式

On a single line print the remainder of dividing the answer to the problem by $ 1000000007 $ $ (10^{9}+7) $ .

## 说明/提示

In the first sample number 9 meets the requirements.

In the second sample number 10 meets the requirements.

In the third sample numbers 10, 110, 210, 120, 103 meet the requirements. There are other suitable numbers, 36 in total.

## 样例 #1

### 输入

```
1
0 0 0 0 0 0 0 0 0 1

```

### 输出

```
1

```

## 样例 #2

### 输入

```
2
1 1 0 0 0 0 0 0 0 0

```

### 输出

```
1

```

## 样例 #3

### 输入

```
3
1 1 0 0 0 0 0 0 0 0

```

### 输出

```
36

```



---

---
title: "Choosing Capital for Treeland"
layout: "post"
diff: 普及+/提高
pid: CF219D
tag: ['动态规划 DP', '树形 DP']
---

# Choosing Capital for Treeland

## 题目描述

Treeland 国有 $n$ 个城市，有些城市间存在 **单向** 道路。这个国家一共有 $n - 1$ 条路。我们知道，如果把边视作双向的，那么从任意城市出发能到达任意城市。

城市的委员会最近决定为 Treeland 国选择一个首都，显然首都会是国中的一个城市。委员会将在首都开会，并经常取其他城市（这里不考虑从其他城市回到首都）。因此，如果城市 $a$ 被选为首都，那么所有的道路应该被定向，以使得我们能从城市 $a$ 到达其他城市。所以，有些路可能需要反转方向。
   
帮助委员会选择首都使得他们需要反转道路的次数最小。

## 输入格式

第一行有一个整数 $n$（$2 \le n \le 2 \times 10^5$），表示城市的数量。

接下来 $n- 1$ 行描述道路，每个道路一行，用一对整数 $s_i,t_i$（$1 \le s_i,t_i\le n$，$s_i \ne t_i$）表示该道路连接的两个城市，第 $i$ 条道路的方向是从城市 $s_i$ 到城市 $t_i$。

你可以认为 Treeland 国的城市被编号为 $1$ 到 $n$。

## 输出格式

第一行输出需要反转的道路数量的最小值。第二行输出所有可能的选择首都的方式，你需要以从小到大的顺序输出所有可能的城市编号。

Translated by uid $408071$.

## 样例 #1

### 输入

```
3
2 1
2 3

```

### 输出

```
0
2 

```

## 样例 #2

### 输入

```
4
1 4
2 4
3 4

```

### 输出

```
2
1 2 3 

```



---

---
title: "Queries for Number of Palindromes"
layout: "post"
diff: 普及+/提高
pid: CF245H
tag: ['字符串', '动态规划 DP', '区间 DP', '前缀和']
---

# Queries for Number of Palindromes

## 题目描述

给你一个字符串s由小写字母组成，有q组询问，每组询问给你两个数，l和r，问在字符串区间l到r的字串中，包含多少回文串。

## 输入格式

第1行，给出s，s的长度小于5000
第2行给出q(1<=q<=10^6)
第2至2+q行 给出每组询问的l和r

## 输出格式

输出每组询问所问的数量。

## 样例 #1

### 输入

```
caaaba
5
1 1
1 4
2 3
4 6
4 5

```

### 输出

```
1
7
3
4
2

```



---

---
title: "Good Sequences"
layout: "post"
diff: 普及+/提高
pid: CF264B
tag: ['动态规划 DP', '枚举', '最大公约数 gcd']
---

# Good Sequences

## 题目描述

Squirrel Liss is interested in sequences. She also has preferences of integers. She thinks $ n $ integers $ a_{1},a_{2},...,a_{n} $ are good.

Now she is interested in good sequences. A sequence $ x_{1},x_{2},...,x_{k} $ is called good if it satisfies the following three conditions:

- The sequence is strictly increasing, i.e. $ x_{i}&lt;x_{i+1} $ for each $ i $ $ (1<=i<=k-1) $ .
- No two adjacent elements are coprime, i.e. $ gcd(x_{i},x_{i+1})&gt;1 $ for each $ i $ $ (1<=i<=k-1) $ (where $ gcd(p,q) $ denotes the greatest common divisor of the integers $ p $ and $ q $ ).
- All elements of the sequence are good integers.

Find the length of the longest good sequence.

## 输入格式

The input consists of two lines. The first line contains a single integer $ n $ ( $ 1<=n<=10^{5} $ ) — the number of good integers. The second line contains a single-space separated list of good integers $ a_{1},a_{2},...,a_{n} $ in strictly increasing order ( $ 1<=a_{i}<=10^{5}; a_{i}&lt;a_{i+1} $ ).

## 输出格式

Print a single integer — the length of the longest good sequence.

## 说明/提示

In the first example, the following sequences are examples of good sequences: \[2; 4; 6; 9\], \[2; 4; 6\], \[3; 9\], \[6\]. The length of the longest good sequence is 4.

## 样例 #1

### 输入

```
5
2 3 4 6 9

```

### 输出

```
4

```

## 样例 #2

### 输入

```
9
1 2 3 5 6 7 8 9 10

```

### 输出

```
4

```



---

---
title: "Greg and Friends"
layout: "post"
diff: 普及+/提高
pid: CF295C
tag: ['模拟', '动态规划 DP', '枚举']
---

# Greg and Friends

## 题目描述

One day Greg and his friends were walking in the forest. Overall there were $ n $ people walking, including Greg. Soon he found himself in front of a river. The guys immediately decided to get across the river. Luckily, there was a boat by the river bank, just where the guys were standing. We know that the boat can hold people with the total weight of at most $ k $ kilograms.

Greg immediately took a piece of paper and listed there the weights of all people in his group (including himself). It turned out that each person weights either 50 or 100 kilograms. Now Greg wants to know what minimum number of times the boat needs to cross the river to transport the whole group to the other bank. The boat needs at least one person to navigate it from one bank to the other. As the boat crosses the river, it can have any non-zero number of passengers as long as their total weight doesn't exceed $ k $ .

Also Greg is wondering, how many ways there are to transport everybody to the other side in the minimum number of boat rides. Two ways are considered distinct if during some ride they have distinct sets of people on the boat.

Help Greg with this problem.

## 输入格式

The first line contains two integers $ n $ , $ k $ $ (1<=n<=50,1<=k<=5000) $ — the number of people, including Greg, and the boat's weight limit. The next line contains $ n $ integers — the people's weights. A person's weight is either $ 50 $ kilos or $ 100 $ kilos.

You can consider Greg and his friends indexed in some way.

## 输出格式

In the first line print an integer — the minimum number of rides. If transporting everyone to the other bank is impossible, print an integer -1.

In the second line print the remainder after dividing the number of ways to transport the people in the minimum number of rides by number $ 1000000007 $ $ (10^{9}+7) $ . If transporting everyone to the other bank is impossible, print integer $ 0 $ .

## 说明/提示

In the first test Greg walks alone and consequently, he needs only one ride across the river.

In the second test you should follow the plan:

1. transport two $ 50 $ kg. people;
2. transport one $ 50 $ kg. person back;
3. transport one $ 100 $ kg. person;
4. transport one $ 50 $ kg. person back;
5. transport two $ 50 $ kg. people.

That totals to $ 5 $ rides. Depending on which person to choose at step 2, we can get two distinct ways.

## 样例 #1

### 输入

```
1 50
50

```

### 输出

```
1
1

```

## 样例 #2

### 输入

```
3 100
50 50 100

```

### 输出

```
5
2

```

## 样例 #3

### 输入

```
2 50
50 50

```

### 输出

```
-1
0

```



---

---
title: "The least round way"
layout: "post"
diff: 普及+/提高
pid: CF2B
tag: ['动态规划 DP', '数学']
---

# The least round way

## 题目描述

给定由非负整数组成的 $n\times n$ 的正方形矩阵，你需要寻找一条路径：

+ 以左上角为起点。
+ 每次只能向右或向下走。
+ 以右下角为终点。
+ 如果我们把沿路遇到的数进行相乘，积应当以尽可能少的 $0$ 结尾。

## 输入格式

第一行包含一个整数 $n (2 \leq n \leq 1000)$，$n$ 为矩阵的规模，接下来的 $n$ 行包含矩阵的元素（不超过 $10^9$ 的非负整数）。

## 输出格式

第一行应包含结尾最少的 $0$ 的个数，第二行打印出相应的路径（译注：`D` 为下，`R`  为右）。

## 样例 #1

### 输入

```
3
1 2 3
4 5 6
7 8 9

```

### 输出

```
0
DDRR

```



---

---
title: "PE Lesson"
layout: "post"
diff: 普及+/提高
pid: CF316D1
tag: ['动态规划 DP']
---

# PE Lesson

## 题目描述

Smart Beaver decided to be not only smart, but also a healthy beaver! And so he began to attend physical education classes at school X. In this school, physical education has a very creative teacher. One of his favorite warm-up exercises is throwing balls. Students line up. Each one gets a single ball in the beginning. The balls are numbered from $ 1 $ to $ n $ (by the demand of the inventory commission).

 ![](https://cdn.luogu.com.cn/upload/vjudge_pic/CF316D1/dd5cf282ea1c98183da55e6989050cd8eabdb84c.png) Figure 1. The initial position for $ n=5 $ . After receiving the balls the students perform the warm-up exercise. The exercise takes place in a few throws. For each throw the teacher chooses any two arbitrary different students who will participate in it. The selected students throw their balls to each other. Thus, after each throw the students remain in their positions, and the two balls are swapped.

 ![](https://cdn.luogu.com.cn/upload/vjudge_pic/CF316D1/6b5342e8a9f57fae45c7b1e47abe66718bc85450.png) Figure 2. The example of a throw. In this case there was a throw between the students, who were holding the $ 2 $ -nd and the $ 4 $ -th balls. Since the warm-up has many exercises, each of them can only continue for little time. Therefore, for each student we know the maximum number of throws he can participate in. For this lessons maximum number of throws will be $ 1 $ or $ 2 $ .

Note that after all phases of the considered exercise any ball can end up with any student. Smart Beaver decided to formalize it and introduced the concept of the "ball order". The ball order is a sequence of $ n $ numbers that correspond to the order of balls in the line. The first number will match the number of the ball of the first from the left student in the line, the second number will match the ball of the second student, and so on. For example, in figure $ 2 $ the order of the balls was ( $ 1 $ , $ 2 $ , $ 3 $ , $ 4 $ , $ 5 $ ), and after the throw it was ( $ 1 $ , $ 4 $ , $ 3 $ , $ 2 $ , $ 5 $ ). Smart beaver knows the number of students and for each student he knows the maximum number of throws in which he can participate. And now he is wondering: what is the number of distinct ways of ball orders by the end of the exercise.

## 输入格式

The first line contains a single number $ n $ — the number of students in the line and the number of balls. The next line contains exactly $ n $ space-separated integers. Each number corresponds to a student in the line (the $ i $ -th number corresponds to the $ i $ -th from the left student in the line) and shows the number of throws he can participate in.

The input limits for scoring 30 points are (subproblem D1):

- $ 1<=n<=10 $ .

The input limits for scoring 70 points are (subproblems D1+D2):

- $ 1<=n<=500 $ .

The input limits for scoring 100 points are (subproblems D1+D2+D3):

- $ 1<=n<=1000000 $ .

## 输出格式

The output should contain a single integer — the number of variants of ball orders after the warm up exercise is complete. As the number can be rather large, print it modulo $ 1000000007 $ $ (10^{9}+7) $ .

## 样例 #1

### 输入

```
5
1 2 2 1 2

```

### 输出

```
120

```

## 样例 #2

### 输入

```
8
1 2 2 1 2 1 1 2

```

### 输出

```
16800

```



---

---
title: "Minesweeper 1D"
layout: "post"
diff: 普及+/提高
pid: CF404D
tag: ['模拟', '动态规划 DP']
---

# Minesweeper 1D

## 题目描述

Game "Minesweeper 1D" is played on a line of squares, the line's height is 1 square, the line's width is $ n $ squares. Some of the squares contain bombs. If a square doesn't contain a bomb, then it contains a number from 0 to 2 — the total number of bombs in adjacent squares.

For example, the correct field to play looks like that: 001\*2\*\*\*101\*. The cells that are marked with "\*" contain bombs. Note that on the correct field the numbers represent the number of bombs in adjacent cells. For example, field 2\* is not correct, because cell with value 2 must have two adjacent cells with bombs.

Valera wants to make a correct field to play "Minesweeper 1D". He has already painted a squared field with width of $ n $ cells, put several bombs on the field and wrote numbers into some cells. Now he wonders how many ways to fill the remaining cells with bombs and numbers are there if we should get a correct field in the end.

## 输入格式

The first line contains sequence of characters without spaces $ s_{1}s_{2}...\ s_{n} $ $ (1<=n<=10^{6}) $ , containing only characters "\*", "?" and digits "0", "1" or "2". If character $ s_{i} $ equals "\*", then the $ i $ -th cell of the field contains a bomb. If character $ s_{i} $ equals "?", then Valera hasn't yet decided what to put in the $ i $ -th cell. Character $ s_{i} $ , that is equal to a digit, represents the digit written in the $ i $ -th square.

## 输出格式

Print a single integer — the number of ways Valera can fill the empty cells and get a correct field.

As the answer can be rather large, print it modulo $ 1000000007 $ $ (10^{9}+7) $ .

## 说明/提示

In the first test sample you can get the following correct fields: 001\*\*1, 001\*\*\*, 001\*2\*, 001\*10.

## 样例 #1

### 输入

```
?01???

```

### 输出

```
4

```

## 样例 #2

### 输入

```
?

```

### 输出

```
2

```

## 样例 #3

### 输入

```
**12

```

### 输出

```
0

```

## 样例 #4

### 输入

```
1

```

### 输出

```
0

```



---

---
title: "Pawn"
layout: "post"
diff: 普及+/提高
pid: CF41D
tag: ['动态规划 DP']
---

# Pawn

## 题目描述

国际象棋棋盘最底行站了一个兵。 它只有两种行动方式： 向上左或向上右走。 它可以选择从最低行哪个节点开始他的旅程。

每个格子上有 $0-9$ 颗豌豆，而士兵想移动到最上一行并且积累到尽可能多的豌豆。同时，因为这个士兵必须把豌豆平均分给自己和他的 $k$ 个兄弟，他所收集到的豌豆必须是 $k+1$ 的倍数。请找到他可以收集到的最多豌豆，并确定他的操作序列。

规定士兵不能手动扔出豌豆，并且他必须捡起所到达的每一个格子的所有豌豆。

## 输入格式

第一行三个整数 $n,m,k(2 \le n,m \le 100, 0 \le k \le 10)$ 行数、列数、士兵的兄弟们。

接下来一个 $n \times m$ 的矩阵，每个元素均是 $0-9$ 的整数（不空格），描述该格的豌豆。第一行被认为是最上一行，最后一行被认为是最下一行。

## 输出格式

如果不能收集到 $k+1$ 倍数的豌豆，输出 `-1`.

否则，输出第一行一个整数，为最多豌豆数；第二行一个整数，为士兵开始移动的位置；第三行包括 $n-1$个字母 `L` 或 `R`，表示士兵的行动序列。

如果有多种收集到相同且是 $k+1$ 倍数数量的豌豆，你可以任意输出一种方案。

Translated by @Maniac丶坚果

## 样例 #1

### 输入

```
3 3 1
123
456
789

```

### 输出

```
16
2
RL

```

## 样例 #2

### 输入

```
3 3 0
123
456
789

```

### 输出

```
17
3
LR

```

## 样例 #3

### 输入

```
2 2 10
98
75

```

### 输出

```
-1

```



---

---
title: "k-Tree"
layout: "post"
diff: 普及+/提高
pid: CF431C
tag: ['动态规划 DP']
---

# k-Tree

## 题目描述

Quite recently a creative student Lesha had a lecture on trees. After the lecture Lesha was inspired and came up with the tree of his own which he called a $ k $ -tree.

A $ k $ -tree is an infinite rooted tree where:

- each vertex has exactly $ k $ children;
- each edge has some weight;
- if we look at the edges that goes from some vertex to its children (exactly $ k $ edges), then their weights will equal $ 1,2,3,...,k $ .

The picture below shows a part of a 3-tree.

 ![](https://cdn.luogu.com.cn/upload/vjudge_pic/CF431C/83eea7df0a509cbc1e6d27ff0b5f74fa2e2e451c.png)

 As soon as Dima, a good friend of Lesha, found out about the tree, he immediately wondered: "How many paths of total weight $ n $ (the sum of all weights of the edges in the path) are there, starting from the root of a $ k $ -tree and also containing at least one edge of weight at least $ d $ ?".Help Dima find an answer to his question. As the number of ways can be rather large, print it modulo $ 1000000007 $ ( $ 10^{9}+7 $ ).

## 输入格式

A single line contains three space-separated integers: $ n $ , $ k $ and $ d $ ( $ 1<=n,k<=100; $ $ 1<=d<=k $ ).

## 输出格式

Print a single integer — the answer to the problem modulo $ 1000000007 $ ( $ 10^{9}+7 $ ).

## 样例 #1

### 输入

```
3 3 2

```

### 输出

```
3

```

## 样例 #2

### 输入

```
3 3 3

```

### 输出

```
1

```

## 样例 #3

### 输入

```
4 3 2

```

### 输出

```
6

```

## 样例 #4

### 输入

```
4 5 2

```

### 输出

```
7

```



---

---
title: "Pashmak and Graph"
layout: "post"
diff: 普及+/提高
pid: CF459E
tag: ['动态规划 DP', '图论']
---

# Pashmak and Graph

## 题目描述

Pashmak's homework is a problem about graphs. Although he always tries to do his homework completely, he can't solve this problem. As you know, he's really weak at graph theory; so try to help him in solving the problem.

You are given a weighted directed graph with $ n $ vertices and $ m $ edges. You need to find a path (perhaps, non-simple) with maximum number of edges, such that the weights of the edges increase along the path. In other words, each edge of the path must have strictly greater weight than the previous edge in the path.

Help Pashmak, print the number of edges in the required path.

## 输入格式

The first line contains two integers $ n $ , $ m $ $ (2<=n<=3·10^{5}; 1<=m<=min(n·(n-1),3·10^{5})) $ . Then, $ m $ lines follows. The $ i $ -th line contains three space separated integers: $ u_{i} $ , $ v_{i} $ , $ w_{i} $ $ (1<=u_{i},v_{i}<=n; 1<=w_{i}<=10^{5}) $ which indicates that there's a directed edge with weight $ w_{i} $ from vertex $ u_{i} $ to vertex $ v_{i} $ .

It's guaranteed that the graph doesn't contain self-loops and multiple edges.

## 输出格式

Print a single integer — the answer to the problem.

## 说明/提示

In the first sample the maximum trail can be any of this trails: ![](https://cdn.luogu.com.cn/upload/vjudge_pic/CF459E/46950f7ebb1a8fb1042610e7d90ce693216dd148.png).

In the second sample the maximum trail is ![](https://cdn.luogu.com.cn/upload/vjudge_pic/CF459E/0a8ef1a8d44f73ed1581f13e754f7328cc98bdea.png).

In the third sample the maximum trail is ![](https://cdn.luogu.com.cn/upload/vjudge_pic/CF459E/077a752077571978dd842d2ca5ed7e4dcecd7b85.png).

## 样例 #1

### 输入

```
3 3
1 2 1
2 3 1
3 1 1

```

### 输出

```
1

```

## 样例 #2

### 输入

```
3 3
1 2 1
2 3 2
3 1 3

```

### 输出

```
3

```

## 样例 #3

### 输入

```
6 7
1 2 1
3 2 5
2 4 2
2 5 2
2 6 9
5 4 3
4 3 4

```

### 输出

```
6

```



---

---
title: "Gargari and Permutations"
layout: "post"
diff: 普及+/提高
pid: CF463D
tag: ['动态规划 DP']
---

# Gargari and Permutations

## 题目描述

给你k个长度为n的排列，求这些排列的最长公共子序列的长度

## 输入格式

第一行包含n(1<=n<=1000)和k(2<=k<=5)。
后面的k行分别表示k个排列。

## 输出格式

输出最长公共子序列的长度

## 说明/提示

第一个测试样本的答案是子序列[1,2,3]。

## 样例 #1

### 输入

```
4 3
1 4 2 3
4 1 2 3
1 2 4 3

```

### 输出

```
3

```



---

---
title: "George and Job"
layout: "post"
diff: 普及+/提高
pid: CF467C
tag: ['动态规划 DP', '优先队列', '前缀和']
---

# George and Job

## 题目描述

新款手机 iTone6 近期上市，George 很想买一只。不幸地，George 没有足够的钱，所以 George 打算当一名程序猿去打工。现在George遇到了一个问题。
给出一组有 $n$ 个整数的数列 $p_1,p_2,...,p_n$ ,你需要挑出 $k$ 组长度为 $m$ 的数，要求这些数互不重叠
即$ [l_{1},r_{1}],[l_{2},r_{2}],...,[l_{k},r_{k}] (1<=l_{1}<=r_{1}<l_{2}<=r_{2}<...<l_{k}<=r_{k}<=n; r_{i}-l_{i}+1=m)$
使选出的数的和值最大，请你帮助George码出这份代码

## 输入格式

第1行读入3个整数 $n , m , k(1\leq(m×k)\leq n\leq5000) (1\leq(m×k)\leq n\leq5000)$,
第2行读入 $n$ 个数 $p_1,p_2,...,p_n$

## 输出格式

输出1个整数，代表可以取到的最大值
# 输入输出样例
如原版
translated by @Venus

## 样例 #1

### 输入

```
5 2 1
1 2 3 4 5

```

### 输出

```
9

```

## 样例 #2

### 输入

```
7 1 3
2 10 7 18 5 33 0

```

### 输出

```
61

```



---

---
title: "Flowers"
layout: "post"
diff: 普及+/提高
pid: CF474D
tag: ['动态规划 DP', '前缀和']
---

# Flowers

## 题目描述

We saw the little game Marmot made for Mole's lunch. Now it's Marmot's dinner time and, as we all know, Marmot eats flowers. At every dinner he eats some red and white flowers. Therefore a dinner can be represented as a sequence of several flowers, some of them white and some of them red.

But, for a dinner to be tasty, there is a rule: Marmot wants to eat white flowers only in groups of size $ k $ .

Now Marmot wonders in how many ways he can eat between $ a $ and $ b $ flowers. As the number of ways could be very large, print it modulo $ 1000000007 $ ( $ 10^{9}+7 $ ).

## 输入格式

We saw the little game Marmot made for Mole's lunch. Now it's Marmot's dinner time and, as we all know, Marmot eats flowers. At every dinner he eats some red and white flowers. Therefore a dinner can be represented as a sequence of several flowers, some of them white and some of them red.

But, for a dinner to be tasty, there is a rule: Marmot wants to eat white flowers only in groups of size $ k $ .

Now Marmot wonders in how many ways he can eat between $ a $ and $ b $ flowers. As the number of ways could be very large, print it modulo $ 1000000007 $ ( $ 10^{9}+7 $ ).

## 输出格式

We saw the little game Marmot made for Mole's lunch. Now it's Marmot's dinner time and, as we all know, Marmot eats flowers. At every dinner he eats some red and white flowers. Therefore a dinner can be represented as a sequence of several flowers, some of them white and some of them red.

But, for a dinner to be tasty, there is a rule: Marmot wants to eat white flowers only in groups of size $ k $ .

Now Marmot wonders in how many ways he can eat between $ a $ and $ b $ flowers. As the number of ways could be very large, print it modulo $ 1000000007 $ ( $ 10^{9}+7 $ ).

## 说明/提示

- For $ K $ = $ 2 $ and length $ 1 $ Marmot can eat ( $ R $ ).
- For $ K $ = $ 2 $ and length $ 2 $ Marmot can eat ( $ RR $ ) and ( $ WW $ ).
- For $ K $ = $ 2 $ and length $ 3 $ Marmot can eat ( $ RRR $ ), ( $ RWW $ ) and ( $ WWR $ ).
- For $ K $ = $ 2 $ and length $ 4 $ Marmot can eat, for example, ( $ WWWW $ ) or ( $ RWWR $ ), but for example he can't eat ( $ WWWR $ ).

## 样例 #1

### 输入

```
3 2
1 3
2 3
4 4

```

### 输出

```
6
5
5

```



---

---
title: "Red-Green Towers"
layout: "post"
diff: 普及+/提高
pid: CF478D
tag: ['动态规划 DP', '背包 DP']
---

# Red-Green Towers

## 题目描述

你有 $r$ 块红色的积木和 $g$ 块绿色的积木，它们用于建造红绿塔。红绿塔按照下面的规则来建造：

- 红绿塔有若干层；
- 如果红绿塔有 $n$ 层，那么塔的第一层应该有 $n$ 块积木，第二层有 $n-1$ 块，第三层有 $n-2$ 块，以此类推，最后一层只有一块。换言之，每一层应该比前面一层少一块；
- 红绿塔的每一层必须使用相同颜色的积木。

令 $h$ 表示用 $r$ 个红积木和 $g$ 个绿积木所能搭建的满足上述规则的塔的最大层数。现在你的任务是确定可以建造出多少不同的有 $h$ 层的红绿塔。

如果两个红绿塔相同的一层使用的是不同的颜色，它们就被认为不同的。

你需要写一个程序来求出有多少种高度为 $h$ 的不同的红绿塔。由于答案很大，你只需要输出答案模 $10^9+7$（也就是$1000000007$）后的值。

## 输入格式

输入仅有一行，用空格隔开的两个数 $r$ 和 $g$，表示可用的红色、绿色积木的数量

## 输出格式

输出仅一行，高度为 $h$ 的不同红绿塔的个数模 $10^9+7$ 的值

**数据规模**

$0\le r,g\le 2\times 10^5$, $r+g\ge 1$

## 样例 #1

### 输入

```
4 6

```

### 输出

```
2

```

## 样例 #2

### 输入

```
9 7

```

### 输出

```
6

```

## 样例 #3

### 输入

```
1 1

```

### 输出

```
2

```



---

---
title: "Riding in a Lift"
layout: "post"
diff: 普及+/提高
pid: CF479E
tag: ['动态规划 DP', '前缀和']
---

# Riding in a Lift

## 题目描述

Imagine that you are in a building that has exactly $ n $ floors. You can move between the floors in a lift. Let's number the floors from bottom to top with integers from $ 1 $ to $ n $ . Now you're on the floor number $ a $ . You are very bored, so you want to take the lift. Floor number $ b $ has a secret lab, the entry is forbidden. However, you already are in the mood and decide to make $ k $ consecutive trips in the lift.

Let us suppose that at the moment you are on the floor number $ x $ (initially, you were on floor $ a $ ). For another trip between floors you choose some floor with number $ y $ ( $ y≠x $ ) and the lift travels to this floor. As you cannot visit floor $ b $ with the secret lab, you decided that the distance from the current floor $ x $ to the chosen $ y $ must be strictly less than the distance from the current floor $ x $ to floor $ b $ with the secret lab. Formally, it means that the following inequation must fulfill: $ |x-y|<|x-b| $ . After the lift successfully transports you to floor $ y $ , you write down number $ y $ in your notepad.

Your task is to find the number of distinct number sequences that you could have written in the notebook as the result of $ k $ trips in the lift. As the sought number of trips can be rather large, find the remainder after dividing the number by $ 1000000007 $ ( $ 10^{9}+7 $ ).

## 输入格式

The first line of the input contains four space-separated integers $ n $ , $ a $ , $ b $ , $ k $ ( $ 2<=n<=5000 $ , $ 1<=k<=5000 $ , $ 1<=a,b<=n $ , $ a≠b $ ).

## 输出格式

Print a single integer — the remainder after dividing the sought number of sequences by $ 1000000007 $ ( $ 10^{9}+7 $ ).

## 说明/提示

Imagine that you are in a building that has exactly $ n $ floors. You can move between the floors in a lift. Let's number the floors from bottom to top with integers from $ 1 $ to $ n $ . Now you're on the floor number $ a $ . You are very bored, so you want to take the lift. Floor number $ b $ has a secret lab, the entry is forbidden. However, you already are in the mood and decide to make $ k $ consecutive trips in the lift.

Let us suppose that at the moment you are on the floor number $ x $ (initially, you were on floor $ a $ ). For another trip between floors you choose some floor with number $ y $ ( $ y≠x $ ) and the lift travels to this floor. As you cannot visit floor $ b $ with the secret lab, you decided that the distance from the current floor $ x $ to the chosen $ y $ must be strictly less than the distance from the current floor $ x $ to floor $ b $ with the secret lab. Formally, it means that the following inequation must fulfill: $ |x-y|<|x-b| $ . After the lift successfully transports you to floor $ y $ , you write down number $ y $ in your notepad.

Your task is to find the number of distinct number sequences that you could have written in the notebook as the result of $ k $ trips in the lift. As the sought number of trips can be rather large, find the remainder after dividing the number by $ 1000000007 $ ( $ 10^{9}+7 $ ).

## 样例 #1

### 输入

```
5 2 4 1

```

### 输出

```
2

```

## 样例 #2

### 输入

```
5 2 4 2

```

### 输出

```
2

```

## 样例 #3

### 输入

```
5 3 4 1

```

### 输出

```
0

```



---

---
title: "Mr. Kitayuta, the Treasure Hunter"
layout: "post"
diff: 普及+/提高
pid: CF505C
tag: ['动态规划 DP', '枚举']
---

# Mr. Kitayuta, the Treasure Hunter

## 题目描述

The Shuseki Islands are an archipelago of $ 30001 $ small islands in the Yutampo Sea. The islands are evenly spaced along a line, numbered from $ 0 $ to $ 30000 $ from the west to the east. These islands are known to contain many treasures. There are $ n $ gems in the Shuseki Islands in total, and the $ i $ -th gem is located on island $ p_{i} $ .

Mr. Kitayuta has just arrived at island $ 0 $ . With his great jumping ability, he will repeatedly perform jumps between islands to the east according to the following process:

- First, he will jump from island $ 0 $ to island $ d $ .
- After that, he will continue jumping according to the following rule. Let $ l $ be the length of the previous jump, that is, if his previous jump was from island $ prev $ to island $ cur $ , let $ l=cur-prev $ . He will perform a jump of length $ l-1 $ , $ l $ or $ l+1 $ to the east. That is, he will jump to island $ (cur+l-1) $ , $ (cur+l) $ or $ (cur+l+1) $ (if they exist). The length of a jump must be positive, that is, he cannot perform a jump of length $ 0 $ when $ l=1 $ . If there is no valid destination, he will stop jumping.

Mr. Kitayuta will collect the gems on the islands visited during the process. Find the maximum number of gems that he can collect.

## 输入格式

The first line of the input contains two space-separated integers $ n $ and $ d $ ( $ 1<=n,d<=30000 $ ), denoting the number of the gems in the Shuseki Islands and the length of the Mr. Kitayuta's first jump, respectively.

The next $ n $ lines describe the location of the gems. The $ i $ -th of them ( $ 1<=i<=n $ ) contains a integer $ p_{i} $ ( $ d<=p_{1}<=p_{2}<=...<=p_{n}<=30000 $ ), denoting the number of the island that contains the $ i $ -th gem.

## 输出格式

Print the maximum number of gems that Mr. Kitayuta can collect.

## 说明/提示

In the first sample, the optimal route is 0 $ → $ 10 (+1 gem) $ → $ 19 $ → $ 27 (+2 gems) $ →...&#x1; $

In the second sample, the optimal route is 0 $ → $ 8 $ → $ 15 $ → $ 21 $ → $ 28 (+1 gem) $ → $ 36 (+1 gem) $ → $ 45 (+1 gem) $ → $ 55 (+1 gem) $ → $ 66 (+1 gem) $ → $ 78 (+1 gem) $ →... $

In the third sample, the optimal route is 0 $ → $ 7 $ → $ 13 $ → $ 18 (+1 gem) $ → $ 24 (+2 gems) $ → $ 30 (+1 gem) $ →... $

## 样例 #1

### 输入

```
4 10
10
21
27
27

```

### 输出

```
3

```

## 样例 #2

### 输入

```
8 8
9
19
28
36
45
55
66
78

```

### 输出

```
6

```

## 样例 #3

### 输入

```
13 7
8
8
9
16
17
17
18
21
23
24
24
26
30

```

### 输出

```
4

```



---

---
title: "Fox And Jumping"
layout: "post"
diff: 普及+/提高
pid: CF510D
tag: ['动态规划 DP', '枚举', '背包 DP', '最大公约数 gcd']
---

# Fox And Jumping

## 题目描述

Fox Ciel is playing a game. In this game there is an infinite long tape with cells indexed by integers (positive, negative and zero). At the beginning she is standing at the cell 0.

There are also $ n $ cards, each card has 2 attributes: length $ l_{i} $ and cost $ c_{i} $ . If she pays $ c_{i} $ dollars then she can apply $ i $ -th card. After applying $ i $ -th card she becomes able to make jumps of length $ l_{i} $ , i. e. from cell $ x $ to cell $ (x-l_{i}) $ or cell $ (x+l_{i}) $ .

She wants to be able to jump to any cell on the tape (possibly, visiting some intermediate cells). For achieving this goal, she wants to buy some cards, paying as little money as possible.

If this is possible, calculate the minimal cost.

## 输入格式

The first line contains an integer $ n $ ( $ 1<=n<=300 $ ), number of cards.

The second line contains $ n $ numbers $ l_{i} $ ( $ 1<=l_{i}<=10^{9} $ ), the jump lengths of cards.

The third line contains $ n $ numbers $ c_{i} $ ( $ 1<=c_{i}<=10^{5} $ ), the costs of cards.

## 输出格式

If it is impossible to buy some cards and become able to jump to any cell, output -1. Otherwise output the minimal cost of buying such set of cards.

## 说明/提示

In first sample test, buying one card is not enough: for example, if you buy a card with length 100, you can't jump to any cell whose index is not a multiple of 100. The best way is to buy first and second card, that will make you be able to jump to any cell.

In the second sample test, even if you buy all cards, you can't jump to any cell whose index is not a multiple of 10, so you should output -1.

## 样例 #1

### 输入

```
3
100 99 9900
1 1 1

```

### 输出

```
2

```

## 样例 #2

### 输入

```
5
10 20 30 40 50
1 1 1 1 1

```

### 输出

```
-1

```

## 样例 #3

### 输入

```
7
15015 10010 6006 4290 2730 2310 1
1 1 1 1 1 1 10

```

### 输出

```
6

```

## 样例 #4

### 输入

```
8
4264 4921 6321 6984 2316 8432 6120 1026
4264 4921 6321 6984 2316 8432 6120 1026

```

### 输出

```
7237

```



---

---
title: "Amr and Chemistry"
layout: "post"
diff: 普及+/提高
pid: CF558C
tag: ['动态规划 DP', '贪心', '枚举', '进制', '字典树 Trie']
---

# Amr and Chemistry

## 题目描述

Amr loves Chemistry, and specially doing experiments. He is preparing for a new interesting experiment.

Amr has $ n $ different types of chemicals. Each chemical $ i $ has an initial volume of $ a_{i} $ liters. For this experiment, Amr has to mix all the chemicals together, but all the chemicals volumes must be equal first. So his task is to make all the chemicals volumes equal.

To do this, Amr can do two different kind of operations.

- Choose some chemical $ i $ and double its current volume so the new volume will be $ 2a_{i} $
- Choose some chemical $ i $ and divide its volume by two (integer division) so the new volume will be ![](https://cdn.luogu.com.cn/upload/vjudge_pic/CF558C/2af906789c62f9845274f856d2f941f2357aa169.png)

Suppose that each chemical is contained in a vessel of infinite volume. Now Amr wonders what is the minimum number of operations required to make all the chemicals volumes equal?

## 输入格式

The first line contains one number $ n $ ( $ 1<=n<=10^{5} $ ), the number of chemicals.

The second line contains $ n $ space separated integers $ a_{i} $ ( $ 1<=a_{i}<=10^{5} $ ), representing the initial volume of the $ i $ -th chemical in liters.

## 输出格式

Output one integer the minimum number of operations required to make all the chemicals volumes equal.

## 说明/提示

In the first sample test, the optimal solution is to divide the second chemical volume by two, and multiply the third chemical volume by two to make all the volumes equal $ 4 $ .

In the second sample test, the optimal solution is to divide the first chemical volume by two, and divide the second and the third chemical volumes by two twice to make all the volumes equal $ 1 $ .

## 样例 #1

### 输入

```
3
4 8 2

```

### 输出

```
2
```

## 样例 #2

### 输入

```
3
3 5 6

```

### 输出

```
5
```



---

---
title: "Clique in the Divisibility Graph"
layout: "post"
diff: 普及+/提高
pid: CF566F
tag: ['动态规划 DP']
---

# Clique in the Divisibility Graph

## 题目描述

As you must know, the maximum clique problem in an arbitrary graph is $ NP $ -hard. Nevertheless, for some graphs of specific kinds it can be solved effectively.

Just in case, let us remind you that a clique in a non-directed graph is a subset of the vertices of a graph, such that any two vertices of this subset are connected by an edge. In particular, an empty set of vertexes and a set consisting of a single vertex, are cliques.

Let's define a divisibility graph for a set of positive integers $ A={a_{1},a_{2},...,a_{n}} $ as follows. The vertices of the given graph are numbers from set $ A $ , and two numbers $ a_{i} $ and $ a_{j} $ ( $ i≠j $ ) are connected by an edge if and only if either $ a_{i} $ is divisible by $ a_{j} $ , or $ a_{j} $ is divisible by $ a_{i} $ .

You are given a set of non-negative integers $ A $ . Determine the size of a maximum clique in a divisibility graph for set $ A $ .

## 输入格式

The first line contains integer $ n $ ( $ 1<=n<=10^{6} $ ), that sets the size of set $ A $ .

The second line contains $ n $ distinct positive integers $ a_{1},a_{2},...,a_{n} $ ( $ 1<=a_{i}<=10^{6} $ ) — elements of subset $ A $ . The numbers in the line follow in the ascending order.

## 输出格式

Print a single number — the maximum size of a clique in a divisibility graph for set $ A $ .

## 说明/提示

In the first sample test a clique of size 3 is, for example, a subset of vertexes $ {3,6,18} $ . A clique of a larger size doesn't exist in this graph.

## 样例 #1

### 输入

```
8
3 4 6 8 10 18 21 24

```

### 输出

```
3

```



---

---
title: "Kefa and Dishes"
layout: "post"
diff: 普及+/提高
pid: CF580D
tag: ['动态规划 DP', '枚举', '状态合并']
---

# Kefa and Dishes

## 题目描述

$\texttt{songshe}$ 进入了一家餐厅，这家餐厅中有 $n\ (1\leqslant n\leqslant18)$ 个菜。$\texttt{songshe}$ 对第 $i$ 个菜的满意度为 $a_i\ (0\leqslant a_i\leqslant10^9)$。

对于这 $n$ 个菜，有 $k\ (0\leqslant k\leqslant n^2-n)$ 条规则：如果 $\texttt{songshe}$ 在吃完第 $x_i$ 个菜之后立刻吃了第 $y_i\ (x_i\neq y_i)$ 个菜，那么会额外获得 $c_i\ (0\leqslant c_i\leqslant10^9)$ 的满意度。

$\texttt{songshe}$ 要吃 $m\ (1\leqslant m\leqslant n)$ 道任意的菜，但是他希望自己吃菜的顺序得到的满意度最大，请你帮 $\texttt{songshe}$ 解决这个问题。

## 输入格式

第 $1$ 行包含三个整数 $n,m,k$。

第 $2$ 行 $n$ 个非负整数，第 $i$ 个数表示 $\texttt{songshe}$ 对第 $i$ 道菜的满意度为 $a_i$。

若 $k\neq0$，第 $3$ 行到第 $k+2$ 行每行 $3$ 个整数 $x_i,y_i,c_i$，含义见上文。

## 输出格式

一行一个整数，表示最大满意度。

## 样例 #1

### 输入

```
2 2 1
1 1
2 1 1

```

### 输出

```
3

```

## 样例 #2

### 输入

```
4 3 2
1 2 3 4
2 1 5
3 4 2

```

### 输出

```
12

```



---

---
title: "Sweets Game"
layout: "post"
diff: 普及+/提高
pid: CF63E
tag: ['动态规划 DP', '搜索', '博弈论', '记忆化搜索']
---

# Sweets Game

## 题目描述

Karlsson has visited Lillebror again. They found a box of chocolates and a big whipped cream cake at Lillebror's place. Karlsson immediately suggested to divide the sweets fairly between Lillebror and himself. Specifically, to play together a game he has just invented with the chocolates. The winner will get the cake as a reward.

The box of chocolates has the form of a hexagon. It contains 19 cells for the chocolates, some of which contain a chocolate. The players move in turns. During one move it is allowed to eat one or several chocolates that lay in the neighboring cells on one line, parallel to one of the box's sides. The picture below shows the examples of allowed moves and of an unacceptable one. The player who cannot make a move loses.

 ![](https://cdn.luogu.com.cn/upload/vjudge_pic/CF63E/d39dc87a25b4bbc8e9ef90055ec2e2d8c38df358.png)Karlsson makes the first move as he is Lillebror's guest and not vice versa. The players play optimally. Determine who will get the cake.

## 输入格式

The input data contains 5 lines, containing 19 words consisting of one symbol. The word "O" means that the cell contains a chocolate and a "." stands for an empty cell. It is guaranteed that the box contains at least one chocolate. See the examples for better understanding.

## 输出格式

If Karlsson gets the cake, print "Karlsson" (without the quotes), otherwise print "Lillebror" (yet again without the quotes).

## 样例 #1

### 输入

```
  . . .
 . . O .
. . O O .
 . . . .
  . . .

```

### 输出

```
Lillebror
```

## 样例 #2

### 输入

```
  . . .
 . . . O
. . . O .
 O . O .
  . O .

```

### 输出

```
Karlsson
```



---

---
title: "Petya and Post"
layout: "post"
diff: 普及+/提高
pid: CF66E
tag: ['动态规划 DP', '线段树', '枚举']
---

# Petya and Post

## 题目描述

### 题意翻译

有 $n$ 个邮局，在每个邮局都有一个加油站。（邮局编号从 $1$ 开始）

对于第 $i$ 个邮局，$a_i$ 表示位于这个邮局加油站最多能加多少油，$b_i$ 表示它到第 $i+1$ 个邮局会耗费多少油。特殊的，对于第 $n$ 个邮局，$b_n$ 表示它到第 $1$ 个邮局会耗费多少油。

现在可以任意选择一个邮局出发，开始的油量为 $0$。可以选择顺时针或者逆时针走动，一旦决定方向就不可以回头。 要求路途上任一时刻油量$\ge 0$。

## 输入格式

第一行一个正整数 $n$。

第二行 $n$ 个正整数表示 $a$。

第三行 $n$ 个正整数表示 $b$。

## 输出格式

第一行一个正整数 $res$，表示有多少个邮局出发可以回到自己。

第二行 $res$ 个正整数，从小到大的输出这些可以回到自己的邮局的编号。

### 数据规模

$1 \le n \le 10^5$。

$\sum\limits_{i=1}^n a_i$ 不超过 $10^9$。

$\sum\limits_{i=1}^n b_i$ 不超过 $10^9$。

## 样例 #1

### 输入

```
4
1 7 2 3
8 1 1 3

```

### 输出

```
2
2 4

```

## 样例 #2

### 输入

```
8
1 2 1 2 1 2 1 2
2 1 2 1 2 1 2 1

```

### 输出

```
8
1 2 3 4 5 6 7 8

```



---

---
title: "Journey"
layout: "post"
diff: 普及+/提高
pid: CF721C
tag: ['动态规划 DP']
---

# Journey

## 题目描述

Recently Irina arrived to one of the most famous cities of Berland — the Berlatov city. There are $ n $ showplaces in the city, numbered from $ 1 $ to $ n $ , and some of them are connected by one-directional roads. The roads in Berlatov are designed in a way such that there are no cyclic routes between showplaces.

Initially Irina stands at the showplace $ 1 $ , and the endpoint of her journey is the showplace $ n $ . Naturally, Irina wants to visit as much showplaces as she can during her journey. However, Irina's stay in Berlatov is limited and she can't be there for more than $ T $ time units.

Help Irina determine how many showplaces she may visit during her journey from showplace $ 1 $ to showplace $ n $ within a time not exceeding $ T $ . It is guaranteed that there is at least one route from showplace $ 1 $ to showplace $ n $ such that Irina will spend no more than $ T $ time units passing it.

## 输入格式

The first line of the input contains three integers $ n,m $ and $ T $ ( $ 2<=n<=5000,1<=m<=5000,1<=T<=10^{9} $ ) — the number of showplaces, the number of roads between them and the time of Irina's stay in Berlatov respectively.

The next $ m $ lines describes roads in Berlatov. $ i $ -th of them contains $ 3 $ integers $ u_{i},v_{i},t_{i} $ ( $ 1<=u_{i},v_{i}<=n,u_{i}≠v_{i},1<=t_{i}<=10^{9} $ ), meaning that there is a road starting from showplace $ u_{i} $ and leading to showplace $ v_{i} $ , and Irina spends $ t_{i} $ time units to pass it. It is guaranteed that the roads do not form cyclic routes.

It is guaranteed, that there is at most one road between each pair of showplaces.

## 输出格式

Print the single integer $ k $ ( $ 2<=k<=n $ ) — the maximum number of showplaces that Irina can visit during her journey from showplace $ 1 $ to showplace $ n $ within time not exceeding $ T $ , in the first line.

Print $ k $ distinct integers in the second line — indices of showplaces that Irina will visit on her route, in the order of encountering them.

If there are multiple answers, print any of them.

## 样例 #1

### 输入

```
4 3 13
1 2 5
2 3 7
2 4 8

```

### 输出

```
3
1 2 4 

```

## 样例 #2

### 输入

```
6 6 7
1 2 2
1 3 3
3 6 3
2 4 2
4 6 2
6 5 1

```

### 输出

```
4
1 2 4 6 

```

## 样例 #3

### 输入

```
5 5 6
1 3 3
3 5 3
1 2 2
2 4 3
4 5 2

```

### 输出

```
3
1 3 5 

```



---

---
title: "Garland"
layout: "post"
diff: 普及+/提高
pid: CF767C
tag: ['动态规划 DP', '剪枝', '树形 DP']
---

# Garland

## 题目描述

Once at New Year Dima had a dream in which he was presented a fairy garland. A garland is a set of lamps, some pairs of which are connected by wires. Dima remembered that each two lamps in the garland were connected directly or indirectly via some wires. Furthermore, the number of wires was exactly one less than the number of lamps.

There was something unusual about the garland. Each lamp had its own brightness which depended on the temperature of the lamp. Temperatures could be positive, negative or zero. Dima has two friends, so he decided to share the garland with them. He wants to cut two different wires so that the garland breaks up into three parts. Each part of the garland should shine equally, i. e. the sums of lamps' temperatures should be equal in each of the parts. Of course, each of the parts should be non-empty, i. e. each part should contain at least one lamp.

 ![](https://cdn.luogu.com.cn/upload/vjudge_pic/CF767C/c2b0d1858f505d34921dc11648298e7a84c2f7b5.png)Help Dima to find a suitable way to cut the garland, or determine that this is impossible.

While examining the garland, Dima lifted it up holding by one of the lamps. Thus, each of the lamps, except the one he is holding by, is now hanging on some wire. So, you should print two lamp ids as the answer which denote that Dima should cut the wires these lamps are hanging on. Of course, the lamp Dima is holding the garland by can't be included in the answer.

## 输入格式

The first line contains single integer $ n $ ( $ 3<=n<=10^{6} $ ) — the number of lamps in the garland.

Then $ n $ lines follow. The $ i $ -th of them contain the information about the $ i $ -th lamp: the number lamp $ a_{i} $ , it is hanging on (and $ 0 $ , if is there is no such lamp), and its temperature $ t_{i} $ ( $ -100<=t_{i}<=100 $ ). The lamps are numbered from $ 1 $ to $ n $ .

## 输出格式

If there is no solution, print -1.

Otherwise print two integers — the indexes of the lamps which mean Dima should cut the wires they are hanging on. If there are multiple answers, print any of them.

## 说明/提示

The garland and cuts scheme for the first example:

 ![](https://cdn.luogu.com.cn/upload/vjudge_pic/CF767C/578d2b3356505b1b3987876ed70f57ef1ae0c5b0.png)

## 样例 #1

### 输入

```
6
2 4
0 5
4 2
2 1
1 1
4 2

```

### 输出

```
1 4

```

## 样例 #2

### 输入

```
6
2 4
0 6
4 2
2 1
1 1
4 2

```

### 输出

```
-1

```



---

---
title: "Round Subset"
layout: "post"
diff: 普及+/提高
pid: CF837D
tag: ['动态规划 DP', '背包 DP']
---

# Round Subset

## 题目描述

我们把一个数的 roundness 值定义为它末尾 $0$ 的个数。

给你一个长度为 $n$ 的数列，要求你从中选出 $k$ 个数，使得这些选出的数的积的 roundness 值最大。

## 输入格式

第一行包括两个正整数 $n$ 和 $k$（$1 \leq n \leq 200$，$1 \leq k \leq n$）。

第二行包括 $n$ 个空白分隔的数 $a_1,a_2,\ldots,a_n$（$1 \leq a_i \leq 10^{18}$）。

## 输出格式

输出一个整数，是选择 $k$ 个数并作积的最大 roundness 值。

## 样例解释

在第一个例子中，有三种选法。$[50,4]$ 的积是 $200$，roundness 值是 $2$；$[4,20]$ 的积是 $80$，roundness 值是 $1$；$[50,20]$ 的积是 $1000$，roundness 值是 $3$。

第二个例子中选法 $[15,16,25]$ 的积是 $6000$，roundness 值是 $3$。

第三个例子中所有的选法的积的 roundness 值都是 $0$。

translated by @poorpool

## 样例 #1

### 输入

```
3 2
50 4 20

```

### 输出

```
3

```

## 样例 #2

### 输入

```
5 3
15 16 3 25 9

```

### 输出

```
3

```

## 样例 #3

### 输入

```
3 3
9 77 13

```

### 输出

```
0

```



---

---
title: "How many trees?"
layout: "post"
diff: 普及+/提高
pid: CF9D
tag: ['动态规划 DP', '枚举']
---

# How many trees?

## 题目描述

In one very old text file there was written Great Wisdom. This Wisdom was so Great that nobody could decipher it, even Phong — the oldest among the inhabitants of Mainframe. But still he managed to get some information from there. For example, he managed to learn that User launches games for pleasure — and then terrible Game Cubes fall down on the city, bringing death to those modules, who cannot win the game...

For sure, as guard Bob appeared in Mainframe many modules stopped fearing Game Cubes. Because Bob (as he is alive yet) has never been defeated by User, and he always meddles with Game Cubes, because he is programmed to this.

However, unpleasant situations can happen, when a Game Cube falls down on Lost Angles. Because there lives a nasty virus — Hexadecimal, who is... mmm... very strange. And she likes to play very much. So, willy-nilly, Bob has to play with her first, and then with User.

This time Hexadecimal invented the following entertainment: Bob has to leap over binary search trees with $ n $ nodes. We should remind you that a binary search tree is a binary tree, each node has a distinct key, for each node the following is true: the left sub-tree of a node contains only nodes with keys less than the node's key, the right sub-tree of a node contains only nodes with keys greater than the node's key. All the keys are different positive integer numbers from $ 1 $ to $ n $ . Each node of such a tree can have up to two children, or have no children at all (in the case when a node is a leaf).

In Hexadecimal's game all the trees are different, but the height of each is not lower than $ h $ . In this problem «height» stands for the maximum amount of nodes on the way from the root to the remotest leaf, the root node and the leaf itself included. When Bob leaps over a tree, it disappears. Bob gets the access to a Cube, when there are no trees left. He knows how many trees he will have to leap over in the worst case. And you?

## 输入格式

The input data contains two space-separated positive integer numbers $ n $ and $ h $ ( $ n<=35 $ , $ h<=n $ ).

## 输出格式

Output one number — the answer to the problem. It is guaranteed that it does not exceed $ 9·10^{18} $ .

## 样例 #1

### 输入

```
3 2

```

### 输出

```
5
```

## 样例 #2

### 输入

```
3 3

```

### 输出

```
4
```



---

