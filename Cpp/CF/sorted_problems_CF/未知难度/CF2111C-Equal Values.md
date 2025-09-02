---
title: "Equal Values"
layout: "post"
diff: 难度0
pid: CF2111C
tag: []
---

# Equal Values

## 题目描述

You are given an array $ a_1, a_2, \dots, a_n $ , consisting of $ n $ integers.

In one operation, you are allowed to perform one of the following actions:

- Choose a position $ i $ ( $ 1 < i \le n $ ) and make all elements to the left of $ i $ equal to $ a_i $ . That is, assign the value $ a_i $ to all $ a_j $ ( $ 1 \le j < i $ ). The cost of such an operation is $ (i - 1) \cdot a_i $ .
- Choose a position $ i $ ( $ 1 \le i < n $ ) and make all elements to the right of $ i $ equal to $ a_i $ . That is, assign the value $ a_i $ to all $ a_j $ ( $ i < j \le n $ ). The cost of such an operation is $ (n - i) \cdot a_i $ .

Note that the elements affected by an operation may already be equal to $ a_i $ , but that doesn't change the cost.

You are allowed to perform any number of operations (including zero). What is the minimum total cost to make all elements of the array equal?

## 输入格式

The first line contains one integer $ t $ ( $ 1 \le t \le 10^4 $ ) — the number of test cases.

The first line of each test case contains a single integer $ n $ ( $ 2 \le n \le 5 \cdot 10^5 $ ).

The second line contains $ n $ integers $ a_1, a_2, \dots, a_n $ ( $ 1 \le a_i \le n $ ).

The sum of $ n $ over all test cases does not exceed $ 5 \cdot 10^5 $ .

## 输出格式

For each test case, print a single integer — the minimum total cost of operations to make all elements of the array equal.

## 说明/提示

In the first test case, you can perform the operation twice:

- choose $ i = 3 $ and make all elements to the left of it equal to it, the cost will be $ 2 \cdot 1 = 2 $ ;
- choose $ i = 3 $ and make all elements to the right of it equal to it, the cost will be $ 1 \cdot 1 = 1 $ .

The total cost is $ 2 + 1 = 3 $ .

In the second test case, all elements are already equal, so no operations need to be performed.

## 样例 #1

### 输入

```
3
4
2 4 1 3
3
1 1 1
10
7 5 5 5 10 9 9 4 6 10
```

### 输出

```
3
0
35
```

