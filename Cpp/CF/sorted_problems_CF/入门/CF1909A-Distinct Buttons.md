---
title: "Distinct Buttons"
layout: "post"
diff: 入门
pid: CF1909A
tag: []
---

# Distinct Buttons

## 题目描述

[Deemo - Entrance](https://soundcloud.com/iceloki/entrance-deemo)

⠀



You are located at the point $ (0, 0) $ of an infinite Cartesian plane. You have a controller with $ 4 $ buttons which can perform one of the following operations:

- $ \texttt{U} $ : move from $ (x, y) $ to $ (x, y+1) $ ;
- $ \texttt{R} $ : move from $ (x, y) $ to $ (x+1, y) $ ;
- $ \texttt{D} $ : move from $ (x, y) $ to $ (x, y-1) $ ;
- $ \texttt{L} $ : move from $ (x, y) $ to $ (x-1, y) $ .

Unfortunately, the controller is broken. If you press all the $ 4 $ buttons (in any order), the controller stops working. It means that, during the whole trip, you can only press at most $ 3 $ distinct buttons (any number of times, in any order).

There are $ n $ special points in the plane, with integer coordinates $ (x_i, y_i) $ .

Can you visit all the special points (in any order) without breaking the controller?

## 输入格式

Each test contains multiple test cases. The first line contains the number of test cases $ t $ ( $ 1 \le t \le 1000 $ ). The description of the test cases follows.

The first line of each test case contains a single integer $ n $ ( $ 1 \le n \le 100 $ ) — the number of special points.

Each of the next $ n $ lines contains two integers $ x_i $ , $ y_i $ ( $ -100 \leq x_i, y_i \leq 100 $ ), which represent the special point $ (x_i, y_i) $ .

Note that there are no constraints on the sum of $ n $ over all test cases.

## 输出格式

For each test case, output "YES" (without quotes), if you can reach all the special points without breaking the controller, and "NO" (without quotes) otherwise.

You may output each letter in any case (for example, "YES", "Yes", "yes", "yEs" will all be recognized as positive answer).

## 说明/提示

In the first test case, you can move as follows:

- you start from $ (0, 0) $ ;
- you visit the special point $ (x_2, y_2) = (0, 0) $ ;
- you press $ \texttt{R} $ , and you move from $ (0, 0) $ to $ (1, 0) $ ;
- you press $ \texttt{D} $ , and you move from $ (1, 0) $ to $ (1, -1) $ ;
- you visit the special point $ (x_1, y_1) = (1, -1) $ ;
- you visit the special point $ (x_3, y_3) = (1, -1) $ .

Therefore, you can visit all the special points using only the buttons $ \texttt{R} $ , $ \texttt{D} $ , so the controller does not break.

Note that the special points may coincide.

In the second test case, you can show that you can visit all the special points using only the buttons $ \texttt{U} $ , $ \texttt{D} $ , $ \texttt{L} $ .

In the third test case, you can show that you must press all the buttons ( $ \texttt{U} $ , $ \texttt{R} $ , $ \texttt{D} $ , $ \texttt{L} $ ) to visit all the points, so the controller would break.

## 样例 #1

### 输入

```
6
3
1 -1
0 0
1 -1
4
-3 -2
-3 -1
-3 0
-3 1
4
1 1
-1 -1
1 -1
-1 1
6
-4 14
-9 -13
-14 5
14 15
-8 -4
19 9
6
82 64
39 91
3 46
87 83
74 21
7 25
1
100 -100
```

### 输出

```
YES
YES
NO
NO
YES
YES
```

