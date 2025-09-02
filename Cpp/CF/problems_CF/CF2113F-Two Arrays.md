---
title: "Two Arrays"
layout: "post"
diff: 提高+/省选-
pid: CF2113F
tag: ['图论', '图论建模', '欧拉回路']
---

# Two Arrays

## 题目描述

You are given two arrays $ a $ and $ b $ of length $ n $ . You can perform the following operation an unlimited number of times:

- Choose an integer $ i $ from $ 1 $ to $ n $ and swap $ a_i $ and $ b_i $ .

Let $ f(c) $ be the number of distinct numbers in array $ c $ . Find the maximum value of $ f(a) + f(b) $ . Also, output the arrays $ a $ and $ b $ after performing all operations.

## 输入格式

Each test contains multiple test cases. The first line contains the number of test cases $ t $ ( $ 1 \le t \le 10^4 $ ). The description of the test cases follows.

The first line of each test case contains a single integer $ n $ ( $ 1 \le n \le 10^5 $ ) — the length of the arrays.

The second line of each test case contains $ n $ integers $ a_1, a_2, \ldots, a_n $ ( $ 1 \le a_i \le 2n $ ) — the elements of array $ a $ .

The third line of each test case contains $ n $ integers $ b_1, b_2, \ldots, b_n $ ( $ 1 \le b_i \le 2n $ ) — the elements of array $ b $ .

It is guaranteed that the sum of $ n $ over all test cases does not exceed $ 10^5 $ .

## 输出格式

For each test case, print a single integer in the first line — the maximum value of $ f(a) + f(b) $ .

In the second line, print $ n $ integers — the elements of array $ a $ after performing the operations.

In the third line, print $ n $ integers — the elements of array $ b $ after performing the operations.

## 说明/提示

In the first test case, after applying three operations with $ i=2 $ , $ i=4 $ , and $ i=5 $ , we obtain $ a = [1, 3, 4, 5, 2] $ and $ b = [1, 2, 3, 4, 4] $ . After that, $ f(a) + f(b) = 5 + 4 = 9 $ . It can be shown that it is not possible to achieve a greater answer.

In the second test case, after applying the operations: $f([2, 3, 4, 2, 1, 5, 6]) + f([1, 2, 3, 4, 5, 6, 5]) = 6 + 6 = 12 $.

## 样例 #1

### 输入

```
3
5
1 2 4 4 4
1 3 3 5 2
7
2 2 4 4 5 5 5
1 3 3 2 1 6 6
7
12 3 3 4 5 6 4
1 2 13 8 10 13 7
```

### 输出

```
9
1 3 4 5 2 
1 2 3 4 4 
12
2 3 4 2 1 5 6 
1 2 3 4 5 6 5 
14
12 3 13 8 10 6 4 
1 2 3 4 5 13 7
```

