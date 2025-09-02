---
title: "Getting Zero"
layout: "post"
diff: 普及/提高-
pid: CF1661B
tag: []
---

# Getting Zero

## 题目描述

Suppose you have an integer $ v $ . In one operation, you can:

- either set $ v = (v + 1) \bmod 32768 $
- or set $ v = (2 \cdot v) \bmod 32768 $ .

You are given $ n $ integers $ a_1, a_2, \dots, a_n $ . What is the minimum number of operations you need to make each $ a_i $ equal to $ 0 $ ?

## 输入格式

The first line contains the single integer $ n $ ( $ 1 \le n \le 32768 $ ) — the number of integers.

The second line contains $ n $ integers $ a_1, a_2, \dots, a_n $ ( $ 0 \le a_i < 32768 $ ).

## 输出格式

Print $ n $ integers. The $ i $ -th integer should be equal to the minimum number of operations required to make $ a_i $ equal to $ 0 $ .

## 说明/提示

Let's consider each $ a_i $ :

- $ a_1 = 19 $ . You can, firstly, increase it by one to get $ 20 $ and then multiply it by two $ 13 $ times. You'll get $ 0 $ in $ 1 + 13 = 14 $ steps.
- $ a_2 = 32764 $ . You can increase it by one $ 4 $ times: $ 32764 \rightarrow 32765 \rightarrow 32766 \rightarrow 32767 \rightarrow 0 $ .
- $ a_3 = 10240 $ . You can multiply it by two $ 4 $ times: $ 10240 \rightarrow 20480 \rightarrow 8192 \rightarrow 16384 \rightarrow 0 $ .
- $ a_4 = 49 $ . You can multiply it by two $ 15 $ times.

## 样例 #1

### 输入

```
4
19 32764 10240 49
```

### 输出

```
14 4 4 15
```

