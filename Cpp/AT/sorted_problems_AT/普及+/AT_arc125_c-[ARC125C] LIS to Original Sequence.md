---
title: "[ARC125C] LIS to Original Sequence"
layout: "post"
diff: 普及+/提高
pid: AT_arc125_c
tag: []
---

# [ARC125C] LIS to Original Sequence

## 题目描述

# [ARC125C] LIS to Original Sequence


[problemUrl]: https://atcoder.jp/contests/arc125/tasks/arc125_c

给定一个长度为 $k$ 的序列 $A_1,A_2,\cdots,A_n$，试求出长度为 $n$ 的序列 $P$，使得 $P$ 的最长上升子序列为 $A_1,A_2,\cdots,A_n$，且 $P$ 的字典序最小。


## 样例 #1

### 样例输入 #1

```
3 2
2 3
```

### 样例输出 #1

```
2 1 3
```

## 样例 #2

### 样例输入 #2

```
5 1
4
```

### 样例输出 #2

```
5 4 3 2 1
```

## 输入格式

第一行两个用空格隔开的整数 $n,k$。

第二行 $n$ 个整数，分别为 $A_1,A_2,\cdots,A_n$。

## 说明/提示

- $ 1\ \leq\ K\ \leq\ N\ \leq\ 2\ \times\ 10^5 $
- $ 1\ \leq\ A_1\ <\ A_2\ <\ \cdots\ <\ A_K\ \leq\ N $
- 输入的所有值均为整数。

### 样例一解释

当 $P=（2，1，3）$ 或 $（2，3，1）$ 时，$P$ 的最长上升子序列与 $A$ 一样。 其中，$（2，1，3）$的字典序最小。

## 样例 #1

### 输入

```
3 2
2 3
```

### 输出

```
2 1 3
```

## 样例 #2

### 输入

```
5 1
4
```

### 输出

```
5 4 3 2 1
```

