---
title: "Jeff and Digits"
layout: "post"
diff: 入门
pid: CF352A
tag: []
---

# Jeff and Digits

## 题目描述

Jeff's got $ n $ cards, each card contains either digit 0, or digit 5. Jeff can choose several cards and put them in a line so that he gets some number. What is the largest possible number divisible by 90 Jeff can make from the cards he's got?

Jeff must make the number without leading zero. At that, we assume that number 0 doesn't contain any leading zeroes. Jeff doesn't have to use all the cards.

## 输入格式

The first line contains integer $ n $ $ (1<=n<=10^{3}) $ . The next line contains $ n $ integers $ a_{1} $ , $ a_{2} $ , $ ... $ , $ a_{n} $ ( $ a_{i}=0 $ or $ a_{i}=5 $ ). Number $ a_{i} $ represents the digit that is written on the $ i $ -th card.

## 输出格式

In a single line print the answer to the problem — the maximum number, divisible by 90. If you can't make any divisible by 90 number from the cards, print -1.

## 说明/提示

In the first test you can make only one number that is a multiple of 90 — $ 0 $ .

In the second test you can make number $ 5555555550 $ , it is a multiple of $ 90 $ .

## 样例 #1

### 输入

```
4
5 0 5 0

```

### 输出

```
0

```

## 样例 #2

### 输入

```
11
5 5 5 5 5 5 5 5 0 5 5

```

### 输出

```
5555555550

```

