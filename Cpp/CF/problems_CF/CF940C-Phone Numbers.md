---
title: "Phone Numbers"
layout: "post"
diff: 普及/提高-
pid: CF940C
tag: ['字符串']
---

# Phone Numbers

## 题目描述

And where the are the phone numbers?

You are given a string $ s $ consisting of lowercase English letters and an integer $ k $ . Find the lexicographically smallest string $ t $ of length $ k $ , such that its set of letters is a subset of the set of letters of $ s $ and $ s $ is lexicographically smaller than $ t $ .

It's guaranteed that the answer exists.

Note that the set of letters is a set, not a multiset. For example, the set of letters of abadaba is $ {a,b,d} $ .

String $ p $ is lexicographically smaller than string $ q $ , if $ p $ is a prefix of $ q $ , is not equal to $ q $ or there exists $ i $ , such that $ p_{i}<q_{i} $ and for all $ j<i $ it is satisfied that $ p_{j}=q_{j} $ . For example, abc is lexicographically smaller than abcd , abd is lexicographically smaller than abec, afa is not lexicographically smaller than ab and a is not lexicographically smaller than a.

## 输入格式

The first line of input contains two space separated integers $ n $ and $ k $ ( $ 1<=n,k<=100000 $ ) — the length of $ s $ and the required length of $ t $ .

The second line of input contains the string $ s $ consisting of $ n $ lowercase English letters.

## 输出格式

Output the string $ t $ conforming to the requirements above.

It's guaranteed that the answer exists.

## 说明/提示

In the first example the list of strings $ t $ of length 3, such that the set of letters of $ t $ is a subset of letters of $ s $ is as follows: aaa, aab, aac, aba, abb, abc, aca, acb, $ ... $ . Among them, those are lexicographically greater than abc: aca, acb, $ ... $ . Out of those the lexicographically smallest is aca.

## 样例 #1

### 输入

```
3 3
abc

```

### 输出

```
aca

```

## 样例 #2

### 输入

```
3 2
abc

```

### 输出

```
ac

```

## 样例 #3

### 输入

```
3 3
ayy

```

### 输出

```
yaa

```

## 样例 #4

### 输入

```
2 3
ba

```

### 输出

```
baa

```

