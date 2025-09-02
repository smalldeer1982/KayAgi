---
title: "Make It Permutation"
layout: "post"
diff: 普及/提高-
pid: CF1810C
tag: []
---

# Make It Permutation

## 题目描述

You have an integer array $ a $ of length $ n $ . There are two kinds of operations you can make.

- Remove an integer from $ a $ . This operation costs $ c $ .
- Insert an arbitrary positive integer $ x $ to any position of $ a $ (to the front, to the back, or between any two consecutive elements). This operation costs $ d $ .

You want to make the final array a permutation of any positive length. Please output the minimum cost of doing that. Note that you can make the array empty during the operations, but the final array must contain at least one integer.

A permutation of length $ n $ is an array consisting of $ n $ distinct integers from $ 1 $ to $ n $ in arbitrary order. For example, $ [2,3,1,5,4] $ is a permutation, but $ [1,2,2] $ is not a permutation ( $ 2 $ appears twice in the array), and $ [1,3,4] $ is also not a permutation ( $ n=3 $ but there is $ 4 $ in the array).

## 输入格式

Each test contains multiple test cases. The first line contains a single integer $ t $ ( $ 1 \le t \le 10^4 $ ) — the number of test cases. Their description follows.

The first line of each test case contains three integers $ n $ , $ c $ , $ d $ ( $ 1 \le n \le 10^5 $ , $ 1 \le c,d \le 10^9 $ ).

The second line of each test case contains $ n $ integers $ a_{1}, a_{2}, \ldots, a_{n} $ ( $ 1 \le a_{i} \le 10^9 $ ).

It is guaranteed that the sum of $ n $ over all test cases does not exceed $ 2 \cdot 10^5 $ .

## 输出格式

For each test case, output in one line the minimum cost to make the final array a permutation.

## 说明/提示

In the first test case, the array is already a permutation, so there's no need for operations.

In the second test case, we can remove numbers $ 5 $ , $ 6 $ to get the permutation $ [1,2,3] $ in cost $ 2 $ . Note that we can also get a permutation by inserting a number $ 4 $ , but it costs $ 5 $ .

In the third test case, we can just remove all the numbers except for the first number $ 1 $ . It costs $ 8 $ , and the final array is $ [1] $ , which is a permutation of length $ 1 $ .

In the fourth test case, we can remove all the numbers except for $ 2 $ , and insert a number $ 1 $ to the first position. It costs $ 4+10=14 $ , and the final array is $ [1,2] $ , which is a permutation of length $ 2 $ .

## 样例 #1

### 输入

```
8
3 3 3
1 2 3
5 1 5
1 2 3 5 6
5 2 3
1 1 1 3 3
5 1 10
2 4 6 8 10
6 2 8
7 3 5 4 4 8
4 10 1
1 2 6 7
4 3 3
2 5 8 7
2 1000000000 1
1000000000 1
```

### 输出

```
0
2
8
14
20
3
12
999999998
```

