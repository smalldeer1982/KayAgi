---
title: "XOR-distance"
layout: "post"
diff: 普及/提高-
pid: CF1918C
tag: []
---

# XOR-distance

## 题目描述

You are given integers $ a $ , $ b $ , $ r $ . Find the smallest value of $ |({a \oplus x}) - ({b \oplus x})| $ among all $ 0 \leq x \leq r $ .

 $ \oplus $ is the operation of [bitwise XOR](https://en.wikipedia.org/wiki/Bitwise_operation#XOR), and $ |y| $ is [absolute value](https://en.wikipedia.org/wiki/Absolute_value) of $ y $ .

## 输入格式

The first line contains a single integer $ t $ ( $ 1 \le t \le 10^4 $ ) — the number of test cases.

Each test case contains integers $ a $ , $ b $ , $ r $ ( $ 0 \le a, b, r \le 10^{18} $ ).

## 输出格式

For each test case, output a single number — the smallest possible value.

## 说明/提示

In the first test, when $ r = 0 $ , then $ x $ is definitely equal to $ 0 $ , so the answer is $ |{4 \oplus 0} - {6 \oplus 0}| = |4 - 6| = 2 $ .

In the second test:

- When $ x = 0 $ , $ |{0 \oplus 0} - {3 \oplus 0}| = |0 - 3| = 3 $ .
- When $ x = 1 $ , $ |{0 \oplus 1} - {3 \oplus 1}| = |1 - 2| = 1 $ .
- When $ x = 2 $ , $ |{0 \oplus 2} - {3 \oplus 2}| = |2 - 1| = 1 $ .

Therefore, the answer is $ 1 $ .

In the third test, the minimum is achieved when $ x = 1 $ .

## 样例 #1

### 输入

```
10
4 6 0
0 3 2
9 6 10
92 256 23
165 839 201
1 14 5
2 7 2
96549 34359 13851
853686404475946 283666553522252166 127929199446003072
735268590557942972 916721749674600979 895150420120690183
```

### 输出

```
2
1
1
164
542
5
3
37102
27934920819538516
104449824168870225
```

