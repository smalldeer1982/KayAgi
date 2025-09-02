---
title: "New Year Concert"
layout: "post"
diff: 提高+/省选-
pid: CF1632D
tag: []
---

# New Year Concert

## 题目描述

New Year is just around the corner, which means that in School 179, preparations for the concert are in full swing.

There are $ n $ classes in the school, numbered from $ 1 $ to $ n $ , the $ i $ -th class has prepared a scene of length $ a_i $ minutes.

As the main one responsible for holding the concert, Idnar knows that if a concert has $ k $ scenes of lengths $ b_1 $ , $ b_2 $ , $ \ldots $ , $ b_k $ minutes, then the audience will get bored if there exist two integers $ l $ and $ r $ such that $ 1 \le l \le r \le k $ and $ \gcd(b_l, b_{l + 1}, \ldots, b_{r - 1}, b_r) = r - l + 1 $ , where $ \gcd(b_l, b_{l + 1}, \ldots, b_{r - 1}, b_r) $ is equal to the [greatest common divisor (GCD)](https://en.wikipedia.org/wiki/Greatest_common_divisor) of the numbers $ b_l $ , $ b_{l + 1} $ , $ \ldots $ , $ b_{r - 1} $ , $ b_r $ .

To avoid boring the audience, Idnar can ask any number of times (possibly zero) for the $ t $ -th class ( $ 1 \le t \le k $ ) to make a new scene $ d $ minutes in length, where $ d $ can be any positive integer. Thus, after this operation, $ b_t $ is equal to $ d $ . Note that $ t $ and $ d $ can be different for each operation.

For a sequence of scene lengths $ b_1 $ , $ b_2 $ , $ \ldots $ , $ b_{k} $ , let $ f(b) $ be the minimum number of classes Idnar has to ask to change their scene if he wants to avoid boring the audience.

Idnar hasn't decided which scenes will be allowed for the concert, so he wants to know the value of $ f $ for each non-empty prefix of $ a $ . In other words, Idnar wants to know the values of $ f(a_1) $ , $ f(a_1 $ , $ a_2) $ , $ \ldots $ , $ f(a_1 $ , $ a_2 $ , $ \ldots $ , $ a_n) $ .

## 输入格式

The first line contains a single integer $ n $ ( $ 1 \le n \le 2 \cdot 10^5 $ ) — the number of classes in the school.

The second line contains $ n $ positive integers $ a_1 $ , $ a_2 $ , $ \ldots $ , $ a_n $ ( $ 1 \le a_i \le 10^9 $ ) — the lengths of the class scenes.

## 输出格式

Print a sequence of $ n $ integers in a single line — $ f(a_1) $ , $ f(a_1 $ , $ a_2) $ , $ \ldots $ , $ f(a_1 $ , $ a_2 $ , $ \ldots $ , $ a_n) $ .

## 说明/提示

In the first test we can change $ 1 $ to $ 2 $ , so the answer is $ 1 $ .

In the second test:

- $ [1] $ can be changed into $ [2] $ ,
- $ [1, 4] $ can be changed into $ [3, 4] $ ,
- $ [1, 4, 2] $ can be changed into $ [2, 3, 2] $ .

## 样例 #1

### 输入

```
1
1
```

### 输出

```
1
```

## 样例 #2

### 输入

```
3
1 4 2
```

### 输出

```
1 1 2
```

## 样例 #3

### 输入

```
7
2 12 4 8 18 3 6
```

### 输出

```
0 1 1 1 2 2 2
```

