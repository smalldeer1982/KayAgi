---
title: "[ABC314D] LOWER"
layout: "post"
diff: 普及/提高-
pid: AT_abc314_d
tag: ['模拟']
---

# [ABC314D] LOWER

## 题目描述

给定一个由英文字母大写和小写字母组成的长度为 $N$ 的字符串 $S$。

接下来，将对字符串 $S$ 进行 $Q$ 次操作。第 $i$ 次操作（$1 \le i \le Q$）由两个整数和一个字符组成的三元组 $(t _ i, x _ i, c _ i)$ 表示，每种操作的含义如下：

- 当 $t _ i = 1$ 时，将 $S$ 的第 $x _ i$ 个字符修改为 $c _ i$。
- 当 $t _ i = 2$ 时，将 $S$ 中的所有大写字母全部转为小写（$x _ i$ 和 $c _ i$ 在此操作中不使用）。
- 当 $t _ i = 3$ 时，将 $S$ 中的所有小写字母全部转为大写（$x _ i$ 和 $c _ i$ 在此操作中不使用）。

输出经过 $Q$ 次操作后的字符串 $S$。

## 输入格式

输入以以下格式从标准输入中提供。

> $ N $  
> $ S $  
> $ Q $  
> $t _ 1$ $x _ 1$ $c _ 1$  
> $t _ 2$ $x _ 2$ $c _ 2$  
> $\vdots$  
> $t _ Q$ $x _ Q$ $c _ Q$

## 输出格式

在 $1$ 行中输出答案。

### 限制条件

- $1 \leq N \leq 5 \times 10 ^ 5$
- $S$ 是由大写字母和小写字母组成的长度为 $N$ 的字符串
- $1 \leq Q \leq 5 \times 10 ^ 5$
- $1 \leq t _ i \leq 3 \ (1 \leq i \leq Q)$
- 如果 $t _ i = 1$，则 $1 \leq x _ i \leq N \ (1 \leq i \leq Q)$
- $c _ i$ 是大写字母或小写字母
- 如果 $t _ i \neq 1$，则 $x _ i = 0$ 且 $c _ i = $ `'a'`
- $N, Q, t _ i, x _ i$ 均为整数

### 样例解释 1

初始时，字符串 $S$ 是 `AtCoder`。

- 第 $1$ 次操作，将第 $4$ 个字符修改为 `i`。修改后的 $S$ 是 `AtCider`。
- 第 $2$ 次操作，将所有小写字母转换为大写字母。修改后的 $S$ 是 `ATCIDER`。
- 第 $3$ 次操作，将第 $5$ 个字符修改为 `b`。修改后的 $S$ 是 `ATCIbER`。
- 第 $4$ 次操作，将所有大写字母转换为小写字母。修改后的 $S$ 是 `atciber`。
- 第 $5$ 次操作，将第 $4$ 个字符修改为 `Y`。修改后的 $S$ 是 `atcYber`。

所有操作结束后，字符串 $S$ 是 `atcYber`，因此输出 `atcYber`。

---

Translated by User 735713.

## 样例 #1

### 输入

```
7
AtCoder
5
1 4 i
3 0 a
1 5 b
2 0 a
1 4 Y
```

### 输出

```
atcYber
```

## 样例 #2

### 输入

```
35
TheQuickBrownFoxJumpsOverTheLazyDog
10
2 0 a
1 19 G
1 13 m
1 2 E
1 21 F
2 0 a
1 27 b
3 0 a
3 0 a
1 15 i
```

### 输出

```
TEEQUICKBROWMFiXJUGPFOVERTBELAZYDOG
```

