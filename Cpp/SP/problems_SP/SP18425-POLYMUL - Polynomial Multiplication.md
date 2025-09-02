---
title: "POLYMUL - Polynomial Multiplication"
layout: "post"
diff: 提高+/省选-
pid: SP18425
tag: []
---

# POLYMUL - Polynomial Multiplication

## 题目描述

为了保护人类，Sam 和 Dean 去和超自然生物搏斗了。现在他们遇到了一种叫 Vedala 的生物，这种生物总时成对出现。两只 Vedala 都必须立刻（在 $1s$ 内——译者注）杀死，否则它们就会永生。只有使用代表两个 Vedala 的多项式的卷积才能同时杀死它们。请帮助 Sam 和 Dean 快速找到多项式的卷积，这样他们能够完成工作。

简化版题意：给定两个多项式，求它们的卷积。

## 输入格式

第一行一个正整数 $T(1\leq T\leq 10)$，表示数据组数。

接下来 $T$ 组数据，每组数据有：

- 第一行一个正整数 $n(n\leq 10000)$。
- 第二行 $n+1$ 个整数 $a_0,a_1,\cdots,a_n$，为表示第一只 Vedala 的多项式的各项系数。
- 第三行 $n+1$ 个整数 $b_0,b_1,\cdots,b_n$，为表示第二只 Vedala 的多项式的各项系数。

## 输出格式

输出 $T$ 行，每行 $2n+1$ 个整数，表示卷积后每一项的系数。

## 说明/提示

$\forall i\in\lbrack 0,n\rbrack,a_i,b_i\leq 1000$。

## 样例 #1

### 输入

```
2
2
1 2 3
3 2 1
2
1 0 1
2 1 0
```

### 输出

```
3 8 14 8 3
2 1 2 1 0
```

