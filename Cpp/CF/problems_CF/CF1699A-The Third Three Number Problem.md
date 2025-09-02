---
title: "The Third Three Number Problem"
layout: "post"
diff: 入门
pid: CF1699A
tag: []
---

# The Third Three Number Problem

## 题目描述

You are given a positive integer $ n $ . Your task is to find any three integers $ a $ , $ b $ and $ c $ ( $ 0 \le a, b, c \le 10^9 $ ) for which $ (a\oplus b)+(b\oplus c)+(a\oplus c)=n $ , or determine that there are no such integers.

Here $ a \oplus b $ denotes the [bitwise XOR](https://en.wikipedia.org/wiki/Bitwise_operation#XOR) of $ a $ and $ b $ . For example, $ 2 \oplus 4 = 6 $ and $ 3 \oplus 1=2 $ .

## 输入格式

Each test contains multiple test cases. The first line contains a single integer $ t $ ( $ 1 \le t \le 10^4 $ ) — the number of test cases. The following lines contain the descriptions of the test cases.

The only line of each test case contains a single integer $ n $ ( $ 1 \le n \le 10^9 $ ).

## 输出格式

For each test case, print any three integers $ a $ , $ b $ and $ c $ ( $ 0 \le a, b, c \le 10^9 $ ) for which $ (a\oplus b)+(b\oplus c)+(a\oplus c)=n $ . If no such integers exist, print $ -1 $ .

## 说明/提示

In the first test case, $ a=3 $ , $ b=3 $ , $ c=1 $ , so $ (3 \oplus 3)+(3 \oplus 1) + (3 \oplus 1)=0+2+2=4 $ .

In the second test case, there are no solutions.

In the third test case, $ (2 \oplus 4)+(4 \oplus 6) + (2 \oplus 6)=6+2+4=12 $ .

## 样例 #1

### 输入

```
5
4
1
12
2046
194723326
```

### 输出

```
3 3 1
-1
2 4 6
69 420 666
12345678 87654321 100000000
```

