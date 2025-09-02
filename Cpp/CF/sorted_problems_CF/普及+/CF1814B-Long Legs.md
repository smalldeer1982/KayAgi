---
title: "Long Legs"
layout: "post"
diff: 普及+/提高
pid: CF1814B
tag: []
---

# Long Legs

## 题目描述

A robot is placed in a cell $ (0, 0) $ of an infinite grid. This robot has adjustable length legs. Initially, its legs have length $ 1 $ .

Let the robot currently be in the cell $ (x, y) $ and have legs of length $ m $ . In one move, it can perform one of the following three actions:

- jump into the cell $ (x + m, y) $ ;
- jump into the cell $ (x, y + m) $ ;
- increase the length of the legs by $ 1 $ , i. e. set it to $ m + 1 $ .

What's the smallest number of moves robot has to make to reach a cell $ (a, b) $ ?

## 输入格式

The first line contains a single integer $ t $ ( $ 1 \le t \le 100 $ ) — the number of test cases.

The only line of each test case contains two integers $ a $ and $ b $ ( $ 1 \le a, b \le 10^9 $ ) — the ending cell.

## 输出格式

For each test case, print a single integer — the smallest number of moves the robot is required to make to reach a cell $ (a, b) $ from a cell $ (0, 0) $ .

## 说明/提示

In the first testcase, the robot can first jump to $ (0, 1) $ , then to $ (1, 1) $ . If it ever increases the length of its legs, it will only be able to jump past $ (1, 1) $ .

In the second testcase, the robot can jump to $ (1, 0) $ , then increase the length of its length to $ 2 $ and jump three times to reach $ (1, 6) $ .

In the third testcase, the robot can increase the length of its legs three times to make it $ 4 $ . Then jump to $ (0, 4) $ . Then jump twice to reach $ (8, 4) $ .

## 样例 #1

### 输入

```
3
1 1
1 6
8 4
```

### 输出

```
2
5
6
```

