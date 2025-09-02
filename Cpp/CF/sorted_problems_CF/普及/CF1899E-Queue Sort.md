---
title: "Queue Sort"
layout: "post"
diff: 普及/提高-
pid: CF1899E
tag: []
---

# Queue Sort

## 题目描述

Vlad found an array $ a $ of $ n $ integers and decided to sort it in non-decreasing order.

To do this, Vlad can apply the following operation any number of times:

- Extract the first element of the array and insert it at the end;
- Swap that element with the previous one until it becomes the first or until it becomes strictly greater than the previous one.

Note that both actions are part of the operation, and for one operation, you must apply both actions.

For example, if you apply the operation to the array \[ $ 4, 3, 1, 2, 6, 4 $ \], it will change as follows:

- \[ $ \color{red}{4}, 3, 1, 2, 6, 4 $ \];
- \[ $ 3, 1, 2, 6, 4, \color{red}{4} $ \];
- \[ $ 3, 1, 2, 6, \color{red}{4}, 4 $ \];
- \[ $ 3, 1, 2, \color{red}{4}, 6, 4 $ \].

Vlad doesn't have time to perform all the operations, so he asks you to determine the minimum number of operations required to sort the array or report that it is impossible.

## 输入格式

The first line of the input contains a single integer $ t $ ( $ 1 \le t \le 10^4 $ ) — the number of test cases. Descriptions of the test cases follow.

The first line of each test case contains a single integer $ n $ ( $ 1 \le n \le 2 \cdot 10^5 $ ) — the length of the array.

The second line of each test case contains $ n $ integers $ a_1, a_2, a_3, \dots, a_n $ ( $ 1 \le a_i \le 10^9 $ ) — the elements of the array.

It is guaranteed that the sum of $ n $ over all testcases does not exceed $ 2 \cdot 10^5 $ .

## 输出格式

For each test case, output a single integer — the minimum number of operations needed to sort the array. If it is impossible to do so, output $ -1 $ as the answer.

## 样例 #1

### 输入

```
5
5
6 4 1 2 5
7
4 5 3 7 8 6 2
6
4 3 1 2 6 4
4
5 2 4 2
3
2 2 3
```

### 输出

```
2
6
-1
-1
0
```

