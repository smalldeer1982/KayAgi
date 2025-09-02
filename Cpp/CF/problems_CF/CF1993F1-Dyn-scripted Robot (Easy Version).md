---
title: "Dyn-scripted Robot (Easy Version)"
layout: "post"
diff: 提高+/省选-
pid: CF1993F1
tag: ['扩展欧几里德算法', '中国剩余定理 CRT']
---

# Dyn-scripted Robot (Easy Version)

## 题目描述

This is the easy version of the problem. The only difference is that in this version $ k \le n $ . You can make hacks only if both versions of the problem are solved.

Given a $ w \times h $ rectangle on the $ Oxy $ plane, with points $ (0, 0) $ at the bottom-left and $ (w, h) $ at the top-right of the rectangle.

You also have a robot initially at point $ (0, 0) $ and a script $ s $ of $ n $ characters. Each character is either L, R, U, or D, which tells the robot to move left, right, up, or down respectively.

The robot can only move inside the rectangle; otherwise, it will change the script $ s $ as follows:

- If it tries to move outside a vertical border, it changes all L characters to R's (and vice versa, all R's to L's).
- If it tries to move outside a horizontal border, it changes all U characters to D's (and vice versa, all D's to U's).

Then, it will execute the changed script starting from the character which it couldn't execute.

 ![](https://cdn.luogu.com.cn/upload/vjudge_pic/CF1993F1/ff49f6aa11a19418f77260f4c00c02fa1a42de65.png) An example of the robot's movement process, $ s = \texttt{"ULULURD"} $ The script $ s $ will be executed for $ k $ times continuously. All changes to the string $ s $ will be retained even when it is repeated. During this process, how many times will the robot move to the point $ (0, 0) $ in total? Note that the initial position does NOT count.

## 输入格式

The first line contains a single integer $ t $ ( $ 1 \le t \le 10^4 $ ) — the number of test cases.

The first line of each test case contains four integers $ n $ , $ k $ , $ w $ , and $ h $ ( $ 1 \le n, w, h \le 10^6 $ ; $ 1 \le k \le n $ ).

The second line contains a single string $ s $ of size $ n $ ( $ s_i \in \{\texttt{L}, \texttt{R}, \texttt{U}, \texttt{D}\} $ ) — the script to be executed.

It is guaranteed that the sum of $ n $ over all test cases does not exceed $ 10^6 $ .

## 输出格式

For each test case, print a single integer — the number of times the robot reaches $ (0, 0) $ when executing script $ s $ for $ k $ times continuously.

## 说明/提示

In the first test case, the robot only moves up and right. In the end, it occupies the position $ (2, 2) $ but never visits $ (0, 0) $ . So the answer is $ 0 $ .

In the second test case, each time executing the script the robot visits the origin twice. And since $ k=2 $ , it visits the origin $ 2 \cdot 2 = 4 $ times overall.

 ![](https://cdn.luogu.com.cn/upload/vjudge_pic/CF1993F1/4c04dc66914a3e1ee672ced7111b24a5891eec80.png)In the third test case, the visualization is shown as below:

 ![](https://cdn.luogu.com.cn/upload/vjudge_pic/CF1993F1/354b17fd45a6d2914b35f5325993193690563e94.png)

## 样例 #1

### 输入

```
5
2 2 2 2
UR
4 2 1 1
LLDD
6 3 3 1
RLRRRL
5 5 3 3
RUURD
7 5 3 4
RRDLUUU
```

### 输出

```
0
4
3
0
1
```

