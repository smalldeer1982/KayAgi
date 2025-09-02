---
title: "Yandex Cuneiform (Hard Version)"
layout: "post"
diff: NOI/NOI+/CTSC
pid: CF2046F2
tag: ['动态规划 DP', '动态规划优化', '凸包']
---

# Yandex Cuneiform (Hard Version)

## 题目描述

This is the hard version of the problem. The difference between the versions is that in this version, there is no restriction on the number of question marks. You can hack only if you solved all versions of this problem.

For a long time, no one could decipher Sumerian cuneiform. However, it has finally succumbed to pressure! Today, you have the chance to decipher Yandex cuneiform.

Yandex cuneiform is defined by the following rules:

1. An empty string is a Yandex cuneiform.
2. If you insert exactly one copy of each of the three letters 'Y', 'D', and 'X' into a Yandex cuneiform in such a way that no two adjacent letters become equal after the operation, you obtain a Yandex cuneiform.
3. If a string can't be obtained using the above rules, it is not a Yandex cuneiform.

You are given a template. A template is a string consisting of the characters 'Y', 'D', 'X', and '?'.

You need to check whether there exists a way to replace each question mark with 'Y', 'D', or 'X' to obtain a Yandex cuneiform, and if it exists, output any of the matching options, as well as a sequence of insertion operations to obtain the resulting cuneiform.

In this version of the problem, the number of question marks in the template can be arbitrary.

## 输入格式

Each test contains multiple test cases. The first line contains the number of test cases $ t $ ( $ 1 \le t \le 5 \cdot 10^4 $ ). The description of the test cases follows.

Each test case consists of a single line containing a template of length $ n $ ( $ 3 \leq n < 2 \cdot 10^5 $ , $ n \bmod 3 = 0 $ ), consisting only of characters 'Y', 'D', 'X', and '?'.

It is guaranteed that the sum of $ n $ over all test cases does not exceed $ 2 \cdot 10^5 $ .

## 输出格式

For each test case, output a single line containing 'NO' if it is not possible to obtain a cuneiform from the given template.

Otherwise, output 'YES' on the first line, and on the second line, any obtainable cuneiform. After that, you need to output the sequence of operations that leads to the cuneiform you printed.

A sequence of operations is described by $ \frac{n}{3} $ triples of pairs. A pair has the form c p, where $ c $ is one of the letters 'Y', 'D', or 'X', and $ p $ is the position at which the letter $ c $ should be inserted. The insertion position is the number of letters to skip from the beginning of the string for the insertion. For example, after inserting the character 'D' into the string "YDX" with $ p=3 $ , the result is "YDXD", and with $ p=0 $ , it is "DYDX". Note that the index cannot exceed the current length of the string.

The operations are applied from top to bottom, left to right. After inserting each triple to the string, there should be no two adjacent identical characters.

## 说明/提示

In the second example, the string is transformed like this: $ "" \to \mathtt{YDX} \to \mathtt{YDXDYX} $ .

## 样例 #1

### 输入

```
4
???
Y??D?X
???
D??DXYXYX
```

### 输出

```
YES
YDX
X 0 D 0 Y 0 
YES
YDXDYX
X 0 Y 0 D 1
X 2 D 3 Y 4
YES
YDX
Y 0 D 1 X 2
NO
```

