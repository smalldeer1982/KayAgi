---
title: "Restore Array"
layout: "post"
diff: 提高+/省选-
pid: CF1028E
tag: []
---

# Restore Array

## 题目描述

While discussing a proper problem A for a Codeforces Round, Kostya created a cyclic array of positive integers $ a_1, a_2, \ldots, a_n $ . Since the talk was long and not promising, Kostya created a new cyclic array $ b_1, b_2, \ldots, b_{n} $ so that $ b_i = (a_i \mod a_{i + 1}) $ , where we take $ a_{n+1} = a_1 $ . Here $ mod $ is the [modulo operation](https://en.wikipedia.org/wiki/Modulo_operation). When the talk became interesting, Kostya completely forgot how array $ a $ had looked like. Suddenly, he thought that restoring array $ a $ from array $ b $ would be an interesting problem (unfortunately, not A).

## 输入格式

The first line contains a single integer $ n $ ( $ 2 \le n \le 140582 $ ) — the length of the array $ a $ .

The second line contains $ n $ integers $ b_1, b_2, \ldots, b_{n} $ ( $ 0 \le b_i \le 187126 $ ).

## 输出格式

If it is possible to restore some array $ a $ of length $ n $ so that $ b_i = a_i \mod a_{(i \mod n) + 1} $ holds for all $ i = 1, 2, \ldots, n $ , print «YES» in the first line and the integers $ a_1, a_2, \ldots, a_n $ in the second line. All $ a_i $ should satisfy $ 1 \le a_i \le 10^{18} $ . We can show that if an answer exists, then an answer with such constraint exists as well.

It it impossible to restore any valid $ a $ , print «NO» in one line.

You can print each letter in any case (upper or lower).

## 说明/提示

In the first example:

- $ 1 \mod 3 = 1 $
- $ 3 \mod 5 = 3 $
- $ 5 \mod 2 = 1 $
- $ 2 \mod 1 = 0 $

## 样例 #1

### 输入

```
4
1 3 1 0

```

### 输出

```
YES
1 3 5 2

```

## 样例 #2

### 输入

```
2
4 4

```

### 输出

```
NO

```

