---
title: "Coinage"
layout: "post"
diff: 难度0
pid: AT_relay2_g
tag: []
---

# Coinage

## 题目描述

给定一个正整数$N$和两个字符串$s,t$，你要求出长度为$N$的，字典序最小的字符串$A$，使得$A$可以由若干个$s$与若干个$t$拼接而成

## 输入格式

第一行：一个正整数$N$

第二行：字符串$s$

第三行：字符串$t$

## 输出格式

一行一个字符串$A$

## 说明/提示

$1\le |s|,|t|\le N\le 200000$

$s,t$仅包含小写英文字母

数据保证有解

### 样例$1$解释
$s=$`at`，$t=$`code`，$N=6$

可以组成`atatat`、`atcode`、`codeat`，其中字典序最小的是`atatat`

## 样例 #1

### 输入

```
6
at
code
```

### 输出

```
atatat
```

## 样例 #2

### 输入

```
8
coding
festival
```

### 输出

```
festival
```

## 样例 #3

### 输入

```
8
same
same
```

### 输出

```
samesame
```

## 样例 #4

### 输入

```
10
coin
age
```

### 输出

```
ageagecoin
```

