---
title: "Minimum path"
layout: "post"
diff: 普及+/提高
pid: CF1031D
tag: ['广度优先搜索 BFS', '深度优先搜索 DFS']
---

# Minimum path

## 题目描述

给你一个n×n的全是小写字母的矩阵,你能改变k个字母

你要从左上角走到右下角,且每步只能移动到右边或下边的字母上。

对于每一条路径都会得到一个由你经过的所有字母组成的字符串。当然,他的长度是2×n-1.

在你最多改动k个字母的情况下,找到一个得到字符串字典序最小的路径.

一个字符串a如果字典序比字符串b小,那他们第一个不同的字符在a中小于b.

## 输入格式

第一行包括两个整数n和k(1≤n≤2000,0≤k≤n2),矩阵的大小和你最多能改变的字母数.

下面n行,每行n个小写字母.

## 输出格式

在你最多改动k个字母的情况下,得到的一个字符串字典序最小的路径.

## 样例 #1

### 输入

```
4 2
abcd
bcde
bcad
bcde

```

### 输出

```
aaabcde

```

## 样例 #2

### 输入

```
5 3
bwwwz
hrhdh
sepsp
sqfaf
ajbvw

```

### 输出

```
aaaepfafw

```

## 样例 #3

### 输入

```
7 6
ypnxnnp
pnxonpm
nxanpou
xnnpmud
nhtdudu
npmuduh
pmutsnz

```

### 输出

```
aaaaaaadudsnz

```

