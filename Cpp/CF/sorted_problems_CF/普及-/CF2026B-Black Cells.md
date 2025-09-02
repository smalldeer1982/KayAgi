---
title: "Black Cells"
layout: "post"
diff: 普及-
pid: CF2026B
tag: ['贪心', '二分']
---

# Black Cells

## 题目描述

You are given a strip divided into cells, numbered from left to right from $ 0 $ to $ 10^{18} $ . Initially, all cells are white.

You can perform the following operation: choose two white cells $ i $ and $ j $ , such that $ i \ne j $ and $ |i - j| \le k $ , and paint them black.

A list $ a $ is given. All cells from this list must be painted black. Additionally, at most one cell that is not in this list can also be painted black. Your task is to determine the minimum value of $ k $ for which this is possible.

## 输入格式

The first line contains a single integer $ t $ ( $ 1 \le t \le 500 $ ) — the number of test cases.

The first line of each test case contains a single integer $ n $ ( $ 1 \le n \le 2000 $ ).

The second line contains $ n $ integers $ a_1, a_2, \dots, a_n $ ( $ 0 < a_i < 10^{18} $ ; $ a_i < a_{i + 1} $ ).

Additional constraint on the input: the sum of $ n $ across all test cases does not exceed $ 2000 $ .

## 输出格式

For each test case, print a single integer — the minimum value of $ k $ for which it is possible to paint all the given cells black.

## 说明/提示

In the first example, with $ k=1 $ , it is possible to paint the cells $ (1, 2) $ .

In the second example, with $ k=1 $ , it is possible to paint the cells $ (7, 8) $ .

In the third example, with $ k=2 $ , it is possible to paint the cells $ (2, 4) $ and $ (8, 9) $ .

In the fourth example, with $ k=3 $ , it is possible to paint the cells $ (0, 1) $ , $ (5, 8) $ and $ (10, 13) $ .

## 样例 #1

### 输入

```
4
2
1 2
1
7
3
2 4 9
5
1 5 8 10 13
```

### 输出

```
1
1
2
3
```

