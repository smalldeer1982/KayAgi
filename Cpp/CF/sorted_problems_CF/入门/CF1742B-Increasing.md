---
title: "Increasing"
layout: "post"
diff: 入门
pid: CF1742B
tag: []
---

# Increasing

## 题目描述

You are given an array $ a $ of $ n $ positive integers. Determine if, by rearranging the elements, you can make the array strictly increasing. In other words, determine if it is possible to rearrange the elements such that $ a_1 < a_2 < \dots < a_n $ holds.

## 输入格式

The first line contains a single integer $ t $ ( $ 1 \leq t \leq 100 $ ) — the number of test cases.

The first line of each test case contains a single integer $ n $ ( $ 1 \leq n \leq 100 $ ) — the length of the array.

The second line of each test case contains $ n $ integers $ a_i $ ( $ 1 \leq a_i \leq 10^9 $ ) — the elements of the array.

## 输出格式

For each test case, output "YES" (without quotes) if the array satisfies the condition, and "NO" (without quotes) otherwise.

You can output the answer in any case (for example, the strings "yEs", "yes", "Yes" and "YES" will be recognized as a positive answer).

## 说明/提示

In the first test case any rearrangement will keep the array $ [1,1,1,1] $ , which is not strictly increasing.

In the second test case, you can make the array $ [1,3,4,7,8] $ .

## 样例 #1

### 输入

```
3
4
1 1 1 1
5
8 7 1 3 4
1
5
```

### 输出

```
NO
YES
YES
```

