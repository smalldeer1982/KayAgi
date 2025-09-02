---
title: "Au Pont Rouge"
layout: "post"
diff: 省选/NOI-
pid: CF1310C
tag: []
---

# Au Pont Rouge

## 题目描述

VK just opened its second HQ in St. Petersburg! Side of its office building has a huge string $ s $ written on its side. This part of the office is supposed to be split into $ m $ meeting rooms in such way that meeting room walls are strictly between letters on the building. Obviously, meeting rooms should not be of size 0, but can be as small as one letter wide. Each meeting room will be named after the substring of $ s $ written on its side.

![](https://cdn.luogu.com.cn/upload/vjudge_pic/CF1310C/3f4208069ef8a30005bed865124fbaec7ac1508a.png)For each possible arrangement of $ m $ meeting rooms we ordered a test meeting room label for the meeting room with lexicographically minimal name. When delivered, those labels got sorted backward lexicographically.

What is printed on $ k $ th label of the delivery?

## 输入格式

In the first line, you are given three integer numbers $ n, m, k $ — length of string $ s $ , number of planned meeting rooms to split $ s $ into and number of the interesting label ( $ 2 \le n \le 1\,000; 1 \le m \le 1\,000; 1 \le k \le 10^{18} $ ).

Second input line has string $ s $ , consisting of $ n $ lowercase english letters.

For given $ n, m, k $ there are at least $ k $ ways to split $ s $ into $ m $ substrings.

## 输出格式

Output single string – name of meeting room printed on $ k $ -th label of the delivery.

## 说明/提示

In the first example, delivery consists of the labels "aba", "ab", "a".

In the second example, delivery consists of $ 3060 $ labels. The first label is "aupontrougevkof" and the last one is "a".

## 样例 #1

### 输入

```
4 2 1
abac
```

### 输出

```
aba
```

## 样例 #2

### 输入

```
19 5 1821
aupontrougevkoffice
```

### 输出

```
au
```

