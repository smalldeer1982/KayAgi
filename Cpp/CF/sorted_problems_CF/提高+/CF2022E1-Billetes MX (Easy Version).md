---
title: "Billetes MX (Easy Version)"
layout: "post"
diff: 提高+/省选-
pid: CF2022E1
tag: ['并查集', '位运算']
---

# Billetes MX (Easy Version)

## 题目描述

This is the easy version of the problem. In this version, it is guaranteed that $ q = 0 $ . You can make hacks only if both versions of the problem are solved.

An integer grid $ A $ with $ p $ rows and $ q $ columns is called beautiful if:

- All elements of the grid are integers between $ 0 $ and $ 2^{30}-1 $ , and
- For any subgrid, the XOR of the values at the corners is equal to $ 0 $ . Formally, for any four integers $ i_1 $ , $ i_2 $ , $ j_1 $ , $ j_2 $ ( $ 1 \le i_1 < i_2 \le p $ ; $ 1 \le j_1 < j_2 \le q $ ), $ A_{i_1, j_1} \oplus A_{i_1, j_2} \oplus A_{i_2, j_1} \oplus A_{i_2, j_2} = 0 $ , where $ \oplus $ denotes the [bitwise XOR operation](https://en.wikipedia.org/wiki/Bitwise_operation#XOR).

There is a partially filled integer grid $ G $ with $ n $ rows and $ m $ columns where only $ k $ cells are filled. Polycarp wants to know how many ways he can assign integers to the unfilled cells so that the grid is beautiful.

However, Monocarp thinks that this problem is too easy. Therefore, he will perform $ q $ updates on the grid. In each update, he will choose an unfilled cell and assign an integer to it. Note that these updates are persistent. That is, changes made to the grid will apply when processing future updates.

For each of the $ q + 1 $ states of the grid, the initial state and after each of the $ q $ queries, determine the number of ways Polycarp can assign integers to the unfilled cells so that the grid is beautiful. Since this number can be very large, you are only required to output their values modulo $ 10^9+7 $ .

## 输入格式

The first line contains $ t $ ( $ 1 \le t \le 10^4 $ ) — the number of test cases.

The first line of each test case contains four integers $ n $ , $ m $ , $ k $ and $ q $ ( $ 2 \le n, m \le 10^5 $ ; $ 0 \le k \le 10^5 $ ; $ q = 0 $ ) — the number of rows, the number of columns, the number of fixed cells, and the number of updates.

The following $ k $ lines contain three integers $ r $ , $ c $ and $ v $ ( $ 1 \le r \le n, 1 \le c \le m $ ; $ 0 \le v < 2^{30} $ ) — indicating that $ G_{r, c} $ is assigned the integer $ v $ .

The following $ q $ lines contain three integers $ r $ , $ c $ and $ v $ ( $ 1 \le r \le n, 1 \le c \le m $ ; $ 0 \le v < 2^{30} $ ) — indicating that $ G_{r, c} $ is assigned the integer $ v $ .

It is guaranteed that the pairs $ (r,c) $ over all assignments are distinct.

It is guaranteed that the sum of $ n $ , $ m $ , $ k $ and $ q $ over all test cases does not exceed $ 10^5 $ respectively.

## 输出格式

For each test case, output $ q + 1 $ lines. The $ i $ -th line of output should contain the answer of the $ i $ -th state of the grid modulo $ 10^9 + 7 $ .

## 说明/提示

In the first test case of the example, we have the following grid:

  $ 0 $  $ 6 $  $ 10 $  $ 6 $  $ 0 $  $ 12 $  $ 10 $  $ 12 $  $ ? $ It can be proven that the only valid value for tile $ (3, 3) $ is $ 0 $ .

## 样例 #1

### 输入

```
2
3 3 8 0
2 1 6
3 2 12
1 2 6
2 2 0
1 3 10
1 1 0
2 3 12
3 1 10
2 5 2 0
1 1 10
1 2 30
```

### 输出

```
1
489373567
```

