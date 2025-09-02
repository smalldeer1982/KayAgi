---
title: "Santa Claus and a Palindrome"
layout: "post"
diff: 提高+/省选-
pid: CF748D
tag: []
---

# Santa Claus and a Palindrome

## 题目描述

Santa Claus likes palindromes very much. There was his birthday recently. $ k $ of his friends came to him to congratulate him, and each of them presented to him a string $ s_{i} $ having the same length $ n $ . We denote the beauty of the $ i $ -th string by $ a_{i} $ . It can happen that $ a_{i} $ is negative — that means that Santa doesn't find this string beautiful at all.

Santa Claus is crazy about palindromes. He is thinking about the following question: what is the maximum possible total beauty of a palindrome which can be obtained by concatenating some (possibly all) of the strings he has? Each present can be used at most once. Note that all strings have the same length $ n $ .

Recall that a palindrome is a string that doesn't change after one reverses it.

Since the empty string is a palindrome too, the answer can't be negative. Even if all $ a_{i} $ 's are negative, Santa can obtain the empty string.

## 输入格式

The first line contains two positive integers $ k $ and $ n $ divided by space and denoting the number of Santa friends and the length of every string they've presented, respectively ( $ 1<=k,n<=100000 $ ; $ n·k <=100000 $ ).

 $ k $ lines follow. The $ i $ -th of them contains the string $ s_{i} $ and its beauty $ a_{i} $ ( $ -10000<=a_{i}<=10000 $ ). The string consists of $ n $ lowercase English letters, and its beauty is integer. Some of strings may coincide. Also, equal strings can have different beauties.

## 输出格式

In the only line print the required maximum possible beauty.

## 说明/提示

In the first example Santa can obtain abbaaaxyxaaabba by concatenating strings $ 5 $ , $ 2 $ , $ 7 $ , $ 6 $ and $ 3 $ (in this order).

## 样例 #1

### 输入

```
7 3
abb 2
aaa -3
bba -1
zyz -4
abb 5
aaa 7
xyx 4

```

### 输出

```
12

```

## 样例 #2

### 输入

```
3 1
a 1
a 2
a 3

```

### 输出

```
6

```

## 样例 #3

### 输入

```
2 5
abcde 10000
abcde 10000

```

### 输出

```
0

```

