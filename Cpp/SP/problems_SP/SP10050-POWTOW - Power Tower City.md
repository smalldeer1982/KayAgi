---
title: "POWTOW - Power Tower City"
layout: "post"
diff: 省选/NOI-
pid: SP10050
tag: []
---

# POWTOW - Power Tower City

## 题目描述

You are living in a city build entirely of power towers such as 3^3^3 and 10^10^10^10. To enter a building you must type the last 9 digits of the number represented by the tower, written in decimal form, on a keypad next to the main entrance. You are not sharp enough at mental maths, but you can write a handy program to bring along in your pocket.

A power tower is defined as repeated exponentiation. We write this using [Knuth's up-arrow notation](http://en.wikipedia.org/wiki/Knuth's_up-arrow_notation) as: e↑↑a = e^e^...^e (a terms). Remember that ^ (exponentiation) is right assosiative. For example: 2↑↑4 = 2^2^2^2 = 2^(2^(2^2)) = 2^2^4 = 2^16 = 65536, and 3↑↑1 = 3. The value of a tower of heigh 0 is 1.

## 输入格式

The first line contains integer C in \[0..1000\], the number of test cases.

Then follows C lines, each with integers e,a in \[0..2147483647\]. (non-negative 32-bit ints).

## 输出格式

For each testcase output e↑↑a, or if the output has more than 9 digits, output "..." and then the last 9 digits.

## 样例 #1

### 输入

```
3
0 0
2 5
993306745 75707320
```

### 输出

```
1
...719156736
...884765625
```

