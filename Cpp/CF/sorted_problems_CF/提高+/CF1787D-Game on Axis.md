---
title: "Game on Axis"
layout: "post"
diff: 提高+/省选-
pid: CF1787D
tag: []
---

# Game on Axis

## 题目描述

There are $ n $ points $ 1,2,\ldots,n $ , each point $ i $ has a number $ a_i $ on it. You're playing a game on them. Initially, you are at point $ 1 $ . When you are at point $ i $ , take following steps:

- If $ 1\le i\le n $ , go to $ i+a_i $ ,
- Otherwise, the game ends.

Before the game begins, you can choose two integers $ x $ and $ y $ satisfying $ 1\le x\le n $ , $ -n \le y \le n $ and replace $ a_x $ with $ y $ (set $ a_x := y $ ). Find the number of distinct pairs $ (x,y) $ such that the game that you start after making the change ends in a finite number of steps.

Notice that you do not have to satisfy $ a_x\not=y $ .

## 输入格式

Each test contains multiple test cases. The first line contains an integer $ t $ ( $ 1\le t\le 10^4) $ — the number of test cases.

The first line of each test case contains one integer $ n $ ( $ 1\le n\le 2\cdot 10^5 $ ) — the number of points.

The second line contains $ n $ integers $ a_1,a_2,\ldots,a_n $ ( $ -n \le a_i \le n $ ) — the numbers on the axis.

It's guaranteed that the sum of $ n $ does not exceed $ 2\cdot 10^5 $ .

## 输出格式

For each test case, print a line containing a single integer — the number of distinct pairs $ (x,y) $ with which the game ends.

## 说明/提示

In the first test case, the pairs $ (x,y) $ with which the game ends are $ (1,-1) $ and $ (1,1) $ , corresponding to the routes $ 1\rightarrow 0 $ and $ 1\rightarrow 2 $ . Note that $ (1,2) $ is invalid since when $ n=1 $ , $ y=2 $ violates $ -n\le y\le n $ . $ (1,0) $ is also invalid since you will go from $ 1 $ to $ 1 $ forever.

In the second test case, the pairs are $ (1,-2),(1,-1),(1,2),(2,-2),(2,-1),(2,0),(2,1),(2,2) $ .

In the fourth test case, the pairs are $ (1,-2),(1,-1),(1,1),(1,2),(2,-2),(2,1),(2,2) $ .

## 样例 #1

### 输入

```
9
1
0
2
-1 0
2
1 -1
2
1 1
3
-1 -2 -1
3
1 -2 -1
4
-1 4 -2 1
5
1 1 1 1 -4
5
1 1 1 1 1
```

### 输出

```
2
8
6
7
20
17
34
30
40
```

