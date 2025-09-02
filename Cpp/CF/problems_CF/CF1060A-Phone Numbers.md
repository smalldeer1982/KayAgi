---
title: "Phone Numbers"
layout: "post"
diff: 普及-
pid: CF1060A
tag: []
---

# Phone Numbers

## 题目描述

Let's call a string a phone number if it has length 11 and fits the pattern "8xxxxxxxxxx", where each "x" is replaced by a digit.

For example, "80123456789" and "80000000000" are phone numbers, while "8012345678" and "79000000000" are not.

You have $ n $ cards with digits, and you want to use them to make as many phone numbers as possible. Each card must be used in at most one phone number, and you don't have to use all cards. The phone numbers do not necessarily have to be distinct.

## 输入格式

The first line contains an integer $ n $ — the number of cards with digits that you have ( $ 1 \leq n \leq 100 $ ).

The second line contains a string of $ n $ digits (characters "0", "1", ..., "9") $ s_1, s_2, \ldots, s_n $ . The string will not contain any other characters, such as leading or trailing spaces.

## 输出格式

If at least one phone number can be made from these cards, output the maximum number of phone numbers that can be made. Otherwise, output 0.

## 说明/提示

In the first example, one phone number, "8000000000", can be made from these cards.

In the second example, you can make two phone numbers from the cards, for example, "80123456789" and "80123456789".

In the third example you can't make any phone number from the given cards.

## 样例 #1

### 输入

```
11
00000000008

```

### 输出

```
1

```

## 样例 #2

### 输入

```
22
0011223344556677889988

```

### 输出

```
2

```

## 样例 #3

### 输入

```
11
31415926535

```

### 输出

```
0

```

