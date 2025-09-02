---
title: "Range = √Sum"
layout: "post"
diff: 普及+/提高
pid: CF1758D
tag: ['前缀和', '构造']
---

# Range = √Sum

## 题目描述

You are given an integer $ n $ . Find a sequence of $ n $ distinct integers $ a_1, a_2, \dots, a_n $ such that $ 1 \leq a_i \leq 10^9 $ for all $ i $ and $ $$$\max(a_1, a_2, \dots, a_n) - \min(a_1, a_2, \dots, a_n)= \sqrt{a_1 + a_2 + \dots + a_n}. $ $$$

It can be proven that there exists a sequence of distinct integers that satisfies all the conditions above.

## 输入格式

The first line of input contains $ t $ ( $ 1 \leq t \leq 10^4 $ ) — the number of test cases.

The first and only line of each test case contains one integer $ n $ ( $ 2 \leq n \leq 3 \cdot 10^5 $ ) — the length of the sequence you have to find.

The sum of $ n $ over all test cases does not exceed $ 3 \cdot 10^5 $ .

## 输出格式

For each test case, output $ n $ space-separated distinct integers $ a_1, a_2, \dots, a_n $ satisfying the conditions in the statement.

If there are several possible answers, you can output any of them. Please remember that your integers must be distinct!

## 说明/提示

In the first test case, the maximum is $ 3 $ , the minimum is $ 1 $ , the sum is $ 4 $ , and $ 3 - 1 = \sqrt{4} $ .

In the second test case, the maximum is $ 29 $ , the minimum is $ 18 $ , the sum is $ 121 $ , and $ 29-18 = \sqrt{121} $ .

For each test case, the integers are all distinct.

## 样例 #1

### 输入

```
3
2
5
4
```

### 输出

```
3 1
20 29 18 26 28
25 21 23 31
```

