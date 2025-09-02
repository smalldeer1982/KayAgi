---
title: "Minimum LCM"
layout: "post"
diff: 普及-
pid: CF1765M
tag: []
---

# Minimum LCM

## 题目描述

You are given an integer $ n $ .

Your task is to find two positive (greater than $ 0 $ ) integers $ a $ and $ b $ such that $ a+b=n $ and the least common multiple (LCM) of $ a $ and $ b $ is the minimum among all possible values of $ a $ and $ b $ . If there are multiple answers, you can print any of them.

## 输入格式

The first line contains a single integer $ t $ ( $ 1 \le t \le 100 $ ) — the number of test cases.

The first line of each test case contains a single integer $ n $ ( $ 2 \le n \le 10^9 $ ).

## 输出格式

For each test case, print two positive integers $ a $ and $ b $ — the answer to the problem. If there are multiple answers, you can print any of them.

## 说明/提示

In the second example, there are $ 8 $ possible pairs of $ a $ and $ b $ :

- $ a = 1 $ , $ b = 8 $ , $ LCM(1, 8) = 8 $ ;
- $ a = 2 $ , $ b = 7 $ , $ LCM(2, 7) = 14 $ ;
- $ a = 3 $ , $ b = 6 $ , $ LCM(3, 6) = 6 $ ;
- $ a = 4 $ , $ b = 5 $ , $ LCM(4, 5) = 20 $ ;
- $ a = 5 $ , $ b = 4 $ , $ LCM(5, 4) = 20 $ ;
- $ a = 6 $ , $ b = 3 $ , $ LCM(6, 3) = 6 $ ;
- $ a = 7 $ , $ b = 2 $ , $ LCM(7, 2) = 14 $ ;
- $ a = 8 $ , $ b = 1 $ , $ LCM(8, 1) = 8 $ .

In the third example, there are $ 5 $ possible pairs of $ a $ and $ b $ :

- $ a = 1 $ , $ b = 4 $ , $ LCM(1, 4) = 4 $ ;
- $ a = 2 $ , $ b = 3 $ , $ LCM(2, 3) = 6 $ ;
- $ a = 3 $ , $ b = 2 $ , $ LCM(3, 2) = 6 $ ;
- $ a = 4 $ , $ b = 1 $ , $ LCM(4, 1) = 4 $ .

## 样例 #1

### 输入

```
4
2
9
5
10
```

### 输出

```
1 1
3 6
1 4
5 5
```

