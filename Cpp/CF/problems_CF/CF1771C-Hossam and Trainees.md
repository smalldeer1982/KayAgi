---
title: "Hossam and Trainees"
layout: "post"
diff: 普及+/提高
pid: CF1771C
tag: []
---

# Hossam and Trainees

## 题目描述

Hossam has $ n $ trainees. He assigned a number $ a_i $ for the $ i $ -th trainee.

A pair of the $ i $ -th and $ j $ -th ( $ i \neq j $ ) trainees is called successful if there is an integer $ x $ ( $ x \geq 2 $ ), such that $ x $ divides $ a_i $ , and $ x $ divides $ a_j $ .

Hossam wants to know if there is a successful pair of trainees.

Hossam is very tired now, so he asks you for your help!

## 输入格式

The input consists of multiple test cases. The first line contains a single integer $ t $ ( $ 1 \le t \le 10^5 $ ), the number of test cases. Description of the test cases follows.

The first line of each test case contains an integer number $ n $ ( $ 2 \le n \le 10^5 $ ).

The second line of each test case contains $ n $ integers, the number of each trainee $ a_1, a_2, \dots, a_n $ ( $ 1 \le a_i \le 10^9 $ ).

It is guaranteed that the sum of $ n $ over all test cases does not exceed $ 10^5 $ .

## 输出格式

Print the answer — "YES" (without quotes) if there is a successful pair of trainees and "NO" otherwise. You can print each letter in any case.

## 说明/提示

In the first example, the first trainee and the second trainee make up a successful pair:

 $ a_1 = 32, a_2 = 48 $ , you can choose $ x = 4 $ .

## 样例 #1

### 输入

```
2
3
32 48 7
3
14 5 9
```

### 输出

```
YES
NO
```

