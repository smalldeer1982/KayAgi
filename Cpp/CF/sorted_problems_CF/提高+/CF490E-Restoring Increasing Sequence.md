---
title: "Restoring Increasing Sequence"
layout: "post"
diff: 提高+/省选-
pid: CF490E
tag: ['字符串', '枚举', '构造']
---

# Restoring Increasing Sequence

## 题目描述

Peter wrote on the board a strictly increasing sequence of positive integers $ a_{1},a_{2},...,a_{n} $ . Then Vasil replaced some digits in the numbers of this sequence by question marks. Thus, each question mark corresponds to exactly one lost digit.

Restore the the original sequence knowing digits remaining on the board.

## 输入格式

The first line of the input contains integer $ n $ ( $ 1<=n<=10^{5} $ ) — the length of the sequence. Next $ n $ lines contain one element of the sequence each. Each element consists only of digits and question marks. No element starts from digit 0. Each element has length from 1 to 8 characters, inclusive.

## 输出格式

If the answer exists, print in the first line "YES" (without the quotes). Next $ n $ lines must contain the sequence of positive integers — a possible variant of Peter's sequence. The found sequence must be strictly increasing, it must be transformed from the given one by replacing each question mark by a single digit. All numbers on the resulting sequence must be written without leading zeroes. If there are multiple solutions, print any of them.

If there is no answer, print a single line "NO" (without the quotes).

## 样例 #1

### 输入

```
3
?
18
1?

```

### 输出

```
YES
1
18
19

```

## 样例 #2

### 输入

```
2
??
?

```

### 输出

```
NO

```

## 样例 #3

### 输入

```
5
12224
12??5
12226
?0000
?00000

```

### 输出

```
YES
12224
12225
12226
20000
100000

```

