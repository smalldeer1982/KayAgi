---
title: "Jellyfish and Math"
layout: "post"
diff: 省选/NOI-
pid: CF1874B
tag: []
---

# Jellyfish and Math

## 题目描述

Jellyfish is given the non-negative integers $ a $ , $ b $ , $ c $ , $ d $ and $ m $ . Initially $ (x,y)=(a,b) $ . Jellyfish wants to do several operations so that $ (x,y)=(c,d) $ .

For each operation, she can do one of the following:

- $ x := x\,\&\,y $ ,
- $ x := x\,|\,y $ ,
- $ y := x \oplus y $ ,
- $ y := y \oplus m $ .

Here $ \& $ denotes the [bitwise AND operation](https://en.wikipedia.org/wiki/Bitwise_operation#AND), $ | $ denotes the [bitwise OR operation](https://en.wikipedia.org/wiki/Bitwise_operation#OR) and $ \oplus $ denotes the [bitwise XOR operation](https://en.wikipedia.org/wiki/Bitwise_operation#XOR).

Now Jellyfish asks you for the minimum number of operations such that $ (x,y)=(c,d) $ .

## 输入格式

Each test contains multiple test cases. The first line contains the number of test cases $ t $ ( $ 1 \leq t \leq 10^5 $ ). The description of the test cases follows.

The only line of each test case contains five integers, $ a $ , $ b $ , $ c $ , $ d $ and $ m $ ( $ 0 \leq a, b, c, d, m < 2^{30} $ ).

## 输出格式

For each test case, output a single integer — the minimum number of operations. If this cannot be achieved, output $ -1 $ instead.

## 说明/提示

In the first test case, we can do the operation $ y = x \oplus y $ .

In the second test case, it is not possible to change $ (x,y)=(1,2) $ using any sequence of operations.

In the third test case, we can do the operation $ x = x\,\&\,y $ followed by the operation $ y = y \oplus m $ .

## 样例 #1

### 输入

```
10
1 0 1 1 1
3 3 1 2 1
1 6 0 7 1
2 4 4 9 8
21 4 0 17 28
50 50 0 0 39
95 33 1 33 110
138 202 174 64 108
78 340 68 340 461
457 291 491 566 766
```

### 输出

```
1
-1
2
-1
-1
2
1
4
1
3
```

