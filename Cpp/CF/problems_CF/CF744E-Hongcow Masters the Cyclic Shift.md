---
title: "Hongcow Masters the Cyclic Shift"
layout: "post"
diff: NOI/NOI+/CTSC
pid: CF744E
tag: []
---

# Hongcow Masters the Cyclic Shift

## 题目描述

Hongcow's teacher heard that Hongcow had learned about the cyclic shift, and decided to set the following problem for him.

You are given a list of $ n $ strings $ s_{1},s_{2},...,s_{n} $ contained in the list $ A $ .

A list $ X $ of strings is called stable if the following condition holds.

First, a message is defined as a concatenation of some elements of the list $ X $ . You can use an arbitrary element as many times as you want, and you may concatenate these elements in any arbitrary order. Let $ S_{X} $ denote the set of of all messages you can construct from the list. Of course, this set has infinite size if your list is nonempty.

Call a single message good if the following conditions hold:

- Suppose the message is the concatenation of $ k $ strings $ w_{1},w_{2},...,w_{k} $ , where each $ w_{i} $ is an element of $ X $ .
- Consider the $ |w_{1}|+|w_{2}|+...+|w_{k}| $ cyclic shifts of the string. Let $ m $ be the number of these cyclic shifts of the string that are elements of $ S_{X} $ .
- A message is good if and only if $ m $ is exactly equal to $ k $ .

The list $ X $ is called stable if and only if every element of $ S_{X} $ is good.

Let $ f(L) $ be $ 1 $ if $ L $ is a stable list, and $ 0 $ otherwise.

Find the sum of $ f(L) $ where $ L $ is a nonempty contiguous sublist of $ A $ (there are ![](https://cdn.luogu.com.cn/upload/vjudge_pic/CF744E/e3b4fb96ad236b842d8223d40fcab7d30a68cb22.png) contiguous sublists in total).

## 输入格式

The first line of input will contain a single integer $ n $ ( $ 1<=n<=30 $ ), denoting the number of strings in the list.

The next $ n $ lines will each contain a string $ s_{i} $ (![](https://cdn.luogu.com.cn/upload/vjudge_pic/CF744E/aa511b29228806a7ab9d89d220f5a75566cfa547.png)).

## 输出格式

Print a single integer, the number of nonempty contiguous sublists that are stable.

## 说明/提示

For the first sample, there are $ 10 $ sublists to consider. Sublists \["a", "ab", "b"\], \["ab", "b", "bba"\], and \["a", "ab", "b", "bba"\] are not stable. The other seven sublists are stable.

For example, $ X $ = \["a", "ab", "b"\] is not stable, since the message "ab" + "ab" = "abab" has four cyclic shifts \["abab", "baba", "abab", "baba"\], which are all elements of $ S_{X} $ .

## 样例 #1

### 输入

```
4
a
ab
b
bba

```

### 输出

```
7

```

## 样例 #2

### 输入

```
5
hh
ee
ll
ll
oo

```

### 输出

```
0

```

## 样例 #3

### 输入

```
6
aab
ab
bba
b
ab
c

```

### 输出

```
13

```

