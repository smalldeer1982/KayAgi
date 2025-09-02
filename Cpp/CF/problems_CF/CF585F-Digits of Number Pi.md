---
title: "Digits of Number Pi"
layout: "post"
diff: 省选/NOI-
pid: CF585F
tag: []
---

# Digits of Number Pi

## 题目描述

Vasily has recently learned about the amazing properties of number $ π $ . In one of the articles it has been hypothesized that, whatever the sequence of numbers we have, in some position, this sequence is found among the digits of number $ π $ . Thus, if you take, for example, the epic novel "War and Peace" of famous Russian author Leo Tolstoy, and encode it with numbers, then we will find the novel among the characters of number $ π $ .

Vasily was absolutely delighted with this, because it means that all the books, songs and programs have already been written and encoded in the digits of $ π $ . Vasily is, of course, a bit wary that this is only a hypothesis and it hasn't been proved, so he decided to check it out.

To do this, Vasily downloaded from the Internet the archive with the sequence of digits of number $ π $ , starting with a certain position, and began to check the different strings of digits on the presence in the downloaded archive. Vasily quickly found short strings of digits, but each time he took a longer string, it turned out that it is not in the archive. Vasily came up with a definition that a string of length $ d $ is a half-occurrence if it contains a substring of length of at least ![](https://cdn.luogu.com.cn/upload/vjudge_pic/CF585F/cb7b717ebd73c919034f7aa2697aede2fa62dd31.png), which occurs in the archive.

To complete the investigation, Vasily took $ 2 $ large numbers $ x,y $ ( $ x<=y $ ) with the same number of digits and now he wants to find the number of numbers in the interval from $ x $ to $ y $ , which are half-occurrences in the archive. Help Vasily calculate this value modulo $ 10^{9}+7 $ .

## 输入格式

The first line contains string $ s $ consisting of decimal digits ( $ 1<=|s|<=1000 $ ) that Vasily will use to search substrings in. According to hypothesis, this sequence of digis indeed occurs in the decimal representation of $ π $ , although we can't guarantee that.

The second and third lines contain two positive integers $ x,y $ of the same length $ d $ ( $ x<=y $ , $ 2<=d<=50 $ ). Numbers $ x,y $ do not contain leading zeroes.

## 输出格式

Print how many numbers in the segment from $ x $ to $ y $ that are half-occurrences in $ s $ modulo $ 10^{9}+7 $ .

## 样例 #1

### 输入

```
02
10
19

```

### 输出

```
2

```

## 样例 #2

### 输入

```
023456789
10
19

```

### 输出

```
9

```

## 样例 #3

### 输入

```
31415926535
10
29

```

### 输出

```
20

```

