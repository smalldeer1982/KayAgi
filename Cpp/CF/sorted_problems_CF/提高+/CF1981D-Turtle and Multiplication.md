---
title: "Turtle and Multiplication"
layout: "post"
diff: 提高+/省选-
pid: CF1981D
tag: ['欧拉回路']
---

# Turtle and Multiplication

## 题目描述

Turtle just learned how to multiply two integers in his math class, and he was very excited.

Then Piggy gave him an integer $ n $ , and asked him to construct a sequence $ a_1, a_2, \ldots, a_n $ consisting of integers which satisfied the following conditions:

- For all $ 1 \le i \le n $ , $ 1 \le a_i \le 3 \cdot 10^5 $ .
- For all $ 1 \le i < j \le n - 1 $ , $ a_i \cdot a_{i + 1} \ne a_j \cdot a_{j + 1} $ .

Of all such sequences, Piggy asked Turtle to find the one with the minimum number of distinct elements.

Turtle definitely could not solve the problem, so please help him!

## 输入格式

Each test contains multiple test cases. The first line contains the number of test cases $ t $ ( $ 1 \le t \le 10^4 $ ). The description of the test cases follows.

The first line of each test case contains a single integer $ n $ ( $ 2 \le n \le 10^6 $ ) — the length of the sequence $ a $ .

It is guaranteed that the sum of $ n $ over all test cases does not exceed $ 10^6 $ .

## 输出格式

For each test case, output $ n $ integers $ a_1, a_2, \ldots, a_n $ — the elements of the sequence $ a $ .

If there are multiple answers, print any of them.

## 说明/提示

In the third test case, $ a = [3, 4, 2, 6] $ violates the second condition since $ a_1 \cdot a_2 = a_3 \cdot a_4 $ . $ a = [2, 3, 4, 4] $ satisfy the conditions but its number of distinct elements isn't minimum.

## 样例 #1

### 输入

```
3
2
3
4
```

### 输出

```
114514 114514
1 2 2
3 3 4 4
```

