---
title: "Swap and Reverse"
layout: "post"
diff: 入门
pid: CF1864B
tag: []
---

# Swap and Reverse

## 题目描述

本题共有 $t$ 组数据。

给定一个长度为 $n$ 的字符串 $s$ 和一个整数 $k$，$s$ 只包含小写字母，你可以进行若干次操作（可以是零次），具体操作如下：

- 选取一个 $i$（$1\le i\le n-2$），交换 $a_i$ 和 $a_{i+2}$

- 选取一个 $i$（$1\le i\le n-k+1$），翻转区间 $s_{[i,i+k-1]}$。如果 $s=s_1,s_2,\dots,s_{i-1},s_i,s_{i+1},\dots,s_{i+k-2},s_{i+k-1},s_{i+k},\dots,s_{n-1},s_n$，可将其改为：$s=s_1,s_2,\dots,s_{i-1},s_{i+k-1},s_{i+k-2},\dots,s_{i+1},s_i,s_{i+k},\dots,s_{n-1},s_n$

输出经过若干次操作后得到的的按字典顺序排列的最小字符串。

## 输入格式

第一行包含一个正整数 $t$，具体含义见上。

第二行包含两个正整数 $n$ 和 $k$。

接下来一行 包含一个长度为 $n$ 的字符串 $s$。

## 输出格式

对于每个测试用例，在进行若干次操作后输出按字典顺序排列的最小字符串。

## 说明/提示

$1\le t\le10^4,1\le k\le n\le10^5$。

Translate by @[Moss\_spresd](https://www.luogu.com.cn/user/718169)

## 样例 #1

### 输入

```
5
4 2
nima
5 3
panda
9 2
theforces
7 3
amirfar
6 4
rounds
```

### 输出

```
aimn
aandp
ceefhorst
aafmirr
dnorsu
```

