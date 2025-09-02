---
title: "Add Plus Minus Sign"
layout: "post"
diff: 入门
pid: CF1774A
tag: []
---

# Add Plus Minus Sign

## 题目描述

AquaMoon has a string $ a $ consisting of only $ 0 $ and $ 1 $ . She wants to add $ + $ and $ - $ between all pairs of consecutive positions to make the absolute value of the resulting expression as small as possible. Can you help her?

## 输入格式

The first line contains a single integer $ t $ ( $ 1 \leq t \leq 2\,000 $ ) – the number of test cases. The description of test cases follows.

The first line of each test case contains a single integer $ n $ ( $ 2 \leq n \leq 100 $ ) — the length of $ a $ .

The second line of each test case contains a string $ a $ of length $ n $ , consisting of only $ 0 $ and $ 1 $ .

## 输出格式

For each test case, output a string of length $ n - 1 $ consisting of $ - $ and $ + $ on a separate line. If there is more than one assignment of signs that produces the smallest possible absolute value, any of them is accepted.

## 说明/提示

In the first test case, we can get the expression $ 1 - 1 = 0 $ , with absolute value $ 0 $ .

In the second test case, we can get the expression $ 0 + 1 - 1 + 0 + 1 = 1 $ , with absolute value $ 1 $ .

In the third test case, we can get the expression $ 1 + 0 + 0 + 0 - 1 = 0 $ , with absolute value $ 0 $ .

## 样例 #1

### 输入

```
3
2
11
5
01101
5
10001
```

### 输出

```
-
+-++
+++-
```

