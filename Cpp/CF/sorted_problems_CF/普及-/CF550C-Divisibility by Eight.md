---
title: "Divisibility by Eight"
layout: "post"
diff: 普及-
pid: CF550C
tag: ['动态规划 DP', '枚举']
---

# Divisibility by Eight

## 题目描述

You are given a non-negative integer $ n $ , its decimal representation consists of at most $ 100 $ digits and doesn't contain leading zeroes.

Your task is to determine if it is possible in this case to remove some of the digits (possibly not remove any digit at all) so that the result contains at least one digit, forms a non-negative integer, doesn't have leading zeroes and is divisible by 8. After the removing, it is forbidden to rearrange the digits.

If a solution exists, you should print it.

## 输入格式

The single line of the input contains a non-negative integer $ n $ . The representation of number $ n $ doesn't contain any leading zeroes and its length doesn't exceed $ 100 $ digits.

## 输出格式

Print "NO" (without quotes), if there is no such way to remove some digits from number $ n $ .

Otherwise, print "YES" in the first line and the resulting number after removing digits from number $ n $ in the second line. The printed number must be divisible by $ 8 $ .

If there are multiple possible answers, you may print any of them.

## 样例 #1

### 输入

```
3454

```

### 输出

```
YES
344

```

## 样例 #2

### 输入

```
10

```

### 输出

```
YES
0

```

## 样例 #3

### 输入

```
111111

```

### 输出

```
NO

```

