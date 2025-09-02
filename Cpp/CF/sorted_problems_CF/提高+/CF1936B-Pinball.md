---
title: "Pinball"
layout: "post"
diff: 提高+/省选-
pid: CF1936B
tag: []
---

# Pinball

## 题目描述

There is a one-dimensional grid of length $ n $ . The $ i $ -th cell of the grid contains a character $ s_i $ , which is either '&lt;' or '&gt;'.

When a pinball is placed on one of the cells, it moves according to the following rules:

- If the pinball is on the $ i $ -th cell and $ s_i $ is '&lt;', the pinball moves one cell to the left in the next second. If $ s_i $ is '&gt;', it moves one cell to the right.
- After the pinball has moved, the character $ s_i $ is inverted (i. e. if $ s_i $ used to be '&lt;', it becomes '&gt;', and vice versa).
- The pinball stops moving when it leaves the grid: either from the left border or from the right one.

You need to answer $ n $ independent queries. In the $ i $ -th query, a pinball will be placed on the $ i $ -th cell. Note that we always place a pinball on the initial grid.

For each query, calculate how many seconds it takes the pinball to leave the grid. It can be shown that the pinball will always leave the grid within a finite number of steps.

## 输入格式

Each test contains multiple test cases. The first line contains the number of test cases $ t $ ( $ 1 \le t \le 10^5 $ ). The description of the test cases follows.

The first line of each test case contains an integer $ n $ ( $ 1 \le n \le 5 \cdot 10^5 $ ).

The second line of each test case contains a string $ s_1s_2 \ldots s_{n} $ of length $ n $ consisting of characters '&lt;' and '&gt;'.

It is guaranteed that the sum of $ n $ over all test cases does not exceed $ 5 \cdot 10^5 $ .

## 输出格式

For each test case, for each $ i $ ( $ 1 \le i \le n $ ) output the answer if a pinball is initially placed on the $ i $ -th cell.

## 说明/提示

In the first test case, the movement of the pinball for $ i=1 $ is shown in the following pictures. It takes the pinball $ 3 $ seconds to leave the grid.

 ![](https://cdn.luogu.com.cn/upload/vjudge_pic/CF1936B/9b874ab4c5ee491df87b5d2616ead8d797821647.png)The movement of the pinball for $ i=2 $ is shown in the following pictures. It takes the pinball $ 6 $ seconds to leave the grid.

 ![](https://cdn.luogu.com.cn/upload/vjudge_pic/CF1936B/b4fdbd3674e32422b13cf88676e6ccbb2eef3a53.png)

## 样例 #1

### 输入

```
3
3
><<
4
<<<<
6
<><<<>
```

### 输出

```
3 6 5 
1 2 3 4 
1 4 7 10 8 1
```

