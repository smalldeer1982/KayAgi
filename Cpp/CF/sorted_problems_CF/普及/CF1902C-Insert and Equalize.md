---
title: "Insert and Equalize"
layout: "post"
diff: 普及/提高-
pid: CF1902C
tag: []
---

# Insert and Equalize

## 题目描述

You are given an integer array $ a_1, a_2, \dots, a_n $ , all its elements are distinct.

First, you are asked to insert one more integer $ a_{n+1} $ into this array. $ a_{n+1} $ should not be equal to any of $ a_1, a_2, \dots, a_n $ .

Then, you will have to make all elements of the array equal. At the start, you choose a positive integer $ x $ ( $ x > 0 $ ). In one operation, you add $ x $ to exactly one element of the array. Note that $ x $ is the same for all operations.

What's the smallest number of operations it can take you to make all elements equal, after you choose $ a_{n+1} $ and $ x $ ?

## 输入格式

The first line contains a single integer $ t $ ( $ 1 \le t \le 10^4 $ ) — the number of testcases.

The first line of each testcase contains a single integer $ n $ ( $ 1 \le n \le 2 \cdot 10^5 $ ).

The second line contains $ n $ integers $ a_1, a_2, \dots, a_n $ ( $ -10^9 \le a_i \le 10^9 $ ). All $ a_i $ are distinct.

The sum of $ n $ over all testcases doesn't exceed $ 2 \cdot 10^5 $ .

## 输出格式

For each testcase, print a single integer — the smallest number of operations it can take you to make all elements equal, after you choose integers $ a_{n+1} $ and $ x $ .

## 说明/提示

In the first testcase, you can choose $ a_{n+1} = 4 $ , the array becomes $ [1, 2, 3, 4] $ . Then choose $ x = 1 $ and apply the operation $ 3 $ times to the first element, $ 2 $ times to the second element, $ 1 $ time to the third element and $ 0 $ times to the fourth element.

In the second testcase, you can choose $ a_{n+1} = 13, x = 4 $ .

In the third testcase, you can choose $ a_{n+1} = 9, x = 1 $ . Then apply the operation once to $ a_{n+1} $ .

## 样例 #1

### 输入

```
3
3
1 2 3
5
1 -19 17 -3 -15
1
10
```

### 输出

```
6
27
1
```

