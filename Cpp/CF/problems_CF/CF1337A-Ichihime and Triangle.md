---
title: "Ichihime and Triangle"
layout: "post"
diff: 入门
pid: CF1337A
tag: []
---

# Ichihime and Triangle

## 题目描述

Ichihime is the current priestess of the Mahjong Soul Temple. She claims to be human, despite her cat ears.

These days the temple is holding a math contest. Usually, Ichihime lacks interest in these things, but this time the prize for the winner is her favorite — cookies. Ichihime decides to attend the contest. Now she is solving the following problem.

![](https://cdn.luogu.com.cn/upload/vjudge_pic/CF1337A/bad2678e993488b99e385b25367de54e5d69583f.png)You are given four positive integers $ a $ , $ b $ , $ c $ , $ d $ , such that $ a \leq b \leq c \leq d $ .

Your task is to find three integers $ x $ , $ y $ , $ z $ , satisfying the following conditions:

- $ a \leq x \leq b $ .
- $ b \leq y \leq c $ .
- $ c \leq z \leq d $ .
- There exists a triangle with a positive non-zero area and the lengths of its three sides are $ x $ , $ y $ , and $ z $ .

Ichihime desires to get the cookie, but the problem seems too hard for her. Can you help her?

## 输入格式

The first line contains a single integer $ t $ ( $ 1 \leq t \leq 1000 $ ) — the number of test cases.

The next $ t $ lines describe test cases. Each test case is given as four space-separated integers $ a $ , $ b $ , $ c $ , $ d $ ( $ 1 \leq a \leq b \leq c \leq d \leq 10^9 $ ).

## 输出格式

For each test case, print three integers $ x $ , $ y $ , $ z $ — the integers you found satisfying the conditions given in the statement.

It is guaranteed that the answer always exists. If there are multiple answers, print any.

## 说明/提示

One of the possible solutions to the first test case:

![](https://cdn.luogu.com.cn/upload/vjudge_pic/CF1337A/49528ea2d26d24e7f32d5d00819a25495e02f95c.png)

One of the possible solutions to the second test case:

![](https://cdn.luogu.com.cn/upload/vjudge_pic/CF1337A/8e967d59d86c6aa1a42fe9df5eb35c845cfbc8ac.png)

## 样例 #1

### 输入

```
4
1 3 5 7
1 5 5 7
100000 200000 300000 400000
1 1 977539810 977539810
```

### 输出

```
3 4 5
5 5 5
182690 214748 300999
1 977539810 977539810
```

