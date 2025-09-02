---
title: "Bitwise Slides"
layout: "post"
diff: 难度0
pid: CF2066C
tag: []
---

# Bitwise Slides

## 题目描述

You are given an array $ a_1, a_2, \ldots, a_n $ . Also, you are given three variables $ P,Q,R $ , initially equal to zero.

You need to process all the numbers $ a_1, a_2, \ldots, a_n $ , in the order from $ 1 $ to $ n $ . When processing the next $ a_i $ , you must perform exactly one of the three actions of your choice:

1. $ P := P \oplus a_i $
2. $ Q := Q \oplus a_i $
3. $ R := R \oplus a_i $

 $ \oplus $ denotes the <a>bitwise XOR operation</a>.

When performing actions, you must follow the main rule: it is necessary that after each action, all three numbers $ P,Q,R $ are not pairwise distinct.

There are a total of $ 3^n $ ways to perform all $ n $ actions. How many of them do not violate the main rule? Since the answer can be quite large, find it modulo $ 10^9 + 7 $ .

## 输入格式

Each test contains multiple test cases. The first line contains the number of test cases $ t $ ( $ 1 \le t \le 10^4 $ ). The description of the test cases follows.

The first line of each test case contains an integer $ n $ ( $ 1 \le n \le 2 \cdot 10^5 $ ) — the length of the array $ a $ .

The second line of each test case contains $ n $ integers $ a_1, a_2, \ldots, a_n $ ( $ 1 \le a_i \le 10^9 $ ) — the elements of the array $ a $ .

It is guaranteed that the sum of the values of $ n $ for all test cases does not exceed $ 2 \cdot 10^5 $ .

## 输出格式

For each test case, output the number of ways to perform all $ n $ actions without violating the main rule, modulo $ 10^9 + 7 $ .

## 说明/提示

In the first test case, there are 3 valid sequences of operations: PPP, QQQ, RRR.

In the second test case, there are 9 valid sequences of operations: PPPP, PPPQ, PPPR, QQQP, QQQQ, QQQR, RRRP, RRRQ, RRRR.

## 样例 #1

### 输入

```
5
3
1 7 9
4
179 1 1 179
5
1 2 3 3 2
12
8 2 5 3 9 1 8 12 9 9 9 4
1
1000000000
```

### 输出

```
3
9
39
123
3
```

