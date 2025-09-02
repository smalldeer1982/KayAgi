---
title: "Lucky?"
layout: "post"
diff: 入门
pid: CF1676A
tag: ['模拟']
---

# Lucky?

## 题目描述

A ticket is a string consisting of six digits. A ticket is considered lucky if the sum of the first three digits is equal to the sum of the last three digits. Given a ticket, output if it is lucky or not. Note that a ticket can have leading zeroes.

## 输入格式

The first line of the input contains an integer $ t $ ( $ 1 \leq t \leq 10^3 $ ) — the number of testcases.

The description of each test consists of one line containing one string consisting of six digits.

## 输出格式

Output $ t $ lines, each of which contains the answer to the corresponding test case. Output "YES" if the given ticket is lucky, and "NO" otherwise.

You can output the answer in any case (for example, the strings "yEs", "yes", "Yes" and "YES" will be recognized as a positive answer).

## 说明/提示

In the first test case, the sum of the first three digits is $ 2 + 1 + 3 = 6 $ and the sum of the last three digits is $ 1 + 3 + 2 = 6 $ , they are equal so the answer is "YES".

In the second test case, the sum of the first three digits is $ 9 + 7 + 3 = 19 $ and the sum of the last three digits is $ 8 + 9 + 4 = 21 $ , they are not equal so the answer is "NO".

In the third test case, the sum of the first three digits is $ 0 + 4 + 5 = 9 $ and the sum of the last three digits is $ 2 + 0 + 7 = 9 $ , they are equal so the answer is "YES".

## 样例 #1

### 输入

```
5
213132
973894
045207
000000
055776
```

### 输出

```
YES
NO
YES
YES
NO
```

