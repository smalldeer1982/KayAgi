---
title: "Concatenation with intersection"
layout: "post"
diff: 省选/NOI-
pid: CF1313E
tag: []
---

# Concatenation with intersection

## 题目描述

给定三个串 $a,b,s$，其中 $a,b$ 长度为 $n$，$s$ 长度为 $m$，求出四元组 $(l1,r1,l2,r2)$ 的个数，满足：

1. $[l1,r1]$ 和 $[l2,r2]$ 的交集非空。

2. $a$ 中位置 $l1$ 到 $r1$ 组成的子串与 $b$ 中位置 $l2$ 到 $r2$ 组成的子串拼起来恰好是 $s$。

$1 \leq n \leq 500000$，$2 \leq m \leq 2n$。

## 输入格式

第一行两个整数 $n,m$。

第二行一个字符串 $a$。

第三行一个字符串 $b$。

第四行一个字符串 $s$。

## 输出格式

输出一个整数表示四元组的个数。

## 样例 #1

### 输入

```
6 5
aabbaa
baaaab
aaaaa
```

### 输出

```
4
```

## 样例 #2

### 输入

```
5 4
azaza
zazaz
azaz
```

### 输出

```
11
```

## 样例 #3

### 输入

```
9 12
abcabcabc
xyzxyzxyz
abcabcayzxyz
```

### 输出

```
2
```

