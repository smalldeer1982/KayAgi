---
title: "Minimum Possible LCM"
layout: "post"
diff: 提高+/省选-
pid: CF1154G
tag: []
---

# Minimum Possible LCM

## 题目描述

You are given an array $ a $ consisting of $ n $ integers $ a_1, a_2, \dots, a_n $ .

Your problem is to find such pair of indices $ i, j $ ( $ 1 \le i < j \le n $ ) that $ lcm(a_i, a_j) $ is minimum possible.

 $ lcm(x, y) $ is the least common multiple of $ x $ and $ y $ (minimum positive number such that both $ x $ and $ y $ are divisors of this number).

## 输入格式

The first line of the input contains one integer $ n $ ( $ 2 \le n \le 10^6 $ ) — the number of elements in $ a $ .

The second line of the input contains $ n $ integers $ a_1, a_2, \dots, a_n $ ( $ 1 \le a_i \le 10^7 $ ), where $ a_i $ is the $ i $ -th element of $ a $ .

## 输出格式

Print two integers $ i $ and $ j $ ( $ 1 \le i < j \le n $ ) such that the value of $ lcm(a_i, a_j) $ is minimum among all valid pairs $ i, j $ . If there are multiple answers, you can print any.

## 样例 #1

### 输入

```
5
2 4 8 3 6

```

### 输出

```
1 2

```

## 样例 #2

### 输入

```
5
5 2 11 3 7

```

### 输出

```
2 4

```

## 样例 #3

### 输入

```
6
2 5 10 1 10 2

```

### 输出

```
1 4

```

