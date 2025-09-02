---
title: "Simple Design"
layout: "post"
diff: 入门
pid: CF1884A
tag: []
---

# Simple Design

## 题目描述

A positive integer is called $ k $ -beautiful, if the digit sum of the decimal representation of this number is divisible by $ k^{\dagger} $ . For example, $ 9272 $ is $ 5 $ -beautiful, since the digit sum of $ 9272 $ is $ 9 + 2 + 7 + 2 = 20 $ .

You are given two integers $ x $ and $ k $ . Please find the smallest integer $ y \ge x $ which is $ k $ -beautiful.

 $ ^{\dagger} $ An integer $ n $ is divisible by $ k $ if there exists an integer $ m $ such that $ n = k \cdot m $ .

## 输入格式

Each test contains multiple test cases. The first line contains the number of test cases $ t $ ( $ 1 \le t \le 10^4 $ ). The description of the test cases follows.

The only line of each test case contains two integers $ x $ and $ k $ ( $ 1 \le x \le 10^9 $ , $ 1 \le k \le 10 $ ).

## 输出格式

For each test case, output the smallest integer $ y \ge x $ which is $ k $ -beautiful.

## 说明/提示

In the first test case, numbers from $ 1 $ to $ 4 $ consist of a single digit, thus the digit sum is equal to the number itself. None of the integers from $ 1 $ to $ 4 $ are divisible by $ 5 $ .

In the fourth test case, the digit sum of $ 777 $ is $ 7 + 7 + 7 = 21 $ which is already divisible by $ 3 $ .

## 样例 #1

### 输入

```
6
1 5
10 8
37 9
777 3
1235 10
1 10
```

### 输出

```
5
17
45
777
1243
19
```

