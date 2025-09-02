---
title: "Black and White Stripe"
layout: "post"
diff: 普及-
pid: CF1690D
tag: []
---

# Black and White Stripe

## 题目描述

You have a stripe of checkered paper of length $ n $ . Each cell is either white or black.

What is the minimum number of cells that must be recolored from white to black in order to have a segment of $ k $ consecutive black cells on the stripe?

If the input data is such that a segment of $ k $ consecutive black cells already exists, then print 0.

## 输入格式

The first line contains an integer $ t $ ( $ 1 \le t \le 10^4 $ ) — the number of test cases.

Next, descriptions of $ t $ test cases follow.

The first line of the input contains two integers $ n $ and $ k $ ( $ 1 \le k \le n \le 2\cdot10^5 $ ). The second line consists of the letters 'W' (white) and 'B' (black). The line length is $ n $ .

It is guaranteed that the sum of values $ n $ does not exceed $ 2\cdot10^5 $ .

## 输出格式

For each of $ t $ test cases print an integer — the minimum number of cells that need to be repainted from white to black in order to have a segment of $ k $ consecutive black cells.

## 说明/提示

In the first test case, $ s $ ="BBWBW" and $ k=3 $ . It is enough to recolor $ s_3 $ and get $ s $ ="BBBBW". This string contains a segment of length $ k=3 $ consisting of the letters 'B'.

In the second test case of the example $ s $ ="BBWBW" and $ k=5 $ . It is enough to recolor $ s_3 $ and $ s_5 $ and get $ s $ ="BBBBB". This string contains a segment of length $ k=5 $ consisting of the letters 'B'.

In the third test case of the example $ s $ ="BBWBW" and $ k=1 $ . The string $ s $ already contains a segment of length $ k=1 $ consisting of the letters 'B'.

## 样例 #1

### 输入

```
4
5 3
BBWBW
5 5
BBWBW
5 1
BBWBW
1 1
W
```

### 输出

```
1
2
0
1
```

