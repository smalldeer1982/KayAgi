---
title: "Divisible Pairs"
layout: "post"
diff: 普及/提高-
pid: CF1931D
tag: []
---

# Divisible Pairs

## 题目描述

Polycarp has two favorite integers $ x $ and $ y $ (they can be equal), and he has found an array $ a $ of length $ n $ .

Polycarp considers a pair of indices $ \langle i, j \rangle $ ( $ 1 \le i < j \le n $ ) beautiful if:

- $ a_i + a_j $ is divisible by $ x $ ;
- $ a_i - a_j $ is divisible by $ y $ .

For example, if $ x=5 $ , $ y=2 $ , $ n=6 $ , $ a= $ \[ $ 1, 2, 7, 4, 9, 6 $ \], then the only beautiful pairs are:

- $ \langle 1, 5 \rangle $ : $ a_1 + a_5 = 1 + 9 = 10 $ ( $ 10 $ is divisible by $ 5 $ ) and $ a_1 - a_5 = 1 - 9 = -8 $ ( $ -8 $ is divisible by $ 2 $ );
- $ \langle 4, 6 \rangle $ : $ a_4 + a_6 = 4 + 6 = 10 $ ( $ 10 $ is divisible by $ 5 $ ) and $ a_4 - a_6 = 4 - 6 = -2 $ ( $ -2 $ is divisible by $ 2 $ ).

 Find the number of beautiful pairs in the array $ a $ .

## 输入格式

The first line of the input contains a single integer $ t $ ( $ 1 \le t \le 10^4 $ ) — the number of test cases. Then the descriptions of the test cases follow.

The first line of each test case contains three integers $ n $ , $ x $ , and $ y $ ( $ 2 \le n \le 2 \cdot 10^5 $ , $ 1 \le x, y \le 10^9 $ ) — the size of the array and Polycarp's favorite integers.

The second line of each test case contains $ n $ integers $ a_1, a_2, \dots, a_n $ ( $ 1 \le a_i \le 10^9 $ ) — the elements of the array.

It is guaranteed that the sum of $ n $ over all test cases does not exceed $ 2 \cdot 10^5 $ .

## 输出格式

For each test case, output a single integer — the number of beautiful pairs in the array $ a $ .

## 样例 #1

### 输入

```
7
6 5 2
1 2 7 4 9 6
7 9 5
1 10 15 3 8 12 15
9 4 10
14 10 2 2 11 11 13 5 6
9 5 6
10 7 6 7 9 7 7 10 10
9 6 2
4 9 7 1 2 2 13 3 15
9 2 3
14 6 1 15 12 15 8 2 15
10 5 7
13 3 3 2 12 11 3 7 13 14
```

### 输出

```
2
0
1
3
5
7
0
```

