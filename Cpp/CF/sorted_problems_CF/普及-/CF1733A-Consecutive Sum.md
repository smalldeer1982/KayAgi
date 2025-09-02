---
title: "Consecutive Sum"
layout: "post"
diff: 普及-
pid: CF1733A
tag: []
---

# Consecutive Sum

## 题目描述

You are given an array $ a $ with $ n $ integers. You can perform the following operation at most $ k $ times:

- Choose two indices $ i $ and $ j $ , in which $ i \,\bmod\, k = j \,\bmod\, k $ ( $ 1 \le i < j \le n $ ).
- Swap $ a_i $ and $ a_j $ .

After performing all operations, you have to select $ k $ consecutive elements, and the sum of the $ k $ elements becomes your score. Find the maximum score you can get.

Here $ x \bmod y $ denotes the remainder from dividing $ x $ by $ y $ .

## 输入格式

The first line contains one integer $ t $ ( $ 1 \le t \le 600 $ ) — the number of test cases.

Each test case consists of two lines.

The first line of each test case contains two integers $ n $ and $ k $ ( $ 1 \le k \le n \le 100 $ ) — the length of the array and the number in the statement above.

The second line of each test case contains $ n $ integers $ a_1, a_2, \ldots, a_n $ ( $ 0 \le a_i \le 10^9 $ ) — the array itself.

## 输出格式

For each test case, print the maximum score you can get, one per line.

## 说明/提示

In the first test case, we can get a score of $ 11 $ if we select $ a_1, a_2 $ without performing any operations.

In the third test case, we can get a score of $ 15 $ if we first swap $ a_1 $ with $ a_4 $ and then select $ a_3, a_4, a_5 $ .

## 样例 #1

### 输入

```
5
3 2
5 6 0
1 1
7
5 3
7 0 4 0 4
4 2
2 7 3 4
3 3
1000000000 1000000000 999999997
```

### 输出

```
11
7
15
10
2999999997
```

