---
title: "[ABC254C] K Swap"
layout: "post"
diff: 普及-
pid: AT_abc254_c
tag: []
---

# [ABC254C] K Swap

## 题目描述

## 题目翻译

给出一个长为 $n$ 的数列 $a_1, a_2, \cdots, a_n$。再给一个整数 $k$。

每次可以选一个下标 $i$（$1 \le i \le n - k$），将 $a_i$ 和 $a_{i + k}$ 交换。

问能否通过交换让数列 $a$ 成为升序（任意 $a_i \le a_{i  +1}$）？

translate by @[liangbowen](https://www.luogu.com.cn/user/367488)。

## 输入格式

输入包括两行，第一行有 $2$ 个正整数 $n, k$。

第二行有 $n$ 个正整数 $a_1, a_2, \cdots, a_n$。

## 输出格式

如果可以通过交换变成升序，输出 $\texttt{Yes}$。不能变成升序，输出 $\texttt{No}$。

## 说明/提示

$2 \le n \le 2 \times 10^5$；$1 \le k \le n - 1$；$1 \le a_i \le 10^9$。

## 样例 #1

### 输入

```
5 2
3 4 1 3 4
```

### 输出

```
Yes
```

## 样例 #2

### 输入

```
5 3
3 4 1 3 4
```

### 输出

```
No
```

## 样例 #3

### 输入

```
7 5
1 2 3 4 5 5 10
```

### 输出

```
Yes
```

