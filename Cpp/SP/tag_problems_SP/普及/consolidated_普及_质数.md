---
title: "SNGPG - Prime Generator The Easiest Question Ever"
layout: "post"
diff: 普及/提高-
pid: SP15891
tag: ['数论', '素数判断,质数,筛法']
---

# SNGPG - Prime Generator The Easiest Question Ever

## 题目描述

给定区间 $[a, b]$，求该区间中满足 $p^2 + 1$ 或 $p^2 + 2$ 为质数的质数 $p$ 的数量。特别地，我们认为 $0$ 和 $1$ 也为质数。

## 输入格式

**本题有多组测试数据。**

第一行，一个整数 $T$，表示数据组数。

对于每组数据：

一行，两个整数 $a, b$。

## 输出格式

对于每组数据，输出一行，一个整数，表示所求的值。
### 输入输出样例
#### 输入 #1
```
2
0 1
4 5
```
#### 输出 #1
```
2
0
```

## 说明/提示

对于 $100\%$ 的数据，$1 \leq T < 100$，$0 \leq a \leq 5 \times 10^4$，$1 \leq b \leq 10^5$，$a < b$。

## 样例 #1

### 输入

```
2\n0 1\n4 5
```

### 输出

```
2\n0\n\n[Consider 0 and 1 as prime numbers for this question]
```



---

---
title: "ARRPRM - Prime is fun"
layout: "post"
diff: 普及/提高-
pid: SP30394
tag: ['动态规划 DP', '素数判断,质数,筛法', '前缀和']
---

# ARRPRM - Prime is fun

## 题目描述

给定一个长为 $n$ 的序列 $a$，从 $a$ 中选出若干个互不相连的长度均为质数的连续段，使这些连续段中的数的和最大。

## 输入格式

**本题有多组测试数据。**

第一行，一个整数 $T$，表示数据组数。

对于每组数据：

第一行，一个整数 $n$；

第二行，$n$ 个整数 $a_1, a_2, \cdots, a_n$。

## 输出格式

对于每组数据：

一行，一个整数，表示所求的值。
### 输入输出样例
#### 输入 #1
```
2
4
1 2 3 4
10
10 1 1 1 1 1 1 2 2 2
```
#### 输出 #1
```
9
21
```

## 说明/提示

对于 $100\%$ 的数据，$1 \leq T \leq 100$，$1 \leq n \leq 2 \times 10^3$，$1 \leq a_i \leq 10^6$。



---

---
title: "TDKPRIME - Finding the Kth Prime"
layout: "post"
diff: 普及/提高-
pid: SP6470
tag: ['数学', '素数判断,质数,筛法']
---

# TDKPRIME - Finding the Kth Prime

## 题目描述

The problem statement is really simple. There are some queries. You are to give the answers.

## 输入格式

An integer stating the number of queries Q(equal to 50000), and Q lines follow, each containing one integer K between 1 and 5000000 inclusive.

## 输出格式

Q lines with the answer of each query: the Kth prime number.

## 样例 #1

### 输入

```
7

1

10

100

1000

10000

100000

1000000
```

### 输出

```
2

29

541

7919

104729

1299709

15485863
```



---

---
title: "NOSQ - No Squares Numbers"
layout: "post"
diff: 普及/提高-
pid: SP8496
tag: ['枚举', '素数判断,质数,筛法']
---

# NOSQ - No Squares Numbers

## 题目描述

A square free number is defined as a number which is not divisible by any square number.

For example, 13, 15, 210 are square free numbers, where as 25 (divisible by 5\*5), 108 (divisible by 6\*6), 18 (divisible by 3\*3) are not square free numbers. However number 1 is not considered to be a square and is a squarefree number.

Now you must find how many numbers from number a to b, are square free and also have a digit d inside it.

For example for in the range 10 to 40 te squarefree numbers having digit 3 are 13, 23, 30, 31, 33, 34, 35, 37, 38, 39

## 输入格式

The first line contains an integer T, which is the number of test-cases

Then follow T lines, each containing 3 integers a, b and d.

1 <= T <= 20,000

1 <= a <= b <= 100,000

0 <= d <= 9

## 输出格式

Print one integer which is the required number as described in the problem statement.

## 样例 #1

### 输入

```
3
10 40 3
1 100 4
1 100000 7
```

### 输出

```
10
9
26318
```



---

