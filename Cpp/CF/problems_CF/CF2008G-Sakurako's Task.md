---
title: "Sakurako's Task"
layout: "post"
diff: 普及+/提高
pid: CF2008G
tag: ['数论', '构造']
---

# Sakurako's Task

## 题目描述

Sakurako has prepared a task for you:

She gives you an array of $ n $ integers and allows you to choose $ i $ and $ j $ such that $ i \neq j $ and $ a_i \ge a_j $ , and then assign $ a_i = a_i - a_j $ or $ a_i = a_i + a_j $ . You can perform this operation any number of times for any $ i $ and $ j $ , as long as they satisfy the conditions.

Sakurako asks you what is the maximum possible value of $ mex_k $ $ ^{\text{∗}} $ of the array after any number of operations.

 $ ^{\text{∗}} $ $ mex_k $ is the $ k $ -th non-negative integer that is absent in the array. For example, $ mex_1(\{1,2,3 \})=0 $ , since $ 0 $ is the first element that is not in the array, and $ mex_2(\{0,2,4 \})=3 $ , since $ 3 $ is the second element that is not in the array.

## 输入格式

The first line contains a single integer $ t $ ( $ 1\le t\le 10^4 $ ) — the number of test cases.

The first line of each test case contains two integers $ n $ and $ k $ ( $ 1\le n\le 2\cdot 10^5,1\le k\le 10^9 $ ) — the number of elements in the array and the value $ k $ for $ mex_k $ .

The second line of each test case contains $ n $ integers $ a_1, a_2, \dots,a_n $ ( $ 1\le a_i\le 10^9 $ ) — the elements of the array.

It is guaranteed that the sum of $ n $ across all test cases does not exceed $ 2\cdot 10^5 $ .

## 输出格式

For each test case, output the maximum $ mex_k $ that can be achieved through the operations.

## 样例 #1

### 输入

```
6
1 3
3
2 10
1 1
3 1
1 2 3
3 2
1 2 4
4 5
2 2 2 16
4 5
2 2 2 3
```

### 输出

```
2
11
3
4
8
8
```

