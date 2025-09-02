---
title: "[ABC374B] Unvarnished Report"
layout: "post"
diff: 入门
pid: AT_abc374_b
tag: ['字符串']
---

# [ABC374B] Unvarnished Report

## 题目描述

给定两个字符串 $s$ 和 $s1$，请求出两个字符串中的字符**第一次不相同**的位置是哪里。

如果两个字符串完全相同，请输出 $0$。

## 输入格式

第一行输入字符串 $s$。

第二行输入字符串 $s1$。

数据不保证 $|s|=|s1|$，其中 $|s|$ 和 $|s1|$ 分别表示 $s$ 和 $s1$ 的长度。

## 输出格式

共一行，输出两串字符串中的字符第一次不相同的位置（下标从 $1$ 开始），完全相同请输出 $0$。

Translation by @[ATION001](https://www.luogu.com.cn/user/1050501).

## 样例 #1

### 输入

```
abcde
abedc
```

### 输出

```
3
```

## 样例 #2

### 输入

```
abcde
abcdefg
```

### 输出

```
6
```

## 样例 #3

### 输入

```
keyence
keyence
```

### 输出

```
0
```

