---
title: "You Are Given Some Letters..."
layout: "post"
diff: 省选/NOI-
pid: CF1202F
tag: []
---

# You Are Given Some Letters...

## 题目描述

给你一个 $a$ ，一个 $b$ ，让你找出所有字符串，满足它仅由 $a$ 个 _A_ 和 $b$ 个 _B_ ，并且分别求出它们的最小周期 $k$ （设该串为 $s$ ,即k满足s[i]=s[i%k]）。

输出共有多少不同的 $k$ 。

## 输入格式

输入一行两个数，即 $a$ , $b$ 。

## 输出格式

输入一行一个数，即 $k$ 的个数 。

# 样例解释

### 样例1：

四个可能：

	"BBABBA"  k = 3
 
    "BBAABB" k = 4

	"BBBAAB" k = 5

	"AABBBB" k = 6
### 样例2：

五个可能：

	 "BAABAABA" k = 3
	 "BAABABAA" k = 5
	 "BABAAABA" k = 6
	"BAABAAAB" k = 7
	"AAAAABBB" k = 8

## 样例 #1

### 输入

```
2 4

```

### 输出

```
4

```

## 样例 #2

### 输入

```
5 3

```

### 输出

```
5

```

