---
title: "Relatively Prime Powers"
layout: "post"
diff: 省选/NOI-
pid: CF1036F
tag: ['排序', '构造']
---

# Relatively Prime Powers

## 题目描述

Consider some positive integer $ x $ . Its prime factorization will be of form $ x = 2^{k_1} \cdot 3^{k_2} \cdot 5^{k_3} \cdot \dots $

Let's call $ x $ elegant if the greatest common divisor of the sequence $ k_1, k_2, \dots $ is equal to $ 1 $ . For example, numbers $ 5 = 5^1 $ , $ 12 = 2^2 \cdot 3 $ , $ 72 = 2^3 \cdot 3^2 $ are elegant and numbers $ 8 = 2^3 $ ( $ GCD = 3 $ ), $ 2500 = 2^2 \cdot 5^4 $ ( $ GCD = 2 $ ) are not.

Count the number of elegant integers from $ 2 $ to $ n $ .

Each testcase contains several values of $ n $ , for each of them you are required to solve the problem separately.

## 输入格式

The first line contains a single integer $ T $ ( $ 1 \le T \le 10^5 $ ) — the number of values of $ n $ in the testcase.

Each of the next $ T $ lines contains a single integer $ n_i $ ( $ 2 \le n_i \le 10^{18} $ ).

## 输出格式

Print $ T $ lines — the $ i $ -th line should contain the number of elegant numbers from $ 2 $ to $ n_i $ .

## 说明/提示

Here is the list of non-elegant numbers up to $ 10 $ :

- $ 4 = 2^2, GCD = 2 $ ;
- $ 8 = 2^3, GCD = 3 $ ;
- $ 9 = 3^2, GCD = 2 $ .

The rest have $ GCD = 1 $ .

## 样例 #1

### 输入

```
4
4
2
72
10

```

### 输出

```
2
1
61
6

```

