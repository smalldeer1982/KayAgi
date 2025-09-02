---
title: "RATAR - Ratar"
layout: "post"
diff: 省选/NOI-
pid: SP16180
tag: ['枚举', '前缀和', '概率论']
---

# RATAR - Ratar

## 题目描述

Unexpected problems with law enforcement have convinced Mirko to take up a less lucrative but less

## 输入格式

The first line of input contains the positive integer N (1

land plot.

Each of the following N lines contains N space-separated numbers Aij (-1000 < Aij < 1000), the income

provided by the respective cell.

## 输出格式

The first and only line of output must contain the total number of plot pairs satisfying the given

condition.

## 样例 #1

### 输入

```
3

1 2 3

2 3 4

3 4 8
```

### 输出

```
7
```



---

---
title: "QTREE6 - Query on a tree VI"
layout: "post"
diff: 省选/NOI-
pid: SP16549
tag: ['枚举', '连通块', '动态树 LCT']
---

# QTREE6 - Query on a tree VI

## 题目描述

给你一棵 $n$ 个点的树，编号 $1\sim n$。每个点可以是黑色，可以是白色。初始时所有点都是黑色。下面有两种操作：

* `0 u`：询问有多少个节点 $v$ 满足路径 $u$ 到 $v$ 上所有节点（包括 $u$）都拥有相同的颜色。

* `1 u`：翻转 $u$ 的颜色。

## 输入格式

第一行一个整数 $n(1\le n\le 10^5)$。

接下来 $n-1$ 行，每行两个整数表示一条边。

接下来一行一个整数 $m(1\le m\le 10^5)$ 表示操作次数。

接下来 $m$ 行，每行两个整数分别表示操作类型和被操作节点。

## 输出格式

对每个询问操作输出相应的结果。

## 样例 #1

### 输入

```
5
1 2
1 3
1 4
1 5
3
0 1
1 1
0 1
```

### 输出

```
5
1
```



---

---
title: "MOD - Power Modulo Inverted"
layout: "post"
diff: 省选/NOI-
pid: SP3105
tag: ['枚举', '分块']
---

# MOD - Power Modulo Inverted

## 题目描述

Given 3 positive integers _x_, _y_ and _z_, you can find _k = x $ ^{y} $ %z_ easily, by fast power-modulo algorithm. Now your task is the inverse of this algorithm. Given 3 positive integers _x_, _z_ and _k_, find the smallest non-negative integer _y_, such that _k%z = x $ ^{y} $ %z_.

## 输入格式

About 600 test cases.

Each test case contains one line with 3 integers _x_, _z_ and _k_.(1<= _x_, _z_, _k_ <=10 $ ^{9} $ )

Input terminates by three zeroes.

## 输出格式

For each test case, output one line with the answer, or "No Solution"(without quotes) if such an integer doesn't exist.

## 样例 #1

### 输入

```
5 58 33
2 4 3
0 0 0
```

### 输出

```
9
No Solution
```



---

---
title: "PAGAIN - Prime Again"
layout: "post"
diff: 省选/NOI-
pid: SP3587
tag: ['数学', '枚举']
---

# PAGAIN - Prime Again

## 题目描述

[English](/problems/PAGAIN/en/) [Vietnamese](/problems/PAGAIN/vn/)In this problem, you have to find the nearest prime number smaller than N. (3 <= N <= 2^32)

## 输入格式

The first line contains an integer T specifying the number of test cases. (T <= 10000)

T lines follow, each line contains an integer N.

## 输出格式

For each test case, output the result on one line.

## 样例 #1

### 输入

```
3

5 

10

17
```

### 输出

```
3

7

13
```



---

---
title: "LPERMUT - Longest Permutation"
layout: "post"
diff: 省选/NOI-
pid: SP744
tag: ['莫队', '枚举', '可持久化线段树']
---

# LPERMUT - Longest Permutation

## 题目描述

You are given a sequence A of n integer numbers (1<=A $ _{i} $ <=n). A subsequence of A has the form A $ _{u} $ , A $ _{u+1} $ ... , A $ _{v} $ (1<=u<=v<=n). We are interested in subsequences that are permutations of 1, 2, .., k (k is the length of the subsequence).

 Your task is to find the longest subsequence of this type.

## 输入格式

- Line 1: n (1<=n<=100000)
- Line 2: n numbers A $ _{1} $ , A $ _{2} $ , ... ,A $ _{n} $ (1<=A $ _{i} $ <=n)

## 输出格式

A single integer that is the length of the longest permutation

## 样例 #1

### 输入

```
5

4 1 3 1 2
```

### 输出

```
3
```



---

