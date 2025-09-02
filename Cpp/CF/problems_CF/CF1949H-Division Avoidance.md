---
title: "Division Avoidance"
layout: "post"
diff: NOI/NOI+/CTSC
pid: CF1949H
tag: []
---

# Division Avoidance

## 题目描述

A newly discovered organism can be represented as a set of cells on an infinite grid. There is a coordinate system on the grid such that each cell has two integer coordinates $ x $ and $ y $ . A cell with coordinates $ x=a $ and $ y=b $ will be denoted as $ (a, b) $ .

Initially, the organism consists of a single cell $ (0, 0) $ . Then zero or more divisions can happen. In one division, a cell $ (a, b) $ is removed and replaced by two cells $ (a+1, b) $ and $ (a, b+1) $ .

For example, after the first division, the organism always consists of two cells $ (1, 0) $ and $ (0, 1) $ , and after the second division, it is either the three cells $ (2, 0) $ , $ (1, 1) $ and $ (0, 1) $ , or the three cells $ (1, 0) $ , $ (1, 1) $ and $ (0, 2) $ .

A division of a cell $ (a, b) $ can only happen if the cells $ (a+1, b) $ and $ (a, b+1) $ are not yet part of the organism. For example, the cell $ (1, 0) $ cannot divide if the organism currently consists of the three cells $ (1, 0) $ , $ (1, 1) $ and $ (0, 2) $ , since the cell $ (1, 1) $ that would be one of the results of this division is already part of the organism.

You are given a set of forbidden cells $ {(c_i, d_i)} $ . Is it possible for the organism to contain none of those cells after zero or more divisions?

## 输入格式

Each test contains multiple test cases. The first line contains an integer $ t $ ( $ 1 \le t \le 10\,000 $ ) — the number of test cases. The descriptions of the $ t $ test cases follow.

The first line of each test case contains an integer $ n $ ( $ 1 \le n \le 10^6 $ ) — the number of forbidden cells.

The next $ n $ lines contain two integers each. The $ i $ -th of such lines contains $ c_i $ and $ d_i $ ( $ 0 \le c_i, d_i \le 10^9 $ ) — the coordinates of the $ i $ -th forbidden cell. It is guaranteed that all forbidden cells are distinct.

It is guaranteed that the sum of values of $ n $ over all test cases does not exceed $ 10^6 $ .

## 输出格式

For each test case, print $ \texttt{YES} $ if it is possible for the organism to contain no forbidden cells after zero or more divisions. Otherwise, print $ \texttt{NO} $ .

## 说明/提示

In the first test case, dividing the following cells in the following order creates an organism without any forbidden cells: $ (0, 0) $ , $ (1, 0) $ , $ (1, 1) $ , $ (0, 1) $ , $ (2, 1) $ , $ (2, 2) $ , $ (1, 2) $ , $ (1, 1) $ . The following picture demonstrates how the organism changes during this process:

![](https://cdn.luogu.com.cn/upload/vjudge_pic/CF1949H/af7492370ff72c66df43c916851ebb0d0425026f.png)In the second test case, you can see that, surprisingly, any organism always has at least one cell in the $ 0 \le x, y \le 3 $ square, no matter how many divisions we do.

## 样例 #1

### 输入

```
2
4
0 0
1 0
0 1
1 1
16
0 0
0 1
0 2
0 3
1 0
1 1
1 2
1 3
2 0
2 1
2 2
2 3
3 0
3 1
3 2
3 3
```

### 输出

```
YES
NO
```

