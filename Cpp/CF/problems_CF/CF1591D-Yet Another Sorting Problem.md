---
title: "Yet Another Sorting Problem"
layout: "post"
diff: 普及+/提高
pid: CF1591D
tag: []
---

# Yet Another Sorting Problem

## 题目描述

### 题意简述
给定一个数组 $a_1,a_2,\dots,a_n$，询问是否能用有限次操作使其单调不减。

这里将一次操作定义为将 $a_i,a_j,a_k$ （$i,j,k$ 互不相等）的值轮换，即将其分别设为 $a_j,a_k,a_i$。

## 输入格式

第一行一个整数 $t(1 \leq t \leq 5 \times 10^5)$，代表数据组数。

对于每一组数据，第一行一个整数 $n(1 \leq n \leq 5 \times 10^5)$，代表数组 $a$ 的长度，第二行 $n$ 个整数，代表 $a_1,a_2,\dots,a_n(1 \leq a_i \leq n)$。
保证 $\sum n \leq 5 \times 10^5$。

## 输出格式

输出共 $t$ 行，每行为一个字符串 "YES" 或 "NO"（大小写随意），代表第 $i$ 组数据的答案。
###### 翻译:@AFOI

## 样例 #1

### 输入

```
7
1
1
2
2 2
2
2 1
3
1 2 3
3
2 1 3
3
3 1 2
4
2 1 4 3
```

### 输出

```
YES
YES
NO
YES
NO
YES
YES
```

