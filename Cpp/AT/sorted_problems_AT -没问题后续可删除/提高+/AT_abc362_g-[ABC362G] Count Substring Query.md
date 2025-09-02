---
title: "[ABC362G] Count Substring Query"
layout: "post"
diff: 提高+/省选-
pid: AT_abc362_g
tag: ['AC 自动机']
---

# [ABC362G] Count Substring Query

## 题目描述

### 题意
给你一个字符串 $S$ 和 $Q$ 个字符串， $T_1$ ~ $T_q$ ,问每一个 $T_i$ 分别在 $S$ 中出现多少次。

## 输入格式

第一行一个字符串 $S$ 。		

第二行一个数字 $Q$ ，表示接下来会有 $Q$ 个字符串。	

下面 $Q$ 行每行一个字符串，表示数组     $T_i$ 。

## 输出格式

共输出 $n$ 行，每行一个数，第$i$行的数字表示 $T_i$ 在 $S$ 中出现的次数。

## 样例 #1

### 输入

```
missisippi
5
i
s
a
is
missisippi
```

### 输出

```
4
3
0
2
1
```

## 样例 #2

### 输入

```
aaaaaa
6
a
aa
aaa
aaaa
aaaaa
aaaaaa
```

### 输出

```
6
5
4
3
2
1
```

