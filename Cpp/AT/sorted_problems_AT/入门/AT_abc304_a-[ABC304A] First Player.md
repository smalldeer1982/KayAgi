---
title: "[ABC304A] First Player"
layout: "post"
diff: 入门
pid: AT_abc304_a
tag: []
---

# [ABC304A] First Player

## 题目描述

有 $N$ 个人站成一个圈，按顺时针分别编号为 $1\sim N$。依次给出他们的名字 $S_i$ 和年龄 $A_i$，且年龄互不相同，请你从最年轻的人开始，按顺时针方向依次输出每个人的名字。
- $2\le N\le100$
- $A_i$ 互不相同
- $S_i$ 互不相同
- $0\le A_i\le 10^9$
- $S_i$ 仅含有英语小写字母，且长度不超过 $10$

## 输入格式

第一行一个整数 $N$。

接下来 $N$ 行每行一个字符串 $S$ 和一个整数 $A$，第 $i+1$ 行表示编号为 $i$ 的人的名字和年龄。

## 输出格式

共 $N$ 行，每行一个字符串表示输出的名字。

## 样例 #1

### 输入

```
5
alice 31
bob 41
carol 5
dave 92
ellen 65
```

### 输出

```
carol
dave
ellen
alice
bob
```

## 样例 #2

### 输入

```
2
takahashi 1000000000
aoki 999999999
```

### 输出

```
aoki
takahashi
```

