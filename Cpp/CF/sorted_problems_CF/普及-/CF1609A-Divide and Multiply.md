---
title: "Divide and Multiply"
layout: "post"
diff: 普及-
pid: CF1609A
tag: ['贪心']
---

# Divide and Multiply

## 题目描述

![](https://cdn.luogu.com.cn/upload/vjudge_pic/CF1609A/ed5b77bcb83c3732516ccac033270f15c3ac243c.png)William has array of $ n $ numbers $ a_1, a_2, \dots, a_n $ . He can perform the following sequence of operations any number of times:

1. Pick any two items from array $ a_i $ and $ a_j $ , where $ a_i $ must be a multiple of $ 2 $
2. $ a_i = \frac{a_i}{2} $
3. $ a_j = a_j \cdot 2 $

Help William find the maximal sum of array elements, which he can get by performing the sequence of operations described above.

## 输入格式

Each test contains multiple test cases. The first line contains the number of test cases $ t $ ( $ 1 \le t \le 10^4 $ ). Description of the test cases follows.

The first line of each test case contains an integer $ n $ $ (1 \le n \le 15) $ , the number of elements in William's array.

The second line contains $ n $ integers $ a_1, a_2, \dots, a_n $ $ (1 \le a_i < 16) $ , the contents of William's array.

## 输出格式

For each test case output the maximal sum of array elements after performing an optimal sequence of operations.

## 说明/提示

In the first example test case the optimal sequence would be:

1. Pick $ i = 2 $ and $ j = 1 $ . After performing a sequence of operations $ a_2 = \frac{4}{2} = 2 $ and $ a_1 = 6 \cdot 2 = 12 $ , making the array look as: \[12, 2, 2\].
2. Pick $ i = 2 $ and $ j = 1 $ . After performing a sequence of operations $ a_2 = \frac{2}{2} = 1 $ and $ a_1 = 12 \cdot 2 = 24 $ , making the array look as: \[24, 1, 2\].
3. Pick $ i = 3 $ and $ j = 1 $ . After performing a sequence of operations $ a_3 = \frac{2}{2} = 1 $ and $ a_1 = 24 \cdot 2 = 48 $ , making the array look as: \[48, 1, 1\].

The final answer $ 48 + 1 + 1 = 50 $ .

In the third example test case there is no way to change the sum of elements, so the answer is $ 10 $ .

## 样例 #1

### 输入

```
5
3
6 4 2
5
1 2 3 4 5
1
10
3
2 3 4
15
8 8 8 8 8 8 8 8 8 8 8 8 8 8 8
```

### 输出

```
50
46
10
26
35184372088846
```

