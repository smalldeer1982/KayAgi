---
title: "The Child and Set"
layout: "post"
diff: 普及-
pid: CF437B
tag: []
---

# The Child and Set

## 题目描述

给你两个整数 $n,m$，要求选若干个不大于 $m$ 的数，使得这几个数的 Lowbit 值和等于 $n$。

## 输入格式

两个数 $n, m$。

## 输出格式

第一行：选了几个数。

第二行：这几个数，用空格分开，有多解输出任意一解，无解输出 $-1$。

**样例 \#1 解释**：$\operatorname {lowbit}(4)=4,\operatorname {lowbit}(5)=1$，$4+1=5$。

**样例 \#2 解释**：$\operatorname {lowbit}(2)=2,\operatorname {lowbit}(1)=1,\operatorname {lowbit}(3)=1$，$2+1+1=4$。

由 @Hjl1777 提供翻译

## 样例 #1

### 输入

```
5 5

```

### 输出

```
2
4 5

```

## 样例 #2

### 输入

```
4 3

```

### 输出

```
3
2 3 1

```

## 样例 #3

### 输入

```
5 1

```

### 输出

```
-1

```

