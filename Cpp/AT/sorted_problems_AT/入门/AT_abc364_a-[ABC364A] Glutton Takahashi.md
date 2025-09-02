---
title: "[ABC364A] Glutton Takahashi"
layout: "post"
diff: 入门
pid: AT_abc364_a
tag: []
---

# [ABC364A] Glutton Takahashi

## 题目描述

高桥君有 $N$ 盘菜，他会按顺序吃掉这些菜。一盘菜要么是甜的，要么是咸的。如果他连续吃了两盘甜的菜，那么他就不再吃菜。如果他能吃完所有的菜，输出 `Yes`，否则，输出 `No`。

## 输入格式

输入共 $N+1$ 行。

第一行一个整数 $N$，表示菜的数量。

接下来 $N$ 行，第 $i$ 行一个字符串 $S_i$。若 $S_i \ = $ `sweet`，表示这盘菜是甜的，若 $S_i \ = $ `salty`，表示这盘菜是咸的。

## 输出格式

输出一行，一个字符串，`Yes` 或 `No`。

## 样例 #1

### 输入

```
5
salty
sweet
salty
salty
sweet
```

### 输出

```
Yes
```

## 样例 #2

### 输入

```
4
sweet
salty
sweet
sweet
```

### 输出

```
Yes
```

## 样例 #3

### 输入

```
6
salty
sweet
sweet
salty
sweet
sweet
```

### 输出

```
No
```

