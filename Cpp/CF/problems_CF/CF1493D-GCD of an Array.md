---
title: "GCD of an Array"
layout: "post"
diff: 提高+/省选-
pid: CF1493D
tag: []
---

# GCD of an Array

## 题目描述

You are given an array $ a $ of length $ n $ . You are asked to process $ q $ queries of the following format: given integers $ i $ and $ x $ , multiply $ a_i $ by $ x $ .

After processing each query you need to output the [greatest common divisor (GCD)](https://en.wikipedia.org/wiki/Greatest_common_divisor) of all elements of the array $ a $ .

Since the answer can be too large, you are asked to output it modulo $ 10^9+7 $ .

## 输入格式

The first line contains two integers — $ n $ and $ q $ ( $ 1 \le n, q \le 2 \cdot 10^5 $ ).

The second line contains $ n $ integers $ a_1, a_2, \ldots, a_n $ ( $ 1 \le a_i \le 2 \cdot 10^5 $ ) — the elements of the array $ a $ before the changes.

The next $ q $ lines contain queries in the following format: each line contains two integers $ i $ and $ x $ ( $ 1 \le i \le n $ , $ 1 \le x \le 2 \cdot 10^5 $ ).

## 输出格式

Print $ q $ lines: after processing each query output the GCD of all elements modulo $ 10^9+7 $ on a separate line.

## 说明/提示

After the first query the array is $ [12, 6, 8, 12] $ , $ \operatorname{gcd}(12, 6, 8, 12) = 2 $ .

After the second query — $ [12, 18, 8, 12] $ , $ \operatorname{gcd}(12, 18, 8, 12) = 2 $ .

After the third query — $ [12, 18, 24, 12] $ , $ \operatorname{gcd}(12, 18, 24, 12) = 6 $ .

Here the $ \operatorname{gcd} $ function denotes the greatest common divisor.

## 样例 #1

### 输入

```
4 3
1 6 8 12
1 12
2 3
3 3
```

### 输出

```
2
2
6
```

