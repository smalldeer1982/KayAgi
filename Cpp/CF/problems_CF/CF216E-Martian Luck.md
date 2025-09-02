---
title: "Martian Luck"
layout: "post"
diff: 普及+/提高
pid: CF216E
tag: []
---

# Martian Luck

## 题目描述

You know that the Martians use a number system with base $ k $ . Digit $ b $ ( $ 0<=b&lt;k $ ) is considered lucky, as the first contact between the Martians and the Earthlings occurred in year $ b $ (by Martian chronology).

A digital root $ d(x) $ of number $ x $ is a number that consists of a single digit, resulting after cascading summing of all digits of number $ x $ . Word "cascading" means that if the first summing gives us a number that consists of several digits, then we sum up all digits again, and again, until we get a one digit number.

For example, $ d(3504_{7})=d((3+5+0+4)_{7})=d(15_{7})=d((1+5)_{7})=d(6_{7})=6_{7} $ . In this sample the calculations are performed in the 7-base notation.

If a number's digital root equals $ b $ , the Martians also call this number lucky.

You have string $ s $ , which consists of $ n $ digits in the $ k $ -base notation system. Your task is to find, how many distinct substrings of the given string are lucky numbers. Leading zeroes are permitted in the numbers.

Note that substring $ s[i...\ j] $ of the string $ s=a_{1}a_{2}...\ a_{n} $ ( $ 1<=i<=j<=n $ ) is the string $ a_{i}a_{i+1}...\ a_{j} $ . Two substrings $ s[i_{1}...\ j_{1}] $ and $ s[i_{2}...\ j_{2}] $ of the string $ s $ are different if either $ i_{1}≠i_{2} $ or $ j_{1}≠j_{2} $ .

## 输入格式

The first line contains three integers $ k $ , $ b $ and $ n $ ( $ 2<=k<=10^{9} $ , $ 0<=b&lt;k $ , $ 1<=n<=10^{5} $ ).

The second line contains string $ s $ as a sequence of $ n $ integers, representing digits in the $ k $ -base notation: the $ i $ -th integer equals $ a_{i} $ ( $ 0<=a_{i}&lt;k $ ) — the $ i $ -th digit of string $ s $ . The numbers in the lines are space-separated.

## 输出格式

Print a single integer — the number of substrings that are lucky numbers.

Please, do not use the %lld specifier to read or write 64-bit integers in С++. It is preferred to use the cin, cout streams or the %I64d specifier.

## 说明/提示

In the first sample the following substrings have the sought digital root: $ s[1...\ 2] $ = "3 2", $ s[1...\ 3] $ = "3 2 0", $ s[3...\ 4] $ = "0 5", $ s[4...\ 4] $ = "5" and $ s[2...\ 6] $ = "2 0 5 6 1".

## 样例 #1

### 输入

```
10 5 6
3 2 0 5 6 1

```

### 输出

```
5
```

## 样例 #2

### 输入

```
7 6 4
3 5 0 4

```

### 输出

```
1
```

## 样例 #3

### 输入

```
257 0 3
0 0 256

```

### 输出

```
3
```

