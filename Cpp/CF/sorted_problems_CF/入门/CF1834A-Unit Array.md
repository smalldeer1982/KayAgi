---
title: "Unit Array"
layout: "post"
diff: 入门
pid: CF1834A
tag: []
---

# Unit Array

## 题目描述

Given an array $ a $ of length $ n $ , which elements are equal to $ -1 $ and $ 1 $ . Let's call the array $ a $ good if the following conditions are held at the same time:

- $ a_1 + a_2 + \ldots + a_n \ge 0 $ ;
- $ a_1 \cdot a_2 \cdot \ldots \cdot a_n = 1 $ .

In one operation, you can select an arbitrary element of the array $ a_i $ and change its value to the opposite. In other words, if $ a_i = -1 $ , you can assign the value to $ a_i := 1 $ , and if $ a_i = 1 $ , then assign the value to $ a_i := -1 $ .

Determine the minimum number of operations you need to perform to make the array $ a $ good. It can be shown that this is always possible.

## 输入格式

Each test consists of multiple test cases. The first line contains a single integer $ t $ ( $ 1 \le t \le 500 $ ) — the number of test cases. The description of the test cases follows.

The first line of each test case contains a single integer $ n $ ( $ 1 \le n \le 100 $ ) — the length of the array $ a $ .

The second line of each test case contains $ n $ integers $ a_1, a_2, \ldots, a_n $ ( $ a_i = \pm 1 $ ) — the elements of the array $ a $ .

## 输出格式

For each test case, output a single integer — the minimum number of operations that need to be done to make the $ a $ array good.

## 说明/提示

In the first test case, we can assign the value $ a_1 := 1 $ . Then $ a_1 + a_2 + a_3 + a_4 = 1 + (-1) + 1 + (-1) = 0 \ge 0 $ and $ a_1 \cdot a_2 \cdot a_3 \cdot a_4 = 1 \cdot (-1) \cdot 1 \cdot (-1) = 1 $ . Thus, we performed $ 1 $ operation.

In the second test case, we can assign $ a_1 := 1 $ . Then $ a_1 + a_2 + a_3 + a_4 + a_5 = 1 + (-1) + (-1) + 1 + 1 = 1 \ge 0 $ and $ a_1 \cdot a_2 \cdot a_3 \cdot a_4 \cdot a_5 = 1 \cdot (-1) \cdot (-1) \cdot 1 \cdot 1 = 1 $ . Thus, we performed $ 1 $ operation.

In the third test case, $ a_1 + a_2 + a_3 + a_4 = (-1) + 1 + (-1) + 1 = 0 \ge 0 $ and $ a_1 \cdot a_2 \cdot a_3 \cdot a_4 = (-1) \cdot 1 \cdot (-1) \cdot 1 = 1 $ . Thus, all conditions are already satisfied and no operations are needed.

In the fourth test case, we can assign the values $ a_1 := 1, a_2 := 1, a_3 := 1 $ . Then $ a_1 + a_2 + a_3 = 1 + 1 + 1 = 3 \ge 0 $ and $ a_1 \cdot a_2 \cdot a_3 = 1 \cdot 1 \cdot 1 = 1 $ . Thus, we performed $ 3 $ operations.

## 样例 #1

### 输入

```
7
4
-1 -1 1 -1
5
-1 -1 -1 1 1
4
-1 1 -1 1
3
-1 -1 -1
5
1 1 1 1 1
1
-1
2
-1 -1
```

### 输出

```
1
1
0
3
0
1
2
```

