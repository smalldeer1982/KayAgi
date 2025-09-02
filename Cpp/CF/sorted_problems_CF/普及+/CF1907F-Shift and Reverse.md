---
title: "Shift and Reverse"
layout: "post"
diff: 普及+/提高
pid: CF1907F
tag: []
---

# Shift and Reverse

## 题目描述

Given an array of integers $ a_1, a_2, \ldots, a_n $ . You can make two types of operations with this array:

- Shift: move the last element of array to the first place, and shift all other elements to the right, so you get the array $ a_n, a_1, a_2, \ldots, a_{n-1} $ .
- Reverse: reverse the whole array, so you get the array $ a_n, a_{n-1}, \ldots, a_1 $ .

Your task is to sort the array in non-decreasing order using the minimal number of operations, or say that it is impossible.

## 输入格式

The first line of input contains a single integer $ t $ ( $ 1 \le t \le 10^4 $ ) — the number of test cases. Descriptions of test cases follow.

The first line of each test case contains an integer $ n $ ( $ 1\le n \le 10^5 $ ) — size of the array.

The second line of each test case contains $ n $ integers $ a_1, a_2, \ldots, a_n $ ( $ 1 \le a_i \le 10^9 $ ) — elements of the array.

It is guaranteed that sum of $ n $ over all test cases does not exceed $ 2 \cdot 10^5 $ .

## 输出格式

For each test case output the number $ k $ , the minimal number of operations you need to sort the array. If it is impossible to sort the array using these operations, output $ -1 $ .

## 说明/提示

In the first test case of the example, to sort the array \[ $ 3, 2, 1, 5, 4 $ \] you need to perform $ 3 $ operations:

- Shift to obtain the array \[ $ 4, 3, 2, 1, 5 $ \];
- Shift to obtain the array \[ $ 5, 4, 3, 2, 1 $ \];
- Reverse to obtain the array \[ $ 1, 2, 3, 4, 5 $ \].

In the third test case of the example, it can be shown that it is impossible to sort the array using the given operations.

In the seventh test case of the example, to sort the array \[ $ 4, 1, 3, 4, 4 $ \] you need to perform $ 3 $ operations:

- Reverse to obtain the array \[ $ 4, 4, 3, 1, 4 $ \];
- Shift to obtain the array \[ $ 4, 4, 4, 3, 1 $ \];
- Reverse to obtain the array \[ $ 1, 3, 4, 4, 4 $ \].

## 样例 #1

### 输入

```
11
5
3 2 1 5 4
5
1 1 2 1 1
4
3 7 10 5
5
1 2 3 4 5
2
5 1
3
3 4 1
5
4 1 3 4 4
3
5 1 1
4
2 5 5 4
5
2 2 1 1 2
2
5 5
```

### 输出

```
3
2
-1
0
1
1
3
1
2
2
0
```

