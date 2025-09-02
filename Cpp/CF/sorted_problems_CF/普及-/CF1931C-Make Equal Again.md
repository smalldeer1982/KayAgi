---
title: "Make Equal Again"
layout: "post"
diff: 普及-
pid: CF1931C
tag: []
---

# Make Equal Again

## 题目描述

You have an array $ a $ of $ n $ integers.

You can no more than once apply the following operation: select three integers $ i $ , $ j $ , $ x $ ( $ 1 \le i \le j \le n $ ) and assign all elements of the array with indexes from $ i $ to $ j $ the value $ x $ . The price of this operation depends on the selected indices and is equal to $ (j - i + 1) $ burles.

For example, the array is equal to $ [1, 2, 3, 4, 5, 1] $ . If we choose $ i = 2, j = 4, x = 8 $ , then after applying this operation, the array will be equal to $ [1, 8, 8, 8, 5, 1] $ .

What is the least amount of burles you need to spend to make all the elements of the array equal?

## 输入格式

The first line contains a single integer $ t $ ( $ 1 \le t \le 10^4 $ ) — the number of input test cases. The descriptions of the test cases follow.

The first line of the description of each test case contains a single integer $ n $ ( $ 1 \le n \le 2 \cdot 10 ^ 5 $ ) — the size of the array.

The second line of the description of each test case contains $ n $ integers $ a_1, a_2, \dots, a_n $ ( $ 1 \le a_i \le n $ ) — array elements.

It is guaranteed that the sum of $ n $ for all test cases does not exceed $ 2 \cdot 10^5 $ .

## 输出格式

For each test case, output one integer — the minimum number of burles that will have to be spent to make all the elements of the array equal. It can be shown that this can always be done.

## 样例 #1

### 输入

```
8
6
1 2 3 4 5 1
7
1 1 1 1 1 1 1
8
8 8 8 1 2 8 8 8
1
1
2
1 2
3
1 2 3
7
4 3 2 7 1 1 3
9
9 9 2 9 2 5 5 5 3
```

### 输出

```
4
0
2
0
1
2
6
7
```

