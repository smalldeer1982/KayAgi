---
title: "Swapping Characters"
layout: "post"
diff: 省选/NOI-
pid: CF903E
tag: []
---

# Swapping Characters

## 题目描述

给你 $k$ 个串，每个串长度都是 $n$，现在问你是否可能这些串是同一个串交换两个位置的字符所产生的，输出这个原串。

## 输入格式

第一行包含两个整数 $k$ 和 $n$ —我们获得的字符串数，以及每个字符串的长度。接下来的 $k$ 行包含字符串 $s_1$，$s_2$，$s_3$，... ，$s_k$ 每个字符串均由 $n$ 个小写拉丁字母组成。

## 输出格式

输出原串，如果不存在则输出"-1"。

## 样例 #1

### 输入

```
3 4
abac
caab
acba

```

### 输出

```
acab

```

## 样例 #2

### 输入

```
3 4
kbbu
kbub
ubkb

```

### 输出

```
kbub

```

## 样例 #3

### 输入

```
5 4
abcd
dcba
acbd
dbca
zzzz

```

### 输出

```
-1

```

