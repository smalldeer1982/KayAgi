---
title: "Turtle Fingers: Count the Values of k"
layout: "post"
diff: 普及-
pid: CF1933C
tag: ['枚举']
---

# Turtle Fingers: Count the Values of k

## 题目描述

You are given three positive integers $ a $ , $ b $ and $ l $ ( $ a,b,l>0 $ ).

It can be shown that there always exists a way to choose non-negative (i.e. $ \ge 0 $ ) integers $ k $ , $ x $ , and $ y $ such that $ l = k \cdot a^x \cdot b^y $ .

Your task is to find the number of distinct possible values of $ k $ across all such ways.

## 输入格式

The first line contains the integer $ t $ ( $ 1 \le t \le 10^4 $ ) — the number of test cases.

The following $ t $ lines contain three integers, $ a $ , $ b $ and $ l $ ( $ 2 \le a, b \le 100 $ , $ 1 \le l \le 10^6 $ ) — description of a test case.

## 输出格式

Output $ t $ lines, with the $ i $ -th ( $ 1 \le i \le t $ ) line containing an integer, the answer to the $ i $ -th test case.

## 说明/提示

In the first test case, $ a=2, b=5, l=20 $ . The possible values of $ k $ (and corresponding $ x,y $ ) are as follows:

- Choose $ k = 1, x = 2, y = 1 $ . Then $ k \cdot a^x \cdot b^y = 1 \cdot 2^2 \cdot 5^1 = 20 = l $ .
- Choose $ k = 2, x = 1, y = 1 $ . Then $ k \cdot a^x \cdot b^y = 2 \cdot 2^1 \cdot 5^1 = 20 = l $ .
- Choose $ k = 4, x = 0, y = 1 $ . Then $ k \cdot a^x \cdot b^y = 4 \cdot 2^0 \cdot 5^1 = 20 = l $ .
- Choose $ k = 5, x = 2, y = 0 $ . Then $ k \cdot a^x \cdot b^y = 5 \cdot 2^2 \cdot 5^0 = 20 = l $ .
- Choose $ k = 10, x = 1, y = 0 $ . Then $ k \cdot a^x \cdot b^y = 10 \cdot 2^1 \cdot 5^0 = 20 = l $ .
- Choose $ k = 20, x = 0, y = 0 $ . Then $ k \cdot a^x \cdot b^y = 20 \cdot 2^0 \cdot 5^0 = 20 = l $ .

In the second test case, $ a=2, b=5, l=21 $ . Note that $ l = 21 $ is not divisible by either $ a = 2 $ or $ b = 5 $ . Therefore, we can only set $ x = 0, y = 0 $ , which corresponds to $ k = 21 $ .

In the third test case, $ a=4, b=6, l=48 $ . The possible values of $ k $ (and corresponding $ x,y $ ) are as follows:

- Choose $ k = 2, x = 1, y = 1 $ . Then $ k \cdot a^x \cdot b^y = 2 \cdot 4^1 \cdot 6^1 = 48 = l $ .
- Choose $ k = 3, x = 2, y = 0 $ . Then $ k \cdot a^x \cdot b^y = 3 \cdot 4^2 \cdot 6^0 = 48 = l $ .
- Choose $ k = 8, x = 0, y = 1 $ . Then $ k \cdot a^x \cdot b^y = 8 \cdot 4^0 \cdot 6^1 = 48 = l $ .
- Choose $ k = 12, x = 1, y = 0 $ . Then $ k \cdot a^x \cdot b^y = 12 \cdot 4^1 \cdot 6^0 = 48 = l $ .
- Choose $ k = 48, x = 0, y = 0 $ . Then $ k \cdot a^x \cdot b^y = 48 \cdot 4^0 \cdot 6^0 = 48 = l $ .

## 样例 #1

### 输入

```
11
2 5 20
2 5 21
4 6 48
2 3 72
3 5 75
2 2 1024
3 7 83349
100 100 1000000
7 3 2
2 6 6
17 3 632043
```

### 输出

```
6
1
5
12
6
11
24
4
1
3
24
```

