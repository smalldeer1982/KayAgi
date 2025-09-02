---
title: "Colored Rectangles"
layout: "post"
diff: 普及+/提高
pid: CF1398D
tag: []
---

# Colored Rectangles

## 题目描述

You are given three multisets of pairs of colored sticks:

- $ R $ pairs of red sticks, the first pair has length $ r_1 $ , the second pair has length $ r_2 $ , $ \dots $ , the $ R $ -th pair has length $ r_R $ ;
- $ G $ pairs of green sticks, the first pair has length $ g_1 $ , the second pair has length $ g_2 $ , $ \dots $ , the $ G $ -th pair has length $ g_G $ ;
- $ B $ pairs of blue sticks, the first pair has length $ b_1 $ , the second pair has length $ b_2 $ , $ \dots $ , the $ B $ -th pair has length $ b_B $ ;

You are constructing rectangles from these pairs of sticks with the following process:

1. take a pair of sticks of one color;
2. take a pair of sticks of another color different from the first one;
3. add the area of the resulting rectangle to the total area.

Thus, you get such rectangles that their opposite sides are the same color and their adjacent sides are not the same color.

Each pair of sticks can be used at most once, some pairs can be left unused. You are not allowed to split a pair into independent sticks.

What is the maximum area you can achieve?

## 输入格式

The first line contains three integers $ R $ , $ G $ , $ B $ ( $ 1 \le R, G, B \le 200 $ ) — the number of pairs of red sticks, the number of pairs of green sticks and the number of pairs of blue sticks.

The second line contains $ R $ integers $ r_1, r_2, \dots,       r_R $ ( $ 1 \le r_i \le 2000 $ ) — the lengths of sticks in each pair of red sticks.

The third line contains $ G $ integers $ g_1, g_2, \dots,       g_G $ ( $ 1 \le g_i \le 2000 $ ) — the lengths of sticks in each pair of green sticks.

The fourth line contains $ B $ integers $ b_1, b_2, \dots,       b_B $ ( $ 1 \le b_i \le 2000 $ ) — the lengths of sticks in each pair of blue sticks.

## 输出格式

Print the maximum possible total area of the constructed rectangles.

## 说明/提示

In the first example you can construct one of these rectangles: red and green with sides $ 3 $ and $ 5 $ , red and blue with sides $ 3 $ and $ 4 $ and green and blue with sides $ 5 $ and $ 4 $ . The best area of them is $ 4 \times 5 = 20 $ .

In the second example the best rectangles are: red/blue $ 9       \times 8 $ , red/blue $ 5 \times 5 $ , green/blue $ 2 \times       1 $ . So the total area is $ 72 + 25 + 2 = 99 $ .

In the third example the best rectangles are: red/green $ 19       \times 8 $ and red/blue $ 20 \times 11 $ . The total area is $ 152 + 220 = 372 $ . Note that you can't construct more rectangles because you are not allowed to have both pairs taken to be the same color.

## 样例 #1

### 输入

```
1 1 1
3
5
4
```

### 输出

```
20
```

## 样例 #2

### 输入

```
2 1 3
9 5
1
2 8 5
```

### 输出

```
99
```

## 样例 #3

### 输入

```
10 1 1
11 7 20 15 19 14 2 4 13 14
8
11
```

### 输出

```
372
```

