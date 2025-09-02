---
title: "Digits Sum"
layout: "post"
diff: 入门
pid: CF1553A
tag: []
---

# Digits Sum

## 题目描述

Let's define $ S(x) $ to be the sum of digits of number $ x $ written in decimal system. For example, $ S(5) = 5 $ , $ S(10) = 1 $ , $ S(322) = 7 $ .

We will call an integer $ x $ interesting if $ S(x + 1) < S(x) $ . In each test you will be given one integer $ n $ . Your task is to calculate the number of integers $ x $ such that $ 1 \le x \le n $ and $ x $ is interesting.

## 输入格式

The first line contains one integer $ t $ ( $ 1 \le t \le 1000 $ ) — number of test cases.

Then $ t $ lines follow, the $ i $ -th line contains one integer $ n $ ( $ 1 \le n \le 10^9 $ ) for the $ i $ -th test case.

## 输出格式

Print $ t $ integers, the $ i $ -th should be the answer for the $ i $ -th test case.

## 说明/提示

The first interesting number is equal to $ 9 $ .

## 样例 #1

### 输入

```
5
1
9
10
34
880055535
```

### 输出

```
0
1
1
3
88005553
```

