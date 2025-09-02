---
title: "Stripe"
layout: "post"
diff: 普及/提高-
pid: CF18C
tag: ['模拟', '枚举', '前缀和']
---

# Stripe

## 题目描述

Once Bob took a paper stripe of $ n $ squares (the height of the stripe is 1 square). In each square he wrote an integer number, possibly negative. He became interested in how many ways exist to cut this stripe into two pieces so that the sum of numbers from one piece is equal to the sum of numbers from the other piece, and each piece contains positive integer amount of squares. Would you help Bob solve this problem?

## 输入格式

The first input line contains integer $ n $ ( $ 1<=n<=10^{5} $ ) — amount of squares in the stripe. The second line contains $ n $ space-separated numbers — they are the numbers written in the squares of the stripe. These numbers are integer and do not exceed 10000 in absolute value.

## 输出格式

Output the amount of ways to cut the stripe into two non-empty pieces so that the sum of numbers from one piece is equal to the sum of numbers from the other piece. Don't forget that it's allowed to cut the stripe along the squares' borders only.

## 样例 #1

### 输入

```
9
1 5 -6 7 9 -16 0 -2 2

```

### 输出

```
3

```

## 样例 #2

### 输入

```
3
1 1 1

```

### 输出

```
0

```

## 样例 #3

### 输入

```
2
0 0

```

### 输出

```
1

```

