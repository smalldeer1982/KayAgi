---
title: "Equalize the Array"
layout: "post"
diff: 普及/提高-
pid: CF1490F
tag: []
---

# Equalize the Array

## 题目描述

Polycarp was gifted an array $ a $ of length $ n $ . Polycarp considers an array beautiful if there exists a number $ C $ , such that each number in the array occurs either zero or $ C $ times. Polycarp wants to remove some elements from the array $ a $ to make it beautiful.

For example, if $ n=6 $ and $ a = [1, 3, 2, 1, 4, 2] $ , then the following options are possible to make the array $ a $ array beautiful:

- Polycarp removes elements at positions $ 2 $ and $ 5 $ , array $ a $ becomes equal to $ [1, 2, 1, 2] $ ;
- Polycarp removes elements at positions $ 1 $ and $ 6 $ , array $ a $ becomes equal to $ [3, 2, 1, 4] $ ;
- Polycarp removes elements at positions $ 1, 2 $ and $ 6 $ , array $ a $ becomes equal to $ [2, 1, 4] $ ;

Help Polycarp determine the minimum number of elements to remove from the array $ a $ to make it beautiful.

## 输入格式

The first line contains one integer $ t $ ( $ 1 \le t \le 10^4 $ ) — the number of test cases. Then $ t $ test cases follow.

The first line of each test case consists of one integer $ n $ ( $ 1 \le n \le 2 \cdot 10^5 $ ) — the length of the array $ a $ .

The second line of each test case contains $ n $ integers $ a_1, a_2, \ldots, a_n $ ( $ 1 \le a_i \le 10^9 $ ) — array $ a $ .

It is guaranteed that the sum of $ n $ over all test cases does not exceed $ 2 \cdot 10^5 $ .

## 输出格式

For each test case, output one integer — the minimum number of elements that Polycarp has to remove from the array $ a $ to make it beautiful.

## 样例 #1

### 输入

```
3
6
1 3 2 1 4 2
4
100 100 4 100
8
1 2 3 3 3 2 6 6
```

### 输出

```
2
1
2
```

