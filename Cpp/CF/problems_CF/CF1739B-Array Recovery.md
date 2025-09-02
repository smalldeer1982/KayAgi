---
title: "Array Recovery"
layout: "post"
diff: 普及-
pid: CF1739B
tag: []
---

# Array Recovery

## 题目描述

For an array of non-negative integers $ a $ of size $ n $ , we construct another array $ d $ as follows: $ d_1 = a_1 $ , $ d_i = |a_i - a_{i - 1}| $ for $ 2 \le i \le n $ .

Your task is to restore the array $ a $ from a given array $ d $ , or to report that there are multiple possible arrays.

## 输入格式

The first line contains a single integer $ t $ ( $ 1 \le t \le 100 $ ) — the number of test cases.

The first line of each test case contains one integer $ n $ ( $ 1 \le n \le 100 $ ) — the size of the arrays $ a $ and $ d $ .

The second line contains $ n $ integers $ d_1, d_2, \dots, d_n $ ( $ 0 \le d_i \le 100 $ ) — the elements of the array $ d $ .

It can be shown that there always exists at least one suitable array $ a $ under these constraints.

## 输出格式

For each test case, print the elements of the array $ a $ , if there is only one possible array $ a $ . Otherwise, print $ -1 $ .

## 说明/提示

In the second example, there are two suitable arrays: $ [2, 8, 5] $ and $ [2, 8, 11] $ .

## 样例 #1

### 输入

```
3
4
1 0 2 5
3
2 6 3
5
0 0 0 0 0
```

### 输出

```
1 1 3 8
-1
0 0 0 0 0
```

