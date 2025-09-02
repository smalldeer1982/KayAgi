---
title: "Magic Numbers"
layout: "post"
diff: 提高+/省选-
pid: CF628D
tag: []
---

# Magic Numbers

## 题目描述

Consider the decimal presentation of an integer. Let's call a number d-magic if digit $ d $ appears in decimal presentation of the number on even positions and nowhere else.

For example, the numbers $ 1727374 $ , $ 17 $ , $ 1 $ are 7-magic but $ 77 $ , $ 7 $ , $ 123 $ , $ 34 $ , $ 71 $ are not 7-magic. On the other hand the number $ 7 $ is 0-magic, $ 123 $ is 2-magic, $ 34 $ is 4-magic and $ 71 $ is 1-magic.

Find the number of d-magic numbers in the segment $ [a,b] $ that are multiple of $ m $ . Because the answer can be very huge you should only find its value modulo $ 10^{9}+7 $ (so you should find the remainder after dividing by $ 10^{9}+7 $ ).

## 输入格式

The first line contains two integers $ m,d $ ( $ 1<=m<=2000 $ , $ 0<=d<=9 $ ) — the parameters from the problem statement.

The second line contains positive integer $ a $ in decimal presentation (without leading zeroes).

The third line contains positive integer $ b $ in decimal presentation (without leading zeroes).

It is guaranteed that $ a<=b $ , the number of digits in $ a $ and $ b $ are the same and don't exceed $ 2000 $ .

## 输出格式

Print the only integer $ a $ — the remainder after dividing by $ 10^{9}+7 $ of the number of d-magic numbers in segment $ [a,b] $ that are multiple of $ m $ .

## 说明/提示

The numbers from the answer of the first example are $ 16 $ , $ 26 $ , $ 36 $ , $ 46 $ , $ 56 $ , $ 76 $ , $ 86 $ and $ 96 $ .

The numbers from the answer of the second example are $ 2 $ , $ 4 $ , $ 6 $ and $ 8 $ .

The numbers from the answer of the third example are $ 1767 $ , $ 2717 $ , $ 5757 $ , $ 6707 $ , $ 8797 $ and $ 9747 $ .

## 样例 #1

### 输入

```
2 6
10
99

```

### 输出

```
8

```

## 样例 #2

### 输入

```
2 0
1
9

```

### 输出

```
4

```

## 样例 #3

### 输入

```
19 7
1000
9999

```

### 输出

```
6

```

