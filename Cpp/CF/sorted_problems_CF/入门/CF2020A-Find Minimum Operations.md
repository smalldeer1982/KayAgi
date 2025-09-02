---
title: "Find Minimum Operations"
layout: "post"
diff: 入门
pid: CF2020A
tag: ['数学', '进制']
---

# Find Minimum Operations

## 题目描述

You are given two integers $ n $ and $ k $ .

In one operation, you can subtract any power of $ k $ from $ n $ . Formally, in one operation, you can replace $ n $ by $ (n-k^x) $ for any non-negative integer $ x $ .

Find the minimum number of operations required to make $ n $ equal to $ 0 $ .

## 输入格式

Each test contains multiple test cases. The first line contains the number of test cases $ t $ ( $ 1 \le t \le 10^4 $ ). The description of the test cases follows.

The only line of each test case contains two integers $ n $ and $ k $ ( $ 1 \le n, k \le 10^9 $ ).

## 输出格式

For each test case, output the minimum number of operations on a new line.

## 说明/提示

In the first test case, $ n = 5 $ and $ k = 2 $ . We can perform the following sequence of operations:

1. Subtract $ 2^0 = 1 $ from $ 5 $ . The current value of $ n $ becomes $ 5 - 1 = 4 $ .
2. Subtract $ 2^2 = 4 $ from $ 4 $ . The current value of $ n $ becomes $ 4 - 4 = 0 $ .

It can be shown that there is no way to make $ n $ equal to $ 0 $ in less than $ 2 $ operations. Thus, $ 2 $ is the answer.

In the second test case, $ n = 3 $ and $ k = 5 $ . We can perform the following sequence of operations:

1. Subtract $ 5^0 = 1 $ from $ 3 $ . The current value of $ n $ becomes $ 3 - 1 = 2 $ .
2. Subtract $ 5^0 = 1 $ from $ 2 $ . The current value of $ n $ becomes $ 2 - 1 = 1 $ .
3. Subtract $ 5^0 = 1 $ from $ 1 $ . The current value of $ n $ becomes $ 1 - 1 = 0 $ .

It can be shown that there is no way to make $ n $ equal to $ 0 $ in less than $ 3 $ operations. Thus, $ 3 $ is the answer.

## 样例 #1

### 输入

```
6
5 2
3 5
16 4
100 3
6492 10
10 1
```

### 输出

```
2
3
1
4
21
10
```

