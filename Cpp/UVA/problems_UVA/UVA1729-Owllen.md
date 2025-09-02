---
title: "Owllen"
layout: "post"
diff: 难度0
pid: UVA1729
tag: []
---

# Owllen

## 题目描述

有多组询问，每组询问给出一个长度为 $N(1\leq N\leq10^5)$ 的字符串 $S$，然后构造一个长度也为 $N$ 的字符串 $T$，使得 $\mathrm{LCS}(S, T)$ 的值最小，输出这个最小值。

## 输入格式

第一行为数据组数 $T(1\leq T \leq 50)$；

接下来 $T$ 行，每行一个字符串 $S$。

## 输出格式

对于每组输入，按照 `Case X: Y` 的格式输出，其中 $X$ 表示这是第几组数据，$Y$ 表示 $\min(\mathrm{LCS}(S, T))$。

## 输入样例

```c++
2
ab
efzadeuopqxrvwxaghijklmnbcastbqy
```

## 输出样例

```c++
Case 1: 0
Case 2: 1
```

