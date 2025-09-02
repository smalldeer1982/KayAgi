---
title: "Kevin and And"
layout: "post"
diff: 普及+/提高
pid: CF2061E
tag: []
---

# Kevin and And

## 题目描述

Kevin has an integer sequence $ a $ of length $ n $ . At the same time, Kevin has $ m $ types of magic, where the $ i $ -th type of magic can be represented by an integer $ b_i $ .

Kevin can perform at most $ k $ (possibly zero) magic operations. In each operation, Kevin can do the following:

- Choose two indices $ i $ ( $ 1\leq i\leq n $ ) and $ j $ ( $ 1\leq j\leq m $ ), and then update $ a_i $ to $ a_i\ \&\ b_j $ . Here, $ \& $ denotes the [bitwise AND operation](https://en.wikipedia.org/wiki/Bitwise_operation#AND).

Find the minimum possible sum of all numbers in the sequence $ a $ after performing at most $ k $ operations.

## 输入格式

Each test contains multiple test cases. The first line contains the number of test cases $ t $ ( $ 1 \le t \le 10^4 $ ). The description of the test cases follows.

The first line of each test case contains three integers $ n, m, k $ ( $ 1\leq n \leq 10^5 $ , $ 1\leq m \leq 10 $ , $ 0\leq k\leq nm $ ) — the length of $ a $ , the number of types of magic, and the maximum number of operations.

The second line contains $ n $ integers $ a_1, a_2, \ldots, a_n $ ( $ 0\leq a_i < 2^{30} $ ).

The third line contains $ m $ integers $ b_1, b_2, \ldots, b_m $ ( $ 0\leq b_i < 2^{30} $ ).

It is guaranteed that the sum of $ n $ over all test cases does not exceed $ 10^5 $ .

## 输出格式

For each test case, output one integer — the minimum possible sum of all numbers in the sequence $ a $ after performing at most $ k $ operations.

## 说明/提示

In the first test case, one possible way could be:

- Update $ a_1 $ to $ a_1\ \&\ b_1 $ . The sequence will become $ [5] $ .
- Update $ a_1 $ to $ a_1\ \&\ b_3 $ . The sequence will become $ [1] $ .

In the second test case, one possible way could be:

- Update $ a_1 $ to $ a_1\ \&\ b_3 $ . The sequence will become $ [1, 6] $ .
- Update $ a_2 $ to $ a_2\ \&\ b_3 $ . The sequence will become $ [1, 2] $ .

## 样例 #1

### 输入

```
5
1 3 2
7
5 6 3
2 3 2
5 6
5 6 3
10 2 5
3 1 4 1 5 9 2 6 5 3
7 8
5 1 0
1073741823 1073741823 1073741823 1073741823 1073741823
1073741823
1 1 0
0
0
```

### 输出

```
1
3
11
5368709115
0
```

