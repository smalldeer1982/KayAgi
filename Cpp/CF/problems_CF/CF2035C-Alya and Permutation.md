---
title: "Alya and Permutation"
layout: "post"
diff: 普及/提高-
pid: CF2035C
tag: ['数学', '构造']
---

# Alya and Permutation

## 题目描述

Alya has been given a hard problem. Unfortunately, she is too busy running for student council. Please solve this problem for her.

Given an integer $ n $ , construct a permutation $ p $ of integers $ 1, 2, \ldots, n $ that maximizes the value of $ k $ (which is initially $ 0 $ ) after the following process.

Perform $ n $ operations, on the $ i $ -th operation ( $ i=1, 2, \dots, n $ ),

- If $ i $ is odd, $ k=k\,\&\,p_i $ , where $ \& $ denotes the [bitwise AND operation](https://en.wikipedia.org/wiki/Bitwise_operation#AND).
- If $ i $ is even, $ k=k\,|\,p_i $ , where $ | $ denotes the [bitwise OR operation](https://en.wikipedia.org/wiki/Bitwise_operation#OR).

## 输入格式

The first line contains a single integer $ t $ ( $ 1\le t\le 500 $ ) — the number of test cases.

The only line of each test case contains a single integer $ n $ ( $ 5\le n\le 2 \cdot 10^5 $ ) — the length of the permutation.

It is guaranteed that the sum of $ n $ over all test cases does not exceed $ 2 \cdot 10^5 $ .

## 输出格式

For each test case, output the maximum value of $ k $ in the first line and output the permutation $ p_1, p_2,\ldots, p_n $ in the second line.

If there are multiple such permutations, output any.

## 说明/提示

For the first test case, the value of $ k $ is determined as follows:

 $ k = 0 $ initially.

- On the $ 1 $ st operation, $ 1 $ is odd, so Alya sets $ k $ to be $ k\&p_1 = 0\&2 = 0 $ .
- On the $ 2 $ nd operation, $ 2 $ is even, so Alya sets $ k $ to be $ k|p_2 = 0|1 = 1 $ .
- On the $ 3 $ rd operation, $ 3 $ is odd, so Alya sets $ k $ to be $ k\&p_3 = 1\&3 = 1 $ .
- On the $ 4 $ th operation, $ 4 $ is even, so Alya sets $ k $ to be $ k|p_4 = 1|4 = 5 $ .
- On the $ 5 $ th operation, $ 5 $ is odd, so Alya sets $ k $ to be $ k\&p_5 = 5\&5 = 5 $ .

The final value of $ k $ is $ 5 $ . It can be shown that the final value of $ k $ is at most $ 5 $ for all permutations of length $ 5 $ . Another valid output is $ [2, 3, 1, 4, 5] $ .

For the second test case, the final value of $ k $ is $ 7 $ . It can be shown that the final value of $ k $ is at most $ 7 $ for all permutations of length $ 6 $ . Other valid outputs include $ [2, 4, 1, 6, 3, 5] $ and $ [5, 2, 6, 1, 3, 4] $ .

## 样例 #1

### 输入

```
6
5
6
7
8
9
10
```

### 输出

```
5
2 1 3 4 5 
7
1 2 4 6 5 3 
7
2 4 5 1 3 6 7 
15
2 4 5 1 3 6 7 8 
9
2 4 5 6 7 1 3 8 9 
15
1 2 3 4 5 6 8 10 9 7
```

