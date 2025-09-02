---
title: "Puzzle"
layout: "post"
diff: 难度0
pid: UVA1399
tag: []
---

# Puzzle

## 题目描述

给定 m 和 n，表示有 m 种不同的字符（大写字母 A,B,C...），n 个禁止串，请构造一个不包含任何禁止串的最长字符串并将其输出。

## 输入格式

第一行一个整数T表示数据组数。

每组数据第一行为两个整数 m 和 n，接下来 n 行输入 n 个禁止串。

## 输出格式

输出这个最长字符串。

如果可以无限长或者无解则输出 No，如果存在多解则输出字典序最大的一种。

**【样例输入】**

```cpp
3
2 4
AAA
AB
BA
BB
2 4
AAA
BBB
ABAB
BBAA
3 7
AA
ABA
BAC
BB
BC
CA
CC
```

**【样例输出】**

```cpp
AA
No
ACBAB
```

