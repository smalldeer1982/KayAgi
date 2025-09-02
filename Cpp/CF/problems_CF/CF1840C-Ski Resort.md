---
title: "Ski Resort"
layout: "post"
diff: 普及-
pid: CF1840C
tag: []
---

# Ski Resort

## 题目描述

Dima Vatrushin is a math teacher at school. He was sent on vacation for $ n $ days for his good work. Dima has long dreamed of going to a ski resort, so he wants to allocate several consecutive days and go skiing. Since the vacation requires careful preparation, he will only go for at least $ k $ days.

You are given an array $ a $ containing the weather forecast at the resort. That is, on the $ i $ -th day, the temperature will be $ a_i $ degrees.

Dima was born in Siberia, so he can go on vacation only if the temperature does not rise above $ q $ degrees throughout the vacation.

Unfortunately, Dima was so absorbed in abstract algebra that he forgot how to count. He asks you to help him and count the number of ways to choose vacation dates at the resort.

## 输入格式

The first line of the input contains an integer $ t $ ( $ 1 \le t \le 10^4 $ ) — the number of test cases.

Then follow the descriptions of the test cases.

The first line of each test case contains three integers $ n $ , $ k $ , $ q $ ( $ 1 \le n \le 2 \cdot 10^5 $ , $ 1 \le k \le n $ , $ -10^9 \le q \le 10^9 $ ) — the length of the array $ a $ , the minimum number of days at the resort, and the maximum comfortable temperature for Dima.

The second line of each test case contains $ n $ integers $ a_1, a_2, a_3, \dots, a_n $ ( $ -10^9 \le a_i \le 10^9 $ ) — the temperature at the ski resort.

The sum of all $ n $ values over all test cases does not exceed $ 2 \cdot 10^5 $ .

## 输出格式

Output $ t $ integers, each of which is the answer to the corresponding test case — the number of ways for Dima to choose vacation dates at the resort.

## 说明/提示

In the first test case of the example, Dima can go on any day, so the suitable dates for him are \[1\], \[2\], \[3\], \[1, 2\], \[2, 3\], \[1, 2, 3\].

In the second and fourth test cases of the example, Dima cannot go on any day due to the high temperature, so there are no suitable dates.

In the third test case of the example, Dima can only go on the dates \[1, 2, 3\].

## 样例 #1

### 输入

```
7
3 1 15
-5 0 -10
5 3 -33
8 12 9 0 5
4 3 12
12 12 10 15
4 1 -5
0 -1 2 5
5 5 0
3 -1 4 -5 -3
1 1 5
5
6 1 3
0 3 -2 5 -4 -4
```

### 输出

```
6
0
1
0
0
1
9
```

