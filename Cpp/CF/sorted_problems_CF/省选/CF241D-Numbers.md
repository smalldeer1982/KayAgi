---
title: "Numbers"
layout: "post"
diff: 省选/NOI-
pid: CF241D
tag: ['搜索']
---

# Numbers

## 题目描述

You have a sequence of $ n $ distinct integers $ a_{1},a_{2},...,a_{n} $ $ (1<=a_{i}<=n) $ . You want to remove some integers in such a way that the resulting sequence of integers satisfies the following three conditions:

1. the resulting sequence is not empty;
2. the exclusive or ( $ xor $ operation) of all the integers in the resulting sequence equals $ 0 $ ;
3. if you write all the integers of the resulting sequence (from beginning to the end) in a row in the decimal numeral system and without any spaces, the written number is divisible by $ p $ .

You are given the sequence of $ n $ integers $ a $ and a prime number $ p $ , find a way to satisfy the described conditions.

## 输入格式

The first line of the input contains two integers $ n $ and $ p $ $ (1<=n,p<=50000) $ . Next line contains $ n $ space-separated distinct integers $ a_{1},a_{2},...,a_{n} $ $ (1<=a_{i}<=n) $ .

It is guaranteed that $ p $ is a prime number.

## 输出格式

If there is no solution for the given input, print "No" (without quotes) in the only line of the output.

Otherwise print "Yes" in the first line of output. The second line should contain an integer $ k $ $ (k&gt;0) $ specifying the number of remaining elements and the third line should contain $ k $ distinct integers $ x_{1},x_{2},...,x_{k} $ $ (1<=x_{i}<=n) $ . These integers mean that you should remove all integers from the sequence except integers $ a_{x1},a_{x2},...,a_{xk} $ to satisfy the described conditions.

If there are multiple solutions, any of them will be accepted.

## 样例 #1

### 输入

```
3 3
1 2 3

```

### 输出

```
Yes
3
1 2 3 

```

## 样例 #2

### 输入

```
3 5
1 2 3

```

### 输出

```
No

```

