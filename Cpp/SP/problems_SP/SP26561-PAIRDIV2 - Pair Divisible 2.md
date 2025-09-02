---
title: "PAIRDIV2 - Pair Divisible 2"
layout: "post"
diff: 省选/NOI-
pid: SP26561
tag: []
---

# PAIRDIV2 - Pair Divisible 2

## 题目描述

Let $ C(N, a, b) $ be the number of integer pairs $ (x, y) $ in $ 1 \le x \le a $ , $ 1 \le y \le b $ such that $ xy $ is divisible by $ N $ .

Given $ N $ , $ a $ and $ b $ , find $ C(N, a, b) $ **modulo** $ 10^{9} $ .

## 输入格式

The first line contains $ T $ , the number of test cases.

In each of the next $ T $ lines, you are given three numbers $ N $ , $ a $ and $ b $ .

## 输出格式

For each test case, print $ C(N, a, b) $ **modulo** $ 10^{9} $ .

## 样例 #1

### 输入

```
5
1 1 1
2 2 2
10 10 10
100 100 100
1 10000 100000
```

### 输出

```
1
3
27
520
0
```

