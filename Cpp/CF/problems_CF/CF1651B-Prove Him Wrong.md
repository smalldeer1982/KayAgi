---
title: "Prove Him Wrong"
layout: "post"
diff: 入门
pid: CF1651B
tag: []
---

# Prove Him Wrong

## 题目描述

Recently, your friend discovered one special operation on an integer array $ a $ :

1. Choose two indices $ i $ and $ j $ ( $ i \neq j $ );
2. Set $ a_i = a_j = |a_i - a_j| $ .

After playing with this operation for a while, he came to the next conclusion:

- For every array $ a $ of $ n $ integers, where $ 1 \le a_i \le 10^9 $ , you can find a pair of indices $ (i, j) $ such that the total sum of $ a $ will decrease after performing the operation.

This statement sounds fishy to you, so you want to find a counterexample for a given integer $ n $ . Can you find such counterexample and prove him wrong?

In other words, find an array $ a $ consisting of $ n $ integers $ a_1, a_2, \dots, a_n $ ( $ 1 \le a_i \le 10^9 $ ) such that for all pairs of indices $ (i, j) $ performing the operation won't decrease the total sum (it will increase or not change the sum).

## 输入格式

The first line contains a single integer $ t $ ( $ 1 \le t \le 100 $ ) — the number of test cases. Then $ t $ test cases follow.

The first and only line of each test case contains a single integer $ n $ ( $ 2 \le n \le 1000 $ ) — the length of array $ a $ .

## 输出格式

For each test case, if there is no counterexample array $ a $ of size $ n $ , print NO.

Otherwise, print YES followed by the array $ a $ itself ( $ 1 \le a_i \le 10^9 $ ). If there are multiple counterexamples, print any.

## 说明/提示

In the first test case, the only possible pairs of indices are $ (1, 2) $ and $ (2, 1) $ .

If you perform the operation on indices $ (1, 2) $ (or $ (2, 1) $ ), you'll get $ a_1 = a_2 = |1 - 337| = 336 $ , or array $ [336, 336] $ . In both cases, the total sum increases, so this array $ a $ is a counterexample.

## 样例 #1

### 输入

```
3
2
512
3
```

### 输出

```
YES
1 337
NO
YES
31 4 159
```

