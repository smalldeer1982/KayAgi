---
title: "Heidi and the Turing Test (Easy)"
layout: "post"
diff: 普及/提高-
pid: CF1184C1
tag: []
---

# Heidi and the Turing Test (Easy)

## 题目描述

The Cybermen and the Daleks have long been the Doctor's main enemies. Everyone knows that both these species enjoy destroying everything they encounter. However, a little-known fact about them is that they both also love taking Turing tests!

Heidi designed a series of increasingly difficult tasks for them to spend their time on, which would allow the Doctor enough time to save innocent lives!

The funny part is that these tasks would be very easy for a human to solve.

The first task is as follows. There are some points on the plane. All but one of them are on the boundary of an axis-aligned square (its sides are parallel to the axes). Identify that point.

## 输入格式

The first line contains an integer $ n $ ( $ 2 \le n \le 10 $ ).

Each of the following $ 4n + 1 $ lines contains two integers $ x_i, y_i $ ( $ 0 \leq x_i, y_i \leq 50 $ ), describing the coordinates of the next point.

It is guaranteed that there are at least $ n $ points on each side of the square and all $ 4n + 1 $ points are distinct.

## 输出格式

Print two integers — the coordinates of the point that is not on the boundary of the square.

## 说明/提示

In both examples, the square has four sides $ x=0 $ , $ x=2 $ , $ y=0 $ , $ y=2 $ .

## 样例 #1

### 输入

```
2
0 0
0 1
0 2
1 0
1 1
1 2
2 0
2 1
2 2

```

### 输出

```
1 1

```

## 样例 #2

### 输入

```
2
0 0
0 1
0 2
0 3
1 0
1 2
2 0
2 1
2 2

```

### 输出

```
0 3

```

