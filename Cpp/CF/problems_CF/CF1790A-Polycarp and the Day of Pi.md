---
title: "Polycarp and the Day of Pi"
layout: "post"
diff: 入门
pid: CF1790A
tag: []
---

# Polycarp and the Day of Pi

## 题目描述

On March 14, the day of the number $ \pi $ is celebrated all over the world. This is a very important mathematical constant equal to the ratio of the circumference of a circle to its diameter.

Polycarp was told at school that the number $ \pi $ is irrational, therefore it has an infinite number of digits in decimal notation. He wanted to prepare for the Day of the number $ \pi $ by memorizing this number as accurately as possible.

Polycarp wrote out all the digits that he managed to remember. For example, if Polycarp remembered $ \pi $ as $ 3.1415 $ , he wrote out 31415.

Polycarp was in a hurry and could have made a mistake, so you decided to check how many first digits of the number $ \pi $ Polycarp actually remembers correctly.

## 输入格式

The first line of the input data contains the single integer $ t $ ( $ 1 \le t \le 10^3 $ ) — the number of test cases in the test.

Each test case is described by a single string of digits $ n $ , which was written out by Polycarp.

The string $ n $ contains up to $ 30 $ digits.

## 输出格式

Output $ t $ integers, each of which is the answer to the corresponding test case, that is how many first digits of the number $ \pi $ Polycarp remembers correctly.

## 样例 #1

### 输入

```
9
000
3
4141592653
141592653589793238462643383279
31420
31415
314159265358
27182
314159265358979323846264338327
```

### 输出

```
0
1
0
0
3
5
12
0
30
```

