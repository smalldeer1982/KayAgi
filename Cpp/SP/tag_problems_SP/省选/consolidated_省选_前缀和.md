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
title: "NORMA2 - Norma"
layout: "post"
diff: 省选/NOI-
pid: SP22343
tag: ['分治', '前缀和', '概率论']
---

# NORMA2 - Norma

## 题目描述

Mirko got an array of integers for his birthday from his grandmother Norma. As any other kid, he was hoping for some money, but got an array. Luckily, in his town there is a pawn shop that buys up arrays. The cost of an array of integers is **min** \* **max** \* **L** kunas, where **min** is the minimal integer in the array, **max** is the maximal and **L** is the array length. Mirko is going to sell a subsequence of consecutive numbers from his array. He calculated the average price of all such subsequences.

In order to check his result, he wants you to do the same. He will be pleased with only the last 9 digits of the sum of all prices, so you don’t need to bother with large and real numbers.

## 输入格式

The first line of input contains an integer N (1

Each of the following N lines contains a member of Mirko’s array. The members of the array will be integers from the interval \[1, 10 $ ^{8} $ \].

## 输出格式

The first and only line of output must contain an integer, the last 9 digits of the required sum from the task. **You don’t need to output** the leading zeroes of that 9-digit integer.

## 样例 #1

### 输入

```
2\n1\n3 
```

### 输出

```
16
```



---

---
title: "GSS5 - Can you answer these queries V"
layout: "post"
diff: 省选/NOI-
pid: SP2916
tag: ['线段树', '前缀和']
---

# GSS5 - Can you answer these queries V

## 题目描述

 You are given a sequence A\[1\], A\[2\], ..., A\[N\] . ( |A\[i\]| <= 10000 , 1 <= N <= 10000 ). A query is defined as follows: Query(x1,y1,x2,y2) = Max { A\[i\]+A\[i+1\]+...+A\[j\] ; x1 <= i <= y1 , x2 <= j <= y2 and x1 <= x2 , y1 <= y2 }. Given M queries (1 <= M <= 10000), your program must output the results of these queries.

## 输入格式

 The first line of the input consist of the number of tests cases <= 5. Each case consist of the integer N and the sequence A. Then the integer M. M lines follow, contains 4 numbers x1, y1, x2 y2.

## 输出格式

 Your program should output the results of the M queries for each test case, one query per line.

## 样例 #1

### 输入

```
2
6 3 -2 1 -4 5 2
2
1 1 2 3
1 3 2 5
1 1
1
1 1 1 1
```

### 输出

```
2
3
1
```



---

