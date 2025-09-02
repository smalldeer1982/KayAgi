---
title: "Ideal Point"
layout: "post"
diff: 普及-
pid: CF1795B
tag: []
---

# Ideal Point

## 题目描述

You are given $ n $ one-dimensional segments (each segment is denoted by two integers — its endpoints).

Let's define the function $ f(x) $ as the number of segments covering point $ x $ (a segment covers the point $ x $ if $ l \le x \le r $ , where $ l $ is the left endpoint and $ r $ is the right endpoint of the segment).

An integer point $ x $ is called ideal if it belongs to more segments than any other integer point, i. e. $ f(y) < f(x) $ is true for any other integer point $ y $ .

You are given an integer $ k $ . Your task is to determine whether it is possible to remove some (possibly zero) segments, so that the given point $ k $ becomes ideal.

## 输入格式

The first line contains one integer $ t $ ( $ 1 \le t \le 1000 $ ) — the number of test cases.

The first line of each test case contains two integers $ n $ and $ k $ ( $ 1 \le n, k \le 50 $ ).

Then $ n $ lines follow, $ i $ -th line of them contains two integers $ l_i $ and $ r_i $ ( $ 1 \le l_i, r_i \le 50 $ ; $ l_i \le r_i $ ) — the endpoints of the $ i $ -th segment.

## 输出格式

For each test case, print YES if it is possible to remove some (possibly zero) segments, so that the given point $ k $ becomes ideal, otherwise print NO.

You may print each letter in any case (YES, yes, Yes will all be recognized as positive answer, NO, no and nO will all be recognized as negative answer).

## 说明/提示

In the first example, the point $ 3 $ is already ideal (it is covered by three segments), so you don't have to delete anything.

In the fourth example, you can delete everything except the segment $ [5, 5] $ .

## 样例 #1

### 输入

```
4
4 3
1 3
7 9
2 5
3 6
2 9
1 4
3 7
1 3
2 4
3 5
1 4
6 7
5 5
```

### 输出

```
YES
NO
NO
YES
```

