---
title: "Was there an Array?"
layout: "post"
diff: 难度0
pid: CF2069A
tag: []
---

# Was there an Array?

## 题目描述

For an array of integers $ a_1, a_2, \dots, a_n $ , we define its equality characteristic as the array $ b_2, b_3, \dots, b_{n-1} $ , where $ b_i = 1 $ if the $ i $ -th element of the array $ a $ is equal to both of its neighbors, and $ b_i = 0 $ if the $ i $ -th element of the array $ a $ is not equal to at least one of its neighbors.

For example, for the array $ [1, 2, 2, 2, 3, 3, 4, 4, 4, 4] $ , the equality characteristic will be $ [0, 1, 0, 0, 0, 0, 1, 1] $ .

You are given the array $ b_2, b_3, \dots, b_{n-1} $ . Your task is to determine whether there exists such an array $ a $ for which the given array is the equality characteristic.

## 输入格式

The first line contains one integer $ t $ ( $ 1 \le t \le 1000 $ ) — the number of test cases.

Each test case consists of two lines:

- the first line contains one integer $ n $ ( $ 3 \le n \le 100 $ );
- the second line contains $ n-2 $ integers $ b_2, b_3, \dots, b_{n-1} $ ( $ 0 \le b_i \le 1 $ ).

## 输出格式

For each test case, output YES if the array $ a $ exists, or NO if such an array does not exist. Each letter can be printed in any case.

## 说明/提示

In the first example, the array $ a = [1, 2, 2, 2, 3, 3, 4, 4, 4, 4] $ is suitable.

In the second example, the array $ a = [7, 7, 7] $ is suitable.

## 样例 #1

### 输入

```
3
10
0 1 0 0 0 0 1 1
3
1
10
0 1 0 1 1 0 0 1
```

### 输出

```
YES
YES
NO
```

